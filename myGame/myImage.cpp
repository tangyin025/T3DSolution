
#include "stdafx.h"
#include "myImage.h"

namespace my
{
#define FAILED_CUSEXCEPT(expr) { if( !(expr) ) T3D_CUSEXCEPT( _T(#expr) ) }

	Image::Image(const std::basic_string<charT> & strFileName)
	{
		FAILED_CUSEXCEPT(m_image.Load(strFileName.c_str()));
	}

	Image::Image(int nWidth, int nHeight, int nBPP, DWORD dwFlags /*= 0*/)
	{
		FAILED_CUSEXCEPT(m_image.Create(nWidth, nHeight, nBPP, dwFlags));
	}

	ImagePtr Image::convertTo16Bits565(void)
	{
		ImagePtr image(new Image(getWidth(), getHeight(), 16, 0));

		HDC hdc = image->getDC();
		HDC hdcSrc = getDC();
		FAILED_CUSEXCEPT(BitBlt(hdc, 0, 0, getWidth(), getHeight(), hdcSrc, 0, 0, SRCCOPY));
		releaseDC();
		image->releaseDC();

		return image;
	}

	ImagePtr Image::convertTo32Bits(void)
	{
		ImagePtr image(new Image(getWidth(), getHeight(), 32, 0));

		HDC hdc = image->getDC();
		HDC hdcSrc = getDC();
		FAILED_CUSEXCEPT(BitBlt(hdc, 0, 0, getWidth(), getHeight(), hdcSrc, 0, 0, SRCCOPY));
		releaseDC();
		image->releaseDC();

		return image;
	}
}
