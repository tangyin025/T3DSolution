
#ifndef __T3DLIB3_H__
#define __T3DLIB3_H__

#include "t3dcommon.h"
#include <string>
#include <cassert>
#include <dsound.h>
#include <atlbase.h>

namespace t3d
{
	class DSException : public Exception
	{
	public:
		static std::basic_string<charT> GetResultStr(HRESULT hres);

	public:
		DSException(const std::basic_string<charT> & file, int line, HRESULT hres);

	public:
		std::basic_string<charT> what(void) const throw();

	protected:
		HRESULT m_hres;
	};

	class DSBuffer
	{
	public:
		CComPtr<IDirectSoundBuffer8> m_dsbuffer;

	public:
		DSBuffer(LPDIRECTSOUND8 lpdsound, LPCDSBUFFERDESC pcDSBufferDesc);

		virtual ~DSBuffer(void);

		void SetCurrentPosition(DWORD dwNewPosition);

		void GetCurrentPosition(LPDWORD pdwCurrentPlayCursor, LPDWORD pdwCurrentWriteCursor = NULL);

		void Lock(DWORD dwOffset, DWORD dwBytes, LPVOID * ppvAudioPtr1, LPDWORD  pdwAudioBytes1, LPVOID * ppvAudioPtr2, LPDWORD pdwAudioBytes2, DWORD dwFlags);

		void Unlock(LPVOID pvAudioPtr1, DWORD dwAudioBytes1, LPVOID pvAudioPtr2, DWORD dwAudioBytes2);

		void Play(DWORD dwPriority = 0, DWORD dwFlags = 0);

		void Stop(void);

		void SetFrequency(DWORD dwFrequency);

		DWORD GetFrequency(void);

		void SetPan(LONG lPan);

		LONG GetPan(void);

		void SetVolume(LONG lVolume);

		LONG GetVolume(void);
	};

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

		void SetCooperativeLevel(HWND hwnd, DWORD dwLevel = CL_PRIORITY);
	};
}

#endif // __T3DLIB3_H__
