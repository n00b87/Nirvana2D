/* wxirrlicht.h -- A wxWidgets control that embeds the 'Irrlicht Engine'.

  Copyright (C) 2006 Yiannis Mandravellos <mandrav@codeblocks.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  ChangeLog
  ---------
    2 Sep 2006:
      * Original version released.
*/

/*
  2007/12/12
  	* changed version by loptr (devy@sourceforge.net)
*/

/*
  6 Jan 2024
  * n00b Edition - Updated to support GTK3 on linux
*/

#ifndef __LOPTRIRR_H__
#define __LOPTRIRR_H__

#ifdef _WIN32
#include <windows.h>
#endif //WINDOWS

#include <irrlicht.h>
#include <wx/wx.h>
#include <wx/propgrid/property.h>
#include <wx/spinctrl.h>
#include <wx/grid.h>
#include <wx/glcanvas.h>
#include "gui_freetype_font.h"
#include "NirvanaEngine_Structs.h"
#include "rc_defines.h"
#include "Nirvana_Project.h"

#define MAX_FONTS 8


struct font_obj
{
    CGUITTFace* face;
    CGUIFreetypeFont* font;
    int font_size;
    bool active = false;
};


class wxIrrlicht : public wxControl {
	public:
		wxIrrlicht(wxWindow* parent, wxWindowID id, bool bs=true, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxPanelNameStr);
		~wxIrrlicht();

        void InitIrr(irr::SIrrlichtCreationParameters* init_params = 0);
        //void InitIrr(irr::IrrlichtDevice* device);

        void StartRendering(int milliseconds = 10);
        void StopRendering();
        void Render();
        virtual void OnCreateScene();
        virtual void OnPreRender() {}
        virtual void OnRender();
        virtual void OnPostRender();

        void force_refresh();
        void setDefaultMaterial(irr::scene::ISceneNode* node, irr::video::ITexture* texture);

        irr::IrrlichtDevice* GetDevice() const { return m_pDevice; }
        irr::video::IVideoDriver* GetVideoDriver() const { return m_pDriver; }
        irr::scene::ISceneManager* GetSceneManager() const { return m_pSceneManager; }
        irr::scene::ICameraSceneNode* GetCameraNode() const { return m_pCameraNode; }
        irr::gui::IGUIEnvironment* GetGuiEnvironment() const { return m_pGuiEnvironment; }

        wxWindow* parent_window;

        font_obj font[MAX_FONTS];
        int active_font = -1;
        int ui_layer = -1;
        int grid_layer = -1;

        int ui_font1 = -1;
        int ui_font2 = -1;

        int stage_edit_tool = -1;

        bool show_grid = false;
        irr::video::SColor grid_color;

        void util_drawGrid();

        bool debug_flag = true;
        wxString debug_string = _("");

        int irr_LoadFont(std::string font_file, int font_size);
        void irr_DrawText(std::string txt, int x, int y, irr::video::SColor color, int camera_index);
        void irr_DeleteFont(int font_id);
        void irr_SetFont(int font_id);

        void rc_setDriverMaterial();

        irr::core::matrix4 ortho_matrix;
        irr::core::matrix4 perspective_matrix;

        int back_buffer = -1;


        irr::core::array<canvas_obj> canvas;
        irr::core::array<irr::u32> canvas_zOrder;
		int active_canvas = -1;

		irr::video::SColor active_color;
		irr::video::SColor clear_color;

		irr::core::array<image_obj> image;
		bool test_init = true;

		irr::video::E_BLEND_OPERATION blend_mode = irr::video::EBO_NONE;
		bool bilinear_filter = false;
		irr::video::E_ANTI_ALIASING_MODE anti_alias = irr::video::EAAM_OFF;

