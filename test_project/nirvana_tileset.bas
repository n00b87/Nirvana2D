NIRVANA_TILE_DIR$ = NIRVANA_PROJECT_BASE_DIR$ + NIRVANA_PATH_SEPARATOR$ + "tiles" + NIRVANA_PATH_SEPARATOR$


Type Nirvana_TileMap
Dim TilesetName$
Dim Tileset_ID
Dim TileMap_ID
Dim Mask_Index
Dim Mask_Count
End Type

Dim Nirvana_Tileset_Image_Stack : Nirvana_Tileset_Image_Stack = CreateStack_N()



Dim Nirvana_TileMask_Matrix[0]
Dim Nirvana_TileMask_Matrix_Name$[0]





Function Nirvana_CreateTileMap(tset_name$, tmap_width, tmap_height) As Nirvana_TileMap
	Dim nv_tmap As Nirvana_TileMap
	nv_tmap.TilesetName$ = tset_name$

	Select Case tset_name$

	End Select

	Return nv_tmap
End Function
