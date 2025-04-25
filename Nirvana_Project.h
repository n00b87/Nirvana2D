#ifndef NIRVANA_PROJECT_H_INCLUDED
#define NIRVANA_PROJECT_H_INCLUDED
#include <wx/wx.h>
#include <wx/filename.h>
#include <vector>

#include "wxIrrlicht.h"
#include "rc_defines.h"

class Nirvana_Project
{
	public:
		std::vector<Nirvana_Stage> stages;

		void createStage(std::string stage_name, int tile_width, int tile_height);
		void deleteStage(int stage_index);
		int copyStage(int stage_index);
		int getStageCount();
		int getStageIndex(std::string stage_name);
		std::string getStageName(int stage_index);
		void setStageName(int stage_index, std::string stage_name);
		void setStageSize(int stage_index, int width, int height);
		irr::core::vector2di getStageSize(int stage_index);
		irr::core::vector2di getStageTileSize(int stage_index);

		void addLayer(int stage_index, std::string layer_name, int layer_type);
		int getStageNumLayers(int stage_index);
		int getLayerIndex(int stage_index, std::string layer_name);
		int getLayerType(int stage_index, int layer_index);
		void setLayerName(int stage_index, int layer_index, std::string layer_name);
		std::string getLayerName(int stage_index, int layer_index);
		void setLayerScrollSpeed(int stage_index, int layer_index, float h_scroll, float v_scroll);
		irr::core::vector2df getLayerScrollSpeed(int stage_index, int layer_index);
		void setLayerAlpha(int stage_index, int layer_index, int alpha);
		int getLayerAlpha(int stage_index, int layer_index);
		void setLayerVisible(int stage_index, int layer_index, bool visible_flag);
		bool getLayerVisible(int stage_index, int layer_index);
		void setLayerTileset(int stage_index, int layer_index, int tileset_index);
		int getLayerTileset(int stage_index, int layer_index);
		void setLayerTile(int stage_index, int layer_index, int x_in_tiles, int y_in_tiles, int tile_index);
		int getLayerTile(int stage_index, int layer_index, int x_in_tiles, int y_in_tiles);
		int addLayerSprite(int stage_index, int layer_index, std::string sprite_name, int sprite_base_index, int x, int y);
		int getLayerSpriteIndex(int stage_index, int layer_index, std::string sprite_name);
		int getLayerSpriteBaseIndex(int stage_index, int layer_index, int sprite_index);
		void setLayerSpritePosition(int stage_index, int layer_index, int sprite_index, int x, int y);
		irr::core::vector2di getLayerSpritePosition(int stage_index, int layer_index, int sprite_index);
		void setLayerSpriteRotation(int stage_index, int layer_index, int sprite_index, float angle);
		float getLayerSpriteRotation(int stage_index, int layer_index, int sprite_index);
		void setLayerSpriteScale(int stage_index, int layer_index, int sprite_index, float scale_x, float scale_y);
		irr::core::vector2df getLayerSpriteScale(int stage_index, int layer_index, int sprite_index);
		int getStageLayerNumSprites(int stage_index, int layer_index);
		Nirvana_Map_Layer getStageLayer(int stage_index, int layer_index);
		void setLayerOrder(int stage_index, int layer_index, int new_layer_index);
		void deleteLayer(int stage_index, int layer_index);
		int copyLayer(int stage_index, int layer_index);

		wxFileName project_filename_obj;

		wxIrrlicht* tileSheet_target;
		wxIrrlicht* tileFrame_target;
		wxIrrlicht* tilePreview_target;
		wxIrrlicht* tileMask_target;

		wxIrrlicht* spriteCollision_target;

		wxIrrlicht* spriteSheet_target;
		wxIrrlicht* spriteFrame_target;
		wxIrrlicht* spritePreview_target;

		std::vector<Nirvana_SpriteBase> sprite_base;
		std::vector<Nirvana_Tileset> tileset;


