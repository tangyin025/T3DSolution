/*
 * File: MyGame.cpp
 */

#include "t3dPrecompiledHeader.h"
#include "MyGame.h"

// ////////////////////////////////////////////////////////////////////////////
// GLOBALS
// ////////////////////////////////////////////////////////////////////////////

static std::map<std::string, t3dMaterialPtr> g_materialMap;

// ////////////////////////////////////////////////////////////////////////////
// IMPLEMENTS
// ////////////////////////////////////////////////////////////////////////////

// ============================================================================
// str_printf
// ============================================================================

#include <stdarg.h>
#include <stdio.h>

std::string T3DLIB_API str_printf(char * format, ...)
{
	va_list arg_list;
	va_start(arg_list, format);
	char buffer[MAX_BUFFER_SIZE];
	int res = vsprintf(buffer, format, arg_list);
	va_end(arg_list);

	if(res < 0)
	{
		throw MyException("format string failed");
	}

	return std::string(buffer);
}

// ============================================================================
// t3dClipper
// ============================================================================

t3dClipper::t3dClipper(t3dDDraw * ddraw, MyWindowBasePtr wnd)
{
	INIT_ZERO(m_clipper);
	if(!Create_Windowed_DDClipper(&ddraw->m_ddraw, &m_clipper, wnd->get_hwnd()))
		throw MyException("create window clipper failed");
}

t3dClipper::t3dClipper(t3dDDraw * ddraw, RECT rect)
{
	INIT_ZERO(m_clipper);
	if(!Create_Memoried_DDClipper(&ddraw->m_ddraw, &m_clipper, &rect, 1))
		throw MyException("create memory clipper failed");
}

t3dClipper::~t3dClipper()
{
	Destroy_DDClipper(&m_clipper);
}

// ============================================================================
// t3dSurface
// ============================================================================

t3dSurface::t3dSurface()
{
	INIT_ZERO(m_ddsurface);
	INIT_ZERO(m_tdc);
}

t3dSurface::~t3dSurface()
{
	Destroy_DDSurface(&m_ddsurface);
}

void t3dSurface::set_clipper(t3dClipperPtr clipper)
{
	if(!Attach_DDSurface_DDClipper(&m_ddsurface, &clipper->m_clipper))
		throw MyException("attach clipper failed");
	m_clipper = clipper;
}

int t3dSurface::get_BPP(void)
{
	return m_ddsurface.bpp;
}

SURFACEV1 t3dSurface::lock(void)
{
	SURFACEV1 surf;
	if(!Lock_DDSurface(&m_ddsurface, &surf))
		throw MyException("lock surface failed");
	return surf;
}

void t3dSurface::unlock(void)
{
	if(!Unlock_DDSurface(&m_ddsurface))
		throw MyException("unlock surface failed");
}

void t3dSurface::fill(RECT rect, unsigned int color)
{
	if(!Fill_DDSurface(&m_ddsurface, &rect, color))
		throw MyException("fill surface failed");
}

void t3dSurface::blit(RECT rect, t3dSurfacePtr other, RECT other_rect)
{
	if(!Blit_DDSurface(&m_ddsurface, &rect, &other->m_ddsurface, &other_rect))
		throw MyException("block transfer failed");
}

void t3dSurface::text_out(std::string text, int x, int y)
{
	if(!Begin_Text_DC(&m_ddsurface, &m_tdc))
		throw MyException("begin text out failed");

	Set_Text_BKColor(&m_tdc, RGB(255, 255, 255));
	Set_Text_BKMode(&m_tdc, TEXT_BKMODE_OPAQUE);
	Set_Text_Color(&m_tdc, RGB(0, 0, 0));

	Text_Out(&m_tdc, text.c_str(), x, y);

	End_Text_DC(&m_tdc);
}

void t3dSurface::text_out(std::string text, int x, int y, COLORREF color)
{
	if(!Begin_Text_DC(&m_ddsurface, &m_tdc))
		throw MyException("begin text out failed");

	Set_Text_BKMode(&m_tdc, TEXT_BKMODE_TRANSPARENT);
	Set_Text_Color(&m_tdc, color);

	Text_Out(&m_tdc, text.c_str(), x, y);

	End_Text_DC(&m_tdc);
}

t3dSurfaceScreen::t3dSurfaceScreen(t3dDDraw * ddraw)
{
	if(!Create_Windowed_DDSurface(&ddraw->m_ddraw, &m_ddsurface))
		throw MyException("create screen surface failed");
}

t3dSurfaceMemory::t3dSurfaceMemory(t3dDDraw * ddraw, int width, int height)
{
	if(!Create_Memoried_DDSurface(&ddraw->m_ddraw, &m_ddsurface, width, height))
		throw MyException("create memory surface failed");
}

