///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6-dirty)
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

	m_comboBox1 = new wxComboBox( m_panel7, wxID_ANY, _("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer5->Add( m_comboBox1, 0, wxALL, 5 );

	m_bpButton1 = new wxBitmapButton( m_panel7, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );

	m_bpButton1->SetBitmap( wxBitmap( wxT("icons/layers.png"), wxBITMAP_TYPE_ANY ) );
	bSizer5->Add( m_bpButton1, 0, wxALL|wxEXPAND, 5 );


	m_panel7->SetSizer( bSizer5 );
	m_panel7->Layout();
	bSizer5->Fit( m_panel7 );
	bSizer4->Add( m_panel7, 0, wxEXPAND | wxALL, 5 );

	m_panel8 = new wxPanel( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	m_panel9 = new wxPanel( m_panel8, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL );
	bSizer6->Add( m_panel9, 1, wxEXPAND | wxALL, 5 );


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
	m_splitter2->Connect( wxEVT_IDLE, wxIdleEventHandler( Nirvana_MainFrame::m_splitter2OnIdle ), NULL, this );
	m_splitter2->SetMinimumPaneSize( 150 );

	m_panel13 = new wxPanel( m_splitter2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );

	m_auinotebook5 = new wxAuiNotebook( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel39 = new wxPanel( m_auinotebook5, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
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


	bSizer14->Add( bSizer931, 0, wxEXPAND, 5 );

	m_treeCtrl1 = new wxTreeCtrl( m_panel39, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
	bSizer14->Add( m_treeCtrl1, 1, wxALL|wxEXPAND, 5 );


	m_panel39->SetSizer( bSizer14 );
	m_panel39->Layout();
	bSizer14->Fit( m_panel39 );
	m_auinotebook5->AddPage( m_panel39, _("Project"), true, wxNullBitmap );
	m_panel40 = new wxPanel( m_auinotebook5, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer871;
	bSizer871 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer911;
	bSizer911 = new wxBoxSizer( wxHORIZONTAL );

	m_button9 = new wxButton( m_panel40, wxID_ANY, _("New Layer"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer911->Add( m_button9, 0, wxALL, 5 );

	m_button10 = new wxButton( m_panel40, wxID_ANY, _("Copy Layer"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer911->Add( m_button10, 0, wxALL, 5 );


	bSizer871->Add( bSizer911, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer94;
	bSizer94 = new wxBoxSizer( wxHORIZONTAL );

	m_staticline15 = new wxStaticLine( m_panel40, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer94->Add( m_staticline15, 1, wxEXPAND | wxALL, 5 );


	bSizer871->Add( bSizer94, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer91;
	bSizer91 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText42 = new wxStaticText( m_panel40, wxID_ANY, _("All Layers:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText42->Wrap( -1 );
	bSizer91->Add( m_staticText42, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_checkBox5 = new wxCheckBox( m_panel40, wxID_ANY, _("Show Tiles"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer91->Add( m_checkBox5, 0, wxALL, 5 );

	m_checkBox6 = new wxCheckBox( m_panel40, wxID_ANY, _("Show Sprites"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer91->Add( m_checkBox6, 0, wxALL, 5 );

	m_checkBox7 = new wxCheckBox( m_panel40, wxID_ANY, _("Show Shapes"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer91->Add( m_checkBox7, 0, wxALL, 5 );


	bSizer871->Add( bSizer91, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer932;
	bSizer932 = new wxBoxSizer( wxHORIZONTAL );

	m_staticline14 = new wxStaticLine( m_panel40, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer932->Add( m_staticline14, 1, wxEXPAND | wxALL, 5 );


	bSizer871->Add( bSizer932, 0, wxEXPAND, 5 );

	m_layerProperties_panel = new wxScrolledWindow( m_panel40, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_layerProperties_panel->SetScrollRate( 5, 5 );
	LayerProperties_Sizer = new wxFlexGridSizer( 0, 12, 0, 0 );
	LayerProperties_Sizer->SetFlexibleDirection( wxBOTH );
	LayerProperties_Sizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );


	m_layerProperties_panel->SetSizer( LayerProperties_Sizer );
	m_layerProperties_panel->Layout();
	LayerProperties_Sizer->Fit( m_layerProperties_panel );
	bSizer871->Add( m_layerProperties_panel, 1, wxEXPAND | wxALL, 5 );


	m_panel40->SetSizer( bSizer871 );
	m_panel40->Layout();
	bSizer871->Fit( m_panel40 );
	m_auinotebook5->AddPage( m_panel40, _("Layers"), false, wxNullBitmap );

	bSizer13->Add( m_auinotebook5, 1, wxEXPAND | wxALL, 5 );


	m_panel13->SetSizer( bSizer13 );
	m_panel13->Layout();
	bSizer13->Fit( m_panel13 );
	m_panel14 = new wxPanel( m_splitter2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );

	m_auinotebook2 = new wxAuiNotebook( m_panel14, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TAB_FIXED_WIDTH );
	m_mapEdit_tile_panel = new wxPanel( m_auinotebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer261;
	bSizer261 = new wxBoxSizer( wxHORIZONTAL );

	m_auiToolBar3 = new wxAuiToolBar( m_mapEdit_tile_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_HORZ_LAYOUT );
	m_tool18 = m_auiToolBar3->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/cursor2.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_tool19 = m_auiToolBar3->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/box_select2.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_tool20 = m_auiToolBar3->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/move2.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_tool21 = m_auiToolBar3->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/place_tile.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_tool22 = m_auiToolBar3->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/flood.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_auiToolBar3->AddSeparator();

	m_tool23 = m_auiToolBar3->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/remove_tile.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_auiToolBar3->Realize();

	bSizer261->Add( m_auiToolBar3, 1, wxALL, 5 );


	bSizer16->Add( bSizer261, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxHORIZONTAL );

	m_comboBox3 = new wxComboBox( m_mapEdit_tile_panel, wxID_ANY, _("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer17->Add( m_comboBox3, 1, wxALL, 5 );


	bSizer16->Add( bSizer17, 0, wxEXPAND, 5 );

	m_panel17 = new wxPanel( m_mapEdit_tile_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL );
	bSizer16->Add( m_panel17, 1, wxEXPAND | wxALL, 5 );


	m_mapEdit_tile_panel->SetSizer( bSizer16 );
	m_mapEdit_tile_panel->Layout();
	bSizer16->Fit( m_mapEdit_tile_panel );
	m_auinotebook2->AddPage( m_mapEdit_tile_panel, _("Tiles"), true, wxNullBitmap );
	m_mapEdit_sprite_panel = new wxPanel( m_auinotebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );

	m_auiToolBar1 = new wxAuiToolBar( m_mapEdit_sprite_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_HORZ_LAYOUT );
	m_tool4 = m_auiToolBar1->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/cursor2.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_tool5 = m_auiToolBar1->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/box_select2.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_tool6 = m_auiToolBar1->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/move2.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_tool7 = m_auiToolBar1->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/rotate2D_2.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_tool8 = m_auiToolBar1->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/scale2.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_auiToolBar1->AddSeparator();

	m_tool1 = m_auiToolBar1->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/new_sprite.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_tool2 = m_auiToolBar1->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/remove_sprite.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_tool3 = m_auiToolBar1->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/nav.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_auiToolBar1->Realize();

	bSizer19->Add( m_auiToolBar1, 1, wxALL, 5 );


	bSizer18->Add( bSizer19, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxHORIZONTAL );

	m_listBox2 = new wxListBox( m_mapEdit_sprite_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer20->Add( m_listBox2, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxVERTICAL );

	m_panel18 = new wxPanel( m_mapEdit_sprite_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL );
	bSizer21->Add( m_panel18, 1, wxEXPAND | wxALL, 5 );

	m_panel19 = new wxPanel( m_mapEdit_sprite_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer221;
	bSizer221 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText81 = new wxStaticText( m_panel19, wxID_ANY, _("ID:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText81->Wrap( -1 );
	bSizer221->Add( m_staticText81, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrl2 = new wxTextCtrl( m_panel19, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	bSizer221->Add( m_textCtrl2, 3, wxALL, 5 );


	bSizer22->Add( bSizer221, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText11 = new wxStaticText( m_panel19, wxID_ANY, _("Type"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizer26->Add( m_staticText11, 1, wxALIGN_CENTER_VERTICAL, 5 );

	m_comboBox31 = new wxComboBox( m_panel19, wxID_ANY, _("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer26->Add( m_comboBox31, 3, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer22->Add( bSizer26, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer231;
	bSizer231 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText7 = new wxStaticText( m_panel19, wxID_ANY, _("Animation:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	bSizer231->Add( m_staticText7, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_staticText8 = new wxStaticText( m_panel19, wxID_ANY, _("NONE"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText8->Wrap( -1 );
	bSizer231->Add( m_staticText8, 2, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_bpButton10 = new wxBitmapButton( m_panel19, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );

	m_bpButton10->SetBitmap( wxBitmap( wxT("icons/line_text.png"), wxBITMAP_TYPE_ANY ) );
	bSizer231->Add( m_bpButton10, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer22->Add( bSizer231, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText5 = new wxStaticText( m_panel19, wxID_ANY, _("Position:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer23->Add( m_staticText5, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrl4 = new wxTextCtrl( m_panel19, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	bSizer23->Add( m_textCtrl4, 3, wxALL, 5 );


	bSizer22->Add( bSizer23, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText6 = new wxStaticText( m_panel19, wxID_ANY, _("Rotation:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	bSizer24->Add( m_staticText6, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_spinCtrl1 = new wxSpinCtrl( m_panel19, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS|wxTE_PROCESS_ENTER, 0, 360, 0 );
	bSizer24->Add( m_spinCtrl1, 3, wxALL, 5 );


	bSizer22->Add( bSizer24, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText9 = new wxStaticText( m_panel19, wxID_ANY, _("Scale:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	bSizer25->Add( m_staticText9, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_spinCtrlDouble1 = new wxSpinCtrlDouble( m_panel19, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS|wxTE_PROCESS_ENTER, 0, 10000, 0, 0.1 );
	m_spinCtrlDouble1->SetDigits( 2 );
	bSizer25->Add( m_spinCtrlDouble1, 3, wxALL, 5 );


	bSizer22->Add( bSizer25, 0, wxEXPAND, 5 );


	m_panel19->SetSizer( bSizer22 );
	m_panel19->Layout();
	bSizer22->Fit( m_panel19 );
	bSizer21->Add( m_panel19, 1, wxEXPAND | wxALL, 5 );


	bSizer20->Add( bSizer21, 1, wxEXPAND, 5 );


	bSizer18->Add( bSizer20, 1, wxEXPAND, 5 );


	m_mapEdit_sprite_panel->SetSizer( bSizer18 );
	m_mapEdit_sprite_panel->Layout();
	bSizer18->Fit( m_mapEdit_sprite_panel );
	m_auinotebook2->AddPage( m_mapEdit_sprite_panel, _("Sprites"), false, wxNullBitmap );
	m_mapEdit_collision_panel = new wxPanel( m_auinotebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer241;
	bSizer241 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer251;
	bSizer251 = new wxBoxSizer( wxHORIZONTAL );

	m_auiToolBar2 = new wxAuiToolBar( m_mapEdit_collision_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_HORZ_LAYOUT );
	m_tool141 = m_auiToolBar2->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/cursor2.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_tool161 = m_auiToolBar2->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/box_select2.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_tool17 = m_auiToolBar2->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/move2.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_tool12 = m_auiToolBar2->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/box.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_tool13 = m_auiToolBar2->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/polygon.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_tool14 = m_auiToolBar2->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/chain.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_tool15 = m_auiToolBar2->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/circle.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_auiToolBar2->AddSeparator();

	m_tool16 = m_auiToolBar2->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/remove_shape.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_auiToolBar2->Realize();

	bSizer251->Add( m_auiToolBar2, 1, wxALL, 5 );


	bSizer241->Add( bSizer251, 0, wxEXPAND, 5 );

	m_listBox21 = new wxListBox( m_mapEdit_collision_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer241->Add( m_listBox21, 1, wxALL|wxEXPAND, 5 );


	m_mapEdit_collision_panel->SetSizer( bSizer241 );
	m_mapEdit_collision_panel->Layout();
	bSizer241->Fit( m_mapEdit_collision_panel );
	m_auinotebook2->AddPage( m_mapEdit_collision_panel, _("Collision"), false, wxNullBitmap );
	m_panel16 = new wxPanel( m_auinotebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxVERTICAL );

	m_panel171 = new wxPanel( m_panel16, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL );
	bSizer27->Add( m_panel171, 1, wxEXPAND | wxALL, 5 );

	m_scrolledWindow1 = new wxScrolledWindow( m_panel16, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow1->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer32;
	bSizer32 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText82 = new wxStaticText( m_scrolledWindow1, wxID_ANY, _("Layer Image"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText82->Wrap( -1 );
	bSizer32->Add( m_staticText82, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_bcomboBox1 = new wxBitmapComboBox( m_scrolledWindow1, wxID_ANY, _("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer32->Add( m_bcomboBox1, 4, wxALL, 5 );


	bSizer30->Add( bSizer32, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer33;
	bSizer33 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText91 = new wxStaticText( m_scrolledWindow1, wxID_ANY, _("Clear Color"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText91->Wrap( -1 );
	bSizer33->Add( m_staticText91, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_colourPicker1 = new wxColourPickerCtrl( m_scrolledWindow1, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	bSizer33->Add( m_colourPicker1, 4, wxALL, 5 );


	bSizer30->Add( bSizer33, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer37;
	bSizer37 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText12 = new wxStaticText( m_scrolledWindow1, wxID_ANY, _("Layer Alpha"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	bSizer37->Add( m_staticText12, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_spinCtrl2 = new wxSpinCtrl( m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 255 );
	bSizer37->Add( m_spinCtrl2, 4, wxALL, 5 );


	bSizer30->Add( bSizer37, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer35;
	bSizer35 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText13 = new wxStaticText( m_scrolledWindow1, wxID_ANY, _("Scroll Flag"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	bSizer35->Add( m_staticText13, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_comboBox4 = new wxComboBox( m_scrolledWindow1, wxID_ANY, _("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer35->Add( m_comboBox4, 4, wxALL, 5 );


	bSizer30->Add( bSizer35, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer34;
	bSizer34 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText10 = new wxStaticText( m_scrolledWindow1, wxID_ANY, _("H Scroll"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	bSizer34->Add( m_staticText10, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_spinCtrlDouble2 = new wxSpinCtrlDouble( m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10000, 0, 0.1 );
	m_spinCtrlDouble2->SetDigits( 1 );
	bSizer34->Add( m_spinCtrlDouble2, 4, wxALL, 5 );


	bSizer30->Add( bSizer34, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer36;
	bSizer36 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText111 = new wxStaticText( m_scrolledWindow1, wxID_ANY, _("V Scroll"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText111->Wrap( -1 );
	bSizer36->Add( m_staticText111, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_spinCtrlDouble3 = new wxSpinCtrlDouble( m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10000, 0, 0.1 );
	m_spinCtrlDouble3->SetDigits( 1 );
	bSizer36->Add( m_spinCtrlDouble3, 4, wxALL, 5 );


	bSizer30->Add( bSizer36, 0, wxEXPAND, 5 );


	m_scrolledWindow1->SetSizer( bSizer30 );
	m_scrolledWindow1->Layout();
	bSizer30->Fit( m_scrolledWindow1 );
	bSizer27->Add( m_scrolledWindow1, 1, wxEXPAND | wxALL, 5 );


	m_panel16->SetSizer( bSizer27 );
	m_panel16->Layout();
	bSizer27->Fit( m_panel16 );
	m_auinotebook2->AddPage( m_panel16, _("Bitmap"), false, wxNullBitmap );

	bSizer15->Add( m_auinotebook2, 1, wxEXPAND | wxALL, 5 );


	m_panel14->SetSizer( bSizer15 );
	m_panel14->Layout();
	bSizer15->Fit( m_panel14 );
	m_splitter2->SplitHorizontally( m_panel13, m_panel14, 152 );
	bSizer7->Add( m_splitter2, 1, wxEXPAND, 5 );


	m_panel2->SetSizer( bSizer7 );
	m_panel2->Layout();
	bSizer7->Fit( m_panel2 );
	m_splitter1->SplitVertically( m_panel1, m_panel2, 500 );
	bSizer12->Add( m_splitter1, 1, wxEXPAND, 5 );


	bSizer3->Add( bSizer12, 1, wxEXPAND, 5 );


	m_mapEdit_panel->SetSizer( bSizer3 );
	m_mapEdit_panel->Layout();
	bSizer3->Fit( m_mapEdit_panel );
	m_editorMainTab_auinotebook->AddPage( m_mapEdit_panel, _("Map Editor"), false, wxNullBitmap );
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

	m_button1 = new wxButton( m_panel191, wxID_ANY, _("New Tileset"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer39->Add( m_button1, 1, wxALL, 5 );

	m_button2 = new wxButton( m_panel191, wxID_ANY, _("Delete Tileset"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer39->Add( m_button2, 1, wxALL, 5 );


	bSizer38->Add( bSizer39, 0, wxEXPAND, 5 );

	m_listBox3 = new wxListBox( m_panel191, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer38->Add( m_listBox3, 1, wxALL|wxEXPAND, 5 );


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

	m_textCtrl6 = new wxTextCtrl( m_panel20, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	bSizer56->Add( m_textCtrl6, 1, wxALL, 5 );


	bSizer56->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer93->Add( bSizer56, 0, wxEXPAND, 5 );

	m_auinotebook4 = new wxAuiNotebook( m_panel20, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TAB_FIXED_WIDTH );
	m_panel35 = new wxPanel( m_auinotebook4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer42;
	bSizer42 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer( wxVERTICAL );

	m_tileAnimation_tileSheet_panel = new wxPanel( m_panel35, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL );
	bSizer40->Add( m_tileAnimation_tileSheet_panel, 1, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer46;
	bSizer46 = new wxBoxSizer( wxHORIZONTAL );

	m_bpButton81 = new wxBitmapButton( m_panel35, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );

	m_bpButton81->SetBitmap( wxBitmap( wxT("icons/previous.png"), wxBITMAP_TYPE_ANY ) );
	bSizer46->Add( m_bpButton81, 0, wxALL, 5 );

	m_tileAnimation_tileFrames_panel = new wxPanel( m_panel35, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL );
	bSizer46->Add( m_tileAnimation_tileFrames_panel, 1, wxEXPAND | wxALL, 5 );

	m_bpButton91 = new wxBitmapButton( m_panel35, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );

	m_bpButton91->SetBitmap( wxBitmap( wxT("icons/next.png"), wxBITMAP_TYPE_ANY ) );
	bSizer46->Add( m_bpButton91, 0, wxALL, 5 );


	bSizer40->Add( bSizer46, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer55;
	bSizer55 = new wxBoxSizer( wxHORIZONTAL );


	bSizer55->Add( 0, 0, 1, wxEXPAND, 5 );

	m_bpButton15 = new wxBitmapButton( m_panel35, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );

	m_bpButton15->SetBitmap( wxBitmap( wxT("icons/minus2.png"), wxBITMAP_TYPE_ANY ) );
	bSizer55->Add( m_bpButton15, 0, wxALL, 5 );

	m_bpButton14 = new wxBitmapButton( m_panel35, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );

	m_bpButton14->SetBitmap( wxBitmap( wxT("icons/add2.png"), wxBITMAP_TYPE_ANY ) );
	bSizer55->Add( m_bpButton14, 0, wxALL, 5 );

	m_bpButton16 = new wxBitmapButton( m_panel35, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );

	m_bpButton16->SetBitmap( wxBitmap( wxT("icons/equal2.png"), wxBITMAP_TYPE_ANY ) );
	bSizer55->Add( m_bpButton16, 0, wxALL, 5 );


	bSizer55->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer40->Add( bSizer55, 0, wxEXPAND, 5 );


	bSizer42->Add( bSizer40, 7, wxEXPAND, 5 );

	wxBoxSizer* bSizer47;
	bSizer47 = new wxBoxSizer( wxVERTICAL );


	bSizer47->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText15 = new wxStaticText( m_panel35, wxID_ANY, _("Preview"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	bSizer47->Add( m_staticText15, 0, wxALL, 5 );

	m_tileAnimation_preview_panel = new wxPanel( m_panel35, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL );
	bSizer47->Add( m_tileAnimation_preview_panel, 1, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer49;
	bSizer49 = new wxBoxSizer( wxHORIZONTAL );

	m_bpButton12 = new wxBitmapButton( m_panel35, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxBORDER_NONE );

	m_bpButton12->SetBitmap( wxBitmap( wxT("icons/play.png"), wxBITMAP_TYPE_ANY ) );
	bSizer49->Add( m_bpButton12, 0, wxALL, 5 );

	m_bpButton13 = new wxBitmapButton( m_panel35, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxBORDER_NONE );

	m_bpButton13->SetBitmap( wxBitmap( wxT("icons/stop.png"), wxBITMAP_TYPE_ANY ) );
	bSizer49->Add( m_bpButton13, 0, wxALL, 5 );


	bSizer47->Add( bSizer49, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer50;
	bSizer50 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText16 = new wxStaticText( m_panel35, wxID_ANY, _("Base Tile:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	bSizer50->Add( m_staticText16, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrl3 = new wxTextCtrl( m_panel35, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer50->Add( m_textCtrl3, 2, wxALL, 5 );


	bSizer47->Add( bSizer50, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer52;
	bSizer52 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText17 = new wxStaticText( m_panel35, wxID_ANY, _("FPS:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	bSizer52->Add( m_staticText17, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrl41 = new wxTextCtrl( m_panel35, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer52->Add( m_textCtrl41, 2, wxALL, 5 );


	bSizer47->Add( bSizer52, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer54;
	bSizer54 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText18 = new wxStaticText( m_panel35, wxID_ANY, _("Frames:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	bSizer54->Add( m_staticText18, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrl5 = new wxTextCtrl( m_panel35, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer54->Add( m_textCtrl5, 2, wxALL, 5 );


	bSizer47->Add( bSizer54, 0, wxEXPAND, 5 );


	bSizer47->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer42->Add( bSizer47, 2, wxEXPAND, 5 );


	m_panel35->SetSizer( bSizer42 );
	m_panel35->Layout();
	bSizer42->Fit( m_panel35 );
	m_auinotebook4->AddPage( m_panel35, _("Animation"), true, wxNullBitmap );
	m_panel36 = new wxPanel( m_auinotebook4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer861;
	bSizer861 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer87;
	bSizer87 = new wxBoxSizer( wxVERTICAL );

	m_button7 = new wxButton( m_panel36, wxID_ANY, _("New Mask"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer87->Add( m_button7, 0, wxALL|wxEXPAND, 5 );

	m_button8 = new wxButton( m_panel36, wxID_ANY, _("Delete Mask"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer87->Add( m_button8, 0, wxALL|wxEXPAND, 5 );

	m_listBox6 = new wxListBox( m_panel36, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer87->Add( m_listBox6, 1, wxALL|wxEXPAND, 5 );


	bSizer861->Add( bSizer87, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer88;
	bSizer88 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer89;
	bSizer89 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText36 = new wxStaticText( m_panel36, wxID_ANY, _("Mask ID"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText36->Wrap( -1 );
	bSizer89->Add( m_staticText36, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrl12 = new wxTextCtrl( m_panel36, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer89->Add( m_textCtrl12, 1, wxALL, 5 );


	bSizer89->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer88->Add( bSizer89, 0, wxEXPAND, 5 );

	m_staticline21 = new wxStaticLine( m_panel36, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer88->Add( m_staticline21, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer90;
	bSizer90 = new wxBoxSizer( wxHORIZONTAL );

	m_auiToolBar6 = new wxAuiToolBar( m_panel36, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_HORZ_LAYOUT );
	m_tool30 = m_auiToolBar6->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/mask_on.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_tool31 = m_auiToolBar6->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/mask_off.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_auiToolBar6->AddSeparator();

	m_tool32 = m_auiToolBar6->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/clear.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_auiToolBar6->Realize();

	bSizer90->Add( m_auiToolBar6, 1, wxALL, 5 );


	bSizer88->Add( bSizer90, 0, wxEXPAND, 5 );

	m_tileMask_tileSheet_panel = new wxPanel( m_panel36, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL );
	bSizer88->Add( m_tileMask_tileSheet_panel, 1, wxEXPAND | wxALL, 5 );


	bSizer861->Add( bSizer88, 4, wxEXPAND, 5 );


	m_panel36->SetSizer( bSizer861 );
	m_panel36->Layout();
	bSizer861->Fit( m_panel36 );
	m_auinotebook4->AddPage( m_panel36, _("Tile Mask"), false, wxNullBitmap );

	bSizer93->Add( m_auinotebook4, 1, wxEXPAND | wxALL, 5 );


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

	m_spriteEditor_newSprite_button = new wxButton( m_panel25, wxID_ANY, _("New Sprite"), wxDefaultPosition, wxDefaultSize, 0 );
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
	bSizer61->Add( m_spriteEdit_spriteID_textCtrl, 1, wxALL, 5 );


	bSizer61->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText21 = new wxStaticText( m_panel26, wxID_ANY, _("Frame Size:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	bSizer61->Add( m_staticText21, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_staticText22 = new wxStaticText( m_panel26, wxID_ANY, _("32 x 32"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	bSizer61->Add( m_staticText22, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


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

	m_staticText421 = new wxStaticText( m_panel42, wxID_ANY, _("Frames"), wxDefaultPosition, wxDefaultSize, 0 );
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
	m_spriteEdit_tools_auinotebook->AddPage( m_spriteEdit_spriteAnimation_panel, _("Animation"), false, wxNullBitmap );
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

	m_spriteEdit_collisionBox_X_spinCtrl = new wxSpinCtrl( m_spriteShape_rect_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10000, 0 );
	bSizer71->Add( m_spriteEdit_collisionBox_X_spinCtrl, 4, wxALL, 5 );


	bSizer701->Add( bSizer71, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer72;
	bSizer72 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText30 = new wxStaticText( m_spriteShape_rect_panel, wxID_ANY, _("Local Y"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	bSizer72->Add( m_staticText30, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_spriteEdit_collisionBox_Y_spinCtrl = new wxSpinCtrl( m_spriteShape_rect_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10000, 0 );
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
	bSizer86->Add( m_spriteEdit_collisionPolygon_grid, 0, wxALL, 5 );


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

	m_spriteEdit_collisionCircle_X_spinCtrl = new wxSpinCtrl( m_spriteShape_circle_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10000, 0 );
	bSizer711->Add( m_spriteEdit_collisionCircle_X_spinCtrl, 4, wxALL, 5 );


	bSizer7011->Add( bSizer711, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer721;
	bSizer721 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText301 = new wxStaticText( m_spriteShape_circle_panel, wxID_ANY, _("Local Y"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText301->Wrap( -1 );
	bSizer721->Add( m_staticText301, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_spriteEdit_collisionCircle_Y_spinCtrl = new wxSpinCtrl( m_spriteShape_circle_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10000, 0 );
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
	m_spriteEdit_tools_auinotebook->AddPage( m_spriteEdit_spriteCollision_panel, _("Collision"), true, wxNullBitmap );

	bSizer611->Add( m_spriteEdit_tools_auinotebook, 1, wxEXPAND | wxALL, 5 );


	m_panel26->SetSizer( bSizer611 );
	m_panel26->Layout();
	bSizer611->Fit( m_panel26 );
	m_splitter4->SplitVertically( m_panel25, m_panel26, 254 );
	bSizer57->Add( m_splitter4, 1, wxEXPAND, 5 );


	m_spriteEdit_panel->SetSizer( bSizer57 );
	m_spriteEdit_panel->Layout();
	bSizer57->Fit( m_spriteEdit_panel );
	m_editorMainTab_auinotebook->AddPage( m_spriteEdit_panel, _("Sprite Editor"), true, wxNullBitmap );

	bSizer1->Add( m_editorMainTab_auinotebook, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();
	m_menubar1 = new wxMenuBar( 0 );
	this->SetMenuBar( m_menubar1 );

	m_toolBar1 = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY );
	m_tool33 = m_toolBar1->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/new-project.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_tool34 = m_toolBar1->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/save.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_toolBar1->AddSeparator();

	m_tool35 = m_toolBar1->AddTool( wxID_ANY, _("tool"), wxBitmap( wxT("icons/build.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_toolBar1->Realize();


	this->Centre( wxBOTH );

	// Connect Events
	m_editorMainTab_auinotebook->Connect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( Nirvana_MainFrame::OnMainTabChanged ), NULL, this );
	m_bpButton1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Nirvana_MainFrame::OnTestButtonClick ), NULL, this );
	m_auinotebook5->Connect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( Nirvana_MainFrame::OnProjectPropertiesTabChanged ), NULL, this );
	m_auinotebook2->Connect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( Nirvana_MainFrame::OnMapEditToolsTabChanged ), NULL, this );
	m_auinotebook4->Connect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( Nirvana_MainFrame::OnTileEditor_Edit_Changed ), NULL, this );
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
	m_spriteEdit_collisionBox_X_spinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Nirvana_MainFrame::OnSpriteEdit_collisionBox_X_spinCtrl ), NULL, this );
	m_spriteEdit_collisionBox_Y_spinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Nirvana_MainFrame::OnSpriteEdit_collisionBox_Y_spinCtrl ), NULL, this );
	m_spriteEdit_collisionBox_Width_spinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Nirvana_MainFrame::OnSpriteEdit_collisionBox_Width_spinCtrl ), NULL, this );
	m_spriteEdit_collisionBox_Height_spinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Nirvana_MainFrame::OnSpriteEdit_collisionBox_Height_spinCtrl ), NULL, this );
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
	wxBoxSizer* bSizer90;
	bSizer90 = new wxBoxSizer( wxVERTICAL );

	m_panel41 = new wxPanel( m_panel40, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 0, 12, 0, 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText43 = new wxStaticText( m_panel41, wxID_ANY, _("0:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText43->Wrap( -1 );
	fgSizer3->Add( m_staticText43, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_staticline10 = new wxStaticLine( m_panel41, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	fgSizer3->Add( m_staticline10, 0, wxEXPAND | wxALL, 5 );

	m_bpButton29 = new wxBitmapButton( m_panel41, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxBORDER_NONE );

	m_bpButton29->SetBitmap( wxBitmap( wxT("icons/up-arrow.png"), wxBITMAP_TYPE_ANY ) );
	fgSizer3->Add( m_bpButton29, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_bpButton30 = new wxBitmapButton( m_panel41, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxBORDER_NONE );

	m_bpButton30->SetBitmap( wxBitmap( wxT("icons/down-arrow.png"), wxBITMAP_TYPE_ANY ) );
	fgSizer3->Add( m_bpButton30, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_staticline11 = new wxStaticLine( m_panel41, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	fgSizer3->Add( m_staticline11, 0, wxEXPAND | wxALL, 5 );

	m_bpButton31 = new wxBitmapButton( m_panel41, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxBORDER_NONE );

	m_bpButton31->SetBitmap( wxBitmap( wxT("icons/delete.png"), wxBITMAP_TYPE_ANY ) );
	fgSizer3->Add( m_bpButton31, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_staticline12 = new wxStaticLine( m_panel41, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	fgSizer3->Add( m_staticline12, 0, wxEXPAND | wxALL, 5 );

	m_staticText45 = new wxStaticText( m_panel41, wxID_ANY, _("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText45->Wrap( -1 );
	fgSizer3->Add( m_staticText45, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrl12 = new wxTextCtrl( m_panel41, wxID_ANY, _("Tile Layer"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( m_textCtrl12, 0, wxALL, 5 );

	m_staticline13 = new wxStaticLine( m_panel41, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	fgSizer3->Add( m_staticline13, 0, wxEXPAND | wxALL, 5 );

	m_checkBox8 = new wxCheckBox( m_panel41, wxID_ANY, _("Tile"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( m_checkBox8, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	fgSizer3->Add( 0, 0, 1, wxEXPAND, 5 );


	m_panel41->SetSizer( fgSizer3 );
	m_panel41->Layout();
	fgSizer3->Fit( m_panel41 );
	bSizer90->Add( m_panel41, 1, wxEXPAND | wxALL, 5 );


	m_panel40->SetSizer( bSizer90 );
	m_panel40->Layout();
	bSizer90->Fit( m_panel40 );
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

	m_newSprite_ok_button = new wxButton( this, wxID_ANY, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer100->Add( m_newSprite_ok_button, 0, wxALL, 5 );

	m_newSprite_cancel_button = new wxButton( this, wxID_ANY, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer100->Add( m_newSprite_cancel_button, 0, wxALL, 5 );


	bSizer95->Add( bSizer100, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer95 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_spriteSheet_searchCtrl->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( NewSprite_Dialog::OnSearch ), NULL, this );
	m_newSprite_ok_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewSprite_Dialog::OnCreate ), NULL, this );
	m_newSprite_cancel_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewSprite_Dialog::OnCancel ), NULL, this );
}

NewSprite_Dialog::~NewSprite_Dialog()
{
}
