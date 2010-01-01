
#include "stdafx.h"
#include "t3dlib3.h"

#pragma comment(lib, "dsound.lib")

namespace t3d
{
	std::basic_string<charT> DSound::getResultStr(HRESULT hres)
	{
		const charT * pstr;
		switch(hres)
		{
		case DS_OK:
			pstr = _T("DS_OK"); break;
		case DS_NO_VIRTUALIZATION:
			pstr = _T("DS_NO_VIRTUALIZATION"); break;
		//case DS_INCOMPLETE:
		//	pstr = _T("DS_INCOMPLETE"); break;
		case DSERR_ACCESSDENIED:
			pstr = _T("DSERR_ACCESSDENIED"); break;
		case DSERR_ALLOCATED:
			pstr = _T("DSERR_ALLOCATED"); break;
		case DSERR_ALREADYINITIALIZED:
			pstr = _T("DSERR_ALREADYINITIALIZED"); break;
		case DSERR_BADFORMAT:
			pstr = _T("DSERR_BADFORMAT"); break;
		case DSERR_BADSENDBUFFERGUID:
			pstr = _T("DSERR_BADSENDBUFFERGUID"); break;
		case DSERR_BUFFERLOST:
			pstr = _T("DSERR_BUFFERLOST"); break;
		case DSERR_BUFFERTOOSMALL:
			pstr = _T("DSERR_BUFFERTOOSMALL"); break;
		case DSERR_CONTROLUNAVAIL:
			pstr = _T("DSERR_CONTROLUNAVAIL"); break;
		case DSERR_DS8_REQUIRED:
			pstr = _T("DSERR_DS8_REQUIRED"); break;
		case DSERR_FXUNAVAILABLE:
			pstr = _T("DSERR_FXUNAVAILABLE"); break;
		case DSERR_GENERIC:
			pstr = _T("DSERR_GENERIC"); break;
		case DSERR_INVALIDCALL:
			pstr = _T("DSERR_INVALIDCALL"); break;
		case DSERR_INVALIDPARAM:
			pstr = _T("DSERR_INVALIDPARAM"); break;
		case DSERR_NOAGGREGATION:
			pstr = _T("DSERR_NOAGGREGATION"); break;
		case DSERR_NODRIVER:
			pstr = _T("DSERR_NODRIVER"); break;
		case DSERR_NOINTERFACE:
			pstr = _T("DSERR_NOINTERFACE"); break;
		case DSERR_OBJECTNOTFOUND:
			pstr = _T("DSERR_OBJECTNOTFOUND"); break;
		case DSERR_OTHERAPPHASPRIO:
			pstr = _T("DSERR_OTHERAPPHASPRIO"); break;
		case DSERR_OUTOFMEMORY:
			pstr = _T("DSERR_OUTOFMEMORY"); break;
		case DSERR_PRIOLEVELNEEDED:
			pstr = _T("DSERR_PRIOLEVELNEEDED"); break;
		case DSERR_SENDLOOP:
			pstr = _T("DSERR_SENDLOOP"); break;
		case DSERR_UNINITIALIZED:
			pstr = _T("DSERR_UNINITIALIZED"); break;
		case DSERR_UNSUPPORTED:
			pstr = _T("DSERR_UNSUPPORTED"); break;
		default:
			pstr = _T("unknown dsound error result"); break;
		}

		return std::basic_string<charT>(pstr);
	}

	t3d::DSound::Exception::Exception(const std::basic_string<charT> & file, int line, HRESULT hres)
		: t3d::Exception(file, line)
		, m_hres(hres)
	{
	}

	std::basic_string<charT> t3d::DSound::Exception::what(void) const throw()
	{
		return getResultStr(m_hres);
	}

#define T3D_DSEXCEPT(hres) { throw t3d::DSound::Exception(_T(__FILE__), __LINE__, (hres)); }

	DSound::DSound(void)
		: m_lpdsound(NULL)
	{
		HRESULT hres;
		if(FAILED(hres = ::DirectSoundCreate8(NULL, &m_lpdsound, NULL)))
			T3D_DSEXCEPT(hres);
	}

	DSound::~DSound(void)
	{
		SAFE_RELEASE(m_lpdsound);
	}

