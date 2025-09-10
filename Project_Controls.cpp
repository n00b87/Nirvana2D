#include "NirvanaEditor_MainFrame.h"
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/arrstr.h>

#include "NirvanaEditor_NewStage_Dialog.h"
#include "NirvanaEditor_NewLayer_Dialog.h"
#include "NirvanaEditor_DeleteStage_Dialog.h"
#include "NirvanaEditor_StageProperties_Dialog.h"
#include "NirvanaEditor_SetCamera_Dialog.h"
#include "NirvanaEditor_NewProject_Dialog.h"
#include "Nirvana_Project.h"

void NirvanaEditor_MainFrame::newProject(wxFileName project_path, wxString project_name, bool create_flag)
{
	if(!editor_init)
		return;

	editor_init = false;
	int current_main_tab = m_editorMainTab_auinotebook->GetSelection();
	int current_project_tab = m_projectManager_auinotebook->GetSelection();
	int current_mapEditTools_tab = m_mapEdit_layerObjectTools_auinotebook->GetSelection();
	int current_tileEdit_tab = m_tileEdit_tools_auinotebook->GetSelection();
	int current_spriteEdit_tab = m_spriteEdit_tools_auinotebook->GetSelection();

	wxString p_dir = project_path.GetFullPath();

	wxFileName fname = project_path;

	if(create_flag)
		fname.AppendDir(project_name);

	if(!wxDirExists(fname.GetAbsolutePath()))
	{
		wxMkdir(fname.GetAbsolutePath());
	}

	if(!wxDirExists(fname.GetAbsolutePath()))
	{
		wxMessageBox(_("ERROR: Failed to create project"));
		return;
	}

	wxFileName tile_path = fname;
	tile_path.AppendDir(default_tile_path);

	wxFileName sprite_path = fname;
	sprite_path.AppendDir(default_sprite_path);

	wxFileName bkg_path = fname;
	bkg_path.AppendDir(default_bkg_path);

	wxFileName stage_path = fname;
	stage_path.AppendDir(default_stage_path);

	if(!wxDirExists(tile_path.GetAbsolutePath()))
		wxMkdir(tile_path.GetAbsolutePath());

	if(!wxDirExists(sprite_path.GetAbsolutePath()))
		wxMkdir(sprite_path.GetAbsolutePath());

	if(!wxDirExists(bkg_path.GetAbsolutePath()))
		wxMkdir(bkg_path.GetAbsolutePath());

	if(!wxDirExists(stage_path.GetAbsolutePath()))
		wxMkdir(stage_path.GetAbsolutePath());


	wxFileName pfile_path = fname;
	pfile_path.SetFullName(project_name.Trim() + _(".nvprj"));

	if(!wxFileExists(pfile_path.GetAbsolutePath()))
	{
		wxFile pfile(pfile_path.GetAbsolutePath(), wxFile::write);

		if(pfile.IsOpened())
		{
			pfile.Write(_("Nirvana version=") + _(NIRVANA_VERSION_STRING) + _(";\n"));
			pfile.Write(_("Project name=\"") + project_name + _("\";\n"));
			pfile.Write(_("MEDIA_PATH ") + _("bkg=\"") + default_bkg_path + _("\" ") +
										   _("tile=\"") + default_tile_path + _("\" ") +
										   _("stage=\"") + default_stage_path + _("\" ") +
										   _("sprite=\"") + default_sprite_path + _("\";\n"));
			pfile.Close();
		}
	}


	map_editor->getMapViewControl()->clearStage();
	map_editor->getMapViewControl()->mapEdit_layerType = -1;
	map_editor->getTileSelectControl()->mapEdit_layerType = -1;

	map_editor->getMapViewControl()->current_sheet_image = -1;
	map_editor->getMapViewControl()->scroll_offset_x = 0;
	map_editor->getMapViewControl()->scroll_offset_y = 0;

	map_editor->getTileSelectControl()->current_sheet_image = -1;
	map_editor->getTileSelectControl()->scroll_offset_x = 0;
	map_editor->getTileSelectControl()->scroll_offset_y = 0;


	map_editor->selectStage(-1);

	map_editor->selectLayer(-1);

	map_editor->selectShape(-1);

	map_editor->selectSprite(-1);

	if(project)
	{
		delete project;
		project = NULL;
	}

	project = new Nirvana_Project();

	project->active = true;

	project->project_filename_obj = pfile_path;
	project->project_name = project_name.Trim().ToStdString();
	project->bkg_path = default_bkg_path;
	project->tile_path = default_tile_path;
	project->sprite_path = default_sprite_path;

	map_editor->getMapViewControl()->project = project;
	map_editor->getTileSelectControl()->project = project;
	map_editor->setProject(project);

	tile_editor->getAnimationFrameControl()->project = project;
	tile_editor->getAnimationSheetControl()->project = project;
	tile_editor->getAnimationPreviewControl()->project = project;
	tile_editor->getMaskSheetControl()->project = project;
	tile_editor->setProject(project);

	sprite_editor->getAnimationFrameControl()->project = project;
	sprite_editor->getAnimationSheetControl()->project = project;
	sprite_editor->getAnimationPreviewControl()->project = project;
	sprite_editor->getCollisionControl()->project = project;
	sprite_editor->setProject(project);

	m_activeLayer_comboBox->Clear();
	m_mapEdit_stageName_staticText->SetLabelText(_("STAGE: [NA]"));
	m_project_treeCtrl->DeleteChildren(project_root_treeItem);

	//Layer Tab
	m_layerVisible_checkList->Clear();
	m_layerName_textCtrl->SetValue(_(""));
	m_mapEdit_layerHScroll_spinCtrlDouble->SetValue(0.0);
	m_mapEdit_layerVScroll_spinCtrlDouble->SetValue(0.0);
	m_mapEdit_layerAlpha_spinCtrl->SetValue(0);


	wxPGProperty * sprite_id = m_mapEdit_sprite_propertyGrid->GetProperty(_("sprite_id"));
	wxPGProperty * sprite_body_type = m_mapEdit_sprite_propertyGrid->GetProperty(_("body_type"));
	wxPGProperty * sprite_animation = m_mapEdit_sprite_propertyGrid->GetProperty(_("animation"));
	wxPGProperty * sprite_pos_x = m_mapEdit_sprite_propertyGrid->GetProperty(_("position_x"));
	wxPGProperty * sprite_pos_y = m_mapEdit_sprite_propertyGrid->GetProperty(_("position_y"));
	wxPGProperty * sprite_angle = m_mapEdit_sprite_propertyGrid->GetProperty(_("angle"));
	wxPGProperty * sprite_scale_x = m_mapEdit_sprite_propertyGrid->GetProperty(_("scale_x"));
	wxPGProperty * sprite_scale_y = m_mapEdit_sprite_propertyGrid->GetProperty(_("scale_y"));
	wxPGProperty * sprite_alpha = m_mapEdit_sprite_propertyGrid->GetProperty(_("alpha"));
	wxPGProperty * sprite_visible = m_mapEdit_sprite_propertyGrid->GetProperty(_("visible"));


	sprite_id->SetValueFromString(_(""));
	sprite_body_type->SetChoiceSelection(0);
	sprite_animation->SetChoices(wxPGChoices());
	sprite_pos_x->SetValue( 0 );
	sprite_pos_y->SetValue( 0 );
	sprite_angle->SetValue( 0 );
	sprite_scale_x->SetValue( 0 );
	sprite_scale_y->SetValue( 0 );
	sprite_alpha->SetValueFromInt( 0 );
	sprite_visible->SetValue( false );

	m_mapEdit_layerSprite_listBox->Clear();
	m_mapEdit_collisionShape_listBox->Clear();

	m_mapEdit_shapeName_textCtrl->SetValue(_(""));

	m_mapEdit_shapeEdit_simplebook->SetSelection(0);

	m_mapEdit_canvasRenderSetting_comboBox->Clear();
	m_mapEdit_canvasImage_comboBox->Clear();

	m_mapEdit_layerSprite_listBox->Clear();
	m_mapEdit_collisionShape_listBox->Clear();

	//Tile Editor
	m_tileEdit_tileset_listBox->Clear();
	m_tileSize_staticText->SetLabelText(_("WIDTH x HEIGHT"));

	tile_editor->getAnimationSheetControl()->clear_flag = true;
	tile_editor->getAnimationSheetControl()->current_sheet_image = -1;
	tile_editor->getAnimationSheetControl()->tileEdit_selected_tileset = -1;
	tile_editor->getAnimationSheetControl()->tileEdit_selected_frame_frame = -1;
	tile_editor->getAnimationSheetControl()->tileEdit_selected_sheet_frame = -1;
	tile_editor->getAnimationSheetControl()->tileEdit_selected_tile = -1;
	tile_editor->getAnimationSheetControl()->tileEdit_mask_set = false;
	tile_editor->getAnimationSheetControl()->tileEdit_Sheet_Update = false;
	tile_editor->getAnimationSheetControl()->scroll_offset_x = 0;
	tile_editor->getAnimationSheetControl()->scroll_offset_y = 0;


	tile_editor->getAnimationFrameControl()->clear_flag = true;
	tile_editor->getAnimationFrameControl()->current_sheet_image = -1;
	tile_editor->getAnimationFrameControl()->tileEdit_selected_tileset = -1;
	tile_editor->getAnimationFrameControl()->tileEdit_selected_frame_frame = -1;
	tile_editor->getAnimationFrameControl()->tileEdit_selected_sheet_frame = -1;
	tile_editor->getAnimationFrameControl()->tileEdit_selected_tile = -1;
	tile_editor->getAnimationFrameControl()->tileEdit_mask_set = false;
	tile_editor->getAnimationFrameControl()->tileEdit_Sheet_Update = false;
	tile_editor->getAnimationFrameControl()->scroll_offset_x = 0;
	tile_editor->getAnimationFrameControl()->scroll_offset_y = 0;

	tile_editor->getAnimationPreviewControl()->clear_flag = true;
	tile_editor->getAnimationPreviewControl()->tileEdit_selected_tileset = -1;
	tile_editor->getAnimationPreviewControl()->tileEdit_selected_frame_frame = -1;
	tile_editor->getAnimationPreviewControl()->tileEdit_selected_sheet_frame = -1;
	tile_editor->getAnimationPreviewControl()->tileEdit_selected_tile = -1;
	tile_editor->getAnimationPreviewControl()->tileEdit_mask_set = false;
	tile_editor->getAnimationPreviewControl()->tileEdit_Sheet_Update = false;
	tile_editor->getAnimationPreviewControl()->tileEdit_play_preview = false;
	tile_editor->getAnimationPreviewControl()->scroll_offset_x = 0;
	tile_editor->getAnimationPreviewControl()->scroll_offset_y = 0;


	tile_editor->getMaskSheetControl()->clear_flag = true;
	tile_editor->getMaskSheetControl()->current_sheet_image = -1;
	tile_editor->getMaskSheetControl()->tileEdit_selected_tileset = -1;
	tile_editor->getMaskSheetControl()->tileEdit_selected_frame_frame = -1;
	tile_editor->getMaskSheetControl()->tileEdit_selected_sheet_frame = -1;
	tile_editor->getMaskSheetControl()->tileEdit_selected_tile = -1;
	tile_editor->getMaskSheetControl()->tileEdit_mask_set = false;
	tile_editor->getMaskSheetControl()->tileEdit_Sheet_Update = false;
	tile_editor->getMaskSheetControl()->tileEdit_play_preview = false;
	tile_editor->getMaskSheetControl()->scroll_offset_x = 0;
	tile_editor->getMaskSheetControl()->scroll_offset_y = 0;

	m_tileEdit_numFrames_spinCtrl->SetValue(0);
	m_tileEdit_FPS_spinCtrl->SetValue(0);
	m_tileEdit_tilesetID_textCtrl->SetValue(_(""));
	m_tileEdit_mask_listBox->Clear();
	m_tileEdit_maskID_textCtrl->SetValue(_(""));

	//Sprite Editor
	m_spriteEdit_frameSize_staticText->SetLabelText(_("WIDTH x HEIGHT"));
	m_spriteEdit_sprite_listBox->Clear();
	m_spriteEdit_animation_listBox->Clear();
	m_spriteEdit_spriteID_textCtrl->SetValue(_(""));
	m_spriteEdit_animationID_textCtrl->SetValue(_(""));
	m_spriteEdit_numFrames_spinCtrl->SetValue(0);
	m_spriteEdit_FPS_spinCtrl->SetValue(0);

	m_spriteEdit_collisionShape_comboBox->SetSelection(0);
	m_spriteCollision_shape_simplebook->SetSelection(0);
	m_spriteEdit_collisionBox_X_spinCtrl->SetValue(0);
	m_spriteEdit_collisionBox_Y_spinCtrl->SetValue(0);
	m_spriteEdit_collisionBox_Width_spinCtrl->SetValue(0);
	m_spriteEdit_collisionBox_Height_spinCtrl->SetValue(0);


	sprite_editor->getAnimationSheetControl()->clear_flag = true;
	sprite_editor->getAnimationSheetControl()->current_sheet_image = -1;
	sprite_editor->getAnimationSheetControl()->spriteEdit_selected_animation = -1;
	sprite_editor->getAnimationSheetControl()->spriteEdit_selected_frame_frame = -1;
	sprite_editor->getAnimationSheetControl()->spriteEdit_selected_sheet_frame = -1;
	sprite_editor->getAnimationSheetControl()->spriteEdit_selected_sprite = -1;
	sprite_editor->getAnimationSheetControl()->scroll_offset_x = 0;
	sprite_editor->getAnimationSheetControl()->scroll_offset_y = 0;


	sprite_editor->getAnimationFrameControl()->clear_flag = true;
	sprite_editor->getAnimationFrameControl()->current_sheet_image = -1;
	sprite_editor->getAnimationFrameControl()->spriteEdit_selected_animation = -1;
	sprite_editor->getAnimationFrameControl()->spriteEdit_selected_frame_frame = -1;
	sprite_editor->getAnimationFrameControl()->spriteEdit_selected_sheet_frame = -1;
	sprite_editor->getAnimationFrameControl()->spriteEdit_selected_sprite = -1;
	sprite_editor->getAnimationFrameControl()->scroll_offset_x = 0;
	sprite_editor->getAnimationFrameControl()->scroll_offset_y = 0;



	if(sprite_editor->getAnimationPreviewControl()->spriteExists(sprite_editor->getAnimationPreviewControl()->spriteEdit_selected_sprite))
		sprite_editor->getAnimationPreviewControl()->deleteSprite(sprite_editor->getAnimationPreviewControl()->spriteEdit_selected_sprite);


	sprite_editor->getAnimationPreviewControl()->clear_flag = true;
	sprite_editor->getAnimationPreviewControl()->current_sheet_image = -1;
	sprite_editor->getAnimationPreviewControl()->spriteEdit_selected_animation = -1;
	sprite_editor->getAnimationPreviewControl()->spriteEdit_selected_frame_frame = -1;
	sprite_editor->getAnimationPreviewControl()->spriteEdit_selected_sheet_frame = -1;
	sprite_editor->getAnimationPreviewControl()->spriteEdit_selected_sprite = -1;
	sprite_editor->getAnimationPreviewControl()->scroll_offset_x = 0;
	sprite_editor->getAnimationPreviewControl()->scroll_offset_y = 0;


	sprite_editor->getCollisionControl()->clear_flag = true;
	sprite_editor->getCollisionControl()->current_sheet_image = -1;
	sprite_editor->getCollisionControl()->spriteEdit_selected_animation = -1;
	sprite_editor->getCollisionControl()->spriteEdit_selected_frame_frame = -1;
	sprite_editor->getCollisionControl()->spriteEdit_selected_sheet_frame = -1;
	sprite_editor->getCollisionControl()->spriteEdit_selected_sprite = -1;
	sprite_editor->getCollisionControl()->scroll_offset_x = 0;
	sprite_editor->getCollisionControl()->scroll_offset_y = 0;


	m_projectManager_auinotebook->SetSelection(current_project_tab);

	m_mapEdit_layerObjectTools_auinotebook->SetSelection(current_mapEditTools_tab);

	m_tileEdit_tools_auinotebook->SetSelection(current_tileEdit_tab);

	m_spriteEdit_tools_auinotebook->SetSelection(current_spriteEdit_tab);

	m_editorMainTab_auinotebook->SetSelection(current_main_tab);


	editor_init = true;
}

void NirvanaEditor_MainFrame::OnNewProject( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	NirvanaEditor_NewProject_Dialog* dialog = new NirvanaEditor_NewProject_Dialog(this);

	dialog->ShowModal();

	if(!dialog->create_flag)
		return;

	newProject(dialog->project_path, dialog->project_name);

	this->SetTitle(wxString(project->project_name) + _(" - Nirvana2D"));

	wxFileName studio_project_path = dialog->project_path;


	studio_project_path.AppendDir(dialog->project_name);


	studio_project_path.SetFullName(dialog->project_name + _(".rcprj"));





	if(!studio_project_path.Exists())
	{
		wxFile pfile(studio_project_path.GetAbsolutePath(), wxFile::write);

		if(pfile.IsOpened())
		{
			pfile.Write(_("RCBASIC_STUDIO:2.0\n"));
			pfile.Write(_("PROJECT_NAME:") + dialog->project_name + _("\n"));
			pfile.Write(_("PROJECT_MAIN:main.bas\n"));
			pfile.Write(_("AUTHOR:Nirvana2D\n"));
			pfile.Write(_("WEBSITE:http://www.rcbasic.com\n"));
			pfile.Write(_("DESCRIPTION:Nirvana2D Project\n"));
			pfile.Write(_("SOURCE_REL:main.bas\n"));
			pfile.Write(_("SOURCE_REL:nirvana.bas\n"));
			pfile.Write(_("SOURCE_REL:nirvana_constants.bas\n"));
			pfile.Write(_("SOURCE_REL:nirvana_spriteDef.bas\n"));
			pfile.Write(_("SOURCE_REL:nirvana_stage.bas\n"));
			pfile.Write(_("SOURCE_REL:nirvana_tileset.bas\n"));

			pfile.Close();
		}

		wxFileName template_path(wxStandardPaths::Get().GetExecutablePath());
		template_path.AppendDir(_("export"));
		template_path.SetFullName(_("template.bas"));

		wxFileName template_tgt_path = dialog->project_path;
		template_tgt_path.AppendDir(dialog->project_name);
		template_tgt_path.SetFullName(_("main.bas"));

		if(!template_tgt_path.Exists())
            wxCopyFile(template_path.GetAbsolutePath(), template_tgt_path.GetAbsolutePath());
	}
}


wxFileName NirvanaEditor_MainFrame::openFileDialog(wxString title, wxString default_wildcard, int flag)
{
	wxFileDialog openFileDialog(this, title, "", "", default_wildcard, flag);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return wxFileName();     // the user changed idea...

    wxFileName fname(openFileDialog.GetPath());
    return fname;
}

