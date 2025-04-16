#ifndef NIRVANA_PROJECT_H_INCLUDED
#define NIRVANA_PROJECT_H_INCLUDED
#include <wx/wx.h>
#include <wx/filename.h>
#include <vector>

#include "wxIrrlicht.h"
#include "rc_defines.h"

struct Nirvana_SpriteBase
{
	wxString file;
	wxString sprite_name;

	sprite2D_obj object;
};

class Nirvana_Project
{
	private:
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

	public:
		Nirvana_Project();

		wxString getDir();
		wxString getFileName();

		bool createSprite(wxString spr_id, wxString img_file, int frame_width, int frame_height);
		void setSpriteObject(int spr_index, sprite2D_obj obj);
		void setSpritePhysics(int spr_index, sprite2D_physics_obj obj);
		sprite2D_physics_obj getSpritePhysics(int spr_index);
		void setSpriteName(int  spr_index, std::string spr_name);
		void setSpriteAnimationName(int spr_index, int animation_index, std::string ani_name);

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

		Nirvana_SpriteBase getSprite(int spr_index);
		int getSpriteCount();
};

#endif // NIRVANA_PROJECT_H_INCLUDED
