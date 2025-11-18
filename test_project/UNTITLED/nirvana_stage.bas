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
Dim Name$
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
Dim Layer_TileMap2 As Nirvana_TileMap
Dim Layer_Sprite_Count
Dim Layer_Shape_Count
Dim Bkg As Nirvana_Background
Dim Layer_TS_Stack
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
NIRVANA_LAYER_TYPE_ISO_TILEMAP = 1
NIRVANA_LAYER_TYPE_SPRITE = 2
NIRVANA_LAYER_TYPE_CANVAS_2D = 3
NIRVANA_LAYER_TYPE_CANVAS_3D = 4

NIRVANA_IMG_RENDER_SETTING_NORMAL = 0
NIRVANA_IMG_RENDER_SETTING_STRETCHED = 1
NIRVANA_IMG_RENDER_SETTING_TILED = 2


NIRVANA_WINDOW_WIDTH = 320
NIRVANA_WINDOW_HEIGHT = 200


Dim Nirvana_Stage_Sprites[9] As Nirvana_Sprite
Dim Nirvana_Stage_Shape_Points[1] As Nirvana_Vector2D
Dim Nirvana_Stage_Shapes[5] As Nirvana_Shape
Dim Nirvana_Stage_Layers[5] As Nirvana_Layer

For i = 0 To 4
	Nirvana_Stage_Layers[i].Ref_Canvas = -1
	Nirvana_Stage_Layers[i].Layer_TileMap.Tileset_ID = -1
	Nirvana_Stage_Layers[i].Layer_TileMap.TileMap_ID = -1
	Nirvana_Stage_Layers[i].Layer_TileMap2.Tileset_ID = -1
	Nirvana_Stage_Layers[i].Layer_TileMap2.TileMap_ID = -1
	Nirvana_Stage_Layers[i].Bkg.Image_ID = -1
Next

For i = 0 To 8
	Nirvana_Stage_Sprites[i].Sprite_ID = -1
Next

For i = 0 To 4
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

		DeleteStack_N(Nirvana_Stage_Layers[i].Layer_TS_Stack)
		Nirvana_Stage_Layers[i].Layer_TS_Stack = -1

		If ImageExists(Nirvana_Stage_Layers[i].Bkg.Image_ID) Then
			DeleteImage(Nirvana_Stage_Layers[i].Bkg.Image_ID)
			Nirvana_Stage_Layers[i].Bkg.Image_ID = -1
		End If

		If Nirvana_Stage_Layers[i].LayerType = NIRVANA_LAYER_TYPE_TILEMAP Then
			DeleteTileMap(Nirvana_Stage_Layers[i].Layer_TileMap.TileMap_ID)
			DeleteTileSet(Nirvana_Stage_Layers[i].Layer_TileMap.Tileset_ID)
		ElseIf Nirvana_Stage_Layers[i].LayerType = NIRVANA_LAYER_TYPE_ISO_TILEMAP Then
			DeleteTileMap(Nirvana_Stage_Layers[i].Layer_TileMap.TileMap_ID)
			DeleteTileMap(Nirvana_Stage_Layers[i].Layer_TileMap2.TileMap_ID)
			DeleteTileSet(Nirvana_Stage_Layers[i].Layer_TileMap.Tileset_ID)
		End If

		Nirvana_Stage_Layers[i].Layer_TileMap.TileMap_ID = -1
		Nirvana_Stage_Layers[i].Layer_TileMap2.TileMap_ID = -1
		Nirvana_Stage_Layers[i].Layer_TileMap.Tileset_ID = -1

		Nirvana_Stage_Layers[i].Layer_TileMap2.Tileset_ID = -1

	Next

	While Stack_Size_N(Nirvana_Tileset_Image_Stack) > 0
		img_id = Pop_N(Nirvana_Tileset_Image_Stack)
		DeleteImage(img_id)
	Wend

	While Stack_Size_N(Nirvana_Sprite_Image_Stack) > 0
		img_id = Pop_N(Nirvana_Sprite_Image_Stack)
		DeleteImage(img_id)
	Wend

	Nirvana_Tileset_ID_0 = -1
	Nirvana_Tileset_Image_0 = -1

	Nirvana_Tileset_ID_1 = -1
	Nirvana_Tileset_Image_1 = -1

	Nirvana_Tileset_ID_2 = -1
	Nirvana_Tileset_Image_2 = -1

	Nirvana_Sprite_Image_0 = -1
	Nirvana_Sprite_Image_1 = -1
	Nirvana_Sprite_Image_2 = -1
	Nirvana_ActiveStage.Active = FALSE

End Sub

Function Nirvana_Stage_0(vp_x, vp_y, vp_w, vp_h) As Nirvana_Stage
	Print "DBG 1"
	Nirvana_ClearStage()
	Print "DBG 2"

	Dim nv_stage As Nirvana_Stage
	Print "DBG x0"
	nv_stage.Name$ = "st1"
	nv_stage.Tile_Size.Width = 32
	nv_stage.Tile_Size.Height = 32
	nv_stage.Stage_Size.Width = 60
	nv_stage.Stage_Size.Height = 70
	nv_stage.Layer_Count = 5
	Print "DBG x1"

	'-------LAYER (bg)-------

	Nirvana_Stage_Layers[0].Name$ = "bg"
	Nirvana_Stage_Layers[0].LayerType = NIRVANA_LAYER_TYPE_CANVAS_2D
	Nirvana_Stage_Layers[0].Visible = TRUE
	Nirvana_Stage_Layers[0].Alpha = 200
	Nirvana_Stage_Layers[0].Scroll_Speed.X = 1
	Nirvana_Stage_Layers[0].Scroll_Speed.Y = 1
	Nirvana_Stage_Layers[0].Layer_TS_Stack = -1  ' This will be set to a stack if needed in sprite layer 
	Print "DBG x2: "; NIRVANA_WINDOW_WIDTH; ", "; NIRVANA_WINDOW_HEIGHT; ", "; vp_x; ", "; vp_y; ", "; vp_w; ", "; vp_h

	Nirvana_Stage_Layers[0].Ref_Canvas = OpenCanvas(NIRVANA_WINDOW_WIDTH, NIRVANA_WINDOW_HEIGHT, vp_x, vp_y, vp_w, vp_h, 1)
	Print "DBG n1"
	Nirvana_Stage_Layers[0].Bkg.Image_ID = LoadImage(NIRVANA_BKG_DIR$ + "final_bkg.png")
	Print "DBG n2"
	Nirvana_Stage_Layers[0].Bkg.RenderSetting = NIRVANA_IMG_RENDER_SETTING_TILED
	Print "DBG x3"

	'-------LAYER (tile_layer1)-------

	Nirvana_Stage_Layers[1].Name$ = "tile_layer1"
	Nirvana_Stage_Layers[1].LayerType = NIRVANA_LAYER_TYPE_TILEMAP
	Nirvana_Stage_Layers[1].Visible = TRUE
	Nirvana_Stage_Layers[1].Alpha = 255
	Nirvana_Stage_Layers[1].Scroll_Speed.X = 1
	Nirvana_Stage_Layers[1].Scroll_Speed.Y = 1
	Nirvana_Stage_Layers[1].Layer_TS_Stack = -1  ' This will be set to a stack if needed in sprite layer 
