#ifndef RC_GFX_INCLUDED
#define RC_GFX_INCLUDED

#include <irrlicht.h>

#include <iostream>
#include <sstream>
#include <string>
#include <locale>
#include <codecvt>
#include <cmath>
#include <set>
#include "rc_gfx_core.h"
#include "gui_freetype_font.h"
#include "rc_utf8.h"
#include "rc_sprite2D.h"
#include "rc_spritelib.h"
#include "rc_tilelib.h"

using namespace irr;

using namespace core;
using namespace video;
using namespace scene;



//The greater Z is, the further back the canvas is
void sortCanvasZ()
{
    for(int i = 0; i < rc_canvas_zOrder.size(); i++)
    {
        for(int j = i+1; j < rc_canvas_zOrder.size(); j++)
        {
            int ca = rc_canvas_zOrder[i];
            int cb = rc_canvas_zOrder[j];
            if(rc_canvas[cb].z >= rc_canvas[ca].z)
            {
                rc_canvas_zOrder.erase(j);
                rc_canvas_zOrder.insert(cb, i);
            }
        }
    }

    //for(int i = 0; i < rc_canvas_zOrder.size(); i++)
    //{
    //    std::cout << "Canvas[" << i << "] Z = " << rc_canvas_zOrder[i] << ( (i+1)==rc_canvas_zOrder.size() ? "" : ", " );
    //}
    //std::cout << std::endl;
}

void rc_setActiveCanvas(int canvas_id)
{
    rc_active_canvas = canvas_id;

    if(rc_active_canvas >= 0 && rc_active_canvas < rc_canvas.size())
    {
        if(rc_canvas[rc_active_canvas].texture)
            VideoDriver->setRenderTarget(rc_canvas[rc_active_canvas].texture, false, false);

		rc_setDriverMaterial();
    }
}

int rc_activeCanvas()
{
    return rc_active_canvas;
}

int rc_canvasOpen(int w, int h, int vx, int vy, int vw, int vh, int mode, int canvas_type=RC_CANVAS_TYPE_2D)
{
    if(!VideoDriver)
        return -1;

    rc_canvas_obj canvas;
    canvas.type = canvas_type;
    canvas.show3D = false;
    canvas.physics2D.enabled = false;

    #ifdef RC_DRIVER_GLES2
    Uint32 size_n = 2;
    Uint32 dim_max = (w > h ? w : h);
    while(size_n < dim_max) size_n *= 2;
    //w = size_n;
    //h = size_n;
    canvas.texture = VideoDriver->addRenderTargetTexture(irr::core::dimension2d<u32>(size_n,size_n), "rt", ECF_A8R8G8B8);
    #else
    canvas.texture = VideoDriver->addRenderTargetTexture(irr::core::dimension2d<u32>(w,h), "rt", ECF_A8R8G8B8);
    #endif // RC_WEB
    //canvas.sprite_layer = VideoDriver->addRenderTargetTexture(irr::core::dimension2d<u32>(w,h), "rt", ECF_A8R8G8B8);

    if(!canvas.texture)
        return -1;


    if(SceneManager && canvas_type==RC_CANVAS_TYPE_3D)
    {
    	canvas.show3D = true;
        canvas.camera.init(SceneManager, 0, 0, 0);
        //canvas.camera = SceneManager->addCameraSceneNode(0, vector3df(0,0,0), vector3df(0,0,0));
        //canvas.camera->setPosition(irr::core::vector3df(0,0,0));
        //canvas.camera->setTarget(irr::core::vector3df(0,0,100));
        //canvas.camera->bindTargetAndRotation(true);
    }
    else if(!SceneManager)
		return -1;

    //std::cout << "texture format = " << canvas.texture->getColorFormat() << std::endl;

    canvas.dimension.Width = w;
    canvas.dimension.Height = h;

    #ifdef RC_DRIVER_GLES2
    if(canvas_type==RC_CANVAS_TYPE_2D)
    {
    	canvas.dimension.Width = size_n;
		canvas.dimension.Height = size_n;
    }
    #endif // RC_DRIVER_GLES2

    canvas.viewport.position.X = vx;
    canvas.viewport.position.Y = vy;
    canvas.viewport.dimension.Width = vw;
    canvas.viewport.dimension.Height = vh;

    canvas.offset.X = 0;
    canvas.offset.Y = 0;

    canvas.mode = mode;

    canvas.color_mod = irr::video::SColor(255,255,255,255).color;

    //2D Physics World
    canvas.physics2D.world = NULL;
    if(canvas_type == RC_CANVAS_TYPE_SPRITE)
    {
    	b2Vec2 gravity(0, 0);
		canvas.physics2D.world = new b2World(gravity);
		canvas.physics2D.timeStep = -1;      //the length of time passed to simulate (seconds)
		canvas.physics2D.time_stamp = SDL_GetTicks();
		canvas.physics2D.velocityIterations = 8;   //how strongly to correct velocity
		canvas.physics2D.positionIterations = 3;   //how strongly to correct position
		canvas.physics2D.enabled = true;
		canvas.physics2D.contact_listener = new rc_contactListener_obj();
		canvas.physics2D.world->SetContactListener(canvas.physics2D.contact_listener);
		canvas.sprite_id.clear();
    }

    switch(mode)
    {
        case 0:
            break;
        case 1:
            VideoDriver->makeColorKeyTexture(canvas.texture, irr::video::SColor(0,0,0,0));
            break;
    }

    int canvas_id = -1;

    for(int i = 0; i < rc_canvas.size(); i++)
    {
        if(!rc_canvas[i].texture)
        {
            canvas_id = i;
            break;
        }
    }

    if(canvas_id < 0)
    {
        canvas_id = rc_canvas.size();
        rc_canvas.push_back(canvas);
    }

    if(rc_active_canvas < 0)
	{
		rc_active_canvas = canvas_id;
		rc_setActiveCanvas(rc_active_canvas);
	}

    for(int i = 0; i < rc_canvas_zOrder.size(); i++)
    {
        if(rc_canvas_zOrder[i] == canvas_id)
        {
            rc_canvas_zOrder.erase(i);
            i--;
        }
    }

    rc_canvas_zOrder.push_back(canvas_id);

    sortCanvasZ();


    return canvas_id;
}


void rc_canvasClose(int canvas_id)
{
    if(canvas_id <= 0 || canvas_id >= rc_canvas.size()) //canvas 0 is being excluded because its the back buffer
        return;

    if(rc_canvas[canvas_id].texture != NULL)
        VideoDriver->removeTexture(rc_canvas[canvas_id].texture);

    rc_canvas[canvas_id].texture = NULL;

    if(rc_canvas[canvas_id].physics2D.world)
		delete rc_canvas[canvas_id].physics2D.world;

	rc_canvas[canvas_id].physics2D.world = NULL;

	for(int i = 0; i < rc_joint.size(); i++)
	{
		if(rc_joint[i].canvas == canvas_id)
		{
			rc_joint[i].canvas = -1;
			rc_joint[i].joint = NULL;
			rc_joint[i].active = false;
		}
	}

	//sprites are destroyed when the world is deleted so I just to set the active attribute to false and set the body to NULL
	for(int i = 0; i < rc_canvas[canvas_id].sprite_id.size(); i++)
	{
		int spr_id = rc_canvas[canvas_id].sprite_id[i];
		rc_sprite[spr_id].active = false;
		rc_sprite[spr_id].physics.body = NULL;
	}

	rc_canvas[canvas_id].sprite_id.clear();

    if(rc_active_canvas == canvas_id)
        rc_active_canvas = -1;

    for(int i = 0; i < rc_canvas_zOrder.size(); i++)
    {
        if(rc_canvas_zOrder[i] == canvas_id)
        {
            rc_canvas_zOrder.erase(i);
            break;
        }
    }
}

void rc_setCanvas3D(int canvas_id, bool flag)
{
    if(canvas_id > 0 && canvas_id < rc_canvas.size())
        rc_canvas[canvas_id].show3D = flag;
}

int rc_canvasOpen3D(int vx, int vy, int vw, int vh, int mode)
{
	return rc_canvasOpen(vw, vh, vx, vy, vw, vh, mode, RC_CANVAS_TYPE_3D);
}

int rc_canvasOpenSpriteLayer(int vx, int vy, int vw, int vh)
{
	//sprite layers are basically infinite since you are just placing objects in the world
	return rc_canvasOpen(vw, vh, vx, vy, vw, vh, 1, RC_CANVAS_TYPE_SPRITE);
}

void rc_setCanvasPhysics2D(int canvas_id, bool flag)
{
	if(canvas_id > 0 && canvas_id < rc_canvas.size())
		rc_canvas[canvas_id].physics2D.enabled = flag;
}

void rc_setCanvasVisible(int canvas_id, bool flag)
{
    if(canvas_id <= 0 || canvas_id >= rc_canvas.size()) //canvas 0 is being excluded because its the back buffer
        return;

    if(rc_canvas[canvas_id].texture)
        rc_canvas[canvas_id].visible = flag;
}

bool rc_canvasIsVisible(int canvas_id)
{
    if(canvas_id <= 0 || canvas_id >= rc_canvas.size()) //canvas 0 is being excluded because its the back buffer
        return false;

    if(rc_canvas[canvas_id].texture)
        return rc_canvas[canvas_id].visible;

    return false;
}

void rc_setCanvasViewport(int canvas_id, int x, int y, int w, int h)
{
    if(canvas_id <= 0 || canvas_id >= rc_canvas.size()) //canvas 0 is being excluded because its the back buffer
        return;

    if(rc_canvas[canvas_id].texture)
    {
        rc_canvas[canvas_id].viewport.position = irr::core::vector2d<irr::s32>(x, y);
        rc_canvas[canvas_id].viewport.dimension = irr::core::dimension2d<irr::u32>(w, h);
    }
}

void rc_getCanvasViewport(int canvas_id, double* x, double* y, double* w, double* h)
{
    if(canvas_id <= 0 || canvas_id >= rc_canvas.size()) //canvas 0 is being excluded because its the back buffer
        return;

    if(rc_canvas[canvas_id].texture)
    {
        *x = (double)rc_canvas[canvas_id].viewport.position.X;
        *y = (double)rc_canvas[canvas_id].viewport.position.Y;
        *w = rc_canvas[canvas_id].viewport.dimension.Width;
        *h = rc_canvas[canvas_id].viewport.dimension.Height;
    }
}

