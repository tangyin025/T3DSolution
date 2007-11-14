/*
 * File: MyGameBase.cpp
 */

#include "t3dPrecompiledHeader.h"
#include "MyGame.h"
#include <vector>

// ////////////////////////////////////////////////////////////////////////////
// GLOBALS
// ////////////////////////////////////////////////////////////////////////////

std::map<std::string, t3dMaterialPtr> g_materialMap;

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

void t3dZbuffer::clear(void)
{
	Clear_ZBuffer(&m_zbuffer);
}

// ============================================================================
// t3dCamera
// ============================================================================

t3dCamera::t3dCamera(RECT rect,
					 REAL fov					/*= DEG_TO_RAD(90)*/,
					 REAL min_clip_z			/*= 10*/,
					 REAL max_clip_z			/*= 1000*/,
					 VIEWPORT_FIX_MODE fixMode	/*= fix_mode_width*/,
					 int rotSeq					/*= ROTATION_SEQ_ZXY*/)
{
	INIT_ZERO(m_camera);

	set_fov(fov);
	set_min_clipZ(min_clip_z);
	set_max_clipZ(max_clip_z);
	set_viewport(rect);
	set_fix_mode(fixMode);
	set_rot_seq(rotSeq);

	m_camera.mode				= CAM4DV1_MODE_UNKNOWN;
}

t3dCamera::~t3dCamera()
{
}

void t3dCamera::set_viewport(RECT rect)
{
	m_camera.viewport.x			= floor((REAL)rect.left);
	m_camera.viewport.y			= floor((REAL)rect.top);
	m_camera.viewport.width		= floor((REAL)MyWindow::GetRectWidth(rect));
	m_camera.viewport.height	= floor((REAL)MyWindow::GetRectHeight(rect));
}

void t3dCamera::set_fov(REAL fov)
{
	m_camera.fov				= fov;
}

void t3dCamera::set_min_clipZ(REAL min_z)
{
	m_camera.min_clip_z			= min_z;
}

void t3dCamera::set_max_clipZ(REAL max_z)
{
	m_camera.max_clip_z			= max_z;
}

void t3dCamera::set_fix_mode(VIEWPORT_FIX_MODE fixMode)
{
	m_fixMode = fixMode;
}

void t3dCamera::set_rot_seq(int rotSeq)
{
	m_rotSeq = rotSeq;
}

void t3dCamera::build_VIEWPLANE(void)
{
	switch(m_fixMode)
	{
	case VIEWPORT_FIX_MODE_WIDTH:
		m_camera.viewplane.width	= tan(m_camera.fov / 2) * 2 * CAM4DV1_VIEWPLANE_DIST;
		assert(m_camera.viewplane.width > 0);
		m_camera.viewplane.height	= m_camera.viewport.height / m_camera.viewport.width * m_camera.viewplane.width;
		break;

	case VIEWPORT_FIX_MODE_HEIGHT:
		m_camera.viewplane.height	= tan(m_camera.fov / 2) * 2 * CAM4DV1_VIEWPLANE_DIST;
		assert(m_camera.viewplane.height > 0);
		m_camera.viewplane.width	= m_camera.viewport.width / m_camera.viewport.height * m_camera.viewplane.height;
		break;

	default:
		assert(0);
		break;
	}
}

t3dCameraEuler::t3dCameraEuler(RECT rect,
							   REAL fov						/*= DEG_TO_RAD(90)*/,
							   REAL min_clip_z				/*= 10*/,
							   REAL max_clip_z				/*= 1000*/,
							   VIEWPORT_FIX_MODE fixMode	/*= VIEWPORT_FIX_MODE_WIDTH*/,
							   int rotSeq					/*= ROTATION_SEQ_ZXY*/)
	: t3dCamera(rect, fov, min_clip_z, max_clip_z, fixMode, rotSeq)
{
	m_camera.mode				= CAM4DV1_MODE_EULAR;
}

t3dCameraEuler::~t3dCameraEuler()
{
}

void t3dCameraEuler::update(void)
{
	build_VIEWPLANE();
	build_MAT();
}

void t3dCameraEuler::set_position(VECTOR4D & pos)
{
	m_camera.vpos = pos;
}

void t3dCameraEuler::set_rotation(VECTOR4D & rot)
{
	m_camera.vrot = rot;
}

