Scriptname ConvaiScript extends ReferenceAlias  

SPELL Property convaiSpell  Auto  

Event OnInit()
	Game.GetPlayer().AddSpell(convaiSpell)
endEvent