        // Canvases
        void sortCanvasZ();
        int createCanvas(int w, int h, int vx, int vy, int vw, int vh, int canvas_type=CANVAS_TYPE_2D);
        void canvasClose(int canvas_id);
        void setActiveCanvas(int canvas_id);
        void clearCanvas();
        void setCanvasVisible(int canvas_id, bool flag);
        bool canvasIsVisible(int canvas_id);
		void setCanvasViewport(int canvas_id, int x, int y, int w, int h);
		void getCanvasViewport(int canvas_id, double* x, double* y, double* w, double* h);
		void setCanvasOffset(int canvas_id, int x, int y);
		void getCanvasOffset(int canvas_id, double* x, double* y);
		void getCanvasSize(int canvas_id, double* w, double* h);
		void setCanvasColorMod(int canvas_id, irr::u32 color_mod);
		irr::u32 getCanvasColorMod(int canvas_id);
		void setCanvasAlpha(int canvas_id, irr::u32 alpha);
		irr::u32 canvasAlpha(int canvas_id);
		void setCanvasZ(int canvas_id, int z);
		int getCanvasZ(int canvas_id);


		//Colors
		void setClearColor(irr::u32 color);
		irr::u32 rgba(irr::u32 r, irr::u32, irr::u32 b, irr::u32 a);
		irr::u32 rgb(irr::u32 r, irr::u32 g, irr::u32 b);
		void setColor(irr::u32 color);

		// Primitives
		double radians(double degree);
		void drawRect(int x, int y, int w, int h);
		void drawRectFill(int x, int y, int w, int h);
		void drawLine(int x1, int y1, int x2, int y2);
		void drawLine_opt(int x1, int y1, int x2, int y2);
		void drawPixel(int x, int y);
		void makeEllipse(irr::core::array<irr::video::S3DVertex>& vertices, irr::core::array<irr::u16>& indices, const CircleSettings& settings);
		void drawEllipse(int x, int y, int rx, int ry);
		void drawEllipseFill(int x, int y, int rx, int ry);
		void drawCircle(int x, int y, double r);
		void drawCircleFill(int x, int y, double r);

		// Images
		void util_draw2DImage(irr::video::IVideoDriver *driver, irr::video::ITexture* texture, irr::core::rect<irr::s32> sourceRect, irr::core::position2d<irr::s32> position, irr::core::position2d<irr::s32> rotationPoint, irr::f32 rotation, irr::core::vector2df scale, bool useAlphaChannel, irr::video::SColor color, irr::core::vector2d<irr::f32> screenSize);
		void util_draw2DImage2(irr::video::IVideoDriver *driver, irr::video::ITexture* texture, irr::core::rect<irr::s32> sourceRect, irr::core::rect<irr::s32> destRect, irr::core::position2d<irr::s32> rotationPoint, irr::f32 rotation, bool useAlphaChannel, irr::video::SColor color, irr::core::vector2d<irr::f32> screenSize );

		int loadImageEx(std::string img_file, irr::u32 color_key = 0, bool use_color_key = true);
		int loadImage(std::string img_file);
		void deleteImage(int img_id);

		void drawImage(int img_id, int x, int y);
		void drawImage_Rotate(int img_id, int x, int y, double angle);
		void drawImage_Zoom(int img_id, int x, int y, double zx, double zy);
		void drawImage_ZoomEx(int img_id, int x, int y, int src_x, int src_y, int src_w, int src_h, double zx, double zy);
		void drawImage_Rotozoom(int img_id, int x, int y, double angle, double zx, double zy);
		void drawImage_RotozoomEx(int img_id, int x, int y, int src_x, int src_y, int src_w, int src_h, double angle, double zx, double zy);
		void drawImage_Flip(int img_id, int x, int y, bool h, bool v);
		void drawImage_FlipEx(int img_id, int x, int y, int src_x, int src_y, int src_w, int src_h, bool h, bool v);
		void drawImage_Blit(int img_id, int x, int y, int src_x, int src_y, int src_w, int src_h);
		void drawImage_RotateEx(int img_id, int x, int y, int src_x, int src_y, int src_w, int src_h, int angle);
		void drawImage_BlitEx(int img_id, int x, int y, int w, int h, int src_x, int src_y, int src_w, int src_h);
		void drawImage_BlitEx_SW(int img_id, int x, int y, int w, int h, int src_x, int src_y, int src_w, int src_h);
		void setImageAlpha(int img_id, irr::u8 alpha);
		irr::u32 getImageAlpha(int img_id);
		bool imageExists(int img_id);
		void getImageSize(int img_id, double* w, double* h);
		void getImageSizeI(int img_id, int* w, int* h);
		void setColorKey(int img_id, irr::u32 colorkey);
		void getImageBuffer(int img_id, irr::u32 * pdata);