bool NirvanaEditor_MainFrame::loadProject(wxFileName project_file)
{
	if(!editor_init)
		return false;

	wxFile pfile(project_file.GetAbsolutePath(), wxFile::read);
	wxString p_data = _("");

	if(pfile.IsOpened())
	{
		pfile.ReadAll(&p_data);

		pfile.Close();
	}
	else
		return false;


	std::vector<nirvana_project_file_obj> p_cmd = project->getParams(p_data);

	for(int i = 0; i < p_cmd.size(); i++)
	{
		if(p_cmd[i].dict.size() == 0)
			continue;

		if(p_cmd[i].dict[0].key.compare(_("PROJECT"))==0)
		{
			for(int obj_index = 1; obj_index < p_cmd[i].dict.size(); obj_index++)
			{
				if(p_cmd[i].dict[obj_index].key.compare(_("name"))==0)
				{
					project->project_name = p_cmd[i].dict[obj_index].val.ToStdString();
				}
			}
		}
		else if(p_cmd[i].dict[0].key.compare(_("MEDIA_PATH"))==0)
		{
			for(int obj_index = 1; obj_index < p_cmd[i].dict.size(); obj_index++)
			{
				if(p_cmd[i].dict[obj_index].key.compare(_("bkg"))==0)
				{
					project->bkg_path = p_cmd[i].dict[obj_index].val.ToStdString();
				}
				else if(p_cmd[i].dict[obj_index].key.compare(_("tile"))==0)
				{
					project->tile_path = p_cmd[i].dict[obj_index].val.ToStdString();
				}
				else if(p_cmd[i].dict[obj_index].key.compare(_("stage"))==0)
				{
					project->stage_path = p_cmd[i].dict[obj_index].val.ToStdString();
				}
				else if(p_cmd[i].dict[obj_index].key.compare(_("sprite"))==0)
				{
					project->sprite_path = p_cmd[i].dict[obj_index].val.ToStdString();
				}
			}
		}
		else if(p_cmd[i].dict[0].key.compare(_("SPRITE"))==0)
		{
			for(int obj_index = 1; obj_index < p_cmd[i].dict.size(); obj_index++)
			{
				if(p_cmd[i].dict[obj_index].key.compare(_("file"))==0)
				{
					int sprite_index = project->loadSpriteDefinition(p_cmd[i].dict[obj_index].val);
					//std::cout << "SPRITE_LOAD: " << p_cmd[i].dict[obj_index].val.ToStdString() << " ->  index = " << sprite_index << std::endl;

					if(sprite_index >= 0)
						m_spriteEdit_sprite_listBox->AppendAndEnsureVisible(project->sprite_base[sprite_index].sprite_name);
				}
			}
		}
		else if(p_cmd[i].dict[0].key.compare(_("TILESET"))==0)
		{
			for(int obj_index = 1; obj_index < p_cmd[i].dict.size(); obj_index++)
			{
				if(p_cmd[i].dict[obj_index].key.compare(_("file"))==0)
				{
					int tset_index = project->loadTileset(p_cmd[i].dict[obj_index].val);

					if(tset_index >= 0)
						m_tileEdit_tileset_listBox->AppendAndEnsureVisible(project->tileset[tset_index].tileset_name);
					//std::cout << "SPRITE_LOAD: " << p_cmd[i].dict[obj_index].val.ToStdString() << " ->  index = " << sprite_index << std::endl;
				}
			}
		}
		else if(p_cmd[i].dict[0].key.compare(_("STAGE"))==0)
		{
			for(int obj_index = 1; obj_index < p_cmd[i].dict.size(); obj_index++)
			{
				if(p_cmd[i].dict[obj_index].key.compare(_("file"))==0)
				{
					int stage_index = project->loadStage(p_cmd[i].dict[obj_index].val);

					if(stage_index >= 0)
					{
						//project->setStageSize(stage_index, dialog->width_in_tiles, dialog->height_in_tiles);
						wxTreeItemId stage_item = m_project_treeCtrl->AppendItem(project_root_treeItem, wxString(project->stages[stage_index].stage_name), stage_tree_stageImage);
						stage_treeItem.push_back(stage_item);
					}
				}
			}
		}

	}

	#ifdef _WIN32
	for(int stage_index = 0; stage_index < project->stages.size(); stage_index++)
	{
	    for(int layer_index = 0; layer_index < project->stages[stage_index].layers.size(); layer_index++)
        {
            for(int t_row = 0; t_row < project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows.size(); t_row++)
            {
                bool t_check = false;
                for(int t_col = 0; t_col < project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows[t_row].tile.size(); t_col++)
                {
                    if(project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows[t_row].tile[t_col] >= 0)
                    {
                        std::cout << "TILE CHECK: " << project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows[t_row].tile[t_col] << std::endl; // I have to touch the array once because of MinGW's bullshit
                        return true;
                    }
                }
            }
        }
	}
	#endif // _WIN32

	//std::cout << "ABSOLUTE CHECK: " << project->stages[0].layers[1].layer_map.tile_map.rows[9].tile[3] << std::endl;


	return true;
}

