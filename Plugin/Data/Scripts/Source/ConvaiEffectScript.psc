Scriptname ConvaiEffectScript extends activemagiceffect

string function MyNativeFunction(Form form, String strArg) global native

Event OnEffectStart(Actor target, Actor caster)
	target.SetDontMove()
	MyNativeFunction((target as Form), (target.GetActorBase() as Form).GetName())
	Utility.Wait(2.5)
	Debug.Notification("SpeakNow")
endEvent
 
