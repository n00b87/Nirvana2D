///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/combobox.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibar.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/statline.h>
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/treectrl.h>
#include <wx/checklst.h>
#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include <wx/checkbox.h>
#include <wx/clrpicker.h>
#include <wx/aui/auibook.h>
#include <wx/listbox.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/grid.h>
#include <wx/simplebook.h>
#include <wx/splitter.h>
#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/frame.h>
#include <wx/dialog.h>
#include <wx/srchctrl.h>
#include <wx/filepicker.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class Nirvana_MainFrame
///////////////////////////////////////////////////////////////////////////////
class Nirvana_MainFrame : public wxFrame
{
	private:

	protected:
		wxAuiNotebook* m_editorMainTab_auinotebook;
		wxPanel* m_mapEdit_panel;
		wxSplitterWindow* m_splitter1;
		wxPanel* m_panel1;
		wxPanel* m_panel7;
		wxStaticText* m_staticText53;
		wxComboBox* m_activeLayer_comboBox;
		wxAuiToolBar* m_auiToolBar6;
		wxAuiToolBarItem* m_camera_tool;
		wxAuiToolBar* m_mapSet_auiToolBar;
		wxAuiToolBarItem* m_mapSet_free_tool;
		wxAuiToolBarItem* m_mapSet_tile_tool;
		wxPanel* m_panel8;
		wxPanel* m_mapEdit_map_panel;
		wxPanel* m_panel48;
		wxPanel* m_panel50;
		wxStaticText* m_staticText641;
		wxStaticText* m_staticText651;
		wxStaticText* m_screenAbsoluteX_staticText;
		wxStaticText* m_staticText661;
		wxStaticText* m_screenAbsoluteY_staticText;
		wxPanel* m_panel49;
		wxStaticText* m_staticText64;
		wxStaticText* m_staticText65;
		wxStaticText* m_stageAbsoluteX_staticText;
		wxStaticText* m_staticText66;
		wxStaticText* m_stageAbsoluteY_staticText;
		wxStaticLine* m_staticline8;
		wxStaticText* m_staticText69;
		wxStaticText* m_stageTileX_staticText;
		wxStaticText* m_staticText71;
		wxStaticText* m_stageTileY_staticText;
		wxPanel* m_panel501;
		wxStaticText* m_staticText6411;
		wxStaticText* m_staticText6511;
		wxStaticText* m_cameraAbsoluteX_staticText;
		wxStaticText* m_staticText6611;
		wxStaticText* m_cameraAbsoluteY_staticText;
		wxStaticLine* m_staticline811;
		wxStaticText* m_staticText6911;
		wxStaticText* m_cameraTileX_staticText;
		wxStaticText* m_staticText7111;
		wxStaticText* m_cameraTileY_staticText;
		wxPanel* m_panel2;
		wxSplitterWindow* m_splitter2;
		wxPanel* m_panel13;
		wxAuiNotebook* m_projectManager_auinotebook;
		wxPanel* m_panel39;
		wxBitmapButton* m_bpButton3;
		wxBitmapButton* m_bpButton4;
		wxBitmapButton* m_bpButton8;
		wxBitmapButton* m_bpButton9;
		wxStaticText* m_mapEdit_stageName_staticText;
		wxTreeCtrl* m_project_treeCtrl;
		wxPanel* m_panel40;
		wxButton* m_button9;
		wxButton* m_button10;
		wxButton* m_button15;
		wxButton* m_button22;
		wxStaticLine* m_staticline14;
		wxBitmapButton* m_bpButton201;
		wxBitmapButton* m_bpButton21;
		wxBitmapButton* m_bpButton22;
		wxCheckListBox* m_layerVisible_checkList;
		wxStaticText* m_staticText99;
		wxStaticText* m_stageLayer_layerType_staticText;
		wxStaticText* m_staticText48;
		wxTextCtrl* m_layerName_textCtrl;
		wxStaticText* m_staticText56;
		wxSpinCtrlDouble* m_mapEdit_layerHScroll_spinCtrlDouble;
		wxStaticText* m_staticText561;
		wxSpinCtrlDouble* m_mapEdit_layerVScroll_spinCtrlDouble;
		wxStaticText* m_staticText5611;
		wxSpinCtrl* m_mapEdit_layerAlpha_spinCtrl;
		wxPanel* m_panel56;
		wxPanel* m_panel57;
		wxStaticText* m_staticText991;
		wxStaticText* m_staticText104;
		wxCheckBox* m_mapEdit_showShapes_checkBox;
		wxStaticText* m_staticText105;
		wxCheckBox* m_mapEdit_showGrid_checkBox;
		wxStaticText* m_staticText103;
		wxColourPickerCtrl* m_mapEdit_gridColor_colourPicker;
		wxPanel* m_panel58;
		wxStaticText* m_staticText101;
		wxStaticText* m_staticText102;
		wxSpinCtrl* m_mapEdit_cameraSpeed_spinCtrl;
		wxPanel* m_panel14;
		wxAuiNotebook* m_mapEdit_layerObjectTools_auinotebook;
		wxPanel* m_mapEdit_tile_panel;
		wxAuiToolBar* m_mapEdit_tileTools_auiToolBar;
		wxAuiToolBarItem* m_mapEdit_tileToolbar_select_tool;
		wxAuiToolBarItem* m_mapEdit_tileToolbar_boxSelect_tool;
		wxAuiToolBarItem* m_mapEdit_tileToolbar_move_tool;
		wxAuiToolBarItem* m_mapEdit_tileToolbar_setTile_tool;
		wxAuiToolBarItem* m_mapEdit_tileToolbar_copyTile_tool;
		wxAuiToolBarItem* m_mapEdit_tileToolbar_fillTile_tool;
		wxAuiToolBarItem* m_mapEdit_tileToolbar_deleteSelected_tool;
		wxPanel* m_mapEdit_tilesetInfo_panel;
		wxStaticText* m_staticText95;
		wxStaticText* m_mapEdit_layerTileset_staticText;
		wxStaticLine* m_staticline11;
		wxPanel* m_mapEdit_tileSelect_panel;
		wxPanel* m_mapEdit_sprite_panel;
		wxAuiToolBar* m_mapEdit_spriteTools_auiToolBar;
		wxAuiToolBarItem* m_mapEdit_spriteToolbar_select_tool;
		wxAuiToolBarItem* m_mapEdit_spriteToolbar_boxSelect_tool;
		wxAuiToolBarItem* m_mapEdit_spriteToolbar_move_tool;
		wxAuiToolBarItem* m_mapEdit_spriteToolbar_rotate_tool;
		wxAuiToolBarItem* m_mapEdit_spriteToolbar_scale_tool;
		wxAuiToolBarItem* m_mapEdit_spriteToolbar_addSprite_tool;
		wxAuiToolBarItem* m_mapEdit_spriteToolbar_deleteSprite_tool;
		wxAuiToolBarItem* m_mapEdit_spriteToolbar_copySprite_tool;
		wxAuiToolBarItem* m_mapEdit_spriteToolbar_centerOnSprite_tool;
		wxListBox* m_mapEdit_layerSprite_listBox;
		wxPropertyGrid* m_mapEdit_sprite_propertyGrid;
		wxPGProperty* m_propertyGridItem12;
		wxPGProperty* m_propertyGridItem1;
		wxPGProperty* m_propertyGridItem2;
		wxPGProperty* m_propertyGridItem3;
		wxPGProperty* m_propertyGridItem4;
		wxPGProperty* m_propertyGridItem5;
		wxPGProperty* m_propertyGridItem6;
		wxPGProperty* m_propertyGridItem7;
		wxPGProperty* m_propertyGridItem8;
		wxPGProperty* m_propertyGridItem9;
		wxPGProperty* m_propertyGridItem10;
		wxPGProperty* m_propertyGridItem11;
		wxPGProperty* m_propertyGridItem13;
		wxPGProperty* m_propertyGridItem14;
		wxPGProperty* m_propertyGridItem15;
		wxPanel* m_mapEdit_collision_panel;
		wxAuiToolBar* m_mapEdit_shapeTools_auiToolBar;
		wxAuiToolBarItem* m_mapEdit_shapeToolbar_select_tool;
		wxAuiToolBarItem* m_mapEdit_shapeToolbar_boxSelect_tool;
		wxAuiToolBarItem* m_mapEdit_shapeToolbar_move_tool;
		wxAuiToolBarItem* m_mapEdit_shapeToolbar_draw_tool;
		wxAuiToolBarItem* m_mapEdit_shapeToolbar_newBox_tool;
		wxAuiToolBarItem* m_mapEdit_shapeToolbar_newPolygon_tool;
		wxAuiToolBarItem* m_mapEdit_shapeToolbar_newChain_tool;
		wxAuiToolBarItem* m_mapEdit_shapeToolbar_newCircle_tool;
		wxAuiToolBarItem* m_mapEdit_shapeToolbar_deleteShape_tool;
		wxListBox* m_mapEdit_collisionShape_listBox;
		wxStaticText* m_staticText86;
		wxTextCtrl* m_mapEdit_shapeName_textCtrl;
		wxStaticLine* m_staticline10;
		wxSimplebook* m_mapEdit_shapeEdit_simplebook;
		wxPanel* m_mapEdit_noShape_panel;
		wxPanel* m_mapEdit_boxShape_panel;
		wxStaticText* m_staticText87;
		wxSpinCtrl* m_mapEdit_boxShape_posX_spinCtrl;
		wxStaticText* m_staticText871;
		wxSpinCtrl* m_mapEdit_boxShape_posY_spinCtrl;
		wxStaticText* m_staticText872;
		wxSpinCtrl* m_mapEdit_boxShape_width_spinCtrl;
		wxStaticText* m_staticText861;
		wxSpinCtrl* m_mapEdit_boxShape_height_spinCtrl;
		wxPanel* m_mapEdit_polyShape_panel;
		wxGrid* m_mapEdit_polyShape_grid;
		wxPanel* m_mapEdit_circleShape_panel;
		wxStaticText* m_staticText873;
		wxSpinCtrl* m_mapEdit_circleShape_centerX_spinCtrl;
		wxStaticText* m_staticText8711;
		wxSpinCtrl* m_mapEdit_circleShape_centerY_spinCtrl;
		wxStaticText* m_staticText8721;
		wxSpinCtrl* m_mapEdit_circleShape_radius_spinCtrl;
		wxPanel* m_panel16;
		wxStaticText* m_staticText562;
		wxComboBox* m_mapEdit_canvasRenderSetting_comboBox;
		wxStaticText* m_staticText82;
		wxComboBox* m_mapEdit_canvasImage_comboBox;
		wxPanel* m_tileEdit_panel;
		wxSplitterWindow* m_splitter3;
		wxPanel* m_panel191;
		wxButton* m_newTileset_button;
		wxButton* m_button2;
		wxListBox* m_tileEdit_tileset_listBox;
		wxPanel* m_panel20;
		wxStaticText* m_staticText19;
		wxTextCtrl* m_tileEdit_tilesetID_textCtrl;
		wxStaticText* m_staticText55;
		wxStaticText* m_tileSize_staticText;
		wxAuiNotebook* m_tileEdit_tools_auinotebook;
		wxPanel* m_tileEdit_tileAnimation_panel;
		wxSplitterWindow* m_splitter6;
		wxPanel* m_tileEdit_tileAnimation_middle_panel;
		wxPanel* m_tileAnimation_tileSheet_panel;
		wxBitmapButton* m_bpButton81;
		wxPanel* m_tileAnimation_tileFrames_panel;
		wxBitmapButton* m_bpButton91;
		wxAuiToolBar* m_tileEdit_mode_auiToolBar;
		wxAuiToolBarItem* m_tileEdit_tileSelect_tool;
		wxAuiToolBarItem* m_tileEdit_tileAnimate_tool;
		wxStaticText* m_staticText4211;
		wxSpinCtrl* m_tileEdit_numFrames_spinCtrl;
		wxStaticText* m_staticText251;
		wxSpinCtrl* m_tileEdit_FPS_spinCtrl;
		wxPanel* m_tileEdit_tileAnimation_Right_panel;
		wxStaticText* m_staticText15;
		wxPanel* m_tileAnimation_preview_panel;
		wxBitmapButton* m_bpButton12;
		wxBitmapButton* m_bpButton13;
		wxPanel* m_tileEdit_tileMask_panel;
		wxButton* m_tileEdit_newMask_button;
		wxButton* m_tileEdit_deleteMask_button;
		wxListBox* m_tileEdit_mask_listBox;
		wxStaticText* m_staticText36;
		wxTextCtrl* m_tileEdit_maskID_textCtrl;
		wxStaticLine* m_staticline21;
		wxPanel* m_tileMask_tileSheet_panel;
		wxPanel* m_spriteEdit_panel;
		wxSplitterWindow* m_splitter4;
		wxPanel* m_panel25;
		wxButton* m_spriteEditor_newSprite_button;
		wxButton* m_spriteEditor_deleteSprite_button;
		wxListBox* m_spriteEdit_sprite_listBox;
		wxPanel* m_panel26;
		wxStaticText* m_staticText20;
		wxTextCtrl* m_spriteEdit_spriteID_textCtrl;
		wxStaticText* m_staticText21;
		wxStaticText* m_spriteEdit_frameSize_staticText;
		wxAuiNotebook* m_spriteEdit_tools_auinotebook;
		wxPanel* m_spriteEdit_spriteAnimation_panel;
		wxStaticText* m_staticText23;
		wxButton* m_spriteEdit_newAnimation_button;
		wxButton* m_spriteEdit_deleteAnimation_button;
		wxListBox* m_spriteEdit_animation_listBox;
		wxSplitterWindow* m_splitter5;
		wxPanel* m_panel42;
		wxStaticText* m_staticText43;
		wxTextCtrl* m_spriteEdit_animationID_textCtrl;
		wxStaticLine* m_staticline9;
		wxPanel* m_spriteAnimation_spriteSheet_panel;
		wxBitmapButton* m_spriteEdit_previousFrame_bpButton;
		wxPanel* m_spriteAnimation_frame_panel;
		wxBitmapButton* m_spriteEdit_nextFrame_bpButton;
		wxStaticText* m_staticText421;
		wxSpinCtrl* m_spriteEdit_numFrames_spinCtrl;
		wxStaticText* m_staticText25;
		wxSpinCtrl* m_spriteEdit_FPS_spinCtrl;
		wxPanel* m_panel43;
		wxPanel* m_spriteAnimation_preview_panel;
		wxBitmapButton* m_spriteEdit_play_bpButton;
		wxBitmapButton* m_spriteEdit_stop_bpButton;
		wxPanel* m_spriteEdit_spriteCollision_panel;
		wxPanel* m_spriteCollision_edit_panel;
		wxAuiToolBar* m_auiToolBar4;
		wxAuiToolBarItem* m_spriteEdit_collisionSelect_tool;
		wxAuiToolBarItem* m_spriteEdit_collisionBoxSelect_tool;
		wxAuiToolBarItem* m_spriteEdit_collisionMove_tool;
		wxAuiToolBarItem* m_spriteEdit_collisionDraw_tool;
		wxStaticText* m_staticText27;
		wxComboBox* m_spriteEdit_collisionShape_comboBox;
		wxStaticLine* m_staticline2;
		wxSimplebook* m_spriteCollision_shape_simplebook;
		wxPanel* m_spriteShape_rect_panel;
		wxStaticText* m_staticText29;
		wxSpinCtrl* m_spriteEdit_collisionBox_X_spinCtrl;
		wxStaticText* m_staticText30;
		wxSpinCtrl* m_spriteEdit_collisionBox_Y_spinCtrl;
		wxStaticText* m_staticText31;
		wxSpinCtrl* m_spriteEdit_collisionBox_Width_spinCtrl;
		wxStaticText* m_staticText32;
		wxSpinCtrl* m_spriteEdit_collisionBox_Height_spinCtrl;
		wxPanel* m_spriteShape_polygon_panel;
		wxGrid* m_spriteEdit_collisionPolygon_grid;
		wxPanel* m_spriteShape_circle_panel;
		wxStaticText* m_staticText291;
		wxSpinCtrl* m_spriteEdit_collisionCircle_X_spinCtrl;
		wxStaticText* m_staticText301;
		wxSpinCtrl* m_spriteEdit_collisionCircle_Y_spinCtrl;
		wxStaticText* m_staticText311;
		wxSpinCtrl* m_spriteEdit_collisionCircle_Radius_spinCtrl;
		wxMenuBar* m_menubar1;
		wxToolBar* m_toolBar1;
		wxToolBarToolBase* m_newProject_tool;
		wxToolBarToolBase* m_openProject_tool;
		wxToolBarToolBase* m_saveProject_tool;
		wxToolBarToolBase* m_generate_tool;

