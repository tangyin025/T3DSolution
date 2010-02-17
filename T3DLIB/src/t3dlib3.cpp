
#include "stdafx.h"
#include "t3dlib3.h"

#pragma comment(lib, "dsound.lib")

namespace t3d
{
#define CASE_RETURN_STRING(branch) case branch: return std::basic_string<charT>(_T( #branch ));

	std::basic_string<charT> DSException::getResultStr(HRESULT hres)
	{
		switch(hres)
		{
		CASE_RETURN_STRING(DS_OK)
		CASE_RETURN_STRING(DS_NO_VIRTUALIZATION)
		//CASE_RETURN_STRING(DS_INCOMPLETE)
		CASE_RETURN_STRING(DSERR_ACCESSDENIED)
		CASE_RETURN_STRING(DSERR_ALLOCATED)
		CASE_RETURN_STRING(DSERR_ALREADYINITIALIZED)
		CASE_RETURN_STRING(DSERR_BADFORMAT)
		CASE_RETURN_STRING(DSERR_BADSENDBUFFERGUID)
		CASE_RETURN_STRING(DSERR_BUFFERLOST)
		CASE_RETURN_STRING(DSERR_BUFFERTOOSMALL)
		CASE_RETURN_STRING(DSERR_CONTROLUNAVAIL)
		CASE_RETURN_STRING(DSERR_DS8_REQUIRED)
		CASE_RETURN_STRING(DSERR_FXUNAVAILABLE)
		CASE_RETURN_STRING(DSERR_GENERIC)
		CASE_RETURN_STRING(DSERR_INVALIDCALL)
		CASE_RETURN_STRING(DSERR_INVALIDPARAM)
		CASE_RETURN_STRING(DSERR_NOAGGREGATION)
		CASE_RETURN_STRING(DSERR_NODRIVER)
		CASE_RETURN_STRING(DSERR_NOINTERFACE)
		CASE_RETURN_STRING(DSERR_OBJECTNOTFOUND)
		CASE_RETURN_STRING(DSERR_OTHERAPPHASPRIO)
		CASE_RETURN_STRING(DSERR_OUTOFMEMORY)
		CASE_RETURN_STRING(DSERR_PRIOLEVELNEEDED)
		CASE_RETURN_STRING(DSERR_SENDLOOP)
		CASE_RETURN_STRING(DSERR_UNINITIALIZED)
		CASE_RETURN_STRING(DSERR_UNSUPPORTED)
		}
		return std::basic_string<charT>(_T("unknown dsound error result"));
	}

	DSException::DSException(const std::basic_string<charT> & file, int line, HRESULT hres)
		: Exception(file, line)
		, m_hres(hres)
	{
	}

	std::basic_string<charT> DSException::what(void) const throw()
	{
		return getResultStr(m_hres);
	}

#define T3D_DSEXCEPT(hres) { throw DSException( _T(__FILE__), __LINE__, (hres) ); }

#define FAILED_DSEXCEPT(expr) { HRESULT hres; if( FAILED( hres = (expr) ) ) T3D_DSEXCEPT(hres) }

