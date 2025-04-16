#ifndef NIRVANA_SPRITEANIMATION_H_INCLUDED
#define NIRVANA_SPRITEANIMATION_H_INCLUDED

#include <wx/wx.h>
#include <wx/window.h>
#include "wxIrrlicht.h"
#include "Nirvana_Project.h"
#include "rc_defines.h"

/*
class spriteSheet_obj : wxIrrlicht
{
	spriteSheet_obj(wxWindow* parent, wxWindowID id, bool bs=true, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxPanelNameStr);
	~spriteSheet_obj();
};

class spriteFrame_obj : wxIrrlicht
{
	spriteFrame_obj(wxWindow* parent, wxWindowID id, bool bs=true, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxPanelNameStr);
	~spriteFrame_obj();
};

class spritePreview_obj : wxIrrlicht
{
	spritePreview_obj(wxWindow* parent, wxWindowID id, bool bs=true, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxPanelNameStr);
	~spritePreview_obj();
};

class spriteCollision_obj : wxIrrlicht
{
	spriteCollision_obj(wxWindow* parent, wxWindowID id, bool bs=true, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxPanelNameStr);
	~spriteCollision_obj();
};
*/

class Nirvana_SpriteEditor
{
	private:
		wxWindow* parent;

		Nirvana_Project* project;

		int selected_sprite = -1;
		int selected_animation = -1;

		wxPanel* animation_spriteSheet;
		wxPanel* animation_spriteFrames;
		wxPanel* animation_preview;
		wxPanel* collision_surface;

		wxIrrlicht* spriteSheet_target;
		wxIrrlicht* spriteFrame_target;
		wxIrrlicht* spritePreview_target;
		wxIrrlicht* spriteCollision_target;

		int ClientH(float pct) { return (int) (parent->GetClientSize().y * pct / 100); }
		int ClientW(float pct) { return (int) (parent->GetClientSize().x * pct / 100); }

		void initAnimationSheet();
		void initAnimationFrame();
		void initAnimationPreview();
		void initCollision();

		int editor_page_num = 0;

	public:
		Nirvana_SpriteEditor(wxWindow* parent, wxPanel* ani_sheet_panel, wxPanel* ani_frame_panel, wxPanel* ani_preview_panel, wxPanel* col_sheet_panel);
		~Nirvana_SpriteEditor();

		void setProject(Nirvana_Project* p);

		wxIrrlicht* getAnimationSheetControl();
		wxIrrlicht* getAnimationFrameControl();
		wxIrrlicht* getAnimationPreviewControl();
		wxIrrlicht* getCollisionControl();

		void stopEditor();
		void startEditor(int n);
		int getEditorPageIndex();

		void setAnimationView();

		int newAnimation();
		void deleteAnimation();

		void selectSprite(wxString spr_id);
		void selectAnimation(wxString animation_id);

		void updateSpriteAnimation();

		int getSelectedSprite();
		int getSelectedAnimation();
};

#endif // NIRVANA_SPRITEANIMATION_H_INCLUDED
