#include "NirvanaEditor_MainFrame.h"
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/arrstr.h>

#include "Nirvana_Project.h"
#include "NirvanaEditor_NewSprite_Dialog.h"



NirvanaEditor_MainFrame::NirvanaEditor_MainFrame( wxWindow* parent )
:
Nirvana_MainFrame( parent )
{
	project = new Nirvana_Project();

	tile_editor = new Nirvana_TileEditor(this, m_tileAnimation_tileSheet_panel, m_tileAnimation_tileFrames_panel,
											m_tileAnimation_preview_panel, m_tileMask_tileSheet_panel);

	tile_editor->setProject(project);

	tile_editor->getAnimationSheetControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());

	sprite_editor = new Nirvana_SpriteEditor(this, m_spriteAnimation_spriteSheet_panel, m_spriteAnimation_frame_panel,
												m_spriteAnimation_preview_panel, m_spriteCollision_edit_panel);

	sprite_editor->setProject(project);

	sprite_editor->getAnimationSheetControl()->update_events = true;

	m_spriteEdit_collisionShape_comboBox->Append(_("BOX"));
	m_spriteEdit_collisionShape_comboBox->Append(_("POLYGON"));
	m_spriteEdit_collisionShape_comboBox->Append(_("CIRCLE"));
}

void NirvanaEditor_MainFrame::OnProjectPropertiesTabChanged( wxAuiNotebookEvent& event )
{
}

void NirvanaEditor_MainFrame::OnMapEditToolsTabChanged( wxAuiNotebookEvent& event )
{
}

void NirvanaEditor_MainFrame::OnTileEditor_Edit_Changed( wxAuiNotebookEvent& event )
{
}

void NirvanaEditor_MainFrame::OnSpriteEditor_Edit_Changed( wxAuiNotebookEvent& event )
{
	int page_index = event.GetSelection();
	wxPanel* new_panel = (wxPanel*)m_spriteEdit_tools_auinotebook->GetPage(page_index);

	sprite_editor->stopEditor();

	if(new_panel == m_spriteEdit_spriteAnimation_panel)
	{
		sprite_editor->startEditor(0);
	}
	else if(new_panel == m_spriteEdit_spriteCollision_panel)
	{
		sprite_editor->startEditor(1);
	}
}

void NirvanaEditor_MainFrame::OnMainTabChanged( wxAuiNotebookEvent& event )
{
	int page_index = event.GetSelection();
	wxPanel* new_panel = (wxPanel*)m_editorMainTab_auinotebook->GetPage(page_index);

	switch(main_page_index)
	{
		case NIRVANA_MAIN_PAGE_INDEX_MAP:
		break;

		case NIRVANA_MAIN_PAGE_INDEX_TILE:
			tile_editor->stopEditor();
		break;

		case NIRVANA_MAIN_PAGE_INDEX_SPRITE:
			sprite_editor->stopEditor();
		break;
	}

	if(new_panel == m_mapEdit_panel)
	{
		main_page_index = NIRVANA_MAIN_PAGE_INDEX_MAP;
	}
	else if(new_panel == m_tileEdit_panel)
	{
		tile_editor->startEditor();

		main_page_index = NIRVANA_MAIN_PAGE_INDEX_TILE;
	}
	else if(new_panel == m_spriteEdit_panel)
	{
		sprite_editor->startEditor(sprite_editor->getEditorPageIndex());
		UpdateSpriteEditor();

		main_page_index = NIRVANA_MAIN_PAGE_INDEX_SPRITE;
	}
}

wxArrayString NirvanaEditor_MainFrame::getDirFileList(wxString dir_path, wxString wildcard)
{
	wxDir dir;
	wxString filename;
	wxString filespec = _T("*.*");

	//if(wildcard.compare(_(""))!=0)
	//	filespec = wildcard;

	wxArrayString files_list;

	if ( dir.Open( dir_path ) )
	{
		bool cont = dir.GetFirst(&filename, filespec, wxDIR_FILES);
		while ( cont )
		{
			files_list.Add( filename );
			cont = dir.GetNext(&filename);
		}
	}
	else
	{
		wxMessageBox(_("Error: Could not open dir: ") + dir_path);
	}

	files_list.Sort();

	return files_list;
}

void NirvanaEditor_MainFrame::OnTestButtonClick( wxCommandEvent& event )
{
	this->RefreshLayerProperties();
}

