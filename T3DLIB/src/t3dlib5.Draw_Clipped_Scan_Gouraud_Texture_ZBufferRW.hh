
#if ( !defined __draw_16 && !defined __draw_32 )
#error must define one between __draw_16 and __draw_32
#endif

#if (  defined __draw_16 &&  defined __draw_32 )
#error must define one between __draw_16 and __draw_32
#endif

#if (defined __draw_UV_PerspectiveLP) && (!defined __draw_UV)
#error __draw_UV_PerspectiveLP must be used with __draw_UV
#endif

//static void Draw_Clipped_Scan_Gouraud_Texture_ZBufferRW32(SCANCONTEXT & sc, const int y_beg, const int y_end, const RENDERCONTEXTV1 * prc)
{
	int y;
	for(y = y_beg; y < y_end; y++)
	{
		int s_beg, s_end;
		//int dx = (int)(floor(sc.rx) - floor(sc.lx));
		int dx = (int)sc.rx - (int)sc.lx;

#ifdef __draw_UV
	#ifdef __draw_UV_PerspectiveLP
		//FIXP16 lu = ((sc.lu << (FIXP28_SHIFT - FIXP22_SHIFT)) / (sc.lz >> (FIXP28_SHIFT - FIXP22_SHIFT))) << (FIXP16_SHIFT - ((FIXP22_SHIFT + (FIXP28_SHIFT - FIXP22_SHIFT)) - (FIXP28_SHIFT - (FIXP28_SHIFT - FIXP22_SHIFT)))); // no body can understand !!!

		/*
		 * Note: this UV PerspectiveLP algorithm have an overflow bug, because of the sc.lu is FIXP22
		 * type when UV PerspectiveLP mode, so sc.lu << 6 will restrict the orignal uv must between
		 * [0, 127), if the uv is 127, such as sc.lu = 33555212, then sc.lu << 6 will be negative,
		 * lead the lu to be -127, bug use float mode will not case any bug, except slow performance
		 */

		//int lu = ((sc.lu << 6) / (sc.lz >> 6)) << 10;
		//int ru = ((sc.ru << 6) / (sc.rz >> 6)) << 10;
		//int lv = ((sc.lv << 6) / (sc.lz >> 6)) << 10;
		//int rv = ((sc.rv << 6) / (sc.rz >> 6)) << 10;

		int lu = ((sc.lu << 0) / (sc.lz >> 12)) << 10;
		int ru = ((sc.ru << 0) / (sc.rz >> 12)) << 10;
		int lv = ((sc.lv << 0) / (sc.lz >> 12)) << 10;
		int rv = ((sc.rv << 0) / (sc.rz >> 12)) << 10;

#ifdef _DEBUG
		{
			if(y == 510)
			{
				int j = 10;
				j++;
			}

			int itmp;
			assert((itmp = lu >> FIXP16_SHIFT) >= 0 && (itmp = lu >> FIXP16_SHIFT) <= prc->t_width - 1);
			assert((itmp = ru >> FIXP16_SHIFT) >= 0 && (itmp = ru >> FIXP16_SHIFT) <= prc->t_width - 1);
			assert((itmp = lv >> FIXP16_SHIFT) >= 0 && (itmp = lv >> FIXP16_SHIFT) <= prc->t_height - 1);
			assert((itmp = rv >> FIXP16_SHIFT) >= 0 && (itmp = rv >> FIXP16_SHIFT) <= prc->t_height - 1);
		}
#endif
	#endif

		FIXP16 u_beg, v_beg;
		FIXP16 du, dv;
#endif

#ifdef __draw_GR
		VECTOR4DI c_beg;
		VECTOR4DI dc;
#endif

#ifdef __draw_ZB
		FIXP28 z_beg;
		FIXP28 dz;
#endif

		if(dx > 0)
		{
#ifdef __draw_UV
	#ifdef __draw_UV_PerspectiveLP
			du = (ru - lu) / dx;
			dv = (rv - lv) / dx;
	#else
			du = (sc.ru - sc.lu) / dx;
			dv = (sc.rv - sc.lv) / dx;
	#endif
#endif

#ifdef __draw_GR
			//VECTOR3DI_Div(VECTOR3DI_Sub(&dc._3D, &sc.rc._3D, &sc.lc._3D), dx);
			dc.x = (sc.rc.x - sc.lc.x) / dx;
			dc.y = (sc.rc.y - sc.lc.y) / dx;
			dc.z = (sc.rc.z - sc.lc.z) / dx;
#endif

#ifdef __draw_ZB
			dz = (sc.rz - sc.lz) / dx;
#endif

#ifdef __draw_CLIP
			if(sc.lx < prc->fmin_clip_x)
			{
				s_beg = (int)prc->fmin_clip_x;

#ifdef __draw_UV
	#ifdef __draw_UV_PerspectiveLP
				u_beg = lu + ((int)prc->fmin_clip_x - (int)sc.lx) * du;
				v_beg = lv + ((int)prc->fmin_clip_x - (int)sc.lx) * dv;
	#else
				u_beg = sc.lu + ((int)prc->fmin_clip_x - (int)sc.lx) * du;
				v_beg = sc.lv + ((int)prc->fmin_clip_x - (int)sc.lx) * dv;
	#endif
#endif

#ifdef __draw_GR
				//VECTOR4DI vtmp;
				//VECTOR3DI_Add(&c_beg._3D, &sc.lc._3D, VECTOR3DI_Mul(&vtmp._3D, &dc._3D, (int)(prc->fmin_clip_x - sc.lx)));
				c_beg.x = sc.lc.x + ((int)prc->fmin_clip_x - (int)sc.lx) * dc.x;
				c_beg.y = sc.lc.y + ((int)prc->fmin_clip_x - (int)sc.lx) * dc.y;
				c_beg.z = sc.lc.z + ((int)prc->fmin_clip_x - (int)sc.lx) * dc.z;
#endif

#ifdef __draw_ZB
				z_beg = sc.lz + (int)(prc->fmin_clip_x - sc.lx) * dz;
#endif
			}
			else
			{
				s_beg = (int)sc.lx;

#ifdef __draw_UV
	#ifdef __draw_UV_PerspectiveLP
				u_beg = lu;
				v_beg = lv;
	#else
				u_beg = sc.lu;
				v_beg = sc.lv;
	#endif
#endif

#ifdef __draw_GR
				c_beg = sc.lc;
#endif

#ifdef __draw_ZB
				z_beg = sc.lz;
#endif
			}
			s_end = (int)MIN(sc.rx, prc->fmax_clip_x + 1);
#else // !CLIP
				s_beg = (int)sc.lx;
				s_end = (int)sc.rx;

#ifdef __draw_UV
	#ifdef __draw_UV_PerspectiveLP
				u_beg = lu;
				v_beg = lv;
	#else
				u_beg = sc.lu;
				v_beg = sc.lv;
	#endif
#endif

#ifdef __draw_GR
				c_beg = sc.lc;
#endif

#ifdef __draw_ZB
				z_beg = sc.lz;
#endif
#endif

#ifdef __draw_16
				unsigned char * ps = prc->s_pbuffer + (s_beg << _16BIT_BYTES_SHIFT) + (y << prc->s_pitch_shift);
#else
				unsigned char * ps = prc->s_pbuffer + (s_beg << _32BIT_BYTES_SHIFT) + (y << prc->s_pitch_shift);
#endif

#ifdef __draw_ZB
			unsigned char * pz = prc->z_pbuffer + (s_beg << _ZBUFF_BYTES_SHIFT) + (y << prc->z_pitch_shift);
#endif

			dx = s_end - s_beg;

			while(dx-- > 0)
			{
#ifdef __draw_ZB
				if(z_beg >= _ZBUFF_TO_FIXP28(*(_ZBUFF *)pz))
#endif
				{
#ifdef __draw_UV
	#ifdef __draw_GR
		#ifdef __draw_16
					*(unsigned short *)ps = (unsigned short)_RGB16BIT(
							COLOR_MUL_16R(c_beg.x >> FIXP16_SHIFT, _16BIT_GETR(*(unsigned short *)(prc->t_pbuffer + (u_beg >> FIXP16_SHIFT << _16BIT_BYTES_SHIFT) + (v_beg >> FIXP16_SHIFT << prc->t_pitch_shift)))),
							COLOR_MUL_16G(c_beg.y >> FIXP16_SHIFT, _16BIT_GETG(*(unsigned short *)(prc->t_pbuffer + (u_beg >> FIXP16_SHIFT << _16BIT_BYTES_SHIFT) + (v_beg >> FIXP16_SHIFT << prc->t_pitch_shift)))),
							COLOR_MUL_16B(c_beg.z >> FIXP16_SHIFT, _16BIT_GETB(*(unsigned short *)(prc->t_pbuffer + (u_beg >> FIXP16_SHIFT << _16BIT_BYTES_SHIFT) + (v_beg >> FIXP16_SHIFT << prc->t_pitch_shift)))));
		#else
					*(unsigned int *)ps = _RGB32BIT(
							COLOR_MUL_32R(c_beg.x >> FIXP16_SHIFT, _32BIT_GETR(*(unsigned int *)(prc->t_pbuffer + (u_beg >> FIXP16_SHIFT << _32BIT_BYTES_SHIFT) + (v_beg >> FIXP16_SHIFT << prc->t_pitch_shift)))),
							COLOR_MUL_32G(c_beg.y >> FIXP16_SHIFT, _32BIT_GETG(*(unsigned int *)(prc->t_pbuffer + (u_beg >> FIXP16_SHIFT << _32BIT_BYTES_SHIFT) + (v_beg >> FIXP16_SHIFT << prc->t_pitch_shift)))),
							COLOR_MUL_32B(c_beg.z >> FIXP16_SHIFT, _32BIT_GETB(*(unsigned int *)(prc->t_pbuffer + (u_beg >> FIXP16_SHIFT << _32BIT_BYTES_SHIFT) + (v_beg >> FIXP16_SHIFT << prc->t_pitch_shift)))));
		#endif
	#else
		#ifdef __draw_16
					*(unsigned short *)ps = (unsigned short)_RGB16BIT(
							COLOR_MUL_16R(_16BIT_GETR(sc.lc.x), _16BIT_GETR(*(unsigned short *)(prc->t_pbuffer + (u_beg >> FIXP16_SHIFT << _16BIT_BYTES_SHIFT) + (v_beg >> FIXP16_SHIFT << prc->t_pitch_shift)))),
							COLOR_MUL_16G(_16BIT_GETG(sc.lc.x), _16BIT_GETG(*(unsigned short *)(prc->t_pbuffer + (u_beg >> FIXP16_SHIFT << _16BIT_BYTES_SHIFT) + (v_beg >> FIXP16_SHIFT << prc->t_pitch_shift)))),
							COLOR_MUL_16B(_16BIT_GETB(sc.lc.x), _16BIT_GETB(*(unsigned short *)(prc->t_pbuffer + (u_beg >> FIXP16_SHIFT << _16BIT_BYTES_SHIFT) + (v_beg >> FIXP16_SHIFT << prc->t_pitch_shift)))));
		#else
					*(unsigned int *)ps = _RGB32BIT(
							COLOR_MUL_32R(_32BIT_GETR(sc.lc.x), _32BIT_GETR(*(unsigned int *)(prc->t_pbuffer + (u_beg >> FIXP16_SHIFT << _32BIT_BYTES_SHIFT) + (v_beg >> FIXP16_SHIFT << prc->t_pitch_shift)))),
							COLOR_MUL_32G(_32BIT_GETG(sc.lc.x), _32BIT_GETG(*(unsigned int *)(prc->t_pbuffer + (u_beg >> FIXP16_SHIFT << _32BIT_BYTES_SHIFT) + (v_beg >> FIXP16_SHIFT << prc->t_pitch_shift)))),
							COLOR_MUL_32B(_32BIT_GETB(sc.lc.x), _32BIT_GETB(*(unsigned int *)(prc->t_pbuffer + (u_beg >> FIXP16_SHIFT << _32BIT_BYTES_SHIFT) + (v_beg >> FIXP16_SHIFT << prc->t_pitch_shift)))));
		#endif
	#endif
#else
	#ifdef __draw_GR
		#ifdef __draw_16
					*(unsigned short *)ps = (unsigned short)_RGB16BIT(
							c_beg.x >> FIXP16_SHIFT, c_beg.y >> FIXP16_SHIFT, c_beg.z >> FIXP16_SHIFT);
		#else
					*(unsigned int *)ps = _RGB32BIT(
							c_beg.x >> FIXP16_SHIFT, c_beg.y >> FIXP16_SHIFT, c_beg.z >> FIXP16_SHIFT);
		#endif
	#else
		#ifdef __draw_16
					*(unsigned short *)ps = (unsigned short)sc.lc.x;
		#else
					*(unsigned int *)ps = sc.lc.x;
		#endif
	#endif
#endif

#ifdef __draw_ZB
					*(_ZBUFF *)pz = _FIXP28_TO_ZBUFF(z_beg);
#endif
				}

#ifdef __draw_16
				ps += _16BIT_BYTES;
#else
				ps += _32BIT_BYTES;
#endif

#ifdef __draw_UV
				u_beg += du;
				v_beg += dv;
#endif

#ifdef __draw_GR
				//VECTOR3DI_Add(&c_beg._3D, &dc._3D);
				c_beg.x += dc.x;
				c_beg.y += dc.y;
				c_beg.z += dc.z;
#endif

#ifdef __draw_ZB
				z_beg += dz;
				pz += _ZBUFF_BYTES;
#endif
			}
		}

		sc.lx += sc.lx_inc;
		sc.rx += sc.rx_inc;

#ifdef __draw_UV
		sc.lu += sc.lu_inc;
		sc.lv += sc.lv_inc;
		sc.ru += sc.ru_inc;
		sc.rv += sc.rv_inc;
#endif

#ifdef __draw_GR
		//VECTOR3DI_Add(&sc.lc._3D, &sc.lc_inc._3D);
		sc.lc.x += sc.lc_inc.x;
		sc.lc.y += sc.lc_inc.y;
		sc.lc.z += sc.lc_inc.z;
		//VECTOR3DI_Add(&sc.rc._3D, &sc.rc_inc._3D);
		sc.rc.x += sc.rc_inc.x;
		sc.rc.y += sc.rc_inc.y;
		sc.rc.z += sc.rc_inc.z;
#endif

#ifdef __draw_ZB
		sc.lz += sc.lz_inc;
		sc.rz += sc.rz_inc;
#endif
	}
}

#undef __draw_UV
#undef __draw_UV_PerspectiveLP
#undef __draw_GR
#undef __draw_ZB
#undef __draw_CLIP
#undef __draw_16
#undef __draw_32
