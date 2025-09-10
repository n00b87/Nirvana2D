///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "NirvanaBase.h"

///////////////////////////////////////////////////////////////////////////

Nirvana_MainFrame::Nirvana_MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	m_editorMainTab_auinotebook = new wxAuiNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TAB_FIXED_WIDTH );
	m_mapEdit_panel = new wxPanel( m_editorMainTab_auinotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );

	m_splitter1 = new wxSplitterWindow( m_mapEdit_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter1->SetSashGravity( 0.9 );
	m_splitter1->Connect( wxEVT_IDLE, wxIdleEventHandler( Nirvana_MainFrame::m_splitter1OnIdle ), NULL, this );
	m_splitter1->SetMinimumPaneSize( 500 );

	m_panel1 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	m_panel7 = new wxPanel( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText53 = new wxStaticText( m_panel7, wxID_ANY, _("Layer:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText53->Wrap( -1 );
	bSizer5->Add( m_staticText53, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_activeLayer_comboBox = new wxComboBox( m_panel7, wxID_ANY, _("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer5->Add( m_activeLayer_comboBox, 1, wxALL, 5 );


	bSizer5->Add( 0, 0, 1, wxEXPAND, 5 );

	m_auiToolBar6 = new wxAuiToolBar( m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_HORZ_LAYOUT );
	m_camera_tool = m_auiToolBar6->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/camera.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_auiToolBar6->Realize();

	bSizer5->Add( m_auiToolBar6, 0, wxALL, 5 );


	bSizer5->Add( 0, 0, 1, wxEXPAND, 5 );

	m_mapSet_auiToolBar = new wxAuiToolBar( m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_HORZ_LAYOUT );
	m_mapSet_free_tool = m_mapSet_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/map_set_free.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_mapSet_tile_tool = m_mapSet_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/map_set_tile.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_mapSet_auiToolBar->Realize();

	bSizer5->Add( m_mapSet_auiToolBar, 0, wxALL, 5 );


	m_panel7->SetSizer( bSizer5 );
	m_panel7->Layout();
	bSizer5->Fit( m_panel7 );
	bSizer4->Add( m_panel7, 0, wxEXPAND | wxALL, 5 );

	m_panel8 = new wxPanel( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	m_mapEdit_map_panel = new wxPanel( m_panel8, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL );
	bSizer6->Add( m_mapEdit_map_panel, 1, wxEXPAND | wxALL, 5 );

	m_panel48 = new wxPanel( m_panel8, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer141;
	bSizer141 = new wxBoxSizer( wxHORIZONTAL );

	m_panel50 = new wxPanel( m_panel48, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer1421;
	bSizer1421 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer1431;
	bSizer1431 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText641 = new wxStaticText( m_panel50, wxID_ANY, _("SCREEN MOUSE"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText641->Wrap( -1 );
	m_staticText641->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true, wxEmptyString ) );

	bSizer1431->Add( m_staticText641, 0, wxALL, 5 );


	bSizer1421->Add( bSizer1431, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer1441;
	bSizer1441 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText651 = new wxStaticText( m_panel50, wxID_ANY, _("Absolute X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText651->Wrap( -1 );
	bSizer1441->Add( m_staticText651, 0, wxALL, 5 );

	m_screenAbsoluteX_staticText = new wxStaticText( m_panel50, wxID_ANY, _("[NA]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_screenAbsoluteX_staticText->Wrap( -1 );
	bSizer1441->Add( m_screenAbsoluteX_staticText, 1, wxALL, 5 );


	bSizer1421->Add( bSizer1441, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer1451;
	bSizer1451 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText661 = new wxStaticText( m_panel50, wxID_ANY, _("Absolute Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText661->Wrap( -1 );
	bSizer1451->Add( m_staticText661, 0, wxALL, 5 );

	m_screenAbsoluteY_staticText = new wxStaticText( m_panel50, wxID_ANY, _("[NA]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_screenAbsoluteY_staticText->Wrap( -1 );
	bSizer1451->Add( m_screenAbsoluteY_staticText, 1, wxALL, 5 );


	bSizer1421->Add( bSizer1451, 0, wxEXPAND, 5 );


	m_panel50->SetSizer( bSizer1421 );
	m_panel50->Layout();
	bSizer1421->Fit( m_panel50 );
	bSizer141->Add( m_panel50, 1, wxEXPAND | wxALL, 5 );

	m_panel49 = new wxPanel( m_panel48, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer142;
	bSizer142 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer143;
	bSizer143 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText64 = new wxStaticText( m_panel49, wxID_ANY, _("STAGE MOUSE"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText64->Wrap( -1 );
	m_staticText64->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true, wxEmptyString ) );

	bSizer143->Add( m_staticText64, 0, wxALL, 5 );


	bSizer142->Add( bSizer143, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer144;
	bSizer144 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText65 = new wxStaticText( m_panel49, wxID_ANY, _("Absolute X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText65->Wrap( -1 );
	bSizer144->Add( m_staticText65, 0, wxALL, 5 );

	m_stageAbsoluteX_staticText = new wxStaticText( m_panel49, wxID_ANY, _("[NA]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stageAbsoluteX_staticText->Wrap( -1 );
	bSizer144->Add( m_stageAbsoluteX_staticText, 1, wxALL, 5 );


	bSizer142->Add( bSizer144, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer145;
	bSizer145 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText66 = new wxStaticText( m_panel49, wxID_ANY, _("Absolute Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText66->Wrap( -1 );
	bSizer145->Add( m_staticText66, 0, wxALL, 5 );

	m_stageAbsoluteY_staticText = new wxStaticText( m_panel49, wxID_ANY, _("[NA]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stageAbsoluteY_staticText->Wrap( -1 );
	bSizer145->Add( m_stageAbsoluteY_staticText, 1, wxALL, 5 );


	bSizer142->Add( bSizer145, 0, wxEXPAND, 5 );

	m_staticline8 = new wxStaticLine( m_panel49, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer142->Add( m_staticline8, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer146;
	bSizer146 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText69 = new wxStaticText( m_panel49, wxID_ANY, _("Tile X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText69->Wrap( -1 );
	bSizer146->Add( m_staticText69, 0, wxALL, 5 );

	m_stageTileX_staticText = new wxStaticText( m_panel49, wxID_ANY, _("[NA]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stageTileX_staticText->Wrap( -1 );
	bSizer146->Add( m_stageTileX_staticText, 1, wxALL, 5 );


	bSizer142->Add( bSizer146, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer147;
	bSizer147 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText71 = new wxStaticText( m_panel49, wxID_ANY, _("Tile Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText71->Wrap( -1 );
	bSizer147->Add( m_staticText71, 0, wxALL, 5 );

	m_stageTileY_staticText = new wxStaticText( m_panel49, wxID_ANY, _("[NA]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stageTileY_staticText->Wrap( -1 );
	bSizer147->Add( m_stageTileY_staticText, 1, wxALL, 5 );


	bSizer142->Add( bSizer147, 0, wxEXPAND, 5 );


	m_panel49->SetSizer( bSizer142 );
	m_panel49->Layout();
	bSizer142->Fit( m_panel49 );
	bSizer141->Add( m_panel49, 1, wxEXPAND | wxALL, 5 );

	m_panel501 = new wxPanel( m_panel48, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer14211;
	bSizer14211 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer14311;
	bSizer14311 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText6411 = new wxStaticText( m_panel501, wxID_ANY, _("CAMERA"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6411->Wrap( -1 );
	m_staticText6411->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true, wxEmptyString ) );

	bSizer14311->Add( m_staticText6411, 0, wxALL, 5 );


	bSizer14211->Add( bSizer14311, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer14411;
	bSizer14411 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText6511 = new wxStaticText( m_panel501, wxID_ANY, _("Absolute X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6511->Wrap( -1 );
	bSizer14411->Add( m_staticText6511, 0, wxALL, 5 );

	m_cameraAbsoluteX_staticText = new wxStaticText( m_panel501, wxID_ANY, _("[NA]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_cameraAbsoluteX_staticText->Wrap( -1 );
	bSizer14411->Add( m_cameraAbsoluteX_staticText, 1, wxALL, 5 );


	bSizer14211->Add( bSizer14411, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer14511;
	bSizer14511 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText6611 = new wxStaticText( m_panel501, wxID_ANY, _("Absolute Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6611->Wrap( -1 );
	bSizer14511->Add( m_staticText6611, 0, wxALL, 5 );

	m_cameraAbsoluteY_staticText = new wxStaticText( m_panel501, wxID_ANY, _("[NA]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_cameraAbsoluteY_staticText->Wrap( -1 );
	bSizer14511->Add( m_cameraAbsoluteY_staticText, 1, wxALL, 5 );


	bSizer14211->Add( bSizer14511, 0, wxEXPAND, 5 );

	m_staticline811 = new wxStaticLine( m_panel501, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer14211->Add( m_staticline811, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer14611;
	bSizer14611 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText6911 = new wxStaticText( m_panel501, wxID_ANY, _("Tile X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6911->Wrap( -1 );
	bSizer14611->Add( m_staticText6911, 0, wxALL, 5 );

	m_cameraTileX_staticText = new wxStaticText( m_panel501, wxID_ANY, _("[NA]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_cameraTileX_staticText->Wrap( -1 );
	bSizer14611->Add( m_cameraTileX_staticText, 1, wxALL, 5 );


	bSizer14211->Add( bSizer14611, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer14711;
	bSizer14711 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText7111 = new wxStaticText( m_panel501, wxID_ANY, _("Tile Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7111->Wrap( -1 );
	bSizer14711->Add( m_staticText7111, 0, wxALL, 5 );

	m_cameraTileY_staticText = new wxStaticText( m_panel501, wxID_ANY, _("[NA]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_cameraTileY_staticText->Wrap( -1 );
	bSizer14711->Add( m_cameraTileY_staticText, 1, wxALL, 5 );


	bSizer14211->Add( bSizer14711, 0, wxEXPAND, 5 );


	m_panel501->SetSizer( bSizer14211 );
	m_panel501->Layout();
	bSizer14211->Fit( m_panel501 );
	bSizer141->Add( m_panel501, 1, wxEXPAND | wxALL, 5 );


	m_panel48->SetSizer( bSizer141 );
	m_panel48->Layout();
	bSizer141->Fit( m_panel48 );
	bSizer6->Add( m_panel48, 0, wxEXPAND | wxALL, 5 );


	m_panel8->SetSizer( bSizer6 );
	m_panel8->Layout();
	bSizer6->Fit( m_panel8 );
	bSizer4->Add( m_panel8, 1, wxEXPAND | wxALL, 5 );


	m_panel1->SetSizer( bSizer4 );
	m_panel1->Layout();
	bSizer4->Fit( m_panel1 );
	m_panel2 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );

	m_splitter2 = new wxSplitterWindow( m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter2->SetSashGravity( 0.4 );
	m_splitter2->Connect( wxEVT_IDLE, wxIdleEventHandler( Nirvana_MainFrame::m_splitter2OnIdle ), NULL, this );
	m_splitter2->SetMinimumPaneSize( 150 );

	m_panel13 = new wxPanel( m_splitter2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );

	m_projectManager_auinotebook = new wxAuiNotebook( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TAB_FIXED_WIDTH );
	m_panel39 = new wxPanel( m_projectManager_auinotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer931;
	bSizer931 = new wxBoxSizer( wxHORIZONTAL );

	m_bpButton3 = new wxBitmapButton( m_panel39, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxBORDER_NONE );

	m_bpButton3->SetBitmap( wxBitmap( wxT("icons/plus_stage.png"), wxBITMAP_TYPE_ANY ) );
	bSizer931->Add( m_bpButton3, 0, wxALL, 5 );

	m_bpButton4 = new wxBitmapButton( m_panel39, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxBORDER_NONE );

	m_bpButton4->SetBitmap( wxBitmap( wxT("icons/remove_stage.png"), wxBITMAP_TYPE_ANY ) );
	bSizer931->Add( m_bpButton4, 0, wxALL, 5 );

	m_bpButton8 = new wxBitmapButton( m_panel39, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxBORDER_NONE );

	m_bpButton8->SetBitmap( wxBitmap( wxT("icons/write.png"), wxBITMAP_TYPE_ANY ) );
	bSizer931->Add( m_bpButton8, 0, wxALL, 5 );

	m_bpButton9 = new wxBitmapButton( m_panel39, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxBORDER_NONE );

	m_bpButton9->SetBitmap( wxBitmap( wxT("icons/copy.png"), wxBITMAP_TYPE_ANY ) );
	bSizer931->Add( m_bpButton9, 0, wxALL, 5 );


	bSizer931->Add( 0, 0, 1, wxEXPAND, 5 );

	m_mapEdit_stageName_staticText = new wxStaticText( m_panel39, wxID_ANY, _("STAGE: [NA]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_mapEdit_stageName_staticText->Wrap( -1 );
	bSizer931->Add( m_mapEdit_stageName_staticText, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer931->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer14->Add( bSizer931, 0, wxEXPAND, 5 );

	m_project_treeCtrl = new wxTreeCtrl( m_panel39, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxTR_HIDE_ROOT );
	bSizer14->Add( m_project_treeCtrl, 1, wxALL|wxEXPAND, 5 );


	m_panel39->SetSizer( bSizer14 );
	m_panel39->Layout();
	bSizer14->Fit( m_panel39 );
	m_projectManager_auinotebook->AddPage( m_panel39, _("Stages"), true, wxNullBitmap );
	m_panel40 = new wxPanel( m_projectManager_auinotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer871;
	bSizer871 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer911;
	bSizer911 = new wxBoxSizer( wxHORIZONTAL );

	m_button9 = new wxButton( m_panel40, wxID_ANY, _("New Layer"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer911->Add( m_button9, 1, wxALL, 5 );

	m_button10 = new wxButton( m_panel40, wxID_ANY, _("Copy Layer"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer911->Add( m_button10, 1, wxALL, 5 );

	m_button15 = new wxButton( m_panel40, wxID_ANY, _("Show All"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer911->Add( m_button15, 1, wxALL, 5 );

	m_button22 = new wxButton( m_panel40, wxID_ANY, _("Hide All"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer911->Add( m_button22, 1, wxALL, 5 );


	bSizer871->Add( bSizer911, 0, wxEXPAND, 5 );

	m_staticline14 = new wxStaticLine( m_panel40, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer871->Add( m_staticline14, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer124;
	bSizer124 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer127;
	bSizer127 = new wxBoxSizer( wxVERTICAL );

	m_bpButton201 = new wxBitmapButton( m_panel40, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );

	m_bpButton201->SetBitmap( wxBitmap( wxT("icons/up-arrow.png"), wxBITMAP_TYPE_ANY ) );
	bSizer127->Add( m_bpButton201, 0, wxALL|wxEXPAND, 5 );

	m_bpButton21 = new wxBitmapButton( m_panel40, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );

	m_bpButton21->SetBitmap( wxBitmap( wxT("icons/down-arrow.png"), wxBITMAP_TYPE_ANY ) );
	bSizer127->Add( m_bpButton21, 0, wxALL|wxEXPAND, 5 );

	m_bpButton22 = new wxBitmapButton( m_panel40, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );

	m_bpButton22->SetBitmap( wxBitmap( wxT("icons/delete.png"), wxBITMAP_TYPE_ANY ) );
	bSizer127->Add( m_bpButton22, 0, wxALL|wxEXPAND, 5 );


	bSizer124->Add( bSizer127, 0, wxEXPAND, 5 );

	wxArrayString m_layerVisible_checkListChoices;
	m_layerVisible_checkList = new wxCheckListBox( m_panel40, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_layerVisible_checkListChoices, 0 );
	bSizer124->Add( m_layerVisible_checkList, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer125;
	bSizer125 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer1761;
	bSizer1761 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText99 = new wxStaticText( m_panel40, wxID_ANY, _("Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText99->Wrap( -1 );
	bSizer1761->Add( m_staticText99, 1, wxALL, 5 );

	m_stageLayer_layerType_staticText = new wxStaticText( m_panel40, wxID_ANY, _("[NA]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stageLayer_layerType_staticText->Wrap( -1 );
	bSizer1761->Add( m_stageLayer_layerType_staticText, 3, wxALL, 5 );


	bSizer125->Add( bSizer1761, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer932;
	bSizer932 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer111;
	bSizer111 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText48 = new wxStaticText( m_panel40, wxID_ANY, _("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText48->Wrap( -1 );
	bSizer111->Add( m_staticText48, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_layerName_textCtrl = new wxTextCtrl( m_panel40, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer111->Add( m_layerName_textCtrl, 3, wxALL, 5 );


	bSizer932->Add( bSizer111, 0, wxEXPAND, 5 );


	bSizer125->Add( bSizer932, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer126;
	bSizer126 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText56 = new wxStaticText( m_panel40, wxID_ANY, _("H Scroll:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText56->Wrap( -1 );
	bSizer126->Add( m_staticText56, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_mapEdit_layerHScroll_spinCtrlDouble = new wxSpinCtrlDouble( m_panel40, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10000, 0, 0.1 );
	m_mapEdit_layerHScroll_spinCtrlDouble->SetDigits( 2 );
	bSizer126->Add( m_mapEdit_layerHScroll_spinCtrlDouble, 3, wxALL, 5 );


	bSizer125->Add( bSizer126, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer1261;
	bSizer1261 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText561 = new wxStaticText( m_panel40, wxID_ANY, _("V Scroll:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText561->Wrap( -1 );
	bSizer1261->Add( m_staticText561, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_mapEdit_layerVScroll_spinCtrlDouble = new wxSpinCtrlDouble( m_panel40, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10000, 0, 0.1 );
	m_mapEdit_layerVScroll_spinCtrlDouble->SetDigits( 2 );
	bSizer1261->Add( m_mapEdit_layerVScroll_spinCtrlDouble, 3, wxALL, 5 );


	bSizer125->Add( bSizer1261, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer12611;
	bSizer12611 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText5611 = new wxStaticText( m_panel40, wxID_ANY, _("Alpha:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5611->Wrap( -1 );
	bSizer12611->Add( m_staticText5611, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_mapEdit_layerAlpha_spinCtrl = new wxSpinCtrl( m_panel40, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0 );
	bSizer12611->Add( m_mapEdit_layerAlpha_spinCtrl, 3, wxALL, 5 );


	bSizer125->Add( bSizer12611, 0, wxEXPAND, 5 );


	bSizer124->Add( bSizer125, 1, wxEXPAND, 5 );


	bSizer871->Add( bSizer124, 1, wxEXPAND, 5 );


	m_panel40->SetSizer( bSizer871 );
	m_panel40->Layout();
	bSizer871->Fit( m_panel40 );
	m_projectManager_auinotebook->AddPage( m_panel40, _("Layers"), false, wxNullBitmap );
	m_panel56 = new wxPanel( m_projectManager_auinotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer1762;
	bSizer1762 = new wxBoxSizer( wxVERTICAL );

	m_panel57 = new wxPanel( m_panel56, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL );
	m_panel57->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_GRAYTEXT ) );

	wxBoxSizer* bSizer177;
	bSizer177 = new wxBoxSizer( wxVERTICAL );

	m_staticText991 = new wxStaticText( m_panel57, wxID_ANY, _("Viewport"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText991->Wrap( -1 );
	m_staticText991->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true, wxEmptyString ) );
	m_staticText991->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );

	bSizer177->Add( m_staticText991, 0, wxALL, 5 );

	wxBoxSizer* bSizer178;
	bSizer178 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText104 = new wxStaticText( m_panel57, wxID_ANY, _("Show Shapes"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText104->Wrap( -1 );
	m_staticText104->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );

	bSizer178->Add( m_staticText104, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_mapEdit_showShapes_checkBox = new wxCheckBox( m_panel57, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_mapEdit_showShapes_checkBox->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );

	bSizer178->Add( m_mapEdit_showShapes_checkBox, 2, wxALL, 5 );


	bSizer177->Add( bSizer178, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer180;
	bSizer180 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText105 = new wxStaticText( m_panel57, wxID_ANY, _("Show Grid"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText105->Wrap( -1 );
	m_staticText105->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );

	bSizer180->Add( m_staticText105, 1, wxALL, 5 );

	m_mapEdit_showGrid_checkBox = new wxCheckBox( m_panel57, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_mapEdit_showGrid_checkBox->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );

	bSizer180->Add( m_mapEdit_showGrid_checkBox, 2, wxALL, 5 );


	bSizer177->Add( bSizer180, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer183;
	bSizer183 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText103 = new wxStaticText( m_panel57, wxID_ANY, _("Grid Color"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText103->Wrap( -1 );
	m_staticText103->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );

	bSizer183->Add( m_staticText103, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_mapEdit_gridColor_colourPicker = new wxColourPickerCtrl( m_panel57, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	bSizer183->Add( m_mapEdit_gridColor_colourPicker, 2, wxALL, 5 );


	bSizer177->Add( bSizer183, 1, wxEXPAND, 5 );


	m_panel57->SetSizer( bSizer177 );
	m_panel57->Layout();
	bSizer177->Fit( m_panel57 );
	bSizer1762->Add( m_panel57, 0, wxEXPAND | wxALL, 5 );

	m_panel58 = new wxPanel( m_panel56, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL );
	m_panel58->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_GRAYTEXT ) );

	wxBoxSizer* bSizer181;
	bSizer181 = new wxBoxSizer( wxVERTICAL );

	m_staticText101 = new wxStaticText( m_panel58, wxID_ANY, _("Camera"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText101->Wrap( -1 );
	m_staticText101->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true, wxEmptyString ) );
	m_staticText101->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );

	bSizer181->Add( m_staticText101, 0, wxALL, 5 );

	wxBoxSizer* bSizer182;
	bSizer182 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText102 = new wxStaticText( m_panel58, wxID_ANY, _("Move Speed"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText102->Wrap( -1 );
	m_staticText102->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );

	bSizer182->Add( m_staticText102, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_mapEdit_cameraSpeed_spinCtrl = new wxSpinCtrl( m_panel58, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 1000, 1 );
	m_mapEdit_cameraSpeed_spinCtrl->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );

	bSizer182->Add( m_mapEdit_cameraSpeed_spinCtrl, 2, wxALL, 5 );


	bSizer181->Add( bSizer182, 0, wxEXPAND, 5 );


	m_panel58->SetSizer( bSizer181 );
	m_panel58->Layout();
	bSizer181->Fit( m_panel58 );
	bSizer1762->Add( m_panel58, 0, wxEXPAND | wxALL, 5 );


	m_panel56->SetSizer( bSizer1762 );
	m_panel56->Layout();
	bSizer1762->Fit( m_panel56 );
	m_projectManager_auinotebook->AddPage( m_panel56, _("Settings"), false, wxNullBitmap );

	bSizer13->Add( m_projectManager_auinotebook, 1, wxEXPAND | wxALL, 5 );


	m_panel13->SetSizer( bSizer13 );
	m_panel13->Layout();
	bSizer13->Fit( m_panel13 );
	m_panel14 = new wxPanel( m_splitter2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );

	m_mapEdit_layerObjectTools_auinotebook = new wxAuiNotebook( m_panel14, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TAB_FIXED_WIDTH );
	m_mapEdit_tile_panel = new wxPanel( m_mapEdit_layerObjectTools_auinotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer261;
	bSizer261 = new wxBoxSizer( wxHORIZONTAL );

	m_mapEdit_tileTools_auiToolBar = new wxAuiToolBar( m_mapEdit_tile_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_HORZ_LAYOUT );
	m_mapEdit_tileToolbar_select_tool = m_mapEdit_tileTools_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/cursor2.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_mapEdit_tileToolbar_boxSelect_tool = m_mapEdit_tileTools_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/box_select2.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_mapEdit_tileToolbar_move_tool = m_mapEdit_tileTools_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/move2.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_mapEdit_tileToolbar_setTile_tool = m_mapEdit_tileTools_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/place_tile.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_mapEdit_tileToolbar_copyTile_tool = m_mapEdit_tileTools_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/copy_tile.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_mapEdit_tileToolbar_fillTile_tool = m_mapEdit_tileTools_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/flood.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_mapEdit_tileTools_auiToolBar->AddSeparator();

	m_mapEdit_tileToolbar_deleteSelected_tool = m_mapEdit_tileTools_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/remove_tile.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_mapEdit_tileTools_auiToolBar->Realize();

	bSizer261->Add( m_mapEdit_tileTools_auiToolBar, 1, wxALL, 5 );


	bSizer16->Add( bSizer261, 0, wxEXPAND, 5 );

	m_mapEdit_tilesetInfo_panel = new wxPanel( m_mapEdit_tile_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer174;
	bSizer174 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText95 = new wxStaticText( m_mapEdit_tilesetInfo_panel, wxID_ANY, _("Tileset:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText95->Wrap( -1 );
	bSizer174->Add( m_staticText95, 0, wxALL, 5 );

	m_mapEdit_layerTileset_staticText = new wxStaticText( m_mapEdit_tilesetInfo_panel, wxID_ANY, _("[NA]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_mapEdit_layerTileset_staticText->Wrap( -1 );
	bSizer174->Add( m_mapEdit_layerTileset_staticText, 0, wxALL, 5 );


	m_mapEdit_tilesetInfo_panel->SetSizer( bSizer174 );
	m_mapEdit_tilesetInfo_panel->Layout();
	bSizer174->Fit( m_mapEdit_tilesetInfo_panel );
	bSizer16->Add( m_mapEdit_tilesetInfo_panel, 0, wxEXPAND | wxALL, 5 );

	m_staticline11 = new wxStaticLine( m_mapEdit_tile_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer16->Add( m_staticline11, 0, wxEXPAND | wxALL, 5 );

	m_mapEdit_tileSelect_panel = new wxPanel( m_mapEdit_tile_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL );
	bSizer16->Add( m_mapEdit_tileSelect_panel, 1, wxEXPAND | wxALL, 5 );


	m_mapEdit_tile_panel->SetSizer( bSizer16 );
	m_mapEdit_tile_panel->Layout();
	bSizer16->Fit( m_mapEdit_tile_panel );
	m_mapEdit_layerObjectTools_auinotebook->AddPage( m_mapEdit_tile_panel, _("Tiles"), true, wxNullBitmap );
	m_mapEdit_sprite_panel = new wxPanel( m_mapEdit_layerObjectTools_auinotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );

	m_mapEdit_spriteTools_auiToolBar = new wxAuiToolBar( m_mapEdit_sprite_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_HORZ_LAYOUT );
	m_mapEdit_spriteToolbar_select_tool = m_mapEdit_spriteTools_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/cursor2.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_mapEdit_spriteToolbar_boxSelect_tool = m_mapEdit_spriteTools_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/box_select2.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_mapEdit_spriteToolbar_move_tool = m_mapEdit_spriteTools_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/move2.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_mapEdit_spriteToolbar_rotate_tool = m_mapEdit_spriteTools_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/rotate2D_2.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_mapEdit_spriteToolbar_scale_tool = m_mapEdit_spriteTools_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/scale2.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_mapEdit_spriteTools_auiToolBar->AddSeparator();

	m_mapEdit_spriteToolbar_addSprite_tool = m_mapEdit_spriteTools_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/new_sprite.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_mapEdit_spriteToolbar_deleteSprite_tool = m_mapEdit_spriteTools_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/remove_sprite.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_mapEdit_spriteToolbar_copySprite_tool = m_mapEdit_spriteTools_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/copy_sprite.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_mapEdit_spriteToolbar_centerOnSprite_tool = m_mapEdit_spriteTools_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/nav.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_mapEdit_spriteTools_auiToolBar->Realize();

	bSizer19->Add( m_mapEdit_spriteTools_auiToolBar, 1, wxALL, 5 );


	bSizer18->Add( bSizer19, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxHORIZONTAL );

	m_mapEdit_layerSprite_listBox = new wxListBox( m_mapEdit_sprite_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer20->Add( m_mapEdit_layerSprite_listBox, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxVERTICAL );

	m_mapEdit_sprite_propertyGrid = new wxPropertyGrid(m_mapEdit_sprite_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxPG_DEFAULT_STYLE|wxPG_SPLITTER_AUTO_CENTER);
	m_propertyGridItem12 = m_mapEdit_sprite_propertyGrid->Append( new wxPropertyCategory( _("Sprite Properties") ) );
	m_propertyGridItem1 = m_mapEdit_sprite_propertyGrid->Append( new wxStringProperty( _("Sprite ID"), wxT("sprite_id") ) );
	m_propertyGridItem2 = m_mapEdit_sprite_propertyGrid->Append( new wxEnumProperty( _("Body Type"), wxT("body_type") ) );
	m_propertyGridItem3 = m_mapEdit_sprite_propertyGrid->Append( new wxEnumProperty( _("Animation"), wxT("animation") ) );
	m_propertyGridItem4 = m_mapEdit_sprite_propertyGrid->Append( new wxPropertyCategory( _("Position") ) );
	m_propertyGridItem5 = m_mapEdit_sprite_propertyGrid->Append( new wxIntProperty( _("X"), wxT("position_x") ) );
	m_propertyGridItem6 = m_mapEdit_sprite_propertyGrid->Append( new wxIntProperty( _("Y"), wxT("position_y") ) );
	m_propertyGridItem7 = m_mapEdit_sprite_propertyGrid->Append( new wxPropertyCategory( _("Rotation") ) );
	m_propertyGridItem8 = m_mapEdit_sprite_propertyGrid->Append( new wxFloatProperty( _("Angle"), wxT("angle") ) );
	m_propertyGridItem9 = m_mapEdit_sprite_propertyGrid->Append( new wxPropertyCategory( _("Scale") ) );
	m_propertyGridItem10 = m_mapEdit_sprite_propertyGrid->Append( new wxFloatProperty( _("X"), wxT("scale_x") ) );
	m_propertyGridItem11 = m_mapEdit_sprite_propertyGrid->Append( new wxFloatProperty( _("Y"), wxT("scale_y") ) );
	m_propertyGridItem13 = m_mapEdit_sprite_propertyGrid->Append( new wxPropertyCategory( _("Render Settings") ) );
	m_propertyGridItem14 = m_mapEdit_sprite_propertyGrid->Append( new wxUIntProperty( _("Alpha"), wxT("alpha") ) );
	m_propertyGridItem15 = m_mapEdit_sprite_propertyGrid->Append( new wxBoolProperty( _("Visible"), wxT("visible") ) );
	bSizer21->Add( m_mapEdit_sprite_propertyGrid, 1, wxALL|wxEXPAND, 1 );


	bSizer20->Add( bSizer21, 1, wxEXPAND, 5 );


	bSizer18->Add( bSizer20, 1, wxEXPAND, 5 );


	m_mapEdit_sprite_panel->SetSizer( bSizer18 );
	m_mapEdit_sprite_panel->Layout();
	bSizer18->Fit( m_mapEdit_sprite_panel );
	m_mapEdit_layerObjectTools_auinotebook->AddPage( m_mapEdit_sprite_panel, _("Sprites"), false, wxNullBitmap );
	m_mapEdit_collision_panel = new wxPanel( m_mapEdit_layerObjectTools_auinotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer241;
	bSizer241 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer251;
	bSizer251 = new wxBoxSizer( wxHORIZONTAL );

	m_mapEdit_shapeTools_auiToolBar = new wxAuiToolBar( m_mapEdit_collision_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_HORZ_LAYOUT );
	m_mapEdit_shapeToolbar_select_tool = m_mapEdit_shapeTools_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/cursor2.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_mapEdit_shapeToolbar_boxSelect_tool = m_mapEdit_shapeTools_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/box_select2.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_mapEdit_shapeToolbar_move_tool = m_mapEdit_shapeTools_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/move2.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_mapEdit_shapeToolbar_draw_tool = m_mapEdit_shapeTools_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/line.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_mapEdit_shapeTools_auiToolBar->AddSeparator();

	m_mapEdit_shapeToolbar_newBox_tool = m_mapEdit_shapeTools_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/box.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_mapEdit_shapeToolbar_newPolygon_tool = m_mapEdit_shapeTools_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/polygon.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_mapEdit_shapeToolbar_newChain_tool = m_mapEdit_shapeTools_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/chain.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_mapEdit_shapeToolbar_newCircle_tool = m_mapEdit_shapeTools_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/circle.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_mapEdit_shapeTools_auiToolBar->AddSeparator();

	m_mapEdit_shapeToolbar_deleteShape_tool = m_mapEdit_shapeTools_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/remove_shape.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_mapEdit_shapeTools_auiToolBar->Realize();

	bSizer251->Add( m_mapEdit_shapeTools_auiToolBar, 1, wxALL, 5 );


	bSizer241->Add( bSizer251, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer175;
	bSizer175 = new wxBoxSizer( wxHORIZONTAL );

	m_mapEdit_collisionShape_listBox = new wxListBox( m_mapEdit_collision_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer175->Add( m_mapEdit_collisionShape_listBox, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer176;
	bSizer176 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer162;
	bSizer162 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText86 = new wxStaticText( m_mapEdit_collision_panel, wxID_ANY, _("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText86->Wrap( -1 );
	bSizer162->Add( m_staticText86, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_mapEdit_shapeName_textCtrl = new wxTextCtrl( m_mapEdit_collision_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer162->Add( m_mapEdit_shapeName_textCtrl, 3, wxALL, 5 );


	bSizer176->Add( bSizer162, 0, wxEXPAND, 5 );

	m_staticline10 = new wxStaticLine( m_mapEdit_collision_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer176->Add( m_staticline10, 0, wxEXPAND | wxALL, 5 );

	m_mapEdit_shapeEdit_simplebook = new wxSimplebook( m_mapEdit_collision_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_mapEdit_noShape_panel = new wxPanel( m_mapEdit_shapeEdit_simplebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer1711;
	bSizer1711 = new wxBoxSizer( wxVERTICAL );


	m_mapEdit_noShape_panel->SetSizer( bSizer1711 );
	m_mapEdit_noShape_panel->Layout();
	bSizer1711->Fit( m_mapEdit_noShape_panel );
	m_mapEdit_shapeEdit_simplebook->AddPage( m_mapEdit_noShape_panel, _("a page"), false );
	m_mapEdit_boxShape_panel = new wxPanel( m_mapEdit_shapeEdit_simplebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer161;
	bSizer161 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer163;
	bSizer163 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText87 = new wxStaticText( m_mapEdit_boxShape_panel, wxID_ANY, _("Pos X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText87->Wrap( -1 );
	bSizer163->Add( m_staticText87, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_mapEdit_boxShape_posX_spinCtrl = new wxSpinCtrl( m_mapEdit_boxShape_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000000, 0 );
	bSizer163->Add( m_mapEdit_boxShape_posX_spinCtrl, 3, wxALL, 5 );


	bSizer161->Add( bSizer163, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer1631;
	bSizer1631 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText871 = new wxStaticText( m_mapEdit_boxShape_panel, wxID_ANY, _("Pos Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText871->Wrap( -1 );
	bSizer1631->Add( m_staticText871, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_mapEdit_boxShape_posY_spinCtrl = new wxSpinCtrl( m_mapEdit_boxShape_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000000, 0 );
	bSizer1631->Add( m_mapEdit_boxShape_posY_spinCtrl, 3, wxALL, 5 );


	bSizer161->Add( bSizer1631, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer1632;
	bSizer1632 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText872 = new wxStaticText( m_mapEdit_boxShape_panel, wxID_ANY, _("Width:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText872->Wrap( -1 );
	bSizer1632->Add( m_staticText872, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_mapEdit_boxShape_width_spinCtrl = new wxSpinCtrl( m_mapEdit_boxShape_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000000, 0 );
	bSizer1632->Add( m_mapEdit_boxShape_width_spinCtrl, 3, wxALL, 5 );


	bSizer161->Add( bSizer1632, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer1621;
	bSizer1621 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText861 = new wxStaticText( m_mapEdit_boxShape_panel, wxID_ANY, _("Height:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText861->Wrap( -1 );
	bSizer1621->Add( m_staticText861, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_mapEdit_boxShape_height_spinCtrl = new wxSpinCtrl( m_mapEdit_boxShape_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000000, 0 );
	bSizer1621->Add( m_mapEdit_boxShape_height_spinCtrl, 3, wxALL, 5 );


	bSizer161->Add( bSizer1621, 0, wxEXPAND, 5 );


	m_mapEdit_boxShape_panel->SetSizer( bSizer161 );
	m_mapEdit_boxShape_panel->Layout();
	bSizer161->Fit( m_mapEdit_boxShape_panel );
	m_mapEdit_shapeEdit_simplebook->AddPage( m_mapEdit_boxShape_panel, _("a page"), false );
	m_mapEdit_polyShape_panel = new wxPanel( m_mapEdit_shapeEdit_simplebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer171;
	bSizer171 = new wxBoxSizer( wxVERTICAL );

	m_mapEdit_polyShape_grid = new wxGrid( m_mapEdit_polyShape_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_mapEdit_polyShape_grid->CreateGrid( 5, 2 );
	m_mapEdit_polyShape_grid->EnableEditing( true );
	m_mapEdit_polyShape_grid->EnableGridLines( true );
	m_mapEdit_polyShape_grid->EnableDragGridSize( false );
	m_mapEdit_polyShape_grid->SetMargins( 0, 0 );

	// Columns
	m_mapEdit_polyShape_grid->SetColSize( 0, 80 );
	m_mapEdit_polyShape_grid->SetColSize( 1, 77 );
	m_mapEdit_polyShape_grid->EnableDragColMove( false );
	m_mapEdit_polyShape_grid->EnableDragColSize( true );
	m_mapEdit_polyShape_grid->SetColLabelValue( 0, _("X") );
	m_mapEdit_polyShape_grid->SetColLabelValue( 1, _("Y") );
	m_mapEdit_polyShape_grid->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_mapEdit_polyShape_grid->EnableDragRowSize( true );
	m_mapEdit_polyShape_grid->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	m_mapEdit_polyShape_grid->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer171->Add( m_mapEdit_polyShape_grid, 1, wxALL|wxEXPAND, 5 );


	m_mapEdit_polyShape_panel->SetSizer( bSizer171 );
	m_mapEdit_polyShape_panel->Layout();
	bSizer171->Fit( m_mapEdit_polyShape_panel );
	m_mapEdit_shapeEdit_simplebook->AddPage( m_mapEdit_polyShape_panel, _("a page"), false );
	m_mapEdit_circleShape_panel = new wxPanel( m_mapEdit_shapeEdit_simplebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer1611;
	bSizer1611 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer1633;
	bSizer1633 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText873 = new wxStaticText( m_mapEdit_circleShape_panel, wxID_ANY, _("Center X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText873->Wrap( -1 );
	bSizer1633->Add( m_staticText873, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_mapEdit_circleShape_centerX_spinCtrl = new wxSpinCtrl( m_mapEdit_circleShape_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000000, 0 );
	bSizer1633->Add( m_mapEdit_circleShape_centerX_spinCtrl, 3, wxALL, 5 );


	bSizer1611->Add( bSizer1633, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer16311;
	bSizer16311 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText8711 = new wxStaticText( m_mapEdit_circleShape_panel, wxID_ANY, _("Center Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8711->Wrap( -1 );
	bSizer16311->Add( m_staticText8711, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_mapEdit_circleShape_centerY_spinCtrl = new wxSpinCtrl( m_mapEdit_circleShape_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000000, 0 );
	bSizer16311->Add( m_mapEdit_circleShape_centerY_spinCtrl, 3, wxALL, 5 );


	bSizer1611->Add( bSizer16311, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer16321;
	bSizer16321 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText8721 = new wxStaticText( m_mapEdit_circleShape_panel, wxID_ANY, _("Radius:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8721->Wrap( -1 );
	bSizer16321->Add( m_staticText8721, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_mapEdit_circleShape_radius_spinCtrl = new wxSpinCtrl( m_mapEdit_circleShape_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000000, 0 );
	bSizer16321->Add( m_mapEdit_circleShape_radius_spinCtrl, 3, wxALL, 5 );


	bSizer1611->Add( bSizer16321, 0, wxEXPAND, 5 );


	m_mapEdit_circleShape_panel->SetSizer( bSizer1611 );
	m_mapEdit_circleShape_panel->Layout();
	bSizer1611->Fit( m_mapEdit_circleShape_panel );
	m_mapEdit_shapeEdit_simplebook->AddPage( m_mapEdit_circleShape_panel, _("a page"), false );

	bSizer176->Add( m_mapEdit_shapeEdit_simplebook, 1, wxEXPAND | wxALL, 5 );


	bSizer175->Add( bSizer176, 1, wxEXPAND, 5 );


	bSizer241->Add( bSizer175, 1, wxEXPAND, 5 );


	m_mapEdit_collision_panel->SetSizer( bSizer241 );
	m_mapEdit_collision_panel->Layout();
	bSizer241->Fit( m_mapEdit_collision_panel );
	m_mapEdit_layerObjectTools_auinotebook->AddPage( m_mapEdit_collision_panel, _("Collision"), false, wxNullBitmap );
	m_panel16 = new wxPanel( m_mapEdit_layerObjectTools_auinotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer1271;
	bSizer1271 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText562 = new wxStaticText( m_panel16, wxID_ANY, _("Render Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText562->Wrap( -1 );
	bSizer1271->Add( m_staticText562, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_mapEdit_canvasRenderSetting_comboBox = new wxComboBox( m_panel16, wxID_ANY, _("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer1271->Add( m_mapEdit_canvasRenderSetting_comboBox, 4, wxALL, 5 );


	bSizer30->Add( bSizer1271, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer32;
	bSizer32 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText82 = new wxStaticText( m_panel16, wxID_ANY, _("Layer Image:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText82->Wrap( -1 );
	bSizer32->Add( m_staticText82, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_mapEdit_canvasImage_comboBox = new wxComboBox( m_panel16, wxID_ANY, _("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer32->Add( m_mapEdit_canvasImage_comboBox, 4, wxALL, 5 );


	bSizer30->Add( bSizer32, 0, wxEXPAND, 5 );


	bSizer27->Add( bSizer30, 1, wxEXPAND, 5 );


	m_panel16->SetSizer( bSizer27 );
	m_panel16->Layout();
	bSizer27->Fit( m_panel16 );
	m_mapEdit_layerObjectTools_auinotebook->AddPage( m_panel16, _("Image"), false, wxNullBitmap );

	bSizer15->Add( m_mapEdit_layerObjectTools_auinotebook, 1, wxEXPAND | wxALL, 5 );


	m_panel14->SetSizer( bSizer15 );
	m_panel14->Layout();
	bSizer15->Fit( m_panel14 );
	m_splitter2->SplitHorizontally( m_panel13, m_panel14, 250 );
	bSizer7->Add( m_splitter2, 1, wxEXPAND, 5 );


	m_panel2->SetSizer( bSizer7 );
	m_panel2->Layout();
	bSizer7->Fit( m_panel2 );
	m_splitter1->SplitVertically( m_panel1, m_panel2, 593 );
	bSizer12->Add( m_splitter1, 1, wxEXPAND, 5 );


	bSizer3->Add( bSizer12, 1, wxEXPAND, 5 );


	m_mapEdit_panel->SetSizer( bSizer3 );
	m_mapEdit_panel->Layout();
	bSizer3->Fit( m_mapEdit_panel );
	m_editorMainTab_auinotebook->AddPage( m_mapEdit_panel, _("Map Editor"), true, wxNullBitmap );
	m_tileEdit_panel = new wxPanel( m_editorMainTab_auinotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer351;
	bSizer351 = new wxBoxSizer( wxVERTICAL );

	m_splitter3 = new wxSplitterWindow( m_tileEdit_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter3->Connect( wxEVT_IDLE, wxIdleEventHandler( Nirvana_MainFrame::m_splitter3OnIdle ), NULL, this );
	m_splitter3->SetMinimumPaneSize( 250 );

	m_panel191 = new wxPanel( m_splitter3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer38;
	bSizer38 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer39;
	bSizer39 = new wxBoxSizer( wxHORIZONTAL );

	m_newTileset_button = new wxButton( m_panel191, wxID_ANY, _("Load Tileset"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer39->Add( m_newTileset_button, 1, wxALL, 5 );

	m_button2 = new wxButton( m_panel191, wxID_ANY, _("Delete Tileset"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer39->Add( m_button2, 1, wxALL, 5 );


	bSizer38->Add( bSizer39, 0, wxEXPAND, 5 );

	m_tileEdit_tileset_listBox = new wxListBox( m_panel191, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer38->Add( m_tileEdit_tileset_listBox, 1, wxALL|wxEXPAND, 5 );


	m_panel191->SetSizer( bSizer38 );
	m_panel191->Layout();
	bSizer38->Fit( m_panel191 );
	m_panel20 = new wxPanel( m_splitter3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer93;
	bSizer93 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer56;
	bSizer56 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText19 = new wxStaticText( m_panel20, wxID_ANY, _("Tileset ID:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText19->Wrap( -1 );
	bSizer56->Add( m_staticText19, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_tileEdit_tilesetID_textCtrl = new wxTextCtrl( m_panel20, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	bSizer56->Add( m_tileEdit_tilesetID_textCtrl, 2, wxALL, 5 );


	bSizer56->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText55 = new wxStaticText( m_panel20, wxID_ANY, _("Tile Size:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText55->Wrap( -1 );
	bSizer56->Add( m_staticText55, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_tileSize_staticText = new wxStaticText( m_panel20, wxID_ANY, _("WIDTH x HEIGHT"), wxDefaultPosition, wxDefaultSize, 0 );
	m_tileSize_staticText->Wrap( -1 );
	bSizer56->Add( m_tileSize_staticText, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer56->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer93->Add( bSizer56, 0, wxEXPAND, 5 );

	m_tileEdit_tools_auinotebook = new wxAuiNotebook( m_panel20, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TAB_FIXED_WIDTH );
	m_tileEdit_tileAnimation_panel = new wxPanel( m_tileEdit_tools_auinotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer42;
	bSizer42 = new wxBoxSizer( wxHORIZONTAL );

	m_splitter6 = new wxSplitterWindow( m_tileEdit_tileAnimation_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter6->SetSashGravity( 0.8 );
	m_splitter6->Connect( wxEVT_IDLE, wxIdleEventHandler( Nirvana_MainFrame::m_splitter6OnIdle ), NULL, this );
	m_splitter6->SetMinimumPaneSize( 200 );

	m_tileEdit_tileAnimation_middle_panel = new wxPanel( m_splitter6, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer( wxVERTICAL );

	m_tileAnimation_tileSheet_panel = new wxPanel( m_tileEdit_tileAnimation_middle_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL );
	bSizer40->Add( m_tileAnimation_tileSheet_panel, 1, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer46;
	bSizer46 = new wxBoxSizer( wxHORIZONTAL );

	m_bpButton81 = new wxBitmapButton( m_tileEdit_tileAnimation_middle_panel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );

	m_bpButton81->SetBitmap( wxBitmap( wxT("icons/previous.png"), wxBITMAP_TYPE_ANY ) );
	bSizer46->Add( m_bpButton81, 0, wxALL, 5 );

	m_tileAnimation_tileFrames_panel = new wxPanel( m_tileEdit_tileAnimation_middle_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL );
	bSizer46->Add( m_tileAnimation_tileFrames_panel, 1, wxEXPAND | wxALL, 5 );

	m_bpButton91 = new wxBitmapButton( m_tileEdit_tileAnimation_middle_panel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );

	m_bpButton91->SetBitmap( wxBitmap( wxT("icons/next.png"), wxBITMAP_TYPE_ANY ) );
	bSizer46->Add( m_bpButton91, 0, wxALL, 5 );


	bSizer40->Add( bSizer46, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer702;
	bSizer702 = new wxBoxSizer( wxHORIZONTAL );

	m_tileEdit_mode_auiToolBar = new wxAuiToolBar( m_tileEdit_tileAnimation_middle_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_HORZ_LAYOUT );
	m_tileEdit_tileSelect_tool = m_tileEdit_mode_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/select_tile.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_tileEdit_tileAnimate_tool = m_tileEdit_mode_auiToolBar->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/tile_animation.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_tileEdit_mode_auiToolBar->Realize();

	bSizer702->Add( m_tileEdit_mode_auiToolBar, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer702->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer10011;
	bSizer10011 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText4211 = new wxStaticText( m_tileEdit_tileAnimation_middle_panel, wxID_ANY, _("Frames:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4211->Wrap( -1 );
	bSizer10011->Add( m_staticText4211, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_tileEdit_numFrames_spinCtrl = new wxSpinCtrl( m_tileEdit_tileAnimation_middle_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 10000, 1 );
	bSizer10011->Add( m_tileEdit_numFrames_spinCtrl, 0, wxALL|wxEXPAND, 5 );


	bSizer702->Add( bSizer10011, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer661;
	bSizer661 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText251 = new wxStaticText( m_tileEdit_tileAnimation_middle_panel, wxID_ANY, _("FPS:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText251->Wrap( -1 );
	bSizer661->Add( m_staticText251, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_tileEdit_FPS_spinCtrl = new wxSpinCtrl( m_tileEdit_tileAnimation_middle_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10000, 0 );
	bSizer661->Add( m_tileEdit_FPS_spinCtrl, 0, wxALL|wxEXPAND, 5 );


	bSizer702->Add( bSizer661, 0, wxEXPAND, 5 );


	bSizer702->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer40->Add( bSizer702, 0, wxEXPAND, 5 );


	m_tileEdit_tileAnimation_middle_panel->SetSizer( bSizer40 );
	m_tileEdit_tileAnimation_middle_panel->Layout();
	bSizer40->Fit( m_tileEdit_tileAnimation_middle_panel );
	m_tileEdit_tileAnimation_Right_panel = new wxPanel( m_splitter6, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer47;
	bSizer47 = new wxBoxSizer( wxVERTICAL );


	bSizer47->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText15 = new wxStaticText( m_tileEdit_tileAnimation_Right_panel, wxID_ANY, _("Preview"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	bSizer47->Add( m_staticText15, 0, wxALL, 5 );

	m_tileAnimation_preview_panel = new wxPanel( m_tileEdit_tileAnimation_Right_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL );
	bSizer47->Add( m_tileAnimation_preview_panel, 1, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer49;
	bSizer49 = new wxBoxSizer( wxHORIZONTAL );

	m_bpButton12 = new wxBitmapButton( m_tileEdit_tileAnimation_Right_panel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxBORDER_NONE );

	m_bpButton12->SetBitmap( wxBitmap( wxT("icons/play.png"), wxBITMAP_TYPE_ANY ) );
	bSizer49->Add( m_bpButton12, 0, wxALL, 5 );

	m_bpButton13 = new wxBitmapButton( m_tileEdit_tileAnimation_Right_panel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxBORDER_NONE );

	m_bpButton13->SetBitmap( wxBitmap( wxT("icons/stop.png"), wxBITMAP_TYPE_ANY ) );
	bSizer49->Add( m_bpButton13, 0, wxALL, 5 );


	bSizer47->Add( bSizer49, 0, wxEXPAND, 5 );


	bSizer47->Add( 0, 0, 1, wxEXPAND, 5 );


	m_tileEdit_tileAnimation_Right_panel->SetSizer( bSizer47 );
	m_tileEdit_tileAnimation_Right_panel->Layout();
	bSizer47->Fit( m_tileEdit_tileAnimation_Right_panel );
	m_splitter6->SplitVertically( m_tileEdit_tileAnimation_middle_panel, m_tileEdit_tileAnimation_Right_panel, -100 );
	bSizer42->Add( m_splitter6, 1, wxEXPAND, 5 );


	m_tileEdit_tileAnimation_panel->SetSizer( bSizer42 );
	m_tileEdit_tileAnimation_panel->Layout();
	bSizer42->Fit( m_tileEdit_tileAnimation_panel );
	m_tileEdit_tools_auinotebook->AddPage( m_tileEdit_tileAnimation_panel, _("Animation"), true, wxNullBitmap );
	m_tileEdit_tileMask_panel = new wxPanel( m_tileEdit_tools_auinotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer861;
	bSizer861 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer87;
	bSizer87 = new wxBoxSizer( wxVERTICAL );

	m_tileEdit_newMask_button = new wxButton( m_tileEdit_tileMask_panel, wxID_ANY, _("New Mask"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer87->Add( m_tileEdit_newMask_button, 0, wxALL|wxEXPAND, 5 );

	m_tileEdit_deleteMask_button = new wxButton( m_tileEdit_tileMask_panel, wxID_ANY, _("Delete Mask"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer87->Add( m_tileEdit_deleteMask_button, 0, wxALL|wxEXPAND, 5 );

	m_tileEdit_mask_listBox = new wxListBox( m_tileEdit_tileMask_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer87->Add( m_tileEdit_mask_listBox, 1, wxALL|wxEXPAND, 5 );


	bSizer861->Add( bSizer87, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer88;
	bSizer88 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer89;
	bSizer89 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText36 = new wxStaticText( m_tileEdit_tileMask_panel, wxID_ANY, _("Mask ID"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText36->Wrap( -1 );
	bSizer89->Add( m_staticText36, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_tileEdit_maskID_textCtrl = new wxTextCtrl( m_tileEdit_tileMask_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer89->Add( m_tileEdit_maskID_textCtrl, 1, wxALL, 5 );


	bSizer89->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer88->Add( bSizer89, 0, wxEXPAND, 5 );

	m_staticline21 = new wxStaticLine( m_tileEdit_tileMask_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer88->Add( m_staticline21, 0, wxEXPAND | wxALL, 5 );

	m_tileMask_tileSheet_panel = new wxPanel( m_tileEdit_tileMask_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL );
	bSizer88->Add( m_tileMask_tileSheet_panel, 1, wxEXPAND | wxALL, 5 );


	bSizer861->Add( bSizer88, 4, wxEXPAND, 5 );


	m_tileEdit_tileMask_panel->SetSizer( bSizer861 );
	m_tileEdit_tileMask_panel->Layout();
	bSizer861->Fit( m_tileEdit_tileMask_panel );
	m_tileEdit_tools_auinotebook->AddPage( m_tileEdit_tileMask_panel, _("Tile Mask"), false, wxNullBitmap );

	bSizer93->Add( m_tileEdit_tools_auinotebook, 1, wxEXPAND | wxALL, 5 );


	m_panel20->SetSizer( bSizer93 );
	m_panel20->Layout();
	bSizer93->Fit( m_panel20 );
	m_splitter3->SplitVertically( m_panel191, m_panel20, 251 );
	bSizer351->Add( m_splitter3, 1, wxEXPAND, 5 );


	m_tileEdit_panel->SetSizer( bSizer351 );
	m_tileEdit_panel->Layout();
	bSizer351->Fit( m_tileEdit_panel );
	m_editorMainTab_auinotebook->AddPage( m_tileEdit_panel, _("Tile Editor"), false, wxNullBitmap );
	m_spriteEdit_panel = new wxPanel( m_editorMainTab_auinotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer57;
	bSizer57 = new wxBoxSizer( wxVERTICAL );

	m_splitter4 = new wxSplitterWindow( m_spriteEdit_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter4->Connect( wxEVT_IDLE, wxIdleEventHandler( Nirvana_MainFrame::m_splitter4OnIdle ), NULL, this );
	m_splitter4->SetMinimumPaneSize( 250 );

	m_panel25 = new wxPanel( m_splitter4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer58;
	bSizer58 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer59;
	bSizer59 = new wxBoxSizer( wxHORIZONTAL );

	m_spriteEditor_newSprite_button = new wxButton( m_panel25, wxID_ANY, _("Load Sprite"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer59->Add( m_spriteEditor_newSprite_button, 1, wxALL, 5 );

	m_spriteEditor_deleteSprite_button = new wxButton( m_panel25, wxID_ANY, _("Delete Sprite"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer59->Add( m_spriteEditor_deleteSprite_button, 1, wxALL, 5 );


	bSizer58->Add( bSizer59, 0, wxEXPAND, 5 );

	m_spriteEdit_sprite_listBox = new wxListBox( m_panel25, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer58->Add( m_spriteEdit_sprite_listBox, 1, wxALL|wxEXPAND, 5 );


	m_panel25->SetSizer( bSizer58 );
	m_panel25->Layout();
	bSizer58->Fit( m_panel25 );
	m_panel26 = new wxPanel( m_splitter4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer611;
	bSizer611 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer61;
	bSizer61 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText20 = new wxStaticText( m_panel26, wxID_ANY, _("Sprite ID:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	bSizer61->Add( m_staticText20, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_spriteEdit_spriteID_textCtrl = new wxTextCtrl( m_panel26, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer61->Add( m_spriteEdit_spriteID_textCtrl, 2, wxALL, 5 );


	bSizer61->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText21 = new wxStaticText( m_panel26, wxID_ANY, _("Frame Size:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	bSizer61->Add( m_staticText21, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_spriteEdit_frameSize_staticText = new wxStaticText( m_panel26, wxID_ANY, _("WIDTH x HEIGHT"), wxDefaultPosition, wxDefaultSize, 0 );
	m_spriteEdit_frameSize_staticText->Wrap( -1 );
	bSizer61->Add( m_spriteEdit_frameSize_staticText, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer61->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer611->Add( bSizer61, 0, wxEXPAND, 5 );

	m_spriteEdit_tools_auinotebook = new wxAuiNotebook( m_panel26, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TAB_FIXED_WIDTH );
	m_spriteEdit_spriteAnimation_panel = new wxPanel( m_spriteEdit_tools_auinotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer60;
	bSizer60 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer62;
	bSizer62 = new wxBoxSizer( wxHORIZONTAL );


	bSizer60->Add( bSizer62, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer63;
	bSizer63 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer64;
	bSizer64 = new wxBoxSizer( wxVERTICAL );

	m_staticText23 = new wxStaticText( m_spriteEdit_spriteAnimation_panel, wxID_ANY, _("Animations"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	bSizer64->Add( m_staticText23, 0, wxALL, 5 );

	m_spriteEdit_newAnimation_button = new wxButton( m_spriteEdit_spriteAnimation_panel, wxID_ANY, _("New Animation"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer64->Add( m_spriteEdit_newAnimation_button, 0, wxALL|wxEXPAND, 5 );

	m_spriteEdit_deleteAnimation_button = new wxButton( m_spriteEdit_spriteAnimation_panel, wxID_ANY, _("Delete Animation"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer64->Add( m_spriteEdit_deleteAnimation_button, 0, wxALL|wxEXPAND, 5 );

	m_spriteEdit_animation_listBox = new wxListBox( m_spriteEdit_spriteAnimation_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer64->Add( m_spriteEdit_animation_listBox, 1, wxALL|wxEXPAND, 5 );


	bSizer63->Add( bSizer64, 0, wxEXPAND, 5 );

	m_splitter5 = new wxSplitterWindow( m_spriteEdit_spriteAnimation_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter5->SetSashGravity( 0.8 );
	m_splitter5->Connect( wxEVT_IDLE, wxIdleEventHandler( Nirvana_MainFrame::m_splitter5OnIdle ), NULL, this );
	m_splitter5->SetMinimumPaneSize( 200 );

	m_panel42 = new wxPanel( m_splitter5, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer65;
	bSizer65 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer100;
	bSizer100 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText43 = new wxStaticText( m_panel42, wxID_ANY, _("Animation ID"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText43->Wrap( -1 );
	bSizer100->Add( m_staticText43, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_spriteEdit_animationID_textCtrl = new wxTextCtrl( m_panel42, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer100->Add( m_spriteEdit_animationID_textCtrl, 2, wxALL, 5 );


	bSizer100->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer65->Add( bSizer100, 0, wxEXPAND, 5 );

	m_staticline9 = new wxStaticLine( m_panel42, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer65->Add( m_staticline9, 0, wxEXPAND | wxALL, 5 );

	m_spriteAnimation_spriteSheet_panel = new wxPanel( m_panel42, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL );
	bSizer65->Add( m_spriteAnimation_spriteSheet_panel, 1, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer69;
	bSizer69 = new wxBoxSizer( wxHORIZONTAL );

	m_spriteEdit_previousFrame_bpButton = new wxBitmapButton( m_panel42, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );

	m_spriteEdit_previousFrame_bpButton->SetBitmap( wxBitmap( wxT("icons/previous.png"), wxBITMAP_TYPE_ANY ) );
	bSizer69->Add( m_spriteEdit_previousFrame_bpButton, 0, wxALL, 5 );

	m_spriteAnimation_frame_panel = new wxPanel( m_panel42, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL );
	bSizer69->Add( m_spriteAnimation_frame_panel, 1, wxEXPAND | wxALL, 5 );

	m_spriteEdit_nextFrame_bpButton = new wxBitmapButton( m_panel42, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );

	m_spriteEdit_nextFrame_bpButton->SetBitmap( wxBitmap( wxT("icons/next.png"), wxBITMAP_TYPE_ANY ) );
	bSizer69->Add( m_spriteEdit_nextFrame_bpButton, 0, wxALL, 5 );


	bSizer65->Add( bSizer69, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer70;
	bSizer70 = new wxBoxSizer( wxHORIZONTAL );


	bSizer70->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer1001;
	bSizer1001 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText421 = new wxStaticText( m_panel42, wxID_ANY, _("Frames:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText421->Wrap( -1 );
	bSizer1001->Add( m_staticText421, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_spriteEdit_numFrames_spinCtrl = new wxSpinCtrl( m_panel42, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 10000, 1 );
	bSizer1001->Add( m_spriteEdit_numFrames_spinCtrl, 0, wxALL|wxEXPAND, 5 );


	bSizer70->Add( bSizer1001, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer66;
	bSizer66 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText25 = new wxStaticText( m_panel42, wxID_ANY, _("FPS:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	bSizer66->Add( m_staticText25, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_spriteEdit_FPS_spinCtrl = new wxSpinCtrl( m_panel42, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10000, 0 );
	bSizer66->Add( m_spriteEdit_FPS_spinCtrl, 0, wxALL|wxEXPAND, 5 );


	bSizer70->Add( bSizer66, 0, wxEXPAND, 5 );


	bSizer70->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer65->Add( bSizer70, 0, wxEXPAND, 5 );


	m_panel42->SetSizer( bSizer65 );
	m_panel42->Layout();
	bSizer65->Fit( m_panel42 );
	m_panel43 = new wxPanel( m_splitter5, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer67;
	bSizer67 = new wxBoxSizer( wxVERTICAL );


	bSizer67->Add( 0, 0, 1, wxEXPAND, 5 );

	m_spriteAnimation_preview_panel = new wxPanel( m_panel43, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL );
	bSizer67->Add( m_spriteAnimation_preview_panel, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer641;
	bSizer641 = new wxBoxSizer( wxHORIZONTAL );

	m_spriteEdit_play_bpButton = new wxBitmapButton( m_panel43, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxBORDER_NONE );

	m_spriteEdit_play_bpButton->SetBitmap( wxBitmap( wxT("icons/play.png"), wxBITMAP_TYPE_ANY ) );
	bSizer641->Add( m_spriteEdit_play_bpButton, 0, wxALL, 5 );

	m_spriteEdit_stop_bpButton = new wxBitmapButton( m_panel43, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxBORDER_NONE );

	m_spriteEdit_stop_bpButton->SetBitmap( wxBitmap( wxT("icons/stop.png"), wxBITMAP_TYPE_ANY ) );
	bSizer641->Add( m_spriteEdit_stop_bpButton, 0, wxALL, 5 );


	bSizer67->Add( bSizer641, 0, wxEXPAND, 5 );


	bSizer67->Add( 0, 0, 1, wxEXPAND, 5 );


	m_panel43->SetSizer( bSizer67 );
	m_panel43->Layout();
	bSizer67->Fit( m_panel43 );
	m_splitter5->SplitVertically( m_panel42, m_panel43, -100 );
	bSizer63->Add( m_splitter5, 1, wxEXPAND, 5 );


	bSizer60->Add( bSizer63, 1, wxEXPAND, 5 );


	m_spriteEdit_spriteAnimation_panel->SetSizer( bSizer60 );
	m_spriteEdit_spriteAnimation_panel->Layout();
	bSizer60->Fit( m_spriteEdit_spriteAnimation_panel );
	m_spriteEdit_tools_auinotebook->AddPage( m_spriteEdit_spriteAnimation_panel, _("Animation"), true, wxNullBitmap );
	m_spriteEdit_spriteCollision_panel = new wxPanel( m_spriteEdit_tools_auinotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer671;
	bSizer671 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer68;
	bSizer68 = new wxBoxSizer( wxVERTICAL );

	m_spriteCollision_edit_panel = new wxPanel( m_spriteEdit_spriteCollision_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL );
	bSizer68->Add( m_spriteCollision_edit_panel, 4, wxEXPAND | wxALL, 5 );


	bSizer68->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer671->Add( bSizer68, 3, wxEXPAND, 5 );

	wxBoxSizer* bSizer691;
	bSizer691 = new wxBoxSizer( wxVERTICAL );

	m_auiToolBar4 = new wxAuiToolBar( m_spriteEdit_spriteCollision_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_HORZ_LAYOUT );
	m_spriteEdit_collisionSelect_tool = m_auiToolBar4->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/cursor2.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_spriteEdit_collisionBoxSelect_tool = m_auiToolBar4->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/box_select2.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_spriteEdit_collisionMove_tool = m_auiToolBar4->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/move2.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_spriteEdit_collisionDraw_tool = m_auiToolBar4->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/line.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_auiToolBar4->Realize();

	bSizer691->Add( m_auiToolBar4, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer681;
	bSizer681 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText27 = new wxStaticText( m_spriteEdit_spriteCollision_panel, wxID_ANY, _("Shape"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText27->Wrap( -1 );
	bSizer681->Add( m_staticText27, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_spriteEdit_collisionShape_comboBox = new wxComboBox( m_spriteEdit_spriteCollision_panel, wxID_ANY, _("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer681->Add( m_spriteEdit_collisionShape_comboBox, 4, wxALL, 5 );


	bSizer691->Add( bSizer681, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer1831;
	bSizer1831 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText1051 = new wxStaticText( m_spriteEdit_spriteCollision_panel, wxID_ANY, _("Detached"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1051->Wrap( -1 );
	bSizer1831->Add( m_staticText1051, 1, wxALL, 5 );

	m_spriteEdit_detachShape_checkBox = new wxCheckBox( m_spriteEdit_spriteCollision_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1831->Add( m_spriteEdit_detachShape_checkBox, 4, wxALL, 5 );


	bSizer691->Add( bSizer1831, 0, wxEXPAND, 5 );

	m_staticline2 = new wxStaticLine( m_spriteEdit_spriteCollision_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer691->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );

	m_spriteCollision_shape_simplebook = new wxSimplebook( m_spriteEdit_spriteCollision_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_spriteShape_rect_panel = new wxPanel( m_spriteCollision_shape_simplebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer701;
	bSizer701 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer71;
	bSizer71 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText29 = new wxStaticText( m_spriteShape_rect_panel, wxID_ANY, _("Local X"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText29->Wrap( -1 );
	bSizer71->Add( m_staticText29, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_spriteEdit_collisionBox_X_spinCtrl = new wxSpinCtrl( m_spriteShape_rect_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -10000, 10000, 0 );
	bSizer71->Add( m_spriteEdit_collisionBox_X_spinCtrl, 4, wxALL, 5 );


	bSizer701->Add( bSizer71, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer72;
	bSizer72 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText30 = new wxStaticText( m_spriteShape_rect_panel, wxID_ANY, _("Local Y"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	bSizer72->Add( m_staticText30, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_spriteEdit_collisionBox_Y_spinCtrl = new wxSpinCtrl( m_spriteShape_rect_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -10000, 10000, 0 );
	bSizer72->Add( m_spriteEdit_collisionBox_Y_spinCtrl, 4, wxALL, 5 );


	bSizer701->Add( bSizer72, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer73;
	bSizer73 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText31 = new wxStaticText( m_spriteShape_rect_panel, wxID_ANY, _("Width"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	bSizer73->Add( m_staticText31, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_spriteEdit_collisionBox_Width_spinCtrl = new wxSpinCtrl( m_spriteShape_rect_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10000, 0 );
	bSizer73->Add( m_spriteEdit_collisionBox_Width_spinCtrl, 4, wxALL, 5 );


	bSizer701->Add( bSizer73, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer74;
	bSizer74 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText32 = new wxStaticText( m_spriteShape_rect_panel, wxID_ANY, _("Height"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText32->Wrap( -1 );
	bSizer74->Add( m_staticText32, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_spriteEdit_collisionBox_Height_spinCtrl = new wxSpinCtrl( m_spriteShape_rect_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10000, 0 );
	bSizer74->Add( m_spriteEdit_collisionBox_Height_spinCtrl, 4, wxALL, 5 );


	bSizer701->Add( bSizer74, 0, wxEXPAND, 5 );


	m_spriteShape_rect_panel->SetSizer( bSizer701 );
	m_spriteShape_rect_panel->Layout();
	bSizer701->Fit( m_spriteShape_rect_panel );
	m_spriteCollision_shape_simplebook->AddPage( m_spriteShape_rect_panel, _("sprite_collision_shape_rect"), false );
	m_spriteShape_polygon_panel = new wxPanel( m_spriteCollision_shape_simplebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer86;
	bSizer86 = new wxBoxSizer( wxVERTICAL );

	m_spriteEdit_collisionPolygon_grid = new wxGrid( m_spriteShape_polygon_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_spriteEdit_collisionPolygon_grid->CreateGrid( 1, 2 );
	m_spriteEdit_collisionPolygon_grid->EnableEditing( true );
	m_spriteEdit_collisionPolygon_grid->EnableGridLines( true );
	m_spriteEdit_collisionPolygon_grid->EnableDragGridSize( false );
	m_spriteEdit_collisionPolygon_grid->SetMargins( 0, 0 );

	// Columns
	m_spriteEdit_collisionPolygon_grid->EnableDragColMove( false );
	m_spriteEdit_collisionPolygon_grid->EnableDragColSize( true );
	m_spriteEdit_collisionPolygon_grid->SetColLabelValue( 0, _("X") );
	m_spriteEdit_collisionPolygon_grid->SetColLabelValue( 1, _("Y") );
	m_spriteEdit_collisionPolygon_grid->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_spriteEdit_collisionPolygon_grid->EnableDragRowSize( true );
	m_spriteEdit_collisionPolygon_grid->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	m_spriteEdit_collisionPolygon_grid->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer86->Add( m_spriteEdit_collisionPolygon_grid, 1, wxALL|wxEXPAND, 5 );


	m_spriteShape_polygon_panel->SetSizer( bSizer86 );
	m_spriteShape_polygon_panel->Layout();
	bSizer86->Fit( m_spriteShape_polygon_panel );
	m_spriteCollision_shape_simplebook->AddPage( m_spriteShape_polygon_panel, _("sprite_collision_shape_polygon"), false );
	m_spriteShape_circle_panel = new wxPanel( m_spriteCollision_shape_simplebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer7011;
	bSizer7011 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer711;
	bSizer711 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText291 = new wxStaticText( m_spriteShape_circle_panel, wxID_ANY, _("Local X"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText291->Wrap( -1 );
	bSizer711->Add( m_staticText291, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_spriteEdit_collisionCircle_X_spinCtrl = new wxSpinCtrl( m_spriteShape_circle_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -10000, 10000, 0 );
	bSizer711->Add( m_spriteEdit_collisionCircle_X_spinCtrl, 4, wxALL, 5 );


	bSizer7011->Add( bSizer711, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer721;
	bSizer721 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText301 = new wxStaticText( m_spriteShape_circle_panel, wxID_ANY, _("Local Y"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText301->Wrap( -1 );
	bSizer721->Add( m_staticText301, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_spriteEdit_collisionCircle_Y_spinCtrl = new wxSpinCtrl( m_spriteShape_circle_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -10000, 10000, 0 );
	bSizer721->Add( m_spriteEdit_collisionCircle_Y_spinCtrl, 4, wxALL, 5 );


	bSizer7011->Add( bSizer721, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer731;
	bSizer731 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText311 = new wxStaticText( m_spriteShape_circle_panel, wxID_ANY, _("Radius"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText311->Wrap( -1 );
	bSizer731->Add( m_staticText311, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_spriteEdit_collisionCircle_Radius_spinCtrl = new wxSpinCtrl( m_spriteShape_circle_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10000, 0 );
	bSizer731->Add( m_spriteEdit_collisionCircle_Radius_spinCtrl, 4, wxALL, 5 );


	bSizer7011->Add( bSizer731, 0, wxEXPAND, 5 );


	m_spriteShape_circle_panel->SetSizer( bSizer7011 );
	m_spriteShape_circle_panel->Layout();
	bSizer7011->Fit( m_spriteShape_circle_panel );
	m_spriteCollision_shape_simplebook->AddPage( m_spriteShape_circle_panel, _("sprite_collision_shape_circle"), false );

	bSizer691->Add( m_spriteCollision_shape_simplebook, 1, wxEXPAND | wxALL, 5 );


	bSizer671->Add( bSizer691, 1, wxEXPAND, 5 );


	m_spriteEdit_spriteCollision_panel->SetSizer( bSizer671 );
	m_spriteEdit_spriteCollision_panel->Layout();
	bSizer671->Fit( m_spriteEdit_spriteCollision_panel );
	m_spriteEdit_tools_auinotebook->AddPage( m_spriteEdit_spriteCollision_panel, _("Collision"), false, wxNullBitmap );

	bSizer611->Add( m_spriteEdit_tools_auinotebook, 1, wxEXPAND | wxALL, 5 );


	m_panel26->SetSizer( bSizer611 );
	m_panel26->Layout();
	bSizer611->Fit( m_panel26 );
	m_splitter4->SplitVertically( m_panel25, m_panel26, 254 );
	bSizer57->Add( m_splitter4, 1, wxEXPAND, 5 );


	m_spriteEdit_panel->SetSizer( bSizer57 );
	m_spriteEdit_panel->Layout();
	bSizer57->Fit( m_spriteEdit_panel );
	m_editorMainTab_auinotebook->AddPage( m_spriteEdit_panel, _("Sprite Editor"), false, wxNullBitmap );

	bSizer1->Add( m_editorMainTab_auinotebook, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();
	m_menubar1 = new wxMenuBar( 0 );
	this->SetMenuBar( m_menubar1 );

	m_toolBar1 = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY );
	m_newProject_tool = m_toolBar1->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/new-project.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_openProject_tool = m_toolBar1->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/folder.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_saveProject_tool = m_toolBar1->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/save.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_toolBar1->AddSeparator();

	m_generate_tool = m_toolBar1->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/build.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_toolBar1->Realize();


	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( Nirvana_MainFrame::OnNirvanaClose ) );
	m_editorMainTab_auinotebook->Connect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( Nirvana_MainFrame::OnMainTabChanged ), NULL, this );
	m_activeLayer_comboBox->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( Nirvana_MainFrame::OnActiveLayerSelect ), NULL, this );
	m_activeLayer_comboBox->Connect( wxEVT_COMBOBOX_CLOSEUP, wxCommandEventHandler( Nirvana_MainFrame::OnLayerComboClose ), NULL, this );
	m_activeLayer_comboBox->Connect( wxEVT_COMBOBOX_DROPDOWN, wxCommandEventHandler( Nirvana_MainFrame::OnLayerComboOpen ), NULL, this );
	this->Connect( m_camera_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnCameraToolClick ) );
	this->Connect( m_mapSet_free_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapSetFree ) );
	this->Connect( m_mapSet_tile_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapSetTiled ) );
	m_mapEdit_map_panel->Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( Nirvana_MainFrame::OnEnterMapView ), NULL, this );
	m_mapEdit_map_panel->Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( Nirvana_MainFrame::OnLeaveMapView ), NULL, this );
	m_mapEdit_map_panel->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( Nirvana_MainFrame::OnMapEdit_Map_UpdateUI ), NULL, this );
	m_projectManager_auinotebook->Connect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( Nirvana_MainFrame::OnProjectPropertiesTabChanged ), NULL, this );
	m_bpButton3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnNewStage ), NULL, this );
	m_bpButton4->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnDeleteStage ), NULL, this );
	m_bpButton8->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_StageSettingsClick ), NULL, this );
	m_bpButton9->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_CopyStageClick ), NULL, this );
	m_project_treeCtrl->Connect( wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler( Nirvana_MainFrame::OnProjectItemActivated ), NULL, this );
	m_button9->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_NewLayerClick ), NULL, this );
	m_button10->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_CopyLayerClick ), NULL, this );
	m_button15->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_ShowAllLayersClick ), NULL, this );
	m_button22->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_HideAllLayersClick ), NULL, this );
	m_bpButton201->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_LayerUpClick ), NULL, this );
	m_bpButton21->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_LayerDownClick ), NULL, this );
	m_bpButton22->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_LayerDeleteClick ), NULL, this );
	m_layerVisible_checkList->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( Nirvana_MainFrame::OnLayerCheckListSelect ), NULL, this );
	m_layerVisible_checkList->Connect( wxEVT_COMMAND_CHECKLISTBOX_TOGGLED, wxCommandEventHandler( Nirvana_MainFrame::OnLayerCheckList_Visible_Toggle ), NULL, this );
	m_layerName_textCtrl->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_LayerNameChange ), NULL, this );
	m_mapEdit_layerHScroll_spinCtrlDouble->Connect( wxEVT_COMMAND_SPINCTRLDOUBLE_UPDATED, wxSpinDoubleEventHandler( Nirvana_MainFrame::OnMapEdit_LayerHScroll ), NULL, this );
	m_mapEdit_layerVScroll_spinCtrlDouble->Connect( wxEVT_COMMAND_SPINCTRLDOUBLE_UPDATED, wxSpinDoubleEventHandler( Nirvana_MainFrame::OnMapEdit_LayerVScroll ), NULL, this );
	m_mapEdit_layerAlpha_spinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Nirvana_MainFrame::OnMapEdit_LayerAlpha ), NULL, this );
	m_mapEdit_showShapes_checkBox->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEditSettings_ShowShapes_Checked ), NULL, this );
	m_mapEdit_showGrid_checkBox->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEditSettings_ShowGrid_Checked ), NULL, this );
	m_mapEdit_gridColor_colourPicker->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( Nirvana_MainFrame::OnMapEditSettings_GridColor_Change ), NULL, this );
	m_mapEdit_cameraSpeed_spinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Nirvana_MainFrame::OnMapEditSettings_CameraSpeed_SpinCtrl ), NULL, this );
	m_mapEdit_layerObjectTools_auinotebook->Connect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( Nirvana_MainFrame::OnMapEditToolsTabChanged ), NULL, this );
	this->Connect( m_mapEdit_tileToolbar_select_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_TileTool_Select ) );
	this->Connect( m_mapEdit_tileToolbar_boxSelect_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_TileTool_BoxSelect ) );
	this->Connect( m_mapEdit_tileToolbar_move_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_TileTool_Move ) );
	this->Connect( m_mapEdit_tileToolbar_setTile_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_TileTool_SetTile ) );
	this->Connect( m_mapEdit_tileToolbar_copyTile_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_TileTool_CopyTile ) );
	this->Connect( m_mapEdit_tileToolbar_fillTile_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_TileTool_FillTile ) );
	this->Connect( m_mapEdit_tileToolbar_deleteSelected_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_TileTool_DeleteSelected ) );
	m_mapEdit_tileSelect_panel->Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( Nirvana_MainFrame::OnEnterMapEditTileSelect ), NULL, this );
	m_mapEdit_tileSelect_panel->Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( Nirvana_MainFrame::OnLeaveMapEditTileSelect ), NULL, this );
	m_mapEdit_tileSelect_panel->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( Nirvana_MainFrame::OnUpdateMapEditTileSelect ), NULL, this );
	this->Connect( m_mapEdit_spriteToolbar_select_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_SpriteTool_Select ) );
	this->Connect( m_mapEdit_spriteToolbar_boxSelect_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_SpriteTool_BoxSelect ) );
	this->Connect( m_mapEdit_spriteToolbar_move_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_SpriteTool_Move ) );
	this->Connect( m_mapEdit_spriteToolbar_rotate_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_SpriteTool_Rotate ) );
	this->Connect( m_mapEdit_spriteToolbar_scale_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_SpriteTool_Scale ) );
	this->Connect( m_mapEdit_spriteToolbar_addSprite_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_SpriteTool_AddSprite ) );
	this->Connect( m_mapEdit_spriteToolbar_deleteSprite_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_SpriteTool_DeleteSprite ) );
	this->Connect( m_mapEdit_spriteToolbar_copySprite_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_SpriteTool_CopySprite ) );
	this->Connect( m_mapEdit_spriteToolbar_centerOnSprite_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_SpriteTool_CenterOnSprite ) );
	m_mapEdit_layerSprite_listBox->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_SpriteListSelect ), NULL, this );
	m_mapEdit_sprite_propertyGrid->Connect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( Nirvana_MainFrame::OnMapEdit_SpritePropertyGridChanged ), NULL, this );
	this->Connect( m_mapEdit_shapeToolbar_select_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_ShapeTool_Select ) );
	this->Connect( m_mapEdit_shapeToolbar_boxSelect_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_ShapeTool_BoxSelect ) );
	this->Connect( m_mapEdit_shapeToolbar_move_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_ShapeTool_Move ) );
	this->Connect( m_mapEdit_shapeToolbar_draw_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_ShapeTool_Draw ) );
	this->Connect( m_mapEdit_shapeToolbar_newBox_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_ShapeTool_NewBoxShape ) );
	this->Connect( m_mapEdit_shapeToolbar_newPolygon_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_ShapeTool_NewPolygonShape ) );
	this->Connect( m_mapEdit_shapeToolbar_newChain_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_ShapeTool_NewChainShape ) );
	this->Connect( m_mapEdit_shapeToolbar_newCircle_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_ShapeTool_NewCircleShape ) );
	this->Connect( m_mapEdit_shapeToolbar_deleteShape_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_ShapeTool_DeleteShape ) );
	m_mapEdit_collisionShape_listBox->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_shapeListSelect ), NULL, this );
	m_mapEdit_shapeName_textCtrl->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Nirvana_MainFrame::OnMapEdit_ShapeName ), NULL, this );
	m_mapEdit_boxShape_posX_spinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Nirvana_MainFrame::OnMapEdit_BoxShape_PosX ), NULL, this );
	m_mapEdit_boxShape_posY_spinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Nirvana_MainFrame::OnMapEdit_BoxShape_PosY ), NULL, this );
	m_mapEdit_boxShape_width_spinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Nirvana_MainFrame::OnMapEdit_BoxShape_Width ), NULL, this );
	m_mapEdit_boxShape_height_spinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Nirvana_MainFrame::OnMapEdit_BoxShape_Height ), NULL, this );
	m_mapEdit_polyShape_grid->Connect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( Nirvana_MainFrame::OnMapEdit_PolyShape_CellChange ), NULL, this );
	m_mapEdit_circleShape_centerX_spinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Nirvana_MainFrame::OnMapEdit_CircleShape_CenterX ), NULL, this );
	m_mapEdit_circleShape_centerY_spinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Nirvana_MainFrame::OnMapEdit_CircleShape_CenterY ), NULL, this );
	m_mapEdit_circleShape_radius_spinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Nirvana_MainFrame::OnMapEdit_CircleShape_Radius ), NULL, this );
	m_mapEdit_canvasRenderSetting_comboBox->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( Nirvana_MainFrame::OnBkg_RenderType ), NULL, this );
	m_mapEdit_canvasImage_comboBox->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( Nirvana_MainFrame::OnBkg_LayerImage ), NULL, this );
	m_newTileset_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnNewTilesetClick ), NULL, this );
	m_button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnDeleteTilesetClick ), NULL, this );
	m_tileEdit_tileset_listBox->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( Nirvana_MainFrame::OnTileEdit_TilesetSelected ), NULL, this );
	m_tileEdit_tilesetID_textCtrl->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Nirvana_MainFrame::OnTileEdit_TileIDChanged ), NULL, this );
	m_tileEdit_tools_auinotebook->Connect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( Nirvana_MainFrame::OnTileEditor_Edit_Changed ), NULL, this );
	m_tileEdit_tileAnimation_panel->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( Nirvana_MainFrame::OnUpdateTileAnimationUI ), NULL, this );
	m_tileEdit_tileAnimation_middle_panel->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( Nirvana_MainFrame::OnUpdateTileAnimationUI ), NULL, this );
	m_tileAnimation_tileSheet_panel->Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( Nirvana_MainFrame::OnEnterTileAnimationSheet ), NULL, this );
	m_tileAnimation_tileSheet_panel->Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( Nirvana_MainFrame::OnLeaveTileAnimationSheet ), NULL, this );
	m_bpButton81->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnTileEdit_PreviousFrame_Click ), NULL, this );
	m_bpButton91->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnTileEdit_NextFrame_Click ), NULL, this );
	this->Connect( m_tileEdit_tileSelect_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnTileEdit_TileSelect_Tool ) );
	this->Connect( m_tileEdit_tileAnimate_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnTileEdit_TileAnimation_Tool ) );
	m_tileEdit_numFrames_spinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Nirvana_MainFrame::OnTileEdit_NumFramesChange ), NULL, this );
	m_tileEdit_FPS_spinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Nirvana_MainFrame::OnTileEdit_FPSChanged ), NULL, this );
	m_bpButton12->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnTileEdit_PlayPreviewClick ), NULL, this );
	m_bpButton13->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnTileEdit_StopPreviewClick ), NULL, this );
	m_tileEdit_tileMask_panel->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( Nirvana_MainFrame::OnUpdateTileMaskUI ), NULL, this );
	m_tileEdit_newMask_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnTileEdit_newMaskClick ), NULL, this );
	m_tileEdit_deleteMask_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnTileEdit_deleteMaskClick ), NULL, this );
	m_tileEdit_mask_listBox->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( Nirvana_MainFrame::OnTileEdit_maskSelected ), NULL, this );
	m_tileEdit_maskID_textCtrl->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Nirvana_MainFrame::OnTileEdit_maskIDChanged ), NULL, this );
	m_tileMask_tileSheet_panel->Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( Nirvana_MainFrame::OnEnterTileMaskSheet ), NULL, this );
	m_tileMask_tileSheet_panel->Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( Nirvana_MainFrame::OnLeaveTileMaskSheet ), NULL, this );
	m_spriteEditor_newSprite_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnNewSpriteClicked ), NULL, this );
	m_spriteEditor_deleteSprite_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnDeleteSpriteClicked ), NULL, this );
	m_spriteEdit_sprite_listBox->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( Nirvana_MainFrame::OnSpriteEdit_Sprite_Selected ), NULL, this );
	m_spriteEdit_spriteID_textCtrl->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Nirvana_MainFrame::OnSpriteEdit_SpriteIDChanged ), NULL, this );
	m_spriteEdit_tools_auinotebook->Connect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( Nirvana_MainFrame::OnSpriteEditor_Edit_Changed ), NULL, this );
	m_spriteEdit_spriteAnimation_panel->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( Nirvana_MainFrame::OnUpdateSpriteAnimationUI ), NULL, this );
	m_spriteEdit_newAnimation_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnSpriteEdit_NewAnimation_Click ), NULL, this );
	m_spriteEdit_deleteAnimation_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnSpriteEdit_DeleteAnimation_Click ), NULL, this );
	m_spriteEdit_animation_listBox->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( Nirvana_MainFrame::OnSpriteEdit_Animation_Selected ), NULL, this );
	m_spriteEdit_animationID_textCtrl->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Nirvana_MainFrame::OnSpriteEdit_AnimationIDChanged ), NULL, this );
	m_spriteAnimation_spriteSheet_panel->Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( Nirvana_MainFrame::OnEnterSpriteAnimationSheet ), NULL, this );
	m_spriteAnimation_spriteSheet_panel->Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( Nirvana_MainFrame::OnLeaveSpriteAnimationSheet ), NULL, this );
	m_spriteAnimation_spriteSheet_panel->Connect( wxEVT_SIZE, wxSizeEventHandler( Nirvana_MainFrame::OnSpriteAnimationSheetSize ), NULL, this );
	m_spriteEdit_previousFrame_bpButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnSpriteEdit_PreviousFrame_Click ), NULL, this );
	m_spriteEdit_nextFrame_bpButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnSpriteEdit_NextFrame_Click ), NULL, this );
	m_spriteEdit_numFrames_spinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Nirvana_MainFrame::OnSpriteEdit_NumFramesChange ), NULL, this );
	m_spriteEdit_FPS_spinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Nirvana_MainFrame::OnSpriteEdit_FPSChanged ), NULL, this );
	m_spriteEdit_play_bpButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnSpriteEdit_PlayPreviewClick ), NULL, this );
	m_spriteEdit_stop_bpButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnSpriteEdit_StopPreviewClick ), NULL, this );
	this->Connect( m_spriteEdit_collisionSelect_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnSpriteEdit_Collision_Select_Click ) );
	this->Connect( m_spriteEdit_collisionBoxSelect_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnSpriteEdit_Collision_BoxSelect_Click ) );
	this->Connect( m_spriteEdit_collisionMove_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnSpriteEdit_Collision_Move_Click ) );
	this->Connect( m_spriteEdit_collisionDraw_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnSpriteEdit_Collision_Draw_Click ) );
	m_spriteEdit_collisionShape_comboBox->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( Nirvana_MainFrame::OnSpriteEdit_ShapeSelect ), NULL, this );
	m_spriteEdit_detachShape_checkBox->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnSpriteEdit_CollisionShapeDetached_Check ), NULL, this );
	m_spriteEdit_collisionBox_X_spinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Nirvana_MainFrame::OnSpriteEdit_collisionBox_X_spinCtrl ), NULL, this );
	m_spriteEdit_collisionBox_Y_spinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Nirvana_MainFrame::OnSpriteEdit_collisionBox_Y_spinCtrl ), NULL, this );
	m_spriteEdit_collisionBox_Width_spinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Nirvana_MainFrame::OnSpriteEdit_collisionBox_Width_spinCtrl ), NULL, this );
	m_spriteEdit_collisionBox_Height_spinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Nirvana_MainFrame::OnSpriteEdit_collisionBox_Height_spinCtrl ), NULL, this );
	m_spriteEdit_collisionPolygon_grid->Connect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( Nirvana_MainFrame::OnSpriteEdit_collisionPolygon_gridCellChange ), NULL, this );
	m_spriteEdit_collisionCircle_X_spinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Nirvana_MainFrame::OnSpriteEdit_collisionCircle_X_spinCtrl ), NULL, this );
	m_spriteEdit_collisionCircle_Y_spinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Nirvana_MainFrame::OnSpriteEdit_collisionCircle_Y_spinCtrl ), NULL, this );
	m_spriteEdit_collisionCircle_Radius_spinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Nirvana_MainFrame::OnSpriteEdit_collisionCircle_Radius_spinCtrl ), NULL, this );
	this->Connect( m_newProject_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnNewProject ) );
	this->Connect( m_openProject_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnOpenProject ) );
	this->Connect( m_saveProject_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnSaveProject ) );
	this->Connect( m_generate_tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnGenerate ) );
}

Nirvana_MainFrame::~Nirvana_MainFrame()
{
}

MyDialog1::MyDialog1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer89;
	bSizer89 = new wxBoxSizer( wxVERTICAL );

	m_panel40 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer105;
	bSizer105 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer106;
	bSizer106 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText45 = new wxStaticText( m_panel40, wxID_ANY, _("Layer Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText45->Wrap( -1 );
	bSizer106->Add( m_staticText45, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrl9 = new wxTextCtrl( m_panel40, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer106->Add( m_textCtrl9, 1, wxALL, 5 );

	m_staticline5 = new wxStaticLine( m_panel40, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer106->Add( m_staticline5, 0, wxEXPAND | wxALL, 5 );

	m_bpButton14 = new wxBitmapButton( m_panel40, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );

	m_bpButton14->SetBitmap( wxBitmap( wxT("icons/up-arrow.png"), wxBITMAP_TYPE_ANY ) );
	bSizer106->Add( m_bpButton14, 0, wxALL, 5 );

	m_bpButton15 = new wxBitmapButton( m_panel40, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );

	m_bpButton15->SetBitmap( wxBitmap( wxT("icons/down-arrow.png"), wxBITMAP_TYPE_ANY ) );
	bSizer106->Add( m_bpButton15, 0, wxALL, 5 );

	m_staticline6 = new wxStaticLine( m_panel40, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer106->Add( m_staticline6, 0, wxEXPAND | wxALL, 5 );

	m_bpButton16 = new wxBitmapButton( m_panel40, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );

	m_bpButton16->SetBitmap( wxBitmap( wxT("icons/delete.png"), wxBITMAP_TYPE_ANY ) );
	bSizer106->Add( m_bpButton16, 0, wxALL, 5 );


	bSizer105->Add( bSizer106, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer107;
	bSizer107 = new wxBoxSizer( wxHORIZONTAL );

	m_staticline7 = new wxStaticLine( m_panel40, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer107->Add( m_staticline7, 1, wxEXPAND | wxALL, 5 );


	bSizer105->Add( bSizer107, 0, wxEXPAND, 5 );

	wxArrayString m_checkList3Choices;
	m_checkList3 = new wxCheckListBox( m_panel40, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_checkList3Choices, 0 );
	bSizer105->Add( m_checkList3, 1, wxALL|wxEXPAND, 5 );


	m_panel40->SetSizer( bSizer105 );
	m_panel40->Layout();
	bSizer105->Fit( m_panel40 );
	bSizer89->Add( m_panel40, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer89 );
	this->Layout();

	this->Centre( wxBOTH );
}

MyDialog1::~MyDialog1()
{
}

NewSprite_Dialog::NewSprite_Dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer95;
	bSizer95 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer951;
	bSizer951 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText39 = new wxStaticText( this, wxID_ANY, _("Sprite ID"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText39->Wrap( -1 );
	bSizer951->Add( m_staticText39, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_spriteID_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer951->Add( m_spriteID_textCtrl, 4, wxALL, 5 );


	bSizer95->Add( bSizer951, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer97;
	bSizer97 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText41 = new wxStaticText( this, wxID_ANY, _("Frame Width  "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	bSizer97->Add( m_staticText41, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_frameWidth_spinCtrl = new wxSpinCtrl( this, wxID_ANY, wxT("32"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10000, 0 );
	bSizer97->Add( m_frameWidth_spinCtrl, 1, wxALL, 5 );


	bSizer97->Add( 0, 0, 3, wxEXPAND, 5 );


	bSizer95->Add( bSizer97, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer98;
	bSizer98 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText42 = new wxStaticText( this, wxID_ANY, _("Frame Height"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText42->Wrap( -1 );
	bSizer98->Add( m_staticText42, 1, wxALL, 5 );

	m_frameHeight_spinCtrl = new wxSpinCtrl( this, wxID_ANY, wxT("32"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10000, 0 );
	bSizer98->Add( m_frameHeight_spinCtrl, 1, wxALL, 5 );


	bSizer98->Add( 0, 0, 3, wxEXPAND, 5 );


	bSizer95->Add( bSizer98, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer96;
	bSizer96 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText40 = new wxStaticText( this, wxID_ANY, _("Spritesheet"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText40->Wrap( -1 );
	bSizer96->Add( m_staticText40, 1, wxALL, 5 );

	wxBoxSizer* bSizer99;
	bSizer99 = new wxBoxSizer( wxVERTICAL );

	m_spriteSheet_searchCtrl = new wxSearchCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifndef __WXMAC__
	m_spriteSheet_searchCtrl->ShowSearchButton( true );
	#endif
	m_spriteSheet_searchCtrl->ShowCancelButton( false );
	bSizer99->Add( m_spriteSheet_searchCtrl, 0, wxALL|wxEXPAND, 5 );

	m_spriteSheet_listBox = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer99->Add( m_spriteSheet_listBox, 1, wxALL|wxEXPAND, 5 );


	bSizer96->Add( bSizer99, 4, wxEXPAND, 5 );


	bSizer95->Add( bSizer96, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer100;
	bSizer100 = new wxBoxSizer( wxHORIZONTAL );


	bSizer100->Add( 0, 0, 1, wxEXPAND, 5 );

	m_newSprite_cancel_button = new wxButton( this, wxID_ANY, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer100->Add( m_newSprite_cancel_button, 0, wxALL, 5 );

	m_newSprite_ok_button = new wxButton( this, wxID_ANY, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer100->Add( m_newSprite_ok_button, 0, wxALL, 5 );


	bSizer95->Add( bSizer100, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer95 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_spriteSheet_searchCtrl->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( NewSprite_Dialog::OnSearch ), NULL, this );
	m_newSprite_cancel_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewSprite_Dialog::OnCancel ), NULL, this );
	m_newSprite_ok_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewSprite_Dialog::OnCreate ), NULL, this );
}

NewSprite_Dialog::~NewSprite_Dialog()
{
}

NewTileset_Dialog::NewTileset_Dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer95;
	bSizer95 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer951;
	bSizer951 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText39 = new wxStaticText( this, wxID_ANY, _("Tileset ID"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText39->Wrap( -1 );
	bSizer951->Add( m_staticText39, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_tilesetID_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer951->Add( m_tilesetID_textCtrl, 4, wxALL, 5 );


	bSizer95->Add( bSizer951, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer97;
	bSizer97 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText41 = new wxStaticText( this, wxID_ANY, _("Tile Width  "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	bSizer97->Add( m_staticText41, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_tileWidth_spinCtrl = new wxSpinCtrl( this, wxID_ANY, wxT("32"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10000, 0 );
	bSizer97->Add( m_tileWidth_spinCtrl, 1, wxALL, 5 );


	bSizer97->Add( 0, 0, 3, wxEXPAND, 5 );


	bSizer95->Add( bSizer97, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer98;
	bSizer98 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText42 = new wxStaticText( this, wxID_ANY, _("Tile Height"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText42->Wrap( -1 );
	bSizer98->Add( m_staticText42, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_tileHeight_spinCtrl = new wxSpinCtrl( this, wxID_ANY, wxT("32"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10000, 0 );
	bSizer98->Add( m_tileHeight_spinCtrl, 1, wxALL, 5 );


	bSizer98->Add( 0, 0, 3, wxEXPAND, 5 );


	bSizer95->Add( bSizer98, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer96;
	bSizer96 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText40 = new wxStaticText( this, wxID_ANY, _("Tilesheet"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText40->Wrap( -1 );
	bSizer96->Add( m_staticText40, 1, wxALL, 5 );

	wxBoxSizer* bSizer99;
	bSizer99 = new wxBoxSizer( wxVERTICAL );

	m_tileSheet_searchCtrl = new wxSearchCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifndef __WXMAC__
	m_tileSheet_searchCtrl->ShowSearchButton( true );
	#endif
	m_tileSheet_searchCtrl->ShowCancelButton( false );
	bSizer99->Add( m_tileSheet_searchCtrl, 0, wxALL|wxEXPAND, 5 );

	m_tileSheet_listBox = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer99->Add( m_tileSheet_listBox, 1, wxALL|wxEXPAND, 5 );


	bSizer96->Add( bSizer99, 4, wxEXPAND, 5 );


	bSizer95->Add( bSizer96, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer100;
	bSizer100 = new wxBoxSizer( wxHORIZONTAL );


	bSizer100->Add( 0, 0, 1, wxEXPAND, 5 );

	m_newTileset_cancel_button = new wxButton( this, wxID_ANY, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer100->Add( m_newTileset_cancel_button, 0, wxALL, 5 );

	m_newTileset_ok_button = new wxButton( this, wxID_ANY, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer100->Add( m_newTileset_ok_button, 0, wxALL, 5 );


	bSizer95->Add( bSizer100, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer95 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_tileSheet_searchCtrl->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( NewTileset_Dialog::OnSearch ), NULL, this );
	m_newTileset_cancel_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewTileset_Dialog::OnCancel ), NULL, this );
	m_newTileset_ok_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewTileset_Dialog::OnCreate ), NULL, this );
}

NewTileset_Dialog::~NewTileset_Dialog()
{
}

NewStage_Dialog::NewStage_Dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer105;
	bSizer105 = new wxBoxSizer( wxVERTICAL );

	m_panel45 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer106;
	bSizer106 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer107;
	bSizer107 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText46 = new wxStaticText( m_panel45, wxID_ANY, _("Stage ID:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText46->Wrap( -1 );
	bSizer107->Add( m_staticText46, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_stageID_textCtrl = new wxTextCtrl( m_panel45, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer107->Add( m_stageID_textCtrl, 3, wxALL, 5 );


	bSizer106->Add( bSizer107, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer10821;
	bSizer10821 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText4721 = new wxStaticText( m_panel45, wxID_ANY, _("Tile Width:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4721->Wrap( -1 );
	bSizer10821->Add( m_staticText4721, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_tileWidth_spinCtrl = new wxSpinCtrl( m_panel45, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 4, 512, 32 );
	bSizer10821->Add( m_tileWidth_spinCtrl, 3, wxALL, 5 );


	bSizer106->Add( bSizer10821, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer108211;
	bSizer108211 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText47211 = new wxStaticText( m_panel45, wxID_ANY, _("Tile Height:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText47211->Wrap( -1 );
	bSizer108211->Add( m_staticText47211, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_tileHeight_spinCtrl = new wxSpinCtrl( m_panel45, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 4, 512, 32 );
	bSizer108211->Add( m_tileHeight_spinCtrl, 3, wxALL, 5 );


	bSizer106->Add( bSizer108211, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer1082;
	bSizer1082 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText472 = new wxStaticText( m_panel45, wxID_ANY, _("Width In Tiles"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText472->Wrap( -1 );
	bSizer1082->Add( m_staticText472, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_width_spinCtrl = new wxSpinCtrl( m_panel45, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000000, 100 );
	bSizer1082->Add( m_width_spinCtrl, 3, wxALL, 5 );


	bSizer106->Add( bSizer1082, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer1083;
	bSizer1083 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText473 = new wxStaticText( m_panel45, wxID_ANY, _("Height in Tiles"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText473->Wrap( -1 );
	bSizer1083->Add( m_staticText473, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_height_spinCtrl = new wxSpinCtrl( m_panel45, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000000, 100 );
	bSizer1083->Add( m_height_spinCtrl, 3, wxALL, 5 );


	bSizer106->Add( bSizer1083, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer116;
	bSizer116 = new wxBoxSizer( wxHORIZONTAL );


	bSizer116->Add( 0, 0, 1, wxEXPAND, 5 );

	m_button17 = new wxButton( m_panel45, wxID_ANY, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer116->Add( m_button17, 0, wxALL, 5 );

	m_button16 = new wxButton( m_panel45, wxID_ANY, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer116->Add( m_button16, 0, wxALL, 5 );


	bSizer106->Add( bSizer116, 0, wxEXPAND, 5 );


	m_panel45->SetSizer( bSizer106 );
	m_panel45->Layout();
	bSizer106->Fit( m_panel45 );
	bSizer105->Add( m_panel45, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer105 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_button17->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewStage_Dialog::OnCancel ), NULL, this );
	m_button16->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewStage_Dialog::OnCreate ), NULL, this );
}

NewStage_Dialog::~NewStage_Dialog()
{
}

NewProject_Dialog::NewProject_Dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer105;
	bSizer105 = new wxBoxSizer( wxVERTICAL );

	m_panel45 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer106;
	bSizer106 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer107;
	bSizer107 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText46 = new wxStaticText( m_panel45, wxID_ANY, _("Project Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText46->Wrap( -1 );
	bSizer107->Add( m_staticText46, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_projectName_textCtrl = new wxTextCtrl( m_panel45, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer107->Add( m_projectName_textCtrl, 3, wxALL, 5 );


	bSizer106->Add( bSizer107, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer176;
	bSizer176 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText98 = new wxStaticText( m_panel45, wxID_ANY, _("Project Location:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText98->Wrap( -1 );
	bSizer176->Add( m_staticText98, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_projectLocation_dirPicker = new wxDirPickerCtrl( m_panel45, wxID_ANY, wxEmptyString, _("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE );
	bSizer176->Add( m_projectLocation_dirPicker, 3, wxALL, 5 );


	bSizer106->Add( bSizer176, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer116;
	bSizer116 = new wxBoxSizer( wxHORIZONTAL );


	bSizer116->Add( 0, 0, 1, wxEXPAND, 5 );

	m_cancel_button = new wxButton( m_panel45, wxID_ANY, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer116->Add( m_cancel_button, 0, wxALL, 5 );

	m_ok_button = new wxButton( m_panel45, wxID_ANY, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer116->Add( m_ok_button, 0, wxALL, 5 );


	bSizer106->Add( bSizer116, 0, wxEXPAND, 5 );


	m_panel45->SetSizer( bSizer106 );
	m_panel45->Layout();
	bSizer106->Fit( m_panel45 );
	bSizer105->Add( m_panel45, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer105 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_cancel_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewProject_Dialog::OnCancel ), NULL, this );
	m_ok_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewProject_Dialog::OnCreate ), NULL, this );
}

NewProject_Dialog::~NewProject_Dialog()
{
}

NewLayer_Dialog::NewLayer_Dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer117;
	bSizer117 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer120;
	bSizer120 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText55 = new wxStaticText( this, wxID_ANY, _("Layer Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText55->Wrap( -1 );
	bSizer120->Add( m_staticText55, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_layerName_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer120->Add( m_layerName_textCtrl, 4, wxALL, 5 );


	bSizer117->Add( bSizer120, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer118;
	bSizer118 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText54 = new wxStaticText( this, wxID_ANY, _("Layer Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText54->Wrap( -1 );
	bSizer118->Add( m_staticText54, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_layerType_comboBox = new wxComboBox( this, wxID_ANY, _("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer118->Add( m_layerType_comboBox, 4, wxALL, 5 );


	bSizer117->Add( bSizer118, 0, wxEXPAND, 5 );

	m_layerType_simplebook = new wxSimplebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_layerType_noTileset_panel = new wxPanel( m_layerType_simplebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_layerType_simplebook->AddPage( m_layerType_noTileset_panel, _("a page"), false );
	m_layerType_tileset_panel = new wxPanel( m_layerType_simplebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer121;
	bSizer121 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer122;
	bSizer122 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText551 = new wxStaticText( m_layerType_tileset_panel, wxID_ANY, _("Tileset:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText551->Wrap( -1 );
	bSizer122->Add( m_staticText551, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_tileset_searchCtrl = new wxSearchCtrl( m_layerType_tileset_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifndef __WXMAC__
	m_tileset_searchCtrl->ShowSearchButton( true );
	#endif
	m_tileset_searchCtrl->ShowCancelButton( false );
	bSizer122->Add( m_tileset_searchCtrl, 4, wxALL, 5 );


	bSizer121->Add( bSizer122, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer123;
	bSizer123 = new wxBoxSizer( wxHORIZONTAL );


	bSizer123->Add( 0, 0, 1, wxEXPAND, 5 );

	m_tileset_listBox = new wxListBox( m_layerType_tileset_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer123->Add( m_tileset_listBox, 4, wxALL|wxEXPAND, 5 );


	bSizer121->Add( bSizer123, 1, wxEXPAND, 5 );


	m_layerType_tileset_panel->SetSizer( bSizer121 );
	m_layerType_tileset_panel->Layout();
	bSizer121->Fit( m_layerType_tileset_panel );
	m_layerType_simplebook->AddPage( m_layerType_tileset_panel, _("a page"), false );

	bSizer117->Add( m_layerType_simplebook, 1, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer119;
	bSizer119 = new wxBoxSizer( wxHORIZONTAL );


	bSizer119->Add( 0, 0, 1, wxEXPAND, 5 );

	m_button21 = new wxButton( this, wxID_ANY, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer119->Add( m_button21, 0, wxALL, 5 );

	m_button20 = new wxButton( this, wxID_ANY, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer119->Add( m_button20, 0, wxALL, 5 );


	bSizer117->Add( bSizer119, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer117 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_layerType_comboBox->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( NewLayer_Dialog::OnLayerTypeSelect ), NULL, this );
	m_tileset_searchCtrl->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( NewLayer_Dialog::OnSearch ), NULL, this );
	m_button21->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewLayer_Dialog::OnCancel ), NULL, this );
	m_button20->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewLayer_Dialog::OnCreate ), NULL, this );
}

NewLayer_Dialog::~NewLayer_Dialog()
{
}

DeleteStage_Dialog::DeleteStage_Dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer127;
	bSizer127 = new wxBoxSizer( wxVERTICAL );


	bSizer127->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer128;
	bSizer128 = new wxBoxSizer( wxHORIZONTAL );


	bSizer128->Add( 0, 0, 1, wxEXPAND, 5 );

	m_msg_staticText = new wxStaticText( this, wxID_ANY, _("DELETE STAGE:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_msg_staticText->Wrap( -1 );
	bSizer128->Add( m_msg_staticText, 0, wxALL, 5 );


	bSizer128->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer127->Add( bSizer128, 2, wxEXPAND, 5 );

	wxBoxSizer* bSizer129;
	bSizer129 = new wxBoxSizer( wxHORIZONTAL );


	bSizer129->Add( 0, 0, 1, wxEXPAND, 5 );

	m_button23 = new wxButton( this, wxID_ANY, _("YES"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer129->Add( m_button23, 0, wxALL, 5 );

	m_button24 = new wxButton( this, wxID_ANY, _("NO"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer129->Add( m_button24, 0, wxALL, 5 );


	bSizer129->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer127->Add( bSizer129, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer127 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_button23->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DeleteStage_Dialog::OnDelete ), NULL, this );
	m_button24->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DeleteStage_Dialog::OnCancel ), NULL, this );
}

DeleteStage_Dialog::~DeleteStage_Dialog()
{
}

StageProperties_Dialog::StageProperties_Dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer105;
	bSizer105 = new wxBoxSizer( wxVERTICAL );

	m_panel45 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer106;
	bSizer106 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer107;
	bSizer107 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText46 = new wxStaticText( m_panel45, wxID_ANY, _("Stage ID:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText46->Wrap( -1 );
	bSizer107->Add( m_staticText46, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_stageID_textCtrl = new wxTextCtrl( m_panel45, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer107->Add( m_stageID_textCtrl, 3, wxALL, 5 );


	bSizer106->Add( bSizer107, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer142;
	bSizer142 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText62 = new wxStaticText( m_panel45, wxID_ANY, _("Tile Width:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText62->Wrap( -1 );
	bSizer142->Add( m_staticText62, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_tileWidth_staticText = new wxStaticText( m_panel45, wxID_ANY, _("[WIDTH]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_tileWidth_staticText->Wrap( -1 );
	bSizer142->Add( m_tileWidth_staticText, 3, wxALL, 5 );


	bSizer106->Add( bSizer142, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer1421;
	bSizer1421 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText621 = new wxStaticText( m_panel45, wxID_ANY, _("Tile Height:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText621->Wrap( -1 );
	bSizer1421->Add( m_staticText621, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_tileHeight_staticText = new wxStaticText( m_panel45, wxID_ANY, _("[HEIGHT]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_tileHeight_staticText->Wrap( -1 );
	bSizer1421->Add( m_tileHeight_staticText, 3, wxALL, 5 );


	bSizer106->Add( bSizer1421, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer1082;
	bSizer1082 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText472 = new wxStaticText( m_panel45, wxID_ANY, _("Width In Tiles:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText472->Wrap( -1 );
	bSizer1082->Add( m_staticText472, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_width_spinCtrl = new wxSpinCtrl( m_panel45, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000000, 100 );
	bSizer1082->Add( m_width_spinCtrl, 3, wxALL, 5 );


	bSizer106->Add( bSizer1082, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer1083;
	bSizer1083 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText473 = new wxStaticText( m_panel45, wxID_ANY, _("Height in Tiles:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText473->Wrap( -1 );
	bSizer1083->Add( m_staticText473, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_height_spinCtrl = new wxSpinCtrl( m_panel45, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000000, 100 );
	bSizer1083->Add( m_height_spinCtrl, 3, wxALL, 5 );


	bSizer106->Add( bSizer1083, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer116;
	bSizer116 = new wxBoxSizer( wxHORIZONTAL );


	bSizer116->Add( 0, 0, 1, wxEXPAND, 5 );

	m_button17 = new wxButton( m_panel45, wxID_ANY, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer116->Add( m_button17, 0, wxALL, 5 );

	m_button16 = new wxButton( m_panel45, wxID_ANY, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer116->Add( m_button16, 0, wxALL, 5 );


	bSizer106->Add( bSizer116, 0, wxEXPAND, 5 );


	m_panel45->SetSizer( bSizer106 );
	m_panel45->Layout();
	bSizer106->Fit( m_panel45 );
	bSizer105->Add( m_panel45, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer105 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_button17->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( StageProperties_Dialog::OnCancel ), NULL, this );
	m_button16->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( StageProperties_Dialog::OnCreate ), NULL, this );
}

StageProperties_Dialog::~StageProperties_Dialog()
{
}

AddSpriteInstance_Dialog::AddSpriteInstance_Dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer132;
	bSizer132 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer133;
	bSizer133 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText59 = new wxStaticText( this, wxID_ANY, _("Sprite ID:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText59->Wrap( -1 );
	bSizer133->Add( m_staticText59, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_spriteID_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer133->Add( m_spriteID_textCtrl, 4, wxALL, 5 );


	bSizer132->Add( bSizer133, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer134;
	bSizer134 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText60 = new wxStaticText( this, wxID_ANY, _("Base Sprite ID:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText60->Wrap( -1 );
	bSizer134->Add( m_staticText60, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_baseSprite_searchCtrl = new wxSearchCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifndef __WXMAC__
	m_baseSprite_searchCtrl->ShowSearchButton( true );
	#endif
	m_baseSprite_searchCtrl->ShowCancelButton( false );
	bSizer134->Add( m_baseSprite_searchCtrl, 4, wxALL, 5 );


	bSizer132->Add( bSizer134, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer135;
	bSizer135 = new wxBoxSizer( wxHORIZONTAL );


	bSizer135->Add( 0, 0, 1, wxEXPAND, 5 );

	m_baseSpriteList_listBox = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer135->Add( m_baseSpriteList_listBox, 4, wxALL|wxEXPAND, 5 );


	bSizer132->Add( bSizer135, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer136;
	bSizer136 = new wxBoxSizer( wxHORIZONTAL );


	bSizer136->Add( 0, 0, 1, wxEXPAND, 5 );

	m_button28 = new wxButton( this, wxID_ANY, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer136->Add( m_button28, 0, wxALL, 5 );

	m_button27 = new wxButton( this, wxID_ANY, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer136->Add( m_button27, 0, wxALL, 5 );


	bSizer132->Add( bSizer136, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer132 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_baseSprite_searchCtrl->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( AddSpriteInstance_Dialog::OnSearch ), NULL, this );
	m_button28->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddSpriteInstance_Dialog::OnCancel ), NULL, this );
	m_button27->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddSpriteInstance_Dialog::OnCreate ), NULL, this );
}

AddSpriteInstance_Dialog::~AddSpriteInstance_Dialog()
{
}

DeleteSprite_Dialog::DeleteSprite_Dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer127;
	bSizer127 = new wxBoxSizer( wxVERTICAL );


	bSizer127->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer140;
	bSizer140 = new wxBoxSizer( wxHORIZONTAL );


	bSizer140->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText63 = new wxStaticText( this, wxID_ANY, _("DELETE SPRITE FROM CURRENT LAYER?"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText63->Wrap( -1 );
	bSizer140->Add( m_staticText63, 0, wxALL, 5 );


	bSizer140->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer127->Add( bSizer140, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer128;
	bSizer128 = new wxBoxSizer( wxHORIZONTAL );


	bSizer128->Add( 0, 0, 1, wxEXPAND, 5 );

	m_msg_staticText = new wxStaticText( this, wxID_ANY, _("SPRITE:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_msg_staticText->Wrap( -1 );
	bSizer128->Add( m_msg_staticText, 0, wxALL, 5 );


	bSizer128->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer127->Add( bSizer128, 2, wxEXPAND, 5 );

	wxBoxSizer* bSizer129;
	bSizer129 = new wxBoxSizer( wxHORIZONTAL );


	bSizer129->Add( 0, 0, 1, wxEXPAND, 5 );

	m_button23 = new wxButton( this, wxID_ANY, _("YES"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer129->Add( m_button23, 0, wxALL, 5 );

	m_button24 = new wxButton( this, wxID_ANY, _("NO"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer129->Add( m_button24, 0, wxALL, 5 );


	bSizer129->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer127->Add( bSizer129, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer127 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_button23->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DeleteSprite_Dialog::OnDelete ), NULL, this );
	m_button24->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DeleteSprite_Dialog::OnCancel ), NULL, this );
}

DeleteSprite_Dialog::~DeleteSprite_Dialog()
{
}

SetCamera_Dialog::SetCamera_Dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer172;
	bSizer172 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer173;
	bSizer173 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText94 = new wxStaticText( this, wxID_ANY, _("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText94->Wrap( -1 );
	bSizer173->Add( m_staticText94, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_posX_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer173->Add( m_posX_textCtrl, 1, wxALL, 5 );

	m_staticText97 = new wxStaticText( this, wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText97->Wrap( -1 );
	bSizer173->Add( m_staticText97, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_posY_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer173->Add( m_posY_textCtrl, 1, wxALL, 5 );


	bSizer172->Add( bSizer173, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer175;
	bSizer175 = new wxBoxSizer( wxHORIZONTAL );


	bSizer175->Add( 0, 0, 1, wxEXPAND, 5 );

	m_cancel_button = new wxButton( this, wxID_ANY, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer175->Add( m_cancel_button, 0, wxALL, 5 );

	m_set_button = new wxButton( this, wxID_ANY, _("Set"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer175->Add( m_set_button, 0, wxALL, 5 );


	bSizer172->Add( bSizer175, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer172 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_cancel_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SetCamera_Dialog::OnCancel ), NULL, this );
	m_set_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SetCamera_Dialog::OnSet ), NULL, this );
}

SetCamera_Dialog::~SetCamera_Dialog()
{
}
