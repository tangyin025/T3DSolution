
#ifndef _DEBUG
#pragma warning(disable : 4701)
#endif

#ifndef __draw_func
#error must define __draw_func
#endif

#ifndef __draw_func_clipped
#ifdef __draw_CLIP
#error must define __draw_func_clipped at Gouraud mode
#endif
#endif

//T3DLIB_API void Draw_Clipped_Triangle_Gouraud_Texture_ZBufferRW32(const RENDERCONTEXTV1 * prc, const VERTEXV1T * pv0, const VERTEXV1T * pv1, const VERTEXV1T * pv2)
{
	const VERTEXV1T * ptmp;
	SCANCONTEXT sc;

#ifndef __draw_GR
	sc.lc.x = pv0->c_diff;
#endif

	if(pv0->y > pv1->y)
		SWAP(pv0, pv1, ptmp);
	if(pv0->y > pv2->y)
		SWAP(pv0, pv2, ptmp);
	if(pv1->y > pv2->y)
		SWAP(pv1, pv2, ptmp);

	REAL x3 = LINE2D_INTERSECT(pv1->y, pv0->y, pv2->y, pv0->x, pv2->x);
	int y0 = (int)pv0->y;
	int y1 = (int)pv1->y;
	int y2 = (int)pv2->y;

	if(pv1->x < x3)
	{
		sc.lx = pv0->x;
		sc.rx = pv0->x;
		sc.lx_inc, sc.rx_inc;

#ifdef __draw_UV
		sc.lu = pv0->u;
		sc.lv = pv0->v;
		sc.ru = pv0->u;
		sc.rv = pv0->v;
		sc.lu_inc, sc.lv_inc;
		sc.ru_inc, sc.rv_inc;
#endif

#ifdef __draw_GR
		sc.lc, sc.lc_inc;
		sc.rc, sc.rc_inc;
		VECTOR4DI_InitXYZW( &sc.lc,
						_32BIT_GETR(pv0->c_diff) << FIXP16_SHIFT,
						_32BIT_GETG(pv0->c_diff) << FIXP16_SHIFT,
						_32BIT_GETB(pv0->c_diff) << FIXP16_SHIFT, 0);
		VECTOR4DI_InitXYZW( &sc.rc,
						_32BIT_GETR(pv0->c_diff) << FIXP16_SHIFT,
						_32BIT_GETG(pv0->c_diff) << FIXP16_SHIFT,
						_32BIT_GETB(pv0->c_diff) << FIXP16_SHIFT, 0);
#endif

#ifdef __draw_ZB
		sc.lz = (FIXP28)(1 / pv0->z * FIXP28_MAG);
		sc.rz = (FIXP28)(1 / pv0->z * FIXP28_MAG);
		sc.lz_inc, sc.rz_inc;
#endif

		if(y1 > y0)
		{
			sc.lx_inc = (pv1->x - pv0->x) / (float)(y1 - y0); // ***

#ifdef __draw_UV
			sc.lu_inc = (pv1->u - pv0->u) / (y1 - y0);
			sc.lv_inc = (pv1->v - pv0->v) / (y1 - y0);
#endif

#ifdef __draw_GR
			VECTOR3DI_Div( &(*VECTOR4DI_InitXYZW( &sc.lc_inc,
							((_32BIT_GETR(pv1->c_diff) - _32BIT_GETR(pv0->c_diff)) << FIXP16_SHIFT),
							((_32BIT_GETG(pv1->c_diff) - _32BIT_GETG(pv0->c_diff)) << FIXP16_SHIFT),
							((_32BIT_GETB(pv1->c_diff) - _32BIT_GETB(pv0->c_diff)) << FIXP16_SHIFT), 0))._3D, y1 - y0);
#endif

#ifdef __draw_ZB
			sc.lz_inc = ((FIXP28)(1 / pv1->z * FIXP28_MAG) - (FIXP28)(1 / pv0->z * FIXP28_MAG)) / (y1 - y0);
#endif
		}

		if(y2 > y0)
		{
			sc.rx_inc = (pv2->x - pv0->x) / (float)(y2 - y0); // ***

#ifdef __draw_UV
			sc.ru_inc = (pv2->u - pv0->u) / (y2 - y0);
			sc.rv_inc = (pv2->v - pv0->v) / (y2 - y0);
#endif

#ifdef __draw_GR
			VECTOR3DI_Div( &(*VECTOR4DI_InitXYZW( &sc.rc_inc,
							((_32BIT_GETR(pv2->c_diff) - _32BIT_GETR(pv0->c_diff)) << FIXP16_SHIFT),
							((_32BIT_GETG(pv2->c_diff) - _32BIT_GETG(pv0->c_diff)) << FIXP16_SHIFT),
							((_32BIT_GETB(pv2->c_diff) - _32BIT_GETB(pv0->c_diff)) << FIXP16_SHIFT), 0))._3D, y2 - y0);
#endif

#ifdef __draw_ZB
			sc.rz_inc = ((FIXP28)(1 / pv2->z * FIXP28_MAG) - (FIXP28)(1 / pv0->z * FIXP28_MAG)) / (y2 - y0);
#endif
		}

#ifdef __draw_CLIP
		int y_beg, y_end;
		if(y1 > prc->fmin_clip_y)
		{
			if(y0 < prc->fmin_clip_y)
			{
				y_beg = (int)prc->fmin_clip_y;
				sc.lx = sc.lx + (prc->fmin_clip_y - y0) * sc.lx_inc; // ***
				sc.rx = sc.rx + (prc->fmin_clip_y - y0) * sc.rx_inc; // ***

#ifdef __draw_UV
				sc.lu = sc.lu + ((int)prc->fmin_clip_y - y0) * sc.lu_inc;
				sc.ru = sc.ru + ((int)prc->fmin_clip_y - y0) * sc.ru_inc;
				sc.lv = sc.lv + ((int)prc->fmin_clip_y - y0) * sc.lv_inc;
				sc.rv = sc.rv + ((int)prc->fmin_clip_y - y0) * sc.rv_inc;
#endif

#ifdef __draw_GR
				VECTOR4DI vtmp;
				VECTOR3DI_Add(&sc.lc._3D, VECTOR3DI_Mul(&vtmp._3D, &sc.lc_inc._3D, (int)prc->fmin_clip_y - y0));
				VECTOR3DI_Add(&sc.rc._3D, VECTOR3DI_Mul(&vtmp._3D, &sc.rc_inc._3D, (int)prc->fmin_clip_y - y0));
#endif

#ifdef __draw_ZB
				sc.lz = sc.lz + ((int)prc->fmin_clip_y - y0) * sc.lz_inc;
				sc.rz = sc.rz + ((int)prc->fmin_clip_y - y0) * sc.rz_inc;
#endif
			}
			else
			{
				y_beg = y0;
			}

			if(y1 > prc->fmax_clip_y + 1)
			{
				y_end = (int)prc->fmax_clip_y + 1;
			}
			else
			{
				y_end = y1;
			}

			if(MIN(pv0->x, pv1->x) < prc->fmin_clip_x || MAX(pv0->x, x3) > prc->fmax_clip_x + 1) // ***
			{
				__draw_func_clipped(sc, y_beg, y_end, prc);
			}
			else
			{
				__draw_func(sc, y_beg, y_end, prc);
			}
		}
#else // ! __draw_CLIP
				__draw_func(sc, y0, y1, prc);
#endif

		sc.lx = pv1->x; // ***

#ifdef __draw_UV
		sc.lu = pv1->u;
		sc.lv = pv1->v;
#endif

#ifdef __draw_GR
		VECTOR4DI_InitXYZW( &sc.lc,
						_32BIT_GETR(pv1->c_diff) << FIXP16_SHIFT,
						_32BIT_GETG(pv1->c_diff) << FIXP16_SHIFT,
						_32BIT_GETB(pv1->c_diff) << FIXP16_SHIFT, 0);
#endif

#ifdef __draw_ZB
		sc.lz = (FIXP28)(1 / pv1->z * FIXP28_MAG);
#endif

		if(y2 > y1)
		{
			sc.lx_inc = (pv2->x - pv1->x) / (float)(y2 - y1); // ***

#ifdef __draw_UV
			sc.lu_inc = (pv2->u - pv1->u) / (y2 - y1);
			sc.lv_inc = (pv2->v - pv1->v) / (y2 - y1);
#endif

#ifdef __draw_GR
			VECTOR3DI_Div( &(*VECTOR4DI_InitXYZW( &sc.lc_inc,
							((_32BIT_GETR(pv2->c_diff) - _32BIT_GETR(pv1->c_diff)) << FIXP16_SHIFT),
							((_32BIT_GETG(pv2->c_diff) - _32BIT_GETG(pv1->c_diff)) << FIXP16_SHIFT),
							((_32BIT_GETB(pv2->c_diff) - _32BIT_GETB(pv1->c_diff)) << FIXP16_SHIFT), 0))._3D, y2 - y1);
#endif

#ifdef __draw_ZB
			sc.lz_inc = ((FIXP28)(1 / pv2->z * FIXP28_MAG) - (FIXP28)(1 / pv1->z * FIXP28_MAG)) / (y2 - y1);
#endif
		}

#ifdef __draw_CLIP
		if(y2 > prc->fmin_clip_y)
		{
			if(y1 <= prc->fmin_clip_y) // !!! <=
			{
				y_beg = (int)prc->fmin_clip_y;
				sc.lx = sc.lx + (prc->fmin_clip_y - y1) * sc.lx_inc; // ***
				sc.rx = sc.rx + (prc->fmin_clip_y - y0) * sc.rx_inc; // ***

#ifdef __draw_UV
				sc.lu = sc.lu + ((int)prc->fmin_clip_y - y1) * sc.lu_inc;
				sc.ru = sc.ru + ((int)prc->fmin_clip_y - y0) * sc.ru_inc;
				sc.lv = sc.lv + ((int)prc->fmin_clip_y - y1) * sc.lv_inc;
				sc.rv = sc.rv + ((int)prc->fmin_clip_y - y0) * sc.rv_inc;
#endif

#ifdef __draw_GR
				VECTOR4DI vtmp;
				VECTOR3DI_Add(&sc.lc._3D, VECTOR3DI_Mul(&vtmp._3D, &sc.lc_inc._3D, (int)prc->fmin_clip_y - y1));
				VECTOR3DI_Add(&sc.rc._3D, VECTOR3DI_Mul(&vtmp._3D, &sc.rc_inc._3D, (int)prc->fmin_clip_y - y0));
#endif

#ifdef __draw_ZB
				sc.lz = sc.lz + ((int)prc->fmin_clip_y - y1) * sc.lz_inc;
				sc.rz = sc.rz + ((int)prc->fmin_clip_y - y0) * sc.rz_inc;
#endif
			}
			else
			{
				y_beg = y1;
			}

			if(y2 > prc->fmax_clip_y + 1)
			{
				y_end = (int)prc->fmax_clip_y + 1;
			}
			else
			{
				y_end = y2;
			}

			if(MIN(pv2->x, pv1->x) < prc->fmin_clip_x || MAX(pv2->x, x3) > prc->fmax_clip_x + 1) // ***
			{
				__draw_func_clipped(sc, y_beg, y_end, prc);
			}
			else
			{
				__draw_func(sc, y_beg, y_end, prc);
			}
		}
#else // ! __draw_CLIP
				__draw_func(sc, y1, y2, prc);
#endif
	}
	else
	{
		sc.lx = pv0->x;
		sc.rx = pv0->x;
		sc.lx_inc, sc.rx_inc;

#ifdef __draw_UV
		sc.lu = pv0->u;
		sc.lv = pv0->v;
		sc.ru = pv0->u;
		sc.rv = pv0->v;
		sc.lu_inc, sc.lv_inc;
		sc.ru_inc, sc.rv_inc;
#endif

#ifdef __draw_GR
		sc.lc, sc.lc_inc;
		sc.rc, sc.rc_inc;
		VECTOR4DI_InitXYZW( &sc.lc,
						_32BIT_GETR(pv0->c_diff) << FIXP16_SHIFT,
						_32BIT_GETG(pv0->c_diff) << FIXP16_SHIFT,
						_32BIT_GETB(pv0->c_diff) << FIXP16_SHIFT, 0);
		VECTOR4DI_InitXYZW( &sc.rc,
						_32BIT_GETR(pv0->c_diff) << FIXP16_SHIFT,
						_32BIT_GETG(pv0->c_diff) << FIXP16_SHIFT,
						_32BIT_GETB(pv0->c_diff) << FIXP16_SHIFT, 0);
#endif

#ifdef __draw_ZB
		sc.lz = (FIXP28)(1 / pv0->z * FIXP28_MAG);
		sc.rz = (FIXP28)(1 / pv0->z * FIXP28_MAG);
		sc.lz_inc, sc.rz_inc;
#endif

		if(y2 > y0)
		{
			sc.lx_inc = (pv2->x - pv0->x) / (float)(y2 - y0); // ***

#ifdef __draw_UV
			sc.lu_inc = (pv2->u - pv0->u) / (y2 - y0);
			sc.lv_inc = (pv2->v - pv0->v) / (y2 - y0);
#endif

#ifdef __draw_GR
			VECTOR3DI_Div( &(*VECTOR4DI_InitXYZW( &sc.lc_inc,
							((_32BIT_GETR(pv2->c_diff) - _32BIT_GETR(pv0->c_diff)) << FIXP16_SHIFT),
							((_32BIT_GETG(pv2->c_diff) - _32BIT_GETG(pv0->c_diff)) << FIXP16_SHIFT),
							((_32BIT_GETB(pv2->c_diff) - _32BIT_GETB(pv0->c_diff)) << FIXP16_SHIFT), 0))._3D, y2 - y0);
#endif

#ifdef __draw_ZB
			sc.lz_inc = ((FIXP28)(1 / pv2->z * FIXP28_MAG) - (FIXP28)(1 / pv0->z * FIXP28_MAG)) / (y2 - y0);
#endif
		}

		if(y1 > y0)
		{
			sc.rx_inc = (pv1->x - pv0->x) / (float)(y1 - y0); // ***

#ifdef __draw_UV
			sc.ru_inc = (pv1->u - pv0->u) / (y1 - y0);
			sc.rv_inc = (pv1->v - pv0->v) / (y1 - y0);
#endif

#ifdef __draw_GR
			VECTOR3DI_Div( &(*VECTOR4DI_InitXYZW( &sc.rc_inc,
							((_32BIT_GETR(pv1->c_diff) - _32BIT_GETR(pv0->c_diff)) << FIXP16_SHIFT),
							((_32BIT_GETG(pv1->c_diff) - _32BIT_GETG(pv0->c_diff)) << FIXP16_SHIFT),
							((_32BIT_GETB(pv1->c_diff) - _32BIT_GETB(pv0->c_diff)) << FIXP16_SHIFT), 0))._3D, y1 - y0);
#endif

#ifdef __draw_ZB
			sc.rz_inc = ((FIXP28)(1 / pv1->z * FIXP28_MAG) - (FIXP28)(1 / pv0->z * FIXP28_MAG)) / (y1 - y0);
#endif
		}

#ifdef __draw_CLIP
		int y_beg, y_end;
		if(y1 > prc->fmin_clip_y)
		{
			if(y0 < prc->fmin_clip_y)
			{
				y_beg = (int)prc->fmin_clip_y;
				sc.lx = sc.lx + (prc->fmin_clip_y - y0) * sc.lx_inc; // ***
				sc.rx = sc.rx + (prc->fmin_clip_y - y0) * sc.rx_inc; // ***

#ifdef __draw_UV
				sc.lu = sc.lu + ((int)prc->fmin_clip_y - y0) * sc.lu_inc;
				sc.ru = sc.ru + ((int)prc->fmin_clip_y - y0) * sc.ru_inc;
				sc.lv = sc.lv + ((int)prc->fmin_clip_y - y0) * sc.lv_inc;
				sc.rv = sc.rv + ((int)prc->fmin_clip_y - y0) * sc.rv_inc;
#endif

#ifdef __draw_GR
				VECTOR4DI vtmp;
				VECTOR3DI_Add(&sc.lc._3D, VECTOR3DI_Mul(&vtmp._3D, &sc.lc_inc._3D, (int)prc->fmin_clip_y - y0));
				VECTOR3DI_Add(&sc.rc._3D, VECTOR3DI_Mul(&vtmp._3D, &sc.rc_inc._3D, (int)prc->fmin_clip_y - y0));
#endif

#ifdef __draw_ZB
				sc.lz = sc.lz + ((int)prc->fmin_clip_y - y0) * sc.lz_inc;
				sc.rz = sc.rz + ((int)prc->fmin_clip_y - y0) * sc.rz_inc;
#endif
			}
			else
			{
				y_beg = y0;
			}

			if(y1 > prc->fmax_clip_y + 1)
			{
				y_end = (int)prc->fmax_clip_y + 1;
			}
			else
			{
				y_end = y1;
			}

			if(MIN(pv0->x, x3) < prc->fmin_clip_x || MAX(pv0->x, pv1->x) > prc->fmax_clip_x + 1) // ***
			{
				__draw_func_clipped(sc, y_beg, y_end, prc);
			}
			else
			{
				__draw_func(sc, y_beg, y_end, prc);
			}
		}
#else // ! __draw_CLIP
				__draw_func(sc, y0, y1, prc);
#endif

		sc.rx = pv1->x; // ***

#ifdef __draw_UV
		sc.ru = pv1->u;
		sc.rv = pv1->v;
#endif

#ifdef __draw_GR
		VECTOR4DI_InitXYZW( &sc.rc,
						_32BIT_GETR(pv1->c_diff) << FIXP16_SHIFT,
						_32BIT_GETG(pv1->c_diff) << FIXP16_SHIFT,
						_32BIT_GETB(pv1->c_diff) << FIXP16_SHIFT, 0);
#endif

#ifdef __draw_ZB
		sc.rz = (FIXP28)(1 / pv1->z * FIXP28_MAG);
#endif

		if(y2 > y1)
		{
			sc.rx_inc = (pv2->x - pv1->x) / (float)(y2 - y1); // ***

#ifdef __draw_UV
			sc.ru_inc = (pv2->u - pv1->u) / (y2 - y1);
			sc.rv_inc = (pv2->v - pv1->v) / (y2 - y1);
#endif

#ifdef __draw_GR
			VECTOR3DI_Div( &(*VECTOR4DI_InitXYZW( &sc.rc_inc,
							((_32BIT_GETR(pv2->c_diff) - _32BIT_GETR(pv1->c_diff)) << FIXP16_SHIFT),
							((_32BIT_GETG(pv2->c_diff) - _32BIT_GETG(pv1->c_diff)) << FIXP16_SHIFT),
							((_32BIT_GETB(pv2->c_diff) - _32BIT_GETB(pv1->c_diff)) << FIXP16_SHIFT), 0))._3D, y2 - y1);
#endif

#ifdef __draw_ZB
			sc.rz_inc = ((FIXP28)(1 / pv2->z * FIXP28_MAG) - (FIXP28)(1 / pv1->z * FIXP28_MAG)) / (y2 - y1);
#endif
		}

#ifdef __draw_CLIP
		if(y2 > prc->fmin_clip_y)
		{
			if(y1 <= prc->fmin_clip_y) // !!! <=
			{
				y_beg = (int)prc->fmin_clip_y;
				sc.lx = sc.lx + (prc->fmin_clip_y - y0) * sc.lx_inc; // ***
				sc.rx = sc.rx + (prc->fmin_clip_y - y1) * sc.rx_inc; // ***

#ifdef __draw_UV
				sc.lu = sc.lu + ((int)prc->fmin_clip_y - y0) * sc.lu_inc;
				sc.ru = sc.ru + ((int)prc->fmin_clip_y - y1) * sc.ru_inc;
				sc.lv = sc.lv + ((int)prc->fmin_clip_y - y0) * sc.lv_inc;
				sc.rv = sc.rv + ((int)prc->fmin_clip_y - y1) * sc.rv_inc;
#endif

#ifdef __draw_GR
				VECTOR4DI vtmp;
				VECTOR3DI_Add(&sc.lc._3D, VECTOR3DI_Mul(&vtmp._3D, &sc.lc_inc._3D, (int)prc->fmin_clip_y - y0));
				VECTOR3DI_Add(&sc.rc._3D, VECTOR3DI_Mul(&vtmp._3D, &sc.rc_inc._3D, (int)prc->fmin_clip_y - y1));
#endif

#ifdef __draw_ZB
				sc.lz = sc.lz + ((int)prc->fmin_clip_y - y0) * sc.lz_inc;
				sc.rz = sc.rz + ((int)prc->fmin_clip_y - y1) * sc.rz_inc;
#endif
			}
			else
			{
				y_beg = y1;
			}

			if(y2 > prc->fmax_clip_y + 1)
			{
				y_end = (int)prc->fmax_clip_y + 1;
			}
			else
			{
				y_end = y2;
			}

			if(MIN(pv2->x, x3) < prc->fmin_clip_x || MAX(pv2->x, pv1->x) > prc->fmax_clip_x + 1) // ***
			{
				__draw_func_clipped(sc, y_beg, y_end, prc);
			}
			else
			{
				__draw_func(sc, y_beg, y_end, prc);
			}
		}
#else // ! __draw_CLIP
				__draw_func(sc, y1, y2, prc);
#endif
	}
}

#undef __draw_UV
#undef __draw_GR
#undef __draw_ZB
#undef __draw_CLIP
#undef __draw_func
#undef __draw_func_clipped
