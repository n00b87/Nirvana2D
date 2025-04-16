#ifndef RC_GFX_CORE_H_INCLUDED
#define RC_GFX_CORE_H_INCLUDED

#if defined(RC_ANDROID)
	#include "SDL.h"
	#include "btBulletDynamicsCommon.h"
	#include "BulletSoftBody/btSoftRigidDynamicsWorld.h"
	#include "BulletCollision/NarrowPhaseCollision/btRaycastCallback.h"
#else
	#include <SDL2/SDL.h>
	#include <bullet/btBulletDynamicsCommon.h>
	#include <BulletSoftBody/btSoftRigidDynamicsWorld.h>
	#include <bullet/BulletCollision/NarrowPhaseCollision/btRaycastCallback.h>
#endif // _IRR_ANDROID_PLATFORM_
#include <irrlicht.h>
#include <iostream>
#include <sstream>
#include <string>
#include <locale>
#include <codecvt>
#include <cmath>
#include <set>
#include "gui_freetype_font.h"
#include "rc_utf8.h"
#include "camera.h"
#include <box2d/box2d.h>
#include "rc_sprite2D.h"
#include <irrBullet.h>
#ifdef RC_ANDROID
	#include "an8parser.h"
#else
	#include <an8parser.h>
#endif

using namespace irr;

using namespace core;
using namespace video;
using namespace scene;


IrrlichtDevice* device;
irr::video::IVideoDriver * VideoDriver;
irr::scene::ISceneManager *SceneManager;

irr::core::dimension2d<u32> rc_window_size;
double rc_window_mouse_scale_x = 1;
double rc_window_mouse_scale_y = 1;


#define RC_CANVAS_TYPE_2D		0
#define RC_CANVAS_TYPE_3D		1
#define RC_CANVAS_TYPE_SPRITE	2

#define RC_PROJECTION_TYPE_ORTHOGRAPHIC		0
#define RC_PROJECTION_TYPE_PERSPECTIVE		1

struct rc_canvas_obj
{
    irr::video::ITexture* texture;

    //irr::video::ITexture* sprite_layer;

    int type;

    irr::core::dimension2d<u32> dimension;

    struct rc_canvas_viewport
    {
        irr::core::vector2d<s32> position;
        irr::core::dimension2d<u32> dimension;
    } viewport;


    bool show3D = false;

    irr::core::vector2d<s32> offset;

    int mode;

    bool visible = true;
    int z = 0;

    irr::u32 color_mod;

    irr::core::array<irr::s32> sprite_id;
};

irr::core::array<rc_canvas_obj> rc_canvas;
irr::core::array<u32> rc_canvas_zOrder;
int rc_active_canvas = -1;
bool hasPreUpdated = false;

irr::video::SColor rc_active_color(0,0,0,0);
irr::video::SColor rc_clear_color(0,0,0,0);

irr::s32 MouseX, MouseY, MouseXRel, MouseYRel;
irr::u32 MouseButtonStates;


static Uint32 baseticks = 0;

struct rc_image_obj
{
    irr::video::ITexture* image;
    Uint8 alpha = 255;
    irr::video::SColor color_mod = irr::video::SColor(255,255,255,255);
};
irr::core::array<rc_image_obj> rc_image;

irr::video::E_BLEND_OPERATION rc_blend_mode = irr::video::EBO_ADD;
bool rc_bilinear_filter = false;
irr::video::E_ANTI_ALIASING_MODE rc_anti_alias = irr::video::EAAM_OFF;

void draw2DImage(irr::video::IVideoDriver *driver, irr::video::ITexture* texture, irr::core::rect<irr::s32> sourceRect, irr::core::position2d<irr::s32> position, irr::core::position2d<irr::s32> rotationPoint, irr::f32 rotation, irr::core::vector2df scale, bool useAlphaChannel, irr::video::SColor color, irr::core::vector2d<irr::f32> screenSize)
{
    if(rc_active_canvas < 0 || rc_active_canvas >= rc_canvas.size())
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
    material.TextureLayer[0].BilinearFilter = rc_bilinear_filter;
    material.MaterialTypeParam = irr::video::pack_textureBlendFunc(irr::video::EBF_SRC_ALPHA, irr::video::EBF_ONE_MINUS_SRC_ALPHA, irr::video::EMFN_MODULATE_1X, irr::video::EAS_TEXTURE | irr::video::EAS_VERTEX_COLOR);
    material.BlendOperation = rc_blend_mode;
    material.AntiAliasing = rc_anti_alias;
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

void draw2DImage2(irr::video::IVideoDriver *driver, irr::video::ITexture* texture, irr::core::rect<irr::s32> sourceRect, irr::core::rect<irr::s32> destRect, irr::core::position2d<irr::s32> rotationPoint, irr::f32 rotation, bool useAlphaChannel, irr::video::SColor color, irr::core::vector2d<irr::f32> screenSize )
{
    if(rc_active_canvas < 0 || rc_active_canvas >= rc_canvas.size())
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
    material.TextureLayer[0].BilinearFilter = rc_bilinear_filter; //TODO: Add option to switch this on/off
    material.BlendOperation = rc_blend_mode;
    material.MaterialTypeParam = irr::video::pack_textureBlendFunc(irr::video::EBF_SRC_ALPHA, irr::video::EBF_ONE_MINUS_SRC_ALPHA, irr::video::EMFN_MODULATE_1X, irr::video::EAS_TEXTURE | irr::video::EAS_VERTEX_COLOR);
    material.AntiAliasing = rc_anti_alias;

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

#endif // RC_GFX_CORE_H_INCLUDED