		// Virtual event handlers, override them in your derived class
		virtual void OnNirvanaClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnMainTabChanged( wxAuiNotebookEvent& event ) { event.Skip(); }
		virtual void OnActiveLayerSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLayerComboClose( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLayerComboOpen( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCameraToolClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapSetFree( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapSetTiled( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEnterMapView( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnLeaveMapView( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_Map_UpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnProjectPropertiesTabChanged( wxAuiNotebookEvent& event ) { event.Skip(); }
		virtual void OnNewStage( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteStage( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_StageSettingsClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_CopyStageClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnProjectItemActivated( wxTreeEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_NewLayerClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_CopyLayerClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_ShowAllLayersClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_HideAllLayersClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_LayerUpClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_LayerDownClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_LayerDeleteClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLayerCheckListSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLayerCheckList_Visible_Toggle( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_LayerNameChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_LayerHScroll( wxSpinDoubleEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_LayerVScroll( wxSpinDoubleEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_LayerAlpha( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnMapEditSettings_ShowShapes_Checked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEditSettings_ShowGrid_Checked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEditSettings_GridColor_Change( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnMapEditSettings_CameraSpeed_SpinCtrl( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnMapEditToolsTabChanged( wxAuiNotebookEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_TileTool_Select( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_TileTool_BoxSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_TileTool_Move( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_TileTool_SetTile( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_TileTool_CopyTile( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_TileTool_FillTile( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_TileTool_DeleteSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEnterMapEditTileSelect( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnLeaveMapEditTileSelect( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnUpdateMapEditTileSelect( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_SpriteTool_Select( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_SpriteTool_BoxSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_SpriteTool_Move( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_SpriteTool_Rotate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_SpriteTool_Scale( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_SpriteTool_AddSprite( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_SpriteTool_DeleteSprite( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_SpriteTool_CopySprite( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_SpriteTool_CenterOnSprite( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_SpriteListSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_SpritePropertyGridChanged( wxPropertyGridEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_ShapeTool_Select( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_ShapeTool_BoxSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_ShapeTool_Move( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_ShapeTool_Draw( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_ShapeTool_NewBoxShape( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_ShapeTool_NewPolygonShape( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_ShapeTool_NewChainShape( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_ShapeTool_NewCircleShape( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_ShapeTool_DeleteShape( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_shapeListSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_ShapeName( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_BoxShape_PosX( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_BoxShape_PosY( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_BoxShape_Width( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_BoxShape_Height( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_PolyShape_CellChange( wxGridEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_CircleShape_CenterX( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_CircleShape_CenterY( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_CircleShape_Radius( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnBkg_RenderType( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBkg_LayerImage( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNewTilesetClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteTilesetClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTileEdit_TilesetSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTileEdit_TileIDChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTileEditor_Edit_Changed( wxAuiNotebookEvent& event ) { event.Skip(); }
		virtual void OnUpdateTileAnimationUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnEnterTileAnimationSheet( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnLeaveTileAnimationSheet( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnTileEdit_PreviousFrame_Click( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTileEdit_NextFrame_Click( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTileEdit_TileSelect_Tool( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTileEdit_TileAnimation_Tool( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTileEdit_NumFramesChange( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnTileEdit_FPSChanged( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnTileEdit_PlayPreviewClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTileEdit_StopPreviewClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateTileMaskUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnTileEdit_newMaskClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTileEdit_deleteMaskClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTileEdit_maskSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTileEdit_maskIDChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEnterTileMaskSheet( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnLeaveTileMaskSheet( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnNewSpriteClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteSpriteClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSpriteEdit_Sprite_Selected( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSpriteEdit_SpriteIDChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSpriteEditor_Edit_Changed( wxAuiNotebookEvent& event ) { event.Skip(); }
		virtual void OnUpdateSpriteAnimationUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnSpriteEdit_NewAnimation_Click( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSpriteEdit_DeleteAnimation_Click( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSpriteEdit_Animation_Selected( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSpriteEdit_AnimationIDChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEnterSpriteAnimationSheet( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnLeaveSpriteAnimationSheet( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnSpriteAnimationSheetSize( wxSizeEvent& event ) { event.Skip(); }
		virtual void OnSpriteEdit_PreviousFrame_Click( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSpriteEdit_NextFrame_Click( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSpriteEdit_NumFramesChange( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnSpriteEdit_FPSChanged( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnSpriteEdit_PlayPreviewClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSpriteEdit_StopPreviewClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSpriteEdit_Collision_Select_Click( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSpriteEdit_Collision_BoxSelect_Click( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSpriteEdit_Collision_Move_Click( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSpriteEdit_Collision_Draw_Click( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSpriteEdit_ShapeSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSpriteEdit_collisionBox_X_spinCtrl( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnSpriteEdit_collisionBox_Y_spinCtrl( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnSpriteEdit_collisionBox_Width_spinCtrl( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnSpriteEdit_collisionBox_Height_spinCtrl( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnSpriteEdit_collisionPolygon_gridCellChange( wxGridEvent& event ) { event.Skip(); }
		virtual void OnSpriteEdit_collisionCircle_X_spinCtrl( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnSpriteEdit_collisionCircle_Y_spinCtrl( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnSpriteEdit_collisionCircle_Radius_spinCtrl( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnNewProject( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOpenProject( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSaveProject( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGenerate( wxCommandEvent& event ) { event.Skip(); }


	public:

		Nirvana_MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Nirvana2D"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1280,720 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~Nirvana_MainFrame();

		void m_splitter1OnIdle( wxIdleEvent& )
		{
			m_splitter1->SetSashPosition( 719 );
			m_splitter1->Disconnect( wxEVT_IDLE, wxIdleEventHandler( Nirvana_MainFrame::m_splitter1OnIdle ), NULL, this );
		}

		void m_splitter2OnIdle( wxIdleEvent& )
		{
			m_splitter2->SetSashPosition( 250 );
			m_splitter2->Disconnect( wxEVT_IDLE, wxIdleEventHandler( Nirvana_MainFrame::m_splitter2OnIdle ), NULL, this );
		}

		void m_splitter3OnIdle( wxIdleEvent& )
		{
			m_splitter3->SetSashPosition( 251 );
			m_splitter3->Disconnect( wxEVT_IDLE, wxIdleEventHandler( Nirvana_MainFrame::m_splitter3OnIdle ), NULL, this );
		}

		void m_splitter6OnIdle( wxIdleEvent& )
		{
			m_splitter6->SetSashPosition( -100 );
			m_splitter6->Disconnect( wxEVT_IDLE, wxIdleEventHandler( Nirvana_MainFrame::m_splitter6OnIdle ), NULL, this );
		}

		void m_splitter4OnIdle( wxIdleEvent& )
		{
			m_splitter4->SetSashPosition( 254 );
			m_splitter4->Disconnect( wxEVT_IDLE, wxIdleEventHandler( Nirvana_MainFrame::m_splitter4OnIdle ), NULL, this );
		}

		void m_splitter5OnIdle( wxIdleEvent& )
		{
			m_splitter5->SetSashPosition( -100 );
			m_splitter5->Disconnect( wxEVT_IDLE, wxIdleEventHandler( Nirvana_MainFrame::m_splitter5OnIdle ), NULL, this );
		}

};

///////////////////////////////////////////////////////////////////////////////
/// Class MyDialog1
///////////////////////////////////////////////////////////////////////////////
class MyDialog1 : public wxDialog
{
	private:

	protected:
		wxPanel* m_panel40;
		wxStaticText* m_staticText45;
		wxTextCtrl* m_textCtrl9;
		wxStaticLine* m_staticline5;
		wxBitmapButton* m_bpButton14;
		wxBitmapButton* m_bpButton15;
		wxStaticLine* m_staticline6;
		wxBitmapButton* m_bpButton16;
		wxStaticLine* m_staticline7;
		wxCheckListBox* m_checkList3;

	public:

		MyDialog1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 545,373 ), long style = wxDEFAULT_DIALOG_STYLE );

		~MyDialog1();

};

///////////////////////////////////////////////////////////////////////////////
/// Class NewSprite_Dialog
///////////////////////////////////////////////////////////////////////////////
class NewSprite_Dialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText39;
		wxTextCtrl* m_spriteID_textCtrl;
		wxStaticText* m_staticText41;
		wxSpinCtrl* m_frameWidth_spinCtrl;
		wxStaticText* m_staticText42;
		wxSpinCtrl* m_frameHeight_spinCtrl;
		wxStaticText* m_staticText40;
		wxSearchCtrl* m_spriteSheet_searchCtrl;
		wxListBox* m_spriteSheet_listBox;
		wxButton* m_newSprite_ok_button;
		wxButton* m_newSprite_cancel_button;

		// Virtual event handlers, override them in your derived class
		virtual void OnSearch( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCreate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }


	public:

		NewSprite_Dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Load Sprite"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 603,461 ), long style = wxDEFAULT_DIALOG_STYLE );

		~NewSprite_Dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class NewTileset_Dialog
///////////////////////////////////////////////////////////////////////////////
class NewTileset_Dialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText39;
		wxTextCtrl* m_tilesetID_textCtrl;
		wxStaticText* m_staticText41;
		wxSpinCtrl* m_tileWidth_spinCtrl;
		wxStaticText* m_staticText42;
		wxSpinCtrl* m_tileHeight_spinCtrl;
		wxStaticText* m_staticText40;
		wxSearchCtrl* m_tileSheet_searchCtrl;
		wxListBox* m_tileSheet_listBox;
		wxButton* m_newTileset_ok_button;
		wxButton* m_newTileset_cancel_button;

		// Virtual event handlers, override them in your derived class
		virtual void OnSearch( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCreate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }


	public:

		NewTileset_Dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Load Tileset"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 603,461 ), long style = wxDEFAULT_DIALOG_STYLE );

		~NewTileset_Dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class NewStage_Dialog
///////////////////////////////////////////////////////////////////////////////
class NewStage_Dialog : public wxDialog
{
	private:

	protected:
		wxPanel* m_panel45;
		wxStaticText* m_staticText46;
		wxTextCtrl* m_stageID_textCtrl;
		wxStaticText* m_staticText4721;
		wxSpinCtrl* m_tileWidth_spinCtrl;
		wxStaticText* m_staticText47211;
		wxSpinCtrl* m_tileHeight_spinCtrl;
		wxStaticText* m_staticText472;
		wxSpinCtrl* m_width_spinCtrl;
		wxStaticText* m_staticText473;
		wxSpinCtrl* m_height_spinCtrl;
		wxButton* m_button16;
		wxButton* m_button17;

		// Virtual event handlers, override them in your derived class
		virtual void OnCreate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }


	public:

		NewStage_Dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("New Stage"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 514,310 ), long style = wxDEFAULT_DIALOG_STYLE );

		~NewStage_Dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class NewProject_Dialog
///////////////////////////////////////////////////////////////////////////////
class NewProject_Dialog : public wxDialog
{
	private:

	protected:
		wxPanel* m_panel45;
		wxStaticText* m_staticText46;
		wxTextCtrl* m_projectName_textCtrl;
		wxStaticText* m_staticText98;
		wxDirPickerCtrl* m_projectLocation_dirPicker;
		wxButton* m_ok_button;
		wxButton* m_cancel_button;

		// Virtual event handlers, override them in your derived class
		virtual void OnCreate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }


	public:

		NewProject_Dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("New Project"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 514,181 ), long style = wxDEFAULT_DIALOG_STYLE );

		~NewProject_Dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class NewLayer_Dialog
///////////////////////////////////////////////////////////////////////////////
class NewLayer_Dialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText55;
		wxTextCtrl* m_layerName_textCtrl;
		wxStaticText* m_staticText54;
		wxComboBox* m_layerType_comboBox;
		wxSimplebook* m_layerType_simplebook;
		wxPanel* m_layerType_noTileset_panel;
		wxPanel* m_layerType_tileset_panel;
		wxStaticText* m_staticText551;
		wxSearchCtrl* m_tileset_searchCtrl;
		wxListBox* m_tileset_listBox;
		wxButton* m_button20;
		wxButton* m_button21;

		// Virtual event handlers, override them in your derived class
		virtual void OnLayerTypeSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSearch( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCreate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }


	public:

		NewLayer_Dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("New Layer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 554,377 ), long style = wxDEFAULT_DIALOG_STYLE );

		~NewLayer_Dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class DeleteStage_Dialog
///////////////////////////////////////////////////////////////////////////////
class DeleteStage_Dialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_msg_staticText;
		wxButton* m_button23;
		wxButton* m_button24;

		// Virtual event handlers, override them in your derived class
		virtual void OnDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }


	public:

		DeleteStage_Dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Delete Stage"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 341,187 ), long style = wxDEFAULT_DIALOG_STYLE );

		~DeleteStage_Dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class StageProperties_Dialog
///////////////////////////////////////////////////////////////////////////////
class StageProperties_Dialog : public wxDialog
{
	private:

	protected:
		wxPanel* m_panel45;
		wxStaticText* m_staticText46;
		wxTextCtrl* m_stageID_textCtrl;
		wxStaticText* m_staticText62;
		wxStaticText* m_tileWidth_staticText;
		wxStaticText* m_staticText621;
		wxStaticText* m_tileHeight_staticText;
		wxStaticText* m_staticText472;
		wxSpinCtrl* m_width_spinCtrl;
		wxStaticText* m_staticText473;
		wxSpinCtrl* m_height_spinCtrl;
		wxButton* m_button16;
		wxButton* m_button17;

		// Virtual event handlers, override them in your derived class
		virtual void OnCreate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }


	public:

		StageProperties_Dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Stage Properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 514,282 ), long style = wxDEFAULT_DIALOG_STYLE );

		~StageProperties_Dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class AddSpriteInstance_Dialog
///////////////////////////////////////////////////////////////////////////////
class AddSpriteInstance_Dialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText59;
		wxTextCtrl* m_spriteID_textCtrl;
		wxStaticText* m_staticText60;
		wxSearchCtrl* m_baseSprite_searchCtrl;
		wxListBox* m_baseSpriteList_listBox;
		wxButton* m_button27;
		wxButton* m_button28;

		// Virtual event handlers, override them in your derived class
		virtual void OnSearch( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCreate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }


	public:

		AddSpriteInstance_Dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Add Sprite"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 566,367 ), long style = wxDEFAULT_DIALOG_STYLE );

		~AddSpriteInstance_Dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class DeleteSprite_Dialog
///////////////////////////////////////////////////////////////////////////////
class DeleteSprite_Dialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText63;
		wxStaticText* m_msg_staticText;
		wxButton* m_button23;
		wxButton* m_button24;

		// Virtual event handlers, override them in your derived class
		virtual void OnDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }


	public:

		DeleteSprite_Dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Delete Sprite"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 341,187 ), long style = wxDEFAULT_DIALOG_STYLE );

		~DeleteSprite_Dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class SetCamera_Dialog
///////////////////////////////////////////////////////////////////////////////
class SetCamera_Dialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText94;
		wxTextCtrl* m_posX_textCtrl;
		wxStaticText* m_staticText97;
		wxTextCtrl* m_posY_textCtrl;
		wxButton* m_cancel_button;
		wxButton* m_set_button;

		// Virtual event handlers, override them in your derived class
		virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSet( wxCommandEvent& event ) { event.Skip(); }


	public:

		SetCamera_Dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Set Camera View"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 381,124 ), long style = wxDEFAULT_DIALOG_STYLE );

		~SetCamera_Dialog();

};

