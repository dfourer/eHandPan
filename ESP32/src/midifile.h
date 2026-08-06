#pragma once

#include <stdint.h>
#include "midiinfo.h"		/* enumerations and constants for GM */

/*
 * midiFile.c -  Header file for Steevs MIDI Library
 * Version 1.4
 *
 *  AUTHOR: Steven Goodwin (StevenGoodwin@gmail.com)
 *			Copyright 1998-2010, Steven Goodwin.
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation; either version 2 of
 *  the License,or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/* 
** All functions start with one of the following prefixes:
**		midiFile*		For non-GM features that relate to the file, and have
**						no use once the file has been created, i.e. CreateFile
**						or SetTrack (those data is embedded into the file, but
**						not explicitly stored)
**		midiSong*		For operations that work across the song, i.e. SetTempo
**		midiTrack*		For operations on a specific track, i.e. AddNoteOn
*/

/*
** Types because we're dealing with files, and need to be careful
*/
typedef	unsigned char	BYTE;
typedef	uint16_t 		WORD;
typedef	uint32_t 		DWORD;

/*
typedef int				BOOL;
#ifndef TRUE
#define TRUE	1
#endif
#ifndef FALSE
#define FALSE	0
#endif
*/

/*
** MIDI Constants
*/
#define MIDI_PPQN_DEFAULT		384
#define MIDI_VERSION_DEFAULT	1

/*
** MIDI Limits
*/
#define MAX_MIDI_TRACKS			10 // 256

/*
** MIDI structures, accessibly externably
*/
typedef	void 	MIDI_FILE;
typedef struct 
{
	tMIDI_MSG	iType;

	DWORD		dt;		/* delta time */
	DWORD		dwAbsPos;
	DWORD		iMsgSize;

	bool		bImpliedMsg;
	tMIDI_MSG	iImpliedMsg;

	/* Raw data chunk */
	BYTE *data;		/* dynamic data block */
	DWORD data_sz;
	
	union {
		struct {
				int			iNote;
				int			iChannel;
				int			iVolume;
				} NoteOn;
		struct {
				int			iNote;
				int			iChannel;
				} NoteOff;
		struct {
				int			iNote;
				int			iChannel;
				int			iPressure;
				} NoteKeyPressure;
		struct {
				int			iChannel;
				tMIDI_CC	iControl;
				int			iParam;
				} NoteParameter;
		struct {
				int			iChannel;
				int			iProgram;
				} ChangeProgram;
		struct {
				int			iChannel;
				int			iPressure;
				} ChangePressure;
		struct {
				int			iChannel;
				int			iPitch;
				} PitchWheel;
		struct {
				tMIDI_META	iType;
				union {
					int					iMIDIPort;
					int					iSequenceNumber;
					struct {
						const BYTE			*pData;
						} Text;
					struct {
						int				iBPM;
						} Tempo;
					struct {
						int				iHours, iMins;
						int				iSecs, iFrames,iFF;
						} SMPTE;
					struct {
						tMIDI_KEYSIG	iKey;
						} KeySig;
					struct {
						int				iNom, iDenom;
						} TimeSig;
					struct {
						const BYTE			*pData;
						int				iSize;
						} Sequencer;
					} Data;
				} MetaEvent;
		struct {
				BYTE		*pData;
				int			iSize;
				} SysEx;
		} MsgData;

	/* State information - Please treat these as private*/
	tMIDI_MSG	iLastMsgType;
	BYTE		iLastMsgChnl;
} MIDI_MSG;



/*
** Internal Data Structures
*/
typedef struct 	
{
	BYTE note, chn;
	BYTE valid, p2;
	DWORD end_pos;
} MIDI_LAST_NOTE;

typedef struct 	
{
	const BYTE *ptr;
	const BYTE *pBase;
	const BYTE *pEnd;

	DWORD pos;
	DWORD dt;
	/* For Reading MIDI Files */
	DWORD sz;						/* size of whole iTrack */
	/* For Writing MIDI Files */
//	DWORD iBlockSize;				/* max size of track */
//	BYTE iDefaultChannel;			/* use for write only */
//	BYTE last_status;				/* used for running status */

//	MIDI_LAST_NOTE LastNote[MAX_TRACK_POLYPHONY];
} MIDI_FILE_TRACK;

typedef struct 	
{
	DWORD	iHeaderSize;
	/**/
	WORD	iVersion;		/* 0, 1 or 2 */
	WORD	iNumTracks;		/* number of tracks... (will be 1 for MIDI type 0) */
	WORD	PPQN;			/* pulses per quarter note */
} MIDI_HEADER;

typedef struct 
{
//	FILE				*pFile;
//	bool				bOpenForWriting;
	
	MIDI_HEADER			Header;
	const BYTE *ptr;			/* to whole data block */
	DWORD file_sz;
	
	MIDI_FILE_TRACK		Track[MAX_MIDI_TRACKS];
} _MIDI_FILE;


/*
** Internal Functions
*/

#define DT_DEF				32			/* assume maximum delta-time + msg is no more than 32 bytes */

// #if BYTE_ORDER == BIG_ENDIAN
// #define SWAP_WORD(w)		(w)
// #define SWAP_DWORD(d)	(d)
// #else
#define SWAP_WORD(w)		(WORD)(((w)>>8)|((w)<<8))
#define SWAP_DWORD(d)	(DWORD)((d)>>24)|(((d)>>8)&0xff00)|(((d)<<8)&0xff0000)|(((d)<<24))
// #endif

#define _VAR_CAST				_MIDI_FILE *pMF = (_MIDI_FILE *)_pMF
#define IsFilePtrValid(pMF)		(pMF)
#define IsTrackValid(_x)		(_midiValidateTrack(pMF, _x))
#define IsChannelValid(_x)		((_x)>=1 && (_x)<=16)
#define IsNoteValid(_x)			((_x)>=0 && (_x)<128)
#define IsMessageValid(_x)		((_x)>=msgNoteOff && (_x)<=msgMetaEvent)



bool muGetKeySigName(char *pName, tMIDI_KEYSIG iKey);

/*
** midiFile* Prototypes
*/

int			midiFileGetTracksDefaultChannel(const MIDI_FILE *pMF, int iTrack);
int			midiFileGetPPQN(const MIDI_FILE *pMF);
int			midiFileGetVersion(const MIDI_FILE *pMF);
MIDI_FILE  *midiMemOpen(const BYTE * mem, size_t memSize);
bool		midiFileClose(MIDI_FILE *pMF);

int		midiTrackGetEndPos(MIDI_FILE *pMF, int iTrack);

/*
** midiRead* Prototypes
*/
int			midiReadGetNumTracks(const MIDI_FILE *pMF);
bool		midiReadGetNextMessage(const MIDI_FILE *pMF, int iTrack, MIDI_MSG *pMsg);
void		midiReadInitMessage(MIDI_MSG *pMsg);
void		midiReadFreeMessage(MIDI_MSG *pMsg);

// void midiMessage(int command, int MIDInote, int MIDIvelocity, int channel);