void NirvanaEditor_MainFrame::OnOpenProject( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	PreDialog();
	wxFileName project_fname = openFileDialog(_("Open Project"), _("Nirvana2D Project (*.nvprj)|*.nvprj"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	PostDialog();

	if(project_fname.GetFullPath().compare("")==0)
		return;

	wxFileName project_path = project_fname;
	project_path.SetFullName(_(""));

	wxString project_name = project_fname.GetName();


	newProject(project_path, project_name, false); // Needed to clear all the UI stuff and create empty project

	if(!loadProject(project_fname))
	{
		wxMessageBox(_("Could not load project"));
		return;
	}


	this->SetTitle(wxString(project->project_name) + _(" - Nirvana2D"));

	return;
}

void NirvanaEditor_MainFrame::OnSaveProject( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	if(!project->active)
	{
		wxMessageBox(_("You must have an open project to save"));
		return;
	}

	int current_main_tab = m_editorMainTab_auinotebook->GetSelection();
	int current_project_tab = m_projectManager_auinotebook->GetSelection();
	int current_mapEditTools_tab = m_mapEdit_layerObjectTools_auinotebook->GetSelection();
	int current_tileEdit_tab = m_tileEdit_tools_auinotebook->GetSelection();
	int current_spriteEdit_tab = m_spriteEdit_tools_auinotebook->GetSelection();

	wxFileName fname = project->project_filename_obj;


	wxFileName pfile_path = fname;
	pfile_path.SetFullName(wxString(project->project_name).Trim() + _(".nvprj"));

	// std::cout << "PFILE: " << pfile_path.GetAbsolutePath().ToStdString() << std::endl;

	wxFile pfile(pfile_path.GetAbsolutePath(), wxFile::write);

	if(pfile.IsOpened())
	{
		pfile.Write(_("NIRVANA version=") + _(NIRVANA_VERSION_STRING) + _(";\n"));
		pfile.Write(_("PROJECT name=\"") + project->project_name + _("\";\n"));
		pfile.Write(_("MEDIA_PATH ") + _("bkg=\"") + project->bkg_path + _("\" ") +
										_("tile=\"") + project->tile_path + _("\" ") +
										_("stage=\"") + project->stage_path + _("\" ") +
										_("sprite=\"") + project->sprite_path + _("\";\n\n"));

		pfile.Write(_("---------------- SPRITES ---------------------;\n\n"));

		//sprite definition stuff
		for(int i = 0; i < project->sprite_base.size(); i++)
		{
			wxFileName sp_path = fname;
			sp_path.AppendDir(project->sprite_path);
			sp_path.SetFullName(project->sprite_base[i].file.Trim() + _(".sprite"));

			pfile.Write(_("SPRITE file=\"") + project->sprite_base[i].file.Trim() + _("\";\n"));

			wxFile sp_file(sp_path.GetAbsolutePath(), wxFile::write);

			sp_file.Write(_("SPRITE "));
			sp_file.Write(_("name=\"") + project->sprite_base[i].sprite_name + _("\" "));
			sp_file.Write(_("frame_size=") + wxString::Format(_("%i"), project->sprite_base[i].object.frame_size.Width) + _(",") +
											 wxString::Format(_("%i"), project->sprite_base[i].object.frame_size.Height) + _(" ") +
                          _("detached_shape=") + (project->sprite_base[i].object.physics.detached ? _("TRUE") : _("FALSE")) + _(";\n"));

			//Collision Shape
			if(project->sprite_base[i].object.physics.shape_type == SPRITE_SHAPE_BOX)
			{
				sp_file.Write(_("SHAPE type=SPRITE_SHAPE_BOX "));
				sp_file.Write(_("point=") + wxString::Format(_("%i"), project->sprite_base[i].object.physics.offset_x) + _(",") +
											wxString::Format(_("%i"), project->sprite_base[i].object.physics.offset_y) + _(" "));
				sp_file.Write(_("size=") + wxString::Format(_("%i"), project->sprite_base[i].object.physics.box_width) + _(",") +
										   wxString::Format(_("%i"), project->sprite_base[i].object.physics.box_height) + _(" "));
				sp_file.Write(_(";\n"));
			}
			else if(project->sprite_base[i].object.physics.shape_type == SPRITE_SHAPE_CIRCLE)
			{
				sp_file.Write(_("SHAPE type=SPRITE_SHAPE_CIRCLE "));
				sp_file.Write(_("point=") + wxString::Format(_("%i"), project->sprite_base[i].object.physics.offset_x) + _(",") +
											wxString::Format(_("%i"), project->sprite_base[i].object.physics.offset_y) + _(" "));
				sp_file.Write(_("radius=") + wxString::FromDouble(project->sprite_base[i].object.physics.radius) + _(" "));
				sp_file.Write(_(";\n"));
			}
			else if(project->sprite_base[i].object.physics.shape_type == SPRITE_SHAPE_POLYGON)
			{
				sp_file.Write(_("SHAPE type=SPRITE_SHAPE_POLYGON "));
				for(int pt_index=0; pt_index < project->sprite_base[i].object.physics.points.size(); pt_index++)
				{
					sp_file.Write(_("point=") + wxString::Format(_("%i"), project->sprite_base[i].object.physics.points[pt_index].X) + _(",") +
												wxString::Format(_("%i"), project->sprite_base[i].object.physics.points[pt_index].Y) + _(" "));
				}
				sp_file.Write(_(";\n"));
			}

			//Animations
			for(int ani=0; ani < project->sprite_base[i].object.animation.size(); ani++)
			{
				sp_file.Write(_("ANIMATION "));
				sp_file.Write(_("name=\"") + wxString(project->sprite_base[i].object.animation[ani].name) + _("\" "));
				sp_file.Write(_("frame_count=") + wxString::Format(_("%i"), project->sprite_base[i].object.animation[ani].frames.size()) + _(" "));
				sp_file.Write(_("fps=") + wxString::FromDouble((double)project->sprite_base[i].object.animation[ani].fps) +_(" "));

				if(project->sprite_base[i].object.animation[ani].frames.size() > 0)
					sp_file.Write(_("frame="));
				for(int frame=0; frame < project->sprite_base[i].object.animation[ani].frames.size(); frame++)
				{
					sp_file.Write(wxString::Format(_("%i"), project->sprite_base[i].object.animation[ani].frames[frame]) +
									( (frame+1) < project->sprite_base[i].object.animation[ani].frames.size() ? _(",") : _(" "))  );
				}
				sp_file.Write(_(";\n"));
			}

			sp_file.Close();
		}


		pfile.Write(_("\n\n---------------- TILESETS ---------------------;\n\n"));

		//tileset definition stuff
		for(int i = 0; i < project->tileset.size(); i++)
		{
			wxFileName tset_path = fname;
			tset_path.AppendDir(project->tile_path);
			tset_path.SetFullName(project->tileset[i].file.Trim() + _(".tset"));

			pfile.Write(_("TILESET file=\"") + project->tileset[i].file.Trim() + _("\";\n"));

			wxFile tset_file(tset_path.GetAbsolutePath(), wxFile::write);

			tset_file.Write(_("TILESET "));
			tset_file.Write(_("name=\"") + project->tileset[i].tileset_name.Trim() + _("\" "));
			tset_file.Write(_("frame_size=") + wxString::Format(_("%i"), project->tileset[i].object.tile_width) + _(",") +
											   wxString::Format(_("%i"), project->tileset[i].object.tile_height) + _(";\n"));

			//Tiles
			for(int t_index=0; t_index < project->tileset[i].object.tiles.size(); t_index++)
			{
				tset_file.Write(_("TILE "));
				tset_file.Write(_("fps=") + wxString::FromDouble(project->tileset[i].object.tiles[t_index].fps) + _(" "));

				if(project->tileset[i].object.tiles[t_index].frames.size() > 0)
					tset_file.Write(_("frame="));

				for(int frame=0; frame < project->tileset[i].object.tiles[t_index].frames.size(); frame++)
				{
					tset_file.Write( wxString::Format(_("%i"), project->tileset[i].object.tiles[t_index].frames[frame]) +
										( (frame+1) < project->tileset[i].object.tiles[t_index].frames.size() ? _(",") : _(" ") ) );
				}

				tset_file.Write(_(";\n"));
			}

			tset_file.Write(_("\n\n"));

			//Mask
			for(int m_index = 0; m_index < project->tileset[i].mask.size(); m_index++)
			{
				tset_file.Write(_("MASK "));
				tset_file.Write(_("name=\"") + wxString(project->tileset[i].mask[m_index].mask_name) + _("\" "));

				if(project->tileset[i].mask[m_index].tiles.size() > 0)
					tset_file.Write(_("value="));

				for(int m_tile_index = 0; m_tile_index < project->tileset[i].mask[m_index].tiles.size(); m_tile_index++)
				{
					tset_file.Write( ( project->tileset[i].mask[m_index].tiles[m_tile_index] ? _("1") : _("0") ) +
										( (m_tile_index+1) < project->tileset[i].mask[m_index].tiles.size() ? _(",") : _(" ") ) );
				}

				tset_file.Write(_(";\n"));
			}

			tset_file.Close();
		}


		pfile.Write(_("\n\n---------------- STAGES ---------------------;\n\n"));

		//stage stuff
		for(int i = 0; i < project->stages.size(); i++)
		{
			wxString stage_name = wxString(project->stages[i].stage_name).Trim() + _(".stage");
			wxFileName stage_path = fname;
			stage_path.AppendDir(project->stage_path);
			stage_path.SetFullName(stage_name);

			pfile.Write(_("STAGE file=\"") + stage_name + _("\";\n"));

			wxFile stage_file(stage_path.GetAbsolutePath(), wxFile::write);

			stage_file.Write(_("STAGE "));
			stage_file.Write(_("name=\"") + wxString(project->stages[i].stage_name).Trim() + _("\" "));
			stage_file.Write(_("tile_size=") + wxString::Format(_("%i"), project->stages[i].tile_width) + _(",") +
											   wxString::Format(_("%i"), project->stages[i].tile_height) + _(" "));
			stage_file.Write(_("stage_size=") + wxString::Format(_("%i"), project->stages[i].width_in_tiles) + _(",") +
												wxString::Format(_("%i"), project->stages[i].height_in_tiles) + _(";\n\n"));

			for(int layer_index = 0; layer_index < project->stages[i].layers.size(); layer_index++)
			{
				stage_file.Write(_("LAYER "));
				stage_file.Write(_("name=\"") + wxString(project->stages[i].layers[layer_index].layer_name) + _("\" "));
				stage_file.Write(_("type="));

				if(project->stages[i].layers[layer_index].layer_type == LAYER_TYPE_CANVAS_2D)
					stage_file.Write(_("LAYER_TYPE_CANVAS_2D"));
				else if(project->stages[i].layers[layer_index].layer_type == LAYER_TYPE_CANVAS_3D)
					stage_file.Write(_("LAYER_TYPE_CANVAS_3D"));
				else if(project->stages[i].layers[layer_index].layer_type == LAYER_TYPE_SPRITE)
					stage_file.Write(_("LAYER_TYPE_SPRITE"));
				else if(project->stages[i].layers[layer_index].layer_type == LAYER_TYPE_TILEMAP)
					stage_file.Write(_("LAYER_TYPE_TILEMAP"));
                else if(project->stages[i].layers[layer_index].layer_type == LAYER_TYPE_ISO_TILEMAP)
					stage_file.Write(_("LAYER_TYPE_ISO_TILEMAP"));

				stage_file.Write(_(" "));

				if(project->stages[i].layers[layer_index].layer_type == LAYER_TYPE_TILEMAP || project->stages[i].layers[layer_index].layer_type == LAYER_TYPE_ISO_TILEMAP)
					stage_file.Write(_("tileset=\"") + wxString( project->stages[i].layers[layer_index].layer_map.nv_tileset_name ) + _("\" "));

				stage_file.Write(_("scroll_speed=") + wxString::FromDouble((double)project->stages[i].layers[layer_index].scroll_speed.X) + _(",") +
													  wxString::FromDouble((double)project->stages[i].layers[layer_index].scroll_speed.Y) + _(" "));

				stage_file.Write(_("alpha=") + wxString::Format(_("%i"), project->stages[i].layers[layer_index].layer_alpha) + _(" "));

				stage_file.Write(_("visible=") + ( project->stages[i].layers[layer_index].visible ? _("TRUE") : _("FALSE") ) + _(";\n"));

				if(project->stages[i].layers[layer_index].layer_type == LAYER_TYPE_CANVAS_2D)
				{
					stage_file.Write(_("BKG "));
					stage_file.Write(_("image=\"") + wxString(project->stages[i].layers[layer_index].bkg.img_file) + _("\" "));
					stage_file.Write(_("render_setting="));

					if(project->stages[i].layers[layer_index].bkg.render_setting == IMG_RENDER_SETTING_NORMAL)
						stage_file.Write(_("IMG_RENDER_SETTING_NORMAL"));
					else if(project->stages[i].layers[layer_index].bkg.render_setting == IMG_RENDER_SETTING_STRETCHED)
						stage_file.Write(_("IMG_RENDER_SETTING_STRETCHED"));
					else if(project->stages[i].layers[layer_index].bkg.render_setting == IMG_RENDER_SETTING_TILED)
						stage_file.Write(_("IMG_RENDER_SETTING_TILED"));

					stage_file.Write(_(";\n"));
				}
				else if(project->stages[i].layers[layer_index].layer_type == LAYER_TYPE_CANVAS_3D)
				{
					stage_file.Write(_(";\n"));
				}
				else if(project->stages[i].layers[layer_index].layer_type == LAYER_TYPE_SPRITE)
				{
					//sprites
					for(int sprite_index = 0; sprite_index < project->stages[i].layers[layer_index].layer_sprites.size(); sprite_index++)
					{
						stage_file.Write(_("SPRITE "));
						stage_file.Write(_("name=\"") + wxString(project->stages[i].layers[layer_index].layer_sprites[sprite_index].sprite_name) + _("\" "));

						int base_index = project->stages[i].layers[layer_index].layer_sprites[sprite_index].sprite_base;
						stage_file.Write(_("base=\"") + project->sprite_base[base_index].sprite_name + _("\" "));

						if(project->stages[i].layers[layer_index].layer_sprites[sprite_index].body_type == SPRITE_TYPE_DYNAMIC)
							stage_file.Write(_("type=SPRITE_TYPE_DYNAMIC "));
						else if(project->stages[i].layers[layer_index].layer_sprites[sprite_index].body_type == SPRITE_TYPE_KINEMATIC)
							stage_file.Write(_("type=SPRITE_TYPE_KINEMATIC "));
						else if(project->stages[i].layers[layer_index].layer_sprites[sprite_index].body_type == SPRITE_TYPE_STATIC)
							stage_file.Write(_("type=SPRITE_TYPE_STATIC "));

						stage_file.Write(_("position=") + wxString::Format(_("%i"), project->stages[i].layers[layer_index].layer_sprites[sprite_index].position.X) + _(",") +
														  wxString::Format(_("%i"), project->stages[i].layers[layer_index].layer_sprites[sprite_index].position.Y) + _(" "));

						stage_file.Write(_("scale=") + wxString::FromDouble((double)project->stages[i].layers[layer_index].layer_sprites[sprite_index].scale.X) + _(",") +
													   wxString::FromDouble((double)project->stages[i].layers[layer_index].layer_sprites[sprite_index].scale.Y) + _(" "));

						stage_file.Write(_("rotation=") + wxString::FromDouble((double)(360-project->stages[i].layers[layer_index].layer_sprites[sprite_index].angle)) + _(" "));

						stage_file.Write(_("alpha=") + wxString::Format(_("%i"), (int)project->stages[i].layers[layer_index].layer_sprites[sprite_index].alpha) + _(" "));

						stage_file.Write(_("animation=\"") + wxString(project->stages[i].layers[layer_index].layer_sprites[sprite_index].animation_name) + _("\" "));

						stage_file.Write(_("visible=") + (project->stages[i].layers[layer_index].layer_sprites[sprite_index].visible ? _("TRUE") : _("FALSE")) + _(";\n"));
					}

					//shapes
					for(int shape_index = 0; shape_index < project->stages[i].layers[layer_index].layer_shapes.size(); shape_index++)
					{
						stage_file.Write(_("SHAPE "));
						stage_file.Write(_("name=\"") + wxString(project->stages[i].layers[layer_index].layer_shapes[shape_index].shape_name) + _("\" "));

						if(project->stages[i].layers[layer_index].layer_shapes[shape_index].shape_type == SPRITE_SHAPE_BOX)
						{
							stage_file.Write(_("type=SPRITE_SHAPE_BOX "));

							stage_file.Write(_("point=") + wxString::Format(_("%i"), project->stages[i].layers[layer_index].layer_shapes[shape_index].offset_x) + _(",") +
														   wxString::Format(_("%i"), project->stages[i].layers[layer_index].layer_shapes[shape_index].offset_y) + _(" "));

							stage_file.Write(_("size=") + wxString::Format(_("%i"), project->stages[i].layers[layer_index].layer_shapes[shape_index].box_width) + _(",") +
														  wxString::Format(_("%i"), project->stages[i].layers[layer_index].layer_shapes[shape_index].box_height) + _(" "));
						}
						else if(project->stages[i].layers[layer_index].layer_shapes[shape_index].shape_type == SPRITE_SHAPE_CIRCLE)
						{
							stage_file.Write(_("type=SPRITE_SHAPE_CIRCLE "));

							stage_file.Write(_("point=") + wxString::Format(_("%i"), project->stages[i].layers[layer_index].layer_shapes[shape_index].offset_x) + _(",") +
														   wxString::Format(_("%i"), project->stages[i].layers[layer_index].layer_shapes[shape_index].offset_y) + _(" "));

							stage_file.Write(_("radius=") + wxString::Format(_("%i"), (int)project->stages[i].layers[layer_index].layer_shapes[shape_index].radius) + _(" "));
						}
						else if(project->stages[i].layers[layer_index].layer_shapes[shape_index].shape_type == SPRITE_SHAPE_CHAIN || project->stages[i].layers[layer_index].layer_shapes[shape_index].shape_type == SPRITE_SHAPE_POLYGON)
						{
							if(project->stages[i].layers[layer_index].layer_shapes[shape_index].shape_type == SPRITE_SHAPE_CHAIN)
								stage_file.Write(_("type=SPRITE_SHAPE_CHAIN "));
							else
								stage_file.Write(_("type=SPRITE_SHAPE_POLYGON "));

							for(int pt_index = 0; pt_index < project->stages[i].layers[layer_index].layer_shapes[shape_index].points.size(); pt_index++)
							{
								stage_file.Write(_("point=") + wxString::Format(_("%i"), project->stages[i].layers[layer_index].layer_shapes[shape_index].points[pt_index].X) + _(",") +
															   wxString::Format(_("%i"), project->stages[i].layers[layer_index].layer_shapes[shape_index].points[pt_index].Y) + _(" "));
							}
						}

						stage_file.Write(_(";\n"));
					}
				}
				else if(project->stages[i].layers[layer_index].layer_type == LAYER_TYPE_TILEMAP || project->stages[i].layers[layer_index].layer_type == LAYER_TYPE_ISO_TILEMAP)
				{
					stage_file.Write(_("START_TILEMAP;\n"));

					for(int t_row = 0; t_row < project->stages[i].layers[layer_index].layer_map.tile_map.rows.size(); t_row++)
					{
						stage_file.Write(_("ROW value="));
						for(int tile_index = 0; tile_index < project->stages[i].layers[layer_index].layer_map.tile_map.rows[t_row].tile.size(); tile_index++)
						{
							stage_file.Write( wxString::Format(_("%i"), project->stages[i].layers[layer_index].layer_map.tile_map.rows[t_row].tile[tile_index]) +
												( ((tile_index+1) < project->stages[i].layers[layer_index].layer_map.tile_map.rows[t_row].tile.size()) ? _(",") : _("") ) );
						}
						stage_file.Write(_(";\n"));
					}

					stage_file.Write(_("END_TILEMAP;\n"));

					if(project->stages[i].layers[layer_index].layer_type == LAYER_TYPE_ISO_TILEMAP)
                    {
                        stage_file.Write(_("START_TILEMAP;\n"));

                        for(int t_row = 0; t_row < project->stages[i].layers[layer_index].layer_map.tile_map2.rows.size(); t_row++)
                        {
                            stage_file.Write(_("ROW value="));
                            for(int tile_index = 0; tile_index < project->stages[i].layers[layer_index].layer_map.tile_map2.rows[t_row].tile.size(); tile_index++)
                            {
                                stage_file.Write( wxString::Format(_("%i"), project->stages[i].layers[layer_index].layer_map.tile_map2.rows[t_row].tile[tile_index]) +
                                                    ( ((tile_index+1) < project->stages[i].layers[layer_index].layer_map.tile_map2.rows[t_row].tile.size()) ? _(",") : _("") ) );
                            }
                            stage_file.Write(_(";\n"));
                        }

                        stage_file.Write(_("END_TILEMAP;\n"));
                    }
				}

				stage_file.Write(_("\n"));
			}

			stage_file.Close();
		}


		pfile.Close();
	}

}

bool NirvanaEditor_MainFrame::generateSpriteDefinitions()
{
	if(!project)
		return false;

	wxFileName fname(project->getDir());
	fname.SetFullName(_("nirvana_spriteDef.bas"));

	wxFile pfile(fname.GetAbsolutePath(), wxFile::write);

	if(!pfile.IsOpened())
		return false;

	pfile.Write(_("NIRVANA_SPRITE_DIR$ = NIRVANA_PROJECT_BASE_DIR$ + NIRVANA_PATH_SEPARATOR$ + \"") + project->sprite_path +  _("\" + NIRVANA_PATH_SEPARATOR$\n"));
	pfile.Write(_("\n\n"));

	//Shared types
	pfile.Write(_("Type Nirvana_Sprite\n"));
	pfile.Write(_("Dim Name$\n"));
	pfile.Write(_("Dim BaseName$\n"));
	pfile.Write(_("Dim Sprite_ID\n"));
	pfile.Write(_("Dim Detached_Sprite_ID\n"));
	pfile.Write(_("Dim IsDetached\n"));
	pfile.Write(_("Dim Animation_Name_Index\n")); //This is to save memory since RC currently can't resize fields in a UDT
	pfile.Write(_("Dim Animation_Count\n"));
	pfile.Write(_("End Type\n"));

	pfile.Write(_("\n"));

	pfile.Write(_("Dim Nirvana_Sprite_Image_Stack : Nirvana_Sprite_Image_Stack = CreateStack_N()\n\n"));

	std::vector<wxString> sprite_build_fn;
	std::vector<wxString> sprite_img_var;

	std::vector<wxString> var_def;
	std::vector<wxString> fn_def;

	std::vector<wxString> sprite_animation_names;

	//Sprite Definitions
	for(int base_index = 0; base_index < project->sprite_base.size(); base_index++)
	{
		wxString fn_name = _("Nirvana_SpriteDef_") + wxString::Format(_("%i"), base_index) + _("(ByRef detached_spr_id)");
		sprite_build_fn.push_back(fn_name);

		wxString spr_img = _("Nirvana_Sprite_Image_") + wxString::Format(_("%i"), base_index);
		sprite_img_var.push_back(spr_img);

		//Sprite Create Function
		var_def.push_back(_("Dim ") + spr_img + _(" : ") + spr_img + _(" = -1"));

		wxString fn_str = _("");

		fn_str += _("Function ") + fn_name + _("\n");

		fn_str += _("\tIf ") + spr_img + _(" < 0 Then\n");
		wxString img_path_win = project->sprite_base[base_index].file;
		wxString img_path_x = project->sprite_base[base_index].file;

		fn_str += _("\t\tIf OS$ = \"WINDOWS\" Then\n");
		fn_str += _("\t\t\t") + spr_img + _(" = LoadImage(NIRVANA_SPRITE_DIR$ + \"") + img_path_win + _("\")\n");
		fn_str += _("\t\tElse\n");
		fn_str += _("\t\t\t") + spr_img + _(" = LoadImage(NIRVANA_SPRITE_DIR$ + \"") + img_path_x + _("\")\n");
		fn_str += _("\t\tEnd If\n\n");

		fn_str += _("\t\tIf ") + spr_img + _(" >= 0 Then\n");
		fn_str += _("\t\t\tPush_N(Nirvana_Sprite_Image_Stack, ") + spr_img + _(")\n");
		fn_str += _("\t\tEnd If\n");

		fn_str += _("\tEnd If\n\n");

		wxString frame_width_str = wxString::Format(_("%i"), project->sprite_base[base_index].object.frame_size.Width);
		wxString frame_height_str = wxString::Format(_("%i"), project->sprite_base[base_index].object.frame_size.Height);

		fn_str += _("\t") + _("spr_id = CreateSprite(") + spr_img + _(", ") + frame_width_str + _(", ") + frame_height_str + _(")\n\n");

		fn_str += _("\t\'-------ANIMATIONS-------\n\n");
		project->sprite_base[base_index].object.animation_list_start_index = sprite_animation_names.size();

		//excluding 0 since base animation is automatically made when sprite is created
		for(int ani = 1; ani < project->sprite_base[base_index].object.animation.size(); ani++)
		{
			wxString ani_length_str = wxString::Format(_("%i"), (int)project->sprite_base[base_index].object.animation[ani].frames.size());
			wxString ani_speed_str = wxString::Format(_("%i"), (int)(project->sprite_base[base_index].object.animation[ani].fps) );
			wxString ani_str = _("spr_animation") + wxString::Format(_("%i"), ani);
			fn_str += _("\t") + ani_str + _(" = CreateSpriteAnimation(spr_id, ") +  ani_length_str + _(", ") + ani_speed_str + _(")\n");
			sprite_animation_names.push_back(wxString(project->sprite_base[base_index].object.animation[ani].name));
			fn_str += _("\n");
			for(int frame = 0; frame < project->sprite_base[base_index].object.animation[ani].frames.size(); frame++)
			{
				wxString ani_frame_str = wxString::Format(_("%i"), frame);
				wxString sheet_index_str = wxString::Format(_("%i"), project->sprite_base[base_index].object.animation[ani].frames[frame]);
				fn_str += _("\tSetSpriteAnimationFrame(spr_id, ") + ani_str + _(", ") + ani_frame_str + _(", ") + sheet_index_str + _(")\n");
			}
			fn_str += _("\n");
		}

		fn_str += _("\n");
		fn_str += _("\t\'-------SHAPE-------\n");

		wxString collision_spr_id = _("spr_id");

		if(project->sprite_base[base_index].object.physics.detached)
        {
            fn_str += _("detached_spr_id = CreateSprite(-1, ") + frame_width_str + _(", ") + frame_height_str + _(")\n\n");
            collision_spr_id = _("detached_spr_id");
        }
        else
        {
            fn_str += _("detached_spr_id = -1") + _("\n\n");
        }

		if(project->sprite_base[base_index].object.physics.shape_type == SPRITE_SHAPE_BOX)
		{
			wxString shape_x_str = wxString::Format(_("%i"), project->sprite_base[base_index].object.physics.offset_x);
			wxString shape_y_str = wxString::Format(_("%i"), project->sprite_base[base_index].object.physics.offset_y);
			wxString shape_w_str = wxString::Format(_("%i"), project->sprite_base[base_index].object.physics.box_width);
			wxString shape_h_str = wxString::Format(_("%i"), project->sprite_base[base_index].object.physics.box_height);

			fn_str += _("\tSetSpriteShape(") + collision_spr_id + _(", SPRITE_SHAPE_BOX)\n");
			fn_str += _("\tSetSpriteShapeOffset(") + collision_spr_id + _(", ") + shape_x_str + _(", ") + shape_y_str + _(")\n");
			fn_str += _("\tSetSpriteBox(") + collision_spr_id + _(", ") + shape_w_str + _(", ") + shape_h_str + _(")\n");
		}
		else if(project->sprite_base[base_index].object.physics.shape_type == SPRITE_SHAPE_CIRCLE)
		{
			wxString shape_x_str = wxString::Format(_("%i"), project->sprite_base[base_index].object.physics.offset_x);
			wxString shape_y_str = wxString::Format(_("%i"), project->sprite_base[base_index].object.physics.offset_y);
			wxString shape_radius_str = wxString::FromDouble( project->sprite_base[base_index].object.physics.radius);

			fn_str += _("\tSetSpriteShape(") + collision_spr_id + _(", SPRITE_SHAPE_CIRCLE)\n");
			fn_str += _("\tSetSpriteShapeOffset(") + collision_spr_id + _(", ") + shape_x_str + _(", ") + shape_y_str + _(")\n");
			fn_str += _("\tSetSpriteRadius(") + collision_spr_id + _(", ") + shape_radius_str + _(")\n");
		}
		else if(project->sprite_base[base_index].object.physics.shape_type == SPRITE_SHAPE_CHAIN || project->sprite_base[base_index].object.physics.shape_type == SPRITE_SHAPE_POLYGON)
		{
			wxString shape_pt_count_str = wxString::Format(_("%i"), (int)project->sprite_base[base_index].object.physics.points.size());

			if(project->sprite_base[base_index].object.physics.shape_type == SPRITE_SHAPE_CHAIN)
				fn_str += _("\tSetSpriteShape(") + collision_spr_id + _(", SPRITE_SHAPE_CHAIN)\n");
			else
				fn_str += _("\tSetSpriteShape(") + collision_spr_id + _(", SPRITE_SHAPE_POLYGON)\n");

			fn_str += _("\tDim shape_point_x[") + shape_pt_count_str + _("]\n");
			fn_str += _("\tDim shape_point_y[") + shape_pt_count_str + _("]\n");

			wxString prev_x_str = _("0");
			wxString prev_y_str = _("0");
			wxString next_x_str = _("0");
			wxString next_y_str = _("0");

			if(project->sprite_base[base_index].object.physics.points.size() > 0)
			{
				prev_x_str = wxString::Format(_("%i"), project->sprite_base[base_index].object.physics.points[0].X-1);
				prev_y_str = wxString::Format(_("%i"), project->sprite_base[base_index].object.physics.points[0].Y-1);

				int last_index = project->sprite_base[base_index].object.physics.points.size()-1;

				prev_x_str = wxString::Format(_("%i"), project->sprite_base[base_index].object.physics.points[last_index].X+1);
				prev_y_str = wxString::Format(_("%i"), project->sprite_base[base_index].object.physics.points[last_index].Y-1);
			}

			fn_str += _("\n");

			for(int pt_index = 0; pt_index < project->sprite_base[base_index].object.physics.points.size(); pt_index++)
			{
				fn_str += _("\tshape_point_x[") + wxString::Format(_("%i"), pt_index) + _("] = ") + wxString::Format(_("%i"), project->sprite_base[base_index].object.physics.points[pt_index].X) + _("\n");
				fn_str += _("\tshape_point_y[") + wxString::Format(_("%i"), pt_index) + _("] = ") + wxString::Format(_("%i"), project->sprite_base[base_index].object.physics.points[pt_index].Y) + _("\n");
				fn_str += _("\n");
			}

			if(project->sprite_base[base_index].object.physics.shape_type == SPRITE_SHAPE_CHAIN)
				fn_str += _("\tSetSpriteChain(") + collision_spr_id + _(", shape_point_x, shape_point_y, ") + shape_pt_count_str + _(", ") + prev_x_str + _(", ") + prev_y_str + _(", ") + next_x_str + _(", ") + next_y_str + _(")\n");
			else
				fn_str += _("\tSetSpritePolygon(") + collision_spr_id + _(", shape_point_x, shape_point_y, ") + shape_pt_count_str + _(")\n");
		}

		fn_str += _("\n");
		fn_str += _("\tReturn spr_id\n");

		fn_str += _("End Function\n");

		fn_def.push_back(fn_str);
	}

	wxString sprite_animation_name_var_def = _("Dim Nirvana_SpriteAnimationNames$[") + wxString::Format(_("%i"), (int)sprite_animation_names.size()) + _("]\n\n");

	var_def.push_back(_("\n"));

	//Sprite Animation Names List
	for(int i = 0; i < sprite_animation_names.size(); i++)
	{
		sprite_animation_name_var_def += _("Nirvana_SpriteAnimationNames$[") + wxString::Format(_("%i"), i) + _("] = \"") + sprite_animation_names[i] + _("\"\n");
	}


	//SpriteDef vars
	for(int i = 0; i < var_def.size(); i++)
	{
		pfile.Write(var_def[i] + _("\n"));
	}

	//Sprite Animation Names to pfile
	pfile.Write(sprite_animation_name_var_def + _("\n"));

	pfile.Write(_("\n"));

	//SpriteDef functions
	for(int i = 0; i < fn_def.size(); i++)
	{
		pfile.Write(fn_def[i] + _("\n"));
	}

	pfile.Write(_("\n"));

	//Nirvana_CreateSprite function
	pfile.Write(_("Function Nirvana_CreateSprite(base_name$, sprite_name$) As Nirvana_Sprite\n"));
	pfile.Write(_("\tDim nv_sprite As Nirvana_Sprite\n"));
	pfile.Write(_("\tnv_sprite.Name$ = sprite_name$\n"));
	pfile.Write(_("\tnv_sprite.BaseName$ = base_name$\n\n"));
	pfile.Write(_("\tSelect Case base_name$\n\n"));
	for(int base_index = 0; base_index < project->sprite_base.size(); base_index++)
	{
		pfile.Write(_("\tCase \"") + project->sprite_base[base_index].sprite_name + _("\"\n"));
		wxString nv_build_fn = sprite_build_fn[base_index];
		nv_build_fn.Replace(_("ByRef detached_spr_id"), _("nv_sprite.Detached_Sprite_ID"));
		pfile.Write(_("\t\tnv_sprite.Sprite_ID = ") + nv_build_fn + _("\n"));
		pfile.Write(_("\t\tnv_sprite.IsDetached = ") + (project->sprite_base[base_index].object.physics.detached ? _("TRUE") : _("FALSE")) + _("\n"));
		pfile.Write(_("\t\tnv_sprite.Animation_Name_Index = ") + wxString::Format(_("%i"), project->sprite_base[base_index].object.animation_list_start_index) + _("\n"));
		pfile.Write(_("\t\tnv_sprite.Animation_Count = ") + wxString::Format(_("%i"), (int)project->sprite_base[base_index].object.animation.size()) + _("\n"));
		pfile.Write(_("\n"));
	}

	pfile.Write(_("\tEnd Select\n\n"));
	pfile.Write(_("\tReturn nv_sprite\n"));
	pfile.Write(_("End Function\n"));

	pfile.Close();

	return true;
}

bool NirvanaEditor_MainFrame::generateTilesets()
{
	if(!project)
		return false;

	wxFileName fname(project->getDir());
	fname.SetFullName(_("nirvana_tileset.bas"));

	wxFile pfile(fname.GetAbsolutePath(), wxFile::write);

	if(!pfile.IsOpened())
		return false;

	pfile.Write(_("NIRVANA_TILE_DIR$ = NIRVANA_PROJECT_BASE_DIR$ + NIRVANA_PATH_SEPARATOR$ + \"") + project->tile_path +  _("\" + NIRVANA_PATH_SEPARATOR$\n"));
	pfile.Write(_("\n\n"));

	//Shared types
	pfile.Write(_("Type Nirvana_TileMap\n"));
	pfile.Write(_("Dim TilesetName$\n"));
	pfile.Write(_("Dim Tileset_ID\n"));
	pfile.Write(_("Dim TileMap_ID\n"));
	pfile.Write(_("Dim Mask_Index\n")); //This is to save memory since RC currently can't resize fields in a UDT; Mask_Index is used to reference name and matrix
	pfile.Write(_("Dim Mask_Count\n"));
	pfile.Write(_("End Type\n"));

	pfile.Write(_("\n"));

	pfile.Write(_("Dim Nirvana_Tileset_Image_Stack : Nirvana_Tileset_Image_Stack = CreateStack_N()\n\n"));

	std::vector<wxString> tileset_build_fn;
	std::vector<wxString> tileset_img_var;

	std::vector<wxString> var_def;
	std::vector<wxString> fn_def;

	std::vector<wxString> tileset_mask_names;
	std::vector<int> tileset_mask_matrix;

	//Tilesets
	for(int tset_index = 0; tset_index < project->tileset.size(); tset_index++)
	{
		wxString tset_id_str = _("Nirvana_Tileset_ID_") + wxString::Format(_("%i"), tset_index);
		wxString fn_name = _("Nirvana_Tileset_") + wxString::Format(_("%i"), tset_index) + _("()");
		tileset_build_fn.push_back(fn_name);

		wxString ts_img = _("Nirvana_Tileset_Image_") + wxString::Format(_("%i"), tset_index);
		tileset_img_var.push_back(ts_img);

		//Sprite Create Function
		var_def.push_back(_("Dim ") + ts_img + _(" : ") + ts_img + _(" = -1"));

		wxString fn_str = _("");

		fn_str += _("Function ") + fn_name + _("\n");

		fn_str += _("\tIf ") + tset_id_str + _(" >= 0 Then\n");
		fn_str += _("\t\tReturn ") + tset_id_str + _("\n");
		fn_str += _("\tEnd If\n");

		fn_str += _("\n");

		fn_str += _("\tIf ") + ts_img + _(" < 0 Then\n");
		wxString img_path_win = project->tileset[tset_index].file;
		wxString img_path_x = project->tileset[tset_index].file;

		fn_str += _("\t\tIf OS$ = \"WINDOWS\" Then\n");
		fn_str += _("\t\t\t") + ts_img + _(" = LoadImage(NIRVANA_TILE_DIR$ + \"") + img_path_win + _("\")\n");
		fn_str += _("\t\tElse\n");
		fn_str += _("\t\t\t") + ts_img + _(" = LoadImage(NIRVANA_TILE_DIR$ + \"") + img_path_x + _("\")\n");
		fn_str += _("\t\tEnd If\n\n");

		fn_str += _("\t\tIf ") + ts_img + _(" >= 0 Then\n");
		fn_str += _("\t\t\tPush_N(Nirvana_Tileset_Image_Stack, ") + ts_img + _(")\n");
		fn_str += _("\t\tEnd If\n");

		fn_str += _("\tEnd If\n\n");

		wxString tile_width_str = wxString::Format(_("%i"), project->tileset[tset_index].object.tile_width);
		wxString tile_height_str = wxString::Format(_("%i"), project->tileset[tset_index].object.tile_height);

		fn_str += _("\t") + tset_id_str + (" = CreateTileSet(") + ts_img + _(", ") + tile_width_str + _(", ") + tile_height_str + _(")\n\n");

		//Tile Animations
		fn_str += _("\t\'-------ANIMATIONS-------\n\n");

		for(int tile_index = 0; tile_index < project->tileset[tset_index].object.tiles.size(); tile_index++)
		{
			//Only Set Properties for tiles that are not default
			if(project->tileset[tset_index].object.tiles[tile_index].frames.size() == 1)
			{
				if(project->tileset[tset_index].object.tiles[tile_index].frames[0] == tile_index &&
				   project->tileset[tset_index].object.tiles[tile_index].fps == 0)
					continue;
			}

			wxString frame_count_str = wxString::Format(_("%i"), (int)project->tileset[tset_index].object.tiles[tile_index].frames.size());
			wxString fps_str = wxString::FromDouble(project->tileset[tset_index].object.tiles[tile_index].fps);
			fn_str += _("\tSetTileAnimationLength(") + tset_id_str + _(", ") + wxString::Format(_("%i"), tile_index) + _(", ") + frame_count_str + _(")\n");
			fn_str += _("\tSetTileAnimationSpeed(") + tset_id_str + _(", ") + wxString::Format(_("%i"), tile_index) + _(", ") + fps_str + _(")\n");
			fn_str += _("\n");

			for(int frame_index = 0; frame_index < project->tileset[tset_index].object.tiles[tile_index].frames.size(); frame_index++)
			{
				wxString frame_index_str = wxString::Format(_("%i"), frame_index);
				wxString frame_tile_str = wxString::Format(_("%i"), project->tileset[tset_index].object.tiles[tile_index].frames[frame_index]);
				fn_str += _("\tSetTileAnimationFrame(") + tset_id_str + _(", ") + wxString::Format(_("%i"), tile_index) + _(", ") + frame_index_str + _(", ") + frame_tile_str + _(")\n");
			}
			fn_str += _("\n");
		}


		//Tile Mask
		fn_str += _("\t\'-------MASK-------\n\n");
		project->tileset[tset_index].object.mask_start_index = (int)tileset_mask_names.size();

		for(int mask_index = 0; mask_index < project->tileset[tset_index].mask.size(); mask_index++)
		{
			wxString mask_var_str = _("Nirvana_TileMask_Matrix[") + wxString::Format(_("%i"), (int)tileset_mask_names.size()) + _("]");
			tileset_mask_names.push_back(wxString(project->tileset[tset_index].mask[mask_index].mask_name));
			wxString mask_size_str = wxString::Format(_("%i"), (int)project->tileset[tset_index].mask[mask_index].tiles.size());

			fn_str += _("\t") + mask_var_str + _(" = DimMatrix(1, ") + mask_size_str + _(")\n");
			fn_str += _("\tFillMatrix(") + mask_var_str + _(", 0)\n");
			for(int tile_index = 0; tile_index < project->tileset[tset_index].mask[mask_index].tiles.size(); tile_index++)
			{
				if(project->tileset[tset_index].mask[mask_index].tiles[tile_index] == 0)
					continue;

				wxString mask_value_str = ( project->tileset[tset_index].mask[mask_index].tiles[tile_index] ? _("1") : _("0") );
				fn_str += _("\tSetMatrixValue(") + mask_var_str + _(", 0, ") + wxString::Format(_("%i"), tile_index) + _(", ") + mask_value_str + _(")\n");
			}
			fn_str += _("\n");
		}

		fn_str += _("\tReturn ") + tset_id_str + _("\n");

		fn_str += _("End Function\n\n");

		fn_def.push_back(fn_str);
	}

	for(int i = 0; i < project->tileset.size(); i++)
	{
		wxString tset_id_str = _("Nirvana_Tileset_ID_") + wxString::Format(_("%i"), i);
		pfile.Write(_("Dim ") + tset_id_str + _(" : ") + tset_id_str + _(" = -1\n"));
	}

	pfile.Write(_("\n"));

	//tileset vars
	for(int i = 0; i < var_def.size(); i++)
	{
		pfile.Write(var_def[i] + _("\n"));
	}

	pfile.Write(_("\n"));

	//tile mask array
	int mask_array_size = tileset_mask_names.size();
	mask_array_size = mask_array_size < 0 ? 1 : mask_array_size;
	pfile.Write(_("Dim Nirvana_TileMask_Matrix[") + wxString::Format(_("%i"), mask_array_size) + _("]\n"));
	pfile.Write(_("Dim Nirvana_TileMask_Matrix_Name$[") + wxString::Format(_("%i"), mask_array_size) + _("]\n"));

	pfile.Write(_("\n"));
	for(int i = 0; i < tileset_mask_names.size(); i++)
	{
		pfile.Write(_("Nirvana_TileMask_Matrix_Name$[") + wxString::Format(_("%i"), i) + _("] = \"") + tileset_mask_names[i] + _("\"\n"));
	}

	pfile.Write(_("\n\n"));

	//tileset functions
	for(int i = 0; i < fn_def.size(); i++)
	{
		pfile.Write(fn_def[i] + _("\n"));
	}

	pfile.Write(_("\n\n"));

	//Nirvana_CreateTileMap function
	pfile.Write(_("Function Nirvana_CreateTileMap(tset_name$, tmap_width, tmap_height) As Nirvana_TileMap\n"));
	pfile.Write(_("\tDim nv_tmap As Nirvana_TileMap\n"));
	pfile.Write(_("\tnv_tmap.TilesetName$ = tset_name$\n"));
	pfile.Write(_("\n"));
	pfile.Write(_("\tSelect Case tset_name$\n\n"));
	for(int tset_index = 0; tset_index < project->tileset.size(); tset_index++)
	{
		pfile.Write(_("\tCase \"") + project->tileset[tset_index].tileset_name + _("\"\n"));
		pfile.Write(_("\t\tnv_tmap.Tileset_ID = ") + tileset_build_fn[tset_index] + _("\n"));
		pfile.Write(_("\t\tnv_tmap.TileMap_ID = CreateTileMap(nv_tmap.Tileset_ID, tmap_width, tmap_height)\n"));
		pfile.Write(_("\t\tnv_tmap.Mask_Index = ") + wxString::Format(_("%i"), project->tileset[tset_index].object.mask_start_index) + _("\n"));
		pfile.Write(_("\t\tnv_tmap.Mask_Count = ") + wxString::Format(_("%i"), (int)project->tileset[tset_index].mask.size()) + _("\n"));
		pfile.Write(_("\n"));
	}

	pfile.Write(_("\tEnd Select\n\n"));
	pfile.Write(_("\tReturn nv_tmap\n"));
	pfile.Write(_("End Function\n"));

	pfile.Close();

	return true;
}

bool NirvanaEditor_MainFrame::generateStages()
{
	if(!project)
		return false;

	wxFileName fname(project->getDir());
	fname.SetFullName(_("nirvana_stage.bas"));

	wxFile pfile(fname.GetAbsolutePath(), wxFile::write);

	if(!pfile.IsOpened())
		return false;

	//Shared types
	pfile.Write(_("Type Nirvana_Vector2D\n"));
	pfile.Write(_("Dim X\n"));
	pfile.Write(_("Dim Y\n"));
	pfile.Write(_("End Type\n"));

	pfile.Write(_("\n"));

	pfile.Write(_("Type Nirvana_Size2D\n"));
	pfile.Write(_("Dim Width\n"));
	pfile.Write(_("Dim Height\n"));
	pfile.Write(_("End Type\n"));

	pfile.Write(_("\n"));

	pfile.Write(_("Type Nirvana_Background\n"));
	pfile.Write(_("Dim Image_ID\n"));
	pfile.Write(_("Dim RenderSetting\n"));
	pfile.Write(_("End Type\n"));

	pfile.Write(_("\n"));

	pfile.Write(_("Type Nirvana_Shape\n"));
	pfile.Write(_("Dim Name$\n"));
	pfile.Write(_("Dim Sprite_ID\n"));
	pfile.Write(_("Dim ShapeType\n"));
	pfile.Write(_("End Type\n"));

	pfile.Write(_("\n"));

	pfile.Write(_("Type Nirvana_Layer\n"));
	pfile.Write(_("Dim Name$\n"));
	pfile.Write(_("Dim LayerType\n"));
	pfile.Write(_("Dim Visible\n"));
	pfile.Write(_("Dim Alpha\n"));
	pfile.Write(_("Dim Scroll_Speed As Nirvana_Vector2D\n"));
	pfile.Write(_("Dim Ref_Canvas\n"));
	pfile.Write(_("Dim Layer_TileMap As Nirvana_TileMap\n"));
	pfile.Write(_("Dim Layer_TileMap2 As Nirvana_TileMap\n"));
	pfile.Write(_("Dim Layer_Sprite_Count\n"));
	pfile.Write(_("Dim Layer_Shape_Count\n"));
	pfile.Write(_("Dim Bkg As Nirvana_Background\n"));
	pfile.Write(_("End Type\n"));

	pfile.Write(_("\n"));

	//---------

	pfile.Write(_("Type Nirvana_Stage\n"));
	pfile.Write(_("Dim Active\n"));
	pfile.Write(_("Dim Name$\n"));
	pfile.Write(_("Dim Tile_Size As Nirvana_Size2D\n"));
	pfile.Write(_("Dim Stage_Size As Nirvana_Size2D\n"));
	pfile.Write(_("Dim Layer_Count\n"));
	pfile.Write(_("Dim Viewport_Size As Nirvana_Size2D\n"));
	pfile.Write(_("Dim Stage_Offset As Nirvana_Vector2D\n"));
	pfile.Write(_("End Type\n"));

	pfile.Write(_("\n"));

	wxString nv_constants = _("");
	nv_constants += _("NIRVANA_DATA_DIR$ = NIRVANA_PROJECT_BASE_DIR$ + NIRVANA_PATH_SEPARATOR$ + \"data\" + NIRVANA_PATH_SEPARATOR$\n");
	nv_constants += _("NIRVANA_BKG_DIR$ = NIRVANA_PROJECT_BASE_DIR$ + NIRVANA_PATH_SEPARATOR$ + \"") + project->bkg_path + _("\" + NIRVANA_PATH_SEPARATOR$\n");
	nv_constants += _("\n");
	nv_constants += _("NIRVANA_LAYER_TYPE_TILEMAP = 0\n");
	nv_constants += _("NIRVANA_LAYER_TYPE_ISO_TILEMAP = 1\n");
	nv_constants += _("NIRVANA_LAYER_TYPE_SPRITE = 2\n");
	nv_constants += _("NIRVANA_LAYER_TYPE_CANVAS_2D = 3\n");
	nv_constants += _("NIRVANA_LAYER_TYPE_CANVAS_3D = 4\n");
	nv_constants += _("\n");
	nv_constants += _("NIRVANA_IMG_RENDER_SETTING_NORMAL = 0\n");
	nv_constants += _("NIRVANA_IMG_RENDER_SETTING_STRETCHED = 1\n");
	nv_constants += _("NIRVANA_IMG_RENDER_SETTING_TILED = 2\n");
	nv_constants += _("\n");

	std::vector<wxString> stage_build_fn;

	std::vector<wxString> var_def;
	std::vector<wxString> fn_def;

	int stage_sprite_array_size = 1;
	int stage_shape_array_size = 1;
	int stage_shape_point_array_size = 1;
	int stage_layer_array_size = 1;

	int tmap_data_index = 0;

	//Tilesets
	for(int stage_index = 0; stage_index < project->stages.size(); stage_index++)
	{
		int sprite_layer_start_index = 0;
		int shape_start_index = 0;
		wxString stage_id_str = _("Nirvana_Stage_ID_") + wxString::Format(_("%i"), stage_index);
		wxString fn_name = _("Nirvana_Stage_") + wxString::Format(_("%i"), stage_index);
		stage_build_fn.push_back(fn_name);

		wxString fn_str = _("");

		fn_str += _("Function ") + fn_name + _("(vp_x, vp_y, vp_w, vp_h) As Nirvana_Stage\n");

		fn_str += _("\tNirvana_ClearStage()\n");

		fn_str += _("\n");

		fn_str += _("\tDim nv_stage As Nirvana_Stage\n");
		fn_str += _("\tnv_stage.Name$ = \"") + wxString(project->stages[stage_index].stage_name) + _("\"\n");
		fn_str += _("\tnv_stage.Tile_Size.Width = ") + wxString::Format(_("%i"), project->stages[stage_index].tile_width) + _("\n");
		fn_str += _("\tnv_stage.Tile_Size.Height = ") + wxString::Format(_("%i"), project->stages[stage_index].tile_height) + _("\n");
		fn_str += _("\tnv_stage.Stage_Size.Width = ") + wxString::Format(_("%i"), project->stages[stage_index].width_in_tiles) + _("\n");
		fn_str += _("\tnv_stage.Stage_Size.Height = ") + wxString::Format(_("%i"), project->stages[stage_index].height_in_tiles) + _("\n");
		fn_str += _("\tnv_stage.Layer_Count = ") + wxString::Format(_("%i"), (int)project->stages[stage_index].layers.size()) + _("\n");

		fn_str += _("\n");

		stage_layer_array_size = project->stages[stage_index].layers.size() > stage_layer_array_size ? project->stages[stage_index].layers.size() : stage_layer_array_size;

		for(int layer_index = 0; layer_index < project->stages[stage_index].layers.size(); layer_index++)
		{
			wxString layer_name = wxString(project->stages[stage_index].layers[layer_index].layer_name);
			wxString layer_type_str = _("-1");

			if(project->stages[stage_index].layers[layer_index].layer_type == LAYER_TYPE_CANVAS_2D)
				layer_type_str = _("NIRVANA_LAYER_TYPE_CANVAS_2D");
			else if(project->stages[stage_index].layers[layer_index].layer_type == LAYER_TYPE_CANVAS_3D)
				layer_type_str = _("NIRVANA_LAYER_TYPE_CANVAS_3D");
			else if(project->stages[stage_index].layers[layer_index].layer_type == LAYER_TYPE_SPRITE)
				layer_type_str = _("NIRVANA_LAYER_TYPE_SPRITE");
			else if(project->stages[stage_index].layers[layer_index].layer_type == LAYER_TYPE_TILEMAP)
				layer_type_str = _("NIRVANA_LAYER_TYPE_TILEMAP");
            else if(project->stages[stage_index].layers[layer_index].layer_type == LAYER_TYPE_ISO_TILEMAP)
				layer_type_str = _("NIRVANA_LAYER_TYPE_ISO_TILEMAP");

			wxString layer_visible_str = (project->stages[stage_index].layers[layer_index].visible ? _("TRUE") : _("FALSE"));
			wxString layer_alpha_str = wxString::Format(_("%i"), project->stages[stage_index].layers[layer_index].layer_alpha);
			wxString layer_scroll_x_str = wxString::FromDouble(project->stages[stage_index].layers[layer_index].scroll_speed.X);
			wxString layer_scroll_y_str = wxString::FromDouble(project->stages[stage_index].layers[layer_index].scroll_speed.Y);

			wxString layer_list_index_str = wxString::Format(_("%i"), layer_index);
			fn_str += _("\t\'-------LAYER (") + layer_name + _(")-------\n\n");
			fn_str += _("\tNirvana_Stage_Layers[") + layer_list_index_str + _("].Name$ = \"") + layer_name + _("\"\n");
			fn_str += _("\tNirvana_Stage_Layers[") + layer_list_index_str + _("].LayerType = ") + layer_type_str + _("\n");
			fn_str += _("\tNirvana_Stage_Layers[") + layer_list_index_str + _("].Visible = ") + layer_visible_str + _("\n");
			fn_str += _("\tNirvana_Stage_Layers[") + layer_list_index_str + _("].Alpha = ") + layer_alpha_str + _("\n");
			fn_str += _("\tNirvana_Stage_Layers[") + layer_list_index_str + _("].Scroll_Speed.X = ") + layer_scroll_x_str + _("\n");
			fn_str += _("\tNirvana_Stage_Layers[") + layer_list_index_str + _("].Scroll_Speed.Y = ") + layer_scroll_y_str + _("\n");
			fn_str += _("\n");

			if(project->stages[stage_index].layers[layer_index].layer_type == LAYER_TYPE_CANVAS_2D)
			{
				fn_str += _("\tNirvana_Stage_Layers[") + layer_list_index_str + _("].Ref_Canvas = ") + _("OpenCanvas(NIRVANA_WINDOW_WIDTH, NIRVANA_WINDOW_HEIGHT, vp_x, vp_y, vp_w, vp_h, 1)\n");
				if(project->stages[stage_index].layers[layer_index].bkg.img_file.compare("")!=0)
				{
					fn_str += _("\tNirvana_Stage_Layers[") + layer_list_index_str + _("].Bkg.Image_ID = LoadImage(NIRVANA_BKG_DIR$ + \"") + wxString(project->stages[stage_index].layers[layer_index].bkg.img_file) + _("\")\n");

					wxString render_setting_str = _("NIRVANA_IMG_RENDER_SETTING_NORMAL");
					if(project->stages[stage_index].layers[layer_index].bkg.render_setting == IMG_RENDER_SETTING_STRETCHED)
						render_setting_str = _("NIRVANA_IMG_RENDER_SETTING_STRETCHED");
					else if(project->stages[stage_index].layers[layer_index].bkg.render_setting == IMG_RENDER_SETTING_TILED)
						render_setting_str = _("NIRVANA_IMG_RENDER_SETTING_TILED");

					fn_str += _("\tNirvana_Stage_Layers[") + layer_list_index_str + _("].Bkg.RenderSetting = ") + render_setting_str + _("\n");
				}
				else
				{
					fn_str += _("\tNirvana_Stage_Layers[") + layer_list_index_str + _("].Bkg.Image_ID = -1\n");
				}
			}
			else if(project->stages[stage_index].layers[layer_index].layer_type == LAYER_TYPE_CANVAS_3D)
			{
				fn_str += _("\tNirvana_Stage_Layers[") + layer_list_index_str + _("].Ref_Canvas = ") + _("OpenCanvas3D(vp_x, vp_y, vp_w, vp_h, 0)\n");
			}
			else if(project->stages[stage_index].layers[layer_index].layer_type == LAYER_TYPE_SPRITE)
			{
				fn_str += _("\tNirvana_Stage_Layers[") + layer_list_index_str + _("].Ref_Canvas = ") + _("OpenCanvasSpriteLayer(vp_x, vp_y, vp_w, vp_h)\n");
				fn_str += _("\tCanvas(Nirvana_Stage_Layers[") + layer_list_index_str + _("].Ref_Canvas)\n");
				fn_str += _("\tNirvana_Stage_Layers[") + layer_list_index_str + _("].Layer_Sprite_Count = ") + wxString::Format(_("%i"), (int)project->stages[stage_index].layers[layer_index].layer_sprites.size()) + _("\n");
				fn_str += _("\tNirvana_Stage_Layers[") + layer_list_index_str + _("].Layer_Shape_Count = ") + wxString::Format(_("%i"), (int)project->stages[stage_index].layers[layer_index].layer_shapes.size()) + _("\n");
				fn_str += _("\n");

				for(int sprite_index = 0; sprite_index < project->stages[stage_index].layers[layer_index].layer_sprites.size(); sprite_index++)
				{
					wxString spr_index_str = wxString::Format(_("%i"), sprite_layer_start_index);


					wxString spr_var_str = _("Nirvana_Stage_Sprites[") + spr_index_str + _("]");
					int base_index = project->getLayerSpriteBaseIndex(stage_index, layer_index, sprite_index);
					wxString base_name = wxString(project->getSpriteBaseName(base_index));
					wxString spr_name = wxString(project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].sprite_name);

					fn_str += _("\t\'------- SPRITE (\"") + spr_name + _("\") -------\n");
					fn_str += _("\tNirvana_Stage_Sprites[") + spr_index_str + _("] = Nirvana_CreateSprite(\"") + base_name + _("\", \"") + spr_name + _("\")\n");
					fn_str += _("\n");

					wxString spr_id_str = spr_var_str + _(".Sprite_ID");

					wxString collision_spr_id = spr_id_str;

					if(project->sprite_base[base_index].object.physics.detached)
                    {
                        collision_spr_id = spr_var_str + _(".Detached_Sprite_ID");
                    }

					fn_str += _("\t\'Base Settings\n");

					wxString body_type_str = _("SPRITE_TYPE_STATIC");
					if(project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].body_type == SPRITE_TYPE_DYNAMIC)
						body_type_str = _("SPRITE_TYPE_DYNAMIC");
					else if(project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].body_type == SPRITE_TYPE_KINEMATIC)
						body_type_str = _("SPRITE_TYPE_KINEMATIC");

					fn_str += _("\tSetSpriteType(") + collision_spr_id + _(", ") + body_type_str + _(")\n");

					wxString sprite_animation_name = wxString(project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].animation_name).Upper().Trim();
					int sprite_animation_index = -1;
					for(int ani_index = 0; ani_index < project->sprite_base[base_index].object.animation.size(); ani_index++)
					{
						if(wxString(project->sprite_base[base_index].object.animation[ani_index].name).Upper().Trim().compare(sprite_animation_name)==0)
						{
							sprite_animation_index = ani_index;
							break;
						}
					}

					if(sprite_animation_index >= 0)
						fn_str += _("\tSetSpriteAnimation(") + spr_id_str + _(", ") + wxString::Format(_("%i"), sprite_animation_index) + _(", -1)\n");

					fn_str += _("\n");

					wxString pos_x_str = wxString::Format(_("%i"), project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].position.X);
					wxString pos_y_str = wxString::Format(_("%i"), project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].position.Y);
					wxString scale_x_str = wxString::FromDouble((double)project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].scale.X);
					wxString scale_y_str = wxString::FromDouble((double)project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].scale.Y);
					wxString angle_str = wxString::FromDouble((double)(360-project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].angle));
					fn_str += _("\t\'Shape\n");

					if(project->sprite_base[base_index].object.physics.shape_type == SPRITE_SHAPE_BOX)
					{
						fn_str += _("\t") + _("SetSpriteShape(") + collision_spr_id + _(", SPRITE_SHAPE_BOX)\n");

						wxString off_x_str = wxString::Format(_("%i"), project->sprite_base[base_index].object.physics.offset_x);
						wxString off_y_str = wxString::Format(_("%i"), project->sprite_base[base_index].object.physics.offset_y);
						wxString box_width_str = wxString::Format(_("%i"), project->sprite_base[base_index].object.physics.box_width);
						wxString box_height_str = wxString::Format(_("%i"), project->sprite_base[base_index].object.physics.box_height);
						fn_str += _("\t") + _("SetSpriteShapeOffset(") + collision_spr_id + _(", ") + off_x_str + _(", ") + off_y_str + _(")\n");
						fn_str += _("\t") + _("SetSpriteBox(") + collision_spr_id + _(", ") + box_width_str + _(", ") + box_height_str + _(")\n");
					}
					else if(project->sprite_base[base_index].object.physics.shape_type == SPRITE_SHAPE_CIRCLE)
					{
						fn_str += _("\t") + _("SetSpriteShape(") + collision_spr_id + _(", SPRITE_SHAPE_CIRCLE)\n");

						wxString off_x_str = wxString::Format(_("%i"), project->sprite_base[base_index].object.physics.offset_x);
						wxString off_y_str = wxString::Format(_("%i"), project->sprite_base[base_index].object.physics.offset_y);
						wxString radius_str = wxString::FromDouble(project->sprite_base[base_index].object.physics.radius);
						fn_str += _("\t") + _("SetSpriteShapeOffset(") + collision_spr_id + _(", ") + off_x_str + _(", ") + off_y_str + _(")\n");
						fn_str += _("\t") + _("SetSpriteRadius(") + collision_spr_id + _(", ") + radius_str + _(")\n");
					}
					else if(project->sprite_base[base_index].object.physics.shape_type == SPRITE_SHAPE_CHAIN || project->sprite_base[base_index].object.physics.shape_type == SPRITE_SHAPE_POLYGON)
					{
						if(project->sprite_base[base_index].object.physics.shape_type == SPRITE_SHAPE_CHAIN)
							fn_str += _("\t") + _("SetSpriteShape(") + collision_spr_id + _(", SPRITE_SHAPE_CHAIN)\n");
						else
							fn_str += _("\t") + _("SetSpriteShape(") + collision_spr_id + _(", SPRITE_SHAPE_POLYGON)\n");

						wxString shape_x_str = _("sprite_shape_x_") + wxString::Format(_("%i"), sprite_layer_start_index);
						wxString shape_y_str = _("sprite_shape_y_") + wxString::Format(_("%i"), sprite_layer_start_index);

						int shape_size = project->sprite_base[base_index].object.physics.points.size();
						shape_size = shape_size < 1 ? 1 : shape_size;

						fn_str += (_("\tDim ")) + shape_x_str + _("[") + wxString::Format(_("%i"), shape_size) + _("]\n");
						fn_str += (_("\tDim ")) + shape_y_str + _("[") + wxString::Format(_("%i"), shape_size) + _("]\n");
						fn_str += _("\n");

						for(int pt_index = 0; pt_index < shape_size; pt_index++)
						{
							fn_str += _("\t") + shape_x_str + _("[") + wxString::Format(_("%i"), pt_index) + _("] = ") + wxString::Format(_("%i"), project->sprite_base[base_index].object.physics.points[pt_index].X) + _("\n");
							fn_str += _("\t") + shape_y_str + _("[") + wxString::Format(_("%i"), pt_index) + _("] = ") + wxString::Format(_("%i"), project->sprite_base[base_index].object.physics.points[pt_index].Y) + _("\n");
							fn_str += _("\n");
						}

						if(project->sprite_base[base_index].object.physics.shape_type == SPRITE_SHAPE_CHAIN)
						{
							wxString prev_x_str = _("0");
							wxString prev_y_str = _("0");

							wxString next_x_str = _("0");
							wxString next_y_str = _("0");

							if(shape_size > 0)
							{
								prev_x_str = wxString::Format(_("%i"), project->sprite_base[base_index].object.physics.points[0].X - 1);
								prev_y_str = wxString::Format(_("%i"), project->sprite_base[base_index].object.physics.points[0].Y - 1);

								next_x_str = wxString::Format(_("%i"), project->sprite_base[base_index].object.physics.points[shape_size-1].X +1);
								next_y_str = wxString::Format(_("%i"), project->sprite_base[base_index].object.physics.points[shape_size-1].Y -1);
							}

							fn_str += _("\t") + _("SetSpriteChain(") + collision_spr_id + _(", ") + shape_x_str + _(", ") + shape_y_str + _(", ") + wxString::Format(_("%i"), shape_size) + _(", ") +
																							  prev_x_str + _(", ") + prev_y_str + _(", ") + next_x_str + _(", ") + next_y_str + _(")\n");
						}
						else
						{
							fn_str += _("\t") + _("SetSpritePolygon(") + collision_spr_id + _(", ") + shape_x_str + _(", ") + shape_y_str + _(", ") + wxString::Format(_("%i"), shape_size) + _(")\n");
						}
					}

					fn_str += _("\n");

					fn_str +=_("\t\'Transform\n");
					fn_str += _("\tSetSpritePosition(") + collision_spr_id + _(", ") + pos_x_str + _(", ") + pos_y_str + _(")\n");
					fn_str += _("\tSetSpriteScale(") + collision_spr_id + _(", ") + scale_x_str + _(", ") + scale_y_str + _(")\n");
					fn_str += _("\tSetSpriteRotation(") + collision_spr_id + _(", ") + angle_str + _(")\n");
					fn_str += _("\n");

					fn_str +=_("\t\'Render Settings\n");
					fn_str += _("\tSetSpriteAlpha(") + spr_id_str + _(", ") + wxString::Format(_("%i"), (int)project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].alpha) + _(")\n");
					fn_str += _("\tSetSpriteVisible(") + spr_id_str + _(", ") + (project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].visible ? _("TRUE") : _("FALSE")) + _(")\n");

					fn_str += _("\n");

					sprite_layer_start_index++;
					stage_sprite_array_size = sprite_layer_start_index > stage_sprite_array_size ? sprite_layer_start_index : stage_sprite_array_size;
				}

				for(int shape_index = 0; shape_index < project->stages[stage_index].layers[layer_index].layer_shapes.size(); shape_index++)
				{
					wxString shape_index_str = wxString::Format(_("%i"), shape_start_index);

					wxString shape_var_str = _("Nirvana_Stage_Shapes[") + shape_index_str + _("]");

					wxString shape_name = wxString(project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].shape_name);

					fn_str += _("\t\'------- SHAPE (\"") + shape_name + _("\") -------\n");
					fn_str += _("\tNirvana_Stage_Shapes[") + shape_index_str + _("].Name$ = \"") + shape_name + _("\"\n");
					fn_str += _("\tNirvana_Stage_Shapes[") + shape_index_str + _("].Sprite_ID = CreateSprite(-1, 1, 1)\n");
					fn_str += _("\n");

					wxString spr_id_str = shape_var_str + _(".Sprite_ID");
					fn_str += _("\t\'Base Settings\n");

					wxString body_type_str = _("SPRITE_TYPE_STATIC");
					fn_str += _("\tSetSpriteType(") + spr_id_str + _(", ") + body_type_str + _(")\n");
					fn_str += _("\tSetSpriteSolid(") + spr_id_str + _(", TRUE)\n");

					fn_str += _("\t\'Shape\n");
					if(project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].shape_type == SPRITE_SHAPE_BOX)
					{
						fn_str += _("\t") + shape_var_str + _(".ShapeType = SPRITE_SHAPE_BOX\n");
						fn_str += _("\t") + _("SetSpriteShape(") + spr_id_str + _(", ") + shape_var_str + _(".ShapeType)\n");

						wxString off_x_str = wxString::Format(_("%i"), project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].offset_x);
						wxString off_y_str = wxString::Format(_("%i"), project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].offset_y);
						wxString box_width_str = wxString::Format(_("%i"), project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].box_width);
						wxString box_height_str = wxString::Format(_("%i"), project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].box_height);
						fn_str += _("\t") + _("SetSpriteShapeOffset(") + spr_id_str + _(", ") + off_x_str + _(", ") + off_y_str + _(")\n");
						fn_str += _("\t") + _("SetSpriteBox(") + spr_id_str + _(", ") + box_width_str + _(", ") + box_height_str + _(")\n");
					}
					else if(project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].shape_type == SPRITE_SHAPE_CIRCLE)
					{
						fn_str += _("\t") + shape_var_str + _(".ShapeType = SPRITE_SHAPE_CIRCLE\n");
						fn_str += _("\t") + _("SetSpriteShape(") + spr_id_str + _(", ") + shape_var_str + _(".ShapeType)\n");

						wxString off_x_str = wxString::Format(_("%i"), project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].offset_x);
						wxString off_y_str = wxString::Format(_("%i"), project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].offset_y);
						wxString radius_str = wxString::FromDouble(project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].radius);
						fn_str += _("\t") + _("SetSpriteShapeOffset(") + spr_id_str + _(", ") + off_x_str + _(", ") + off_y_str + _(")\n");
						fn_str += _("\t") + _("SetSpriteRadius(") + spr_id_str + _(", ") + radius_str + _(")\n");
					}
					else if(project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].shape_type == SPRITE_SHAPE_CHAIN || project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].shape_type == SPRITE_SHAPE_POLYGON)
					{
						if(project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].shape_type == SPRITE_SHAPE_CHAIN)
							fn_str += _("\t") + shape_var_str + _(".ShapeType = SPRITE_SHAPE_CHAIN\n");
						else
							fn_str += _("\t") + shape_var_str + _(".ShapeType = SPRITE_SHAPE_POLYGON\n");

						fn_str += _("\t") + _("SetSpriteShape(") + spr_id_str + _(", ") + shape_var_str + _(".ShapeType)\n");

						wxString shape_x_str = _("stage_shape_x_") + wxString::Format(_("%i"), shape_start_index);
						wxString shape_y_str = _("stage_shape_y_") + wxString::Format(_("%i"), shape_start_index);

						int shape_size = project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].points.size();
						shape_size = shape_size < 1 ? 1 : shape_size;

						fn_str += (_("\tDim ")) + shape_x_str + _("[") + wxString::Format(_("%i"), shape_size) + _("]\n");
						fn_str += (_("\tDim ")) + shape_y_str + _("[") + wxString::Format(_("%i"), shape_size) + _("]\n");
						fn_str += _("\n");

						for(int pt_index = 0; pt_index < shape_size; pt_index++)
						{
							fn_str += _("\t") + shape_x_str + _("[") + wxString::Format(_("%i"), pt_index) + _("] = ") + wxString::Format(_("%i"), project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].points[pt_index].X) + _("\n");
							fn_str += _("\t") + shape_y_str + _("[") + wxString::Format(_("%i"), pt_index) + _("] = ") + wxString::Format(_("%i"), project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].points[pt_index].Y) + _("\n");
							fn_str += _("\n");
						}

						if(project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].shape_type == SPRITE_SHAPE_CHAIN)
						{
							wxString prev_x_str = _("0");
							wxString prev_y_str = _("0");

							wxString next_x_str = _("0");
							wxString next_y_str = _("0");

							if(shape_size > 0)
							{
								prev_x_str = wxString::Format(_("%i"), project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].points[0].X - 1);
								prev_y_str = wxString::Format(_("%i"), project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].points[0].Y - 1);

								next_x_str = wxString::Format(_("%i"), project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].points[shape_size-1].X +1);
								next_y_str = wxString::Format(_("%i"), project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].points[shape_size-1].Y -1);
							}

							fn_str += _("\t") + _("SetSpriteChain(") + spr_id_str + _(", ") + shape_x_str + _(", ") + shape_y_str + _(", ") + wxString::Format(_("%i"), shape_size) + _(", ") +
																							  prev_x_str + _(", ") + prev_y_str + _(", ") + next_x_str + _(", ") + next_y_str + _(")\n");
						}
						else
						{
							fn_str += _("\t") + _("SetSpritePolygon(") + spr_id_str + _(", ") + shape_x_str + _(", ") + shape_y_str + _(", ") + wxString::Format(_("%i"), shape_size) + _(")\n");
						}
					}

					fn_str += _("\n");

					fn_str +=_("\t\'Transform\n");
					fn_str += _("\tSetSpritePosition(") + spr_id_str + _(",  0, 0) \'Set to (0,0) so that offset will be world position\n");
					fn_str += _("\tSetSpriteVisible(") + spr_id_str + _(", FALSE) \'Image is -1 so it wouldn\'t render anyway\n");

					fn_str += _("\n");

					shape_start_index++;
					stage_shape_array_size = shape_start_index > stage_shape_array_size ? shape_start_index : stage_shape_array_size;
				}
			}
			else if(project->stages[stage_index].layers[layer_index].layer_type == LAYER_TYPE_TILEMAP)
			{
				fn_str += _("\tNirvana_Stage_Layers[") + layer_list_index_str + _("].Ref_Canvas = ") + _("OpenCanvas(NIRVANA_WINDOW_WIDTH, NIRVANA_WINDOW_HEIGHT, vp_x, vp_y, vp_w, vp_h, 1)\n");
				wxString tmap_data_filename = _("tm") + wxString::Format(_("%i"), tmap_data_index) + _(".data");
				tmap_data_index++;

				fn_str += _("\n");
				if(project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows.size() > 0)
				{
					if(project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows[0].tile.size() > 0)
					{
						fn_str += _("\t\'------- TILEMAP -------\n");
						wxString tset_name_str = wxString(project->stages[stage_index].layers[layer_index].layer_map.nv_tileset_name);
						wxString tmap_width_str = wxString::Format(_("%i"), (int)project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows[0].tile.size());
						wxString tmap_height_str = wxString::Format(_("%i"), (int)project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows.size());
						fn_str += _("\tNirvana_Stage_Layers[") + layer_list_index_str + _("].Layer_TileMap = Nirvana_CreateTileMap(\"") + tset_name_str + _("\", ") + tmap_width_str + _(", ") + tmap_height_str + _(")\n");
						fn_str += _("\n");

						fn_str += _("\t") + _("f = OpenFile(NIRVANA_DATA_DIR$ + \"") + tmap_data_filename + ("\", BINARY_INPUT)\n");
						fn_str += _("\t") + _("For y = 0 To ") + wxString::Format(_("%i"), (int)(project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows.size()-1)) + _("\n");
						fn_str += _("\t\t") + _("For x = 0 To ") + wxString::Format(_("%i"), (int)(project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows[0].tile.size()-1)) + _("\n");
						fn_str += _("\t\t\t") + _("SetTile(Nirvana_Stage_Layers[") + layer_list_index_str + _("].Layer_TileMap.TileMap_ID, Nirvana_Read32(f), x, y)\n");
						fn_str += _("\t\t") + _("Next\n");
						fn_str += _("\t") + _("Next\n");
						fn_str += _("\t") + _("CloseFile(f)\n");
					}
				}

				wxFileName tm_fname(project->getDir());
				tm_fname.AppendDir(_("data"));
				if(!tm_fname.Exists())
					wxMkdir(tm_fname.GetAbsolutePath());

				tm_fname.SetFullName(tmap_data_filename);
				wxFile tmap_file(tm_fname.GetAbsolutePath(), wxFile::write);

				if(tmap_file.IsOpened())
				{
					if(project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows.size() > 0)
					{
						int* t_value = new int[project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows[0].tile.size()];

						for(int t_row = 0; t_row < project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows.size(); t_row++)
						{
							for(int t_col = 0; t_col < project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows[t_row].tile.size(); t_col++)
							{
								t_value[t_col] = project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows[t_row].tile[t_col];
							}
							tmap_file.Write(t_value, sizeof(int) * project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows[t_row].tile.size());
						}
					}

					tmap_file.Close();
				}
			}
			else if(project->stages[stage_index].layers[layer_index].layer_type == LAYER_TYPE_ISO_TILEMAP)
			{
				fn_str += _("\tNirvana_Stage_Layers[") + layer_list_index_str + _("].Ref_Canvas = ") + _("OpenCanvas(NIRVANA_WINDOW_WIDTH, NIRVANA_WINDOW_HEIGHT, vp_x, vp_y, vp_w, vp_h, 1)\n");
				wxString tmap1_data_filename = _("tm") + wxString::Format(_("%i"), tmap_data_index) + _(".data");
				tmap_data_index++;

				wxString tmap2_data_filename = _("tm") + wxString::Format(_("%i"), tmap_data_index) + _(".data");
				tmap_data_index++;

				fn_str += _("\n");
				if(project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows.size() > 0)
				{
					if(project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows[0].tile.size() > 0)
					{
						fn_str += _("\t\'------- ISO TILEMAP 1 -------\n");
						wxString tset_name_str = wxString(project->stages[stage_index].layers[layer_index].layer_map.nv_tileset_name);
						wxString tmap_width_str = wxString::Format(_("%i"), (int)project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows[0].tile.size());
						wxString tmap_height_str = wxString::Format(_("%i"), (int)project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows.size());
						fn_str += _("\tNirvana_Stage_Layers[") + layer_list_index_str + _("].Layer_TileMap = Nirvana_CreateTileMap(\"") + tset_name_str + _("\", ") + tmap_width_str + _(", ") + tmap_height_str + _(")\n");
						fn_str += _("\n");

						fn_str += _("\t") + _("f = OpenFile(NIRVANA_DATA_DIR$ + \"") + tmap1_data_filename + ("\", BINARY_INPUT)\n");
						fn_str += _("\t") + _("For y = 0 To ") + wxString::Format(_("%i"), (int)(project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows.size()-1)) + _("\n");
						fn_str += _("\t\t") + _("For x = 0 To ") + wxString::Format(_("%i"), (int)(project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows[0].tile.size()-1)) + _("\n");
						fn_str += _("\t\t\t") + _("SetTile(Nirvana_Stage_Layers[") + layer_list_index_str + _("].Layer_TileMap.TileMap_ID, Nirvana_Read32(f), x, y)\n");
						fn_str += _("\t\t") + _("Next\n");
						fn_str += _("\t") + _("Next\n");
						fn_str += _("\t") + _("CloseFile(f)\n");
					}
				}

				if(project->stages[stage_index].layers[layer_index].layer_map.tile_map2.rows.size() > 0)
				{
					if(project->stages[stage_index].layers[layer_index].layer_map.tile_map2.rows[0].tile.size() > 0)
					{
						fn_str += _("\t\'------- ISO TILEMAP 2 -------\n");
						wxString tset_name_str = wxString(project->stages[stage_index].layers[layer_index].layer_map.nv_tileset_name);
						wxString tmap_width_str = wxString::Format(_("%i"), (int)project->stages[stage_index].layers[layer_index].layer_map.tile_map2.rows[0].tile.size());
						wxString tmap_height_str = wxString::Format(_("%i"), (int)project->stages[stage_index].layers[layer_index].layer_map.tile_map2.rows.size());
						fn_str += _("\tNirvana_Stage_Layers[") + layer_list_index_str + _("].Layer_TileMap2 = Nirvana_CreateTileMap(\"") + tset_name_str + _("\", ") + tmap_width_str + _(", ") + tmap_height_str + _(")\n");
						fn_str += _("\n");

						fn_str += _("\t") + _("f = OpenFile(NIRVANA_DATA_DIR$ + \"") + tmap2_data_filename + ("\", BINARY_INPUT)\n");
						fn_str += _("\t") + _("For y = 0 To ") + wxString::Format(_("%i"), (int)(project->stages[stage_index].layers[layer_index].layer_map.tile_map2.rows.size()-1)) + _("\n");
						fn_str += _("\t\t") + _("For x = 0 To ") + wxString::Format(_("%i"), (int)(project->stages[stage_index].layers[layer_index].layer_map.tile_map2.rows[0].tile.size()-1)) + _("\n");
						fn_str += _("\t\t\t") + _("SetTile(Nirvana_Stage_Layers[") + layer_list_index_str + _("].Layer_TileMap2.TileMap_ID, Nirvana_Read32(f), x, y)\n");
						fn_str += _("\t\t") + _("Next\n");
						fn_str += _("\t") + _("Next\n");
						fn_str += _("\t") + _("CloseFile(f)\n");
					}
				}

				wxFileName tm1_fname(project->getDir());
				tm1_fname.AppendDir(_("data"));
				if(!tm1_fname.Exists())
					wxMkdir(tm1_fname.GetAbsolutePath());

				tm1_fname.SetFullName(tmap1_data_filename);
				wxFile tmap1_file(tm1_fname.GetAbsolutePath(), wxFile::write);

				if(tmap1_file.IsOpened())
				{
					if(project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows.size() > 0)
					{
						int* t_value = new int[project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows[0].tile.size()];

						for(int t_row = 0; t_row < project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows.size(); t_row++)
						{
							for(int t_col = 0; t_col < project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows[t_row].tile.size(); t_col++)
							{
								t_value[t_col] = project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows[t_row].tile[t_col];
							}
							tmap1_file.Write(t_value, sizeof(int) * project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows[t_row].tile.size());
						}
					}

					tmap1_file.Close();
				}


				wxFileName tm2_fname(project->getDir());
				tm2_fname.AppendDir(_("data"));
				if(!tm2_fname.Exists())
					wxMkdir(tm2_fname.GetAbsolutePath());

				tm2_fname.SetFullName(tmap2_data_filename);
				wxFile tmap2_file(tm2_fname.GetAbsolutePath(), wxFile::write);

				if(tmap2_file.IsOpened())
				{
					if(project->stages[stage_index].layers[layer_index].layer_map.tile_map2.rows.size() > 0)
					{
						int* t_value = new int[project->stages[stage_index].layers[layer_index].layer_map.tile_map2.rows[0].tile.size()];

						for(int t_row = 0; t_row < project->stages[stage_index].layers[layer_index].layer_map.tile_map2.rows.size(); t_row++)
						{
							for(int t_col = 0; t_col < project->stages[stage_index].layers[layer_index].layer_map.tile_map2.rows[t_row].tile.size(); t_col++)
							{
								t_value[t_col] = project->stages[stage_index].layers[layer_index].layer_map.tile_map2.rows[t_row].tile[t_col];
							}
							tmap2_file.Write(t_value, sizeof(int) * project->stages[stage_index].layers[layer_index].layer_map.tile_map2.rows[t_row].tile.size());
						}
					}

					tmap2_file.Close();
				}

			}

			fn_str += _("\n");
		}

		fn_str += _("\tReturn nv_stage\n");
		fn_str += _("End Function\n");
		fn_str += _("\n");

		fn_def.push_back(fn_str);
	}

	pfile.Write(_("\n"));

	pfile.Write(nv_constants);
	pfile.Write(_("\n"));

	pfile.Write(_("NIRVANA_WINDOW_WIDTH = 320\n"));
	pfile.Write(_("NIRVANA_WINDOW_HEIGHT = 200\n"));
	pfile.Write(_("\n\n"));


	pfile.Write(_("Dim Nirvana_Stage_Sprites[") + wxString::Format(_("%i"), stage_sprite_array_size) + _("] As Nirvana_Sprite\n"));
	pfile.Write(_("Dim Nirvana_Stage_Shape_Points[") + wxString::Format(_("%i"), stage_shape_point_array_size) + _("] As Nirvana_Vector2D\n"));
	pfile.Write(_("Dim Nirvana_Stage_Shapes[") + wxString::Format(_("%i"), stage_shape_array_size) + _("] As Nirvana_Shape\n"));
	pfile.Write(_("Dim Nirvana_Stage_Layers[") + wxString::Format(_("%i"), stage_layer_array_size) + _("] As Nirvana_Layer\n"));
	pfile.Write(_("\n"));
	pfile.Write(_("For i = 0 To ") + wxString::Format(_("%i"), stage_layer_array_size-1) + _("\n"));
	pfile.Write(_("\tNirvana_Stage_Layers[i].Ref_Canvas = -1\n"));
	pfile.Write(_("\tNirvana_Stage_Layers[i].Layer_TileMap.Tileset_ID = -1\n"));
	pfile.Write(_("\tNirvana_Stage_Layers[i].Layer_TileMap.TileMap_ID = -1\n"));
	pfile.Write(_("\tNirvana_Stage_Layers[i].Layer_TileMap2.Tileset_ID = -1\n"));
	pfile.Write(_("\tNirvana_Stage_Layers[i].Layer_TileMap2.TileMap_ID = -1\n"));
	pfile.Write(_("\tNirvana_Stage_Layers[i].Bkg.Image_ID = -1\n"));
	pfile.Write(_("Next\n\n"));

	pfile.Write(_("For i = 0 To ") + wxString::Format(_("%i"), stage_sprite_array_size-1) + _("\n"));
	pfile.Write(_("\tNirvana_Stage_Sprites[i].Sprite_ID = -1\n"));
	pfile.Write(_("Next\n\n"));

	pfile.Write(_("For i = 0 To ") + wxString::Format(_("%i"), stage_shape_array_size-1) + _("\n"));
	pfile.Write(_("\tNirvana_Stage_Shapes[i].Sprite_ID = -1\n"));
	pfile.Write(_("Next\n\n"));

	pfile.Write(_("Dim Nirvana_ActiveStage As Nirvana_Stage : Nirvana_ActiveStage.Active = FALSE\n"));
	pfile.Write(_("\n"));

	pfile.Write(_("\'This is a utility function for reading binary data from tile maps\n"));
	pfile.Write(_("Function Nirvana_Read32(stream)\n"));
	pfile.Write(_("\t\tDim byte_array[4]\n"));
	pfile.Write(_("\t\tbyte_array[3] = ReadByte(stream)\n"));
	pfile.Write(_("\t\tbyte_array[2] = ReadByte(stream)\n"));
	pfile.Write(_("\t\tbyte_array[1] = ReadByte(stream)\n"));
	pfile.Write(_("\t\tbyte_array[0] = ReadByte(stream)\n"));
	pfile.Write(_("\t\tReturn (byte_array[0] shl 24) + (byte_array[1] shl 16) + (byte_array[2] shl 8) + byte_array[3]\n"));
	pfile.Write(_("End Function\n"));
	pfile.Write(_("\n"));

	//Nirvana_ClearStage function
	pfile.Write(_("Sub Nirvana_ClearStage()\n"));
	pfile.Write(_("\tIf Not Nirvana_ActiveStage.Active Then\n"));
	pfile.Write(_("\t\tReturn\n"));
	pfile.Write(_("\tEnd If\n\n"));
	pfile.Write(_("\tNirvana_ActiveStage.Stage_Offset.X = 0\n"));
	pfile.Write(_("\tNirvana_ActiveStage.Stage_Offset.Y = 0\n"));
	pfile.Write(_("\tFor i = 0 To Nirvana_ActiveStage.Layer_Count-1\n\n"));
	pfile.Write(_("\t\tCloseCanvas(Nirvana_Stage_Layers[i].Ref_Canvas)\n"));
	pfile.Write(_("\t\tNirvana_Stage_Layers[i].Ref_Canvas = -1\n\n"));
	pfile.Write(_("\t\tIf ImageExists(Nirvana_Stage_Layers[i].Bkg.Image_ID) Then\n"));
	pfile.Write(_("\t\t\tDeleteImage(Nirvana_Stage_Layers[i].Bkg.Image_ID)\n"));
	pfile.Write(_("\t\t\tNirvana_Stage_Layers[i].Bkg.Image_ID = -1\n"));
	pfile.Write(_("\t\tEnd If\n\n"));
	pfile.Write(_("\t\tIf Nirvana_Stage_Layers[i].LayerType = NIRVANA_LAYER_TYPE_TILEMAP Then\n"));
	pfile.Write(_("\t\t\tDeleteTileMap(Nirvana_Stage_Layers[i].Layer_TileMap.TileMap_ID)\n"));
	pfile.Write(_("\t\t\tDeleteTileSet(Nirvana_Stage_Layers[i].Layer_TileMap.Tileset_ID)\n"));
	pfile.Write(_("\t\tElseIf Nirvana_Stage_Layers[i].LayerType = NIRVANA_LAYER_TYPE_ISO_TILEMAP Then\n"));
	pfile.Write(_("\t\t\tDeleteTileMap(Nirvana_Stage_Layers[i].Layer_TileMap.TileMap_ID)\n"));
	pfile.Write(_("\t\t\tDeleteTileMap(Nirvana_Stage_Layers[i].Layer_TileMap2.TileMap_ID)\n"));
	pfile.Write(_("\t\t\tDeleteTileSet(Nirvana_Stage_Layers[i].Layer_TileMap.Tileset_ID)\n"));
	pfile.Write(_("\t\tEnd If\n\n"));
	pfile.Write(_("\t\tNirvana_Stage_Layers[i].Layer_TileMap.TileMap_ID = -1\n"));
	pfile.Write(_("\t\tNirvana_Stage_Layers[i].Layer_TileMap2.TileMap_ID = -1\n"));
	pfile.Write(_("\t\tNirvana_Stage_Layers[i].Layer_TileMap.Tileset_ID = -1\n\n"));
	pfile.Write(_("\t\tNirvana_Stage_Layers[i].Layer_TileMap2.Tileset_ID = -1\n\n"));
	pfile.Write(_("\tNext\n\n"));

	pfile.Write(_("\tWhile Stack_Size_N(Nirvana_Tileset_Image_Stack) > 0\n"));
	pfile.Write(_("\t\timg_id = Pop_N(Nirvana_Tileset_Image_Stack)\n"));
	pfile.Write(_("\t\tDeleteImage(img_id)\n"));
	pfile.Write(_("\tWend\n\n"));
	pfile.Write(_("\tWhile Stack_Size_N(Nirvana_Sprite_Image_Stack) > 0\n"));
	pfile.Write(_("\t\timg_id = Pop_N(Nirvana_Sprite_Image_Stack)\n"));
	pfile.Write(_("\t\tDeleteImage(img_id)\n"));
	pfile.Write(_("\tWend\n\n"));

	//Set Tileset IDs to -1
	for(int tset_index = 0; tset_index < project->tileset.size(); tset_index++)
	{
		wxString tset_id_str = _("Nirvana_Tileset_ID_") + wxString::Format(_("%i"), tset_index);
		pfile.Write(_("\t") + tset_id_str + _(" = -1\n"));

		wxString ts_img = _("Nirvana_Tileset_Image_") + wxString::Format(_("%i"), tset_index);
		pfile.Write(_("\t") + ts_img + _(" = -1\n\n"));
	}

	//Set SpriteDef IDs to -1
	for(int base_index = 0; base_index < project->sprite_base.size(); base_index++)
	{
		wxString spr_img = _("Nirvana_Sprite_Image_") + wxString::Format(_("%i"), base_index);
		pfile.Write(_("\t") + spr_img + _(" = -1\n"));
	}

	pfile.Write(_("\tNirvana_ActiveStage.Active = FALSE\n\n"));
	pfile.Write(_("End Sub\n"));
	pfile.Write(_("\n"));

	//stage functions
	for(int i = 0; i < fn_def.size(); i++)
	{
		pfile.Write(fn_def[i]);
		pfile.Write(_("\n"));
	}

	pfile.Write(_("\n"));
	pfile.Write(_("Function Nirvana_LoadStage(stage_name$, viewport_x, viewport_y, viewport_w, viewport_h)\n"));
	pfile.Write(_("\tGetWindowSize(NIRVANA_WINDOW_WIDTH, NIRVANA_WINDOW_HEIGHT)\n\n"));
	pfile.Write(_("\tSelect Case stage_name$\n"));
	pfile.Write(_("\n"));
	for(int stage_index = 0; stage_index < project->stages.size(); stage_index++)
	{
		pfile.Write(_("\tCase \"") + wxString(project->stages[stage_index].stage_name) + _("\"\n"));
		pfile.Write(_("\t\tNirvana_ActiveStage = ") + stage_build_fn[stage_index] + _("(viewport_x, viewport_y, viewport_w, viewport_h)\n"));
		pfile.Write(_("\n"));
	}

	pfile.Write(_("\tDefault\n"));
	pfile.Write(_("\t\tReturn FALSE\n"));
	pfile.Write(_("\tEnd Select\n"));
	pfile.Write(_("\n"));
	pfile.Write(_("\tNirvana_ActiveStage.Active = TRUE\n"));
	pfile.Write(_("\tNirvana_ActiveStage.Stage_Offset.X = 0\n"));
	pfile.Write(_("\tNirvana_ActiveStage.Stage_Offset.Y = 0\n"));
	pfile.Write(_("\tNirvana_ActiveStage.Viewport_Size.Width = viewport_w\n"));
	pfile.Write(_("\tNirvana_ActiveStage.Viewport_Size.Height = viewport_h\n"));
	pfile.Write(_("\tReturn TRUE\n"));
	pfile.Write(_("End Function\n"));
	pfile.Write(_("\n\n"));

	pfile.Close();

	return true;
}

