#include "NirvanaEditor_MainFrame.h"


void NirvanaEditor_MainFrame::OnStageUndo( wxCommandEvent& event )
{
    stage_undo();
}

void NirvanaEditor_MainFrame::OnStageRedo( wxCommandEvent& event )
{
    stage_redo();
}


void NirvanaEditor_MainFrame::stage_action_setTile(nirvana_stageAction* n_action)
{
    if(! project )
        return;

    int stage_index = n_action->stage_index;
    int layer_index = n_action->layer_index;

    if(stage_index < 0 || stage_index >= project->stages.size())
        return;

    if(layer_index < 0 || layer_index >= project->stages[stage_index].layers.size())
        return;


    for(int i = 0; i < n_action->tiles.size(); i++)
    {
        int tmap_x = n_action->tiles[i].map_tile_pos_x;
        int tmap_y = n_action->tiles[i].map_tile_pos_y;

        //std::cout << "YOLO: (" << tmap_x << ", " << tmap_y << ") -> " << n_action.tiles[i].old_tile << ", " << n_action.tiles[i].new_tile << std::endl;

        project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows[tmap_y].tile[tmap_x] = n_action->tiles[i].old_tile;

        int old_tmp = n_action->tiles[i].old_tile;

        n_action->tiles[i].old_tile = n_action->tiles[i].new_tile;
        n_action->tiles[i].new_tile = old_tmp;
    }
}

void NirvanaEditor_MainFrame::stage_action_setTile_iso(nirvana_stageAction* n_action)
{
    if(! project )
        return;

    int stage_index = n_action->stage_index;
    int layer_index = n_action->layer_index;

    if(stage_index < 0 || stage_index >= project->stages.size())
        return;

    if(layer_index < 0 || layer_index >= project->stages[stage_index].layers.size())
        return;

    //std::cout << "DBG: NUM_TILES = " << n_action.tiles.size() << std::endl;

    for(int i = 0; i < n_action->tiles.size(); i++)
    {
        int iso_map = n_action->tiles[i].iso_map;
        int tmap_x = n_action->tiles[i].map_tile_pos_x;
        int tmap_y = n_action->tiles[i].map_tile_pos_y;

        //std::cout << "YOLO: (" << tmap_x << ", " << tmap_y << ") -> " << n_action.tiles[i].old_tile << ", " << n_action.tiles[i].new_tile << std::endl;

        switch(iso_map)
        {
            case 0:
            {
                //std::cout << "iso 0" << std::endl;
                project->stages[stage_index].layers[layer_index].layer_map.tile_map.rows[tmap_y].tile[tmap_x] = n_action->tiles[i].old_tile;
            }
            break;

            case 1:
            {
                //std::cout << "iso 1" << std::endl;
                project->stages[stage_index].layers[layer_index].layer_map.tile_map2.rows[tmap_y].tile[tmap_x] = n_action->tiles[i].old_tile;
            }
            break;
        }

        int tmp_tile = n_action->tiles[i].old_tile;
        n_action->tiles[i].old_tile = n_action->tiles[i].new_tile;
        n_action->tiles[i].new_tile =  tmp_tile;
    }

    //std::cout << "------------------" << std::endl;
}


void NirvanaEditor_MainFrame::stage_action_fillTile(nirvana_stageAction* n_action)
{
    if(! project )
        return;

    int stage_index = n_action->stage_index;
    int layer_index = n_action->layer_index;

    if(stage_index < 0 || stage_index >= project->stages.size())
        return;

    if(layer_index < 0 || layer_index >= project->stages[stage_index].layers.size())
        return;

    if(!map_editor)
        return;

    if(!map_editor->getMapViewControl())
        return;

    wxIrrlicht* map_view = map_editor->getMapViewControl();

    int current_layer = map_editor->getSelectedLayer();
    map_editor->selectLayer(layer_index);

    for(int i = 0; i < n_action->tiles.size(); i++)
    {
        int iso_map = n_action->tiles[i].iso_map;

        int tmap_x = n_action->tiles[i].map_tile_pos_x;
        int tmap_y = n_action->tiles[i].map_tile_pos_y;

        int base_tile = n_action->tiles[i].old_tile;
        int fill_tile = n_action->tiles[i].new_tile;

        n_action->tiles[i].old_tile = fill_tile;
        n_action->tiles[i].new_tile = base_tile;

        map_view->util_fillTile(fill_tile, base_tile, tmap_x, tmap_y);
    }

    map_editor->selectLayer(current_layer);
}

