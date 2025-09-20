#include "NirvanaEditor_MainFrame.h"
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/arrstr.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/property.h>

#include "NirvanaEditor_AddSpriteInstance_Dialog.h"
#include "NirvanaEditor_DeleteSprite_Dialog.h"
#include "Nirvana_Project.h"

void NirvanaEditor_MainFrame::OnMapEdit_SpriteTool_Select( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	selected_map_tool = MAP_TOOL_SPRITE_SELECT;
	map_editor->setMapTool(selected_map_tool);
}

void NirvanaEditor_MainFrame::OnMapEdit_SpriteTool_BoxSelect( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	selected_map_tool = MAP_TOOL_SPRITE_BOXSELECT;
	map_editor->setMapTool(selected_map_tool);
}

void NirvanaEditor_MainFrame::OnMapEdit_SpriteTool_Move( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	selected_map_tool = MAP_TOOL_SPRITE_MOVE;
	map_editor->setMapTool(selected_map_tool);
}

void NirvanaEditor_MainFrame::OnMapEdit_SpriteTool_Rotate( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	selected_map_tool = MAP_TOOL_SPRITE_ROTATE;
	map_editor->setMapTool(selected_map_tool);
}

void NirvanaEditor_MainFrame::OnMapEdit_SpriteTool_Scale( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	selected_map_tool = MAP_TOOL_SPRITE_SCALE;
	map_editor->setMapTool(selected_map_tool);
}

void NirvanaEditor_MainFrame::OnMapEdit_SpriteTool_AddSprite( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0)
		return;

	int layer_index = map_editor->getSelectedLayer();
	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	if(project->getLayerType(stage_index, layer_index) != LAYER_TYPE_SPRITE)
	{
		wxMessageBox(_("Must be on sprite layer to add a sprite"));
		return;
	}

	NirvanaEditor_AddSpriteInstance_Dialog* dialog = new NirvanaEditor_AddSpriteInstance_Dialog(this);

	dialog->stage_index = stage_index;
	dialog->layer_index = layer_index;
	dialog->project = project;

	for(int i = 0; i < project->sprite_base.size(); i++)
	{
		if(project->sprite_base[i].sprite_name.Trim().length() > 0)
			dialog->base_sprites.push_back(project->sprite_base[i].sprite_name);
	}

	dialog->refresh_list();

	PreDialog();
	dialog->ShowModal();
	PostDialog();

	if(!dialog->create_flag)
		return;

	int base_sprite_index = project->getSpriteBaseIndex(dialog->selected_base.ToStdString());

	if(base_sprite_index < 0)
	{
		wxMessageBox(_("Could not create instance of base [") + dialog->selected_base + _("]"));
		return;
	}

	int screen_w = map_editor->getMapViewControl()->GetClientSize().GetWidth();
	int screen_h = map_editor->getMapViewControl()->GetClientSize().GetHeight();

	int x = map_editor->getMapViewControl()->scroll_offset_x * project->stages[stage_index].layers[layer_index].scroll_speed.X + (screen_w/2);
	int y = map_editor->getMapViewControl()->scroll_offset_y* project->stages[stage_index].layers[layer_index].scroll_speed.Y + (screen_h/2);

	int sprite_index = project->addLayerSprite(stage_index, layer_index, dialog->id_name.ToStdString(), base_sprite_index, x, y);

	if(sprite_index < 0 || sprite_index >= project->stages[stage_index].layers[layer_index].layer_sprites.size())
	{
		wxMessageBox(_("ERROR: Failed to add new sprite to current layer"));
		return;
	}

	map_editor->getMapViewControl()->mapEdit_getContext();
	map_editor->getMapViewControl()->setActiveCanvas(project->stages[stage_index].layers[layer_index].ref_canvas);
	map_editor->getMapViewControl()->addLayerSprite(layer_index, sprite_index);

	m_mapEdit_layerSprite_listBox->AppendAndEnsureVisible(dialog->id_name);
	m_mapEdit_layerSprite_listBox->SetSelection(project->getLayerSpriteIndex(stage_index, layer_index, dialog->id_name.ToStdString()));
	map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection.clear();
	Nirvana_SelectTool_SpriteSelection new_sprite_selection;
	new_sprite_selection.layer_sprite_index = project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].map_sprite_id;
	map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection.push_back(new_sprite_selection);
	reloadSpriteProperties();

	m_mapEdit_spriteTools_auiToolBar->ToggleTool(m_mapEdit_spriteToolbar_move_tool->GetId(), true);
	selected_map_tool = MAP_TOOL_SPRITE_MOVE;
	map_editor->setMapTool(selected_map_tool);
}