Print "DBG x4"
	Nirvana_Stage_Layers[1].Ref_Canvas = OpenCanvas(NIRVANA_WINDOW_WIDTH, NIRVANA_WINDOW_HEIGHT, vp_x, vp_y, vp_w, vp_h, 1)
Print "DBG x5"
	'------- TILEMAP -------
	Nirvana_Stage_Layers[1].Layer_TileMap = Nirvana_CreateTileMap("tset1", 60, 70)

	Print "DBG 2.1"
	f = OpenFile(NIRVANA_DATA_DIR$ + "tm0.data", BINARY_INPUT)
	For y = 0 To 69
		For x = 0 To 59
			SetTile(Nirvana_Stage_Layers[1].Layer_TileMap.TileMap_ID, Nirvana_Read32(f), x, y)
		Next
	Next
	CloseFile(f)
	Print "DBG 2.2"

	'-------LAYER (sprite_layer1)-------

	Nirvana_Stage_Layers[2].Name$ = "sprite_layer1"
	Nirvana_Stage_Layers[2].LayerType = NIRVANA_LAYER_TYPE_SPRITE
	Nirvana_Stage_Layers[2].Visible = TRUE
	Nirvana_Stage_Layers[2].Alpha = 255
	Nirvana_Stage_Layers[2].Scroll_Speed.X = 1
	Nirvana_Stage_Layers[2].Scroll_Speed.Y = 1
	Nirvana_Stage_Layers[2].Layer_TS_Stack = -1  ' This will be set to a stack if needed in sprite layer 

	Nirvana_Stage_Layers[2].Ref_Canvas = OpenCanvasSpriteLayer(vp_x, vp_y, vp_w, vp_h)
	SetSpriteCanvasRenderPriority(Nirvana_Stage_Layers[2].Ref_Canvas, SPRITE_PRIORITY_GREATEST_Y, SPRITE_ORDER_DESCENDING)
	Canvas(Nirvana_Stage_Layers[2].Ref_Canvas)
	Nirvana_Stage_Layers[2].Layer_Sprite_Count = 8
	Nirvana_Stage_Layers[2].Layer_Shape_Count = 5

	'------- SPRITE ("g1") -------
	Nirvana_Stage_Sprites[0] = Nirvana_CreateSprite("grz", "g1")

	'Base Settings
	SetSpriteType(Nirvana_Stage_Sprites[0].Sprite_ID, SPRITE_TYPE_STATIC)
	SetSpriteAnimation(Nirvana_Stage_Sprites[0].Sprite_ID, 2, -1)

	'Shape
	SetSpriteShape(Nirvana_Stage_Sprites[0].Sprite_ID, SPRITE_SHAPE_BOX)
	SetSpriteShapeOffset(Nirvana_Stage_Sprites[0].Sprite_ID, 20, 0)
	SetSpriteBox(Nirvana_Stage_Sprites[0].Sprite_ID, 23, 64)

	'Transform
	SetSpritePosition(Nirvana_Stage_Sprites[0].Sprite_ID, 108, 417)
	SetSpriteScale(Nirvana_Stage_Sprites[0].Sprite_ID, 1, 1)
	SetSpriteRotation(Nirvana_Stage_Sprites[0].Sprite_ID, 228.829)

	'Render Settings
	SetSpriteAlpha(Nirvana_Stage_Sprites[0].Sprite_ID, 255)
	SetSpriteVisible(Nirvana_Stage_Sprites[0].Sprite_ID, TRUE)

	'------- SPRITE ("c1") -------
	Nirvana_Stage_Sprites[1] = Nirvana_CreateSprite("chr", "c1")

	'Base Settings
	SetSpriteType(Nirvana_Stage_Sprites[1].Sprite_ID, SPRITE_TYPE_DYNAMIC)
	SetSpriteAnimation(Nirvana_Stage_Sprites[1].Sprite_ID, 0, -1)

	'Shape
	SetSpriteShape(Nirvana_Stage_Sprites[1].Sprite_ID, SPRITE_SHAPE_BOX)
	SetSpriteShapeOffset(Nirvana_Stage_Sprites[1].Sprite_ID, 8, 138)
	SetSpriteBox(Nirvana_Stage_Sprites[1].Sprite_ID, 87, 57)

	'Transform
	SetSpritePosition(Nirvana_Stage_Sprites[1].Sprite_ID, 944, 369)
	SetSpriteScale(Nirvana_Stage_Sprites[1].Sprite_ID, 1, 1)
	SetSpriteRotation(Nirvana_Stage_Sprites[1].Sprite_ID, 0)

	'Render Settings
	SetSpriteAlpha(Nirvana_Stage_Sprites[1].Sprite_ID, 255)
	SetSpriteVisible(Nirvana_Stage_Sprites[1].Sprite_ID, TRUE)

	'------- SPRITE ("G1_1") -------
	Nirvana_Stage_Sprites[2] = Nirvana_CreateSprite("grz", "G1_1")

	'Base Settings
	SetSpriteType(Nirvana_Stage_Sprites[2].Sprite_ID, SPRITE_TYPE_STATIC)
	SetSpriteAnimation(Nirvana_Stage_Sprites[2].Sprite_ID, 2, -1)

	'Shape
	SetSpriteShape(Nirvana_Stage_Sprites[2].Sprite_ID, SPRITE_SHAPE_BOX)
	SetSpriteShapeOffset(Nirvana_Stage_Sprites[2].Sprite_ID, 20, 0)
	SetSpriteBox(Nirvana_Stage_Sprites[2].Sprite_ID, 23, 64)

	'Transform
	SetSpritePosition(Nirvana_Stage_Sprites[2].Sprite_ID, 86, 422)
	SetSpriteScale(Nirvana_Stage_Sprites[2].Sprite_ID, 1, 1)
	SetSpriteRotation(Nirvana_Stage_Sprites[2].Sprite_ID, 331.669)

	'Render Settings
	SetSpriteAlpha(Nirvana_Stage_Sprites[2].Sprite_ID, 255)
	SetSpriteVisible(Nirvana_Stage_Sprites[2].Sprite_ID, TRUE)

	'------- SPRITE ("G1_1_1") -------
	Nirvana_Stage_Sprites[3] = Nirvana_CreateSprite("grz", "G1_1_1")

	'Base Settings
	SetSpriteType(Nirvana_Stage_Sprites[3].Sprite_ID, SPRITE_TYPE_STATIC)
	SetSpriteAnimation(Nirvana_Stage_Sprites[3].Sprite_ID, 2, -1)

	'Shape
	SetSpriteShape(Nirvana_Stage_Sprites[3].Sprite_ID, SPRITE_SHAPE_BOX)
	SetSpriteShapeOffset(Nirvana_Stage_Sprites[3].Sprite_ID, 20, 0)
	SetSpriteBox(Nirvana_Stage_Sprites[3].Sprite_ID, 23, 64)

	'Transform
	SetSpritePosition(Nirvana_Stage_Sprites[3].Sprite_ID, 57, 413)
	SetSpriteScale(Nirvana_Stage_Sprites[3].Sprite_ID, 1, 1)
	SetSpriteRotation(Nirvana_Stage_Sprites[3].Sprite_ID, 54.021)

	'Render Settings
	SetSpriteAlpha(Nirvana_Stage_Sprites[3].Sprite_ID, 255)
	SetSpriteVisible(Nirvana_Stage_Sprites[3].Sprite_ID, TRUE)

	'------- SPRITE ("C1_1") -------
	Nirvana_Stage_Sprites[4] = Nirvana_CreateSprite("chr", "C1_1")

	'Base Settings
	SetSpriteType(Nirvana_Stage_Sprites[4].Sprite_ID, SPRITE_TYPE_DYNAMIC)
	SetSpriteAnimation(Nirvana_Stage_Sprites[4].Sprite_ID, 0, -1)

	'Shape
	SetSpriteShape(Nirvana_Stage_Sprites[4].Sprite_ID, SPRITE_SHAPE_BOX)
	SetSpriteShapeOffset(Nirvana_Stage_Sprites[4].Sprite_ID, 8, 138)
	SetSpriteBox(Nirvana_Stage_Sprites[4].Sprite_ID, 87, 57)

	'Transform
	SetSpritePosition(Nirvana_Stage_Sprites[4].Sprite_ID, 1040, 457)
	SetSpriteScale(Nirvana_Stage_Sprites[4].Sprite_ID, 1, 1)
	SetSpriteRotation(Nirvana_Stage_Sprites[4].Sprite_ID, 0)

	'Render Settings
	SetSpriteAlpha(Nirvana_Stage_Sprites[4].Sprite_ID, 255)
	SetSpriteVisible(Nirvana_Stage_Sprites[4].Sprite_ID, TRUE)

	'------- SPRITE ("C1_1_1") -------
	Nirvana_Stage_Sprites[5] = Nirvana_CreateSprite("chr", "C1_1_1")

	'Base Settings
	SetSpriteType(Nirvana_Stage_Sprites[5].Sprite_ID, SPRITE_TYPE_DYNAMIC)
	SetSpriteAnimation(Nirvana_Stage_Sprites[5].Sprite_ID, 0, -1)

	'Shape
	SetSpriteShape(Nirvana_Stage_Sprites[5].Sprite_ID, SPRITE_SHAPE_BOX)
	SetSpriteShapeOffset(Nirvana_Stage_Sprites[5].Sprite_ID, 8, 138)
	SetSpriteBox(Nirvana_Stage_Sprites[5].Sprite_ID, 87, 57)

	'Transform
	SetSpritePosition(Nirvana_Stage_Sprites[5].Sprite_ID, 1136, 546)
	SetSpriteScale(Nirvana_Stage_Sprites[5].Sprite_ID, 1, 1)
	SetSpriteRotation(Nirvana_Stage_Sprites[5].Sprite_ID, 0)

	'Render Settings
	SetSpriteAlpha(Nirvana_Stage_Sprites[5].Sprite_ID, 255)
	SetSpriteVisible(Nirvana_Stage_Sprites[5].Sprite_ID, TRUE)

	'------- SPRITE ("C1_1_1_1") -------
	Nirvana_Stage_Sprites[6] = Nirvana_CreateSprite("chr", "C1_1_1_1")

	'Base Settings
	SetSpriteType(Nirvana_Stage_Sprites[6].Sprite_ID, SPRITE_TYPE_DYNAMIC)
	SetSpriteAnimation(Nirvana_Stage_Sprites[6].Sprite_ID, 0, -1)

	'Shape
	SetSpriteShape(Nirvana_Stage_Sprites[6].Sprite_ID, SPRITE_SHAPE_BOX)
	SetSpriteShapeOffset(Nirvana_Stage_Sprites[6].Sprite_ID, 8, 138)
	SetSpriteBox(Nirvana_Stage_Sprites[6].Sprite_ID, 87, 57)

	'Transform
	SetSpritePosition(Nirvana_Stage_Sprites[6].Sprite_ID, 991, 415)
	SetSpriteScale(Nirvana_Stage_Sprites[6].Sprite_ID, 1, 1)
	SetSpriteRotation(Nirvana_Stage_Sprites[6].Sprite_ID, 0)

	'Render Settings
	SetSpriteAlpha(Nirvana_Stage_Sprites[6].Sprite_ID, 255)
	SetSpriteVisible(Nirvana_Stage_Sprites[6].Sprite_ID, TRUE)

	'------- SPRITE ("C1_1_1_1_1") -------
	Nirvana_Stage_Sprites[7] = Nirvana_CreateSprite("chr", "C1_1_1_1_1")

	'Base Settings
	SetSpriteType(Nirvana_Stage_Sprites[7].Sprite_ID, SPRITE_TYPE_DYNAMIC)
	SetSpriteAnimation(Nirvana_Stage_Sprites[7].Sprite_ID, 0, -1)

	'Shape
	SetSpriteShape(Nirvana_Stage_Sprites[7].Sprite_ID, SPRITE_SHAPE_BOX)
	SetSpriteShapeOffset(Nirvana_Stage_Sprites[7].Sprite_ID, 8, 138)
	SetSpriteBox(Nirvana_Stage_Sprites[7].Sprite_ID, 87, 57)

	'Transform
	SetSpritePosition(Nirvana_Stage_Sprites[7].Sprite_ID, 1089, 503)
	SetSpriteScale(Nirvana_Stage_Sprites[7].Sprite_ID, 1, 1)
	SetSpriteRotation(Nirvana_Stage_Sprites[7].Sprite_ID, 0)

	'Render Settings
	SetSpriteAlpha(Nirvana_Stage_Sprites[7].Sprite_ID, 255)
	SetSpriteVisible(Nirvana_Stage_Sprites[7].Sprite_ID, TRUE)

	'------- SHAPE ("POLYGON_1") -------
	Nirvana_Stage_Shapes[0].Name$ = "POLYGON_1"
	Nirvana_Stage_Shapes[0].Sprite_ID = CreateSprite(-1, 1, 1)

	'Base Settings
	SetSpriteType(Nirvana_Stage_Shapes[0].Sprite_ID, SPRITE_TYPE_STATIC)
	SetSpriteSolid(Nirvana_Stage_Shapes[0].Sprite_ID, TRUE)
	'Shape
	Nirvana_Stage_Shapes[0].ShapeType = SPRITE_SHAPE_POLYGON
	SetSpriteShape(Nirvana_Stage_Shapes[0].Sprite_ID, Nirvana_Stage_Shapes[0].ShapeType)
	Dim stage_shape_x_0[4]
	Dim stage_shape_y_0[4]

	stage_shape_x_0[0] = 671
	stage_shape_y_0[0] = 242

	stage_shape_x_0[1] = 548
	stage_shape_y_0[1] = 340

	stage_shape_x_0[2] = 683
	stage_shape_y_0[2] = 450

	stage_shape_x_0[3] = 792
	stage_shape_y_0[3] = 345

	SetSpritePolygon(Nirvana_Stage_Shapes[0].Sprite_ID, stage_shape_x_0, stage_shape_y_0, 4)

	'Transform
	SetSpritePosition(Nirvana_Stage_Shapes[0].Sprite_ID,  0, 0) 'Set to (0,0) so that offset will be world position
	SetSpriteVisible(Nirvana_Stage_Shapes[0].Sprite_ID, FALSE) 'Image is -1 so it wouldn't render anyway

	'------- SHAPE ("CHAIN_1") -------
	Nirvana_Stage_Shapes[1].Name$ = "CHAIN_1"
	Nirvana_Stage_Shapes[1].Sprite_ID = CreateSprite(-1, 1, 1)

	'Base Settings
	SetSpriteType(Nirvana_Stage_Shapes[1].Sprite_ID, SPRITE_TYPE_STATIC)
	SetSpriteSolid(Nirvana_Stage_Shapes[1].Sprite_ID, TRUE)
	'Shape
	Nirvana_Stage_Shapes[1].ShapeType = SPRITE_SHAPE_CHAIN
	SetSpriteShape(Nirvana_Stage_Shapes[1].Sprite_ID, Nirvana_Stage_Shapes[1].ShapeType)
	Dim stage_shape_x_1[5]
	Dim stage_shape_y_1[5]

	stage_shape_x_1[0] = 637
	stage_shape_y_1[0] = 382

	stage_shape_x_1[1] = 614
	stage_shape_y_1[1] = 302

	stage_shape_x_1[2] = 668
	stage_shape_y_1[2] = 346

	stage_shape_x_1[3] = 724
	stage_shape_y_1[3] = 297

	stage_shape_x_1[4] = 696
	stage_shape_y_1[4] = 378

	SetSpriteChain(Nirvana_Stage_Shapes[1].Sprite_ID, stage_shape_x_1, stage_shape_y_1, 5, 636, 381, 697, 377)

	'Transform
	SetSpritePosition(Nirvana_Stage_Shapes[1].Sprite_ID,  0, 0) 'Set to (0,0) so that offset will be world position
	SetSpriteVisible(Nirvana_Stage_Shapes[1].Sprite_ID, FALSE) 'Image is -1 so it wouldn't render anyway

	'------- SHAPE ("BOX_1") -------
	Nirvana_Stage_Shapes[2].Name$ = "BOX_1"
	Nirvana_Stage_Shapes[2].Sprite_ID = CreateSprite(-1, 1, 1)

	'Base Settings
	SetSpriteType(Nirvana_Stage_Shapes[2].Sprite_ID, SPRITE_TYPE_STATIC)
	SetSpriteSolid(Nirvana_Stage_Shapes[2].Sprite_ID, TRUE)
	'Shape
	Nirvana_Stage_Shapes[2].ShapeType = SPRITE_SHAPE_BOX
	SetSpriteShape(Nirvana_Stage_Shapes[2].Sprite_ID, Nirvana_Stage_Shapes[2].ShapeType)
	SetSpriteShapeOffset(Nirvana_Stage_Shapes[2].Sprite_ID, 571, 476)
	SetSpriteBox(Nirvana_Stage_Shapes[2].Sprite_ID, 233, 40)

	'Transform
	SetSpritePosition(Nirvana_Stage_Shapes[2].Sprite_ID,  0, 0) 'Set to (0,0) so that offset will be world position
	SetSpriteVisible(Nirvana_Stage_Shapes[2].Sprite_ID, FALSE) 'Image is -1 so it wouldn't render anyway

	'------- SHAPE ("BOX_2") -------
	Nirvana_Stage_Shapes[3].Name$ = "BOX_2"
	Nirvana_Stage_Shapes[3].Sprite_ID = CreateSprite(-1, 1, 1)

	'Base Settings
	SetSpriteType(Nirvana_Stage_Shapes[3].Sprite_ID, SPRITE_TYPE_STATIC)
	SetSpriteSolid(Nirvana_Stage_Shapes[3].Sprite_ID, TRUE)
	'Shape
	Nirvana_Stage_Shapes[3].ShapeType = SPRITE_SHAPE_BOX
	SetSpriteShape(Nirvana_Stage_Shapes[3].Sprite_ID, Nirvana_Stage_Shapes[3].ShapeType)
	SetSpriteShapeOffset(Nirvana_Stage_Shapes[3].Sprite_ID, 8, 288)
	SetSpriteBox(Nirvana_Stage_Shapes[3].Sprite_ID, 532, 127)

	'Transform
	SetSpritePosition(Nirvana_Stage_Shapes[3].Sprite_ID,  0, 0) 'Set to (0,0) so that offset will be world position
	SetSpriteVisible(Nirvana_Stage_Shapes[3].Sprite_ID, FALSE) 'Image is -1 so it wouldn't render anyway

	'------- SHAPE ("CHAIN_2") -------
	Nirvana_Stage_Shapes[4].Name$ = "CHAIN_2"
	Nirvana_Stage_Shapes[4].Sprite_ID = CreateSprite(-1, 1, 1)

	'Base Settings
	SetSpriteType(Nirvana_Stage_Shapes[4].Sprite_ID, SPRITE_TYPE_STATIC)
	SetSpriteSolid(Nirvana_Stage_Shapes[4].Sprite_ID, TRUE)
	'Shape
	Nirvana_Stage_Shapes[4].ShapeType = SPRITE_SHAPE_CHAIN
	SetSpriteShape(Nirvana_Stage_Shapes[4].Sprite_ID, Nirvana_Stage_Shapes[4].ShapeType)
	Dim stage_shape_x_4[6]
	Dim stage_shape_y_4[6]

	stage_shape_x_4[0] = 928
	stage_shape_y_4[0] = 577

	stage_shape_x_4[1] = 1214
	stage_shape_y_4[1] = 861

	stage_shape_x_4[2] = 1311
	stage_shape_y_4[2] = 862

	stage_shape_x_4[3] = 1551
	stage_shape_y_4[3] = 622

	stage_shape_x_4[4] = 1779
	stage_shape_y_4[4] = 852

	stage_shape_x_4[5] = 1914
	stage_shape_y_4[5] = 703

	SetSpriteChain(Nirvana_Stage_Shapes[4].Sprite_ID, stage_shape_x_4, stage_shape_y_4, 6, 927, 576, 1915, 702)

	'Transform
	SetSpritePosition(Nirvana_Stage_Shapes[4].Sprite_ID,  0, 0) 'Set to (0,0) so that offset will be world position
	SetSpriteVisible(Nirvana_Stage_Shapes[4].Sprite_ID, FALSE) 'Image is -1 so it wouldn't render anyway

	Print "DBG 3"
	'------- TILE SPRITES  -------
	Cut_Start_Index = 0
	Nirvana_Stage_Layers[2].Layer_TS_Stack = CreateStack_N()
	cut_index = Cut_Start_Index + 0
	t_sprite = CreateSprite(Nirvana_Tileset_Cuts[Cut_Start_Index + 0].Image_ID, Nirvana_Tileset_Cuts[cut_index].NumCols * 32, Nirvana_Tileset_Cuts[cut_index].NumRows * 32)
	Push_N(Nirvana_Stage_Layers[2].Layer_TS_Stack, t_sprite)
	SetSpritePosition( t_sprite, 32, 32)

	cut_index = Cut_Start_Index + 0
	t_sprite = CreateSprite(Nirvana_Tileset_Cuts[Cut_Start_Index + 0].Image_ID, Nirvana_Tileset_Cuts[cut_index].NumCols * 32, Nirvana_Tileset_Cuts[cut_index].NumRows * 32)
	Push_N(Nirvana_Stage_Layers[2].Layer_TS_Stack, t_sprite)
	SetSpritePosition( t_sprite, 464, 16)

	cut_index = Cut_Start_Index + 0
	t_sprite = CreateSprite(Nirvana_Tileset_Cuts[Cut_Start_Index + 0].Image_ID, Nirvana_Tileset_Cuts[cut_index].NumCols * 32, Nirvana_Tileset_Cuts[cut_index].NumRows * 32)
	Push_N(Nirvana_Stage_Layers[2].Layer_TS_Stack, t_sprite)
	SetSpritePosition( t_sprite, 128, 128)

	cut_index = Cut_Start_Index + 1
	t_sprite = CreateSprite(Nirvana_Tileset_Cuts[Cut_Start_Index + 1].Image_ID, Nirvana_Tileset_Cuts[cut_index].NumCols * 32, Nirvana_Tileset_Cuts[cut_index].NumRows * 32)
	Push_N(Nirvana_Stage_Layers[2].Layer_TS_Stack, t_sprite)
	SetSpritePosition( t_sprite, 272, 176)

	cut_index = Cut_Start_Index + 2
	t_sprite = CreateSprite(Nirvana_Tileset_Cuts[Cut_Start_Index + 2].Image_ID, Nirvana_Tileset_Cuts[cut_index].NumCols * 32, Nirvana_Tileset_Cuts[cut_index].NumRows * 32)
	Push_N(Nirvana_Stage_Layers[2].Layer_TS_Stack, t_sprite)
	SetSpritePosition( t_sprite, 176, 272)

	cut_index = Cut_Start_Index + 2
	t_sprite = CreateSprite(Nirvana_Tileset_Cuts[Cut_Start_Index + 2].Image_ID, Nirvana_Tileset_Cuts[cut_index].NumCols * 32, Nirvana_Tileset_Cuts[cut_index].NumRows * 32)
	Push_N(Nirvana_Stage_Layers[2].Layer_TS_Stack, t_sprite)
	SetSpritePosition( t_sprite, 240, 272)

	cut_index = Cut_Start_Index + 2
	t_sprite = CreateSprite(Nirvana_Tileset_Cuts[Cut_Start_Index + 2].Image_ID, Nirvana_Tileset_Cuts[cut_index].NumCols * 32, Nirvana_Tileset_Cuts[cut_index].NumRows * 32)
	Push_N(Nirvana_Stage_Layers[2].Layer_TS_Stack, t_sprite)
	SetSpritePosition( t_sprite, 304, 272)

	cut_index = Cut_Start_Index + 3
	t_sprite = CreateSprite(Nirvana_Tileset_Cuts[Cut_Start_Index + 3].Image_ID, Nirvana_Tileset_Cuts[cut_index].NumCols * 32, Nirvana_Tileset_Cuts[cut_index].NumRows * 32)
	Push_N(Nirvana_Stage_Layers[2].Layer_TS_Stack, t_sprite)
	SetSpritePosition( t_sprite, 64, 320)


	'-------LAYER (tile_layer2)-------

	Nirvana_Stage_Layers[3].Name$ = "tile_layer2"
	Nirvana_Stage_Layers[3].LayerType = NIRVANA_LAYER_TYPE_TILEMAP
	Nirvana_Stage_Layers[3].Visible = TRUE
	Nirvana_Stage_Layers[3].Alpha = 255
	Nirvana_Stage_Layers[3].Scroll_Speed.X = 1
	Nirvana_Stage_Layers[3].Scroll_Speed.Y = 1
	Nirvana_Stage_Layers[3].Layer_TS_Stack = -1  ' This will be set to a stack if needed in sprite layer 

	Nirvana_Stage_Layers[3].Ref_Canvas = OpenCanvas(NIRVANA_WINDOW_WIDTH, NIRVANA_WINDOW_HEIGHT, vp_x, vp_y, vp_w, vp_h, 1)

	'------- TILEMAP -------
	Nirvana_Stage_Layers[3].Layer_TileMap = Nirvana_CreateTileMap("tset2", 60, 70)

	f = OpenFile(NIRVANA_DATA_DIR$ + "tm1.data", BINARY_INPUT)
	For y = 0 To 69
		For x = 0 To 59
			SetTile(Nirvana_Stage_Layers[3].Layer_TileMap.TileMap_ID, Nirvana_Read32(f), x, y)
		Next
	Next
	CloseFile(f)

	'-------LAYER (sprite_layer2)-------

	Nirvana_Stage_Layers[4].Name$ = "sprite_layer2"
	Nirvana_Stage_Layers[4].LayerType = NIRVANA_LAYER_TYPE_SPRITE
	Nirvana_Stage_Layers[4].Visible = TRUE
	Nirvana_Stage_Layers[4].Alpha = 255
	Nirvana_Stage_Layers[4].Scroll_Speed.X = 1
	Nirvana_Stage_Layers[4].Scroll_Speed.Y = 1
	Nirvana_Stage_Layers[4].Layer_TS_Stack = -1  ' This will be set to a stack if needed in sprite layer 

	Nirvana_Stage_Layers[4].Ref_Canvas = OpenCanvasSpriteLayer(vp_x, vp_y, vp_w, vp_h)
	SetSpriteCanvasRenderPriority(Nirvana_Stage_Layers[4].Ref_Canvas, SPRITE_PRIORITY_NONE, SPRITE_ORDER_ASCENDING)
	Canvas(Nirvana_Stage_Layers[4].Ref_Canvas)
	Nirvana_Stage_Layers[4].Layer_Sprite_Count = 1
	Nirvana_Stage_Layers[4].Layer_Shape_Count = 0

	'------- SPRITE ("guy1") -------
	Nirvana_Stage_Sprites[8] = Nirvana_CreateSprite("gren_guy", "guy1")

	'Base Settings
	SetSpriteType(Nirvana_Stage_Sprites[8].Sprite_ID, SPRITE_TYPE_DYNAMIC)
	SetSpriteAnimation(Nirvana_Stage_Sprites[8].Sprite_ID, 0, -1)

	'Shape
	SetSpriteShape(Nirvana_Stage_Sprites[8].Sprite_ID, SPRITE_SHAPE_POLYGON)
	Dim sprite_shape_x_8[6]
	Dim sprite_shape_y_8[6]

	sprite_shape_x_8[0] = 16
	sprite_shape_y_8[0] = 59

	sprite_shape_x_8[1] = 6
	sprite_shape_y_8[1] = 20

	sprite_shape_x_8[2] = 25
	sprite_shape_y_8[2] = 4

	sprite_shape_x_8[3] = 40
	sprite_shape_y_8[3] = 4

	sprite_shape_x_8[4] = 45
	sprite_shape_y_8[4] = 32

	sprite_shape_x_8[5] = 41
	sprite_shape_y_8[5] = 60

	SetSpritePolygon(Nirvana_Stage_Sprites[8].Sprite_ID, sprite_shape_x_8, sprite_shape_y_8, 6)

	'Transform
	SetSpritePosition(Nirvana_Stage_Sprites[8].Sprite_ID, 559, 446)
	SetSpriteScale(Nirvana_Stage_Sprites[8].Sprite_ID, 1, 1)
	SetSpriteRotation(Nirvana_Stage_Sprites[8].Sprite_ID, 360)

	'Render Settings
	SetSpriteAlpha(Nirvana_Stage_Sprites[8].Sprite_ID, 180)
	SetSpriteVisible(Nirvana_Stage_Sprites[8].Sprite_ID, TRUE)

	'------- TILE SPRITES  -------
	Cut_Start_Index = 4
	Nirvana_Stage_Layers[4].Layer_TS_Stack = CreateStack_N()
	cut_index = Cut_Start_Index + -1
	t_sprite = CreateSprite(Nirvana_Tileset_Cuts[Cut_Start_Index + -1].Image_ID, Nirvana_Tileset_Cuts[cut_index].NumCols * 32, Nirvana_Tileset_Cuts[cut_index].NumRows * 32)
	Push_N(Nirvana_Stage_Layers[4].Layer_TS_Stack, t_sprite)
	SetSpritePosition( t_sprite, 64, 256)

	cut_index = Cut_Start_Index + 0
	t_sprite = CreateSprite(Nirvana_Tileset_Cuts[Cut_Start_Index + 0].Image_ID, Nirvana_Tileset_Cuts[cut_index].NumCols * 32, Nirvana_Tileset_Cuts[cut_index].NumRows * 32)
	Push_N(Nirvana_Stage_Layers[4].Layer_TS_Stack, t_sprite)
	SetSpritePosition( t_sprite, 384, 256)

	cut_index = Cut_Start_Index + 0
	t_sprite = CreateSprite(Nirvana_Tileset_Cuts[Cut_Start_Index + 0].Image_ID, Nirvana_Tileset_Cuts[cut_index].NumCols * 32, Nirvana_Tileset_Cuts[cut_index].NumRows * 32)
	Push_N(Nirvana_Stage_Layers[4].Layer_TS_Stack, t_sprite)
	SetSpritePosition( t_sprite, 224, 32)


	Return nv_stage
