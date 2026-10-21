#ifndef NIRVANAENGINE_STRUCTS_H_INCLUDED
#define NIRVANAENGINE_STRUCTS_H_INCLUDED

#include <irrlicht.h>
#include <vector>

#include "rc_defines.h"

struct canvas_obj
{
    irr::video::ITexture* texture;

    int type;

    irr::core::dimension2d<irr::u32> dimension;

    struct rc_canvas_viewport
    {
        irr::core::vector2d<irr::s32> position;
        irr::core::dimension2d<irr::u32> dimension;
    } viewport;


    irr::core::vector2d<irr::s32> offset;

    bool visible = true;
    int z = 0;

    irr::u32 color_mod;

    irr::core::array<irr::s32> sprite_id;

    int bkg_render_type = -1;
    int bkg_render_image_id = -1;
    int layer_index = -1;

    int tilemap;
};

struct CircleSettings
{
    irr::core::vector2di center;       // in screen coordinates
    irr::f32 radius;             // in pixels
    irr::f32 radius2;
    irr::video::SColor color;
    irr::u32 numVertices = 21;   // including center
};

struct image_obj
{
    std::string file_name;
    irr::video::ITexture* image;
    irr::u8 alpha = 255;
    irr::video::SColor color_mod = irr::video::SColor(255,255,255,255);
};

struct tile_obj
{
	int id;

	double fps;
	int num_frames;
	int current_frame;
	std::vector<int> frames;

	irr::u32 frame_start_time;
	irr::u32 frame_swap_time;
};

struct tileset_obj
{
	bool active;

	int img_id = -1;
	bool color_set_flag;
	irr::u32 default_color_key;

	int tile_width;
	int tile_height;

	std::vector<tile_obj> tiles;

	//specifically for export purposes
	int mask_start_index = -1;
};

struct tilemap_row_obj
{
	std::vector<int> tile;
};

struct tilemask_obj
{
	bool active = false;
	std::string mask_name;
	std::vector<bool> tiles;
};

struct tilemap_obj
{
	bool active;

	int tileset = -1;
	irr::video::ITexture* texture = NULL;

	int num_tiles_across;
	int num_tiles_down;

	std::vector<tilemap_row_obj> rows;

	//std::vector<tilemap_row_obj> iso_rows1;
	//std::vector<tilemap_row_obj> iso_rows2;
};

struct nv_editor_point
{
	irr::core::vector2di position;
	bool selected = false;
};

struct sprite2D_physics_obj
{
	std::string shape_name;

	bool init = false; //specifically to prevent project from overriding default values on creation

	bool detached = false;

	int body_type;
	int shape_type;

	int offset_x;
	int offset_y;

	//box points
	bool ul_selected = false;
	bool ll_selected = false;
	bool ur_selected = false;
	bool lr_selected = false;

	//circle points
	bool top_selected = false;
	bool left_selected = false;
	bool right_selected = false;
	bool bottom_selected = false;

	int box_width;
	int box_height;

	double radius;

	irr::core::array<bool> point_selection;
	irr::core::array<irr::core::vector2di> points;
	irr::core::array<irr::core::vector2di> prev_points;
	irr::core::array<irr::core::vector2di> next_points;
};

struct sprite2D_animation_obj
{
	std::string name;

	int image_file_index; //index in Nirvana_SpriteBase
	int animation_image_id;
	irr::core::array<int> frames;

	int num_frames;

	int current_frame;

	double fps;
	double frame_start_time;
	double frame_swap_time;
};

struct sprite2D_obj
{
	int id; //This is needed to reference this sprite in the contact listener
	bool active = false;
	int image_id;
	int active_image_id; //used for loading stages
	int sheet_numFrames;
	int frames_per_row;

	int layer_sprite_index = -1;
	int layer_sprite_unique_id = -1;
	int layer_ts_index = -1;

	int type;

	irr::core::vector2di position;
	double angle;

	irr::core::vector2df scale;

	irr::core::dimension2di frame_size;

	bool visible = true;
	irr::u8 alpha;

	irr::video::SColor color_mod;

	bool isSolid = false;
	sprite2D_physics_obj physics;

	int current_animation;
	int num_animation_loops;
	int current_animation_loop;
	bool isPlaying;
	irr::core::array<int> deleted_animation;
	irr::core::array<sprite2D_animation_obj> animation;

	int parent_canvas = -1;

	double z;

	//specifically for export purposes
	int animation_list_start_index = -1;
};

struct render_cmd_arg_obj
{
	int type;
	irr::core::array<irr::s32> int_arg;
	irr::core::array<irr::f64> double_arg;
	irr::core::array<irr::core::vector2di> i_vec_arg;
	irr::core::array<irr::core::vector2df> f_vec_arg;
	irr::core::array<irr::core::dimension2di> i_dim_arg;
	irr::core::array<irr::core::dimension2df> f_dim_arg;
};



