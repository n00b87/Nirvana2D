Include "nirvana.bas"

title$ = "Nirvana2D Template"
w = 640
h = 480
fullscreen = FALSE
vsync = FALSE

'Open a graphics window
OpenWindow( title$, w, h, fullscreen, vsync )

'Load Nirvana Stage
Nirvana_LoadStage("[STAGE_NAME_HERE]", 0, 0, w, h)

'Vector for storing camera position
Dim camera_position As Nirvana_Vector2D

'Variable for storing camera move speed
cam_speed = 4

'Exit While Loop when ESCAPE is pressed
While Not Key(K_ESCAPE)
	'Get the Current Camera Position
	camera_position = Nirvana_GetStageOffset()
	
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
