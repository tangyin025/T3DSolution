
#include "stdafx.h"
#include "myResource.h"
#include <sstream>
#include <mmsystem.h>

#ifdef _UNICODE
#define fopen _wfopen
#endif

namespace my
{
	IOStream::~IOStream(void)
	{
	}

	FileIOStream::FileIOStream(FILE * handle)
		: m_handle(handle)
	{
		assert(NULL != m_handle);
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

	ResourceMgr * ResourceMgr::s_ptr = NULL;

	ResourceMgr::ResourceMgr(void)
	{
		assert(NULL == s_ptr);
		s_ptr = this;
	}

	ResourceMgr::~ResourceMgr(void)
	{
		assert(this == s_ptr);
		s_ptr = NULL;
	}

	void ResourceMgr::registerDir(const std::basic_string<charT> & dir)
	{
		m_dirList.push_back(dir);
	}

	IOStreamPtr ResourceMgr::openIOStream(const std::basic_string<charT> & fname, const std::basic_string<charT> & fmode /*= _T("rb")*/)
	{
		DirList::const_iterator iter = m_dirList.begin();
		for(; iter != m_dirList.end(); iter++)
		{
			std::basic_string<charT> full_path = *iter + _T("/") + fname;
			FILE * handle;
			if(NULL != (handle = fopen(full_path.c_str(), fmode.c_str())))
			{
				return IOStreamPtr(new FileIOStream(handle));
			}
		}

		std::basic_ostringstream<charT> osstr;
		osstr << _T("cannot find \"") << fname << _T("\" in resource dirs");
		T3D_CUSEXCEPT(osstr.str());
	}

	std::basic_string<charT> ResourceMgr::findFile(const std::basic_string<charT> & fname)
	{
		DirList::const_iterator iter = m_dirList.begin();
		for(; iter != m_dirList.end(); iter++)
		{
			std::basic_string<charT> full_path = *iter + _T("/") + fname;
			FILE * handle;
			if(NULL != (handle = fopen(full_path.c_str(), _T("rb"))))
			{
				fclose(handle);
				return full_path;
			}
		}

		return std::basic_string<charT>();
	}

	std::basic_string<charT> ResourceMgr::findFileOrException(const std::basic_string<charT> & fname)
	{
		DirList::const_iterator iter = m_dirList.begin();
		for(; iter != m_dirList.end(); iter++)
		{
			std::basic_string<charT> full_path = *iter + _T("/") + fname;
			FILE * handle;
			if(NULL != (handle = fopen(full_path.c_str(), _T("rb"))))
			{
				fclose(handle);
				return full_path;
			}
		}

		std::basic_ostringstream<charT> osstr;
		osstr << _T("cannot find \"") << fname << _T("\" in resource dirs");
		T3D_CUSEXCEPT(osstr.str());
	}

	Wav::Wav(const std::basic_string<charT> & wavFilePath)
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

		if(NULL == (buffer = boost::shared_ptr<unsigned char>((unsigned char *)malloc(child.cksize))))
		{
			mmioClose(hwav, 0);
			T3D_CUSEXCEPT(_T("malloc buffer failed"));
		}

		if((LONG)child.cksize != mmioRead(hwav, (HPSTR)buffer.get(), child.cksize))
		{
			mmioClose(hwav, 0);
			T3D_CUSEXCEPT(_T("mmioRead wav buffer failed"));
		}
	}

	Wav::~Wav(void)
	{
		mmioClose(hwav, 0);
	}

	t3d::DSBufferPtr createDSoundBufferForWholeWav(
		t3d::DSound * dsound,
		const Wav * wav,
		int flags /*= DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME*/,
		unsigned short channels /*= 1*/,
		int samplesPerSec /*= 11025*/)
	{
		WAVEFORMATEX wavfmt;
		wavfmt.wFormatTag = wav->wavfmt.wFormatTag;
		wavfmt.nChannels = channels;
		wavfmt.nSamplesPerSec = samplesPerSec;
		wavfmt.wBitsPerSample = wav->wavfmt.wBitsPerSample;
		wavfmt.nBlockAlign = wavfmt.nChannels * wavfmt.wBitsPerSample / 8;
		wavfmt.nAvgBytesPerSec = wavfmt.nSamplesPerSec * wavfmt.nBlockAlign;
		wavfmt.cbSize = 0;

		DSBUFFERDESC dsbd;
		dsbd.dwSize = sizeof(dsbd);
		dsbd.dwFlags = flags | DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE;
		dsbd.dwBufferBytes = wav->child.cksize;
		dsbd.dwReserved = 0;
		dsbd.lpwfxFormat = &wavfmt;
		dsbd.guid3DAlgorithm = DS3DALG_DEFAULT;

		return dsound->createSoundBuffer(&dsbd);
	}

	void copyWholeWavBufferToDSoundBuffer(
		t3d::DSBuffer * dsbuffer,
		const Wav * wav)
	{
		unsigned char * audioPtr1;
		DWORD audioBytes1;
		unsigned char * audioPtr2;
		DWORD audioBytes2;
		dsbuffer->lock(0, wav->child.cksize, (LPVOID *)&audioPtr1, &audioBytes1, (LPVOID *)&audioPtr2, &audioBytes2, DSBLOCK_ENTIREBUFFER);

		assert(audioBytes1 + audioBytes2 <= wav->child.cksize);

		if(audioPtr1 != NULL)
			memcpy(audioPtr1, wav->buffer.get(), audioBytes1);

		if(audioPtr2 != NULL)
			memcpy(audioPtr2, wav->buffer.get() + audioBytes1, audioBytes2);

		dsbuffer->unlock(audioPtr1, audioBytes1, audioPtr2, audioBytes2);
	}
}
