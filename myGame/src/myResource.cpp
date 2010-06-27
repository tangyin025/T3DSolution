
#include "stdafx.h"
#include "myResource.h"
#include <sstream>
#include <t3dlib5.h>
#include "libc.h"

#pragma comment(lib, "winmm.lib")

namespace my
{
	IOStream::~IOStream(void)
	{
	}

	FileIOStream::FileIOStream(FILE * handle)
		: m_handle(handle)
	{
		_ASSERT(NULL != m_handle);
	}

	FileIOStream::~FileIOStream(void)
	{
		fclose(m_handle);
	}

	size_t FileIOStream::read(void * buffer, size_t size, size_t count)
	{
		return fread(buffer, size, count, m_handle);
	}

	size_t FileIOStream::write(void * buffer, size_t size, size_t count)
	{
		return fwrite(buffer, size, count, m_handle);
	}

	int FileIOStream::seek(long offset, int origin)
	{
		return fseek(m_handle, offset, origin);
	}

	long FileIOStream::tell(void)
	{
		return ftell(m_handle);
	}

	void * FileIOStream::getHandle(void)
	{
		return m_handle;
	}

	Singleton<ResourceMgr>::DRIVED_CLASS_PTR ResourceMgr::s_ptr;

	ResourceMgr::ResourceMgr(void)
	{
	}

	ResourceMgr::~ResourceMgr(void)
	{
	}

	void ResourceMgr::addDir(const std::basic_string<charT> & dir)
	{
		_ASSERT(!dir.empty());

		m_dirList.push_back(dir);
	}

	void ResourceMgr::clearDir(void)
	{
		m_dirList.clear();
	}

	//static std::basic_string<charT> combinPath(const std::basic_string<charT> & dir, const std::basic_string<charT> & fname)
	//{
	//	_ASSERT(!fname.empty());

	//	_ASSERT(_T('/') != *(fname.begin()) || _T('\\') != *(fname.begin()));

	//	charT back = *(dir.rbegin());
	//	if(_T('/') != back || _T('\\') != back)
	//	{
	//		if(std::basic_string<charT>::npos != dir.rfind(_T('/')))
	//		{
	//			return dir + _T("/") + fname;
	//		}

	//		return dir + _T("\\") + fname;
	//	}

	//	return dir + fname;
	//}

	IOStreamPtr ResourceMgr::openIOStream(const std::basic_string<charT> & fname, const std::basic_string<charT> & fmode /*= _T("rb")*/)
	{
		_ASSERT(!fname.empty());

		std::basic_string<charT> full_path = findFileOrException(fname);

		FILE * handle;
		if(NULL == (handle = _tfopen(full_path.c_str(), fmode.c_str())))
		{
			std::basic_ostringstream<charT> osstr;
			osstr << _T("cannot open \"") << full_path << _T("\"");
			T3D_CUSEXCEPT(osstr.str());
		}

		return IOStreamPtr(new FileIOStream(handle));
	}

	std::basic_string<charT> ResourceMgr::findFile(const std::basic_string<charT> & fname)
	{
		_ASSERT(!fname.empty());

		DirList::const_iterator dir_iter = m_dirList.begin();
		for(; dir_iter != m_dirList.end(); dir_iter++)
		{
			std::basic_string<charT> full_path;
			charT * lpFilePath;
			DWORD dwLen = MAX_PATH;
			do
			{
				full_path.resize(dwLen);

				dwLen = SearchPath(dir_iter->c_str(), fname.c_str(), NULL, full_path.size(), &full_path[0], &lpFilePath);
			}
			while(dwLen > full_path.size());

			if(dwLen != 0)
			{
				full_path.resize(dwLen);

				return full_path;
			}
		}

		return std::basic_string<charT>();
	}

