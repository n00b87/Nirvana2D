Include Once
Include "nirvana_constants.bas"
Include "nirvana_spriteDef.bas"
Include "nirvana_tileset.bas"
Include "nirvana_stage.bas"

Function Nirvana_CreateVector2D(x, y) As Nirvana_Vector2D
	Dim v As Nirvana_Vector2D
	v.x = x
	v.y = y
	Return v
End Function

Function Nirvana_CreateSize2D(w, h) As Nirvana_Size2D
	Dim v As Nirvana_Size2D
	v.Width = w
	v.Height = h
	Return v
End Function

'------LAYERS------
Function Nirvana_GetLayerIndex(layer_name$)
	For i = 0 To Nirvana_ActiveStage.Layer_Count-1
		If UCase$(Trim$(Nirvana_Stage_Layers[i].Name$)) = UCase$(Trim$(layer_name$)) Then
			Return i
		End If
	Next
	Return -1
End Function

Function Nirvana_GetLayerCanvasID(layer_index)
	If layer_index < 0 Or layer_index >= Nirvana_ActiveStage.Layer_Count Then
		Return -1
	End If
	Return Nirvana_Stage_Layers[layer_index].Ref_Canvas
End Function

Function Nirvana_GetLayerType(layer_index)
	If layer_index < 0 Or layer_index >= Nirvana_ActiveStage.Layer_Count Then
		Return -1
	End If
	Return Nirvana_Stage_Layers[layer_index].LayerType
End Function

Function Nirvana_GetLayerName$(layer_index)
	If layer_index < 0 Or layer_index >= Nirvana_ActiveStage.Layer_Count Then
		Return ""
	End If
	Return Nirvana_Stage_Layers[layer_index].Name$
End Function

Function Nirvana_GetLayerAlpha(layer_index)
	If layer_index < 0 Or layer_index >= Nirvana_ActiveStage.Layer_Count Then
		Return -1
	End If
	Return Nirvana_Stage_Layers[layer_index].Alpha
End Function

Function Nirvana_GetLayerScrollSpeed(layer_index) As Nirvana_Vector2D
	If layer_index < 0 Or layer_index >= Nirvana_ActiveStage.Layer_Count Then
		Return Nirvana_CreateVector2D(0, 0)
	End If
	Return Nirvana_Stage_Layers[layer_index].Scroll_Speed
End Function

Function Nirvana_GetLayerTileSetName$(layer_index)
	If layer_index < 0 Or layer_index >= Nirvana_ActiveStage.Layer_Count Then
		Return ""
	End If
	Return Nirvana_Stage_Layers[layer_index].Layer_TileMap.TilesetName$
End Function

Function Nirvana_GetLayerTileSetID(layer_index)
	If layer_index < 0 Or layer_index >= Nirvana_ActiveStage.Layer_Count Then
		Return -1
	End If
	Return Nirvana_Stage_Layers[layer_index].Layer_TileMap.Tileset_ID
End Function

Function Nirvana_GetLayerTileMapID(layer_index)
	If layer_index < 0 Or layer_index >= Nirvana_ActiveStage.Layer_Count Then
		Return -1
	End If
	Return Nirvana_Stage_Layers[layer_index].Layer_TileMap.TileMap_ID
End Function

Function Nirvana_GetLayerTileMaskCount(layer_index)
	If layer_index < 0 Or layer_index >= Nirvana_ActiveStage.Layer_Count Then
		Return -1
	End If
	Return Nirvana_Stage_Layers[layer_index].Layer_TileMap.Mask_Count
End Function

Function Nirvana_GetLayerTileMaskIndex(layer_index, mask_num)
	If layer_index < 0 Or layer_index >= Nirvana_ActiveStage.Layer_Count Then
		Return -1
	End If
	If mask_num < 0 Or mask_num >= Nirvana_Stage_Layers[layer_index].Layer_TileMap.Mask_Count Then
		Return -1
	End If
	Return (Nirvana_Stage_Layers[layer_index].Layer_TileMap.Mask_Index + mask_num)
End Function