void NirvanaEditor_MainFrame::OnGenerate( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	if(!project->active)
	{
		wxMessageBox(_("You must have an open project to generate."));
		return;
	}

	//Shared Constants
	wxFileName fname(project->getDir());
	fname.SetFullName(_("nirvana_constants.bas"));

	wxFile constant_file(fname.GetAbsolutePath(), wxFile::write);

	if(!constant_file.IsOpened())
		return;

	constant_file.Write(_("NIRVANA_PROJECT_BASE_DIR$ = Dir$()\n"));
	constant_file.Write(_("NIRVANA_PATH_SEPARATOR$ = \"/\" : If OS$() = \"WINDOWS\" Then : NIRVANA_PATH_SEPARATOR$ = \"\\\\\" : End If \n"));

	constant_file.Close();


	if(!generateSpriteDefinitions())
	{
		wxMessageBox(_("Generate ERROR: Failed to generate sprite definitions"));
		return;
	}

	if(!generateTilesets())
	{
		wxMessageBox(_("Generate ERROR: Failed to generate tilesets"));
		return;
	}

	if(!generateStages())
	{
		wxMessageBox(_("Generate ERROR: Failed to generate stages"));
		return;
	}

	//Main Include
	wxFileName src_inc_fname(wxStandardPaths::Get().GetExecutablePath());
	src_inc_fname.AppendDir(_("export"));
	src_inc_fname.SetFullName(_("nirvana.bas"));

	wxFileName dst_inc_fname(project->getDir());
	dst_inc_fname.SetFullName(_("nirvana.bas"));

	wxCopyFile(src_inc_fname.GetAbsolutePath(), dst_inc_fname.GetAbsolutePath());



	wxFileName studio_project_path = project->project_filename_obj;
	studio_project_path.SetFullName(wxString(project->project_name) + _(".rcprj"));

	if(!studio_project_path.Exists())
	{
		wxFile pfile(studio_project_path.GetAbsolutePath(), wxFile::write);

		if(pfile.IsOpened())
		{
			pfile.Write(_("RCBASIC_STUDIO:2.0\n"));
			pfile.Write(_("PROJECT_NAME:") + wxString(project->project_name) + _("\n"));
			pfile.Write(_("PROJECT_MAIN:main.bas\n"));
			pfile.Write(_("AUTHOR:Nirvana2D\n"));
			pfile.Write(_("WEBSITE:http://www.rcbasic.com\n"));
			pfile.Write(_("DESCRIPTION:Nirvana2D Project\n"));
			pfile.Write(_("SOURCE_REL:main.bas\n"));
			pfile.Write(_("SOURCE_REL:nirvana.bas\n"));
			pfile.Write(_("SOURCE_REL:nirvana_constants.bas\n"));
			pfile.Write(_("SOURCE_REL:nirvana_spriteDef.bas\n"));
			pfile.Write(_("SOURCE_REL:nirvana_stage.bas\n"));
			pfile.Write(_("SOURCE_REL:nirvana_tileset.bas\n"));

			pfile.Close();
		}

		wxFileName template_path(wxStandardPaths::Get().GetExecutablePath());
		template_path.AppendDir(_("export"));
		template_path.SetFullName(_("template.bas"));

		wxFileName template_tgt_path = project->project_filename_obj;
		template_tgt_path.SetFullName(_("main.bas"));

		if(!template_tgt_path.Exists())
            wxCopyFile(template_path.GetAbsolutePath(), template_tgt_path.GetAbsolutePath());
	}
}

