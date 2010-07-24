
#ifndef __T3DLIB3_H__
#define __T3DLIB3_H__

#include "t3dcommon.h"
#include <string>
#include <crtdbg.h>
#include <dsound.h>
#include <mmreg.h>
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

	class DSNotify;

	typedef boost::shared_ptr<DSNotify> DSNotifyPtr;

	class DS3DBuffer;

	typedef boost::shared_ptr<DS3DBuffer> DS3DBufferPtr;

	class DS3DListener;

	typedef boost::shared_ptr<DS3DListener> DS3DListenerPtr;

	class DSBuffer
	{
		friend DSound;

	public:
		CComPtr<IDirectSoundBuffer> m_dsbuffer;

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

		DWORD getStatus(void);

		BOOL isPlaying(void);

		DSNotifyPtr getDSNotify(void);

		DS3DBufferPtr getDS3DBuffer(void);

		DS3DListenerPtr getDS3DListener(void);
	};

	typedef boost::shared_ptr<DSBuffer> DSBufferPtr;

	class DSNotify
	{
		friend DSBuffer;

	public:
		CComPtr<IDirectSoundNotify> m_dsnotify;

	protected:
		DSNotify(DSBuffer * dsbuffer);

	public:
		virtual ~DSNotify(void);

		void setNotificationPositions(DWORD dwPositionNotifies, LPCDSBPOSITIONNOTIFY pcPositionNotifies);
	};

	class DS3DBuffer
	{
		friend DSBuffer;

	public:
		CComPtr<IDirectSound3DBuffer> m_ds3dbuffer;

	protected:
		DS3DBuffer(DSBuffer * dsbuffer);

	public:
		virtual ~DS3DBuffer(void);

		void setMaxDistance(D3DVALUE flMaxDistance, DWORD dwApply = DS3D_DEFERRED);

		D3DVALUE getMaxDistance(void);

		void setMinDistance(D3DVALUE flMinDistance, DWORD dwApply = DS3D_DEFERRED);

		D3DVALUE getMinDistance(void);

		void setPosition(D3DVALUE x, D3DVALUE y, D3DVALUE z, DWORD dwApply = DS3D_DEFERRED);

		D3DVECTOR getPosition(void);

		void setVelocity(D3DVALUE x, D3DVALUE y, D3DVALUE z, DWORD dwApply = DS3D_DEFERRED);

		D3DVECTOR getVelocity(void);

		void setAllParameters(LPCDS3DBUFFER pcDs3dBuffer, DWORD dwApply = DS3D_DEFERRED);

		void getAllParameters(LPDS3DBUFFER pDs3dBuffer);
	};

	class DS3DListener
	{
		friend DSBuffer;

	public:
		CComPtr<IDirectSound3DListener> m_ds3dlistener;

	protected:
		DS3DListener(DSBuffer * dsbuffer);

	public:
		virtual ~DS3DListener(void);

		void commitDeferredSettings(void);

		void setOrientation(D3DVALUE xFront, D3DVALUE yFront, D3DVALUE zFront, D3DVALUE xTop, D3DVALUE yTop, D3DVALUE zTop, DWORD dwApply = DS3D_DEFERRED);

		void getOrientation(D3DVECTOR * pvOrientFront, D3DVECTOR * pvOrientTop);

		void setPosition(D3DVALUE x, D3DVALUE y, D3DVALUE z, DWORD dwApply = DS3D_DEFERRED);

		D3DVECTOR getPosition(void);

		void setVelocity(D3DVALUE x, D3DVALUE y, D3DVALUE z, DWORD dwApply = DS3D_DEFERRED);

		D3DVECTOR getVelocity(void);

		void setAllParameters(LPCDS3DLISTENER pcListener, DWORD dwApply = DS3D_DEFERRED);

		void getAllParameters(LPDS3DLISTENER pListener);
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

		void setCooperativeLevel(HWND hwnd, DWORD dwLevel = CL_PRIORITY);

		DSBufferPtr createSoundBuffer(LPCDSBUFFERDESC pcDSBufferDesc);

		DSBufferPtr getPrimarySoundBuffer(void);
	};

	typedef boost::shared_ptr<DSound> DSoundPtr;
}

#endif // __T3DLIB3_H__
