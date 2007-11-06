/*
 * File: demo1_3/main.cpp
 */

// ////////////////////////////////////////////////////////////////////////////////////
// INCLUDES
// ////////////////////////////////////////////////////////////////////////////////////

#include "t3dPrecompiledHeader.h"
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
#include "MyGame.h"
#pragma comment(lib, "winmm.lib")

// ////////////////////////////////////////////////////////////////////////////////////
// CLASSES
// ////////////////////////////////////////////////////////////////////////////////////

class DemoWindow : public MyWindow
{
protected:
	virtual LRESULT OnProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
	{
		return ::DefWindowProc(hwnd, message, wparam, lparam);
	}
};

class DemoApplication : public MyApplication
{
public:
	virtual int run(void)
	{
		rect.left = 0;
		rect.top = 0;
		rect.right = 800;
		rect.bottom = 600;

		wnd = MyWindowPtr(new DemoWindow);
		g_msgArr->addWindow(wnd);

		wnd->SetWindowText("demo1_3");
		wnd->SetClientRect(rect);
		wnd->CenterWindow();

		ddraw = t3dDDrawPtr(new t3dDDraw);

		ddraw->set_coop_level(t3dDDraw::normal);

		prim = ddraw->create_screen_surface();
		prim->set_clipper(ddraw->create_screen_clipper(wnd));

		back = ddraw->create_memory_surface(MyWindow::GetRectWidth(rect), MyWindow::GetRectHeight(rect));
		back->set_clipper(ddraw->create_single_clipper(rect));

		dinput = t3dDInputPtr(new t3dDInput);

		key = dinput->create_key();
		key->set_coop_level(t3dKey::background, wnd);

		t3d_INIT(prim->get_BPP());

		//obj.load("Box1_2.ms3d.txt", "Box01");

		obj.load("jack.ms3d.txt");

		obj2.load("ct.ms3d.txt", "Sphere01");

		for(size_t i = 0; i < obj2.m_object.ver_list.length; i++)
		{
			VECTOR3D_Mul(&obj2.m_object.ver_list.elems[i]._3D, 0.2f);
		}

		obj3.load("ct.ms3d.txt", "Box01");

		for(size_t i = 0; i < obj3.m_object.ver_list.length; i++)
		{
			VECTOR3D_Mul(&obj3.m_object.ver_list.elems[i]._3D, 0.5f);
		}

		obj3.m_material = g_materialMap[t3dMaterial::default_name];

		wnd->ShowWindow();

		//dsound.set_coop_level(t3dDSound::normal, wnd);
		//wav1 = dsound.create_wav();
		//wav1->load("engines.wav");

		fps.init();

		return MyApplication::run();
	}