void NirvanaEditor_MainFrame::OnNewStage( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	if(!project->active)
	{
		wxMessageBox(_("You must have an open project to add a new stage."));
		return;
	}

	NirvanaEditor_NewStage_Dialog* dialog = new NirvanaEditor_NewStage_Dialog(this);

	dialog->project = project;

	PreDialog();
	dialog->ShowModal();
	PostDialog();

	if(!dialog->create_flag)
		return;

	project->createStage(dialog->stage_name.ToStdString(), dialog->tile_width, dialog->tile_height);

	int stage_index = project->getStageIndex(dialog->stage_name.ToStdString());

	if(stage_index < 0)
		return;

	project->setStageSize(stage_index, dialog->width_in_tiles, dialog->height_in_tiles);

	wxTreeItemId stage_item = m_project_treeCtrl->AppendItem(project_root_treeItem, dialog->stage_name, stage_tree_stageImage);

	stage_treeItem.push_back(stage_item);
}

void NirvanaEditor_MainFrame::OnDeleteStage( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	wxString stage_name = m_project_treeCtrl->GetItemText(m_project_treeCtrl->GetSelection());
	int stage_index = project->getStageIndex(stage_name.ToStdString());

	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	NirvanaEditor_DeleteStage_Dialog* dialog = new NirvanaEditor_DeleteStage_Dialog(this);

	dialog->setStageName(project->getStageName(stage_index));

	PreDialog();
	dialog->ShowModal();
	PostDialog();

	if(!dialog->delete_flag)
		return;

	if(stage_index == map_editor->getSelectedStage())
	{
		wxMessageBox(_("Can't delete stage while its active"));
		return;
	}

	wxString active_stage_name = wxString(project->getStageName(map_editor->getSelectedStage()));

	project->deleteStage(stage_index);

	m_project_treeCtrl->Delete( stage_treeItem[stage_index] );
	stage_treeItem.erase(stage_treeItem.begin() + stage_index);

	int active_stage_index = project->getStageIndex(active_stage_name.ToStdString());

	if(active_stage_index < 0)
		return;

	map_editor->selectStage(active_stage_index);

	//SET LAYER COMBO AND CHECKLIST
	m_layerVisible_checkList->Clear();

	for(int i = 0; i < project->getStageNumLayers(active_stage_index); i++)
	{
		m_layerVisible_checkList->AppendAndEnsureVisible(wxString(project->getLayerName(active_stage_index, i)));
		m_layerVisible_checkList->Check(i, project->getLayerVisible(active_stage_index, i));
	}
}