		// SPRITES
		irr::core::array<sprite2D_obj> sprite;

		int createSpriteAnimation(std::string name, int spr_id, int anim_length, double fps);
		void deleteSpriteAnimation(int spr_id, int animation);
		void setSpriteFrame(int spr_id, int frame);
		int getSpriteFrame(int spr_id);
		void setSpriteAnimationFrame(int spr_id, int spr_animation, int anim_frame, int frame);
		int getSpriteAnimationFrame(int spr_id, int spr_animation, int anim_frame);
		void setSpriteAnimationLength(int spr_id, int animation, int num_frames);
		int getSpriteAnimationLength(int spr_id, int animation);
		void setSpriteAnimationSpeed(int spr_id, int animation, double fps);
		double getSpriteAnimationSpeed(int spr_id, int animation);
		void setSpriteAnimation(int spr_id, int animation, int num_loops);
		int getSpriteAnimation(int spr_id);
		int getSpriteCurrentAnimationFrame(int spr_id);
		void setSpriteAnimationLoops(int spr_id, int num_loops);
		int numSpriteAnimationLoops(int spr_id);
		bool spriteAnimationIsPlaying(int spr_id);

		void sortSpriteZ(int canvas_id);
		bool spriteExists(int spr_id);
		int createSprite(int layer_sprite_index, int img_id, double w, double h);
		void deleteSprite(int spr_id);
		int getSpriteSource(int spr_id);
		void setSpriteCollisionShape(int spr_id, int sprite_shape);
		int getSpriteCollisionShape(int spr_id);
		void setSpriteRadius(int spr_id, double radius);
		double getSpriteRadius(int spr_id);
		void setSpriteBox(int spr_id, int w, int h);
		void getSpriteBoxSize(int spr_id, int* w, int* h);
		void setSpriteChain(int spr_id, irr::core::array<irr::core::vector2di> vert, irr::core::array<irr::core::vector2di> prev_vert, irr::core::array<irr::core::vector2di> next_vert);
		void setSpriteChainLoop(int spr_id, irr::core::array<irr::core::vector2di> vert);
		void setSpritePolygon(int spr_id, irr::core::array<irr::core::vector2di> vert);
		void setSpriteType(int spr_id, int body_type);
		int getSpriteType(int spr_id);
		void setSpriteSolid(int spr_id, bool flag);
		bool spriteIsSolid(int spr_id);
		void setSpritePosition(int spr_id, int x, int y);
		irr::core::vector2di getSpritePosition(int spr_id);
		void setSpriteRotation(int spr_id, double angle);
		double getSpriteRotation(int spr_id);
		void setSpriteScale(int spr_id, double x, double y);
		irr::core::vector2df getSpriteScale(int spr_id);
		int spriteWidth(int spr_id);
		int spriteHeight(int spr_id);
		irr::core::dimension2di getSpriteSize(int spr_id);
		void setSpriteZ(int spr_id, double z);
		double spriteZ(int spr_id);
		void setSpriteVisible(int spr_id, bool flag);
		bool spriteIsVisible(int spr_id);
		void setSpriteColorMod(int spr_id, irr::u32 color);
		void setSpriteAlpha(int spr_id, irr::u8 alpha);
		irr::u32 getSpriteColorMod(int spr_id);
		irr::u32 getSpriteAlpha(int spr_id);
		void util_drawSprites(int canvas_id);
		void util_drawSelectedSprites();
		void util_drawShapes(int layer_index);


		// TILES
		std::vector<tileset_obj> tileset;
		std::vector<tilemap_obj> tilemap;

		std::vector<int> deleted_tileset;
		std::vector<int> deleted_tilemap;

