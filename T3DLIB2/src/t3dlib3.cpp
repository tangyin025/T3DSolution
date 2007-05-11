/**
 * File: T3DLIB2/t3dlib3.cpp
 */

#include "t3dheaders.h"
#include "t3dlib1.h"
#include "t3dlib3.h"

#define GET_DSOUND_ERROR(h)		(Get_DSound_Error(gbuffer, (h)))
#define GET_DMUSIC_ERROR(h)		(Get_DMusic_Error(gbuffer, (h)))
#define CARE_STOP(o)			{ if((o) != NULL) { (o)->Stop(); } }

_CTOR_IMPLEMENT(WAVV1_TYP);
_DTOR_IMPLEMENT_W1(WAVV1_TYP, Destroy_Wav, pbuffer);

_CTOR_IMPLEMENT(DSOUNDV1_TYP);
_DTOR_IMPLEMENT_W1(DSOUNDV1_TYP, Destroy_DSound, lpdsound);

_CTOR_IMPLEMENT(DSBUFFERV1_TYP);
_DTOR_IMPLEMENT_W1(DSBUFFERV1_TYP, Destroy_DSBuffer, lpdsbuffer);

T3DLIB_API char * Get_DSound_Error(char * pbuffer, const HRESULT hresult)
{
	char * pmsg = "no message";
	switch(hresult)
	{
	case DS_OK:
		pmsg = "DS_OK"; break;
	case DS_NO_VIRTUALIZATION:
		pmsg = "DS_NO_VIRTUALIZATION"; break;
	//case DS_INCOMPLETE:
	//	pmsg = "DS_INCOMPLETE"; break;
	case DSERR_ACCESSDENIED:
		pmsg = "DSERR_ACCESSDENIED"; break;
	case DSERR_ALLOCATED:
		pmsg = "DSERR_ALLOCATED"; break;
	case DSERR_ALREADYINITIALIZED:
		pmsg = "DSERR_ALREADYINITIALIZED"; break;
	case DSERR_BADFORMAT:
		pmsg = "DSERR_BADFORMAT"; break;
	case DSERR_BADSENDBUFFERGUID:
		pmsg = "DSERR_BADSENDBUFFERGUID"; break;
	case DSERR_BUFFERLOST:
		pmsg = "DSERR_BUFFERLOST"; break;
	case DSERR_BUFFERTOOSMALL:
		pmsg = "DSERR_BUFFERTOOSMALL"; break;
	case DSERR_CONTROLUNAVAIL:
		pmsg = "DSERR_CONTROLUNAVAIL"; break;
	case DSERR_DS8_REQUIRED:
		pmsg = "DSERR_DS8_REQUIRED"; break;
	case DSERR_FXUNAVAILABLE:
		pmsg = "DSERR_FXUNAVAILABLE"; break;
	case DSERR_GENERIC:
		pmsg = "DSERR_GENERIC"; break;
	case DSERR_INVALIDCALL:
		pmsg = "DSERR_INVALIDCALL"; break;
	case DSERR_INVALIDPARAM:
		pmsg = "DSERR_INVALIDPARAM"; break;
	case DSERR_NOAGGREGATION:
		pmsg = "DSERR_NOAGGREGATION"; break;
	case DSERR_NODRIVER:
		pmsg = "DSERR_NODRIVER"; break;
	case DSERR_NOINTERFACE:
		pmsg = "DSERR_NOINTERFACE"; break;
	case DSERR_OBJECTNOTFOUND:
		pmsg = "DSERR_OBJECTNOTFOUND"; break;
	case DSERR_OTHERAPPHASPRIO:
		pmsg = "DSERR_OTHERAPPHASPRIO"; break;
	case DSERR_OUTOFMEMORY:
		pmsg = "DSERR_OUTOFMEMORY"; break;
	case DSERR_PRIOLEVELNEEDED:
		pmsg = "DSERR_PRIOLEVELNEEDED"; break;
	case DSERR_SENDLOOP:
		pmsg = "DSERR_SENDLOOP"; break;
	case DSERR_UNINITIALIZED:
		pmsg = "DSERR_UNINITIALIZED"; break;
	case DSERR_UNSUPPORTED:
		pmsg = "DSERR_UNSUPPORTED"; break;
	default:
		//_ASSERT(0);
		pmsg = "unknown dsound error result"; break;
	}
	return strcpy(pbuffer, pmsg);
}

T3DLIB_API bool Create_DSound(DSOUNDV1 * pdsound, const HWND hwnd)
{
	LPDIRECTSOUND8 lpds = NULL;
	if(FAILED(gresult = DirectSoundCreate8(NULL, &lpds, NULL)))
		ON_ERROR_GOTO(GET_DSOUND_ERROR(gresult));

	if(FAILED(gresult = lpds->SetCooperativeLevel(hwnd, DSSCL_NORMAL)))
		ON_ERROR_GOTO(GET_DSOUND_ERROR(gresult));

	pdsound->lpdsound = lpds;
	return true;

ON_ERROR:
	SAFE_RELEASE(lpds);
	return false;
}

