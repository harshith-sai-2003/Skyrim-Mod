#include <spdlog/sinks/basic_file_sink.h>
#define MAX_SIZE 16382

namespace logger = SKSE::log;

std::unordered_map<std::string, std::string> vars = {
    {"SKSE_DIR", "Path/to/SKSE_Code/"}, //Update path
    {"CONVAI_DIR", "Path/to/ConvaiSDK/"}, //Update path
    {"MOD_DIR", "C:/Program Files (x86)/Steam/steamapps/common/Skyrim Special Edition/Data/Sound/Voice/convaiNPCMod.esp/"} //Update if game is installed in a different location than default
};

std::unordered_map<std::string, std::pair<std::string, std::string>> mp = {
    {"Abelone", {"279cda0a-2c5e-11ee-9df5-42010a40000b", "FemaleCommoner"}},
    {"Acolyte Jenssen", {"29c589e4-2c5e-11ee-ae56-42010a40000b", "MaleNord"}},
    {"Addvar", {"2bf67354-2c5e-11ee-b931-42010a40000b", "MaleCommonerAccented"}},
    {"Addvild", {"2e2952ea-2c5e-11ee-af47-42010a40000b", "MaleCommonerAccented"}},
    {"Adeber", {"3068c478-2c5e-11ee-b1c8-42010a40000b", "MaleCommoner"}},
    {"Adelaisa Vendicci", {"323e691a-2c5e-11ee-8b50-42010a40000b", "FemaleCommander"}},
    {"Adisla", {"341320fa-2c5e-11ee-bf15-42010a40000b", "FemaleCommoner"}},
    {"Adonato Leotelli", {"35e8b4c6-2c5e-11ee-8c15-42010a40000b", "MaleCondescending"}},
    {"Adrianne Avenicci", {"3821d024-2c5e-11ee-ad7d-42010a40000b", "FemaleCommander"}},
    {"Aduri Sarethi", {"3a4d8348-2c5e-11ee-bdec-42010a40000b", "FemaleYoungEager"}},
    {"Aela the Huntress", {"3c7fc0a4-2c5e-11ee-923a-42010a40000b", "FemaleCommander"}},
    {"Aeri", {"3eb270d8-2c5e-11ee-97b2-42010a40000b", "MaleYoungEager"}},
    {"Aerin", {"40e0454c-2c5e-11ee-97a0-42010a40000b", "MaleYoungEager"}},
    {"Agna", {"4307a2f2-2c5e-11ee-8460-42010a40000b", "MaleCommonerAccented"}},
    {"Agni", {"453b20ee-2c5e-11ee-997e-42010a40000b", "FemaleOldKindly"}},
    {"Agnis", {"4768afe4-2c5e-11ee-a063-42010a40000b", "FemaleOldKindly"}},
    {"Ahjisi", {"49c294e4-2c5e-11ee-8a9e-42010a40000b", "FemaleKhajiit"}},
    {"Ahkari", {"4bf40856-2c5e-11ee-8447-42010a40000b", "FemaleKhajiit"}},
    {"Ahtar", {"4e28d304-2c5e-11ee-8956-42010a40000b", "MaleBrute"}},
    {"Aia Arria", {"50502790-2c5e-11ee-b8c9-42010a40000b", "FemaleSultry"}},
    {"Aicantar", {"527aa72a-2c5e-11ee-835c-42010a40000b", "MaleEvenToned"}},
    {"Ainethach", {"54a8cc48-2c5e-11ee-b9aa-42010a40000b", "MaleEvenToned"}},
    {"Alain Dufont", {"56d64126-2c5e-11ee-ad7f-42010a40000b", "MaleSlyCynical"}},
    {"Alding", {"5909f0fa-2c5e-11ee-be65-42010a40000b", "MaleDrunk"}},
    {"Alea Quintus", {"5b385bdc-2c5e-11ee-9f1d-42010a40000b", "FemaleShrill"}},
    {"Alessandra", {"5d6700e8-2c5e-11ee-86f9-42010a40000b", "FemaleEvenToned"}},
    {"Alexia Vici", {"5f96720e-2c5e-11ee-8b48-42010a40000b", "FemaleOldKindly"}},
    {"Alfarinn", {"61ca55fe-2c5e-11ee-a598-42010a40000b", "MaleCommonerAccented"}},
    {"Alva", {"63fb86ea-2c5e-11ee-9047-42010a40000b", "MaleYoungEager"}},
    {"Alvor", {"663238be-2c5e-11ee-b5df-42010a40000b", "MaleNord"}},
    {"Amaund Motierre", {"686aa3d2-2c5e-11ee-998d-42010a40000b", "MaleUniqueAncano"}},
    {"Ambarys Rendar", {"6aa50ec6-2c5e-11ee-904b-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Amren", {"6cda9fee-2c5e-11ee-92fa-42010a40000b", "MaleEvenToned"}},
    {"Ancano", {"6f0e2074-2c5e-11ee-91b4-42010a40000b", "MaleUniqueAncano"}},
    {"Andurs", {"7124ab30-2c5e-11ee-8762-42010a40000b", "MaleSlyCynical"}},
    {"Angeline Morrard", {"73526406-2c5e-11ee-92ad-42010a40000b", "FemaleOldKindly"}},
    {"Angi", {"757ee1b4-2c5e-11ee-862f-42010a40000b", "FemaleNord"}},
    {"Angvid", {"77b28152-2c5e-11ee-8c44-42010a40000b", "MaleEvenTonedAccented"}},
    {"Anise", {"79ddce46-2c5e-11ee-bce0-42010a40000b", "FemaleOldKindly"}},
    {"Anoriath", {"7c0a0518-2c5e-11ee-9f7b-42010a40000b", "MaleYoungEager"}},
    {"Anska", {"7e33ffd8-2c5e-11ee-971c-42010a40000b", "FemaleNord"}},
    {"Anton Virane", {"806756d8-2c5e-11ee-9d8e-42010a40000b", "MaleCondescending"}},
    {"Anuriel", {"8296698a-2c5e-11ee-bae3-42010a40000b", "FemaleEvenToned"}},
    {"Anwen", {"84ca5ffe-2c5e-11ee-a66e-42010a40000b", "FemaleCondescending"}},
    {"Aquillius Aeresius", {"87074cd2-2c5e-11ee-8b61-42010a40000b", "MaleEvenToned"}},
    {"Aranea Ienith", {"893a2844-2c5e-11ee-9cd7-42010a40000b", "FemaleDarkElf"}},
    {"Arcadia", {"8b6c7d6a-2c5e-11ee-9eaf-42010a40000b", "FemaleEvenToned"}},
    {"Arcturus", {"8d9f800a-2c5e-11ee-92eb-42010a40000b", "MaleSoldier"}},
    {"Ardwen", {"8fc95ebe-2c5e-11ee-92ec-42010a40000b", "FemaleElfHaughty"}},
    {"Argis the Bulwark", {"91f3a3ac-2c5e-11ee-8bce-42010a40000b", "MaleBrute"}},
    {"Aringoth", {"941e1c20-2c5e-11ee-a55a-42010a40000b", "MaleElfHaughty"}},
    {"Arivanya", {"964764ac-2c5e-11ee-949d-42010a40000b", "FemaleEvenToned"}},
    {"Arnbjorn", {"987300a6-2c5e-11ee-84c3-42010a40000b", "MaleBrute"}},
    {"Arngeir", {"9aa129d4-2c5e-11ee-b11d-42010a40000b", "MaleUniqueArngeir"}},
    {"Arniel Gane", {"9cd07354-2c5e-11ee-aec4-42010a40000b", "MaleCoward"}},
    {"Arob", {"9f031942-2c5e-11ee-aec1-42010a40000b", "FemaleOrc"}},
    {"Arondil", {"a0dd70fa-2c5e-11ee-acf6-42010a40000b", "MaleElfHaughty"}},
    {"Arvel the Swift", {"a30e9818-2c5e-11ee-8b91-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Aslfur", {"a53bc250-2c5e-11ee-93cd-42010a40000b", "MaleCommander"}},
    {"Asta", {"a76969ba-2c5e-11ee-ba60-42010a40000b", "FemaleNord"}},
    {"Astrid", {"a9a2ad7c-2c5e-11ee-9e4f-42010a40000b", "FemaleUniqueAstrid"}},
    {"Ataf", {"abdfb9f4-2c5e-11ee-b5e2-42010a40000b", "MaleYoungEager"}},
    {"Atahbah", {"ae0e945c-2c5e-11ee-9df8-42010a40000b", "FemaleKhajiit"}},
    {"Atar", {"b0425628-2c5e-11ee-afd0-42010a40000b", "MaleCondescending"}},
    {"Athis", {"b27af940-2c5e-11ee-b95f-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Atmah", {"b4b36058-2c5e-11ee-af61-42010a40000b", "FemaleEvenToned"}},
    {"Atub", {"b6df53be-2c5e-11ee-933f-42010a40000b", "FemaleOrc"}},
    {"Aval Atheron", {"b90892ea-2c5e-11ee-97ec-42010a40000b", "MaleEvenToned"}},
    {"Avrusa Sarethi", {"bb2c9530-2c5e-11ee-afec-42010a40000b", "FemaleUniqueMaven"}},
    {"Azzada Lylvieve", {"bd0a6026-2c5e-11ee-8c76-42010a40000b", "MaleEvenToned"}},
    {"Badnir", {"bf309834-2c5e-11ee-87e2-42010a40000b", "MaleBrute"}},
    {"Bagrak", {"c12736c0-2c5e-11ee-a681-42010a40000b", "FemaleOrc"}},
    {"Balbus", {"c34e3570-2c5e-11ee-9df2-42010a40000b", "MaleYoungEager"}},
    {"Balgruuf the Greater", {"c57dcdba-2c5e-11ee-9af1-42010a40000b", "MaleNord"}},
    {"Balimund", {"c7acf854-2c5e-11ee-9bd5-42010a40000b", "MaleBrute"}},
    {"Banning", {"c9d82900-2c5e-11ee-a2e6-42010a40000b", "MaleBrute"}},
    {"Barbas", {"cc0e36ce-2c5e-11ee-bbc1-42010a40000b", "MaleSlyCynical"}},
    {"Barknar", {"ce3d78ba-2c5e-11ee-bef0-42010a40000b", "MaleNord"}},
    {"Bashnag", {"d06fe082-2c5e-11ee-928b-42010a40000b", "MaleOrc"}},
    {"Bassianus Axius", {"d24861ea-2c5e-11ee-9ba3-42010a40000b", "MaleCondescending"}},
    {"Beggars", {"d475eef6-2c5e-11ee-b92e-42010a40000b", "FemaleUniqueMaven"}},
    {"Beirand", {"d6a544ce-2c5e-11ee-9702-42010a40000b", "MaleNord"}},
    {"Beitild", {"d8855afe-2c5e-11ee-945a-42010a40000b", "FemaleCondescending"}},
    {"Belchimac", {"dab4a03c-2c5e-11ee-9954-42010a40000b", "MaleCoward"}},
    {"Belethor", {"dcdff672-2c5e-11ee-ae43-42010a40000b", "MaleSlyCynical"}},
    {"Belrand", {"df0bcda4-2c5e-11ee-9d7b-42010a40000b", "MaleNord"}},
    {"Belyn Hlaalu", {"e0dbe6fa-2c5e-11ee-b84d-42010a40000b", "MaleCommoner"}},
    {"Bendt", {"e33fbd54-2c5e-11ee-8dcd-42010a40000b", "MaleOldGrumpy"}},
    {"Benkum", {"e573a964-2c5e-11ee-b0e0-42010a40000b", "MaleNord"}},
    {"Benor", {"e79f48f6-2c5e-11ee-a47b-42010a40000b", "MaleBrute"}},
    {"Birna", {"e9d49ea0-2c5e-11ee-913c-42010a40000b", "FemaleNord"}},
    {"Bjorlam", {"ec029ff6-2c5e-11ee-a0f6-42010a40000b", "MaleCommonerAccented"}},
    {"Bodil", {"ee3e727c-2c5e-11ee-af41-42010a40000b", "FemaleCommoner"}},
    {"Bolar", {"f06d8baa-2c5e-11ee-9d2e-42010a40000b", "FemaleOrc"}},
    {"Bolgeir Bearclaw", {"f29f1042-2c5e-11ee-84c5-42010a40000b", "MaleNordCommander"}},
    {"Bolli", {"f4d4ee0e-2c5e-11ee-b24f-42010a40000b", "MaleEvenTonedAccented"}},
    {"Bolund", {"f70aeaf2-2c5e-11ee-95cb-42010a40000b", "MaleBrute"}},
    {"Bor", {"f93cb788-2c5e-11ee-8651-42010a40000b", "MaleOldGrumpy"}},
    {"Borgakh the Steel Heart", {"fb6d7d12-2c5e-11ee-9cfa-42010a40000b", "FemaleOrc"}},
    {"Borgny", {"fd9cb7ec-2c5e-11ee-ba0c-42010a40000b", "MaleEvenTonedAccented"}},
    {"Borkul the Beast", {"ff71eefc-2c5e-11ee-a3b1-42010a40000b", "MaleOrc"}},
    {"Bothela", {"019f92ce-2c5f-11ee-a23c-42010a40000b", "FemaleOldGrumpy"}},
    {"Boti", {"03d3a76a-2c5f-11ee-855e-42010a40000b", "FemaleCommoner"}},
    {"Braig", {"060607b2-2c5f-11ee-840f-42010a40000b", "MaleSlyCynical"}},
    {"Brandish", {"0833a896-2c5f-11ee-8eac-42010a40000b", "MaleCommoner"}},
    {"Brelas", {"0a61814c-2c5f-11ee-a5cc-42010a40000b", "FemaleCommoner"}},
    {"Brelyna Maryon", {"0c9417a4-2c5f-11ee-bcb3-42010a40000b", "FemaleYoungEager"}},
    {"Brenuin", {"0ec8ef7c-2c5f-11ee-b123-42010a40000b", "MaleDrunk"}},
    {"Breya", {"10f7b26a-2c5f-11ee-b862-42010a40000b", "FemaleCommander"}},
    {"Briehl", {"1323cec0-2c5f-11ee-b2c3-42010a40000b", "MaleCommonerAccented"}},
    {"Brill", {"15552158-2c5f-11ee-9a44-42010a40000b", "MaleCommonerAccented"}},
    {"Brina Merilis", {"178d0d32-2c5f-11ee-8b7b-42010a40000b", "FemaleCommander"}},
    {"Brother Verulus", {"19668f98-2c5f-11ee-b6f4-42010a40000b", "MaleYoungEager"}},
    {"Bryling", {"1b9c64fe-2c5f-11ee-aa88-42010a40000b", "FemaleCommander"}},
    {"Brynjolf", {"1d958f1a-2c5f-11ee-9d68-42010a40000b", "MaleUniqueBrynjolf"}},
    {"Bulfrek", {"1f6f6f4a-2c5f-11ee-9186-42010a40000b", "MaleCommonerAccented"}},
    {"Cairine", {"219e1794-2c5f-11ee-9044-42010a40000b", "FemaleUniqueMaven"}},
    {"Calcelmo", {"23d0d416-2c5f-11ee-bb95-42010a40000b", "MaleOldKindly"}},
    {"Calder", {"2602223a-2c5f-11ee-a509-42010a40000b", "MaleNord"}},
    {"Calixto Corrium", {"2830cd68-2c5f-11ee-8ece-42010a40000b", "MaleOldKindly"}},
    {"Camilla Valerius", {"2a5e0466-2c5f-11ee-9687-42010a40000b", "FemaleYoungEager"}},
    {"Captain Aldis", {"2c8ba130-2c5f-11ee-8cb8-42010a40000b", "MaleNordCommander"}},
    {"Captain Aquilius", {"2ebab3e2-2c5f-11ee-aae2-42010a40000b", "MaleSlyCynical"}},
    {"Captain Avidius", {"30e7b58e-2c5f-11ee-9c8f-42010a40000b", "MaleCommoner"}},
    {"Captain Hargar", {"331003a2-2c5f-11ee-9650-42010a40000b", "MaleCommonerAccented"}},
    {"Captain Valmir", {"3564f2d4-2c5f-11ee-984d-42010a40000b", "MaleSlyCynical"}},
    {"Captain Wayfinder", {"37928436-2c5f-11ee-ba0b-42010a40000b", "MaleYoungEager"}},
    {"Carlotta Valentia", {"39becc1a-2c5f-11ee-abd3-42010a40000b", "FemaleEvenToned"}},
    {"Cedran", {"3bfd899e-2c5f-11ee-92e2-42010a40000b", "MaleOldKindly"}},
    {"Champion of Boethiah", {"3e349ef0-2c5f-11ee-aed1-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Chief Burguk", {"40649db0-2c5f-11ee-9982-42010a40000b", "MaleOrc"}},
    {"Chief Larak", {"4293d02e-2c5f-11ee-8344-42010a40000b", "MaleOrc"}},
    {"Chief Mauhulakh", {"44c22f1c-2c5f-11ee-a998-42010a40000b", "MaleOrc"}},
    {"Chief Yamarz", {"46eab5ac-2c5f-11ee-8129-42010a40000b", "MaleOrc"}},
    {"Christer", {"4919f69e-2c5f-11ee-9304-42010a40000b", "MaleCoward"}},
    {"Clavicus Vile", {"4b4847fe-2c5f-11ee-bbfe-42010a40000b", "MaleSlyCynical"}},
    {"Clavicus Vile", {"4d19249a-2c5f-11ee-b6f1-42010a40000b", "MaleSlyCynical"}},
    {"Colette Marence", {"4f485394-2c5f-11ee-966d-42010a40000b", "FemaleShrill"}},
    {"Commander Maro", {"518105c0-2c5f-11ee-8fe1-42010a40000b", "MaleCommander"}},
    {"Constance Michel", {"53b19184-2c5f-11ee-9ab6-42010a40000b", "FemaleYoungEager"}},
    {"Corpulus Vinius", {"55daa3e2-2c5f-11ee-8f4d-42010a40000b", "MaleEvenToned"}},
    {"Cosnach", {"5808c7f2-2c5f-11ee-94af-42010a40000b", "MaleDrunk"}},
    {"Cynric Endell", {"5a337aea-2c5f-11ee-9850-42010a40000b", "MaleSlyCynical"}},
    {"Dagur", {"5c670098-2c5f-11ee-8cf1-42010a40000b", "MaleCommonerAccented"}},
    {"Daighre", {"5e9c818a-2c5f-11ee-add0-42010a40000b", "FemaleEvenToned"}},
    {"Dalan Merchad", {"60c220fa-2c5f-11ee-9970-42010a40000b", "MaleCommander"}},
    {"Dark Brotherhood Initiate", {"62ed47a6-2c5f-11ee-be19-42010a40000b", "FemaleSultry"}},
    {"Deeja", {"651a236e-2c5f-11ee-a49e-42010a40000b", "FemaleArgonian"}},
    {"Deekus", {"67467d04-2c5f-11ee-a42c-42010a40000b", "MaleArgonian"}},
    {"Degaine", {"69703b24-2c5f-11ee-9b23-42010a40000b", "MaleDrunk"}},
    {"Delacourt", {"6b99f16a-2c5f-11ee-80f9-42010a40000b", "MaleYoungEager"}},
    {"Delphine", {"6dcdbe58-2c5f-11ee-ba2b-42010a40000b", "FemaleUniqueDelphine"}},
    {"Dengeir of Stuhn", {"70043fe4-2c5f-11ee-8132-42010a40000b", "MaleOldGrumpy"}},
    {"Derkeethus", {"723a49ca-2c5f-11ee-be0a-42010a40000b", "MaleArgonian"}},
    {"Dervenin", {"746c5c74-2c5f-11ee-8c04-42010a40000b", "MaleCoward"}},
    {"Dinya Balu", {"76404218-2c5f-11ee-a800-42010a40000b", "FemaleEvenToned"}},
    {"Dirge", {"7878e6f2-2c5f-11ee-8269-42010a40000b", "MaleBrute"}},
    {"Donnel", {"7aa9e282-2c5f-11ee-abb3-42010a40000b", "MaleOldGrumpy"}},
    {"Dorian", {"7cdb095a-2c5f-11ee-8e47-42010a40000b", "MaleEvenToned"}},
    {"Drahff", {"7f07c7a4-2c5f-11ee-b4ca-42010a40000b", "MaleCondescending"}},
    {"Dravin Llanith", {"8133843c-2c5f-11ee-ba4e-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Dravynea the Stoneweaver", {"835e80b8-2c5f-11ee-9811-42010a40000b", "FemaleDarkElf"}},
    {"Drelas", {"859c347e-2c5f-11ee-8adb-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Drennen", {"87daeac8-2c5f-11ee-8268-42010a40000b", "MaleYoungEager"}},
    {"Drevis Neloren", {"8a0af2fc-2c5f-11ee-b6db-42010a40000b", "MaleEvenToned"}},
    {"Drifa", {"8c395046-2c5f-11ee-bdb0-42010a40000b", "FemaleCommoner"}},
    {"Dryston", {"8ea0a320-2c5f-11ee-8d8b-42010a40000b", "MaleBrute"}},
    {"Duach", {"90d2c966-2c5f-11ee-a577-42010a40000b", "MaleCommoner"}},
    {"Dulug", {"92fd416c-2c5f-11ee-867c-42010a40000b", "FemaleOrc"}},
    {"Dushnamub", {"952dd668-2c5f-11ee-b1f0-42010a40000b", "MaleOrc"}},
    {"Edda", {"97623e6a-2c5f-11ee-9c0b-42010a40000b", "FemaleUniqueMaven"}},
    {"Edith", {"9990ffd2-2c5f-11ee-926d-42010a40000b", "FemaleCommoner"}},
    {"Eimar", {"9b630878-2c5f-11ee-aa60-42010a40000b", "MaleYoungEager"}},
    {"Eisa Blackthorn", {"9d8e93ce-2c5f-11ee-b548-42010a40000b", "FemaleNord"}},
    {"Elgrim", {"9fc47564-2c5f-11ee-995d-42010a40000b", "MaleOldGrumpy"}},
    {"Elisif the Fair", {"a1efc460-2c5f-11ee-8346-42010a40000b", "FemaleYoungEager"}},
    {"Elrindir", {"a427a22a-2c5f-11ee-997f-42010a40000b", "MaleCondescending"}},
    {"Eltrys", {"a5fa8dba-2c5f-11ee-84e2-42010a40000b", "MaleYoungEager"}},
    {"Elvali Veren", {"a8287458-2c5f-11ee-911b-42010a40000b", "FemaleYoungEager"}},
    {"Embry", {"aa5762e8-2c5f-11ee-b602-42010a40000b", "MaleDrunk"}},
    {"Endarie", {"ac8c0852-2c5f-11ee-9875-42010a40000b", "FemaleElfHaughty"}},
    {"Endon", {"aec73664-2c5f-11ee-b26c-42010a40000b", "MaleEvenToned"}},
    {"Engar", {"b0f3e180-2c5f-11ee-910a-42010a40000b", "MaleCommonerAccented"}},
    {"Enmon", {"b3319140-2c5f-11ee-8069-42010a40000b", "MaleYoungEager"}},
    {"Ennis", {"b5631f92-2c5f-11ee-909c-42010a40000b", "MaleCommoner"}},
    {"Ennoc", {"b794b37a-2c5f-11ee-88d5-42010a40000b", "MaleYoungEager"}},
    {"Ennodius Papius", {"b9c53f34-2c5f-11ee-8a71-42010a40000b", "MaleCoward"}},
    {"Enthir", {"bbf276e6-2c5f-11ee-a6ab-42010a40000b", "MaleSlyCynical"}},
    {"Eola", {"be1d33a2-2c5f-11ee-b6d3-42010a40000b", "FemaleSultry"}},
    {"Erandur", {"c052a8a0-2c5f-11ee-a969-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Erdi", {"c285d85e-2c5f-11ee-8e68-42010a40000b", "FemaleYoungEager"}},
    {"Eriana", {"c4b63dd0-2c5f-11ee-b6f8-42010a40000b", "FemaleNord"}},
    {"Erikur", {"c727428a-2c5f-11ee-ab3c-42010a40000b", "MaleSlyCynical"}},
    {"Erlendr", {"c9553d00-2c5f-11ee-b84b-42010a40000b", "MaleNordCommander"}},
    {"Esbern", {"cb818980-2c5f-11ee-84d6-42010a40000b", "MaleUniqueEsbern"}},
    {"Estormo", {"cdaff03e-2c5f-11ee-bcb6-42010a40000b", "MaleElfHaughty"}},
    {"Etienne Rarnis", {"cfe1e4b6-2c5f-11ee-a54c-42010a40000b", "MaleCommoner"}},
    {"Evette San", {"d2129366-2c5f-11ee-a854-42010a40000b", "FemaleCommoner"}},
    {"Eydis", {"d443b9b2-2c5f-11ee-93e3-42010a40000b", "FemaleCommoner"}},
    {"Faendal", {"d679ef62-2c5f-11ee-8d35-42010a40000b", "MaleEvenToned"}},
    {"Faida", {"d8a73592-2c5f-11ee-950a-42010a40000b", "FemaleCommoner"}},
    {"Faldrus", {"dacf3a36-2c5f-11ee-b5b7-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Faleen", {"dd0087d8-2c5f-11ee-963f-42010a40000b", "FemaleCommander"}},
    {"Falion", {"df2be3f4-2c5f-11ee-a1a2-42010a40000b", "MaleSlyCynical"}},
    {"Falk Firebeard", {"e15c17f2-2c5f-11ee-a409-42010a40000b", "MaleNord"}},
    {"Faralda", {"e387d5ca-2c5f-11ee-bb2e-42010a40000b", "FemaleSultry"}},
    {"Farkas", {"e5b59558-2c5f-11ee-b56b-42010a40000b", "MaleBrute"}},
    {"Faryl Atheron", {"e7e284f8-2c5f-11ee-8e6b-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Fastred", {"ea178dcc-2c5f-11ee-af23-42010a40000b", "FemaleYoungEager"}},
    {"Felldir the Old", {"ec44248e-2c5f-11ee-a4e2-42010a40000b", "MaleUniqueGalmar"}},
    {"Festus Krex", {"ee23ebe0-2c5f-11ee-a162-42010a40000b", "MaleOldGrumpy"}},
    {"Fianna", {"f052e916-2c5f-11ee-a846-42010a40000b", "FemaleShrill"}},
    {"Fihada", {"f27ff3e6-2c5f-11ee-9f31-42010a40000b", "MaleCondescending"}},
    {"Filnjar", {"f4acbf5a-2c5f-11ee-87b4-42010a40000b", "MaleNord"}},
    {"Fjola", {"f6d87724-2c5f-11ee-b35a-42010a40000b", "FemaleNord"}},
    {"Frabbi", {"f9054428-2c5f-11ee-8ed1-42010a40000b", "FemaleShrill"}},
    {"Freir", {"fadbf88c-2c5f-11ee-bfd8-42010a40000b", "FemaleNord"}},
    {"Frida", {"fd06dce4-2c5f-11ee-b414-42010a40000b", "FemaleNord"}},
    {"Fridrika", {"ff355b62-2c5f-11ee-a10f-42010a40000b", "FemaleCommoner"}},
    {"Frightened Woman", {"0168ac40-2c60-11ee-900d-42010a40000b", "FemaleCommoner"}},
    {"Fruki", {"03c0b46a-2c60-11ee-987f-42010a40000b", "FemaleNord"}},
    {"Fultheim", {"05ebc2f2-2c60-11ee-90a0-42010a40000b", "MaleOldGrumpy"}},
    {"Fultheim the Fearless", {"081ca53c-2c60-11ee-a360-42010a40000b", "MaleNord"}},
    {"Gabriella", {"09fd145e-2c60-11ee-ab81-42010a40000b", "FemaleEvenToned"}},
    {"Gaius Maro", {"0c3617fc-2c60-11ee-b33d-42010a40000b", "MaleSoldier"}},
    {"Ganna Uriel", {"0e658af8-2c60-11ee-8e21-42010a40000b", "FemaleUniqueMaven"}},
    {"Garakh", {"1092fe1e-2c60-11ee-b39a-42010a40000b", "FemaleOrc"}},
    {"Garthar", {"12ed9624-2c60-11ee-aa9b-42010a40000b", "MaleBrute"}},
    {"Garvey", {"14bdac8c-2c60-11ee-99af-42010a40000b", "MaleCoward"}},
    {"Gavros Plinius", {"16eaa794-2c60-11ee-ab94-42010a40000b", "MaleEvenToned"}},
    {"Geimund", {"18ce55f6-2c60-11ee-87dd-42010a40000b", "MaleCommonerAccented"}},
    {"Geirlund", {"1b011ae8-2c60-11ee-8461-42010a40000b", "MaleCommander"}},
    {"Gelebros", {"1d36d712-2c60-11ee-9ffa-42010a40000b", "MaleEvenToned"}},
    {"Gemma Uriel", {"1f9c8524-2c60-11ee-b80a-42010a40000b", "FemaleShrill"}},
    {"Gerda", {"21ca6b2c-2c60-11ee-930d-42010a40000b", "FemaleOldKindly"}},
    {"Gerdur", {"23f871dc-2c60-11ee-bb5e-42010a40000b", "FemaleNord"}},
    {"Gestur Rockbreaker", {"26263e1c-2c60-11ee-82b0-42010a40000b", "MaleEvenTonedAccented"}},
    {"Ghak", {"28566dce-2c60-11ee-aecf-42010a40000b", "FemaleOrc"}},
    {"Ghamorz", {"2a84505c-2c60-11ee-a39b-42010a40000b", "MaleOrc"}},
    {"Gharol", {"2cb3800a-2c60-11ee-afd8-42010a40000b", "FemaleOrc"}},
    {"Ghorbash the Iron Hand", {"2ede1390-2c60-11ee-a14a-42010a40000b", "MaleOrc"}},
    {"Ghunzul", {"310861d4-2c60-11ee-b2b6-42010a40000b", "MaleOrc"}},
    {"Gian the Fist", {"3333f072-2c60-11ee-acf7-42010a40000b", "MaleDrunk"}},
    {"Gianna", {"35664ef8-2c60-11ee-86cc-42010a40000b", "FemaleCommoner"}},
    {"Gilfre", {"3795e206-2c60-11ee-acc1-42010a40000b", "FemaleCommoner"}},
    {"Giraud Gemane", {"39cde2ee-2c60-11ee-8ce7-42010a40000b", "MaleEvenToned"}},
    {"Girduin", {"3bf557e6-2c60-11ee-8a67-42010a40000b", "MaleCoward"}},
    {"Gisli", {"3e24751a-2c60-11ee-b4e7-42010a40000b", "FemaleCondescending"}},
    {"Gissur", {"404cdecc-2c60-11ee-96cb-42010a40000b", "MaleCoward"}},
    {"Gjak", {"4289d514-2c60-11ee-aa76-42010a40000b", "MaleCommonerAccented"}},
    {"Gjuk", {"44b44964-2c60-11ee-a703-42010a40000b", "MaleDrunk"}},
    {"Gloth", {"46dcf0ce-2c60-11ee-bb78-42010a40000b", "MaleCommoner"}},
    {"Gregor", {"491e02ec-2c60-11ee-b4b9-42010a40000b", "MaleNord"}},
    {"Grelka", {"4b47a870-2c60-11ee-8d9e-42010a40000b", "FemaleCondescending"}},
    {"Grelod the Kind", {"4d791a3e-2c60-11ee-83eb-42010a40000b", "FemaleOldGrumpy"}},
    {"Greta", {"4fa7a01e-2c60-11ee-bcd6-42010a40000b", "FemaleCommoner"}},
    {"Grisvar the Unlucky", {"51dd5a04-2c60-11ee-8b3f-42010a40000b", "MaleCoward"}},
    {"Grosta", {"540b8558-2c60-11ee-b0b7-42010a40000b", "FemaleNord"}},
    {"Gul", {"56387dd6-2c60-11ee-b53a-42010a40000b", "MaleNord"}},
    {"Gularzob", {"585f1098-2c60-11ee-83e7-42010a40000b", "MaleOrc"}},
    {"Gunding", {"5a866b0a-2c60-11ee-82cd-42010a40000b", "MaleCommonerAccented"}},
    {"Gunjar", {"5cb34e20-2c60-11ee-939c-42010a40000b", "MaleCommonerAccented"}},
    {"Guthrum", {"5edaf0a4-2c60-11ee-b6b5-42010a40000b", "MaleOldGrumpy"}},
    {"Gwendolyn", {"60a895d0-2c60-11ee-972a-42010a40000b", "FemaleCommoner"}},
    {"Gwilin", {"62d3c3d4-2c60-11ee-9ca8-42010a40000b", "MaleYoungEager"}},
    {"Hadring", {"64fc6274-2c60-11ee-b1dc-42010a40000b", "MaleNord"}},
    {"Hadvar", {"67264da8-2c60-11ee-9580-42010a40000b", "MaleUniqueHadvar"}},
    {"Haelga", {"694fdfcc-2c60-11ee-a3a8-42010a40000b", "FemaleSultry"}},
    {"Hafjorg", {"6b7bf56a-2c60-11ee-835d-42010a40000b", "FemaleOldKindly"}},
    {"Haldyn", {"6da78a70-2c60-11ee-8b20-42010a40000b", "MaleCommoner"}},
    {"Hamal", {"6fd4c54c-2c60-11ee-a16b-42010a40000b", "FemaleCondescending"}},
    {"Hamelyn", {"71f9960e-2c60-11ee-93b9-42010a40000b", "MaleCommoner"}},
    {"Haran", {"74291f44-2c60-11ee-9fb2-42010a40000b", "FemaleCommoner"}},
    {"Harrald", {"764c179a-2c60-11ee-a1b1-42010a40000b", "MaleCondescending"}},
    {"Hathrasil", {"7889a0f4-2c60-11ee-82dc-42010a40000b", "MaleBrute"}},
    {"Hefid the Deaf", {"7a61474c-2c60-11ee-8f2e-42010a40000b", "FemaleUniqueMaven"}},
    {"Heimskr", {"7c916e7a-2c60-11ee-b78e-42010a40000b", "MaleNord"}},
    {"Heimvar", {"7eb359ca-2c60-11ee-ad25-42010a40000b", "MaleYoungEager"}},
    {"Helvard", {"80dd72da-2c60-11ee-ae53-42010a40000b", "MaleEvenTonedAccented"}},
    {"Heratar", {"83099f98-2c60-11ee-bd01-42010a40000b", "FemaleNord"}},
    {"Herluin Lothaire", {"85388766-2c60-11ee-b7bb-42010a40000b", "MaleOldGrumpy"}},
    {"Hern", {"875f6528-2c60-11ee-bd3e-42010a40000b", "MaleCommonerAccented"}},
    {"Hilde", {"892dbda0-2c60-11ee-9b34-42010a40000b", "FemaleOldGrumpy"}},
    {"Hjorunn", {"8b8c7d02-2c60-11ee-98be-42010a40000b", "MaleNord"}},
    {"Hod", {"8dba8344-2c60-11ee-8849-42010a40000b", "MaleNordCommander"}},
    {"Horgeir", {"8f8b546e-2c60-11ee-8f76-42010a40000b", "MaleCoward"}},
    {"Horik Halfhand", {"91b62ade-2c60-11ee-8b4b-42010a40000b", "MaleNordCommander"}},
    {"Horm", {"93e06efa-2c60-11ee-939f-42010a40000b", "MaleYoungEager"}},
    {"Hreinn", {"960cc430-2c60-11ee-8e7a-42010a40000b", "MaleYoungEager"}},
    {"Hroggar", {"983cf554-2c60-11ee-80d2-42010a40000b", "MaleEvenTonedAccented"}},
    {"Hroki", {"9a623ed4-2c60-11ee-92d5-42010a40000b", "FemaleYoungEager"}},
    {"Hrongar", {"9c8df464-2c60-11ee-a2a7-42010a40000b", "MaleNordCommander"}},
    {"Hulda", {"9eb681d4-2c60-11ee-907e-42010a40000b", "FemaleNord"}},
    {"Hunroor", {"a0e0bc68-2c60-11ee-ad81-42010a40000b", "MaleNord"}},
    {"Iddra", {"a2b93fa6-2c60-11ee-92c9-42010a40000b", "FemaleCommoner"}},
    {"Idesa Sadri", {"a4e7a93e-2c60-11ee-a4fe-42010a40000b", "FemaleDarkElf"}},
    {"Idgrod Ravencrone", {"a6d4b7d2-2c60-11ee-9688-42010a40000b", "FemaleOldGrumpy"}},
    {"Idgrod the Younger", {"a905921a-2c60-11ee-9cbb-42010a40000b", "FemaleYoungEager"}},
    {"Igmund", {"ab314854-2c60-11ee-aa23-42010a40000b", "MaleNordCommander"}},
    {"Illdi", {"ad006e58-2c60-11ee-8825-42010a40000b", "FemaleYoungEager"}},
    {"Illia", {"af2be7ca-2c60-11ee-aba9-42010a40000b", "FemaleEvenToned"}},
    {"Imedhnain", {"b181830e-2c60-11ee-9e46-42010a40000b", "MaleEvenToned"}},
    {"Imperial Captain", {"b3a9085a-2c60-11ee-a973-42010a40000b", "FemaleCommander"}},
    {"Imperial Soldier", {"b5d30658-2c60-11ee-8c83-42010a40000b", "MaleSoldier"}},
    {"Indara Caerellia", {"b7fe44e2-2c60-11ee-86d2-42010a40000b", "FemaleCommoner"}},
    {"Indaryn", {"ba3a94d6-2c60-11ee-93a1-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Inge Six Fingers", {"bc6cf7ee-2c60-11ee-980b-42010a40000b", "FemaleOldGrumpy"}},
    {"Ingrid", {"be9fa5ca-2c60-11ee-9c57-42010a40000b", "FemaleCommoner"}},
    {"Iona", {"c0d47bae-2c60-11ee-9108-42010a40000b", "MaleSlyCynical"}},
    {"Irgnir", {"c2ffb0ce-2c60-11ee-bae7-42010a40000b", "FemaleCommoner"}},
    {"Irileth", {"c52d1c1a-2c60-11ee-abb2-42010a40000b", "FemaleDarkElf"}},
    {"Irlof", {"c75403dc-2c60-11ee-9961-42010a40000b", "MaleDrunk"}},
    {"Irnskar Ironhand", {"c9874754-2c60-11ee-8170-42010a40000b", "MaleNordCommander"}},
    {"Jala", {"cbb5640c-2c60-11ee-8140-42010a40000b", "FemaleShrill"}},
    {"Jawanan", {"cdd88408-2c60-11ee-92c7-42010a40000b", "MaleBrute"}},
    {"Jenassa", {"d000c6be-2c60-11ee-9105-42010a40000b", "FemaleDarkElf"}},
    {"Jervar", {"d22d79b4-2c60-11ee-8610-42010a40000b", "MaleCommonerAccented"}},
    {"Jesper", {"d4054474-2c60-11ee-acd8-42010a40000b", "MaleSlyCynical"}},
    {"Jod", {"d62e022c-2c60-11ee-9e50-42010a40000b", "MaleBrute"}},
    {"Jofthor", {"d85b7df4-2c60-11ee-b2c9-42010a40000b", "MaleCommonerAccented"}},
    {"Jolf", {"da8526c0-2c60-11ee-9087-42010a40000b", "MaleNordCommander"}},
    {"Jonna", {"9242e0ce-0ebe-11ee-bd7e-42010a400002", "FemaleCommoner"}},
    {"Jora", {"df081d9c-2c60-11ee-a2a6-42010a40000b", "FemaleCondescending"}},
    {"Jorgen", {"e1389a92-2c60-11ee-96fc-42010a40000b", "MaleCommonerAccented"}},
    {"Jorleif", {"e36f6be2-2c60-11ee-8b7f-42010a40000b", "MaleNordCommander"}},
    {"Jorn", {"e53f5496-2c60-11ee-aa21-42010a40000b", "MaleNordCommander"}},
    {"Jouane Manette", {"e76256ba-2c60-11ee-9416-42010a40000b", "MaleOldKindly"}},
    {"Julienne Lylvieve", {"e988b556-2c60-11ee-a2d1-42010a40000b", "FemaleYoungEager"}},
    {"Jurgen Windcaller", {"ebb04830-2c60-11ee-b214-42010a40000b", "MaleNordCommander"}},
    {"Kaie", {"eddf4b4c-2c60-11ee-9e10-42010a40000b", "FemaleSultry"}},
    {"Karl", {"f013dcfc-2c60-11ee-b99a-42010a40000b", "FemaleUniqueKarliah"}},
    {"Karliah", {"f243ae08-2c60-11ee-bbfd-42010a40000b", "FemaleUniqueKarliah"}},
    {"Katla", {"f46a59fc-2c60-11ee-bb75-42010a40000b", "FemaleNord"}},
    {"Keeper Carcette", {"f64a6d7a-2c60-11ee-bc1a-42010a40000b", "FemaleEvenToned"}},
    {"Keerava", {"f8780a08-2c60-11ee-98eb-42010a40000b", "FemaleArgonian"}},
    {"Kematu", {"fa9fdb12-2c60-11ee-8cb5-42010a40000b", "MaleEvenToned"}},
    {"Kerah", {"fccb3094-2c60-11ee-a19b-42010a40000b", "FemaleCommoner"}},
    {"Kesh the Clean", {"fef96796-2c60-11ee-87fc-42010a40000b", "MaleKhajiit"}},
    {"Kharjo", {"01265dbc-2c61-11ee-97a7-42010a40000b", "MaleKhajiit"}},
    {"Khayla", {"03566104-2c61-11ee-a8db-42010a40000b", "FemaleKhajiit"}},
    {"Kibell", {"05816de8-2c61-11ee-b910-42010a40000b", "MaleCommonerAccented"}},
    {"Kjar", {"07adf406-2c61-11ee-a111-42010a40000b", "MaleNord"}},
    {"Kjeld", {"09d4b33c-2c61-11ee-8901-42010a40000b", "MaleNord"}},
    {"Kjeld the Younger", {"0c00e66c-2c61-11ee-9539-42010a40000b", "MaleEvenTonedAccented"}},
    {"Kleppr", {"0e2d4aca-2c61-11ee-8fbc-42010a40000b", "MaleCondescending"}},
    {"Klimmek", {"10582554-2c61-11ee-bee0-42010a40000b", "MaleBrute"}},
    {"Knjakr", {"128f65b2-2c61-11ee-8d33-42010a40000b", "MaleBrute"}},
    {"Kodlak Whitemane", {"14bc1330-2c61-11ee-a794-42010a40000b", "MaleUniqueKodlakWhitemane"}},
    {"Kodrir", {"16e8dd1e-2c61-11ee-81fd-42010a40000b", "MaleSlyCynical"}},
    {"Korir", {"18ea9ea4-2c61-11ee-9cc5-42010a40000b", "MaleNord"}},
    {"Kornalus", {"1abdeb78-2c61-11ee-9905-42010a40000b", "MaleElfHaughty"}},
    {"Kraldar", {"1cf754ba-2c61-11ee-8ba1-42010a40000b", "MaleNord"}},
    {"Kust", {"1f2bccca-2c61-11ee-869b-42010a40000b", "MaleNord"}},
    {"Kyr", {"2158025c-2c61-11ee-8540-42010a40000b", "MaleNord"}},
    {"Laelette the Vampire", {"2383298a-2c61-11ee-ba5f-42010a40000b", "FemaleShrill"}},
    {"Lami", {"25ab62b8-2c61-11ee-ad76-42010a40000b", "FemaleNord"}},
    {"Legate", {"27d48b0a-2c61-11ee-bf7d-42010a40000b", "FemaleCommander"}},
    {"Legate Adventus Caesennius", {"29fd7284-2c61-11ee-a01e-42010a40000b", "MaleCommander"}},
    {"Legate Constantius Tituleius", {"2c2ab076-2c61-11ee-82e5-42010a40000b", "MaleCommander"}},
    {"Legate Emmanuel Admand", {"2e5909c4-2c61-11ee-9fcc-42010a40000b", "MaleCommander"}},
    {"Legate Fasendil", {"308e488a-2c61-11ee-8e57-42010a40000b", "MaleCommander"}},
    {"Legate Hrollod", {"3267840a-2c61-11ee-8a7e-42010a40000b", "MaleCommander"}},
    {"Legate Quentin Cipius", {"3496b386-2c61-11ee-9b51-42010a40000b", "MaleCommander"}},
    {"Legate Rikke", {"36bf8f48-2c61-11ee-856c-42010a40000b", "FemaleCommander"}},
    {"Legate Sevan Telendas", {"38e6d56a-2c61-11ee-a4c2-42010a40000b", "MaleCommander"}},
    {"Legate Skulnar", {"3b0fe336-2c61-11ee-a418-42010a40000b", "MaleCommander"}},
    {"Legate Taurinus Duilis", {"3d672d56-2c61-11ee-8437-42010a40000b", "MaleCommander"}},
    {"Leifur", {"3f91f142-2c61-11ee-8185-42010a40000b", "MaleEvenTonedAccented"}},
    {"Leigelf", {"41665cba-2c61-11ee-a02c-42010a40000b", "MaleCondescending"}},
    {"Lemkil", {"438cea22-2c61-11ee-9e33-42010a40000b", "MaleSlyCynical"}},
    {"Leonara Arius", {"45b544d4-2c61-11ee-a7d5-42010a40000b", "FemaleEvenToned"}},
    {"Leontius Salvius", {"47d9f372-2c61-11ee-bea7-42010a40000b", "MaleCommoner"}},
    {"Liesl", {"4a011180-2c61-11ee-b4b5-42010a40000b", "FemaleNord"}},
    {"Lieutenant Salvarus", {"4c31b41e-2c61-11ee-9f37-42010a40000b", "MaleSoldier"}},
    {"Linwe", {"4e5f4170-2c61-11ee-9657-42010a40000b", "MaleElfHaughty"}},
    {"Lisbet", {"508e18fe-2c61-11ee-b6df-42010a40000b", "FemaleNord"}},
    {"Lisette", {"52b549b8-2c61-11ee-89cf-42010a40000b", "FemaleEvenToned"}},
    {"Llewellyn the Nightingale", {"54df8096-2c61-11ee-b414-42010a40000b", "MaleYoungEager"}},
    {"Lob", {"570b512e-2c61-11ee-8853-42010a40000b", "MaleOrc"}},
    {"Lod", {"59397638-2c61-11ee-9e6a-42010a40000b", "MaleCommonerAccented"}},
    {"Lodvar", {"5b619af8-2c61-11ee-828e-42010a40000b", "MaleNord"}},
    {"Logrolf the Willful", {"5d8e8106-2c61-11ee-9fae-42010a40000b", "MaleOldGrumpy"}},
    {"Lokir", {"5f5f8a2a-2c61-11ee-a388-42010a40000b", "MaleCoward"}},
    {"Lond", {"61bbde5e-2c61-11ee-a28b-42010a40000b", "MaleCommonerAccented"}},
    {"Lortheim", {"63e72db4-2c61-11ee-ac4e-42010a40000b", "MaleNord"}},
    {"Louis Letrush", {"660e12f6-2c61-11ee-b10e-42010a40000b", "MaleCommoner"}},
    {"Luaffyn", {"68445daa-2c61-11ee-a966-42010a40000b", "FemaleEvenToned"}},
    {"Lucan Valerius", {"6a7360e4-2c61-11ee-a1c8-42010a40000b", "MaleSlyCynical"}},
    {"Lund", {"6c9a43f6-2c61-11ee-93e9-42010a40000b", "MaleNordCommander"}},
    {"Lurbuk", {"6ebee57e-2c61-11ee-8a03-42010a40000b", "MaleOrc"}},
    {"Lydia", {"8c3bfe92-d9d3-11ed-a90b-42010a7c4003", "FemaleEvenToned"}},
    {"Madanach", {"72bc6ee4-2c61-11ee-a188-42010a40000b", "MaleSlyCynical"}},
    {"Madena", {"74e641cc-2c61-11ee-aad7-42010a40000b", "FemaleCondescending"}},
    {"Madesi", {"77101e3c-2c61-11ee-9a1e-42010a40000b", "MaleArgonian"}},
    {"Mahk", {"7937086a-2c61-11ee-81c1-42010a40000b", "MaleOrc"}},
    {"Malacath", {"7b632664-2c61-11ee-b704-42010a40000b", "MaleUniqueKodlakWhitemane"}},
    {"Malacath", {"7b632664-2c61-11ee-b704-42010a40000b", "MaleUniqueKodlakWhitemane"}},
    {"Malborn", {"7fc583b4-2c61-11ee-a0f7-42010a40000b", "MaleEvenToned"}},
    {"Mallus Maccius", {"81ef73ac-2c61-11ee-aa7f-42010a40000b", "MaleSlyCynical"}},
    {"Malthyr Elenil", {"8448dc10-2c61-11ee-9ba9-42010a40000b", "MaleSlyCynical"}},
    {"Malur Seloth", {"8617cefc-2c61-11ee-bf98-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Maluril", {"883ed20c-2c61-11ee-a154-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Malyn Varen", {"8a70b68a-2c61-11ee-924c-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Maramal", {"8c953616-2c61-11ee-b95b-42010a40000b", "MaleEvenToned"}},
    {"Marcurio", {"8ed589f8-2c61-11ee-8956-42010a40000b", "MaleEvenToned"}},
    {"Margret", {"9104e872-2c61-11ee-acd3-42010a40000b", "FemaleEvenToned"}},
    {"Marise Aravel", {"93331ba0-2c61-11ee-8158-42010a40000b", "FemaleDarkElf"}},
    {"Markus", {"955f51fa-2c61-11ee-bb56-42010a40000b", "MaleCommonerAccented"}},
    {"Mathies", {"97329e4c-2c61-11ee-a7e3-42010a40000b", "MaleCommonerAccented"}},
    {"Maul", {"9958b2f6-2c61-11ee-a7f0-42010a40000b", "MaleBrute"}},
    {"Maurice Jondrelle", {"9b89d726-2c61-11ee-9424-42010a40000b", "MaleCondescending"}},
    {"Medresi Dran", {"9db13ecc-2c61-11ee-8687-42010a40000b", "FemaleCondescending"}},
    {"Melaran", {"9fe22968-2c61-11ee-8a2c-42010a40000b", "MaleElfHaughty"}},
    {"Mena", {"a209ef96-2c61-11ee-87b1-42010a40000b", "FemaleYoungEager"}},
    {"Mephala", {"a43a1782-2c61-11ee-ba15-42010a40000b", "FemaleEvenToned"}},
    {"Mercer Frey", {"a667778e-2c61-11ee-a623-42010a40000b", "MaleSlyCynical"}},
    {"Michel Lylvieve", {"a88ce9ae-2c61-11ee-bdf3-42010a40000b", "FemaleEvenToned"}},
    {"Mikael", {"ab5076b0-2c61-11ee-82cc-42010a40000b", "MaleYoungEager"}},
    {"Mirabelle Ervine", {"ad75a7ee-2c61-11ee-82ce-42010a40000b", "FemaleUniqueMirabelleErvine"}},
    {"Mjoll the Lioness", {"afa35458-2c61-11ee-a738-42010a40000b", "FemaleNord"}},
    {"Mogdurz", {"b1cca298-2c61-11ee-ad65-42010a40000b", "FemaleOrc"}},
    {"Molag Bal", {"b3fb439e-2c61-11ee-8dc2-42010a40000b", "MaleCommoner"}},
    {"Molag Bal", {"b3fb439e-2c61-11ee-8dc2-42010a40000b", "MaleCommoner"}},
    {"Morokei", {"b84ed546-2c61-11ee-aeef-42010a40000b", "MaleCommoner"}},
    {"Morven", {"ba778bce-2c61-11ee-974c-42010a40000b", "MaleCondescending"}},
    {"Movarth Piquine", {"bcb17a94-2c61-11ee-86d2-42010a40000b", "MaleSlyCynical"}},
    {"Mralki", {"be874010-2c61-11ee-bb74-42010a40000b", "MaleCommonerAccented"}},
    {"Muiri", {"c0555c60-2c61-11ee-9a18-42010a40000b", "FemaleYoungEager"}},
    {"Murbul", {"c27b3b22-2c61-11ee-9ca3-42010a40000b", "FemaleOrc"}},
    {"Nagrub", {"c4aa31d2-2c61-11ee-9da5-42010a40000b", "MaleOrc"}},
    {"Nahkriin", {"c6da06a8-2c61-11ee-8cd1-42010a40000b", "MaleCommoner"}},
    {"Namira", {"c9094330-2c61-11ee-8a60-42010a40000b", "FemaleUniqueMirabelleErvine"}},
    {"Nana Ildene", {"cb339994-2c61-11ee-ab36-42010a40000b", "FemaleOldKindly"}},
    {"Narfi", {"cd5c24d4-2c61-11ee-b0e5-42010a40000b", "MaleDrunk"}},
    {"Naris the Wicked", {"cf87cf24-2c61-11ee-93d9-42010a40000b", "MaleElfHaughty"}},
    {"Narri", {"d15ae5a2-2c61-11ee-a4e5-42010a40000b", "FemaleNord"}},
    {"Nazeem", {"d38b2f12-2c61-11ee-8f58-42010a40000b", "MaleCondescending"}},
    {"Nazir", {"d5bf60b4-2c61-11ee-bfe5-42010a40000b", "MaleUniqueNazir"}},
    {"Neetrenaza", {"d7f21700-2c61-11ee-b1f4-42010a40000b", "MaleArgonian"}},
    {"Nelacar", {"da2541c8-2c61-11ee-ab0d-42010a40000b", "MaleElfHaughty"}},
    {"Nenya", {"dc4b4362-2c61-11ee-abdf-42010a40000b", "FemaleEvenToned"}},
    {"Nepos the Nose", {"de74053e-2c61-11ee-904a-42010a40000b", "MaleOldKindly"}},
    {"Nerien", {"e09f9dc8-2c61-11ee-8e6a-42010a40000b", "MaleElfHaughty"}},
    {"Nikulas", {"e2d6bbf8-2c61-11ee-b072-42010a40000b", "MaleYoungEager"}},
    {"Nils", {"e502e64a-2c61-11ee-8269-42010a40000b", "MaleOldKindly"}},
    {"Niluva Hlaalu", {"e745f83e-2c61-11ee-a028-42010a40000b", "FemaleDarkElf"}},
    {"Nimphaneth", {"e9779216-2c61-11ee-a1ba-42010a40000b", "FemaleYoungEager"}},
    {"Nimriel", {"eba3b8f8-2c61-11ee-9987-42010a40000b", "FemaleYoungEager"}},
    {"Niranye", {"edd20882-2c61-11ee-a533-42010a40000b", "FemaleElfHaughty"}},
    {"Niruin", {"effbd598-2c61-11ee-b71d-42010a40000b", "MaleCondescending"}},
    {"Nirya", {"f1d2f446-2c61-11ee-8491-42010a40000b", "FemaleElfHaughty"}},
    {"Nivenor", {"f3f936a4-2c61-11ee-bed9-42010a40000b", "FemaleYoungEager"}},
    {"Nocturnal", {"f62d8812-2c61-11ee-9696-42010a40000b", "FemaleDarkElf"}},
    {"Nocturnal", {"f62d8812-2c61-11ee-9696-42010a40000b", "FemaleDarkElf"}},
    {"Nurelion", {"fa8fadb8-2c61-11ee-ab43-42010a40000b", "MaleOldGrumpy"}},
    {"Octieve San", {"fcbe9edc-2c61-11ee-8a46-42010a40000b", "MaleCoward"}},
    {"Odar", {"fef699f2-2c61-11ee-8e70-42010a40000b", "MaleNord"}},
    {"Odfel", {"012843ce-2c62-11ee-9e8f-42010a40000b", "MaleCondescending"}},
    {"Odvan", {"02fca76c-2c62-11ee-b123-42010a40000b", "MaleEvenToned"}},
    {"Oglub", {"0528d0c4-2c62-11ee-b51c-42010a40000b", "MaleOrc"}},
    {"Ogmund", {"06f7e7dc-2c62-11ee-867f-42010a40000b", "MaleNord"}},
    {"Ogol", {"0924b8fa-2c62-11ee-ae36-42010a40000b", "MaleOrc"}},
    {"Olava the Feeble", {"0b529106-2c62-11ee-b877-42010a40000b", "FemaleOldKindly"}},
    {"Old Orc", {"0d830bae-2c62-11ee-82a4-42010a40000b", "MaleOrc"}},
    {"Olur", {"0fb4bf62-2c62-11ee-8dc0-42010a40000b", "MaleOrc"}},
    {"Omluag", {"11ea567a-2c62-11ee-8344-42010a40000b", "MaleCommoner"}},
    {"Ondolemar", {"13bd53e4-2c62-11ee-8ca9-42010a40000b", "MaleElfHaughty"}},
    {"Onmund", {"1d891656-2c62-11ee-bfcc-42010a40000b", "MaleYoungEager"}},
    {"Orchendor", {"1fbf7ef6-2c62-11ee-a8bf-42010a40000b", "MaleCondescending"}},
    {"Orgnar", {"2192a168-2c62-11ee-a34a-42010a40000b", "MaleBrute"}},
    {"Oriella", {"23f5e096-2c62-11ee-a5a6-42010a40000b", "FemaleEvenToned"}},
    {"Orini Dral", {"262427c4-2c62-11ee-b6cc-42010a40000b", "MaleSlyCynical"}},
    {"Orla", {"28581c80-2c62-11ee-af53-42010a40000b", "MaleCommonerAccented"}},
    {"Orthorn", {"2a82ac32-2c62-11ee-841a-42010a40000b", "MaleCoward"}},
    {"Orthus Endario", {"2cb21d94-2c62-11ee-be18-42010a40000b", "MaleCondescending"}},
    {"Pactur", {"2edb4424-2c62-11ee-a21b-42010a40000b", "MaleNord"}},
    {"Pantea Ateia", {"3104821a-2c62-11ee-bf6a-42010a40000b", "FemaleEvenToned"}},
    {"Paratus Decimius", {"332dd6a4-2c62-11ee-82cd-42010a40000b", "MaleCoward"}},
    {"Pavo Attius", {"35593090-2c62-11ee-9c66-42010a40000b", "MaleEvenToned"}},
    {"Pelagius Septim III", {"378fe976-2c62-11ee-81b4-42010a40000b", "MaleSlyCynical"}},
    {"Perth", {"39c61472-2c62-11ee-b2c8-42010a40000b", "MaleCommoner"}},
    {"Phinis Gestor", {"3bf224b6-2c62-11ee-a6d8-42010a40000b", "MaleCondescending"}},
    {"Plautis Carvain", {"3e1e7596-2c62-11ee-9173-42010a40000b", "MaleCommoner"}},
    {"Proventus Avenicci", {"404788bc-2c62-11ee-ac5c-42010a40000b", "MaleCoward"}},
    {"Quaranir", {"4271019a-2c62-11ee-b4e8-42010a40000b", "MaleElfHaughty"}},
    {"Quintus Navale", {"449c56e0-2c62-11ee-8031-42010a40000b", "MaleYoungEager"}},
    {"Raerek", {"46fb54fe-2c62-11ee-bbfb-42010a40000b", "MaleOldKindly"}},
    {"Ragnar", {"494d0c48-2c62-11ee-a7d8-42010a40000b", "MaleCommonerAccented"}},
    {"Ralof", {"4b285f0e-2c62-11ee-bdb7-42010a40000b", "MaleNord"}},
    {"Ranmir", {"4d5898fc-2c62-11ee-b843-42010a40000b", "MaleDrunk"}},
    {"Ravam Verethi", {"4f8787be-2c62-11ee-b8f5-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Ravyn Imyan", {"51b1f812-2c62-11ee-80ba-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Rayya", {"53da2fec-2c62-11ee-906e-42010a40000b", "FemaleCommander"}},
    {"Razelan", {"56043bf0-2c62-11ee-a542-42010a40000b", "MaleDrunk"}},
    {"Reburrus Quintilius", {"58307f92-2c62-11ee-b497-42010a40000b", "MaleCondescending"}},
    {"Reldith", {"5a5a603a-2c62-11ee-83d4-42010a40000b", "FemaleElfHaughty"}},
    {"Revyn Sadri", {"5c86364a-2c62-11ee-9b98-42010a40000b", "MaleCondescending"}},
    {"Rexus", {"5eefde04-2c62-11ee-be34-42010a40000b", "MaleSoldier"}},
    {"Rhiada", {"6118a350-2c62-11ee-bea3-42010a40000b", "FemaleYoungEager"}},
    {"Rhorlak", {"63492faa-2c62-11ee-b7f2-42010a40000b", "MaleEvenTonedAccented"}},
    {"Ria", {"658bdd76-2c62-11ee-abbb-42010a40000b", "MaleSlyCynical"}},
    {"Rissing", {"67ba1cb6-2c62-11ee-af15-42010a40000b", "MaleNord"}},
    {"Rochelle the Red", {"69e3a57a-2c62-11ee-aee8-42010a40000b", "FemaleEvenToned"}},
    {"Rogatus Salvius", {"6c117f2a-2c62-11ee-af28-42010a40000b", "MaleOldGrumpy"}},
    {"Roggvir", {"6e47d9ce-2c62-11ee-9c8a-42010a40000b", "MaleNord"}},
    {"Romlyn Dreth", {"7070c922-2c62-11ee-8a42-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Rondach", {"729b5aa0-2c62-11ee-a54b-42010a40000b", "MaleCommoner"}},
    {"Rorik", {"68d20da0-5e51-11ed-a19e-42010a80000c", "MaleEvenTonedAccented"}},
    {"Rorlund", {"76f164f0-2c62-11ee-a2e3-42010a40000b", "MaleEvenTonedAccented"}},
    {"Rulindil", {"791b6eec-2c62-11ee-be6e-42010a40000b", "MaleElfHaughty"}},
    {"Runil", {"7b473c00-2c62-11ee-a621-42010a40000b", "MaleOldKindly"}},
    {"Rustleif", {"7d6fd140-2c62-11ee-93dd-42010a40000b", "MaleEvenTonedAccented"}},
    {"Saadia", {"7f95e90a-2c62-11ee-9681-42010a40000b", "FemaleSultry"}},
    {"Sabine Nytte", {"81cd0d70-2c62-11ee-857f-42010a40000b", "FemaleDarkElf"}},
    {"Sabjorn", {"83ffd898-2c62-11ee-abdd-42010a40000b", "MaleCondescending"}},
    {"Saerlund", {"862e870e-2c62-11ee-b7e4-42010a40000b", "MaleYoungEager"}},
    {"Saffir", {"8889f3da-2c62-11ee-97c1-42010a40000b", "FemaleCondescending"}},
    {"Safia", {"8abb1f26-2c62-11ee-b301-42010a40000b", "FemaleSultry"}},
    {"Salma", {"8daa08bc-e47f-11ed-981f-42010a7c4003", "FemaleYoungEager"}},
    {"Salonia Carvain", {"8f118ec0-2c62-11ee-9af4-42010a40000b", "FemaleUniqueMaven"}},
    {"Salvianus", {"913990b2-2c62-11ee-9d4b-42010a40000b", "MaleCommoner"}},
    {"Sam Guevenne", {"936305c6-2c62-11ee-9245-42010a40000b", "MaleDrunk"}},
    {"Sanguine", {"95bbb69c-2c62-11ee-a69e-42010a40000b", "MaleDrunk"}},
    {"Sanyon", {"97e4391c-2c62-11ee-b747-42010a40000b", "MaleElfHaughty"}},
    {"Sarthis Idren", {"9a0ce662-2c62-11ee-b31c-42010a40000b", "MaleSlyCynical"}},
    {"Savos Aren", {"7b09b9e6-0af9-11ee-b91a-42010a400002", "MaleCondescending"}},
    {"Sayma", {"9e08950e-2c62-11ee-be93-42010a40000b", "FemaleEvenToned"}},
    {"Sebastian Lort", {"a03f3076-2c62-11ee-9fc8-42010a40000b", "MaleCondescending"}},
    {"Selveni Nethri", {"a26dbfca-2c62-11ee-93c4-42010a40000b", "FemaleUniqueMaven"}},
    {"Senna", {"a4c4d3ee-2c62-11ee-9f4c-42010a40000b", "FemaleSultry"}},
    {"Septimus Signus", {"a6fb7d5c-2c62-11ee-8dcf-42010a40000b", "MaleUniqueGalmar"}},
    {"Seren", {"a92a888e-2c62-11ee-bed0-42010a40000b", "FemaleEvenToned"}},
    {"Sergius Turrianus", {"aafd8b2a-2c62-11ee-a60c-42010a40000b", "MaleOldGrumpy"}},
    {"Severio Pelagia", {"ad34e3ca-2c62-11ee-b651-42010a40000b", "MaleCommander"}},
    {"Shadr", {"af6053be-2c62-11ee-a3bf-42010a40000b", "MaleYoungEager"}},
    {"Shahvee", {"b1426bf4-2c62-11ee-9b44-42010a40000b", "FemaleArgonian"}},
    {"Sharamph", {"b376cfaa-2c62-11ee-977a-42010a40000b", "FemaleOrc"}},
    {"Shavari", {"b5a2d90e-2c62-11ee-ac87-42010a40000b", "FemaleKhajiit"}},
    {"Shel", {"b7cbd276-2c62-11ee-964a-42010a40000b", "FemaleOrc"}},
    {"Shuftharz", {"b9f534fc-2c62-11ee-a0b3-42010a40000b", "FemaleOrc"}},
    {"Siddgeir", {"bc211c46-2c62-11ee-be25-42010a40000b", "MaleCondescending"}},
    {"Sifnar Ironkettle", {"be539354-2c62-11ee-8068-42010a40000b", "MaleCoward"}},
    {"Sigaar", {"c08875ae-2c62-11ee-a769-42010a40000b", "MaleCommonerAccented"}},
    {"Sigrid", {"b3c5ff1a-65b3-11ed-8efc-42010a80000c", "FemaleEvenToned"}},
    {"Sigurd", {"c4de417e-2c62-11ee-9f93-42010a40000b", "MaleYoungEager"}},
    {"Silana Petreia", {"c70bd1f0-2c62-11ee-bd8d-42010a40000b", "FemaleEvenToned"}},
    {"Sild the Warlock", {"c935e858-2c62-11ee-8492-42010a40000b", "MaleSlyCynical"}},
    {"Silda the Unseen", {"cb63742e-2c62-11ee-9aa3-42010a40000b", "FemaleUniqueMaven"}},
    {"Silus Vesuius", {"cd9a7382-2c62-11ee-8e6f-42010a40000b", "MaleCondescending"}},
    {"Silvia", {"f96cefa6-ddea-11ed-b298-42010a7c4003", "FemaleOldGrumpy"}},
    {"Sinding", {"d1a39b98-2c62-11ee-9f3b-42010a40000b", "MaleCommonerAccented"}},
    {"Sinmir", {"d3cea1d8-2c62-11ee-9597-42010a40000b", "MaleNordCommander"}},
    {"Sirgar", {"d5f965c4-2c62-11ee-9157-42010a40000b", "MaleYoungEager"}},
    {"Skald the Elder", {"d822bd00-2c62-11ee-9dd7-42010a40000b", "MaleOldGrumpy"}},
    {"Skjor", {"da5fb8fc-2c62-11ee-ba79-42010a40000b", "MaleCommander"}},
    {"Snilf", {"dc92b5fc-2c62-11ee-9b06-42010a40000b", "MaleCoward"}},
    {"Snorreid", {"dec8c230-2c62-11ee-9baf-42010a40000b", "MaleCommonerAccented"}},
    {"Solaf", {"e0a49c78-2c62-11ee-95af-42010a40000b", "MaleNord"}},
    {"Soldier", {"1a8864ca-d721-11ed-a4c2-42010a7c4003", "MaleNordCommander"}},
    {"Sondas Drenim", {"e4a91fba-2c62-11ee-9152-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Sonir", {"e6d48d74-2c62-11ee-b6c6-42010a40000b", "FemaleYoungEager"}},
    {"Sorex Vinius", {"e90992f6-2c62-11ee-8fa4-42010a40000b", "MaleSlyCynical"}},
    {"Sorli the Builder", {"eb699712-2c62-11ee-af1a-42010a40000b", "FemaleCommander"}},
    {"Sosia Tremellia", {"ed93abd6-2c62-11ee-a2ab-42010a40000b", "FemaleSultry"}},
    {"Stalleo", {"efbf2ac0-2c62-11ee-85ef-42010a40000b", "MaleNord"}},
    {"Stenvar", {"f1eb225e-2c62-11ee-8223-42010a40000b", "MaleBrute"}},
    {"Styrr", {"f41fa7c0-2c62-11ee-b53f-42010a40000b", "MaleOldGrumpy"}},
    {"Sulla Trebatius", {"f64b6106-2c62-11ee-8e03-42010a40000b", "MaleSoldier"}},
    {"Susanna the Wicked", {"f883dd18-2c62-11ee-b889-42010a40000b", "FemaleSultry"}},
    {"Suvaris Atheron", {"fabd5a50-2c62-11ee-8a9e-42010a40000b", "FemaleDarkElf"}},
    {"Sven", {"3b3b0ae6-ced0-11ed-8c64-42010a7c4003", "MaleYoungEager"}},
    {"Swanhvir", {"ff1e2020-2c62-11ee-af15-42010a40000b", "FemaleEvenToned"}},
    {"Sybille Stentor", {"0153d51a-2c63-11ee-8ab5-42010a40000b", "FemaleSultry"}},
    {"Sylgja", {"03847754-2c63-11ee-8fc9-42010a40000b", "FemaleYoungEager"}},
    {"Synda Llanith", {"05ba949a-2c63-11ee-a3d4-42010a40000b", "FemaleDarkElf"}},
    {"Syndus", {"07f0f34e-2c63-11ee-9409-42010a40000b", "MaleElfHaughty"}},
    {"Taarie", {"0a21b054-2c63-11ee-9ee0-42010a40000b", "FemaleElfHaughty"}},
    {"Tacitus Sallustius", {"0c4b6596-2c63-11ee-81f0-42010a40000b", "MaleYoungEager"}},
    {"Talsgar the Wanderer", {"0e7cba90-2c63-11ee-9485-42010a40000b", "MaleNord"}},
    {"Tandil", {"10abaea2-2c63-11ee-9018-42010a40000b", "MaleElfHaughty"}},
    {"Tekla", {"12e9b4a2-2c63-11ee-8160-42010a40000b", "FemaleUniqueMaven"}},
    {"Telrav", {"151614f0-2c63-11ee-9a4f-42010a40000b", "MaleCommoner"}},
    {"Thadgeir", {"16e9d0a0-2c63-11ee-a0d1-42010a40000b", "MaleOldGrumpy"}},
    {"Thaena", {"1911bc6c-2c63-11ee-8f5d-42010a40000b", "FemaleCommoner"}},
    {"The Caller", {"1b3eb49a-2c63-11ee-ab9d-42010a40000b", "FemaleElfHaughty"}},
    {"Thonjolf", {"1d6ab8fe-2c63-11ee-a988-42010a40000b", "MaleEvenTonedAccented"}},
    {"Thonnir", {"1fa522ee-2c63-11ee-98a4-42010a40000b", "MaleNord"}},
    {"Thorek", {"21d0a138-2c63-11ee-b48d-42010a40000b", "MaleNord"}},
    {"Thorgar", {"24011ce4-2c63-11ee-bff6-42010a40000b", "MaleNord"}},
    {"Thoring", {"26310952-2c63-11ee-9ad8-42010a40000b", "MaleCommonerAccented"}},
    {"Threki the Innocent", {"285e6ac6-2c63-11ee-a6ad-42010a40000b", "FemaleSultry"}},
    {"Thrynn", {"2a8f20a6-2c63-11ee-965b-42010a40000b", "MaleSlyCynical"}},
    {"Tolfdir", {"2cbc28a6-2c63-11ee-842e-42010a40000b", "MaleOldKindly"}},
    {"Tonilia", {"2ee92b4c-2c63-11ee-8e30-42010a40000b", "FemaleCondescending"}},
    {"Torkild the Fearsome", {"30bd11f4-2c63-11ee-81f3-42010a40000b", "MaleNord"}},
    {"Tormir", {"32e7d32e-2c63-11ee-b786-42010a40000b", "FemaleYoungEager"}},
    {"Torolf", {"35136bcc-2c63-11ee-ba73-42010a40000b", "MaleEvenTonedAccented"}},
    {"Torvar", {"37436ed8-2c63-11ee-b296-42010a40000b", "MaleDrunk"}},
    {"Torygg", {"3999fe04-2c63-11ee-81b7-42010a40000b", "MaleEvenTonedAccented"}},
    {"Tsavani", {"3bcbe278-2c63-11ee-b295-42010a40000b", "FemaleKhajiit"}},
    {"Tsrasuna", {"3df94fa4-2c63-11ee-aa9f-42010a40000b", "FemaleKhajiit"}},
    {"Tsun", {"402f1542-2c63-11ee-ab3f-42010a40000b", "MaleCommonerAccented"}},
    {"Tulvur", {"426289f2-2c63-11ee-b845-42010a40000b", "MaleCommonerAccented"}},
    {"Tuthul", {"44956834-2c63-11ee-ba3b-42010a40000b", "MaleCoward"}},
    {"Tynan", {"466eaa08-2c63-11ee-83e4-42010a40000b", "MaleCommoner"}},
    {"Tythis Ulen", {"48a72340-2c63-11ee-ac21-42010a40000b", "MaleEvenToned"}},
    {"Uaile", {"4acef56c-2c63-11ee-953f-42010a40000b", "FemaleEvenToned"}},
    {"Ugor", {"4d3e406e-2c63-11ee-8d64-42010a40000b", "FemaleOrc"}},
    {"Ulfgar the Unending", {"4f86c346-2c63-11ee-95fe-42010a40000b", "MaleNord"}},
    {"Ulfr the Blind", {"51c53110-2c63-11ee-ba2a-42010a40000b", "MaleOldGrumpy"}},
    {"Ulfric Stormcloak", {"53f5d476-2c63-11ee-9f11-42010a40000b", "MaleUniqueUlfric"}},
    {"Ulundil", {"562cc650-2c63-11ee-9ed5-42010a40000b", "MaleEvenToned"}},
    {"Umana", {"5886aad8-2c63-11ee-a497-42010a40000b", "FemaleSultry"}},
    {"Umurn", {"5ab39b36-2c63-11ee-a800-42010a40000b", "MaleOrc"}},
    {"Una", {"5ceeff58-2c63-11ee-b9e8-42010a40000b", "FemaleCommoner"}},
    {"Ungrien", {"5f269498-2c63-11ee-91ff-42010a40000b", "MaleEvenToned"}},
    {"Uraccen", {"6155c892-2c63-11ee-a3ee-42010a40000b", "MaleCondescending"}},
    {"Urog", {"63828d1c-2c63-11ee-ab00-42010a40000b", "FemaleOrc"}},
    {"Uthgerd the Unbroken", {"65affe6c-2c63-11ee-a0fb-42010a40000b", "FemaleCommander"}},
    {"Vaermina", {"67dcfcda-2c63-11ee-ae96-42010a40000b", "FemaleUniqueElenwen"}},
    {"Vaermina", {"67dcfcda-2c63-11ee-ae96-42010a40000b", "FemaleUniqueElenwen"}},
    {"Valdr", {"6c340814-2c63-11ee-8e3c-42010a40000b", "MaleEvenToned"}},
    {"Valga Vinicia", {"6e61be92-2c63-11ee-ac50-42010a40000b", "FemaleCommoner"}},
    {"Valindor", {"708c033a-2c63-11ee-aaf6-42010a40000b", "MaleYoungEager"}},
    {"Vals Veran", {"72b0cac4-2c63-11ee-8c2b-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Vampire", {"74eef572-2c63-11ee-8f82-42010a40000b", "FemaleSultry"}},
    {"Vanryth Gatharian", {"771ede20-2c63-11ee-8f93-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Vantus Loreius", {"79466e02-2c63-11ee-98c6-42010a40000b", "MaleEvenToned"}},
    {"Varnius Junius", {"7b7f13fe-2c63-11ee-8aa0-42010a40000b", "MaleYoungEager"}},
    {"Vasha", {"7dafbfa2-2c63-11ee-b663-42010a40000b", "MaleKhajiit"}},
    {"Veezara", {"80128414-2c63-11ee-9643-42010a40000b", "MaleArgonian"}},
    {"Vekel the Man", {"8243a90c-2c63-11ee-8d02-42010a40000b", "MaleNord"}},
    {"Veren Duleri", {"846d1bf0-2c63-11ee-ac1d-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Vex", {"869a5f46-2c63-11ee-a6e2-42010a40000b", "FemaleUniqueVex"}},
    {"Viarmo", {"88c7c15a-2c63-11ee-a664-42010a40000b", "MaleSlyCynical"}},
    {"Vidrald", {"8af1bd5a-2c63-11ee-b42f-42010a40000b", "MaleBrute"}},
    {"Vigdis Salvius", {"8d289d46-2c63-11ee-91f2-42010a40000b", "FemaleOldKindly"}},
    {"Vigilant Tyranus", {"8f8877a0-2c63-11ee-94ed-42010a40000b", "MaleCommander"}},
    {"Vilkas", {"91bd7f20-2c63-11ee-ab51-42010a40000b", "MaleNord"}},
    {"Vilod", {"9403a19c-2c63-11ee-899b-42010a40000b", "MaleNord"}},
    {"Viola Giordano", {"962f8918-2c63-11ee-b529-42010a40000b", "FemaleShrill"}},
    {"Vipir the Fleet", {"98610b26-2c63-11ee-8afa-42010a40000b", "MaleNord"}},
    {"Vittoria Vici", {"9a330c4c-2c63-11ee-8648-42010a40000b", "FemaleEvenToned"}},
    {"Vivienne Onis", {"9c61253a-2c63-11ee-aafc-42010a40000b", "FemaleSultry"}},
    {"Voada", {"9e87eaa6-2c63-11ee-8896-42010a40000b", "FemaleCommoner"}},
    {"Voldsea Giryon", {"a0b4a4fe-2c63-11ee-b3fd-42010a40000b", "FemaleCommander"}},
    {"Vorstag", {"a2df67fa-2c63-11ee-872a-42010a40000b", "MaleEvenTonedAccented"}},
    {"Weylin", {"a50e5590-2c63-11ee-a8cd-42010a40000b", "MaleCommoner"}},
    {"Wilhelm", {"a76c4004-2c63-11ee-a5c2-42010a40000b", "MaleNord"}},
    {"Willem", {"a9949200-2c63-11ee-8a9e-42010a40000b", "MaleEvenToned"}},
    {"Wilmuth", {"abbf9c3c-2c63-11ee-b184-42010a40000b", "MaleOldGrumpy"}},
    {"Wujeeta", {"ad92b828-2c63-11ee-bf16-42010a40000b", "FemaleArgonian"}},
    {"Wuunferth the Unliving", {"afc0c6bc-2c63-11ee-a988-42010a40000b", "MaleOldGrumpy"}},
    {"Wylandriah", {"b1ee0e04-2c63-11ee-892e-42010a40000b", "FemaleEvenToned"}},
    {"Xander", {"b3ce970c-2c63-11ee-a4f0-42010a40000b", "MaleCondescending"}},
    {"Yatul", {"b5faa930-2c63-11ee-ab9e-42010a40000b", "FemaleOrc"}},
    {"Yngvar the Singer", {"b82a717c-2c63-11ee-88e5-42010a40000b", "MaleBrute"}},
    {"Ysgramor", {"b9ff704c-2c63-11ee-85c2-42010a40000b", "MaleNordCommander"}},
    {"Ysolda", {"bbd3afd2-2c63-11ee-986a-42010a40000b", "FemaleYoungEager"}},
    {"Zaria", {"be0077fe-2c63-11ee-914c-42010a40000b", "FemaleCommander"}},
    {"Zaynabi", {"c0265a76-2c63-11ee-a60a-42010a40000b", "FemaleKhajiit"}},
    {"Agmaer", {"c25578cc-2c63-11ee-b2d0-42010a40000b", "MaleYoungEager"}},
    {"Beleval", {"c47cc038-2c63-11ee-b95f-42010a40000b", "FemaleSultry"}},
    {"Celann", {"c6b8d684-2c63-11ee-a4b5-42010a40000b", "MaleEvenToned"}},
    {"Dawnguard Novice Hakar", {"c8e53416-2c63-11ee-9d2a-42010a40000b", "MaleEvenToned"}},
    {"Dexion Evicus", {"cb0dde96-2c63-11ee-b2eb-42010a40000b", "MaleCoward"}},
    {"Durak", {"cd34f3d0-2c63-11ee-88b2-42010a40000b", "MaleOrc"}},
    {"Florentius Baenius", {"cf680c8c-2c63-11ee-95f8-42010a40000b", "MaleCoward"}},
    {"Galathil", {"d1ad30da-2c63-11ee-9c42-42010a40000b", "FemaleElfHaughty"}},
    {"Gort", {"d3dec4ae-2c63-11ee-b288-42010a40000b", "MaleEvenToned"}},
    {"Harkon", {"d60f818c-2c63-11ee-8175-42010a40000b", "MaleElfHaughty"}},
    {"Harlaug", {"d851a2b8-2c63-11ee-842d-42010a40000b", "MaleEvenToned"}},
    {"Ingjard", {"da835694-2c63-11ee-84e6-42010a40000b", "FemaleCondescending"}},
    {"Lokil", {"dcaedd3a-2c63-11ee-8cba-42010a40000b", "MaleCommoner"}},
    {"Lynoit", {"dedd8f34-2c63-11ee-99fa-42010a40000b", "MaleEvenToned"}},
    {"Moric Sidrey", {"e10c4390-2c63-11ee-97ad-42010a40000b", "MaleCommonerAccented"}},
    {"Morven Stroud", {"e3330348-2c63-11ee-a234-42010a40000b", "MaleCondescending"}},
    {"Orthjolf", {"e560fc9c-2c63-11ee-bc96-42010a40000b", "MaleNordCommander"}},
    {"Rargal Thrallmaster", {"e78ac192-2c63-11ee-b725-42010a40000b", "MaleNord"}},
    {"Ronthil", {"e95d0124-2c63-11ee-ac12-42010a40000b", "MaleYoungEager"}},
    {"Sorine Jurard", {"eb88fd0e-2c63-11ee-a487-42010a40000b", "FemaleEvenToned"}},
    {"Stalf", {"edb7d884-2c63-11ee-8b08-42010a40000b", "MaleCommander"}},
    {"Taron Dreth", {"efe42554-2c63-11ee-bb21-42010a40000b", "MaleElfHaughty"}},
    {"Valerica", {"f2106f86-2c63-11ee-94e3-42010a40000b", "FemaleUniqueAstrid"}},
    {"Vanik", {"f442d83e-2c63-11ee-8f82-42010a40000b", "MaleCommander"}},
    {"Venarus Vulpin", {"f66b672a-2c63-11ee-b2d3-42010a40000b", "MaleSlyCynical"}},
    {"Vigilant Adalvald", {"f89d1f0c-2c63-11ee-bebe-42010a40000b", "MaleEvenTonedAccented"}},
    {"Vigilant Tolan", {"fac9d98c-2c63-11ee-b633-42010a40000b", "MaleNord"}},
    {"Vingalmo", {"fc9fb1a0-2c63-11ee-8517-42010a40000b", "MaleElfHaughty"}},
    {"Volk", {"fec6fba0-2c63-11ee-98c1-42010a40000b", "MaleEvenTonedAccented"}},
    {"Akar", {"00f4cbf0-2c64-11ee-a71c-42010a40000b", "MaleBrute"}},
    {"Bradyn", {"031df51e-2c64-11ee-b5c0-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Bujold the Unworthy", {"054d452e-2c64-11ee-b8d8-42010a40000b", "FemaleNord"}},
    {"Cindiri Arano", {"0776ea12-2c64-11ee-9eb2-42010a40000b", "FemaleDarkElf"}},
    {"Deor Woodcutter", {"09abac00-2c64-11ee-94a9-42010a40000b", "MaleEvenTonedAccented"}},
    {"Dremora Merchant", {"0bda652a-2c64-11ee-b076-42010a40000b", "DLC2MaleDarkElfCynical"}},
    {"Drovas Relvi", {"0dc281b0-2c64-11ee-9343-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Ebony Warrior", {"0ff3453c-2c64-11ee-a2a5-42010a40000b", "MaleEvenToned"}},
    {"Edla", {"1225e40e-2c64-11ee-82ae-42010a40000b", "FemaleSultry"}},
    {"Elder Othreloth", {"1458228c-2c64-11ee-b8f9-42010a40000b", "DLC2MaleDarkElfCynical"}},
    {"Elmus", {"1688a766-2c64-11ee-b287-42010a40000b", "MaleEvenTonedAccented"}},
    {"Evul Seloth", {"18bea9f4-2c64-11ee-8f69-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Falas Selvayn", {"1af54886-2c64-11ee-a34d-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Galdrus Hlervu", {"1d253d46-2c64-11ee-9f25-42010a40000b", "DLC2MaleDarkElfCynical"}},
    {"Garyn Ienth", {"1f528ed4-2c64-11ee-be54-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Geldis Sadri", {"217cbf68-2c64-11ee-81b9-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"General Falx Carius", {"23a69462-2c64-11ee-b15b-42010a40000b", "MaleEvenToned"}},
    {"Glover Mallory", {"25cb61aa-2c64-11ee-8b17-42010a40000b", "MaleBrute"}},
    {"Herkja", {"27f3a442-2c64-11ee-9954-42010a40000b", "FemaleCommoner"}},
    {"Hilund", {"2a1f4294-2c64-11ee-9b90-42010a40000b", "FemaleCommoner"}},
    {"Hjalfar", {"2c4efa64-2c64-11ee-b8d9-42010a40000b", "MaleNordCommander"}},
    {"Ildari Sarothril", {"2e7bb3cc-2c64-11ee-8774-42010a40000b", "FemaleDarkElf"}},
    {"Kuvar", {"30a84638-2c64-11ee-842d-42010a40000b", "MaleBrute"}},
    {"Lygrleid", {"32d732c0-2c64-11ee-a6fc-42010a40000b", "MaleEvenTonedAccented"}},
    {"Majni", {"35028892-2c64-11ee-b0f6-42010a40000b", "MaleNord"}},
    {"Meden Maren", {"373cdc34-2c64-11ee-a37f-42010a40000b", "MaleYoungEager"}},
    {"Mirri Severin", {"396bcf74-2c64-11ee-8b95-42010a40000b", "FemaleSultry"}},
    {"Morwen", {"3b99e880-2c64-11ee-9c22-42010a40000b", "FemaleEvenToned"}},
    {"Naris Mavani", {"3dce6932-2c64-11ee-9853-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Niyya", {"3ffae8e8-2c64-11ee-92f0-42010a40000b", "FemaleCommoner"}},
    {"Oslaf", {"42294f56-2c64-11ee-94a1-42010a40000b", "MaleCommonerAccented"}},
    {"Palevius Lex", {"447ddd4e-2c64-11ee-8900-42010a40000b", "MaleOldKindly"}},
    {"Raleth Eldri", {"46a7e646-2c64-11ee-917f-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Ralis Sedarys", {"48d9b336-2c64-11ee-8980-42010a40000b", "DLC2MaleDarkElfCynical"}},
    {"Revus Sarvani", {"4b05870c-2c64-11ee-9198-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Rirns Llervu", {"4d422dc2-2c64-11ee-942f-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Saden", {"4f700d76-2c64-11ee-bc8b-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Sirkjorg", {"51971946-2c64-11ee-b50a-42010a40000b", "MaleEvenToned"}},
    {"Slitter", {"53d13fd4-2c64-11ee-b220-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Sogrlaf", {"55b7bae4-2c64-11ee-9ed2-42010a40000b", "MaleYoungEager"}},
    {"Talvas Fathryon", {"57e0f1c8-2c64-11ee-bdab-42010a40000b", "MaleYoungEager"}},
    {"Teldryn Sero", {"5a1bba86-2c64-11ee-867a-42010a40000b", "DLC2MaleDarkElfCynical"}},
    {"Tharstan", {"5c48a49a-2c64-11ee-980f-42010a40000b", "MaleOldKindly"}},
    {"Tilisu Severin", {"5e789482-2c64-11ee-b97e-42010a40000b", "FemaleDarkElf"}},
    {"Tolenos Omoren", {"60a2496a-2c64-11ee-8e20-42010a40000b", "DLC2MaleDarkElfCynical"}},
    {"Torkild", {"62cf14b6-2c64-11ee-bdb6-42010a40000b", "MaleNordCommander"}},
    {"Ulves Romoran", {"64f6ec96-2c64-11ee-86a1-42010a40000b", "DLC2MaleDarkElfCommoner"}},
    {"Vendil Severin", {"671ea982-2c64-11ee-adc3-42010a40000b", "DLC2MaleDarkElfCynical"}},
    {"Yrsa", {"68f4c3e0-2c64-11ee-80fa-42010a40000b", "MaleNordCommander"}}
    };

void SetupLog() {
    auto logsFolder = SKSE::log::log_directory();
    if (!logsFolder) SKSE::stl::report_and_fail("SKSE log_directory not provided, logs disabled.");
    auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();
    auto logFilePath = *logsFolder / std::format("{}.log", pluginName);
    auto fileLoggerPtr = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFilePath.string(), true);
    auto loggerPtr = std::make_shared<spdlog::logger>("log", std::move(fileLoggerPtr));
    spdlog::set_default_logger(std::move(loggerPtr));
    spdlog::set_level(spdlog::level::trace);
    spdlog::flush_on(spdlog::level::trace);
}

void OnDataLoaded() {
    auto formID = 0x64B3D;
    auto* form = RE::TESForm::LookupByID(formID);
    auto value = form->GetGoldValue();
    auto name = form->GetName();
    logger::info("Name: {} Value: {}", name, value);
}

void onMessage(SKSE::MessagingInterface::Message* message) {
    // if (message->type == SKSE::MessagingInterface::kDataLoaded)
    // OnDataLoaded();
    if (message->type == SKSE::MessagingInterface::kPostLoadGame) {
        RE::ConsoleLog::GetSingleton()->Print("Hello, world boi");
    }
}

std::string executableOutput;
std::string resp;

bool monitorDirectory(const std::string& directoryPath) {

    FILE_NOTIFY_INFORMATION buffer[MAX_SIZE]{};
    DWORD bytesReturned;

    HANDLE hDirectory =
        CreateFileA(directoryPath.c_str(), FILE_LIST_DIRECTORY, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                    NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);

    if (hDirectory == INVALID_HANDLE_VALUE) {
        return false;
    }

    std::time_t lastEventTime = std::time(nullptr);

    while (true) {
        BOOL result = ReadDirectoryChangesW(hDirectory, buffer, sizeof(buffer), TRUE, FILE_NOTIFY_CHANGE_LAST_WRITE,
                                            &bytesReturned, NULL, NULL);

        if (result && bytesReturned > 0) {
            std::time_t currentTime = std::time(nullptr);
            if (currentTime - lastEventTime >= 1) {
                lastEventTime = currentTime;
                CloseHandle(hDirectory);
                return true;
            }
        }

        // Sleep for 1 second before checking again (Windows-specific sleep)
        Sleep(1000);
    }

    CloseHandle(hDirectory);
    return false;
}

void updateFiles(std::string targetName) {

    std::string inputFile = vars["SKSE_DIR"] + "inputFile.txt";
    std::string outputFile = vars["SKSE_DIR"] + "outputFile.txt";
    std::fstream newfile;
    newfile.open(inputFile, std::ios::out);
    std::string charID = mp[targetName].first;
    std::string dir = mp[targetName].second;
    newfile << charID;
    newfile.close();
    std::fstream outfile;
    outfile.open(outputFile, std::ios::out);
    outfile << dir;
    outfile.close();

}


void ExecuteExternalProcess(const std::string& executablePath) {

    std::string output;
    HANDLE pipeRead, pipeWrite;
    SECURITY_ATTRIBUTES sa{};
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = nullptr;

    // Create a pipe for the standard output
    if (!CreatePipe(&pipeRead, &pipeWrite, &sa, 0)) {
        std::cerr << "Failed to create pipe." << std::endl;
        return;
    }

    STARTUPINFOA startupInfo{};
    PROCESS_INFORMATION processInfo{};

    // Set the STARTUPINFO structure to redirect the standard output to the pipe
    startupInfo.cb = sizeof(startupInfo);
    startupInfo.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    startupInfo.wShowWindow = SW_HIDE;
    startupInfo.hStdOutput = pipeWrite;

    // Create the process with the redirected standard output
    if (!CreateProcessA(nullptr, const_cast<char*>(executablePath.c_str()), nullptr, nullptr, TRUE, CREATE_NO_WINDOW,
                        nullptr, nullptr, &startupInfo, &processInfo)) {
        std::cerr << "Failed to create the process." << std::endl;
        CloseHandle(pipeRead);
        CloseHandle(pipeWrite);
        return;
    }


    // Close the write end of the pipe as it's no longer needed
    CloseHandle(pipeWrite);

    // Read the output from the pipe
    char buffer[4096];
    DWORD bytesRead;
    
    while (ReadFile(pipeRead, buffer, sizeof(buffer) - 1, &bytesRead, nullptr)) {
        buffer[bytesRead] = '\0';
        output += buffer;
        resp = output;
        if (!output.empty()) {
                break;
        }
    }

    std::string dir;
    std::string outputFile = vars["SKSE_DIR"] + "outputFile.txt";
    std::fstream outfile;
    outfile.open(outputFile, std::ios::in);
    std::getline(outfile, dir);
    outfile.close();
    
    std::string directoryPath = vars["MOD_DIR"] + dir + "/ ";  // Replace with your desired directory path
    if (monitorDirectory(directoryPath)) {
        //place the callback here
        RE::CrosshairPickData* npc = RE::CrosshairPickData::GetSingleton();
        SKSE::ModCallbackEvent modEvent{"ResponseGenerated", "", 600, nullptr};
        SKSE::GetModCallbackEventSource()->SendEvent(&modEvent);
        auto sm = RE::SubtitleManager::GetSingleton();
        RE::BSTArray<RE::SubtitleInfo> si = sm->subtitles;
        RE::SubtitleInfo subt;
        subt.subtitle = output;
        subt.speaker = npc->targetActor;
        subt.pad04 = 0;
        subt.targetDistance = 0;
        subt.forceDisplay = true;
        sm->subtitles.push_back(subt);
    }
    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);
    CloseHandle(pipeRead);

    return;
}

std::string MyNativeFunction(RE::StaticFunctionTag*, RE::TESForm* sender, std::string targetName) {
    SKSE::ModCallbackEvent modEvent1{"GetActor", "", 600, sender};
    SKSE::GetModCallbackEventSource()->SendEvent(&modEvent1);
    updateFiles(targetName);
    std::string executablePath = vars["CONVAI_DIR"] + "bazel-bin/main.exe ";
    std::thread processThread(ExecuteExternalProcess, executablePath);
    
     //Check if the process has finished executing
    if (processThread.joinable()) {
         //Process is still running, detach the thread and let it continue in the background
        processThread.detach();
    }
    return resp;
}


bool BindPapyrusFunctions(RE::BSScript::IVirtualMachine* vm) {
    vm->RegisterFunction("MyNativeFunction", "ConvaiEffectScript", MyNativeFunction);
    return true;
}

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
    SKSE::Init(skse);
    SetupLog();
    SKSE::GetPapyrusInterface()->Register(BindPapyrusFunctions);
    return true;
}