	void DSound::setCooperativeLevel(HWND hwnd, DWORD level /*= CL_PRIORITY*/)
	{
		HRESULT hres;
		if(FAILED(hres = m_lpdsound->SetCooperativeLevel(hwnd, level)))
			T3D_DSEXCEPT(hres);
	}

	DSound::Buffer::Buffer(DSound * sound, const DSBUFFERDESC & dsbd)
	{
		HRESULT hres;
		if(FAILED(hres = sound->m_lpdsound->CreateSoundBuffer(&dsbd, &m_lpdsbuffer, NULL)))
			T3D_DSEXCEPT(hres);
	}

	DSound::Buffer::~Buffer(void)
	{
		SAFE_RELEASE(m_lpdsbuffer);
	}

	void DSound::Buffer::setCurrentPosition(DWORD position)
	{
		HRESULT hres;
		if(FAILED(hres = m_lpdsbuffer->SetCurrentPosition(position)))
			T3D_DSEXCEPT(hres);
	}

	void DSound::Buffer::getCurrentPosition(LPDWORD pCurrentPlayCursor, LPDWORD pCurrentWriteCursor /*= NULL*/) const
	{
		HRESULT hres;
		if(FAILED(hres = m_lpdsbuffer->GetCurrentPosition(pCurrentPlayCursor, pCurrentWriteCursor)))
			T3D_DSEXCEPT(hres);
	}

	void DSound::Buffer::lock(DWORD offset, DWORD bytes, LPVOID * audioPtr1, LPDWORD  audioBytes1, LPVOID * audioPtr2, LPDWORD audioBytes2, DWORD flags)
	{
		HRESULT hres;
		if(FAILED(hres = m_lpdsbuffer->Lock(offset, bytes, audioPtr1, audioBytes1, audioPtr2, audioBytes2, flags)))
			T3D_DSEXCEPT(hres);
	}

	void DSound::Buffer::unlock(LPVOID audioPtr1, DWORD audioBytes1, LPVOID audioPtr2, DWORD audioBytes2)
	{
		HRESULT hres;
		if(FAILED(hres = m_lpdsbuffer->Unlock(audioPtr1, audioBytes1, audioPtr2, audioBytes2)))
			T3D_DSEXCEPT(hres);
	}

	void DSound::Buffer::play(DWORD priority /*= 0*/, DWORD flags /*= 0*/)
	{
		HRESULT hres;
		if(FAILED(hres = m_lpdsbuffer->Play(0, priority, flags)))
			T3D_DSEXCEPT(hres);
	}

	void DSound::Buffer::stop(void)
	{
		HRESULT hres;
		if(FAILED(hres = m_lpdsbuffer->Stop()))
			T3D_DSEXCEPT(hres);
	}

	void DSound::Buffer::setFrequency(DWORD frequency)
	{
		HRESULT hres;
		if(FAILED(hres = m_lpdsbuffer->SetFrequency(frequency)))
			T3D_DSEXCEPT(hres);
	}

	DWORD DSound::Buffer::getFrequency(void) const
	{
		DWORD ret;
		HRESULT hres;
		if(FAILED(hres = m_lpdsbuffer->GetFrequency(&ret)))
			T3D_DSEXCEPT(hres);

		return ret;
	}

	void DSound::Buffer::setPan(LONG lPan)
	{
		HRESULT hres;
		if(FAILED(hres = m_lpdsbuffer->SetPan(lPan)))
			T3D_DSEXCEPT(hres);
	}

	LONG DSound::Buffer::getPan(void) const
	{
		LONG ret;
		HRESULT hres;
		if(FAILED(hres = m_lpdsbuffer->GetPan(&ret)))
			T3D_DSEXCEPT(hres);

		return ret;
	}

	void DSound::Buffer::setVolume(LONG lVolume)
	{
		HRESULT hres;
		if(FAILED(hres = m_lpdsbuffer->SetVolume(lVolume)))
			T3D_DSEXCEPT(hres);
	}

	LONG DSound::Buffer::getVolume(void) const
	{
		LONG ret;
		HRESULT hres;
		if(FAILED(hres = m_lpdsbuffer->GetVolume(&ret)))
			T3D_DSEXCEPT(hres);

		return ret;
	}
}