void NirvanaEditor_MainFrame::stage_action_fillTile_iso(nirvana_stageAction* n_action)
{
    if(! project )
        return;

    int stage_index = n_action->stage_index;
    int layer_index = n_action->layer_index;

    if(stage_index < 0 || stage_index >= project->stages.size())
        return;

    if(layer_index < 0 || layer_index >= project->stages[stage_index].layers.size())
        return;

    if(!map_editor)
        return;

    if(!map_editor->getMapViewControl())
        return;

    wxIrrlicht* map_view = map_editor->getMapViewControl();

    int current_layer = map_editor->getSelectedLayer();
    map_editor->selectLayer(layer_index);

    for(int i = 0; i < n_action->tiles.size(); i++)
    {
        int iso_map = n_action->tiles[i].iso_map;

        bool use_map2 = (iso_map == 0 ? false : true);

        int tmap_x = n_action->tiles[i].map_tile_pos_x;
        int tmap_y = n_action->tiles[i].map_tile_pos_y;

        int base_tile = n_action->tiles[i].old_tile;
        int fill_tile = n_action->tiles[i].new_tile;

        n_action->tiles[i].old_tile = fill_tile;
        n_action->tiles[i].new_tile = base_tile;

        map_view->util_fillTile_ISO(fill_tile, base_tile, tmap_x, tmap_y, use_map2);
    }

    map_editor->selectLayer(current_layer);
}



void NirvanaEditor_MainFrame::stage_action_moveTile(nirvana_stageAction* n_action)
{
    if(! project )
        return;

    int stage_index = n_action->stage_index;
    int layer_index = n_action->layer_index;

    if(stage_index < 0 || stage_index >= project->stages.size())
        return;

    if(layer_index < 0 || layer_index >= project->stages[stage_index].layers.size())
        return;

    if(!map_editor)
        return;

    if(!map_editor->getMapViewControl())
        return;

    wxIrrlicht* map_view = map_editor->getMapViewControl();

    stage_action_setTile(n_action);

    map_view->mapEdit_selectTileTool_selection.clear();
}

void NirvanaEditor_MainFrame::stage_action_moveTile_iso(nirvana_stageAction* n_action)
{
    if(! project )
        return;

    int stage_index = n_action->stage_index;
    int layer_index = n_action->layer_index;

    if(stage_index < 0 || stage_index >= project->stages.size())
        return;

    if(layer_index < 0 || layer_index >= project->stages[stage_index].layers.size())
        return;

    if(!map_editor)
        return;

    if(!map_editor->getMapViewControl())
        return;

    wxIrrlicht* map_view = map_editor->getMapViewControl();

    stage_action_setTile_iso(n_action);

    map_view->mapEdit_selectTileTool_selection.clear();
}


void NirvanaEditor_MainFrame::stage_action_createSprite(nirvana_stageAction* n_action)
{
    if(! project )
        return;

    int stage_index = n_action->stage_index;
    int layer_index = n_action->layer_index;

    if(stage_index < 0 || stage_index >= project->stages.size())
        return;

    if(layer_index < 0 || layer_index >= project->stages[stage_index].layers.size())
        return;

    if(!map_editor)
        return;

    if(!map_editor->getMapViewControl())
        return;

    wxIrrlicht* map_view = map_editor->getMapViewControl();

    int current_canvas = map_view->active_canvas;

    map_view->mapEdit_getContext();
    map_view->setActiveCanvas(project->stages[stage_index].layers[layer_index].ref_canvas);

    for(int i = 0; i < n_action->sprite.size(); i++)
    {
        int sprite_index = project->addLayerSprite(stage_index, layer_index, n_action->sprite[i].id_name, n_action->sprite[i].base_sprite_index, n_action->sprite[i].pos_x, n_action->sprite[i].pos_y);

        if(sprite_index < 0 || sprite_index >= project->stages[stage_index].layers[layer_index].layer_sprites.size())
        {
            continue;
        }

        map_view->addLayerSprite(layer_index, sprite_index);

        int sprite_id = project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].map_sprite_id;

        n_action->sprite[i].sprite_id = sprite_id;
        n_action->sprite[i].layer_sprite_unique_id = project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].layer_sprite_unique_id;

        double angle = n_action->sprite[i].angle;

        double scale_x = n_action->sprite[i].scale_x;
        double scale_y = n_action->sprite[i].scale_y;

        bool visible = n_action->sprite[i].visible;

        irr::u8 alpha = n_action->sprite[i].alpha;

        int body_type = n_action->sprite[i].body_type;

        map_view->setSpriteRotation(sprite_id, angle);
        map_view->setSpriteScale(sprite_id, scale_x, scale_y);
        map_view->setSpriteAlpha(sprite_id, alpha);
        map_view->setSpriteVisible(sprite_id, visible);

        int sprite_base_index = n_action->sprite[i].base_sprite_index;

        if(sprite_base_index >= 0 && sprite_base_index < project->sprite_base.size())
        {
            for(int ani = 0; ani < project->sprite_base[sprite_base_index].object.animation.size(); ani++)
            {
                if(project->sprite_base[sprite_base_index].object.animation[ani].name.compare(n_action->sprite[i].animation_name)==0)
                {
                    map_view->setSpriteAnimation(sprite_id, ani, -1);
                    break;
                }
            }
        }

        project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].angle = angle;
        project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].scale.set(scale_x, scale_y);
        project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].alpha = alpha;
        project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].visible = visible;
        project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].body_type = body_type;
        project->stages[stage_index].layers[layer_index].layer_sprites[sprite_index].animation_name = n_action->sprite[i].animation_name;

        if(map_editor->getSelectedLayer() == layer_index)
        {
            m_mapEdit_layerSprite_listBox->AppendAndEnsureVisible(wxString(n_action->sprite[i].id_name));
            m_mapEdit_layerSprite_listBox->SetSelection(project->getLayerSpriteIndex(stage_index, layer_index, n_action->sprite[i].id_name));
            map_view->mapEdit_selectSpriteTool_selection.clear();

            reloadSpriteProperties();
        }
    }

    map_view->setActiveCanvas(current_canvas);
}