void NirvanaEditor_MainFrame::OnMapEdit_SpriteTool_DeleteSprite( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0)
		return;

	int layer_index = map_editor->getSelectedLayer();
	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	if(project->getLayerType(stage_index, layer_index) != LAYER_TYPE_SPRITE)
	{
		return;
	}

	if(map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection.size() == 0)
		return;


	wxString spr_name = _("");


	int map_spr_id = map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection[0].layer_sprite_index;
	int spr_index = map_editor->getMapViewControl()->sprite[map_spr_id].layer_sprite_index;

	if(spr_index < 0 || spr_index >= project->getStageLayerNumSprites(stage_index, layer_index))
		return;

	if(map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection.size() == 1)
	{
		spr_name = wxString(project->stages[stage_index].layers[layer_index].layer_sprites[spr_index].sprite_name).Trim();
	}
	else
	{
		spr_name = _("[MULTIPLE SELECTED]");
	}

	NirvanaEditor_DeleteSprite_Dialog* dialog = new NirvanaEditor_DeleteSprite_Dialog(this);
	dialog->setSpriteName(spr_name);

	PreDialog();
	dialog->ShowModal();
	PostDialog();

	if(!dialog->delete_flag)
		return;

	irr::core::array<int> layer_spr_array; //The irrlicht array has built-in sort and I don't feel like doing it myself

	for(int i = 0; i < map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection.size(); i++)
	{
		map_spr_id = map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection[i].layer_sprite_index;
		spr_index = map_editor->getMapViewControl()->sprite[map_spr_id].layer_sprite_index;

		//std::cout << "delete: " << map_spr_id << ", " << spr_index << ", " << project->stages[stage_index].layers[layer_index].layer_sprites[spr_index].sprite_name << std::endl;

		map_editor->getMapViewControl()->deleteSprite(map_spr_id);
		layer_spr_array.push_back(spr_index);
	}

	layer_spr_array.sort();

	for(int i = layer_spr_array.size()-1; i >= 0; i--)
	{
		if(i < 0)
			break;

		//std::cout << "array: " << layer_spr_array[i] << ", " << project->stages[stage_index].layers[layer_index].layer_sprites[layer_spr_array[i]].sprite_name << std::endl;

		project->deleteLayerSprite(stage_index, layer_index, layer_spr_array[i]);
	}

	// REMAP LAYER_SPRITE_INDEX for remaining sprites on the current layer
	int ref_canvas = project->stages[stage_index].layers[layer_index].ref_canvas;

	if(ref_canvas >= 0 && ref_canvas < map_editor->getMapViewControl()->canvas.size())
	{
		for(int i = 0; i < map_editor->getMapViewControl()->canvas[ref_canvas].sprite_id.size(); i++)
		{
			map_spr_id = map_editor->getMapViewControl()->canvas[ref_canvas].sprite_id[i];

			if(map_spr_id < 0 || map_spr_id >= map_editor->getMapViewControl()->sprite.size())
				continue;

			if(!map_editor->getMapViewControl()->sprite[map_spr_id].active)
				continue;

			for(int lsi = 0; lsi < project->stages[stage_index].layers[layer_index].layer_sprites.size(); lsi++)
			{
				if(map_editor->getMapViewControl()->sprite[map_spr_id].layer_sprite_unique_id == project->stages[stage_index].layers[layer_index].layer_sprites[lsi].layer_sprite_unique_id)
				{
					map_editor->getMapViewControl()->sprite[map_spr_id].layer_sprite_index = lsi;
					break;
				}
			}
		}
	}


	map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection.clear();
	map_editor->getMapViewControl()->selected_sprite = -1;

	m_mapEdit_layerSprite_listBox->Clear();

	for(int i = 0; i < project->stages[stage_index].layers[layer_index].layer_sprites.size(); i++)
	{
		wxString list_spr_name = wxString(project->stages[stage_index].layers[layer_index].layer_sprites[i].sprite_name).Trim();
		m_mapEdit_layerSprite_listBox->AppendAndEnsureVisible(list_spr_name);
	}
}