void rc_setCanvasOffset(int canvas_id, int x, int y)
{
    if(canvas_id <= 0 || canvas_id >= rc_canvas.size()) //canvas 0 is being excluded because its the back buffer
        return;

    if(rc_canvas[canvas_id].texture)
    {
        rc_canvas[canvas_id].offset = irr::core::vector2d<irr::s32>(x, y);
    }
}

void rc_getCanvasOffset(int canvas_id, double* x, double* y)
{
    if(canvas_id <= 0 || canvas_id >= rc_canvas.size()) //canvas 0 is being excluded because its the back buffer
        return;

    if(rc_canvas[canvas_id].texture)
    {
        *x = (double)rc_canvas[canvas_id].offset.X;
        *y = (double)rc_canvas[canvas_id].offset.Y;
    }
}

void rc_getCanvasSize(int canvas_id, double* w, double* h)
{
    if(canvas_id <= 0 || canvas_id >= rc_canvas.size()) //canvas 0 is being excluded because its the back buffer
        return;

    if(rc_canvas[canvas_id].texture)
    {
        *w = (double)rc_canvas[canvas_id].dimension.Width;
        *h = (double)rc_canvas[canvas_id].dimension.Height;
    }
}

void rc_setCanvasColorMod(int canvas_id, Uint32 color_mod)
{
    if(canvas_id <= 0 || canvas_id >= rc_canvas.size()) //canvas 0 is being excluded because its the back buffer
        return;

    if(rc_canvas[canvas_id].texture)
    {
        rc_canvas[canvas_id].color_mod = color_mod;
    }
}

Uint32 rc_getCanvasColorMod(int canvas_id)
{
    if(canvas_id <= 0 || canvas_id >= rc_canvas.size()) //canvas 0 is being excluded because its the back buffer
        return 0;

    if(rc_canvas[canvas_id].texture)
    {
        return rc_canvas[canvas_id].color_mod;
    }

    return 0;
}

void rc_setCanvasAlpha(int canvas_id, Uint32 alpha)
{
    if(canvas_id <= 0 || canvas_id >= rc_canvas.size()) //canvas 0 is being excluded because its the back buffer
        return;

    if(rc_canvas[canvas_id].texture)
    {
        irr::video::SColor color(rc_canvas[canvas_id].color_mod);
        color.setAlpha(alpha);
        rc_canvas[canvas_id].color_mod = color.color;
    }
}

Uint32 rc_canvasAlpha(int canvas_id)
{
    if(canvas_id <= 0 || canvas_id >= rc_canvas.size()) //canvas 0 is being excluded because its the back buffer
        return 0;

    if(rc_canvas[canvas_id].texture)
    {
        irr::video::SColor color(rc_canvas[canvas_id].color_mod);
        Uint32 alpha = color.getAlpha();
        return alpha;
    }
    return 0;
}

void rc_setCanvasZ(int canvas_id, int z)
{
    if(canvas_id <= 0 || canvas_id >= rc_canvas.size()) //canvas 0 is being excluded because its the back buffer
        return;

    rc_canvas[canvas_id].z = z;
    sortCanvasZ();
}

int rc_getCanvasZ(int canvas_id)
{
    if(canvas_id <= 0 || canvas_id >= rc_canvas.size()) //canvas 0 is being excluded because its the back buffer
        return 0;

    if(rc_canvas[canvas_id].texture)
    {
        return rc_canvas[canvas_id].z;
    }

    return 0;
}

int rc_cloneCanvas(int origin_canvas_id, int mode)
{
	if(!VideoDriver)
        return -1;

	if(origin_canvas_id < 0 || origin_canvas_id >= rc_canvas.size())
		return -1;

	if(!rc_canvas[origin_canvas_id].texture)
		return -1;

    rc_canvas_obj canvas;
    canvas.type = rc_canvas[origin_canvas_id].type;
    canvas.physics2D.enabled = false; //There is no need for this to process its own physics since its done on the origin
    canvas.show3D = rc_canvas[origin_canvas_id].show3D;
    canvas.color_mod = rc_canvas[origin_canvas_id].color_mod;
    canvas.texture = rc_canvas[origin_canvas_id].texture;
    //canvas.sprite_layer = rc_canvas[origin_canvas_id].sprite_layer;

    if(!canvas.texture)
        return -1;


    if(SceneManager)
    {
        canvas.camera.init(SceneManager, 0, 0, 0);
        //canvas.camera = SceneManager->addCameraSceneNode(0, vector3df(0,0,0), vector3df(0,0,0));
        //canvas.camera->setPosition(irr::core::vector3df(0,0,0));
        //canvas.camera->setTarget(irr::core::vector3df(0,0,100));
        //canvas.camera->bindTargetAndRotation(true);
    }

    //std::cout << "texture format = " << canvas.texture->getColorFormat() << std::endl;

    canvas.dimension.Width = rc_canvas[origin_canvas_id].dimension.Width;
    canvas.dimension.Height = rc_canvas[origin_canvas_id].dimension.Height;

    canvas.viewport.position.X = rc_canvas[origin_canvas_id].viewport.position.X;
    canvas.viewport.position.Y = rc_canvas[origin_canvas_id].viewport.position.Y;
    canvas.viewport.dimension.Width = rc_canvas[origin_canvas_id].viewport.dimension.Width;
    canvas.viewport.dimension.Height = rc_canvas[origin_canvas_id].viewport.dimension.Height;

    canvas.offset.X = 0;
    canvas.offset.Y = 0;

    canvas.mode = mode;

    canvas.color_mod = irr::video::SColor(255,255,255,255).color;


    switch(mode)
    {
        case 0:
            break;
        case 1:
            VideoDriver->makeColorKeyTexture(canvas.texture, irr::video::SColor(0,0,0,0));
            break;
    }

    int canvas_id = -1;

    for(int i = 0; i < rc_canvas.size(); i++)
    {
        if(!rc_canvas[i].texture)
        {
            canvas_id = i;
            break;
        }
    }

    if(canvas_id < 0)
    {
        canvas_id = rc_canvas.size();
        rc_canvas.push_back(canvas);
    }

    if(rc_active_canvas < 0)
        rc_active_canvas = canvas_id;

    for(int i = 0; i < rc_canvas_zOrder.size(); i++)
    {
        if(rc_canvas_zOrder[i] == canvas_id)
        {
            rc_canvas_zOrder.erase(i);
            i--;
        }
    }

    rc_canvas_zOrder.push_back(canvas_id);

    sortCanvasZ();


    return canvas_id;
}

void rc_getWorldToViewportPosition(double x, double y, double z, double* vx, double* vy)
{
	if(!VideoDriver)
        return;

	if(rc_active_canvas < 0 || rc_active_canvas >= rc_canvas.size())
		return;

	if(!rc_canvas[rc_active_canvas].texture)
		return;

	if(!rc_canvas[rc_active_canvas].camera.camera)
		return;

	irr::scene::ISceneCollisionManager* collman = SceneManager->getSceneCollisionManager();

	irr::core::vector2di vpos = collman->getScreenCoordinatesFrom3DPosition(irr::core::vector3df(x, y, z), rc_canvas[rc_active_canvas].camera.camera);
	*vx = vpos.X;
	*vy = vpos.Y;
}


void rc_setClearColor(Uint32 color)
{
    rc_clear_color.set(color);
}

Uint32 rc_rgba(Uint32 r, Uint32 g, Uint32 b, Uint32 a)
{
    irr::video::SColor color(a, r, g, b);
    return color.color;
}

Uint32 rc_rgb(Uint32 r, Uint32 g, Uint32 b)
{
    irr::video::SColor color(255, r, g, b);
    return color.color;
}


void rc_setColor(Uint32 color)
{
    rc_active_color.set(color);
}

Uint32 rc_getPixel(int x, int y)
{
	if(rc_active_canvas < 0 || rc_active_canvas >= rc_canvas.size())
		return 0;

    if(!rc_canvas[rc_active_canvas].texture)
    {
        return 0;
    }

    if(x < 0 || x >= rc_window_size.Width)
        x = 0;

    if(y < 0 || y >= rc_window_size.Height)
        y = 0;

	#ifdef RC_DRIVER_GLES2
	y = rc_canvas[rc_active_canvas].texture->getSize().Height - (y+1);
	#endif // RC_DRIVER_GLES2


    irr::video::ITexture* texture = rc_canvas[rc_active_canvas].texture;

    video::ECOLOR_FORMAT format = texture->getColorFormat(); //std::cout << "format = " << (int) format << std::endl;

    Uint32 color = 0;

    //this if statement is unnessesary since right now ECF_A8R8G8B8 is the only color format supported.
    //I am leaving it here since I may want to support more color formats in the future
    if(video::ECF_A8R8G8B8 == format)
    {
        u8 * texels = (u8 *)texture->lock(irr::video::ETLM_READ_ONLY);

        u32 pitch = texture->getPitch();

        irr::video::SColor * texel = (SColor *)(texels + ((y * pitch) + (x * sizeof(SColor))));

        irr::video::SColor c = texel[0];

        texture->unlock();

        color = c.color;

        //std::cout << "color(" << x << ", " << y << ") = " << c.getRed() << ", " << c.getGreen() << ", " << c.getBlue() << std::endl;
    }

    return color;

}

void rc_drawRect(int x, int y, int w, int h)
{
	// x and y seems to be offset by -1 in the GLES driver for this function. I will remove this once I fix it in the GLES driver but this works for now.
	#ifdef RC_DRIVER_GLES2
	x++;
	y++;
	#endif // RC_DRIVER_GLES2
    irr::core::vector2d<s32> r_pos(x,y);
    irr::core::dimension2d<s32> r_dim(w,h);
    irr::core::rect<s32> r(r_pos, r_dim);
    //std::cout << "drawRect: color=" << rc_active_color.color << " ( " << x << ", " << y << ", " << w << ", " << h << " ) " << std::endl;
    VideoDriver->draw2DRectangleOutline(r, rc_active_color);
}

