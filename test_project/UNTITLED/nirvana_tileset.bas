NIRVANA_TILE_DIR$ = NIRVANA_PROJECT_BASE_DIR$ + NIRVANA_PATH_SEPARATOR$ + "tiles" + NIRVANA_PATH_SEPARATOR$


Type Nirvana_TileMap
Dim TilesetName$
Dim Tileset_ID
Dim TileMap_ID
Dim Mask_Index
Dim Mask_Count
Dim Cut_Index
Dim Cut_Count
End Type

Type Nirvana_TilesetCut
Dim StartTile
Dim NumRows
Dim NumCols
Dim Image_ID
End Type

Dim Nirvana_Tileset_Image_Stack : Nirvana_Tileset_Image_Stack = CreateStack_N()

Dim Nirvana_Tileset_ID_0 : Nirvana_Tileset_ID_0 = -1
Dim Nirvana_Tileset_ID_1 : Nirvana_Tileset_ID_1 = -1
Dim Nirvana_Tileset_ID_2 : Nirvana_Tileset_ID_2 = -1

Dim Nirvana_Tileset_Image_0 : Nirvana_Tileset_Image_0 = -1
Dim Nirvana_Tileset_Image_1 : Nirvana_Tileset_Image_1 = -1
Dim Nirvana_Tileset_Image_2 : Nirvana_Tileset_Image_2 = -1

Dim Nirvana_TileMask_Matrix[3]
Dim Nirvana_TileMask_Matrix_Name$[3]

Nirvana_TileMask_Matrix_Name$[0] = "water_mask"
Nirvana_TileMask_Matrix_Name$[1] = "lava_mask"
Nirvana_TileMask_Matrix_Name$[2] = "white"


Dim Nirvana_Tileset_Cuts[6] As Nirvana_TilesetCut

Function Nirvana_MakeTileCut(tmp_canvas, tset_image, cut_index, tile_w, tile_h)
	If Not ImageExists(tset_image) Then
		Return -1
	End If

	If cut_index < 0 Or cut_index >= ArraySize(Nirvana_Tileset_Cuts, 1) Then
		Return -1
	End If

	current_canvas = ActiveCanvas()
	Canvas(tmp_canvas)
	ClearCanvas()

	Dim img_w, img_h
	GetImageSize(tset_image, img_w, img_h)
	widthInTiles = img_w / tile_w

	src_x = (Nirvana_Tileset_Cuts[cut_index].StartTile MOD widthInTiles) * tile_w
	src_y = (Nirvana_Tileset_Cuts[cut_index].StartTile  /  widthInTiles) * tile_h
	src_w = tile_w * Nirvana_Tileset_Cuts[cut_index].NumCols
	src_h = tile_h * Nirvana_Tileset_Cuts[cut_index].NumRows

	DrawImage_Blit(tset_image, 0, 0, src_x, src_y, src_w, src_h)

	Img_ID = CanvasClip(0, 0, src_w, src_h)

	Canvas(current_canvas)
	
	Print "Image: "; Img_ID

	Return Img_ID
End Function

