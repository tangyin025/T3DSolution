
#ifndef __MYRESOURCE_H__
#define __MYRESOURCE_H__

#include "myCommon.h"
#include <t3dlib3.h>
#include <cstdio>
#include <crtdbg.h>
#include <list>
#include <mmsystem.h>
#pragma push_macro("min")
#pragma push_macro("max")
#define min std::min
#define max std::max
#pragma push_macro("REAL_MIN")
#pragma push_macro("REAL_MAX")
#undef REAL_MIN
#undef REAL_MAX
#include <atlimage.h>
#pragma pop_macro("REAL_MAX")
#pragma pop_macro("REAL_MIN")
#pragma pop_macro("max")
#pragma pop_macro("min")
#include <memory>
#include <vector>
#include "mySingleton.h"
#include "myWindow.h"

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

	typedef std::tr1::shared_ptr<IOStream> IOStreamPtr;

	class FileStream : public IOStream
	{
		friend class ResourceMgr;

	protected:
		std::basic_string<charT> m_fpath;

		FILE * m_handle;

	public:
		FileStream(const std::basic_string<charT> & fpath, const std::basic_string<charT> & fmode = _T("rb"));

		virtual ~FileStream(void);

	public:
		size_t read(void * buffer, size_t size, size_t count);

		size_t write(void * buffer, size_t size, size_t count);

		int seek(long offset, int origin);

		long tell(void);

		void * getHandle(void);
	};

	typedef std::tr1::shared_ptr<FileStream> FileStreamPtr;

	class ResourceMgr : public Singleton<ResourceMgr>
	{
	protected:
		typedef std::list<std::basic_string<charT> > DirList;

		DirList m_dirList;

	public:
		ResourceMgr(void);

		virtual ~ResourceMgr(void);

	public:
		void addDir(const std::basic_string<charT> & dir);

		void clearDir(void);

		//IOStreamPtr openIOStream(const std::basic_string<charT> & fname, const std::basic_string<charT> & fmode = _T("rb"));

		std::basic_string<charT> findFile(const std::basic_string<charT> & fname);

		std::basic_string<charT> findFileOrException(const std::basic_string<charT> & fname);
	};

	typedef std::tr1::shared_ptr<ResourceMgr> ResourceMgrPtr;

	class Image;

	typedef std::tr1::shared_ptr<Image> ImagePtr;

	class Image
	{
	//protected:
	public:
		CImage m_image;

	public:
		Image(const std::basic_string<charT> & strFileName);

		Image(int nWidth, int nHeight, int nBPP, DWORD dwFlags = 0);

		Image(int nWidth, int nHeight, int nBPP, DWORD eCompression, const DWORD* pdwBitmasks = NULL, DWORD dwFlags = 0);

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

	class Wav
	{
	public:
		HMMIO hwav;

		MMCKINFO parent;

		MMCKINFO child;

		WAVEFORMATEX wavfmt;

		//std::vector<unsigned char> buffer;

		t3d::DSBufferPtr m_dsbuffer;

	public:
		Wav(
			t3d::DSound * dsound,
			const std::basic_string<charT> & wavFilePath,
			DWORD flags = DSBCAPS_CTRL3D | DSBCAPS_CTRLVOLUME | DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE);

		virtual ~Wav(void);
	};

	typedef std::tr1::shared_ptr<Wav> WavPtr;

	//t3d::DSBufferPtr createDSoundBufferForWholeWav(
	//	t3d::DSound * dsound,
	//	const Wav * wav,
	//	DWORD flags = DSBCAPS_CTRLVOLUME | DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE);

	//void copyWholeWavBufferToDSoundBuffer(
	//	t3d::DSBuffer * dsbuffer,
	//	const Wav * wav);

	class Mp3 : public ::my::Thread
	{
	protected:
		static const DWORD MPEG_BUFSZ = 40000;

		static const DWORD MAX_RESAMPLEFACTOR = 6;

		static const DWORD MAX_NSAMPLES = 1152 * MAX_RESAMPLEFACTOR;

		static const DWORD BUFFER_COUNT = 2;

	protected:
		t3d::DSoundPtr m_dsound;

		t3d::DSBufferPtr m_dsbuffer;

		t3d::DSNotifyPtr m_dsnotify;

		DSBPOSITIONNOTIFY m_dsnp[BUFFER_COUNT];

		Event m_events[BUFFER_COUNT + 1];

		IOStreamPtr m_stream;

		DWORD m_flags;

		typedef std::vector<unsigned char> FileBuffer;

		FileBuffer m_buffer;

		bool m_loop;

		CriticalSection m_loopLock;

		void setLoop(bool loop)
		{
			CriticalSectionLock lock(m_loopLock);
			m_loop = loop;
		}

		bool getLoop(void)
		{
			CriticalSectionLock lock(m_loopLock);
			return m_loop;
		}

	public:
		Mp3(
			t3d::DSoundPtr dsound,
			IOStreamPtr fstream,
			DWORD flags = DSBCAPS_CTRLVOLUME | DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE);

		virtual ~Mp3(void);

	protected:
		void playOnce(void);

	public:
		void play(bool loop = false);

		void stop(void);

		DWORD onProc(void);
	};

	typedef std::tr1::shared_ptr<Mp3> Mp3Ptr;
}

#endif // __MYRESOURCE_H__