void t3dCameraEuler::build_MAT(void)
{
	Build_Camera4D_Mat_Euler(&m_camera.mcam, &m_camera, m_rotSeq);
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

void t3dDDraw::set_coop_level(coop_level_type type, MyWindowBasePtr wnd)
{
	if(FAILED(gresult = m_ddraw.lpddraw->SetCooperativeLevel(wnd->get_hwnd(), type)))
	{
		Set_Last_Error(Get_DDraw_Error(gbuffer, gresult), __FILE__, __LINE__);
		throw MyException("set cooperative level failed");
	}
}

void t3dDDraw::set_display_mode(int width, int height, int bpp)
{
	if(!Set_Display_Model(&m_ddraw, width, height, bpp))
		throw MyException("set display mode failed");
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
// t3dMouse
// ============================================================================

t3dMouseState::t3dMouseState()
{
	INIT_ZERO(m_dimousestate);
}

t3dMouseState::~t3dMouseState()
{
}

long t3dMouseState::get_X(void)
{
	return m_dimousestate.lX;
}

long t3dMouseState::get_Y(void)
{
	return m_dimousestate.lY;
}

long t3dMouseState::get_Z(void)
{
	return m_dimousestate.lZ;
}

unsigned char t3dMouseState::is_lbutton_down(void)
{
	return m_dimousestate.rgbButtons[0];
}

unsigned char t3dMouseState::is_mbutton_down(void)
{
	return m_dimousestate.rgbButtons[1];
}

unsigned char t3dMouseState::is_rbutton_down(void)
{
	return m_dimousestate.rgbButtons[2];
}

t3dMouse::t3dMouse(t3dDInput * input)
{
	INIT_ZERO(m_dimouse);

	LPDIRECTINPUTDEVICE8A lpdimouse;
	if(FAILED(gresult = input->m_dinput.lpdinput->CreateDevice(GUID_SysMouse, &lpdimouse, NULL)))
	{
		Get_DInput_Error(gbuffer, gresult);
		throw MyException("create dimouse failed");
	}

	if(FAILED(gresult = lpdimouse->SetDataFormat(&c_dfDIMouse)))
	{
		Get_DInput_Error(gbuffer, gresult);
		throw MyException("set dimouse data format failed");
	}

	m_dimouse.lpdimouse = lpdimouse;
	m_state = t3dMouseStatePtr(new t3dMouseState);
}

t3dMouse::~t3dMouse()
{
	Destroy_DIMouse(&m_dimouse);
}

void t3dMouse::set_coop_level(coop_level_type type, MyWindowBasePtr wnd)
{
	if(FAILED(gresult = m_dimouse.lpdimouse->SetCooperativeLevel(
			wnd->get_hwnd(), type)))
	{
		Get_DInput_Error(gbuffer, gresult);
		throw MyException("set dimouse cooperative level failed");
	}

	if(FAILED(gresult = m_dimouse.lpdimouse->Acquire()))
	{
		Get_DInput_Error(gbuffer, gresult);
		throw MyException("acquire dimouse failed");
	}
}

t3dMouseStatePtr t3dMouse::get_state(void)
{
	if(!Read_DIMouse_State(&m_dimouse, &m_state->m_dimousestate))
		throw MyException("read dimouse state failed");

	return m_state;
}

// ============================================================================
// t3dKey
// ============================================================================

t3dKeyState::t3dKeyState()
{
	INIT_ZERO(m_dikeystate);
}

t3dKeyState::~t3dKeyState()
{
}

unsigned char t3dKeyState::is_key_down(const DWORD key_i)
{
	return m_dikeystate.state[key_i];
}

t3dKey::t3dKey(t3dDInput * input)
{
	INIT_ZERO(m_dikey);

	LPDIRECTINPUTDEVICE8A lpdikey;
	if(FAILED(gresult = input->m_dinput.lpdinput->CreateDevice(GUID_SysKeyboard, &lpdikey, NULL)))
	{
		Get_DInput_Error(gbuffer, gresult);
		throw MyException("create dikey failed");
	}

	if(FAILED(gresult = lpdikey->SetDataFormat(&c_dfDIKeyboard)))
	{
		Get_DInput_Error(gbuffer, gresult);
		throw MyException("set dikey data format failed");
	}

	m_dikey.lpdikey = lpdikey;
	m_state = t3dKeyStatePtr(new t3dKeyState);
}

t3dKey::~t3dKey()
{
	Destroy_DIKey(&m_dikey);
}

void t3dKey::set_coop_level(coop_level_type type, MyWindowBasePtr wnd)
{
	if(FAILED(gresult = m_dikey.lpdikey->SetCooperativeLevel(
			wnd->get_hwnd(), type)))
	{
		Get_DInput_Error(gbuffer, gresult);
		throw MyException("set dikey cooperative level failed");
	}

	if(FAILED(gresult = m_dikey.lpdikey->Acquire()))
	{
		Get_DInput_Error(gbuffer, gresult);
		throw MyException("acquire dikey failed");
	}
}

t3dKeyStatePtr t3dKey::get_state(void)
{
	if(!Read_DIKey_State(&m_dikey, &m_state->m_dikeystate))
		throw MyException("read dikey state failed");

	return m_state;
}

// ============================================================================
// t3dDInput
// ============================================================================

t3dDInput::t3dDInput()
{
	INIT_ZERO(m_dinput);
	if(!Create_DInput(&m_dinput, ::GetModuleHandle(NULL)))
		throw MyException("create dinput failed");
}

t3dDInput::~t3dDInput()
{
	Destroy_DInput(&m_dinput);
}

t3dMousePtr t3dDInput::create_mouse(void)
{
	return t3dMousePtr(new t3dMouse(this));
}

t3dKeyPtr t3dDInput::create_key(void)
{
	return t3dKeyPtr(new t3dKey(this));
}

// ============================================================================
// t3dWav
// ============================================================================

t3dWav::t3dWav(t3dDSound * dsound)
{
	INIT_ZERO(m_dsbuffer);
	m_pds = dsound;
}

t3dWav::~t3dWav()
{
	Destroy_DSBuffer(&m_dsbuffer);
}

void t3dWav::load(const std::string f_name)
{
	WAVV1 wav;
	INIT_ZERO(wav);
	if(!Create_Wav_From_File(&wav, f_name.c_str()))
		throw MyException("load wav failed");

	if(!Create_DSBuffer_From_Wav(&m_pds->m_dsound, &m_dsbuffer, &wav))
	{
		Destroy_Wav(&wav);
		throw MyException("create dsbuffer failed");
	}

	Destroy_Wav(&wav);
}

void t3dWav::play(void)
{
	if(!Play_DSBuffer(&m_dsbuffer))
		throw MyException("play dsbuffer failed");
}

void t3dWav::stop(void)
{
	if(!Stop_DSBuffer(&m_dsbuffer))
		throw MyException("stop dsbuffer failed");
}

void t3dWav::set_volumn(const long volumn)
{
	if(!Set_DSBuffer_Volume(&m_dsbuffer, volumn))
		throw MyException("set dsbuffer volumn failed");
}

// ============================================================================
// t3dMidi
// ============================================================================

t3dMidiPerf::t3dMidiPerf(t3dDSound * dsound, MyWindowBasePtr wnd)
{
	INIT_ZERO(m_dmperf);
	if(!Create_DMPerformance(&dsound->m_dsound, &m_dmperf, wnd->get_hwnd()))
		throw MyException("create dmperf failed");
}

t3dMidiPerf::~t3dMidiPerf()
{
	Destroy_DMPerformance(&m_dmperf);
}

t3dMidiLoader::t3dMidiLoader()
{
	INIT_ZERO(m_dmloader);
	if(!Create_DMLoader(&m_dmloader))
		throw MyException("create dmloader failed");
}

t3dMidiLoader::~t3dMidiLoader()
{
	Destroy_DMLoader(&m_dmloader);
}

t3dMidi::t3dMidi(t3dDSound * dsound, MyWindowBasePtr wnd)
{
	INIT_ZERO(m_dmsegment);

	if(m_perf == NULL)
	{
		m_perf = t3dMidiPerfPtr(new t3dMidiPerf(dsound, wnd));
	}

	if(m_loader == NULL)
	{
		m_loader = t3dMidiLoaderPtr(new t3dMidiLoader);
	}
}

t3dMidiPerfPtr t3dMidi::m_perf;

t3dMidiLoaderPtr t3dMidi::m_loader;

t3dMidi::~t3dMidi()
{
	Destroy_DMSegment(&m_dmsegment);
}

void t3dMidi::load(const std::string f_name)
{
	if(!Create_DMSegment_From_Midi_File(
			&m_loader->m_dmloader, &m_dmsegment, f_name.c_str(), &m_perf->m_dmperf))
		throw MyException("load midi segment failed");
}

void t3dMidi::play(void)
{
	if(!Play_DMSegment(&m_perf->m_dmperf, &m_dmsegment))
		throw MyException("play midi segment failed");
}

void t3dMidi::stop(void)
{
	if(!Stop_DMSegment(&m_perf->m_dmperf, &m_dmsegment))
		throw MyException("stop midi segment failed");
}

// ============================================================================
// t3dDSound
// ============================================================================

t3dDSound::t3dDSound()
{
	INIT_ZERO(m_dsound);
	LPDIRECTSOUND8 lpds = NULL;
	if(FAILED(gresult = DirectSoundCreate8(NULL, &lpds, NULL)))
	{
		Get_DSound_Error(gbuffer, gresult);
		throw MyException("create dsound failed");
	}

	m_dsound.lpdsound = lpds;
}

t3dDSound::~t3dDSound()
{
	Destroy_DSound(&m_dsound);
}

void t3dDSound::set_coop_level(coop_level_type type, MyWindowBasePtr wnd)
{
	if(FAILED(gresult = m_dsound.lpdsound->SetCooperativeLevel(wnd->get_hwnd(), type)))
	{
		Get_DSound_Error(gbuffer, gresult);
		throw MyException("set dsound cooperative level failed");
	}
}

t3dWavPtr t3dDSound::create_wav(void)
{
	return t3dWavPtr(new t3dWav(this));
}

t3dMidiPtr t3dDSound::create_midi(MyWindowBasePtr wnd)
{
	return t3dMidiPtr(new t3dMidi(this, wnd));
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

	t3dMaterialPtr mat = t3dMaterialPtr(new t3dMaterial);
	mat->m_material.c_ambi = Create_RGBI(255, 255, 255);
	mat->m_material.c_diff = Create_RGBI(255, 255, 255);

	assert(g_materialMap.end() == g_materialMap.find(t3dMaterial::default_name));
	g_materialMap[t3dMaterial::default_name] = mat;
}

// ============================================================================
// t3dFPS
// ============================================================================

const unsigned int t3dFPS::interval_time = 1000;

const REAL t3dFPS::max_fps = 100;

const REAL t3dFPS::min_fps = 25;

t3dFPS::t3dFPS()
#ifdef _DEBUG
	: m_tqueue(30 + 1)
#else
	: m_tqueue(60 + 1)
#endif
{
	curr_time = 0;
	last_time = 0;
	pass_time = 0;
	pass_frames = 0;
	fps = 0;
	tpf = 0;
	tpf_s = 0;
}

t3dFPS::~t3dFPS()
{
}

void t3dFPS::init(void)
{
	last_time = ::timeGetTime();
	pass_frames = 0;

	m_tqueue.push_head(last_time);
}

void t3dFPS::OnFrame(void)
{
	pass_frames++;

	curr_time = ::timeGetTime();
	pass_time += curr_time - last_time;
	last_time = curr_time;

	m_tqueue.push_head(curr_time);

	update_FPS();

	update_TPF();
}

void t3dFPS::update_FPS(void)
{
	if(pass_time >= interval_time)
	{
		fps = (REAL)pass_frames / (REAL)pass_time * 1000;
		pass_time = 0;
		pass_frames = 0;
	}
}

void t3dFPS::update_TPF(void)
{
	if(m_tqueue.head() == m_tqueue.rear_B())
	{
		tpf = (*m_tqueue.head() - *m_tqueue.rear()) / (REAL)1000 / (REAL)m_tqueue.size();

		tpf_s = (1 / min_fps < tpf) ? (1 / max_fps) : tpf;
	}
}

REAL t3dFPS::get_FPS(void)
{
	return fps;
}

REAL t3dFPS::get_TPF(void)
{
	return tpf;
}

REAL t3dFPS::get_TPF_SAFE(void)
{
	return tpf_s;
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

	obj->draw_SELF(this);
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
		{
			Destroy_MsModel(&model);
			throw MyException(std::string("cannot read mesh " + mesh_name));
		}
	}
	else
	{
		if(0 >= model.nNumMeshes)
		{
			Destroy_MsModel(&model);
			throw MyException(std::string("no mesh in this file " + file_name));
		}

		//if(!Create_Object4D_From_MsMesh(&m_object, &model.pMeshes[0]))
		//	throw MyException(std::string("read first mesh from " + file_name + " failed"));

		//if(0 <= model.pMeshes[0].nMaterialIndex && model.nNumMaterials > model.pMeshes[0].nMaterialIndex)
		//	strcpy(m_object.material_name, model.pMaterials[model.pMeshes[0].nMaterialIndex].szName);

		if(!Create_Object4D_From_MsModel_By_Name(&m_object, &model, model.pMeshes[0].szName))
		{
			Destroy_MsModel(&model);
			throw MyException(std::string("read first mesh from " + file_name + " failed"));
		}
	}

	if(strlen(m_object.material_name) > 0)
	{
		assert(strcmp(m_object.material_name, t3dMaterial::default_name.c_str()) != 0);
		if(g_materialMap.end() == g_materialMap.find(m_object.material_name))
		{
			t3dMaterialPtr material = t3dMaterialPtr(new t3dMaterial);
			try
			{
				material->load(model, m_object.material_name);
			}
			catch(std::exception & e)
			{
				Destroy_MsModel(&model);
				throw e;
			}
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

/*
 * return:
 * make the special cos theta invalid, such as [-1, 1]
 */
static inline REAL make_cos_theta_invalid(REAL theta)
{
	if(theta > 1)
	{
		assert(theta <  (1 + EPSILON_E6));
		return 1;
	}

	if(theta < -1)
	{
		assert(theta > -(1 + EPSILON_E6));
		return -1;
	}

	return theta;
}

/*
 * return:
 * if the intersection point vint is inside the triangle
 */
static inline bool is_inside_triangle(const VECTOR4D & v0,
									 const VECTOR4D & v1,
									 const VECTOR4D & v2,
									 const VECTOR4D & vint)
{
	VECTOR4D dir1, dir2;
	REAL angle = 0;

	// Note: acos(-1.0000001) == -1.#IND000

	angle += acos(make_cos_theta_invalid(VECTOR3D_CosTheta(
					VECTOR3D_Sub(&dir1._3D, &v0._3D, &vint._3D),
					VECTOR3D_Sub(&dir2._3D, &v1._3D, &vint._3D))));

	angle += acos(make_cos_theta_invalid(VECTOR3D_CosTheta(
					VECTOR3D_Sub(&dir1._3D, &v1._3D, &vint._3D),
					VECTOR3D_Sub(&dir2._3D, &v2._3D, &vint._3D))));

	angle += acos(make_cos_theta_invalid(VECTOR3D_CosTheta(
					VECTOR3D_Sub(&dir1._3D, &v2._3D, &vint._3D),
					VECTOR3D_Sub(&dir2._3D, &v0._3D, &vint._3D))));

	// DEG_TO_RAD(360)	== 6.2831855
	// DEG_TO_RAD(1)	== 0.017453294
	// angle			== 6.2828398 || -1.#IND000

	assert(!_isnan(angle));

	return angle >= (DEG_TO_RAD(360) - DEG_TO_RAD(1)); // !!!
	//return angle >= 2 * PI * 0.999; // !!!
}

/*
 * return value:
 * vres - the reaction velocity of this collision test
 */
static inline bool TRIANGLE_Inside_Test(VECTOR4D & vres,
									const VECTOR4D & v0,
									const VECTOR4D & v1,
									const VECTOR4D & v2,
									const VECTOR4D & sphere_center,
									const REAL sphere_radius)
{
	assert(sphere_radius > 0);

	VECTOR4D dir1, dir2;
	VECTOR4D p_nor;
	VECTOR3D_Cross(&p_nor._3D,
					VECTOR3D_Sub(&dir1._3D, &v1._3D, &v0._3D),
					VECTOR3D_Sub(&dir2._3D, &v2._3D, &v0._3D));

	VECTOR4D l_dir;
	VECTOR3D_Mul(&l_dir._3D, &p_nor._3D, -1);

	REAL t = line_intersection(&l_dir, &sphere_center, &p_nor, &v0);

	VECTOR4D l_inc;
	REAL distance = VECTOR3D_Length(VECTOR3D_Mul(&l_inc._3D, &l_dir._3D, t));

	/*
	 * if t < 0, then the sphere center was at this planes back, in some case, fix this velocity
	 * was no meanfull, because if the raduis is 3, the speed is 4, the sphere center move back
	 * of one triangle plane, but, if the speed have 2 axis move, both is 4, the speed actually
	 * is sqrt( 4 * 4 + 4 * 4 ), it will move both triangle back, this collision test is non-effect
	 */
	if(t > 0 && distance < sphere_radius)
	{
		VECTOR3D_Add(&vres._3D, &sphere_center._3D, &l_inc._3D);

		if(is_inside_triangle(v0, v1, v2, vres))
		{
			return true;
		}
	}
	return false;
}

/*
 * return:
 * get the nearest point between sphere_center and line v0, v1
 */
static inline bool get_near_intersection(VECTOR4D & vres,
									const VECTOR4D & v0,
									const VECTOR4D & v1,
									const VECTOR4D & sphere_center)
{
	VECTOR4D dir1, dir2;

	REAL len1 = VECTOR3D_Dot(
					VECTOR3D_Sub(&dir1._3D, &sphere_center._3D, &v0._3D),
					VECTOR3D_Sub(&dir2._3D, &v1._3D, &v0._3D));

	REAL len2 = VECTOR3D_Length(&dir2._3D);

	len1 /= len2;

	if(len1 <= 0)
	{
		VECTOR4D_Copy(&vres, &v0);
		return false;
	}
	else if(len1 >= len2)
	{
		VECTOR4D_Copy(&vres, &v1);
		return false;
	}
	else
	{
		VECTOR3D_Add(&vres._3D, &v0._3D, VECTOR3D_Mul(&dir2._3D, len1 / len2));
		vres.w = 1;
		return true;
	}
}

/*
 * return:
 * if the sphere is cross the edge, return its intersection
 */
static inline bool TRIANGLE_Edge_Test(VECTOR4D & vres,
									const VECTOR4D & v0,
									const VECTOR4D & v1,
									const VECTOR4D & v2,
									const VECTOR4D & sphere_center,
									const REAL sphere_radius)
{
	VECTOR4D res_s[3];
	REAL len_s[3] = {sphere_radius + 100, sphere_radius + 100, sphere_radius + 100};

	VECTOR4D vdir;
	if(get_near_intersection(res_s[0], v0, v1, sphere_center))
	{
		len_s[0] = VECTOR3D_Length(VECTOR3D_Sub(&vdir._3D, &res_s[0]._3D, &sphere_center._3D));
	}

	if(get_near_intersection(res_s[1], v1, v2, sphere_center))
	{
		len_s[1] = VECTOR3D_Length(VECTOR3D_Sub(&vdir._3D, &res_s[1]._3D, &sphere_center._3D));
	}

	if(get_near_intersection(res_s[2], v2, v0, sphere_center))
	{
		len_s[2] = VECTOR3D_Length(VECTOR3D_Sub(&vdir._3D, &res_s[2]._3D, &sphere_center._3D));
	}

	size_t i;
	i = len_s[0] < len_s[1] ? 0 : 1;
	i = len_s[i] < len_s[2] ? i : 2;

	if(len_s[i] < sphere_radius)
	{
		VECTOR4D_Copy(&vres, &res_s[i]);
		return true;
	}
	return false;
}

/*
 * return value:
 * vres - the new center of sphere, witch is recommanded
 */
bool t3dObject::collision_test(VECTOR4D & vres, const VECTOR4D & sphere_center, const REAL sphere_radius)
{
	assert(&vres != &sphere_center);
	VECTOR4D_Copy(&vres, &sphere_center);

#define COLLISION_UNKNOWN	0
#define COLLISION_EDGE		1

	std::vector<int> collision_type(m_object.tri_list.length, COLLISION_UNKNOWN);
	bool bres = false;
	for(size_t i = 0; i < m_object.tri_list.length; i++)
	{
		assert(m_object.tri_list.elems[i].v0_i < (int)m_object.ver_list_t.length);
		assert(m_object.tri_list.elems[i].v1_i < (int)m_object.ver_list_t.length);
		assert(m_object.tri_list.elems[i].v2_i < (int)m_object.ver_list_t.length);

		VERTEXV1T & v0 = m_object.ver_list_t.elems[m_object.tri_list.elems[i].v0_i];
		VERTEXV1T & v1 = m_object.ver_list_t.elems[m_object.tri_list.elems[i].v1_i];
		VERTEXV1T & v2 = m_object.ver_list_t.elems[m_object.tri_list.elems[i].v2_i];

		if(	max(max(v0.x, v1.x), v2.x) < vres.x - sphere_radius
			|| max(max(v0.y, v1.y), v2.y) < vres.y - sphere_radius
			|| max(max(v0.z, v1.z), v2.z) < vres.z - sphere_radius)
		{
			continue;
		}

		if(	min(min(v0.x, v1.x), v2.x) > vres.x + sphere_radius
			|| min(min(v0.y, v1.y), v2.y) > vres.y + sphere_radius
			|| min(min(v0.z, v1.z), v2.z) > vres.z + sphere_radius)
		{
			continue;
		}

		VECTOR4D vint;
		if(TRIANGLE_Inside_Test(vint, v0._4D, v1._4D, v2._4D, vres, sphere_radius))
		{
			/*
			 * vres = vint + (vres - vint) * radius / |vres - vint|
			 */
			VECTOR4D vtmp;
			VECTOR3D_Sub(&vtmp._3D, &vres._3D, &vint._3D);
			VECTOR3D_Add(&vres._3D, &vint._3D, VECTOR3D_Mul(&vtmp._3D, sphere_radius / VECTOR3D_Length(&vtmp._3D)));

			bres = true;
		}
		else
		{
			collision_type[i] = COLLISION_EDGE;
		}
	}

	for(size_t i = 0; i < m_object.tri_list.length; i++)
	{
		if(COLLISION_EDGE != collision_type[i])
		{
			continue;
		}

		VERTEXV1T & v0 = m_object.ver_list_t.elems[m_object.tri_list.elems[i].v0_i];
		VERTEXV1T & v1 = m_object.ver_list_t.elems[m_object.tri_list.elems[i].v1_i];
		VERTEXV1T & v2 = m_object.ver_list_t.elems[m_object.tri_list.elems[i].v2_i];

		VECTOR4D vint;
		if(TRIANGLE_Edge_Test(vint, v0._4D, v1._4D, v2._4D, vres, sphere_radius))
		{
			/*
			 * vres = vint + (vres - vint) * radius / |vres - vint|
			 */
			VECTOR4D vtmp;
			VECTOR3D_Sub(&vtmp._3D, &vres._3D, &vint._3D);
			VECTOR3D_Add(&vres._3D, &vint._3D, VECTOR3D_Mul(&vtmp._3D, sphere_radius / VECTOR3D_Length(&vtmp._3D)));

			bres = true;
		}
	}
	return bres;
}

void t3dObject::reset(void)
{
	Reset_Object4D(&m_object);
}

void t3dObject::to_WORLD(VECTOR4D & pos, VECTOR4D & rot)
{
	Model_To_World_Object4D(&m_object, &pos, &rot, TRANSFORM_MODE_LOCAL_TO_TRANS);
}

void t3dObjectWire::draw_SELF(t3dRender * render)
{
	assert(NULL != Clip_Object4D);
	assert(NULL != Clip_Object4D_Gouraud_Texture);

	{
		Remove_Object4D_Backface_At_World(&m_object, &render->m_cam->m_camera);

		t3dLightAmbient light(Create_RGBI(255, 255, 255));
		light.light(this, m_material);

		World_To_Camera_Object4D(&m_object, &render->m_cam->m_camera);

		if(!Clip_Object4D(&m_object, &render->m_cam->m_camera))
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

void t3dObjectFlat::draw_SELF(t3dRender * render)
{
	assert(NULL != Clip_Object4D);
	assert(NULL != Clip_Object4D_Gouraud_Texture);

	if(NULL != m_material->m_material.texture.pbuffer)
	{
		Remove_Object4D_Backface_At_World(&m_object, &render->m_cam->m_camera);

		//std::map<std::string, t3dLightPtr>::const_iterator l_iter;
		//for(l_iter = render->m_lightMap.begin(); l_iter != render->m_lightMap.end(); l_iter++)
		//{
		//	l_iter->second->light(this, m_material);
		//}

		World_To_Camera_Object4D(&m_object, &render->m_cam->m_camera);

		if(!Clip_Object4D_Gouraud_Texture(&m_object, &render->m_cam->m_camera))
			throw MyException("clip object failed");

		Camera_To_Perspective_Object4D(&m_object, &render->m_cam->m_camera);

		Perspective_To_Screen_Object4D(&m_object, &render->m_cam->m_camera);

		SURFACEV1 surf = render->m_surf->lock();
		render->m_cam->m_camera.psurf = &surf;
		render->m_cam->m_camera.pzbuf = &render->m_zbuf->m_zbuffer;
		{
			Draw_Object4D_Texture_ZBufferRW(&m_object, &render->m_cam->m_camera, &m_material->m_material);
		}
		render->m_surf->unlock();
	}
	else
	{
		Remove_Object4D_Backface_At_World(&m_object, &render->m_cam->m_camera);

		std::map<std::string, t3dLightPtr>::const_iterator l_iter;
		for(l_iter = render->m_lightMap.begin(); l_iter != render->m_lightMap.end(); l_iter++)
		{
			l_iter->second->light(this, m_material);
		}

		World_To_Camera_Object4D(&m_object, &render->m_cam->m_camera);

		if(!Clip_Object4D(&m_object, &render->m_cam->m_camera))
			throw MyException("clip object failed");

		Camera_To_Perspective_Object4D(&m_object, &render->m_cam->m_camera);

		Perspective_To_Screen_Object4D(&m_object, &render->m_cam->m_camera);

		SURFACEV1 surf = render->m_surf->lock();
		render->m_cam->m_camera.psurf = &surf;
		render->m_cam->m_camera.pzbuf = &render->m_zbuf->m_zbuffer;
		{
			Draw_Object4D_ZBufferRW(&m_object, &render->m_cam->m_camera);
		}
		render->m_surf->unlock();
	}
}

void t3dObjectFlatPerspectiveLP::draw_SELF(t3dRender * render)
{
	assert(NULL != Clip_Object4D);
	assert(NULL != Clip_Object4D_Gouraud_Texture);

	if(NULL != m_material->m_material.texture.pbuffer)
	{
		Remove_Object4D_Backface_At_World(&m_object, &render->m_cam->m_camera);

		//std::map<std::string, t3dLightPtr>::const_iterator l_iter;
		//for(l_iter = render->m_lightMap.begin(); l_iter != render->m_lightMap.end(); l_iter++)
		//{
		//	l_iter->second->light(this, m_material);
		//}

		World_To_Camera_Object4D(&m_object, &render->m_cam->m_camera);

		if(!Clip_Object4D_Gouraud_Texture(&m_object, &render->m_cam->m_camera))
			throw MyException("clip object failed");

		Camera_To_Perspective_Object4D(&m_object, &render->m_cam->m_camera);

		Perspective_To_Screen_Object4D(&m_object, &render->m_cam->m_camera);

		SURFACEV1 surf = render->m_surf->lock();
		render->m_cam->m_camera.psurf = &surf;
		render->m_cam->m_camera.pzbuf = &render->m_zbuf->m_zbuffer;
		{
			Draw_Object4D_Texture_PerspectiveLP_ZBufferRW(&m_object, &render->m_cam->m_camera, &m_material->m_material);
		}
		render->m_surf->unlock();
	}
	else
	{
		t3dObjectFlat::draw_SELF(render);
	}
}

void t3dObjectGouraud::draw_SELF(t3dRender * render)
{
	assert(NULL != Clip_Object4D);
	assert(NULL != Clip_Object4D_Gouraud_Texture);

	if(NULL != m_material->m_material.texture.pbuffer)
	{
		Remove_Object4D_Backface_At_World(&m_object, &render->m_cam->m_camera);

		std::map<std::string, t3dLightPtr>::const_iterator l_iter;
		for(l_iter = render->m_lightMap.begin(); l_iter != render->m_lightMap.end(); l_iter++)
		{
			l_iter->second->light(this, m_material);
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
			Draw_Object4D_Gouraud_Texture_ZBufferRW(&m_object, &render->m_cam->m_camera, &m_material->m_material);
		}
		render->m_surf->unlock();
	}
	else
	{
		Remove_Object4D_Backface_At_World(&m_object, &render->m_cam->m_camera);

		std::map<std::string, t3dLightPtr>::const_iterator l_iter;
		for(l_iter = render->m_lightMap.begin(); l_iter != render->m_lightMap.end(); l_iter++)
		{
			l_iter->second->light(this, m_material);
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
			Draw_Object4D_Gouraud_ZBufferRW(&m_object, &render->m_cam->m_camera);
		}
		render->m_surf->unlock();
	}
}
//
//void t3dObjectGouraudPerspectiveLP::draw_SELF(t3dRender * render)
//{
//	assert(false);
//
//	UNREFERENCED_PARAMETER(render);
//}

// ============================================================================
// MyConfigBase
// ============================================================================

MyConfigBase::MyConfigBase()
{
}

MyConfigBase::~MyConfigBase()
{
}

MyConfigBase::screen_mode_type MyConfigBase::get_screen_mode(void)
{
	return MyConfigBase::windowed;
}

int MyConfigBase::get_screen_width(void)
{
	return 800;
}

int MyConfigBase::get_screen_height(void)
{
	return 600;
}

int MyConfigBase::get_screen_bpp(void)
{
	return 32;
}

// ============================================================================
// MyGameBase
// ============================================================================

MyGameBase::MyGameBase()
{
}

MyGameBase::~MyGameBase()
{
}

int MyGameBase::run(void)
{
	MyConfigPtr config = init_CFG();
	assert(config != NULL);
	RECT rect = {0, 0, config->get_screen_width(), config->get_screen_height()};

	m_wnd = init_WND();
	g_msgArr->addWindow(m_wnd);
	m_wnd->SetClientRect(rect);

	m_ddraw = t3dDDrawPtr(new t3dDDraw);
	if(config->get_screen_mode() == MyConfig::fullscreen)
	{
		m_wnd->SetWindowStyle(WS_POPUP | WS_VISIBLE);
		if(0 == ::SetWindowPos(m_wnd->get_hwnd(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED))
			throw MyException("set window top most failed");

		m_ddraw->set_coop_level(t3dDDraw::fullscreen, m_wnd);
		m_ddraw->set_display_mode(
						config->get_screen_width(),
						config->get_screen_height(),
						config->get_screen_bpp());
	}
	else
	{
		m_wnd->CenterWindow();

		m_ddraw->set_coop_level(t3dDDraw::normal, m_wnd);
	}

	DDSURFACEDESC2 ddsd;
	INIT_ZERO(ddsd);
	ddsd.dwSize = sizeof(ddsd);

	if(FAILED(gresult = m_ddraw->m_ddraw.lpddraw->GetDisplayMode(&ddsd)))
	{
		Set_Last_Error(Get_DDraw_Error(gbuffer, gresult), __FILE__, __LINE__);
		throw MyException("get display mode failed");
	}

	if(16 != ddsd.ddpfPixelFormat.dwRGBBitCount && 32 != ddsd.ddpfPixelFormat.dwRGBBitCount)
	{
		if(config->get_screen_mode() == MyConfig::fullscreen)
		{
			m_ddraw->m_ddraw.lpddraw->RestoreDisplayMode();
		}
		throw MyException("unsupported screen bpp");
	}

	t3d_INIT(ddsd.ddpfPixelFormat.dwRGBBitCount);
	init();

	m_wnd->ShowWindow();
	return MyApplication::run();
}

void MyGameBase::OnIdle(void)
{
	OnFrame();
}

// ============================================================================
// MyConfig
// ============================================================================

MyConfig::MyConfig(std::string app_name)
	: m_mode(MyConfigBase::windowed), m_width(800), m_height(600), m_bpp(32)
{
	char buffer[MAX_BUFFER_SIZE];
	if(0 == GetCurrentDirectoryA(MAX_BUFFER_SIZE, buffer))
		throw MyException("get config file dir failed");

	std::string f_path(buffer);
	f_path += "\\config.ini";

	if(GetPrivateProfileInt(app_name.c_str(), "fullscreen", 0, f_path.c_str()))
		m_mode	= MyConfigBase::fullscreen;
	else
		m_mode	= MyConfigBase::windowed;
	m_width		= GetPrivateProfileInt(app_name.c_str(), "width", m_width, f_path.c_str());
	m_height	= GetPrivateProfileInt(app_name.c_str(), "height", m_height, f_path.c_str());
	m_bpp		= GetPrivateProfileInt(app_name.c_str(), "bpp", m_bpp, f_path.c_str());
}

MyConfig::~MyConfig()
{
}

MyConfigBase::screen_mode_type MyConfig::get_screen_mode(void)
{
	return m_mode;
}

int MyConfig::get_screen_width(void)
{
	return m_width;
}

int MyConfig::get_screen_height(void)
{
	return m_height;
}

int MyConfig::get_screen_bpp(void)
{
	return m_bpp;
}

// ============================================================================
// MyGame
// ============================================================================

MyGame::MyGame(std::string appName /*= "My_Game"*/)
	: m_appName(appName)
{
}

MyGame::~MyGame()
{
}

MyConfigPtr MyGame::init_CFG(void)
{
	return m_config = MyConfigPtr(new MyConfig(m_appName));
}

void MyGame::init(void)
{
	m_wnd->SetWindowText(m_appName);

	m_prim = m_ddraw->create_screen_surface();
	m_prim->set_clipper(m_ddraw->create_screen_clipper(m_wnd));

	m_back = m_ddraw->create_memory_surface(
			m_config->get_screen_width(), m_config->get_screen_height());
	m_back->set_clipper(m_ddraw->create_single_clipper(m_back->m_ddsurface.rect));

	m_zbuf = t3dZbufferPtr(new t3dZbuffer(
			m_config->get_screen_width(), m_config->get_screen_height()));

	m_dinput = t3dDInputPtr(new t3dDInput);

	m_key = m_dinput->create_key();
	m_key->set_coop_level(t3dKey::background, m_wnd);

	m_mouse = m_dinput->create_mouse();
	m_mouse->set_coop_level(t3dMouse::background, m_wnd);

	m_dsound = t3dDSoundPtr(new t3dDSound);
	m_dsound->set_coop_level(t3dDSound::normal, m_wnd);

	do_INIT();

	m_fps = t3dFPSPtr(new t3dFPS);
	m_fps->init();
}

void MyGame::OnFrame(void)
{
	m_fps->OnFrame();

	do_DRAW();

	m_prim->blit(m_wnd->GetClientRect(), m_back, m_back->m_ddsurface.rect);
}

// ============================================================================
// FPSGameCamera
// ============================================================================

FPSGameCamera::FPSGameCamera(RECT rect)
	: t3dCameraEuler(rect)
{
}

FPSGameCamera::~FPSGameCamera()
{
}

VECTOR4D & FPSGameCamera::mov_scale(VECTOR4D & vres, t3dKeyStatePtr k_state)
{
	VECTOR4D_InitXYZ(&vres, 0, 0, 0);

	if(k_state->is_key_down(DIK_W) || k_state->is_key_down(DIK_UP))
	{
		vres.x =  sin(m_camera.vrot.y);
		vres.z =  cos(m_camera.vrot.y);
	}

	if(k_state->is_key_down(DIK_S) || k_state->is_key_down(DIK_DOWN))
	{
		vres.x = -sin(m_camera.vrot.y);
		vres.z = -cos(m_camera.vrot.y);
	}

	if(k_state->is_key_down(DIK_A) || k_state->is_key_down(DIK_LEFT))
	{
		vres.x = -cos(m_camera.vrot.y);
		vres.z =  sin(m_camera.vrot.y);
	}

	if(k_state->is_key_down(DIK_D) || k_state->is_key_down(DIK_RIGHT))
	{
		vres.x =  cos(m_camera.vrot.y);
		vres.z = -sin(m_camera.vrot.y);
	}

	return vres;
}

VECTOR4D & FPSGameCamera::rot_scale(VECTOR4D & vres, t3dMouseStatePtr m_state)
{
	VECTOR4D_InitXYZ(&vres,
			DEG_TO_RAD(m_state->get_Y()) * (REAL)0.1, DEG_TO_RAD(m_state->get_X()) * (REAL)0.1, 0 /*(REAL)m_state->get_Z()*/);

	return vres;
}