void NirvanaEditor_MainFrame::stage_action_deleteSprite(nirvana_stageAction* n_action)
{
    if(! project )
        return;

    int stage_index = n_action->stage_index;
    int layer_index = n_action->layer_index;

    if(stage_index < 0 || stage_index >= project->stages.size())
        return;

    if(layer_index < 0 || layer_index >= project->stages[stage_index].layers.size())
        return;

    if(!map_editor)
        return;

    if(!map_editor->getMapViewControl())
        return;

    wxIrrlicht* map_view = map_editor->getMapViewControl();


    int sprite_id = -1;


    for(int i = 0; i < n_action->sprite.size(); i++)
    {
        sprite_id = n_action->sprite[i].sprite_id;
        n_action->sprite[i].sprite_id = -1;
        //map_view->setSpritePosition(sprite_id, pos_x, pos_y);

        if(sprite_id < 0 || sprite_id >= map_view->sprite.size())
        {
            //wxMessageBox(_("sprite_id = ") + wxString::Format(_("%i"), sprite_id));
            continue;
        }


        irr::core::array<int> layer_spr_array; //The irrlicht array has built-in sort and I don't feel like doing it myself

        int spr_index = map_view->sprite[sprite_id].layer_sprite_index;

        map_view->deleteSprite(sprite_id);

        project->deleteLayerSprite(stage_index, layer_index, spr_index);
    }

    // REMAP LAYER_SPRITE_INDEX for remaining sprites on the current layer
    int ref_canvas = project->stages[stage_index].layers[layer_index].ref_canvas;

    if(ref_canvas >= 0 && ref_canvas < map_view->canvas.size())
    {
        for(int i = 0; i < map_view->canvas[ref_canvas].sprite_id.size(); i++)
        {
            int map_spr_id = map_view->canvas[ref_canvas].sprite_id[i];

            if(map_spr_id < 0 || map_spr_id >= map_view->sprite.size())
                continue;

            if(!map_view->sprite[map_spr_id].active)
                continue;

            for(int lsi = 0; lsi < project->stages[stage_index].layers[layer_index].layer_sprites.size(); lsi++)
            {
                if(map_view->sprite[map_spr_id].layer_sprite_unique_id == project->stages[stage_index].layers[layer_index].layer_sprites[lsi].layer_sprite_unique_id)
                {
                    map_view->sprite[map_spr_id].layer_sprite_index = lsi;
                    break;
                }
            }
        }
    }

    if(map_editor->getSelectedLayer() != layer_index)
        return;


    map_view->mapEdit_selectSpriteTool_selection.clear();
    map_view->selected_sprite = -1;

    m_mapEdit_layerSprite_listBox->Clear();

    for(int i = 0; i < project->stages[stage_index].layers[layer_index].layer_sprites.size(); i++)
    {
        wxString list_spr_name = wxString(project->stages[stage_index].layers[layer_index].layer_sprites[i].sprite_name).Trim();
        m_mapEdit_layerSprite_listBox->AppendAndEnsureVisible(list_spr_name);
    }

}

