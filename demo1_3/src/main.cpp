/*
 * File: demo1_3/main.cpp
 */

// ////////////////////////////////////////////////////////////////////////////////////
// INCLUDES
// ////////////////////////////////////////////////////////////////////////////////////

#include "t3dPrecompiledHeader.h"
#include "MyGame.h"

// ////////////////////////////////////////////////////////////////////////////////////
// CLASSES
// ////////////////////////////////////////////////////////////////////////////////////

// ====================================================================================
// DemoGame
// ====================================================================================

class DemoGame : public MyGame
{
public:
	DemoGame(std::string appName)
		: MyGame(appName)
	{
	}

	~DemoGame()
	{
	}

protected:
	void do_INIT(void)
	{
		RECT rect = {m_back->m_ddsurface.rect.left + 10, m_back->m_ddsurface.rect.top + 10, m_back->m_ddsurface.rect.right - 10, m_back->m_ddsurface.rect.bottom - 10};
		m_cam = FPSGameCameraPtr(new FPSGameCamera(rect));
		//m_cam->m_camera.vpos.y = 10;
		//m_cam->m_camera.vpos.z = -60;
		m_cam->set_fov(DEG_TO_RAD(60));

		//m_obj = t3dObjectPtr(new t3dObjectGouraud);
		//m_obj->load("jack.ms3d.txt");
		//m_obj = t3dObjectPtr(new t3dObjectFlatPerspectiveLP);
		m_obj = t3dObjectPtr(new t3dObjectWire);
		//m_obj->load("ct2.ms3d.txt", "Box01");
		m_obj->load("room.ms3d.txt", "pCube1");

		for(size_t i = 0; i < m_obj->m_object.ver_list.length; i++)
		{
			VECTOR3D_Mul(&m_obj->m_object.ver_list.elems[i]._3D, 5.0f);
			m_obj->m_object.ver_list.elems[i].y += -10;
		}

		m_obj2 = t3dObjectPtr(new t3dObjectWire);
		m_obj2->load("ct2.ms3d.txt", "Sphere01");

		for(size_t i = 0; i < m_obj2->m_object.ver_list.length; i++)
		{
			VECTOR3D_Mul(&m_obj2->m_object.ver_list.elems[i]._3D, 0.2f);
		}
	}

	void do_DRAW(void)
	{
		m_back->fill(m_back->m_ddsurface.rect, Create_RGBI(128, 128, 128));
		m_zbuf->clear();

		{
			// draw the clipper region
			SURFACEV1 surf = m_back->lock();
			RENDERCONTEXTV1 rc;
			memcpy(&rc._SURFACE, &surf, sizeof(rc._SURFACE));

			VERTEXV1T v0, v1;
			VECTOR4D_InitXYZW(	&v0._4D,
								m_cam->m_camera.viewport.x - 1,
								m_cam->m_camera.viewport.y - 1,
								0, 0);
			VECTOR4D_InitXYZW(	&v1._4D,
								m_cam->m_camera.viewport.x + m_cam->m_camera.viewport.width,
								m_cam->m_camera.viewport.y + m_cam->m_camera.viewport.height,
								0, 0);

			v0.c_diff = Create_RGBI(255, 255, 255);
			v1.c_diff = Create_RGBI(255, 255, 255);

			Draw_HLine(&rc, &v0._VERTEXV1, &v1._VERTEXV1);
			Draw_HLine(&rc, &v1._VERTEXV1, &v0._VERTEXV1);
			Draw_VLine(&rc, &v0._VERTEXV1, &v1._VERTEXV1);
			Draw_VLine(&rc, &v1._VERTEXV1, &v0._VERTEXV1);
			m_back->unlock();
		}

		t3dKeyStatePtr k_state = m_key->get_state();
		t3dMouseStatePtr m_state = m_mouse->get_state();

		if(k_state->is_key_down(DIK_ESCAPE))
		{
			::PostMessage(m_wnd->get_hwnd(), WM_CLOSE, 0, 0);
			return;
		}

		static VECTOR4D sphere_pos = {0, 0, 0, 1};

		if(k_state->is_key_down(DIK_NUMPAD8))
		{
			sphere_pos.z += cos(m_cam->m_camera.vrot.y);
			sphere_pos.x += sin(m_cam->m_camera.vrot.y);
		}

		if(k_state->is_key_down(DIK_NUMPAD5))
		{
			sphere_pos.z -= cos(m_cam->m_camera.vrot.y);
			sphere_pos.x -= sin(m_cam->m_camera.vrot.y);
		}

		if(k_state->is_key_down(DIK_NUMPAD4))
		{
			sphere_pos.x -= cos(m_cam->m_camera.vrot.y);
			sphere_pos.z += sin(m_cam->m_camera.vrot.y);
		}

		if(k_state->is_key_down(DIK_NUMPAD6))
		{
			sphere_pos.x += cos(m_cam->m_camera.vrot.y);
			sphere_pos.z -= sin(m_cam->m_camera.vrot.y);
		}

		if(k_state->is_key_down(DIK_NUMPAD1))
		{
			sphere_pos.y += 1;
		}

		if(k_state->is_key_down(DIK_NUMPAD3))
		{
			sphere_pos.y -= 1;
		}

		VECTOR4D vtmp;
		VECTOR3D_Add(&m_cam->m_camera.vpos._3D, &m_cam->mov_scale(vtmp, k_state)._3D);
		VECTOR3D_Add(&m_cam->m_camera.vrot._3D, &m_cam->rot_scale(vtmp, m_state)._3D);
		m_cam->update();

		static VECTOR4D o_emp = {0, 0, 0, 1};
		m_obj->reset();
		m_obj->to_WORLD(o_emp, o_emp);

		VECTOR4D vres;
		//VECTOR4D_InitXYZ(&sphere_pos, 14, -6, 0);
		//VECTOR4D_InitXYZ(&sphere_pos, 16.6f, -7, 0);
		if(m_obj->collision_test(vres, sphere_pos, 4))
		{
			VECTOR4D_Copy(&sphere_pos, &vres);
		}

		m_obj2->reset();
		m_obj2->to_WORLD(sphere_pos, o_emp);

		t3dRender render;
		render.set_camera(m_cam);
		render.set_surface(m_back);
		render.set_zbuffer(m_zbuf);

		render.add_light("light1", t3dLightPtr(new t3dLightAmbient(Create_RGBI(92, 92, 92))));
		render.add_light("light2", t3dLightPtr(new t3dLightPoint(Create_RGBI(255, 255, 255), o_emp)));

		render.draw(m_obj.get());
		render.draw(m_obj2.get());

		m_back->text_out(str_printf("%.1f fps", m_fps->get_FPS()), 10, 10);

		m_back->text_out(str_printf("sphere: %f, %f, %f", sphere_pos.x, sphere_pos.y, sphere_pos.z), 10, 50);

		Sleep(30);
	}

protected:
	FPSGameCameraPtr m_cam;
	t3dObjectPtr m_obj;
	t3dObjectPtr m_obj2;
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
		DemoGame app("demo1_3");
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
