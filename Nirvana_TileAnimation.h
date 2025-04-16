#ifndef NIRVANA_TILEANIMATION_H_INCLUDED
#define NIRVANA_TILEANIMATION_H_INCLUDED

#include <wx/wx.h>
#include <wx/window.h>
#include "wxIrrlicht.h"
#include "Nirvana_Project.h"
#include "rc_defines.h"

class Nirvana_TileEditor
{
	private:
		wxWindow* parent;

		Nirvana_Project* project;

		int selected_tileset = -1;
		int selected_tile = -1;

		wxPanel* animation_tileSheet;
		wxPanel* animation_tileFrames;
		wxPanel* animation_preview;
		wxPanel* mask_surface;

		wxIrrlicht* tileSheet_target;
		wxIrrlicht* tileFrame_target;
		wxIrrlicht* tilePreview_target;
		wxIrrlicht* tileMask_target;

		int ClientH(float pct) { return (int) (parent->GetClientSize().y * pct / 100); }
		int ClientW(float pct) { return (int) (parent->GetClientSize().x * pct / 100); }

		void initAnimationSheet();
		void initAnimationFrame();
		void initAnimationPreview();

	public:
		Nirvana_TileEditor(wxWindow* parent, wxPanel* ani_sheet_panel, wxPanel* ani_frame_panel, wxPanel* ani_preview_panel, wxPanel* mask_sheet_panel);
		~Nirvana_TileEditor();

		void setProject(Nirvana_Project* p);

		wxIrrlicht* getAnimationSheetControl();
		wxIrrlicht* getAnimationFrameControl();
		wxIrrlicht* getAnimationPreviewControl();

		void stopEditor();
		void startEditor();

		void setAnimationView();

		void selectTileset(wxString tset_id);
		void selectTile(wxString tile_id);

		int getSelectedTileset();
		int getSelectedTile();
};

#endif // NIRVANA_TILEANIMATION_H_INCLUDED