T3DLIB_API bool Create_Wav_From_File(WAVV1 * pwav, char * fname)
{
	HMMIO	hwav = NULL;
	unsigned char * pbuffer = NULL;

	if(NULL == (hwav = mmioOpenA(fname, NULL, MMIO_READ | MMIO_ALLOCBUF)))
		ON_ERROR_GOTO("open wave file failed");

	pwav->parent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	if(MMSYSERR_NOERROR != mmioDescend(hwav, &pwav->parent, NULL, MMIO_FINDRIFF))
		ON_ERROR_GOTO("mmioDescend parent failed");

	pwav->child.fccType = mmioFOURCC('f', 'm', 't', ' ');
	if(MMSYSERR_NOERROR != mmioDescend(hwav, &pwav->child, &pwav->parent, 0))
		ON_ERROR_GOTO("mmioDescend child failed");

	if(sizeof(pwav->wavfmt) != mmioRead(hwav, (HPSTR)&pwav->wavfmt, sizeof(pwav->wavfmt)))
		ON_ERROR_GOTO("mmioRead wav format failed");

	if(WAVE_FORMAT_PCM != pwav->wavfmt.wFormatTag)
		ON_ERROR_GOTO("not wave format pcm");

	if(MMSYSERR_NOERROR != mmioAscend(hwav, &pwav->child, 0))
		ON_ERROR_GOTO("mmioAscend child failed");

	pwav->child.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if(MMSYSERR_NOERROR != mmioDescend(hwav, &pwav->child, &pwav->parent, 0))
		ON_ERROR_GOTO("mmioDescend child failed");

	if(NULL == (pbuffer = (unsigned char *)malloc(pwav->child.cksize)))
		ON_ERROR_GOTO("malloc buffer failed");

	if((LONG)pwav->child.cksize != mmioRead(hwav, (HPSTR)pbuffer, pwav->child.cksize))
		ON_ERROR_GOTO("mmioRead wav buffer failed");

	pwav->hwav		= hwav;
	pwav->pbuffer	= pbuffer;
	return true;

ON_ERROR:
	if(hwav != NULL)
	{
		mmioClose(hwav, 0);
		hwav = NULL;
	}
	SAFE_DELETE(pbuffer);
	return false;
}

T3DLIB_API bool Create_DSBuffer_From_Wav(	DSOUNDV1 * pdsound,
											DSBUFFERV1 * pdsbuffer,
											const WAVV1 * pwav,
											const int flags					/*= DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME*/,
											const unsigned short channels	/*= 1*/,
											const unsigned int sps			/*= 11025*/)
{
	assert(pwav->hwav != NULL);
	assert(pwav->pbuffer != NULL);

	LPDIRECTSOUNDBUFFER		lpdsbuffer = NULL;
	DSBUFFERDESC			dsbd;

	pdsbuffer->wavfmt.wFormatTag		= pwav->wavfmt.wFormatTag;
	pdsbuffer->wavfmt.nChannels			= channels;
	pdsbuffer->wavfmt.nSamplesPerSec	= sps;
	pdsbuffer->wavfmt.wBitsPerSample	= pwav->wavfmt.wBitsPerSample;
	pdsbuffer->wavfmt.cbSize			= 0;
	pdsbuffer->wavfmt.nBlockAlign		= pdsbuffer->wavfmt.nChannels * pdsbuffer->wavfmt.wBitsPerSample >> 3;
	pdsbuffer->wavfmt.nAvgBytesPerSec	= pdsbuffer->wavfmt.nSamplesPerSec * pdsbuffer->wavfmt.nBlockAlign;

	memset(&dsbd, 0, sizeof(dsbd));
	dsbd.dwSize = sizeof(dsbd);
	dsbd.dwFlags				= flags | DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE;
	dsbd.dwBufferBytes			= pwav->child.cksize;
	dsbd.lpwfxFormat			= &pdsbuffer->wavfmt;

	if(FAILED(gresult = pdsound->lpdsound->CreateSoundBuffer(&dsbd, &lpdsbuffer, NULL)))
		ON_ERROR_GOTO(GET_DSOUND_ERROR(gresult));

	CHAR	* pbuf1, * pbuf2;
	DWORD	len1, len2;
	if(FAILED(gresult = lpdsbuffer->Lock(0, pwav->child.cksize,
			(LPVOID *)&pbuf1, &len1, (LPVOID *)&pbuf2, &len2, DSBLOCK_FROMWRITECURSOR)))
		ON_ERROR_GOTO(GET_DSOUND_ERROR(gresult));

	if(pbuf1 != NULL)
		memcpy(pbuf1, pwav->pbuffer, len1);
	if(pbuf2 != NULL)
	{
		assert(len1 + len2 <= pwav->child.cksize);
		memcpy(pbuf2, pwav->pbuffer + len1, len2);
	}

	if(FAILED(gresult = lpdsbuffer->Unlock(pbuf1, len1, pbuf2, len2)))
		ON_ERROR_GOTO(GET_DSOUND_ERROR(gresult));

	pdsbuffer->lpdsbuffer = lpdsbuffer;
	return true;

ON_ERROR:
	SAFE_RELEASE(lpdsbuffer);
	return false;
}

