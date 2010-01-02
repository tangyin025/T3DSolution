
#include "stdafx.h"
#include "t3dlib3.h"

#pragma comment(lib, "dsound.lib")

namespace t3d
{
#define CASE_RETURN_STRING(branch) case branch: return std::basic_string<charT>(_T( #branch ));

	std::basic_string<charT> DSException::GetResultStr(HRESULT hres)
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
		return GetResultStr(m_hres);
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

	void DSBuffer::SetCurrentPosition(DWORD dwNewPosition)
	{
		SUCCEEDED_VERIFY(m_dsbuffer->SetCurrentPosition(dwNewPosition));
	}

	void DSBuffer::GetCurrentPosition(LPDWORD pdwCurrentPlayCursor, LPDWORD pdwCurrentWriteCursor /*= NULL*/)
	{
		SUCCEEDED_VERIFY(m_dsbuffer->GetCurrentPosition(pdwCurrentPlayCursor, pdwCurrentWriteCursor));
	}

	void DSBuffer::Lock(DWORD dwOffset, DWORD dwBytes, LPVOID * ppvAudioPtr1, LPDWORD  pdwAudioBytes1, LPVOID * ppvAudioPtr2, LPDWORD pdwAudioBytes2, DWORD dwFlags)
	{
		FAILED_DSEXCEPT(m_dsbuffer->Lock(dwOffset, dwBytes, ppvAudioPtr1, pdwAudioBytes1, ppvAudioPtr2, pdwAudioBytes2, dwFlags));
	}

	void DSBuffer::Unlock(LPVOID pvAudioPtr1, DWORD dwAudioBytes1, LPVOID pvAudioPtr2, DWORD dwAudioBytes2)
	{
		SUCCEEDED_VERIFY(m_dsbuffer->Unlock(pvAudioPtr1, dwAudioBytes1, pvAudioPtr2, dwAudioBytes2));
	}

	void DSBuffer::Play(DWORD dwPriority /*= 0*/, DWORD dwFlags /*= 0*/)
	{
		FAILED_DSEXCEPT(m_dsbuffer->Play(0, dwPriority, dwFlags));
	}

	void DSBuffer::Stop(void)
	{
		SUCCEEDED_VERIFY(m_dsbuffer->Stop());
	}

	void DSBuffer::SetFrequency(DWORD dwFrequency)
	{
		SUCCEEDED_VERIFY(m_dsbuffer->SetFrequency(dwFrequency));
	}

	DWORD DSBuffer::GetFrequency(void)
	{
		DWORD dwFrequency;
		SUCCEEDED_VERIFY(m_dsbuffer->GetFrequency(&dwFrequency));

		return dwFrequency;
	}

	void DSBuffer::SetPan(LONG lPan)
	{
		SUCCEEDED_VERIFY(m_dsbuffer->SetPan(lPan));
	}

	LONG DSBuffer::GetPan(void)
	{
		LONG lPan;
		SUCCEEDED_VERIFY(m_dsbuffer->GetPan(&lPan));

		return lPan;
	}

	void DSBuffer::SetVolume(LONG lVolume)
	{
		SUCCEEDED_VERIFY(m_dsbuffer->SetVolume(lVolume));
	}

	LONG DSBuffer::GetVolume(void)
	{
		LONG lVolume;
		SUCCEEDED_VERIFY(m_dsbuffer->GetVolume(&lVolume));

		return lVolume;
	}

	DSound::DSound(void)
	{
		FAILED_DSEXCEPT(DirectSoundCreate8(NULL, &m_dsound, NULL));
	}

	DSound::~DSound(void)
	{
	}

	void DSound::SetCooperativeLevel(HWND hwnd, DWORD dwLevel /*= CL_PRIORITY*/)
	{
		FAILED_DSEXCEPT(m_dsound->SetCooperativeLevel(hwnd, dwLevel));
	}

	DSBufferPtr DSound::CreateSoundBuffer(LPCDSBUFFERDESC pcDSBufferDesc)
	{
		return DSBufferPtr(new DSBuffer(this, pcDSBufferDesc));
	}
}
