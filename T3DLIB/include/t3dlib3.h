/*
 * File: T3DLIB/t3dlib3.h
 */

#ifndef __T3DLIB3_H__
#define __T3DLIB3_H__

#include "t3dcommons.h"

#define DSBUFFER_STATUS_STOPPED		0
#define DSBUFFER_STATUS_PLAYING		1

typedef struct T3DLIB_API WAVV1_TYP
{
	HMMIO			hwav;
	MMCKINFO		parent;
	MMCKINFO		child;
	WAVEFORMATEX	wavfmt;
	unsigned char *	pbuffer;

	_CTOR_DECLARE(WAVV1_TYP);
	_DTOR_DECLARE(WAVV1_TYP);

} WAVV1, * WAVV1_PTR;

typedef struct T3DLIB_API DSOUNDV1_TYP
{
	LPDIRECTSOUND8 lpdsound;

	_CTOR_DECLARE(DSOUNDV1_TYP);
	_DTOR_DECLARE(DSOUNDV1_TYP);

} DSOUNDV1, * DSOUNDV1_PTR;

typedef struct T3DLIB_API DSBUFFERV1_TYP
{
	LPDIRECTSOUNDBUFFER		lpdsbuffer;
	WAVEFORMATEX			wavfmt;

	_CTOR_DECLARE(DSBUFFERV1_TYP);
	_DTOR_DECLARE(DSBUFFERV1_TYP);

} DSBUFFERV1, * DSBUFFERV1_PTR;

T3DLIB_API char * Get_DSound_Error(char * pbuffer, const HRESULT hresult);

T3DLIB_API bool Create_DSound(DSOUNDV1 * pdsound, const HWND hwnd);

T3DLIB_API bool Create_Wav_From_File(WAVV1 * pwav, char * fname);

T3DLIB_API bool Create_DSBuffer_From_Wav(	DSOUNDV1 * pdsound,
											DSBUFFERV1 * pdsbuffer,
											const WAVV1 * pwav,
											const int flags					= DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME,
											const unsigned short channels	= 1,
											const unsigned int sps			= 11025);

T3DLIB_API void Destroy_DSound(DSOUNDV1 * pdsound);

T3DLIB_API void Destroy_Wav(WAVV1 * pwav);

T3DLIB_API void Destroy_DSBuffer(DSBUFFERV1 * pdsbuffer);

//T3DLIB_API bool Load_DSBuffer_From_Wav_File(DSBUFFERV1 * pdsbuffer, const char * fname);

//T3DLIB_API bool Load_DSBuffer_From_Mp3_File(DSBUFFERV1 * pdsbuffer, const char * fname);

T3DLIB_API bool Play_DSBuffer(DSBUFFERV1 * pdsbuffer, const int flags = 0);

T3DLIB_API bool Stop_DSBuffer(DSBUFFERV1 * pdsbuffer);

T3DLIB_API bool Get_DSBuffer_Status(DSBUFFERV1 * pdsbuffer, int * pstatus);

T3DLIB_API bool Set_DSBuffer_Volume(DSBUFFERV1 * pdsbuffer, const long volume);

T3DLIB_API bool Set_DSBuffer_Frequency(DSBUFFERV1 * pdsbuffer, const unsigned int frequency);

T3DLIB_API bool Set_DSBuffer_Pan(DSBUFFERV1 * pdsbuffer, const long pan);

#define DMSAGMENT_STATUS_STOPPED	0
#define DMSAGMENT_STATUS_PLAYING	1

typedef struct T3DLIB_API DMPERFORMANCEV1_TYP
{
	IDirectMusicPerformance *	lpdmperf;

	DMPERFORMANCEV1_TYP();
	~DMPERFORMANCEV1_TYP();

} DMPERFORMANCEV1, * DMPERFORMANCEV1_PTR;

typedef struct T3DLIB_API DMLOADERV1_TYP
{
	IDirectMusicLoader *		lpdmloader;

	DMLOADERV1_TYP();
	~DMLOADERV1_TYP();

} DMLOADERV1, * DMLOADERV1_PTR;

typedef struct T3DLIB_API DMSEGMENTV1_TYP
{
	IDirectMusicSegment *		lpdmsegment;
	IDirectMusicSegmentState *	lpdmsegment_state;
	DMPERFORMANCEV1_PTR			pdmperf;

	DMSEGMENTV1_TYP();
	~DMSEGMENTV1_TYP();

} DMSEGMENTV1, * DMSEGMENTV1_PTR;

T3DLIB_API char * Get_DMusic_Error(char * pbuffer, const HRESULT hresult);

T3DLIB_API bool Create_DMPerformance(DSOUNDV1 * dsound, DMPERFORMANCEV1 * pdmperf, const HWND hwnd);

T3DLIB_API bool Create_DMLoader(DMLOADERV1 * pdmloader);

T3DLIB_API bool Create_DMSegment_From_Midi_File(	DMLOADERV1 * pdmloader,
													DMSEGMENTV1 * pdmseg,
													const char * fname,
													DMPERFORMANCEV1 * pdmperf);

T3DLIB_API void Destroy_DMPerformance(DMPERFORMANCEV1 * pdmperf);

T3DLIB_API void Destroy_DMLoader(DMLOADERV1 * pdmloader);

T3DLIB_API void Destroy_DMSegment(DMSEGMENTV1 * pdmseg);

T3DLIB_API bool Play_DMSegment(DMPERFORMANCEV1 * pdmperf, DMSEGMENTV1 * pdmseg);

T3DLIB_API bool Stop_DMSegment(DMPERFORMANCEV1 * pdmperf, DMSEGMENTV1 * pdmseg);

T3DLIB_API bool Get_DMSegment_Status(DMPERFORMANCEV1 * pdmperf, DMSEGMENTV1 * pdmseg, int * pstatus);

#endif // __T3DLIB3_H__