		int createTileSet(int img_id, int tile_w, int tile_h);
		void deleteTileSet(int tset);
		void setTileAnimationLength(int tset, int base_tile, int num_frames);
		int getTileAnimationLength(int tset, int base_tile);
		void setTileAnimationFrame(int tset, int base_tile, int anim_frame, int tile_frame);
		int getTileAnimationFrame(int tset, int base_tile, int anim_frame);
		void setTileAnimationSpeed(int tset, int base_tile, double speed);
		double getTileAnimationSpeed(int tset, int base_tile);

		//--------------------------------------TILEMAP-----------------------------------------------
		int createTileMap(int tset, int widthInTiles, int heightInTiles);
		void deleteTileMap(int tmap);
		bool tilesetExists(int tset);
		void setTileMapSize(int tmap, int widthInTiles, int heightInTiles);
		void getTileMapSize(int tmap, double* widthInTiles, double* heightInTiles);
		void setTile(int tmap, int tile, int x, int y);
		int getTile(int tmap, int x, int y);
		void fillTile(int tmap, int tile, int x, int y, int widthInTiles, int heightInTiles);
		void getTileInTileset(int tset, int tile, int* x, int* y);
		int getNumTilesInTileset(int tset);
		void updateTileset(int tset);
		void drawTileMap(int tmap, int x, int y, int w, int h, int offset_x, int offset_y);

		void util_getTileInTileset(int project_tset, int tile, int* x, int* y);
		int util_getNumTilesInTileset(int project_tset);
		void util_updateTileset(int project_tset);
		void util_drawTileLayer(int layer);
		void util_setSpriteLayerOffset(int layer);

		int util_getImageID(std::string img_file); //checks to see if file has already been loaded

		void initStage(int stage_index);
		void initLayer(int layer_index);
		void addLayerSprite(int layer_index, int project_sprite);
		void resizeLayers();

		void clearStage();


        irr::video::ITexture* test_texture;


        int window_type = 0;
        irr::video::ITexture* view2D_texture;

        bool stage_window_isActive = false;

	//protected:
        void OnPaint(wxPaintEvent& event);
        void OnSize(wxSizeEvent& event);
        void OnParentSize(wxSizeEvent& event);
        void OnEraseBackground(wxEraseEvent& event) {}
        void OnTimer(wxTimerEvent& event);
        void OnMouse(wxMouseEvent& event);
        void OnKey(wxKeyEvent& event);


        bool enable_update = true;
        void OnUpdate();

        bool tst_tset_render = true;

        int control_id = -1;

        int map_tool = -1;

        int current_frame_width = 32;
        int current_frame_height = 32;

        int sheet_width = 0;
        int sheet_height = 0;

        int current_sheet_image = -1;
        int selected_frame = -1; //Used for sheet and frame

        int scroll_offset_x = 0;
        int scroll_offset_y = 0;
        int scroll_speed = 2;

        int sheet_canvas = -1;
        int overlay_canvas = -1;
        int frame_canvas = -1;
        int preview_canvas = -1;
        int collision_canvas = -1;
        sprite2D_physics_obj collision_physics_obj;

        bool clear_flag = false;

        bool tile_snap = false;

        //Collision Stuff
        int collision_tool = -1;
        bool collision_object_modified = false;
        bool collision_boxShapeSelect_ul = false;
        bool collision_boxShapeSelect_ll = false;
        bool collision_boxShapeSelect_ur = false;
        bool collision_boxShapeSelect_lr = false;
        irr::core::vector2di collision_move_start_offset;
        irr::core::vector2di collision_move_start_size;
        int collision_move_start_radius = 0;

        bool collision_circleShapeSelect_center = false;
        bool collision_circleShapeSelect_u = false;
        bool collision_circleShapeSelect_d = false;
        bool collision_circleShapeSelect_l = false;
        bool collision_circleShapeSelect_r = false;

		bool collision_poly_draw_flag = false;
        irr::core::array<int> collision_selected_points; //index in the points of the collision object
        irr::core::array<irr::core::vector2di> collision_move_start_points;

        void collisionEdit_select();
        void collisionEdit_boxSelect();
        void collisionEdit_move();
        void collisionEdit_draw();

        bool collisionPointIsSelected(int pt_index);

        int spriteEdit_selected_sprite = -1;
        int spriteEdit_selected_animation = -1;
        int spriteEdit_selected_sheet_frame = -1;
        int spriteEdit_selected_frame_frame = -1;

