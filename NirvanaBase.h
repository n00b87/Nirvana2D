///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6-dirty)
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
#include <wx/bmpbuttn.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/treectrl.h>
#include <wx/statline.h>
#include <wx/checklst.h>
#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include <wx/aui/auibook.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibar.h>
#include <wx/listbox.h>
#include <wx/scrolwin.h>
#include <wx/splitter.h>
#include <wx/grid.h>
#include <wx/simplebook.h>
#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/frame.h>
#include <wx/dialog.h>
#include <wx/srchctrl.h>

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
		wxBitmapButton* m_bpButton20;
		wxStaticText* m_mapEdit_stageName_staticText;
		wxPanel* m_panel8;
		wxPanel* m_mapEdit_map_panel;
		wxPanel* m_panel2;
		wxSplitterWindow* m_splitter2;
		wxPanel* m_panel13;
		wxAuiNotebook* m_auinotebook5;
		wxPanel* m_panel39;
		wxBitmapButton* m_bpButton3;
		wxBitmapButton* m_bpButton4;
		wxBitmapButton* m_bpButton8;
		wxBitmapButton* m_bpButton9;
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
		wxStaticText* m_staticText48;
		wxTextCtrl* m_layerName_textCtrl;
		wxStaticText* m_staticText56;
		wxSpinCtrlDouble* m_mapEdit_layerHScroll_spinCtrlDouble;
		wxStaticText* m_staticText561;
		wxSpinCtrlDouble* m_mapEdit_layerVScroll_spinCtrlDouble;
		wxStaticText* m_staticText5611;
		wxSpinCtrl* m_mapEdit_layerAlpha_spinCtrl;
		wxPanel* m_panel14;
		wxAuiNotebook* m_mapEdit_layerObjectTools_auinotebook;
		wxPanel* m_mapEdit_tile_panel;
		wxAuiToolBar* m_auiToolBar3;
		wxAuiToolBarItem* m_tool18;
		wxAuiToolBarItem* m_tool19;
		wxAuiToolBarItem* m_tool20;
		wxAuiToolBarItem* m_tool21;
		wxAuiToolBarItem* m_tool22;
		wxAuiToolBarItem* m_tool23;
		wxPanel* m_mapEdit_tileSelect_panel;
		wxPanel* m_mapEdit_sprite_panel;
		wxAuiToolBar* m_auiToolBar1;
		wxAuiToolBarItem* m_tool4;
		wxAuiToolBarItem* m_tool5;
		wxAuiToolBarItem* m_tool6;
		wxAuiToolBarItem* m_tool7;
		wxAuiToolBarItem* m_tool8;
		wxAuiToolBarItem* m_tool1;
		wxAuiToolBarItem* m_tool2;
		wxAuiToolBarItem* m_tool3;
		wxListBox* m_mapEdit_layerSprite_listBox;
		wxPanel* m_mapEdit_sprite_preview_panel;
		wxScrolledWindow* m_scrolledWindow2;
		wxStaticText* m_staticText81;
		wxTextCtrl* m_textCtrl2;
		wxStaticText* m_staticText11;
		wxComboBox* m_comboBox31;
		wxStaticText* m_staticText7;
		wxComboBox* m_comboBox6;
		wxStaticText* m_staticText5;
		wxTextCtrl* m_textCtrl4;
		wxStaticText* m_staticText6;
		wxSpinCtrl* m_spinCtrl1;
		wxStaticText* m_staticText9;
		wxSpinCtrlDouble* m_spinCtrlDouble1;
		wxPanel* m_mapEdit_collision_panel;
		wxAuiToolBar* m_auiToolBar2;
		wxAuiToolBarItem* m_tool141;
		wxAuiToolBarItem* m_tool161;
		wxAuiToolBarItem* m_tool17;
		wxAuiToolBarItem* m_tool12;
		wxAuiToolBarItem* m_tool13;
		wxAuiToolBarItem* m_tool14;
		wxAuiToolBarItem* m_tool15;
		wxAuiToolBarItem* m_tool16;
		wxListBox* m_mapEdit_collisionShape_listBox;
		wxPanel* m_panel16;
		wxPanel* m_mapEdit_image_preview_panel;
		wxStaticText* m_staticText82;
		wxTextCtrl* m_textCtrl14;
		wxBitmapButton* m_bpButton202;
		wxStaticText* m_staticText562;
		wxComboBox* m_comboBox7;
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
		wxToolBarToolBase* m_tool33;
		wxToolBarToolBase* m_tool34;
		wxToolBarToolBase* m_tool35;

		// Virtual event handlers, override them in your derived class
		virtual void OnMainTabChanged( wxAuiNotebookEvent& event ) { event.Skip(); }
		virtual void OnActiveLayerSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEnterMapView( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnLeaveMapView( wxMouseEvent& event ) { event.Skip(); }
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
		virtual void OnMapEdit_LayerNameChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_LayerHScroll( wxSpinDoubleEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_LayerVScroll( wxSpinDoubleEvent& event ) { event.Skip(); }
		virtual void OnMapEdit_LayerAlpha( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnMapEditToolsTabChanged( wxAuiNotebookEvent& event ) { event.Skip(); }
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


	public:

		Nirvana_MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1280,720 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~Nirvana_MainFrame();

		void m_splitter1OnIdle( wxIdleEvent& )
		{
			m_splitter1->SetSashPosition( 646 );
			m_splitter1->Disconnect( wxEVT_IDLE, wxIdleEventHandler( Nirvana_MainFrame::m_splitter1OnIdle ), NULL, this );
		}

		void m_splitter2OnIdle( wxIdleEvent& )
		{
			m_splitter2->SetSashPosition( 152 );
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

		NewSprite_Dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("New Sprite"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 603,461 ), long style = wxDEFAULT_DIALOG_STYLE );

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

		NewTileset_Dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("New Tileset"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 603,461 ), long style = wxDEFAULT_DIALOG_STYLE );

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
		wxTextCtrl* m_textCtrl11;
		wxStaticText* m_staticText472;
		wxSpinCtrl* m_spinCtrl182;
		wxStaticText* m_staticText473;
		wxSpinCtrl* m_spinCtrl183;
		wxButton* m_button16;
		wxButton* m_button17;

	public:

		NewProject_Dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("New Project"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 514,216 ), long style = wxDEFAULT_DIALOG_STYLE );

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

		DeleteStage_Dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 341,187 ), long style = wxDEFAULT_DIALOG_STYLE );

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

