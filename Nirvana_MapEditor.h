#ifndef NIRVANA_MAPEDITOR_H_INCLUDED
#define NIRVANA_MAPEDITOR_H_INCLUDED

#include <wx/wx.h>
#include <wx/window.h>
#include "wxIrrlicht.h"
#include "Nirvana_Project.h"
#include "rc_defines.h"

class Nirvana_MapEditor
{
	private:
		wxWindow* parent;

		Nirvana_Project* project;

		int selected_stage = -1;
		int selected_layer = -1;
		int selected_sprite = -1;
		int selected_tile = -1;
		int selected_shape = -1;

		wxPanel* tileSelect_Sheet;
		wxPanel* map_surface;
		//wxPanel* spritePreview_surface;

		wxIrrlicht* map_target;
		wxIrrlicht* tileSelect_target;
		//wxIrrlicht* spritePreview_target;

		int ClientH(float pct) { return (int) (parent->GetClientSize().y * pct / 100); }
		int ClientW(float pct) { return (int) (parent->GetClientSize().x * pct / 100); }

		void initMapView();
		void initTileSelect();
		//void initSpritePreview();

		int editor_page_num = 0;

		int map_tool = -1;

	public:
		Nirvana_MapEditor(wxWindow* parent, wxPanel* map_panel, wxPanel* tile_panel);
		~Nirvana_MapEditor();

		void setProject(Nirvana_Project* p);

		wxIrrlicht* getMapViewControl();
		wxIrrlicht* getTileSelectControl();
		//wxIrrlicht* getSpritePreviewControl();

		void selectStage(int stage_index);
		void selectLayer(int layer_index);
		void selectShape(int shape_index);
		void selectSprite(int sprite_index);

		int getSelectedStage();
		int getSelectedLayer();
		int getSelectedShape();

		void stopEditor(bool stop_mapView = false);
		void startEditor(int n, bool start_mapView=false);
		int getEditorPageIndex();

		void setMapTool(int tool_id);
};


#endif // NIRVANA_MAPEDITOR_H_INCLUDED