Function Nirvana_Tileset_0()
	If Nirvana_Tileset_ID_0 >= 0 Then
		Return Nirvana_Tileset_ID_0
	End If

	TMP_CANVAS = OpenCanvas( 1024, 1024, 0, 0, 1024, 1024, 1)

	If Nirvana_Tileset_Image_0 < 0 Then
		If OS$ = "WINDOWS" Then
			Nirvana_Tileset_Image_0 = LoadImage(NIRVANA_TILE_DIR$ + "tiles2.png")
		Else
			Nirvana_Tileset_Image_0 = LoadImage(NIRVANA_TILE_DIR$ + "tiles2.png")
		End If

		If Nirvana_Tileset_Image_0 >= 0 Then
			Push_N(Nirvana_Tileset_Image_Stack, Nirvana_Tileset_Image_0)
		End If
	End If

	Nirvana_Tileset_ID_0 = CreateTileSet(Nirvana_Tileset_Image_0, 32, 32)

	'-------ANIMATIONS-------

	SetTileAnimationLength(Nirvana_Tileset_ID_0, 7, 2)
	SetTileAnimationSpeed(Nirvana_Tileset_ID_0, 7, 6)

	SetTileAnimationFrame(Nirvana_Tileset_ID_0, 7, 0, 7)
	SetTileAnimationFrame(Nirvana_Tileset_ID_0, 7, 1, 8)

	SetTileAnimationLength(Nirvana_Tileset_ID_0, 46, 2)
	SetTileAnimationSpeed(Nirvana_Tileset_ID_0, 46, 8)

	SetTileAnimationFrame(Nirvana_Tileset_ID_0, 46, 0, 46)
	SetTileAnimationFrame(Nirvana_Tileset_ID_0, 46, 1, 47)

	'-------MASK-------

	Nirvana_TileMask_Matrix[0] = DimMatrix(1, 112)
	FillMatrix(Nirvana_TileMask_Matrix[0], 0)
	SetMatrixValue(Nirvana_TileMask_Matrix[0], 0, 7, 1)
	SetMatrixValue(Nirvana_TileMask_Matrix[0], 0, 8, 1)
	SetMatrixValue(Nirvana_TileMask_Matrix[0], 0, 9, 1)

	Nirvana_TileMask_Matrix[1] = DimMatrix(1, 112)
	FillMatrix(Nirvana_TileMask_Matrix[1], 0)
	SetMatrixValue(Nirvana_TileMask_Matrix[1], 0, 46, 1)
	SetMatrixValue(Nirvana_TileMask_Matrix[1], 0, 47, 1)
	SetMatrixValue(Nirvana_TileMask_Matrix[1], 0, 48, 1)

	'-------CUTS-------

	Nirvana_Tileset_Cuts[0].StartTile = 18
	Nirvana_Tileset_Cuts[0].NumRows = 3
	Nirvana_Tileset_Cuts[0].NumCols = 3
	Nirvana_Tileset_Cuts[0].Image_ID = Nirvana_MakeTileCut(TMP_CANVAS, Nirvana_Tileset_Image_0, 0, 32, 32)

	Nirvana_Tileset_Cuts[1].StartTile = 18
	Nirvana_Tileset_Cuts[1].NumRows = 1
	Nirvana_Tileset_Cuts[1].NumCols = 5
	Nirvana_Tileset_Cuts[1].Image_ID = Nirvana_MakeTileCut(TMP_CANVAS, Nirvana_Tileset_Image_0, 1, 32, 32)

	Nirvana_Tileset_Cuts[2].StartTile = 44
	Nirvana_Tileset_Cuts[2].NumRows = 1
	Nirvana_Tileset_Cuts[2].NumCols = 1
	Nirvana_Tileset_Cuts[2].Image_ID = Nirvana_MakeTileCut(TMP_CANVAS, Nirvana_Tileset_Image_0, 2, 32, 32)

	Nirvana_Tileset_Cuts[3].StartTile = 39
	Nirvana_Tileset_Cuts[3].NumRows = 1
	Nirvana_Tileset_Cuts[3].NumCols = 1
	Nirvana_Tileset_Cuts[3].Image_ID = Nirvana_MakeTileCut(TMP_CANVAS, Nirvana_Tileset_Image_0, 3, 32, 32)

	CloseCanvas(TMP_CANVAS)
	Return Nirvana_Tileset_ID_0
End Function


