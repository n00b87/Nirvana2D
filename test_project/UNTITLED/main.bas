Include "nirvana.bas"

title$ = "Nirvana2D Template"
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


'Exit While Loop when ESCAPE is pressed
While Not Key(K_ESCAPE) And WindowExists()
	'Get the Current Camera Position
	camera_position = Nirvana_GetStageOffset()
	
	If MouseButton(1) Then
		
		SetSpriteScale(Nirvana_GetSpriteID(Nirvana_GetLayerSpriteIndex(2, "C1_1")), 1, 1)
		
		While MouseButton(1)
			Update
		Wend
		
		Dim v As Nirvana_Vector2D 
		v = Nirvana_GetTileMapPosition(0, MouseX() + camera_position.X, MouseY() + camera_position.Y)
		Print "V = "; v.X; ", "; v.Y; ": "; Nirvana_GetTile(0, v.X, v.Y)
		
		'Nirvana_SetTile(0, 0, v.X, v.Y)
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
	
	If Key(K_SPACE) Then
		Nirvana_LoadStage("st2", 0, 0, w, h)
	ElseIf Key(K_B) Then
		Nirvana_LoadStage("st1", 0, 0, w, h)
	End If
	
	'Set camera to new position
	Nirvana_SetStageOffset(camera_position)

	'This update function must be used for Nirvana Projects
	Nirvana_Update()
Wend
