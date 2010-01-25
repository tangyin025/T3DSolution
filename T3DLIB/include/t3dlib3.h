
#ifndef __T3DLIB3_H__
#define __T3DLIB3_H__

#include "t3dcommon.h"
#include <string>
#include <crtdbg.h>
#include <dsound.h>
#include <atlbase.h>
#include <boost/shared_ptr.hpp>

namespace t3d
{
	class DSException : public Exception
	{
	public:
		static std::basic_string<charT> getResultStr(HRESULT hres);

	public:
		DSException(const std::basic_string<charT> & file, int line, HRESULT hres);

	public:
		std::basic_string<charT> what(void) const throw();

	protected:
		HRESULT m_hres;
	};

	class DSound;

	class DSBuffer
	{
		friend DSound;

	public:
		CComPtr<IDirectSoundBuffer8> m_dsbuffer;

	protected:
		DSBuffer(DSound * dsound, LPCDSBUFFERDESC pcDSBufferDesc);

	public:
		virtual ~DSBuffer(void);

		void setCurrentPosition(DWORD dwNewPosition);

		void getCurrentPosition(LPDWORD pdwCurrentPlayCursor, LPDWORD pdwCurrentWriteCursor = NULL);

		void lock(DWORD dwOffset, DWORD dwBytes, LPVOID * ppvAudioPtr1, LPDWORD  pdwAudioBytes1, LPVOID * ppvAudioPtr2, LPDWORD pdwAudioBytes2, DWORD dwFlags);

		void unlock(LPVOID pvAudioPtr1, DWORD dwAudioBytes1, LPVOID pvAudioPtr2, DWORD dwAudioBytes2);

		void play(DWORD dwPriority = 0, DWORD dwFlags = 0);

		void stop(void);

		void setFrequency(DWORD dwFrequency);

		DWORD getFrequency(void);

		void setPan(LONG lPan);

		LONG getPan(void);

		void setVolume(LONG lVolume);

		LONG getVolume(void);
	};

	typedef boost::shared_ptr<DSBuffer> DSBufferPtr;

	class DSound
	{
	public:
		CComPtr<IDirectSound8> m_dsound;

	public:
		enum COOPERATIVE_LEVEL
		{
			CL_PRIORITY = DSSCL_PRIORITY,
		};

	public:
		DSound(void);

		virtual ~DSound(void);

		void setCooperativeLevel(HWND hwnd, DWORD dwLevel = CL_PRIORITY);

		DSBufferPtr createSoundBuffer(LPCDSBUFFERDESC pcDSBufferDesc);
	};

	typedef boost::shared_ptr<DSound> DSoundPtr;
}

#endif // __T3DLIB3_H__