Function Nirvana_Tileset_1()
	If Nirvana_Tileset_ID_1 >= 0 Then
		Return Nirvana_Tileset_ID_1
	End If

	TMP_CANVAS = OpenCanvas( 1024, 1024, 0, 0, 1024, 1024, 1)

	If Nirvana_Tileset_Image_1 < 0 Then
		If OS$ = "WINDOWS" Then
			Nirvana_Tileset_Image_1 = LoadImage(NIRVANA_TILE_DIR$ + "tilesheet.png")
		Else
			Nirvana_Tileset_Image_1 = LoadImage(NIRVANA_TILE_DIR$ + "tilesheet.png")
		End If

		If Nirvana_Tileset_Image_1 >= 0 Then
			Push_N(Nirvana_Tileset_Image_Stack, Nirvana_Tileset_Image_1)
		End If
	End If

	Nirvana_Tileset_ID_1 = CreateTileSet(Nirvana_Tileset_Image_1, 32, 32)

	'-------ANIMATIONS-------

	SetTileAnimationLength(Nirvana_Tileset_ID_1, 42, 4)
	SetTileAnimationSpeed(Nirvana_Tileset_ID_1, 42, 11)

	SetTileAnimationFrame(Nirvana_Tileset_ID_1, 42, 0, 42)
	SetTileAnimationFrame(Nirvana_Tileset_ID_1, 42, 1, 43)
	SetTileAnimationFrame(Nirvana_Tileset_ID_1, 42, 2, 44)
	SetTileAnimationFrame(Nirvana_Tileset_ID_1, 42, 3, 45)

	'-------MASK-------

	Nirvana_TileMask_Matrix[2] = DimMatrix(1, 64)
	FillMatrix(Nirvana_TileMask_Matrix[2], 0)
	SetMatrixValue(Nirvana_TileMask_Matrix[2], 0, 42, 1)
	SetMatrixValue(Nirvana_TileMask_Matrix[2], 0, 43, 1)
	SetMatrixValue(Nirvana_TileMask_Matrix[2], 0, 44, 1)
	SetMatrixValue(Nirvana_TileMask_Matrix[2], 0, 45, 1)

	'-------CUTS-------

	Nirvana_Tileset_Cuts[4].StartTile = 25
	Nirvana_Tileset_Cuts[4].NumRows = 1
	Nirvana_Tileset_Cuts[4].NumCols = 3
	Nirvana_Tileset_Cuts[4].Image_ID = Nirvana_MakeTileCut(TMP_CANVAS, Nirvana_Tileset_Image_1, 4, 32, 32)

	CloseCanvas(TMP_CANVAS)
	Return Nirvana_Tileset_ID_1
End Function


Function Nirvana_Tileset_2()
	If Nirvana_Tileset_ID_2 >= 0 Then
		Return Nirvana_Tileset_ID_2
	End If

	TMP_CANVAS = OpenCanvas( 1024, 1024, 0, 0, 1024, 1024, 1)

	If Nirvana_Tileset_Image_2 < 0 Then
		If OS$ = "WINDOWS" Then
			Nirvana_Tileset_Image_2 = LoadImage(NIRVANA_TILE_DIR$ + "brickpavers2-sheet.png")
		Else
			Nirvana_Tileset_Image_2 = LoadImage(NIRVANA_TILE_DIR$ + "brickpavers2-sheet.png")
		End If

		If Nirvana_Tileset_Image_2 >= 0 Then
			Push_N(Nirvana_Tileset_Image_Stack, Nirvana_Tileset_Image_2)
		End If
	End If

	Nirvana_Tileset_ID_2 = CreateTileSet(Nirvana_Tileset_Image_2, 64, 32)

	'-------ANIMATIONS-------

	'-------MASK-------

	'-------CUTS-------

	CloseCanvas(TMP_CANVAS)
	Return Nirvana_Tileset_ID_2
End Function




Function Nirvana_CreateTileMap(tset_name$, tmap_width, tmap_height) As Nirvana_TileMap
	Dim nv_tmap As Nirvana_TileMap
	nv_tmap.TilesetName$ = tset_name$

	Select Case tset_name$

	Case "tset1"
		nv_tmap.Tileset_ID = Nirvana_Tileset_0()
		nv_tmap.TileMap_ID = CreateTileMap(nv_tmap.Tileset_ID, tmap_width, tmap_height)
		nv_tmap.Mask_Index = 0
		nv_tmap.Mask_Count = 2

	Case "tset2"
		nv_tmap.Tileset_ID = Nirvana_Tileset_1()
		nv_tmap.TileMap_ID = CreateTileMap(nv_tmap.Tileset_ID, tmap_width, tmap_height)
		nv_tmap.Mask_Index = 2
		nv_tmap.Mask_Count = 1

	Case "iso_test"
		nv_tmap.Tileset_ID = Nirvana_Tileset_2()
		nv_tmap.TileMap_ID = CreateTileMap(nv_tmap.Tileset_ID, tmap_width, tmap_height)
		nv_tmap.Mask_Index = 3
		nv_tmap.Mask_Count = 0

	End Select

	Return nv_tmap
End Function
