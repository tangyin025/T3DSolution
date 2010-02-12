
#ifndef __MYRESOURCE_H__
#define __MYRESOURCE_H__

#include "myCommon.h"
#include <t3dlib3.h>
#include <cstdio>
#include <crtdbg.h>
#include <list>
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
	class IOStream
	{
	public:
		enum seek_type
		{
			seek_cur = SEEK_CUR,
			seek_end = SEEK_END,
			seek_set = SEEK_SET,
		};

	public:
		virtual ~IOStream(void);

	public:
		virtual size_t read(void * buffer, size_t size, size_t count) = 0;

		virtual size_t write(void * buffer, size_t size, size_t count) = 0;

		virtual int seek(long offset, int origin) = 0;

		virtual long tell(void) = 0;

		virtual void * getHandle(void) = 0;
	};

	typedef boost::shared_ptr<IOStream> IOStreamPtr;

	class FileIOStream : public IOStream
	{
		friend class ResourceMgr;

	protected:
		FileIOStream(FILE * handle);

	public:
		virtual ~FileIOStream(void);

	public:
		size_t read(void * buffer, size_t size, size_t count);

		size_t write(void * buffer, size_t size, size_t count);

		int seek(long offset, int origin);

		long tell(void);

		void * getHandle(void);

	protected:
		FILE * m_handle;
	};

	class ResourceMgr
	{
	protected:
		static ResourceMgr * s_ptr;

	public:
		static inline ResourceMgr & getSingleton(void)
		{
			_ASSERT(NULL != s_ptr); return * s_ptr;
		}

	public:
		ResourceMgr(void);

		virtual ~ResourceMgr(void);

	public:
		void addDir(const std::basic_string<charT> & dir);

		void clearDir(void);

		IOStreamPtr openIOStream(const std::basic_string<charT> & fname, const std::basic_string<charT> & fmode = _T("rb"));

		std::basic_string<charT> findFile(const std::basic_string<charT> & fname);

		std::basic_string<charT> findFileOrException(const std::basic_string<charT> & fname);

	protected:
		typedef std::list<std::basic_string<charT> > DirList;

		DirList m_dirList;
	};

	typedef boost::shared_ptr<ResourceMgr> ResourceMgrPtr;

	class Wav
	{
	public:
		Wav(const std::basic_string<charT> & wavFilePath);

		virtual ~Wav(void);

	public:
		HMMIO hwav;
		MMCKINFO parent;
		MMCKINFO child;
		WAVEFORMATEX wavfmt;
		boost::shared_ptr<unsigned char> buffer;
	};

	typedef boost::shared_ptr<Wav> WavPtr;

	t3d::DSBufferPtr createDSoundBufferForWholeWav(
		t3d::DSound * dsound,
		const Wav * wav,
		int flags = DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME,
		unsigned short channels = 1,
		int samplesPerSec = 11025);

	void copyWholeWavBufferToDSoundBuffer(
		t3d::DSBuffer * dsbuffer,
		const Wav * wav);

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

#endif // __MYRESOURCE_H__