Function Nirvana_GetLayerSpriteCount(layer_index)
	If layer_index < 0 Or layer_index >= Nirvana_ActiveStage.Layer_Count Then
		Return -1
	End If
	Return Nirvana_Stage_Layers[layer_index].Layer_Sprite_Count
End Function

Function Nirvana_GetLayerSpriteIndex(layer_index, sprite_name$)
	If layer_index < 0 Or layer_index >= Nirvana_ActiveStage.Layer_Count Then
		Return -1
	End If
	
	For i = 0 To Nirvana_Stage_Layers[layer_index].Layer_Sprite_Count-1
		If UCase$(Trim$(Nirvana_Stage_Sprites[i].Name$)) = UCase$(Trim$(sprite_name$)) Then
			Return i
		End If
	Next
	
	Return -1
End Function

Function Nirvana_GetLayerShapeCount(layer_index)
	If layer_index < 0 Or layer_index >= Nirvana_ActiveStage.Layer_Count Then
		Return -1
	End If
	Return Nirvana_Stage_Layers[layer_index].Layer_Shape_Count
End Function

Function Nirvana_GetLayerBackgroundImageID(layer_index)
	If layer_index < 0 Or layer_index >= Nirvana_ActiveStage.Layer_Count Then
		Return -1
	End If
	
	Return Nirvana_Stage_Layers[layer_index].Bkg.Image_ID
End Function

Function Nirvana_SetLayerBackgroundImage(layer_index, image_id)
	If layer_index < 0 Or layer_index >= Nirvana_ActiveStage.Layer_Count Then
		Return -1
	End If
	
	Nirvana_Stage_Layers[layer_index].Bkg.Image_ID = image_id
End Function

Function Nirvana_GetLayerBackgroundRenderType(layer_index)
	If layer_index < 0 Or layer_index >= Nirvana_ActiveStage.Layer_Count Then
		Return -1
	End If
	
	Return Nirvana_Stage_Layers[layer_index].Bkg.RenderSetting
End Function

Function Nirvana_SetLayerBackgroundRenderType(layer_index, render_type)
	If layer_index < 0 Or layer_index >= Nirvana_ActiveStage.Layer_Count Then
		Return -1
	End If
	
	Nirvana_Stage_Layers[layer_index].Bkg.RenderSetting = render_type
End Function


'-------TILE MASK----------
Function Nirvana_GetTileMaskName$(mask_index)
	If mask_index < 0 Or mask_index >= ArraySize(Nirvana_TileMask_Matrix_Name$, 1) Then
		Return ""
	End If
	Return Nirvana_TileMask_Matrix_Name$[mask_index]
End Function

Function Nirvana_GetTileMaskMatrix(mask_index)
	If mask_index < 0 Or mask_index >= ArraySize(Nirvana_TileMask_Matrix_Name$, 1) Then
		Return -1
	End If
	Return Nirvana_TileMask_Matrix[mask_index]
End Function

Function Nirvana_GetLayerMaskHit(layer_index, mask_index, x, y)
	If layer_index < 0 Or layer_index >= Nirvana_ActiveStage.Layer_Count Then
		Return -1
	End If
	If Not TileMapExists(Nirvana_Stage_Layers[layer_index].Layer_TileMap.TileMap_ID) Then
		Return False
	End If
	mask_start_index = Nirvana_Stage_Layers[layer_index].Layer_TileMap.Mask_Index
	mask_count = Nirvana_Stage_Layers[layer_index].Layer_TileMap.Mask_Count
	If mask_index < mask_start_index Or mask_index >= (mask_start_index+mask_count) Then
		Return False
	End If
	tile_x = Int(x / Nirvana_ActiveStage.Tile_Size.Width)
	tile_y = Int(y / Nirvana_ActiveStage.Tile_Size.Height)
	tile = GetTile(Nirvana_Stage_Layers[layer_index].Layer_TileMap.TileMap_ID, tile_x, tile_y)
	If tile < 0 Then
		Return False
	End If
	Return MatrixValue(Nirvana_TileMask_Matrix[mask_index], 0, tile)
End Function


