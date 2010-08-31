




#if ( !defined __draw_func )
#error __draw_func must be defined
#endif

#if (  defined __draw_clipped && !defined __draw_clipped_func )
#error __draw_clipped_func must be defined at __draw_clipped
#endif

		const Vec4<real> * pv0, * pv1, * pv2;

		if(v0.y < v1.y)
		{
			if(v1.y < v2.y)
			{
				pv0 = &v0; pv1 = &v1; pv2 = &v2;
			}
			else if(v0.y < v2.y)
			{
				pv0 = &v0; pv1 = &v2; pv2 = &v1;
			}
			else
			{
				pv0 = &v2; pv1 = &v0; pv2 = &v1;
			}
		}
		else
		{
			if(v0.y < v2.y)
			{
				pv0 = &v1; pv1 = &v0; pv2 = &v2;
			}
			else if(v1.y < v2.y)
			{
				pv0 = &v1; pv1 = &v2; pv2 = &v0;
			}
			else
			{
				pv0 = &v2; pv1 = &v1; pv2 = &v0;
			}
		}

		int y0 = real_to_int(floor(pv0->y));
		int y1 = real_to_int(floor(pv1->y));
		int y2 = real_to_int(floor(pv2->y));

		real x3 = LINE2D_INTERSECT(pv1->y, pv0->y, pv2->y, pv0->x, pv2->x);

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
				fixp28 rz = real_to_fixp28(1 / pv0->z);
				fixp28 rz_inc = (real_to_fixp28(1 / pv2->z) - rz) / (y2 - y0);

				if(
#ifdef __draw_clipped
					y1 > clipper.top &&
#endif
					y0 < y1)
				{
					fixp16 lx = real_to_fixp16(pv0->x);
					fixp16 lx_inc = (real_to_fixp16(pv1->x) - lx) / (y1 - y0);
					fixp28 lz = real_to_fixp28(1 / pv0->z);
					fixp28 lz_inc = (real_to_fixp28(1 / pv1->z) - lz) / (y1 - y0);

#ifdef __draw_clipped
					if(y0 < clipper.top)
					{
						lx += lx_inc * (clipper.top - y0);
						rx += rx_inc * (clipper.top - y0);
						lz += lz_inc * (clipper.top - y0);
						rz += rz_inc * (clipper.top - y0);
						y0 = clipper.top;
					}
#endif // __draw_clipped

#ifdef __draw_clipped
					if(std::min(fixp16_to_real(lx), pv1->x) < clipper.left || std::max(fixp16_to_real(rx), x3) >= clipper.right)
					{
						for(; y0 < std::min(y1, (int)clipper.bottom); y0++)
						{
							__draw_clipped_func
								( stencilbuff
								, clipper
								, zbuffer
								, lx
								, rx
								, y0
								, lz
								, rz
								);

							lx += lx_inc;
							rx += rx_inc;
							lz += lz_inc;
							rz += rz_inc;
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
								( stencilbuff
								, zbuffer
								, lx
								, rx
								, y0
								, lz
								, rz
								);

							lx += lx_inc;
							rx += rx_inc;
							lz += lz_inc;
							rz += rz_inc;
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
					fixp28 lz = real_to_fixp28(1 / pv1->z);
					fixp28 lz_inc = (real_to_fixp28(1 / pv2->z) - lz) / (y2 - y1);

#ifdef __draw_clipped
					if(y1 < clipper.top)
					{
						lx += lx_inc * (clipper.top - y1);
						rx += rx_inc * (clipper.top - y0);
						lz += lz_inc * (clipper.top - y1);
						rz += rz_inc * (clipper.top - y0);
						y1 = clipper.top;
					}
					else if(y1 == clipper.top)
					{
						rx += rx_inc * (clipper.top - y0);
						rz += rz_inc * (clipper.top - y0);
					}
#endif // __draw_clipped

#ifdef __draw_clipped
					if(std::min(fixp16_to_real(lx), pv2->x) < clipper.left || std::max(fixp16_to_real(rx), pv2->x) >= clipper.right)
					{
						for(; y1 < std::min(y2, (int)clipper.bottom); y1++)
						{
							__draw_clipped_func
								( stencilbuff
								, clipper
								, zbuffer
								, lx
								, rx
								, y1
								, lz
								, rz
								);

							lx += lx_inc;
							rx += rx_inc;
							lz += lz_inc;
							rz += rz_inc;
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
								( stencilbuff
								, zbuffer
								, lx
								, rx
								, y1
								, lz
								, rz
								);

							lx += lx_inc;
							rx += rx_inc;
							lz += lz_inc;
							rz += rz_inc;
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
				fixp28 lz = real_to_fixp28(1 / pv0->z);
				fixp28 lz_inc = (real_to_fixp28(1 / pv2->z) - lz) / (y2 - y0);

				if(
#ifdef __draw_clipped
					y1 > clipper.top &&
#endif
					y0 < y1)
				{
					fixp16 rx = real_to_fixp16(pv0->x);
					fixp16 rx_inc = (real_to_fixp16(pv1->x) - rx) / (y1 - y0);
					fixp28 rz = real_to_fixp28(1 / pv0->z);
					fixp28 rz_inc = (real_to_fixp28(1 / pv1->z) - rz) / (y1 - y0);

#ifdef __draw_clipped
					if(y0 < clipper.top)
					{
						rx += rx_inc * (clipper.top - y0);
						lx += lx_inc * (clipper.top - y0);
						rz += rz_inc * (clipper.top - y0);
						lz += lz_inc * (clipper.top - y0);
						y0 = clipper.top;
					}
#endif // __draw_clipped

#ifdef __draw_clipped
					if(std::min(fixp16_to_real(lx), x3) < clipper.left || std::max(fixp16_to_real(rx), pv1->x) >= clipper.right)
					{
						for(; y0 < std::min(y1, (int)clipper.bottom); y0++)
						{
							__draw_clipped_func
								( stencilbuff
								, clipper
								, zbuffer
								, lx
								, rx
								, y0
								, lz
								, rz
								);

							rx += rx_inc;
							lx += lx_inc;
							rz += rz_inc;
							lz += lz_inc;
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
								( stencilbuff
								, zbuffer
								, lx
								, rx
								, y0
								, lz
								, rz
								);

							rx += rx_inc;
							lx += lx_inc;
							rz += rz_inc;
							lz += lz_inc;
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
					fixp28 rz = real_to_fixp28(1 / pv1->z);
					fixp28 rz_inc = (real_to_fixp28(1 / pv2->z) - rz) / (y2 - y1);

#ifdef __draw_clipped
					if(y1 < clipper.top)
					{
						rx += rx_inc * (clipper.top - y1);
						lx += lx_inc * (clipper.top - y0);
						rz += rz_inc * (clipper.top - y1);
						lz += lz_inc * (clipper.top - y0);
						y1 = clipper.top;
					}
					else if(y1 == clipper.top)
					{
						lx += lx_inc * (clipper.top - y0);
						lz += lz_inc * (clipper.top - y0);
					}
#endif // __draw_clipped

#ifdef __draw_clipped
					if(std::min(fixp16_to_real(lx), pv2->x) < clipper.left || std::max(fixp16_to_real(rx), pv2->x) >= clipper.right)
					{
						for(; y1 < std::min(y2, (int)clipper.bottom); y1++)
						{
							__draw_clipped_func
								( stencilbuff
								, clipper
								, zbuffer
								, lx
								, rx
								, y1
								, lz
								, rz
								);

							rx += rx_inc;
							lx += lx_inc;
							rz += rz_inc;
							lz += lz_inc;
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
								( stencilbuff
								, zbuffer
								, lx
								, rx
								, y1
								, lz
								, rz
								);

							rx += rx_inc;
							lx += lx_inc;
							rz += rz_inc;
							lz += lz_inc;
						}
					}
				}
			}
		}

#undef __draw_clipped
#undef __draw_func
#undef __draw_clipped_func