void NirvanaEditor_MainFrame::OnMapEdit_SpriteTool_CopySprite( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0)
		return;

	int layer_index = map_editor->getSelectedLayer();
	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	if(project->getLayerType(stage_index, layer_index) != LAYER_TYPE_SPRITE)
	{
		return;
	}

	//COPY SELECTION
	std::vector<int> spr_copy;

	map_editor->getMapViewControl()->mapEdit_getContext();
	map_editor->getMapViewControl()->setActiveCanvas(project->stages[stage_index].layers[layer_index].ref_canvas);

	for(int i = 0; i < map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection.size(); i++)
	{
		int map_sprite_index = map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection[i].layer_sprite_index;

		if(map_sprite_index < 0 || map_sprite_index >= map_editor->getMapViewControl()->sprite.size())
			continue;

		int layer_sprite_index = map_editor->getMapViewControl()->sprite[map_sprite_index].layer_sprite_index;

		int copy_layer_sprite_index = project->copyLayerSprite(stage_index, layer_index, layer_sprite_index);

		int base_index = project->stages[stage_index].layers[layer_index].layer_sprites[copy_layer_sprite_index].sprite_base;
		int img_id = project->sprite_base[base_index].object.image_id;
		int frame_w = project->sprite_base[base_index].object.frame_size.Width;
		int frame_h = project->sprite_base[base_index].object.frame_size.Height;
		int map_spr_id = map_editor->getMapViewControl()->createSprite(copy_layer_sprite_index, img_id, frame_w, frame_h);

		map_editor->getMapViewControl()->sprite[map_spr_id] = map_editor->getMapViewControl()->sprite[map_sprite_index];
		map_editor->getMapViewControl()->sprite[map_spr_id].layer_sprite_index = copy_layer_sprite_index;
		map_editor->getMapViewControl()->sprite[map_spr_id].layer_sprite_unique_id = project->stages[stage_index].layers[layer_index].layer_sprites[copy_layer_sprite_index].layer_sprite_unique_id;

		project->stages[stage_index].layers[layer_index].layer_sprites[copy_layer_sprite_index].map_sprite_id = map_spr_id;
		spr_copy.push_back(map_spr_id);

		wxString list_spr_name = wxString(project->stages[stage_index].layers[layer_index].layer_sprites[copy_layer_sprite_index].sprite_name).Trim();
		m_mapEdit_layerSprite_listBox->AppendAndEnsureVisible(list_spr_name);
	}

	m_mapEdit_layerSprite_listBox->DeselectAll();

	map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection.clear();

	for(int i = 0; i < spr_copy.size(); i++)
	{
		Nirvana_SelectTool_SpriteSelection n_sprite_selection;
		n_sprite_selection.layer_sprite_index = spr_copy[i];
		map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection.push_back(n_sprite_selection);
	}

	selected_map_tool = MAP_TOOL_SPRITE_MOVE;
	map_editor->setMapTool(selected_map_tool);
}

void NirvanaEditor_MainFrame::OnMapEdit_SpriteTool_CenterOnSprite( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0)
		return;

	int layer_index = map_editor->getSelectedLayer();
	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	if(project->getLayerType(stage_index, layer_index) != LAYER_TYPE_SPRITE)
	{
		return;
	}

	int x = 0;
	int y = 0;

	for(int i = 0; i < map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection.size(); i++)
	{
		int map_spr_id = map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection[i].layer_sprite_index;
		//std::cout << "SELECT: " << map_spr_id << std::endl;

		x += map_editor->getMapViewControl()->sprite[map_spr_id].position.X;
		y += map_editor->getMapViewControl()->sprite[map_spr_id].position.Y;
	}

	if(map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection.size() > 0)
	{
		x = x / map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection.size();
		y = y / map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection.size();
	}

	float scroll_speed_x = project->stages[stage_index].layers[layer_index].scroll_speed.X;
	float scroll_speed_y = project->stages[stage_index].layers[layer_index].scroll_speed.Y;

	map_editor->getMapViewControl()->scroll_offset_x = x/scroll_speed_x - (map_editor->getMapViewControl()->GetClientSize().GetWidth()/2)/scroll_speed_x;
	map_editor->getMapViewControl()->scroll_offset_y = y/scroll_speed_y - (map_editor->getMapViewControl()->GetClientSize().GetHeight()/2)/scroll_speed_y;
}

void NirvanaEditor_MainFrame::OnMapEdit_SpriteTool_SortSettings( wxCommandEvent& event )
{

}


