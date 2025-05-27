#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>

#ifdef _WIN32
#include <windows.h>
#endif // WINDOWS

#ifdef __linux__
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include <gtk/gtk.h>
#include <X11/Xlib.h>
#endif // __linux__

#include <irrlicht.h>
#include "wxIrrlicht.h"

#include "rc_defines.h"
#include "rc_utf8.h"
#include "NirvanaEngine_Structs.h"

#include <cmath>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//BEGIN_EVENT_TABLE(wxIrrlicht, wxControl)
//    EVT_TIMER(ID_IRR_TIMER, wxIrrlicht::OnTimer)
//    EVT_SIZE(wxIrrlicht::OnSize)
//    EVT_PAINT(wxIrrlicht::OnPaint)
//    EVT_ERASE_BACKGROUND(wxIrrlicht::OnEraseBackground)
//    EVT_MOUSE_EVENTS(wxIrrlicht::OnMouse)
//    EVT_KEY_DOWN(wxIrrlicht::OnKey)
//    EVT_KEY_UP(wxIrrlicht::OnKey)
//END_EVENT_TABLE()

wxIrrlicht::wxIrrlicht(wxWindow* parent, wxWindowID id, bool bs, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
	: wxControl(parent, id, pos, size, style, wxDefaultValidator, name),
	m_pDevice(0),
    m_pDriver(0),
    m_pSceneManager(0),
    m_pGuiEnvironment(0),
    m_pCameraNode(0),
    m_Timer(this, ID_IRR_TIMER),
    m_pFPSText(0),
	m_showFPS(bs) {
		//this->SetFocus();
		//this->SetClientSize(size);
		//this->CaptureMouse();
	    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	    parent_window = parent;

}//ctor

wxIrrlicht::~wxIrrlicht() {
	m_pDevice->drop();
}//dtor


void wxIrrlicht::InitIrr(irr::SIrrlichtCreationParameters* init_params) {
    SIrrlichtCreationParameters params;
    params.DriverType = EDT_OPENGL;

    SIrrlichtCreationParameters* actual_params = init_params ? init_params : &params;
    dimension2d<u32> irrSize(parent_window->GetClientSize().GetX(), parent_window->GetClientSize().GetY());
    if(init_params)
    {
    	irrSize = init_params->WindowSize;
    }

    actual_params->WindowSize = irrSize;

#ifdef __linux__
    wxWindow* renderPanel = parent_window;
    GtkWidget* widget = renderPanel->GetHandle();

    if(!widget)
    {
        wxMessageBox(_("Could not get window handle"));
        return;
    }

    if (!gtk_widget_get_realized(widget)) {
            gtk_widget_realize(widget);
    }


    GdkWindow* gdkWindow = gtk_widget_get_window(widget);

    Window xid;

    if (gdkWindow)
    {
        xid = GDK_WINDOW_XID(gdkWindow);
    }
    else
    {
        wxMessageBox(_("Could not get window ID"));
        return;
    }

    actual_params->WindowId = reinterpret_cast<void*>(xid);

#endif

#ifdef _WIN32
actual_params->WindowId = (HWND)this->GetHandle();
#endif // _WIN32


    m_pDevice = createDeviceEx(*actual_params);

    //SIrrlichtCreationParameters wx_params;
    //wx_params.WindowId = parent_window;
    //wx_params.DeviceType = EIDT_WX;
    //wx_params.DriverType = EDT_OPENGL;

    //dimension2d<u32> irrSize(GetClientSize().GetX(), GetClientSize().GetY());
    //wx_params.WindowSize = irrSize;
    //wxMessageBox(_("testing"));
    //m_pDevice = createDeviceEx(wx_params);
    //wxMessageBox(_("no dice"));


    if (!m_pDevice) {
        throw "Can't create Irrlicht device!";
	}//if

	m_pDriver = m_pDevice->getVideoDriver();
	m_pSceneManager = m_pDevice->getSceneManager();
	m_pGuiEnvironment = m_pDevice->getGUIEnvironment();
    m_pDriver->OnResize(irrSize);

    parent_window->Connect( wxEVT_SIZE, wxSizeEventHandler( wxIrrlicht::OnParentSize ), NULL, this );

    Bind(wxEVT_TIMER, &wxIrrlicht::OnTimer, this);

    Bind(wxEVT_SIZE, &wxIrrlicht::OnSize, this);

    Bind(wxEVT_PAINT, &wxIrrlicht::OnPaint, this);

    Bind(wxEVT_ERASE_BACKGROUND, &wxIrrlicht::OnEraseBackground, this);

    //Bind(wxEVT_MOUSEWHEEL, &wxIrrlicht::OnMouse, this);

    Bind(wxEVT_KEY_DOWN, &wxIrrlicht::OnKey, this);
    Bind(wxEVT_KEY_UP, &wxIrrlicht::OnKey, this);

    m_forceWindowActive = true;
    rendering = false;
    Refresh();

    int t_size_w = 1024;
    int t_size_h = 128;

    if(init_params && (actual_params->DriverType == EDT_BURNINGSVIDEO || actual_params->DriverType == EDT_SOFTWARE))
	{
		t_size_w = (init_params->WindowSize.Width > t_size_w ? init_params->WindowSize.Width : t_size_w);
		t_size_h = (init_params->WindowSize.Height > t_size_h ? init_params->WindowSize.Height : t_size_h);
	}
	else
	{
		t_size_w = irrSize.Width;
		t_size_h = irrSize.Height;
	}

	back_buffer = createCanvas(t_size_w, t_size_h, 0, 0, parent_window->GetClientSize().GetX(), parent_window->GetClientSize().GetY());
	ui_layer = createCanvas(t_size_w, t_size_h, 0, 0, parent_window->GetClientSize().GetX(), parent_window->GetClientSize().GetY());

	//back_buffer = m_pDriver->addRenderTargetTexture(irr::core::dimension2d<irr::u32>((irr::u32)t_size, (irr::u32)t_size), "rt", ECF_A8R8G8B8);
	//ui_layer = m_pDriver->addRenderTargetTexture(irr::core::dimension2d<irr::u32>((irr::u32)t_size, (irr::u32)t_size), "rt", ECF_A8R8G8B8);


	ortho_matrix.buildProjectionMatrixOrthoLH(500.0f,300.0f,1.0f,-3000.0f);
	//perspective_matrix = camera[0].camera.camera->getProjectionMatrix();

	view2D_texture = NULL;

	m_init = true;

	wxString editor_path = wxStandardPaths::Get().GetExecutablePath();
	wxFileName font_fname(editor_path);
	font_fname.AppendDir(_("font"));
	font_fname.SetFullName(_("FreeMono.ttf"));

	ui_font1 = irr_LoadFont(font_fname.GetAbsolutePath().ToStdString(), 24);
	ui_font2 = irr_LoadFont(font_fname.GetAbsolutePath().ToStdString(), 16);

	wxFileName t_path(editor_path);
	t_path.AppendDir(_("sprites"));
	t_path.SetFullName(_("graizor.png"));
	//test_texture = m_pDriver->getTexture(t_path.GetAbsolutePath().ToStdString().c_str());

	if(init_params && (actual_params->DriverType == EDT_BURNINGSVIDEO || actual_params->DriverType == EDT_SOFTWARE))
	{
		force_refresh();
	}

}//InitIrr()

void wxIrrlicht::setDefaultMaterial(irr::scene::ISceneNode* node, irr::video::ITexture* texture)
{
	node->getMaterial(0).MaterialType = irr::video::EMT_ONETEXTURE_BLEND;
	node->getMaterial(0).Lighting = false;
	node->getMaterial(0).ZWriteEnable = irr::video::EZW_OFF;
	node->getMaterial(0).ZBuffer = false;
	node->getMaterial(0).BackfaceCulling = false;
	node->getMaterial(0).TextureLayer[0].Texture = texture;
	node->getMaterial(0).BlendOperation = irr::video::EBO_ADD;
	node->getMaterial(0).MaterialTypeParam = irr::video::pack_textureBlendFunc(irr::video::EBF_SRC_ALPHA, irr::video::EBF_ONE_MINUS_SRC_ALPHA, irr::video::EMFN_MODULATE_1X, irr::video::EAS_TEXTURE | irr::video::EAS_VERTEX_COLOR);
}


void wxIrrlicht::StartRendering(int milliseconds) {
    m_Timer.Start(milliseconds);
}//StartRendering()

void wxIrrlicht::StopRendering(){
    m_Timer.Stop();
}//StopRendering()

void wxIrrlicht::Render() {

    if (rendering) {
        return;
	}//if

	if(control_id == NV_MAP_EDIT_MAP_SHEET || control_id == NV_MAP_EDIT_TILE_SHEET)
	{
		if(!mapEdit_hasContext)
			return;
	}


    if(this->GetScreenRect().Contains( wxGetMousePosition() ))
        m_windowIsActive = true;
    else
        m_windowIsActive = false;

    if(m_forceWindowInActive)
        m_windowIsActive = false;

    if(m_forceWindowActive)
        m_windowIsActive = true;

    m_forceWindowInActive = false;
    m_forceWindowActive = false;

    rendering = true;
    //OnPreRender();
    OnRender();
    //OnPostRender();
    rendering = false;
}//Render()

void wxIrrlicht::OnCreateScene() {
	if (m_showFPS) {
		m_pFPSText = m_pGuiEnvironment->addStaticText(L"FPS: 0", rect<s32>(1, 1, 50, 10), false);
		m_pFPSText->setOverrideColor(SColor(255,255,255,255));
	}//if
}//OnCreateScene()

void wxIrrlicht::OnRender() {
        // draw everything here
        if(!m_init)
			return;

		if(test_init)
		{
			//m_pDriver->setRenderTarget(canvas[2].texture);
			//m_pDriver->draw2DImage(image[0].image, irr::core::vector2di(0,0));
				//drawImage(0, 0, 0);
		}

		if(back_buffer < 0 || ui_layer < 0)
			return;

		m_pDriver->beginScene(false, false, SColor(255,170,170,170));

		setActiveCanvas(back_buffer);
		setClearColor(rgba(0,0,0,0));
		clearCanvas();

		//m_pDriver->draw2DImage(test_texture, irr::core::vector2d(0,0));

		// Draw Canvases
		for(int cz = 0; cz < canvas_zOrder.size(); cz++)
        {
            int canvas_id = canvas_zOrder[cz];

            if(canvas_id == back_buffer || canvas_id == ui_layer)
				continue;

			if(!canvas[canvas_id].visible)
				continue;

            if(canvas[canvas_id].texture) // && canvas[canvas_id].visible)
            {
            	irr::core::dimension2du tst(this->GetSize().GetWidth(), this->GetSize().GetHeight());
            	//irr::core::vector2d<f32> bb_size(canvas[back_buffer].viewport.dimension.Width, canvas[back_buffer].viewport.dimension.Height);
            	irr::core::vector2d<f32> bb_size(canvas[back_buffer].dimension.Width, canvas[back_buffer].dimension.Height);
                irr::core::rect<s32> dest(canvas[canvas_id].viewport.position, canvas[canvas_id].viewport.dimension);
                irr::core::rect<s32> src(canvas[canvas_id].offset, canvas[canvas_id].viewport.dimension);

                irr::video::SColor color(canvas[canvas_id].color_mod);
                //irr::video::SColor color(255,0,255,0);

                if(canvas[canvas_id].type == CANVAS_TYPE_SPRITE)
				{
					src = irr::core::rect<s32>( irr::core::vector2d<s32>(0, 0), canvas[canvas_id].viewport.dimension); //sprite layers will just offset the sprites in drawSprites()
					util_drawSprites(canvas_id);
				}
				else if(canvas[canvas_id].type == CANVAS_TYPE_TILEMAP)
				{

					src = irr::core::rect<s32>( irr::core::vector2d<s32>(0, 0), canvas[canvas_id].viewport.dimension); //sprite layers will just offset the sprites in drawSprites()
					int vpw = canvas[canvas_id].viewport.dimension.Width;
					int vph = canvas[canvas_id].viewport.dimension.Height;
					int off_x = canvas[canvas_id].offset.X;
					int off_y = canvas[canvas_id].offset.Y;
					m_pDriver->setRenderTarget(canvas[canvas_id].texture, true, true);
					m_pDriver->clearBuffers(true, true, true, irr::video::SColor(0,0,0,0));
					drawTileMap(canvas[canvas_id].tilemap, 0, 0, vpw, vph, off_x, off_y);
				}
				else if(canvas[canvas_id].type == CANVAS_TYPE_2D && canvas[canvas_id].bkg_render_type >= 0)
				{
					setActiveCanvas(canvas_id);
					clearCanvas();

					int vpw = canvas[canvas_id].viewport.dimension.Width;
					int vph = canvas[canvas_id].viewport.dimension.Height;
					int off_x = canvas[canvas_id].offset.X;
					int off_y = canvas[canvas_id].offset.Y;
					int img_w = 0;
					int img_h = 0;
					int layer_index = canvas[canvas_id].layer_index;

					float scroll_speed_x = project->getLayerScrollSpeed(selected_stage, layer_index).X;
					float scroll_speed_y = project->getLayerScrollSpeed(selected_stage, layer_index).Y;

					int adj_scroll_offset_x = scroll_speed_x * scroll_offset_x;
					int adj_scroll_offset_y = scroll_speed_y * scroll_offset_y;

					int tsx = -adj_scroll_offset_x;
					int tsy = -adj_scroll_offset_y;

					getImageSizeI(canvas[canvas_id].bkg_render_image_id, &img_w, &img_h);

					if(canvas[canvas_id].bkg_render_type == IMG_RENDER_SETTING_NORMAL)
					{
						if(imageExists(canvas[canvas_id].bkg_render_image_id))
						{
							drawImage(canvas[canvas_id].bkg_render_image_id, 0, 0);
						}
					}
					else if(canvas[canvas_id].bkg_render_type == IMG_RENDER_SETTING_STRETCHED)
					{
						if(imageExists(canvas[canvas_id].bkg_render_image_id))
						{
							drawImage_BlitEx(canvas[canvas_id].bkg_render_image_id, 0, 0, vpw, vph, 0, 0, img_w, img_h);
						}
					}
					else if(canvas[canvas_id].bkg_render_type == IMG_RENDER_SETTING_TILED)
					{
						if(imageExists(canvas[canvas_id].bkg_render_image_id))
						{
							for(int it_y = tsy; it_y < vph; it_y+=img_h)
							{
								for(int  it_x = tsx; it_x < vpw; it_x+=img_w)
								{
									drawImage(canvas[canvas_id].bkg_render_image_id, it_x, it_y);
								}
							}
						}
					}

					setActiveCanvas(back_buffer);
				}

				if(test_init)
				{
					//setActiveCanvas(canvas_id);
					//m_pDriver->setRenderTarget(canvas[canvas_id].texture);
					//m_pDriver->draw2DImage(image[0].image, irr::core::vector2di(0,0));
					//drawImage(0, 0, 0);
				}

                //Set Target to back buffer
				m_pDriver->setRenderTarget(canvas[back_buffer].texture, false, false);
                util_draw2DImage2(m_pDriver, canvas[canvas_id].texture, src, dest, irr::core::position2d<irr::s32>(0, 0), 0, true, color, bb_size);
            }
        }

        //Draw shapes in other layer
        if(selected_stage >= 0 && selected_stage < project->stages.size())
		{
			if(show_grid)
			{
				util_drawGrid();
			}

			if(show_shapes_all)
			{
				for(int i = 0; i < project->stages[selected_stage].layers.size(); i++)
				{
					if(project->stages[selected_stage].layers[i].layer_type != LAYER_TYPE_SPRITE)
						continue;

					if(i == selected_layer)
						continue;

					if(!project->stages[selected_stage].layers[i].ref_canvas)
						continue;

					//std::cout << "Draw Shapes in Layer " << i << std::endl;
					util_drawShapes(i);
				}
			}

		}

		//Set Target to back buffer
		m_pDriver->setRenderTarget(canvas[back_buffer].texture, false, false);

        test_init = false;

        //UI LAYER
        irr::core::recti ui_rect( irr::core::position2di(0, 0), irr::core::dimension2du(this->GetSize().GetWidth(), this->GetSize().GetHeight()) );
		irr::core::vector2d<f32> bb_size(canvas[back_buffer].dimension.Width, canvas[back_buffer].dimension.Height);
		irr::video::SColor color(canvas[ui_layer].color_mod);
        if(control_id == NV_MAP_EDIT_MAP_SHEET)
			util_draw2DImage2(m_pDriver, canvas[ui_layer].texture, ui_rect, ui_rect, irr::core::position2d<irr::s32>(0, 0), 0, true, color, bb_size );


        m_pDriver->setRenderTarget(0);

        irr::core::recti bb_rect( irr::core::position2di(0, 0), irr::core::dimension2du(this->GetSize().GetWidth(), this->GetSize().GetHeight()) );
        m_pDriver->draw2DImage(canvas[back_buffer].texture, bb_rect, bb_rect );


        //m_pDriver->beginScene(true, true, SColor(255,170,170,170));
        //m_pSceneManager->drawAll();
        //m_pGuiEnvironment->drawAll();
        m_pDriver->endScene();

        setActiveCanvas(active_canvas);

        Refresh();

}//OnRender()

void wxIrrlicht::OnPostRender() {

    if (m_pFPSText && m_showFPS) {
        int fps = m_pDriver->getFPS();

        static int lastFPS = 0;
        if (lastFPS != fps) {
            core::stringw str = L"FPS: ";
            str += fps;

            m_pFPSText->setText(str.c_str());
            lastFPS = fps;
        }//if
    }//if
}//OnPostRender()

void wxIrrlicht::OnPaint(wxPaintEvent& event){
    mapEdit_getContext();
    Render();
    wxPaintDC paint_dc(this);

}//OnPaint()

void wxIrrlicht::OnParentSize(wxSizeEvent& event)
{
	if(!m_init)
		return;

    if (!m_pDriver) {
        return;
	}//if

    s32 w;
    s32 h;

    wxWindow* parent = (wxWindow*)event.GetEventObject();

    parent->GetClientSize(&w, &h);
    this->SetClientSize(w, h);

    dimension2d<u32> size(w, h);
    m_pDriver->OnResize(size);

    setCanvasViewport(sheet_canvas, 0, 0, w, h);
    setCanvasViewport(collision_canvas, 0, 0, w, h);

    if (m_pCameraNode) {
        m_pCameraNode->setAspectRatio((float)w / (float)h);
	}//if

	m_pDevice->setWindowSize(irr::core::dimension2d<irr::u32>((irr::u32)w,(irr::u32)h));

	resizeLayers();

	m_forceWindowActive = true;
	parent->Refresh();
	Refresh();

	//wxMessageBox(_("REFRESH"));
}

void wxIrrlicht::OnSize(wxSizeEvent& event) {
    if (!m_pDriver) {
        return;
	}//if


    return;
}//OnSize


void wxIrrlicht::OnTimer(wxTimerEvent& event) {
	if(!m_init)
		return;

    m_pDevice->getTimer()->tick();

    OnUpdate();
}

void wxIrrlicht::OnMouse(wxMouseEvent& event) {

	return;

	if(!m_init)
		return;

    irr::SEvent sevt;

    wxMessageBox(_("CALL") + wxString::Format(_("%d"), event.GetEventType()));

    sevt.EventType = irr::EET_MOUSE_INPUT_EVENT;

    if (event.IsButton()) {
        if (event.LeftDown())
		{
			sevt.MouseInput.Event = irr::EMIE_LMOUSE_PRESSED_DOWN;
		}
        else if (event.LeftUp())
            sevt.MouseInput.Event = irr::EMIE_LMOUSE_LEFT_UP;
        else if (event.MiddleDown())
            sevt.MouseInput.Event = irr::EMIE_MMOUSE_PRESSED_DOWN;
        else if (event.MiddleUp())
            sevt.MouseInput.Event = irr::EMIE_MMOUSE_LEFT_UP;
        else if (event.RightDown())
            sevt.MouseInput.Event = irr::EMIE_RMOUSE_PRESSED_DOWN;
        else if (event.RightUp())
            sevt.MouseInput.Event = irr::EMIE_RMOUSE_LEFT_UP;
    }//if

    else if (event.GetWheelRotation() != 0) {
        sevt.MouseInput.Wheel = (float)event.GetWheelRotation();
        sevt.MouseInput.Event = irr::EMIE_MOUSE_WHEEL;
    }//else if

    else if (event.Moving() || event.Dragging()) {
		sevt.MouseInput.Event = irr::EMIE_MOUSE_MOVED;
	}//else if

    sevt.MouseInput.X = event.GetX();
    sevt.MouseInput.Y = event.GetY();

    m_pDevice->postEventFromUser(sevt);

    event.Skip();
}//OnMouse()

void wxIrrlicht::OnKey(wxKeyEvent& event) {
	if(!m_init)
		return;

    irr::SEvent sevt;

    //wxMessageBox(_("KEY EVENT: ") + wxString::Format(_("%d"), event.GetKeyCode()));

    sevt.EventType = irr::EET_KEY_INPUT_EVENT;

    sevt.KeyInput.Key = (irr::EKEY_CODE)event.GetRawKeyCode();
    sevt.KeyInput.PressedDown = event.GetEventType() == wxEVT_KEY_DOWN;

    sevt.KeyInput.Shift = event.ShiftDown();
    sevt.KeyInput.Control = event.CmdDown();
    VIEW_KEY_CTRL = event.ControlDown();
#if wxUSE_UNICODE
    sevt.KeyInput.Char = event.GetUnicodeKey();
#else
    sevt.KeyInput.Char = event.GetKeyCode();
#endif

    m_pDevice->postEventFromUser(sevt);

    if(event.GetKeyCode() == irr::KEY_KEY_W)
	{
		VIEW_KEY_W = sevt.KeyInput.PressedDown;
		//wxMessageBox(_("KEY EVENT2: ") + wxString::Format(_("%d"), VIEW_KEY_W));
	}
	else if(event.GetKeyCode() == irr::KEY_KEY_A)
	{
		VIEW_KEY_A = sevt.KeyInput.PressedDown;
		//wxMessageBox(_("KEY EVENT2: ") + wxString::Format(_("%d"), VIEW_KEY_W));
	}
	else if(event.GetKeyCode() == irr::KEY_KEY_S)
	{
		VIEW_KEY_S = sevt.KeyInput.PressedDown;
		//wxMessageBox(_("KEY EVENT2: ") + wxString::Format(_("%d"), VIEW_KEY_W));
	}
	else if(event.GetKeyCode() == irr::KEY_KEY_D)
	{
		VIEW_KEY_D = sevt.KeyInput.PressedDown;
		//wxMessageBox(_("KEY EVENT2: ") + wxString::Format(_("%d"), VIEW_KEY_W));
	}
	else if(event.GetKeyCode() == irr::KEY_KEY_R)
	{
		VIEW_KEY_R = sevt.KeyInput.PressedDown;
		//wxMessageBox(_("KEY EVENT2: ") + wxString::Format(_("%d"), VIEW_KEY_W));
	}
	else if(event.GetKeyCode() == irr::KEY_KEY_F)
	{
		VIEW_KEY_F = sevt.KeyInput.PressedDown;
		//wxMessageBox(_("KEY EVENT2: ") + wxString::Format(_("%d"), VIEW_KEY_W));
	}

    event.Skip();
}//OnKey()


void wxIrrlicht::force_refresh()
{
    if (!m_pDriver) {
        return;
	}//if

    s32 w;
    s32 h;

    wxWindow* parent = parent_window;

    parent->GetClientSize(&w, &h);
    this->SetClientSize(w, h);

    dimension2d<u32> size(w, h);
    m_pDriver->OnResize(size);

    if (m_pCameraNode) {
        m_pCameraNode->setAspectRatio((float)w / (float)h);
	}//if

	m_pDevice->setWindowSize(irr::core::dimension2du((irr::u32)w,(irr::u32)h));

	m_forceWindowActive = true;
	parent->Refresh();
	Refresh();
}

void wxIrrlicht::rc_setDriverMaterial()
{
	if(!m_pDriver)
		return;

	irr::video::SMaterial material;
    material.Lighting = false;
    material.ZWriteEnable = irr::video::EZW_OFF;
    material.ZBuffer = false;
    material.BackfaceCulling = false;
    material.TextureLayer[0].Texture = 0;
    //material.TextureLayer[0].BilinearFilter = true;
    material.MaterialTypeParam = irr::video::pack_textureBlendFunc(irr::video::EBF_SRC_ALPHA, irr::video::EBF_ONE_MINUS_SRC_ALPHA, irr::video::EMFN_MODULATE_1X, irr::video::EAS_TEXTURE | irr::video::EAS_VERTEX_COLOR);
    material.BlendOperation = irr::video::EBO_ADD;
    //material.AntiAliasing = rc_anti_alias;

    material.MaterialType = irr::video::EMT_ONETEXTURE_BLEND;

    m_pDriver->setMaterial(material);
}

void wxIrrlicht::OnUpdate()
{
	if(!enable_update)
		return;

	if((!update_events) && m_pDriver->getDriverType() == irr::video::EDT_OPENGL)
		return;

	if(!stage_window_isActive)
	{
		VIEW_KEY_A = false;
		VIEW_KEY_D = false;
		VIEW_KEY_F = false;
		VIEW_KEY_R = false;
		VIEW_KEY_S = false;
		VIEW_KEY_W = false;
		VIEW_KEY_CTRL = false;
	}

	switch(control_id)
	{
		case NV_SPRITE_EDIT_ANIMATION_SHEET:
			UpdateSpriteAnimationSheet();
			break;

		case NV_SPRITE_EDIT_ANIMATION_FRAME:
			UpdateSpriteAnimationFrame();
			break;

		case NV_SPRITE_EDIT_ANIMATION_PREVIEW:
			UpdateSpriteAnimationPreview();
			break;

		case NV_SPRITE_EDIT_COLLISION_SHEET:
			UpdateSpriteCollision();
			break;

		case NV_TILE_EDIT_ANIMATION_SHEET:
			UpdateTileAnimationSheet();
			break;

		case NV_TILE_EDIT_ANIMATION_FRAME:
			UpdateTileAnimationFrame();
			break;

		case NV_TILE_EDIT_ANIMATION_PREVIEW:
			UpdateTileAnimationPreview();
			break;

		case NV_TILE_EDIT_MASK_SHEET:
			UpdateTileMask();
			break;

		case NV_MAP_EDIT_MAP_SHEET:
			UpdateStageSheet();
			break;

		case NV_MAP_EDIT_TILE_SHEET:
			UpdateStageTileSelect();
			break;

		case NV_MAP_EDIT_SPRITE_PREVIEW:
			UpdateStageSpritePreview();
			break;
	}

	return;

}

void wxIrrlicht::util_drawGrid()
{
	if(!project)
		return;


	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	if(selected_layer < 0 || selected_layer >= project->stages[selected_stage].layers.size())
		return;

	mapEdit_getContext();
	setActiveCanvas(ui_layer);

	setColor(grid_color.color);

	int adj_scroll_offset_x = project->stages[selected_stage].layers[selected_layer].scroll_speed.X * scroll_offset_x;
	int adj_scroll_offset_y = project->stages[selected_stage].layers[selected_layer].scroll_speed.Y * scroll_offset_y;

	int start_x = adj_scroll_offset_x;
	int start_y = adj_scroll_offset_y;

	//std::cout << "offset debug: " << start_x << " ~ " << ((start_x + (start_x*32)) % project->stages[selected_stage].tile_width) << std::endl;

	start_x = (project->stages[selected_stage].tile_width - (start_x % project->stages[selected_stage].tile_width)) - project->stages[selected_stage].tile_width;
	start_y = (project->stages[selected_stage].tile_height - (start_y % project->stages[selected_stage].tile_height)) - project->stages[selected_stage].tile_height;

	int pw = this->GetClientSize().GetWidth();
	int ph = this->GetClientSize().GetHeight();

	for(int y = start_y; y < ph+1; y += project->stages[selected_stage].tile_height)
	{
		drawLine(-1, y, pw+1, y);
		for(int x = start_x; x < pw+1; x += project->stages[selected_stage].tile_width)
		{
			drawLine(x, -1, x, ph+1);
		}
	}
}

void wxIrrlicht::UpdateSpriteAnimationSheet()
{
	if(clear_flag)
	{
		setActiveCanvas(sheet_canvas);
		clearCanvas();
		clear_flag = false;
		return;
	}

	if(current_sheet_image < 0 || current_sheet_image >= image.size())
		return;

	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();

	if(stage_window_isActive)
	{
		this->SetFocusFromKbd();
	}


	setActiveCanvas(sheet_canvas);
	clearCanvas();

	double w = 0;
	double h = 0;

	if(VIEW_KEY_W)
	{
		scroll_offset_y -= scroll_speed;
	}

	if(VIEW_KEY_A)
	{
		scroll_offset_x -= scroll_speed;
	}

	if(VIEW_KEY_S)
	{
		scroll_offset_y += scroll_speed;
	}

	if(VIEW_KEY_D)
	{
		scroll_offset_x += scroll_speed;
	}

	int bx = ( (px+scroll_offset_x) / current_frame_width) *  current_frame_width;
	int by = ( (py+scroll_offset_y) / current_frame_height) *  current_frame_height;

	int off_x_i = (int)scroll_offset_x;
	int off_y_i = (int)scroll_offset_y;

	int select_x = bx - off_x_i;
	int select_y = by - off_y_i;

	int img_x = -scroll_offset_x;
	int img_y = -scroll_offset_y;

	if(imageExists(current_sheet_image))
	{
		getImageSize(current_sheet_image, &w, &h);
		//m_pDriver->draw2DImage(image[current_sheet_image].image, irr::core::vector2di(0,0),);
		drawImage_BlitEx_SW(current_sheet_image, img_x, img_y, (int)w, (int)h, 0, 0, (int)w, (int)h);
		//drawImage_Rotozoom(current_sheet_image, 0, 0, 0, 1, 1);
	}

	if(px >= img_x && px < (img_x+w) && py >= img_y && py < (img_y+h))
	{
		setColor(rgb(255, 0, 0));
		drawRect(select_x, select_y, current_frame_width, current_frame_height);
	}


	if(mouse_state.LeftIsDown())
	{
        bool init_click = false;

		if(!(middle_drag_init||left_drag_init||right_drag_init))
		{

			if( px >= 0 && px < pw && py >= 0 && py < ph )
			{
				int fx = select_x + scroll_offset_x;
				int fy = select_y + scroll_offset_y;
				int fw = w;
				int fh = h;

				if(stage_window_isActive)
				{
					if(px >= img_x && px < (img_x+w) && py >= img_y && py < (img_y+h))
						selected_frame = (fy/current_frame_height) * (fw/current_frame_width) + (fx/current_frame_width);
					else
						selected_frame = -1;
				}
				else
					selected_frame = -1;

				//std::cout << "TEST: " << select_x << ", " << select_y << " --> " << selected_frame << std::endl;

				parent_window->UpdateWindowUI();

				left_drag_init = true;
			}
		}
	}
	else if( (!mouse_state.LeftIsDown()) && left_drag_init )
	{
		//SHOW_CURSOR;
		//this->ReleaseMouse();
		left_drag_init = false;
		//wxMessageBox(_("RELEASE"));
		return;
	}
}

void wxIrrlicht::UpdateSpriteAnimationFrame()
{
	if(clear_flag)
	{
		setActiveCanvas(frame_canvas);
		clearCanvas();
		clear_flag = false;
		return;
	}

	if(current_sheet_image < 0 || current_sheet_image >= image.size())
		return;

	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();

	if( px < 0 || px >= pw || py < 0 || py >= ph)
		stage_window_isActive = false;
	else
		stage_window_isActive = true;


	setActiveCanvas(frame_canvas);
	clearCanvas();

	setColor(rgb(70,70,70));
	drawRectFill(0,64,pw,30);

	int bx = (px / current_frame_width) *  current_frame_width;
	int by = (py / current_frame_height) *  current_frame_height;

	double d_sheet_w = 0;
	double d_sheet_h = 0;

	int sheet_w = 0;
	int sheet_h = 0;

	if(imageExists(current_sheet_image))
	{
		//getImageSize(current_sheet_image, &d_sheet_w, &d_sheet_h);
		sheet_w = sheet_width; // (int) d_sheet_w;
		sheet_h = sheet_height; //(int) d_sheet_h;
	}

	int num_frames = 0;

	//draw borders
	if(spriteExists(spriteEdit_selected_sprite))
	{
		//wxMessageBox(_("ANIMATION: ") + wxString::Format(_("%i"), sprite[spriteEdit_selected_sprite].animation.size()));
		if(spriteEdit_selected_animation >= 0 &&  spriteEdit_selected_animation < sprite[spriteEdit_selected_sprite].animation.size())
		{
			num_frames = getSpriteAnimationLength(spriteEdit_selected_sprite, spriteEdit_selected_animation);

			int all_frame_width = num_frames*64;
			if( (all_frame_width - scroll_offset_x) <= 64)
				scroll_offset_x = all_frame_width - 64;

			if( scroll_offset_x < 0)
				scroll_offset_x = 0;

			setColor(rgb(30, 30, 30));
			if(imageExists(current_sheet_image))
			{
				irr_SetFont(1);
				for(int i = 0; i < num_frames; i++)
				{
					int sheet_frame = getSpriteAnimationFrame(spriteEdit_selected_sprite, spriteEdit_selected_animation, i);
					int fx = i*64-scroll_offset_x;
					if(sheet_frame >= 0 && fx >= 0 && fx < pw)
					{
						int frames_per_row = sheet_w / current_frame_width;
						int sheet_x = (sheet_frame % frames_per_row) * current_frame_width;
						int sheet_y = (sheet_frame / frames_per_row) * current_frame_height;

						if(mouse_state.RightIsDown())
						{
							//std::cout << "DEBUG: ani_frame=" << i << "   sheet_frame=" << sheet_frame << "   src=(" << sheet_x << ", " << sheet_y << ") ";
							//std::cout << "sheet=(" << sheet_w << ", " << frames_per_row << ") frame=(" << current_frame_width << ", " << current_frame_height << ") " << std::endl;
						}

						drawImage_BlitEx_SW(current_sheet_image, fx, 0, 64, 64, sheet_x, sheet_y, current_frame_width, current_frame_height);
					}
					setColor(rgb(30, 30, 30));
					drawRect(fx, 0, 64, 63);
					wxString f_num_txt = wxString::Format(_("%i"), i);
					setColor(rgb(0,0,0));
					drawRectFill(fx, 0, 20, 20);
					irr_DrawText(f_num_txt.ToStdString(), fx+1, 1, irr::video::SColor(255, 255, 255, 255), 1);

					setColor(rgb(255,255,255));
					if(selected_frame == i)
					{
						drawRect(fx, 0, 63, 63);
					}
				}
			}
		}
	}

	if( px >= 0 && px < pw && py >= 0 && py < ph )
	{

		double off_x = 0;
		double off_y = 0;

		getCanvasOffset(frame_canvas, &off_x, &off_y);

		int off_x_i = (int)off_x;
		int off_y_i = (int)off_y;

		int bx = (px / 64) *  64;
		int by = (py / 64) *  64;

		setColor(rgb(255, 0, 0));
		drawRect(bx - off_x_i, 0, 64, 63);
	}


	if(mouse_state.LeftIsDown())
	{
        bool init_click = false;

		if(!(middle_drag_init||left_drag_init||right_drag_init))
		{

			if( px >= 0 && px < pw && py >= 0 && py < ph )
			{
				left_drag_init = true;

				selected_frame = (scroll_offset_x/64) + (px/64);

				//std::cout << "SELECTED: " << selected_frame << std::endl;
			}
		}
	}
	else if( (!mouse_state.LeftIsDown()) && left_drag_init )
	{
		//SHOW_CURSOR;
		//this->ReleaseMouse();
		left_drag_init = false;
		//wxMessageBox(_("RELEASE"));
		return;
	}
}

void wxIrrlicht::UpdateSpriteAnimationPreview()
{
	if(clear_flag)
	{
		setActiveCanvas(preview_canvas);
		clearCanvas();
		clear_flag = false;
		return;
	}

	if(current_sheet_image < 0 || current_sheet_image >= image.size())
		return;


	setActiveCanvas(preview_canvas);
	clearCanvas();

	//int bx = (px / current_frame_width) *  current_frame_width;
	//int by = (py / current_frame_height) *  current_frame_height;


	if(imageExists(current_sheet_image))
	{
		drawImage_BlitEx_SW(current_sheet_image, 0, 0, 64, 64, 0, 0, 64, 64);
	}

	return;
}

bool wxIrrlicht::collisionPointIsSelected(int pt_index)
{
	for(int i = 0; i < collision_selected_points.size(); i++)
	{
		if(collision_selected_points[i] == pt_index)
			return true;
	}
	return false;
}

void wxIrrlicht::collisionEdit_select()
{
	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();

	int img_scale = ph/current_frame_height;
	int img_w = current_frame_width*img_scale;
	int img_h = current_frame_height*img_scale;
	int img_x = pw/2 - img_w/2;
	int img_y = ph/2 - img_h/2;

	int box_x = img_x + (collision_physics_obj.offset_x*img_scale);
	int box_y = img_y + (collision_physics_obj.offset_y*img_scale);

	int box_w = (collision_physics_obj.box_width*img_scale);
	int box_h = (collision_physics_obj.box_height*img_scale);

	int circle_radius = collision_physics_obj.radius*img_scale;
	int circle_center_x = img_x + (collision_physics_obj.offset_x*img_scale) + (img_w/2);
	int circle_center_y = img_y + (collision_physics_obj.offset_y*img_scale) + (img_h/2);

	int circle_ux = circle_center_x;
	int circle_uy = circle_center_y - circle_radius;

	int circle_dx = circle_center_x;
	int circle_dy = circle_center_y + circle_radius;

	int circle_lx = circle_center_x - circle_radius;
	int circle_ly = circle_center_y;

	int circle_rx = circle_center_x + circle_radius;
	int circle_ry = circle_center_y;

	irr::core::vector2di mouse_pos(px, py);

	switch(collision_physics_obj.shape_type)
	{
		case SPRITE_SHAPE_BOX:
		{
			if(mouse_state.LeftIsDown())
			{
				bool init_click = false;

				if(!(middle_drag_init||left_drag_init||right_drag_init))
				{

					if( px >= 0 && px < pw && py >= 0 && py < ph )
					{
						left_drag_init = true;
						this->SetFocusFromKbd();
						init_click = true;

						float ul_distance = mouse_pos.getDistanceFrom(irr::core::vector2di(box_x, box_y)); //need to factor in offset and box size
						float ll_distance = mouse_pos.getDistanceFrom(irr::core::vector2di(box_x, box_y+box_h));
						float ur_distance = mouse_pos.getDistanceFrom(irr::core::vector2di(box_x+box_w, box_y));
						float lr_distance = mouse_pos.getDistanceFrom(irr::core::vector2di(box_x+box_w, box_y+box_h));

						//std::cout << "dist: " << ul_distance << ", " << ll_distance << ", " << ur_distance << ", " << lr_distance << std::endl;

						int select_tolerance = 1;
						collision_boxShapeSelect_ul = ul_distance < (img_scale+select_tolerance);
						collision_boxShapeSelect_ll = collision_boxShapeSelect_ul ? false : ll_distance < (img_scale+select_tolerance);
						collision_boxShapeSelect_ur = collision_boxShapeSelect_ll ? false : ur_distance < (img_scale+select_tolerance);
						collision_boxShapeSelect_lr = collision_boxShapeSelect_ur ? false : lr_distance < (img_scale+select_tolerance);

						if(collision_boxShapeSelect_ul)
						{
							//std::cout << "upper left selected" << std::endl;
						}
						else if(collision_boxShapeSelect_ll)
						{
						}
						else if(collision_boxShapeSelect_ur)
						{
						}
						else if(collision_boxShapeSelect_lr)
						{
						}
					}
				}
			}
		}
		break;

		case SPRITE_SHAPE_CIRCLE:
		{
			if(mouse_state.LeftIsDown())
			{
				bool init_click = false;

				if(!(middle_drag_init||left_drag_init||right_drag_init))
				{

					if( px >= 0 && px < pw && py >= 0 && py < ph )
					{
						left_drag_init = true;
						this->SetFocusFromKbd();
						init_click = true;

						float u_distance = mouse_pos.getDistanceFrom(irr::core::vector2di(circle_ux, circle_uy)); //need to factor in offset and box size
						float d_distance = mouse_pos.getDistanceFrom(irr::core::vector2di(circle_dx, circle_dy));
						float l_distance = mouse_pos.getDistanceFrom(irr::core::vector2di(circle_lx, circle_ly));
						float r_distance = mouse_pos.getDistanceFrom(irr::core::vector2di(circle_rx, circle_ry));

						//std::cout << "DBG: " << circle_center_x << ", " << circle_center_y << std::endl;
						//std::cout << "dist: " << ul_distance << ", " << ll_distance << ", " << ur_distance << ", " << lr_distance << std::endl;

						int select_tolerance = 1;
						collision_circleShapeSelect_u = u_distance < (img_scale+select_tolerance);
						collision_circleShapeSelect_d = collision_circleShapeSelect_u ? false : d_distance < (img_scale+select_tolerance);
						collision_circleShapeSelect_l = collision_circleShapeSelect_d ? false : l_distance < (img_scale+select_tolerance);
						collision_circleShapeSelect_r = collision_circleShapeSelect_l ? false : r_distance < (img_scale+select_tolerance);

						if(collision_circleShapeSelect_u)
						{
							//std::cout << "upper left selected" << std::endl;
						}
						else if(collision_circleShapeSelect_d)
						{
						}
						else if(collision_circleShapeSelect_l)
						{
						}
						else if(collision_circleShapeSelect_r)
						{
						}
					}
				}
			}
		}
		break;

		case SPRITE_SHAPE_POLYGON:
		{
			if(mouse_state.LeftIsDown())
			{
				bool init_click = false;

				if(!(middle_drag_init||left_drag_init||right_drag_init))
				{

					if( px >= 0 && px < pw && py >= 0 && py < ph )
					{
						left_drag_init = true;
						this->SetFocusFromKbd();
						init_click = true;

						float pt_distance = mouse_pos.getDistanceFrom(irr::core::vector2di(circle_ux, circle_uy)); //need to factor in offset and box size
						int select_tolerance = 1;

						if(!VIEW_KEY_CTRL)
							collision_selected_points.clear();

						for(int i = 0; i < collision_physics_obj.points.size(); i++)
						{
							int point_x = img_x + collision_physics_obj.points[i].X * img_scale;
							int point_y = img_y + collision_physics_obj.points[i].Y * img_scale;
							pt_distance = mouse_pos.getDistanceFrom(irr::core::vector2di(point_x, point_y));

							bool point_select = pt_distance < (img_scale+select_tolerance);
							if(point_select)
							{
								if(!collisionPointIsSelected(i))
									collision_selected_points.push_back(i);

								//std::cout << "VCTRL: " << (int)VIEW_KEY_CTRL << std::endl;

								if(!VIEW_KEY_CTRL)
									break;
							}
						}
					}
				}
			}
		}
		break;
	}
}

void wxIrrlicht::collisionEdit_boxSelect()
{
	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();

	int img_scale = ph/current_frame_height;
	int img_w = current_frame_width*img_scale;
	int img_h = current_frame_height*img_scale;
	int img_x = pw/2 - img_w/2;
	int img_y = ph/2 - img_h/2;

	int box_x = img_x + (collision_physics_obj.offset_x*img_scale);
	int box_y = img_y + (collision_physics_obj.offset_y*img_scale);

	int box_w = (collision_physics_obj.box_width*img_scale);
	int box_h = (collision_physics_obj.box_height*img_scale);

	int circle_radius = collision_physics_obj.radius*img_scale;
	int circle_center_x = img_x + (collision_physics_obj.offset_x*img_scale) + (img_w/2);
	int circle_center_y = img_y + (collision_physics_obj.offset_y*img_scale) + (img_h/2);

	int circle_ux = circle_center_x;
	int circle_uy = circle_center_y - circle_radius;

	int circle_dx = circle_center_x;
	int circle_dy = circle_center_y + circle_radius;

	int circle_lx = circle_center_x - circle_radius;
	int circle_ly = circle_center_y;

	int circle_rx = circle_center_x + circle_radius;
	int circle_ry = circle_center_y;

	irr::core::vector2di mouse_pos(px, py);


	switch(collision_physics_obj.shape_type)
	{
		case SPRITE_SHAPE_BOX:
		{
			if(mouse_state.LeftIsDown())
			{
				bool init_click = false;

				if(!(middle_drag_init||left_drag_init||right_drag_init))
				{

					if( px >= 0 && px < pw && py >= 0 && py < ph )
					{
						left_drag_init = true;
						this->SetFocusFromKbd();
						init_click = true;

						drag_start = wxPoint(px, py);
					}
				}
				else if(left_drag_init)
				{
					if( px >= 0 && px < pw && py >= 0 && py < ph )
					{
						this->SetFocusFromKbd();

						setColor(rgb(255,255,255));
						drawRect(drag_start.x, drag_start.y, px-drag_start.x, py-drag_start.y);

						float ul_distance = mouse_pos.getDistanceFrom(irr::core::vector2di(box_x, box_y)); //need to factor in offset and box size
						float ll_distance = mouse_pos.getDistanceFrom(irr::core::vector2di(box_x, box_y+box_h));
						float ur_distance = mouse_pos.getDistanceFrom(irr::core::vector2di(box_x+box_w, box_y));
						float lr_distance = mouse_pos.getDistanceFrom(irr::core::vector2di(box_x+box_w, box_y+box_h));

						int select_tolerance = 1;

						collision_boxShapeSelect_ul = false;
						collision_boxShapeSelect_ll = false;
						collision_boxShapeSelect_ur = false;
						collision_boxShapeSelect_lr = false;

						if( ( (box_x >= drag_start.x && box_x <= px) || (box_x >= px && box_x <= drag_start.x) ) &&
							( (box_y >= drag_start.y && box_y <= py) || (box_y >= py && box_y <= drag_start.y) ) )
							collision_boxShapeSelect_ul = true;

						if( ( (box_x >= drag_start.x && box_x <= px) || (box_x >= px && box_x <= drag_start.x) ) &&
							( ((box_y+box_h) >= drag_start.y && (box_y+box_h) <= py) || ((box_y+box_h) >= py && (box_y+box_h) <= drag_start.y) ) )
							collision_boxShapeSelect_ll = true;

						if( ( ((box_x+box_w) >= drag_start.x && (box_x+box_w) <= px) || ((box_x+box_w) >= px && (box_x+box_w) <= drag_start.x) ) &&
							( (box_y >= drag_start.y && box_y <= py) || (box_y >= py && box_y <= drag_start.y) ) )
							collision_boxShapeSelect_ur = true;

						if( ( ((box_x+box_w) >= drag_start.x && (box_x+box_w) <= px) || ((box_x+box_w) >= px && (box_x+box_w) <= drag_start.x) ) &&
							( ((box_y+box_h) >= drag_start.y && (box_y+box_h) <= py) || ((box_y+box_h) >= py && (box_y+box_h) <= drag_start.y) ) )
							collision_boxShapeSelect_lr = true;

						if((collision_boxShapeSelect_ul || collision_boxShapeSelect_ll || collision_boxShapeSelect_ur || collision_boxShapeSelect_lr) &&
						 (!(collision_boxShapeSelect_ul && collision_boxShapeSelect_ll && collision_boxShapeSelect_ur && collision_boxShapeSelect_lr)))
						{
							bool ul = collision_boxShapeSelect_ul;
							bool ll = collision_boxShapeSelect_ll;
							bool ur = collision_boxShapeSelect_ur;
							bool lr = collision_boxShapeSelect_lr;

							collision_boxShapeSelect_ul = false;
							collision_boxShapeSelect_ll = false;
							collision_boxShapeSelect_ur = false;
							collision_boxShapeSelect_lr = false;

							float min_dist = ul ? ul_distance : 99999;
							min_dist = ll ? (ll_distance < min_dist ? ll_distance : min_dist) : min_dist;
							min_dist = ur ? (ur_distance < min_dist ? ur_distance : min_dist) : min_dist;
							min_dist = lr ? (lr_distance < min_dist ? lr_distance : min_dist) : min_dist;

							if(min_dist == ul_distance && ul)
								collision_boxShapeSelect_ul = true;
							else if(min_dist == ll_distance && ll)
								collision_boxShapeSelect_ll = true;
							else if(min_dist == ur_distance && ur)
								collision_boxShapeSelect_ur = true;
							else if(min_dist == lr_distance && lr)
								collision_boxShapeSelect_lr = true;
						}

					}
				}
			}
		}
		break;

		case SPRITE_SHAPE_CIRCLE:
		{
			if(mouse_state.LeftIsDown())
			{
				bool init_click = false;

				if(!(middle_drag_init||left_drag_init||right_drag_init))
				{

					if( px >= 0 && px < pw && py >= 0 && py < ph )
					{
						left_drag_init = true;
						this->SetFocusFromKbd();
						init_click = true;

						drag_start = wxPoint(px, py);
					}
				}
				else if(left_drag_init)
				{
					if( px >= 0 && px < pw && py >= 0 && py < ph )
					{
						this->SetFocusFromKbd();

						setColor(rgb(255,255,255));
						drawRect(drag_start.x, drag_start.y, px-drag_start.x, py-drag_start.y);

						float u_distance = mouse_pos.getDistanceFrom(irr::core::vector2di(circle_ux, circle_uy)); //need to factor in offset and box size
						float d_distance = mouse_pos.getDistanceFrom(irr::core::vector2di(circle_dx, circle_dy));
						float l_distance = mouse_pos.getDistanceFrom(irr::core::vector2di(circle_lx, circle_ly));
						float r_distance = mouse_pos.getDistanceFrom(irr::core::vector2di(circle_rx, circle_ry));

						collision_circleShapeSelect_u = false;
						collision_circleShapeSelect_d = false;
						collision_circleShapeSelect_l = false;
						collision_circleShapeSelect_r = false;

						if( ( (circle_ux >= drag_start.x && circle_ux <= px) || (circle_ux >= px && circle_ux <= drag_start.x) ) &&
							( (circle_uy >= drag_start.y && circle_uy <= py) || (circle_uy >= py && circle_uy <= drag_start.y) ) )
							collision_circleShapeSelect_u = true;

						if( ( (circle_dx >= drag_start.x && circle_dx <= px) || (circle_dx >= px && circle_dx <= drag_start.x) ) &&
							( (circle_dy >= drag_start.y && circle_dy <= py) || (circle_dy >= py && circle_dy <= drag_start.y) ) )
							collision_circleShapeSelect_d = true;

						if( ( (circle_lx >= drag_start.x && circle_lx <= px) || (circle_lx >= px && circle_lx <= drag_start.x) ) &&
							( (circle_ly >= drag_start.y && circle_ly <= py) || (circle_ly >= py && circle_ly <= drag_start.y) ) )
							collision_circleShapeSelect_l = true;

						if( ( (circle_rx >= drag_start.x && circle_rx <= px) || (circle_rx >= px && circle_rx <= drag_start.x) ) &&
							( (circle_ry >= drag_start.y && circle_ry <= py) || (circle_ry >= py && circle_ry <= drag_start.y) ) )
							collision_circleShapeSelect_r = true;

						if((collision_circleShapeSelect_u || collision_circleShapeSelect_d || collision_circleShapeSelect_l || collision_circleShapeSelect_r) &&
						 (!(collision_circleShapeSelect_u && collision_circleShapeSelect_d && collision_circleShapeSelect_l && collision_circleShapeSelect_r)))
						{
							bool u = collision_circleShapeSelect_u;
							bool d = collision_circleShapeSelect_d;
							bool l = collision_circleShapeSelect_l;
							bool r = collision_circleShapeSelect_r;

							collision_circleShapeSelect_u = false;
							collision_circleShapeSelect_d = false;
							collision_circleShapeSelect_l = false;
							collision_circleShapeSelect_r = false;

							float min_dist = u ? u_distance : 99999;
							min_dist = d ? (d_distance < min_dist ? d_distance : min_dist) : min_dist;
							min_dist = l ? (l_distance < min_dist ? l_distance : min_dist) : min_dist;
							min_dist = r ? (r_distance < min_dist ? r_distance : min_dist) : min_dist;

							if(min_dist == u_distance && u)
								collision_circleShapeSelect_u = true;
							else if(min_dist == d_distance && d)
								collision_circleShapeSelect_d = true;
							else if(min_dist == l_distance && l)
								collision_circleShapeSelect_l = true;
							else if(min_dist == r_distance && r)
								collision_circleShapeSelect_r = true;
						}

					}
				}
			}
		}
		break;

		case SPRITE_SHAPE_POLYGON:
		{
			if(mouse_state.LeftIsDown())
			{
				bool init_click = false;

				if(!(middle_drag_init||left_drag_init||right_drag_init))
				{

					if( px >= 0 && px < pw && py >= 0 && py < ph )
					{
						left_drag_init = true;
						this->SetFocusFromKbd();
						init_click = true;

						drag_start = wxPoint(px, py);
					}
				}
				else if(left_drag_init)
				{
					if( px >= 0 && px < pw && py >= 0 && py < ph )
					{
						this->SetFocusFromKbd();

						setColor(rgb(255,255,255));
						drawRect(drag_start.x, drag_start.y, px-drag_start.x, py-drag_start.y);

						collision_selected_points.clear();

						for(int i = 0; i < collision_physics_obj.points.size(); i++)
						{
							int point_x = img_x + collision_physics_obj.points[i].X * img_scale;
							int point_y = img_y + collision_physics_obj.points[i].Y * img_scale;
							float pt_distance = mouse_pos.getDistanceFrom(irr::core::vector2di(point_x, point_y)); //need to factor in offset and box size

							if( ( (point_x >= drag_start.x && point_x <= px) || (point_x >= px && point_x <= drag_start.x) ) &&
								( (point_y >= drag_start.y && point_y <= py) || (point_y >= py && point_y <= drag_start.y) ) )
							{
								if(!collisionPointIsSelected(i))
								{
									collision_selected_points.push_back(i);
								}
							}
						}
					}
				}
			}
		}
		break;
	}
}

void wxIrrlicht::collisionEdit_move()
{
	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();

	int img_scale = ph/current_frame_height;
	int img_w = current_frame_width*img_scale;
	int img_h = current_frame_height*img_scale;
	int img_x = pw/2 - img_w/2;
	int img_y = ph/2 - img_h/2;

	irr::core::vector2di mouse_pos(px, py);

	switch(collision_physics_obj.shape_type)
	{
		case SPRITE_SHAPE_BOX:
		{
			if(mouse_state.LeftIsDown())
			{
				bool init_click = false;

				if(!(middle_drag_init||left_drag_init||right_drag_init))
				{

					if( px >= 0 && px < pw && py >= 0 && py < ph )
					{
						left_drag_init = true;
						this->SetFocusFromKbd();
						init_click = true;

						drag_start = wxPoint(px, py);
						collision_move_start_offset.set(collision_physics_obj.offset_x, collision_physics_obj.offset_y);
						collision_move_start_size.set(collision_physics_obj.box_width, collision_physics_obj.box_height);
					}
				}
				else if(left_drag_init)
				{
					if( px >= 0 && px < pw && py >= 0 && py < ph )
					{
						this->SetFocusFromKbd();

						if(collision_boxShapeSelect_ul && collision_boxShapeSelect_ll && collision_boxShapeSelect_ur && collision_boxShapeSelect_lr)
						{
							collision_physics_obj.offset_x = collision_move_start_offset.X + (px - drag_start.x)/img_scale;
							collision_physics_obj.offset_y = collision_move_start_offset.Y + (py - drag_start.y)/img_scale;
						}
						else if(collision_boxShapeSelect_ul)
						{
							collision_physics_obj.offset_x = collision_move_start_offset.X + (px - drag_start.x)/img_scale;
							collision_physics_obj.offset_y = collision_move_start_offset.Y + (py - drag_start.y)/img_scale;

							collision_physics_obj.box_width = collision_move_start_size.X - (px - drag_start.x)/img_scale;
							collision_physics_obj.box_height = collision_move_start_size.Y - (py - drag_start.y)/img_scale;
						}
						else if(collision_boxShapeSelect_ll)
						{
							collision_physics_obj.offset_x = collision_move_start_offset.X + (px - drag_start.x)/img_scale;
							//collision_physics_obj.offset_y = collision_move_start_offset.Y + (py - drag_start.y)/img_scale;

							collision_physics_obj.box_width = collision_move_start_size.X - (px - drag_start.x)/img_scale;
							collision_physics_obj.box_height = collision_move_start_size.Y + (py - drag_start.y)/img_scale;
						}
						else if(collision_boxShapeSelect_ur)
						{
							//collision_physics_obj.offset_x = collision_move_start_offset.X + (px - drag_start.x)/img_scale;
							collision_physics_obj.offset_y = collision_move_start_offset.Y + (py - drag_start.y)/img_scale;

							collision_physics_obj.box_width = collision_move_start_size.X + (px - drag_start.x)/img_scale;
							collision_physics_obj.box_height = collision_move_start_size.Y - (py - drag_start.y)/img_scale;
						}
						else if(collision_boxShapeSelect_lr)
						{
							//collision_physics_obj.offset_x = collision_move_start_offset.X + (px - drag_start.x)/img_scale;
							//collision_physics_obj.offset_y = collision_move_start_offset.Y + (py - drag_start.y)/img_scale;

							collision_physics_obj.box_width = collision_move_start_size.X + (px - drag_start.x)/img_scale;
							collision_physics_obj.box_height = collision_move_start_size.Y + (py - drag_start.y)/img_scale;
						}

						collision_object_modified = true;
						parent_window->UpdateWindowUI();
					}
				}
			}
		}
		break;

		case SPRITE_SHAPE_CIRCLE:
		{
			if(mouse_state.LeftIsDown())
			{
				bool init_click = false;

				if(!(middle_drag_init||left_drag_init||right_drag_init))
				{

					if( px >= 0 && px < pw && py >= 0 && py < ph )
					{
						left_drag_init = true;
						this->SetFocusFromKbd();
						init_click = true;

						drag_start = wxPoint(px, py);
						collision_move_start_offset.set(collision_physics_obj.offset_x, collision_physics_obj.offset_y);
						collision_move_start_radius = collision_physics_obj.radius;
					}
				}
				else if(left_drag_init)
				{
					if( px >= 0 && px < pw && py >= 0 && py < ph )
					{
						this->SetFocusFromKbd();

						if(collision_circleShapeSelect_u && collision_circleShapeSelect_d && collision_circleShapeSelect_l && collision_circleShapeSelect_r)
						{
							collision_physics_obj.offset_x = collision_move_start_offset.X + (px - drag_start.x)/img_scale;
							collision_physics_obj.offset_y = collision_move_start_offset.Y + (py - drag_start.y)/img_scale;
						}
						else if(collision_circleShapeSelect_u)
						{
							collision_physics_obj.radius = collision_move_start_radius - (py - drag_start.y)/img_scale;
						}
						else if(collision_circleShapeSelect_d)
						{
							collision_physics_obj.radius = collision_move_start_radius + (py - drag_start.y)/img_scale;
						}
						else if(collision_circleShapeSelect_l)
						{
							collision_physics_obj.radius = collision_move_start_radius - (px - drag_start.x)/img_scale;
						}
						else if(collision_circleShapeSelect_r)
						{
							collision_physics_obj.radius = collision_move_start_radius + (px - drag_start.x)/img_scale;
						}

						collision_object_modified = true;
						parent_window->UpdateWindowUI();
					}
				}
			}
		}
		break;

		case SPRITE_SHAPE_POLYGON:
		{
			if(mouse_state.LeftIsDown())
			{
				bool init_click = false;

				if(!(middle_drag_init||left_drag_init||right_drag_init))
				{

					if( px >= 0 && px < pw && py >= 0 && py < ph )
					{
						left_drag_init = true;
						this->SetFocusFromKbd();
						init_click = true;

						drag_start = wxPoint(px, py);
						collision_move_start_offset.set(collision_physics_obj.offset_x, collision_physics_obj.offset_y);
						collision_move_start_points.clear();

						for(int i = 0; i < collision_physics_obj.points.size(); i++)
						{
							collision_move_start_points.push_back(collision_physics_obj.points[i]);
						}
					}
				}
				else if(left_drag_init)
				{
					if( px >= 0 && px < pw && py >= 0 && py < ph )
					{
						this->SetFocusFromKbd();

						int mouse_move_x = (px - drag_start.x)/img_scale;
						int mouse_move_y = (py - drag_start.y)/img_scale;

						for(int i = 0; i < collision_selected_points.size(); i++)
						{
							int pt_index = collision_selected_points[i];
							collision_physics_obj.points[pt_index].X = collision_move_start_points[pt_index].X + mouse_move_x;
							collision_physics_obj.points[pt_index].Y = collision_move_start_points[pt_index].Y + mouse_move_y;
						}

						collision_object_modified = true;
						parent_window->UpdateWindowUI();
					}
				}
			}
		}
		break;
	}
}

void wxIrrlicht::collisionEdit_draw()
{
	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();

	int img_scale = ph/current_frame_height;
	int img_w = current_frame_width*img_scale;
	int img_h = current_frame_height*img_scale;
	int img_x = pw/2 - img_w/2;
	int img_y = ph/2 - img_h/2;

	irr::core::vector2di mouse_pos(px, py);

	switch(collision_physics_obj.shape_type)
	{
		case SPRITE_SHAPE_POLYGON:
		{
			if(mouse_state.LeftIsDown())
			{
				bool init_click = false;

				if(!(middle_drag_init||left_drag_init||right_drag_init))
				{

					if( px >= 0 && px < pw && py >= 0 && py < ph )
					{
						left_drag_init = true;
						this->SetFocusFromKbd();
						init_click = true;

						if(!collision_poly_draw_flag)
						{
							collision_selected_points.clear();

							collision_physics_obj.points.clear();

							collision_poly_draw_flag = true;
						}

						collision_physics_obj.points.push_back(irr::core::vector2di((px-img_x)/img_scale, (py-img_y)/img_scale));

						collision_object_modified = true;
						parent_window->UpdateWindowUI();
					}
				}
			}
			else if(mouse_state.RightIsDown() && (!right_drag_init))
			{
				right_drag_init = true;
				//must be atleast a triangle
				if(collision_physics_obj.points.size() < 3)
				{
					//collision_physics_obj.points.push_back(collision_physics_obj.points[0]);
					for(int i = collision_physics_obj.points.size(); i < 3; i++)
					{
						collision_physics_obj.points.push_back(irr::core::vector2di(0, 0));
					}
				}

				collision_poly_draw_flag = false;

				collision_object_modified = true;
				parent_window->Refresh();
			}
		}
		break;
	}
}

void wxIrrlicht::UpdateSpriteCollision()
{
	if(clear_flag)
	{
		setActiveCanvas(collision_canvas);
		clearCanvas();
		clear_flag = false;
		return;
	}

	if(current_sheet_image < 0 || current_sheet_image >= image.size())
		return;

	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();

	if(stage_window_isActive)
	{
		this->SetFocusFromKbd();
	}

	if( (!mouse_state.LeftIsDown()) && left_drag_init )
	{
		left_drag_init = false;
	}

	if( (!mouse_state.RightIsDown()) && right_drag_init )
	{
		right_drag_init = false;
	}

	setActiveCanvas(collision_canvas);
	clearCanvas();

	int img_scale = ph/current_frame_height;
	int img_w = current_frame_width*img_scale;
	int img_h = current_frame_height*img_scale;
	int img_x = pw/2 - img_w/2;
	int img_y = ph/2 - img_h/2;

	setColor(rgb(90,90,90));
	drawRectFill(0, 0, pw, ph);
	setColor(rgb(120, 120, 120));
	drawRectFill(img_x-1, img_y-1, img_w+2, img_h+2);

	drawImage_BlitEx(current_sheet_image, img_x, img_y, img_w, img_h, 0, 0, current_frame_width, current_frame_height);

	//Tool operations
	switch(collision_tool)
	{
		case COLLISION_TOOL_SELECT:
		{
			collisionEdit_select();
		}
		break;

		case COLLISION_TOOL_BOX_SELECT:
		{
			collisionEdit_boxSelect();
		}
		break;

		case COLLISION_TOOL_MOVE:
		{
			collisionEdit_move();
		}
		break;

		case COLLISION_TOOL_DRAW:
		{
			collisionEdit_draw();
		}
		break;
	}

	//Render Collision Shape
	int ipx = 3; //img_scale;

	switch(collision_physics_obj.shape_type)
	{
		case SPRITE_SHAPE_BOX:
		{
			int box_x = img_x + (collision_physics_obj.offset_x*img_scale);
			int box_y = img_y + (collision_physics_obj.offset_y*img_scale);
			int box_w = collision_physics_obj.box_width * img_scale;
			int box_h = collision_physics_obj.box_height * img_scale;

			setColor(rgb(0,0,0));
			drawRect(box_x, box_y, box_w, box_h);

			setColor( collision_boxShapeSelect_ul ? rgb(0,255, 0) : rgb(0, 0, 0) );
			drawRectFill(box_x-ipx, box_y-ipx, ipx*2, ipx*2);

			setColor( collision_boxShapeSelect_ll ? rgb(0,255, 0) : rgb(0, 0, 0) );
			drawRectFill(box_x-ipx, (box_y+box_h)-ipx, ipx*2, ipx*2);

			setColor( collision_boxShapeSelect_ur ? rgb(0,255, 0) : rgb(0, 0, 0) );
			drawRectFill((box_x+box_w)-ipx, box_y-ipx, ipx*2, ipx*2);

			setColor( collision_boxShapeSelect_lr ? rgb(0,255, 0) : rgb(0, 0, 0) );
			drawRectFill((box_x+box_w)-ipx, (box_y+box_h)-ipx, ipx*2, ipx*2);
		}
		break;

		case SPRITE_SHAPE_CIRCLE:
		{
			int circle_radius = (((int)collision_physics_obj.radius)*img_scale);
			int circle_x = img_x + (img_w/2) + (collision_physics_obj.offset_x*img_scale);
			int circle_y = img_y + (img_h/2) + (collision_physics_obj.offset_y*img_scale);

			int pt_u_x = circle_x;
			int pt_u_y = circle_y-circle_radius;

			int pt_d_x = circle_x;
			int pt_d_y = circle_y+circle_radius;

			int pt_l_x = circle_x-circle_radius;
			int pt_l_y = circle_y;

			int pt_r_x = circle_x+circle_radius;
			int pt_r_y = circle_y;

			setColor(rgb(0,0,0));
			drawCircle(circle_x, circle_y, circle_radius);

			setColor( collision_circleShapeSelect_u ? rgb(0,255, 0) : rgb(0, 0, 0) );
			drawRectFill(pt_u_x-ipx, pt_u_y-ipx, ipx*2, ipx*2);

			setColor( collision_circleShapeSelect_d ? rgb(0,255, 0) : rgb(0, 0, 0) );
			drawRectFill(pt_d_x-ipx, pt_d_y-ipx, ipx*2, ipx*2);

			setColor( collision_circleShapeSelect_l ? rgb(0,255, 0) : rgb(0, 0, 0) );
			drawRectFill(pt_l_x-ipx, pt_l_y-ipx, ipx*2, ipx*2);

			setColor( collision_circleShapeSelect_r ? rgb(0,255, 0) : rgb(0, 0, 0) );
			drawRectFill(pt_r_x-ipx, pt_r_y-ipx, ipx*2, ipx*2);
		}
		break;

		case SPRITE_SHAPE_POLYGON:
		{
			if(collision_physics_obj.points.size() == 0)
				break;

			int prev_x = 0;
			int prev_y = 0;

			for(int i = 0; i < collision_physics_obj.points.size(); i++)
			{
				int pt_x = img_x + (collision_physics_obj.points[i].X*img_scale);
				int pt_y = img_y + (collision_physics_obj.points[i].Y*img_scale);

				setColor(rgb(0,0,0));

				if(i > 0)
				{
					drawLine(prev_x, prev_y, pt_x, pt_y);
				}

				setColor(rgb(0,0,0));
				drawRectFill(pt_x-ipx, pt_y-ipx, ipx*2, ipx*2);

				prev_x = pt_x;
				prev_y = pt_y;
			}

			if(collision_poly_draw_flag)
			{
				drawLine(prev_x, prev_y, px, py);
				drawRectFill(px-ipx, py-ipx, ipx*2, ipx*2);
			}
			else if(collision_physics_obj.points.size() >= 3)
			{
				int num_points = collision_physics_obj.points.size();
				int pt_x = img_x + collision_physics_obj.points[0].X*img_scale;
				int pt_y = img_y + collision_physics_obj.points[0].Y*img_scale;
				drawLine(prev_x, prev_y, pt_x, pt_y);
				drawRectFill(pt_x-ipx, pt_y-ipx, ipx*2, ipx*2);
			}

			//draw Selected
			for(int i = 0; i < collision_selected_points.size(); i++)
			{
				int pt_index = collision_selected_points[i];
				int pt_x = img_x + (collision_physics_obj.points[pt_index].X*img_scale);
				int pt_y = img_y + (collision_physics_obj.points[pt_index].Y*img_scale);

				setColor(rgb(0,255,0));
				drawRectFill(pt_x-ipx, pt_y-ipx, ipx*2, ipx*2);
			}
		}
		break;
	}

	//std::cout << "DRAW: " << ph << ", " << current_frame_height << std::endl;
}

void wxIrrlicht::UpdateTileAnimationSheet()
{
	if(clear_flag)
	{
		setActiveCanvas(sheet_canvas);
		clearCanvas();
		clear_flag = false;
		return;
	}

	if(current_sheet_image < 0 || current_sheet_image >= image.size())
		return;

	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();

	if(stage_window_isActive)
	{
		this->SetFocusFromKbd();
	}


	setActiveCanvas(sheet_canvas);
	clearCanvas();

	if(VIEW_KEY_W)
	{
		scroll_offset_y -= scroll_speed;
	}

	if(VIEW_KEY_A)
	{
		scroll_offset_x -= scroll_speed;
	}

	if(VIEW_KEY_S)
	{
		scroll_offset_y += scroll_speed;
	}

	if(VIEW_KEY_D)
	{
		scroll_offset_x += scroll_speed;
	}

	int bx = ( (px+scroll_offset_x) / current_frame_width) *  current_frame_width;
	int by = ( (py+scroll_offset_y) / current_frame_height) *  current_frame_height;

	int off_x_i = (int)scroll_offset_x;
	int off_y_i = (int)scroll_offset_y;

	int select_x = bx - off_x_i;
	int select_y = by - off_y_i;

	int img_x = -scroll_offset_x;
	int img_y = -scroll_offset_y;
	int img_w = 0;
	int img_h = 0;

	if(imageExists(current_sheet_image))
	{
		getImageSizeI(current_sheet_image, &img_w, &img_h);

		//m_pDriver->draw2DImage(image[current_sheet_image].image, irr::core::vector2di(0,0),);
		drawImage_BlitEx_SW(current_sheet_image, img_x, img_y, (int)img_w, (int)img_h, 0, 0, (int)img_w, (int)img_h);
		//drawImage_Rotozoom(current_sheet_image, 0, 0, 0, 1, 1);
	}

	if(px >= img_x && px < (img_x+img_w) && py >= img_y && py < (img_y+img_h))
	{
		setColor(rgb(255, 0, 0));
		drawRect(select_x, select_y, current_frame_width, current_frame_height);
	}

	if(tileEdit_selected_sheet_frame >= 0)
	{
		int selected_tile_x = current_frame_width * (tileEdit_selected_sheet_frame % (img_w/current_frame_width)) - scroll_offset_x;
		int selected_tile_y = current_frame_height * (tileEdit_selected_sheet_frame / (img_w/current_frame_height)) - scroll_offset_y;

		setColor(rgb(255, 255, 255));
		drawRect(selected_tile_x, selected_tile_y, current_frame_width, current_frame_height);
	}


	if(mouse_state.LeftIsDown())
	{
        bool init_click = false;

		if(!(middle_drag_init||left_drag_init||right_drag_init))
		{

			if( px >= 0 && px < pw && py >= 0 && py < ph )
			{
				int fx = select_x + scroll_offset_x;
				int fy = select_y + scroll_offset_y;
				int fw = img_w;
				int fh = img_h;

				if(stage_window_isActive)
				{
					if(px >= img_x && px < (img_x+img_w) && py >= img_y && py < (img_y+img_h))
						selected_frame = (fy/current_frame_height) * (fw/current_frame_width) + (fx/current_frame_width);
					else
						selected_frame = -1;
				}
				else
					selected_frame = -1;

				if(selected_frame >= 0)
				{
					tileEdit_selected_sheet_frame = selected_frame;
					tileEdit_Sheet_Update = true;
					parent_window->UpdateWindowUI();
				}

				//std::cout << "TEST: " << selected_frame << std::endl;

				left_drag_init = true;
			}
		}
	}
	else if( (!mouse_state.LeftIsDown()) && left_drag_init )
	{
		//SHOW_CURSOR;
		//this->ReleaseMouse();
		left_drag_init = false;
		//wxMessageBox(_("RELEASE"));
		return;
	}
}

void wxIrrlicht::UpdateTileAnimationFrame()
{
	if(clear_flag)
	{
		setActiveCanvas(frame_canvas);
		clearCanvas();
		clear_flag = false;
		return;
	}

	if(current_sheet_image < 0 || current_sheet_image >= image.size())
		return;

	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();

	if( px < 0 || px >= pw || py < 0 || py >= ph)
		stage_window_isActive = false;
	else
		stage_window_isActive = true;


	setActiveCanvas(frame_canvas);
	clearCanvas();

	setColor(rgb(70,70,70));
	drawRectFill(0,64,pw,30);

	int bx = (px / current_frame_width) *  current_frame_width;
	int by = (py / current_frame_height) *  current_frame_height;

	double d_sheet_w = 0;
	double d_sheet_h = 0;

	int sheet_w = 0;
	int sheet_h = 0;

	if(imageExists(current_sheet_image))
	{
		//getImageSize(current_sheet_image, &d_sheet_w, &d_sheet_h);
		sheet_w = sheet_width; // (int) d_sheet_w;
		sheet_h = sheet_height; //(int) d_sheet_h;
	}

	int num_frames = 0;

	//draw borders
	if(tilesetExists(tileEdit_selected_tileset))
	{
		//std::cout << "FRAME TSET exists: " << tileEdit_selected_tile << std::endl;
		//wxMessageBox(_("ANIMATION: ") + wxString::Format(_("%i"), sprite[spriteEdit_selected_sprite].animation.size()));
		if(tileEdit_selected_tile >= 0 &&  tileEdit_selected_tile < tileset[tileEdit_selected_tileset].tiles.size())
		{
			num_frames = getTileAnimationLength(tileEdit_selected_tileset, tileEdit_selected_tile);

			//std::cout << "FRAME TILE exists: " << num_frames << "; " << (int)(imageExists(current_sheet_image)) << std::endl;

			int all_frame_width = num_frames*64;
			if( (all_frame_width - scroll_offset_x) <= 64)
				scroll_offset_x = all_frame_width - 64;

			if( scroll_offset_x < 0)
				scroll_offset_x = 0;

			setColor(rgb(30, 30, 30));
			if(imageExists(current_sheet_image))
			{
				irr_SetFont(1);
				for(int i = 0; i < num_frames; i++)
				{
					int sheet_frame = getTileAnimationFrame(tileEdit_selected_tileset, tileEdit_selected_tile, i);
					int fx = i*64-scroll_offset_x;
					if(sheet_frame >= 0 && fx >= 0 && fx < pw)
					{
						int frames_per_row = sheet_w / current_frame_width;
						int sheet_x = (sheet_frame % frames_per_row) * current_frame_width;
						int sheet_y = (sheet_frame / frames_per_row) * current_frame_height;

						if(mouse_state.RightIsDown())
						{
							//std::cout << "DEBUG: ani_frame=" << i << "   sheet_frame=" << sheet_frame << "   src=(" << sheet_x << ", " << sheet_y << ") ";
							//std::cout << "sheet=(" << sheet_w << ", " << frames_per_row << ") frame=(" << current_frame_width << ", " << current_frame_height << ") " << std::endl;
						}

						drawImage_BlitEx_SW(current_sheet_image, fx, 0, 64, 64, sheet_x, sheet_y, current_frame_width, current_frame_height);
					}
					setColor(rgb(30, 30, 30));
					drawRect(fx, 0, 64, 63);
					wxString f_num_txt = wxString::Format(_("%i"), i);
					setColor(rgb(0,0,0));
					drawRectFill(fx, 0, 20, 20);
					irr_DrawText(f_num_txt.ToStdString(), fx+1, 1, irr::video::SColor(255, 255, 255, 255), 1);

					setColor(rgb(255,255,255));
					if(selected_frame == i)
					{
						drawRect(fx, 0, 63, 63);
					}
				}
			}
		}
	}

	if( px >= 0 && px < pw && py >= 0 && py < ph )
	{

		double off_x = 0;
		double off_y = 0;

		getCanvasOffset(frame_canvas, &off_x, &off_y);

		int off_x_i = (int)off_x;
		int off_y_i = (int)off_y;

		int bx = (px / 64) *  64;
		int by = (py / 64) *  64;

		setColor(rgb(255, 0, 0));
		drawRect(bx - off_x_i, 0, 64, 63);
	}


	if(mouse_state.LeftIsDown())
	{
        bool init_click = false;

		if(!(middle_drag_init||left_drag_init||right_drag_init))
		{

			if( px >= 0 && px < pw && py >= 0 && py < ph )
			{
				left_drag_init = true;

				selected_frame = (scroll_offset_x/64) + (px/64);
				tileEdit_selected_frame_frame = selected_frame;

				parent_window->UpdateWindowUI();

				//std::cout << "SELECTED: " << selected_frame << std::endl;
			}
		}
	}
	else if( (!mouse_state.LeftIsDown()) && left_drag_init )
	{
		//SHOW_CURSOR;
		//this->ReleaseMouse();
		left_drag_init = false;
		//wxMessageBox(_("RELEASE"));
		return;
	}
}

void wxIrrlicht::UpdateTileAnimationPreview()
{
	if(clear_flag)
	{
		setActiveCanvas(preview_canvas);
		clearCanvas();
		clear_flag = false;
		return;
	}

	if(tileEdit_preview_tilemap < 0 || tileEdit_preview_tilemap >= tilemap.size())
		return;

	setActiveCanvas(preview_canvas);
	clearCanvas();

	if(!tileEdit_play_preview)
	{
		return;
	}

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();

	drawTileMap(tileEdit_preview_tilemap, 0, 0, pw, ph, 0, 0);
}

void wxIrrlicht::UpdateTileMask()
{
	if(clear_flag)
	{
		setActiveCanvas(sheet_canvas);
		clearCanvas();
		clear_flag = false;
		return;
	}

	if(current_sheet_image < 0 || current_sheet_image >= image.size())
		return;

	if(!tileEdit_tileMask.active)
		return;

	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();

	if(stage_window_isActive)
	{
		this->SetFocusFromKbd();
	}


	setActiveCanvas(sheet_canvas);
	clearCanvas();

	if(VIEW_KEY_W)
	{
		scroll_offset_y -= scroll_speed;
	}

	if(VIEW_KEY_A)
	{
		scroll_offset_x -= scroll_speed;
	}

	if(VIEW_KEY_S)
	{
		scroll_offset_y += scroll_speed;
	}

	if(VIEW_KEY_D)
	{
		scroll_offset_x += scroll_speed;
	}

	int bx = ( (px+scroll_offset_x) / current_frame_width) *  current_frame_width;
	int by = ( (py+scroll_offset_y) / current_frame_height) *  current_frame_height;

	int off_x_i = (int)scroll_offset_x;
	int off_y_i = (int)scroll_offset_y;

	int select_x = bx - off_x_i;
	int select_y = by - off_y_i;

	int img_x = -scroll_offset_x;
	int img_y = -scroll_offset_y;
	int img_w = 0;
	int img_h = 0;

	if(imageExists(current_sheet_image))
	{
		getImageSizeI(current_sheet_image, &img_w, &img_h);

		//m_pDriver->draw2DImage(image[current_sheet_image].image, irr::core::vector2di(0,0),);
		drawImage_BlitEx_SW(current_sheet_image, img_x, img_y, (int)img_w, (int)img_h, 0, 0, (int)img_w, (int)img_h);
		//drawImage_Rotozoom(current_sheet_image, 0, 0, 0, 1, 1);
	}

	if(px >= img_x && px < (img_x+img_w) && py >= img_y && py < (img_y+img_h))
	{
		setColor(rgb(255, 0, 0));
		drawRect(select_x, select_y, current_frame_width, current_frame_height);
	}

	for(int i = 0; i < tileEdit_tileMask.tiles.size(); i++)
	{
		if(tileEdit_tileMask.tiles[i])
		{
			int selected_tile_x = current_frame_width * (i % (img_w/current_frame_width)) - scroll_offset_x;
			int selected_tile_y = current_frame_height * (i / (img_w/current_frame_height)) - scroll_offset_y;

			setColor(rgb(150, 150, 150));
			drawRect(selected_tile_x, selected_tile_y, current_frame_width, current_frame_height);
			drawCircleFill(selected_tile_x+(current_frame_width/2),
						   selected_tile_y+(current_frame_height/2),
						   3);
		}
	}


	if(mouse_state.LeftIsDown())
	{
        bool init_click = false;

		if(!(middle_drag_init||left_drag_init||right_drag_init))
		{

			if( px >= 0 && px < pw && py >= 0 && py < ph )
			{
				int fx = select_x + scroll_offset_x;
				int fy = select_y + scroll_offset_y;
				int fw = img_w;
				int fh = img_h;

				if(stage_window_isActive)
				{
					if(px >= img_x && px < (img_x+img_w) && py >= img_y && py < (img_y+img_h))
						selected_frame = (fy/current_frame_height) * (fw/current_frame_width) + (fx/current_frame_width);
					else
						selected_frame = -1;
				}
				else
					selected_frame = -1;

				if(selected_frame >= 0)
				{
					tileEdit_selected_sheet_frame = selected_frame;
					tileEdit_mask_set = true;
					tileEdit_Sheet_Update = true;
					parent_window->UpdateWindowUI();
				}

				//std::cout << "TEST: " << selected_frame << std::endl;

				left_drag_init = true;
			}
		}
	}
	else if( (!mouse_state.LeftIsDown()) && left_drag_init )
	{
		//SHOW_CURSOR;
		//this->ReleaseMouse();
		left_drag_init = false;
		//wxMessageBox(_("RELEASE"));
		return;
	}

	if(mouse_state.RightIsDown())
	{
        bool init_click = false;

		if(!(middle_drag_init||left_drag_init||right_drag_init))
		{

			if( px >= 0 && px < pw && py >= 0 && py < ph )
			{
				int fx = select_x + scroll_offset_x;
				int fy = select_y + scroll_offset_y;
				int fw = img_w;
				int fh = img_h;

				if(stage_window_isActive)
				{
					if(px >= img_x && px < (img_x+img_w) && py >= img_y && py < (img_y+img_h))
						selected_frame = (fy/current_frame_height) * (fw/current_frame_width) + (fx/current_frame_width);
					else
						selected_frame = -1;
				}
				else
					selected_frame = -1;

				if(selected_frame >= 0)
				{
					tileEdit_selected_sheet_frame = selected_frame;
					tileEdit_mask_set = false;
					tileEdit_Sheet_Update = true;
					parent_window->UpdateWindowUI();
				}

				//std::cout << "TEST: " << selected_frame << std::endl;

				right_drag_init = true;
			}
		}
	}
	else if( (!mouse_state.RightIsDown()) && right_drag_init )
	{
		//SHOW_CURSOR;
		//this->ReleaseMouse();
		right_drag_init = false;
		//wxMessageBox(_("RELEASE"));
		return;
	}
}


void wxIrrlicht::StageSheet_SetTileUpdate()
{
	if(!project)
		return;

	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	if(selected_layer < 0 || selected_layer >= project->stages[selected_stage].layers.size())
		return;

	int canvas_index = project->stages[selected_stage].layers[selected_layer].ref_canvas;

	if(canvas_index < 0 || canvas_index >= canvas.size())
		return;

	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();


	setActiveCanvas(canvas_index);
	//clearCanvas();

	float scroll_speed_x = project->getLayerScrollSpeed(selected_stage, selected_layer).X;
	float scroll_speed_y = project->getLayerScrollSpeed(selected_stage, selected_layer).Y;

	int adj_scroll_offset_x = scroll_speed_x * scroll_offset_x;
	int adj_scroll_offset_y = scroll_speed_y * scroll_offset_y;

	int bx = ( (px+adj_scroll_offset_x) / current_frame_width) *  current_frame_width;
	int by = ( (py+adj_scroll_offset_y) / current_frame_height) *  current_frame_height;

	int off_x_i = (int)adj_scroll_offset_x;
	int off_y_i = (int)adj_scroll_offset_y;

	int select_x = bx - off_x_i;
	int select_y = by - off_y_i;

	int img_x = -adj_scroll_offset_x;
	int img_y = -adj_scroll_offset_y;
	int img_w = 0;
	int img_h = 0;

	int tset = project->stages[selected_stage].layers[selected_layer].layer_map.nv_tileset_index;

	if(tset < 0 || tset >= project->tileset.size())
		return;

	int img_id = project->tileset[tset].object.img_id;

	if(img_id < 0 || img_id >= image.size())
		return;

	int num_rows = mapEdit_tile_selection.row.size();
	int num_cols = 0;

	if(num_rows > 0)
		num_cols = mapEdit_tile_selection.row[0].data.size();


	//util_drawTileLayer(selected_layer);

	if(stage_window_isActive && num_cols > 0 && (!mapEdit_lastAction_erase))
	{
		int src_x = 0;
		int src_y = 0;
		int dst_x = 0;
		int dst_y = 0;

		for(int tr = 0; tr < num_rows; tr++)
		{
			for(int tc = 0; tc < num_cols; tc++)
			{
				util_getTileInTileset(tset, mapEdit_tile_selection.row[tr].data[tc], &src_x, &src_y);
				dst_x = select_x + (tc*current_frame_width);
				dst_y = select_y + (tr*current_frame_height);

				drawImage_Blit(img_id, dst_x, dst_y, src_x, src_y, current_frame_width, current_frame_height);
			}
		}

		setColor(rgb(255, 0, 0));
		drawRect(select_x, select_y, num_cols*current_frame_width, num_rows*current_frame_height);

	}

	if(mapEdit_lastAction_erase)
	{
		setColor(rgb(255, 0, 0));
		drawRect(select_x, select_y, current_frame_width, current_frame_height);
	}

	if(!stage_window_isActive)
	{
		left_drag_init = false;
		right_drag_init = false;
		mapEdit_lastAction_erase = false;
		return;
	}


	if(mouse_state.LeftIsDown())
	{
		mapEdit_lastAction_erase = false;
        bool init_click = false;

        int src_x = 0;
		int src_y = 0;
		int dst_x = 0;
		int dst_y = 0;

		for(int tr = 0; tr < num_rows; tr++)
		{
			for(int tc = 0; tc < num_cols; tc++)
			{
				util_getTileInTileset(tset, mapEdit_tile_selection.row[tr].data[tc], &src_x, &src_y);
				dst_x = select_x + (tc*current_frame_width);
				dst_y = select_y + (tr*current_frame_height);

				int tbx = ( (px+adj_scroll_offset_x) / current_frame_width);
				int tby = ( (py+adj_scroll_offset_y) / current_frame_height);

				int tmap_x = tbx + tc;
				int tmap_y = tby + tr;
				if(tmap_y < project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows.size())
				{
					if(tmap_x < project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[tmap_y].tile.size())
					{
						project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[tmap_y].tile[tmap_x] = mapEdit_tile_selection.row[tr].data[tc];
					}
				}
				//drawImage_Blit(img_id, dst_x, dst_y, src_x, src_y, current_frame_width, current_frame_height);
			}
		}


		if(!(middle_drag_init||left_drag_init||right_drag_init))
		{

			if( px >= 0 && px < pw && py >= 0 && py < ph )
			{
				int fx = select_x + scroll_offset_x;
				int fy = select_y + scroll_offset_y;
				int fw = img_w;
				int fh = img_h;

				if(stage_window_isActive)
				{
					if(px >= img_x && px < (img_x+img_w) && py >= img_y && py < (img_y+img_h))
						selected_frame = (fy/current_frame_height) * (fw/current_frame_width) + (fx/current_frame_width);
					else
						selected_frame = -1;
				}
				else
					selected_frame = -1;

				if(selected_frame >= 0)
				{
					//tileEdit_selected_sheet_frame = selected_frame;
					//tileEdit_mask_set = true;
					//tileEdit_Sheet_Update = true;
					//parent_window->UpdateWindowUI();
				}

				//std::cout << "TEST: " << selected_layer << std::endl;

				left_drag_init = true;
			}
		}
	}
	else if( (!mouse_state.LeftIsDown()) && left_drag_init )
	{
		//SHOW_CURSOR;
		//this->ReleaseMouse();
		left_drag_init = false;
		//wxMessageBox(_("RELEASE"));
		return;
	}

	if(mouse_state.RightIsDown())
	{
        bool init_click = false;
        mapEdit_lastAction_erase = true;

		int tbx = ( (px+adj_scroll_offset_x) / current_frame_width);
		int tby = ( (py+adj_scroll_offset_y) / current_frame_height);

		int tmap_x = tbx;
		int tmap_y = tby;
		if(tmap_y < project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows.size())
		{
			if(tmap_x < project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[tmap_y].tile.size())
			{
				project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[tmap_y].tile[tmap_x] = -1;
			}
		}

		if(!(middle_drag_init||left_drag_init||right_drag_init))
		{

			if( px >= 0 && px < pw && py >= 0 && py < ph )
			{
				right_drag_init = true;
			}
		}
	}
	else if( (!mouse_state.RightIsDown()) && right_drag_init )
	{
		//SHOW_CURSOR;
		//this->ReleaseMouse();
		right_drag_init = false;
		//wxMessageBox(_("RELEASE"));
		return;
	}
}

void wxIrrlicht::util_fillTile(int base_tile, int fill_tile, int x, int y)
{
	//std::cout << "test: " << x << ", " << y << std::endl;
	if(y < 0 || y >= project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows.size())
		return;

	if(x < 0 || x >= project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[y].tile.size())
		return;

	int tgt_tile = project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[y].tile[x];

	if(tgt_tile == base_tile)
	{
		project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[y].tile[x] = fill_tile;
		this->util_fillTile(base_tile, fill_tile, x-1, y);
		this->util_fillTile(base_tile, fill_tile, x+1, y);
		this->util_fillTile(base_tile, fill_tile, x, y-1);
		this->util_fillTile(base_tile, fill_tile, x, y+1);
	}
}

void wxIrrlicht::StageSheet_FillTileUpdate()
{
	if(!project)
		return;

	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	if(selected_layer < 0 || selected_layer >= project->stages[selected_stage].layers.size())
		return;

	int canvas_index = project->stages[selected_stage].layers[selected_layer].ref_canvas;

	if(canvas_index < 0 || canvas_index >= canvas.size())
		return;

	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();


	setActiveCanvas(canvas_index);
	//clearCanvas();

	float scroll_speed_x = project->getLayerScrollSpeed(selected_stage, selected_layer).X;
	float scroll_speed_y = project->getLayerScrollSpeed(selected_stage, selected_layer).Y;

	int adj_scroll_offset_x = scroll_speed_x * scroll_offset_x;
	int adj_scroll_offset_y = scroll_speed_y * scroll_offset_y;

	int bx = ( (px+adj_scroll_offset_x) / current_frame_width) *  current_frame_width;
	int by = ( (py+adj_scroll_offset_y) / current_frame_height) *  current_frame_height;

	int off_x_i = (int)adj_scroll_offset_x;
	int off_y_i = (int)adj_scroll_offset_y;

	int select_x = bx - off_x_i;
	int select_y = by - off_y_i;

	int img_x = -adj_scroll_offset_x;
	int img_y = -adj_scroll_offset_y;
	int img_w = 0;
	int img_h = 0;

	int tset = project->stages[selected_stage].layers[selected_layer].layer_map.nv_tileset_index;

	if(tset < 0 || tset >= project->tileset.size())
		return;

	int img_id = project->tileset[tset].object.img_id;

	if(img_id < 0 || img_id >= image.size())
		return;

	int num_rows = mapEdit_tile_selection.row.size();
	int num_cols = 0;

	if(num_rows > 0)
		num_cols = mapEdit_tile_selection.row[0].data.size();

	int fill_tile = -1;

	if(num_cols > 0)
		fill_tile = mapEdit_tile_selection.row[0].data[0];

	if(mapEdit_lastAction_erase)
	{
		setColor(rgb(255, 0, 0));
		drawRect(select_x, select_y, current_frame_width, current_frame_height);
	}
	else
	{
		if(num_cols > 0)
		{
			int src_x = 0;
			int src_y = 0;

			util_getTileInTileset(tset, mapEdit_tile_selection.row[0].data[0], &src_x, &src_y);
			int dst_x = select_x;
			int dst_y = select_y;

			drawImage_Blit(img_id, dst_x, dst_y, src_x, src_y, current_frame_width, current_frame_height);
		}

		setColor(rgb(255, 0, 0));
		drawRect(select_x, select_y, current_frame_width, current_frame_height);
	}

	if(!stage_window_isActive)
	{
		left_drag_init = false;
		right_drag_init = false;
		mapEdit_lastAction_erase = false;
		return;
	}


	if(mouse_state.LeftIsDown() && fill_tile >= 0)
	{
		mapEdit_lastAction_erase = false;
        bool init_click = false;

		int tbx = ( (px+adj_scroll_offset_x) / current_frame_width);
		int tby = ( (py+adj_scroll_offset_y) / current_frame_height);

		int tmap_x = tbx;
		int tmap_y = tby;


		if(!(middle_drag_init||left_drag_init||right_drag_init))
		{
			//std::cout << "t_map: " << tmap_x << ", " << tmap_y << std::endl;

			if( px >= 0 && px < pw && py >= 0 && py < ph )
			{
				if(stage_window_isActive)
				{
					if(mapEdit_tile_selection.row.size() > 0)
					{
						if(mapEdit_tile_selection.row[0].data.size() > 0)
						{
							if(tmap_y < project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows.size())
							{
								if(tmap_x < project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[tmap_y].tile.size())
								{
									int base_tile = project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[tmap_y].tile[tmap_x];
									if(base_tile != fill_tile)
										util_fillTile(base_tile, fill_tile, tmap_x, tmap_y);
								}
							}
						}
					}
				}

				left_drag_init = true;
			}
		}
	}
	else if( (!mouse_state.LeftIsDown()) && left_drag_init )
	{
		//SHOW_CURSOR;
		//this->ReleaseMouse();
		left_drag_init = false;
		//wxMessageBox(_("RELEASE"));
		return;
	}

	if(mouse_state.RightIsDown())
	{
        bool init_click = false;
        mapEdit_lastAction_erase = true;

		int tbx = ( (px+adj_scroll_offset_x) / current_frame_width);
		int tby = ( (py+adj_scroll_offset_y) / current_frame_height);

		int tmap_x = tbx;
		int tmap_y = tby;

		if(!(middle_drag_init||left_drag_init||right_drag_init))
		{

			if( px >= 0 && px < pw && py >= 0 && py < ph )
			{
				if(stage_window_isActive)
				{
					if(mapEdit_tile_selection.row.size() > 0)
					{
						if(mapEdit_tile_selection.row[0].data.size() > 0)
						{
							if(tmap_y < project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows.size())
							{
								if(tmap_x < project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[tmap_y].tile.size())
								{
									int base_tile = project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[tmap_y].tile[tmap_x];
									if(base_tile >= 0)
										util_fillTile(base_tile, -1, tmap_x, tmap_y);
								}
							}
						}
					}
				}

				right_drag_init = true;
			}
		}
	}
	else if( (!mouse_state.RightIsDown()) && right_drag_init )
	{
		//SHOW_CURSOR;
		//this->ReleaseMouse();
		right_drag_init = false;
		//wxMessageBox(_("RELEASE"));
		return;
	}
}

void wxIrrlicht::StageSheet_SelectTileUpdate()
{
	if(!project)
		return;

	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	if(selected_layer < 0 || selected_layer >= project->stages[selected_stage].layers.size())
		return;

	int canvas_index = project->stages[selected_stage].layers[selected_layer].ref_canvas;

	if(canvas_index < 0 || canvas_index >= canvas.size())
		return;

	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();


	setActiveCanvas(canvas_index);
	//clearCanvas();

	float scroll_speed_x = project->getLayerScrollSpeed(selected_stage, selected_layer).X;
	float scroll_speed_y = project->getLayerScrollSpeed(selected_stage, selected_layer).Y;

	int adj_scroll_offset_x = scroll_speed_x * scroll_offset_x;
	int adj_scroll_offset_y = scroll_speed_y * scroll_offset_y;

	int bx = ( (px+adj_scroll_offset_x) / current_frame_width) *  current_frame_width;
	int by = ( (py+adj_scroll_offset_y) / current_frame_height) *  current_frame_height;

	int off_x_i = (int)adj_scroll_offset_x;
	int off_y_i = (int)adj_scroll_offset_y;

	int select_x = bx - off_x_i;
	int select_y = by - off_y_i;

	int img_x = -adj_scroll_offset_x;
	int img_y = -adj_scroll_offset_y;
	int img_w = 0;
	int img_h = 0;

	int tset = project->stages[selected_stage].layers[selected_layer].layer_map.nv_tileset_index;

	if(tset < 0 || tset >= project->tileset.size())
		return;

	int img_id = project->tileset[tset].object.img_id;

	if(img_id < 0 || img_id >= image.size())
		return;

	if(stage_window_isActive)
	{
		setColor(rgb(255, 0, 0));
		drawRect(select_x, select_y, current_frame_width, current_frame_height);
	}

	if(!stage_window_isActive)
	{
		left_drag_init = false;
		right_drag_init = false;
		mapEdit_lastAction_erase = false;
		return;
	}


	if(mouse_state.LeftIsDown())
	{
		mapEdit_lastAction_erase = false;
        bool init_click = false;

		if(!(middle_drag_init||left_drag_init||right_drag_init))
		{

			if( px >= 0 && px < pw && py >= 0 && py < ph )
			{
				if(!VIEW_KEY_CTRL)
					mapEdit_selectTileTool_selection.clear();

				int fx = select_x + adj_scroll_offset_x;
				int fy = select_y + adj_scroll_offset_x;
				int fw = img_w;
				int fh = img_h;

				int tbx = ( (px+adj_scroll_offset_x) / current_frame_width);
				int tby = ( (py+adj_scroll_offset_y) / current_frame_height);

				int tmap_x = tbx;
				int tmap_y = tby;

				if(tmap_y < project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows.size())
				{
					if(tmap_x < project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[tmap_y].tile.size())
					{
						Nirvana_SelectTool_TileSelection t_select;
						t_select.tile_index = project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[tmap_y].tile[tmap_x];
						t_select.map_tile_pos.set(tmap_x, tmap_y);

						if(t_select.tile_index >= 0)
							mapEdit_selectTileTool_selection.push_back(t_select);
					}
				}

				//std::cout << "TEST: " << selected_layer << std::endl;

				left_drag_init = true;
			}
		}
	}
	else if( (!mouse_state.LeftIsDown()) && left_drag_init )
	{
		//SHOW_CURSOR;
		//this->ReleaseMouse();
		left_drag_init = false;
		//wxMessageBox(_("RELEASE"));
		return;
	}

	if(mouse_state.RightIsDown())
	{
		mapEdit_lastAction_erase = false;
        bool init_click = false;

		if(!(middle_drag_init||left_drag_init||right_drag_init))
		{

			if( px >= 0 && px < pw && py >= 0 && py < ph )
			{
				mapEdit_selectTileTool_selection.clear();

				//std::cout << "TEST: " << selected_layer << std::endl;

				right_drag_init = true;
			}
		}
	}
	else if( (!mouse_state.RightIsDown()) && right_drag_init )
	{
		//SHOW_CURSOR;
		//this->ReleaseMouse();
		right_drag_init = false;
		//wxMessageBox(_("RELEASE"));
		return;
	}
}

void wxIrrlicht::StageSheet_BoxSelectTileUpdate()
{
	if(!project)
		return;

	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	if(selected_layer < 0 || selected_layer >= project->stages[selected_stage].layers.size())
		return;

	int canvas_index = project->stages[selected_stage].layers[selected_layer].ref_canvas;

	if(canvas_index < 0 || canvas_index >= canvas.size())
		return;

	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();


	setActiveCanvas(canvas_index);
	//clearCanvas();

	float scroll_speed_x = project->getLayerScrollSpeed(selected_stage, selected_layer).X;
	float scroll_speed_y = project->getLayerScrollSpeed(selected_stage, selected_layer).Y;

	int adj_scroll_offset_x = scroll_speed_x * scroll_offset_x;
	int adj_scroll_offset_y = scroll_speed_y * scroll_offset_y;

	int bx = ( (px+adj_scroll_offset_x) / current_frame_width) *  current_frame_width;
	int by = ( (py+adj_scroll_offset_y) / current_frame_height) *  current_frame_height;

	int off_x_i = (int)adj_scroll_offset_x;
	int off_y_i = (int)adj_scroll_offset_y;

	int select_x = bx - off_x_i;
	int select_y = by - off_y_i;

	int img_x = -adj_scroll_offset_x;
	int img_y = -adj_scroll_offset_y;
	int img_w = 0;
	int img_h = 0;

	int tset = project->stages[selected_stage].layers[selected_layer].layer_map.nv_tileset_index;

	if(tset < 0 || tset >= project->tileset.size())
		return;

	int img_id = project->tileset[tset].object.img_id;

	if(img_id < 0 || img_id >= image.size())
		return;

	if(stage_window_isActive)
	{
		//setColor(rgb(255, 0, 0));
		//drawRect(select_x, select_y, current_frame_width, current_frame_height);
	}

	if(!stage_window_isActive)
	{
		left_drag_init = false;
		right_drag_init = false;
		mapEdit_lastAction_erase = false;
		return;
	}


	if(mouse_state.LeftIsDown())
	{
		mapEdit_lastAction_erase = false;
        bool init_click = false;

		if(!(middle_drag_init||left_drag_init||right_drag_init))
		{

			if( px >= 0 && px < pw && py >= 0 && py < ph )
			{
				mapEdit_selectTileTool_box.clear();

				if(!VIEW_KEY_CTRL)
					mapEdit_selectTileTool_selection.clear();

				int fx = select_x + adj_scroll_offset_x;
				int fy = select_y + adj_scroll_offset_x;
				int fw = img_w;
				int fh = img_h;

				int tbx = ( (px+adj_scroll_offset_x) / current_frame_width);
				int tby = ( (py+adj_scroll_offset_y) / current_frame_height);

				int tmap_x = tbx;
				int tmap_y = tby;

				if(tmap_y < project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows.size())
				{
					if(tmap_x < project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[tmap_y].tile.size())
					{
						Nirvana_SelectTool_TileSelection t_select;
						t_select.tile_index = project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[tmap_y].tile[tmap_x];
						t_select.map_tile_pos.set(tmap_x, tmap_y);
						t_select.box_start_pos.set(px+adj_scroll_offset_x, py+adj_scroll_offset_y);
						mapEdit_selectTileTool_box.push_back(t_select);
					}
				}

				//std::cout << "TEST: " << selected_layer << std::endl;

				left_drag_init = true;
			}
		}
		else if(left_drag_init)
		{
			if(stage_window_isActive && mapEdit_selectTileTool_box.size() > 0)
			{
				setColor(rgb(255, 255, 255));
				int rect_x = mapEdit_selectTileTool_box[0].box_start_pos.X - adj_scroll_offset_x;
				int rect_y = mapEdit_selectTileTool_box[0].box_start_pos.Y - adj_scroll_offset_y;
				int rect_w = (px+adj_scroll_offset_x) - mapEdit_selectTileTool_box[0].box_start_pos.X;
				int rect_h = (py+adj_scroll_offset_y) - mapEdit_selectTileTool_box[0].box_start_pos.Y;
				drawRect(rect_x, rect_y, rect_w, rect_h);
			}
		}
	}
	else if( (!mouse_state.LeftIsDown()) && left_drag_init )
	{
		if(stage_window_isActive && mapEdit_selectTileTool_box.size() > 0)
		{
			//setColor(rgb(255, 255, 255));
			int rect_x = mapEdit_selectTileTool_box[0].box_start_pos.X - adj_scroll_offset_x;
			int rect_y = mapEdit_selectTileTool_box[0].box_start_pos.Y - adj_scroll_offset_y;
			int rect_w = (px+adj_scroll_offset_x) - mapEdit_selectTileTool_box[0].box_start_pos.X;
			int rect_h = (py+adj_scroll_offset_y) - mapEdit_selectTileTool_box[0].box_start_pos.Y;

			int tmap_x = mapEdit_selectTileTool_box[0].map_tile_pos.X;
			int tmap_y = mapEdit_selectTileTool_box[0].map_tile_pos.Y;

			int end_x = (px+adj_scroll_offset_x)/current_frame_width;
			int end_y = (py+adj_scroll_offset_y)/current_frame_height;

			int tmap_w = (end_x > tmap_x ? (end_x - tmap_x) : (tmap_x - end_x)) + 1;
			int tmap_h = (end_y > tmap_y ? (end_y - tmap_y) : (tmap_y - end_y)) + 1;

			tmap_x = (end_x < tmap_x ? end_x : tmap_x);
			tmap_y = (end_y < tmap_y ? end_y : tmap_y);

			for(int tr = tmap_y; tr < (tmap_y+tmap_h); tr++)
			{
				if(tr < 0 || tr >= project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows.size())
					continue;

				for(int tc = tmap_x; tc < (tmap_x+tmap_w); tc++)
				{
					if(tc < 0 || tc >= project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[tr].tile.size())
						continue;

					Nirvana_SelectTool_TileSelection t_select;
					t_select.tile_index = project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[tr].tile[tc];

					if(t_select.tile_index < 0)
						continue;

					t_select.map_tile_pos.set(tc, tr);
					mapEdit_selectTileTool_selection.push_back(t_select);
				}
			}


			//std::cout << "RECT: " << tmap_x << ", " << tmap_y << ", " << tmap_w << ", " << tmap_h << std::endl;


			//drawRect(rect_x, rect_y, rect_w, rect_h);
		}


		//SHOW_CURSOR;
		//this->ReleaseMouse();
		left_drag_init = false;
		//wxMessageBox(_("RELEASE"));
		return;
	}

	if(mouse_state.RightIsDown())
	{
		mapEdit_lastAction_erase = false;
        bool init_click = false;

		if(!(middle_drag_init||left_drag_init||right_drag_init))
		{

			if( px >= 0 && px < pw && py >= 0 && py < ph )
			{
				mapEdit_selectTileTool_selection.clear();

				//std::cout << "TEST: " << selected_layer << std::endl;

				right_drag_init = true;
			}
		}
	}
	else if( (!mouse_state.RightIsDown()) && right_drag_init )
	{
		//SHOW_CURSOR;
		//this->ReleaseMouse();
		right_drag_init = false;
		//wxMessageBox(_("RELEASE"));
		return;
	}
}

void wxIrrlicht::StageSheet_MoveTileUpdate()
{
	if(!project)
		return;

	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	if(selected_layer < 0 || selected_layer >= project->stages[selected_stage].layers.size())
		return;

	int canvas_index = project->stages[selected_stage].layers[selected_layer].ref_canvas;

	if(canvas_index < 0 || canvas_index >= canvas.size())
		return;

	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();


	setActiveCanvas(canvas_index);
	//clearCanvas();

	float scroll_speed_x = project->getLayerScrollSpeed(selected_stage, selected_layer).X;
	float scroll_speed_y = project->getLayerScrollSpeed(selected_stage, selected_layer).Y;

	int adj_scroll_offset_x = scroll_speed_x * scroll_offset_x;
	int adj_scroll_offset_y = scroll_speed_y * scroll_offset_y;

	int bx = ( (px+adj_scroll_offset_x) / current_frame_width) *  current_frame_width;
	int by = ( (py+adj_scroll_offset_y) / current_frame_height) *  current_frame_height;

	int off_x_i = (int)adj_scroll_offset_x;
	int off_y_i = (int)adj_scroll_offset_y;

	int select_x = bx - off_x_i;
	int select_y = by - off_y_i;

	int img_x = -adj_scroll_offset_x;
	int img_y = -adj_scroll_offset_y;
	int img_w = 0;
	int img_h = 0;

	int tset = project->stages[selected_stage].layers[selected_layer].layer_map.nv_tileset_index;

	if(tset < 0 || tset >= project->tileset.size())
		return;

	int img_id = project->tileset[tset].object.img_id;

	if(img_id < 0 || img_id >= image.size())
		return;

	getImageSizeI(img_id, &img_w, &img_h);

	if(stage_window_isActive)
	{
		//setColor(rgb(255, 0, 0));
		//drawRect(select_x, select_y, current_frame_width, current_frame_height);
	}

	if(!stage_window_isActive)
	{
		left_drag_init = false;
		right_drag_init = false;
		mapEdit_lastAction_erase = false;
		return;
	}


	if(mouse_state.LeftIsDown())
	{
		mapEdit_lastAction_erase = false;
        bool init_click = false;

		if(!(middle_drag_init||left_drag_init||right_drag_init))
		{

			if( px >= 0 && px < pw && py >= 0 && py < ph )
			{
				mapEdit_selectTileTool_box.clear();


				int fx = select_x + adj_scroll_offset_x;
				int fy = select_y + adj_scroll_offset_x;
				int fw = img_w;
				int fh = img_h;

				int tbx = ( (px+adj_scroll_offset_x) / current_frame_width);
				int tby = ( (py+adj_scroll_offset_y) / current_frame_height);

				int tmap_x = tbx;
				int tmap_y = tby;

				if(tmap_y < project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows.size())
				{
					if(tmap_x < project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[tmap_y].tile.size())
					{
						Nirvana_SelectTool_TileSelection t_select;
						t_select.tile_index = project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[tmap_y].tile[tmap_x];
						t_select.map_tile_pos.set(tmap_x, tmap_y);
						t_select.box_start_pos.set(px+adj_scroll_offset_x-current_frame_width, py+adj_scroll_offset_y-current_frame_height);
						mapEdit_selectTileTool_box.push_back(t_select);
					}
				}

				//std::cout << "TEST: " << selected_layer << std::endl;

				left_drag_init = true;
			}
		}
		else if(left_drag_init)
		{
			if(stage_window_isActive && mapEdit_selectTileTool_box.size() > 0)
			{
				//setColor(rgb(255, 255, 255));
				int start_x = mapEdit_selectTileTool_box[0].box_start_pos.X;
				int start_y = mapEdit_selectTileTool_box[0].box_start_pos.Y;

				int end_x = px+adj_scroll_offset_x;
				int end_y = py+adj_scroll_offset_y;

				//std::cout << "end_x = " << end_x << std::endl;

				int move_x = end_x - start_x;
				int move_y = end_y - start_y;

				setColor(rgb(255,255,255));

				setImageAlpha(img_id, 170);

				for(int i = 0; i < mapEdit_selectTileTool_selection.size(); i++)
				{
					if(img_w <= 0 || img_h <= 0)
						continue;

					int tile_index = mapEdit_selectTileTool_selection[i].tile_index;
					//std::cout << "[" << i << "] = " << tile_index << std::endl;
					int tx = mapEdit_selectTileTool_selection[i].map_tile_pos.X*current_frame_width-adj_scroll_offset_x;
					int ty = mapEdit_selectTileTool_selection[i].map_tile_pos.Y*current_frame_height-adj_scroll_offset_y;

					int src_x = (tile_index % (img_w / current_frame_width))*current_frame_width;
					int src_y = (tile_index / (img_w / current_frame_width))*current_frame_height;

					int dst_x = (tx+move_x)/current_frame_width * current_frame_width - (adj_scroll_offset_x % current_frame_width);
					int dst_y = (ty+move_y)/current_frame_height * current_frame_height - (adj_scroll_offset_y % current_frame_height);

					drawImage_Blit(img_id, dst_x, dst_y, src_x, src_y, current_frame_width, current_frame_height);
					drawRect(dst_x, dst_y, current_frame_width, current_frame_height);

					//drawImage_Blit(img_id, tx+move_x, ty+move_y, src_x, src_y, current_frame_width, current_frame_height);
				}

				setImageAlpha(img_id, 255);

				//TODO: CONVERTING THIS TO MOVE



				//std::cout << "RECT: " << tmap_x << ", " << tmap_y << ", " << tmap_w << ", " << tmap_h << std::endl;

			}
		}
	}
	else if( (!mouse_state.LeftIsDown()) && left_drag_init )
	{

		if(stage_window_isActive && mapEdit_selectTileTool_box.size() > 0)
		{
			//setColor(rgb(255, 255, 255));
			int start_x = mapEdit_selectTileTool_box[0].box_start_pos.X;
			int start_y = mapEdit_selectTileTool_box[0].box_start_pos.Y;

			int end_x = px+adj_scroll_offset_x;
			int end_y = py+adj_scroll_offset_y;

			//std::cout << "end_x = " << end_x << std::endl;

			int move_x = end_x - start_x;
			int move_y = end_y - start_y;

			std::vector<Nirvana_SelectTool_TileSelection> tmp_selection;
			if(mapEdit_selectTileTool_selection.size() > 0)
				tmp_selection.resize(mapEdit_selectTileTool_selection.size());
			tmp_selection.clear();

			//Clear old tile positions
			for(int i = 0; i < mapEdit_selectTileTool_selection.size(); i++)
			{
				int tile_index = mapEdit_selectTileTool_selection[i].tile_index;
				int dst_x = mapEdit_selectTileTool_selection[i].map_tile_pos.X;
				int dst_y = mapEdit_selectTileTool_selection[i].map_tile_pos.Y;
				if(dst_y >= 0 && dst_y < project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows.size())
				{
					if(dst_x >= 0 && dst_x < project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[dst_y].tile.size())
					{
						project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[dst_y].tile[dst_x] = -1;
					}
				}
			}

			for(int i = 0; i < mapEdit_selectTileTool_selection.size(); i++)
			{
				if(img_w <= 0 || img_h <= 0)
					continue;

				int tile_index = mapEdit_selectTileTool_selection[i].tile_index;
				//std::cout << "[" << i << "] = " << tile_index << std::endl;
				int tx = mapEdit_selectTileTool_selection[i].map_tile_pos.X*current_frame_width;
				int ty = mapEdit_selectTileTool_selection[i].map_tile_pos.Y*current_frame_height;

				int dst_x = ((tx+move_x)-(adj_scroll_offset_x%current_frame_width))/current_frame_width;
				int dst_y = ((ty+move_y)-(adj_scroll_offset_y%current_frame_height))/current_frame_height;

				if(dst_y >= 0 && dst_y < project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows.size())
				{
					if(dst_x >= 0 && dst_x < project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[dst_y].tile.size())
					{
						project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[dst_y].tile[dst_x] = tile_index;

						Nirvana_SelectTool_TileSelection t_select;
						t_select.tile_index = tile_index;
						t_select.map_tile_pos.set(dst_x, dst_y);
						tmp_selection.push_back(t_select);
					}
				}
			}

			mapEdit_selectTileTool_selection.clear();
			mapEdit_selectTileTool_selection = tmp_selection;
		}


		//SHOW_CURSOR;
		//this->ReleaseMouse();
		left_drag_init = false;
		//wxMessageBox(_("RELEASE"));
		return;
	}

}


void wxIrrlicht::StageSheet_CopyTileUpdate()
{
	if(!project)
		return;

	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	if(selected_layer < 0 || selected_layer >= project->stages[selected_stage].layers.size())
		return;

	int canvas_index = project->stages[selected_stage].layers[selected_layer].ref_canvas;

	if(canvas_index < 0 || canvas_index >= canvas.size())
		return;

	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();


	setActiveCanvas(canvas_index);
	//clearCanvas();

	float scroll_speed_x = project->getLayerScrollSpeed(selected_stage, selected_layer).X;
	float scroll_speed_y = project->getLayerScrollSpeed(selected_stage, selected_layer).Y;

	int adj_scroll_offset_x = scroll_speed_x * scroll_offset_x;
	int adj_scroll_offset_y = scroll_speed_y * scroll_offset_y;

	int bx = ( (px+adj_scroll_offset_x) / current_frame_width) *  current_frame_width;
	int by = ( (py+adj_scroll_offset_y) / current_frame_height) *  current_frame_height;

	int off_x_i = (int)adj_scroll_offset_x;
	int off_y_i = (int)adj_scroll_offset_y;

	int select_x = bx - off_x_i;
	int select_y = by - off_y_i;

	int img_x = -adj_scroll_offset_x;
	int img_y = -adj_scroll_offset_y;
	int img_w = 0;
	int img_h = 0;

	int tset = project->stages[selected_stage].layers[selected_layer].layer_map.nv_tileset_index;

	if(tset < 0 || tset >= project->tileset.size())
		return;

	int img_id = project->tileset[tset].object.img_id;

	if(img_id < 0 || img_id >= image.size())
		return;

	getImageSizeI(img_id, &img_w, &img_h);

	if(stage_window_isActive)
	{
		//setColor(rgb(255, 0, 0));
		//drawRect(select_x, select_y, current_frame_width, current_frame_height);
	}

	if(!stage_window_isActive)
	{
		left_drag_init = false;
		right_drag_init = false;
		mapEdit_lastAction_erase = false;
		return;
	}


	if(mouse_state.LeftIsDown())
	{
		mapEdit_lastAction_erase = false;
        bool init_click = false;

		if(!(middle_drag_init||left_drag_init||right_drag_init))
		{

			if( px >= 0 && px < pw && py >= 0 && py < ph )
			{
				mapEdit_selectTileTool_box.clear();


				int fx = select_x + adj_scroll_offset_x;
				int fy = select_y + adj_scroll_offset_x;
				int fw = img_w;
				int fh = img_h;

				int tbx = ( (px+adj_scroll_offset_x) / current_frame_width);
				int tby = ( (py+adj_scroll_offset_y) / current_frame_height);

				int tmap_x = tbx;
				int tmap_y = tby;

				if(tmap_y < project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows.size())
				{
					if(tmap_x < project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[tmap_y].tile.size())
					{
						Nirvana_SelectTool_TileSelection t_select;
						t_select.tile_index = project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[tmap_y].tile[tmap_x];
						t_select.map_tile_pos.set(tmap_x, tmap_y);
						t_select.box_start_pos.set(px+adj_scroll_offset_x, py+adj_scroll_offset_y);
						mapEdit_selectTileTool_box.push_back(t_select);
					}
				}

				//std::cout << "TEST: " << selected_layer << std::endl;

				left_drag_init = true;
			}
		}
		else if(left_drag_init)
		{
			if(stage_window_isActive && mapEdit_selectTileTool_box.size() > 0)
			{
				//setColor(rgb(255, 255, 255));
				int start_x = mapEdit_selectTileTool_box[0].box_start_pos.X;
				int start_y = mapEdit_selectTileTool_box[0].box_start_pos.Y;

				int end_x = px+adj_scroll_offset_x;
				int end_y = py+adj_scroll_offset_y;

				//std::cout << "end_x = " << end_x << std::endl;

				int move_x = end_x - start_x;
				int move_y = end_y - start_y;

				setColor(rgb(255,255,255));

				setImageAlpha(img_id, 170);

				for(int i = 0; i < mapEdit_selectTileTool_selection.size(); i++)
				{
					if(img_w <= 0 || img_h <= 0)
						continue;

					int tile_index = mapEdit_selectTileTool_selection[i].tile_index;
					//std::cout << "[" << i << "] = " << tile_index << std::endl;
					int tx = mapEdit_selectTileTool_selection[i].map_tile_pos.X*current_frame_width-adj_scroll_offset_x;
					int ty = mapEdit_selectTileTool_selection[i].map_tile_pos.Y*current_frame_height-adj_scroll_offset_y;

					int src_x = (tile_index % (img_w / current_frame_width))*current_frame_width;
					int src_y = (tile_index / (img_w / current_frame_width))*current_frame_height;

					int dst_x = (tx+move_x)/current_frame_width * current_frame_width - (adj_scroll_offset_x % current_frame_width);
					int dst_y = (ty+move_y)/current_frame_height * current_frame_height - (adj_scroll_offset_y % current_frame_height);

					drawImage_Blit(img_id, dst_x, dst_y, src_x, src_y, current_frame_width, current_frame_height);
					drawRect(dst_x, dst_y, current_frame_width, current_frame_height);

					//drawImage_Blit(img_id, tx+move_x, ty+move_y, src_x, src_y, current_frame_width, current_frame_height);
				}

				setImageAlpha(img_id, 255);

				//TODO: CONVERTING THIS TO MOVE



				//std::cout << "RECT: " << tmap_x << ", " << tmap_y << ", " << tmap_w << ", " << tmap_h << std::endl;

			}
		}
	}
	else if( (!mouse_state.LeftIsDown()) && left_drag_init )
	{

		if(stage_window_isActive && mapEdit_selectTileTool_box.size() > 0)
		{
			//setColor(rgb(255, 255, 255));
			int start_x = mapEdit_selectTileTool_box[0].box_start_pos.X;
			int start_y = mapEdit_selectTileTool_box[0].box_start_pos.Y;

			int end_x = px+adj_scroll_offset_x;
			int end_y = py+adj_scroll_offset_y;

			//std::cout << "end_x = " << end_x << std::endl;

			int move_x = end_x - start_x;
			int move_y = end_y - start_y;

			std::vector<Nirvana_SelectTool_TileSelection> tmp_selection;
			if(mapEdit_selectTileTool_selection.size() > 0)
				tmp_selection.resize(mapEdit_selectTileTool_selection.size());
			tmp_selection.clear();

			for(int i = 0; i < mapEdit_selectTileTool_selection.size(); i++)
			{
				if(img_w <= 0 || img_h <= 0)
					continue;

				int tile_index = mapEdit_selectTileTool_selection[i].tile_index;
				//std::cout << "[" << i << "] = " << tile_index << std::endl;
				int tx = mapEdit_selectTileTool_selection[i].map_tile_pos.X*current_frame_width;
				int ty = mapEdit_selectTileTool_selection[i].map_tile_pos.Y*current_frame_height;

				int dst_x = ((tx+move_x)-(adj_scroll_offset_x%current_frame_width))/current_frame_width;
				int dst_y = ((ty+move_y)-(adj_scroll_offset_y%current_frame_height))/current_frame_height;

				if(dst_y >= 0 && dst_y < project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows.size())
				{
					if(dst_x >= 0 && dst_x < project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[dst_y].tile.size())
					{
						project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[dst_y].tile[dst_x] = tile_index;

						Nirvana_SelectTool_TileSelection t_select;
						t_select.tile_index = tile_index;
						t_select.map_tile_pos.set(dst_x, dst_y);
						tmp_selection.push_back(t_select);
					}
				}
			}

			mapEdit_selectTileTool_selection.clear();
			mapEdit_selectTileTool_selection = tmp_selection;
		}


		//SHOW_CURSOR;
		//this->ReleaseMouse();
		left_drag_init = false;
		//wxMessageBox(_("RELEASE"));
		return;
	}

}

void wxIrrlicht::StageSheet_DeleteSelectedTileUpdate()
{
	if(!project)
		return;

	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	if(selected_layer < 0 || selected_layer >= project->stages[selected_stage].layers.size())
		return;


	//Clear old tile positions
	for(int i = 0; i < mapEdit_selectTileTool_selection.size(); i++)
	{
		int tile_index = mapEdit_selectTileTool_selection[i].tile_index;
		int dst_x = mapEdit_selectTileTool_selection[i].map_tile_pos.X;
		int dst_y = mapEdit_selectTileTool_selection[i].map_tile_pos.Y;
		if(dst_y >= 0 && dst_y < project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows.size())
		{
			if(dst_x >= 0 && dst_x < project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[dst_y].tile.size())
			{
				project->stages[selected_stage].layers[selected_layer].layer_map.tile_map.rows[dst_y].tile[dst_x] = -1;
			}
		}
	}

	mapEdit_selectTileTool_selection.clear();

}


void wxIrrlicht::util_drawSelectedTiles()
{
	if(!project)
		return;

	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	if(selected_layer < 0 || selected_layer >= project->stages[selected_stage].layers.size())
		return;

	int canvas_index = project->stages[selected_stage].layers[selected_layer].ref_canvas;

	if(canvas_index < 0 || canvas_index >= canvas.size())
		return;

	setActiveCanvas(canvas_index);

	float scroll_speed_x = project->getLayerScrollSpeed(selected_stage, selected_layer).X;
	float scroll_speed_y = project->getLayerScrollSpeed(selected_stage, selected_layer).Y;

	int adj_scroll_offset_x = scroll_speed_x * scroll_offset_x;
	int adj_scroll_offset_y = scroll_speed_y * scroll_offset_y;

	int off_x_i = (int)adj_scroll_offset_x;
	int off_y_i = (int)adj_scroll_offset_y;

	setColor(rgb(255,255,255));
	for(int i = 0; i < mapEdit_selectTileTool_selection.size(); i++)
	{
		int tile_x = mapEdit_selectTileTool_selection[i].map_tile_pos.X;
		int tile_y = mapEdit_selectTileTool_selection[i].map_tile_pos.Y;
		int select_x = (tile_x*current_frame_width) - off_x_i;
		int select_y = (tile_y*current_frame_height) - off_y_i;
		drawRect(select_x, select_y, current_frame_width, current_frame_height);
	}
}


void wxIrrlicht::pickSprites(int start_x, int start_y, int end_x, int end_y, bool current_canvas_only)
{
	pick_sprites.clear();
	for(int i = 0; i < sprite.size(); i++)
	{
		if(!sprite[i].active)
			continue;

		if(current_canvas_only && (sprite[i].parent_canvas != active_canvas))
			continue;

		float scale_x = sprite[i].scale.X;
		float scale_y = sprite[i].scale.Y;


		int ul_x = sprite[i].position.X;
		int ul_y = sprite[i].position.Y;

		int lr_x = ul_x + (sprite[i].frame_size.Width*scale_x);
		int lr_y = ul_y + (sprite[i].frame_size.Height*scale_y);

		int ll_x = ul_x;
		int ll_y = ul_y + (sprite[i].frame_size.Height*scale_y);

		int ur_x = ul_x + (sprite[i].frame_size.Width*scale_x);
		int ur_y = ul_y;

		//Check if Upper Left in Select Box
		if( (ul_x >= start_x && ul_x < end_x) && (ul_y >= start_y && ul_y < end_y) )
		{
			pick_sprites.push_back(i);
			continue;
		}

		//Check if Lower Left in Select Box
		if( (ll_x >= start_x && ll_x < end_x) && (ll_y >= start_y && ll_y < end_y) )
		{
			pick_sprites.push_back(i);
			continue;
		}

		//Check if Upper Right in Select Box
		if( (ur_x >= start_x && ur_x < end_x) && (ur_y >= start_y && ur_y < end_y) )
		{
			pick_sprites.push_back(i);
			continue;
		}

		//Check if Lower Right in Select Box
		if( (lr_x >= start_x && lr_x < end_x) && (lr_y >= start_y && lr_y < end_y) )
		{
			pick_sprites.push_back(i);
			continue;
		}


		int select_ur_x = end_x;
		int select_ur_y = start_y;

		int select_ll_x = start_x;
		int select_ll_y = end_y;

		//Check if Upper Left Select Point is in Sprite Box
		if( (start_x >= ul_x && start_x < lr_x) && (start_y >= ul_y && start_y < lr_y) )
		{
			pick_sprites.push_back(i);
			continue;
		}

		//Check if Lower Right Select Point is in Sprite Box
		if( (end_x >= ul_x && end_x < lr_x) && (end_y >= ul_y && end_y < lr_y) )
		{
			pick_sprites.push_back(i);
			continue;
		}

		//Check if Upper Right Select Point is in Sprite Box
		if( (select_ur_x >= ul_x && select_ur_x < lr_x) && (select_ur_y >= ul_y && select_ur_y < lr_y) )
		{
			pick_sprites.push_back(i);
			continue;
		}

		//Check if Upper Right Select Point is in Sprite Box
		if( (select_ll_x >= ul_x && select_ll_x < lr_x) && (select_ll_y >= ul_y && select_ll_y < lr_y) )
		{
			pick_sprites.push_back(i);
			continue;
		}

	}
}

void wxIrrlicht::StageSheet_SelectSpriteUpdate()
{
	if(!project)
		return;

	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	if(selected_layer < 0 || selected_layer >= project->stages[selected_stage].layers.size())
		return;

	int canvas_index = project->stages[selected_stage].layers[selected_layer].ref_canvas;

	if(canvas_index < 0 || canvas_index >= canvas.size())
		return;

	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();


	setActiveCanvas(canvas_index);
	//clearCanvas();

	float scroll_speed_x = project->getLayerScrollSpeed(selected_stage, selected_layer).X;
	float scroll_speed_y = project->getLayerScrollSpeed(selected_stage, selected_layer).Y;

	int adj_scroll_offset_x = scroll_speed_x * scroll_offset_x;
	int adj_scroll_offset_y = scroll_speed_y * scroll_offset_y;

	int bx = ( (px+adj_scroll_offset_x) / current_frame_width) *  current_frame_width;
	int by = ( (py+adj_scroll_offset_y) / current_frame_height) *  current_frame_height;

	int off_x_i = (int)adj_scroll_offset_x;
	int off_y_i = (int)adj_scroll_offset_y;

	int select_x = bx - off_x_i;
	int select_y = by - off_y_i;


	if(!stage_window_isActive)
	{
		left_drag_init = false;
		right_drag_init = false;
		return;
	}


	if(mouse_state.LeftIsDown())
	{
		bool init_click = false;

		if(!(middle_drag_init||left_drag_init||right_drag_init))
		{

			if( px >= 0 && px < pw && py >= 0 && py < ph )
			{
				if(!VIEW_KEY_CTRL)
					mapEdit_selectSpriteTool_selection.clear();

				pickSprites(bx, by, bx+1, by+1);

				if(pick_sprites.size() > 0)
				{
					Nirvana_SelectTool_SpriteSelection n_sprite_selection;
					n_sprite_selection.layer_sprite_index = pick_sprites[0];
					mapEdit_selectSpriteTool_selection.push_back(n_sprite_selection);
				}

				map_sprite_selection_changed = true;


				//std::cout << "TEST: " << selected_layer << std::endl;

				left_drag_init = true;
			}
		}
	}
	else if( (!mouse_state.LeftIsDown()) && left_drag_init )
	{
		//SHOW_CURSOR;
		//this->ReleaseMouse();
		left_drag_init = false;
		//wxMessageBox(_("RELEASE"));
		return;
	}
}

void wxIrrlicht::StageSheet_BoxSelectSpriteUpdate()
{
	if(!project)
		return;

	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	if(selected_layer < 0 || selected_layer >= project->stages[selected_stage].layers.size())
		return;

	int canvas_index = project->stages[selected_stage].layers[selected_layer].ref_canvas;

	if(canvas_index < 0 || canvas_index >= canvas.size())
		return;

	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();


	setActiveCanvas(canvas_index);
	//clearCanvas();

	float scroll_speed_x = project->getLayerScrollSpeed(selected_stage, selected_layer).X;
	float scroll_speed_y = project->getLayerScrollSpeed(selected_stage, selected_layer).Y;

	int adj_scroll_offset_x = scroll_speed_x * scroll_offset_x;
	int adj_scroll_offset_y = scroll_speed_y * scroll_offset_y;

	int bx =px+adj_scroll_offset_x;
	int by = py+adj_scroll_offset_y;

	int off_x_i = (int)adj_scroll_offset_x;
	int off_y_i = (int)adj_scroll_offset_y;

	int select_x = bx - off_x_i;
	int select_y = by - off_y_i;


	if(!stage_window_isActive)
	{
		left_drag_init = false;
		right_drag_init = false;
		return;
	}

	if(left_drag_init)
	{

		setActiveCanvas(ui_layer);
		setColor(rgb(255,255,255));
		int rect_x = selectSprite_box_start.X - adj_scroll_offset_x;
		int rect_y = selectSprite_box_start.Y - adj_scroll_offset_y;
		int rect_w = bx - selectSprite_box_start.X;
		int rect_h = by - selectSprite_box_start.Y;
		drawRect(rect_x, rect_y, rect_w, rect_h);
		setActiveCanvas(canvas_index);
	}


	if(mouse_state.LeftIsDown())
	{
		bool init_click = false;

		if(!(middle_drag_init||left_drag_init||right_drag_init))
		{

			if( px >= 0 && px < pw && py >= 0 && py < ph )
			{
				if(!VIEW_KEY_CTRL)
					mapEdit_selectSpriteTool_selection.clear();

				selectSprite_box_start.set(bx, by);

				left_drag_init = true;
			}
		}
	}
	else if( (!mouse_state.LeftIsDown()) && left_drag_init )
	{
		int min_x = selectSprite_box_start.X < bx ? selectSprite_box_start.X : bx;
		int min_y = selectSprite_box_start.Y < by ? selectSprite_box_start.Y : by;

		int max_x = selectSprite_box_start.X > bx ? selectSprite_box_start.X : bx;
		int max_y = selectSprite_box_start.Y > by ? selectSprite_box_start.Y : by;

		pickSprites(min_x, min_y, max_x, max_y);

		if(pick_sprites.size() > 0)
		{
			for(int i = 0; i < pick_sprites.size(); i++)
			{
				Nirvana_SelectTool_SpriteSelection n_sprite_selection;
				n_sprite_selection.layer_sprite_index = pick_sprites[i];
				mapEdit_selectSpriteTool_selection.push_back(n_sprite_selection);
			}
			map_sprite_selection_changed = true;
		}


		//SHOW_CURSOR;
		//this->ReleaseMouse();
		left_drag_init = false;
		//wxMessageBox(_("RELEASE"));
		return;
	}
}

void wxIrrlicht::StageSheet_MoveSpriteUpdate()
{
	if(!project)
		return;

	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	if(selected_layer < 0 || selected_layer >= project->stages[selected_stage].layers.size())
		return;

	int canvas_index = project->stages[selected_stage].layers[selected_layer].ref_canvas;

	if(canvas_index < 0 || canvas_index >= canvas.size())
		return;

	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();


	setActiveCanvas(canvas_index);
	//clearCanvas();

	float scroll_speed_x = project->getLayerScrollSpeed(selected_stage, selected_layer).X;
	float scroll_speed_y = project->getLayerScrollSpeed(selected_stage, selected_layer).Y;

	int adj_scroll_offset_x = scroll_speed_x * scroll_offset_x;
	int adj_scroll_offset_y = scroll_speed_y * scroll_offset_y;

	int bx =px+adj_scroll_offset_x;
	int by = py+adj_scroll_offset_y;

	int off_x_i = (int)adj_scroll_offset_x;
	int off_y_i = (int)adj_scroll_offset_y;

	int select_x = bx - off_x_i;
	int select_y = by - off_y_i;


	if(!stage_window_isActive)
	{
		left_drag_init = false;
		right_drag_init = false;
		return;
	}


	if(mouse_state.LeftIsDown())
	{
		bool init_click = false;

		if(!(middle_drag_init||left_drag_init||right_drag_init))
		{

			if( px >= 0 && px < pw && py >= 0 && py < ph )
			{

				selectSprite_box_start.set(bx, by);

				for(int i = 0; i < mapEdit_selectSpriteTool_selection.size(); i++)
				{
					int sprite_index = mapEdit_selectSpriteTool_selection[i].layer_sprite_index; //This is suppose to be rc index
					int spr_x = sprite[sprite_index].position.X;
					int spr_y = sprite[sprite_index].position.Y;
					mapEdit_selectSpriteTool_selection[i].start_pos.set(spr_x, spr_y);
				}

				left_drag_init = true;
			}
		}
		else if(left_drag_init)
		{
			int move_x = bx - selectSprite_box_start.X;
			int move_y = by - selectSprite_box_start.Y;

			//std::cout << "MOVE: " << move_x << ", " << move_y << std::endl;

			for(int i = 0; i < mapEdit_selectSpriteTool_selection.size(); i++)
			{
				int sprite_index = mapEdit_selectSpriteTool_selection[i].layer_sprite_index; //This is suppose to be rc index
				int spr_x = mapEdit_selectSpriteTool_selection[i].start_pos.X + move_x;
				int spr_y = mapEdit_selectSpriteTool_selection[i].start_pos.Y + move_y;

				if(tile_snap)
				{
					spr_x = (spr_x/current_frame_width)*current_frame_width;
					spr_y = (spr_y/current_frame_height)*current_frame_height;
				}

				setSpritePosition(sprite_index, spr_x, spr_y);
			}

			map_sprite_pos_changed = true;
			//parent_window->UpdateWindowUI();
		}
	}
	else if( (!mouse_state.LeftIsDown()) && left_drag_init )
	{

		//SHOW_CURSOR;
		//this->ReleaseMouse();
		left_drag_init = false;
		//wxMessageBox(_("RELEASE"));
		return;
	}
}

void wxIrrlicht::StageSheet_RotateSpriteUpdate()
{
	if(!project)
		return;

	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	if(selected_layer < 0 || selected_layer >= project->stages[selected_stage].layers.size())
		return;

	int canvas_index = project->stages[selected_stage].layers[selected_layer].ref_canvas;

	if(canvas_index < 0 || canvas_index >= canvas.size())
		return;

	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();


	setActiveCanvas(canvas_index);
	//clearCanvas();

	float scroll_speed_x = project->getLayerScrollSpeed(selected_stage, selected_layer).X;
	float scroll_speed_y = project->getLayerScrollSpeed(selected_stage, selected_layer).Y;

	int adj_scroll_offset_x = scroll_speed_x * scroll_offset_x;
	int adj_scroll_offset_y = scroll_speed_y * scroll_offset_y;

	int bx =px+adj_scroll_offset_x;
	int by = py+adj_scroll_offset_y;

	int off_x_i = (int)adj_scroll_offset_x;
	int off_y_i = (int)adj_scroll_offset_y;

	int select_x = bx - off_x_i;
	int select_y = by - off_y_i;


	if(!stage_window_isActive)
	{
		left_drag_init = false;
		right_drag_init = false;
		return;
	}


	if(mouse_state.LeftIsDown())
	{
		bool init_click = false;

		if(!(middle_drag_init||left_drag_init||right_drag_init))
		{

			if( px >= 0 && px < pw && py >= 0 && py < ph )
			{

				int spr_x = this->GetClientSize().GetWidth()/2;
				int spr_y = this->GetClientSize().GetHeight()/2;

				if(mapEdit_selectSpriteTool_selection.size() > 0)
				{
					if(spr_x >= 0 && spr_x < this->GetClientSize().GetWidth() && spr_y >= 0 && spr_y < this->GetClientSize().GetHeight())
					{
						int half_frame_width = sprite[mapEdit_selectSpriteTool_selection[0].layer_sprite_index].frame_size.Width/2;
						int half_frame_height = sprite[mapEdit_selectSpriteTool_selection[0].layer_sprite_index].frame_size.Height/2;
						half_frame_width *= sprite[mapEdit_selectSpriteTool_selection[0].layer_sprite_index].scale.X;
						half_frame_height *= sprite[mapEdit_selectSpriteTool_selection[0].layer_sprite_index].scale.Y;
						spr_x = (sprite[mapEdit_selectSpriteTool_selection[0].layer_sprite_index].position.X + half_frame_width)-adj_scroll_offset_x;
						spr_y = (sprite[mapEdit_selectSpriteTool_selection[0].layer_sprite_index].position.Y + half_frame_height)-adj_scroll_offset_y;
					}
				}

				rotSprite_center_pos.set((float)spr_x, (float)spr_y); // screen position
				rotSprite_angle_start = getHeading(irr::core::vector2df((float)spr_x, (float)spr_y), irr::core::vector2df((float)px, (float)py));


				for(int i = 0; i < mapEdit_selectSpriteTool_selection.size(); i++)
				{
					int sprite_index = mapEdit_selectSpriteTool_selection[i].layer_sprite_index; //This is suppose to be rc index
					float spr_angle = sprite[sprite_index].angle;
					mapEdit_selectSpriteTool_selection[i].angle = spr_angle;
				}

				left_drag_init = true;
			}
		}
		else if(left_drag_init)
		{
			//std::cout << "dbg rot: " << rotSprite_center_pos.X << ", " << rotSprite_center_pos.Y << " to " << px << ", " << py << std::endl;
			float rot_angle = getHeading(rotSprite_center_pos, irr::core::vector2df(px, py)) - rotSprite_angle_start;

			//if(rot_angle < 0)
			//	rot_angle += 360;

			//std::cout << "dt angle = " << rot_angle << std::endl;

			for(int i = 0; i < mapEdit_selectSpriteTool_selection.size(); i++)
			{
				int sprite_index = mapEdit_selectSpriteTool_selection[i].layer_sprite_index; //This is suppose to be rc index
				float spr_angle = mapEdit_selectSpriteTool_selection[i].angle - rot_angle;
				spr_angle = spr_angle < 0 ? spr_angle+360 :spr_angle;
				spr_angle = spr_angle >= 360 ? spr_angle-360 : spr_angle;
				//std::cout << "spr_angle = " << spr_angle << std::endl;
				setSpriteRotation(sprite_index, spr_angle);
			}

			setActiveCanvas(ui_layer);
			setColor(rgb(0, 255, 0));
			drawLine(rotSprite_center_pos.X, rotSprite_center_pos.Y, px, py);

			map_sprite_angle_changed = true;
			//parent_window->UpdateWindowUI();
		}
	}
	else if( (!mouse_state.LeftIsDown()) && left_drag_init )
	{

		//SHOW_CURSOR;
		//this->ReleaseMouse();
		left_drag_init = false;
		//wxMessageBox(_("RELEASE"));
		return;
	}
}

void wxIrrlicht::StageSheet_ScaleSpriteUpdate()
{
	if(!project)
		return;

	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	if(selected_layer < 0 || selected_layer >= project->stages[selected_stage].layers.size())
		return;

	int canvas_index = project->stages[selected_stage].layers[selected_layer].ref_canvas;

	if(canvas_index < 0 || canvas_index >= canvas.size())
		return;

	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();


	setActiveCanvas(canvas_index);
	//clearCanvas();

	float scroll_speed_x = project->getLayerScrollSpeed(selected_stage, selected_layer).X;
	float scroll_speed_y = project->getLayerScrollSpeed(selected_stage, selected_layer).Y;

	int adj_scroll_offset_x = scroll_speed_x * scroll_offset_x;
	int adj_scroll_offset_y = scroll_speed_y * scroll_offset_y;

	int bx =px+adj_scroll_offset_x;
	int by = py+adj_scroll_offset_y;

	int off_x_i = (int)adj_scroll_offset_x;
	int off_y_i = (int)adj_scroll_offset_y;

	int select_x = bx - off_x_i;
	int select_y = by - off_y_i;


	if(!stage_window_isActive)
	{
		left_drag_init = false;
		right_drag_init = false;
		return;
	}


	if(mouse_state.LeftIsDown())
	{
		bool init_click = false;

		if(!(middle_drag_init||left_drag_init||right_drag_init))
		{

			if( px >= 0 && px < pw && py >= 0 && py < ph )
			{

				selectSprite_box_start.set(px, py);

				for(int i = 0; i < mapEdit_selectSpriteTool_selection.size(); i++)
				{
					int sprite_index = mapEdit_selectSpriteTool_selection[i].layer_sprite_index; //This is suppose to be rc index
					int spr_x = sprite[sprite_index].scale.X;
					int spr_y = sprite[sprite_index].scale.Y;
					mapEdit_selectSpriteTool_selection[i].start_scale.set(spr_x, spr_y);
				}

				left_drag_init = true;
			}
		}
		else if(left_drag_init)
		{
			//float distance_from_start = irr::core::vector2df((float)selectSprite_box_start.X, (float)selectSprite_box_start.Y).getDistanceFrom(irr::core::vector2df((float)px, (float)py));

			float half_w = 0;
			float half_h = 0;

			float center_x = 0;
			float center_y = 0;
			if(mapEdit_selectSpriteTool_selection.size() > 0)
			{
				half_w = sprite[mapEdit_selectSpriteTool_selection[0].layer_sprite_index].frame_size.Width/2;
				half_h = sprite[mapEdit_selectSpriteTool_selection[0].layer_sprite_index].frame_size.Height/2;
				center_x = sprite[mapEdit_selectSpriteTool_selection[0].layer_sprite_index].position.X + half_w;
				center_y = sprite[mapEdit_selectSpriteTool_selection[0].layer_sprite_index].position.Y + half_h;
			}

			float distacne_from_center = irr::core::vector2df(center_x, center_y).getDistanceFrom(irr::core::vector2df((float)px, (float)py));

			float start_from_center = irr::core::vector2df(center_x, center_y).getDistanceFrom(irr::core::vector2df((float)selectSprite_box_start.X, (float)selectSprite_box_start.Y));

			float frame_half = half_w < half_h ? half_w : half_h;
			float scale_inc = (distacne_from_center - start_from_center)/frame_half;
			//std::cout << "SCALE: " << scale_inc << std::endl;

			for(int i = 0; i < mapEdit_selectSpriteTool_selection.size(); i++)
			{
				int sprite_index = mapEdit_selectSpriteTool_selection[i].layer_sprite_index; //This is suppose to be rc index
				float spr_x = mapEdit_selectSpriteTool_selection[i].start_scale.X + scale_inc;
				float spr_y = mapEdit_selectSpriteTool_selection[i].start_scale.Y + scale_inc;
				setSpriteScale(sprite_index, spr_x, spr_y);
			}

			map_sprite_scale_changed = true;
			//parent_window->UpdateWindowUI();
		}
	}
	else if( (!mouse_state.LeftIsDown()) && left_drag_init )
	{

		//SHOW_CURSOR;
		//this->ReleaseMouse();
		left_drag_init = false;
		//wxMessageBox(_("RELEASE"));
		return;
	}
}

float wxIrrlicht::getHeading(irr::core::vector2df a, irr::core::vector2df b)
{
    float PI = 3.1415926535;
    float x = b.X - a.X;
    float y = b.Y - a.Y;
    return std::atan2(y, x) * (180.0 / PI);
}


void wxIrrlicht::pickShape(int start_x, int start_y, int end_x, int end_y)
{
	int min_x = start_x < end_x ? start_x : end_x;
	int min_y = start_y < end_y ? start_y : end_y;

	int max_x = start_x > end_x ? start_x : end_x;
	int max_y = start_y > end_y ? start_y : end_y;

	start_x = min_x;
	start_y = min_y;

	end_x = max_x;
	end_y = max_y;

	pick_points.clear();

	int current_shape = selected_shape;

	if(selected_points.size() == 0)
		selected_shape = -1;

	for(int i = selected_shape < 0 ? 0 : selected_shape; i < project->stages[selected_stage].layers[selected_layer].layer_shapes.size(); i++)
	{
		int shape_type = project->stages[selected_stage].layers[selected_layer].layer_shapes[i].shape_type;

		if(shape_type == SPRITE_SHAPE_BOX)
		{
			// UL - 0, LL - 1, UR - 2, LR - 3
			int x = project->stages[selected_stage].layers[selected_layer].layer_shapes[i].offset_x;
			int y = project->stages[selected_stage].layers[selected_layer].layer_shapes[i].offset_y;

			int w = project->stages[selected_stage].layers[selected_layer].layer_shapes[i].box_width;
			int h = project->stages[selected_stage].layers[selected_layer].layer_shapes[i].box_height;

			int ul_x = x;
			int ul_y = y;

			int ll_x = x;
			int ll_y = y+h;

			int ur_x = x+w;
			int ur_y = y;

			int lr_x = x+w;
			int lr_y = y+h;

			//std::cout << "BOX DBG: " << start_x << ", " << start_y << ", " << end_x << ", " << end_y << " :: " << ul_x << ", " << ul_y << std::endl;

			if(ul_x >= start_x && ul_x < end_x && ul_y >= start_y && ul_y < end_y)
			{
				selected_shape = i;
				pick_points.push_back(0);
			}

			if(ll_x >= start_x && ll_x < end_x && ll_y >= start_y && ll_y < end_y)
			{
				selected_shape = i;
				pick_points.push_back(1);
			}

			if(ur_x >= start_x && ur_x < end_x && ur_y >= start_y && ur_y < end_y)
			{
				selected_shape = i;
				pick_points.push_back(2);
			}

			if(lr_x >= start_x && lr_x < end_x && lr_y >= start_y && lr_y < end_y)
			{
				selected_shape = i;
				pick_points.push_back(3);
			}
		}
		else if(shape_type == SPRITE_SHAPE_CIRCLE)
		{
			//TOP - 0, LEFT - 1, RIGHT - 2, BOTTOM - 3
			int x = project->stages[selected_stage].layers[selected_layer].layer_shapes[i].offset_x;
			int y = project->stages[selected_stage].layers[selected_layer].layer_shapes[i].offset_y;

			int r = project->stages[selected_stage].layers[selected_layer].layer_shapes[i].radius;

			int top_x = x;
			int top_y = y-r;

			int left_x = x-r;
			int left_y = y;

			int right_x = x+r;
			int right_y = y;

			int bottom_x = x;
			int bottom_y = y+r;

			if(top_x >= start_x && top_x < end_x && top_y >= start_y && top_y < end_y)
			{
				selected_shape = i;
				pick_points.push_back(0);
			}

			if(left_x >= start_x && left_x < end_x && left_y >= start_y && left_y < end_y)
			{
				selected_shape = i;
				pick_points.push_back(1);
			}

			if(right_x >= start_x && right_x < end_x && right_y >= start_y && right_y < end_y)
			{
				selected_shape = i;
				pick_points.push_back(2);
			}

			if(bottom_x >= start_x && bottom_x < end_x && bottom_y >= start_y && bottom_y < end_y)
			{
				selected_shape = i;
				pick_points.push_back(3);
			}
		}
		else if(shape_type == SPRITE_SHAPE_POLYGON || shape_type == SPRITE_SHAPE_CHAIN)
		{
			if(project->stages[selected_stage].layers[selected_layer].layer_shapes[i].point_selection.size() != project->stages[selected_stage].layers[selected_layer].layer_shapes[i].points.size())
			{
				for(int n = project->stages[selected_stage].layers[selected_layer].layer_shapes[i].point_selection.size(); n < project->stages[selected_stage].layers[selected_layer].layer_shapes[i].points.size(); n++)
				{
					project->stages[selected_stage].layers[selected_layer].layer_shapes[i].point_selection.push_back(false);
				}
			}

			for(int pt_index = 0; pt_index < project->stages[selected_stage].layers[selected_layer].layer_shapes[i].points.size(); pt_index++)
			{
				int x = project->stages[selected_stage].layers[selected_layer].layer_shapes[i].points[pt_index].X;
				int y = project->stages[selected_stage].layers[selected_layer].layer_shapes[i].points[pt_index].Y;

				if(x >= start_x && x < end_x && y >= start_y && y < end_y)
				{
					selected_shape = i;
					pick_points.push_back(pt_index);
					//project->stages[selected_stage].layers[selected_layer].layer_shapes[i].point_selection[pt_index] = true;
				}
				else
				{
					//project->stages[selected_stage].layers[selected_layer].layer_shapes[i].point_selection[pt_index] = false;
				}
			}
		}

		if(selected_shape >= 0)
			break;
	}

	if(selected_shape < 0)
		selected_shape = current_shape;

	if(selected_shape != current_shape && selected_shape >= 0 && m_mapEdit_collisionShape_listBox != NULL)
	{
		int list_item_index = -1;
		wxString list_item_name = wxString(project->getShapeName(selected_stage, selected_layer, selected_shape)).Upper().Trim();

		//find shape in list box by name
		for(int i = 0; i < m_mapEdit_collisionShape_listBox->GetCount(); i++)
		{
			if(list_item_name.compare(m_mapEdit_collisionShape_listBox->GetString(i).Upper().Trim())==0)
			{
				list_item_index = i;
				break;
			}
		}

		if(list_item_index >= 0)
		{
			m_mapEdit_collisionShape_listBox->SetSelection(list_item_index);
		}
	}
}

void wxIrrlicht::stage_collisionEdit_select()
{
	if(!project)
		return;

	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	if(selected_layer < 0 || selected_layer >= project->stages[selected_stage].layers.size())
		return;

	if(project->getLayerType(selected_stage, selected_layer) != LAYER_TYPE_SPRITE)
		return;

	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();


	float scroll_speed_x = project->getLayerScrollSpeed(selected_stage, selected_layer).X;
	float scroll_speed_y = project->getLayerScrollSpeed(selected_stage, selected_layer).Y;

	int adj_scroll_offset_x = scroll_speed_x * scroll_offset_x;
	int adj_scroll_offset_y = scroll_speed_y * scroll_offset_y;

	int bx = px+adj_scroll_offset_x;
	int by = py+adj_scroll_offset_y;

	if(mouse_state.LeftIsDown())
	{
		bool init_click = false;

		if(!(middle_drag_init||left_drag_init||right_drag_init))
		{

			if( px >= 0 && px < pw && py >= 0 && py < ph )
			{
				if(!VIEW_KEY_CTRL)
				{
					selected_points.clear();

					if(selected_shape >= 0 && selected_shape < project->stages[selected_stage].layers[selected_layer].layer_shapes.size())
						project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].point_selection.clear();
				}

				pickShape(bx-5, by-5, bx+5, by+5);

				//check for first point not in selected points already
				for(int i = 0; i < pick_points.size(); i++)
				{
					bool point_selected = false;

					for(int n = 0; n < selected_points.size(); n++)
					{
						if(selected_points[n] == pick_points[i])
						{
							point_selected = true;
							break;
						}
					}

					if(!point_selected)
					{
						selected_points.push_back(pick_points[i]);

						if(selected_shape >= 0)
						{
							if(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].shape_type == SPRITE_SHAPE_CHAIN ||
							   project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].shape_type == SPRITE_SHAPE_POLYGON)
							{
								if(pick_points[i] >= 0 && pick_points[i] < project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].point_selection.size())
								{
									project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].point_selection[pick_points[i]] = true;
								}
							}
						}

						break;
					}
				}

				//std::cout << std::endl << "SELECTED: " << std::endl;
				//for(int i = 0; i < selected_points.size(); i++)
				//	std::cout << "point: " << selected_points[i] << std::endl;
				//std::cout << "----------------" << std::endl << std::endl;

				pick_shape_update = true;

				parent_window->UpdateWindowUI();

				//std::cout << "TEST: " << selected_layer << std::endl;

				left_drag_init = true;
			}
		}
	}
	else if( (!mouse_state.LeftIsDown()) && left_drag_init )
	{
		//SHOW_CURSOR;
		//this->ReleaseMouse();
		left_drag_init = false;
		//wxMessageBox(_("RELEASE"));
		return;
	}
}

void wxIrrlicht::stage_collisionEdit_boxSelect()
{
	if(!project)
		return;

	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	if(selected_layer < 0 || selected_layer >= project->stages[selected_stage].layers.size())
		return;

	if(project->getLayerType(selected_stage, selected_layer) != LAYER_TYPE_SPRITE)
		return;

	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();


	float scroll_speed_x = project->getLayerScrollSpeed(selected_stage, selected_layer).X;
	float scroll_speed_y = project->getLayerScrollSpeed(selected_stage, selected_layer).Y;

	int adj_scroll_offset_x = scroll_speed_x * scroll_offset_x;
	int adj_scroll_offset_y = scroll_speed_y * scroll_offset_y;

	int bx = px+adj_scroll_offset_x;
	int by = py+adj_scroll_offset_y;

	if(mouse_state.LeftIsDown())
	{
		bool init_click = false;

		if(!(middle_drag_init||left_drag_init||right_drag_init))
		{

			if( px >= 0 && px < pw && py >= 0 && py < ph )
			{
				drag_start.x = bx;
				drag_start.y = by;
				//std::cout << "TEST: " << selected_layer << std::endl;

				left_drag_init = true;
			}
		}
	}
	else if( (!mouse_state.LeftIsDown()) && left_drag_init )
	{
		if(!VIEW_KEY_CTRL)
		{
			selected_points.clear();

			if(selected_shape >= 0 && selected_shape < project->stages[selected_stage].layers[selected_layer].layer_shapes.size())
				project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].point_selection.clear();
		}

		pickShape(drag_start.x-2, drag_start.y-2, bx+2, by+2);

		//check for first point not in selected points already
		for(int i = 0; i < pick_points.size(); i++)
		{
			bool point_selected = false;

			for(int n = 0; n < selected_points.size(); n++)
			{
				if(selected_points[n] == pick_points[i])
				{
					point_selected = true;
					break;
				}
			}

			if(!point_selected)
			{
				selected_points.push_back(pick_points[i]);

				if(selected_shape >= 0)
				{
					if(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].shape_type == SPRITE_SHAPE_CHAIN ||
					   project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].shape_type == SPRITE_SHAPE_POLYGON)
					{
						if(pick_points[i] >= 0 && pick_points[i] < project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].point_selection.size())
						{
							project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].point_selection[pick_points[i]] = true;
						}
					}
				}
			}
		}

		pick_shape_update = true;

		parent_window->UpdateWindowUI();

		//SHOW_CURSOR;
		//this->ReleaseMouse();
		left_drag_init = false;
		//wxMessageBox(_("RELEASE"));
		return;
	}
}

void wxIrrlicht::stage_collisionEdit_move()
{
	if(!project)
		return;

	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	if(selected_layer < 0 || selected_layer >= project->stages[selected_stage].layers.size())
		return;

	if(project->getLayerType(selected_stage, selected_layer) != LAYER_TYPE_SPRITE)
		return;

	if(selected_shape < 0 || selected_shape >= project->stages[selected_stage].layers[selected_layer].layer_shapes.size())
		return;

	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();


	float scroll_speed_x = project->getLayerScrollSpeed(selected_stage, selected_layer).X;
	float scroll_speed_y = project->getLayerScrollSpeed(selected_stage, selected_layer).Y;

	int adj_scroll_offset_x = scroll_speed_x * scroll_offset_x;
	int adj_scroll_offset_y = scroll_speed_y * scroll_offset_y;

	int bx = px+adj_scroll_offset_x;
	int by = py+adj_scroll_offset_y;

	irr::core::vector2di mouse_pos(px, py);

	switch(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].shape_type)
	{
		case SPRITE_SHAPE_BOX:
		{
			if(mouse_state.LeftIsDown())
			{
				bool init_click = false;

				if(!(middle_drag_init||left_drag_init||right_drag_init))
				{

					if( px >= 0 && px < pw && py >= 0 && py < ph )
					{
						left_drag_init = true;
						this->SetFocusFromKbd();
						init_click = true;

						drag_start = wxPoint(bx, by);
						collision_move_start_offset.set(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_x, project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_y);
						collision_move_start_size.set(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_width, project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_height);

						project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].ul_selected = false;
						project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].ll_selected = false;
						project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].ur_selected = false;
						project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].lr_selected = false;

						project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].top_selected = false;
						project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].left_selected = false;
						project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].right_selected = false;
						project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].bottom_selected = false;

						int shape_type = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].shape_type;

						if(shape_type == SPRITE_SHAPE_BOX)
						{
							for(int i = 0; i < selected_points.size(); i++)
							{
								if(selected_points[i] == 0)
								{
									project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].ul_selected = true;
								}
								else if(selected_points[i] == 1)
								{
									project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].ll_selected = true;
								}
								else if(selected_points[i] == 2)
								{
									project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].ur_selected = true;
								}
								else if(selected_points[i] == 3)
								{
									project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].lr_selected = true;
								}
							}
						}
					}
				}
				else if(left_drag_init)
				{
					if( px >= 0 && px < pw && py >= 0 && py < ph )
					{
						this->SetFocusFromKbd();

						collision_boxShapeSelect_ul = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].ul_selected;
						collision_boxShapeSelect_ll = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].ll_selected;
						collision_boxShapeSelect_ur = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].ur_selected;
						collision_boxShapeSelect_lr = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].lr_selected;

						if(collision_boxShapeSelect_ul && collision_boxShapeSelect_ll && collision_boxShapeSelect_ur && collision_boxShapeSelect_lr)
						{
							project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_x = collision_move_start_offset.X + (bx - drag_start.x);
							project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_y = collision_move_start_offset.Y + (by - drag_start.y);

							if(tile_snap)
							{
								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_x = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_x / current_frame_width * current_frame_width;
								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_y = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_y / current_frame_height * current_frame_height;
							}

							if(m_mapEdit_boxShape_posX_spinCtrl)
								m_mapEdit_boxShape_posX_spinCtrl->SetValue(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_x);

							if(m_mapEdit_boxShape_posY_spinCtrl)
								m_mapEdit_boxShape_posY_spinCtrl->SetValue(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_y);
						}
						else if(collision_boxShapeSelect_ul)
						{
							project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_x = collision_move_start_offset.X + (bx - drag_start.x);
							project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_y = collision_move_start_offset.Y + (by - drag_start.y);

							project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_width = collision_move_start_size.X - (bx - drag_start.x);
							project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_height = collision_move_start_size.Y - (by - drag_start.y);

							if(tile_snap)
							{
								int diff_off_x = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_x;
								int diff_off_y = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_y;

								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_x = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_x / current_frame_width * current_frame_width;
								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_y = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_y / current_frame_height * current_frame_height;

								diff_off_x = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_x - diff_off_x;
								diff_off_y = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_y - diff_off_y;

								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_width -= diff_off_x;
								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_height -= diff_off_y;
							}

							if(m_mapEdit_boxShape_posX_spinCtrl)
								m_mapEdit_boxShape_posX_spinCtrl->SetValue(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_x);

							if(m_mapEdit_boxShape_posY_spinCtrl)
								m_mapEdit_boxShape_posY_spinCtrl->SetValue(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_y);

							if(m_mapEdit_boxShape_width_spinCtrl)
								m_mapEdit_boxShape_width_spinCtrl->SetValue(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_width);

							if(m_mapEdit_boxShape_height_spinCtrl)
								m_mapEdit_boxShape_height_spinCtrl->SetValue(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_height);
						}
						else if(collision_boxShapeSelect_ll)
						{
							project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_x = collision_move_start_offset.X + (bx - drag_start.x);
							//collision_physics_obj.offset_y = collision_move_start_offset.Y + (py - drag_start.y)/img_scale;

							project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_width = collision_move_start_size.X - (bx - drag_start.x);
							project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_height = collision_move_start_size.Y + (by - drag_start.y);

							if(tile_snap)
							{
								int diff_off_x = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_x;
								int diff_off_y = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_y;

								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_x = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_x / current_frame_width * current_frame_width;

								diff_off_x = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_x - diff_off_x;

								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_width -= diff_off_x;
								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_height = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_height / current_frame_height * current_frame_height;
							}

							if(m_mapEdit_boxShape_posX_spinCtrl)
								m_mapEdit_boxShape_posX_spinCtrl->SetValue(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_x);

							if(m_mapEdit_boxShape_width_spinCtrl)
								m_mapEdit_boxShape_width_spinCtrl->SetValue(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_width);

							if(m_mapEdit_boxShape_height_spinCtrl)
								m_mapEdit_boxShape_height_spinCtrl->SetValue(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_height);
						}
						else if(collision_boxShapeSelect_ur)
						{
							//collision_physics_obj.offset_x = collision_move_start_offset.X + (px - drag_start.x)/img_scale;
							project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_y = collision_move_start_offset.Y + (by - drag_start.y);

							project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_width = collision_move_start_size.X + (bx - drag_start.x);
							project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_height = collision_move_start_size.Y - (by - drag_start.y);

							if(tile_snap)
							{
								int diff_off_x = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_x;
								int diff_off_y = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_y;

								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_y = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_y / current_frame_height * current_frame_height;

								diff_off_x = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_x - diff_off_x;
								diff_off_y = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_y - diff_off_y;

								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_width = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_width / current_frame_width * current_frame_width;
								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_height -= diff_off_y;
							}

							if(m_mapEdit_boxShape_posY_spinCtrl)
								m_mapEdit_boxShape_posY_spinCtrl->SetValue(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_y);

							if(m_mapEdit_boxShape_width_spinCtrl)
								m_mapEdit_boxShape_width_spinCtrl->SetValue(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_width);

							if(m_mapEdit_boxShape_height_spinCtrl)
								m_mapEdit_boxShape_height_spinCtrl->SetValue(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_height);
						}
						else if(collision_boxShapeSelect_lr)
						{
							//collision_physics_obj.offset_x = collision_move_start_offset.X + (px - drag_start.x)/img_scale;
							//collision_physics_obj.offset_y = collision_move_start_offset.Y + (py - drag_start.y)/img_scale;

							project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_width = collision_move_start_size.X + (bx - drag_start.x);
							project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_height = collision_move_start_size.Y + (by - drag_start.y);

							if(tile_snap)
							{
								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_width = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_width / current_frame_width * current_frame_width;
								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_height = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_height / current_frame_height * current_frame_height;
							}

							if(m_mapEdit_boxShape_width_spinCtrl)
								m_mapEdit_boxShape_width_spinCtrl->SetValue(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_width);

							if(m_mapEdit_boxShape_height_spinCtrl)
								m_mapEdit_boxShape_height_spinCtrl->SetValue(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_height);
						}

						collision_object_modified = true;
						parent_window->UpdateWindowUI();
					}
				}
			}
		}
		break;

		case SPRITE_SHAPE_CIRCLE:
		{
			if(mouse_state.LeftIsDown())
			{
				bool init_click = false;

				if(!(middle_drag_init||left_drag_init||right_drag_init))
				{

					if( px >= 0 && px < pw && py >= 0 && py < ph )
					{
						left_drag_init = true;
						this->SetFocusFromKbd();
						init_click = true;

						drag_start = wxPoint(bx, by);
						collision_move_start_offset.set(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_x, project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_y);
						collision_move_start_radius = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].radius;

						project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].top_selected = false;
						project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].left_selected = false;
						project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].right_selected = false;
						project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].bottom_selected = false;

						for(int i = 0; i < selected_points.size(); i++)
						{
							if(selected_points[i] == 0)
							{
								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].top_selected = true;
							}
							else if(selected_points[i] == 1)
							{
								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].left_selected = true;
							}
							else if(selected_points[i] == 2)
							{
								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].right_selected = true;
							}
							else if(selected_points[i] == 3)
							{
								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].bottom_selected = true;
							}
						}
					}
				}
				else if(left_drag_init)
				{
					if( px >= 0 && px < pw && py >= 0 && py < ph )
					{
						this->SetFocusFromKbd();

						collision_circleShapeSelect_u = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].top_selected;
						collision_circleShapeSelect_l = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].left_selected;
						collision_circleShapeSelect_r = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].right_selected;
						collision_circleShapeSelect_d = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].bottom_selected;

						if(collision_circleShapeSelect_u && collision_circleShapeSelect_d && collision_circleShapeSelect_l && collision_circleShapeSelect_r)
						{
							project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_x = collision_move_start_offset.X + (bx - drag_start.x);
							project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_y = collision_move_start_offset.Y + (by - drag_start.y);

							if(tile_snap)
							{
								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_x = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_x / current_frame_width * current_frame_width;
								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_y = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_y / current_frame_height * current_frame_height;
							}

							if(m_mapEdit_circleShape_centerX_spinCtrl)
								m_mapEdit_circleShape_centerX_spinCtrl->SetValue(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_x);

							if(m_mapEdit_circleShape_centerY_spinCtrl)
								m_mapEdit_circleShape_centerY_spinCtrl->SetValue(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_y);
						}
						else if(collision_circleShapeSelect_u)
						{
							project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].radius = collision_move_start_radius - (by - drag_start.y);

							if(tile_snap)
							{
								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].radius = ( (int)(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].radius / current_frame_height) * current_frame_height);
							}

							if(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].radius < 0)
								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].radius *= -1;

							if(m_mapEdit_circleShape_radius_spinCtrl)
								m_mapEdit_circleShape_radius_spinCtrl->SetValue(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].radius);
						}
						else if(collision_circleShapeSelect_d)
						{
							project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].radius = collision_move_start_radius + (by - drag_start.y);

							if(tile_snap)
							{
								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].radius = ( (int)(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].radius / current_frame_height) * current_frame_height);
							}

							if(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].radius < 0)
								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].radius *= -1;

							if(m_mapEdit_circleShape_radius_spinCtrl)
								m_mapEdit_circleShape_radius_spinCtrl->SetValue(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].radius);
						}
						else if(collision_circleShapeSelect_l)
						{
							project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].radius = collision_move_start_radius - (bx - drag_start.x);

							if(tile_snap)
							{
								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].radius = ( (int)(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].radius / current_frame_width) * current_frame_width);
							}

							if(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].radius < 0)
								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].radius *= -1;

							if(m_mapEdit_circleShape_radius_spinCtrl)
								m_mapEdit_circleShape_radius_spinCtrl->SetValue(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].radius);
						}
						else if(collision_circleShapeSelect_r)
						{
							project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].radius = collision_move_start_radius + (bx - drag_start.x);

							if(tile_snap)
							{
								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].radius = ( (int)(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].radius / current_frame_width) * current_frame_width);
							}

							if(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].radius < 0)
								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].radius *= -1;

							if(m_mapEdit_circleShape_radius_spinCtrl)
								m_mapEdit_circleShape_radius_spinCtrl->SetValue(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].radius);
						}

						collision_object_modified = true;
						parent_window->UpdateWindowUI();
					}
				}
			}
		}
		break;

		case SPRITE_SHAPE_CHAIN:
		case SPRITE_SHAPE_POLYGON:
		{
			if(mouse_state.LeftIsDown())
			{
				bool init_click = false;

				if(!(middle_drag_init||left_drag_init||right_drag_init))
				{
					if( px >= 0 && px < pw && py >= 0 && py < ph )
					{
						left_drag_init = true;
						this->SetFocusFromKbd();
						init_click = true;

						drag_start = wxPoint(bx, by);
						collision_move_start_offset.set(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_x, project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].offset_y);
						collision_move_start_points.clear();

						for(int i = 0; i < project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].points.size(); i++)
						{
							collision_move_start_points.push_back(project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].points[i]);
						}
					}
				}
				else if(left_drag_init)
				{
					if( px >= 0 && px < pw && py >= 0 && py < ph )
					{
						this->SetFocusFromKbd();

						int mouse_move_x = (bx - drag_start.x);
						int mouse_move_y = (by - drag_start.y);

						for(int i = 0; i < selected_points.size(); i++)
						{
							int pt_index = selected_points[i];
							project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].points[pt_index].X = collision_move_start_points[pt_index].X + mouse_move_x;
							project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].points[pt_index].Y = collision_move_start_points[pt_index].Y + mouse_move_y;

							if(tile_snap)
							{
								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].points[pt_index].X = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].points[pt_index].X / current_frame_width * current_frame_width;
								project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].points[pt_index].Y = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].points[pt_index].Y / current_frame_height * current_frame_height;
							}

							if(m_mapEdit_polyShape_grid)
							{
								if(pt_index >= 0 && pt_index < m_mapEdit_polyShape_grid->GetNumberRows())
								{
									m_mapEdit_polyShape_grid->SetCellValue(pt_index, 0, wxString::Format(_("%i"), project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].points[pt_index].X));
									m_mapEdit_polyShape_grid->SetCellValue(pt_index, 1, wxString::Format(_("%i"), project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].points[pt_index].Y));
								}
							}
						}

						collision_object_modified = true;
						parent_window->UpdateWindowUI();
					}
				}
			}
		}
		break;
	}
}

void wxIrrlicht::stage_collisionEdit_draw()
{
	if(!project)
		return;

	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	if(selected_layer < 0 || selected_layer >= project->stages[selected_stage].layers.size())
		return;

	if(project->getLayerType(selected_stage, selected_layer) != LAYER_TYPE_SPRITE)
		return;

	if(selected_shape < 0 || selected_shape >= project->stages[selected_stage].layers[selected_layer].layer_shapes.size())
		return;

	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();


	float scroll_speed_x = project->getLayerScrollSpeed(selected_stage, selected_layer).X;
	float scroll_speed_y = project->getLayerScrollSpeed(selected_stage, selected_layer).Y;

	int adj_scroll_offset_x = scroll_speed_x * scroll_offset_x;
	int adj_scroll_offset_y = scroll_speed_y * scroll_offset_y;

	int bx = px+adj_scroll_offset_x;
	int by = py+adj_scroll_offset_y;

	irr::core::vector2di mouse_pos(px, py);

	switch(collision_physics_obj.shape_type)
	{
		case SPRITE_SHAPE_BOX:
		{
			if(mouse_state.LeftIsDown())
			{
				bool init_click = false;

				if(!(middle_drag_init||left_drag_init||right_drag_init))
				{

					if( px >= 0 && px < pw && py >= 0 && py < ph )
					{
						left_drag_init = true;
						this->SetFocusFromKbd();
						init_click = true;

						if(!collision_poly_draw_flag)
						{
							collision_physics_obj.offset_x = bx;
							collision_physics_obj.offset_y = by;

							if(tile_snap)
							{
								collision_physics_obj.offset_x = collision_physics_obj.offset_x / current_frame_width * current_frame_width;
								collision_physics_obj.offset_y = collision_physics_obj.offset_y / current_frame_height * current_frame_height;
							}

							if(m_mapEdit_boxShape_posX_spinCtrl)
								m_mapEdit_boxShape_posX_spinCtrl->SetValue(collision_physics_obj.offset_x);

							if(m_mapEdit_boxShape_posY_spinCtrl)
								m_mapEdit_boxShape_posY_spinCtrl->SetValue(collision_physics_obj.offset_y);

							collision_poly_draw_flag = true;
						}

						collision_object_modified = true;
						//parent_window->UpdateWindowUI();
					}
				}
				else
				{
					//collision_physics_obj.radius = irr::core::vector2di(bx,by).getDistanceFrom(irr::core::vector2di(collision_physics_obj.offset_x, collision_physics_obj.offset_y));
					collision_physics_obj.box_width = bx - collision_physics_obj.offset_x;
					collision_physics_obj.box_height = by - collision_physics_obj.offset_y;

					if(tile_snap)
					{
						collision_physics_obj.box_width = collision_physics_obj.box_width / current_frame_width * current_frame_width;
						collision_physics_obj.box_height = collision_physics_obj.box_height / current_frame_height * current_frame_height;
					}

					if(m_mapEdit_boxShape_width_spinCtrl)
						m_mapEdit_boxShape_width_spinCtrl->SetValue(collision_physics_obj.box_width);

					if(m_mapEdit_boxShape_height_spinCtrl)
						m_mapEdit_boxShape_height_spinCtrl->SetValue(collision_physics_obj.box_height);
				}
			}
			else
			{
				//collision_object_modified = true;
				if(collision_poly_draw_flag)
				{
					collision_poly_draw_flag = false;
					collision_physics_obj.shape_name = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].shape_name; //to keep shape name
					project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape] = collision_physics_obj;
					//std::cout << "test: " << project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].shape_name << ", " << project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].box_width << std::endl;
				}
			}
		}
		break;

		case SPRITE_SHAPE_CHAIN:
		case SPRITE_SHAPE_POLYGON:
		{
			if(mouse_state.LeftIsDown())
			{
				bool init_click = false;

				if(!(middle_drag_init||left_drag_init||right_drag_init))
				{

					if( px >= 0 && px < pw && py >= 0 && py < ph )
					{
						left_drag_init = true;
						this->SetFocusFromKbd();
						init_click = true;

						if(!collision_poly_draw_flag)
						{
							collision_selected_points.clear();

							collision_physics_obj.points.clear();

							collision_poly_draw_flag = true;

							if(m_mapEdit_polyShape_grid)
							{
								if(m_mapEdit_polyShape_grid->GetNumberRows() > 0)
								{
									m_mapEdit_polyShape_grid->DeleteRows(0, m_mapEdit_polyShape_grid->GetNumberRows());
								}
							}
						}

						if(tile_snap)
						{
							bx = bx / current_frame_width * current_frame_width;
							by = by / current_frame_height * current_frame_height;
						}

						collision_physics_obj.points.push_back(irr::core::vector2di(bx, by));

						if(m_mapEdit_polyShape_grid)
						{
							m_mapEdit_polyShape_grid->AppendRows();
							m_mapEdit_polyShape_grid->SetCellValue(m_mapEdit_polyShape_grid->GetNumberRows()-1, 0, wxString::Format(_("%i"), bx));
							m_mapEdit_polyShape_grid->SetCellValue(m_mapEdit_polyShape_grid->GetNumberRows()-1, 1, wxString::Format(_("%i"), by));
						}


						collision_object_modified = true;
						//parent_window->UpdateWindowUI();
					}
				}
			}
			else if(mouse_state.RightIsDown() && (!right_drag_init))
			{
				right_drag_init = true;
				//must be atleast a triangle
				if(collision_physics_obj.points.size() < 3)
				{
					//collision_physics_obj.points.push_back(collision_physics_obj.points[0]);
					for(int i = collision_physics_obj.points.size(); i < 3; i++)
					{
						collision_physics_obj.points.push_back(irr::core::vector2di(0, 0));

						if(m_mapEdit_polyShape_grid)
						{
							m_mapEdit_polyShape_grid->AppendRows();
							m_mapEdit_polyShape_grid->SetCellValue(m_mapEdit_polyShape_grid->GetNumberRows()-1, 0, wxString::Format(_("%i"), 0));
							m_mapEdit_polyShape_grid->SetCellValue(m_mapEdit_polyShape_grid->GetNumberRows()-1, 1, wxString::Format(_("%i"), 0));
						}
					}
				}

				collision_physics_obj.shape_name = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].shape_name; //to keep shape name
				project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape] = collision_physics_obj;

				collision_physics_obj.points.clear();

				//for(int i = 0; i < collision_physics_obj.points.size(); i++)
				//{
				//	std::cout << "point: " << collision_physics_obj.points[i].X << ", " << collision_physics_obj.points[i].Y << std::endl;
				//}

				collision_poly_draw_flag = false;

				collision_object_modified = true;
				parent_window->Refresh();
			}
		}
		break;


		case SPRITE_SHAPE_CIRCLE:
		{
			if(mouse_state.LeftIsDown())
			{
				bool init_click = false;

				if(!(middle_drag_init||left_drag_init||right_drag_init))
				{

					if( px >= 0 && px < pw && py >= 0 && py < ph )
					{
						left_drag_init = true;
						this->SetFocusFromKbd();
						init_click = true;

						if(!collision_poly_draw_flag)
						{
							collision_physics_obj.offset_x = bx;
							collision_physics_obj.offset_y = by;

							if(tile_snap)
							{
								collision_physics_obj.offset_x = collision_physics_obj.offset_x / current_frame_width * current_frame_width;
								collision_physics_obj.offset_y = collision_physics_obj.offset_y / current_frame_height * current_frame_height;
							}

							collision_poly_draw_flag = true;

							if(m_mapEdit_circleShape_centerX_spinCtrl)
								m_mapEdit_circleShape_centerX_spinCtrl->SetValue(collision_physics_obj.offset_x);

							if(m_mapEdit_circleShape_centerY_spinCtrl)
								m_mapEdit_circleShape_centerY_spinCtrl->SetValue(collision_physics_obj.offset_y);

						}

						collision_object_modified = true;
						//parent_window->UpdateWindowUI();
					}
				}
				else
				{
					collision_physics_obj.radius = irr::core::vector2di(bx,by).getDistanceFrom(irr::core::vector2di(collision_physics_obj.offset_x, collision_physics_obj.offset_y));

					if(tile_snap)
					{
						collision_physics_obj.radius = ( (int)(collision_physics_obj.radius / current_frame_width) * current_frame_width ); //If width and height are different this is going to be weird but I had to choose one
					}

					if(m_mapEdit_circleShape_radius_spinCtrl)
						m_mapEdit_circleShape_radius_spinCtrl->SetValue(collision_physics_obj.radius);
				}
			}
			else
			{
				//collision_object_modified = true;
				if(collision_poly_draw_flag)
				{
					collision_poly_draw_flag = false;
					collision_physics_obj.shape_name = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].shape_name; //to keep shape name
					project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape] = collision_physics_obj;
				}
			}
		}
		break;
	}

	if(!mouse_state.LeftIsDown())
	{
		//collision_object_modified = true;
		//collision_poly_draw_flag = false;
		left_drag_init = false;
	}

	if(!mouse_state.RightIsDown())
	{
		right_drag_init = false;
	}
}


void wxIrrlicht::updateStageViewportInfo()
{
	if(!stage_window_isActive)
	{
		return;
	}

	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();


	float scroll_speed_x = project->getLayerScrollSpeed(selected_stage, selected_layer).X;
	float scroll_speed_y = project->getLayerScrollSpeed(selected_stage, selected_layer).Y;

	int adj_scroll_offset_x = scroll_speed_x * scroll_offset_x;
	int adj_scroll_offset_y = scroll_speed_y * scroll_offset_y;

	int bx = ( (px+adj_scroll_offset_x) / current_frame_width) *  current_frame_width;
	int by = ( (py+adj_scroll_offset_y) / current_frame_height) *  current_frame_height;

	int cam_bx = ( (adj_scroll_offset_x) / current_frame_width) *  current_frame_width;
	int cam_by = ( (adj_scroll_offset_y) / current_frame_height) *  current_frame_height;

	m_cameraAbsoluteX_staticText->SetLabelText(wxString::Format(_("%i"), adj_scroll_offset_x));
	m_cameraAbsoluteY_staticText->SetLabelText(wxString::Format(_("%i"), adj_scroll_offset_y));

	if(mapEdit_layerType == LAYER_TYPE_TILEMAP)
	{
		m_cameraTileX_staticText->SetLabelText(wxString::Format(_("%i"), cam_bx) );
		m_cameraTileY_staticText->SetLabelText(wxString::Format(_("%i"), cam_by) );

		m_stageTileX_staticText->SetLabelText(wxString::Format(_("%i"), bx ));
		m_stageTileY_staticText->SetLabelText(wxString::Format(_("%i"), by ));
	}
	else
	{
		m_cameraTileX_staticText->SetLabelText( _("[NA]") );
		m_cameraTileY_staticText->SetLabelText( _("[NA]") );

		m_stageTileX_staticText->SetLabelText( _("[NA]") );
		m_stageTileY_staticText->SetLabelText( _("[NA]") );
	}

	m_stageAbsoluteX_staticText->SetLabelText(wxString::Format(_("%i"), (px+adj_scroll_offset_x)) );
	m_stageAbsoluteY_staticText->SetLabelText(wxString::Format(_("%i"), (py+adj_scroll_offset_y)) );


	m_screenAbsoluteX_staticText->SetLabelText(wxString::Format(_("%i"), px ));
	m_screenAbsoluteY_staticText->SetLabelText(wxString::Format(_("%i"), py ));
}

void wxIrrlicht::UpdateStageSheet()
{
	map_sprite_pos_changed = false;
	map_sprite_angle_changed = false;
	map_sprite_scale_changed = false;

	mapEdit_getContext();

	if(!mapEdit_hasContext)
		return;

	setActiveCanvas(ui_layer);
	clearCanvas();

	setActiveCanvas(sheet_canvas);

	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();

	if(stage_window_isActive)
	{
		this->SetFocusFromKbd();
	}

	if(VIEW_KEY_W)
	{
		scroll_offset_y -= scroll_speed;
	}

	if(VIEW_KEY_A)
	{
		scroll_offset_x -= scroll_speed;
	}

	if(VIEW_KEY_S)
	{
		scroll_offset_y += scroll_speed;
	}

	if(VIEW_KEY_D)
	{
		scroll_offset_x += scroll_speed;
	}

	updateStageViewportInfo();


	if(mouse_state.LeftIsDown() && stage_window_isActive)
	{
		if(mapEdit_layerType != LAYER_TYPE_TILEMAP)
			mapEdit_selectTileTool_selection.clear();
		else
		{
			if(map_tool != MAP_TOOL_TILE_BOXSELECT && map_tool != MAP_TOOL_TILE_SELECT && map_tool != MAP_TOOL_TILE_MOVE && map_tool != MAP_TOOL_TILE_COPY)
				mapEdit_selectTileTool_selection.clear();
		}
	}

	if(!stage_window_isActive)
	{
		if(collision_poly_draw_flag && (collision_physics_obj.shape_type == SPRITE_SHAPE_POLYGON || collision_physics_obj.shape_type == SPRITE_SHAPE_CHAIN) &&
		   selected_shape >= 0 && selected_shape < project->stages[selected_stage].layers[selected_layer].layer_shapes.size())
		{
			collision_physics_obj.shape_name = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].shape_name; //to keep shape name
			project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape] = collision_physics_obj;

			collision_physics_obj.points.clear();

			collision_object_modified = true;
			parent_window->Refresh();
		}

		collision_poly_draw_flag = false;
	}


	for(int i = 0; i < project->getStageNumLayers(selected_stage); i++)
	{
		setCanvasZ(project->stages[selected_stage].layers[i].ref_canvas, project->getStageNumLayers(selected_stage)-i);
		setCanvasAlpha(project->stages[selected_stage].layers[i].ref_canvas, project->stages[selected_stage].layers[i].layer_alpha);

		//if(i == selected_layer)
		//	continue;

		if(project->getLayerType(selected_stage, i) == LAYER_TYPE_TILEMAP)
		{
			util_drawTileLayer(i);
		}
		else if(project->getLayerType(selected_stage, i) == LAYER_TYPE_SPRITE)
		{
			util_setSpriteLayerOffset(i);
		}
	}

	switch(mapEdit_layerType)
	{
		case LAYER_TYPE_TILEMAP:
		{
			if(map_tool == MAP_TOOL_TILE_SET)
				StageSheet_SetTileUpdate();
			else if(map_tool == MAP_TOOL_TILE_FILL)
				StageSheet_FillTileUpdate();
			else if(map_tool == MAP_TOOL_TILE_SELECT)
				StageSheet_SelectTileUpdate();
			else if(map_tool == MAP_TOOL_TILE_BOXSELECT)
				StageSheet_BoxSelectTileUpdate();
			else if(map_tool == MAP_TOOL_TILE_MOVE)
				StageSheet_MoveTileUpdate();
			else if(map_tool == MAP_TOOL_TILE_COPY)
				StageSheet_CopyTileUpdate();
			else if(map_tool == MAP_TOOL_TILE_DELETE)
				StageSheet_DeleteSelectedTileUpdate();

			util_drawSelectedTiles();
		}
		break;

		case LAYER_TYPE_SPRITE:
		{
			if(map_tool == MAP_TOOL_SPRITE_SELECT)
				StageSheet_SelectSpriteUpdate();
			else if(map_tool == MAP_TOOL_SPRITE_BOXSELECT)
				StageSheet_BoxSelectSpriteUpdate();
			else if(map_tool == MAP_TOOL_SPRITE_MOVE)
				StageSheet_MoveSpriteUpdate();
			else if(map_tool == MAP_TOOL_SPRITE_ROTATE)
				StageSheet_RotateSpriteUpdate();
			else if(map_tool == MAP_TOOL_SPRITE_SCALE)
				StageSheet_ScaleSpriteUpdate();
			else if(map_tool == MAP_TOOL_SHAPE_SELECT)
				stage_collisionEdit_select();
			else if(map_tool == MAP_TOOL_SHAPE_BOXSELECT)
				stage_collisionEdit_boxSelect();
			else if(map_tool == MAP_TOOL_SHAPE_MOVE)
				stage_collisionEdit_move();
			else if(map_tool == MAP_TOOL_SHAPE_DRAW)
				stage_collisionEdit_draw();

			if(selected_stage >= 0 && selected_stage < project->stages.size())
			{
				if(selected_layer >= 0 && selected_layer < project->stages[selected_stage].layers.size())
				{
					selected_sprite = -1;
					//update all sprites in selected layer
					for(int layer_sprite_index = 0; layer_sprite_index < project->stages[selected_stage].layers[selected_layer].layer_sprites.size(); layer_sprite_index++)
					{
						int spr_index = project->stages[selected_stage].layers[selected_layer].layer_sprites[layer_sprite_index].map_sprite_id;
						if(spr_index < 0 || spr_index >= sprite.size())
							continue;

						if(mapEdit_selectSpriteTool_selection.size()==1)
						{
							if(mapEdit_selectSpriteTool_selection[0].layer_sprite_index == spr_index)
								selected_sprite = layer_sprite_index;
						}

						int spr_x = sprite[spr_index].position.X;
						int spr_y = sprite[spr_index].position.Y;
						double spr_angle = sprite[spr_index].angle;
						//spr_angle = spr_angle < 0 ? spr_angle + 360 : spr_angle;
						//spr_angle = spr_angle >= 360 ? spr_angle - 360 : spr_angle;
						double spr_scale_x = sprite[spr_index].scale.X;
						double spr_scale_y = sprite[spr_index].scale.Y;

						project->stages[selected_stage].layers[selected_layer].layer_sprites[layer_sprite_index].position.set(spr_x, spr_y);
						project->stages[selected_stage].layers[selected_layer].layer_sprites[layer_sprite_index].scale.set(spr_scale_x, spr_scale_y);
						project->stages[selected_stage].layers[selected_layer].layer_sprites[layer_sprite_index].angle = spr_angle;
					}

					if(mapEdit_selectSpriteTool_selection.size()==1)
					{
						if(selected_sprite >= 0 && selected_sprite < project->stages[selected_stage].layers[selected_layer].layer_sprites.size())
						{
							if(nv_sprite_positionX_property && map_sprite_pos_changed)
								nv_sprite_positionX_property->SetValue(project->stages[selected_stage].layers[selected_layer].layer_sprites[selected_sprite].position.X);

							if(nv_sprite_positionY_property && map_sprite_pos_changed)
								nv_sprite_positionY_property->SetValue(project->stages[selected_stage].layers[selected_layer].layer_sprites[selected_sprite].position.Y);

							if(nv_sprite_scaleX_property && map_sprite_scale_changed)
								nv_sprite_scaleX_property->SetValue(project->stages[selected_stage].layers[selected_layer].layer_sprites[selected_sprite].scale.X);

							if(nv_sprite_scaleY_property && map_sprite_scale_changed)
								nv_sprite_scaleY_property->SetValue(project->stages[selected_stage].layers[selected_layer].layer_sprites[selected_sprite].scale.Y);

							if(nv_sprite_angle_property && map_sprite_angle_changed)
								nv_sprite_angle_property->SetValue(360-project->stages[selected_stage].layers[selected_layer].layer_sprites[selected_sprite].angle);
						}
					}

					util_drawSelectedSprites();
				}
			}
		}
		break;
		//TODO: add sprite and canvas layer
	}
}

void wxIrrlicht::util_draw_cursor(int tile_x, int tile_y, irr::video::SColor cursor_color)
{
	irr::core::dimension2du img_size = image[current_sheet_image].image->getSize();
	irr::core::dimension2du img_og_size = image[current_sheet_image].image->getOriginalSize();
	int t_across = img_og_size.Width / current_frame_width;
	int t_down = img_og_size.Height / current_frame_height;
	irr::core::dimension2du t_size(img_size.Width / t_across, img_size.Height / t_down);

	float off_tile_x = ( (img_size.Width / t_across) / current_frame_width );
	float off_tile_y = ( (img_size.Height / t_down) / current_frame_height );

	tile_x = (int)(off_tile_x*tile_x);
	tile_y = (int)(off_tile_y*tile_y);

	for(int iy = 0; iy < t_size.Height; iy++)
	{
		m_pDriver->drawPixel(tile_x, tile_y+iy, cursor_color);
		m_pDriver->drawPixel(t_size.Width-1, tile_y+iy, cursor_color);

		if(iy > 0 && iy < (t_size.Height-1))
			continue;

		for(int ix = 1; ix < t_size.Width-1; ix++)
		{
			m_pDriver->drawPixel(tile_x+ix, tile_y+iy, cursor_color);
		}
	}
}

void wxIrrlicht::mapEdit_getContext()
{
	if(control_id == NV_MAP_EDIT_MAP_SHEET || control_id == NV_MAP_EDIT_TILE_SHEET)
	{
		if(shared_control)
		{
			if(shared_control->mapEdit_hasContext)
			{
				shared_control->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());
				shared_control->mapEdit_hasContext = false;
				GetDevice()->getContextManager()->activateContext(GetDevice()->getVideoDriver()->getExposedVideoData());
				mapEdit_hasContext = true;
			}
		}
	}
}

void wxIrrlicht::UpdateStageTileSelect()
{
	if(clear_flag)
	{
		mapEdit_getContext();
		setActiveCanvas(sheet_canvas);
		clearCanvas();
		clear_flag = false;
		return;
	}

	//std::cout << "DEBUG: " << mapEdit_layerType << ", " << current_sheet_image << std::endl;

	if(mapEdit_layerType != LAYER_TYPE_TILEMAP)
		return;

	if(current_sheet_image < 0 || current_sheet_image >= image.size())
		return;

	//std::cout << "DEB2" << std::endl;

	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();

	if(stage_window_isActive)
	{
		this->SetFocusFromKbd();
	}


	//setActiveCanvas(sheet_canvas);
	//clearCanvas();

	if(VIEW_KEY_W)
	{
		scroll_offset_y -= scroll_speed;
	}

	if(VIEW_KEY_A)
	{
		scroll_offset_x -= scroll_speed;
	}

	if(VIEW_KEY_S)
	{
		scroll_offset_y += scroll_speed;
	}

	if(VIEW_KEY_D)
	{
		scroll_offset_x += scroll_speed;
	}

	int bx = ( (px+scroll_offset_x) / current_frame_width) *  current_frame_width;
	int by = ( (py+scroll_offset_y) / current_frame_height) *  current_frame_height;

	int off_x_i = (int)scroll_offset_x;
	int off_y_i = (int)scroll_offset_y;

	int select_x = bx - off_x_i;
	int select_y = by - off_y_i;

	int img_x = -scroll_offset_x;
	int img_y = -scroll_offset_y;
	int img_w = 0;
	int img_h = 0;

	mapEdit_getContext();

	if(!mapEdit_hasContext)
		return;

	if(imageExists(current_sheet_image))
	{
		setActiveCanvas(sheet_canvas);
		clearCanvas();

		getImageSizeI(current_sheet_image, &img_w, &img_h);
		irr::core::dimension2du t_size = image[current_sheet_image].image->getSize();

		//m_pDriver->draw2DImage(image[current_sheet_image].image, irr::core::vector2di(0,0));
		drawImage_BlitEx_SW(current_sheet_image, img_x, img_y, img_w, img_h, 0, 0, img_w, img_h);
		//drawImage_Rotozoom(current_sheet_image, 0, 0, 0, 1, 1);
	}

	setActiveCanvas(overlay_canvas);
	clearCanvas();

	if(px >= img_x && px < (img_x+img_w) && py >= img_y && py < (img_y+img_h))
	{
		setColor(rgb(255, 0, 0));

		int dw = px - drag_start.x;
		int dh = py - drag_start.y;

		if(left_drag_init)
		{
			int dbx = ( (drag_start.x+scroll_offset_x) / current_frame_width) *  current_frame_width;
			int dby = ( (drag_start.y+scroll_offset_y) / current_frame_height) *  current_frame_height;

			int d_select_x = dbx - off_x_i;
			int d_select_y = dby - off_y_i;

			int d_select_w = (( (px+scroll_offset_x) / current_frame_width) *  current_frame_width + current_frame_width) - dbx;
			int d_select_h = (( (py+scroll_offset_y) / current_frame_height) *  current_frame_height + current_frame_height) - dby;
			//drawRect(drag_start.x, drag_start.y, dw, dh);
			drawRect(d_select_x, d_select_y, d_select_w, d_select_h);
		}
		else
			drawRect(select_x, select_y, current_frame_width, current_frame_height);

		//util_draw_cursor(select_x, select_y, irr::video::SColor(255,255,0,0));
	}

	if(mapEdit_tile_selection.width_in_tiles > 0 && mapEdit_tile_selection.height_in_tiles > 0)
	{
		int start_tile = mapEdit_tile_selection.row[0].data[0];

		int selected_tile_x = current_frame_width * (start_tile % (img_w/current_frame_width)) - scroll_offset_x;
		int selected_tile_y = current_frame_height * (start_tile / (img_w/current_frame_height)) - scroll_offset_y;

		int selected_w = mapEdit_tile_selection.width_in_tiles * current_frame_width;
		int selected_h = mapEdit_tile_selection.height_in_tiles * current_frame_height;

		setColor(rgb(255, 255, 255));
		drawRect(selected_tile_x, selected_tile_y, selected_w, selected_h);
		//drawRect(selected_tile_x, selected_tile_y, current_frame_width, current_frame_height);
	}


	if(mouse_state.LeftIsDown() && stage_window_isActive)
	{
        bool init_click = false;

		if(!(middle_drag_init||left_drag_init||right_drag_init))
		{

			if( px >= 0 && px < pw && py >= 0 && py < ph )
			{
				drag_start.x = px;
				drag_start.y = py;

				mapEdit_tile_selection.row.clear();

				mapEdit_tile_selection.width_in_tiles = 0;
				mapEdit_tile_selection.height_in_tiles = 0;

				int fx = select_x + scroll_offset_x;
				int fy = select_y + scroll_offset_y;
				int fw = img_w;
				int fh = img_h;

				if(stage_window_isActive)
				{
					if(px >= img_x && px < (img_x+img_w) && py >= img_y && py < (img_y+img_h))
						selected_frame = (fy/current_frame_height) * (fw/current_frame_width) + (fx/current_frame_width);
					else
						selected_frame = -1;
				}
				else
					selected_frame = -1;

				if(selected_frame >= 0)
				{
					selected_tile = selected_frame;
					selected_tile_end = -1;
					//tileEdit_mask_set = true;
					//tileEdit_Sheet_Update = true;
					//parent_window->UpdateWindowUI();
				}

				//std::cout << "TEST: " << selected_tile << std::endl;

				left_drag_init = true;
			}
		}
	}
	else if( ((!mouse_state.LeftIsDown()) || (!stage_window_isActive)) && left_drag_init )
	{
		//SHOW_CURSOR;
		//this->ReleaseMouse();
		left_drag_init = false;



		int fx = select_x + scroll_offset_x;
		int fy = select_y + scroll_offset_y;
		int fw = img_w;
		int fh = img_h;

		if(stage_window_isActive)
		{
			if(px >= img_x && px < (img_x+img_w) && py >= img_y && py < (img_y+img_h))
				selected_frame = (fy/current_frame_height) * (fw/current_frame_width) + (fx/current_frame_width);
			else
				selected_frame = -1;
		}
		else
			selected_frame = -1;

		if(selected_frame < 0)
		{
			mapEdit_tile_selection.width_in_tiles = 1;
			mapEdit_tile_selection.height_in_tiles = 1;
			Nirvana_TileSelection_Row t_row;
			t_row.data.push_back(selected_tile);
			mapEdit_tile_selection.row.push_back(t_row);
		}
		else
		{
			int d_start_x = (selected_tile % (img_w / current_frame_width)) * current_frame_width;
			int d_start_y = (selected_tile / (img_w / current_frame_width)) * current_frame_height;

			int d_end_x = (selected_frame % (img_w / current_frame_width)) * current_frame_width;
			int d_end_y = (selected_frame / (img_w / current_frame_width)) * current_frame_height;

			int rect_x = d_start_x < d_end_x ? d_start_x : d_end_x;
			int rect_y = d_start_y < d_end_y ? d_start_y : d_end_y;

			int rect_w = d_end_x - d_start_x;
			if(rect_w < 0)
				rect_w *= -1;
			rect_w += current_frame_width;

			int rect_h = d_end_y - d_start_y;
			if(rect_h < 0)
				rect_h *= -1;
			rect_h += current_frame_height;

			int num_rows = rect_h / current_frame_height;
			int num_cols = rect_w / current_frame_width;

			num_rows = (num_rows <= 0 ? 1 : num_rows);
			num_cols = (num_cols <= 0 ? 1 : num_cols);

			int fw = img_w / current_frame_width;
			for(int tr = 0; tr < num_rows; tr++)
			{
				Nirvana_TileSelection_Row t_row;
				int fy = (rect_y + (current_frame_height*tr)) / current_frame_height;
				for(int tc = 0; tc < num_cols; tc++)
				{
					int fx = (rect_x + (current_frame_width*tc)) / current_frame_width;
					t_row.data.push_back(fy*fw+fx);
					//std::cout << (fy*fw+fx) << ", ";
				}
				//std::cout << std::endl;
				mapEdit_tile_selection.row.push_back(t_row);
			}

			mapEdit_tile_selection.width_in_tiles = num_cols;
			mapEdit_tile_selection.height_in_tiles = num_rows;

			//std::cout << std::endl;

			//std::cout << "START_POS: " << start_x << ", " << start_y << std::endl;
		}

		//wxMessageBox(_("RELEASE"));
		return;
	}
}

void wxIrrlicht::UpdateStageSpritePreview()
{
}


int wxIrrlicht::irr_LoadFont(std::string fnt_file, int font_size)
{
	irr::io::path file_path = fnt_file.c_str();
    int font_id = -1;
    for(int i = 0; i < MAX_FONTS; i++)
    {
        if(!font[i].active)
        {
            font_id = i;
            break;
        }
    }

    if(font_id < 0)
		return -1;

    CGUITTFace* Face;
    CGUIFreetypeFont* dfont;

    Face = new CGUITTFace();
    Face->load(file_path);

    dfont = new CGUIFreetypeFont(m_pDriver);
    dfont->attach(Face, font_size);

    if(!dfont)
	{
		if(Face)
		{
			delete Face;
			return -1;
		}
	}

	font[font_id].face = Face;
	font[font_id].font = dfont;
	font[font_id].font_size = font_size;
	font[font_id].active = true;

	if(active_font < 0)
		active_font = font_id;

    return font_id;
}


void wxIrrlicht::irr_DeleteFont(int font_id)
{
	if(font_id < 0 || font_id >= MAX_FONTS)
		return;

    if(font[font_id].active)
    {
        delete font[font_id].font;
        delete font[font_id].face;
        font[font_id].font = NULL;
        font[font_id].face = NULL;
        font[font_id].font_size = 0;
        font[font_id].active = false;
    }
}

void wxIrrlicht::irr_SetFont(int font_id)
{
	if(font_id < 0 || font_id >= MAX_FONTS)
		return;

    if(font[font_id].active)
        active_font = font_id;
}

void wxIrrlicht::irr_DrawText(std::string txt, int x, int y, irr::video::SColor color, int camera_index)
{
	if(active_font < 0 || active_font >= MAX_FONTS)
		return;

    if(!font[active_font].active)
        return;

	if(camera_index < 0)
		m_pDriver->setRenderTarget(canvas[ui_layer].texture, false, false);

    std::wstring text = utf8_to_wstring(txt);
	irr::core::dimension2d<irr::u32> text_dim = font[active_font].font->getDimension(text.c_str());
	irr::core::rect<s32> tpos(x, y, text_dim.Width, font[active_font].font_size);
    font[active_font].font->draw(text.c_str(), tpos, color);

    if(camera_index < 0)
		setActiveCanvas(active_canvas);
        //std::cout << "------------------" << std::endl;

}




// RCBasic Drawing Routines
void wxIrrlicht::sortCanvasZ()
{
    for(int i = 0; i < canvas_zOrder.size(); i++)
    {
        for(int j = i+1; j < canvas_zOrder.size(); j++)
        {
            int ca = canvas_zOrder[i];
            int cb = canvas_zOrder[j];
            if(canvas[cb].z >= canvas[ca].z)
            {
                canvas_zOrder.erase(j);
                canvas_zOrder.insert(cb, i);
            }
        }
    }
}

int wxIrrlicht::createCanvas(int w, int h, int vx, int vy, int vw, int vh, int canvas_type)
{
	if(!m_pDriver)
        return -1;

    canvas_obj n_canvas;

    n_canvas.visible = true;

    n_canvas.type = canvas_type;

    n_canvas.texture = m_pDriver->addRenderTargetTexture(irr::core::dimension2d<u32>(w,h), "rt", irr::video::ECF_A8R8G8B8);

    if(n_canvas.texture == NULL)
        return -1;

    n_canvas.dimension.Width = w;
    n_canvas.dimension.Height = h;

    n_canvas.viewport.position.X = vx;
    n_canvas.viewport.position.Y = vy;
    n_canvas.viewport.dimension.Width = vw;
    n_canvas.viewport.dimension.Height = vh;

    n_canvas.offset.X = 0;
    n_canvas.offset.Y = 0;

    n_canvas.color_mod = irr::video::SColor(255,255,255,255).color;

	m_pDriver->makeColorKeyTexture(n_canvas.texture, irr::video::SColor(0,0,0,0));

	int canvas_id = -1;

    for(int i = 0; i < canvas.size(); i++)
    {
        if(!canvas[i].texture)
        {
            canvas_id = i;
            break;
        }
    }

    if(canvas_id < 0)
    {
        canvas_id = canvas.size();
        canvas.push_back(n_canvas);
    }
    else
	{
		canvas[canvas_id] = n_canvas;
	}

    for(int i = 0; i < canvas_zOrder.size(); i++)
    {
        if(canvas_zOrder[i] == canvas_id)
        {
            canvas_zOrder.erase(i);
            i--;
        }
    }

    canvas_zOrder.push_back(canvas_id);

    sortCanvasZ();


    return canvas_id;
}

void wxIrrlicht::canvasClose(int canvas_id)
{
    if(canvas_id <= 0 || canvas_id >= canvas.size()) //canvas 0 is being excluded because its the back buffer
        return;

    if(canvas[canvas_id].texture != NULL)
        m_pDriver->removeTexture(canvas[canvas_id].texture);

    canvas[canvas_id].texture = NULL;


	//sprites are destroyed when the world is deleted so I just to set the active attribute to false and set the body to NULL
	for(int i = 0; i < canvas[canvas_id].sprite_id.size(); i++)
	{
		int spr_id = canvas[canvas_id].sprite_id[i];
		sprite[spr_id].active = false;
	}

	canvas[canvas_id].sprite_id.clear();

    if(active_canvas == canvas_id)
        active_canvas = -1;

    for(int i = 0; i < canvas_zOrder.size(); i++)
    {
        if(canvas_zOrder[i] == canvas_id)
        {
            canvas_zOrder.erase(i);
            break;
        }
    }
}

void wxIrrlicht::setActiveCanvas(int canvas_id)
{
	if(canvas.size() == 0)
	{
		active_canvas = -1;
	}
	else if(canvas_id < canvas.size())
	{
		active_canvas = canvas_id;
		m_pDriver->setRenderTarget(canvas[active_canvas].texture, false, false, irr::video::SColor(255, 255, 0, 0));
	}
}

void wxIrrlicht::clearCanvas()
{
    if(active_canvas >= 0 && active_canvas < canvas.size())
    {
        m_pDriver->clearBuffers(true, true, true, clear_color);
    }
}

void wxIrrlicht::setCanvasVisible(int canvas_id, bool flag)
{
    if(canvas_id <= 0 || canvas_id >= canvas.size()) //canvas 0 is being excluded because its the back buffer
        return;

    if(canvas[canvas_id].texture)
        canvas[canvas_id].visible = flag;
}

bool wxIrrlicht::canvasIsVisible(int canvas_id)
{
    if(canvas_id <= 0 || canvas_id >= canvas.size()) //canvas 0 is being excluded because its the back buffer
        return false;

    if(canvas[canvas_id].texture)
        return canvas[canvas_id].visible;

    return false;
}

void wxIrrlicht::setCanvasViewport(int canvas_id, int x, int y, int w, int h)
{
    if(canvas_id <= 0 || canvas_id >= canvas.size()) //canvas 0 is being excluded because its the back buffer
        return;

    if(canvas[canvas_id].texture)
    {
        canvas[canvas_id].viewport.position = irr::core::vector2d<irr::s32>(x, y);
        canvas[canvas_id].viewport.dimension = irr::core::dimension2d<irr::u32>(w, h);
    }
}

void wxIrrlicht::getCanvasViewport(int canvas_id, double* x, double* y, double* w, double* h)
{
    if(canvas_id <= 0 || canvas_id >= canvas.size()) //canvas 0 is being excluded because its the back buffer
        return;

    if(canvas[canvas_id].texture)
    {
        *x = (double)canvas[canvas_id].viewport.position.X;
        *y = (double)canvas[canvas_id].viewport.position.Y;
        *w = canvas[canvas_id].viewport.dimension.Width;
        *h = canvas[canvas_id].viewport.dimension.Height;
    }
}

void wxIrrlicht::setCanvasOffset(int canvas_id, int x, int y)
{
    if(canvas_id <= 0 || canvas_id >= canvas.size()) //canvas 0 is being excluded because its the back buffer
        return;

    if(canvas[canvas_id].texture)
    {
        canvas[canvas_id].offset = irr::core::vector2d<irr::s32>(x, y);
    }
}

void wxIrrlicht::getCanvasOffset(int canvas_id, double* x, double* y)
{
    if(canvas_id <= 0 || canvas_id >= canvas.size()) //canvas 0 is being excluded because its the back buffer
        return;

    if(canvas[canvas_id].texture)
    {
        *x = (double)canvas[canvas_id].offset.X;
        *y = (double)canvas[canvas_id].offset.Y;
    }
}

void wxIrrlicht::getCanvasSize(int canvas_id, double* w, double* h)
{
    if(canvas_id <= 0 || canvas_id >= canvas.size()) //canvas 0 is being excluded because its the back buffer
        return;

    if(canvas[canvas_id].texture)
    {
        *w = (double)canvas[canvas_id].dimension.Width;
        *h = (double)canvas[canvas_id].dimension.Height;
    }
}

void wxIrrlicht::setCanvasColorMod(int canvas_id, irr::u32 color_mod)
{
    if(canvas_id <= 0 || canvas_id >= canvas.size()) //canvas 0 is being excluded because its the back buffer
        return;

    if(canvas[canvas_id].texture)
    {
        canvas[canvas_id].color_mod = color_mod;
    }
}

irr::u32 wxIrrlicht::getCanvasColorMod(int canvas_id)
{
    if(canvas_id <= 0 || canvas_id >= canvas.size()) //canvas 0 is being excluded because its the back buffer
        return 0;

    if(canvas[canvas_id].texture)
    {
        return canvas[canvas_id].color_mod;
    }

    return 0;
}

void wxIrrlicht::setCanvasAlpha(int canvas_id, irr::u32 alpha)
{
    if(canvas_id <= 0 || canvas_id >= canvas.size()) //canvas 0 is being excluded because its the back buffer
        return;

    if(canvas[canvas_id].texture)
    {
        irr::video::SColor color(canvas[canvas_id].color_mod);
        color.setAlpha(alpha);
        canvas[canvas_id].color_mod = color.color;
    }
}

irr::u32 wxIrrlicht::canvasAlpha(int canvas_id)
{
    if(canvas_id <= 0 || canvas_id >= canvas.size()) //canvas 0 is being excluded because its the back buffer
        return 0;

    if(canvas[canvas_id].texture)
    {
        irr::video::SColor color(canvas[canvas_id].color_mod);
        irr::u32 alpha = color.getAlpha();
        return alpha;
    }
    return 0;
}

void wxIrrlicht::setCanvasZ(int canvas_id, int z)
{
    if(canvas_id <= 0 || canvas_id >= canvas.size()) //canvas 0 is being excluded because its the back buffer
        return;

    canvas[canvas_id].z = z;
    sortCanvasZ();
}

int wxIrrlicht::getCanvasZ(int canvas_id)
{
    if(canvas_id <= 0 || canvas_id >= canvas.size()) //canvas 0 is being excluded because its the back buffer
        return 0;

    if(canvas[canvas_id].texture)
    {
        return canvas[canvas_id].z;
    }

    return 0;
}

void wxIrrlicht::setClearColor(irr::u32 color)
{
    clear_color.set(color);
}

irr::u32 wxIrrlicht::rgba(irr::u32 r, irr::u32 g, irr::u32 b, irr::u32 a)
{
    irr::video::SColor color(a, r, g, b);
    return color.color;
}

irr::u32 wxIrrlicht::rgb(irr::u32 r, irr::u32 g, irr::u32 b)
{
    irr::video::SColor color(255, r, g, b);
    return color.color;
}

void wxIrrlicht::setColor(irr::u32 color)
{
    active_color.set(color);
}



void wxIrrlicht::drawRect(int x, int y, int w, int h)
{
    irr::core::vector2d<s32> r_pos(x,y);
    irr::core::dimension2d<s32> r_dim(w,h);
    irr::core::rect<s32> r(r_pos, r_dim);
    m_pDriver->draw2DRectangleOutline(r, active_color);
}

void wxIrrlicht::drawRectFill(int x, int y, int w, int h)
{
    irr::core::vector2d<s32> r_pos(x,y);
    irr::core::dimension2d<s32> r_dim(w,h);
    irr::core::rect<s32> r(r_pos, r_dim);
    //std::cout << "drawRect: color=" << rc_active_color.color << " ( " << x << ", " << y << ", " << w << ", " << h << " ) " << std::endl;
    m_pDriver->draw2DRectangle(active_color, r);
}



void wxIrrlicht::drawLine(int x1, int y1, int x2, int y2)
{
    irr::core::vector2d<s32> r_pos_start(x1,y1);
    irr::core::vector2d<s32> r_pos_end(x2,y2);

    m_pDriver->draw2DLine(r_pos_start, r_pos_end, active_color);
}


void wxIrrlicht::drawPixel(int x, int y)
{
    m_pDriver->drawPixel(x, y, active_color);
}

double wxIrrlicht::radians(double degree)
{
    double pi = 3.14159265359;
    return (degree * (pi / 180));
}

void wxIrrlicht::makeEllipse(irr::core::array<irr::video::S3DVertex>& vertices, irr::core::array<irr::u16>& indices, const CircleSettings& settings)
{
    const f64 stepSize = 360.0 / (f64)(settings.numVertices-1); // degree angles between vertex points on circle
    indices.set_used(settings.numVertices+1);   // one more as first and last vertex in circle is identical
    for ( u32 i=0; i<settings.numVertices; ++i)
        indices[i] = i;
    indices[settings.numVertices] = 1;

    const vector2df centerf((f32)settings.center.X, (f32)settings.center.Y);
    vertices.set_used(settings.numVertices);
    vertices[0] = video::S3DVertex(centerf.X, centerf.Y, 0.f, 0.f, 1.f, 0.f, settings.color, 0.5f, 0.5f);
    int rx = settings.radius2;
    int ry = settings.radius;
    for ( u32 i=1; i < settings.numVertices; i++ )
    {
        irr::f32 x = rx * std::cos( radians(i*stepSize) ) + centerf.X ;
        irr::f32 y = ry * std::sin( radians(i*stepSize) ) + centerf.Y ;

        vertices[i] = video::S3DVertex(x, y, 0.f, 0.f, 1.f, 0.f, settings.color, 0.5f, 0.5f);
    }
}

void wxIrrlicht::drawEllipse(int x, int y, int rx, int ry)
{
    irr::core::vector2d<s32> r_pos(x,y);

    // create the circle
    irr::core::array<irr::video::S3DVertex> verticesCircle;
    irr::core::array<irr::u16> indicesCircle;
    CircleSettings circle;
    circle.center = r_pos;
    circle.radius = ry;
    circle.radius2 = rx;
    circle.color = active_color;
    circle.numVertices = 21;
    makeEllipse(verticesCircle, indicesCircle, circle);

    for(int i = 2; i < verticesCircle.size(); i++)
    {
    	//std::cout << "V[" << i << "] = (" << verticesCircle[i-1].Pos.X << ", " << verticesCircle[i-1].Pos.Y << ") (" << verticesCircle[i].Pos.X << ", " << verticesCircle[i].Pos.Y << ")" << std::endl;
        drawLine(verticesCircle[i-1].Pos.X, verticesCircle[i-1].Pos.Y, verticesCircle[i].Pos.X, verticesCircle[i].Pos.Y);
    }

    int n = verticesCircle.size()-1;
    drawLine(verticesCircle[n].Pos.X, verticesCircle[n].Pos.Y, verticesCircle[1].Pos.X, verticesCircle[1].Pos.Y);
}


void wxIrrlicht::drawEllipseFill(int x, int y, int rx, int ry)
{
    irr::core::vector2d<s32> r_pos(x,y);

    // create the circle
    irr::core::array<irr::video::S3DVertex> verticesCircle;
    irr::core::array<irr::u16> indicesCircle;
    CircleSettings circle;
    circle.center = r_pos;
    circle.radius = ry;
    circle.radius2 = rx;
    circle.color = active_color;
    circle.numVertices = 21;
    makeEllipse(verticesCircle, indicesCircle, circle);

    m_pDriver->draw2DVertexPrimitiveList(verticesCircle.pointer(), verticesCircle.size(),
        indicesCircle.pointer(), indicesCircle.size()-2, video::EVT_STANDARD, scene::EPT_TRIANGLE_FAN,
        video::EIT_16BIT);
}

void wxIrrlicht::drawCircle(int x, int y, double r)
{
    drawEllipse(x, y, r, r);
}

void wxIrrlicht::drawCircleFill(int x, int y, double r)
{
	drawEllipseFill(x, y, r, r);
}



void wxIrrlicht::util_draw2DImage(irr::video::IVideoDriver *driver, irr::video::ITexture* texture, irr::core::rect<irr::s32> sourceRect, irr::core::position2d<irr::s32> position, irr::core::position2d<irr::s32> rotationPoint, irr::f32 rotation, irr::core::vector2df scale, bool useAlphaChannel, irr::video::SColor color, irr::core::vector2d<irr::f32> screenSize)
{
    if(active_canvas < 0 || active_canvas >= canvas.size())
        return;

    // Store and clear the projection matrix
    irr::core::matrix4 oldProjMat = driver->getTransform(irr::video::ETS_PROJECTION);
    driver->setTransform(irr::video::ETS_PROJECTION,irr::core::matrix4());

    // Store and clear the view matrix
    irr::core::matrix4 oldViewMat = driver->getTransform(irr::video::ETS_VIEW);
    driver->setTransform(irr::video::ETS_VIEW,irr::core::matrix4());

    // Store and clear the world matrix
    irr::core::matrix4 oldWorldMat = driver->getTransform(irr::video::ETS_WORLD);
    driver->setTransform(irr::video::ETS_WORLD,irr::core::matrix4());

    // Find horizontal and vertical axes after rotation
    irr::f32 c = cos(-rotation*irr::core::DEGTORAD);
    irr::f32 s = sin(-rotation*irr::core::DEGTORAD);
    irr::core::vector2df horizontalAxis(c,s);
    irr::core::vector2df verticalAxis(s,-c);

    // First, we'll find the offset of the center and then where the center would be after rotation
    irr::core::vector2df centerOffset(position.X+sourceRect.getWidth()/2.0f*scale.X-rotationPoint.X,position.Y+sourceRect.getHeight()/2.0f*scale.Y-rotationPoint.Y);
    irr::core::vector2df center = centerOffset.X*horizontalAxis - centerOffset.Y*verticalAxis;
    center.X += rotationPoint.X;
    center.Y += rotationPoint.Y;

    // Now find the corners based off the center
    irr::core::vector2df cornerOffset(sourceRect.getWidth()*scale.X/2.0f,sourceRect.getHeight()*scale.Y/2.0f);
    verticalAxis *= cornerOffset.Y;
    horizontalAxis *= cornerOffset.X;
    irr::core::vector2df corner[4];
    corner[0] = center + verticalAxis - horizontalAxis;
    corner[1] = center + verticalAxis + horizontalAxis;
    corner[2] = center - verticalAxis - horizontalAxis;
    corner[3] = center - verticalAxis + horizontalAxis;

    // Find the uv coordinates of the sourceRect
    irr::core::vector2df textureSize(texture->getSize().Width, texture->getSize().Height);
    irr::core::vector2df uvCorner[4];
    uvCorner[0] = irr::core::vector2df(sourceRect.UpperLeftCorner.X,sourceRect.UpperLeftCorner.Y);
    uvCorner[1] = irr::core::vector2df(sourceRect.LowerRightCorner.X,sourceRect.UpperLeftCorner.Y);
    uvCorner[2] = irr::core::vector2df(sourceRect.UpperLeftCorner.X,sourceRect.LowerRightCorner.Y);
    uvCorner[3] = irr::core::vector2df(sourceRect.LowerRightCorner.X,sourceRect.LowerRightCorner.Y);
    for (irr::s32 i = 0; i < 4; i++)
            uvCorner[i] /= textureSize;

    // Vertices for the image
    irr::video::S3DVertex vertices[4];
    irr::u16 indices[6] = { 0, 1, 2, 3 ,2 ,1 };

    // Convert pixels to world coordinates
    //irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].dimension.Width, rc_canvas[rc_active_canvas].dimension.Height);

    for (irr::s32 i = 0; i < 4; i++) {
            vertices[i].Pos = irr::core::vector3df(((corner[i].X/screenSize.X)-0.5f)*2.0f,((corner[i].Y/screenSize.Y)-0.5f)*-2.0f,1);
            vertices[i].TCoords = uvCorner[i];
            vertices[i].Color = color;
    }

    // Create the material
    // IMPORTANT: For irrlicht 1.8 and above you MUST ADD THIS LINE:
    // material.BlendOperation = irr::video::EBO_ADD;
    irr::video::SMaterial material;
    material.Lighting = false;
    material.ZWriteEnable = irr::video::EZW_OFF;
    material.ZBuffer = false;
    material.BackfaceCulling = false;
    material.TextureLayer[0].Texture = texture;
    material.TextureLayer[0].BilinearFilter = bilinear_filter;
    material.MaterialTypeParam = irr::video::pack_textureBlendFunc(irr::video::EBF_SRC_ALPHA, irr::video::EBF_ONE_MINUS_SRC_ALPHA, irr::video::EMFN_MODULATE_1X, irr::video::EAS_TEXTURE | irr::video::EAS_VERTEX_COLOR);
    material.BlendOperation = blend_mode;
    material.AntiAliasing = anti_alias;
    //material.BlendOperation = irr::video::EBO_ADD;

    if (useAlphaChannel)
            material.MaterialType = irr::video::EMT_ONETEXTURE_BLEND;
    else
            material.MaterialType = irr::video::EMT_SOLID;

    driver->setMaterial(material);
    driver->drawIndexedTriangleList(&vertices[0],4,&indices[0],2);

    // Restore projection, world, and view matrices
    driver->setTransform(irr::video::ETS_PROJECTION,oldProjMat);
    driver->setTransform(irr::video::ETS_VIEW,oldViewMat);
    driver->setTransform(irr::video::ETS_WORLD,oldWorldMat);

    rc_setDriverMaterial();
}

void wxIrrlicht::util_draw2DImage2(irr::video::IVideoDriver *driver, irr::video::ITexture* texture, irr::core::rect<irr::s32> sourceRect, irr::core::rect<irr::s32> destRect, irr::core::position2d<irr::s32> rotationPoint, irr::f32 rotation, bool useAlphaChannel, irr::video::SColor color, irr::core::vector2d<irr::f32> screenSize )
{
    if(active_canvas < 0 || active_canvas >= canvas.size())
        return;

    // Store and clear the projection matrix
    irr::core::matrix4 oldProjMat = driver->getTransform(irr::video::ETS_PROJECTION);
    driver->setTransform(irr::video::ETS_PROJECTION,irr::core::matrix4());

    // Store and clear the view matrix
    irr::core::matrix4 oldViewMat = driver->getTransform(irr::video::ETS_VIEW);
    driver->setTransform(irr::video::ETS_VIEW,irr::core::matrix4());

    // Store and clear the world matrix
    irr::core::matrix4 oldWorldMat = driver->getTransform(irr::video::ETS_WORLD);
    driver->setTransform(irr::video::ETS_WORLD,irr::core::matrix4());

    // Find horizontal and vertical axes after rotation
    irr::f32 c = cos(-rotation*irr::core::DEGTORAD);
    irr::f32 s = sin(-rotation*irr::core::DEGTORAD);
    irr::core::vector2df horizontalAxis(c,s);
    irr::core::vector2df verticalAxis(s,-c);

    // First, we'll find the offset of the center and then where the center would be after rotation
    irr::core::vector2df centerOffset(destRect.UpperLeftCorner.X+destRect.getWidth()/2.0f-rotationPoint.X,destRect.UpperLeftCorner.Y+destRect.getHeight()/2.0f-rotationPoint.Y);
    irr::core::vector2df center = centerOffset.X*horizontalAxis - centerOffset.Y*verticalAxis;
    center.X += rotationPoint.X;
    center.Y += rotationPoint.Y;

    // Now find the corners based off the center
    irr::core::vector2df cornerOffset(destRect.getWidth()/2.0f,destRect.getHeight()/2.0f);
    verticalAxis *= cornerOffset.Y;
    horizontalAxis *= cornerOffset.X;
    irr::core::vector2df corner[4];
    corner[0] = center + verticalAxis - horizontalAxis;
    corner[1] = center + verticalAxis + horizontalAxis;
    corner[2] = center - verticalAxis - horizontalAxis;
    corner[3] = center - verticalAxis + horizontalAxis;

    // Find the uv coordinates of the sourceRect
    irr::core::vector2df textureSize(texture->getSize().Width, texture->getSize().Height);
    irr::core::vector2df uvCorner[4];
    uvCorner[0] = irr::core::vector2df(sourceRect.UpperLeftCorner.X,sourceRect.UpperLeftCorner.Y);
    uvCorner[1] = irr::core::vector2df(sourceRect.LowerRightCorner.X,sourceRect.UpperLeftCorner.Y);
    uvCorner[2] = irr::core::vector2df(sourceRect.UpperLeftCorner.X,sourceRect.LowerRightCorner.Y);
    uvCorner[3] = irr::core::vector2df(sourceRect.LowerRightCorner.X,sourceRect.LowerRightCorner.Y);
    for (irr::s32 i = 0; i < 4; i++)
            uvCorner[i] /= textureSize;

    // Vertices for the image
    irr::video::S3DVertex vertices[4];
    irr::u16 indices[6] = { 0, 1, 2, 3 ,2 ,1 };

    // Convert pixels to world coordinates
    //irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].dimension.Width, rc_canvas[rc_active_canvas].dimension.Height);

    for (irr::s32 i = 0; i < 4; i++) {
            vertices[i].Pos = irr::core::vector3df(((corner[i].X/screenSize.X)-0.5f)*2.0f,((corner[i].Y/screenSize.Y)-0.5f)*-2.0f,1);
            vertices[i].TCoords = uvCorner[i];
            vertices[i].Color = color;
    }

    // Create the material
    // IMPORTANT: For irrlicht 1.8 and above you MUST ADD THIS LINE:
    // material.BlendOperation = irr::video::EBO_ADD;
    irr::video::SMaterial material;
    material.Lighting = false;
    material.ZWriteEnable = irr::video::EZW_OFF;
    material.ZBuffer = false;
    material.BackfaceCulling = false;
    material.TextureLayer[0].Texture = texture;
    material.TextureLayer[0].BilinearFilter = bilinear_filter; //TODO: Add option to switch this on/off
    material.BlendOperation = blend_mode;
    material.MaterialTypeParam = irr::video::pack_textureBlendFunc(irr::video::EBF_SRC_ALPHA, irr::video::EBF_ONE_MINUS_SRC_ALPHA, irr::video::EMFN_MODULATE_1X, irr::video::EAS_TEXTURE | irr::video::EAS_VERTEX_COLOR);
    material.AntiAliasing = anti_alias;

    if (useAlphaChannel)
            material.MaterialType = irr::video::EMT_ONETEXTURE_BLEND;
    else
            material.MaterialType = irr::video::EMT_SOLID;

    driver->setMaterial(material);
    driver->drawIndexedTriangleList(&vertices[0],4,&indices[0],2);

    // Restore projection, world, and view matrices
    driver->setTransform(irr::video::ETS_PROJECTION,oldProjMat);
    driver->setTransform(irr::video::ETS_VIEW,oldViewMat);
    driver->setTransform(irr::video::ETS_WORLD,oldWorldMat);

    rc_setDriverMaterial();
}



int wxIrrlicht::loadImageEx(std::string img_file, irr::u32 color_key, bool use_color_key)
{
    image_obj img;
    img.image = m_pDriver->getTexture(img_file.c_str());
    img.alpha = 255;

    if(img.image == NULL)
        return -1;

	if(color_key == -1)
	{
		irr::u32* img_pixels = (irr::u32*)img.image->lock();
		color_key = img_pixels[0];
		img.image->unlock();
	}

    if(use_color_key)
        m_pDriver->makeColorKeyTexture(img.image, irr::video::SColor(color_key), false);

    int img_id = -1;

    for(int i = 0; i < image.size(); i++)
    {
        if(image[i].image == NULL)
        {
            img_id = i;
            break;
        }
    }

    if(img_id < 0)
    {
        img_id = image.size();
        image.push_back(img);
    }
    else
    {
        image[img_id] = img;
    }

    return img_id;
}

int wxIrrlicht::loadImage(std::string img_file)
{
    return loadImageEx(img_file, 0, false);
}

void wxIrrlicht::deleteImage(int img_id)
{
    if(img_id < 0 || img_id >= image.size())
        return;

	irr::video::ITexture* texture = image[img_id].image;

	for(int i = 0; i < image.size(); i++)
	{
		if(image[i].image == texture)
			image[i].image = NULL;
	}

    if(texture)
    {
        m_pDriver->removeTexture(texture);
    }

    image[img_id].image = NULL;
	image[img_id].alpha = 255;
}

void wxIrrlicht::getImageBuffer(int img_id, irr::u32 * pdata)
{
    if(img_id < 0 || img_id >= image.size())
        return;

    if(!image[img_id].image)
        return;

    irr::u32* img_pixels = (irr::u32*)image[img_id].image->lock();

    int image_size = image[img_id].image->getSize().Width * image[img_id].image->getSize().Height;

    for(int i = 0; i < image_size; i++)
        pdata[i] = img_pixels[i];

    image[img_id].image->unlock();
}






void wxIrrlicht::drawImage(int img_id, int x, int y)
{
	if(active_canvas < 0 || active_canvas >= canvas.size())
		return;

	if(active_canvas == back_buffer || active_canvas == ui_layer)
		return;

    if(img_id < 0 || img_id >= image.size())
        return;

    if(image[img_id].image)
    {
        irr::core::dimension2d<irr::u32> src_size = image[img_id].image->getOriginalSize();
        irr::core::rect<irr::s32> sourceRect( irr::core::vector2d<irr::s32>(0, 0), src_size);

        irr::core::position2d<irr::s32> position(x, y);

        irr::core::position2d<irr::s32> rotationPoint(0, 0); //since we are not rotating it doesn't matter

        irr::f32 rotation = 0;
        irr::core::vector2df scale(1.0, 1.0);
        bool useAlphaChannel = true;
        irr::video::SColor color(image[img_id].alpha,
                                 image[img_id].color_mod.getRed(),
                                 image[img_id].color_mod.getGreen(),
                                 image[img_id].color_mod.getBlue());

        //irr::core::rect<irr::s32> dest( irr::core::vector2d(x, y), irr::core::dimension2d(src_w, src_h));;

        //irr::core::vector2df screenSize(canvas[active_canvas].dimension.Width, canvas[active_canvas].dimension.Height);
        irr::core::vector2df screenSize(canvas[active_canvas].texture->getOriginalSize().Width, canvas[active_canvas].texture->getOriginalSize().Height);

        //m_pDriver->setRenderTarget(canvas[active_canvas].texture);
        util_draw2DImage(m_pDriver, image[img_id].image, sourceRect, position, rotationPoint, rotation, scale, useAlphaChannel, color, screenSize);
    }
}


void wxIrrlicht::drawImage_Rotate(int img_id, int x, int y, double angle)
{
	if(active_canvas < 0 || active_canvas >= canvas.size())
		return;

    if(img_id < 0 || img_id >= image.size())
        return;

    if(image[img_id].image)
    {
        irr::core::dimension2d<irr::u32> src_size = image[img_id].image->getOriginalSize();
        irr::core::rect<irr::s32> sourceRect(0, 0, src_size.Width, src_size.Height);

        irr::core::position2d<irr::s32> position(x, y);

        irr::core::position2d<irr::s32> rotationPoint(x + (src_size.Width/2), y + (src_size.Height/2));

        irr::f32 rotation = -1*angle;
        irr::core::vector2df scale(1.0, 1.0);
        bool useAlphaChannel = true;
        irr::video::SColor color(image[img_id].alpha,
                                 image[img_id].color_mod.getRed(),
                                 image[img_id].color_mod.getGreen(),
                                 image[img_id].color_mod.getBlue());

        //irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].dimension.Width, rc_canvas[rc_active_canvas].dimension.Height);
        irr::core::vector2df screenSize(canvas[active_canvas].texture->getOriginalSize().Width, canvas[active_canvas].texture->getOriginalSize().Height);

        util_draw2DImage(m_pDriver, image[img_id].image, sourceRect, position, rotationPoint, rotation, scale, useAlphaChannel, color, screenSize);
    }
}

void wxIrrlicht::drawImage_Zoom(int img_id, int x, int y, double zx, double zy)
{
	if(active_canvas < 0 || active_canvas >= canvas.size())
		return;

    if(img_id < 0 || img_id >= image.size())
        return;

    if(image[img_id].image)
    {
        irr::core::dimension2d<irr::u32> src_size = image[img_id].image->getOriginalSize();
        irr::core::rect<irr::s32> sourceRect(0, 0, src_size.Width, src_size.Height);

        irr::core::position2d<irr::s32> position(x, y);

        irr::core::position2d<irr::s32> rotationPoint(x + (src_size.Width/2), y + (src_size.Height/2));

        irr::f32 rotation = 0;
        irr::core::vector2df scale((irr::f32)zx, (irr::f32)zy);
        bool useAlphaChannel = true;
        irr::video::SColor color(image[img_id].alpha,
                                 image[img_id].color_mod.getRed(),
                                 image[img_id].color_mod.getGreen(),
                                 image[img_id].color_mod.getBlue());

        //irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].dimension.Width, rc_canvas[rc_active_canvas].dimension.Height);
        irr::core::vector2df screenSize(canvas[active_canvas].texture->getOriginalSize().Width, canvas[active_canvas].texture->getOriginalSize().Height);

        util_draw2DImage(m_pDriver, image[img_id].image, sourceRect, position, rotationPoint, rotation, scale, useAlphaChannel, color, screenSize);
    }
}

void wxIrrlicht::drawImage_ZoomEx(int img_id, int x, int y, int src_x, int src_y, int src_w, int src_h, double zx, double zy)
{
	if(active_canvas < 0 || active_canvas >= canvas.size())
		return;

    if(img_id < 0 || img_id >= image.size())
        return;

    if(image[img_id].image)
    {
        //irr::core::dimension2d<irr::u32> src_size = rc_image[img_id].image->getSize();
        irr::core::rect<irr::s32> sourceRect( irr::core::vector2d<irr::s32>(src_x, src_y), irr::core::dimension2d<irr::s32>(src_w, src_h));

        irr::core::position2d<irr::s32> position(x, y);

        irr::core::position2d<irr::s32> rotationPoint(x + (src_w/2), y + (src_h/2));

        irr::f32 rotation = 0;
        irr::core::vector2df scale((irr::f32)zx, (irr::f32)zy);
        bool useAlphaChannel = true;
        irr::video::SColor color(image[img_id].alpha,
                                 image[img_id].color_mod.getRed(),
                                 image[img_id].color_mod.getGreen(),
                                 image[img_id].color_mod.getBlue());

        //irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].dimension.Width, rc_canvas[rc_active_canvas].dimension.Height);
        irr::core::vector2df screenSize(canvas[active_canvas].texture->getOriginalSize().Width, canvas[active_canvas].texture->getOriginalSize().Height);

        util_draw2DImage(m_pDriver, image[img_id].image, sourceRect, position, rotationPoint, rotation, scale, useAlphaChannel, color, screenSize);
    }
}

void wxIrrlicht::drawImage_Rotozoom(int img_id, int x, int y, double angle, double zx, double zy)
{
	if(active_canvas < 0 || active_canvas >= canvas.size())
		return;

    if(img_id < 0 || img_id >= image.size())
        return;

    if(image[img_id].image)
    {
        irr::core::dimension2d<irr::u32> src_size = image[img_id].image->getOriginalSize();
        irr::core::rect<irr::s32> sourceRect(0, 0, src_size.Width, src_size.Height);

        irr::core::position2d<irr::s32> position(x, y);

        irr::core::position2d<irr::s32> rotationPoint(x + (src_size.Width/2)*zx, y + (src_size.Height/2)*zy);

        irr::f32 rotation = -1*angle;
        irr::core::vector2df scale((irr::f32)zx, (irr::f32)zy);
        bool useAlphaChannel = true;
        irr::video::SColor color(image[img_id].alpha,
                                 image[img_id].color_mod.getRed(),
                                 image[img_id].color_mod.getGreen(),
                                 image[img_id].color_mod.getBlue());

        //irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].dimension.Width, rc_canvas[rc_active_canvas].dimension.Height);
        irr::core::vector2df screenSize(canvas[active_canvas].texture->getOriginalSize().Width, canvas[active_canvas].texture->getOriginalSize().Height);

        util_draw2DImage(m_pDriver, image[img_id].image, sourceRect, position, rotationPoint, rotation, scale, useAlphaChannel, color, screenSize);
    }
}

void wxIrrlicht::drawImage_RotozoomEx(int img_id, int x, int y, int src_x, int src_y, int src_w, int src_h, double angle, double zx, double zy)
{
	if(active_canvas < 0 || active_canvas >= canvas.size())
		return;

    if(img_id < 0 || img_id >= image.size())
        return;

    if(image[img_id].image)
    {
        //irr::core::dimension2d<irr::u32> src_size = rc_image[img_id].image->getSize();
        irr::core::rect<irr::s32> sourceRect( irr::core::vector2d<irr::s32>(src_x, src_y), irr::core::dimension2d<irr::s32>(src_w, src_h));

        irr::core::position2d<irr::s32> position(x, y);

        irr::core::position2d<irr::s32> rotationPoint(x + (src_w/2)*zx, y + (src_h/2)*zy);

        irr::f32 rotation = -1*angle;
        irr::core::vector2df scale((irr::f32)zx, (irr::f32)zy);
        bool useAlphaChannel = true;
        irr::video::SColor color(image[img_id].alpha,
                                 image[img_id].color_mod.getRed(),
                                 image[img_id].color_mod.getGreen(),
                                 image[img_id].color_mod.getBlue());

        //irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].dimension.Width, rc_canvas[rc_active_canvas].dimension.Height);
        irr::core::vector2df screenSize(canvas[active_canvas].texture->getOriginalSize().Width, canvas[active_canvas].texture->getOriginalSize().Height);

        util_draw2DImage(m_pDriver, image[img_id].image, sourceRect, position, rotationPoint, rotation, scale, useAlphaChannel, color, screenSize);
    }
}


void wxIrrlicht::drawImage_Flip(int img_id, int x, int y, bool h, bool v)
{
	if(active_canvas < 0 || active_canvas >= canvas.size())
		return;

    if(img_id < 0 || img_id >= image.size())
        return;

    if(image[img_id].image)
    {
        irr::core::dimension2d<irr::u32> src_size = image[img_id].image->getOriginalSize();
        irr::core::rect<irr::s32> sourceRect(0, 0, src_size.Width, src_size.Height);

        irr::core::position2d<irr::s32> rotationPoint(x + (src_size.Width/2), y + (src_size.Height/2));

        irr::f32 rotation = 0;
        irr::core::vector2df scale((irr::f32)(h ? -1 : 1), (irr::f32) (v ? -1 : 1));

        irr::core::position2d<irr::s32> position( (h ? x+src_size.Width : x), (v ? y+src_size.Height : y));

        bool useAlphaChannel = true;
        irr::video::SColor color(image[img_id].alpha,
                                 image[img_id].color_mod.getRed(),
                                 image[img_id].color_mod.getGreen(),
                                 image[img_id].color_mod.getBlue());

        //irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].dimension.Width, rc_canvas[rc_active_canvas].dimension.Height);
        irr::core::vector2df screenSize(canvas[active_canvas].texture->getOriginalSize().Width, canvas[active_canvas].texture->getOriginalSize().Height);

        util_draw2DImage(m_pDriver, image[img_id].image, sourceRect, position, rotationPoint, rotation, scale, useAlphaChannel, color, screenSize);
    }
}

void wxIrrlicht::drawImage_FlipEx(int img_id, int x, int y, int src_x, int src_y, int src_w, int src_h, bool h, bool v)
{
	if(active_canvas < 0 || active_canvas >= canvas.size())
		return;

    if(img_id < 0 || img_id >= image.size())
        return;

    if(image[img_id].image)
    {
        //irr::core::dimension2d<irr::u32> src_size = rc_image[img_id].image->getSize();
        irr::core::rect<irr::s32> sourceRect( irr::core::vector2d<irr::s32>(src_x, src_y), irr::core::dimension2d<irr::s32>(src_w, src_h));

        irr::core::position2d<irr::s32> rotationPoint(x + (src_w/2), y + (src_h/2));

        irr::f32 rotation = 0;
        irr::core::vector2df scale((irr::f32)(h ? -1 : 1), (irr::f32) (v ? -1 : 1));

        irr::core::position2d<irr::s32> position( (h ? x+src_w : x), (v ? y+src_h : y));

        bool useAlphaChannel = true;
        irr::video::SColor color(image[img_id].alpha,
                                 image[img_id].color_mod.getRed(),
                                 image[img_id].color_mod.getGreen(),
                                 image[img_id].color_mod.getBlue());

        //irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].dimension.Width, rc_canvas[rc_active_canvas].dimension.Height);
        irr::core::vector2df screenSize(canvas[active_canvas].texture->getOriginalSize().Width, canvas[active_canvas].texture->getOriginalSize().Height);

        util_draw2DImage(m_pDriver, image[img_id].image, sourceRect, position, rotationPoint, rotation, scale, useAlphaChannel, color, screenSize);
    }
}


void wxIrrlicht::drawImage_Blit(int img_id, int x, int y, int src_x, int src_y, int src_w, int src_h)
{
	if(active_canvas < 0 || active_canvas >= canvas.size())
		return;

    if(img_id < 0 || img_id >= image.size())
        return;

    if(image[img_id].image)
    {
        //irr::core::dimension2d<irr::u32> src_size = rc_image[img_id].image->getSize();
        irr::core::rect<irr::s32> sourceRect( irr::core::vector2d<irr::s32>(src_x, src_y), irr::core::dimension2d<irr::s32>(src_w, src_h));

        irr::core::position2d<irr::s32> position(x, y);

        irr::core::position2d<irr::s32> rotationPoint(0, 0); //since we are not rotating it doesn't matter

        irr::f32 rotation = 0;
        irr::core::vector2df scale(1.0, 1.0);
        bool useAlphaChannel = true;
        irr::video::SColor color(image[img_id].alpha,
                                 image[img_id].color_mod.getRed(),
                                 image[img_id].color_mod.getGreen(),
                                 image[img_id].color_mod.getBlue());

        irr::core::rect<irr::s32> dest( irr::core::vector2d<irr::s32>(x, y), irr::core::dimension2d<irr::s32>(src_w, src_h));

        //irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].dimension.Width, rc_canvas[rc_active_canvas].dimension.Height);
        //std::cout << "A: " << (canvas[active_canvas].texture == NULL ? "null" : "active") << std::endl;
        irr::core::vector2df screenSize(canvas[active_canvas].texture->getOriginalSize().Width, canvas[active_canvas].texture->getOriginalSize().Height);

        util_draw2DImage(m_pDriver, image[img_id].image, sourceRect, position, rotationPoint, rotation, scale, useAlphaChannel, color, screenSize);
    }
}


void wxIrrlicht::drawImage_RotateEx(int img_id, int x, int y, int src_x, int src_y, int src_w, int src_h, int angle)
{
	if(active_canvas < 0 || active_canvas >= canvas.size())
		return;

    if(img_id < 0 || img_id >= image.size())
        return;

    if(image[img_id].image)
    {
        //irr::core::dimension2d<irr::u32> src_size = rc_image[img_id].image->getSize();
        irr::core::rect<irr::s32> sourceRect( irr::core::vector2d<irr::s32>(src_x, src_y), irr::core::dimension2d<irr::s32>(src_w, src_h));

        //irr::core::position2d<irr::s32> position(x, y);

        irr::core::vector2d<irr::s32> rotationPoint(x + (src_w/2), y + (src_h/2));

        irr::f32 rotation = -1*angle;
        //irr::core::vector2df scale(1.0, 1.0);
        bool useAlphaChannel = true;
        irr::video::SColor color(image[img_id].alpha,
                                 image[img_id].color_mod.getRed(),
                                 image[img_id].color_mod.getGreen(),
                                 image[img_id].color_mod.getBlue());

        //irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].dimension.Width, rc_canvas[rc_active_canvas].dimension.Height);
        irr::core::vector2df screenSize(canvas[active_canvas].texture->getOriginalSize().Width, canvas[active_canvas].texture->getOriginalSize().Height);

        irr::core::rect<irr::s32> dest( irr::core::vector2d<irr::s32>(x, y), irr::core::dimension2d<irr::s32>(src_w, src_h));

        util_draw2DImage2(m_pDriver, image[img_id].image, sourceRect, dest, rotationPoint, rotation, useAlphaChannel, color, screenSize);
    }
}

void wxIrrlicht::drawImage_BlitEx(int img_id, int x, int y, int w, int h, int src_x, int src_y, int src_w, int src_h)
{
	if(active_canvas < 0 || active_canvas >= canvas.size())
		return;

    if(img_id < 0 || img_id >= image.size())
        return;

    if(image[img_id].image)
    {
        //irr::core::dimension2d<irr::u32> src_size = rc_image[img_id].image->getSize();
        irr::core::rect<irr::s32> sourceRect( irr::core::vector2d<irr::s32>(src_x, src_y), irr::core::dimension2d<irr::s32>(src_w, src_h));

        //irr::core::position2d<irr::s32> position(x, y);

        irr::core::position2d<irr::s32> rotationPoint(0, 0); //since we are not rotating it doesn't matter

        irr::f32 rotation = 0;
        irr::core::vector2df scale(1.0, 1.0);
        bool useAlphaChannel = true;
        irr::video::SColor color(image[img_id].alpha,
                                 image[img_id].color_mod.getRed(),
                                 image[img_id].color_mod.getGreen(),
                                 image[img_id].color_mod.getBlue());

        irr::core::rect<irr::s32> dest( irr::core::vector2d<irr::s32>(x, y), irr::core::dimension2d<irr::s32>(w, h));

        //irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].dimension.Width, rc_canvas[rc_active_canvas].dimension.Height);
        irr::core::vector2df screenSize(canvas[active_canvas].texture->getOriginalSize().Width, canvas[active_canvas].texture->getOriginalSize().Height);

        util_draw2DImage2(m_pDriver, image[img_id].image, sourceRect, dest, rotationPoint, rotation, useAlphaChannel, color, screenSize );
    }
}

void wxIrrlicht::drawImage_BlitEx_SW(int img_id, int x, int y, int w, int h, int src_x, int src_y, int src_w, int src_h)
{
	if(active_canvas < 0 || active_canvas >= canvas.size())
		return;

    if(img_id < 0 || img_id >= image.size())
        return;

    if(image[img_id].image)
    {
        //irr::core::dimension2d<irr::u32> src_size = rc_image[img_id].image->getSize();
        irr::core::rect<irr::s32> sourceRect( irr::core::vector2d<irr::s32>(src_x, src_y), irr::core::dimension2d<irr::s32>(src_w, src_h));

        //irr::core::position2d<irr::s32> position(x, y);

        irr::core::position2d<irr::s32> rotationPoint(0, 0); //since we are not rotating it doesn't matter

        irr::f32 rotation = 0;
        irr::core::vector2df scale(1.0, 1.0);
        bool useAlphaChannel = false;
        irr::video::SColor color(image[img_id].alpha,
                                 image[img_id].color_mod.getRed(),
                                 image[img_id].color_mod.getGreen(),
                                 image[img_id].color_mod.getBlue());

        irr::core::rect<irr::s32> dest( irr::core::vector2d<irr::s32>(x, y), irr::core::dimension2d<irr::s32>(w, h));

        //irr::core::vector2df screenSize(2560, 2560);
        //irr::core::vector2df screenSize(canvas[active_canvas].dimension.Width, canvas[active_canvas].dimension.Height);
        //irr::core::vector2df screenSize(canvas[active_canvas].texture->getSize().Width, canvas[active_canvas].texture->getSize().Height);

        //util_draw2DImage2(m_pDriver, image[img_id].image, sourceRect, dest, rotationPoint, rotation, useAlphaChannel, color, screenSize );
        m_pDriver->draw2DImage(image[img_id].image, dest, sourceRect, 0, 0, true);
    }
}


void wxIrrlicht::setImageAlpha(int img_id, irr::u8 alpha)
{
    if(img_id < 0 || img_id >= image.size())
        return;

    if(image[img_id].image)
    {
        image[img_id].alpha = alpha;
    }
}

irr::u32 wxIrrlicht::getImageAlpha(int img_id)
{
    if(img_id < 0 || img_id >= image.size())
        return 0;

    if(image[img_id].image)
    {
        return image[img_id].alpha;
    }

    return 0;
}

bool wxIrrlicht::imageExists(int img_id)
{
    if(img_id < 0 || img_id >= image.size())
        return false;

    if(image[img_id].image)
        return true;

    return false;
}

void wxIrrlicht::getImageSize(int img_id, double* w, double* h)
{
    if(img_id < 0 || img_id >= image.size())
        return;

    if(image[img_id].image)
    {
        *w = (double)image[img_id].image->getOriginalSize().Width;
        *h = (double)image[img_id].image->getOriginalSize().Height;
    }
}

void wxIrrlicht::getImageSizeI(int img_id, int* w, int* h)
{
    if(img_id < 0 || img_id >= image.size())
        return;

    if(image[img_id].image)
    {
        *w = image[img_id].image->getOriginalSize().Width;
        *h = image[img_id].image->getOriginalSize().Height;
    }
}

void wxIrrlicht::setColorKey(int img_id, irr::u32 colorkey)
{
    if(!imageExists(img_id))
        return;

    if(colorkey == -1)
	{
		irr::u32* img_pixels = (irr::u32*)image[img_id].image->lock();
		colorkey = img_pixels[0];
		image[img_id].image->unlock();
	}
    m_pDriver->makeColorKeyTexture(image[img_id].image, irr::video::SColor(colorkey));
}





// wxIrrlicht::

#define SPRITE_BASE_ANIMATION 0

int wxIrrlicht::createSpriteAnimation(std::string name, int spr_id, int anim_length, double fps)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return -1;

	if(!sprite[spr_id].active)
		return -1;

	if(anim_length <= 0)
		anim_length = 1;

	sprite2D_animation_obj animation;
	animation.name = name;
	animation.current_frame = 0;
	animation.fps = fps;
	animation.frame_swap_time = 1000/fps;
	animation.num_frames = anim_length;
	for(int i = 0; i < anim_length; i++)
		animation.frames.push_back(0);

	int animation_id = sprite[spr_id].animation.size();
	if(sprite[spr_id].deleted_animation.size() > 0)
	{
		animation_id = sprite[spr_id].deleted_animation[0];
		sprite[spr_id].deleted_animation.erase(0);
		sprite[spr_id].animation[animation_id] = animation;
	}
	else
		sprite[spr_id].animation.push_back(animation);

	//std::cout << "animation id = " << animation_id << std::endl;
	return animation_id;
}

void wxIrrlicht::deleteSpriteAnimation(int spr_id, int animation)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return;

	if(!sprite[spr_id].active)
		return;

	for(int i = 0; i < sprite[spr_id].deleted_animation.size(); i++)
	{
		if(sprite[spr_id].deleted_animation[i] == animation)
			return;
	}

	sprite[spr_id].deleted_animation.push_back(animation);
}

void wxIrrlicht::setSpriteFrame(int spr_id, int frame)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return;

	if(!sprite[spr_id].active)
		return;

	if(frame < 0 || frame >= sprite[spr_id].sheet_numFrames)
		return;

	sprite[spr_id].current_animation = SPRITE_BASE_ANIMATION;
	sprite[spr_id].animation[SPRITE_BASE_ANIMATION].current_frame = 0;
	sprite[spr_id].animation[SPRITE_BASE_ANIMATION].frames[0] = frame;
}

int wxIrrlicht::getSpriteFrame(int spr_id)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return -1;

	if(!sprite[spr_id].active)
		return -1;

	int current_animation = sprite[spr_id].current_animation;
	int current_frame = sprite[spr_id].animation[current_animation].current_frame;
	return sprite[spr_id].animation[current_animation].frames[current_frame];
}

void wxIrrlicht::setSpriteAnimationFrame(int spr_id, int spr_animation, int anim_frame, int frame)
{
	if(spr_id < 0 || spr_id >= sprite.size())
	{
		std::cout << "SetSpriteAnimationFrame ERROR: SPR_ID (" << spr_id << ") is out of range [size=" << sprite.size() << "]" << std::endl;
		return;
	}

	if(!sprite[spr_id].active)
	{
		std::cout << "SetSpriteAnimationFrame ERROR: SPR (" << spr_id << ") is not active" << std::endl;
		return;
	}

	if(anim_frame < 0 || anim_frame >= sprite[spr_id].animation[spr_animation].num_frames)
	{
		std::cout << "SetSpriteAnimationFrame ERROR: ANI_FRAME (" << anim_frame << ") is out of range [size=" << sprite[spr_id].animation[spr_animation].num_frames << "]" << std::endl;
		return;
	}

	if(frame < 0 || frame >= sprite[spr_id].sheet_numFrames)
	{
		std::cout << "SetSpriteAnimationFrame ERROR: frame (" << frame << ") is out of range [size=" << sprite[spr_id].sheet_numFrames << "]" << std::endl;
		return;
	}

	sprite[spr_id].animation[spr_animation].frames[anim_frame] = frame;
}

int wxIrrlicht::getSpriteAnimationFrame(int spr_id, int spr_animation, int anim_frame)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return -1;

	if(!sprite[spr_id].active)
		return -1;

	if(anim_frame < 0 || anim_frame >= sprite[spr_id].animation[spr_animation].num_frames)
		return -1;

	return sprite[spr_id].animation[spr_animation].frames[anim_frame];
}


void wxIrrlicht::setSpriteAnimationLength(int spr_id, int animation, int num_frames)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return;

	if(!sprite[spr_id].active)
		return;

	// I intentionally checked for less than or equal to 0 because 0 is the base animation and should not be changed
	if(animation <= 0 || animation >= sprite[spr_id].animation.size())
		return;

	if(num_frames <= 0)
		num_frames = 1;

	if(num_frames > sprite[spr_id].animation[animation].num_frames)
	{
		for(int i = sprite[spr_id].animation[animation].num_frames; i < sprite[spr_id].animation[animation].frames.size(); i++)
			sprite[spr_id].animation[animation].frames[i] = 0;
	}

	sprite[spr_id].animation[animation].num_frames = num_frames;
	if(num_frames > sprite[spr_id].animation[animation].frames.size())
	{
		while(num_frames > sprite[spr_id].animation[animation].frames.size())
			sprite[spr_id].animation[animation].frames.push_back(0);
	}

	if(num_frames < sprite[spr_id].animation[animation].frames.size())
	{
		if(sprite[spr_id].animation[animation].current_frame >= num_frames)
			sprite[spr_id].animation[animation].current_frame = num_frames - 1;
	}
}

int wxIrrlicht::getSpriteAnimationLength(int spr_id, int animation)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return 0;

	if(!sprite[spr_id].active)
		return 0;

	if(animation < 0 || animation >= sprite[spr_id].animation.size())
		return 0;

	return sprite[spr_id].animation[animation].num_frames;
}

void wxIrrlicht::setSpriteAnimationSpeed(int spr_id, int animation, double fps)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return;

	if(!sprite[spr_id].active)
		return;

	if(animation < 0 || animation >= sprite[spr_id].animation.size())
		return;

	sprite[spr_id].animation[animation].fps = fps;
	sprite[spr_id].animation[animation].frame_swap_time = 1000/fps;
}

double wxIrrlicht::getSpriteAnimationSpeed(int spr_id, int animation)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return 0;

	if(!sprite[spr_id].active)
		return 0;

	if(animation < 0 || animation >= sprite[spr_id].animation.size())
		return 0;

	return sprite[spr_id].animation[animation].fps;
}

void wxIrrlicht::setSpriteAnimation(int spr_id, int animation, int num_loops)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return;

	if(!sprite[spr_id].active)
		return;

	if(animation < 0 || animation >= sprite[spr_id].animation.size())
		return;

	sprite[spr_id].current_animation = animation;
	sprite[spr_id].animation[animation].current_frame = 0;
	sprite[spr_id].isPlaying = true;
	sprite[spr_id].animation[animation].frame_start_time = m_pDevice->getTimer()->getTime();
	sprite[spr_id].num_animation_loops = num_loops;
}

int wxIrrlicht::getSpriteAnimation(int spr_id)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return -1;

	if(!sprite[spr_id].active)
		return -1;

	return sprite[spr_id].current_animation;
}

int wxIrrlicht::getSpriteCurrentAnimationFrame(int spr_id)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return -1;

	if(!sprite[spr_id].active)
		return -1;

	int current_animation = sprite[spr_id].current_animation;
	return sprite[spr_id].animation[current_animation].current_frame;
}

void wxIrrlicht::setSpriteAnimationLoops(int spr_id, int num_loops)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return;

	if(!sprite[spr_id].active)
		return;

	sprite[spr_id].num_animation_loops = num_loops;
}

int wxIrrlicht::numSpriteAnimationLoops(int spr_id)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return 0;

	if(!sprite[spr_id].active)
		return 0;

	return sprite[spr_id].num_animation_loops;
}

bool wxIrrlicht::spriteAnimationIsPlaying(int spr_id)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return false;

	if(!sprite[spr_id].active)
		return false;

	return sprite[spr_id].isPlaying;
}

//------------------------------SPRITES-------------------------------------------------------
//Larger z gets drawn first
void wxIrrlicht::sortSpriteZ(int canvas_id)
{
	if(canvas_id < 0 || canvas_id >= canvas.size())
		return;

	if(!canvas[canvas_id].texture)
		return;

	for(int i = 0; i < canvas[canvas_id].sprite_id.size(); i++)
	{
		int spriteA = canvas[canvas_id].sprite_id[i];

		for(int j = i+1; j < canvas[canvas_id].sprite_id.size(); j++)
		{
			int spriteB = canvas[canvas_id].sprite_id[j];

			if(sprite[spriteB].z > sprite[spriteA].z)
			{
				canvas[canvas_id].sprite_id.erase(j);
				canvas[canvas_id].sprite_id.insert(spriteB, i);
			}
		}
	}
}

bool wxIrrlicht::spriteExists(int spr_id)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return false;

	return sprite[spr_id].active;
}

int wxIrrlicht::createSprite(int layer_sprite_index, int img_id, double w, double h)
{
	if(active_canvas < 0 || active_canvas >= canvas.size())
		return -1;

	//if(canvas[active_canvas].type != CANVAS_TYPE_SPRITE)
	//	return -1;

	int spr_id = -1;
	for(int i = 0; i < sprite.size(); i++)
	{
		if(!sprite[i].active)
		{
			spr_id = i;
			break;
		}
	}

	if(spr_id < 0)
	{
		spr_id = sprite.size();
		sprite2D_obj n_sprite;
		sprite.push_back(n_sprite);
	}

	sprite[spr_id].active = true;
	sprite[spr_id].id = spr_id;
	sprite[spr_id].image_id = img_id;
	sprite[spr_id].frame_size.set(w, h);
	sprite[spr_id].layer_sprite_index = layer_sprite_index;

	if(selected_stage >= 0 && selected_stage < project->stages.size())
	{
		if(selected_layer >= 0 && selected_layer < project->stages[selected_stage].layers.size())
		{
			if(layer_sprite_index >= 0 && layer_sprite_index < project->stages[selected_stage].layers[selected_layer].layer_sprites.size())
			{
				sprite[spr_id].layer_sprite_unique_id = project->stages[selected_stage].layers[selected_layer].layer_sprites[layer_sprite_index].layer_sprite_unique_id;
			}
		}
	}

	if(img_id >= 0 && img_id < image.size())
	{
		if(image[img_id].image)
		{
			int img_w = image[img_id].image->getOriginalSize().Width;
			int img_h = image[img_id].image->getOriginalSize().Height;

			sprite[spr_id].frames_per_row = (int)(img_w / w);
			sprite[spr_id].sheet_numFrames = ((int)(img_h / h)) * sprite[spr_id].frames_per_row;
		}
		else
			sprite[spr_id].image_id = -1;
	}
	else
		sprite[spr_id].image_id = -1;


	sprite[spr_id].physics.shape_type = SPRITE_SHAPE_BOX;
	sprite[spr_id].physics.box_width = w;
	sprite[spr_id].physics.box_height = h;

	sprite[spr_id].physics.radius = (w > h ? w : h)/2;

	sprite[spr_id].physics.offset_x = 0; // This should be w/2 but for the purposes of this editor I am using 0 to represent center
	sprite[spr_id].physics.offset_y = 0; // This should be h/2 but for the purposes of this editor I am using 0 to represent center
	sprite[spr_id].isSolid = false;

	if(sprite[spr_id].image_id < 0)
		sprite[spr_id].visible =false;
	else
		sprite[spr_id].visible = true;

	sprite[spr_id].scale.set(1.0, 1.0);
	sprite[spr_id].alpha = 255;
	sprite[spr_id].z = 0;
	sprite[spr_id].color_mod.set(255,255,255,255);
	sprite[spr_id].parent_canvas = active_canvas;

	sprite[spr_id].current_animation = SPRITE_BASE_ANIMATION;
	sprite[spr_id].num_animation_loops = 0;
	sprite[spr_id].current_animation_loop = 0;
	sprite[spr_id].isPlaying = false;
	sprite[spr_id].animation.clear();
	createSpriteAnimation("SPRITE_BASE_ANIMATION", spr_id, 1, 0);
	//sprite[spr_id].animation[0].name = "SPRITE_BASE_ANIMATION";

	int i = canvas[active_canvas].sprite_id.size();
	canvas[active_canvas].sprite_id.push_back(spr_id);

	sortSpriteZ(active_canvas);

	return spr_id;
}

void wxIrrlicht::deleteSprite(int spr_id)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return;


	sprite[spr_id].active = false;
	sprite[spr_id].parent_canvas = -1;
	sprite[spr_id].animation.clear();
	int parent_canvas = sprite[spr_id].parent_canvas;

	if(parent_canvas < 0 || parent_canvas >= canvas.size())
		return;

	for(int i = 0; i < canvas[parent_canvas].sprite_id.size(); i++)
	{
		int canvas_sprite = canvas[parent_canvas].sprite_id[i];

		if(canvas_sprite == spr_id)
		{
			canvas[parent_canvas].sprite_id.erase(i,1);
			break;
		}
	}
}

int wxIrrlicht::getSpriteSource(int spr_id)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return -1;

	if(!sprite[spr_id].active)
		return -1;

	return sprite[spr_id].image_id;
}

void wxIrrlicht::setSpriteCollisionShape(int spr_id, int sprite_shape)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return;

	if(!sprite[spr_id].active)
		return;

	switch(sprite_shape)
	{
		case SPRITE_SHAPE_BOX:
		{
			sprite[spr_id].physics.shape_type = SPRITE_SHAPE_BOX;
		}
		break;

		case SPRITE_SHAPE_POLYGON:
		{
			sprite[spr_id].physics.shape_type = SPRITE_SHAPE_POLYGON;
		}
		break;

		case SPRITE_SHAPE_CIRCLE:
		{
			sprite[spr_id].physics.shape_type = SPRITE_SHAPE_CIRCLE;
		}
		break;

		case SPRITE_SHAPE_CHAIN:
		{
			sprite[spr_id].physics.shape_type = SPRITE_SHAPE_CHAIN;
		}
		break;
	}
}

int wxIrrlicht::getSpriteCollisionShape(int spr_id)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return 0;

	if(!sprite[spr_id].active)
		return 0;

	return sprite[spr_id].physics.shape_type;
}

void wxIrrlicht::setSpriteRadius(int spr_id, double radius)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return;

	if(!sprite[spr_id].active)
		return;

	if(sprite[spr_id].physics.shape_type == SPRITE_SHAPE_CIRCLE)
	{
		sprite[spr_id].physics.radius = radius;
	}
}

double wxIrrlicht::getSpriteRadius(int spr_id)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return 0;

	if(!sprite[spr_id].active)
		return 0;

	if(sprite[spr_id].physics.shape_type == SPRITE_SHAPE_CIRCLE)
	{
		return sprite[spr_id].physics.radius;
	}

	return 0;
}

void wxIrrlicht::setSpriteBox(int spr_id, int w, int h)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return;

	if(!sprite[spr_id].active)
		return;

	if(sprite[spr_id].physics.shape_type == SPRITE_SHAPE_BOX)
	{
		sprite[spr_id].physics.box_width = w;
		sprite[spr_id].physics.box_height = h;
	}
}

void wxIrrlicht::getSpriteBoxSize(int spr_id, int* w, int* h)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return;

	if(!sprite[spr_id].active)
		return;

	*w = -1;
	*h = -1;

	if(sprite[spr_id].physics.shape_type == SPRITE_SHAPE_BOX)
	{
		*w = sprite[spr_id].physics.box_width;
		*h = sprite[spr_id].physics.box_height;
	}
}


void wxIrrlicht::setSpriteChain(int spr_id, irr::core::array<irr::core::vector2di> vert, irr::core::array<irr::core::vector2di> prev_vert, irr::core::array<irr::core::vector2di> next_vert)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return;

	if(!sprite[spr_id].active)
		return;

	if(sprite[spr_id].physics.shape_type == SPRITE_SHAPE_CHAIN)
	{
		for(int i = 0; i < vert.size(); i++)
			sprite[spr_id].physics.points.push_back(vert[0]);

		for(int i = 0; i < prev_vert.size(); i++)
			sprite[spr_id].physics.prev_points.push_back(prev_vert[0]);

		for(int i = 0; i < next_vert.size(); i++)
			sprite[spr_id].physics.next_points.push_back(next_vert[0]);
	}
}

void wxIrrlicht::setSpriteChainLoop(int spr_id, irr::core::array<irr::core::vector2di> vert)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return;

	if(!sprite[spr_id].active)
		return;

	if(sprite[spr_id].physics.shape_type == SPRITE_SHAPE_CHAIN)
	{
		for(int i = 0; i < vert.size(); i++)
			sprite[spr_id].physics.points.push_back(vert[0]);
	}
}

void wxIrrlicht::setSpritePolygon(int spr_id, irr::core::array<irr::core::vector2di> vert)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return;

	if(!sprite[spr_id].active)
		return;

	if(vert.size() < 3)
		return; // A convex hull must have atleast 3 points

	if(sprite[spr_id].physics.shape_type == SPRITE_SHAPE_POLYGON)
	{
		sprite[spr_id].physics.points.clear();

		for(int i = 0; i < vert.size(); i++)
		{
			sprite[spr_id].physics.points.push_back(vert[i]);
		}
	}
}

void wxIrrlicht::setSpriteType(int spr_id, int body_type)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return;

	if(!sprite[spr_id].active)
		return;

	sprite[spr_id].physics.body_type = body_type;
}

int wxIrrlicht::getSpriteType(int spr_id)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return -1;

	if(!sprite[spr_id].active)
		return -1;

	return (int)sprite[spr_id].physics.body_type;
}

void wxIrrlicht::setSpriteSolid(int spr_id, bool flag)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return;

	if(!sprite[spr_id].active)
		return;

	sprite[spr_id].isSolid = flag;
}

bool wxIrrlicht::spriteIsSolid(int spr_id)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return false;

	if(!sprite[spr_id].active)
		return false;

	return sprite[spr_id].isSolid;
}

void wxIrrlicht::setSpritePosition(int spr_id, int x, int y)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return;

	if(!sprite[spr_id].active)
		return;

	sprite[spr_id].position.set(x, y);
}

irr::core::vector2di wxIrrlicht::getSpritePosition(int spr_id)
{
	irr::core::vector2di n;

	if(spr_id < 0 || spr_id >= sprite.size())
		return n;

	if(!sprite[spr_id].active)
		return n;

	return sprite[spr_id].position;
}


void wxIrrlicht::setSpriteRotation(int spr_id, double angle)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return;

	if(!sprite[spr_id].active)
		return;

	sprite[spr_id].angle = angle;
}

double wxIrrlicht::getSpriteRotation(int spr_id)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return 0;

	if(!sprite[spr_id].active)
		return 0;

	return sprite[spr_id].angle;
}

void wxIrrlicht::setSpriteScale(int spr_id, double x, double y)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return;

	if(!sprite[spr_id].active)
		return;

	sprite[spr_id].scale.set(x, y);
}


irr::core::vector2df wxIrrlicht::getSpriteScale(int spr_id)
{
	irr::core::vector2df n(0.0, 0.0);

	if(spr_id < 0 || spr_id >= sprite.size())
		return n;

	if(!sprite[spr_id].active)
		return n;

	return sprite[spr_id].scale;
}

int wxIrrlicht::spriteWidth(int spr_id)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return 0;

	if(!sprite[spr_id].active)
		return 0;

	return sprite[spr_id].frame_size.Width;
}

int wxIrrlicht::spriteHeight(int spr_id)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return 0;

	if(!sprite[spr_id].active)
		return 0;

	return sprite[spr_id].frame_size.Height;
}

irr::core::dimension2di wxIrrlicht::getSpriteSize(int spr_id)
{
	irr::core::dimension2di n(0, 0);

	if(spr_id < 0 || spr_id >= sprite.size())
		return n;

	if(!sprite[spr_id].active)
		return n;

	return sprite[spr_id].frame_size;
}

void wxIrrlicht::setSpriteZ(int spr_id, double z)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return;

	if(!sprite[spr_id].active)
		return;

	sprite[spr_id].z = z;
	sortSpriteZ(sprite[spr_id].parent_canvas);
}

double wxIrrlicht::spriteZ(int spr_id)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return 0;

	if(!sprite[spr_id].active)
		return 0;

	return sprite[spr_id].z;
}

void wxIrrlicht::setSpriteVisible(int spr_id, bool flag)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return;

	if(!sprite[spr_id].active)
		return;

	//std::cout << "Set Visible: " << (flag ? "TRUE" : "FALSE") << std::endl;
	//std::cout << "DEBUG: " << sprite[spr_id].frame_size.Width << ", " << sprite[spr_id].frame_size.Height << std::endl;

	if(sprite[spr_id].image_id >= 0)
		sprite[spr_id].visible = flag;
	else
		sprite[spr_id].visible = false;
}

bool wxIrrlicht::spriteIsVisible(int spr_id)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return false;

	if(!sprite[spr_id].active)
		return false;

	return sprite[spr_id].visible;
}

void wxIrrlicht::setSpriteColorMod(int spr_id, irr::u32 color)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return;

	if(!sprite[spr_id].active)
		return;

	if(sprite[spr_id].image_id >= 0)
		sprite[spr_id].color_mod = irr::video::SColor(color);
}

void wxIrrlicht::setSpriteAlpha(int spr_id, irr::u8 alpha)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return;

	if(!sprite[spr_id].active)
		return;

	if(sprite[spr_id].image_id >= 0)
		sprite[spr_id].alpha = alpha;
}

irr::u32 wxIrrlicht::getSpriteColorMod(int spr_id)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return 0;

	if(!sprite[spr_id].active)
		return 0;

	return sprite[spr_id].color_mod.color;
}

irr::u32 wxIrrlicht::getSpriteAlpha(int spr_id)
{
	if(spr_id < 0 || spr_id >= sprite.size())
		return 0;

	if(!sprite[spr_id].active)
		return 0;

	return (irr::u32)sprite[spr_id].alpha;
}

//-----------------------------------PHYSICS----------------------------------------------------------------------------------
void wxIrrlicht::util_setSpriteLayerOffset(int layer)
{
	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	if(layer < 0 || layer >= project->getStageNumLayers(selected_stage))
		return;

	int ref_canvas = project->stages[selected_stage].layers[layer].ref_canvas;

	if(ref_canvas < 0 || ref_canvas >= canvas.size())
		return;

	if(!canvas[ref_canvas].texture)
		return;

	if(project->getLayerType(selected_stage, layer) != LAYER_TYPE_SPRITE)
		return;

	int canvas_id = project->stages[selected_stage].layers[layer].ref_canvas;
	int layer_offset_x = project->stages[selected_stage].layers[layer].scroll_speed.X * scroll_offset_x;
	int layer_offset_y = project->stages[selected_stage].layers[layer].scroll_speed.Y * scroll_offset_y;
	setCanvasOffset(canvas_id, layer_offset_x, layer_offset_y);
}


void wxIrrlicht::util_drawShapes(int layer_index)
{
	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	if(project->stages[selected_stage].layers[layer_index].layer_type != LAYER_TYPE_SPRITE)
		return;

	int ref_canvas = project->stages[selected_stage].layers[layer_index].ref_canvas;

	if(ref_canvas < 0 || ref_canvas >= canvas.size())
		return;

	mapEdit_getContext();
	setActiveCanvas(ui_layer);


	wxMouseState  mouse_state = wxGetMouseState();

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();


	float scroll_speed_x = project->getLayerScrollSpeed(selected_stage, layer_index).X;
	float scroll_speed_y = project->getLayerScrollSpeed(selected_stage, layer_index).Y;

	int adj_scroll_offset_x = scroll_speed_x * scroll_offset_x;
	int adj_scroll_offset_y = scroll_speed_y * scroll_offset_y;


	setColor(rgb(255, 255, 255));

	double canvas_offset_x = 0;
	double canvas_offset_y = 0;
	getCanvasOffset(ref_canvas, &canvas_offset_x, &canvas_offset_y);

	int off_x = (int)canvas_offset_x;
	int off_y = (int)canvas_offset_y;

	//draw shapes
	int shape_x = 0;
	int shape_y = 0;

	int non_selected_shape_color = rgb(255,0,255);

	//std::cout << "shape count: " << project->stages[selected_stage].layers[selected_layer].layer_shapes.size() << std::endl;

	for(int i = 0; i < project->stages[selected_stage].layers[layer_index].layer_shapes.size(); i++)
	{
		int shape_type = project->stages[selected_stage].layers[layer_index].layer_shapes[i].shape_type;


		if(shape_type == SPRITE_SHAPE_BOX)
		{
			setColor(non_selected_shape_color);

			//std::cout << "cir: " << selected_shape << std::endl;
			int box_width = (int)project->stages[selected_stage].layers[layer_index].layer_shapes[i].box_width;
			int box_height = (int)project->stages[selected_stage].layers[layer_index].layer_shapes[i].box_height;
			int box_x = project->stages[selected_stage].layers[layer_index].layer_shapes[i].offset_x-adj_scroll_offset_x;
			int box_y = project->stages[selected_stage].layers[layer_index].layer_shapes[i].offset_y-adj_scroll_offset_y;

			drawRect(box_x, box_y, box_width, box_height);
		}
		else if(shape_type == SPRITE_SHAPE_CIRCLE)
		{
			setColor(non_selected_shape_color);

			int circle_radius = (int)project->stages[selected_stage].layers[layer_index].layer_shapes[i].radius;
			int circle_x = project->stages[selected_stage].layers[layer_index].layer_shapes[i].offset_x-adj_scroll_offset_x;
			int circle_y = project->stages[selected_stage].layers[layer_index].layer_shapes[i].offset_y-adj_scroll_offset_y;


			drawCircle(circle_x, circle_y, circle_radius);
		}
		else if(shape_type == SPRITE_SHAPE_POLYGON || shape_type == SPRITE_SHAPE_CHAIN)
		{
			setColor(non_selected_shape_color);

			if(project->stages[selected_stage].layers[layer_index].layer_shapes[i].points.size() >= 3)
			{
				shape_x = project->stages[selected_stage].layers[layer_index].layer_shapes[i].points[0].X-adj_scroll_offset_x;
				shape_y = project->stages[selected_stage].layers[layer_index].layer_shapes[i].points[0].Y-adj_scroll_offset_y;

				//std::string shape_name = project->stages[selected_stage].layers[layer_index].layer_shapes[i].shape_name;
				//std::cout << "SHAPE[" << shape_name << "] =" << shape_x << ", " << shape_y << std::endl;
			}
			else
				continue;

			for(int point_index = 1; point_index < project->stages[selected_stage].layers[layer_index].layer_shapes[i].points.size(); point_index++)
			{
				setColor(non_selected_shape_color);

				drawLine(shape_x,
						 shape_y,
						 project->stages[selected_stage].layers[layer_index].layer_shapes[i].points[point_index].X-adj_scroll_offset_x,
						 project->stages[selected_stage].layers[layer_index].layer_shapes[i].points[point_index].Y-adj_scroll_offset_y);

				shape_x = project->stages[selected_stage].layers[layer_index].layer_shapes[i].points[point_index].X-adj_scroll_offset_x;
				shape_y = project->stages[selected_stage].layers[layer_index].layer_shapes[i].points[point_index].Y-adj_scroll_offset_y;
			}
			if(project->stages[selected_stage].layers[layer_index].layer_shapes[i].points.size() > 0 && shape_type == SPRITE_SHAPE_POLYGON)
			{
				setColor(non_selected_shape_color);

				int start_x = project->stages[selected_stage].layers[layer_index].layer_shapes[i].points[0].X-adj_scroll_offset_x;
				int start_y = project->stages[selected_stage].layers[layer_index].layer_shapes[i].points[0].Y-adj_scroll_offset_y;
				drawLine(shape_x, shape_y, start_x, start_y);
			}

			shape_x = 0;
			shape_y = 0;
		}
	}
}


void wxIrrlicht::util_drawSelectedSprites()
{
	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	if(selected_layer < 0 || selected_layer >= project->getStageNumLayers(selected_stage))
		return;

	int ref_canvas = project->stages[selected_stage].layers[selected_layer].ref_canvas;

	if(ref_canvas < 0 || ref_canvas >= canvas.size())
		return;

	mapEdit_getContext();
	setActiveCanvas(ui_layer);


	wxMouseState  mouse_state = wxGetMouseState();

	int px = mouse_state.GetPosition().x - this->GetScreenPosition().x;
	int py = mouse_state.GetPosition().y - this->GetScreenPosition().y;

	int pw = this->GetSize().GetWidth();
	int ph = this->GetSize().GetHeight();


	float scroll_speed_x = project->getLayerScrollSpeed(selected_stage, selected_layer).X;
	float scroll_speed_y = project->getLayerScrollSpeed(selected_stage, selected_layer).Y;

	int adj_scroll_offset_x = scroll_speed_x * scroll_offset_x;
	int adj_scroll_offset_y = scroll_speed_y * scroll_offset_y;

	int bx = px+adj_scroll_offset_x;
	int by = py+adj_scroll_offset_y;


	setColor(rgb(255, 255, 255));

	double canvas_offset_x = 0;
	double canvas_offset_y = 0;
	getCanvasOffset(ref_canvas, &canvas_offset_x, &canvas_offset_y);

	int off_x = (int)canvas_offset_x;
	int off_y = (int)canvas_offset_y;

	for(int i = 0; i < mapEdit_selectSpriteTool_selection.size(); i++)
	{
		if(mapEdit_selectSpriteTool_selection[i].layer_sprite_index < 0 || mapEdit_selectSpriteTool_selection[i].layer_sprite_index >= sprite.size())
			continue;

		int spr_index = sprite[mapEdit_selectSpriteTool_selection[i].layer_sprite_index].layer_sprite_index;
		int base_index = project->stages[selected_stage].layers[selected_layer].layer_sprites[spr_index].sprite_base;
		if(spr_index < 0 || spr_index >= project->stages[selected_stage].layers[selected_layer].layer_sprites.size())
			continue;
		if(base_index < 0 || base_index >= project->sprite_base.size())
			continue;

		int spr_map_id = project->stages[selected_stage].layers[selected_layer].layer_sprites[spr_index].map_sprite_id;

		float scale_x = 1;
		float scale_y = 1;
		if(spr_map_id >= 0 && spr_map_id < sprite.size())
		{
			scale_x = sprite[spr_map_id].scale.X;
			scale_y = sprite[spr_map_id].scale.Y;
		}

		int x = project->stages[selected_stage].layers[selected_layer].layer_sprites[spr_index].position.X - off_x;
		int y = project->stages[selected_stage].layers[selected_layer].layer_sprites[spr_index].position.Y - off_y;
		int w = project->sprite_base[base_index].object.frame_size.Width * scale_x;
		int h = project->sprite_base[base_index].object.frame_size.Height * scale_y;

		drawRect(x, y, w, h);
	}

	//draw shapes
	int shape_x = 0;
	int shape_y = 0;

	int non_selected_shape_color = rgb(255,0,0);

	//std::cout << "shape count: " << project->stages[selected_stage].layers[selected_layer].layer_shapes.size() << std::endl;

	for(int i = 0; i < project->stages[selected_stage].layers[selected_layer].layer_shapes.size(); i++)
	{
		int shape_type = project->stages[selected_stage].layers[selected_layer].layer_shapes[i].shape_type;

		if(i == selected_shape && collision_poly_draw_flag)
			continue;

		if(shape_type == SPRITE_SHAPE_BOX)
		{
			if(i == selected_shape)
				setColor(rgb(255,255,255));
			else
				setColor(non_selected_shape_color);

			//std::cout << "cir: " << selected_shape << std::endl;
			int box_width = (int)project->stages[selected_stage].layers[selected_layer].layer_shapes[i].box_width;
			int box_height = (int)project->stages[selected_stage].layers[selected_layer].layer_shapes[i].box_height;
			int box_x = project->stages[selected_stage].layers[selected_layer].layer_shapes[i].offset_x-adj_scroll_offset_x;
			int box_y = project->stages[selected_stage].layers[selected_layer].layer_shapes[i].offset_y-adj_scroll_offset_y;

			drawRect(box_x, box_y, box_width, box_height);

			int ipx = 2;

			bool ul_selected = false;
			bool ll_selected = false;
			bool ur_selected = false;
			bool lr_selected = false;

			for(int pt_index = 0; pt_index < selected_points.size(); pt_index++)
			{
				if(selected_points[pt_index] == 0)
					ul_selected = true;
				else if(selected_points[pt_index] == 1)
					ll_selected = true;
				else if(selected_points[pt_index] == 2)
					ur_selected = true;
				else if(selected_points[pt_index] == 3)
					lr_selected = true;
			}

			// COME BACK TO THIS
			if(i == selected_shape)
			{
				if(ul_selected)
					setColor(rgb(0, 255, 0));
				else
					setColor(rgb(255,255,255));
			}
			else
			{
				setColor(non_selected_shape_color);
			}

			//setColor( collision_circleShapeSelect_u ? rgb(0,255, 0) : rgb(0, 0, 0) );
			drawRectFill(box_x-ipx, box_y-ipx, ipx*2, ipx*2);


			if(i == selected_shape)
			{
				if(ll_selected)
					setColor(rgb(0, 255, 0));
				else
					setColor(rgb(255,255,255));
			}
			else
			{
				setColor(non_selected_shape_color);
			}

			//setColor( collision_circleShapeSelect_d ? rgb(0,255, 0) : rgb(0, 0, 0) );
			drawRectFill(box_x-ipx, (box_y+box_height)-ipx, ipx*2, ipx*2);


			if(i == selected_shape)
			{
				if(ur_selected)
					setColor(rgb(0, 255, 0));
				else
					setColor(rgb(255,255,255));
			}
			else
			{
				setColor(non_selected_shape_color);
			}
			//setColor( collision_circleShapeSelect_l ? rgb(0,255, 0) : rgb(0, 0, 0) );
			drawRectFill((box_x+box_width)-ipx, box_y-ipx, ipx*2, ipx*2);


			if(i == selected_shape)
			{
				if(lr_selected)
					setColor(rgb(0, 255, 0));
				else
					setColor(rgb(255,255,255));
			}
			else
			{
				setColor(non_selected_shape_color);
			}
			//setColor( collision_circleShapeSelect_r ? rgb(0,255, 0) : rgb(0, 0, 0) );
			drawRectFill((box_x+box_width)-ipx, (box_y+box_height)-ipx, ipx*2, ipx*2);
		}
		else if(shape_type == SPRITE_SHAPE_CIRCLE)
		{
			if(i == selected_shape)
				setColor(rgb(255,255,255));
			else
				setColor(non_selected_shape_color);

			int circle_radius = (int)project->stages[selected_stage].layers[selected_layer].layer_shapes[i].radius;
			int circle_x = project->stages[selected_stage].layers[selected_layer].layer_shapes[i].offset_x-adj_scroll_offset_x;
			int circle_y = project->stages[selected_stage].layers[selected_layer].layer_shapes[i].offset_y-adj_scroll_offset_y;

			//std::cout << "draw circle: " << i << " -> " << circle_x << ", " << circle_y << ", " << circle_radius << std::endl;

			int pt_u_x = circle_x;
			int pt_u_y = circle_y-circle_radius;

			int pt_d_x = circle_x;
			int pt_d_y = circle_y+circle_radius;

			int pt_l_x = circle_x-circle_radius;
			int pt_l_y = circle_y;

			int pt_r_x = circle_x+circle_radius;
			int pt_r_y = circle_y;

			drawCircle(circle_x, circle_y, circle_radius);

			int ipx = 2;


			bool top_selected = false;
			bool left_selected = false;
			bool right_selected = false;
			bool bottom_selected = false;

			for(int pt_index = 0; pt_index < selected_points.size(); pt_index++)
			{
				if(selected_points[pt_index] == 0)
					top_selected = true;
				else if(selected_points[pt_index] == 1)
					left_selected = true;
				else if(selected_points[pt_index] == 2)
					right_selected = true;
				else if(selected_points[pt_index] == 3)
					bottom_selected = true;
			}

			// COME BACK TO THIS
			if(i == selected_shape)
			{
				if(top_selected)
					setColor(rgb(0, 255, 0));
				else
					setColor(rgb(255,255,255));
			}
			else
			{
				setColor(non_selected_shape_color);
			}
			//setColor( collision_circleShapeSelect_u ? rgb(0,255, 0) : rgb(0, 0, 0) );
			drawRectFill(pt_u_x-ipx, pt_u_y-ipx, ipx*2, ipx*2);


			if(i == selected_shape)
			{
				if(bottom_selected)
					setColor(rgb(0, 255, 0));
				else
					setColor(rgb(255,255,255));
			}
			else
			{
				setColor(non_selected_shape_color);
			}
			//setColor( collision_circleShapeSelect_d ? rgb(0,255, 0) : rgb(0, 0, 0) );
			drawRectFill(pt_d_x-ipx, pt_d_y-ipx, ipx*2, ipx*2);

			if(i == selected_shape)
			{
				if(left_selected)
					setColor(rgb(0, 255, 0));
				else
					setColor(rgb(255,255,255));
			}
			else
			{
				setColor(non_selected_shape_color);
			}
			//setColor( collision_circleShapeSelect_l ? rgb(0,255, 0) : rgb(0, 0, 0) );
			drawRectFill(pt_l_x-ipx, pt_l_y-ipx, ipx*2, ipx*2);

			if(i == selected_shape)
			{
				if(right_selected)
					setColor(rgb(0, 255, 0));
				else
					setColor(rgb(255,255,255));
			}
			else
			{
				setColor(non_selected_shape_color);
			}
			//setColor( collision_circleShapeSelect_r ? rgb(0,255, 0) : rgb(0, 0, 0) );
			drawRectFill(pt_r_x-ipx, pt_r_y-ipx, ipx*2, ipx*2);
		}
		else if(shape_type == SPRITE_SHAPE_POLYGON || shape_type == SPRITE_SHAPE_CHAIN)
		{
			if(i == selected_shape)
				setColor(rgb(255,255,255));
			else
				setColor(non_selected_shape_color);

			if(project->stages[selected_stage].layers[selected_layer].layer_shapes[i].point_selection.size() != project->stages[selected_stage].layers[selected_layer].layer_shapes[i].points.size())
			{
				for(int n = project->stages[selected_stage].layers[selected_layer].layer_shapes[i].point_selection.size(); n < project->stages[selected_stage].layers[selected_layer].layer_shapes[i].points.size(); n++)
				{
					project->stages[selected_stage].layers[selected_layer].layer_shapes[i].point_selection.push_back(false);
				}
			}

			if(project->stages[selected_stage].layers[selected_layer].layer_shapes[i].points.size() > 0)
			{
				shape_x = project->stages[selected_stage].layers[selected_layer].layer_shapes[i].points[0].X-adj_scroll_offset_x;
				shape_y = project->stages[selected_stage].layers[selected_layer].layer_shapes[i].points[0].Y-adj_scroll_offset_y;

				if(i == selected_shape)
				{
					if(project->stages[selected_stage].layers[selected_layer].layer_shapes[i].point_selection[0])
						setColor(rgb(0, 255, 0));
					else
						setColor(rgb(255,255,255));
				}
				else
				{
					setColor(non_selected_shape_color);
				}

				drawRectFill(shape_x-2, shape_y-2, 4, 4);
			}

			for(int point_index = 1; point_index < project->stages[selected_stage].layers[selected_layer].layer_shapes[i].points.size(); point_index++)
			{
				if(i == selected_shape)
					setColor(rgb(255,255,255));
				else
					setColor(non_selected_shape_color);

				drawLine(shape_x,
						 shape_y,
						 project->stages[selected_stage].layers[selected_layer].layer_shapes[i].points[point_index].X-adj_scroll_offset_x,
						 project->stages[selected_stage].layers[selected_layer].layer_shapes[i].points[point_index].Y-adj_scroll_offset_y);

				shape_x = project->stages[selected_stage].layers[selected_layer].layer_shapes[i].points[point_index].X-adj_scroll_offset_x;
				shape_y = project->stages[selected_stage].layers[selected_layer].layer_shapes[i].points[point_index].Y-adj_scroll_offset_y;

				if(i == selected_shape)
				{
					if(project->stages[selected_stage].layers[selected_layer].layer_shapes[i].point_selection[point_index])
						setColor(rgb(0, 255, 0));
					else
						setColor(rgb(255,255,255));
				}
				else
				{
					setColor(non_selected_shape_color);
				}

				drawRectFill(shape_x-2, shape_y-2, 4, 4);
			}
			if(project->stages[selected_stage].layers[selected_layer].layer_shapes[i].points.size() > 0 && shape_type == SPRITE_SHAPE_POLYGON)
			{
				if(i == selected_shape)
					setColor(rgb(255,255,255));
				else
					setColor(non_selected_shape_color);

				int start_x = project->stages[selected_stage].layers[selected_layer].layer_shapes[i].points[0].X-adj_scroll_offset_x;
				int start_y = project->stages[selected_stage].layers[selected_layer].layer_shapes[i].points[0].Y-adj_scroll_offset_y;
				drawLine(shape_x, shape_y, start_x, start_y);
				//drawRectFill((collision_physics_obj.points[0].X-adj_scroll_offset_x)-2, (collision_physics_obj.points[0].X-adj_scroll_offset_x)-2, 4, 4);
			}
		}
	}

	if(left_drag_init && map_tool == MAP_TOOL_SHAPE_BOXSELECT)
	{
		setColor(rgb(255,255,255));
		int bselect_w = bx - drag_start.x;
		int bselect_h = by - drag_start.y;
		drawRect(drag_start.x-adj_scroll_offset_x, drag_start.y-adj_scroll_offset_y, bselect_w, bselect_h);
	}

	if(selected_shape >= 0 && selected_shape < project->stages[selected_stage].layers[selected_layer].layer_shapes.size())
	{
		int shape_type = project->stages[selected_stage].layers[selected_layer].layer_shapes[selected_shape].shape_type;
		setColor(rgb(0, 255, 0));

		if(shape_type == SPRITE_SHAPE_POLYGON || shape_type == SPRITE_SHAPE_CHAIN)
		{
			if(collision_physics_obj.points.size() > 0)
			{
				shape_x = collision_physics_obj.points[0].X-adj_scroll_offset_x;
				shape_y = collision_physics_obj.points[0].Y-adj_scroll_offset_y;
				drawRectFill(shape_x-2, shape_y-2, 4, 4);
			}
			for(int point_index = 1; point_index < collision_physics_obj.points.size(); point_index++)
			{
				drawLine(shape_x, shape_y, collision_physics_obj.points[point_index].X-adj_scroll_offset_x, collision_physics_obj.points[point_index].Y-adj_scroll_offset_y);
				shape_x = collision_physics_obj.points[point_index].X-adj_scroll_offset_x;
				shape_y = collision_physics_obj.points[point_index].Y-adj_scroll_offset_y;
				drawRectFill(shape_x-2, shape_y-2, 4, 4);
			}

			if(collision_poly_draw_flag && collision_physics_obj.points.size() > 0)
			{
				int poly_x = px;
				int poly_y = py;
				if(tile_snap)
				{
					poly_x = bx / current_frame_width * current_frame_width - adj_scroll_offset_x;
					poly_y = by / current_frame_height * current_frame_height - adj_scroll_offset_y;
				}

				drawLine(shape_x, shape_y, poly_x, poly_y);
				drawRectFill(poly_x-2, poly_y-2, 4, 4);
			}
		}
		else if(shape_type == SPRITE_SHAPE_CIRCLE && collision_poly_draw_flag)
		{
			//std::cout << "cir: " << selected_shape << std::endl;
			int circle_radius = (int)collision_physics_obj.radius;
			int circle_x = collision_physics_obj.offset_x-adj_scroll_offset_x;
			int circle_y = collision_physics_obj.offset_y-adj_scroll_offset_y;

			int pt_u_x = circle_x;
			int pt_u_y = circle_y-circle_radius;

			int pt_d_x = circle_x;
			int pt_d_y = circle_y+circle_radius;

			int pt_l_x = circle_x-circle_radius;
			int pt_l_y = circle_y;

			int pt_r_x = circle_x+circle_radius;
			int pt_r_y = circle_y;

			drawCircle(circle_x, circle_y, circle_radius);

			int ipx = 2;

			//setColor( collision_circleShapeSelect_u ? rgb(0,255, 0) : rgb(0, 0, 0) );
			drawRectFill(pt_u_x-ipx, pt_u_y-ipx, ipx*2, ipx*2);

			//setColor( collision_circleShapeSelect_d ? rgb(0,255, 0) : rgb(0, 0, 0) );
			drawRectFill(pt_d_x-ipx, pt_d_y-ipx, ipx*2, ipx*2);

			//setColor( collision_circleShapeSelect_l ? rgb(0,255, 0) : rgb(0, 0, 0) );
			drawRectFill(pt_l_x-ipx, pt_l_y-ipx, ipx*2, ipx*2);

			//setColor( collision_circleShapeSelect_r ? rgb(0,255, 0) : rgb(0, 0, 0) );
			drawRectFill(pt_r_x-ipx, pt_r_y-ipx, ipx*2, ipx*2);

		}
		else if(shape_type == SPRITE_SHAPE_BOX && collision_poly_draw_flag)
		{
			//std::cout << "cir: " << selected_shape << std::endl;
			int box_width = (int)collision_physics_obj.box_width;
			int box_height = (int)collision_physics_obj.box_height;
			int box_x = collision_physics_obj.offset_x-adj_scroll_offset_x;
			int box_y = collision_physics_obj.offset_y-adj_scroll_offset_y;

			drawRect(box_x, box_y, box_width, box_height);

			int ipx = 2;

			//setColor( collision_circleShapeSelect_u ? rgb(0,255, 0) : rgb(0, 0, 0) );
			drawRectFill(box_x-ipx, box_y-ipx, ipx*2, ipx*2);

			//setColor( collision_circleShapeSelect_d ? rgb(0,255, 0) : rgb(0, 0, 0) );
			drawRectFill(box_x-ipx, (box_y+box_height)-ipx, ipx*2, ipx*2);

			//setColor( collision_circleShapeSelect_l ? rgb(0,255, 0) : rgb(0, 0, 0) );
			drawRectFill((box_x+box_width)-ipx, box_y-ipx, ipx*2, ipx*2);

			//setColor( collision_circleShapeSelect_r ? rgb(0,255, 0) : rgb(0, 0, 0) );
			drawRectFill((box_x+box_width)-ipx, (box_y+box_height)-ipx, ipx*2, ipx*2);

		}
	}
}


//This function is called on each canvas on update
void wxIrrlicht::util_drawSprites(int canvas_id)
{
	//Setting the render target to the current canvas.  NOTE: I might change this target to a separate sprite layer later.
	m_pDriver->setRenderTarget(canvas[canvas_id].texture, true, true);
	m_pDriver->clearBuffers(true, true, true, irr::video::SColor(0,0,0,0));


	irr::core::dimension2d<irr::u32> src_size;
	irr::core::rect<irr::s32> sourceRect;

	irr::core::position2d<irr::s32> position;

	irr::core::position2d<irr::s32> rotationPoint;

	irr::f32 rotation = 0;
	irr::core::vector2df scale(1.0, 1.0);
	bool useAlphaChannel = true;
	irr::video::SColor color;

	irr::core::vector2df screenSize(canvas[canvas_id].dimension.Width, canvas[canvas_id].dimension.Height);

	int x = 0;
	int y = 0;

	irr::f32 RAD_TO_DEG = 180.0/3.141592653589793238463;

	double spr_timer = m_pDevice->getTimer()->getTime();

	int offset_x = canvas[canvas_id].offset.X;
	int offset_y = canvas[canvas_id].offset.Y;

	//std::cout << "DG: " << canvas[canvas_id].sprite_id.size() << " ~ " << sprite.size() << std::endl;

	for(int spr_index = 0; spr_index < canvas[canvas_id].sprite_id.size(); spr_index++)
	{
		int spr_id = canvas[canvas_id].sprite_id[spr_index];

		sprite2D_obj* n_sprite = &sprite[spr_id];

		if(!n_sprite->active)
			continue;
		//std::cout << "TEST" << std::endl;
		//td::cout << "debug info: " << canvas_id << " --> " << spr_index << "   id = " << sprite->id << "   anim_size = " << sprite->animation.size() << std::endl; continue;
		if(!n_sprite->visible)
			continue;

		x = n_sprite->position.X - offset_x;
		y = n_sprite->position.Y - offset_y;

		int xf = x + (n_sprite->frame_size.Width * n_sprite->scale.X);
		int yf = y + (n_sprite->frame_size.Height * n_sprite->scale.Y);

		//std::cout << "sprite info[" << spr_index << "]: (" << x << ", " << y << ") (" << xf << ", " << yf << ")" << std::endl;

		int post_x = x - (n_sprite->frame_size.Width * n_sprite->scale.X);
		int post_y = y - (n_sprite->frame_size.Height * n_sprite->scale.Y);

		if( (xf < 0) || (post_x > ((int)canvas[canvas_id].viewport.dimension.Width)) )
		{
			//std::cout << "skip draw[X]: " << spr_index << std::endl;
			continue;
		}

		if( (yf < 0) || (post_y > ((int)canvas[canvas_id].viewport.dimension.Height)) )
		{
			//std::cout << "skip draw[Y]: " << spr_index << std::endl;
			continue;
		}

		position.set(x, y);

		int img_id = n_sprite->image_id;
		if(img_id < 0 || img_id >= image.size())
			continue;

		//src_size = rc_image[img_id].image->getSize();
		int current_animation = n_sprite->current_animation;
		//std::cout << "current_animation = " << n_sprite->current_animation << " ~ " << n_sprite->animation.size() << std::endl;
		if((spr_timer - n_sprite->animation[current_animation].frame_start_time) >= n_sprite->animation[current_animation].frame_swap_time)
		{
			n_sprite->animation[current_animation].current_frame++;

			if(n_sprite->animation[current_animation].current_frame >= n_sprite->animation[current_animation].num_frames)
			{
				n_sprite->animation[current_animation].current_frame = 0;
				n_sprite->current_animation_loop++;

				if(n_sprite->current_animation_loop >= n_sprite->num_animation_loops)
				{
					if(n_sprite->num_animation_loops < 0)
						n_sprite->isPlaying = true;
					else
						n_sprite->isPlaying = false;
					n_sprite->current_animation_loop = 0;
				}
			}

			if(!n_sprite->isPlaying)
				n_sprite->animation[current_animation].current_frame = 0;

			n_sprite->animation[current_animation].frame_start_time = spr_timer;
		}

		int current_animation_frame = n_sprite->animation[current_animation].current_frame;

		int frame_x = (int)(n_sprite->animation[current_animation].frames[current_animation_frame]%n_sprite->frames_per_row)*n_sprite->frame_size.Width;
		int frame_y = (int)(n_sprite->animation[current_animation].frames[current_animation_frame]/n_sprite->frames_per_row)*n_sprite->frame_size.Height;
		irr::core::vector2d<irr::s32> frame_pos(frame_x, frame_y);
		src_size = n_sprite->frame_size;
		sourceRect = irr::core::rect<irr::s32>( frame_pos, src_size);
		//sourceRect = irr::core::rect<irr::s32>( irr::core::vector2d<irr::s32>(0, 0), src_size);

		//physics_pos = n_sprite->physics.body->GetPosition();
		//x = (int)physics_pos.x;
		//y = (int)physics_pos.y;
		//position.set(x, y);

		scale.set(n_sprite->scale.X, n_sprite->scale.Y);

		rotationPoint.set(x + (src_size.Width/2)*scale.X, y + (src_size.Height/2)*scale.Y); //TODO: need to account for offset once that is implemented
		rotation = n_sprite->angle;

		color.set(n_sprite->alpha,
							 n_sprite->color_mod.getRed(),
							 n_sprite->color_mod.getGreen(),
							 n_sprite->color_mod.getBlue());

		//I don't want to draw an image that doesn't exists. Thats just crazy.
		if(m_pDriver->getDriverType() == irr::video::EDT_OPENGL)
			util_draw2DImage(m_pDriver, image[img_id].image, sourceRect, position, rotationPoint, rotation, scale, useAlphaChannel, color, screenSize);
		else
		{
			//setColor(rgb(255,0,0));
			//drawRectFill(0, 0, 100, 100);
			//std::cout << "COME ON" << std::endl;
			drawImage_BlitEx_SW(img_id, 0, 0, 64, 64, frame_pos.X, frame_pos.Y, current_frame_width, current_frame_height);
		}
	}
	//Must set back to canvas 0 (the backbuffer) before returning

	m_pDriver->setRenderTarget(canvas[back_buffer].texture, false, false);
}

//-----------------------------END OF SPRITE STUFF------------------------------------------------------------------------------






int wxIrrlicht::createTileSet(int img_id, int tile_w, int tile_h)
{
	if(img_id < 0 || img_id >= image.size())
		return -1;

	if(!image[img_id].image)
		return -1;

	tileset_obj tset;

	tset.active = true;
	tset.img_id = img_id;

	tset.tile_width = tile_w;
	tset.tile_height = tile_h;

	//std::cout << "CreateTileset: " << img_id << ", " << tile_w << ", " << tile_h << std::endl;

	int num_tiles = ((int)image[img_id].image->getOriginalSize().Width / tile_w) * ((int)image[img_id].image->getOriginalSize().Height / tile_h);
	tset.tiles.resize(num_tiles);

	for(int i = 0; i < tset.tiles.size(); i++)
	{
		tset.tiles[i].frames.push_back(i);
		tset.tiles[i].fps = 0;
		tset.tiles[i].frame_swap_time = 0;
		tset.tiles[i].frame_start_time = 0;
		tset.tiles[i].num_frames = 1;
	}

	int tset_id = tileset.size();

	if(deleted_tileset.size() > 0)
	{
		tset_id = deleted_tileset[0];
		deleted_tileset.erase(deleted_tileset.begin());
		tileset[tset_id] = tset;
	}
	else
		tileset.push_back(tset);

	return tset_id;
}

void wxIrrlicht::deleteTileSet(int tset)
{
	if(tset < 0 || tset >= tileset.size())
		return;

	if(!tileset[tset].active)
		return;

	tileset[tset].tiles.clear();
	tileset[tset].img_id = -1;
	tileset[tset].active = false;

	deleted_tileset.push_back(tset);
}

void wxIrrlicht::setTileAnimationLength(int tset, int base_tile, int num_frames)
{
	if(tset < 0 || tset >= tileset.size())
		return;

	if(!tileset[tset].active)
		return;

	if(base_tile < 0 || base_tile >= tileset[tset].tiles.size())
		return;

	tileset[tset].tiles[base_tile].frames.resize(num_frames);
	tileset[tset].tiles[base_tile].num_frames = num_frames;
}

int wxIrrlicht::getTileAnimationLength(int tset, int base_tile)
{
	if(tset < 0 || tset >= tileset.size())
		return 0;

	if(!tileset[tset].active)
		return 0;

	if(base_tile < 0 || base_tile >= tileset[tset].tiles.size())
		return 0;

	return tileset[tset].tiles[base_tile].num_frames;
}

void wxIrrlicht::setTileAnimationFrame(int tset, int base_tile, int anim_frame, int tile_frame)
{
	if(tset < 0 || tset >= tileset.size())
		return;

	if(!tileset[tset].active)
		return;

	if(base_tile < 0 || base_tile >= tileset[tset].tiles.size())
		return;

	tileset[tset].tiles[base_tile].frames[anim_frame] = tile_frame;
}

int wxIrrlicht::getTileAnimationFrame(int tset, int base_tile, int anim_frame)
{
	if(tset < 0 || tset >= tileset.size())
		return -1;

	if(!tileset[tset].active)
		return -1;

	if(base_tile < 0 || base_tile >= tileset[tset].tiles.size())
		return -1;

	return tileset[tset].tiles[base_tile].frames[anim_frame];
}


void wxIrrlicht::setTileAnimationSpeed(int tset, int base_tile, double speed)
{
	if(tset < 0 || tset >= tileset.size())
		return;

	if(!tileset[tset].active)
		return;

	if(base_tile < 0 || base_tile >= tileset[tset].tiles.size())
		return;

	tileset[tset].tiles[base_tile].fps = speed;
	tileset[tset].tiles[base_tile].frame_swap_time = 1000/speed;
}

double wxIrrlicht::getTileAnimationSpeed(int tset, int base_tile)
{
	if(tset < 0 || tset >= tileset.size())
		return 0;

	if(!tileset[tset].active)
		return 0;

	if(base_tile < 0 || base_tile >= tileset[tset].tiles.size())
		return 0;

	return tileset[tset].tiles[base_tile].fps;
}


//--------------------------------------TILEMAP-----------------------------------------------
int wxIrrlicht::createTileMap(int tset, int widthInTiles, int heightInTiles)
{
	if(tset < 0 || tset >= tileset.size())
		return -1;

	if(!tileset[tset].active)
		return -1;

	tilemap_obj tmap;

	tmap.active = true;
	tmap.texture = NULL;
	tmap.tileset = tset;

	tmap.num_tiles_across = widthInTiles;
	tmap.num_tiles_down = heightInTiles;

	tmap.rows.resize(heightInTiles);
	for(int i = 0; i < tmap.rows.size(); i++)
	{
		tmap.rows[i].tile.resize(widthInTiles);
	}

	int tm_id = tilemap.size();

	if(deleted_tilemap.size() > 0)
	{
		tm_id = deleted_tilemap[0];
		deleted_tilemap.erase(deleted_tilemap.begin());
		tilemap[tm_id] = tmap;
	}
	else
		tilemap.push_back(tmap);

	return tm_id;
}

void wxIrrlicht::deleteTileMap(int tmap)
{
	if(tmap < 0 || tmap >= tilemap.size())
		return;

	if(!tilemap[tmap].active)
		return;

	tilemap[tmap].rows.clear();
	tilemap[tmap].num_tiles_across = 0;
	tilemap[tmap].num_tiles_down = 0;
	tilemap[tmap].texture = NULL;
	tilemap[tmap].tileset = -1;
	tilemap[tmap].active = false;

	deleted_tilemap.push_back(tmap);
}

bool wxIrrlicht::tilesetExists(int tset)
{
	if(tset < 0 || tset >= tileset.size())
		return false;

	return tileset[tset].active;
}

void wxIrrlicht::setTileMapSize(int tmap, int widthInTiles, int heightInTiles)
{
	if(tmap < 0 || tmap >= tilemap.size())
		return;

	if(!tilemap[tmap].active)
		return;

	tilemap[tmap].num_tiles_across = widthInTiles;
	tilemap[tmap].num_tiles_down = heightInTiles;

	tilemap[tmap].rows.resize(heightInTiles);
	for(int i = 0; i < tilemap[tmap].rows.size(); i++)
	{
		tilemap[tmap].rows[i].tile.resize(widthInTiles);
	}
}

void wxIrrlicht::getTileMapSize(int tmap, double* widthInTiles, double* heightInTiles)
{
	if(tmap < 0 || tmap >= tilemap.size())
		return;

	if(!tilemap[tmap].active)
		return;

	*widthInTiles = tilemap[tmap].num_tiles_across;
	*heightInTiles = tilemap[tmap].num_tiles_down;
}

void wxIrrlicht::setTile(int tmap, int tile, int x, int y)
{
	if(tmap < 0 || tmap >= tilemap.size())
		return;

	if(!tilemap[tmap].active)
		return;

	int tset = tilemap[tmap].tileset;

	//if tilemap exists, then its safe to assume tileset is in range since tilemap can't be created if its not
	if(!tileset[tset].active)
		return;

	int num_tset_tiles = tileset[tset].tiles.size();

	if(tile < 0 || tile >= num_tset_tiles)
		tile = -1;

	if( (x < 0 || x >= tilemap[tmap].num_tiles_across) || (y < 0 || y >= tilemap[tmap].num_tiles_down) )
		return;

	tilemap[tmap].rows[y].tile[x] = tile;
}

int wxIrrlicht::getTile(int tmap, int x, int y)
{
	if(tmap < 0 || tmap >= tilemap.size())
		return -1;

	if(!tilemap[tmap].active)
		return -1;

	if( (x < 0 || x >= tilemap[tmap].num_tiles_across) || (y < 0 || y >= tilemap[tmap].num_tiles_down) )
		return -1;

	return tilemap[tmap].rows[y].tile[x];
}

void wxIrrlicht::fillTile(int tmap, int tile, int x, int y, int widthInTiles, int heightInTiles)
{
	if(tmap < 0 || tmap >= tilemap.size())
		return;

	if(!tilemap[tmap].active)
		return;

	int tset = tilemap[tmap].tileset;

	//if tilemap exists, then its safe to assume tileset is in range since tilemap can't be created if its not
	if(!tileset[tset].active)
		return;

	int num_tset_tiles = tileset[tset].tiles.size();

	if(tile < 0 || tile >= num_tset_tiles)
		tile = -1;

	if( (x < 0 || x >= tilemap[tmap].num_tiles_across) || (y < 0 || y >= tilemap[tmap].num_tiles_down) )
		return;

	if( ( (x+widthInTiles) < 0 || (x+widthInTiles) > tilemap[tmap].num_tiles_across) || ( (y+heightInTiles) < 0 || (y+heightInTiles) > tilemap[tmap].num_tiles_down) )
		return;

	for(int iy = 0; iy < heightInTiles; iy++)
		for(int ix = 0; ix < widthInTiles; ix++)
			tilemap[tmap].rows[y+iy].tile[x+ix] = tile;
}

void wxIrrlicht::getTileInTileset(int tset, int tile, int* x, int* y)
{
	int img_w = image[ tileset[tset].img_id ].image->getOriginalSize().Width;
	int img_h = image[ tileset[tset].img_id ].image->getOriginalSize().Height;
	int tile_w = tileset[tset].tile_width;
	int tile_h = tileset[tset].tile_height;
	int widthInTiles = img_w / tile_w;

	*x = (tile%widthInTiles) * tile_w;
	*y = (tile/widthInTiles) * tile_h;
}

int wxIrrlicht::getNumTilesInTileset(int tset)
{
	int img_w = image[ tileset[tset].img_id ].image->getOriginalSize().Width;
	int img_h = image[ tileset[tset].img_id ].image->getOriginalSize().Height;
	int tile_w = tileset[tset].tile_width;
	int tile_h = tileset[tset].tile_height;
	int widthInTiles = img_w / tile_w;
	int heightInTiles = img_h / tile_h;

	return (widthInTiles*heightInTiles);
}

void wxIrrlicht::updateTileset(int tset)
{
	irr::u32 current_time_ms = m_pDevice->getTimer()->getTime();
	for(int i = 0; i < tileset[tset].tiles.size(); i++)
	{
		if( (current_time_ms-tileset[tset].tiles[i].frame_start_time) >= tileset[tset].tiles[i].frame_swap_time )
		{
			tileset[tset].tiles[i].current_frame++;
			if(tileset[tset].tiles[i].current_frame >= tileset[tset].tiles[i].num_frames)
				tileset[tset].tiles[i].current_frame = 0;

			tileset[tset].tiles[i].frame_start_time = current_time_ms;
		}
	}
}

void wxIrrlicht::drawTileMap(int tmap, int x, int y, int w, int h, int offset_x, int offset_y)
{
	if(tmap < 0 || tmap >= tilemap.size())
		return;

	if(!tilemap[tmap].active)
		return;

	if(active_canvas < 0 || active_canvas >= canvas.size())
		return;

	if(!canvas[active_canvas].type == CANVAS_TYPE_2D)
		return;

	if(!canvas[active_canvas].texture)
		return;

	tilemap[tmap].texture = m_pDriver->addRenderTargetTexture(irr::core::dimension2d<u32>(w,h), "rt", ECF_A8R8G8B8);
	m_pDriver->setRenderTarget(tilemap[tmap].texture, true, true, irr::video::SColor(0,0,0,0));


	int tset = tilemap[tmap].tileset;

	updateTileset(tset);

	int vp_widthInTiles = w/tileset[tset].tile_width;
	int vp_heightInTiles = h/tileset[tset].tile_height;

	int tset_img_id = tileset[tset].img_id;
	int src_w = tileset[tset].tile_width;
	int src_h = tileset[tset].tile_height;

	int tile_offset_x = offset_x / src_w;
	int tile_offset_y = offset_y / src_h;

	int screen_offset_x = 0 - (offset_x % src_w);
	int screen_offset_y = 0 - (offset_y % src_h);

	int num_tiles_in_tset = getNumTilesInTileset(tset);

	for(int iy = 0; iy < vp_heightInTiles+1; iy++)
	{
		for(int ix = 0; ix < vp_widthInTiles+1; ix++)
		{
			int current_frame = 0; //TODO: ADD TIMING
			int map_x = tile_offset_x + ix;
			int map_y = tile_offset_y + iy;

			if(map_x < 0 || map_x >= tilemap[tmap].num_tiles_across || map_y < 0 || map_y >= tilemap[tmap].num_tiles_down)
				continue;

			int tile = tilemap[tmap].rows[map_y].tile[map_x];

			if(tile < 0 || tile >= num_tiles_in_tset)
				continue;

			current_frame = tileset[tset].tiles[tile].current_frame;
			tile = tileset[tset].tiles[tile].frames[current_frame];

			if(tile < 0 || tile >= num_tiles_in_tset)
				continue;

			int src_x = 0;
			int src_y = 0;
			getTileInTileset(tset, tile, &src_x, &src_y);
			//std::cout << "DEBUG TMAP: " << tile << " -> " << src_x << ", " << src_y << std::endl;
			irr::core::rect<irr::s32> sourceRect( irr::core::vector2d<irr::s32>(src_x, src_y), irr::core::dimension2d<irr::s32>(src_w, src_h));

			irr::video::SColor color(image[tset_img_id].alpha,
									image[tset_img_id].color_mod.getRed(),
									image[tset_img_id].color_mod.getGreen(),
									image[tset_img_id].color_mod.getBlue());

			int dst_x = screen_offset_x + (ix*src_w);
			int dst_y = screen_offset_y + (iy*src_h);
			irr::core::rect<irr::s32> dest( irr::core::vector2d<irr::s32>(dst_x, dst_y), irr::core::dimension2d<irr::s32>(src_w, src_h));


			m_pDriver->draw2DImage(image[tset_img_id].image, dest, sourceRect, 0, 0, true);
		}
	}

	m_pDriver->setRenderTarget(canvas[active_canvas].texture, false, false);

	irr::core::rect<irr::s32> sourceRect( irr::core::vector2d<irr::s32>(0, 0), irr::core::dimension2d<irr::s32>(w, h));
	irr::core::rect<irr::s32> dest( irr::core::vector2d<irr::s32>(x, y), irr::core::dimension2d<irr::s32>(w, h));

	m_pDriver->draw2DImage(tilemap[tmap].texture, dest, sourceRect, 0, 0, false);
	m_pDriver->removeTexture(tilemap[tmap].texture);
	tilemap[tmap].texture = NULL;
	//draw2DImage(VideoDriver, rc_tilemap[tilemap].texture, src, pos,)
}






int wxIrrlicht::util_getNumTilesInTileset(int project_tset)
{
	//std::cout << "tset dbg: " << project_tset << ", " << project->tileset[ project_tset ].tileset_name << ", " << image.size() << " < " << project->tileset[ project_tset ].object.img_id << std::endl;
	int img_w = image[ project->tileset[ project_tset ].object.img_id ].image->getOriginalSize().Width;
	int img_h = image[ project->tileset[ project_tset ].object.img_id ].image->getOriginalSize().Height;
	int tile_w = project->tileset[ project_tset ].object.tile_width;
	int tile_h = project->tileset[ project_tset ].object.tile_height;
	int widthInTiles = img_w / tile_w;
	int heightInTiles = img_h / tile_h;

	return (widthInTiles*heightInTiles);
}

void wxIrrlicht::util_updateTileset(int project_tset)
{
	if(project_tset < 0 || project_tset >= project->tileset.size())
		return;

	irr::u32 current_time_ms = m_pDevice->getTimer()->getTime();
	for(int i = 0; i < project->tileset[ project_tset ].object.tiles.size(); i++)
	{
		if( (current_time_ms-project->tileset[ project_tset ].object.tiles[i].frame_start_time) >= project->tileset[ project_tset ].object.tiles[i].frame_swap_time )
		{
			project->tileset[ project_tset ].object.tiles[i].current_frame++;
			if(project->tileset[ project_tset ].object.tiles[i].current_frame >= project->tileset[ project_tset ].object.tiles[i].num_frames)
				project->tileset[ project_tset ].object.tiles[i].current_frame = 0;

			project->tileset[ project_tset ].object.tiles[i].frame_start_time = current_time_ms;
		}
	}
}

void wxIrrlicht::util_getTileInTileset(int project_tset, int tile, int* x, int* y)
{
	if(project_tset < 0 || project_tset >= project->tileset.size())
		return;

	int img_w = image[ project->tileset[ project_tset ].object.img_id ].image->getOriginalSize().Width;
	int img_h = image[ project->tileset[ project_tset ].object.img_id ].image->getOriginalSize().Height;
	int tile_w = project->tileset[ project_tset ].object.tile_width;
	int tile_h = project->tileset[ project_tset ].object.tile_height;
	int widthInTiles = img_w / tile_w;

	*x = (tile%widthInTiles) * tile_w;
	*y = (tile/widthInTiles) * tile_h;
}


void wxIrrlicht::util_drawTileLayer(int layer)
{
	if(selected_stage < 0 || selected_stage >= project->getStageCount())
		return;

	if(layer < 0 || layer >= project->getStageNumLayers(selected_stage))
		return;

	int ref_canvas = project->stages[selected_stage].layers[layer].ref_canvas;

	if(ref_canvas < 0 || ref_canvas >= canvas.size())
		return;

	if(!canvas[ref_canvas].texture)
		return;

	int x = 0;
	int y = 0;
	int w = this->GetClientSize().GetWidth()+current_frame_width;
	int h = this->GetClientSize().GetHeight()+current_frame_height;

	int offset_x = (int)( (float)(scroll_offset_x) * project->stages[selected_stage].layers[layer].scroll_speed.X );
	int offset_y = (int)( (float)(scroll_offset_y) * project->stages[selected_stage].layers[layer].scroll_speed.Y );


	project->stages[selected_stage].layers[layer].layer_map.tile_map.texture = m_pDriver->addRenderTargetTexture(irr::core::dimension2d<u32>(w,h), "rt", ECF_A8R8G8B8);
	m_pDriver->setRenderTarget(project->stages[selected_stage].layers[layer].layer_map.tile_map.texture, true, true, irr::video::SColor(0,0,0,0));


	int tset = project->stages[selected_stage].layers[layer].layer_map.nv_tileset_index;

	if(tset < 0 || tset >= project->tileset.size())
		return;

	util_updateTileset(tset);

	int vp_widthInTiles = w/project->tileset[ tset ].object.tile_width;
	int vp_heightInTiles = h/project->tileset[ tset ].object.tile_height;

	int tset_img_id = project->tileset[ tset ].object.img_id;
	int src_w = project->tileset[ tset ].object.tile_width;
	int src_h = project->tileset[ tset ].object.tile_height;

	int tile_offset_x = offset_x / src_w;
	int tile_offset_y = offset_y / src_h;

	int screen_offset_x = 0 - (offset_x % src_w);
	int screen_offset_y = 0 - (offset_y % src_h);

	int num_tiles_in_tset = util_getNumTilesInTileset(tset);

	for(int iy = 0; iy < vp_heightInTiles+1; iy++)
	{
		for(int ix = 0; ix < vp_widthInTiles+1; ix++)
		{
			int current_frame = 0; //TODO: ADD TIMING
			int map_x = tile_offset_x + ix;
			int map_y = tile_offset_y + iy;

			if(map_x < 0 || map_x >= project->stages[selected_stage].layers[layer].layer_map.tile_map.num_tiles_across ||
			   map_y < 0 || map_y >= project->stages[selected_stage].layers[layer].layer_map.tile_map.num_tiles_down)
				continue;

			int tile = project->stages[selected_stage].layers[layer].layer_map.tile_map.rows[map_y].tile[map_x];

			if(tile < 0 || tile >= num_tiles_in_tset)
				continue;

			//std::cout << "Tile = " << tile << " < " << project->tileset[ tset ].object.tiles.size() << std::endl;

			current_frame = project->tileset[ tset ].object.tiles[tile].current_frame;
			tile = project->tileset[ tset ].object.tiles[tile].frames[current_frame];

			if(tile < 0 || tile >= num_tiles_in_tset)
				continue;

			int src_x = 0;
			int src_y = 0;
			util_getTileInTileset(tset, tile, &src_x, &src_y);
			//std::cout << "DEBUG TMAP: " << tile << " -> " << src_x << ", " << src_y << std::endl;
			irr::core::rect<irr::s32> sourceRect( irr::core::vector2d<irr::s32>(src_x, src_y), irr::core::dimension2d<irr::s32>(src_w, src_h));

			irr::video::SColor color(image[tset_img_id].alpha,
									image[tset_img_id].color_mod.getRed(),
									image[tset_img_id].color_mod.getGreen(),
									image[tset_img_id].color_mod.getBlue());

			int dst_x = screen_offset_x + (ix*src_w);
			int dst_y = screen_offset_y + (iy*src_h);
			irr::core::rect<irr::s32> dest( irr::core::vector2d<irr::s32>(dst_x, dst_y), irr::core::dimension2d<irr::s32>(src_w, src_h));


			m_pDriver->draw2DImage(image[tset_img_id].image, dest, sourceRect, 0, 0, true);
		}
	}

	m_pDriver->setRenderTarget(canvas[ref_canvas].texture, false, false);

	irr::core::rect<irr::s32> sourceRect( irr::core::vector2d<irr::s32>(0, 0), irr::core::dimension2d<irr::s32>(w, h));
	irr::core::rect<irr::s32> dest( irr::core::vector2d<irr::s32>(x, y), irr::core::dimension2d<irr::s32>(w, h));

	m_pDriver->draw2DImage(project->stages[selected_stage].layers[layer].layer_map.tile_map.texture, dest, sourceRect, 0, 0, false);
	m_pDriver->removeTexture(project->stages[selected_stage].layers[layer].layer_map.tile_map.texture);
	project->stages[selected_stage].layers[layer].layer_map.tile_map.texture = NULL;
	//draw2DImage(VideoDriver, rc_tilemap[tilemap].texture, src, pos,)
}



void wxIrrlicht::initStage(int stage_index)
{
	if(!project)
		return;

	if(stage_index < 0 || stage_index >= project->stages.size())
		return;

	mapEdit_getContext();

	//Unload all textures and delete associated canvases
	if(selected_stage >= 0 && selected_stage < project->stages.size())
	{
		for(int layer_index = 0; layer_index < project->stages[selected_stage].layers.size(); layer_index++)
		{
			canvasClose(project->stages[selected_stage].layers[layer_index].ref_canvas);
			project->stages[selected_stage].layers[layer_index].ref_canvas = -1;

			int tset = project->stages[selected_stage].layers[layer_index].layer_map.nv_tileset_index;

			if(tset >= 0 && tset < project->tileset.size())
			{
				deleteImage( project->tileset[ tset ].object.img_id );
				project->tileset[ tset ].object.img_id = -1;
			}
		}
	}

	selected_stage = stage_index;

	//wxFileName gfx_path(project->getDir());
	//gfx_path.AppendDir(_("gfx"));

	//Load new stage stuff
	for(int layer_index = 0; layer_index < project->stages[stage_index].layers.size(); layer_index++)
	{
		initLayer(layer_index);
	}
}

void wxIrrlicht::initLayer(int layer_index)
{
	if(!project)
		return;

	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	if(layer_index < 0 || layer_index >= project->stages[selected_stage].layers.size())
		return;

	mapEdit_getContext();


	wxFileName gfx_path(project->getDir());

	//std::cout << "P_TEST: " << layer_index << ", " << project->getLayerType(selected_stage, layer_index) << ", " << project->tile_path << std::endl;

	if(project)
		gfx_path.AppendDir(project->tile_path);
	else
		gfx_path.AppendDir(_("gfx"));

	if(project->getLayerType(selected_stage, layer_index) == LAYER_TYPE_TILEMAP)
	{
		int screen_width = m_pDevice->getVideoDriver()->getScreenSize().Width;
		int screen_height = m_pDevice->getVideoDriver()->getScreenSize().Height;
		int w = this->GetClientSize().GetWidth();
		int h = this->GetClientSize().GetHeight();

		project->stages[selected_stage].layers[layer_index].ref_canvas = createCanvas(screen_width, screen_height, 0, 0, w, h, CANVAS_TYPE_2D);

		project->stages[selected_stage].layers[layer_index].layer_map.nv_tileset_index = project->getTilesetIndex(project->stages[selected_stage].layers[layer_index].layer_map.nv_tileset_name);
		int tset = project->stages[selected_stage].layers[layer_index].layer_map.nv_tileset_index;
		if(tset < 0 || tset >= project->tileset.size())
		{
			//std::cout << "TSET: " << tset << ", " << project->stages[selected_stage].layers[layer_index].layer_name << std::endl;
			wxMessageBox(_("ERROR: Failed to load tileset [") + wxString(project->stages[selected_stage].layers[layer_index].layer_map.nv_tileset_name));
		}
		else
		{
			//std::cout << "dbg tileset: " << project->stages[selected_stage].layers[layer_index].layer_map.nv_tileset_name << " -> " << tset << std::endl;
			wxFileName img_path = gfx_path;
			img_path.SetFullName(project->tileset[tset].file);

			project->tileset[ tset ].object.img_id = util_getImageID(img_path.GetAbsolutePath().ToStdString());

			if(!imageExists(project->tileset[ tset ].object.img_id))
				project->tileset[ tset ].object.img_id = loadImage(img_path.GetAbsolutePath().ToStdString());
		}
	}
	else if(project->getLayerType(selected_stage, layer_index) == LAYER_TYPE_SPRITE)
	{
		int screen_width = m_pDevice->getVideoDriver()->getScreenSize().Width;
		int screen_height = m_pDevice->getVideoDriver()->getScreenSize().Height;
		int w = this->GetClientSize().GetWidth();
		int h = this->GetClientSize().GetHeight();

		project->stages[selected_stage].layers[layer_index].ref_canvas = createCanvas(screen_width, screen_height, 0, 0, w, h, CANVAS_TYPE_SPRITE);

		for(int spr_index = 0; spr_index < project->stages[selected_stage].layers[layer_index].layer_sprites.size(); spr_index++)
		{
			//std::cout << "add sprite: " << project->stages[selected_stage].layers[layer_index].layer_sprites[spr_index].map_sprite_id << std::endl;
			addLayerSprite(layer_index, spr_index);
		}
	}
	else if(project->getLayerType(selected_stage, layer_index) == LAYER_TYPE_CANVAS_2D)
	{
		int screen_width = m_pDevice->getVideoDriver()->getScreenSize().Width;
		int screen_height = m_pDevice->getVideoDriver()->getScreenSize().Height;
		int w = this->GetClientSize().GetWidth();
		int h = this->GetClientSize().GetHeight();

		project->stages[selected_stage].layers[layer_index].ref_canvas = createCanvas(screen_width, screen_height, 0, 0, w, h, CANVAS_TYPE_2D);

		wxFileName fname(project->getDir());
		fname.AppendDir(_("bkg"));
		fname.SetFullName(wxString(project->stages[selected_stage].layers[layer_index].bkg.img_file).Trim());

		if(fname.Exists() && wxString(project->stages[selected_stage].layers[layer_index].bkg.img_file).Trim().length()!=0)
		{
			if(!imageExists(project->stages[selected_stage].layers[layer_index].bkg.image_id))
			{
				project->stages[selected_stage].layers[layer_index].bkg.image_id = util_getImageID(fname.GetAbsolutePath().ToStdString());

				if(!imageExists(project->stages[selected_stage].layers[layer_index].bkg.image_id))
					project->stages[selected_stage].layers[layer_index].bkg.image_id = loadImage(fname.GetAbsolutePath().ToStdString());
			}
		}

		int canvas_id = project->stages[selected_stage].layers[layer_index].ref_canvas;
		canvas[canvas_id].bkg_render_image_id = -1;
		if(canvas_id >= 0 && canvas_id < canvas.size())
		{
			canvas[canvas_id].bkg_render_image_id = project->stages[selected_stage].layers[layer_index].bkg.image_id;
			canvas[canvas_id].bkg_render_type = project->stages[selected_stage].layers[layer_index].bkg.render_setting;
		}
	}

	int canvas_id = project->stages[selected_stage].layers[layer_index].ref_canvas;
	if(canvas_id >= 0 && canvas_id < canvas.size())
	{
		canvas[canvas_id].layer_index = layer_index;
		canvas[canvas_id].visible = project->stages[selected_stage].layers[layer_index].visible;
	}
}

void wxIrrlicht::resizeLayers()
{
	if(!project)
		return;

	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	mapEdit_getContext();

	for(int layer_index = 0; layer_index < project->stages[selected_stage].layers.size(); layer_index++)
	{
		if(project->stages[selected_stage].layers[layer_index].ref_canvas >= 0 && project->stages[selected_stage].layers[layer_index].ref_canvas < canvas.size())
		{
			int canvas_id = project->stages[selected_stage].layers[layer_index].ref_canvas;
			canvas[canvas_id].bkg_render_image_id = -1;
			canvas[canvas_id].bkg_render_type = -1;
		}

		if(project->getLayerType(selected_stage, layer_index) == LAYER_TYPE_TILEMAP || project->getLayerType(selected_stage, layer_index) == LAYER_TYPE_CANVAS_2D)
		{
			int screen_width = parent_window->GetClientSize().GetX();
			int screen_height = parent_window->GetClientSize().GetY();
			int w = this->GetClientSize().GetWidth();
			int h = this->GetClientSize().GetHeight();

			canvasClose(project->stages[selected_stage].layers[layer_index].ref_canvas);
			project->stages[selected_stage].layers[layer_index].ref_canvas = -1;

			bool ref_is_active = (project->stages[selected_stage].layers[layer_index].ref_canvas == active_canvas);

			project->stages[selected_stage].layers[layer_index].ref_canvas = createCanvas(screen_width, screen_height, 0, 0, w, h, CANVAS_TYPE_2D);


			int canvas_id = project->stages[selected_stage].layers[layer_index].ref_canvas;

			if(canvas_id >= 0 && canvas_id < canvas.size())
				canvas[canvas_id].visible = project->stages[selected_stage].layers[layer_index].visible;

			if(project->getLayerType(selected_stage, layer_index) == LAYER_TYPE_TILEMAP)
			{
				project->stages[selected_stage].layers[layer_index].layer_map.nv_tileset_index = project->getTilesetIndex(project->stages[selected_stage].layers[layer_index].layer_map.nv_tileset_name);
				int tset = project->stages[selected_stage].layers[layer_index].layer_map.nv_tileset_index;
				if(tset < 0 || tset >= project->tileset.size())
				{
					//std::cout << "TSET: " << tset << ", " << project->stages[selected_stage].layers[layer_index].layer_name << std::endl;
					wxMessageBox(_("ERROR: Failed to load tileset [") + wxString(project->stages[selected_stage].layers[layer_index].layer_map.nv_tileset_name));
				}
				else
				{
					wxFileName gfx_path(project->getDir());

					if(project)
						gfx_path.AppendDir(project->tile_path);
					else
						gfx_path.AppendDir(_("gfx"));

					wxFileName img_path = gfx_path;
					img_path.SetFullName(project->tileset[tset].file);

					project->tileset[ tset ].object.img_id = util_getImageID(img_path.GetAbsolutePath().ToStdString());

					if(!imageExists(project->tileset[ tset ].object.img_id))
						project->tileset[ tset ].object.img_id = loadImage(img_path.GetAbsolutePath().ToStdString());
				}
			}
			else
			{
				project->stages[selected_stage].layers[layer_index].bkg.image_id = util_getImageID(project->stages[selected_stage].layers[layer_index].bkg.img_file);
				canvas[canvas_id].bkg_render_type = project->stages[selected_stage].layers[layer_index].bkg.render_setting;
				canvas[canvas_id].bkg_render_image_id = project->stages[selected_stage].layers[layer_index].bkg.image_id;
				canvas[canvas_id].layer_index = layer_index;
			}

			//std::cout << "Resize: " << project->stages[selected_stage].layers[layer_index].ref_canvas << " -> " << (canvas[project->stages[selected_stage].layers[layer_index].ref_canvas].texture == NULL ? "NULL" : "active") << std::endl;
		}
		else if(project->getLayerType(selected_stage, layer_index) == LAYER_TYPE_SPRITE)
		{
			int screen_width = parent_window->GetClientSize().GetX();
			int screen_height = parent_window->GetClientSize().GetY();
			int w = this->GetClientSize().GetWidth();
			int h = this->GetClientSize().GetHeight();

			canvasClose(project->stages[selected_stage].layers[layer_index].ref_canvas);
			project->stages[selected_stage].layers[layer_index].ref_canvas = -1;

			bool ref_is_active = (project->stages[selected_stage].layers[layer_index].ref_canvas == active_canvas);

			project->stages[selected_stage].layers[layer_index].ref_canvas = createCanvas(screen_width, screen_height, 0, 0, w, h, CANVAS_TYPE_SPRITE);

			int canvas_id = project->stages[selected_stage].layers[layer_index].ref_canvas;

			if(canvas_id >= 0 && canvas_id < canvas.size())
				canvas[canvas_id].visible = project->stages[selected_stage].layers[layer_index].visible;

			for(int spr_index = 0; spr_index < project->stages[selected_stage].layers[layer_index].layer_sprites.size(); spr_index++)
			{
				//std::cout << "add sprite: " << project->stages[selected_stage].layers[layer_index].layer_sprites[spr_index].map_sprite_id << std::endl;
				addLayerSprite(layer_index, spr_index);
			}
		}
	}
}

void wxIrrlicht::clearStage()
{
	mapEdit_selectTileTool_selection.clear();
	mapEdit_selectSpriteTool_selection.clear();


	//Unload all textures and delete associated canvases
	for(int i = 0; i < image.size(); i++)
		deleteImage(i);

	for(int i = 0; i < sprite.size(); i++)
	{
		deleteSprite(i);
	}


	if(!project)
		return;

	for(int i = 0; i < project->sprite_base.size(); i++)
	{
		project->sprite_base[i].object.image_id = -1;
	}

	for(int i = 0; i < project->tileset.size(); i++)
	{
		project->tileset[i].object.img_id = -1;
	}



	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	mapEdit_getContext();

	//Load new stage stuff
	for(int layer_index = 0; layer_index < project->stages[selected_stage].layers.size(); layer_index++)
	{
		if(project->stages[selected_stage].layers[layer_index].ref_canvas >= 0 && project->stages[selected_stage].layers[layer_index].ref_canvas < canvas.size())
		{
			int canvas_id = project->stages[selected_stage].layers[layer_index].ref_canvas;
			canvas[canvas_id].bkg_render_image_id = -1;
			canvas[canvas_id].bkg_render_type = -1;
		}
		canvasClose(project->stages[selected_stage].layers[layer_index].ref_canvas);
		project->stages[selected_stage].layers[layer_index].ref_canvas = -1;

		for(int spr_index = 0; spr_index < project->stages[selected_stage].layers[layer_index].layer_sprites.size(); spr_index++)
		{
			project->stages[selected_stage].layers[layer_index].layer_sprites[spr_index].map_sprite_id = -1;
		}

		project->stages[selected_stage].layers[layer_index].bkg.image_id = -1;
	}

	selected_stage = -1;
	selected_layer = -1;
	mapEdit_layerType = -1;
}

int wxIrrlicht::util_getImageID(std::string img_file) //checks to see if file has already been loaded
{
	wxString test_img_file = wxString(img_file).Trim();

	for(int i = 0; i < project->getTilesetCount(); i++)
	{
		if(project->tileset[i].file.Trim().compare(test_img_file)==0)
		{
			if(imageExists(project->tileset[i].object.img_id))
				return project->tileset[i].object.img_id;
		}
	}

	for(int i = 0; i < project->getSpriteCount(); i++)
	{
		if(project->sprite_base[i].file.Trim().compare(test_img_file)==0)
		{
			if(imageExists(project->sprite_base[i].object.image_id))
				return project->sprite_base[i].object.image_id;
		}
	}

	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return -1;

	for(int i = 0; i < project->stages[selected_stage].layers.size(); i++)
	{
		if(wxString(project->stages[selected_stage].layers[i].bkg.img_file).Trim().compare(test_img_file)==0)
		{
			if(imageExists(project->stages[selected_stage].layers[i].bkg.image_id))
				return project->stages[selected_stage].layers[i].bkg.image_id;
		}
	}

	return -1;
}

void wxIrrlicht::addLayerSprite(int layer_index, int project_sprite)
{
	if(!project)
		return;

	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	if(layer_index < 0 || layer_index >= project->stages[selected_stage].layers.size())
		return;

	if(project->getLayerType(selected_stage, layer_index) != LAYER_TYPE_SPRITE)
		return;

	if(project_sprite < 0 || project_sprite >= project->stages[selected_stage].layers[layer_index].layer_sprites.size())
		return;

	int base_index = project->stages[selected_stage].layers[layer_index].layer_sprites[project_sprite].sprite_base;

	if(base_index < 0 || base_index >= project->sprite_base.size())
		return;

	mapEdit_getContext();
	setActiveCanvas(project->stages[selected_stage].layers[layer_index].ref_canvas);

	int img_id = project->sprite_base[base_index].object.image_id;

	if(img_id < 0)
	{
		wxFileName img_path(project->getDir());

		if(project)
			img_path.AppendDir(project->sprite_path);
		else
			img_path.AppendDir(_("gfx"));

		img_path.SetFullName(project->sprite_base[base_index].file);

		//std::cout << "Load: " << base_index << " :: " << img_path.GetAbsolutePath().ToStdString() << std::endl;

		img_id = util_getImageID(img_path.GetAbsolutePath().ToStdString());

		if(img_id < 0)
			project->sprite_base[base_index].object.image_id = loadImage(img_path.GetAbsolutePath().ToStdString());
		else
			project->sprite_base[base_index].object.image_id = img_id;

		img_id = project->sprite_base[base_index].object.image_id;

		if(img_id < 0)
			return;
	}

	int w = project->sprite_base[base_index].object.frame_size.Width;
	int h = project->sprite_base[base_index].object.frame_size.Height;

	project->stages[selected_stage].layers[layer_index].layer_sprites[project_sprite].map_sprite_id = createSprite(project_sprite, img_id, w, h);
	int spr_id = project->stages[selected_stage].layers[layer_index].layer_sprites[project_sprite].map_sprite_id;

	int x = project->stages[selected_stage].layers[layer_index].layer_sprites[project_sprite].position.X;
	int y = project->stages[selected_stage].layers[layer_index].layer_sprites[project_sprite].position.Y;

	double angle = project->stages[selected_stage].layers[layer_index].layer_sprites[project_sprite].angle;

	double scale_x = project->stages[selected_stage].layers[layer_index].layer_sprites[project_sprite].scale.X;
	double scale_y = project->stages[selected_stage].layers[layer_index].layer_sprites[project_sprite].scale.Y;

	int alpha = project->stages[selected_stage].layers[layer_index].layer_sprites[project_sprite].alpha;
	bool visible = project->stages[selected_stage].layers[layer_index].layer_sprites[project_sprite].visible;

	setSpritePosition(spr_id, x, y);
	setSpriteScale(spr_id, scale_x, scale_y);
	setSpriteRotation(spr_id, angle);
	setSpriteAlpha(spr_id, alpha);
	setSpriteVisible(spr_id, visible);
	sprite[spr_id].layer_sprite_unique_id = project->stages[selected_stage].layers[layer_index].layer_sprites[project_sprite].layer_sprite_unique_id;

	if(spr_id < 0)
		return;

	// NOTE: Starting at 1 since createSprite() will automatically create BASE_ANIMATION
	for(int i = 1; i < project->sprite_base[base_index].object.animation.size(); i++)
	{
		createSpriteAnimation(project->sprite_base[base_index].object.animation[i].name,
							  spr_id,
							  project->getSpriteNumAnimationFrames(base_index, i),
							  project->getSpriteAnimationFPS(base_index, i));
		for(int frame = 0; frame < project->getSpriteNumAnimationFrames(base_index, i); frame++)
		{
			setSpriteAnimationFrame(spr_id, i, frame, project->getSpriteAnimationFrame(base_index, i, frame));
		}
	}

	wxString current_animation_name = wxString(project->stages[selected_stage].layers[layer_index].layer_sprites[project_sprite].animation_name).Upper().Trim();

	for(int i = 0; i < sprite[spr_id].animation.size(); i++)
	{
		if(wxString(sprite[spr_id].animation[i].name).Upper().Trim().compare(current_animation_name)==0)
		{
			setSpriteAnimation(spr_id, i, -1);
			break;
		}
	}
}
