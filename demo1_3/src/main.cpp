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

		//m_scene = t3dObjectPtr(new t3dObjectFlatPerspectiveLP);
		//m_scene->load("room.ms3d.txt", "pCube1");
		m_scene = t3dObjectPtr(new t3dObjectGouraud);
		m_scene->load("scene.ms3d.txt", "polySurface1");

		for(size_t i = 0; i < m_scene->m_object.ver_list.length; i++)
		{
			VECTOR3D_Mul(&m_scene->m_object.ver_list.elems[i]._4D, 5.0f);
			m_scene->m_object.ver_list.elems[i].x *= 1;
			m_scene->m_object.ver_list.elems[i].z *= 1;
			m_scene->m_object.ver_list.elems[i].y += -10;
		}

		m_hand = t3dObjectPtr(new t3dObjectGouraudPerspectiveLP);
		//m_hand = t3dObjectPtr(new t3dObjectGouraudSrcKey(Create_RGBI(0, 0, 0)));
		m_hand->load("hand.ms3d.txt", "polySurface4");

		for(size_t i = 0; i < m_hand->m_object.ver_list.length; i++)
		{
			VECTOR3D_Mul(&m_hand->m_object.ver_list.elems[i]._4D, 0.6f);
			m_hand->m_object.ver_list.elems[i].x += 0;
			m_hand->m_object.ver_list.elems[i].y += -1;
			m_hand->m_object.ver_list.elems[i].z += 0;
		}

		m_player.add_scene(m_scene);

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

		BITMAPV1 btmp;
		INIT_ZERO(btmp);
		INIT_ZERO(image);
		if(!Create_Bitmap_From_File(&btmp, "jack.bmp"))
			MY_EXCEPT("create btmp failed");

		if(!Create_Image(&image,
				btmp.bitmapinfoheader.biWidth, btmp.bitmapinfoheader.biHeight))
			MY_EXCEPT("create image failed");

		if(!Load_Image_From_Bitmap32(&image, &btmp, 0, 0,
				btmp.bitmapinfoheader.biWidth, btmp.bitmapinfoheader.biHeight))
			MY_EXCEPT("load image failed");

		Destroy_Bitmap(&btmp);
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
			VECTOR4D_InitXYZ(	&v0._4D,
								m_cam->m_camera.viewport.x - 1,
								m_cam->m_camera.viewport.y - 1,
								0);
			VECTOR4D_InitXYZ(	&v1._4D,
								m_cam->m_camera.viewport.x + m_cam->m_camera.viewport.width,
								m_cam->m_camera.viewport.y + m_cam->m_camera.viewport.height,
								0);

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

		m_scene->reset();
		m_scene->to_WORLD(emplyVector, emplyVector);

		if(k_state->is_key_down(DIK_R))
		{
			m_player.reset();
		}

		// update camera attribute
		m_player.update(k_state, m_state, m_fps);

		m_cam->set_position(m_player.m_posHead);
		m_cam->set_rotation(m_player.m_rot);
		m_cam->update();

		m_hand->reset();
		m_hand->to_WORLD(m_player.m_posHead, m_player.m_rot);

		t3dRender render;
		render.set_camera(m_cam);
		render.set_surface(m_back);
		render.set_zbuffer(m_zbuf);

		static VECTOR4D l_pos = {30, 30, 30, 1};

		render.add_light("light1", t3dLightPtr(new t3dLightAmbient(Create_RGBI(64, 64, 64))));
		render.add_light("light2", t3dLightPtr(new t3dLightPoint(Create_RGBI(220, 220, 220), l_pos)));

		//{
		//	RENDERCONTEXTV1 rc;
		//	INIT_ZERO(rc);

		//	SURFACEV1 surf = m_back->lock();

		//	//memcpy(&rc._SURFACE, m_cam->m_camera.psurf, sizeof(rc._SURFACE));
		//	//memcpy(&rc._ZBUFFER, m_cam->m_camera.pzbuf, sizeof(rc._ZBUFFER));
		//	memcpy(&rc._SURFACE, &surf, sizeof(rc._SURFACE));
		//	memcpy(&rc._ZBUFFER, &m_zbuf->m_zbuffer, sizeof(rc._ZBUFFER));
		//	//memcpy(&rc._TEXTURE, &pmaterial->texture, sizeof(rc._TEXTURE));

		//	rc.fmin_clip_x = m_cam->m_camera.viewport.x;
		//	rc.fmin_clip_y = m_cam->m_camera.viewport.y;
		//	rc.fmax_clip_x = m_cam->m_camera.viewport.x + m_cam->m_camera.viewport.width - 1;
		//	rc.fmax_clip_y = m_cam->m_camera.viewport.y + m_cam->m_camera.viewport.height - 1;

		//	assert(rc.fmin_clip_x >= 0 && rc.fmax_clip_x < rc._SURFACE.width);
		//	assert(rc.fmin_clip_y >= 0 && rc.fmax_clip_y < rc._SURFACE.height);
		//	assert(rc.fmin_clip_x >= 0 && rc.fmax_clip_x < rc._ZBUFFER.width);
		//	assert(rc.fmin_clip_y >= 0 && rc.fmax_clip_y < rc._ZBUFFER.height);

		//	VERTEXV1T v0, v1, v2;
		//	//VECTOR4D_InitXYZ(&v0._4D, 3,	150, 100);
		//	//VECTOR4D_InitXYZ(&v1._4D, 100,	150, 100);
		//	//VECTOR4D_InitXYZ(&v2._4D, 100,	151, 100);
		//	VECTOR4D_InitXYZ(&v0._4D, -2.9382737, 349.10370, 44.831829);
		//	VECTOR4D_InitXYZ(&v1._4D, 15.556519, 349.39020, 45.805763);
		//	VECTOR4D_InitXYZ(&v2._4D, 230.29062, 353.74454, 44.230614);

		//	v0.c_diff = Create_RGBI(255, 0, 0);
		//	v1.c_diff = Create_RGBI(255, 0, 0);
		//	v2.c_diff = Create_RGBI(255, 0, 0);

		//	Draw_Clipped_Triangle_Gouraud_ZBufferRW32(&rc, &v0, &v1, &v2);

		//	m_back->unlock();
		//}

		render.draw(m_scene.get());

		render.draw(m_hand.get());

		{
			// draw the cross hander
			SURFACEV1 surf = m_back->lock();
			RENDERCONTEXTV1 rc;
			memcpy(&rc._SURFACE, &surf, sizeof(rc._SURFACE));

			REAL cen_x = REAL((m_back->m_ddsurface.rect.right - m_back->m_ddsurface.rect.left) / 2 + m_back->m_ddsurface.rect.left);
			REAL cen_y = REAL((m_back->m_ddsurface.rect.bottom - m_back->m_ddsurface.rect.top) / 2 + m_back->m_ddsurface.rect.top);
			REAL dis_a = REAL((m_back->m_ddsurface.rect.right - m_back->m_ddsurface.rect.left) / 80);
			REAL dis_b = REAL((m_back->m_ddsurface.rect.right - m_back->m_ddsurface.rect.left) / 60);
			{
				VERTEXV1T v0, v1;
				v0.c_diff = Create_RGBI(0, 255, 0);
				v1.c_diff = Create_RGBI(0, 255, 0);

				VECTOR4D_InitXYZ(	&v0._4D, cen_x, cen_y - dis_a - dis_b, 0);
				VECTOR4D_InitXYZ(	&v1._4D, cen_x, cen_y - dis_a, 0);
				Draw_VLine(&rc, &v0._VERTEXV1, &v1._VERTEXV1);

				VECTOR4D_InitXYZ(	&v0._4D, cen_x, cen_y + dis_a, 0);
				VECTOR4D_InitXYZ(	&v1._4D, cen_x, cen_y + dis_a + dis_b, 0);
				Draw_VLine(&rc, &v0._VERTEXV1, &v1._VERTEXV1);

				VECTOR4D_InitXYZ(	&v0._4D, cen_x - dis_a - dis_b, cen_y, 0);
				VECTOR4D_InitXYZ(	&v1._4D, cen_x - dis_a, cen_y, 0);
				Draw_HLine(&rc, &v0._VERTEXV1, &v1._VERTEXV1);

				VECTOR4D_InitXYZ(	&v0._4D, cen_x + dis_a, cen_y, 0);
				VECTOR4D_InitXYZ(	&v1._4D, cen_x + dis_a + dis_b, cen_y, 0);
				Draw_HLine(&rc, &v0._VERTEXV1, &v1._VERTEXV1);
			}

			//rc.fmin_clip_x = m_cam->m_camera.viewport.x;
			//rc.fmin_clip_y = m_cam->m_camera.viewport.y;
			//rc.fmax_clip_x = m_cam->m_camera.viewport.x + m_cam->m_camera.viewport.width - 1;
			//rc.fmax_clip_y = m_cam->m_camera.viewport.y + m_cam->m_camera.viewport.height - 1;

			////memcpy(&rc._SURFACE, &surf, sizeof(rc._SURFACE));
			//memcpy(&rc._ZBUFFER, &m_zbuf->m_zbuffer._SURFACE, sizeof(rc._ZBUFFER));
			//memcpy(&rc._TEXTURE, &image._SURFACE, sizeof(rc._TEXTURE));
			//VERTEXV1T v0, v1, v2;
			//VECTOR4D_InitXYZ(&v0._4D, 20, 20, 100);
			//VECTOR4D_InitXYZ(&v1._4D, 500, 20, 100);
			//VECTOR4D_InitXYZ(&v2._4D, 500, 500, 100);
			//v0.u = 0;
			//v0.v = 0;
			//v1.u = 0;
			//v1.v = image.height << FIXP16_SHIFT;
			//v2.u = image.width << FIXP16_SHIFT;
			//v2.v = image.height << FIXP16_SHIFT;

			//rc.c_src_key = Create_RGBI(0, 0, 0);
			//Draw_Triangle_Texture_SrcKey_ZBufferRW(&rc, &v0, &v1, &v2);

			m_back->unlock();
		}

		m_back->text_out(str_printf("%.1f fps", m_fps->get_FPS()), 10, 10);

		m_back->text_out(str_printf("cam.pos: %f, %f, %f", m_cam->m_camera.vpos.x, m_cam->m_camera.vpos.y, m_cam->m_camera.vpos.z), 10, 50);

		m_back->text_out(str_printf("cam.rot: %f, %f, %f", m_cam->m_camera.vrot.x, m_cam->m_camera.vrot.y, m_cam->m_camera.vrot.z), 10, 90);

		//Sleep(30);
	}

	void do_SHUTDOWN(void)
	{
		Destroy_Image(&image);
	}

protected:
	t3dCameraEulerPtr m_cam;
	t3dObjectPtr m_scene;

	FPSPlayer m_player;
	t3dObjectPtr m_hand;

	IMAGEV1 image;
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
	catch(MyException & e)
	{
		::MessageBoxA(NULL, e.getFullDesc().c_str(), "Exception", MB_OK);
	}

	return 0;
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);
}