void NirvanaEditor_MainFrame::reloadSpriteProperties()
{
	if(!editor_init)
		return;

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


	if(!project)
		return;

	if(map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection.size() > 1)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0)
		return;

	int layer_index = map_editor->getSelectedLayer();
	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	int list_item_index = m_mapEdit_layerSprite_listBox->GetSelection();
	if(list_item_index < 0 || list_item_index >= m_mapEdit_layerSprite_listBox->GetCount())
		return;

	int sprite_index = project->getLayerSpriteIndex(stage_index, layer_index, m_mapEdit_layerSprite_listBox->GetString(list_item_index).ToStdString());
	if(sprite_index < 0 || sprite_index >= project->getStageLayerNumSprites(stage_index, layer_index))
		return;

	Nirvana_Map_Sprite n_sprite = project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index];

	sprite_id->SetValueFromString(wxString(n_sprite.sprite_name));
	if(n_sprite.body_type < 0 || n_sprite.body_type >= 3)
		sprite_body_type->SetChoiceSelection(0);
	else
		sprite_body_type->SetChoiceSelection(n_sprite.body_type);


	wxPGChoices animation_choices;
	animation_choices.Clear();

	int animation_selection = 0;

	wxString ani_name = wxString(n_sprite.animation_name).Upper().Trim();

	for(int i = 0; i < project->sprite_base[n_sprite.sprite_base].object.animation.size(); i++)
	{
		if(wxString(project->sprite_base[n_sprite.sprite_base].object.animation[i].name).Upper().Trim().compare(ani_name)==0)
			animation_selection = i;

		animation_choices.Add(wxString(project->sprite_base[n_sprite.sprite_base].object.animation[i].name));
	}

	if(animation_choices.GetCount() == 0)
		animation_choices.Add(_("SPRITE_BASE_ANIMATION"));

	sprite_animation->SetChoices(animation_choices);
	sprite_animation->SetChoiceSelection(animation_selection);

	sprite_pos_x->SetValue( n_sprite.position.X );
	sprite_pos_y->SetValue( n_sprite.position.Y );
	sprite_angle->SetValue( 360-n_sprite.angle );
	sprite_scale_x->SetValue( n_sprite.scale.X );
	sprite_scale_y->SetValue( n_sprite.scale.Y );
	sprite_alpha->SetValueFromInt( (int)n_sprite.alpha );
	sprite_visible->SetValue( n_sprite.visible );
}


void NirvanaEditor_MainFrame::OnMapEdit_SpriteListSelect( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	reloadSpriteProperties();
	map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection.clear();

	if(!project)
		return;

	if(map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection.size() > 1)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0)
		return;

	int layer_index = map_editor->getSelectedLayer();
	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	int list_item_index = m_mapEdit_layerSprite_listBox->GetSelection();
	if(list_item_index < 0 || list_item_index >= m_mapEdit_layerSprite_listBox->GetCount())
		return;

	int sprite_index = project->getLayerSpriteIndex(stage_index, layer_index, m_mapEdit_layerSprite_listBox->GetString(list_item_index).ToStdString());
	if(sprite_index < 0 || sprite_index >= project->getStageLayerNumSprites(stage_index, layer_index))
		return;

	int map_spr_id = project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].map_sprite_id;

	if(map_spr_id < 0 || map_spr_id >= map_editor->getMapViewControl()->sprite.size())
		return;

	Nirvana_SelectTool_SpriteSelection sprite_selection;
	sprite_selection.layer_sprite_index = map_spr_id;
	map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection.push_back(sprite_selection);
}

