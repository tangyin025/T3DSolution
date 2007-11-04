/*
 * File: MyGame.h
 */

#ifndef __MY_GAME_H__
#define __MY_GAME_H__

#include "t3dCommons.h"
#include "t3dlib1.h"
#include "t3dlib2.h"
#include "t3dlib3.h"
#include "t3dlib4.h"
#include "t3dlib5.h"
#include "t3dlib6.h"
#include "t3dlib7.h"
#include "t3dlib8.h"
#include "t3dlib9.h"
#include "MyApp.h"

// ============================================================================
// str_printf
// ============================================================================

std::string T3DLIB_API str_printf(char * format, ...);

// ============================================================================
// t3dClipper
// ============================================================================

class T3DLIB_API t3dClipper
{
	friend class t3dDDraw;

protected:
	t3dClipper(t3dDDraw * ddraw, MyWindowBasePtr wnd);

	t3dClipper(t3dDDraw * ddraw, RECT rect);

public:
	~t3dClipper();

public:
	DDCLIPPERV1 m_clipper;
};

typedef boost::shared_ptr<t3dClipper> t3dClipperPtr;

// ============================================================================
// t3dSurface
// ============================================================================

class t3dSurface;

typedef boost::shared_ptr<t3dSurface> t3dSurfacePtr;

class T3DLIB_API t3dSurface
{
protected:
	t3dSurface() throw();

public:
	virtual ~t3dSurface();

public:
	void set_clipper(t3dClipperPtr clipper);

	int get_BPP(void);

	SURFACEV1 lock(void);

	void unlock(void);

	void fill(RECT rect, unsigned int color);

	void blit(RECT rect, t3dSurfacePtr other, RECT other_rect);

	void text_out(std::string text, int x, int y);

	void text_out(std::string text, int x, int y, COLORREF color);

public:
	DDSURFACEV1 m_ddsurface;

	t3dClipperPtr m_clipper;

	TEXTDCV1 m_tdc;
};

class T3DLIB_API t3dSurfaceScreen : public t3dSurface
{
	friend class t3dDDraw;

protected:
	t3dSurfaceScreen(t3dDDraw * ddraw);
};

class T3DLIB_API t3dSurfaceMemory : public t3dSurface
{
	friend class t3dDDraw;

protected:
	t3dSurfaceMemory(t3dDDraw * ddraw, int width, int height);
};

class T3DLIB_API t3dSurfaceVideos : public t3dSurface
{
	friend class t3dDDraw;

protected:
	t3dSurfaceVideos(t3dDDraw * ddraw, int width, int height);
};

// ============================================================================
// t3dZbuffer
// ============================================================================

class T3DLIB_API t3dZbuffer
{
public:
	t3dZbuffer(int width, int height);

	~t3dZbuffer();

public:
	ZBUFFERV1 m_zbuffer;
};

typedef boost::shared_ptr<t3dZbuffer> t3dZbufferPtr;

// ============================================================================
// t3dCamera
// ============================================================================

class T3DLIB_API t3dCamera
{
protected:
	t3dCamera();

	~t3dCamera();

public:
	CAM4DV1 m_camera;
};

typedef boost::shared_ptr<t3dCamera> t3dCameraPtr;

class T3DLIB_API t3dCameraEuler : public t3dCamera
{
public:
	t3dCameraEuler(	RECT rect, const VECTOR4D & pos, const VECTOR4D & rot,
					REAL fov = DEG_TO_RAD(90),
					REAL min_clip_z = 10,
					REAL max_clip_z = 1000,
					VIEWPORT_FIX_MODE fix_mode = VIEWPORT_FIX_MODE_WIDTH,
					int rot_seq = ROTATION_SEQ_ZXY);
};

// ============================================================================
// t3dDDraw
// ============================================================================

class T3DLIB_API t3dDDraw
{
public:
	typedef enum
	{
		normal		= DDSCL_NORMAL,
		fullscreen	= DDSCL_ALLOWMODEX | DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_MULTITHREADED,

	} coop_level_type;

public:
	t3dDDraw();

	~t3dDDraw();

public:
	void set_coop_level(coop_level_type type);

	t3dSurfacePtr create_screen_surface(void);

	t3dSurfacePtr create_memory_surface(int width, int height);

	t3dSurfacePtr create_videos_surface(int width, int height);

	t3dClipperPtr create_screen_clipper(MyWindowBasePtr wnd);

	t3dClipperPtr create_single_clipper(RECT rect);

public:
	DDRAWV1 m_ddraw;
};

typedef boost::shared_ptr<t3dDDraw> t3dDDrawPtr;

// ============================================================================
// t3dMouse
// ============================================================================

class t3dDInput;

class T3DLIB_API t3dMouse
{
	friend class t3dDInput;

public:
	typedef enum
	{
		foreground	= DISCL_NONEXCLUSIVE | DISCL_FOREGROUND,
		background	= DISCL_NONEXCLUSIVE | DISCL_BACKGROUND,

	} coop_level_type;

protected:
	t3dMouse(t3dDInput * input);

public:
	~t3dMouse();

public:
	void set_coop_level(coop_level_type type, MyWindowBasePtr wnd);

protected:
	DIMOUSEV1 m_mouse;
};

typedef boost::shared_ptr<t3dMouse> t3dMousePtr;

// ============================================================================
// t3dKey
// ============================================================================

class T3DLIB_API t3dKeyState
{
public:
	t3dKeyState();

