Include Once
Include "nirvana_constants.bas"
Include "nirvana_spriteDef.bas"
Include "nirvana_tileset.bas"
Include "nirvana_stage.bas"

Function Nirvana_GetLayerIndex(layer_name$)
	For i = 0 To Nirvana_ActiveStage.Layer_Count-1
		If Nirvana_Stage_Layers[i].Name$ = layer_name$ Then
			Return i
		End If
	Next
	Return -1
End Function

Function Nirvana_GetLayerCanvas(layer_index)
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


Function Nirvana_GetSpriteIndex(layer_index, sprite_name$)
	If layer_index < 0 Or layer_index >= Nirvana_ActiveStage.Layer_Count Then
		Return -1
	End If
	
	For i = 0 To Nirvana_Stage_Layers[layer_index].Layer_Sprite_Count-1
		If Nirvana_Stage_Sprites[i].Name$ = sprite_name$ Then
			Return i
		End If
	Next
	
	Return -1
End Function

Function Nirvana_GetSprite(sprite_index)
	If sprite_index < 0 Or sprite_index >= ArraySize(Nirvana_Stage_Sprites, 1) Then
		Return -1
	End If
	Return Nirvana_Stage_Sprites[sprite_index].Sprite_ID
End Function

Function Nirvana_GetBackgroundImage(layer_index)
	If layer_index < 0 Or layer_index >= Nirvana_ActiveStage.Layer_Count Then
		Return -1
	End If
	
	Return Nirvana_Stage_Layers[layer_index].Bkg.Image_ID
End Function

Function Nirvana_SetBackgroundImage(layer_index, image_id)
	If layer_index < 0 Or layer_index >= Nirvana_ActiveStage.Layer_Count Then
		Return -1
	End If
	
	Nirvana_Stage_Layers[layer_index].Bkg.Image_ID = image_id
End Function

Function Nirvana_GetBackgroundRenderType(layer_index)
	If layer_index < 0 Or layer_index >= Nirvana_ActiveStage.Layer_Count Then
		Return -1
	End If
	
	Return Nirvana_Stage_Layers[layer_index].Bkg.RenderSetting
End Function

Function Nirvana_SetBackgroundRenderType(layer_index, render_type)
	If layer_index < 0 Or layer_index >= Nirvana_ActiveStage.Layer_Count Then
		Return -1
	End If
	
	Nirvana_Stage_Layers[layer_index].Bkg.RenderSetting = render_type
End Function


Sub Nirvana_SetStageOffset(offset As Nirvana_Vector2D)
	Nirvana_ActiveStage.Stage_Offset.X = offset.x
	Nirvana_ActiveStage.Stage_Offset.Y = offset.y
End Sub

Function Nirvana_GetStageOffset() As Nirvana_Vector2D
	Return Nirvana_ActiveStage.Stage_Offset
End Function
