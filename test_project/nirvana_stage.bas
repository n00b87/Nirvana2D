Type Nirvana_Vector2D
Dim X
Dim Y
End Type

Type Nirvana_Size2D
Dim Width
Dim Height
End Type

Type Nirvana_Background
Dim Image_ID
Dim RenderSetting
End Type

Type Nirvana_Shape
Dim Sprite_ID
Dim ShapeType
End Type

Type Nirvana_Layer
Dim Name$
Dim LayerType
Dim Visible
Dim Alpha
Dim Scroll_Speed As Nirvana_Vector2D
Dim Ref_Canvas
Dim Layer_TileMap As Nirvana_TileMap
Dim Layer_Sprite_Count
Dim Layer_Shape_Count
Dim Bkg As Nirvana_Background
End Type

Type Nirvana_Stage
Dim Active
Dim Name$
Dim Tile_Size As Nirvana_Size2D
Dim Stage_Size As Nirvana_Size2D
Dim Layer_Count
Dim Viewport_Size As Nirvana_Size2D
Dim Stage_Offset As Nirvana_Vector2D
End Type


NIRVANA_DATA_DIR$ = NIRVANA_PROJECT_BASE_DIR$ + NIRVANA_PATH_SEPARATOR$ + "data" + NIRVANA_PATH_SEPARATOR$
NIRVANA_BKG_DIR$ = NIRVANA_PROJECT_BASE_DIR$ + NIRVANA_PATH_SEPARATOR$ + "bkg" + NIRVANA_PATH_SEPARATOR$

NIRVANA_LAYER_TYPE_TILEMAP = 0
NIRVANA_LAYER_TYPE_SPRITE = 1
NIRVANA_LAYER_TYPE_CANVAS_2D = 2
NIRVANA_LAYER_TYPE_CANVAS_3D = 3

NIRVANA_IMG_RENDER_SETTING_NORMAL = 0
NIRVANA_IMG_RENDER_SETTING_STRETCHED = 1
NIRVANA_IMG_RENDER_SETTING_TILED = 2


NIRVANA_WINDOW_WIDTH = 320
NIRVANA_WINDOW_HEIGHT = 200


Dim Nirvana_Stage_Sprites[1] As Nirvana_Sprite
Dim Nirvana_Stage_Shape_Points[1] As Nirvana_Vector2D
Dim Nirvana_Stage_Shapes[1] As Nirvana_Shape
Dim Nirvana_Stage_Layers[1] As Nirvana_Layer

For i = 0 To 0
	Nirvana_Stage_Layers[i].Ref_Canvas = -1
	Nirvana_Stage_Layers[i].Layer_TileMap.Tileset_ID = -1
	Nirvana_Stage_Layers[i].Layer_TileMap.TileMap_ID = -1
	Nirvana_Stage_Layers[i].Bkg.Image_ID = -1
Next

For i = 0 To 0
	Nirvana_Stage_Sprites[i].Sprite_ID = -1
Next

For i = 0 To 0
	Nirvana_Stage_Shapes[i].Sprite_ID = -1
Next

Dim Nirvana_ActiveStage As Nirvana_Stage : Nirvana_ActiveStage.Active = FALSE

'This is a utility function for reading binary data from tile maps
Function Nirvana_Read32(stream)
		Dim byte_array[4]
		byte_array[3] = ReadByte(stream)
		byte_array[2] = ReadByte(stream)
		byte_array[1] = ReadByte(stream)
		byte_array[0] = ReadByte(stream)
		Return (byte_array[0] shl 24) + (byte_array[1] shl 16) + (byte_array[2] shl 8) + byte_array[3]
End Function

Sub Nirvana_ClearStage()
	If Not Nirvana_ActiveStage.Active Then
		Return
	End If

	Nirvana_ActiveStage.Stage_Offset.X = 0
	Nirvana_ActiveStage.Stage_Offset.Y = 0
	For i = 0 To Nirvana_ActiveStage.Layer_Count-1

		CloseCanvas(Nirvana_Stage_Layers[i].Ref_Canvas)
		Nirvana_Stage_Layers[i].Ref_Canvas = -1

		If ImageExists(Nirvana_Stage_Layers[i].Bkg.Image_ID) Then
			DeleteImage(Nirvana_Stage_Layers[i].Bkg.Image_ID)
			Nirvana_Stage_Layers[i].Bkg.Image_ID = -1
		End If

		If Nirvana_Stage_Layers[i].LayerType = NIRVANA_LAYER_TYPE_TILEMAP Then
			DeleteTileMap(Nirvana_Stage_Layers[i].Layer_TileMap.TileMap_ID)
			DeleteTileSet(Nirvana_Stage_Layers[i].Layer_TileMap.Tileset_ID)
		End If

		Nirvana_Stage_Layers[i].Layer_TileMap.TileMap_ID = -1
		Nirvana_Stage_Layers[i].Layer_TileMap.Tileset_ID = -1

	Next

	While Stack_Size_N(Nirvana_Tileset_Image_Stack) > 0
		img_id = Pop_N(Nirvana_Tileset_Image_Stack)
		DeleteImage(img_id)
	Wend

	While Stack_Size_N(Nirvana_Sprite_Image_Stack) > 0
		img_id = Pop_N(Nirvana_Sprite_Image_Stack)
		DeleteImage(img_id)
	Wend

	Nirvana_ActiveStage.Active = FALSE