void NirvanaEditor_MainFrame::OnMapEdit_StageSettingsClick( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	wxString stage_name = m_project_treeCtrl->GetItemText(m_project_treeCtrl->GetSelection());
	int stage_index = project->getStageIndex(stage_name.ToStdString());

	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	NirvanaEditor_StageProperties_Dialog* dialog = new NirvanaEditor_StageProperties_Dialog(this);

	int tile_width = project->getStageTileSize(stage_index).X;
	int tile_height = project->getStageTileSize(stage_index).Y;

	int tiles_across = project->getStageSize(stage_index).X;
	int tiles_down = project->getStageSize(stage_index).Y;

	dialog->setStageProperties(stage_name, tile_width, tile_height, tiles_across, tiles_down);


	PreDialog();
	dialog->ShowModal();
	PostDialog();

	if(!dialog->set_flag)
		return;

	if(stage_index == map_editor->getSelectedStage())
	{
		m_mapEdit_stageName_staticText->SetLabelText(_("STAGE: ") + dialog->stage_name);
	}

	project->setStageName(stage_index, dialog->stage_name.ToStdString());
	project->setStageSize(stage_index, dialog->tiles_across, dialog->tiles_down);
	project->setStageSizeISO(stage_index, dialog->tiles_across, dialog->tiles_down);

	m_project_treeCtrl->SetItemText( stage_treeItem[stage_index], dialog->stage_name );

}