	std::basic_string<charT> ResourceMgr::findFileOrException(const std::basic_string<charT> & fname)
	{
		_ASSERT(!fname.empty());

		std::basic_string<charT> full_path = findFile(fname);

		if(full_path.empty())
		{
			std::basic_ostringstream<charT> osstr;
			osstr << _T("cannot find \"") << fname << _T("\" in resource dirs");
			T3D_CUSEXCEPT(osstr.str());
		}

		return full_path;
	}

#define FAILED_CUSEXCEPT(expr) { if( !(expr) ) T3D_CUSEXCEPT( _T(#expr) ) }

	Image::Image(const std::basic_string<charT> & strFileName)
	{
		FAILED_CUSEXCEPT(SUCCEEDED(m_image.Load(strFileName.c_str())));
	}

	Image::Image(int nWidth, int nHeight, int nBPP, DWORD dwFlags /*= 0*/)
	{
		FAILED_CUSEXCEPT(m_image.Create(nWidth, nHeight, nBPP, dwFlags));
	}

	Image::Image(int nWidth, int nHeight, int nBPP, DWORD eCompression, const DWORD* pdwBitmasks /*= NULL*/, DWORD dwFlags /*= 0*/)
	{
		FAILED_CUSEXCEPT(m_image.CreateEx(nWidth, nHeight, nBPP, eCompression, pdwBitmasks, dwFlags));
	}

	ImagePtr Image::convertTo16Bits565(void) const
	{
		const DWORD dwBitmasks[] = {RGB16_RED_MASK, RGB16_GREEN_MASK, RGB16_BLUE_MASK};

		ImagePtr image(new Image(getWidth(), getHeight(), 16, BI_BITFIELDS, dwBitmasks));

		HDC hdc = image->getDC();
		FAILED_CUSEXCEPT(m_image.BitBlt(hdc, 0, 0));
		image->releaseDC();

		return image;
	}

	ImagePtr Image::convertTo32Bits(void) const
	{
		ImagePtr image(new Image(getWidth(), getHeight(), 32));

		HDC hdc = image->getDC();
		FAILED_CUSEXCEPT(m_image.BitBlt(hdc, 0, 0));
		image->releaseDC();

		return image;
	}