'-------SPRITES-------
Function Nirvana_GetSpriteID(sprite_index)
	If sprite_index < 0 Or sprite_index >= ArraySize(Nirvana_Stage_Sprites, 1) Then
		Return -1
	End If
	Return Nirvana_Stage_Sprites[sprite_index].Sprite_ID
End Function

Function Nirvana_GetSpriteName$(sprite_index)
	If sprite_index < 0 Or sprite_index >= ArraySize(Nirvana_Stage_Sprites, 1) Then
		Return ""
	End If
	Return Nirvana_Stage_Sprites[sprite_index].Name$
End Function

Function Nirvana_GetSpriteDefinitionName$(sprite_index)
	If sprite_index < 0 Or sprite_index >= ArraySize(Nirvana_Stage_Sprites, 1) Then
		Return ""
	End If
	Return Nirvana_Stage_Sprites[sprite_index].BaseName$
End Function

Function Nirvana_GetSpriteAnimationCount(sprite_index)
	If sprite_index < 0 Or sprite_index >= ArraySize(Nirvana_Stage_Sprites, 1) Then
		Return 0
	End If
	Return Nirvana_Stage_Sprites[sprite_index].Animation_Count
End Function

Function Nirvana_GetSpriteAnimationName$(sprite_index, animation_num)
	If sprite_index < 0 Or sprite_index >= ArraySize(Nirvana_Stage_Sprites, 1) Then
		Return ""
	End If
	If animation_num < 0 Or animation_num >= Nirvana_Stage_Sprites[sprite_index].Animation_Count Then
		Return ""
	End If
	animation_index = Nirvana_Stage_Sprites[sprite_index].Animation_Name_Index + animation_num
	If animation_index < 0 Or animation_index >= ArraySize(Nirvana_SpriteAnimationNames$, 1) Then
		Return ""
	End If
	Return Nirvana_SpriteAnimationNames$[animation_index]
End Function

Function Nirvana_GetSpriteAnimationIndex(sprite_index, animation_name$)
	If sprite_index < 0 Or sprite_index >= ArraySize(Nirvana_Stage_Sprites, 1) Then
		Return -1
	End If
	For i = 0 To Nirvana_GetSpriteAnimationCount(sprite_index)-1
		If Nirvana_SpriteAnimationNames$[i] = animation_name$ Then
			Return i+1
		End If
	Next
	Return -1
End Function


'-------CAMERA-------
Sub Nirvana_SetStageOffset(offset As Nirvana_Vector2D)
	Nirvana_ActiveStage.Stage_Offset.X = offset.x
	Nirvana_ActiveStage.Stage_Offset.Y = offset.y
End Sub

Function Nirvana_GetStageOffset() As Nirvana_Vector2D
	Return Nirvana_ActiveStage.Stage_Offset
End Function


'-------VIEWPORT-------
Sub Nirvana_SetStageViewport(v_position As Nirvana_Vector2D, v_size As Nirvana_Size2D)
	Nirvana_ActiveStage.Viewport_Size = v_size
	For layer_index = 0 To Nirvana_ActiveStage.Layer_Count-1
		SetCanvasViewport(Nirvana_Stage_Layers[layer_index].Ref_Canvas, v_position.x, v_position.y, v_size.Width, v_size.Height)
	Next
End Sub

Function Nirvana_GetViewportPosition() As Nirvana_Vector2D
	Dim v_pos As Nirvana_Vector2D
	v_pos.X = 0
	v_pos.Y = 0
	If Nirvana_ActiveStage.Layer_Count > 0 Then
		Dim w, h
		GetCanvasViewport(Nirvana_Stage_Layers[0].Ref_Canvas, v_pos.X, v_pos.Y, w, h)
	End If
	Return v_pos
End Function

Function Nirvana_GetViewportSize() As Nirvana_Size2D
	Dim v_size As Nirvana_Size2D
	v_size.Width = 0
	v_size.Height = 0
	If Nirvana_ActiveStage.Layer_Count > 0 Then
		Dim x, y
		GetCanvasViewport(Nirvana_Stage_Layers[0].Ref_Canvas, x, y, v_size.Width, v_size.Height)
	End If
	Return v_size
End Function