void NirvanaEditor_MainFrame::OnMapEdit_SpritePropertyGridChanged( wxPropertyGridEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0)
		return;

	int layer_index = map_editor->getSelectedLayer();
	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	int list_item_index = m_mapEdit_layerSprite_listBox->GetSelection();
	if(list_item_index < 0 || list_item_index >= m_mapEdit_layerSprite_listBox->GetCount())
		return;

	int sprite_index = project->getLayerSpriteIndex(stage_index, layer_index, m_mapEdit_layerSprite_listBox->GetString(list_item_index).ToStdString());
	if(sprite_index < 0 || sprite_index >= project->getStageLayerNumSprites(stage_index, layer_index))
		return;

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

	if(event.GetProperty()->GetName().compare(_("sprite_id"))==0)
	{
		bool sprite_id_exists = false;
		wxString test_id = sprite_id->GetValueAsString().Upper().Trim();

		for(int i = 0; i < project->stages[stage_index].layers[layer_index].layer_sprites.size(); i++)
		{
			if(i == sprite_index)
				continue;

			wxString test_2 = wxString(project->stages[stage_index].layers[layer_index].layer_sprites[i].sprite_name).Upper().Trim();

			//std::cout << "ID CMP[" << i << "]: " << test_id.ToStdString() << " ~ " << test_2.ToStdString() << std::endl;

			if(test_2.compare(test_id)==0)
			{
				sprite_id_exists = true;
				break;
			}
		}

		if(!project->checkName(sprite_id->GetValueAsString().ToStdString()))
		{
			wxMessageBox(_("Illegal Character or Invalid Sprite ID"));
			wxString sprite_actual_id = wxString(project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].sprite_name).Trim();
			sprite_id->SetValueFromString(sprite_actual_id);
		}
		else if(sprite_id_exists)
		{
			wxMessageBox(_("Sprite ID already exists in current layer"));
			wxString sprite_actual_id = wxString(project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].sprite_name).Trim();
			sprite_id->SetValueFromString(sprite_actual_id);
		}
		else
		{
			project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].sprite_name = sprite_id->GetValueAsString().Trim();

			int list_item_index = m_mapEdit_layerSprite_listBox->GetSelection();
			if(list_item_index >= 0 && list_item_index < m_mapEdit_layerSprite_listBox->GetCount())
			{
				m_mapEdit_layerSprite_listBox->SetString(list_item_index, sprite_id->GetValueAsString());
			}
		}
	}
	else if(event.GetProperty()->GetName().compare(_("body_type"))==0)
	{
		project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].body_type = sprite_body_type->GetChoiceSelection();
	}
	else if(event.GetProperty()->GetName().compare(_("animation"))==0)
	{
		int animation_index = sprite_animation->GetChoiceSelection();
		int base_index = project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].sprite_base;
		if(base_index >= 0 && base_index < project->sprite_base.size())
		{
			if(animation_index >= 0 && animation_index < project->sprite_base[base_index].object.animation.size())
			{
				std::string animation_name = project->sprite_base[base_index].object.animation[animation_index].name;
				project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].animation_name = animation_name;
				int map_sprite_id = project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].map_sprite_id;
				map_editor->getMapViewControl()->setSpriteAnimation(map_sprite_id, animation_index, -1);
			}
		}
	}
	else if(event.GetProperty()->GetName().compare(_("position_x"))==0)
	{
		project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].position.X = sprite_pos_x->GetValue().GetInteger();
		int map_sprite_id = project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].map_sprite_id;
		int x = project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].position.X;
		int y = project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].position.Y;
		map_editor->getMapViewControl()->setSpritePosition(map_sprite_id, x, y);
	}
	else if(event.GetProperty()->GetName().compare(_("position_y"))==0)
	{
		project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].position.Y = sprite_pos_y->GetValue().GetInteger();
		int map_sprite_id = project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].map_sprite_id;
		int x = project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].position.X;
		int y = project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].position.Y;
		map_editor->getMapViewControl()->setSpritePosition(map_sprite_id, x, y);
	}
	else if(event.GetProperty()->GetName().compare(_("angle"))==0)
	{
		project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].angle = sprite_angle->GetValue().GetDouble();
		int map_sprite_id = project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].map_sprite_id;
		double angle = project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].angle;
		map_editor->getMapViewControl()->setSpriteRotation(map_sprite_id, 360-angle);
	}
	else if(event.GetProperty()->GetName().compare(_("scale_x"))==0)
	{
		project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].scale.X = sprite_scale_x->GetValue().GetDouble();
		int map_sprite_id = project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].map_sprite_id;
		double x = project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].scale.X;
		double y = project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].scale.Y;
		map_editor->getMapViewControl()->setSpriteScale(map_sprite_id, x, y);
	}
	else if(event.GetProperty()->GetName().compare(_("scale_y"))==0)
	{
		project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].scale.Y = sprite_scale_y->GetValue().GetDouble();
		int map_sprite_id = project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].map_sprite_id;
		double x = project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].scale.X;
		double y = project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].scale.Y;
		map_editor->getMapViewControl()->setSpriteScale(map_sprite_id, x, y);
	}
	else if(event.GetProperty()->GetName().compare(_("alpha"))==0)
	{
		project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].alpha = (irr::u8)sprite_alpha->GetValue().GetInteger();
		int map_sprite_id = project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].map_sprite_id;
		int alpha = (int)project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].alpha;
		map_editor->getMapViewControl()->setSpriteAlpha(map_sprite_id, alpha);
	}
	else if(event.GetProperty()->GetName().compare(_("visible"))==0)
	{
		project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].visible = sprite_visible->GetValue().GetBool();
		int map_sprite_id = project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].map_sprite_id;
		bool visible = project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].visible;
		map_editor->getMapViewControl()->setSpriteVisible(map_sprite_id, visible);
	}
}