t3dSurfaceVideos::t3dSurfaceVideos(t3dDDraw *ddraw, int width, int height)
{
	if(!Create_Videoied_DDSurface(&ddraw->m_ddraw, &m_ddsurface, width, height))
		throw MyException("create video's surface failed");
}

// ============================================================================
// t3dZbuffer
// ============================================================================

t3dZbuffer::t3dZbuffer(int width, int height)
{
	INIT_ZERO(m_zbuffer);
	if(!Create_ZBuffer(&m_zbuffer, width, height))
		throw MyException("create zbuffer failed");
}

t3dZbuffer::~t3dZbuffer()
{
	Destroy_ZBuffer(&m_zbuffer);
}

// ============================================================================
// t3dCamera
// ============================================================================

t3dCamera::t3dCamera()
{
	INIT_ZERO(m_camera);
}

t3dCamera::~t3dCamera()
{
}

t3dCameraEuler::t3dCameraEuler(RECT rect, const VECTOR4D & pos, const VECTOR4D & rot,
							   REAL fov /*= DEG_TO_RAD(90)*/,
							   REAL min_clip_z /*= 10*/,
							   REAL max_clip_z /*= 1000*/,
							   VIEWPORT_FIX_MODE fix_mode /*= VIEWPORT_FIX_MODE_WIDTH*/,
							   int rot_seq /*= ROTATION_SEQ_ZXY*/)
{
	CAM4DV1_Init(	&m_camera,
					(REAL)MyWindow::GetRectWidth(rect),
					(REAL)MyWindow::GetRectHeight(rect),
					(REAL)rect.left,
					(REAL)rect.top,
					min_clip_z,
					max_clip_z,
					fov,
					fix_mode, NULL, NULL);

	m_camera.vpos = pos;
	m_camera.vrot = rot;
	Build_Camera4D_Mat_Euler(&m_camera.mcam, &m_camera, rot_seq);
}

// ============================================================================
// t3dDDraw
// ============================================================================

t3dDDraw::t3dDDraw()
{
	INIT_ZERO(*this);
	if(!Create_DDraw(&m_ddraw))
		throw MyException("create ddraw failed");
}

t3dDDraw::~t3dDDraw()
{
	Destroy_DDraw(&m_ddraw);
}

void t3dDDraw::set_coop_level(coop_level_type type)
{
	if(FAILED(gresult = m_ddraw.lpddraw->SetCooperativeLevel(NULL, type)))
	{
		Set_Last_Error(Get_DDraw_Error(gbuffer, gresult), __FILE__, __LINE__);
		throw MyException("set cooperative level failed");
	}
}

t3dSurfacePtr t3dDDraw::create_screen_surface(void)
{
	return t3dSurfacePtr(new t3dSurfaceScreen(this));
}

t3dSurfacePtr t3dDDraw::create_memory_surface(int width, int height)
{
	return t3dSurfacePtr(new t3dSurfaceMemory(this, width, height));
}

t3dSurfacePtr t3dDDraw::create_videos_surface(int width, int height)
{
	return t3dSurfacePtr(new t3dSurfaceVideos(this, width, height));
}

t3dClipperPtr t3dDDraw::create_screen_clipper(MyWindowBasePtr wnd)
{
	return t3dClipperPtr(new t3dClipper(this, wnd));
}

t3dClipperPtr t3dDDraw::create_single_clipper(RECT rect)
{
	return t3dClipperPtr(new t3dClipper(this, rect));
}

// ============================================================================
// t3d_INIT( const int BPP )
// ============================================================================

void T3DLIB_API t3d_INIT( const int BPP )
{
	if(!Init_T3dlib1(BPP))
		throw MyException("initial t3dlib1 failed");

	if(!Init_T3dlib4(BPP))
		throw MyException("initial t3dlib4 failed");

	if(!Init_T3dlib5(BPP))
		throw MyException("initial t3dlib5 failed");

	if(!Init_T3dlib6(BPP))
		throw MyException("initial t3dlib6 failed");
}

// ============================================================================
// t3dFPS
// ============================================================================

const unsigned int t3dFPS::interval_time = 1000;

t3dFPS::t3dFPS()
{
	INIT_ZERO(*this);
}

t3dFPS::~t3dFPS()
{
}

void t3dFPS::init(void)
{
	last_time = ::timeGetTime();
	pass_frames = 0;
}

void t3dFPS::OnFrame(void)
{
	pass_frames++;

	curr_time = ::timeGetTime();
	pass_time += curr_time - last_time;
	last_time = curr_time;

	if(pass_time >= interval_time)
	{
		fps = (REAL)pass_frames / (REAL)pass_time * 1000;
		pass_time = 0;
		pass_frames = 0;
	}
}

REAL t3dFPS::get_FPS(void)
{
	return fps;
}

// ============================================================================
// t3dMaterial
// ============================================================================