struct render_cmd_obj
{
	int cmd;
	irr::core::array<render_cmd_arg_obj> arg;
};

struct Nirvana_TileSelection_Row
{
	std::vector<int> data;
};

struct Nirvana_TileSelection
{
	int width_in_tiles = 0;
	int height_in_tiles = 0;
	std::vector<Nirvana_TileSelection_Row> row;
};

struct Nirvana_SelectTool_TileSelection
{
	int tile_index = -1;
	irr::core::vector2di map_tile_pos;
	irr::core::vector2di box_start_pos;
	bool use_map2;
};

struct Nirvana_SelectTool_SpriteSelection
{
	int layer_sprite_index = -1;
	irr::core::vector2di start_pos;
	irr::core::vector2df start_scale;
	float angle;
};


struct Nirvana_SpriteBase
{
	std::vector<wxString> file;
	wxString sprite_name;

	sprite2D_obj object;

	int unique_id = -1;

	bool include_flag = false;
};


struct ts_cut
{
    int tileset_index;
    int start_tile;
    int num_cols;
    int num_rows;
    int cut_image_id;
};


struct Nirvana_Tileset
{
	wxString file;
	wxString tileset_name;

	tileset_obj object;

	std::vector<tilemask_obj> mask;

	std::vector<ts_cut> tileset_cut;
};

struct Nirvana_Map_Sprite
{
	std::string sprite_name;
	int map_sprite_id = -1;
	int layer_id = -1;
	int sprite_base = -1;
	int base_unique_id = -1;

	int layer_sprite_unique_id = -1;

	irr::core::vector2di position;
	irr::core::vector2df scale;
	float angle = 0;
	irr::u8 alpha = 255;
	bool visible = true;
	int body_type = SPRITE_TYPE_DYNAMIC;
	std::string animation_name = "SPRITE_BASE_ANIMATION";
};

struct Nirvana_Map_TileMap
{
	std::string nv_tileset_name;
	int nv_tileset_index = -1;
	int tile_map_index = -1;
	tilemap_obj tile_map;
	tilemap_obj tile_map2;
};

struct Nirvana_Map_Background
{
	int image_id = -1;
	std::string img_file;
	image_obj image;
	int render_setting = 0;
};

struct Nirvana_Map_CollisionShape
{
	int type = -1;
	std::string shape_name;
	irr::core::vector2di position;
	irr::core::array<irr::core::vector2di> points;
	float radius;

	irr::core::array<irr::core::vector2di> prev_points;
	irr::core::array<irr::core::vector2di> next_points;
};

struct tileSprite_obj
{
    int tset;
    int cut_index;
    int sheet_index;
    int x;
    int y;
    int width;
    int height;
    int image_id;
    int nv_sprite_id;
    int sprite_id;
};


struct Nirvana_Map_Layer
{
	std::string layer_name;
	int layer_type = -1;
	bool visible = true;
	Nirvana_Map_TileMap layer_map;
	std::vector<Nirvana_Map_Sprite> layer_sprites;
	std::vector<sprite2D_physics_obj> layer_shapes;
	int ts_tileset;  // NOTE: tileset for sprite layers
	std::vector<tileSprite_obj> layer_tile_sprites; // sprites created from tileset
	Nirvana_Map_Background bkg;
	irr::core::vector2df scroll_speed;
	int layer_alpha = 255;

	int spriteGrid_type = 0;
	int spriteSortBy = 0;
	int spriteSortOrder = 0;
	int spriteShapeDataSetting = 0;

	int ref_canvas = -1;
};

struct Nirvana_Stage
{
	int stage_id = -1;
	std::string stage_name;
	int tile_width = 0;
	int tile_height = 0;
	int width_in_tiles = 0;
	int height_in_tiles = 0;
	std::vector<int> layer_order;
	std::vector<Nirvana_Map_Layer> layers;
};

struct nirvana_project_dict_obj
{
	wxString key;
	wxString val;
};

struct nirvana_project_file_obj
{
	std::vector<nirvana_project_dict_obj> dict;
};



#define NIRVANA_ACTION_SETTILE              1
#define NIRVANA_ACTION_FILLTILE             2
#define NIRVANA_ACTION_COPYTILE             3
#define NIRVANA_ACTION_MOVETILE             4
#define NIRVANA_ACTION_DELETETILE           5

#define NIRVANA_ACTION_CREATE_TSPRITE       6
#define NIRVANA_ACTION_DELETE_TSPRITE       7
#define NIRVANA_ACTION_TRANSFORM_TSPRITE    8

#define NIRVANA_ACTION_CREATESPRITE         9
#define NIRVANA_ACTION_DELETESPRITE         10
#define NIRVANA_ACTION_COPYSPRITE           11
#define NIRVANA_ACTION_TRANSFORM_SPRITE     12