void rc_drawRectFill(int x, int y, int w, int h)
{
    irr::core::vector2d<s32> r_pos(x,y);
    irr::core::dimension2d<s32> r_dim(w,h);
    irr::core::rect<s32> r(r_pos, r_dim);
    //std::cout << "drawRect: color=" << rc_active_color.color << " ( " << x << ", " << y << ", " << w << ", " << h << " ) " << std::endl;
    VideoDriver->draw2DRectangle(rc_active_color, r);
}



//Filled Circle Code from CuteAlien on Irrlicht forum
struct CircleSettings
{
    vector2di center;       // in screen coordinates
    f32 radius;             // in pixels
    f32 radius2;
    video::SColor color;
    u32 numVertices = 21;   // including center
};

void makeCircle(irr::core::array<irr::video::S3DVertex>& vertices, irr::core::array<irr::u16>& indices, const CircleSettings& settings)
{
    const f64 stepSize = 360.0 / (f64)(settings.numVertices-1); // degree angles between vertex points on circle
    indices.set_used(settings.numVertices+1);   // one more as first and last vertex in circle is identical
    for ( u32 i=0; i<settings.numVertices; ++i)
        indices[i] = i;
    indices[settings.numVertices] = 1;

    const vector2df centerf((f32)settings.center.X, (f32)settings.center.Y);
    vertices.set_used(settings.numVertices);
    vertices[0] = video::S3DVertex(centerf.X, centerf.Y, 0.f, 0.f, 1.f, 0.f, settings.color, 0.5f, 0.5f);
    for ( u32 i=0; i < settings.numVertices-1; ++i )
    {
        vector2df offset(0.f, settings.radius);
        offset.rotateBy(i*stepSize);
        vertices[i+1] = video::S3DVertex(centerf.X+offset.X, centerf.Y+offset.Y, 0.f, 0.f, 1.f, 0.f, settings.color, 0.5f, 0.5f);
    }
}


void rc_drawLine(int x1, int y1, int x2, int y2)
{
    irr::core::vector2d<s32> r_pos_start(x1,y1);
    irr::core::vector2d<s32> r_pos_end(x2,y2);

    VideoDriver->draw2DLine(r_pos_start, r_pos_end, rc_active_color);
}

void prim3d_drawLine3D(double x1, double y1, double z1, double x2, double y2, double z2)
{
    irr::core::vector3d<f32> r_pos_start(x1,y1,z1);
    irr::core::vector3d<f32> r_pos_end(x2,y2,z2);

    VideoDriver->draw3DLine(r_pos_start, r_pos_end, rc_active_color);
}

void prim3d_drawBox3D(double x1, double y1, double z1, double x2, double y2, double z2)
{
    irr::core::aabbox3d<f32> bbox(x1, y1, z1, x2, y2, z2);
    VideoDriver->draw3DBox(bbox, rc_active_color);
}

void prim3d_drawTriangle3D(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3)
{
    irr::core::vector3d<f32> v1(x1,y1,z1);
    irr::core::vector3d<f32> v2(x2,y2,z2);
    irr::core::vector3d<f32> v3(x3,y3,z3);

    irr::core::triangle3d<f32> tri(v1, v2, v3);

    VideoDriver->draw3DTriangle(tri, rc_active_color);
}

void rc_drawLine3D(double x1, double y1, double z1, double x2, double y2, double z2)
{
    rc_prim3d_op_obj op;
    op.prim_type = PRIM3D_LINE;
    op.color = rc_active_color;
    op.x[0] = x1;
    op.y[0] = y1;
    op.z[0] = z1;
    op.x[1] = x2;
    op.y[1] = y2;
    op.z[1] = z2;
    rc_prim3d_operation.push_back(op);
}

void rc_drawBox3D(double x1, double y1, double z1, double x2, double y2, double z2)
{
    rc_prim3d_op_obj op;
    op.prim_type = PRIM3D_BOX;
    op.color = rc_active_color;
    op.x[0] = x1;
    op.y[0] = y1;
    op.z[0] = z1;
    op.x[1] = x2;
    op.y[1] = y2;
    op.z[1] = z2;
    rc_prim3d_operation.push_back(op);
}

void rc_drawTriangle3D(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3)
{
    rc_prim3d_op_obj op;
    op.prim_type = PRIM3D_TRIANGLE;
    op.color = rc_active_color;
    op.x[0] = x1;
    op.y[0] = y1;
    op.z[0] = z1;
    op.x[1] = x2;
    op.y[1] = y2;
    op.z[1] = z2;
    op.x[2] = x3;
    op.y[2] = y3;
    op.z[2] = z3;
    rc_prim3d_operation.push_back(op);
}

void rc_drawTriangle(double x1, double y1, double x2, double y2, double x3, double y3)
{
	irr::core::array<irr::video::S3DVertex> v;
    v.push_back(video::S3DVertex(x1, y1, 0.f, 0.f, 1.f, 0.f, rc_active_color, 0.5f, 0.5f));
    v.push_back(video::S3DVertex(x2, y2, 0.f, 0.f, 1.f, 0.f, rc_active_color, 0.5f, 0.5f));
    v.push_back(video::S3DVertex(x3, y3, 0.f, 0.f, 1.f, 0.f, rc_active_color, 0.5f, 0.5f));

    irr::core::array<irr::u16> i;
    i.push_back(0);
    i.push_back(1);
    i.push_back(2);

    v.sort();

    VideoDriver->draw2DVertexPrimitiveList(v.pointer(), 3, i.pointer(), 1);
}

void rc_poly(Uint32 n, double* vx_d, double* vy_d)
{
    if(n <= 0)
        return;

    for(int i = 1; i < n; i++)
    {
        rc_drawLine((int)vx_d[i-1], (int)vy_d[i-1], (int)vx_d[i], (int)vy_d[i]);
    }

    rc_drawLine((int)vx_d[n-1], (int)vy_d[n-1], (int)vx_d[0], (int)vy_d[0]);
}

void rc_drawPixel(int x, int y)
{
    VideoDriver->drawPixel(x, y, rc_active_color);
}


double radians(double degree)
{
    double pi = 3.14159265359;
    return (degree * (pi / 180));
}

void makeEllipse(irr::core::array<irr::video::S3DVertex>& vertices, irr::core::array<irr::u16>& indices, const CircleSettings& settings)
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

void rc_drawEllipse(int x, int y, int rx, int ry)
{
    irr::core::vector2d<s32> r_pos(x,y);

    // create the circle
    irr::core::array<irr::video::S3DVertex> verticesCircle;
    irr::core::array<irr::u16> indicesCircle;
    CircleSettings circle;
    circle.center = r_pos;
    circle.radius = ry;
    circle.radius2 = rx;
    circle.color = rc_active_color;
    circle.numVertices = 21;
    makeEllipse(verticesCircle, indicesCircle, circle);

    for(int i = 2; i < verticesCircle.size(); i++)
    {
    	//std::cout << "V[" << i << "] = (" << verticesCircle[i-1].Pos.X << ", " << verticesCircle[i-1].Pos.Y << ") (" << verticesCircle[i].Pos.X << ", " << verticesCircle[i].Pos.Y << ")" << std::endl;
        rc_drawLine(verticesCircle[i-1].Pos.X, verticesCircle[i-1].Pos.Y, verticesCircle[i].Pos.X, verticesCircle[i].Pos.Y);
    }

    int n = verticesCircle.size()-1;
    rc_drawLine(verticesCircle[n].Pos.X, verticesCircle[n].Pos.Y, verticesCircle[1].Pos.X, verticesCircle[1].Pos.Y);
}


void rc_drawEllipseFill(int x, int y, int rx, int ry)
{
    irr::core::vector2d<s32> r_pos(x,y);

    // create the circle
    irr::core::array<irr::video::S3DVertex> verticesCircle;
    irr::core::array<irr::u16> indicesCircle;
    CircleSettings circle;
    circle.center = r_pos;
    circle.radius = ry;
    circle.radius2 = rx;
    circle.color = rc_active_color;
    circle.numVertices = 21;
    makeEllipse(verticesCircle, indicesCircle, circle);

    VideoDriver->draw2DVertexPrimitiveList(verticesCircle.pointer(), verticesCircle.size(),
        indicesCircle.pointer(), indicesCircle.size()-2, video::EVT_STANDARD, scene::EPT_TRIANGLE_FAN,
        video::EIT_16BIT);
}

void rc_drawCircle(int x, int y, double r)
{
    rc_drawEllipse(x, y, r, r);
}

void rc_drawCircleFill(int x, int y, double r)
{
	rc_drawEllipseFill(x, y, r, r);
	return;

    irr::core::vector2d<s32> r_pos(x,y);

    // create the circle
    irr::core::array<irr::video::S3DVertex> verticesCircle;
    irr::core::array<irr::u16> indicesCircle;
    CircleSettings circle;
    circle.center = r_pos;
    circle.radius = r;
    circle.color = rc_active_color;
    makeCircle(verticesCircle, indicesCircle, circle);

    VideoDriver->draw2DVertexPrimitiveList(verticesCircle.pointer(), verticesCircle.size(),
        indicesCircle.pointer(), indicesCircle.size()-2, video::EVT_STANDARD, scene::EPT_TRIANGLE_FAN,
        video::EIT_16BIT);
}


int rc_loadFont(std::string fnt_file, int font_size)
{
	irr::io::path file_path = fnt_file.c_str();
    int font_id = -1;
    for(int i = 0; i < rc_font.size(); i++)
    {
        if(!rc_font[i].active)
        {
            font_id = i;
            break;
        }
    }

    CGUITTFace* Face;
    CGUIFreetypeFont* dfont;

    Face = new CGUITTFace();
    Face->load(file_path);

    dfont = new CGUIFreetypeFont(VideoDriver);
    dfont->attach(Face, font_size);


    if(font_id < 0)
    {
        font_id = rc_font.size();

        rc_font_obj f;

        f.face = Face;
        f.font = dfont;
        f.font_size = font_size;
        f.active = true;

        rc_font.push_back(f);

        rc_active_font = font_id;
    }
    else
    {
        rc_font[font_id].face = Face;
        rc_font[font_id].font = dfont;
        rc_font[font_id].font_size = font_size;
        rc_font[font_id].active = true;
    }

    //std::cout << "id: " << font_id << std::endl;

    return font_id;
}