void NirvanaEditor_MainFrame::stage_action_transformSprite(nirvana_stageAction* n_action)
{
    if(! project )
        return;

    int stage_index = n_action->stage_index;
    int layer_index = n_action->layer_index;

    if(stage_index < 0 || stage_index >= project->stages.size())
        return;

    if(layer_index < 0 || layer_index >= project->stages[stage_index].layers.size())
        return;

    if(!map_editor)
        return;

    if(!map_editor->getMapViewControl())
        return;

    wxIrrlicht* map_view = map_editor->getMapViewControl();


    int sprite_id = -1;

    int pos_x = -1;
    int pos_y = -1;

    double angle = -1;

    double scale_x = -1;
    double scale_y = -1;


    for(int i = 0; i < n_action->sprite.size(); i++)
    {
        sprite_id = n_action->sprite[i].sprite_id;

        if(n_action->isUndo)
        {
            pos_x = n_action->sprite[i].old_pos_x;
            pos_y = n_action->sprite[i].old_pos_y;
        }
        else
        {
            pos_x = n_action->sprite[i].pos_x;
            pos_y = n_action->sprite[i].pos_y;
        }

        if(n_action->isUndo)
        {
            angle = n_action->sprite[i].old_angle;
        }
        else
        {
            angle = n_action->sprite[i].angle;
        }

        if(n_action->isUndo)
        {
            scale_x = n_action->sprite[i].old_scale_x;
            scale_y = n_action->sprite[i].old_scale_y;
        }
        else
        {
            scale_x = n_action->sprite[i].scale_x;
            scale_y = n_action->sprite[i].scale_y;
        }

        map_view->setSpritePosition(sprite_id, pos_x, pos_y);

        map_view->setSpriteRotation(sprite_id, angle);

        map_view->setSpriteScale(sprite_id, scale_x, scale_y);
    }
}


void NirvanaEditor_MainFrame::stage_action_createTileSprite(nirvana_stageAction* n_action)
{
    if(! project )
        return;

    int stage_index = n_action->stage_index;
    int layer_index = n_action->layer_index;

    if(stage_index < 0 || stage_index >= project->stages.size())
        return;

    if(layer_index < 0 || layer_index >= project->stages[stage_index].layers.size())
        return;

    if(!map_editor)
        return;

    if(!map_editor->getMapViewControl())
        return;

    wxIrrlicht* map_view = map_editor->getMapViewControl();

    int current_canvas = map_view->active_canvas;
    int canvas_id = project->stages[stage_index].layers[layer_index].ref_canvas;
    map_view->setActiveCanvas(canvas_id);


    for(int i = 0; i < n_action->sprite.size(); i++)
    {
        tileSprite_obj tsprite = n_action->sprite[i].t_sprite;

        if(tsprite.sprite_id >= 0)
        {
            map_view->deleteSprite(tsprite.sprite_id);
            tsprite.sprite_id = -1;
        }


        //std::cout << "pre create: image=" << tsprite.image_id << "  canvas=" << canvas_id << "  size=(" << tsprite.width << ", " << tsprite.height << ")" << std::endl;

        tsprite.sprite_id = map_view->createSprite(-1, tsprite.image_id, tsprite.width, tsprite.height);

        map_view->setSpritePosition(tsprite.sprite_id, tsprite.x, tsprite.y);

        //std::cout << "spr_id=" << tsprite.sprite_id << std::endl << std::endl;

        int layer_ts_index = n_action->sprite[i].layer_ts_index;


        if(layer_ts_index < 0 || layer_ts_index >= project->stages[stage_index].layers[layer_index].layer_tile_sprites.size())
        {
            map_view->sprite[tsprite.sprite_id].layer_ts_index = project->stages[stage_index].layers[layer_index].layer_tile_sprites.size();
            project->stages[stage_index].layers[layer_index].layer_tile_sprites.push_back(tsprite);
        }
        else
        {
            map_view->sprite[tsprite.sprite_id].layer_ts_index = layer_ts_index;
            project->stages[stage_index].layers[layer_index].layer_tile_sprites[layer_ts_index] = tsprite;
        }

        n_action->sprite[i].t_sprite = tsprite;
    }

    map_view->setActiveCanvas(current_canvas);

}


void NirvanaEditor_MainFrame::stage_action_deleteTileSprite(nirvana_stageAction* n_action)
{
    if(! project )
        return;

    int stage_index = n_action->stage_index;
    int layer_index = n_action->layer_index;

    if(stage_index < 0 || stage_index >= project->stages.size())
        return;

    if(layer_index < 0 || layer_index >= project->stages[stage_index].layers.size())
        return;

    if(!map_editor)
        return;

    if(!map_editor->getMapViewControl())
        return;

    wxIrrlicht* map_view = map_editor->getMapViewControl();

    for(int i = 0; i < n_action->sprite.size(); i++)
    {
        int sprite_id = n_action->sprite[i].t_sprite.sprite_id;

        map_view->deleteSprite(sprite_id);

        int layer_ts = n_action->sprite[i].layer_ts_index;

        if(layer_ts < 0 || layer_ts >= project->stages[stage_index].layers[layer_index].layer_tile_sprites.size())
            continue;

        project->stages[stage_index].layers[layer_index].layer_tile_sprites[layer_ts].sprite_id = -1;
        project->stages[stage_index].layers[layer_index].layer_tile_sprites[layer_ts].sheet_index = -1;
        project->stages[stage_index].layers[layer_index].layer_tile_sprites[layer_ts].image_id = -1;
        project->stages[stage_index].layers[layer_index].layer_tile_sprites[layer_ts].cut_index = -1;
        project->stages[stage_index].layers[layer_index].layer_tile_sprites[layer_ts].tset = -1;

        n_action->sprite[i].t_sprite.sprite_id = -1;
    }

    map_view->mapEdit_selectSpriteTool_selection.clear();
    map_view->selected_sprite = -1;
}