End Function


Function Nirvana_Stage_1(vp_x, vp_y, vp_w, vp_h) As Nirvana_Stage
	Nirvana_ClearStage()

	Dim nv_stage As Nirvana_Stage
	nv_stage.Name$ = "st2"
	nv_stage.Tile_Size.Width = 32
	nv_stage.Tile_Size.Height = 32
	nv_stage.Stage_Size.Width = 100
	nv_stage.Stage_Size.Height = 100
	nv_stage.Layer_Count = 2

	'-------LAYER (background_layer)-------

	Nirvana_Stage_Layers[0].Name$ = "background_layer"
	Nirvana_Stage_Layers[0].LayerType = NIRVANA_LAYER_TYPE_CANVAS_2D
	Nirvana_Stage_Layers[0].Visible = TRUE
	Nirvana_Stage_Layers[0].Alpha = 255
	Nirvana_Stage_Layers[0].Scroll_Speed.X = 1
	Nirvana_Stage_Layers[0].Scroll_Speed.Y = 1
	Nirvana_Stage_Layers[0].Layer_TS_Stack = -1  ' This will be set to a stack if needed in sprite layer 

	Nirvana_Stage_Layers[0].Ref_Canvas = OpenCanvas(NIRVANA_WINDOW_WIDTH, NIRVANA_WINDOW_HEIGHT, vp_x, vp_y, vp_w, vp_h, 1)
	Nirvana_Stage_Layers[0].Bkg.Image_ID = LoadImage(NIRVANA_BKG_DIR$ + "bkg_city_ruin.png")
	Nirvana_Stage_Layers[0].Bkg.RenderSetting = NIRVANA_IMG_RENDER_SETTING_STRETCHED

	'-------LAYER (sp_layer)-------

	Nirvana_Stage_Layers[1].Name$ = "sp_layer"
	Nirvana_Stage_Layers[1].LayerType = NIRVANA_LAYER_TYPE_SPRITE
	Nirvana_Stage_Layers[1].Visible = TRUE
	Nirvana_Stage_Layers[1].Alpha = 255
	Nirvana_Stage_Layers[1].Scroll_Speed.X = 1
	Nirvana_Stage_Layers[1].Scroll_Speed.Y = 1
	Nirvana_Stage_Layers[1].Layer_TS_Stack = -1  ' This will be set to a stack if needed in sprite layer 

	Nirvana_Stage_Layers[1].Ref_Canvas = OpenCanvasSpriteLayer(vp_x, vp_y, vp_w, vp_h)
	SetSpriteCanvasRenderPriority(Nirvana_Stage_Layers[1].Ref_Canvas, SPRITE_PRIORITY_NONE, SPRITE_ORDER_ASCENDING)
	Canvas(Nirvana_Stage_Layers[1].Ref_Canvas)
	Nirvana_Stage_Layers[1].Layer_Sprite_Count = 1
	Nirvana_Stage_Layers[1].Layer_Shape_Count = 5

	'------- SPRITE ("stage2_guy") -------
	Nirvana_Stage_Sprites[0] = Nirvana_CreateSprite("gren_guy", "stage2_guy")

	'Base Settings
	SetSpriteType(Nirvana_Stage_Sprites[0].Sprite_ID, SPRITE_TYPE_DYNAMIC)
	SetSpriteAnimation(Nirvana_Stage_Sprites[0].Sprite_ID, 0, -1)

	'Shape
	SetSpriteShape(Nirvana_Stage_Sprites[0].Sprite_ID, SPRITE_SHAPE_POLYGON)
	Dim sprite_shape_x_0[6]
	Dim sprite_shape_y_0[6]

	sprite_shape_x_0[0] = 16
	sprite_shape_y_0[0] = 59

	sprite_shape_x_0[1] = 6
	sprite_shape_y_0[1] = 20

	sprite_shape_x_0[2] = 25
	sprite_shape_y_0[2] = 4

	sprite_shape_x_0[3] = 40
	sprite_shape_y_0[3] = 4

	sprite_shape_x_0[4] = 45
	sprite_shape_y_0[4] = 32

	sprite_shape_x_0[5] = 41
	sprite_shape_y_0[5] = 60

	SetSpritePolygon(Nirvana_Stage_Sprites[0].Sprite_ID, sprite_shape_x_0, sprite_shape_y_0, 6)

	'Transform
	SetSpritePosition(Nirvana_Stage_Sprites[0].Sprite_ID, 323, 181)
	SetSpriteScale(Nirvana_Stage_Sprites[0].Sprite_ID, 1, 1)
	SetSpriteRotation(Nirvana_Stage_Sprites[0].Sprite_ID, 0)

	'Render Settings
	SetSpriteAlpha(Nirvana_Stage_Sprites[0].Sprite_ID, 255)
	SetSpriteVisible(Nirvana_Stage_Sprites[0].Sprite_ID, TRUE)

	'------- SHAPE ("BOX_1") -------
	Nirvana_Stage_Shapes[0].Name$ = "BOX_1"
	Nirvana_Stage_Shapes[0].Sprite_ID = CreateSprite(-1, 1, 1)

	'Base Settings
	SetSpriteType(Nirvana_Stage_Shapes[0].Sprite_ID, SPRITE_TYPE_STATIC)
	SetSpriteSolid(Nirvana_Stage_Shapes[0].Sprite_ID, TRUE)
	'Shape
	Nirvana_Stage_Shapes[0].ShapeType = SPRITE_SHAPE_BOX
	SetSpriteShape(Nirvana_Stage_Shapes[0].Sprite_ID, Nirvana_Stage_Shapes[0].ShapeType)
	SetSpriteShapeOffset(Nirvana_Stage_Shapes[0].Sprite_ID, 326, 366)
	SetSpriteBox(Nirvana_Stage_Shapes[0].Sprite_ID, 233, 92)

	'Transform
	SetSpritePosition(Nirvana_Stage_Shapes[0].Sprite_ID,  0, 0) 'Set to (0,0) so that offset will be world position
	SetSpriteVisible(Nirvana_Stage_Shapes[0].Sprite_ID, FALSE) 'Image is -1 so it wouldn't render anyway

	'------- SHAPE ("BOX_2") -------
	Nirvana_Stage_Shapes[1].Name$ = "BOX_2"
	Nirvana_Stage_Shapes[1].Sprite_ID = CreateSprite(-1, 1, 1)

	'Base Settings
	SetSpriteType(Nirvana_Stage_Shapes[1].Sprite_ID, SPRITE_TYPE_STATIC)
	SetSpriteSolid(Nirvana_Stage_Shapes[1].Sprite_ID, TRUE)
	'Shape
	Nirvana_Stage_Shapes[1].ShapeType = SPRITE_SHAPE_BOX
	SetSpriteShape(Nirvana_Stage_Shapes[1].Sprite_ID, Nirvana_Stage_Shapes[1].ShapeType)
	SetSpriteShapeOffset(Nirvana_Stage_Shapes[1].Sprite_ID, 763, 356)
	SetSpriteBox(Nirvana_Stage_Shapes[1].Sprite_ID, 370, 118)

	'Transform
	SetSpritePosition(Nirvana_Stage_Shapes[1].Sprite_ID,  0, 0) 'Set to (0,0) so that offset will be world position
	SetSpriteVisible(Nirvana_Stage_Shapes[1].Sprite_ID, FALSE) 'Image is -1 so it wouldn't render anyway

	'------- SHAPE ("POLYGON_1") -------
	Nirvana_Stage_Shapes[2].Name$ = "POLYGON_1"
	Nirvana_Stage_Shapes[2].Sprite_ID = CreateSprite(-1, 1, 1)

	'Base Settings
	SetSpriteType(Nirvana_Stage_Shapes[2].Sprite_ID, SPRITE_TYPE_STATIC)
	SetSpriteSolid(Nirvana_Stage_Shapes[2].Sprite_ID, TRUE)
	'Shape
	Nirvana_Stage_Shapes[2].ShapeType = SPRITE_SHAPE_POLYGON
	SetSpriteShape(Nirvana_Stage_Shapes[2].Sprite_ID, Nirvana_Stage_Shapes[2].ShapeType)
	Dim stage_shape_x_2[4]
	Dim stage_shape_y_2[4]

	stage_shape_x_2[0] = 559
	stage_shape_y_2[0] = 460

	stage_shape_x_2[1] = 626
	stage_shape_y_2[1] = 533

	stage_shape_x_2[2] = 757
	stage_shape_y_2[2] = 533

	stage_shape_x_2[3] = 762
	stage_shape_y_2[3] = 476

	SetSpritePolygon(Nirvana_Stage_Shapes[2].Sprite_ID, stage_shape_x_2, stage_shape_y_2, 4)

	'Transform
	SetSpritePosition(Nirvana_Stage_Shapes[2].Sprite_ID,  0, 0) 'Set to (0,0) so that offset will be world position
	SetSpriteVisible(Nirvana_Stage_Shapes[2].Sprite_ID, FALSE) 'Image is -1 so it wouldn't render anyway

	'------- SHAPE ("CIRCLE_1") -------
	Nirvana_Stage_Shapes[3].Name$ = "CIRCLE_1"
	Nirvana_Stage_Shapes[3].Sprite_ID = CreateSprite(-1, 1, 1)

	'Base Settings
	SetSpriteType(Nirvana_Stage_Shapes[3].Sprite_ID, SPRITE_TYPE_STATIC)
	SetSpriteSolid(Nirvana_Stage_Shapes[3].Sprite_ID, TRUE)
	'Shape
	Nirvana_Stage_Shapes[3].ShapeType = SPRITE_SHAPE_CIRCLE
	SetSpriteShape(Nirvana_Stage_Shapes[3].Sprite_ID, Nirvana_Stage_Shapes[3].ShapeType)
	SetSpriteShapeOffset(Nirvana_Stage_Shapes[3].Sprite_ID, 656, 388)
	SetSpriteRadius(Nirvana_Stage_Shapes[3].Sprite_ID, 76)

	'Transform
	SetSpritePosition(Nirvana_Stage_Shapes[3].Sprite_ID,  0, 0) 'Set to (0,0) so that offset will be world position
	SetSpriteVisible(Nirvana_Stage_Shapes[3].Sprite_ID, FALSE) 'Image is -1 so it wouldn't render anyway

	'------- SHAPE ("CHAIN_1") -------
	Nirvana_Stage_Shapes[4].Name$ = "CHAIN_1"
	Nirvana_Stage_Shapes[4].Sprite_ID = CreateSprite(-1, 1, 1)

	'Base Settings
	SetSpriteType(Nirvana_Stage_Shapes[4].Sprite_ID, SPRITE_TYPE_STATIC)
	SetSpriteSolid(Nirvana_Stage_Shapes[4].Sprite_ID, TRUE)
	'Shape
	Nirvana_Stage_Shapes[4].ShapeType = SPRITE_SHAPE_CHAIN
	SetSpriteShape(Nirvana_Stage_Shapes[4].Sprite_ID, Nirvana_Stage_Shapes[4].ShapeType)
	Dim stage_shape_x_4[3]
	Dim stage_shape_y_4[3]

	stage_shape_x_4[0] = 655
	stage_shape_y_4[0] = 309

	stage_shape_x_4[1] = 988
	stage_shape_y_4[1] = 134

	stage_shape_x_4[2] = 1132
	stage_shape_y_4[2] = 356

	SetSpriteChain(Nirvana_Stage_Shapes[4].Sprite_ID, stage_shape_x_4, stage_shape_y_4, 3, 654, 308, 1133, 355)

	'Transform
	SetSpritePosition(Nirvana_Stage_Shapes[4].Sprite_ID,  0, 0) 'Set to (0,0) so that offset will be world position
	SetSpriteVisible(Nirvana_Stage_Shapes[4].Sprite_ID, FALSE) 'Image is -1 so it wouldn't render anyway

	'------- TILE SPRITES  -------

	Return nv_stage