bool rc_fontExists(int font_id)
{
	if(font_id < 0 || font_id >= rc_font.size())
		return false;

    if(rc_font[font_id].active)
            return true;

    return false;
}

void rc_deleteFont(int font_id)
{
    if(rc_fontExists(font_id))
    {
        delete rc_font[font_id].font;
        delete rc_font[font_id].face;
        rc_font[font_id].font = NULL;
        rc_font[font_id].face = NULL;
        rc_font[font_id].font_size = 0;
        rc_font[font_id].active = false;
    }
}

void rc_setFont(int font_id)
{
    if(rc_fontExists(font_id))
        rc_active_font = font_id;
}

void rc_drawText(std::string txt, int x, int y)
{
    if(rc_fontExists(rc_active_font))
    {
        std::wstring text = utf8_to_wstring(txt);
        irr::core::dimension2d<irr::u32> text_dim = rc_font[rc_active_font].font->getDimension(text.c_str());
        irr::core::rect<s32> tpos(x, y, text_dim.Width, rc_font[rc_active_font].font_size);

        //std::cout << "Start drawing text: " << tpos.getWidth() << ", " << tpos.getHeight() << std::endl;
        rc_font[rc_active_font].font->draw(text.c_str(), tpos, rc_active_color);
        //std::cout << "------------------" << std::endl;
    }
}

Uint32 rc_getTextWidth(const std::string txt)
{
    if(rc_fontExists(rc_active_font))
    {
        std::wstring text = utf8_to_wstring(txt);
        irr::core::dimension2d<irr::u32> text_dim = rc_font[rc_active_font].font->getDimension(text.c_str());
        return text_dim.Width;
    }
    return 0;
}

Uint32 rc_getTextHeight(const std::string txt)
{
    if(rc_fontExists(rc_active_font))
    {
        std::wstring text = utf8_to_wstring(txt);
        //std::wstring wide = converter.from_bytes(txt);
        //irr::core::dimension2d<irr::u32> text_dim = rc_font[rc_active_font]->getDimension(wide.c_str());
        return rc_font[rc_active_font].font_size;
    }
    return 0;
}

void rc_getTextSize(const std::string txt, double* w, double* h)
{
    if(rc_fontExists(rc_active_font))
    {
        std::wstring text = utf8_to_wstring(txt);
        irr::core::dimension2d<irr::u32> text_dim = rc_font[rc_active_font].font->getDimension(text.c_str());
        *w = text_dim.Width;
        *h = rc_font[rc_active_font].font_size;
    }
    else
    {
        *w = 0;
        *h = 0;
    }
}


#define RC_MOUSE_BUTTON_LEFT 0
#define RC_MOUSE_BUTTON_MIDDLE 1
#define RC_MOUSE_BUTTON_RIGHT 2

int rc_mwheelx = -1;
int rc_mwheely = -1;

bool rc_cursor_visible = true;


bool rc_mouseButton(int b)
{
	int ix, iy;
    int current_button_state = SDL_GetMouseState(&ix, &iy);
    return (current_button_state & SDL_BUTTON(b));
}

int rc_mouseX()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    return (int)( (double)x * rc_window_mouse_scale_x );
}

int rc_mouseY()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    return (int)( (double)y * rc_window_mouse_scale_y );
}