	DSBuffer::DSBuffer(DSound * dsound, LPCDSBUFFERDESC pcDSBufferDesc)
	{
		CComPtr<IDirectSoundBuffer> dsbuffer;
		FAILED_DSEXCEPT(dsound->m_dsound->CreateSoundBuffer(pcDSBufferDesc, &dsbuffer, NULL));

		FAILED_DSEXCEPT(dsbuffer->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID *)&m_dsbuffer));
	}

	DSBuffer::~DSBuffer(void)
	{
	}

	void DSBuffer::setCurrentPosition(DWORD dwNewPosition)
	{
		SUCCEEDED_VERIFY(m_dsbuffer->SetCurrentPosition(dwNewPosition));
	}

	void DSBuffer::getCurrentPosition(LPDWORD pdwCurrentPlayCursor, LPDWORD pdwCurrentWriteCursor /*= NULL*/)
	{
		SUCCEEDED_VERIFY(m_dsbuffer->GetCurrentPosition(pdwCurrentPlayCursor, pdwCurrentWriteCursor));
	}

	void DSBuffer::lock(DWORD dwOffset, DWORD dwBytes, LPVOID * ppvAudioPtr1, LPDWORD  pdwAudioBytes1, LPVOID * ppvAudioPtr2, LPDWORD pdwAudioBytes2, DWORD dwFlags)
	{
		FAILED_DSEXCEPT(m_dsbuffer->Lock(dwOffset, dwBytes, ppvAudioPtr1, pdwAudioBytes1, ppvAudioPtr2, pdwAudioBytes2, dwFlags));
	}

	void DSBuffer::unlock(LPVOID pvAudioPtr1, DWORD dwAudioBytes1, LPVOID pvAudioPtr2, DWORD dwAudioBytes2)
	{
		SUCCEEDED_VERIFY(m_dsbuffer->Unlock(pvAudioPtr1, dwAudioBytes1, pvAudioPtr2, dwAudioBytes2));
	}

	void DSBuffer::play(DWORD dwPriority /*= 0*/, DWORD dwFlags /*= 0*/)
	{
		FAILED_DSEXCEPT(m_dsbuffer->Play(0, dwPriority, dwFlags));
	}

	void DSBuffer::stop(void)
	{
		SUCCEEDED_VERIFY(m_dsbuffer->Stop());
	}

	void DSBuffer::setFrequency(DWORD dwFrequency)
	{
		SUCCEEDED_VERIFY(m_dsbuffer->SetFrequency(dwFrequency));
	}

	DWORD DSBuffer::getFrequency(void)
	{
		DWORD dwFrequency;
		SUCCEEDED_VERIFY(m_dsbuffer->GetFrequency(&dwFrequency));
		return dwFrequency;
	}

	void DSBuffer::setPan(LONG lPan)
	{
		SUCCEEDED_VERIFY(m_dsbuffer->SetPan(lPan));
	}

	LONG DSBuffer::getPan(void)
	{
		LONG lPan;
		SUCCEEDED_VERIFY(m_dsbuffer->GetPan(&lPan));
		return lPan;
	}

	void DSBuffer::setVolume(LONG lVolume)
	{
		SUCCEEDED_VERIFY(m_dsbuffer->SetVolume(lVolume));
	}

	LONG DSBuffer::getVolume(void)
	{
		LONG lVolume;
		SUCCEEDED_VERIFY(m_dsbuffer->GetVolume(&lVolume));
		return lVolume;
	}

	DS3DBufferPtr DSBuffer::createDS3DBuffer(void)
	{
		return DS3DBufferPtr(new DS3DBuffer(this));
	}

	DS3DListenerPtr DSBuffer::createDS3DListener(void)
	{
		return DS3DListenerPtr(new DS3DListener(this));
	}

	DS3DBuffer::DS3DBuffer(DSBuffer * dsbuffer)
	{
		FAILED_DSEXCEPT(dsbuffer->m_dsbuffer->QueryInterface(IID_IDirectSound3DBuffer8, (LPVOID *)&m_ds3dbuffer));
	}

	DS3DBuffer::~DS3DBuffer(void)
	{
	}

	void DS3DBuffer::setMaxDistance(D3DVALUE flMaxDistance, DWORD dwApply /*= DS3D_DEFERRED*/)
	{
		SUCCEEDED_VERIFY(m_ds3dbuffer->SetMaxDistance(flMaxDistance, dwApply));
	}

	D3DVALUE DS3DBuffer::getMaxDistance(void)
	{
		D3DVALUE value;
		SUCCEEDED_VERIFY(m_ds3dbuffer->GetMaxDistance(&value));
		return value;
	}

	void DS3DBuffer::setMinDistance(D3DVALUE flMinDistance, DWORD dwApply /*= DS3D_DEFERRED*/)
	{
		SUCCEEDED_VERIFY(m_ds3dbuffer->SetMinDistance(flMinDistance, dwApply));
	}

	D3DVALUE DS3DBuffer::getMinDistance(void)
	{
		D3DVALUE value;
		SUCCEEDED_VERIFY(m_ds3dbuffer->GetMinDistance(&value));
		return value;
	}

	void DS3DBuffer::setPosition(D3DVALUE x, D3DVALUE y, D3DVALUE z, DWORD dwApply /*= DS3D_DEFERRED*/)
	{
		SUCCEEDED_VERIFY(m_ds3dbuffer->SetPosition(x, y, z, dwApply));
	}

	D3DVECTOR DS3DBuffer::getPosition(void)
	{
		D3DVECTOR vector;
		SUCCEEDED_VERIFY(m_ds3dbuffer->GetPosition(&vector));
		return vector;
	}

	void DS3DBuffer::setVelocity(D3DVALUE x, D3DVALUE y, D3DVALUE z, DWORD dwApply /*= DS3D_DEFERRED*/)
	{
		SUCCEEDED_VERIFY(m_ds3dbuffer->SetVelocity(x, y, z, dwApply));
	}

	D3DVECTOR DS3DBuffer::getVelocity(void)
	{
		D3DVECTOR vector;
		SUCCEEDED_VERIFY(m_ds3dbuffer->GetVelocity(&vector));
		return vector;
	}

	void DS3DBuffer::setAllParameters(LPCDS3DBUFFER pcDs3dBuffer, DWORD dwApply /*= DS3D_DEFERRED*/)
	{
		SUCCEEDED_VERIFY(m_ds3dbuffer->SetAllParameters(pcDs3dBuffer, dwApply));
	}

	void DS3DBuffer::getAllParameters(LPDS3DBUFFER pDs3dBuffer)
	{
		SUCCEEDED_VERIFY(m_ds3dbuffer->GetAllParameters(pDs3dBuffer));
	}

	DS3DListener::DS3DListener(DSBuffer * dsbuffer)
	{
		FAILED_DSEXCEPT(dsbuffer->m_dsbuffer->QueryInterface(IID_IDirectSound3DListener8, (LPVOID *)&m_ds3dlistener));
	}

	DS3DListener::~DS3DListener(void)
	{
	}

	void DS3DListener::CommitDeferredSettings(void)
	{
		SUCCEEDED_VERIFY(m_ds3dlistener->CommitDeferredSettings());
	}

	void DS3DListener::SetOrientation(D3DVALUE xFront, D3DVALUE yFront, D3DVALUE zFront, D3DVALUE xTop, D3DVALUE yTop, D3DVALUE zTop, DWORD dwApply /*= DS3D_DEFERRED*/)
	{
		SUCCEEDED_VERIFY(m_ds3dlistener->SetOrientation(xFront, yFront, zFront, xTop, yTop, zTop, dwApply));
	}

	void DS3DListener::GetOrientation(D3DVECTOR * pvOrientFront, D3DVECTOR * pvOrientTop)
	{
		SUCCEEDED_VERIFY(m_ds3dlistener->GetOrientation(pvOrientFront, pvOrientTop));
	}

	void DS3DListener::setPosition(D3DVALUE x, D3DVALUE y, D3DVALUE z, DWORD dwApply /*= DS3D_DEFERRED*/)
	{
		SUCCEEDED_VERIFY(m_ds3dlistener->SetPosition(x, y, z, dwApply));
	}

	D3DVECTOR DS3DListener::getPosition(void)
	{
		D3DVECTOR vector;
		SUCCEEDED_VERIFY(m_ds3dlistener->GetPosition(&vector));
		return vector;
	}

	void DS3DListener::setVelocity(D3DVALUE x, D3DVALUE y, D3DVALUE z, DWORD dwApply /*= DS3D_DEFERRED*/)
	{
		SUCCEEDED_VERIFY(m_ds3dlistener->SetVelocity(x, y, z, dwApply));
	}

	D3DVECTOR DS3DListener::getVelocity(void)
	{
		D3DVECTOR vector;
		SUCCEEDED_VERIFY(m_ds3dlistener->GetVelocity(&vector));
		return vector;
	}

	void DS3DListener::setAllParameters(LPCDS3DLISTENER pcListener, DWORD dwApply /*= DS3D_DEFERRED*/)
	{
		SUCCEEDED_VERIFY(m_ds3dlistener->SetAllParameters(pcListener, dwApply));
	}

	void DS3DListener::getAllParameters(LPDS3DLISTENER pListener)
	{
		SUCCEEDED_VERIFY(m_ds3dlistener->GetAllParameters(pListener));
	}

	DSound::DSound(void)
	{
		FAILED_DSEXCEPT(DirectSoundCreate8(NULL, &m_dsound, NULL));
	}

	DSound::~DSound(void)
	{
	}

	void DSound::setCooperativeLevel(HWND hwnd, DWORD dwLevel /*= CL_PRIORITY*/)
	{
		FAILED_DSEXCEPT(m_dsound->SetCooperativeLevel(hwnd, dwLevel));
	}

	DSBufferPtr DSound::createSoundBuffer(LPCDSBUFFERDESC pcDSBufferDesc)
	{
		return DSBufferPtr(new DSBuffer(this, pcDSBufferDesc));
	}
}