void NirvanaEditor_MainFrame::stage_action_transformTileSprite(nirvana_stageAction* n_action)
{
    if(! project )
        return;

    int stage_index = n_action->stage_index;
    int layer_index = n_action->layer_index;

    if(stage_index < 0 || stage_index >= project->stages.size())
        return;

    if(layer_index < 0 || layer_index >= project->stages[stage_index].layers.size())
        return;

    if(!map_editor)
        return;

    if(!map_editor->getMapViewControl())
        return;

    wxIrrlicht* map_view = map_editor->getMapViewControl();


    int sprite_id = -1;

    int pos_x = -1;
    int pos_y = -1;

    double angle = -1;

    double scale_x = -1;
    double scale_y = -1;

    int ts_index = -1;


    for(int i = 0; i < n_action->sprite.size(); i++)
    {
        sprite_id = n_action->sprite[i].sprite_id;

        ts_index = n_action->sprite[i].layer_ts_index;

        if(n_action->isUndo)
        {
            pos_x = n_action->sprite[i].old_pos_x;
            pos_y = n_action->sprite[i].old_pos_y;
        }
        else
        {
            pos_x = n_action->sprite[i].pos_x;
            pos_y = n_action->sprite[i].pos_y;
        }

        map_view->setSpritePosition(sprite_id, pos_x, pos_y);

        //map_view->setSpriteRotation(sprite_id, angle);

        //map_view->setSpriteScale(sprite_id, scale_x, scale_y);

        if(ts_index >= 0 && ts_index < project->stages[stage_index].layers[layer_index].layer_tile_sprites.size())
        {
            project->stages[stage_index].layers[layer_index].layer_tile_sprites[ts_index].x = pos_x;
            project->stages[stage_index].layers[layer_index].layer_tile_sprites[ts_index].y = pos_y;
        }
    }
}


void NirvanaEditor_MainFrame::stage_action_createShape(nirvana_stageAction* n_action)
{
    if(! project )
        return;

    int stage_index = n_action->stage_index;
    int layer_index = n_action->layer_index;

    if(stage_index < 0 || stage_index >= project->stages.size())
        return;

    if(layer_index < 0 || layer_index >= project->stages[stage_index].layers.size())
        return;

    int shape_index = -1;

    for(int i = 0; i < n_action->sprite.size(); i++)
    {
        shape_index = n_action->sprite[i].project_shape_index;

        if(shape_index < 0)
            continue;

        if(map_editor->getSelectedLayer() == layer_index)
            map_editor->selectShape(shape_index);

        project->stages[stage_index].layers[layer_index].layer_shapes.insert(project->stages[stage_index].layers[layer_index].layer_shapes.begin() + shape_index, n_action->sprite[i].old_shape.shape_obj);
    }



    if(map_editor->getSelectedLayer() != layer_index)
        return;


    m_mapEdit_collisionShape_listBox->DeselectAll();
	m_mapEdit_collisionShape_listBox->Clear();
	for(int i = 0; i < project->stages[stage_index].layers[layer_index].layer_shapes.size(); i++)
	{
		m_mapEdit_collisionShape_listBox->AppendAndEnsureVisible(wxString(project->stages[stage_index].layers[layer_index].layer_shapes[i].shape_name));
	}

	if(shape_index >= 0 && shape_index < m_mapEdit_collisionShape_listBox->GetCount())
        m_mapEdit_collisionShape_listBox->SetSelection(shape_index);

    refreshCurrentShapeUI();
}

void NirvanaEditor_MainFrame::stage_action_deleteShape(nirvana_stageAction* n_action)
{
    if(! project )
        return;

    int stage_index = n_action->stage_index;
    int layer_index = n_action->layer_index;

    if(stage_index < 0 || stage_index >= project->stages.size())
        return;

    if(layer_index < 0 || layer_index >= project->stages[stage_index].layers.size())
        return;

    for(int i = 0; i < n_action->sprite.size(); i++)
    {
        int shape_index = n_action->sprite[i].project_shape_index;

        if(shape_index < 0)
            continue;

        project->deleteShape(stage_index, layer_index, shape_index);
    }

    if(map_editor->getSelectedLayer() != layer_index)
        return;

    map_editor->selectShape(-1);
    m_mapEdit_collisionShape_listBox->DeselectAll();
	m_mapEdit_collisionShape_listBox->Clear();
	for(int i = 0; i < project->stages[stage_index].layers[layer_index].layer_shapes.size(); i++)
	{
		m_mapEdit_collisionShape_listBox->AppendAndEnsureVisible(wxString(project->stages[stage_index].layers[layer_index].layer_shapes[i].shape_name));
	}

    refreshCurrentShapeUI();
}