        bool update_events = false;

        void UpdateSpriteAnimationSheet();
        void UpdateSpriteAnimationFrame();
        void UpdateSpriteAnimationPreview();
        void UpdateSpriteCollision();


        int tileEdit_selected_tileset = -1;
        int tileEdit_selected_tile = -1;
        int tileEdit_selected_sheet_frame = -1;
        int tileEdit_selected_frame_frame = -1;
        bool tileEdit_mask_set = false;

        bool tileEdit_Sheet_Update = false;
        int tileEdit_animationMode = 0;

        int tileEdit_preview_tilemap = -1;
        bool tileEdit_play_preview = false;

        tilemask_obj tileEdit_tileMask;

        void UpdateTileAnimationSheet();
        void UpdateTileAnimationFrame();
        void UpdateTileAnimationPreview();
        void UpdateTileMask();

        Nirvana_Project* project = NULL;
        int selected_stage = -1;
        int selected_layer = -1;
        int selected_sprite = -1;
        int selected_tile = -1;
        int selected_tile_end = -1;
        Nirvana_TileSelection mapEdit_tile_selection;
        std::vector<Nirvana_SelectTool_TileSelection> mapEdit_selectTileTool_selection;
        std::vector<Nirvana_SelectTool_TileSelection> mapEdit_selectTileTool_box;
        std::vector<Nirvana_SelectTool_SpriteSelection> mapEdit_selectSpriteTool_selection;

        int mapEdit_layerType = -1;

        bool mapEdit_lastAction_erase = false;

        void StageSheet_SetTileUpdate();
        void util_fillTile(int base_tile, int fill_tile, int x, int y);
        void StageSheet_FillTileUpdate();

        void util_drawSelectedTiles();
        void StageSheet_SelectTileUpdate();

        void StageSheet_BoxSelectTileUpdate();

        void StageSheet_MoveTileUpdate();
        void StageSheet_CopyTileUpdate();

        void StageSheet_DeleteSelectedTileUpdate();

        //void updateTileSelectionTilemap();



        //ISO Tiles
        void StageSheet_SetTileUpdate_ISO();
        void util_fillTile_ISO(int base_tile, int fill_tile, int x, int y, bool use_map2);
        void StageSheet_FillTileUpdate_ISO();

        void StageSheet_SelectTileUpdate_ISO();

        void getTriangleSides(float angle, float hyp, float* t_adjacent, float* t_opposite);
        bool getLineIntersect(double p0_x, double p0_y, double p1_x, double p1_y, double p2_x, double p2_y, double p3_x, double p3_y, double* i_x, double* i_y);

        void selectTileAt(int x, int y);
        Nirvana_SelectTool_TileSelection getTileMapPositionAt(int x, int y);
        void selectISOTilesInBox(bool start_m, int start_x, int start_y, int num_across, int num_down );

        void StageSheet_BoxSelectTileUpdate_ISO();

        void StageSheet_MoveTileUpdate_ISO();
        void StageSheet_CopyTileUpdate_ISO();

        void StageSheet_DeleteSelectedTileUpdate_ISO();
        //----------------------------------------------------




        std::vector<int> pick_sprites;
        void pickSprites(int start_x, int start_y, int end_x, int end_y, bool current_canvas_only=true);

        bool map_sprite_selection_changed = false;
        bool map_sprite_pos_changed = false;
        bool map_sprite_angle_changed = false;
        bool map_sprite_scale_changed = false;
        wxPGProperty* nv_sprite_positionX_property = NULL;
        wxPGProperty* nv_sprite_positionY_property = NULL;
        wxPGProperty* nv_sprite_angle_property = NULL;
        wxPGProperty* nv_sprite_scaleX_property = NULL;
        wxPGProperty* nv_sprite_scaleY_property = NULL;

        void StageSheet_SelectSpriteUpdate();
        irr::core::vector2di selectSprite_box_start;
        irr::core::vector2df rotSprite_center_pos;
        float rotSprite_angle_start;
        float getHeading(irr::core::vector2df a, irr::core::vector2df b);