void NirvanaEditor_MainFrame::OnMapEdit_CopyStageClick( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	wxString stage_name = m_project_treeCtrl->GetItemText(m_project_treeCtrl->GetSelection());
	int stage_index = project->getStageIndex(stage_name.ToStdString());

	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int copy_index = project->copyStage(stage_index);

	wxTreeItemId stage_item = m_project_treeCtrl->AppendItem(project_root_treeItem, project->getStageName(copy_index), stage_tree_stageImage);

	stage_treeItem.push_back(stage_item);
}

void NirvanaEditor_MainFrame::OnMapEdit_NewLayerClick( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0)
		return;

	NirvanaEditor_NewLayer_Dialog* dialog = new NirvanaEditor_NewLayer_Dialog(this);

	int tile_width = project->getStageTileSize(stage_index).X;
	int tile_height = project->getStageTileSize(stage_index).Y;

	dialog->stage_index = stage_index;
	dialog->project = project;

	for(int i = 0; i < project->getTilesetCount(); i++)
	{
		if(tile_width == project->getTilesetTileSize(i).X && tile_height == project->getTilesetTileSize(i).Y)
			dialog->tileset_list.push_back(wxString(project->getTilesetName(i)));
	}

	dialog->refresh_list();

	PreDialog();
	dialog->ShowModal();
	PostDialog();

	if(!dialog->create_flag)
		return;

	project->addLayer(stage_index, dialog->layer_name.ToStdString(), dialog->selected_type);
	int layer_index = project->getLayerIndex(stage_index, dialog->layer_name.ToStdString());

	if(layer_index < 0)
	{
		return;
	}


	project->setLayerTileset(stage_index, layer_index, project->getTilesetIndex(dialog->selected_tileset.ToStdString()));

	map_editor->getMapViewControl()->initLayer(layer_index);

	updateMapEditor();

	m_layerVisible_checkList->AppendAndEnsureVisible(wxString(project->getLayerName(stage_index, layer_index)));
	m_layerVisible_checkList->Check(m_layerVisible_checkList->GetCount()-1, true);
	m_activeLayer_comboBox->Append(project->getLayerName(stage_index, layer_index));
}

void NirvanaEditor_MainFrame::OnMapEdit_CopyLayerClick( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = m_layerVisible_checkList->GetSelection();

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	int copy_index = project->copyLayer(stage_index, layer_index);

	if(copy_index < 0)
		return;

	map_editor->getMapViewControl()->initLayer(copy_index);

	updateMapEditor();

	wxString copy_name = wxString(project->getLayerName(stage_index, copy_index));
	m_layerVisible_checkList->AppendAndEnsureVisible(copy_name);
	m_layerVisible_checkList->Check(m_layerVisible_checkList->GetCount()-1, project->getLayerVisible(stage_index, copy_index));
	m_activeLayer_comboBox->Append(copy_name);
}

void NirvanaEditor_MainFrame::OnMapEdit_ShowAllLayersClick( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	for(int i = 0; i < project->getStageNumLayers(stage_index); i++)
	{
		project->setLayerVisible(stage_index, i, true);

		if(project->stages[stage_index].layers[i].ref_canvas >= 0 && project->stages[stage_index].layers[i].ref_canvas < map_editor->getMapViewControl()->canvas.size())
			map_editor->getMapViewControl()->setCanvasVisible(project->stages[stage_index].layers[i].ref_canvas, true);
	}

	for(int i = 0; i < m_layerVisible_checkList->GetCount(); i++)
	{
		m_layerVisible_checkList->Check(i, true);
	}
}

void NirvanaEditor_MainFrame::OnMapEdit_HideAllLayersClick( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	for(int i = 0; i < project->getStageNumLayers(stage_index); i++)
	{
		project->setLayerVisible(stage_index, i, false);

		if(project->stages[stage_index].layers[i].ref_canvas >= 0 && project->stages[stage_index].layers[i].ref_canvas < map_editor->getMapViewControl()->canvas.size())
			map_editor->getMapViewControl()->setCanvasVisible(project->stages[stage_index].layers[i].ref_canvas, false);
	}

	for(int i = 0; i < m_layerVisible_checkList->GetCount(); i++)
	{
		m_layerVisible_checkList->Check(i, false);
	}
}


void NirvanaEditor_MainFrame::OnProjectItemActivated( wxTreeEvent& event )
{
	if(!editor_init)
		return;

	wxTreeItemId selected_item = event.GetItem();
	bool is_stage = false;

	for(int i = 0; i < stage_treeItem.size(); i++)
	{
		if(selected_item == stage_treeItem[i])
		{
			is_stage = true;
			break;
		}
	}

	if(!is_stage)
		return;

	wxString item_label = m_project_treeCtrl->GetItemText(selected_item);
	int stage_index = project->getStageIndex(item_label.ToStdString());

	map_editor->getMapViewControl()->mapEdit_getContext();
	map_editor->getMapViewControl()->clearStage();
	map_editor->getMapViewControl()->mapEdit_selectTileTool_selection.clear();
	map_editor->getMapViewControl()->scroll_offset_x = 0;
	map_editor->getMapViewControl()->scroll_offset_y = 0;

	map_editor->selectStage(stage_index);
	map_editor->selectLayer(-1);

	m_mapEdit_stageName_staticText->SetLabelText(_("STAGE: ") + wxString(project->getStageName(stage_index)));



	//SET LAYER COMBO AND CHECKLIST
	m_layerVisible_checkList->Clear();
	m_activeLayer_comboBox->Clear();

	for(int i = 0; i < project->getStageNumLayers(stage_index); i++)
	{
		m_layerVisible_checkList->AppendAndEnsureVisible(wxString(project->getLayerName(stage_index, i)));
		m_layerVisible_checkList->Check(i, project->getLayerVisible(stage_index, i));

		m_activeLayer_comboBox->Append(project->getLayerName(stage_index, i));
	}

	//CLEAR SPRITE LIST
	m_mapEdit_layerSprite_listBox->Clear();

	//CLEAR SHAPE LIST
	m_mapEdit_collisionShape_listBox->Clear();

	m_layerName_textCtrl->SetValue(_(""));
	m_mapEdit_layerHScroll_spinCtrlDouble->SetValue(0);
	m_mapEdit_layerVScroll_spinCtrlDouble->SetValue(0);
	m_mapEdit_layerAlpha_spinCtrl->SetValue(0);

	//CLEAR BKG IMAGE COMBO
	m_mapEdit_canvasRenderSetting_comboBox->Clear();
	m_mapEdit_canvasImage_comboBox->Clear();
}

void NirvanaEditor_MainFrame::updateMapEditor()
{
	if(!editor_init)
		return;

	//Clear All Canvases

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	wxString selected_stage_name(project->getStageName(stage_index));

	int layer_index = map_editor->getSelectedLayer();
	wxString selected_layer_name(project->getLayerName(stage_index, layer_index));

//	m_project_treeCtrl->DeleteChildren(project_root_treeItem);
//	stage_treeItem.clear();
//
//	for(int i = 0; i < project->getStageCount(); i++)
//	{
//		stage_treeItem.push_back(m_project_treeCtrl->AppendItem(project_root_treeItem, wxString(project->getStageName(i)), stage_tree_stageImage));
//	}

	if(stage_index >= 0 && stage_index < project->getStageCount())
	{
		wxPGProperty * sprite_id = m_mapEdit_sprite_propertyGrid->GetProperty(_("sprite_id"));
		wxPGProperty * sprite_body_type = m_mapEdit_sprite_propertyGrid->GetProperty(_("body_type"));
		wxPGProperty * sprite_animation = m_mapEdit_sprite_propertyGrid->GetProperty(_("animation"));
		wxPGProperty * sprite_pos_x = m_mapEdit_sprite_propertyGrid->GetProperty(_("position_x"));
		wxPGProperty * sprite_pos_y = m_mapEdit_sprite_propertyGrid->GetProperty(_("position_y"));
		wxPGProperty * sprite_angle = m_mapEdit_sprite_propertyGrid->GetProperty(_("angle"));
		wxPGProperty * sprite_scale_x = m_mapEdit_sprite_propertyGrid->GetProperty(_("scale_x"));
		wxPGProperty * sprite_scale_y = m_mapEdit_sprite_propertyGrid->GetProperty(_("scale_y"));
		wxPGProperty * sprite_alpha = m_mapEdit_sprite_propertyGrid->GetProperty(_("alpha"));
		wxPGProperty * sprite_visible = m_mapEdit_sprite_propertyGrid->GetProperty(_("visible"));


		sprite_id->SetValueFromString(_(""));
		sprite_body_type->SetChoiceSelection(0);
		sprite_animation->SetChoices(wxPGChoices());
		sprite_pos_x->SetValue( 0 );
		sprite_pos_y->SetValue( 0 );
		sprite_angle->SetValue( 0 );
		sprite_scale_x->SetValue( 0 );
		sprite_scale_y->SetValue( 0 );
		sprite_alpha->SetValueFromInt( 0 );
		sprite_visible->SetValue( false );

		m_mapEdit_layerSprite_listBox->Clear();
		m_mapEdit_collisionShape_listBox->Clear();

		m_mapEdit_shapeName_textCtrl->SetValue(_(""));

		m_mapEdit_shapeEdit_simplebook->SetSelection(0);

		map_editor->getTileSelectControl()->mapEdit_layerType = project->getLayerType(stage_index, layer_index);

		Nirvana_Map_Layer current_layer = project->getStageLayer(stage_index, layer_index);

		m_mapEdit_canvasRenderSetting_comboBox->Clear();
		m_mapEdit_canvasImage_comboBox->Clear();

		m_mapEdit_layerTileset_staticText->SetLabelText(_("[NA]"));

		switch(project->getLayerType(stage_index, layer_index))
		{
		    case LAYER_TYPE_ISO_TILEMAP:
			case LAYER_TYPE_TILEMAP:
			{
				m_mapEdit_layerTileset_staticText->SetLabelText( wxString(project->getTilesetName( project->getLayerTileset(stage_index, layer_index) )));
			}
			break;

			case LAYER_TYPE_SPRITE:
			{
				m_mapEdit_layerSprite_listBox->Clear();
				for(int i = 0; i < current_layer.layer_sprites.size(); i++)
				{
					m_mapEdit_layerSprite_listBox->AppendAndEnsureVisible(wxString(current_layer.layer_sprites[i].sprite_name));
				}

				m_mapEdit_collisionShape_listBox->Clear();
				for(int i = 0; i < current_layer.layer_shapes.size(); i++)
				{
					m_mapEdit_collisionShape_listBox->AppendAndEnsureVisible(wxString(current_layer.layer_shapes[i].shape_name));
				}

				reloadSpriteProperties();
			}
			break;

			case LAYER_TYPE_CANVAS_2D:
			{
				m_mapEdit_canvasRenderSetting_comboBox->Append(_("NORMAL"));
				m_mapEdit_canvasRenderSetting_comboBox->Append(_("STRETCHED"));
				m_mapEdit_canvasRenderSetting_comboBox->Append(_("TILED"));

				if(current_layer.bkg.render_setting >= 0 && current_layer.bkg.render_setting < 3)
					m_mapEdit_canvasRenderSetting_comboBox->SetSelection(current_layer.bkg.render_setting);

				wxFileName fname(project->getDir());
				fname.AppendDir(_("bkg"));

				wxArrayString bkg_list = getDirFileList(fname.GetAbsolutePath());

				int img_selection = -1;

				wxString bkg_image = wxString(current_layer.bkg.img_file).Trim();

				for(int i = 0; i < bkg_list.size(); i++)
				{
					if(bkg_list.Item(i).Trim().compare(bkg_image)==0)
						img_selection = i;

					m_mapEdit_canvasImage_comboBox->Append(bkg_list.Item(i));
				}

				if(img_selection >= 0)
					m_mapEdit_canvasImage_comboBox->SetSelection(img_selection);
			}
			break;

			case LAYER_TYPE_CANVAS_3D:
			{
			}
			break;
		}
	}
}

void NirvanaEditor_MainFrame::OnEnterMapView( wxMouseEvent& event )
{
	if(!editor_init)
		return;

    //std::cout << "ENTER" << std::endl;

	map_editor->getMapViewControl()->stage_window_isActive = true;
	map_editor->getMapViewControl()->mapEdit_tile_selection = map_editor->getTileSelectControl()->mapEdit_tile_selection;
}

void NirvanaEditor_MainFrame::OnLeaveMapView( wxMouseEvent& event )
{
	if(!editor_init)
		return;

    //std::cout << "EXIT" << std::endl;

	map_editor->getMapViewControl()->stage_window_isActive = false;
	map_editor->getMapViewControl()->mapEdit_lastAction_erase = false;
}

void NirvanaEditor_MainFrame::OnActiveLayerSelect( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	map_editor->selectLayer(event.GetSelection());
	updateMapEditor();
}

