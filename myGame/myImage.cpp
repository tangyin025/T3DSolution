
#include "stdafx.h"
#include "myImage.h"

#ifdef _UNICODE
#define FreeImage_GetFileType FreeImage_GetFileTypeU
#define FreeImage_Load FreeImage_LoadU
#define FreeImage_Save FreeImage_SaveU
#endif

#include <cassert>
#include <sstream>

#ifdef _DEBUG
#pragma comment(lib, "freeimaged.lib")
#else
#pragma comment(lib, "freeimage.lib")
#endif

namespace my
{
	static unsigned DLL_CALLCONV _ReadProc(void *buffer, unsigned size, unsigned count, fi_handle handle)
	{
		return (unsigned)static_cast<IOStream *>(handle)->read(buffer, size, count);
	}

	static unsigned DLL_CALLCONV _WriteProc(void *buffer, unsigned size, unsigned count, fi_handle handle)
	{
		return (unsigned)static_cast<IOStream *>(handle)->write(buffer, size, count);
	}

	static int DLL_CALLCONV _SeekProc(fi_handle handle, long offset, int origin)
	{
		return static_cast<IOStream *>(handle)->seek(offset, origin);
	}

	static long DLL_CALLCONV _TellProc(fi_handle handle)
	{
		return static_cast<IOStream *>(handle)->tell();
	}

	static inline void SetMyIOStreamIO(FreeImageIO *io)
	{
		io->read_proc  = _ReadProc;
		io->seek_proc  = _SeekProc;
		io->tell_proc  = _TellProc;
		io->write_proc = _WriteProc;
	}

	Image::InitManager::InitManager(void)
	{
		FreeImage_Initialise();
	}

	Image::InitManager::~InitManager(void)
	{
#ifdef FREEIMAGE_LIB
		FreeImage_DeInitialise();
#endif
	}

	Image::InitManager Image::m_initMgr;

	std::basic_string<charT> Image::getFIFStr(FREE_IMAGE_FORMAT fif)
	{
		const charT * pstr;
		switch(fif)
		{
		case FIF_UNKNOWN:
			pstr = _T("FIF_UNKNOWN"); break;
		case FIF_BMP:
			pstr = _T("FIF_BMP"); break;
		case FIF_ICO:
			pstr = _T("FIF_ICO"); break;
		case FIF_JPEG:
			pstr = _T("FIF_JPEG"); break;
		case FIF_JNG:
			pstr = _T("FIF_JNG"); break;
		case FIF_KOALA:
			pstr = _T("FIF_KOALA"); break;
		case FIF_LBM:
			pstr = _T("FIF_LBM"); break;
		//case FIF_IFF:
		//	pstr = _T("FIF_IFF"); break;
		case FIF_MNG:
			pstr = _T("FIF_MNG"); break;
		case FIF_PBM:
			pstr = _T("FIF_PBM"); break;
		case FIF_PBMRAW:
			pstr = _T("FIF_PBMRAW"); break;
		case FIF_PCD:
			pstr = _T("FIF_PCD"); break;
		case FIF_PCX:
			pstr = _T("FIF_PCX"); break;
		case FIF_PGM:
			pstr = _T("FIF_PGM"); break;
		case FIF_PGMRAW:
			pstr = _T("FIF_PGMRAW"); break;
		case FIF_PNG:
			pstr = _T("FIF_PNG"); break;
		case FIF_PPM:
			pstr = _T("FIF_PPM"); break;
		case FIF_PPMRAW:
			pstr = _T("FIF_PPMRAW"); break;
		case FIF_RAS:
			pstr = _T("FIF_RAS"); break;
		case FIF_TARGA:
			pstr = _T("FIF_TARGA"); break;
		case FIF_TIFF:
			pstr = _T("FIF_TIFF"); break;
		case FIF_WBMP:
			pstr = _T("FIF_WBMP"); break;
		case FIF_PSD:
			pstr = _T("FIF_PSD"); break;
		case FIF_CUT:
			pstr = _T("FIF_CUT"); break;
		case FIF_XBM:
			pstr = _T("FIF_XBM"); break;
		case FIF_XPM:
			pstr = _T("FIF_XPM"); break;
		case FIF_DDS:
			pstr = _T("FIF_DDS"); break;
		case FIF_GIF:
			pstr = _T("FIF_GIF"); break;
		case FIF_HDR:
			pstr = _T("FIF_HDR"); break;
		case FIF_FAXG3:
			pstr = _T("FIF_FAXG3"); break;
		case FIF_SGI:
			pstr = _T("FIF_SGI"); break;
		case FIF_EXR:
			pstr = _T("FIF_EXR"); break;
		case FIF_J2K:
			pstr = _T("FIF_J2K"); break;
		case FIF_JP2:
			pstr = _T("FIF_JP2"); break;
		default:
			pstr = _T("unknown FreeImage format"); break;
		}
		return std::basic_string<charT>(pstr);
	}

