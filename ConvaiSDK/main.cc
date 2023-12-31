#include "audio.h"
#include "interaction.h"
#include "proto_utils.h"
#include <Windows.h>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <mmreg.h>
#include <sstream>
#include <string>
#pragma comment(lib, "winmm.lib")
#pragma pack(push, 1)

using convai_sdk::Audio;
using convai_sdk::FRAMES_PER_BUFFER;
using convai_sdk::Interaction;
using convai_sdk::RECORD_SECONDS;
using convai_sdk::SAMPLING_RATE;
using convai_sdk::proto_util::GetResponseConfigFromFile;
using service::GetResponseRequest;
using service::GetResponseResponse;

std::unordered_map<std::string, std::string> vars = {
    {"API", "Path/to/get_response_config_example.txt"},   // Update the path name
    {"SKSE", "Path/to/SKSE_Code/"},   // update the path name
    {"MOD_DIR", "C:/Program Files (x86)/Steam/steamapps/common/Skyrim Special Edition/Data/Sound/Voice/convaiNPCMod.esp/"}   // update the path if the game is installed in a different location than default
};

static constexpr int WAV_HEADER_SIZE = 44;
static constexpr char GET_RESPONSE_CONFIG_FILE[] = "Path/to/get_response_config_example.txt";//Update the path name

int ind = 0;
std::string respText, query, dir;
std::vector<std::string> files;


void ConcatenateByteStreamsToWav(const std::vector<std::string> &byteStreams,
                                 const std::string &outputFilePath) {
  std::ofstream outputFile(outputFilePath, std::ios::binary);

  if (!outputFile) {
    return;
  }

  // Calculate total size of the concatenated byte streams
  size_t totalSize = 0;
  for (const auto &byteStream : byteStreams) {
    totalSize += byteStream.size();
  }

  // Write the WAV header
  outputFile.write("RIFF", 4);   // RIFF chunk
  outputFile.write(reinterpret_cast<const char *>(&totalSize),
                   4);           // Chunk size
  outputFile.write("WAVE", 4);   // WAVE chunk

  outputFile.write("fmt ", 4);   // fmt subchunk
  uint32_t subchunkSize = 16;    // Subchunk size
  outputFile.write(reinterpret_cast<const char *>(&subchunkSize), 4);
  uint16_t audioFormat = 1;   // Audio format (PCM)
  outputFile.write(reinterpret_cast<const char *>(&audioFormat), 2);
  uint16_t numChannels = 1;   // Number of channels
  outputFile.write(reinterpret_cast<const char *>(&numChannels), 2);
  uint32_t sampleRate = 44100;   // Sample rate (Hz)
  outputFile.write(reinterpret_cast<const char *>(&sampleRate), 4);
  uint32_t byteRate =
      sampleRate * numChannels * 2;   // Byte rate (bytes/second)
  outputFile.write(reinterpret_cast<const char *>(&byteRate), 4);
  uint16_t blockAlign = numChannels * 2;   // Block align
  outputFile.write(reinterpret_cast<const char *>(&blockAlign), 2);
  uint16_t bitsPerSample = 16;   // Bits per sample
  outputFile.write(reinterpret_cast<const char *>(&bitsPerSample), 2);

  outputFile.write("data", 4);   // data subchunk
  outputFile.write(reinterpret_cast<const char *>(&totalSize),
                   4);   // Subchunk size

  // Concatenate the byte streams and write to the output file
  for (const auto &byteStream : byteStreams) {
    outputFile.write(byteStream.c_str(), byteStream.size());
  }

  outputFile.close();
}

void editCharacterIdValue(std::string &fileContent,
                          const std::string &newCharacterId) {
  size_t startPos = fileContent.find("character_id: ");
  if (startPos != std::string::npos) {
    startPos += 15;   // Length of "character_id: "
    size_t endPos = fileContent.find_first_of("\"", startPos);
    if (endPos != std::string::npos) {
      fileContent.replace(startPos, endPos - startPos, newCharacterId);
    }
  }
}

void selectCharacter(std::string charID) {
  std::ifstream file(vars["API"]);
  if (file.is_open()) {
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    std::string fileContent = buffer.str();

    // Find and modify the character_id value (replace it with a new value)
    std::string newCharacterId =
        charID;   // Replace with the desired new character_id
    editCharacterIdValue(fileContent, newCharacterId);

    // Write the updated content back to the file
    std::ofstream outFile(vars["API"]);
    if (outFile.is_open()) {
      outFile << fileContent;
      outFile.close();
    }
  }
}

int main() {
  std::string inputFile = vars["SKSE"] + "inputFile.txt";
  std::fstream newfile;
  newfile.open(inputFile, std::ios::in);
  std::string charName;
  std::getline(newfile, charName);
  selectCharacter(charName);
  newfile.close();

  std::string outputFile = vars["SKSE"] + "outputFile.txt";
  std::fstream outfile;
  outfile.open(outputFile, std::ios::in);
  std::getline(outfile, dir);
  outfile.close();

  GetResponseRequest::GetResponseConfig get_response_config =
      GetResponseConfigFromFile(GET_RESPONSE_CONFIG_FILE);
  Audio audio_in;
  Audio audio_out;
  Interaction interaction(get_response_config);

  std::string transcript = "";
  std::string temp_transcript = "";
  respText = "";
  interaction.Start(
      /*response_callback=*/[&audio_out, &get_response_config, &transcript,
                             &temp_transcript](GetResponseResponse resp) {
        if (resp.has_user_query()) {
          auto user_query = resp.user_query();
          if (user_query.is_final()) {
            transcript += user_query.text_data();
            temp_transcript = "";
          } else {
            temp_transcript = user_query.text_data();
            query = temp_transcript;
          }
        } 
        else if (resp.has_audio_response()) {
          if (get_response_config.session_id() == "") {
            get_response_config.set_session_id(resp.session_id());
          }

          respText += resp.audio_response().text_data();
          if (resp.audio_response().end_of_response()) {
            std::cout << respText << std::endl;
          }

          if (resp.audio_response().audio_data() != "") {
            const std::string audio_d =
                resp.audio_response().audio_data().substr(WAV_HEADER_SIZE);

            std::string byteStream = resp.audio_response().audio_data();
            files.push_back(byteStream);
          }
        }
      });

  audio_in.Start();
  for (int i = 0; i < (SAMPLING_RATE / FRAMES_PER_BUFFER * RECORD_SECONDS);
       ++i) {
    int16_t buffer[FRAMES_PER_BUFFER];
    audio_in.ReadBuffer(buffer);
    char *audio_data = (char *) buffer;
    int length = FRAMES_PER_BUFFER * sizeof(int16_t) / sizeof(char);
    interaction.SendAudio(audio_data, length);
  }
  audio_in.Close();
  auto status = interaction.Stop();
  if (audio_out.Started()) {
    audio_out.Close();
  }
  if (!status.ok()) {
    exit(1);
  }

  std::string outputFileName =
      vars["MOD_DIR"] + dir + "/convaiQues_convaiQuestDial_00000804_1.wav";
  ConcatenateByteStreamsToWav(files, outputFileName);
  files.clear();
  return 0;
}
