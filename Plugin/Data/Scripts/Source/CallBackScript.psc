Scriptname CallBackScript extends Quest

Form speakerForm

Topic Property convaiTopic  Auto

Event OnInit()
	RegisterForModEvent("ResponseGenerated", "OnResponseGenerated")
	RegisterForModEvent("GetActor", "OnGetActor")
endEvent

Event OnResponseGenerated(String eventName, string strArg, float numArg, Form sender)
	Actor speaker = speakerForm as Actor
	speaker.SetExpressionOverride(2,85)
	speaker.Say(convaiTopic,speaker,false)
	Utility.Wait(10)
	speaker.SetDontMove(false)
endEvent

Event OnGetActor(String eventName, string strArg, float numArg, Form sender)
	speakerForm = sender
endEvent
