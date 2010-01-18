
#ifndef __MYIMAGE_H__
#define __MYIMAGE_H__

#include "myCommon.h"
#pragma push_macro("min")
#pragma push_macro("max")
#define min std::min
#define max std::max
#include <atlimage.h>
#pragma pop_macro("max")
#pragma pop_macro("min")
#include <boost/shared_ptr.hpp>

namespace my
{
	class Image;

	typedef boost::shared_ptr<Image> ImagePtr;

	class Image
	{
	protected:
		CImage m_image;

	public:
		Image(const std::basic_string<charT> & strFileName);

		Image(int nWidth, int nHeight, int nBPP, DWORD dwFlags = 0);

		int getBPP(void) const
		{
			return m_image.GetBPP();
		}

		int getWidth(void) const
		{
			return m_image.GetWidth();
		}

		int getHeight(void) const
		{
			return m_image.GetHeight();
		}

		int getPitch(void) const
		{
			return m_image.GetPitch();
		}

		void * getBits(void)
		{
			return m_image.GetBits();
		}

		HDC getDC(void) const
		{
			return m_image.GetDC();
		}

		void releaseDC(void) const
		{
			m_image.ReleaseDC();
		}

		ImagePtr convertTo16Bits565(void) const;

		ImagePtr convertTo32Bits(void) const;
	};
}

#endif // __MYIMAGE_H__