	std::basic_string<charT> Image::getFITStr(FREE_IMAGE_TYPE fit)
	{
		const charT * pstr;
		switch(fit)
		{
		case FIT_UNKNOWN:
			pstr = _T("FIT_UNKNOWN"); break;
		case FIT_BITMAP:
			pstr = _T("FIT_BITMAP"); break;
		case FIT_UINT16:
			pstr = _T("FIT_UINT16"); break;
		case FIT_INT16:
			pstr = _T("FIT_INT16"); break;
		case FIT_UINT32:
			pstr = _T("FIT_UINT32"); break;
		case FIT_INT32:
			pstr = _T("FIT_INT32"); break;
		case FIT_FLOAT:
			pstr = _T("FIT_FLOAT"); break;
		case FIT_DOUBLE:
			pstr = _T("FIT_DOUBLE"); break;
		case FIT_COMPLEX:
			pstr = _T("FIT_COMPLEX"); break;
		case FIT_RGB16:
			pstr = _T("FIT_RGB16"); break;
		case FIT_RGBA16:
			pstr = _T("FIT_RGBA16"); break;
		case FIT_RGBF:
			pstr = _T("FIT_RGBF"); break;
		case FIT_RGBAF:
			pstr = _T("FIT_RGBAF"); break;
		default:
			pstr = _T("unknown FreeImage type"); break;
		}
		return std::basic_string<charT>(pstr);
	}

	FREE_IMAGE_FORMAT Image::getFileType(IOStream * stream)
	{
		FreeImageIO io;
		SetMyIOStreamIO(&io);

		return FreeImage_GetFileTypeFromHandle(&io, static_cast<fi_handle>(stream));
	}

	Image * Image::load(IOStream * stream)
	{
		FreeImageIO io;
		SetMyIOStreamIO(&io);

		FIBITMAP * dib;
		if(NULL == (dib = FreeImage_LoadFromHandle(getFileType(stream), &io, static_cast<fi_handle>(stream))))
			T3D_CUSEXCEPT(_T("load image failed"));

		return new Image(dib);
	}

	Image * Image::allocate(FREE_IMAGE_TYPE type, int width, int height, int bpp)
	{
		FIBITMAP * dib;
		if(NULL == (dib = FreeImage_AllocateT(type, width, height, bpp)))
			T3D_CUSEXCEPT(_T("allocate image failed"));

		return new Image(dib);
	}

	Image::Image(FIBITMAP * dib)
		: m_dib(dib)
	{
		assert(NULL != m_dib);
	}

	Image::~Image(void)
	{
		FreeImage_Unload(m_dib);
	}

	BOOL Image::save(FREE_IMAGE_FORMAT fif, IOStream * stream)
	{
		FreeImageIO io;
		SetMyIOStreamIO(&io);

		return FreeImage_SaveToHandle(fif, m_dib, &io, static_cast<fi_handle>(stream));
	}

	Image * Image::clone(void)
	{
		FIBITMAP * dib;
		if(NULL == (dib = FreeImage_Clone(m_dib)))
			T3D_CUSEXCEPT(_T("clone image failed"));

		return new Image(dib);
	}

	FREE_IMAGE_TYPE Image::getType(void)
	{
		return FreeImage_GetImageType(m_dib);
	}

	unsigned Image::getBPP(void)
	{
		return FreeImage_GetBPP(m_dib);
	}

	unsigned Image::getWidth(void)
	{
		return FreeImage_GetWidth(m_dib);
	}

	unsigned Image::getHeight(void)
	{
		return FreeImage_GetHeight(m_dib);
	}

	unsigned Image::getPitch(void)
	{
		return FreeImage_GetPitch(m_dib);
	}

	BYTE * Image::getBits(void)
	{
		return FreeImage_GetBits(m_dib);
	}

	Image * Image::convertTo16Bits565(void) const
	{
		FIBITMAP * dib;
		if(NULL == (dib = FreeImage_ConvertTo16Bits565(m_dib)))
			T3D_CUSEXCEPT(_T("convert image to 16bits 565 failed"));

		return new Image(dib);
	}

	Image * Image::convertTo32Bits(void) const
	{
		FIBITMAP * dib;
		if(NULL == (dib = FreeImage_ConvertTo32Bits(m_dib)))
			T3D_CUSEXCEPT(_T("convert image to 32bits failed"));

		return new Image(dib);
	}
}