void NirvanaEditor_MainFrame::RefreshLayerProperties()
{
	LayerProperties_Sizer->Clear();

	wxStaticText* m_staticText43 = new wxStaticText( m_layerProperties_panel, wxID_ANY, _("0:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText43->Wrap( -1 );
	LayerProperties_Sizer->Add( m_staticText43, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxStaticLine* m_staticline10 = new wxStaticLine( m_layerProperties_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	LayerProperties_Sizer->Add( m_staticline10, 0, wxEXPAND | wxALL, 5 );

	wxBitmapButton* m_bpButton29 = new wxBitmapButton( m_layerProperties_panel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxBORDER_NONE );

	m_bpButton29->SetBitmap( wxBitmap( wxT("icons/up-arrow.png"), wxBITMAP_TYPE_ANY ) );
	LayerProperties_Sizer->Add( m_bpButton29, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxBitmapButton* m_bpButton30 = new wxBitmapButton( m_layerProperties_panel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxBORDER_NONE );

	m_bpButton30->SetBitmap( wxBitmap( wxT("icons/down-arrow.png"), wxBITMAP_TYPE_ANY ) );
	LayerProperties_Sizer->Add( m_bpButton30, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxStaticLine* m_staticline11 = new wxStaticLine( m_layerProperties_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	LayerProperties_Sizer->Add( m_staticline11, 0, wxEXPAND | wxALL, 5 );

	wxBitmapButton* m_bpButton31 = new wxBitmapButton( m_layerProperties_panel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxBORDER_NONE );

	m_bpButton31->SetBitmap( wxBitmap( wxT("icons/delete.png"), wxBITMAP_TYPE_ANY ) );
	LayerProperties_Sizer->Add( m_bpButton31, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxStaticLine* m_staticline12 = new wxStaticLine( m_layerProperties_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	LayerProperties_Sizer->Add( m_staticline12, 0, wxEXPAND | wxALL, 5 );

	wxStaticText* m_staticText45 = new wxStaticText( m_layerProperties_panel, wxID_ANY, _("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText45->Wrap( -1 );
	LayerProperties_Sizer->Add( m_staticText45, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxTextCtrl* m_textCtrl12 = new wxTextCtrl( m_layerProperties_panel, wxID_ANY, _("Tile Layer"), wxDefaultPosition, wxDefaultSize, 0 );
	LayerProperties_Sizer->Add( m_textCtrl12, 0, wxALL, 5 );

	wxStaticLine* m_staticline13 = new wxStaticLine( m_layerProperties_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	LayerProperties_Sizer->Add( m_staticline13, 0, wxEXPAND | wxALL, 5 );

	wxCheckBox* m_checkBox8 = new wxCheckBox( m_layerProperties_panel, wxID_ANY, _("Tile"), wxDefaultPosition, wxDefaultSize, 0 );
	LayerProperties_Sizer->Add( m_checkBox8, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	LayerProperties_Sizer->Add( 0, 0, 1, wxEXPAND, 5 );


	m_layerProperties_panel->SetSizer( LayerProperties_Sizer );
	m_layerProperties_panel->Layout();
	LayerProperties_Sizer->Fit( m_layerProperties_panel );
}




// ------- SPRITE EDITOR ----------------
void NirvanaEditor_MainFrame::UpdateSpriteEditor()
{
	int page_index = m_editorMainTab_auinotebook->GetSelection();
	wxPanel* current_panel = (wxPanel*)m_editorMainTab_auinotebook->GetPage(page_index);

	if(current_panel == m_spriteEdit_panel)
	{
		int tool_page_index = m_spriteEdit_tools_auinotebook->GetSelection();
		wxPanel* tool_panel = (wxPanel*)m_spriteEdit_tools_auinotebook->GetPage(tool_page_index);

		if(tool_panel == m_spriteEdit_spriteAnimation_panel)
		{
			sprite_editor->setAnimationView();
		}
		else if(tool_panel == m_spriteEdit_spriteCollision_panel)
		{
			// TODO
		}
	}
}

void NirvanaEditor_MainFrame::OnNewSpriteClicked( wxCommandEvent& event )
{
	sprite_editor->getAnimationSheetControl()->enable_update = false;
	NirvanaEditor_NewSprite_Dialog* dialog = new NirvanaEditor_NewSprite_Dialog(this);

	wxFileName gfx_path(project->getDir());
	gfx_path.AppendDir(_("gfx"));

	dialog->files = getDirFileList(gfx_path.GetAbsolutePath());

	dialog->refresh_list();

	dialog->ShowModal();

	sprite_editor->getAnimationSheetControl()->enable_update = true;

	project->createSprite(dialog->id_name, dialog->selected_file, dialog->frame_width, dialog->frame_height);

	m_spriteEdit_sprite_listBox->AppendAndEnsureVisible(dialog->id_name);
}

void NirvanaEditor_MainFrame::OnSpriteEdit_Sprite_Selected( wxCommandEvent& event )
{
	int selected_index = event.GetSelection();
	wxString sprite_name = m_spriteEdit_sprite_listBox->GetString(selected_index);

	sprite_editor->selectSprite(sprite_name);

	int spr_id = sprite_editor->getSelectedSprite();
	if(spr_id < 0)
		return;

	m_spriteEdit_spriteID_textCtrl->SetValue(sprite_name);

	m_spriteEdit_animation_listBox->Clear();

	sprite2D_obj n_sprite = project->getSprite(spr_id).object;

	//std::cout << "N_SPRT2: " << n_sprite.physics.offset_x << std::endl;

	for(int i = 0; i < n_sprite.animation.size(); i++)
	{
		m_spriteEdit_animation_listBox->AppendAndEnsureVisible(wxString(n_sprite.animation[i].name));
	}


	//Set Physics Stuff
	switch(n_sprite.physics.shape_type)
	{
		case SPRITE_SHAPE_BOX:
			m_spriteEdit_collisionShape_comboBox->SetSelection(0);
			m_spriteCollision_shape_simplebook->SetSelection(0);

			m_spriteEdit_collisionBox_X_spinCtrl->SetValue(n_sprite.physics.offset_x);
			m_spriteEdit_collisionBox_Y_spinCtrl->SetValue(n_sprite.physics.offset_y);
			m_spriteEdit_collisionBox_Width_spinCtrl->SetValue(n_sprite.physics.box_width);
			m_spriteEdit_collisionBox_Height_spinCtrl->SetValue(n_sprite.physics.box_height);
		break;

		case SPRITE_SHAPE_POLYGON:
			m_spriteEdit_collisionShape_comboBox->SetSelection(1);
			m_spriteCollision_shape_simplebook->SetSelection(1);

			if(m_spriteEdit_collisionPolygon_grid->GetNumberRows() > 0)
				m_spriteEdit_collisionPolygon_grid->DeleteRows(0, m_spriteEdit_collisionPolygon_grid->GetNumberRows());

			for(int i = 0; i < n_sprite.physics.points.size(); i++)
			{
				m_spriteEdit_collisionPolygon_grid->AppendRows();
				m_spriteEdit_collisionPolygon_grid->SetCellValue(i, 0, wxString::Format(_("%i"), (int)n_sprite.physics.points[i].X));
				m_spriteEdit_collisionPolygon_grid->SetCellValue(i, 1, wxString::Format(_("%i"), (int)n_sprite.physics.points[i].Y));
			}
		break;

		case SPRITE_SHAPE_CIRCLE:
			m_spriteEdit_collisionShape_comboBox->SetSelection(2);
			m_spriteCollision_shape_simplebook->SetSelection(2);

			m_spriteEdit_collisionCircle_X_spinCtrl->SetValue(n_sprite.physics.offset_x);
			m_spriteEdit_collisionCircle_Y_spinCtrl->SetValue(n_sprite.physics.offset_y);
			m_spriteEdit_collisionCircle_Radius_spinCtrl->SetValue(n_sprite.physics.radius);
		break;
	}
}

void NirvanaEditor_MainFrame::OnSpriteEdit_Animation_Selected( wxCommandEvent& event )
{
	int selected_index = event.GetSelection();
	wxString ani_name = m_spriteEdit_animation_listBox->GetString(selected_index);

	sprite_editor->selectAnimation(ani_name);

	int spr_id = sprite_editor->getSelectedSprite();
	int ani_id = sprite_editor->getSelectedAnimation();

	if(spr_id < 0 || spr_id >= project->getSpriteCount())
		return;

	if(ani_id < 0 || ani_id >= project->getSpriteNumAnimations(spr_id))
		return;

	m_spriteEdit_animationID_textCtrl->SetValue(ani_name);
	m_spriteEdit_numFrames_spinCtrl->SetValue(project->getSpriteNumAnimationFrames(spr_id, ani_id));
	m_spriteEdit_FPS_spinCtrl->SetValue(project->getSpriteAnimationFPS(spr_id, ani_id));
}

void NirvanaEditor_MainFrame::OnSpriteEdit_NewAnimation_Click( wxCommandEvent& event )
{
	int animation_id = sprite_editor->newAnimation();
	int spr_id = sprite_editor->getSelectedSprite();

	if(spr_id < 0 || spr_id >= project->getSpriteCount())
		return;

	sprite2D_obj n_sprite = project->getSprite(spr_id).object;
	if(animation_id < 0 || animation_id >= n_sprite.animation.size())
		return;

	m_spriteEdit_animation_listBox->AppendAndEnsureVisible(wxString(n_sprite.animation[animation_id].name));
}

void NirvanaEditor_MainFrame::OnSpriteEdit_DeleteAnimation_Click( wxCommandEvent& event )
{
	int spr_id = sprite_editor->getSelectedSprite();

	//sprite and animation bounds checks are done in deleteAnimation()
	sprite_editor->deleteAnimation();

	m_spriteEdit_animation_listBox->Clear();

	sprite2D_obj n_sprite = project->getSprite(spr_id).object;

	for(int i = 0; i < n_sprite.animation.size(); i++)
	{
		m_spriteEdit_animation_listBox->AppendAndEnsureVisible(wxString(n_sprite.animation[i].name));
	}
}

void NirvanaEditor_MainFrame::OnSpriteEdit_SpriteIDChanged( wxCommandEvent& event )
{
	int list_index = m_spriteEdit_sprite_listBox->GetSelection();

	if(list_index < 0 || list_index >= m_spriteEdit_sprite_listBox->GetCount())
		return;

	int spr_id = sprite_editor->getSelectedSprite();

	if(spr_id < 0 || spr_id >= project->getSpriteCount())
		return;

	wxString new_value = m_spriteEdit_spriteID_textCtrl->GetValue();

	if(new_value.Trim().length() == 0)
		new_value = _("WARNING: [MISSING ID]");

	m_spriteEdit_sprite_listBox->SetString(list_index, new_value);
	project->setSpriteName(spr_id, new_value.ToStdString());
}

void NirvanaEditor_MainFrame::OnSpriteEdit_AnimationIDChanged( wxCommandEvent& event )
{
	int list_index = m_spriteEdit_animation_listBox->GetSelection();

	if(list_index < 0 || list_index >= m_spriteEdit_animation_listBox->GetCount())
		return;

	int spr_id = sprite_editor->getSelectedSprite();

	if(spr_id < 0 || spr_id >= project->getSpriteCount())
		return;

	wxString new_value = m_spriteEdit_animationID_textCtrl->GetValue();

	if(new_value.Trim().length() == 0)
		new_value = _("WARNING: [MISSING ID]");

	m_spriteEdit_animation_listBox->SetString(list_index, new_value);
	project->setSpriteAnimationName(spr_id, list_index, new_value.ToStdString());
}

void NirvanaEditor_MainFrame::OnSpriteEdit_NumFramesChange( wxSpinEvent& event )
{
	int spr_id = sprite_editor->getSelectedSprite();

	if(spr_id < 0 || spr_id >= project->getSpriteCount())
		return;

	int ani_id = sprite_editor->getSelectedAnimation();

	if(ani_id < 0 || ani_id >= project->getSpriteNumAnimations(spr_id))
		return;

	int new_frame_count = event.GetValue();

	if(new_frame_count < 0 || new_frame_count >= m_spriteEdit_numFrames_spinCtrl->GetMax())
		return;

	project->setSpriteNumAnimationFrames(spr_id, ani_id, new_frame_count);
	sprite_editor->updateSpriteAnimation();
}

void NirvanaEditor_MainFrame::OnSpriteEdit_FPSChanged( wxSpinEvent& event )
{
	int spr_id = sprite_editor->getSelectedSprite();

	if(spr_id < 0 || spr_id >= project->getSpriteCount())
		return;

	int ani_id = sprite_editor->getSelectedAnimation();

	if(ani_id < 0 || ani_id >= project->getSpriteNumAnimations(spr_id))
		return;

	int new_fps = event.GetValue();

	if(new_fps < 0 || new_fps >= m_spriteEdit_FPS_spinCtrl->GetMax())
		return;

	project->setSpriteAnimationFPS(spr_id, ani_id, new_fps);
	sprite_editor->updateSpriteAnimation();
}

void NirvanaEditor_MainFrame::OnSpriteEdit_PreviousFrame_Click( wxCommandEvent& event )
{
	int spr_id = sprite_editor->getSelectedSprite();

	if(spr_id < 0 || spr_id >= project->getSpriteCount())
		return;

	int ani_id = sprite_editor->getSelectedAnimation();

	if(ani_id < 0 || ani_id >= project->getSpriteNumAnimations(spr_id))
		return;

	int new_offset = sprite_editor->getAnimationFrameControl()->scroll_offset_x - 64;

	sprite_editor->getAnimationFrameControl()->scroll_offset_x = new_offset;
}

void NirvanaEditor_MainFrame::OnSpriteEdit_NextFrame_Click( wxCommandEvent& event )
{
	int spr_id = sprite_editor->getSelectedSprite();

	if(spr_id < 0 || spr_id >= project->getSpriteCount())
		return;

	int ani_id = sprite_editor->getSelectedAnimation();

	if(ani_id < 0 || ani_id >= project->getSpriteNumAnimations(spr_id))
		return;

	int new_offset = sprite_editor->getAnimationFrameControl()->scroll_offset_x + 64;

	sprite_editor->getAnimationFrameControl()->scroll_offset_x = new_offset;
}

void NirvanaEditor_MainFrame::OnUpdateSpriteAnimationUI( wxUpdateUIEvent& event )
{
	int sheet_selected_frame = sprite_editor->getAnimationSheetControl()->selected_frame;
	int frame_selected_frame = sprite_editor->getAnimationFrameControl()->selected_frame;
	int spr_index = sprite_editor->getSelectedSprite();
	int ani_index = sprite_editor->getSelectedAnimation();

	if(spr_index >= 0 && spr_index < project->getSpriteCount())
	{
		//Collision stuff
		if(sprite_editor->getCollisionControl()->collision_object_modified)
		{
			project->setSpritePhysics(spr_index, sprite_editor->getCollisionControl()->collision_physics_obj);
			sprite_editor->getCollisionControl()->collision_object_modified = false;

			sprite2D_physics_obj physics = project->getSpritePhysics(spr_index);

			switch(physics.shape_type)
			{
				case SPRITE_SHAPE_BOX:
					m_spriteEdit_collisionBox_X_spinCtrl->SetValue(physics.offset_x);
					m_spriteEdit_collisionBox_Y_spinCtrl->SetValue(physics.offset_y);
					m_spriteEdit_collisionBox_Width_spinCtrl->SetValue(physics.box_width);
					m_spriteEdit_collisionBox_Height_spinCtrl->SetValue(physics.box_height);
				break;

				case SPRITE_SHAPE_POLYGON:
					if(m_spriteEdit_collisionPolygon_grid->GetNumberRows() > 0)
						m_spriteEdit_collisionPolygon_grid->DeleteRows(0, m_spriteEdit_collisionPolygon_grid->GetNumberRows());

					for(int i = 0; i < physics.points.size(); i++)
					{
						m_spriteEdit_collisionPolygon_grid->AppendRows();
						m_spriteEdit_collisionPolygon_grid->SetCellValue(i, 0, wxString::Format(_("%i"), (int)physics.points[i].X));
						m_spriteEdit_collisionPolygon_grid->SetCellValue(i, 1, wxString::Format(_("%i"), (int)physics.points[i].Y));
					}
				break;

				case SPRITE_SHAPE_CIRCLE:
					m_spriteEdit_collisionCircle_X_spinCtrl->SetValue(physics.offset_x);
					m_spriteEdit_collisionCircle_Y_spinCtrl->SetValue(physics.offset_y);
					m_spriteEdit_collisionCircle_Radius_spinCtrl->SetValue(physics.radius);
				break;
			}
		}

		//Animation stuff
		if(ani_index >= 0 && ani_index < project->getSpriteNumAnimations(spr_index))
		{
			if(frame_selected_frame >= 0 && frame_selected_frame < project->getSpriteNumAnimationFrames(spr_index, ani_index))
			{
				if(sheet_selected_frame >= 0) //Its set to -1 if outside the sprite sheet so I am not wasting my time checking here. Also, I am fucking lazy.
				{
					std::cout << "Set frames: " << frame_selected_frame << " -> " << sheet_selected_frame  << std::endl;
					project->setSpriteAnimationFrame(spr_index, ani_index, frame_selected_frame, sheet_selected_frame);
					sprite_editor->updateSpriteAnimation();
				}
			}
		}
	}

	sprite_editor->getAnimationSheetControl()->selected_frame = -1;
}

void NirvanaEditor_MainFrame::OnSpriteEdit_PlayPreviewClick( wxCommandEvent& event )
{
	sprite_editor->getAnimationPreviewControl()->setSpriteAnimation(sprite_editor->getAnimationPreviewControl()->spriteEdit_selected_sprite,
																	sprite_editor->getSelectedAnimation(), -1);
	sprite_editor->updateSpriteAnimation();
}

void NirvanaEditor_MainFrame::OnSpriteEdit_StopPreviewClick( wxCommandEvent& event )
{
	sprite_editor->getAnimationPreviewControl()->setSpriteAnimation(sprite_editor->getAnimationPreviewControl()->spriteEdit_selected_sprite,
																	0, 0);
	sprite_editor->updateSpriteAnimation();
}

void NirvanaEditor_MainFrame::OnEnterSpriteAnimationSheet( wxMouseEvent& event )
{
	//std::cout << "ENTER" << std::endl;
	sprite_editor->getAnimationSheetControl()->stage_window_isActive = true;
}

void NirvanaEditor_MainFrame::OnLeaveSpriteAnimationSheet( wxMouseEvent& event )
{
	sprite_editor->getAnimationSheetControl()->stage_window_isActive = false;
	//std::cout << "LEAVE" << std::endl;
}


void NirvanaEditor_MainFrame::OnSpriteAnimationSheetSize( wxSizeEvent& event )
{
}



// SPRITE COLLISION
void NirvanaEditor_MainFrame::OnSpriteEdit_ShapeSelect( wxCommandEvent& event )
{
	int shape_index = event.GetSelection();

	if(shape_index < 0 || shape_index >= 3)
		return;

	m_spriteCollision_shape_simplebook->SetSelection(shape_index);

	m_spriteEdit_collisionBox_X_spinCtrl->SetValue(0);
	m_spriteEdit_collisionBox_Y_spinCtrl->SetValue(0);
	m_spriteEdit_collisionBox_Width_spinCtrl->SetValue(0);
	m_spriteEdit_collisionBox_Height_spinCtrl->SetValue(0);

	if(m_spriteEdit_collisionPolygon_grid->GetNumberRows() > 0)
		m_spriteEdit_collisionPolygon_grid->DeleteRows(0, m_spriteEdit_collisionPolygon_grid->GetNumberRows());

	m_spriteEdit_collisionCircle_X_spinCtrl->SetValue(0);
	m_spriteEdit_collisionCircle_Y_spinCtrl->SetValue(0);
	m_spriteEdit_collisionCircle_Radius_spinCtrl->SetValue(0);

	int spr_id = sprite_editor->getSelectedSprite();
	if(spr_id < 0)
		return;

	sprite2D_obj n_sprite = project->getSprite(spr_id).object;

	//Set Physics Stuff
	switch(shape_index+1)
	{
		case SPRITE_SHAPE_BOX:
			project->setSpriteCollision_Shape(spr_id, SPRITE_SHAPE_BOX);
		break;

		case SPRITE_SHAPE_POLYGON:
			project->setSpriteCollision_Shape(spr_id, SPRITE_SHAPE_POLYGON);
		break;

		case SPRITE_SHAPE_CIRCLE:
			project->setSpriteCollision_Shape(spr_id, SPRITE_SHAPE_CIRCLE);
		break;
	}

	//Set Physics Stuff
	switch(n_sprite.physics.shape_type)
	{
		case SPRITE_SHAPE_BOX:
			m_spriteEdit_collisionBox_X_spinCtrl->SetValue(n_sprite.physics.offset_x);
			m_spriteEdit_collisionBox_Y_spinCtrl->SetValue(n_sprite.physics.offset_y);
			m_spriteEdit_collisionBox_Width_spinCtrl->SetValue(n_sprite.physics.box_width);
			m_spriteEdit_collisionBox_Height_spinCtrl->SetValue(n_sprite.physics.box_height);
		break;

		case SPRITE_SHAPE_POLYGON:
			if(m_spriteEdit_collisionPolygon_grid->GetNumberRows() > 0)
				m_spriteEdit_collisionPolygon_grid->DeleteRows(0, m_spriteEdit_collisionPolygon_grid->GetNumberRows());

			for(int i = 0; i < n_sprite.physics.points.size(); i++)
			{
				m_spriteEdit_collisionPolygon_grid->AppendRows();
				m_spriteEdit_collisionPolygon_grid->SetCellValue(i, 0, wxString::Format(_("%i"), (int)n_sprite.physics.points[i].X));
				m_spriteEdit_collisionPolygon_grid->SetCellValue(i, 1, wxString::Format(_("%i"), (int)n_sprite.physics.points[i].Y));
			}
		break;

		case SPRITE_SHAPE_CIRCLE:
			m_spriteEdit_collisionCircle_X_spinCtrl->SetValue(n_sprite.physics.offset_x);
			m_spriteEdit_collisionCircle_Y_spinCtrl->SetValue(n_sprite.physics.offset_y);
			m_spriteEdit_collisionCircle_Radius_spinCtrl->SetValue(n_sprite.physics.radius);
		break;
	}

	sprite_editor->getCollisionControl()->collision_physics_obj = project->getSpritePhysics(sprite_editor->getSelectedSprite());
}

void NirvanaEditor_MainFrame::OnSpriteEdit_Collision_Select_Click( wxCommandEvent& event )
{
	sprite_editor->getCollisionControl()->collision_tool = COLLISION_TOOL_SELECT;
}

void NirvanaEditor_MainFrame::OnSpriteEdit_Collision_BoxSelect_Click( wxCommandEvent& event )
{
	sprite_editor->getCollisionControl()->collision_tool = COLLISION_TOOL_BOX_SELECT;
}

void NirvanaEditor_MainFrame::OnSpriteEdit_Collision_Move_Click( wxCommandEvent& event )
{
	sprite_editor->getCollisionControl()->collision_tool = COLLISION_TOOL_MOVE;
}

void NirvanaEditor_MainFrame::OnSpriteEdit_Collision_Draw_Click( wxCommandEvent& event )
{
	sprite_editor->getCollisionControl()->collision_tool = COLLISION_TOOL_DRAW;
}

void NirvanaEditor_MainFrame::OnSpriteEdit_collisionBox_X_spinCtrl( wxSpinEvent& event )
{
	int spr_id = sprite_editor->getSelectedSprite();
	if(spr_id < 0)
		return;

	project->setSpriteCollision_OffsetX(spr_id, event.GetValue());
	sprite_editor->getCollisionControl()->collision_physics_obj = project->getSpritePhysics(sprite_editor->getSelectedSprite());
}

void NirvanaEditor_MainFrame::OnSpriteEdit_collisionBox_Y_spinCtrl( wxSpinEvent& event )
{
	int spr_id = sprite_editor->getSelectedSprite();
	if(spr_id < 0)
		return;

	project->setSpriteCollision_OffsetY(spr_id, event.GetValue());
	sprite_editor->getCollisionControl()->collision_physics_obj = project->getSpritePhysics(sprite_editor->getSelectedSprite());
}

void NirvanaEditor_MainFrame::OnSpriteEdit_collisionBox_Width_spinCtrl( wxSpinEvent& event )
{
	int spr_id = sprite_editor->getSelectedSprite();
	if(spr_id < 0)
		return;

	project->setSpriteCollisionBox_Width(spr_id, event.GetValue());
	sprite_editor->getCollisionControl()->collision_physics_obj = project->getSpritePhysics(sprite_editor->getSelectedSprite());
}

void NirvanaEditor_MainFrame::OnSpriteEdit_collisionBox_Height_spinCtrl( wxSpinEvent& event )
{
	int spr_id = sprite_editor->getSelectedSprite();
	if(spr_id < 0)
		return;

	project->setSpriteCollisionBox_Height(spr_id, event.GetValue());
	sprite_editor->getCollisionControl()->collision_physics_obj = project->getSpritePhysics(sprite_editor->getSelectedSprite());
}
