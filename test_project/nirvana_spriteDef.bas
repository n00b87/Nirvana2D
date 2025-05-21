NIRVANA_SPRITE_DIR$ = NIRVANA_PROJECT_BASE_DIR$ + NIRVANA_PATH_SEPARATOR$ + "sprites" + NIRVANA_PATH_SEPARATOR$


Type Nirvana_Sprite
Dim Name$
Dim BaseName$
Dim Sprite_ID
Dim Animation_Name_Index
Dim Animation_Count
End Type

Dim Nirvana_Sprite_Image_Stack : Nirvana_Sprite_Image_Stack = CreateStack_N()



Dim Nirvana_SpriteAnimationNames$[0]




Function Nirvana_CreateSprite(base_name$, sprite_name$) As Nirvana_Sprite
	Dim nv_sprite As Nirvana_Sprite
	nv_sprite.Name$ = sprite_name$
	nv_sprite.BaseName$ = base_name$

	Select Case base_name$

	End Select

	Return nv_sprite
End Function