void NirvanaEditor_MainFrame::stage_action_transformShape(nirvana_stageAction* n_action)
{
    if(! project )
        return;

    int stage_index = n_action->stage_index;
    int layer_index = n_action->layer_index;

    if(stage_index < 0 || stage_index >= project->stages.size())
        return;

    if(layer_index < 0 || layer_index >= project->stages[stage_index].layers.size())
        return;

    if(!map_editor)
        return;

    if(!map_editor->getMapViewControl())
        return;

    wxIrrlicht* map_view = map_editor->getMapViewControl();

    int current_canvas = map_view->active_canvas;

    //map_view->mapEdit_getContext();
    //map_view->setActiveCanvas(project->stages[stage_index].layers[layer_index].ref_canvas);

    for(int i = 0; i < n_action->sprite.size(); i++)
    {
        int shape_index = n_action->sprite[i].project_shape_index;

        //map_editor->selectShape(shape_index);

        //wxMessageBox(_("SHAPE: ") + wxString::Format(_("%i"), shape_index));

        project->stages[stage_index].layers[layer_index].layer_shapes[shape_index] = n_action->sprite[i].old_shape.shape_obj;

        nirvana_stageAction_shape tmp_shape = n_action->sprite[i].old_shape;

        n_action->sprite[i].old_shape = n_action->sprite[i].new_shape;
        n_action->sprite[i].new_shape = tmp_shape;
    }

    if(map_editor->getSelectedLayer() == layer_index)
        refreshCurrentShapeUI();

    //map_view->setActiveCanvas(current_canvas);
}


void NirvanaEditor_MainFrame::stage_action_setBackground(nirvana_stageAction* n_action)
{
    if(! project )
        return;

    int stage_index = n_action->stage_index;
    int layer_index = n_action->layer_index;

    if(stage_index < 0 || stage_index >= project->stages.size())
        return;

    if(layer_index < 0 || layer_index >= project->stages[stage_index].layers.size())
        return;

    if(!map_editor)
        return;

    if(!map_editor->getMapViewControl())
        return;

    wxIrrlicht* map_view = map_editor->getMapViewControl();


    if(map_view->imageExists(n_action->bkg.new_bkg.image_id))
		map_view->deleteImage(n_action->bkg.new_bkg.image_id);

    n_action->bkg.new_bkg.image_id = -1;
    project->stages[stage_index].layers[layer_index].bkg.image_id = -1;

    wxFileName fname(project->getDir());
	fname.AppendDir(project->bkg_path);
	fname.SetFullName(wxString(n_action->bkg.new_bkg.img_file));

	if(fname.Exists())
    {
        //std::cout << "CHANGE IMG" << std::endl;
        project->stages[stage_index].layers[layer_index].bkg = n_action->bkg.old_bkg;

        project->stages[stage_index].layers[layer_index].bkg.image_id = map_view->loadImage(fname.GetAbsolutePath().ToStdString());

        if(project->stages[stage_index].layers[layer_index].ref_canvas >= 0 && project->stages[stage_index].layers[layer_index].ref_canvas < map_view->canvas.size())
        {
            map_view->canvas[project->stages[stage_index].layers[layer_index].ref_canvas].bkg_render_image_id = project->stages[stage_index].layers[layer_index].bkg.image_id;
        }

        n_action->bkg.old_bkg.image_id = project->stages[stage_index].layers[layer_index].bkg.image_id;
    }


    if(layer_index == map_editor->getSelectedLayer())
    {
        if(n_action->bkg.old_bkg.render_setting >= 0 && n_action->bkg.old_bkg.render_setting < 4)
        {
            std::cout << "bKG Setting: " << n_action->bkg.old_bkg.render_setting << std::endl;
            m_mapEdit_canvasRenderSetting_comboBox->SetSelection(n_action->bkg.old_bkg.render_setting);
        }


        wxString bkg_image = wxString(n_action->bkg.old_bkg.img_file).Trim();

        for(int i = 0; i < m_mapEdit_canvasImage_comboBox->GetCount(); i++)
        {
            if(m_mapEdit_canvasImage_comboBox->GetString(i).Trim().compare(bkg_image)==0)
            {
                m_mapEdit_canvasImage_comboBox->SetSelection(i);
                break;
            }
        }

    }



    Nirvana_Map_Background tmp_bkg = n_action->bkg.old_bkg;

    n_action->bkg.old_bkg = n_action->bkg.new_bkg;
    n_action->bkg.new_bkg = tmp_bkg;

    map_view->initLayer(layer_index);
}