End Function


Function Nirvana_Stage_2(vp_x, vp_y, vp_w, vp_h) As Nirvana_Stage
	Nirvana_ClearStage()

	Dim nv_stage As Nirvana_Stage
	nv_stage.Name$ = "st3"
	nv_stage.Tile_Size.Width = 64
	nv_stage.Tile_Size.Height = 32
	nv_stage.Stage_Size.Width = 100
	nv_stage.Stage_Size.Height = 100
	nv_stage.Layer_Count = 1

	'-------LAYER (fd)-------

	Nirvana_Stage_Layers[0].Name$ = "fd"
	Nirvana_Stage_Layers[0].LayerType = NIRVANA_LAYER_TYPE_ISO_TILEMAP
	Nirvana_Stage_Layers[0].Visible = TRUE
	Nirvana_Stage_Layers[0].Alpha = 255
	Nirvana_Stage_Layers[0].Scroll_Speed.X = 1
	Nirvana_Stage_Layers[0].Scroll_Speed.Y = 1
	Nirvana_Stage_Layers[0].Layer_TS_Stack = -1  ' This will be set to a stack if needed in sprite layer 

	Nirvana_Stage_Layers[0].Ref_Canvas = OpenCanvas(NIRVANA_WINDOW_WIDTH, NIRVANA_WINDOW_HEIGHT, vp_x, vp_y, vp_w, vp_h, 1)

	'------- ISO TILEMAP 1 -------
	Nirvana_Stage_Layers[0].Layer_TileMap = Nirvana_CreateTileMap("iso_test", 101, 101)

	f = OpenFile(NIRVANA_DATA_DIR$ + "tm2.data", BINARY_INPUT)
	For y = 0 To 100
		For x = 0 To 100
			SetTile(Nirvana_Stage_Layers[0].Layer_TileMap.TileMap_ID, Nirvana_Read32(f), x, y)
		Next
	Next
	CloseFile(f)
	'------- ISO TILEMAP 2 -------
	Nirvana_Stage_Layers[0].Layer_TileMap2 = Nirvana_CreateTileMap("iso_test", 101, 101)

	f = OpenFile(NIRVANA_DATA_DIR$ + "tm3.data", BINARY_INPUT)
	For y = 0 To 100
		For x = 0 To 100
			SetTile(Nirvana_Stage_Layers[0].Layer_TileMap2.TileMap_ID, Nirvana_Read32(f), x, y)
		Next
	Next
	CloseFile(f)

	Return nv_stage
End Function



Function Nirvana_LoadStage(stage_name$, viewport_x, viewport_y, viewport_w, viewport_h)
	GetWindowSize(NIRVANA_WINDOW_WIDTH, NIRVANA_WINDOW_HEIGHT)

	Select Case stage_name$

	Case "st1"
		Nirvana_ActiveStage = Nirvana_Stage_0(viewport_x, viewport_y, viewport_w, viewport_h)

	Case "st2"
		Nirvana_ActiveStage = Nirvana_Stage_1(viewport_x, viewport_y, viewport_w, viewport_h)

	Case "st3"
		Nirvana_ActiveStage = Nirvana_Stage_2(viewport_x, viewport_y, viewport_w, viewport_h)

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


