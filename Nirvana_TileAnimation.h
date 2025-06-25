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
		int selected_mask = -1;

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
		void initMaskSheet();

		int editor_page_num = 0;

	public:
		Nirvana_TileEditor(wxWindow* parent, wxPanel* ani_sheet_panel, wxPanel* ani_frame_panel, wxPanel* ani_preview_panel, wxPanel* mask_sheet_panel);
		~Nirvana_TileEditor();

		void setProject(Nirvana_Project* p);

		wxIrrlicht* getAnimationSheetControl();
		wxIrrlicht* getAnimationFrameControl();
		wxIrrlicht* getAnimationPreviewControl();
		wxIrrlicht* getMaskSheetControl();

		void stopEditor();
		void startEditor(int n);
		int getEditorPageIndex();

		void setAnimationView();

		void selectTileset(wxString tset_id);
		void selectTile(int tile_index);

		int getSelectedTileset();
		int getSelectedTile();

		void updateTileAnimation();

		void playPreview();
		void stopPreview();

		void selectMask(wxString mask_name);
		int getSelectedMask();
};

#endif // NIRVANA_TILEANIMATION_H_INCLUDED
