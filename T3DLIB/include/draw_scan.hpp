




#if ( !defined __draw_16bit && !defined __draw_32bit )
#error must define one between __draw_16bit and __draw_32bit
#endif

#if (  defined __draw_16bit &&  defined __draw_32bit )
#error must define one between __draw_16bit and __draw_32bit
#endif

#ifdef __draw_clipped
		_ASSERT(y0 >= clipper.top && y0 < clipper.bottom);
#endif

		int x0 = fixp16_to_int(lx);
		int x1 = fixp16_to_int(rx);

		if(
#ifdef __draw_clipped
			x0 < clipper.right &&
			x1 > clipper.left &&
#endif
			x0 < x1)
		{
			fixp28 z_inc = (rz - lz) / (x1 - x0);
#ifdef __draw_gouraud
			Vec4<fixp16> c_inc = (rc - lc) / (x1 - x0);
#endif
#ifdef __draw_texture
			Vec2<fixp16> t_inc = (rt - lt) / (x1 - x0);
#endif

#ifdef __draw_clipped
			if(x0 < clipper.left)
			{
#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
				lz += z_inc * (clipper.left - x0);
#endif
#ifdef __draw_gouraud
				lc += c_inc * (clipper.left - x0);
#endif
#ifdef __draw_texture
				lt += t_inc * (clipper.left - x0);
#endif
				x0 = clipper.left;
			}
#endif // __draw_clipped

#ifdef __draw_clipped
			if(x1 > clipper.right)
			{
				x1 = clipper.right;
			}
#endif

			for(; x0 < x1; x0++)
			{
#ifdef __draw_zbuffer_r
				if(lz > zbuffer[y0][x0])
#endif
				{
#ifdef __draw_gouraud
	#ifdef __draw_texture
		#ifdef __draw_16bit
					surface[y0][x0] = _RGB16BIT_WITHOUT_RSHIFT(
						_COLORMUL(_RGB16GETR(texture[fixp16_to_int(lt.y)][fixp16_to_int(lt.x)]), fixp16_to_int(lc.x)),
						_COLORMUL(_RGB16GETG(texture[fixp16_to_int(lt.y)][fixp16_to_int(lt.x)]), fixp16_to_int(lc.y)),
						_COLORMUL(_RGB16GETB(texture[fixp16_to_int(lt.y)][fixp16_to_int(lt.x)]), fixp16_to_int(lc.z)));
		#else
					surface[y0][x0] = _RGB32BIT(
						_COLORMUL(_RGB32GETR(texture[fixp16_to_int(lt.y)][fixp16_to_int(lt.x)]), fixp16_to_int(lc.x)),
						_COLORMUL(_RGB32GETG(texture[fixp16_to_int(lt.y)][fixp16_to_int(lt.x)]), fixp16_to_int(lc.y)),
						_COLORMUL(_RGB32GETB(texture[fixp16_to_int(lt.y)][fixp16_to_int(lt.x)]), fixp16_to_int(lc.z)));
		#endif
	#else // __draw_texture
		#ifdef __draw_16bit
					surface[y0][x0] = _RGB16BIT(fixp16_to_int(lc.x), fixp16_to_int(lc.y), fixp16_to_int(lc.z));
		#else
					surface[y0][x0] = _RGB32BIT(fixp16_to_int(lc.x), fixp16_to_int(lc.y), fixp16_to_int(lc.z));
		#endif
	#endif // __draw_texture
#else // __draw_gouraud
	#ifdef __draw_texture
					surface[y0][x0] = texture[fixp16_to_int(lt.y)][fixp16_to_int(lt.x)];
	#else // __draw_texture
		#ifdef __draw_16bit
					surface[y0][x0] = _RGB16BIT(fixp16_to_int(color.x), fixp16_to_int(color.y), fixp16_to_int(color.z));
		#else
					surface[y0][x0] = _RGB32BIT(fixp16_to_int(color.x), fixp16_to_int(color.y), fixp16_to_int(color.z));
		#endif
	#endif // __draw_texture
#endif // __draw_gouraud

#ifdef __draw_zbuffer_w
					zbuffer[y0][x0] = lz;
#endif
				}

#if defined(__draw_zbuffer_r) || defined(__draw_zbuffer_w)
				lz += z_inc;
#endif
#ifdef __draw_gouraud
				lc += c_inc;
#endif
#ifdef __draw_texture
				lt += t_inc;
#endif
			}
		}

#undef __draw_texture
#undef __draw_gouraud
#undef __draw_zbuffer_r
#undef __draw_zbuffer_w
#undef __draw_clipped
#undef __draw_16bit
#undef __draw_32bit