	~t3dKeyState();

public:
	unsigned char is_key_down(const DWORD key_i);

public:
	DIKEYSTATEV1 m_dikeystate;
};

typedef boost::shared_ptr<t3dKeyState> t3dKeyStatePtr;

class T3DLIB_API t3dKey
{
	friend class t3dDInput;

public:
	typedef enum
	{
		foreground	= DISCL_NONEXCLUSIVE | DISCL_FOREGROUND,
		background	= DISCL_NONEXCLUSIVE | DISCL_BACKGROUND,

	} coop_level_type;

protected:
	t3dKey(t3dDInput * input);

public:
	~t3dKey();

public:
	void set_coop_level(coop_level_type type, MyWindowBasePtr wnd);

	t3dKeyStatePtr get_state(void);

protected:
	DIKEYV1 m_dikey;

	t3dKeyStatePtr m_state;
};

typedef boost::shared_ptr<t3dKey> t3dKeyPtr;

// ============================================================================
// t3dDInput
// ============================================================================

class T3DLIB_API t3dDInput
{
public:
	t3dDInput();

	~t3dDInput();

public:
	t3dMousePtr create_mouse(void);

	t3dKeyPtr create_key(void);

public:
	DINPUTV1 m_dinput;
};

typedef boost::shared_ptr<t3dDInput> t3dDInputPtr;

// ============================================================================
// t3dWav
// ============================================================================

// ============================================================================
// t3dDSound
// ============================================================================

// ============================================================================
// t3dMidi
// ============================================================================

// ============================================================================
// t3dDMusic
// ============================================================================

// ============================================================================
// t3d_INIT( const int BPP )
// ============================================================================

void T3DLIB_API t3d_INIT( const int BPP );

// ============================================================================
// t3dFPS
// ============================================================================

class T3DLIB_API t3dFPS
{
protected:
	static const unsigned int interval_time;

public:
	t3dFPS();

	~t3dFPS();

public:
	void init(void);

	void OnFrame(void);

	REAL get_FPS(void);

protected:
	unsigned int	curr_time;
	unsigned int	last_time;
	unsigned int	pass_time;
	unsigned int	pass_frames;
	REAL			fps;
};

typedef boost::shared_ptr<t3dFPS> t3dFPSPtr;

// ============================================================================
// t3dMaterial
// ============================================================================

class T3DLIB_API t3dMaterial
{
public:
	static const std::string default_name;

public:
	t3dMaterial();

	~t3dMaterial();

public:
	void load(msModel & model, const std::string material_name = "");

public:
	MATERIALV1 m_material;
};

typedef boost::shared_ptr<t3dMaterial> t3dMaterialPtr;

// ============================================================================
// t3dLight
// ============================================================================

class t3dLight;

class T3DLIB_API t3dLightObject
{
public:
	virtual void light_SELF(t3dLight * light, t3dMaterialPtr mat) = 0;
};

class T3DLIB_API t3dLight
{
protected:
	t3dLight();

	~t3dLight();

public:
	void light(t3dLightObject * obj, t3dMaterialPtr mat);

public:
	LIGHT4DV1 m_light;
};

typedef boost::shared_ptr<t3dLight> t3dLightPtr;

class T3DLIB_API t3dLightAmbient : public t3dLight
{
public:
	t3dLightAmbient(unsigned int color);
};

class T3DLIB_API t3dLightDirect : public t3dLight
{
public:
	t3dLightDirect(unsigned int color, const VECTOR4D & pos, const VECTOR4D & dir);
};

class T3DLIB_API t3dLightPoint : public t3dLight
{
public:
	t3dLightPoint(	unsigned int color, const VECTOR4D & pos,
					REAL kc = (REAL)1.0,
					REAL kl = (REAL)0.001,
					REAL kq = (REAL)0.00001);
};

// ============================================================================
// t3dRender
// ============================================================================

class t3dRender;

class T3DLIB_API t3dRenderObject
{
public:
	virtual void draw_SELF(t3dRender * render) = 0;
};

class T3DLIB_API t3dRender
{
public:
	t3dRender();

	~t3dRender();

public:
	void draw(t3dRenderObject * obj);

	void add_light(std::string l_name, t3dLightPtr light);

	void del_light(std::string l_name);

	t3dLightPtr get_light(std::string l_name);

	void set_camera(t3dCameraPtr cam);

	void set_surface(t3dSurfacePtr surf);

	void set_zbuffer(t3dZbufferPtr zbuf);

	void set_material(t3dMaterialPtr mat);

public:
	std::map<std::string, t3dLightPtr> m_lightMap;

	t3dCameraPtr m_cam;

	t3dSurfacePtr m_surf;

	t3dZbufferPtr m_zbuf;

	t3dMaterialPtr m_mat;
};

// ============================================================================
// t3dObject
// ============================================================================

class T3DLIB_API t3dObject : public t3dLightObject, public t3dRenderObject
{
public:
	t3dObject();

	virtual ~t3dObject();

protected:
	virtual void light_SELF(t3dLight * light, t3dMaterialPtr mat);

	virtual void draw_SELF(t3dRender * render);

public:
	void load(const std::string file_name, const std::string mesh_name = "");

	void reset(void);

	void to_WORLD(VECTOR4D & pos, VECTOR4D & rot);

public:
	OBJECT4DV1 m_object;

	t3dMaterialPtr m_material;
};

#endif // __MY_GAME_H__