void NirvanaEditor_MainFrame::OnLayerCheckListSelect( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	wxString layer_name = event.GetString();
	m_layerName_textCtrl->SetValue(layer_name);

	int stage_index = map_editor->getSelectedStage();
	int layer_index = project->getLayerIndex(stage_index, layer_name.ToStdString());
	irr::core::vector2df scroll_speed = project->getLayerScrollSpeed(stage_index, layer_index);
	m_mapEdit_layerHScroll_spinCtrlDouble->SetValue(scroll_speed.X);
	m_mapEdit_layerVScroll_spinCtrlDouble->SetValue(scroll_speed.Y);

	int alpha = project->getLayerAlpha(stage_index, layer_index);
	m_mapEdit_layerAlpha_spinCtrl->SetValue(alpha);

	switch(project->getLayerType(stage_index, layer_index))
	{
		case LAYER_TYPE_CANVAS_2D:
		{
			m_stageLayer_layerType_staticText->SetLabelText(_("CANVAS_2D"));
		}
		break;

		case LAYER_TYPE_CANVAS_3D:
		{
			m_stageLayer_layerType_staticText->SetLabelText(_("CANVAS_3D"));
		}
		break;

		case LAYER_TYPE_SPRITE:
		{
			m_stageLayer_layerType_staticText->SetLabelText(_("SPRITE"));
		}
		break;

		case LAYER_TYPE_TILEMAP:
		{
			m_stageLayer_layerType_staticText->SetLabelText(_("TILEMAP"));
		}
		break;

		case LAYER_TYPE_ISO_TILEMAP:
		{
			m_stageLayer_layerType_staticText->SetLabelText(_("ISO_TILEMAP"));
		}
		break;

		default:
		{
			m_stageLayer_layerType_staticText->SetLabelText(_("[NA]"));
		}
		break;
	}
}

void NirvanaEditor_MainFrame::OnLayerCheckList_Visible_Toggle( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	int selected_item = event.GetSelection();
	if(selected_item < 0 || selected_item >= m_layerVisible_checkList->GetCount())
		return;

	wxString layer_name = m_layerVisible_checkList->GetString(selected_item);

	int stage_index = map_editor->getSelectedStage();
	int layer_index = project->getLayerIndex(stage_index, layer_name.ToStdString());

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	//std::cout << "Visible: " << ( m_layerVisible_checkList->IsChecked(selected_item) ? "TRUE" : "FALSE" ) << std::endl;
	project->setLayerVisible(stage_index, layer_index, m_layerVisible_checkList->IsChecked(selected_item));

	int canvas_id = project->stages[stage_index].layers[layer_index].ref_canvas;

	if(canvas_id < 0 || canvas_id >= map_editor->getMapViewControl()->canvas.size())
		return;

	map_editor->getMapViewControl()->setCanvasVisible(canvas_id, project->getLayerVisible(stage_index, layer_index));
}

void NirvanaEditor_MainFrame::OnMapEdit_LayerNameChange( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	if(event.GetString().Trim().length()==0)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = m_layerVisible_checkList->GetSelection();

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	wxString test_layer_name = wxString(project->getLayerName(stage_index, layer_index)).Upper().Trim(); //Need to get name before change

	project->setLayerName(stage_index, layer_index, event.GetString().ToStdString());

	m_layerVisible_checkList->SetString(layer_index, wxString(project->getLayerName(stage_index, layer_index)));
	m_activeLayer_comboBox->SetString(layer_index, wxString(project->getLayerName(stage_index, layer_index)));
}

void NirvanaEditor_MainFrame::OnMapEdit_LayerHScroll( wxSpinDoubleEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = m_layerVisible_checkList->GetSelection();

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	irr::core::vector2df scroll_speed = project->getLayerScrollSpeed(stage_index, layer_index);
	scroll_speed.X = m_mapEdit_layerHScroll_spinCtrlDouble->GetValue();
	project->setLayerScrollSpeed(stage_index, layer_index, scroll_speed.X, scroll_speed.Y);
}

void NirvanaEditor_MainFrame::OnMapEdit_LayerVScroll( wxSpinDoubleEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = m_layerVisible_checkList->GetSelection();

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	irr::core::vector2df scroll_speed = project->getLayerScrollSpeed(stage_index, layer_index);
	scroll_speed.Y = m_mapEdit_layerVScroll_spinCtrlDouble->GetValue();
	project->setLayerScrollSpeed(stage_index, layer_index, scroll_speed.X, scroll_speed.Y);
}

void NirvanaEditor_MainFrame::OnMapEdit_LayerAlpha( wxSpinEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = m_layerVisible_checkList->GetSelection();

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	int alpha = m_mapEdit_layerAlpha_spinCtrl->GetValue();
	project->setLayerAlpha(stage_index, layer_index, alpha);
}

void NirvanaEditor_MainFrame::OnMapEdit_LayerUpClick( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = m_layerVisible_checkList->GetSelection();

	//
	if(layer_index < 1 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	wxString active_layer_name = wxString(project->getLayerName(stage_index, map_editor->getSelectedLayer())).Upper().Trim();
	wxString checklist_layer_name = wxString(project->getLayerName(stage_index, layer_index)).Upper().Trim();

	bool active_layer_changed = (map_editor->getSelectedLayer() == layer_index);

	int new_layer_index = layer_index - 1;
	project->setLayerOrder(stage_index, layer_index, new_layer_index);

	//SET LAYER COMBO AND CHECKLIST
	m_layerVisible_checkList->Clear();
	m_activeLayer_comboBox->Clear();

	for(int i = 0; i < project->getStageNumLayers(stage_index); i++)
	{
		m_layerVisible_checkList->AppendAndEnsureVisible(wxString(project->getLayerName(stage_index, i)));
		m_layerVisible_checkList->Check(i, project->getLayerVisible(stage_index, i));

		m_activeLayer_comboBox->Append(project->getLayerName(stage_index, i));
	}

	m_layerVisible_checkList->SetSelection(new_layer_index);

	int active_layer_index = project->getLayerIndex(stage_index, active_layer_name.ToStdString());
	//std::cout << "ACT: " << active_layer_name.ToStdString() << " -> " << active_layer_index << std::endl;
	m_activeLayer_comboBox->SetSelection(active_layer_index);

	map_editor->selectLayer(active_layer_index);
}

void NirvanaEditor_MainFrame::OnMapEdit_LayerDownClick( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = m_layerVisible_checkList->GetSelection();

	//
	if(layer_index < 0 || layer_index >= (project->getStageNumLayers(stage_index)-1) )
		return;

	wxString active_layer_name = wxString(project->getLayerName(stage_index, map_editor->getSelectedLayer())).Upper().Trim();
	wxString checklist_layer_name = wxString(project->getLayerName(stage_index, layer_index)).Upper().Trim();

	bool active_layer_changed = (map_editor->getSelectedLayer() == layer_index);

	int new_layer_index = layer_index + 1;
	project->setLayerOrder(stage_index, layer_index, new_layer_index);

	//SET LAYER COMBO AND CHECKLIST
	m_layerVisible_checkList->Clear();
	m_activeLayer_comboBox->Clear();

	for(int i = 0; i < project->getStageNumLayers(stage_index); i++)
	{
		m_layerVisible_checkList->AppendAndEnsureVisible(wxString(project->getLayerName(stage_index, i)));
		m_layerVisible_checkList->Check(i, project->getLayerVisible(stage_index, i));

		m_activeLayer_comboBox->Append(project->getLayerName(stage_index, i));
	}

	m_layerVisible_checkList->SetSelection(new_layer_index);

	int active_layer_index = project->getLayerIndex(stage_index, active_layer_name.ToStdString());
	//std::cout << "ACT: " << active_layer_name.ToStdString() << " -> " << active_layer_index << std::endl;
	m_activeLayer_comboBox->SetSelection(active_layer_index);

	map_editor->selectLayer(active_layer_index);
}

void NirvanaEditor_MainFrame::OnMapEdit_LayerDeleteClick( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = m_layerVisible_checkList->GetSelection();

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	wxString active_layer_name = wxString(project->getLayerName(stage_index, map_editor->getSelectedLayer())).Upper().Trim();
	wxString checklist_layer_name = wxString(project->getLayerName(stage_index, layer_index)).Upper().Trim();

	bool active_layer_changed = (map_editor->getSelectedLayer() == layer_index);

	map_editor->getMapViewControl()->canvasClose(project->stages[stage_index].layers[layer_index].ref_canvas);
	map_editor->getMapViewControl()->mapEdit_selectTileTool_selection.clear();
	project->stages[stage_index].layers[layer_index].ref_canvas = -1;
	project->deleteLayer(stage_index, layer_index);

	//SET LAYER COMBO AND CHECKLIST
	m_layerVisible_checkList->Clear();
	m_activeLayer_comboBox->Clear();

	for(int i = 0; i < project->getStageNumLayers(stage_index); i++)
	{
		m_layerVisible_checkList->AppendAndEnsureVisible(wxString(project->getLayerName(stage_index, i)));
		m_layerVisible_checkList->Check(i, project->getLayerVisible(stage_index, i));

		m_activeLayer_comboBox->Append(project->getLayerName(stage_index, i));
	}

	int active_layer_index = project->getLayerIndex(stage_index, active_layer_name.ToStdString());
	//std::cout << "ACT: " << active_layer_name.ToStdString() << " -> " << active_layer_index << std::endl;
	m_activeLayer_comboBox->SetSelection(active_layer_index);
	map_editor->selectLayer(active_layer_index);

	m_layerName_textCtrl->SetValue(_(""));
	m_mapEdit_layerHScroll_spinCtrlDouble->SetValue(0.0);
	m_mapEdit_layerVScroll_spinCtrlDouble->SetValue(0.0);
	m_mapEdit_layerAlpha_spinCtrl->SetValue(0);

	refreshCurrentLayerUI();
}

void NirvanaEditor_MainFrame::refreshCurrentLayerUI()
{
	if(!editor_init)
		return;

	m_mapEdit_layerSprite_listBox->Clear();

	wxPGProperty * sprite_id = m_mapEdit_sprite_propertyGrid->GetProperty(_("sprite_id"));
	wxPGProperty * sprite_body_type = m_mapEdit_sprite_propertyGrid->GetProperty(_("body_type"));
	wxPGProperty * sprite_animation = m_mapEdit_sprite_propertyGrid->GetProperty(_("animation"));
	wxPGProperty * sprite_pos_x = m_mapEdit_sprite_propertyGrid->GetProperty(_("position_x"));
	wxPGProperty * sprite_pos_y = m_mapEdit_sprite_propertyGrid->GetProperty(_("position_y"));
	wxPGProperty * sprite_angle = m_mapEdit_sprite_propertyGrid->GetProperty(_("angle"));
	wxPGProperty * sprite_scale_x = m_mapEdit_sprite_propertyGrid->GetProperty(_("scale_x"));
	wxPGProperty * sprite_scale_y = m_mapEdit_sprite_propertyGrid->GetProperty(_("scale_y"));
	wxPGProperty * sprite_alpha = m_mapEdit_sprite_propertyGrid->GetProperty(_("alpha"));
	wxPGProperty * sprite_visible = m_mapEdit_sprite_propertyGrid->GetProperty(_("visible"));


	sprite_id->SetValue(_(""));
	sprite_body_type->SetChoiceSelection(0);
	sprite_animation->SetChoices(wxPGChoices());
	sprite_pos_x->SetValue( 0 );
	sprite_pos_y->SetValue( 0 );
	sprite_angle->SetValue( 0 );
	sprite_scale_x->SetValue( 0 );
	sprite_scale_y->SetValue( 0 );
	sprite_alpha->SetValueFromInt( 0 );
	sprite_visible->SetValue( false );

	m_mapEdit_collisionShape_listBox->Clear();

	m_mapEdit_canvasImage_comboBox->Clear();
	//m_mapEdit_canvasRenderSetting_comboBox->SetSelection(0);

	int active_stage = map_editor->getSelectedStage();
	int active_layer = map_editor->getSelectedLayer();

	if(active_stage < 0 || active_stage >= project->stages.size())
		return;

	if(active_layer < 0 || active_layer >= project->stages[active_stage].layers.size())
		return;


	switch(project->getLayerType(active_stage, active_layer))
	{
		case LAYER_TYPE_TILEMAP:
		{
		}
		break;

		case LAYER_TYPE_SPRITE:
		{
			reloadSpriteProperties();
		}
		break;

		case LAYER_TYPE_CANVAS_2D:
		{
		}
		break;

		case LAYER_TYPE_CANVAS_3D:
		{
		}
		break;
	}
}

void NirvanaEditor_MainFrame::OnBkg_RenderType( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();

	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = map_editor->getSelectedLayer();

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	project->stages[stage_index].layers[layer_index].bkg.render_setting = m_mapEdit_canvasRenderSetting_comboBox->GetSelection();

	if(project->stages[stage_index].layers[layer_index].ref_canvas >= 0 && project->stages[stage_index].layers[layer_index].ref_canvas < map_editor->getMapViewControl()->canvas.size())
	{
		map_editor->getMapViewControl()->canvas[project->stages[stage_index].layers[layer_index].ref_canvas].bkg_render_type = project->stages[stage_index].layers[layer_index].bkg.render_setting;
	}
}

void NirvanaEditor_MainFrame::OnBkg_LayerImage( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();

	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = map_editor->getSelectedLayer();

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	wxFileName fname(project->getDir());
	fname.AppendDir(project->bkg_path);
	int img_selection = m_mapEdit_canvasImage_comboBox->GetSelection();
	if(img_selection >= 0 && img_selection < m_mapEdit_canvasImage_comboBox->GetCount())
		fname.SetFullName(m_mapEdit_canvasImage_comboBox->GetString(img_selection));

	if(!fname.Exists())
		return;

	project->stages[stage_index].layers[layer_index].bkg.img_file = fname.GetFullName();
	//std::cout << "Filename: " << project->stages[stage_index].layers[layer_index].bkg.img_file << std::endl;

	if(map_editor->getMapViewControl()->imageExists(project->stages[stage_index].layers[layer_index].bkg.image_id))
		map_editor->getMapViewControl()->deleteImage(project->stages[stage_index].layers[layer_index].bkg.image_id);

	project->stages[stage_index].layers[layer_index].bkg.image_id = -1;

	project->stages[stage_index].layers[layer_index].bkg.image_id = map_editor->getMapViewControl()->loadImage(fname.GetAbsolutePath().ToStdString());

	if(project->stages[stage_index].layers[layer_index].ref_canvas >= 0 && project->stages[stage_index].layers[layer_index].ref_canvas < map_editor->getMapViewControl()->canvas.size())
	{
		map_editor->getMapViewControl()->canvas[project->stages[stage_index].layers[layer_index].ref_canvas].bkg_render_image_id = project->stages[stage_index].layers[layer_index].bkg.image_id;
	}

	//std::cout << "IMG ID: " << project->stages[stage_index].layers[layer_index].bkg.image_id << std::endl;
}

void NirvanaEditor_MainFrame::OnMapEdit_Map_UpdateUI( wxUpdateUIEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();

	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = map_editor->getSelectedLayer();

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	if(project->getLayerType(stage_index, layer_index)==LAYER_TYPE_SPRITE)
	{
		if(map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection.size()==1)
		{
			if(map_editor->getMapViewControl()->map_sprite_selection_changed)
			{
				int selected_sprite = map_editor->getMapViewControl()->selected_sprite;
				if(selected_sprite >= 0 && selected_sprite < project->stages[stage_index].layers[layer_index].layer_sprites.size())
				{
					wxString spr_name = wxString(project->stages[stage_index].layers[layer_index].layer_sprites[selected_sprite].sprite_name).Upper().Trim();

					//std::cout << std::endl << "LOOKUP: " << spr_name.ToStdString() << std::endl;

					for(int i = 0; i < m_mapEdit_layerSprite_listBox->GetCount(); i++)
					{
						wxString list_item = m_mapEdit_layerSprite_listBox->GetString(i).Upper().Trim();
						if(list_item.compare(spr_name) == 0)
						{
							//std::cout << "Found: " << spr_name << " at " << i << std::endl;
							m_mapEdit_layerSprite_listBox->SetSelection(i);
							break;
						}
					}
				}
				else
				{
					m_mapEdit_layerSprite_listBox->DeselectAll();
				}

				reloadSpriteProperties();
			}
		}
		else if(map_editor->getMapViewControl()->map_sprite_selection_changed)
		{
			m_mapEdit_layerSprite_listBox->DeselectAll();
			reloadSpriteProperties();
		}

		if(map_editor->getMapViewControl()->pick_shape_update)
		{
			map_editor->getMapViewControl()->pick_shape_update = false;
			int list_selection = m_mapEdit_collisionShape_listBox->GetSelection();
			if(list_selection >= 0 && list_selection < m_mapEdit_collisionShape_listBox->GetCount())
			{
				int shape_index = project->getShapeIndex(stage_index, layer_index, m_mapEdit_collisionShape_listBox->GetString(list_selection).ToStdString());
				map_editor->selectShape(shape_index);
			}
			//std::cout << "REFRESH UI" << std::endl;
			refreshCurrentShapeUI();
		}
	}

	map_editor->getMapViewControl()->map_sprite_selection_changed = false;
}

void NirvanaEditor_MainFrame::OnCameraToolClick( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();

	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	NirvanaEditor_SetCamera_Dialog* dialog = new NirvanaEditor_SetCamera_Dialog(this);

	dialog->initOffset(map_editor->getMapViewControl()->scroll_offset_x, map_editor->getMapViewControl()->scroll_offset_y);

	PreDialog();
	dialog->ShowModal();
	PostDialog();

	if(!dialog->set_flag)
		return;

	map_editor->getMapViewControl()->scroll_offset_x = dialog->offset_x;
	map_editor->getMapViewControl()->scroll_offset_y = dialog->offset_y;
}

void NirvanaEditor_MainFrame::OnMapSetFree( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	map_editor->getMapViewControl()->tile_snap = false;
}

void NirvanaEditor_MainFrame::OnMapSetTiled( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	map_editor->getMapViewControl()->tile_snap = true;
}


void NirvanaEditor_MainFrame::OnMapEditSettings_ShowShapes_Checked( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	map_editor->getMapViewControl()->show_shapes_all = event.IsChecked();

	//if(map_editor->getMapViewControl()->show_shapes_all)
	//	wxMessageBox(_("Show Shapes"));
}

void NirvanaEditor_MainFrame::OnMapEditSettings_ShowGrid_Checked( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	map_editor->getMapViewControl()->show_grid = event.IsChecked();
}

void NirvanaEditor_MainFrame::OnMapEditSettings_GridColor_Change( wxColourPickerEvent& event )
{
	if(!editor_init)
		return;

	wxColour grid_color = event.GetColour();
	map_editor->getMapViewControl()->grid_color.set(255, grid_color.GetRed(), grid_color.GetGreen(), grid_color.GetBlue());
}

void NirvanaEditor_MainFrame::OnMapEditSettings_CameraSpeed_SpinCtrl( wxSpinEvent& event )
{
	if(!editor_init)
		return;

	map_editor->getMapViewControl()->scroll_speed = event.GetValue();
}

void NirvanaEditor_MainFrame::OnMapEditSettings_TileSelectSpeed_SpinCtrl( wxSpinEvent& event )
{
	if(!editor_init)
		return;

	map_editor->getTileSelectControl()->scroll_speed = event.GetValue();
	tile_editor->getAnimationSheetControl()->scroll_speed = event.GetValue();
	tile_editor->getMaskSheetControl()->scroll_speed = event.GetValue();
}

void NirvanaEditor_MainFrame::OnMapEditSettings_SpriteSelectSpeed_SpinCtrl( wxSpinEvent& event )
{
    if(!editor_init)
		return;

	sprite_editor->getAnimationSheetControl()->scroll_speed = event.GetValue();
	sprite_editor->getCollisionControl()->scroll_speed = event.GetValue();
}