	Wav::Wav(
			t3d::DSound * dsound,
			const std::basic_string<charT> & wavFilePath,
			DWORD flags /*= DSBCAPS_CTRL3D | DSBCAPS_CTRLVOLUME | DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE*/)
		: hwav(NULL)
	{
		if(NULL == (hwav = mmioOpen(const_cast<charT *>(wavFilePath.c_str()), NULL, MMIO_READ | MMIO_ALLOCBUF)))
			T3D_CUSEXCEPT(_T("open wave file failed"));

		parent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		if(MMSYSERR_NOERROR != mmioDescend(hwav, &parent, NULL, MMIO_FINDRIFF))
		{
			mmioClose(hwav, 0);
			T3D_CUSEXCEPT(_T("mmioDescend parent failed"));
		}

		child.fccType = mmioFOURCC('f', 'm', 't', ' ');
		if(MMSYSERR_NOERROR != mmioDescend(hwav, &child, &parent, 0))
		{
			mmioClose(hwav, 0);
			T3D_CUSEXCEPT(_T("mmioDescend child failed"));
		}

		if(sizeof(wavfmt) != mmioRead(hwav, (HPSTR)&wavfmt, sizeof(wavfmt)))
		{
			mmioClose(hwav, 0);
			T3D_CUSEXCEPT(_T("mmioRead wav format failed"));
		}

		if(WAVE_FORMAT_PCM != wavfmt.wFormatTag)
		{
			mmioClose(hwav, 0);
			T3D_CUSEXCEPT(_T("not wave format pcm"));
		}

		if(MMSYSERR_NOERROR != mmioAscend(hwav, &child, 0))
		{
			mmioClose(hwav, 0);
			T3D_CUSEXCEPT(_T("mmioAscend child failed"));
		}

		child.ckid = mmioFOURCC('d', 'a', 't', 'a');
		if(MMSYSERR_NOERROR != mmioDescend(hwav, &child, &parent, 0))
		{
			mmioClose(hwav, 0);
			T3D_CUSEXCEPT(_T("mmioDescend child failed"));
		}

		//buffer.resize(child.cksize);

		//if((LONG)child.cksize != mmioRead(hwav, (HPSTR)&buffer[0], child.cksize))
		//{
		//	mmioClose(hwav, 0);
		//	T3D_CUSEXCEPT(_T("mmioRead wav buffer failed"));
		//}

		DSBUFFERDESC dsbd;
		dsbd.dwSize = sizeof(dsbd);
		dsbd.dwFlags = flags;
		dsbd.dwBufferBytes = child.cksize;
		dsbd.dwReserved = 0;
		dsbd.lpwfxFormat = &wavfmt;
		dsbd.guid3DAlgorithm = DS3DALG_DEFAULT;

		t3d::DSBufferPtr dsbuffer = dsound->createSoundBuffer(&dsbd);

		unsigned char * buffer1;
		DWORD bytes1;
		unsigned char * buffer2;
		DWORD bytes2;
		dsbuffer->lock(0, child.cksize, (LPVOID *)&buffer1, &bytes1, (LPVOID *)&buffer2, &bytes2, DSBLOCK_ENTIREBUFFER);

		_ASSERT(bytes1 + bytes2 == child.cksize);

		if(buffer1 != NULL && (LONG)bytes1 != mmioRead(hwav, (HPSTR)buffer1, bytes1))
		{
			mmioClose(hwav, 0);
			T3D_CUSEXCEPT(_T("mmioRead wav buffer failed"));
		}

		if(buffer2 != NULL && (LONG)bytes2 != mmioRead(hwav, (HPSTR)buffer2, bytes2))
		{
			mmioClose(hwav, 0);
			T3D_CUSEXCEPT(_T("mmioRead wav buffer failed"));
		}

		dsbuffer->unlock(buffer1, bytes1, buffer2, bytes2);

		m_dsbuffer = dsbuffer;
	}

	Wav::~Wav(void)
	{
		mmioClose(hwav, 0);
	}

	//t3d::DSBufferPtr createDSoundBufferForWholeWav(
	//	t3d::DSound * dsound,
	//	const Wav * wav,
	//	DWORD flags /*= DSBCAPS_CTRLVOLUME | DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE*/)
	//{
	//	WAVEFORMATEX wavfmt = wav->wavfmt;

	//	DSBUFFERDESC dsbd;
	//	dsbd.dwSize = sizeof(dsbd);
	//	dsbd.dwFlags = flags;
	//	dsbd.dwBufferBytes = wav->child.cksize;
	//	dsbd.dwReserved = 0;
	//	dsbd.lpwfxFormat = &wavfmt;
	//	dsbd.guid3DAlgorithm = DS3DALG_DEFAULT;

	//	return dsound->createSoundBuffer(&dsbd);
	//}

	//void copyWholeWavBufferToDSoundBuffer(
	//	t3d::DSBuffer * dsbuffer,
	//	const Wav * wav)
	//{
	//	unsigned char * audioPtr1;
	//	DWORD audioBytes1;
	//	unsigned char * audioPtr2;
	//	DWORD audioBytes2;
	//	dsbuffer->lock(0, wav->child.cksize, (LPVOID *)&audioPtr1, &audioBytes1, (LPVOID *)&audioPtr2, &audioBytes2, DSBLOCK_ENTIREBUFFER);

	//	_ASSERT(audioBytes1 + audioBytes2 <= wav->child.cksize);

	//	if(audioPtr1 != NULL)
	//	{
	//		memcpy(audioPtr1, &wav->buffer[0], audioBytes1);
	//	}

	//	if(audioPtr2 != NULL)
	//	{
	//		memcpy(audioPtr2, &wav->buffer[0 + audioBytes1], audioBytes2);
	//	}

	//	dsbuffer->unlock(audioPtr1, audioBytes1, audioPtr2, audioBytes2);
	//}
}