#define NIRVANA_ACTION_MOVESHAPE            13
#define NIRVANA_ACTION_DRAWPOINT            14
#define NIRVANA_ACTION_CREATESHAPE          15
#define NIRVANA_ACTION_DELETESHAPE          16

#define NIRVANA_ACTION_SETBKG               17

#define NIRVANA_ACTION_SETTILE_ISO          18
#define NIRVANA_ACTION_FILLTILE_ISO         19
#define NIRVANA_ACTION_MOVETILE_ISO         20
#define NIRVANA_ACTION_COPYTILE_ISO         21
#define NIRVANA_ACTION_DELETETILE_ISO       22


struct nirvana_stageAction_tile
{
    int iso_map;

    int old_tile;
    int new_tile;

    int map_tile_pos_x;
    int map_tile_pos_y;
};

struct nirvana_stageAction_shape
{
    sprite2D_physics_obj shape_obj;
};

struct nirvana_stageAction_sprite
{
    int sprite_id;

    int canvas_id;

    int image_id;

    int base_sprite_index;

    std::string id_name;

    int project_shape_index;

    int layer_ts_index;

    tileSprite_obj t_sprite;

    int old_pos_x;
    int old_pos_y;

    int pos_x;
    int pos_y;

    double old_angle;

    double angle;

    double old_scale_x;
    double old_scale_y;

    double scale_x;
    double scale_y;


	int base_unique_id = -1;

	int layer_sprite_unique_id = -1;

	irr::u8 alpha = 255;
	bool visible = true;
	int body_type = SPRITE_TYPE_DYNAMIC;
	std::string animation_name = "SPRITE_BASE_ANIMATION";

	nirvana_stageAction_shape old_shape;
	nirvana_stageAction_shape new_shape;
};

struct nirvana_stageAction_bkg
{
    Nirvana_Map_Background old_bkg;
    Nirvana_Map_Background new_bkg;
};

struct nirvana_stageAction
{
    int action_type;

    bool isUndo;

    int stage_index;
    int layer_index;

    int tset;

    int num_rows;
    int num_cols;

    std::vector<nirvana_stageAction_tile> tiles;

    std::vector<nirvana_stageAction_sprite> sprite;

    nirvana_stageAction_bkg bkg;
};

//bool current_action_is_undo = false;
//bool current_action_is_redo = false;

nirvana_stageAction current_action;

std::vector<nirvana_stageAction> undo_buffer;
std::vector<nirvana_stageAction> redo_buffer;

#define UNDO_REDO_BUFFER_SIZE   50

void push_undo(nirvana_stageAction n_action)
{
    if(undo_buffer.size() >= UNDO_REDO_BUFFER_SIZE)
    {
        std::vector<nirvana_stageAction> tmp_action;
        for(int i = 0; i < (undo_buffer.size()-1); i++)
        {
            tmp_action.push_back(undo_buffer[i+1]);
        }

        undo_buffer.clear();

        for(int i = 0; i < tmp_action.size(); i++)
        {
            undo_buffer.push_back(tmp_action[i]);
        }

        undo_buffer[undo_buffer.size()-1] = n_action;
    }
    else
    {
        undo_buffer.push_back(n_action);
    }

    current_action.action_type = -1;
    current_action.tiles.clear();
    current_action.sprite.clear();
}

nirvana_stageAction pop_undo()
{
    nirvana_stageAction n_action;

    if(undo_buffer.size() > 0)
    {
        n_action = undo_buffer[undo_buffer.size()-1];
        undo_buffer.erase(undo_buffer.begin() + undo_buffer.size()-1);
    }
    else
    {
        n_action.action_type = -1;
    }

    return n_action;
}

void clear_undo()
{
    undo_buffer.clear();
}


void push_redo(nirvana_stageAction n_action)
{
    if(redo_buffer.size() >= UNDO_REDO_BUFFER_SIZE)
    {
        std::vector<nirvana_stageAction> tmp_action;
        for(int i = 0; i < (redo_buffer.size()-1); i++)
        {
            tmp_action.push_back(redo_buffer[i+1]);
        }

        redo_buffer.clear();

        for(int i = 0; i < tmp_action.size(); i++)
        {
            redo_buffer.push_back(tmp_action[i]);
        }

        redo_buffer[redo_buffer.size()-1] = n_action;
    }
    else
    {
        redo_buffer.push_back(n_action);
    }

    current_action.action_type = -1;
    current_action.tiles.clear();
    current_action.sprite.clear();
}

nirvana_stageAction pop_redo()
{
    nirvana_stageAction n_action;

    if(redo_buffer.size() > 0)
    {
        n_action = redo_buffer[redo_buffer.size()-1];
        redo_buffer.erase(redo_buffer.begin() + redo_buffer.size()-1);
    }
    else
    {
        n_action.action_type = -1;
    }

    return n_action;
}

void clear_redo()
{
    redo_buffer.clear();
}


#endif // NIRVANAENGINE_STRUCTS_H_INCLUDED
