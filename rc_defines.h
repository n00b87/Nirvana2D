#ifndef RC_DEFINES_H_INCLUDED
#define RC_DEFINES_H_INCLUDED

#define RC_MOUSEBUTTON_NONE   0
#define RC_MOUSEBUTTON_LEFT   1
#define RC_MOUSEBUTTON_RIGHT  2
#define RC_MOUSEBUTTON_MIDDLE 3

#if defined(__WXGTK__)
	#define HIDE_CURSOR wxSetCursor(wxCURSOR_BLANK)
	#define SHOW_CURSOR wxSetCursor(*wxSTANDARD_CURSOR)
#elif defined(__WXMSW__)
	#define HIDE_CURSOR ShowCursor(0)
	#define SHOW_CURSOR ShowCursor(1)
#endif

#define NIRVANA_VERSION_STRING "1.0"

#define NIRVANA_MAIN_PAGE_INDEX_MAP		0
#define NIRVANA_MAIN_PAGE_INDEX_TILE	1
#define NIRVANA_MAIN_PAGE_INDEX_SPRITE	2

#define CANVAS_TYPE_2D		0
#define CANVAS_TYPE_3D		1
#define CANVAS_TYPE_SPRITE	2
#define CANVAS_TYPE_TILEMAP	3	//This canvas type is only for Nirvana

#define SPRITE_SHAPE_BOX		1
#define SPRITE_SHAPE_POLYGON	2
#define SPRITE_SHAPE_CIRCLE		3
#define SPRITE_SHAPE_CHAIN	4

#define COLLISION_TOOL_SELECT		0
#define COLLISION_TOOL_BOX_SELECT	1
#define COLLISION_TOOL_MOVE			2
#define COLLISION_TOOL_DRAW			3

#define NV_SPRITE_EDIT_ANIMATION_SHEET		1
#define NV_SPRITE_EDIT_ANIMATION_FRAME		2
#define NV_SPRITE_EDIT_ANIMATION_PREVIEW	3
#define NV_SPRITE_EDIT_COLLISION_SHEET		4
#define NV_TILE_EDIT_ANIMATION_SHEET		5
#define NV_TILE_EDIT_ANIMATION_FRAME		6
#define NV_TILE_EDIT_ANIMATION_PREVIEW		7
#define NV_TILE_EDIT_MASK_SHEET				8
#define NV_MAP_EDIT_MAP_SHEET				9
#define NV_MAP_EDIT_TILE_SHEET				10
#define NV_MAP_EDIT_SPRITE_PREVIEW			11

#define TILE_EDIT_ANIMATION_MODE_SELECT		0
#define TILE_EDIT_ANIMATION_MODE_ANIMATE	1

#define LAYER_TYPE_TILEMAP		0
#define LAYER_TYPE_SPRITE		1
#define LAYER_TYPE_CANVAS_2D	2
#define LAYER_TYPE_CANVAS_3D	3

#define MAP_TOOL_TILE_SELECT		0
#define MAP_TOOL_TILE_BOXSELECT		1
#define MAP_TOOL_TILE_MOVE			2
#define MAP_TOOL_TILE_SET			3
#define MAP_TOOL_TILE_COPY			4
#define MAP_TOOL_TILE_FILL			5
#define MAP_TOOL_TILE_DELETE		6
#define MAP_TOOL_SPRITE_SELECT		7
#define MAP_TOOL_SPRITE_BOXSELECT	8
#define MAP_TOOL_SPRITE_MOVE		9
#define MAP_TOOL_SPRITE_ROTATE		10
#define MAP_TOOL_SPRITE_SCALE		11
#define MAP_TOOL_SPRITE_COPY		12
#define MAP_TOOL_SHAPE_SELECT		13
#define MAP_TOOL_SHAPE_BOXSELECT	14
#define MAP_TOOL_SHAPE_MOVE			15
#define MAP_TOOL_SHAPE_DRAW			16


#define SPRITE_TYPE_STATIC		0
#define SPRITE_TYPE_KINEMATIC	1
#define SPRITE_TYPE_DYNAMIC		2

#define IMG_RENDER_SETTING_NORMAL		0
#define IMG_RENDER_SETTING_STRETCHED	1
#define IMG_RENDER_SETTING_TILED		2


#endif // RC_DEFINES_H_INCLUDED
