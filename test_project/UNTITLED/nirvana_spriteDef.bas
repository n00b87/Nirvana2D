NIRVANA_SPRITE_DIR$ = NIRVANA_PROJECT_BASE_DIR$ + NIRVANA_PATH_SEPARATOR$ + "sprites" + NIRVANA_PATH_SEPARATOR$


Type Nirvana_Sprite
Dim Name$
Dim BaseName$
Dim Sprite_ID
Dim Detached_Sprite_ID
Dim IsDetached
Dim Animation_Name_Index
Dim Animation_Count
End Type

Dim Nirvana_Sprite_Image_Stack : Nirvana_Sprite_Image_Stack = CreateStack_N()

Dim Nirvana_Sprite_Image_0 : Nirvana_Sprite_Image_0 = -1
Dim Nirvana_Sprite_Image_1 : Nirvana_Sprite_Image_1 = -1
Dim Nirvana_Sprite_Image_2 : Nirvana_Sprite_Image_2 = -1


Dim Nirvana_SpriteAnimationNames$[4]

Nirvana_SpriteAnimationNames$[0] = "Walk_Right"
Nirvana_SpriteAnimationNames$[1] = "Walk_Left"
Nirvana_SpriteAnimationNames$[2] = "hover"
Nirvana_SpriteAnimationNames$[3] = "default"


Function Nirvana_SpriteDef_0(ByRef detached_spr_id)
	If Nirvana_Sprite_Image_0 < 0 Then
		If OS$ = "WINDOWS" Then
			Nirvana_Sprite_Image_0 = LoadImage(NIRVANA_SPRITE_DIR$ + "graizor.png")
		Else
			Nirvana_Sprite_Image_0 = LoadImage(NIRVANA_SPRITE_DIR$ + "graizor.png")
		End If

		If Nirvana_Sprite_Image_0 >= 0 Then
			Push_N(Nirvana_Sprite_Image_Stack, Nirvana_Sprite_Image_0)
		End If
	End If

	spr_id = CreateSprite(Nirvana_Sprite_Image_0, 64, 64)

	'-------ANIMATIONS-------

	spr_animation1 = CreateSpriteAnimation(spr_id, 4, 6)

	SetSpriteAnimationFrame(spr_id, spr_animation1, 0, 0)
	SetSpriteAnimationFrame(spr_id, spr_animation1, 1, 1)
	SetSpriteAnimationFrame(spr_id, spr_animation1, 2, 0)
	SetSpriteAnimationFrame(spr_id, spr_animation1, 3, 3)

	spr_animation2 = CreateSpriteAnimation(spr_id, 4, 7)

	SetSpriteAnimationFrame(spr_id, spr_animation2, 0, 28)
	SetSpriteAnimationFrame(spr_id, spr_animation2, 1, 29)
	SetSpriteAnimationFrame(spr_id, spr_animation2, 2, 30)
	SetSpriteAnimationFrame(spr_id, spr_animation2, 3, 31)


	'-------SHAPE-------
detached_spr_id = -1

	SetSpriteShape(spr_id, SPRITE_SHAPE_BOX)
	SetSpriteShapeOffset(spr_id, 20, 0)
	SetSpriteBox(spr_id, 23, 64)

	Return spr_id
End Function

Function Nirvana_SpriteDef_1(ByRef detached_spr_id)
	If Nirvana_Sprite_Image_1 < 0 Then
		If OS$ = "WINDOWS" Then
			Nirvana_Sprite_Image_1 = LoadImage(NIRVANA_SPRITE_DIR$ + "chronos.png")
		Else
			Nirvana_Sprite_Image_1 = LoadImage(NIRVANA_SPRITE_DIR$ + "chronos.png")
		End If

		If Nirvana_Sprite_Image_1 >= 0 Then
			Push_N(Nirvana_Sprite_Image_Stack, Nirvana_Sprite_Image_1)
		End If
	End If

	spr_id = CreateSprite(Nirvana_Sprite_Image_1, 128, 196)

	'-------ANIMATIONS-------

	spr_animation1 = CreateSpriteAnimation(spr_id, 3, 6)

	SetSpriteAnimationFrame(spr_id, spr_animation1, 0, 0)
	SetSpriteAnimationFrame(spr_id, spr_animation1, 1, 1)
	SetSpriteAnimationFrame(spr_id, spr_animation1, 2, 2)


	'-------SHAPE-------
detached_spr_id = -1

	SetSpriteShape(spr_id, SPRITE_SHAPE_BOX)
	SetSpriteShapeOffset(spr_id, 8, 138)
	SetSpriteBox(spr_id, 87, 57)

	Return spr_id
End Function

Function Nirvana_SpriteDef_2(ByRef detached_spr_id)
	If Nirvana_Sprite_Image_2 < 0 Then
		If OS$ = "WINDOWS" Then
			Nirvana_Sprite_Image_2 = LoadImage(NIRVANA_SPRITE_DIR$ + "grenguy.png")
		Else
			Nirvana_Sprite_Image_2 = LoadImage(NIRVANA_SPRITE_DIR$ + "grenguy.png")
		End If

		If Nirvana_Sprite_Image_2 >= 0 Then
			Push_N(Nirvana_Sprite_Image_Stack, Nirvana_Sprite_Image_2)
		End If
	End If

	spr_id = CreateSprite(Nirvana_Sprite_Image_2, 64, 64)

	'-------ANIMATIONS-------

	spr_animation1 = CreateSpriteAnimation(spr_id, 2, 11)

	SetSpriteAnimationFrame(spr_id, spr_animation1, 0, 0)
	SetSpriteAnimationFrame(spr_id, spr_animation1, 1, 1)


	'-------SHAPE-------
detached_spr_id = -1

	SetSpriteShape(spr_id, SPRITE_SHAPE_POLYGON)
	Dim shape_point_x[6]
	Dim shape_point_y[6]

	shape_point_x[0] = 16
	shape_point_y[0] = 59

	shape_point_x[1] = 6
	shape_point_y[1] = 20

	shape_point_x[2] = 25
	shape_point_y[2] = 4

	shape_point_x[3] = 40
	shape_point_y[3] = 4

	shape_point_x[4] = 45
	shape_point_y[4] = 32

	shape_point_x[5] = 41
	shape_point_y[5] = 60

	SetSpritePolygon(spr_id, shape_point_x, shape_point_y, 6)

	Return spr_id
End Function


Function Nirvana_CreateSprite(base_name$, sprite_name$) As Nirvana_Sprite
	Dim nv_sprite As Nirvana_Sprite
	nv_sprite.Name$ = sprite_name$
	nv_sprite.BaseName$ = base_name$

	Select Case base_name$

	Case "grz"
		nv_sprite.Sprite_ID = Nirvana_SpriteDef_0(nv_sprite.Detached_Sprite_ID)
		nv_sprite.IsDetached = FALSE
		nv_sprite.Animation_Name_Index = 0
		nv_sprite.Animation_Count = 3

	Case "chr"
		nv_sprite.Sprite_ID = Nirvana_SpriteDef_1(nv_sprite.Detached_Sprite_ID)
		nv_sprite.IsDetached = FALSE
		nv_sprite.Animation_Name_Index = 2
		nv_sprite.Animation_Count = 2

	Case "gren_guy"
		nv_sprite.Sprite_ID = Nirvana_SpriteDef_2(nv_sprite.Detached_Sprite_ID)
		nv_sprite.IsDetached = FALSE
		nv_sprite.Animation_Name_Index = 3
		nv_sprite.Animation_Count = 2

	End Select

	Return nv_sprite
End Function