void rc_getMouse(double* x, double* y, double* mb1, double* mb2, double* mb3)
{
    int ix, iy;
    int current_button_state = SDL_GetMouseState(&ix, &iy);

    *mb1 = (current_button_state & SDL_BUTTON(SDL_BUTTON_LEFT))!=0;
    *mb2 = (current_button_state & SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0;
    *mb3 = (current_button_state & SDL_BUTTON(SDL_BUTTON_RIGHT))!=0;

    *x = (double)ix * rc_window_mouse_scale_x;
    *y = (double)iy * rc_window_mouse_scale_x;
}

int rc_mouseWheelX()
{
    return rc_mwheelx;
}

int rc_mouseWheelY()
{
    return rc_mwheely;
}

int rc_globalMouseX()
{
    int x, y;
    SDL_GetGlobalMouseState(&x,&y);
    return x;
}

int rc_globalMouseY()
{
    int x, y;
    SDL_GetGlobalMouseState(&x,&y);
    return y;
}

void rc_getGlobalMouse(double * x, double* y, double* mb1, double* mb2, double* mb3)
{
    int ix, iy;
    int current_button_state = SDL_GetGlobalMouseState(&ix,&iy);

    *mb1 = (current_button_state & SDL_BUTTON(SDL_BUTTON_LEFT))!=0;
    *mb2 = (current_button_state & SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0;
    *mb3 = (current_button_state & SDL_BUTTON(SDL_BUTTON_RIGHT))!=0;

    *x = ix;
    *y = iy;
}

void rc_getMouseWheel(double* x, double* y)
{
    *x = rc_mwheelx;
    *y = rc_mwheely;
}

void rc_hideMouse()
{
    SDL_ShowCursor(0);
    rc_cursor_visible = false;
}

void rc_showMouse()
{
    SDL_ShowCursor(1);
    rc_cursor_visible = true;
}

bool rc_mouseIsVisible()
{
    return rc_cursor_visible;
}


int rc_inKey()
{
    return rc_inkey_val;
}

int rc_key(int check_Key)
{
	keyState = SDL_GetKeyboardState(NULL);
    return keyState[SDL_GetScancodeFromKey(check_Key)];
}

int rc_waitKey()
{
    bool wk_loop = true;
    SDL_Event e;
    while(wk_loop)
    {
        while(SDL_WaitEvent(&e))
        {
            if(e.type == SDL_KEYDOWN)
                return (int)e.key.keysym.sym;
        }
    }
    return 0;
}

void rc_wait(Uint32 ms)
{
    SDL_Delay(ms);
}



void rc_grabInput(bool flag)
{
    SDL_SetWindowGrab(rc_window, flag ? SDL_TRUE : SDL_FALSE);
}

int rc_windowIsGrabbed()
{
    return SDL_GetWindowGrab(rc_window);
}

void rc_warpMouse(int x, int y)
{
    SDL_WarpMouseInWindow(rc_window, (int)( (double)x*rc_window_zone_scale_x ), (int)( (double)y*rc_window_zone_scale_y ));
}

void rc_warpMouseGlobal(int x, int y)
{
    SDL_WarpMouseGlobal(x, y);
}

void rc_setMouseZone(int x, int y, int w, int h)
{
    SDL_Rect r;
    rc_mouse_zone.x = x;
    rc_mouse_zone.y = y;
    rc_mouse_zone.w = w;
    rc_mouse_zone.h = h;
    r.x = (int)( (double)x * rc_window_zone_scale_x );
    r.y = (int)( (double)y * rc_window_zone_scale_y );
    r.w = (int)( (double)w * rc_window_zone_scale_x );
    r.h = (int)( (double)h * rc_window_zone_scale_y );
    SDL_SetWindowMouseRect(rc_window, &r);
    rc_mouse_zone_active = true;
}

void rc_clearMouseZone()
{
    SDL_SetWindowMouseRect(rc_window, NULL);
    rc_mouse_zone_active = false;
}

void rc_setWindowAlwaysOnTop(bool flag)
{
    SDL_SetWindowAlwaysOnTop(rc_window, flag ? SDL_TRUE : SDL_FALSE);
}

void rc_setMouseRelative(bool flag)
{
    SDL_SetRelativeMouseMode(flag ? SDL_TRUE : SDL_FALSE);
}

void rc_setWindowVSync(bool flag)
{
    rc_window_setfps = true;
    SDL_DisplayMode dm;
    SDL_GetDesktopDisplayMode(0, &dm);
    rc_setfps_refresh_rate = dm.refresh_rate;
    rc_setfps_timer = SDL_GetTicks();
}

void rc_setFPS(int fps)
{
	if(fps < 0)
	{
		rc_window_setfps = false;
	}
	else
	{
		rc_window_setfps = true;
		rc_setfps_refresh_rate = fps;
		rc_setfps_timer = SDL_GetTicks();
	}
}

int rc_openURL(std::string url)
{
    return SDL_OpenURL(url.c_str());
}

std::string rc_SDLVersion()
{
    SDL_version version;
    SDL_GetVersion(&version);

    std::stringstream ss;
    ss << (uint32_t)version.major << "." << (uint32_t)version.minor << "." << (uint32_t)version.patch;
    return ss.str();

}

int rc_flashWindow(int flag)
{
    switch(flag)
    {
        case 0:
            return SDL_FlashWindow(rc_window, SDL_FLASH_CANCEL);
        case 1:
            return SDL_FlashWindow(rc_window, SDL_FLASH_BRIEFLY);
        case 2:
            return SDL_FlashWindow(rc_window, SDL_FLASH_UNTIL_FOCUSED);
    }

    return -1;
}

int rc_messageBox(std::string title, std::string msg)
{
    return SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title.c_str(), msg.c_str(), NULL);
}

int rc_FPS()
{
    return VideoDriver->getFPS();
}




int rc_getNumJoysticks()
{
    return SDL_NumJoysticks();
}

int rc_joyAxis(int joy_num, int axis)
{
    if(joy_num >= 0 && joy_num < MAX_JOYSTICKS)
        return SDL_JoystickGetAxis(rc_joystick[joy_num], axis);
    return 0;
}

int rc_joyButton(int joy_num, int jbutton)
{
    if(joy_num >= 0 && joy_num < MAX_JOYSTICKS)
        return SDL_JoystickGetButton(rc_joystick[joy_num], jbutton);
    return 0;
}

std::string rc_joyName(int joy_num)
{
    if(joy_num >= 0 && joy_num < MAX_JOYSTICKS)
        return (std::string)SDL_JoystickName(rc_joystick[joy_num]);
    return "";
}

int rc_numJoyButtons(int joy_num)
{
    if(joy_num >= 0 && joy_num < MAX_JOYSTICKS)
        return SDL_JoystickNumButtons(rc_joystick[joy_num]);
    return 0;
}

int rc_numJoyAxes(int joy_num)
{
    if(joy_num >= 0 && joy_num < MAX_JOYSTICKS)
        return SDL_JoystickNumAxes(rc_joystick[joy_num]);
    return 0;
}

int rc_numJoyHats(int joy_num)
{
    if(joy_num >= 0 && joy_num < MAX_JOYSTICKS)
        return SDL_JoystickNumHats(rc_joystick[joy_num]);
    return 0;
}

int rc_joyHat(int joy_num, int hat)
{
    if(joy_num >= 0 && joy_num < MAX_JOYSTICKS)
        return SDL_JoystickGetHat(rc_joystick[joy_num], hat);
    return 0;
}

int rc_numJoyTrackBalls(int joy_num)
{
    if(joy_num >= 0 && joy_num < MAX_JOYSTICKS)
        return SDL_JoystickNumBalls(rc_joystick[joy_num]);
    return 0;
}

void rc_getJoyTrackBall(int joy_num, int ball, double * dx, double * dy)
{
    int x = 0;
    int y = 0;
    if(joy_num >= 0 && joy_num < MAX_JOYSTICKS)
        SDL_JoystickGetBall(rc_joystick[joy_num], ball, &x, &y);
    *dx = x;
    *dy = y;
}

bool rc_joystickIsConnected( int joy_num )
{
    if(joy_num >= 0 && joy_num < MAX_JOYSTICKS)
    {
        if(rc_joystick[joy_num])
            return true;
        return false;
    }
    return false;
}

void rc_joyRumblePlay(int joy_num, double strength, double duration)
{
    if(joy_num >= 0 && joy_num < MAX_JOYSTICKS)
    {
        SDL_HapticRumblePlay(rc_haptic[joy_num], strength, (Uint32)duration);
    }
}

void rc_joyRumbleStop(int joy_num)
{
    if(joy_num >= 0 && joy_num < MAX_JOYSTICKS)
        SDL_HapticRumbleStop(rc_haptic[joy_num]);
}

int rc_joystickIsHaptic( int joy_num )
{
    if(joy_num >= 0 && joy_num < MAX_JOYSTICKS)
    {
        if(rc_haptic[joy_num])
            return 1;
    }
    return 0;
}





void rc_getTouchFinger(int finger, double * x, double * y, double * pressure)
{
    if(finger < MAX_FINGERS)
    {
        *x = rc_finger[finger].x;
        *y = rc_finger[finger].y;
        *pressure = rc_finger[finger].pressure;
    }
}

int rc_numFingers()
{
    return rc_fingers_pressed.size();
}

double rc_touchPressure()
{
    return rc_pressure;
}

void rc_getTouch(double * status, double * x, double * y, double * distX, double * distY)
{
    *status = (double)rc_touch;
    *x = (double)rc_touchX;
    *y = (double)rc_touchY;
    *distX = (double)rc_motionX;
    *distY = (double)rc_motionY;
    return;
}

void rc_getMultiTouch(double * status, double * x, double * y, double * numFingers, double * dist, double * theta)
{
    *status = (double)rc_mt_status;
    *x = (double)rc_mt_x;
    *y = (double)rc_mt_y;
    *numFingers = (double)rc_mt_numFingers;
    *dist = rc_mt_dist;
    *theta = rc_mt_theta;
    return;
}

void rc_getAccel(uint32_t accel_num, double * x, double * y, double * z)
{
    float sensor_data[4];
    if(accel_num < num_accels)
        SDL_SensorGetData(rc_accel[accel_num], &sensor_data[0], 3);
    *x = sensor_data[0];
    *y = sensor_data[1];
    *z = sensor_data[2];
}

std::string rc_accelName(uint32_t accel_num)
{
    if(accel_num < num_accels)
        return (std::string)SDL_SensorGetName(rc_accel[accel_num]);
    return "";
}

int rc_numAccels()
{
    return num_accels;
}

void rc_getGyro(uint32_t gyro_num, double * x, double * y, double * z)
{
    float sensor_data[4];
    if(gyro_num < num_gyros)
        SDL_SensorGetData(rc_gyro[gyro_num], &sensor_data[0], 3);
    *x = sensor_data[0];
    *y = sensor_data[1];
    *z = sensor_data[2];
}

std::string rc_gyroName(uint32_t gyro_num)
{
    if(gyro_num < num_gyros)
        return (std::string)SDL_SensorGetName(rc_gyro[gyro_num]);
    return "";
}

int rc_numGyros()
{
    return num_gyros;
}

void rc_readInput_Start()
{
    SDL_StartTextInput();
    rc_textinput_isActive = true;
    rc_textinput_string = "";
    rc_textinput_timer = clock() / (double)(CLOCKS_PER_SEC / 1000);
}

void rc_readInput_Stop()
{
    rc_textinput_isActive = false;
    rc_textinput_timer = 0;
    rc_textinput_string = "";
    SDL_StopTextInput();
}

std::string rc_readInput_GetText()
{
    return rc_textinput_string;
}

void rc_readInput_SetText(std::string txt)
{
    rc_textinput_string = txt;
}

void rc_readInput_ToggleBackspace(bool flag)
{
    rc_toggleBackspace = flag;
}


int rc_loadImageEx(std::string img_file, Uint32 color_key = 0, bool use_color_key = true)
{
    rc_image_obj img;
    img.image = VideoDriver->getTexture(img_file.c_str());

    if(img.image == NULL)
        return -1;

	if(color_key == -1)
	{
		Uint32* img_pixels = (Uint32*)img.image->lock();
		color_key = img_pixels[0];
		img.image->unlock();
	}

    if(use_color_key)
        VideoDriver->makeColorKeyTexture(img.image, irr::video::SColor(color_key), false);

    int img_id = -1;

    for(int i = 0; i < rc_image.size(); i++)
    {
        if(rc_image[i].image == NULL)
        {
            img_id = i;
            break;
        }
    }

    if(img_id < 0)
    {
        img_id = rc_image.size();
        rc_image.push_back(img);
    }
    else
    {
        rc_image[img_id] = img;
    }

    return img_id;
}

int rc_loadImage(std::string img_file)
{
    return rc_loadImageEx(img_file, 0, false);
}

void rc_deleteImage(int img_id)
{
    if(img_id < 0 || img_id >= rc_image.size())
        return;

    if(rc_image[img_id].image)
    {
        rc_image[img_id].image->drop();
        rc_image[img_id].image = NULL;
        rc_image[img_id].alpha = 255;
    }
}

int rc_createImageEx(int w, int h, double * pdata, Uint32 colorkey, bool use_color_key=true)
{
    if(w <= 0 || h <=0)
        return -1;

    irr::video::IImage* image = VideoDriver->createImage(irr::video::ECF_A8R8G8B8, irr::core::dimension2d<irr::u32>((irr::u32)w,(irr::u32)h));
    if(!image)
        return -1;

    Uint32 * img_pixels = (Uint32*)image->getData();

    if( ((w*h) >= 1) && colorkey == -1)
    {
    	colorkey = img_pixels[0];
    }


    for(int i = 0; i < (w*h); i++)
    {
        img_pixels[i] = (Uint32)pdata[i];
    }

    irr::video::ITexture* texture = VideoDriver->addTexture("buffer_image", image);
    image->drop();

    if(!texture)
        return -1;

    if(use_color_key)
        VideoDriver->makeColorKeyTexture(texture, irr::video::SColor(colorkey));

    int img_id = -1;
    rc_image_obj img;
    img.image = texture;
    img.alpha = 255;

    for(int i = 0; i < rc_image.size(); i++)
    {
        if(rc_image[i].image == NULL)
        {
            img_id = i;
            break;
        }
    }

    if(img_id < 0)
    {
        img_id = rc_image.size();
        rc_image.push_back(img);
    }
    else
    {
        rc_image[img_id] = img;
    }

    return img_id;
}

int rc_createImage(int w, int h, double* pdata)
{
    return rc_createImageEx(w, h, pdata, 0, false);
}


void rc_getImageBuffer(int img_id, double * pdata)
{
    if(img_id < 0 || img_id >= rc_image.size())
        return;

    if(!rc_image[img_id].image)
        return;

    Uint32* img_pixels = (Uint32*)rc_image[img_id].image->lock();

    int image_size = rc_image[img_id].image->getSize().Width * rc_image[img_id].image->getSize().Height;

    for(int i = 0; i < image_size; i++)
        pdata[i] = (double)img_pixels[i];

    rc_image[img_id].image->unlock();
}

void rc_setBilinearFilter(bool flag)
{
    rc_bilinear_filter = flag;
    rc_setDriverMaterial();
}

bool rc_getBilinearFilter()
{
    return rc_bilinear_filter;
}

void rc_setAntiAliasMode( int aa_mode )
{
	rc_anti_alias = (irr::video::E_ANTI_ALIASING_MODE) aa_mode;
}

int rc_getAntiAliasMode( )
{
	return (int)rc_anti_alias;
}

void rc_setImageColorMod(int img_id, Uint32 color)
{
    if(img_id < 0 || img_id >= rc_image.size())
        return;

    if(rc_image[img_id].image)
    {
        rc_image[img_id].color_mod = irr::video::SColor(color);
    }
}

Uint32 rc_getImageColorMod(int img_id)
{
    if(img_id < 0 || img_id >= rc_image.size())
        return 0;

    if(rc_image[img_id].image)
    {
        return rc_image[img_id].color_mod.color;
    }

    return 0;
}


void rc_setBlendMode(int blend_mode)
{
    switch(blend_mode)
    {
        case 0: rc_blend_mode = EBO_NONE; break;
        case 1: rc_blend_mode = EBO_ADD; break;
        case 2: rc_blend_mode = EBO_SUBTRACT; break;
        case 3: rc_blend_mode = EBO_REVSUBTRACT; break;
        case 4: rc_blend_mode = EBO_MIN; break;
        case 5: rc_blend_mode = EBO_MAX; break;
        case 6: rc_blend_mode = EBO_MIN_FACTOR; break;
        case 7: rc_blend_mode = EBO_MAX_FACTOR; break;
        case 8: rc_blend_mode = EBO_MIN_ALPHA; break;
        case 9: rc_blend_mode = EBO_MAX_ALPHA; break;
    }

    rc_setDriverMaterial();
}

int rc_getBlendMode()
{
    return (int)rc_blend_mode;
}

void rc_drawImage(int img_id, int x, int y)
{
    if(img_id < 0 || img_id >= rc_image.size())
        return;

    if(rc_image[img_id].image)
    {
        irr::core::dimension2d<irr::u32> src_size = rc_image[img_id].image->getSize();
        irr::core::rect<irr::s32> sourceRect( irr::core::vector2d<irr::s32>(0, 0), src_size);

        irr::core::position2d<irr::s32> position(x, y);

        irr::core::position2d<irr::s32> rotationPoint(0, 0); //since we are not rotating it doesn't matter

        irr::f32 rotation = 0;
        irr::core::vector2df scale(1.0, 1.0);
        bool useAlphaChannel = true;
        irr::video::SColor color(rc_image[img_id].alpha,
                                 rc_image[img_id].color_mod.getRed(),
                                 rc_image[img_id].color_mod.getGreen(),
                                 rc_image[img_id].color_mod.getBlue());

        //irr::core::rect<irr::s32> dest( irr::core::vector2d(x, y), irr::core::dimension2d(src_w, src_h));;

        //irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].dimension.Width, rc_canvas[rc_active_canvas].dimension.Height);
        irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].texture->getSize().Width, rc_canvas[rc_active_canvas].texture->getSize().Height);

        draw2DImage(VideoDriver, rc_image[img_id].image, sourceRect, position, rotationPoint, rotation, scale, useAlphaChannel, color, screenSize);
    }
}