End Sub


Function Nirvana_LoadStage(stage_name$, viewport_x, viewport_y, viewport_w, viewport_h)
	GetWindowSize(NIRVANA_WINDOW_WIDTH, NIRVANA_WINDOW_HEIGHT)

	Select Case stage_name$

	Default
		Return FALSE
	End Select

	Nirvana_ActiveStage.Active = TRUE
	Nirvana_ActiveStage.Stage_Offset.X = 0
	Nirvana_ActiveStage.Stage_Offset.Y = 0
	Nirvana_ActiveStage.Viewport_Size.Width = viewport_w
	Nirvana_ActiveStage.Viewport_Size.Height = viewport_h
	Return TRUE
End Function


Sub Nirvana_Update()
	For layer_index = 0 To Nirvana_ActiveStage.Layer_Count-1
		Canvas(Nirvana_Stage_Layers[layer_index].Ref_Canvas)
		SetCanvasZ(Nirvana_Stage_Layers[layer_index].Ref_Canvas, Nirvana_ActiveStage.Layer_Count-layer_index)
		offset_x = Nirvana_ActiveStage.Stage_Offset.X * Nirvana_Stage_Layers[layer_index].Scroll_Speed.X
		offset_y = Nirvana_ActiveStage.Stage_Offset.Y * Nirvana_Stage_Layers[layer_index].Scroll_Speed.Y
		Select Case Nirvana_Stage_Layers[layer_index].LayerType
		Case NIRVANA_LAYER_TYPE_SPRITE
			SetCanvasOffset(Nirvana_Stage_Layers[layer_index].Ref_Canvas, offset_x, offset_y)
		Case NIRVANA_LAYER_TYPE_CANVAS_2D
			ClearCanvas()
			If ImageExists(Nirvana_Stage_Layers[layer_index].Bkg.Image_ID) Then
				Select Case Nirvana_Stage_Layers[layer_index].Bkg.RenderSetting
				Case NIRVANA_IMG_RENDER_SETTING_NORMAL
					DrawImage(Nirvana_Stage_Layers[layer_index].Bkg.Image_ID, 0, 0)
				Case NIRVANA_IMG_RENDER_SETTING_STRETCHED
					Dim img_w, img_h
					GetImageSize(Nirvana_Stage_Layers[layer_index].Bkg.Image_ID, img_w, img_h)
					DrawImage_BlitEx(Nirvana_Stage_Layers[layer_index].Bkg.Image_ID, 0, 0, Nirvana_ActiveStage.Viewport_Size.Width, Nirvana_ActiveStage.Viewport_Size.Height, 0, 0, img_w, img_h) 
				Case NIRVANA_IMG_RENDER_SETTING_TILED
					Dim img_w, img_h
					GetImageSize(Nirvana_Stage_Layers[layer_index].Bkg.Image_ID, img_w, img_h)
					tile_off_x = offset_x MOD img_w
					tile_off_y = offset_y MOD img_h
					For y = -1*tile_off_y To Nirvana_ActiveStage.Viewport_Size.Height-1 Step img_h
						For x = -1*tile_off_x To Nirvana_ActiveStage.Viewport_Size.Width-1 Step img_w
							DrawImage(Nirvana_Stage_Layers[layer_index].Bkg.Image_ID, x, y)
						Next
					Next
				End Select
			End If
		Case NIRVANA_LAYER_TYPE_TILEMAP
			ClearCanvas()
			DrawTileMap(Nirvana_Stage_Layers[layer_index].Layer_TileMap.TileMap_ID, 0, 0, Nirvana_ActiveStage.Viewport_Size.Width, Nirvana_ActiveStage.Viewport_Size.Height, offset_x, offset_y)
		End Select
	Next
	Update()
End Sub
