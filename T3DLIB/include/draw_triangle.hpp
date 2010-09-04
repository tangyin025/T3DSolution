




#if ( !defined __draw_func )
#error __draw_func must be defined
#endif

#if (  defined __draw_clipped && !defined __draw_clipped_func )
#error __draw_clipped_func must be defined at __draw_clipped
#endif

		const Vec4<real> * pv0, * pv1, * pv2;
#ifdef __draw_gouraud
		const Vec4<real> * pc0, * pc1, * pc2;
#endif
#ifdef __draw_texture
		const Vec2<real> * pt0, * pt1, * pt2;
#endif

		if(v0.y < v1.y)
		{
			if(v1.y < v2.y)
			{
				pv0 = &v0; pv1 = &v1; pv2 = &v2;
#ifdef __draw_gouraud
				pc0 = &c0; pc1 = &c1; pc2 = &c2;
#endif
#ifdef __draw_texture
				pt0 = &t0; pt1 = &t1; pt2 = &t2;
#endif
			}
			else if(v0.y < v2.y)
			{
				pv0 = &v0; pv1 = &v2; pv2 = &v1;
#ifdef __draw_gouraud
				pc0 = &c0; pc1 = &c2; pc2 = &c1;
#endif
#ifdef __draw_texture
				pt0 = &t0; pt1 = &t2; pt2 = &t1;
#endif
			}
			else
			{
				pv0 = &v2; pv1 = &v0; pv2 = &v1;
#ifdef __draw_gouraud
				pc0 = &c2; pc1 = &c0; pc2 = &c1;
#endif
#ifdef __draw_texture
				pt0 = &t2; pt1 = &t0; pt2 = &t1;
#endif
			}
		}
		else
		{
			if(v0.y < v2.y)
			{
				pv0 = &v1; pv1 = &v0; pv2 = &v2;
#ifdef __draw_gouraud
				pc0 = &c1; pc1 = &c0; pc2 = &c2;
#endif
#ifdef __draw_texture
				pt0 = &t1; pt1 = &t0; pt2 = &t2;
#endif
			}
			else if(v1.y < v2.y)
			{
				pv0 = &v1; pv1 = &v2; pv2 = &v0;
#ifdef __draw_gouraud
				pc0 = &c1; pc1 = &c2; pc2 = &c0;
#endif
#ifdef __draw_texture
				pt0 = &t1; pt1 = &t2; pt2 = &t0;
#endif
			}
			else
			{
				pv0 = &v2; pv1 = &v1; pv2 = &v0;
#ifdef __draw_gouraud
				pc0 = &c2; pc1 = &c1; pc2 = &c0;
#endif
#ifdef __draw_texture
				pt0 = &t2; pt1 = &t1; pt2 = &t0;
#endif
			}
		}

		int y0 = real_to_int(floor(pv0->y));
		int y1 = real_to_int(floor(pv1->y));
		int y2 = real_to_int(floor(pv2->y));

		real x3 = LINE2D_INTERSECT(floor(pv1->y), floor(pv0->y), floor(pv2->y), pv0->x, pv2->x);

		if(pv1->x < x3)
		{
			/****************************************************************************
			 *		0
			 *	1
			 *		2
			 ****************************************************************************/

			if(
#ifdef __draw_clipped
				y0 < clipper.bottom &&
				y2 > clipper.top &&
#endif
				y0 < y2)
			{
				fixp16 rx = real_to_fixp16(pv0->x);
				fixp16 rx_inc = (real_to_fixp16(pv2->x) - rx) / (y2 - y0);
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
#ifdef __draw_texture_perspective_lp
				real rz = 1 / pv0->z;
				real rz_inc = (1 / pv2->z - rz) / (y2 - y0);
#else
				fixp28 rz = real_to_fixp28(1 / pv0->z);
				fixp28 rz_inc = (real_to_fixp28(1 / pv2->z) - rz) / (y2 - y0);
#endif
#endif
#ifdef __draw_gouraud
				Vec4<fixp16> rc = real_to_fixp16(*pc0);
				Vec4<fixp16> rc_inc = (real_to_fixp16(*pc2) - rc) / (y2 - y0);
#endif
#ifdef __draw_texture
#ifdef __draw_texture_perspective_lp
				Vec2<real> rt = *pt0 / pv0->z;
				Vec2<real> rt_inc = (*pt2 / pv2->z - rt) / (y2 - y0);
#else
				Vec2<fixp16> rt = real_to_fixp16(*pt0);
				Vec2<fixp16> rt_inc = (real_to_fixp16(*pt2) - rt) / (y2 - y0);
#endif
#endif

				if(
#ifdef __draw_clipped
					y1 > clipper.top &&
#endif
					y0 < y1)
				{
					fixp16 lx = real_to_fixp16(pv0->x);
					fixp16 lx_inc = (real_to_fixp16(pv1->x) - lx) / (y1 - y0);
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
#ifdef __draw_texture_perspective_lp
					real lz = 1 / pv0->z;
					real lz_inc = (1 / pv1->z - lz) / (y1 - y0);
#else
					fixp28 lz = real_to_fixp28(1 / pv0->z);
					fixp28 lz_inc = (real_to_fixp28(1 / pv1->z) - lz) / (y1 - y0);
#endif
#endif
#ifdef __draw_gouraud
					Vec4<fixp16> lc = real_to_fixp16(*pc0);
					Vec4<fixp16> lc_inc = (real_to_fixp16(*pc1) - lc) / (y1 - y0);
#endif
#ifdef __draw_texture
#ifdef __draw_texture_perspective_lp
					Vec2<real> lt = *pt0 / pv0->z;
					Vec2<real> lt_inc = (*pt1 / pv1->z - lt) / (y1 - y0);
#else
					Vec2<fixp16> lt = real_to_fixp16(*pt0);
					Vec2<fixp16> lt_inc = (real_to_fixp16(*pt1) - lt) / (y1 - y0);
#endif
#endif

#ifdef __draw_clipped
					if(y0 < clipper.top)
					{
						lx += lx_inc * (clipper.top - y0);
						rx += rx_inc * (clipper.top - y0);
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
						lz += lz_inc * (clipper.top - y0);
						rz += rz_inc * (clipper.top - y0);
#endif
#ifdef __draw_gouraud
						lc += lc_inc * (clipper.top - y0);
						rc += rc_inc * (clipper.top - y0);
#endif
#ifdef __draw_texture
						lt += lt_inc * (clipper.top - y0);
						rt += rt_inc * (clipper.top - y0);
#endif
						y0 = clipper.top;
					}
#endif // __draw_clipped

#ifdef __draw_clipped
					if(std::min(fixp16_to_real(lx), pv1->x) < clipper.left || std::max(fixp16_to_real(rx), x3) >= clipper.right)
					{
						for(; y0 < std::min(y1, (int)clipper.bottom); y0++)
						{
							__draw_clipped_func
								( surface
								, clipper
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
								, zbuffer
#endif
#ifdef __draw_texture
								, texture
#endif
								, lx
								, rx
								, y0
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
#ifdef __draw_texture_perspective_lp
								, real_to_fixp28(lz)
								, real_to_fixp28(rz)
#else
								, lz
								, rz
#endif
#endif
#ifdef __draw_gouraud
								, lc
								, rc
#elif !defined(__draw_texture)
								, real_to_fixp16(color)
#endif
#ifdef __draw_texture
#ifdef __draw_texture_perspective_lp
								, real_to_fixp16(lt / lz)
								, real_to_fixp16(rt / rz)
#else
								, lt
								, rt
#endif
#endif
								);

							lx += lx_inc;
							rx += rx_inc;
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
							lz += lz_inc;
							rz += rz_inc;
#endif
#ifdef __draw_gouraud
							lc += lc_inc;
							rc += rc_inc;
#endif
#ifdef __draw_texture
							lt += lt_inc;
							rt += rt_inc;
#endif
						}
					}
					else
#endif // __draw_clipped
					{
						for(;
#ifdef __draw_clipped
							y0 < clipper.bottom &&
#endif
							y0 < y1; y0++)
						{
							__draw_func
								( surface
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
								, zbuffer
#endif
#ifdef __draw_texture
								, texture
#endif
								, lx
								, rx
								, y0
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
#ifdef __draw_texture_perspective_lp
								, real_to_fixp28(lz)
								, real_to_fixp28(rz)
#else
								, lz
								, rz
#endif
#endif
#ifdef __draw_gouraud
								, lc
								, rc
#elif !defined(__draw_texture)
								, real_to_fixp16(color)
#endif
#ifdef __draw_texture
#ifdef __draw_texture_perspective_lp
								, real_to_fixp16(lt / lz)
								, real_to_fixp16(rt / rz)
#else
								, lt
								, rt
#endif
#endif
								);

							lx += lx_inc;
							rx += rx_inc;
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
							lz += lz_inc;
							rz += rz_inc;
#endif
#ifdef __draw_gouraud
							lc += lc_inc;
							rc += rc_inc;
#endif
#ifdef __draw_texture
							lt += lt_inc;
							rt += rt_inc;
#endif
						}
					}
				}

				if(
#ifdef __draw_clipped
					y1 < clipper.bottom &&
#endif
					y1 < y2)
				{
					fixp16 lx = real_to_fixp16(pv1->x);
					fixp16 lx_inc = (real_to_fixp16(pv2->x) - lx) / (y2 - y1);
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
#ifdef __draw_texture_perspective_lp
					real lz = 1 / pv1->z;
					real lz_inc = (1 / pv2->z - lz) / (y2 - y1);
#else
					fixp28 lz = real_to_fixp28(1 / pv1->z);
					fixp28 lz_inc = (real_to_fixp28(1 / pv2->z) - lz) / (y2 - y1);
#endif
#endif
#ifdef __draw_gouraud
					Vec4<fixp16> lc = real_to_fixp16(*pc1);
					Vec4<fixp16> lc_inc = (real_to_fixp16(*pc2) - lc) / (y2 - y1);
#endif
#ifdef __draw_texture
#ifdef __draw_texture_perspective_lp
					Vec2<real> lt = *pt1 / pv1->z;
					Vec2<real> lt_inc = (*pt2 / pv2->z - lt) / (y2 - y1);
#else
					Vec2<fixp16> lt = real_to_fixp16(*pt1);
					Vec2<fixp16> lt_inc = (real_to_fixp16(*pt2) - lt) / (y2 - y1);
#endif
#endif

#ifdef __draw_clipped
					if(y1 < clipper.top)
					{
						lx += lx_inc * (clipper.top - y1);
						rx += rx_inc * (clipper.top - y0);
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
						lz += lz_inc * (clipper.top - y1);
						rz += rz_inc * (clipper.top - y0);
#endif
#ifdef __draw_gouraud
						lc += lc_inc * (clipper.top - y1);
						rc += rc_inc * (clipper.top - y0);
#endif
#ifdef __draw_texture
						lt += lt_inc * (clipper.top - y1);
						rt += rt_inc * (clipper.top - y0);
#endif
						y1 = clipper.top;
					}
					else if(y1 == clipper.top)
					{
						rx += rx_inc * (clipper.top - y0);
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
						rz += rz_inc * (clipper.top - y0);
#endif
#ifdef __draw_gouraud
						rc += rc_inc * (clipper.top - y0);
#endif
#ifdef __draw_texture
						rt += rt_inc * (clipper.top - y0);
#endif
					}
#endif // __draw_clipped

#ifdef __draw_clipped
					if(std::min(fixp16_to_real(lx), pv2->x) < clipper.left || std::max(fixp16_to_real(rx), pv2->x) >= clipper.right)
					{
						for(; y1 < std::min(y2, (int)clipper.bottom); y1++)
						{
							__draw_clipped_func
								( surface
								, clipper
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
								, zbuffer
#endif
#ifdef __draw_texture
								, texture
#endif
								, lx
								, rx
								, y1
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
#ifdef __draw_texture_perspective_lp
								, real_to_fixp28(lz)
								, real_to_fixp28(rz)
#else
								, lz
								, rz
#endif
#endif
#ifdef __draw_gouraud
								, lc
								, rc
#elif !defined(__draw_texture)
								, real_to_fixp16(color)
#endif
#ifdef __draw_texture
#ifdef __draw_texture_perspective_lp
								, real_to_fixp16(lt / lz)
								, real_to_fixp16(rt / rz)
#else
								, lt
								, rt
#endif
#endif
								);

							lx += lx_inc;
							rx += rx_inc;
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
							lz += lz_inc;
							rz += rz_inc;
#endif
#ifdef __draw_gouraud
							lc += lc_inc;
							rc += rc_inc;
#endif
#ifdef __draw_texture
							lt += lt_inc;
							rt += rt_inc;
#endif
						}
					}
					else
#endif // __draw_clipped
					{
						for(;
#ifdef __draw_clipped
							y1 < clipper.bottom &&
#endif
							y1 < y2; y1++)
						{
							__draw_func
								( surface
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
								, zbuffer
#endif
#ifdef __draw_texture
								, texture
#endif
								, lx
								, rx
								, y1
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
#ifdef __draw_texture_perspective_lp
								, real_to_fixp28(lz)
								, real_to_fixp28(rz)
#else
								, lz
								, rz
#endif
#endif
#ifdef __draw_gouraud
								, lc
								, rc
#elif !defined(__draw_texture)
								, real_to_fixp16(color)
#endif
#ifdef __draw_texture
#ifdef __draw_texture_perspective_lp
								, real_to_fixp16(lt / lz)
								, real_to_fixp16(rt / rz)
#else
								, lt
								, rt
#endif
#endif
								);

							lx += lx_inc;
							rx += rx_inc;
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
							lz += lz_inc;
							rz += rz_inc;
#endif
#ifdef __draw_gouraud
							lc += lc_inc;
							rc += rc_inc;
#endif
#ifdef __draw_texture
							lt += lt_inc;
							rt += rt_inc;
#endif
						}
					}
				}
			}
		}
		else
		{
			/**********************************************************************
			*	0
			*		1
			*	2
			**********************************************************************/

			if(
#ifdef __draw_clipped
				y0 < clipper.bottom &&
				y2 > clipper.top &&
#endif
				y0 < y2)
			{
				fixp16 lx = real_to_fixp16(pv0->x);
				fixp16 lx_inc = (real_to_fixp16(pv2->x) - lx) / (y2 - y0);
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
#ifdef __draw_texture_perspective_lp
				real lz = 1 / pv0->z;
				real lz_inc = (1 / pv2->z - lz) / (y2 - y0);
#else
				fixp28 lz = real_to_fixp28(1 / pv0->z);
				fixp28 lz_inc = (real_to_fixp28(1 / pv2->z) - lz) / (y2 - y0);
#endif
#endif
#ifdef __draw_gouraud
				Vec4<fixp16> lc = real_to_fixp16(*pc0);
				Vec4<fixp16> lc_inc = (real_to_fixp16(*pc2) - lc) / (y2 - y0);
#endif
#ifdef __draw_texture
#ifdef __draw_texture_perspective_lp
				Vec2<real> lt = *pt0 / pv0->z;
				Vec2<real> lt_inc = (*pt2 / pv2->z - lt) / (y2 - y0);
#else
				Vec2<fixp16> lt = real_to_fixp16(*pt0);
				Vec2<fixp16> lt_inc = (real_to_fixp16(*pt2) - lt) / (y2 - y0);
#endif
#endif

				if(
#ifdef __draw_clipped
					y1 > clipper.top &&
#endif
					y0 < y1)
				{
					fixp16 rx = real_to_fixp16(pv0->x);
					fixp16 rx_inc = (real_to_fixp16(pv1->x) - rx) / (y1 - y0);
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
#ifdef __draw_texture_perspective_lp
					real rz = 1 / pv0->z;
					real rz_inc = (1 / pv1->z - rz) / (y1 - y0);
#else
					fixp28 rz = real_to_fixp28(1 / pv0->z);
					fixp28 rz_inc = (real_to_fixp28(1 / pv1->z) - rz) / (y1 - y0);
#endif
#endif
#ifdef __draw_gouraud
					Vec4<fixp16> rc = real_to_fixp16(*pc0);
					Vec4<fixp16> rc_inc = (real_to_fixp16(*pc1) - rc) / (y1 - y0);
#endif
#ifdef __draw_texture
#ifdef __draw_texture_perspective_lp
					Vec2<real> rt = *pt0 / pv0->z;
					Vec2<real> rt_inc = (*pt1 / pv1->z - rt) / (y1 - y0);
#else
					Vec2<fixp16> rt = real_to_fixp16(*pt0);
					Vec2<fixp16> rt_inc = (real_to_fixp16(*pt1) - rt) / (y1 - y0);
#endif
#endif

#ifdef __draw_clipped
					if(y0 < clipper.top)
					{
						rx += rx_inc * (clipper.top - y0);
						lx += lx_inc * (clipper.top - y0);
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
						rz += rz_inc * (clipper.top - y0);
						lz += lz_inc * (clipper.top - y0);
#endif
#ifdef __draw_gouraud
						rc += rc_inc * (clipper.top - y0);
						lc += lc_inc * (clipper.top - y0);
#endif
#ifdef __draw_texture
						rt += rt_inc * (clipper.top - y0);
						lt += lt_inc * (clipper.top - y0);
#endif
						y0 = clipper.top;
					}
#endif // __draw_clipped

#ifdef __draw_clipped
					if(std::min(fixp16_to_real(lx), x3) < clipper.left || std::max(fixp16_to_real(rx), pv1->x) >= clipper.right)
					{
						for(; y0 < std::min(y1, (int)clipper.bottom); y0++)
						{
							__draw_clipped_func
								( surface
								, clipper
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
								, zbuffer
#endif
#ifdef __draw_texture
								, texture
#endif
								, lx
								, rx
								, y0
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
#ifdef __draw_texture_perspective_lp
								, real_to_fixp28(lz)
								, real_to_fixp28(rz)
#else
								, lz
								, rz
#endif
#endif
#ifdef __draw_gouraud
								, lc
								, rc
#elif !defined(__draw_texture)
								, real_to_fixp16(color)
#endif
#ifdef __draw_texture
#ifdef __draw_texture_perspective_lp
								, real_to_fixp16(lt / lz)
								, real_to_fixp16(rt / rz)
#else
								, lt
								, rt
#endif
#endif
								);

							rx += rx_inc;
							lx += lx_inc;
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
							rz += rz_inc;
							lz += lz_inc;
#endif
#ifdef __draw_gouraud
							rc += rc_inc;
							lc += lc_inc;
#endif
#ifdef __draw_texture
							rt += rt_inc;
							lt += lt_inc;
#endif
						}
					}
					else
#endif // __draw_clipped
					{
						for(;
#ifdef __draw_clipped
							y0 < clipper.bottom &&
#endif
							y0 < y1; y0++)
						{
							__draw_func
								( surface
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
								, zbuffer
#endif
#ifdef __draw_texture
								, texture
#endif
								, lx
								, rx
								, y0
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
#ifdef __draw_texture_perspective_lp
								, real_to_fixp28(lz)
								, real_to_fixp28(rz)
#else
								, lz
								, rz
#endif
#endif
#ifdef __draw_gouraud
								, lc
								, rc
#elif !defined(__draw_texture)
								, real_to_fixp16(color)
#endif
#ifdef __draw_texture
#ifdef __draw_texture_perspective_lp
								, real_to_fixp16(lt / lz)
								, real_to_fixp16(rt / rz)
#else
								, lt
								, rt
#endif
#endif
								);

							rx += rx_inc;
							lx += lx_inc;
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
							rz += rz_inc;
							lz += lz_inc;
#endif
#ifdef __draw_gouraud
							rc += rc_inc;
							lc += lc_inc;
#endif
#ifdef __draw_texture
							rt += rt_inc;
							lt += lt_inc;
#endif
						}
					}
				}

				if(
#ifdef __draw_clipped
					y1 < clipper.bottom &&
#endif
					y1 < y2)
				{
					fixp16 rx = real_to_fixp16(pv1->x);
					fixp16 rx_inc = (real_to_fixp16(pv2->x) - rx) / (y2 - y1);
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
#ifdef __draw_texture_perspective_lp
					real rz = 1 / pv1->z;
					real rz_inc = (1 / pv2->z - rz) / (y2 - y1);
#else
					fixp28 rz = real_to_fixp28(1 / pv1->z);
					fixp28 rz_inc = (real_to_fixp28(1 / pv2->z) - rz) / (y2 - y1);
#endif
#endif
#ifdef __draw_gouraud
					Vec4<fixp16> rc = real_to_fixp16(*pc1);
					Vec4<fixp16> rc_inc = (real_to_fixp16(*pc2) - rc) / (y2 - y1);
#endif
#ifdef __draw_texture
#ifdef __draw_texture_perspective_lp
					Vec2<real> rt = *pt1 / pv1->z;
					Vec2<real> rt_inc = (*pt2 / pv2->z - rt) / (y2 - y1);
#else
					Vec2<fixp16> rt = real_to_fixp16(*pt1);
					Vec2<fixp16> rt_inc = (real_to_fixp16(*pt2) - rt) / (y2 - y1);
#endif
#endif

#ifdef __draw_clipped
					if(y1 < clipper.top)
					{
						rx += rx_inc * (clipper.top - y1);
						lx += lx_inc * (clipper.top - y0);
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
						rz += rz_inc * (clipper.top - y1);
						lz += lz_inc * (clipper.top - y0);
#endif
#ifdef __draw_gouraud
						rc += rc_inc * (clipper.top - y1);
						lc += lc_inc * (clipper.top - y0);
#endif
#ifdef __draw_texture
						rt += rt_inc * (clipper.top - y1);
						lt += lt_inc * (clipper.top - y0);
#endif
						y1 = clipper.top;
					}
					else if(y1 == clipper.top)
					{
						lx += lx_inc * (clipper.top - y0);
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
						lz += lz_inc * (clipper.top - y0);
#endif
#ifdef __draw_gouraud
						lc += lc_inc * (clipper.top - y0);
#endif
#ifdef __draw_texture
						lt += lt_inc * (clipper.top - y0);
#endif
					}
#endif // __draw_clipped

#ifdef __draw_clipped
					if(std::min(fixp16_to_real(lx), pv2->x) < clipper.left || std::max(fixp16_to_real(rx), pv2->x) >= clipper.right)
					{
						for(; y1 < std::min(y2, (int)clipper.bottom); y1++)
						{
							__draw_clipped_func
								( surface
								, clipper
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
								, zbuffer
#endif
#ifdef __draw_texture
								, texture
#endif
								, lx
								, rx
								, y1
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
#ifdef __draw_texture_perspective_lp
								, real_to_fixp28(lz)
								, real_to_fixp28(rz)
#else
								, lz
								, rz
#endif
#endif
#ifdef __draw_gouraud
								, lc
								, rc
#elif !defined(__draw_texture)
								, real_to_fixp16(color)
#endif
#ifdef __draw_texture
#ifdef __draw_texture_perspective_lp
								, real_to_fixp16(lt / lz)
								, real_to_fixp16(rt / rz)
#else

								, lt
								, rt
#endif
#endif
								);

							rx += rx_inc;
							lx += lx_inc;
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
							rz += rz_inc;
							lz += lz_inc;
#endif
#ifdef __draw_gouraud
							rc += rc_inc;
							lc += lc_inc;
#endif
#ifdef __draw_texture
							rt += rt_inc;
							lt += lt_inc;
#endif
						}
					}
					else
#endif // __draw_clipped
					{
						for(;
#ifdef __draw_clipped
							y1 < clipper.bottom &&
#endif
							y1 < y2; y1++)
						{
							__draw_func
								( surface
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
								, zbuffer
#endif
#ifdef __draw_texture
								, texture
#endif
								, lx
								, rx
								, y1
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
#ifdef __draw_texture_perspective_lp
								, real_to_fixp28(lz)
								, real_to_fixp28(rz)
#else
								, lz
								, rz
#endif
#endif
#ifdef __draw_gouraud
								, lc
								, rc
#elif !defined(__draw_texture)
								, real_to_fixp16(color)
#endif
#ifdef __draw_texture
#ifdef __draw_texture_perspective_lp
								, real_to_fixp16(lt / lz)
								, real_to_fixp16(rt / rz)
#else
								, lt
								, rt
#endif
#endif
								);

							rx += rx_inc;
							lx += lx_inc;
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
							rz += rz_inc;
							lz += lz_inc;
#endif
#ifdef __draw_gouraud
							rc += rc_inc;
							lc += lc_inc;
#endif
#ifdef __draw_texture
							rt += rt_inc;
							lt += lt_inc;
#endif
						}
					}
				}
			}
		}

#undef __draw_texture
#undef __draw_texture_perspective_lp
#undef __draw_gouraud
#undef __draw_zbuffer_r
#undef __draw_zbuffer_w
#undef __draw_clipped
#undef __draw_16bit
#undef __draw_32bit
#undef __draw_func
#undef __draw_clipped_func





