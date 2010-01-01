
#ifndef __T3DLIB3_H__
#define __T3DLIB3_H__

#include "t3dcommon.h"

#include <string>
#include <cassert>
#include <dsound.h>

namespace t3d
{
	class DSound
	{
	public:
		static std::basic_string<charT> getResultStr(HRESULT hres);

		class Exception : public t3d::Exception
		{
		public:
			Exception(const std::basic_string<charT> & file, int line, HRESULT hres);

		public:
			std::basic_string<charT> what(void) const throw();

		protected:
			HRESULT m_hres;
		};

	public:
		enum COOPERATIVE_LEVEL
		{
			CL_PRIORITY = DSSCL_PRIORITY,
		};

	public:
		DSound(void);

		virtual ~DSound(void);

	protected:
		LPDIRECTSOUND8 m_lpdsound;

	public:
		void setCooperativeLevel(HWND hwnd, DWORD level = CL_PRIORITY);

	public:
		class Buffer
		{
		protected:
			LPDIRECTSOUNDBUFFER m_lpdsbuffer;

		public:
			Buffer(DSound * sound, const DSBUFFERDESC & dsbd);

			virtual ~Buffer(void);

			void setCurrentPosition(DWORD position);

			void getCurrentPosition(LPDWORD pCurrentPlayCursor, LPDWORD pCurrentWriteCursor = NULL) const;

			void lock(DWORD offset, DWORD bytes, LPVOID * audioPtr1, LPDWORD  audioBytes1, LPVOID * audioPtr2, LPDWORD audioBytes2, DWORD flags);

			void unlock(LPVOID audioPtr1, DWORD audioBytes1, LPVOID audioPtr2, DWORD audioBytes2);

			void play(DWORD priority = 0, DWORD flags = 0);

			void stop(void);

			void setFrequency(DWORD frequency);

			DWORD getFrequency(void) const;

			void setPan(LONG lPan);

			LONG getPan(void) const;

			void setVolume(LONG lVolume);

			LONG getVolume(void) const;
		};
	};
}

#endif // __T3DLIB3_H__