void NirvanaEditor_MainFrame::stage_undo()
{
    if(undo_buffer.size() == 0)
        return;

    nirvana_stageAction n_action = pop_undo();
    n_action.isUndo = true;


    switch(n_action.action_type)
    {
        case NIRVANA_ACTION_CREATESPRITE:
        case NIRVANA_ACTION_DELETESPRITE:
        case NIRVANA_ACTION_COPYSPRITE:
        case NIRVANA_ACTION_TRANSFORM_SPRITE:
            m_mapEdit_layerObjectTools_auinotebook->SetSelection( m_mapEdit_layerObjectTools_auinotebook->GetPageIndex(m_mapEdit_sprite_panel) );
        break;

        case NIRVANA_ACTION_MOVESHAPE:
        case NIRVANA_ACTION_DRAWPOINT:
        case NIRVANA_ACTION_CREATESHAPE:
        case NIRVANA_ACTION_DELETESHAPE:
            m_mapEdit_layerObjectTools_auinotebook->SetSelection( m_mapEdit_layerObjectTools_auinotebook->GetPageIndex(m_mapEdit_collision_panel) );
        break;

        case NIRVANA_ACTION_SETBKG:
            m_mapEdit_layerObjectTools_auinotebook->SetSelection( m_mapEdit_layerObjectTools_auinotebook->GetPageIndex(m_mapEdit_displayImage_panel) );
        break;
    }

    switch(n_action.action_type)
    {
        case NIRVANA_ACTION_SETTILE:
        {
            //std::cout << "DEBUG: UNDO SETTILE" << std::endl;
            stage_action_setTile(&n_action);
        }
        break;

        case NIRVANA_ACTION_FILLTILE:
        {
            stage_action_fillTile(&n_action);
        }
        break;

        case NIRVANA_ACTION_COPYTILE:
        {
            stage_action_moveTile(&n_action);
        }
        break;

        case NIRVANA_ACTION_MOVETILE:
        {
            stage_action_moveTile(&n_action);
        }
        break;

        case NIRVANA_ACTION_DELETETILE:
        {
            stage_action_moveTile(&n_action);
        }
        break;

        case NIRVANA_ACTION_TRANSFORM_SPRITE:
        {
            stage_action_transformSprite(&n_action);
        }
        break;

        case NIRVANA_ACTION_TRANSFORM_TSPRITE:
        {
            stage_action_transformTileSprite(&n_action);
        }
        break;

        case NIRVANA_ACTION_CREATE_TSPRITE:
        {
            //std::cout << "DBG: Delete T_SPR" << std::endl;
            stage_action_deleteTileSprite(&n_action);
        }
        break;

        case NIRVANA_ACTION_DELETE_TSPRITE:
        {
            //std::cout << "DEBUG: DELETE T_SPRITE" << std::endl;
            stage_action_createTileSprite(&n_action);
        }
        break;

        case NIRVANA_ACTION_CREATESPRITE:
        {
            stage_action_deleteSprite(&n_action);
        }
        break;

        case NIRVANA_ACTION_DELETESPRITE:
        {
            stage_action_createSprite(&n_action);
        }
        break;

        case NIRVANA_ACTION_COPYSPRITE:
        {
            stage_action_deleteSprite(&n_action);
        }
        break;

        case NIRVANA_ACTION_MOVESHAPE:
        {
            stage_action_transformShape(&n_action);
        }
        break;

        case NIRVANA_ACTION_DRAWPOINT:
        {
            stage_action_transformShape(&n_action);
        }
        break;

        case NIRVANA_ACTION_CREATESHAPE:
        {
            stage_action_deleteShape(&n_action);
        }
        break;

        case NIRVANA_ACTION_DELETESHAPE:
        {
            stage_action_createShape(&n_action);
        }
        break;

        case NIRVANA_ACTION_SETBKG:
        {
            stage_action_setBackground(&n_action);
        }
        break;

        case NIRVANA_ACTION_SETTILE_ISO:
        {
            stage_action_setTile_iso(&n_action);
        }
        break;

        case NIRVANA_ACTION_FILLTILE_ISO:
        {
            stage_action_fillTile_iso(&n_action);
        }
        break;

        case NIRVANA_ACTION_MOVETILE_ISO:
        {
            stage_action_moveTile_iso(&n_action);
        }
        break;

        case NIRVANA_ACTION_COPYTILE_ISO:
        {
            stage_action_moveTile_iso(&n_action);
        }
        break;

        case NIRVANA_ACTION_DELETETILE_ISO:
        {
            stage_action_moveTile_iso(&n_action);
        }
        break;
    }

    push_redo(n_action);
}


