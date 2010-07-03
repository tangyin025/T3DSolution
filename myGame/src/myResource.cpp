
#include "stdafx.h"
#include "myResource.h"
#include <sstream>
#include <id3tag.h>
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

	struct audio_dither
	{
	public:
		mad_fixed_t error[3];
		mad_fixed_t random;

	public:
		audio_dither(void)
		{
			memset(this, 0, sizeof(*this));
		}
	};

	struct audio_stats
	{
	public:
		unsigned long clipped_samples;
		mad_fixed_t peak_clipping;
		mad_fixed_t peak_sample;

	public:
		audio_stats(void)
		{
			memset(this, 0, sizeof(*this));
		}
	};

	static unsigned long prng(unsigned long state)
	{
		return (state * 0x0019660dL + 0x3c6ef35fL) & 0xffffffffL;
	}
	
	static signed long audio_linear_dither(
		unsigned int bits,
		signed int sample,
		struct audio_dither * dither,
		struct audio_stats * stats)
	{
		unsigned int scalebits;
		mad_fixed_t output, mask, random;

		enum {
			MIN = -MAD_F_ONE,
			MAX =  MAD_F_ONE - 1
		};

		/* noise shape */
		sample += dither->error[0] - dither->error[1] + dither->error[2];

		dither->error[2] = dither->error[1];
		dither->error[1] = dither->error[0] / 2;

		/* bias */
		output = sample + (1L << (MAD_F_FRACBITS + 1 - bits - 1));

		scalebits = MAD_F_FRACBITS + 1 - bits;
		mask = (1L << scalebits) - 1;

		/* dither */
		random  = prng(dither->random);
		output += (random & mask) - (dither->random & mask);

		dither->random = random;

		/* clip */
		if (output >= stats->peak_sample) {
			if (output > MAX) {
				++stats->clipped_samples;
				if (output - MAX > stats->peak_clipping)
					stats->peak_clipping = output - MAX;

				output = MAX;

				if (sample > MAX)
					sample = MAX;
			}
			stats->peak_sample = output;
		}
		else if (output < -stats->peak_sample) {
			if (output < MIN) {
				++stats->clipped_samples;
				if (MIN - output > stats->peak_clipping)
					stats->peak_clipping = MIN - output;

				output = MIN;

				if (sample < MIN)
					sample = MIN;
			}
			stats->peak_sample = -output;
		}

		/* quantize */
		output &= ~mask;

		/* error feedback */
		dither->error[0] = sample - output;

		/* scale */
		return output >> scalebits;
	}

	Mp3::Mp3(
		t3d::DSoundPtr dsound,
		IOStreamPtr stream,
		DWORD flags /*= DSBCAPS_CTRLVOLUME | DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE*/)
		: m_dsound(dsound)
		, m_stream(stream)
		, m_flags(flags)
		, m_buffer(MPEG_BUFSZ / sizeof(m_buffer[0]))
	{

		for(int i = 0; i < _countof(m_events); i++)
		{
			m_events[i] = ::CreateEvent(NULL, FALSE, FALSE, NULL);
		}

		for(int i = 0; i < _countof(m_dsnp); i++)
		{
			m_dsnp[i].dwOffset = 0;
			m_dsnp[i].hEventNotify = m_events[i];
		}
	}

	Mp3::~Mp3(void)
	{
		stop();

		for(int i = 0; i < _countof(m_events); i++)
		{
			VERIFY(::CloseHandle(m_events[i]));
		}
	}

	void Mp3::playOnce(void)
	{
		WAVEFORMATEX wavfmt;
		DSBUFFERDESC dsbd;
		audio_dither left_dither, right_dither;
		unsigned short last_channels = 0;
		unsigned int last_samplerate = 0;
		std::vector<unsigned char> soundBuffer;

		m_stream->seek(0, my::IOStream::seek_set);

		mad_stream stream;
		mad_frame frame;
		mad_synth synth;

		mad_stream_init(&stream);
		mad_frame_init(&frame);
		mad_synth_init(&synth);

		do
		{
			// get file buffer from stream
			int remain = 0;
			if(NULL != stream.next_frame)
			{
				remain = &m_buffer[0] + MPEG_BUFSZ - stream.next_frame;
				memmove(&m_buffer[0], stream.next_frame, remain);
			}

			int read = m_stream->read(&m_buffer[0] + remain, sizeof(m_buffer[0]), m_buffer.size() - remain);
			if(0 == read)
			{
				if(NULL == m_dsbuffer)
				{
					goto end;
				}

				VERIFY(::SetEvent(m_events[_countof(m_dsnp)]));
			}

			// if file was too small, set remaining bytes as zero
			if(read < MAD_BUFFER_GUARD)
			{
				_ASSERT(MPEG_BUFSZ - remain > MAD_BUFFER_GUARD);
				memset(&m_buffer[remain + read], 0, MAD_BUFFER_GUARD - read);
				read = MAD_BUFFER_GUARD;
			}

			// attach buffer to mad stream
			mad_stream_buffer(&stream, &m_buffer[0], (remain + read) * sizeof(m_buffer[0]));

			while(true)
			{
				// decode audio frame
				if(-1 == mad_frame_decode(&frame, &stream))
				{
					if(!MAD_RECOVERABLE(stream.error))
					{
						break;
					}

					switch(stream.error)
					{
					case MAD_ERROR_BADDATAPTR:
						continue;

					case MAD_ERROR_LOSTSYNC:
						{
							// excute id3 tag frame skipping
							unsigned long tagsize = id3_tag_query(stream.this_frame, stream.bufend - stream.this_frame);
							if(tagsize > 0)
							{
								mad_stream_skip(&stream, tagsize);
							}
						}
						continue;

					default:
						continue;
					}
				}

				// convert frame data to pcm data
				mad_synth_frame(&synth, &frame);

				// parse dither linear pcm data to compatible format
				audio_stats stats;
				if(2 == synth.pcm.channels)
				{
					register signed int sample0, sample1;
					for(int i = 0; i < (int)synth.pcm.length; i++)
					{
						sample0 = audio_linear_dither(16, synth.pcm.samples[0][i], &left_dither, &stats);
						sample1 = audio_linear_dither(16, synth.pcm.samples[1][i], &right_dither, &stats);
						soundBuffer.push_back(sample0 >> 0);
						soundBuffer.push_back(sample0 >> 8);
						soundBuffer.push_back(sample1 >> 0);
						soundBuffer.push_back(sample1 >> 8);
					}
				}
				else
				{
					register int sample0;
					for(int i = 0; i < (int)synth.pcm.length; i++)
					{
						sample0 = audio_linear_dither(16, synth.pcm.samples[0][i], &left_dither, &stats);
						soundBuffer.push_back(sample0 >> 0);
						soundBuffer.push_back(sample0 >> 8);
					}
				}

				// create dsbuffer if necessary
				if(last_channels != synth.pcm.channels || last_samplerate != synth.pcm.samplerate)
				{
					m_dsnotify = t3d::DSNotifyPtr();
					m_dsbuffer = t3d::DSBufferPtr();

					wavfmt.wFormatTag = WAVE_FORMAT_PCM;
					wavfmt.nChannels = synth.pcm.channels;
					wavfmt.nSamplesPerSec = synth.pcm.samplerate;
					wavfmt.wBitsPerSample = 16;
					wavfmt.nBlockAlign = wavfmt.nChannels * wavfmt.wBitsPerSample / 8;
					wavfmt.nAvgBytesPerSec = wavfmt.nSamplesPerSec * wavfmt.nBlockAlign;
					wavfmt.cbSize = 0;

					dsbd.dwSize = sizeof(dsbd);
					dsbd.dwFlags = DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE | DSBCAPS_CTRLPOSITIONNOTIFY;
					dsbd.dwBufferBytes = wavfmt.nAvgBytesPerSec * BUFFER_COUNT;
					dsbd.dwReserved = 0;
					dsbd.lpwfxFormat = &wavfmt;
					dsbd.guid3DAlgorithm = DS3DALG_DEFAULT;

					m_dsbuffer = m_dsound->createSoundBuffer(&dsbd);
					last_channels = wavfmt.nChannels;
					last_samplerate = wavfmt.nSamplesPerSec;

					for(int i = 0; i < _countof(m_dsnp); i++)
					{
						m_dsnp[i].dwOffset = i * wavfmt.nAvgBytesPerSec;
						VERIFY(::ResetEvent(m_dsnp[i].hEventNotify));
					}
					m_dsnotify = m_dsbuffer->getDSNotify();
					m_dsnotify->setNotificationPositions(_countof(m_dsnp), m_dsnp);
				}

				// fill pcm data to dsbuffer
				_ASSERT(NULL != m_dsbuffer);
				if(soundBuffer.size() > wavfmt.nAvgBytesPerSec)
				{
					if(!m_dsbuffer->isPlaying())
					{
						unsigned char * audioPtr1;
						DWORD audioBytes1;
						unsigned char * audioPtr2;
						DWORD audioBytes2;
						m_dsbuffer->lock(0, wavfmt.nAvgBytesPerSec, (LPVOID *)&audioPtr1, &audioBytes1, (LPVOID *)&audioPtr2, &audioBytes2, 0);

						if(audioPtr1 != NULL)
							memcpy(audioPtr1, &soundBuffer[0], audioBytes1);

						if(audioPtr2 != NULL)
							memcpy(audioPtr2, &soundBuffer[0 + audioBytes1], audioBytes2);

						m_dsbuffer->unlock(audioPtr1, audioBytes1, audioPtr2, audioBytes2);

						m_dsbuffer->play(0, DSBPLAY_LOOPING);
					}
					else
					{
						DWORD wait_res = ::WaitForMultipleObjects(_countof(m_events), m_events, FALSE, INFINITE);
						_ASSERT(WAIT_TIMEOUT != wait_res);
						DWORD curr_event_index = wait_res - WAIT_OBJECT_0;
						if(curr_event_index >= _countof(m_dsnp))
						{
							m_dsbuffer->stop();
							goto end;
						}

						DWORD next_event_index = (curr_event_index + 1) % _countof(m_dsnp);
						_ASSERT(next_event_index < _countof(m_dsnp));
						DWORD next_position = m_dsnp[next_event_index].dwOffset;

						unsigned char * audioPtr1;
						DWORD audioBytes1;
						unsigned char * audioPtr2;
						DWORD audioBytes2;
						m_dsbuffer->lock(next_position, wavfmt.nAvgBytesPerSec, (LPVOID *)&audioPtr1, &audioBytes1, (LPVOID *)&audioPtr2, &audioBytes2, 0);

						if(audioPtr1 != NULL)
							memcpy(audioPtr1, &soundBuffer[0], audioBytes1);

						if(audioPtr2 != NULL)
							memcpy(audioPtr2, &soundBuffer[0 + audioBytes1], audioBytes2);

						m_dsbuffer->unlock(audioPtr1, audioBytes1, audioPtr2, audioBytes2);
					}

					size_t remain = soundBuffer.size() - wavfmt.nAvgBytesPerSec;

					memmove(&soundBuffer[0], &soundBuffer[wavfmt.nAvgBytesPerSec], remain);

					soundBuffer.resize(remain);
				}
			}
		}
		while(stream.error == MAD_ERROR_BUFLEN);

		_ASSERT(false);

end:
		mad_synth_finish(&synth);
		mad_frame_finish(&frame);
		mad_stream_finish(&stream);
	}

	void Mp3::play(bool loop /*= false*/)
	{
		if(NULL != m_hThread)
		{
			if(!WaitForThreadStopped(0))
			{
				return;
			}

			VERIFY(::CloseHandle(m_hThread));
			m_hThread = NULL;
		}

		setLoop(loop);
		VERIFY(::ResetEvent(m_events[_countof(m_dsnp)]));
		CreateThread();
		ResumeThread();
	}

	void Mp3::stop(void)
	{
		_ASSERT(NULL != m_hThread);
		setLoop(false);
		VERIFY(::SetEvent(m_events[_countof(m_dsnp)]));
		VERIFY(WaitForThreadStopped(INFINITE));
	}

	DWORD Mp3::onProc(void)
	{
		do
		{
			playOnce();
		}
		while(getLoop());

		return 0;
	}
}