const std::string t3dMaterial::default_name = "DEFAULT_MATERIAL";

t3dMaterial::t3dMaterial()
{
	INIT_ZERO(m_material);
}

t3dMaterial::~t3dMaterial()
{
	Destroy_Material(&m_material);
}

void t3dMaterial::load(msModel & model, const std::string material_name /*= ""*/)
{
	assert(NULL != Create_Material_From_MsModel_By_Name);

	if(!material_name.empty())
	{
		if(!Create_Material_From_MsModel_By_Name(&m_material, &model, material_name.c_str()))
			throw MyException(std::string("cannot read material " + material_name));
	}
	else
	{
		if(0 >= model.nNumMaterials)
			throw MyException(std::string("no material in this model"));

		//if(!Create_Material_From_MsMaterial(&m_material, &model.pMaterials[0]))
		//	throw MyException(std::string("read first material failed"));

		if(!Create_Material_From_MsModel_By_Name(&m_material, &model, model.pMaterials[0].szName))
			throw MyException(std::string("read first material failed"));
	}
}

// ============================================================================
// t3dLight
// ============================================================================

t3dLight::t3dLight()
{
	INIT_ZERO(m_light);
}

t3dLight::~t3dLight()
{
}

void t3dLight::light(t3dLightObject * obj, t3dMaterialPtr mat)
{
	obj->light_SELF(this, mat);
}

t3dLightAmbient::t3dLightAmbient(unsigned int color)
{
	m_light.mode = LIGHT4DV1_MODE_AMBIENT;
	m_light.color = color;
}

t3dLightDirect::t3dLightDirect(unsigned int color, const VECTOR4D & pos, const VECTOR4D & dir)
{
	m_light.mode = LIGHT4DV1_MODE_DIRECT;
	m_light.color = color;
	m_light.vpos = pos;
	m_light.vdir = dir;
}

t3dLightPoint::t3dLightPoint(unsigned int color, const VECTOR4D & pos,
							 REAL kc /*= (REAL)1.0*/,
							 REAL kl /*= (REAL)0.001*/,
							 REAL kq /*= (REAL)0.00001*/)
{
	m_light.mode = LIGHT4DV1_MODE_POINT;
	m_light.color = color;
	m_light.vpos = pos;
	m_light.kc = kc;
	m_light.kl = kl;
	m_light.kq = kq;
}

// ============================================================================
// t3dRender
// ============================================================================

t3dRender::t3dRender()
{
}

t3dRender::~t3dRender()
{
}

void t3dRender::draw(t3dRenderObject * obj)
{
	assert(m_cam != NULL);
	assert(m_surf != NULL);
	assert(m_zbuf != NULL);
	assert(m_mat != NULL);

	obj->draw_SELF(this);
}

void t3dRender::add_light(std::string l_name, t3dLightPtr light)
{
	assert(m_lightMap.end() == m_lightMap.find(l_name));
	m_lightMap[l_name] = light;
}

void t3dRender::del_light(std::string l_name)
{
	assert(m_lightMap.end() != m_lightMap.find(l_name));
	m_lightMap.erase(l_name);
}

t3dLightPtr t3dRender::get_light(std::string l_name)
{
	assert(m_lightMap.end() != m_lightMap.find(l_name));
	return m_lightMap[l_name];
}

void t3dRender::set_camera(t3dCameraPtr cam)
{
	assert(cam != NULL);
	m_cam = cam;
}

void t3dRender::set_surface(t3dSurfacePtr surf)
{
	assert(surf != NULL);
	m_surf = surf;
}

void t3dRender::set_zbuffer(t3dZbufferPtr zbuf)
{
	assert(zbuf != NULL);
	m_zbuf = zbuf;
}

void t3dRender::set_material(t3dMaterialPtr mat)
{
	assert(mat != NULL);
	m_mat = mat;
}

// ============================================================================
// t3dObject
// ============================================================================

t3dObject::t3dObject()
{
	INIT_ZERO(m_object);
}

t3dObject::~t3dObject()
{
	Destroy_Object4D(&m_object);
}

void t3dObject::light_SELF(t3dLight * light, t3dMaterialPtr mat)
{
	Light_Object4D(&m_object, &light->m_light, &mat->m_material);
}