T3DLIB_API void Destroy_DSound(DSOUNDV1 * pdsound)
{
	SAFE_RELEASE(pdsound->lpdsound);
}

T3DLIB_API void Destroy_Wav(WAVV1 * pwav)
{
	if(pwav->hwav != NULL)
	{
		mmioClose(pwav->hwav, 0);
		pwav->hwav = NULL;
	}
	SAFE_DELETE(pwav->pbuffer);
}

T3DLIB_API void Destroy_DSBuffer(DSBUFFERV1 * pdsbuffer)
{
	CARE_STOP(pdsbuffer->lpdsbuffer);
	SAFE_RELEASE(pdsbuffer->lpdsbuffer);
}

//T3DLIB_API bool Load_DSBuffer_From_Wav_File(DSBUFFERV1 * pdsbuffer, const char * fname);

//T3DLIB_API bool Load_DSBuffer_From_Mp3_File(DSBUFFERV1 * pdsbuffer, const char * fname);

T3DLIB_API bool Play_DSBuffer(DSBUFFERV1 * pdsbuffer, const int flags /*= 0*/)
{
	if(FAILED(gresult = pdsbuffer->lpdsbuffer->SetCurrentPosition(0)))
		ON_ERROR_GOTO(GET_DSOUND_ERROR(gresult));

	if(FAILED(gresult = pdsbuffer->lpdsbuffer->Play(0, 0, flags)))
		ON_ERROR_GOTO(GET_DSOUND_ERROR(gresult));
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Stop_DSBuffer(DSBUFFERV1 * pdsbuffer)
{
	if(FAILED(gresult = pdsbuffer->lpdsbuffer->Stop()))
		ON_ERROR_GOTO(GET_DSOUND_ERROR(gresult));
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Get_DSBuffer_Status(DSBUFFERV1 * pdsbuffer, int * pstatus)
{
	static DWORD status;
	if(FAILED(gresult = pdsbuffer->lpdsbuffer->GetStatus(&status)))
		ON_ERROR_GOTO(GET_DSOUND_ERROR(gresult));
	if(status & DSBSTATUS_PLAYING)
		*pstatus = DSBUFFER_STATUS_PLAYING;
	else
		*pstatus = DSBUFFER_STATUS_STOPPED;
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Set_DSBuffer_Volume(DSBUFFERV1 * pdsbuffer, const long volume)
{
	if(FAILED(gresult = pdsbuffer->lpdsbuffer->SetVolume(volume)))
		ON_ERROR_GOTO(GET_DSOUND_ERROR(gresult));
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Set_DSBuffer_Frequency(DSBUFFERV1 * pdsbuffer, const unsigned int frequency)
{
	if(FAILED(gresult = pdsbuffer->lpdsbuffer->SetFrequency(frequency)))
		ON_ERROR_GOTO(GET_DSOUND_ERROR(gresult));
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Set_DSBuffer_Pan(DSBUFFERV1 * pdsbuffer, const long pan)
{
	if(FAILED(gresult = pdsbuffer->lpdsbuffer->SetPan(pan)))
		ON_ERROR_GOTO(GET_DSOUND_ERROR(gresult));
	return true;

ON_ERROR:
	return false;
}

DMPERFORMANCEV1_TYP::DMPERFORMANCEV1_TYP()
	: lpdmperf(NULL)
{
	;
}

DMPERFORMANCEV1_TYP::~DMPERFORMANCEV1_TYP()
{
	_WARNING(lpdmperf != NULL);
	Destroy_DMPerformance(this);
}

DMLOADERV1_TYP::DMLOADERV1_TYP()
	: lpdmloader(NULL)
{
	;
}

DMLOADERV1_TYP::~DMLOADERV1_TYP()
{
	_WARNING(lpdmloader != NULL);
	Destroy_DMLoader(this);
}

DMSEGMENTV1_TYP::DMSEGMENTV1_TYP()
	: lpdmsegment(NULL)
	, lpdmsegment_state(NULL)
	, pdmperf(NULL)
{
	;
}

DMSEGMENTV1_TYP::~DMSEGMENTV1_TYP()
{
	_WARNING(lpdmsegment != NULL);
	Destroy_DMSegment(this);
}

T3DLIB_API char * Get_DMusic_Error(char * pbuffer, const HRESULT hresult)
{
	char * pmsg = "no message";
	switch(hresult)
	{
	case CLASS_E_NOAGGREGATION:
		pmsg = "CLASS_E_NOAGGREGATION"; break;
	case DMUS_E_ALL_TOOLS_FAILED:
		pmsg = "DMUS_E_ALL_TOOLS_FAILED"; break;
	case DMUS_E_ALL_TRACKS_FAILED:
		pmsg = "DMUS_E_ALL_TRACKS_FAILED"; break;
	case DMUS_E_ALREADY_ACTIVATED:
		pmsg = "DMUS_E_ALREADY_ACTIVATED"; break;
	case DMUS_E_ALREADY_DOWNLOADED:
		pmsg = "DMUS_E_ALREADY_DOWNLOADED"; break;
	case DMUS_E_ALREADY_EXISTS:
		pmsg = "DMUS_E_ALREADY_EXISTS"; break;
	case DMUS_E_ALREADY_INITED:
		pmsg = "DMUS_E_ALREADY_INITED"; break;
	case DMUS_E_ALREADY_LOADED:
		pmsg = "DMUS_E_ALREADY_LOADED"; break;
	case DMUS_E_ALREADY_SENT:
		pmsg = "DMUS_E_ALREADY_SENT"; break;
	case DMUS_E_ALREADYCLOSED:
		pmsg = "DMUS_E_ALREADYCLOSED"; break;
	case DMUS_E_ALREADYOPEN:
		pmsg = "DMUS_E_ALREADYOPEN"; break;
	case DMUS_E_AUDIOPATH_INACTIVE:
		pmsg = "DMUS_E_AUDIOPATH_INACTIVE"; break;
	case DMUS_E_AUDIOPATH_NOBUFFER:
		pmsg = "DMUS_E_AUDIOPATH_NOBUFFER"; break;
	case DMUS_E_AUDIOPATH_NOGLOBALFXBUFFER:
		pmsg = "DMUS_E_AUDIOPATH_NOGLOBALFXBUFFER"; break;
	case DMUS_E_AUDIOPATH_NOPORT:
		pmsg = "DMUS_E_AUDIOPATH_NOPORT"; break;
	case DMUS_E_AUDIOPATHS_IN_USE:
		pmsg = "DMUS_E_AUDIOPATHS_IN_USE"; break;
	case DMUS_E_AUDIOPATHS_NOT_VALID:
		pmsg = "DMUS_E_AUDIOPATHS_NOT_VALID"; break;
	case DMUS_E_AUDIOVBSCRIPT_OPERATIONFAILURE:
		pmsg = "DMUS_E_AUDIOVBSCRIPT_OPERATIONFAILURE"; break;
	case DMUS_E_AUDIOVBSCRIPT_RUNTIMEERROR:
		pmsg = "DMUS_E_AUDIOVBSCRIPT_RUNTIMEERROR"; break;
	case DMUS_E_AUDIOVBSCRIPT_SYNTAXERROR:
		pmsg = "DMUS_E_AUDIOVBSCRIPT_SYNTAXERROR"; break;
	case DMUS_E_BADARTICULATION:
		pmsg = "DMUS_E_BADARTICULATION"; break;
	case DMUS_E_BADINSTRUMENT:
		pmsg = "DMUS_E_BADINSTRUMENT"; break;
	case DMUS_E_BADOFFSETTABLE:
		pmsg = "DMUS_E_BADOFFSETTABLE"; break;
	case DMUS_E_BADWAVE:
		pmsg = "DMUS_E_BADWAVE"; break;
	case DMUS_E_BADWAVELINK:
		pmsg = "DMUS_E_BADWAVELINK"; break;
	case DMUS_E_BUFFER_EMPTY:
		pmsg = "DMUS_E_BUFFER_EMPTY"; break;
	case DMUS_E_BUFFER_FULL:
		pmsg = "DMUS_E_BUFFER_FULL"; break;
	case DMUS_E_BUFFERNOTAVAILABLE:
		pmsg = "DMUS_E_BUFFERNOTAVAILABLE"; break;
	case DMUS_E_BUFFERNOTSET:
		pmsg = "DMUS_E_BUFFERNOTSET"; break;
	case DMUS_E_CANNOT_CONVERT:
		pmsg = "DMUS_E_CANNOT_CONVERT"; break;
	case DMUS_E_CANNOT_FREE:
		pmsg = "DMUS_E_CANNOT_FREE"; break;
	case DMUS_E_CANNOT_OPEN_PORT:
		pmsg = "DMUS_E_CANNOT_OPEN_PORT"; break;
	case DMUS_E_CANNOTREAD:
		pmsg = "DMUS_E_CANNOTREAD"; break;
	case DMUS_E_CANNOTSEEK:
		pmsg = "DMUS_E_CANNOTSEEK"; break;
	case DMUS_E_CANNOTWRITE:
		pmsg = "DMUS_E_CANNOTWRITE"; break;
	case DMUS_E_CHUNKNOTFOUND:
		pmsg = "DMUS_E_CHUNKNOTFOUND"; break;
	case DMUS_E_DESCEND_CHUNK_FAIL:
		pmsg = "DMUS_E_DESCEND_CHUNK_FAIL"; break;
	case DMUS_E_DEVICE_IN_USE:
		pmsg = "DMUS_E_DEVICE_IN_USE"; break;
	case DMUS_E_DMUSIC_RELEASED:
		pmsg = "DMUS_E_DMUSIC_RELEASED"; break;
	case DMUS_E_DRIVER_FAILED:
		pmsg = "DMUS_E_DRIVER_FAILED"; break;
	case DMUS_E_DSOUND_ALREADY_SET:
		pmsg = "DMUS_E_DSOUND_ALREADY_SET"; break;
	case DMUS_E_DSOUND_NOT_SET:
		pmsg = "DMUS_E_DSOUND_NOT_SET"; break;
	case DMUS_E_GET_UNSUPPORTED:
		pmsg = "DMUS_E_GET_UNSUPPORTED"; break;
	case DMUS_E_INSUFFICIENTBUFFER:
		pmsg = "DMUS_E_INSUFFICIENTBUFFER"; break;
	case DMUS_E_INVALID_BAND:
		pmsg = "DMUS_E_INVALID_BAND"; break;
	case DMUS_E_INVALID_CONTAINER_OBJECT:
		pmsg = "DMUS_E_INVALID_CONTAINER_OBJECT"; break;
	case DMUS_E_INVALID_DOWNLOADID:
		pmsg = "DMUS_E_INVALID_DOWNLOADID"; break;
	case DMUS_E_INVALID_EVENT:
		pmsg = "DMUS_E_INVALID_EVENT"; break;
	case DMUS_E_INVALID_LYRICSTRACK:
		pmsg = "DMUS_E_INVALID_LYRICSTRACK"; break;
	case DMUS_E_INVALID_PARAMCONTROLTRACK:
		pmsg = "DMUS_E_INVALID_PARAMCONTROLTRACK"; break;
	case DMUS_E_INVALID_SCRIPTTRACK:
		pmsg = "DMUS_E_INVALID_SCRIPTTRACK"; break;
	case DMUS_E_INVALID_SEGMENTTRIGGERTRACK:
		pmsg = "DMUS_E_INVALID_SEGMENTTRIGGERTRACK"; break;
	case DMUS_E_INVALID_TOOL_HDR:
		pmsg = "DMUS_E_INVALID_TOOL_HDR"; break;
	case DMUS_E_INVALID_TRACK_HDR:
		pmsg = "DMUS_E_INVALID_TRACK_HDR"; break;
	case DMUS_E_INVALIDBUFFER:
		pmsg = "DMUS_E_INVALIDBUFFER"; break;
	case DMUS_E_INVALIDCHUNK:
		pmsg = "DMUS_E_INVALIDCHUNK"; break;
	case DMUS_E_INVALIDFILE:
		pmsg = "DMUS_E_INVALIDFILE"; break;
	case DMUS_E_INVALIDOFFSET:
		pmsg = "DMUS_E_INVALIDOFFSET"; break;
	case DMUS_E_INVALIDPATCH:
		pmsg = "DMUS_E_INVALIDPATCH"; break;
	case DMUS_E_INVALIDPOS:
		pmsg = "DMUS_E_INVALIDPOS"; break;
	case DMUS_E_LOADER_BADPATH:
		pmsg = "DMUS_E_LOADER_BADPATH"; break;
	case DMUS_E_LOADER_FAILEDCREATE:
		pmsg = "DMUS_E_LOADER_FAILEDCREATE"; break;
	case DMUS_E_LOADER_FAILEDOPEN:
		pmsg = "DMUS_E_LOADER_FAILEDOPEN"; break;
	case DMUS_E_LOADER_FORMATNOTSUPPORTED:
		pmsg = "DMUS_E_LOADER_FORMATNOTSUPPORTED"; break;
	case DMUS_E_LOADER_NOCLASSID:
		pmsg = "DMUS_E_LOADER_NOCLASSID"; break;
	case DMUS_E_LOADER_NOFILENAME:
		pmsg = "DMUS_E_LOADER_NOFILENAME"; break;
	case DMUS_E_LOADER_OBJECTNOTFOUND:
		pmsg = "DMUS_E_LOADER_OBJECTNOTFOUND"; break;
	case DMUS_E_NO_AUDIOPATH:
		pmsg = "DMUS_E_NO_AUDIOPATH"; break;
	case DMUS_E_NO_AUDIOPATH_CONFIG:
		pmsg = "DMUS_E_NO_AUDIOPATH_CONFIG"; break;
	case DMUS_E_NO_MASTER_CLOCK:
		pmsg = "DMUS_E_NO_MASTER_CLOCK"; break;
	case DMUS_E_NOARTICULATION:
		pmsg = "DMUS_E_NOARTICULATION"; break;
	case DMUS_E_NOSYNTHSINK:
		pmsg = "DMUS_E_NOSYNTHSINK"; break;
	case DMUS_E_NOT_DOWNLOADED_TO_PORT:
		pmsg = "DMUS_E_NOT_DOWNLOADED_TO_PORT"; break;
	case DMUS_E_NOT_FOUND:
		pmsg = "DMUS_E_NOT_FOUND"; break;
	case DMUS_E_NOT_INIT:
		pmsg = "DMUS_E_NOT_INIT"; break;
	case DMUS_E_NOT_LOADED:
		pmsg = "DMUS_E_NOT_LOADED"; break;
	case DMUS_E_NOTADLSCOL:
		pmsg = "DMUS_E_NOTADLSCOL"; break;
	case DMUS_E_NOTMONO:
		pmsg = "DMUS_E_NOTMONO"; break;
	case DMUS_E_NOTPCM:
		pmsg = "DMUS_E_NOTPCM"; break;
	case DMUS_E_OUT_OF_RANGE:
		pmsg = "DMUS_E_OUT_OF_RANGE"; break;
	case DMUS_E_PORT_NOT_CAPTURE:
		pmsg = "DMUS_E_PORT_NOT_CAPTURE"; break;
	case DMUS_E_PORT_NOT_RENDER:
		pmsg = "DMUS_E_PORT_NOT_RENDER"; break;
	case DMUS_E_PORTS_OPEN:
		pmsg = "DMUS_E_PORTS_OPEN"; break;
	case DMUS_E_SCRIPT_CANTLOAD_OLEAUT32:
		pmsg = "DMUS_E_SCRIPT_CANTLOAD_OLEAUT32"; break;
	case DMUS_E_SCRIPT_CONTENT_READONLY:
		pmsg = "DMUS_E_SCRIPT_CONTENT_READONLY"; break;
	case DMUS_E_SCRIPT_ERROR_IN_SCRIPT:
		pmsg = "DMUS_E_SCRIPT_ERROR_IN_SCRIPT"; break;
	case DMUS_E_SCRIPT_INVALID_FILE:
		pmsg = "DMUS_E_SCRIPT_INVALID_FILE"; break;
	case DMUS_E_SCRIPT_LANGUAGE_INCOMPATIBLE:
		pmsg = "DMUS_E_SCRIPT_LANGUAGE_INCOMPATIBLE"; break;
	case DMUS_E_SCRIPT_LOADSCRIPT_ERROR:
		pmsg = "DMUS_E_SCRIPT_LOADSCRIPT_ERROR"; break;
	case DMUS_E_SCRIPT_NOT_A_REFERENCE:
		pmsg = "DMUS_E_SCRIPT_NOT_A_REFERENCE"; break;
	case DMUS_E_SCRIPT_ROUTINE_NOT_FOUND:
		pmsg = "DMUS_E_SCRIPT_ROUTINE_NOT_FOUND"; break;
	case DMUS_E_SCRIPT_UNSUPPORTED_VARTYPE:
		pmsg = "DMUS_E_SCRIPT_UNSUPPORTED_VARTYPE"; break;
	case DMUS_E_SCRIPT_VALUE_NOT_SUPPORTED:
		pmsg = "DMUS_E_SCRIPT_VALUE_NOT_SUPPORTED"; break;
	case DMUS_E_SCRIPT_VARIABLE_NOT_FOUND:
		pmsg = "DMUS_E_SCRIPT_VARIABLE_NOT_FOUND"; break;
	case DMUS_E_SEGMENT_INIT_FAILED:
		pmsg = "DMUS_E_SEGMENT_INIT_FAILED"; break;
	case DMUS_E_SET_UNSUPPORTED:
		pmsg = "DMUS_E_SET_UNSUPPORTED"; break;
	case DMUS_E_SYNTHACTIVE:
		pmsg = "DMUS_E_SYNTHACTIVE"; break;
	case DMUS_E_SYNTHINACTIVE:
		pmsg = "DMUS_E_SYNTHINACTIVE"; break;
	case DMUS_E_SYNTHNOTCONFIGURED:
		pmsg = "DMUS_E_SYNTHNOTCONFIGURED"; break;
	case DMUS_E_TIME_PAST:
		pmsg = "DMUS_E_TIME_PAST"; break;
	case DMUS_E_TOOL_HDR_NOT_FIRST_CK:
		pmsg = "DMUS_E_TOOL_HDR_NOT_FIRST_CK"; break;
	case DMUS_E_TRACK_HDR_NOT_FIRST_CK:
		pmsg = "DMUS_E_TRACK_HDR_NOT_FIRST_CK"; break;
	case DMUS_E_TRACK_NO_CLOCKTIME_SUPPORT:
		pmsg = "DMUS_E_TRACK_NO_CLOCKTIME_SUPPORT"; break;
	case DMUS_E_TRACK_NOT_FOUND:
		pmsg = "DMUS_E_TRACK_NOT_FOUND"; break;
	case DMUS_E_TYPE_DISABLED:
		pmsg = "DMUS_E_TYPE_DISABLED"; break;
	case DMUS_E_TYPE_UNSUPPORTED:
		pmsg = "DMUS_E_TYPE_UNSUPPORTED"; break;
	case DMUS_E_UNKNOWN_PROPERTY:
		pmsg = "DMUS_E_UNKNOWN_PROPERTY"; break;
	case DMUS_E_UNKNOWNDOWNLOAD:
		pmsg = "DMUS_E_UNKNOWNDOWNLOAD"; break;
	case DMUS_E_UNSUPPORTED_STREAM:
		pmsg = "DMUS_E_UNSUPPORTED_STREAM"; break;
	case DMUS_E_WAVEFORMATNOTSUPPORTED:
		pmsg = "DMUS_E_WAVEFORMATNOTSUPPORTED"; break;
	case DMUS_S_DOWN_OCTAVE:
		pmsg = "DMUS_S_DOWN_OCTAVE"; break;
	case DMUS_S_END:
		pmsg = "DMUS_S_END"; break;
	case DMUS_S_FREE:
		pmsg = "DMUS_S_FREE"; break;
	case DMUS_S_GARBAGE_COLLECTED:
		pmsg = "DMUS_S_GARBAGE_COLLECTED"; break;
	case DMUS_S_LAST_TOOL:
		pmsg = "DMUS_S_LAST_TOOL"; break;
	case DMUS_S_NOBUFFERCONTROL:
		pmsg = "DMUS_S_NOBUFFERCONTROL"; break;
	case DMUS_S_OVER_CHORD:
		pmsg = "DMUS_S_OVER_CHORD"; break;
	case DMUS_S_PARTIALDOWNLOAD:
		pmsg = "DMUS_S_PARTIALDOWNLOAD"; break;
	case DMUS_S_PARTIALLOAD:
		pmsg = "DMUS_S_PARTIALLOAD"; break;
	case DMUS_S_REQUEUE:
		pmsg = "DMUS_S_REQUEUE"; break;
	case DMUS_S_STRING_TRUNCATED:
		pmsg = "DMUS_S_STRING_TRUNCATED"; break;
	case DMUS_S_UP_OCTAVE:
		pmsg = "DMUS_S_UP_OCTAVE"; break;
	case E_FAIL:
		pmsg = "E_FAIL"; break;
	case E_INVALIDARG:
		pmsg = "E_INVALIDARG"; break;
	case E_NOINTERFACE:
		pmsg = "E_NOINTERFACE"; break;
	case E_NOTIMPL:
		pmsg = "E_NOTIMPL"; break;
	case E_OUTOFMEMORY:
		pmsg = "E_OUTOFMEMORY"; break;
	case E_POINTER:
		pmsg = "E_POINTER"; break;
	case REGDB_E_CLASSNOTREG:
		pmsg = "REGDB_E_CLASSNOTREG"; break;
	case S_FALSE:
		pmsg = "S_FALSE"; break;
	case S_OK:
		pmsg = "S_OK"; break;
	default:
		//_ASSERT(0);
		pmsg = "unknown dsound error result"; break;
	}
	return strcpy(pbuffer, pmsg);
}

T3DLIB_API bool Create_DMPerformance(DSOUNDV1 * dsound, DMPERFORMANCEV1 * pdmperf, const HWND hwnd)
{
	IDirectMusicPerformance * lpdmperf = NULL;
	if(FAILED(CoInitialize(NULL)))
		ON_ERROR_GOTO("initialize com failed");

	if(FAILED(CoCreateInstance(CLSID_DirectMusicPerformance,
			NULL, CLSCTX_INPROC, IID_IDirectMusicPerformance, (LPVOID *)&lpdmperf)))
		ON_ERROR_GOTO("create dmusic performance failed");

	if(FAILED(gresult = lpdmperf->Init(NULL, dsound->lpdsound, hwnd)))
		ON_ERROR_GOTO(GET_DMUSIC_ERROR(gresult));

	if(FAILED(gresult = lpdmperf->AddPort(NULL)))
		ON_ERROR_GOTO(GET_DMUSIC_ERROR(gresult));

	pdmperf->lpdmperf = lpdmperf;
	return true;

ON_ERROR:
	SAFE_RELEASE(lpdmperf);
	return false;
}

T3DLIB_API bool Create_DMLoader(DMLOADERV1 * pdmloader)
{
	IDirectMusicLoader * lpdmloader = NULL;
	if(FAILED(CoCreateInstance(CLSID_DirectMusicLoader,
			NULL, CLSCTX_INPROC, IID_IDirectMusicLoader, (LPVOID *)&lpdmloader)))
		ON_ERROR_GOTO("create dmusic loader failed");

	pdmloader->lpdmloader = lpdmloader;
	return true;

ON_ERROR:
	SAFE_RELEASE(lpdmloader);
	return false;
}

T3DLIB_API bool Create_DMSegment_From_Midi_File(	DMLOADERV1 * pdmloader,
													DMSEGMENTV1 * pdmseg,
													const char * fname,
													DMPERFORMANCEV1 * pdmperf)
{
	IDirectMusicSegment * lpdmsegment = NULL;
	WCHAR wkdir[MAX_PATH];
	GetCurrentDirectoryW(MAX_PATH, wkdir);
	if(FAILED(gresult = pdmloader->lpdmloader->SetSearchDirectory(
			GUID_DirectMusicAllTypes, wkdir, FALSE)))
		ON_ERROR_GOTO(GET_DMUSIC_ERROR(gresult));

	DMUS_OBJECTDESC dmod;
	memset(&dmod, 0, sizeof(dmod));
	dmod.dwSize			= sizeof(dmod);
	dmod.dwValidData	= DMUS_OBJ_CLASS | DMUS_OBJ_FILENAME;
	dmod.guidClass		= CLSID_DirectMusicSegment;
	if(0 == MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED,
			fname, -1, dmod.wszFileName, sizeof(dmod.wszFileName) / sizeof(WCHAR)))
		ON_ERROR_GOTO("MultiByteToWideChar failed");

	if(FAILED(gresult = pdmloader->lpdmloader->GetObject(
			&dmod, IID_IDirectMusicSegment, (LPVOID *)&lpdmsegment)))
		ON_ERROR_GOTO(GET_DMUSIC_ERROR(gresult));

	if(FAILED(gresult = lpdmsegment->SetParam(GUID_StandardMIDIFile,
			0xFFFFFFFF, 0, 0, (void *)pdmperf->lpdmperf)))
		ON_ERROR_GOTO(GET_DMUSIC_ERROR(gresult));

	if(FAILED(gresult = lpdmsegment->SetParam(GUID_Download,
			0xFFFFFFFF, 0, 0, (void *)pdmperf->lpdmperf)))
		ON_ERROR_GOTO(GET_DMUSIC_ERROR(gresult));

	pdmseg->lpdmsegment			= lpdmsegment;
	pdmseg->lpdmsegment_state	= NULL;
	pdmseg->pdmperf				= pdmperf;
	return true;

ON_ERROR:
	SAFE_RELEASE(lpdmsegment);
	return false;
}

T3DLIB_API void Destroy_DMPerformance(DMPERFORMANCEV1 * pdmperf)
{
	if(pdmperf->lpdmperf != NULL)
	{
		pdmperf->lpdmperf->Stop(NULL, NULL, 0, 0);
	}
	SAFE_RELEASE(pdmperf->lpdmperf);
}

T3DLIB_API void Destroy_DMLoader(DMLOADERV1 * pdmloader)
{
	SAFE_RELEASE(pdmloader->lpdmloader);
}

T3DLIB_API void Destroy_DMSegment(DMSEGMENTV1 * pdmseg)
{
	if(pdmseg->lpdmsegment != NULL)
	{
		assert(pdmseg->pdmperf->lpdmperf != NULL);
		pdmseg->lpdmsegment->SetParam(GUID_Unload,
			0xFFFFFFFF, 0, 0, (void *)pdmseg->pdmperf->lpdmperf);
	}
	SAFE_RELEASE(pdmseg->lpdmsegment);
}

T3DLIB_API bool Play_DMSegment(DMPERFORMANCEV1 * pdmperf, DMSEGMENTV1 * pdmseg)
{
	Stop_DMSegment(pdmperf, pdmseg);
	if(FAILED(gresult = pdmperf->lpdmperf->PlaySegment(
			pdmseg->lpdmsegment, 0, 0, &pdmseg->lpdmsegment_state)))
		ON_ERROR_GOTO(GET_DMUSIC_ERROR(gresult));
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Stop_DMSegment(DMPERFORMANCEV1 * pdmperf, DMSEGMENTV1 * pdmseg)
{
	if(FAILED(gresult = pdmperf->lpdmperf->Stop(pdmseg->lpdmsegment, NULL, 0, 0)))
		ON_ERROR_GOTO(GET_DMUSIC_ERROR(gresult));
	return true;

ON_ERROR:
	return false;
}

T3DLIB_API bool Get_DMSegment_Status(DMPERFORMANCEV1 * pdmperf, DMSEGMENTV1 * pdmseg, int * pstatus)
{
	if(FAILED(gresult = pdmperf->lpdmperf->IsPlaying(pdmseg->lpdmsegment, pdmseg->lpdmsegment_state)))
		*pstatus = DMSAGMENT_STATUS_PLAYING;
	else
		*pstatus = DMSAGMENT_STATUS_STOPPED;

	return true;
}
