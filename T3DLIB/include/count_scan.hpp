




#if ( !defined __draw_behind_depth && !defined __draw_in_front_of_depth )
#error must define one between __draw_behind_depth and __draw_in_front_of_depth
#endif

#if (  defined __draw_behind_depth &&  defined __draw_in_front_of_depth )
#error must define one between __draw_behind_depth and __draw_in_front_of_depth
#endif

#if ( !defined __draw_increment && !defined __draw_decrement )
#error must define one between __draw_increment and __draw_decrement
#endif

#if (  defined __draw_increment &&  defined __draw_decrement )
#error must define one between __draw_increment and __draw_decrement
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

#ifdef __draw_clipped
			if(x0 < clipper.left)
			{
				lz += z_inc * (clipper.left - x0);
				x0 = clipper.left;
			}
#endif

#ifdef __draw_clipped
			if(x1 > clipper.right)
			{
				x1 = clipper.right;
			}
#endif

			for(; x0 < x1; x0++)
			{
#ifdef __draw_behind_depth
				if(lz < zbuffer[y0][x0])
#else
				if(lz > zbuffer[y0][x0])
#endif
				{
#ifdef __draw_increment
					stencilbuff[y0][x0]++;
#else
					stencilbuff[y0][x0]--;
#endif
				}

				lz += z_inc;
			}
		}

#undef __draw_clipped
#undef __draw_increment
#undef __draw_decrement
#undef __draw_behind_depth
#undef __draw_in_front_of_depth