int rc_copyImage(int src_id)
{
    if(src_id < 0 || src_id >= rc_image.size())
        return -1;

    if(!rc_image[src_id].image)
        return -1;

    irr::video::ITexture* texture = VideoDriver->addRenderTargetTexture(rc_image[src_id].image->getSize(), "img_copy", irr::video::ECF_A8R8G8B8);

    if(!texture)
        return -1;

    VideoDriver->setRenderTarget(texture, true, false, irr::video::SColor(0));


    irr::core::dimension2d<irr::u32> src_size = rc_image[src_id].image->getSize();
    irr::core::rect<irr::s32> sourceRect( irr::core::vector2d<irr::s32>(0, 0), src_size);
    irr::core::position2d<irr::s32> position(0, 0);
    irr::core::position2d<irr::s32> rotationPoint(0, 0); //since we are not rotating it doesn't matter
    irr::f32 rotation = 0;
    irr::core::vector2df scale(1.0, 1.0);
    bool useAlphaChannel = true;
    irr::video::SColor color(rc_image[src_id].alpha,
                             rc_image[src_id].color_mod.getRed(),
                             rc_image[src_id].color_mod.getGreen(),
                             rc_image[src_id].color_mod.getBlue());
    irr::core::vector2df screenSize(src_size.Width, src_size.Height);

    draw2DImage(VideoDriver, rc_image[src_id].image, sourceRect, position, rotationPoint, rotation, scale, useAlphaChannel, color, screenSize);

    rc_setActiveCanvas(rc_active_canvas);

    int img_id = -1;
    rc_image_obj img;
    img.image = texture;
    img.alpha = 255;

    for(int i = 0; i < rc_image.size(); i++)
    {
        if(rc_image[i].image == NULL)
        {
            img_id = i;
            break;
        }
    }

    if(img_id < 0)
    {
        img_id = rc_image.size();
        rc_image.push_back(img);
    }
    else
    {
        rc_image[img_id] = img;
    }

    return img_id;
}


void rc_drawImage_Rotate(int img_id, int x, int y, double angle)
{
    if(img_id < 0 || img_id >= rc_image.size())
        return;

    if(rc_image[img_id].image)
    {
        irr::core::dimension2d<irr::u32> src_size = rc_image[img_id].image->getSize();
        irr::core::rect<irr::s32> sourceRect(0, 0, src_size.Width, src_size.Height);

        irr::core::position2d<irr::s32> position(x, y);

        irr::core::position2d<irr::s32> rotationPoint(x + (src_size.Width/2), y + (src_size.Height/2));

        irr::f32 rotation = -1*angle;
        irr::core::vector2df scale(1.0, 1.0);
        bool useAlphaChannel = true;
        irr::video::SColor color(rc_image[img_id].alpha,
                                 rc_image[img_id].color_mod.getRed(),
                                 rc_image[img_id].color_mod.getGreen(),
                                 rc_image[img_id].color_mod.getBlue());

        //irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].dimension.Width, rc_canvas[rc_active_canvas].dimension.Height);
        irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].texture->getSize().Width, rc_canvas[rc_active_canvas].texture->getSize().Height);

        draw2DImage(VideoDriver, rc_image[img_id].image, sourceRect, position, rotationPoint, rotation, scale, useAlphaChannel, color, screenSize);
    }
}

void rc_drawImage_Zoom(int img_id, int x, int y, double zx, double zy)
{
    if(img_id < 0 || img_id >= rc_image.size())
        return;

    if(rc_image[img_id].image)
    {
        irr::core::dimension2d<irr::u32> src_size = rc_image[img_id].image->getSize();
        irr::core::rect<irr::s32> sourceRect(0, 0, src_size.Width, src_size.Height);

        irr::core::position2d<irr::s32> position(x, y);

        irr::core::position2d<irr::s32> rotationPoint(x + (src_size.Width/2), y + (src_size.Height/2));

        irr::f32 rotation = 0;
        irr::core::vector2df scale((irr::f32)zx, (irr::f32)zy);
        bool useAlphaChannel = true;
        irr::video::SColor color(rc_image[img_id].alpha,
                                 rc_image[img_id].color_mod.getRed(),
                                 rc_image[img_id].color_mod.getGreen(),
                                 rc_image[img_id].color_mod.getBlue());

        //irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].dimension.Width, rc_canvas[rc_active_canvas].dimension.Height);
        irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].texture->getSize().Width, rc_canvas[rc_active_canvas].texture->getSize().Height);

        draw2DImage(VideoDriver, rc_image[img_id].image, sourceRect, position, rotationPoint, rotation, scale, useAlphaChannel, color, screenSize);
    }
}

void rc_drawImage_ZoomEx(int img_id, int x, int y, int src_x, int src_y, int src_w, int src_h, double zx, double zy)
{
    if(img_id < 0 || img_id >= rc_image.size())
        return;

    if(rc_image[img_id].image)
    {
        //irr::core::dimension2d<irr::u32> src_size = rc_image[img_id].image->getSize();
        irr::core::rect<irr::s32> sourceRect( irr::core::vector2d<irr::s32>(src_x, src_y), irr::core::dimension2d<irr::s32>(src_w, src_h));

        irr::core::position2d<irr::s32> position(x, y);

        irr::core::position2d<irr::s32> rotationPoint(x + (src_w/2), y + (src_h/2));

        irr::f32 rotation = 0;
        irr::core::vector2df scale((irr::f32)zx, (irr::f32)zy);
        bool useAlphaChannel = true;
        irr::video::SColor color(rc_image[img_id].alpha,
                                 rc_image[img_id].color_mod.getRed(),
                                 rc_image[img_id].color_mod.getGreen(),
                                 rc_image[img_id].color_mod.getBlue());

        //irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].dimension.Width, rc_canvas[rc_active_canvas].dimension.Height);
        irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].texture->getSize().Width, rc_canvas[rc_active_canvas].texture->getSize().Height);

        draw2DImage(VideoDriver, rc_image[img_id].image, sourceRect, position, rotationPoint, rotation, scale, useAlphaChannel, color, screenSize);
    }
}

void rc_drawImage_Rotozoom(int img_id, int x, int y, double angle, double zx, double zy)
{
    if(img_id < 0 || img_id >= rc_image.size())
        return;

    if(rc_image[img_id].image)
    {
        irr::core::dimension2d<irr::u32> src_size = rc_image[img_id].image->getSize();
        irr::core::rect<irr::s32> sourceRect(0, 0, src_size.Width, src_size.Height);

        irr::core::position2d<irr::s32> position(x, y);

        irr::core::position2d<irr::s32> rotationPoint(x + (src_size.Width/2)*zx, y + (src_size.Height/2)*zy);

        irr::f32 rotation = -1*angle;
        irr::core::vector2df scale((irr::f32)zx, (irr::f32)zy);
        bool useAlphaChannel = true;
        irr::video::SColor color(rc_image[img_id].alpha,
                                 rc_image[img_id].color_mod.getRed(),
                                 rc_image[img_id].color_mod.getGreen(),
                                 rc_image[img_id].color_mod.getBlue());

        //irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].dimension.Width, rc_canvas[rc_active_canvas].dimension.Height);
        irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].texture->getSize().Width, rc_canvas[rc_active_canvas].texture->getSize().Height);

        draw2DImage(VideoDriver, rc_image[img_id].image, sourceRect, position, rotationPoint, rotation, scale, useAlphaChannel, color, screenSize);
    }
}

void rc_drawImage_RotozoomEx(int img_id, int x, int y, int src_x, int src_y, int src_w, int src_h, double angle, double zx, double zy)
{
    if(img_id < 0 || img_id >= rc_image.size())
        return;

    if(rc_image[img_id].image)
    {
        //irr::core::dimension2d<irr::u32> src_size = rc_image[img_id].image->getSize();
        irr::core::rect<irr::s32> sourceRect( irr::core::vector2d<irr::s32>(src_x, src_y), irr::core::dimension2d<irr::s32>(src_w, src_h));

        irr::core::position2d<irr::s32> position(x, y);

        irr::core::position2d<irr::s32> rotationPoint(x + (src_w/2)*zx, y + (src_h/2)*zy);

        irr::f32 rotation = -1*angle;
        irr::core::vector2df scale((irr::f32)zx, (irr::f32)zy);
        bool useAlphaChannel = true;
        irr::video::SColor color(rc_image[img_id].alpha,
                                 rc_image[img_id].color_mod.getRed(),
                                 rc_image[img_id].color_mod.getGreen(),
                                 rc_image[img_id].color_mod.getBlue());

        //irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].dimension.Width, rc_canvas[rc_active_canvas].dimension.Height);
        irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].texture->getSize().Width, rc_canvas[rc_active_canvas].texture->getSize().Height);

        draw2DImage(VideoDriver, rc_image[img_id].image, sourceRect, position, rotationPoint, rotation, scale, useAlphaChannel, color, screenSize);
    }
}