void t3dObject::draw_SELF(t3dRender * render)
{
	assert(NULL != Clip_Object4D);
	assert(NULL != Clip_Object4D_Gouraud_Texture);

	if(NULL != render->m_mat->m_material.texture.pbuffer)
	{
		Remove_Object4D_Backface_At_World(&m_object, &render->m_cam->m_camera);
		std::map<std::string, t3dLightPtr>::const_iterator l_iter;
		for(l_iter = render->m_lightMap.begin(); l_iter != render->m_lightMap.end(); l_iter++)
		{
			l_iter->second->light(this, render->m_mat);
		}

		World_To_Camera_Object4D(&m_object, &render->m_cam->m_camera);
		if(!Clip_Object4D_Gouraud_Texture(&m_object, &render->m_cam->m_camera))
			throw MyException("clip object failed");
		Camera_To_Perspective_Object4D(&m_object, &render->m_cam->m_camera);
		Perspective_To_Screen_Object4D(&m_object, &render->m_cam->m_camera);

		SURFACEV1 surf = render->m_surf->lock();
		render->m_cam->m_camera.psurf = &surf;
		render->m_cam->m_camera.pzbuf = &render->m_zbuf->m_zbuffer;
		{
			Draw_Object4D_Gouraud_Texture_ZBufferRW(&m_object, &render->m_cam->m_camera, &render->m_mat->m_material);
		}
		render->m_surf->unlock();
	}
	else
	{
		Remove_Object4D_Backface_At_World(&m_object, &render->m_cam->m_camera);
		std::map<std::string, t3dLightPtr>::const_iterator l_iter;
		for(l_iter = render->m_lightMap.begin(); l_iter != render->m_lightMap.end(); l_iter++)
		{
			l_iter->second->light(this, render->m_mat);
		}

		World_To_Camera_Object4D(&m_object, &render->m_cam->m_camera);
		if(!Clip_Object4D_Gouraud_Texture(&m_object, &render->m_cam->m_camera))
			throw MyException("clip object failed");
		Camera_To_Perspective_Object4D(&m_object, &render->m_cam->m_camera);
		Perspective_To_Screen_Object4D(&m_object, &render->m_cam->m_camera);

		SURFACEV1 surf = render->m_surf->lock();
		render->m_cam->m_camera.psurf = &surf;
		render->m_cam->m_camera.pzbuf = &render->m_zbuf->m_zbuffer;
		{
			Draw_Object4D_Wire_ZBufferRW(&m_object, &render->m_cam->m_camera);
		}
		render->m_surf->unlock();
	}
}

void t3dObject::load(const std::string file_name, const std::string mesh_name /*= ""*/)
{
	msModel model;
	INIT_ZERO(model);

	/*
	 * Note, if the std::string file_name have upper to 16 character (include 16 character)
	 * then if throw an exception, the std::~basic_string of 'file_name' will throw an
	 * unknown exception. for example, please trans file_name = "1234567890123456" ...
	 */
	//throw MyException("Hehehe");

	if(!Create_MsModel_From_File(&model, file_name.c_str()))
		throw MyException("cannot read file");

	if(!mesh_name.empty())
	{
		if(!Create_Object4D_From_MsModel_By_Name(&m_object, &model, mesh_name.c_str()))
			throw MyException(std::string("cannot read mesh " + mesh_name));
	}
	else
	{
		if(0 >= model.nNumMeshes)
			throw MyException(std::string("no mesh in this file " + file_name));

		//if(!Create_Object4D_From_MsMesh(&m_object, &model.pMeshes[0]))
		//	throw MyException(std::string("read first mesh from " + file_name + " failed"));

		//if(0 <= model.pMeshes[0].nMaterialIndex && model.nNumMaterials > model.pMeshes[0].nMaterialIndex)
		//	strcpy(m_object.material_name, model.pMaterials[model.pMeshes[0].nMaterialIndex].szName);

		if(!Create_Object4D_From_MsModel_By_Name(&m_object, &model, model.pMeshes[0].szName))
			throw MyException(std::string("read first mesh from " + file_name + " failed"));
	}

	if(strlen(m_object.material_name) > 0)
	{
		assert(strcmp(m_object.material_name, t3dMaterial::default_name.c_str()) != 0);
		if(g_materialMap.end() == g_materialMap.find(m_object.material_name))
		{
			t3dMaterialPtr material = t3dMaterialPtr(new t3dMaterial);
			material->load(model, m_object.material_name);
			g_materialMap[m_object.material_name] = material;

			assert(strcmp(m_object.material_name, material->m_material.name) == 0);
		}

		m_material = g_materialMap[m_object.material_name];
	}
	else
	{
		assert(g_materialMap.end() != g_materialMap.find(t3dMaterial::default_name));
		m_material = g_materialMap[t3dMaterial::default_name];
	}

	if(NULL != m_material->m_material.texture.pbuffer)
	{
		Undate_Object4D_Absolute_UV(&m_object, &model, &m_material->m_material);
	}

	Destroy_MsModel(&model);
}

void t3dObject::reset(void)
{
	Reset_Object4D(&m_object);
}

void t3dObject::to_WORLD(VECTOR4D & pos, VECTOR4D & rot)
{
	Model_To_World_Object4D(&m_object, &pos, &rot, TRANSFORM_MODE_LOCAL_TO_TRANS);
}