        void StageSheet_BoxSelectSpriteUpdate();
        void StageSheet_MoveSpriteUpdate();
        void StageSheet_RotateSpriteUpdate();
        void StageSheet_ScaleSpriteUpdate();

		wxStaticText* m_cameraAbsoluteX_staticText = NULL;
		wxStaticText* m_cameraAbsoluteY_staticText = NULL;
		wxStaticText* m_cameraTileX_staticText = NULL;
		wxStaticText* m_cameraTileY_staticText = NULL;

		wxStaticText* m_stageAbsoluteX_staticText = NULL;
		wxStaticText* m_stageAbsoluteY_staticText = NULL;
		wxStaticText* m_stageTileX_staticText = NULL;
		wxStaticText* m_stageTileY_staticText = NULL;

		wxStaticText* m_screenAbsoluteX_staticText = NULL;
		wxStaticText* m_screenAbsoluteY_staticText = NULL;

		wxListBox* m_mapEdit_collisionShape_listBox = NULL;

		void updateStageViewportInfo();


		int selected_shape = -1;
		std::vector<int> pick_points;
		std::vector<int> selected_points;
		std::vector<sprite2D_physics_obj> stage_physics_obj;

        bool show_shapes_all = false;
        bool pick_shape_update = false;
        void pickShape(int start_x, int start_y, int end_x, int end_y);

        void stage_collisionEdit_select();
        void stage_collisionEdit_boxSelect();
        void stage_collisionEdit_move();
        void stage_collisionEdit_draw();

        wxSpinCtrl* m_mapEdit_boxShape_posX_spinCtrl = NULL;
		wxSpinCtrl* m_mapEdit_boxShape_posY_spinCtrl = NULL;
		wxSpinCtrl* m_mapEdit_boxShape_width_spinCtrl = NULL;
		wxSpinCtrl* m_mapEdit_boxShape_height_spinCtrl = NULL;

		wxGrid* m_mapEdit_polyShape_grid = NULL;

		wxSpinCtrl* m_mapEdit_circleShape_centerX_spinCtrl = NULL;
		wxSpinCtrl* m_mapEdit_circleShape_centerY_spinCtrl = NULL;
		wxSpinCtrl* m_mapEdit_circleShape_radius_spinCtrl = NULL;

		int pointInQuad(double x, double y, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);


        void UpdateStageSheet();
        void UpdateStageTileSelect();
        void UpdateStageSpritePreview();

        std::vector<wxIrrlicht*> shared_control;
        wxIrrlicht* stage_edit_control = NULL;
        bool mapEdit_hasContext = false;

        void util_draw_cursor(int tile_x, int tile_y, irr::video::SColor cursor_color);

        void mapEdit_getContext();


        irr::IrrlichtDevice* m_pDevice;
        irr::video::IVideoDriver* m_pDriver;
        irr::scene::ISceneManager* m_pSceneManager;
        irr::gui::IGUIEnvironment* m_pGuiEnvironment;
        irr::scene::ICameraSceneNode* m_pCameraNode;
		wxTimer m_Timer;
        irr::gui::IGUIStaticText* m_pFPSText;
        bool m_showFPS;
        bool m_windowIsActive;
        bool m_forceWindowInActive;
        bool m_forceWindowActive;
        bool rendering;
        bool m_init = false;

        wxPoint drag_start;
        irr::core::rect<irr::s32> box_select_shape;
        bool box_select_draw_flag = false;
        int box_select_view = 0;
        wxPoint mouse_position;
        bool middle_drag_init = false;
        bool left_drag_init = false;
        bool right_drag_init = false;

        bool VIEW_KEY_W = false;
        bool VIEW_KEY_A = false;
        bool VIEW_KEY_S = false;
        bool VIEW_KEY_D = false;
        bool VIEW_KEY_R = false;
        bool VIEW_KEY_F = false;
        bool VIEW_KEY_CTRL = false;

        #ifdef __linux__
        GdkWindow* gdkWindow;
        #endif // __linux__

		enum {
			ID_IRR_TIMER=1000
		};

    private:
		//DECLARE_EVENT_TABLE();

};//wxIrrlicht

#endif
