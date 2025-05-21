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

	int img_id;

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

	int tileset;
	irr::video::ITexture* texture;

	int num_tiles_across;
	int num_tiles_down;

	std::vector<tilemap_row_obj> rows;
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
	int sheet_numFrames;
	int frames_per_row;

	int layer_sprite_index = -1;
	int layer_sprite_unique_id = -1;

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
	wxString file;
	wxString sprite_name;

	sprite2D_obj object;

	int unique_id = -1;

	bool include_flag = false;
};

struct Nirvana_Tileset
{
	wxString file;
	wxString tileset_name;

	tileset_obj object;

	std::vector<tilemask_obj> mask;
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

struct Nirvana_Map_Layer
{
	std::string layer_name;
	int layer_type = -1;
	bool visible = true;
	Nirvana_Map_TileMap layer_map;
	std::vector<Nirvana_Map_Sprite> layer_sprites;
	std::vector<sprite2D_physics_obj> layer_shapes;
	Nirvana_Map_Background bkg;
	irr::core::vector2df scroll_speed;
	int layer_alpha = 255;

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

#endif // NIRVANAENGINE_STRUCTS_H_INCLUDED