	virtual void OnIdle(void)
	{
		static VECTOR4D c_pos = {0, 0, -80, 1};
		static VECTOR4D c_rot = {DEG_TO_RAD((REAL)0), 0, 0, 1};
		static VECTOR4D o_emp = {0, 0, 0, 1};
		static VECTOR4D l_pos = {-20, 20, -20, 1};
		//static VECTOR4D sphere_pos = {18, 18, 18, 1};
		static VECTOR4D sphere_pos = {0, 0, 0, 1};

		fps.OnFrame();

		REAL cam_mov_speed = fps.get_TPF_SAFE() * 100;
		REAL cam_rot_speed = fps.get_TPF_SAFE() * 100;

		t3dKeyStatePtr ks = key->get_state();

		if(ks->is_key_down(DIK_ESCAPE))
			::PostMessage(wnd->get_hwnd(), WM_CLOSE, NULL, NULL);

		if(ks->is_key_down(DIK_R))
		{
			VECTOR4D_InitXYZ(&c_pos, 0, 0, -80);
			VECTOR4D_InitXYZ(&c_rot, 0, 0, 0);
			VECTOR4D_InitXYZ(&sphere_pos, 0, 0, 0);
		}

		if(ks->is_key_down(DIK_W))
		{
			c_rot.x -= cam_rot_speed * DEG_TO_RAD((REAL)2);
		}

		if(ks->is_key_down(DIK_S))
		{
			c_rot.x += cam_rot_speed * DEG_TO_RAD((REAL)2);
		}

		if(ks->is_key_down(DIK_A))
		{
			c_rot.z += cam_rot_speed * DEG_TO_RAD((REAL)2);
		}

		if(ks->is_key_down(DIK_D))
		{
			c_rot.z -= cam_rot_speed * DEG_TO_RAD((REAL)2);
		}

		if(ks->is_key_down(DIK_LEFT))
		{
			c_rot.y -= cam_rot_speed * DEG_TO_RAD((REAL)2);
		}

		if(ks->is_key_down(DIK_RIGHT))
		{
			c_rot.y += cam_rot_speed * DEG_TO_RAD((REAL)2);
		}

		if(ks->is_key_down(DIK_UP))
		{
			c_pos.z += cam_mov_speed * cos(c_rot.y);
			c_pos.x += cam_mov_speed * sin(c_rot.y);
		}

		if(ks->is_key_down(DIK_DOWN))
		{
			c_pos.z -= cam_mov_speed * cos(c_rot.y);
			c_pos.x -= cam_mov_speed * sin(c_rot.y);
		}

		if(ks->is_key_down(DIK_HOME))
		{
			c_pos.y += cam_mov_speed;
		}

		if(ks->is_key_down(DIK_END))
		{
			c_pos.y -= cam_mov_speed;
		}

		if(ks->is_key_down(DIK_DELETE))
		{
			c_pos.x -= cam_mov_speed * cos(c_rot.y);
			c_pos.z += cam_mov_speed * sin(c_rot.y);
		}

		if(ks->is_key_down(DIK_PGDN))
		{
			c_pos.x += cam_mov_speed * cos(c_rot.y);
			c_pos.z -= cam_mov_speed * sin(c_rot.y);
		}

		if(ks->is_key_down(DIK_NUMPAD8))
		{
			sphere_pos.z += cam_mov_speed * cos(c_rot.y);
			sphere_pos.x += cam_mov_speed * sin(c_rot.y);
		}

		if(ks->is_key_down(DIK_NUMPAD5))
		{
			sphere_pos.z -= cam_mov_speed * cos(c_rot.y);
			sphere_pos.x -= cam_mov_speed * sin(c_rot.y);
		}

		if(ks->is_key_down(DIK_NUMPAD4))
		{
			sphere_pos.x -= cam_mov_speed * cos(c_rot.y);
			sphere_pos.z += cam_mov_speed * sin(c_rot.y);
		}

		if(ks->is_key_down(DIK_NUMPAD6))
		{
			sphere_pos.x += cam_mov_speed * cos(c_rot.y);
			sphere_pos.z -= cam_mov_speed * sin(c_rot.y);
		}

		if(ks->is_key_down(DIK_NUMPAD1))
		{
			sphere_pos.y += cam_mov_speed;
		}

		if(ks->is_key_down(DIK_NUMPAD3))
		{
			sphere_pos.y -= cam_mov_speed;
		}

		if(ks->is_key_down(DIK_SPACE))
		{
			//wav1->play();
		}

		back->fill(rect, Create_RGBI(128, 128, 128));

		t3dRender render;
		render.set_camera(t3dCameraPtr(new t3dCameraEuler(rect, c_pos, c_rot, DEG_TO_RAD(60), 10, 1000)));
		render.set_surface(back);
		render.set_zbuffer(t3dZbufferPtr(new t3dZbuffer(MyWindow::GetRectWidth(rect), MyWindow::GetRectHeight(rect))));

		obj.reset();
		obj.to_WORLD(o_emp, o_emp);

		obj3.reset();
		obj3.to_WORLD(o_emp, o_emp);

		VECTOR4D vres;
		if(obj3.collision_test(vres, sphere_pos, 3))
		{
			VECTOR4D_Copy(&sphere_pos, &vres);
		}

		obj2.reset();
		obj2.to_WORLD(sphere_pos, o_emp);

		render.add_light("light1", t3dLightPtr(new t3dLightAmbient(Create_RGBI(92, 92, 92))));
		render.add_light("light2", t3dLightPtr(new t3dLightPoint(Create_RGBI(255, 255, 255), l_pos)));

		render.set_material(obj.m_material);
		render.draw(&obj);

		render.set_material(obj3.m_material);
		render.draw(&obj3);

		render.set_material(obj2.m_material);
		render.draw(&obj2);

		back->text_out(str_printf("%.1f fps", fps.get_FPS()), 10, 10);

		back->text_out(str_printf("%f tpf", fps.get_TPF()), 10, 50);

		back->text_out(str_printf("%f 1/tpf", 1/fps.get_TPF()), 10, 90);

		back->text_out(str_printf("%.1f, %.1f, %.1f", vres.x, vres.y, vres.z), 10, 130);

		prim->blit(wnd->GetClientRect(), back, rect);
	}

protected:
	t3dDDrawPtr ddraw;
	t3dSurfacePtr prim;
	t3dSurfacePtr back;

	t3dDInputPtr dinput;
	t3dKeyPtr key;

	MyWindowPtr wnd;
	RECT rect;

	t3dFPS fps;
	t3dObject obj;

	t3dObject obj2;
	t3dObject obj3;

	//t3dDSound dsound;
	//t3dWavPtr wav1;
};

// ////////////////////////////////////////////////////////////////////////////////////
// WinMain
// ////////////////////////////////////////////////////////////////////////////////////

int APIENTRY WinMain(HINSTANCE	hInstance,
					 HINSTANCE	hPrevInstance,
					 LPSTR		lpCmdLine,
					 int		nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	try
	{
		DemoApplication app;
		app.run();
	}
	catch(std::exception & e)
	{
		::MessageBoxA(NULL, e.what(), "Exception!", MB_OK);
	}

	return 0;
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);
}