void rc_drawImage_Flip(int img_id, int x, int y, bool h, bool v)
{
    if(img_id < 0 || img_id >= rc_image.size())
        return;

    if(rc_image[img_id].image)
    {
        irr::core::dimension2d<irr::u32> src_size = rc_image[img_id].image->getSize();
        irr::core::rect<irr::s32> sourceRect(0, 0, src_size.Width, src_size.Height);

        irr::core::position2d<irr::s32> rotationPoint(x + (src_size.Width/2), y + (src_size.Height/2));

        irr::f32 rotation = 0;
        irr::core::vector2df scale((irr::f32)(h ? -1 : 1), (irr::f32) (v ? -1 : 1));

        irr::core::position2d<irr::s32> position( (h ? x+src_size.Width : x), (v ? y+src_size.Height : y));

        bool useAlphaChannel = true;
        irr::video::SColor color(rc_image[img_id].alpha,
                                 rc_image[img_id].color_mod.getRed(),
                                 rc_image[img_id].color_mod.getGreen(),
                                 rc_image[img_id].color_mod.getBlue());

        //irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].dimension.Width, rc_canvas[rc_active_canvas].dimension.Height);
        irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].texture->getSize().Width, rc_canvas[rc_active_canvas].texture->getSize().Height);

        draw2DImage(VideoDriver, rc_image[img_id].image, sourceRect, position, rotationPoint, rotation, scale, useAlphaChannel, color, screenSize);
    }
}

void rc_drawImage_FlipEx(int img_id, int x, int y, int src_x, int src_y, int src_w, int src_h, bool h, bool v)
{
    if(img_id < 0 || img_id >= rc_image.size())
        return;

    if(rc_image[img_id].image)
    {
        //irr::core::dimension2d<irr::u32> src_size = rc_image[img_id].image->getSize();
        irr::core::rect<irr::s32> sourceRect( irr::core::vector2d<irr::s32>(src_x, src_y), irr::core::dimension2d<irr::s32>(src_w, src_h));

        irr::core::position2d<irr::s32> rotationPoint(x + (src_w/2), y + (src_h/2));

        irr::f32 rotation = 0;
        irr::core::vector2df scale((irr::f32)(h ? -1 : 1), (irr::f32) (v ? -1 : 1));

        irr::core::position2d<irr::s32> position( (h ? x+src_w : x), (v ? y+src_h : y));

        bool useAlphaChannel = true;
        irr::video::SColor color(rc_image[img_id].alpha,
                                 rc_image[img_id].color_mod.getRed(),
                                 rc_image[img_id].color_mod.getGreen(),
                                 rc_image[img_id].color_mod.getBlue());

        //irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].dimension.Width, rc_canvas[rc_active_canvas].dimension.Height);
        irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].texture->getSize().Width, rc_canvas[rc_active_canvas].texture->getSize().Height);

        draw2DImage(VideoDriver, rc_image[img_id].image, sourceRect, position, rotationPoint, rotation, scale, useAlphaChannel, color, screenSize);
    }
}


void rc_drawImage_Blit(int img_id, int x, int y, int src_x, int src_y, int src_w, int src_h)
{
    if(img_id < 0 || img_id >= rc_image.size())
        return;

    if(rc_image[img_id].image)
    {
        //irr::core::dimension2d<irr::u32> src_size = rc_image[img_id].image->getSize();
        irr::core::rect<irr::s32> sourceRect( irr::core::vector2d<irr::s32>(src_x, src_y), irr::core::dimension2d<irr::s32>(src_w, src_h));

        irr::core::position2d<irr::s32> position(x, y);

        irr::core::position2d<irr::s32> rotationPoint(0, 0); //since we are not rotating it doesn't matter

        irr::f32 rotation = 0;
        irr::core::vector2df scale(1.0, 1.0);
        bool useAlphaChannel = true;
        irr::video::SColor color(rc_image[img_id].alpha,
                                 rc_image[img_id].color_mod.getRed(),
                                 rc_image[img_id].color_mod.getGreen(),
                                 rc_image[img_id].color_mod.getBlue());

        irr::core::rect<irr::s32> dest( irr::core::vector2d<irr::s32>(x, y), irr::core::dimension2d<irr::s32>(src_w, src_h));

        //irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].dimension.Width, rc_canvas[rc_active_canvas].dimension.Height);
        irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].texture->getSize().Width, rc_canvas[rc_active_canvas].texture->getSize().Height);

        draw2DImage(VideoDriver, rc_image[img_id].image, sourceRect, position, rotationPoint, rotation, scale, useAlphaChannel, color, screenSize);
    }
}


void rc_drawImage_RotateEx(int img_id, int x, int y, int src_x, int src_y, int src_w, int src_h, int angle)
{
    if(img_id < 0 || img_id >= rc_image.size())
        return;

    if(rc_image[img_id].image)
    {
        //irr::core::dimension2d<irr::u32> src_size = rc_image[img_id].image->getSize();
        irr::core::rect<irr::s32> sourceRect( irr::core::vector2d<irr::s32>(src_x, src_y), irr::core::dimension2d<irr::s32>(src_w, src_h));

        //irr::core::position2d<irr::s32> position(x, y);

        irr::core::vector2d<irr::s32> rotationPoint(x + (src_w/2), y + (src_h/2));

        irr::f32 rotation = -1*angle;
        //irr::core::vector2df scale(1.0, 1.0);
        bool useAlphaChannel = true;
        irr::video::SColor color(rc_image[img_id].alpha,
                                 rc_image[img_id].color_mod.getRed(),
                                 rc_image[img_id].color_mod.getGreen(),
                                 rc_image[img_id].color_mod.getBlue());

        //irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].dimension.Width, rc_canvas[rc_active_canvas].dimension.Height);
        irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].texture->getSize().Width, rc_canvas[rc_active_canvas].texture->getSize().Height);

        irr::core::rect<irr::s32> dest( irr::core::vector2d<irr::s32>(x, y), irr::core::dimension2d<irr::s32>(src_w, src_h));

        draw2DImage2(VideoDriver, rc_image[img_id].image, sourceRect, dest, rotationPoint, rotation, useAlphaChannel, color, screenSize);
    }
}

void rc_drawImage_BlitEx(int img_id, int x, int y, int w, int h, int src_x, int src_y, int src_w, int src_h)
{
    if(img_id < 0 || img_id >= rc_image.size())
        return;

    if(rc_image[img_id].image)
    {
        //irr::core::dimension2d<irr::u32> src_size = rc_image[img_id].image->getSize();
        irr::core::rect<irr::s32> sourceRect( irr::core::vector2d<irr::s32>(src_x, src_y), irr::core::dimension2d<irr::s32>(src_w, src_h));

        //irr::core::position2d<irr::s32> position(x, y);

        irr::core::position2d<irr::s32> rotationPoint(0, 0); //since we are not rotating it doesn't matter

        irr::f32 rotation = 0;
        irr::core::vector2df scale(1.0, 1.0);
        bool useAlphaChannel = true;
        irr::video::SColor color(rc_image[img_id].alpha,
                                 rc_image[img_id].color_mod.getRed(),
                                 rc_image[img_id].color_mod.getGreen(),
                                 rc_image[img_id].color_mod.getBlue());

        irr::core::rect<irr::s32> dest( irr::core::vector2d<irr::s32>(x, y), irr::core::dimension2d<irr::s32>(w, h));

        //irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].dimension.Width, rc_canvas[rc_active_canvas].dimension.Height);
        irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].texture->getSize().Width, rc_canvas[rc_active_canvas].texture->getSize().Height);

        draw2DImage2(VideoDriver, rc_image[img_id].image, sourceRect, dest, rotationPoint, rotation, useAlphaChannel, color, screenSize );
    }
}

void rc_setImageAlpha(int img_id, Uint8 alpha)
{
    if(img_id < 0 || img_id >= rc_image.size())
        return;

    if(rc_image[img_id].image)
    {
        rc_image[img_id].alpha = alpha;
    }
}

Uint32 rc_getImageAlpha(int img_id)
{
    if(img_id < 0 || img_id >= rc_image.size())
        return 0;

    if(rc_image[img_id].image)
    {
        return rc_image[img_id].alpha;
    }

    return 0;
}

bool rc_imageExists(int img_id)
{
    if(img_id < 0 || img_id >= rc_image.size())
        return false;

    if(rc_image[img_id].image)
        return true;

    return false;
}

void rc_getImageSize(int img_id, double* w, double* h)
{
    if(img_id < 0 || img_id >= rc_image.size())
        return;

    if(rc_image[img_id].image)
    {
        *w = (double)rc_image[img_id].image->getSize().Width;
        *h = (double)rc_image[img_id].image->getSize().Height;
    }
}

void rc_setColorKey(int img_id, Uint32 colorkey)
{
    if(!rc_imageExists(img_id))
        return;

    if(colorkey == -1)
	{
		Uint32* img_pixels = (Uint32*)rc_image[img_id].image->lock();
		colorkey = img_pixels[0];
		rc_image[img_id].image->unlock();
	}
    VideoDriver->makeColorKeyTexture(rc_image[img_id].image, irr::video::SColor(colorkey));
}



//FloodFill is technically a primitive but it uses the draw2Dimage function since the pixels returned by lock are flipped vertically
void floodFill(int x, int y, Uint32* img_pixels, Uint32 prev_color)
{
	if(x < 0 || x >= rc_canvas[rc_active_canvas].texture->getSize().Width)
		return;

	if(y < 0 || y >= rc_canvas[rc_active_canvas].texture->getSize().Height)
		return;

	if(img_pixels[y*rc_canvas[rc_active_canvas].texture->getSize().Width+x] != prev_color)
		return;

	img_pixels[y*rc_canvas[rc_active_canvas].texture->getSize().Width+x] = rc_active_color.color;

	floodFill(x-1, y, img_pixels, prev_color);
	floodFill(x, y-1, img_pixels, prev_color);
	floodFill(x+1, y, img_pixels, prev_color);
	floodFill(x, y+1, img_pixels, prev_color);
}

