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
		m_cam = t3dCameraEulerPtr(new t3dCameraEuler(rect));
		m_cam->set_fov(DEG_TO_RAD(60));
		m_cam->set_min_clipZ(9);

		//m_obj = t3dObjectPtr(new t3dObjectFlatPerspectiveLP);
		//m_obj->load("room.ms3d.txt", "pCube1");
		m_obj = t3dObjectPtr(new t3dObjectGouraud);
		m_obj->load("scene.ms3d.txt", "polySurface1");

		for(size_t i = 0; i < m_obj->m_object.ver_list.length; i++)
		{
			VECTOR3D_Mul(&m_obj->m_object.ver_list.elems[i]._3D, 5.0f);
			m_obj->m_object.ver_list.elems[i].x *= 1;
			m_obj->m_object.ver_list.elems[i].z *= 1;
			m_obj->m_object.ver_list.elems[i].y += -10;
		}

		m_player.add_scene(m_obj);

		/*
		m_attrMovResisSpeed			= 30;
		m_attrMovSpeedAccel			= 2 * m_attrMovResisSpeed;
		m_attrMovSpeedLimit			= 50;
		m_attrJmpSpeedAccel			= 200;
		m_attrGravitySpeedAccel		= -9;
		m_attrGravitySpeedLimit		= -100;
		m_attrPlayerSphereRadius	= 4;
		m_attrPlayerSlideLimit		= 1;
		m_attrPlayerHeadStature		= 10;
		m_attrRotSpeedLimit			= (REAL)0.2;
		*/

		m_player.m_attrMovResisSpeed = 20;
		m_player.m_attrMovSpeedAccel = 40;
		m_player.m_attrMovSpeedLimit = 90;
		m_player.m_attrJmpSpeedAccel = 300;
		m_player.m_attrGravitySpeedAccel = -40;
		m_player.m_attrGravitySpeedLimit = -200;
		m_player.m_attrPlayerSphereRadius = 10;
		m_player.m_attrPlayerHeadStature = 18;
		m_player.m_attrPlayerInitPos.y += 5;

		m_player.reset();

		rect = m_wnd->GetClientRect();
		rect.left += MyWindow::GetRectWidth(rect) / 2;
		rect.top += MyWindow::GetRectHeight(rect) / 2;
		rect.right = rect.left;
		rect.bottom = rect.top;
		::ClipCursor(&rect);
		::ShowCursor(FALSE);
	}

	void do_DRAW(void)
	{
		//m_back->fill(m_back->m_ddsurface.rect, Create_RGBI(128, 128, 128));
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
			::PostMessage(m_wnd->get_HWND(), WM_CLOSE, 0, 0);
			return;
		}

		static VECTOR4D emplyVector = {0, 0, 0, 1};

		m_obj->reset();
		m_obj->to_WORLD(emplyVector, emplyVector);

		if(k_state->is_key_down(DIK_R))
		{
			m_player.reset();
		}

		// update camera attribute
		m_player.update(k_state, m_state, m_fps);

		m_cam->set_position(m_player.m_posHead);
		m_cam->set_rotation(m_player.m_rot);
		m_cam->update();

		t3dRender render;
		render.set_camera(m_cam);
		render.set_surface(m_back);
		render.set_zbuffer(m_zbuf);

		static VECTOR4D l_pos = {30, 30, 30, 1};

		render.add_light("light1", t3dLightPtr(new t3dLightAmbient(Create_RGBI(64, 64, 64))));
		render.add_light("light2", t3dLightPtr(new t3dLightPoint(Create_RGBI(220, 220, 220), l_pos)));

		render.draw(m_obj.get());

		m_back->text_out(str_printf("%.1f fps", m_fps->get_FPS()), 10, 10);

		m_back->text_out(str_printf("cam.pos: %f, %f, %f", m_cam->m_camera.vpos.x, m_cam->m_camera.vpos.y, m_cam->m_camera.vpos.z), 10, 50);

		m_back->text_out(str_printf("cam.rot: %f, %f, %f", m_cam->m_camera.vrot.x, m_cam->m_camera.vrot.y, m_cam->m_camera.vrot.z), 10, 90);

		//Sleep(30);
	}

protected:
	t3dCameraEulerPtr m_cam;
	t3dObjectPtr m_obj;

	FPSPlayer m_player;
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
