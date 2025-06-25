Include "nirvana.bas"

Print "Color: "; RGBA(200, 200, 200, 255)

End

title$ = "Nirvana Template"
w = 640
h = 480
fullscreen = FALSE
vsync = FALSE

'Open a graphics window
OpenWindow( title$, w, h, fullscreen, vsync )

'Load Nirvana Stage
Nirvana_LoadStage("st1", 0, 0, w, h)

'Vector for storing camera position
Dim camera_position As Nirvana_Vector2D

'Variable for storing camera move speed
cam_speed = 4

layer_index = Nirvana_GetLayerIndex("sprite_layer1")
c_id = Nirvana_GetLayerCanvasID(layer_index)

Print "Layer Sprite Count = "; Nirvana_GetLayerSpriteCount(layer_index)

Print "Layer Sprite Index(guy1) = "; Nirvana_GetLayerSpriteIndex(layer_index, "guy1")
Print "Layer Sprite Index(c1) = "; Nirvana_GetLayerSpriteIndex(layer_index, "c1")

Print "NEW TEST"

Canvas(c_id)
chronos_id = Nirvana_GetSpriteID(Nirvana_GetLayerSpriteIndex(layer_index, "c1"))

Nirvana_SetStageOffset(Nirvana_CreateVector2D(816, 270))

'Exit While Loop when ESCAPE is pressed
While Not Key(K_ESCAPE)
	'Get the Current Camera Position
	camera_position = Nirvana_GetStageOffset()
	
	If Key(K_U) Then
		Print "Sprite Info: "; SpriteX(chronos_id); ", "; SpriteY(chronos_id)
		
		'SetSpriteAngularVelocity(chronos_id, 20)
		'RotateSprite(chronos_id, 2)
		Wait(5000)
		WaitKey()
	End If
	
	If Key(K_R) Then
		'SetSpriteAngularVelocity(chronos_id, 20)
		RotateSprite(chronos_id, 2)
	End If
	
	If Key(K_Y) Then
		setSpriteLinearVelocity(chronos_id, 20, 0)
		'Print "C: "; SpriteX(chronos_id); ", "; SpriteY(chronos_id)
		
		'Wait(5000)
		'WaitKey()
	End If
	
	If Key(K_T) Then
		Canvas(c_id)
		SetSpriteVisible(chronos_id, TRUE)
		SetSpriteSolid(chronos_id, TRUE)
		SetGravity2D(0, 10)
		While Key(K_T) : Update() : Wend
	End If
	
	If Key(K_1) Then
		'gz = Nirvana_GetSprite(Nirvana_GetSpriteIndex(Nirvana_GetLayerIndex("sprite_layer1"), "g1"))
		'DeleteSprite(gz)
		Nirvana_LoadStage("st1", 50, 50, w-100, h-100)
		camera_position = Nirvana_GetStageOffset()
	ElseIf Key(K_2) Then
		Nirvana_LoadStage("st2", 50, 50, w-100, h-100)
		camera_position = Nirvana_GetStageOffset()
	End If
	
	'Move camera position Left or Right when arrow keys are pressed
	If Key(K_LEFT) Then
		camera_position.X = camera_position.X - cam_speed
	ElseIf Key(K_RIGHT) Then
		camera_position.X = camera_position.X + cam_speed
	End If
	
	'Move camera position Up or Down when arrow keys are pressed
	If Key(K_UP) Then
		camera_position.Y = camera_position.Y - cam_speed
	ElseIf Key(K_DOWN) Then
		camera_position.Y = camera_position.Y + cam_speed
	End If
	
	'Set camera to new position
	Nirvana_SetStageOffset(camera_position)

	'This update function must be used for Nirvana Projects
	Nirvana_Update()
Wend