		Nirvana_Project();

		wxString getDir();
		wxString getFileName();

		bool isValidName(wxString test_name);

		bool createSprite(wxString spr_id, wxString img_file, int frame_width, int frame_height);
		void setSpriteObject(int spr_index, sprite2D_obj obj);
		void setSpritePhysics(int spr_index, sprite2D_physics_obj obj);
		sprite2D_physics_obj getSpritePhysics(int spr_index);
		void setSpriteName(int  spr_index, std::string spr_name);
		void setSpriteAnimationName(int spr_index, int animation_index, std::string ani_name);
		void deleteSprite(int spr_index);

		void setSpriteNumAnimationFrames(int spr_index, int animation_index, int num_frames);
		void setSpriteAnimationFrame(int spr_index, int animation_index, int ani_frame, int sheet_frame);
		void setSpriteAnimationFPS(int spr_index, int animation_index, int fps);

		int getSpriteNumAnimations(int spr_index);
		int getSpriteNumAnimationFrames(int spr_index, int animation_index);
		int getSpriteAnimationFrame(int spr_index, int animation_index, int ani_frame);
		int getSpriteAnimationFPS(int spr_index, int animation_index);

		void setSpriteCollision_Shape(int spr_index, int shape);
		int getSpriteCollision_Shape(int spr_index);

		void setSpriteCollision_OffsetX(int spr_index, int x);
		int getSpriteCollision_OffsetX(int spr_index);

		void setSpriteCollision_OffsetY(int spr_index, int y);
		int getSpriteCollision_OffsetY(int spr_index);

		void setSpriteCollisionBox_Width(int spr_index, int width);
		int getSpriteCollisionBox_Width(int spr_index);

		void setSpriteCollisionBox_Height(int spr_index, int height);
		int getSpriteCollisionBox_Height(int spr_index);

		void setSpriteCollisionCircle_Radius(int spr_index, float radius);
		float getSpriteCollisionCircle_Radius(int spr_index);

		Nirvana_SpriteBase getSprite(int spr_index);
		int getSpriteCount();

		//--------TILESETS------------
		bool createTileset(wxString tset_id, wxString img_file, int tile_width, int tile_height);
		void setTilesetObject(int tileset_index, tileset_obj obj);
		void setTilesetName(int  tileset_index, std::string tileset_name);
		std::string getTilesetName(int tileset_index);
		int getTilesetIndex(std::string tileset_name);
		irr::core::vector2di getTilesetTileSize(int tileset_index);
		void deleteTileset(int tileset_index);

		void setTileNumAnimationFrames(int tileset_index, int base_tile_index, int num_frames);
		void setTileAnimationFrame(int tileset_index, int base_tile_index, int ani_frame, int sheet_frame);
		void setTileAnimationFPS(int tileset_index, int base_tile_index, int fps);

		int getTileNumAnimationFrames(int tileset_index, int base_tile_index);
		int getTileAnimationFrame(int tileset_index, int base_tile_index, int ani_frame);
		int getTileAnimationFPS(int tileset_index, int base_tile_index);

		Nirvana_Tileset getTileset(int tileset_index);
		int getTilesetCount();
		int getTilesetNumTiles(int tileset_index);

		//--------MASK------------
		int createMask(int tileset_index, std::string mask_name);
		void deleteMask(int tileset_index, int mask_index);
		int getMaskCount(int tileset_index);
		void setMaskName(int tileset_index, int mask_index, std::string mask_name);
		std::string getMaskName(int tileset_index, int mask_index);
		int getMaskIndex(int tileset_index, std::string mask_name);
		void setTileMask(int tileset_index, int mask_index, int tile_index, bool flag);
		bool getTileMask(int tileset_index, int mask_index, int tile_index);
		void clearTileMask(int tileset_index, int mask_index);
};

#endif // NIRVANA_PROJECT_H_INCLUDED
