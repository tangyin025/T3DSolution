
#ifndef __MYIMAGE_H__
#define __MYIMAGE_H__

#include "myCommon.h"

#include <boost/shared_ptr.hpp>

#include "FreeImage.h"
#include "myResource.h"

namespace my
{
	class MYGAME_API Image
	{
	protected:
		class InitManager
		{
		public:
			InitManager(void);

			virtual ~InitManager(void);
		};

		static InitManager m_initMgr;

	public:
		static std::basic_string<charT> getFIFStr(FREE_IMAGE_FORMAT fif);

		static std::basic_string<charT> getFITStr(FREE_IMAGE_TYPE fit);

		static FREE_IMAGE_FORMAT getFileType(IOStream * stream);

		static Image * allocate(FREE_IMAGE_TYPE type, int width, int height, int bpp);

		static Image * load(IOStream * stream);

	protected:
		Image(FIBITMAP * dib);

	public:
		virtual ~Image(void);

	public:
		BOOL save(FREE_IMAGE_FORMAT fif, IOStream * stream);

		Image * clone(void);

		FREE_IMAGE_TYPE getType(void);

		unsigned getBPP(void);

		unsigned getWidth(void);

		unsigned getHeight(void);

		unsigned getPitch(void);

		BYTE * getBits(void);

		Image * convertTo16Bits565(void) const;

		Image * convertTo32Bits(void) const;

	protected:
		FIBITMAP * m_dib;
	};

	typedef boost::shared_ptr<Image> ImagePtr;
}

#endif // __MYIMAGE_H__