void rc_floodFill(int x, int y)
{
    if(!rc_canvas[rc_active_canvas].texture)
        return;

	if(x < 0 || x >= rc_canvas[rc_active_canvas].dimension.Width)
		return;

	if(y < 0 || y >= rc_canvas[rc_active_canvas].dimension.Height)
		return;

	#ifdef RC_DRIVER_GLES2
	y = rc_canvas[rc_active_canvas].texture->getSize().Height - (y+1);
	#endif // RC_DRIVER_GLES2

    Uint32* img_pixels = (Uint32*)rc_canvas[rc_active_canvas].texture->lock();

    Uint32 flood_size = rc_canvas[rc_active_canvas].texture->getSize().Width*rc_canvas[rc_active_canvas].texture->getSize().Height;
    Uint32* flood_buffer = new Uint32[flood_size];

    for(int i = 0; i < flood_size; i++)
	{
		flood_buffer[i] = img_pixels[i];
	}

    floodFill(x, y,flood_buffer, flood_buffer[y*rc_canvas[rc_active_canvas].texture->getSize().Width+x]);

    for(int i = 0; i < flood_size; i++)
	{
		img_pixels[i] = flood_buffer[i];
	}

    rc_canvas[rc_active_canvas].texture->unlock();

    Uint32 nw = rc_canvas[rc_active_canvas].dimension.Width;
	Uint32 nh = rc_canvas[rc_active_canvas].dimension.Height;
    irr::video::ITexture* new_canvas = VideoDriver->addRenderTargetTexture(irr::core::dimension2d<u32>(nw,nh), "rt", ECF_A8R8G8B8);
    irr::video::ITexture* old_canvas = rc_canvas[rc_active_canvas].texture;
    rc_canvas[rc_active_canvas].texture = new_canvas;

    irr::core::dimension2d<irr::u32> src_size = new_canvas->getSize();
	irr::core::rect<irr::s32> sourceRect(0, 0, src_size.Width, src_size.Height);

	irr::core::position2d<irr::s32> rotationPoint((src_size.Width/2), (src_size.Height/2));

	irr::f32 rotation = 0;
	irr::core::vector2df scale((irr::f32)1, (irr::f32)-1);

	irr::core::position2d<irr::s32> position(0, src_size.Height);

	bool useAlphaChannel = true;
	irr::video::SColor color(rc_canvas[rc_active_canvas].color_mod);

	//irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].dimension.Width, rc_canvas[rc_active_canvas].dimension.Height);
	irr::core::vector2df screenSize(rc_canvas[rc_active_canvas].texture->getSize().Width, rc_canvas[rc_active_canvas].texture->getSize().Height);

	rc_setActiveCanvas(rc_active_canvas);
	draw2DImage(VideoDriver, old_canvas, sourceRect, position, rotationPoint, rotation, scale, useAlphaChannel, color, screenSize);

	VideoDriver->removeTexture(old_canvas);
}




void drawCanvasImage(irr::video::ITexture* texture, int x, int y, int src_x, int src_y, int src_w, int src_h, int tgt_width, int tgt_height)
{
    if(texture)
    {
        irr::core::rect<irr::s32> sourceRect( irr::core::vector2d<irr::s32>(src_x, src_y), irr::core::dimension2d<irr::s32>(src_w, src_h));

        irr::core::position2d<irr::s32> position(x, y);

        irr::core::position2d<irr::s32> rotationPoint(0, 0); //since we are not rotating it doesn't matter

        irr::f32 rotation = 0;
        irr::core::vector2df scale(1.0, 1.0);
        bool useAlphaChannel = true;
        irr::video::SColor color(255,255,255,255);

        irr::core::rect<irr::s32> dest( irr::core::vector2d<irr::s32>(x, y), irr::core::dimension2d<irr::s32>(src_w, src_h));

        irr::core::vector2df screenSize(tgt_width, tgt_height);

        draw2DImage(VideoDriver, texture, sourceRect, position, rotationPoint, rotation, scale, useAlphaChannel, color, screenSize);
    }
}


int rc_windowClip(int x, int y, int w, int h)
{
    if(w <= 0 || h <=0)
        return -1;

	if(rc_canvas.size() == 0)
		return -1;

    if(!rc_canvas[0].texture)
            return -1;

    #ifdef RC_DRIVER_GLES2
    Uint32 size_n = 2;
    Uint32 dim_max = (w > h ? w : h);
    while(size_n < dim_max) size_n *= 2;
    irr::video::ITexture* texture = VideoDriver->addRenderTargetTexture(irr::core::dimension2d<irr::u32>((irr::u32)size_n, (irr::u32)size_n), "canvas_clip_image", ECF_A8R8G8B8);
    #else
    irr::video::ITexture* texture = VideoDriver->addRenderTargetTexture(irr::core::dimension2d<irr::u32>((irr::u32)w, (irr::u32)h), "canvas_clip_image", irr::video::ECF_A8R8G8B8);
    #endif // RC_WEB

    if(!texture)
        return -1;

    VideoDriver->setRenderTarget(texture);

    int tgt_w = texture->getSize().Width;
    int tgt_h = texture->getSize().Height;

    #ifdef RC_DRIVER_GLES2
    int canvas_id = 0;

    irr::core::vector2d<irr::f32> screenSize( (irr::f32) tgt_w, (irr::f32) tgt_h );
    irr::video::SColor color(rc_canvas[canvas_id].color_mod);
    irr::core::dimension2d<irr::u32> cv_dim(tgt_w, tgt_h);
	irr::core::position2d<irr::s32> cv_pos(0, 0);
	irr::core::vector2d<irr::s32> cv_offset(x, rc_canvas[canvas_id].texture->getSize().Height - y - cv_dim.Height);
	irr::core::rect<s32> src( cv_offset, cv_dim );
	irr::core::rect<s32> dest( irr::core::vector2d<s32>(cv_pos.X, cv_pos.Y), irr::core::dimension2d<s32>(cv_dim.Width, cv_dim.Height) );
	draw2DImage2(VideoDriver, rc_canvas[canvas_id].texture, src, dest, irr::core::position2d<irr::s32>(0, 0), 0, true, color, screenSize);

	//rc_setDriverMaterial();
    //VideoDriver->draw2DImage(rc_canvas[rc_active_canvas].texture, dest, src, 0, 0, false);
    #else
    drawCanvasImage(rc_canvas[0].texture, 0, 0, x, y, w, h, tgt_w, tgt_h);
    #endif // RC_DRIVER_GLES2

    rc_setActiveCanvas(rc_active_canvas);
    //VideoDriver->setRenderTarget(rc_canvas[rc_active_canvas].texture, false, false);

    int img_id = -1;
    rc_image_obj img;
    img.image = texture;
    img.alpha = 255;

    for(int i = 0; i < rc_image.size(); i++)
    {
        if(rc_image[i].image == NULL)
        {
            img_id = i;
            break;
        }
    }

    if(img_id < 0)
    {
        img_id = rc_image.size();
        rc_image.push_back(img);
    }
    else
    {
        rc_image[img_id] = img;
    }

    return img_id;
}


int rc_canvasClip(int x, int y, int w, int h)
{
    if(w <= 0 || h <=0)
        return -1;

    if(rc_active_canvas >= 0 && rc_active_canvas < rc_canvas.size())
    {
        if(!rc_canvas[rc_active_canvas].texture)
            return -1;
    }
    else
        return -1;

    #ifdef RC_DRIVER_GLES2
    Uint32 size_n = 2;
    Uint32 dim_max = (w > h ? w : h);
    while(size_n < dim_max) size_n *= 2;
    irr::video::ITexture* texture = VideoDriver->addRenderTargetTexture(irr::core::dimension2d<irr::u32>((irr::u32)size_n, (irr::u32)size_n), "canvas_clip_image", ECF_A8R8G8B8);
    #else
    irr::video::ITexture* texture = VideoDriver->addRenderTargetTexture(irr::core::dimension2d<irr::u32>((irr::u32)w, (irr::u32)h), "canvas_clip_image", irr::video::ECF_A8R8G8B8);
    #endif // RC_WEB

    if(!texture)
        return -1;

    VideoDriver->setRenderTarget(texture);

    int tgt_w = texture->getSize().Width;
    int tgt_h = texture->getSize().Height;

    #ifdef RC_DRIVER_GLES2
    int canvas_id = rc_active_canvas;

    irr::core::vector2d<irr::f32> screenSize( (irr::f32) tgt_w, (irr::f32) tgt_h );
    irr::video::SColor color(rc_canvas[canvas_id].color_mod);
    irr::core::dimension2d<irr::u32> cv_dim(tgt_w, tgt_h);
	irr::core::position2d<irr::s32> cv_pos(0, 0);
	irr::core::vector2d<irr::s32> cv_offset(x, rc_canvas[canvas_id].texture->getSize().Height - y - cv_dim.Height);
	irr::core::rect<s32> src( cv_offset, cv_dim );
	irr::core::rect<s32> dest( irr::core::vector2d<s32>(cv_pos.X, cv_pos.Y), irr::core::dimension2d<s32>(cv_dim.Width, cv_dim.Height) );
	draw2DImage2(VideoDriver, rc_canvas[canvas_id].texture, src, dest, irr::core::position2d<irr::s32>(0, 0), 0, true, color, screenSize);

	//rc_setDriverMaterial();
    //VideoDriver->draw2DImage(rc_canvas[rc_active_canvas].texture, dest, src, 0, 0, false);
    #else
    drawCanvasImage(rc_canvas[rc_active_canvas].texture, 0, 0, x, y, w, h, tgt_w, tgt_h);
    #endif // RC_DRIVER_GLES2

    rc_setActiveCanvas(rc_active_canvas);
    //VideoDriver->setRenderTarget(rc_canvas[rc_active_canvas].texture, false, false);

    int img_id = -1;
    rc_image_obj img;
    img.image = texture;
    img.alpha = 255;

    for(int i = 0; i < rc_image.size(); i++)
    {
        if(rc_image[i].image == NULL)
        {
            img_id = i;
            break;
        }
    }

    if(img_id < 0)
    {
        img_id = rc_image.size();
        rc_image.push_back(img);
    }
    else
    {
        rc_image[img_id] = img;
    }

    return img_id;
}

#endif // RC_GFX_INCLUDED