void NirvanaEditor_MainFrame::stage_redo()
{
    if(redo_buffer.size() == 0)
        return;

    nirvana_stageAction n_action = pop_redo();
    n_action.isUndo = false;

    switch(n_action.action_type)
    {
        case NIRVANA_ACTION_CREATESPRITE:
        case NIRVANA_ACTION_DELETESPRITE:
        case NIRVANA_ACTION_COPYSPRITE:
        case NIRVANA_ACTION_TRANSFORM_SPRITE:
            m_mapEdit_layerObjectTools_auinotebook->SetSelection( m_mapEdit_layerObjectTools_auinotebook->GetPageIndex(m_mapEdit_sprite_panel) );
        break;

        case NIRVANA_ACTION_MOVESHAPE:
        case NIRVANA_ACTION_DRAWPOINT:
        case NIRVANA_ACTION_CREATESHAPE:
        case NIRVANA_ACTION_DELETESHAPE:
            m_mapEdit_layerObjectTools_auinotebook->SetSelection( m_mapEdit_layerObjectTools_auinotebook->GetPageIndex(m_mapEdit_collision_panel) );
        break;

        case NIRVANA_ACTION_SETBKG:
            m_mapEdit_layerObjectTools_auinotebook->SetSelection( m_mapEdit_layerObjectTools_auinotebook->GetPageIndex(m_mapEdit_displayImage_panel) );
        break;
    }

    switch(n_action.action_type)
    {
        case NIRVANA_ACTION_SETTILE:
        {
            //std::cout << "DEBUG: UNDO SETTILE" << std::endl;
            stage_action_setTile(&n_action);
        }
        break;

        case NIRVANA_ACTION_FILLTILE:
        {
            stage_action_fillTile(&n_action);
        }
        break;

        case NIRVANA_ACTION_COPYTILE:
        {
            stage_action_moveTile(&n_action);
        }
        break;

        case NIRVANA_ACTION_MOVETILE:
        {
            stage_action_moveTile(&n_action);
        }
        break;

        case NIRVANA_ACTION_DELETETILE:
        {
            stage_action_moveTile(&n_action);
        }
        break;

        case NIRVANA_ACTION_TRANSFORM_SPRITE:
        {
            stage_action_transformSprite(&n_action);
        }
        break;

        case NIRVANA_ACTION_TRANSFORM_TSPRITE:
        {
            stage_action_transformTileSprite(&n_action);
        }
        break;

        case NIRVANA_ACTION_CREATE_TSPRITE:
        {
            //std::cout << "DBG: Delete T_SPR" << std::endl;
            stage_action_createTileSprite(&n_action);
        }
        break;

        case NIRVANA_ACTION_DELETE_TSPRITE:
        {
            //std::cout << "DEBUG: DELETE T_SPRITE" << std::endl;
            stage_action_deleteTileSprite(&n_action);
        }
        break;

        case NIRVANA_ACTION_CREATESPRITE:
        {
            stage_action_createSprite(&n_action);
        }
        break;

        case NIRVANA_ACTION_DELETESPRITE:
        {
            stage_action_deleteSprite(&n_action);
        }
        break;

        case NIRVANA_ACTION_COPYSPRITE:
        {
            stage_action_createSprite(&n_action);
        }
        break;

        case NIRVANA_ACTION_MOVESHAPE:
        {
            stage_action_transformShape(&n_action);
        }
        break;

        case NIRVANA_ACTION_DRAWPOINT:
        {
            stage_action_transformShape(&n_action);
        }
        break;

        case NIRVANA_ACTION_CREATESHAPE:
        {
            stage_action_createShape(&n_action);
        }
        break;

        case NIRVANA_ACTION_DELETESHAPE:
        {
            stage_action_deleteShape(&n_action);
        }
        break;

        case NIRVANA_ACTION_SETBKG:
        {
            stage_action_setBackground(&n_action);
        }
        break;

        case NIRVANA_ACTION_SETTILE_ISO:
        {
            stage_action_setTile_iso(&n_action);
        }
        break;

        case NIRVANA_ACTION_FILLTILE_ISO:
        {
            stage_action_fillTile_iso(&n_action);
        }
        break;

        case NIRVANA_ACTION_MOVETILE_ISO:
        {
            stage_action_moveTile_iso(&n_action);
        }
        break;

        case NIRVANA_ACTION_COPYTILE_ISO:
        {
            stage_action_moveTile_iso(&n_action);
        }
        break;

        case NIRVANA_ACTION_DELETETILE_ISO:
        {
            stage_action_moveTile_iso(&n_action);
        }
        break;
    }

    push_undo(n_action);
}
