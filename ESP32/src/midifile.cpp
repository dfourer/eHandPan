/*
 * midiFile.c - A general purpose midi file handling library. This code
 *				can read and write MIDI files in formats 0 and 1.
 * Version 1.4
 *
 *  AUTHOR: Steven Goodwin (StevenGoodwin@gmail.com)
 *          Copyright 1998-2010, Steven Goodwin
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

// #  include <endian.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "midifile.h"
#include "tools.h"


bool muGetKeySigName(char *pName, tMIDI_KEYSIG iKey)
{
	static const char *iKeysList[2][8] = {
	/*#*/{"C ", "G ", "D ", "A ", "E ", "B ", "F#", "C#", },
	/*b*/{"C ", "F ", "Bb", "Eb", "Ab", "Db", "Gb", "Cb", },
	};

	int iRootNum = (iKey&7);
	int iFlats = (iKey&keyMaskNeg);
	int iMin = (iKey&keyMaskMin);

	strcpy(pName,iKeysList[iFlats?1:0][iRootNum]);
	strcat(pName,iMin?" Min":" Maj");
	return true;
}


static bool _midiValidateTrack(const _MIDI_FILE *pMF, int iTrack)
{
	if (!IsFilePtrValid(pMF))	return false;
	
	if (!pMF->ptr)
		return false;
	
	if (iTrack < 0 || iTrack>=pMF->Header.iNumTracks)
		return false;

	return true;
}

#ifdef OLD
int	midiFileGetTracksDefaultChannel(const MIDI_FILE *_pMF, int iTrack)
{
	_VAR_CAST;
	if (!IsFilePtrValid(pMF))				return 0;
	if (!IsTrackValid(iTrack))				return 0;

	return pMF->Track[iTrack].iDefaultChannel+1;
}
#endif


int	midiFileGetPPQN(const MIDI_FILE *_pMF)
{
	_VAR_CAST;
	if (!IsFilePtrValid(pMF))				return MIDI_PPQN_DEFAULT;
	return (int)pMF->Header.PPQN;
}


int	midiFileGetVersion(const MIDI_FILE *_pMF)
{
	_VAR_CAST;
	if (!IsFilePtrValid(pMF))				return MIDI_VERSION_DEFAULT;
	return pMF->Header.iVersion;
}


//------------------------------------------------------------------------------------------------------------------------
/// @brief Open a MIDI FILE stored in memory. initialize the context in a MIDI_FILE record 
/// @param mem       Input DATA : MIDI file
/// @param memSize   Size of input data
/// @return 		MIDI_FILE record
MIDI_FILE  * midiMemOpen(const BYTE * mem, size_t memSize)
{
	_MIDI_FILE *pMF = NULL;
	const BYTE *ptr;
	bool bValidFile=false;

	DEBUG2("midiMemOpen...",memSize);
	if ( ! (pMF = (_MIDI_FILE *)malloc(sizeof(_MIDI_FILE))) ) {
		DEBUG1("Cannot create _MIDI_FILE");
		return NULL;
	}
	pMF->ptr = mem;

	/* Is this a valid MIDI file ? */
	ptr = pMF->ptr;
	if (*(ptr+0) == 'M' && *(ptr+1) == 'T' && 
		*(ptr+2) == 'h' && *(ptr+3) == 'd')	{
		DWORD dwData;
		WORD wData;
		int i;

		dwData = *((DWORD *)(ptr+4));
		pMF->Header.iHeaderSize = SWAP_DWORD(dwData);
		
		wData = *((WORD *)(ptr+8));
		pMF->Header.iVersion = (WORD)SWAP_WORD(wData);
		
		wData = *((WORD *)(ptr+10));
		pMF->Header.iNumTracks = (WORD)SWAP_WORD(wData);
		pMF->Header.iNumTracks = min((int)pMF->Header.iNumTracks,MAX_MIDI_TRACKS); // Limit nb of tracks
		
		wData = *((WORD *)(ptr+12));
		pMF->Header.PPQN = (WORD)SWAP_WORD(wData);
		
		ptr += pMF->Header.iHeaderSize+8;
		/*
		**	 Get all tracks
		*/
		for (i=0; i<MAX_MIDI_TRACKS; ++i) {
			pMF->Track[i].pos = 0;
//			pMF->Track[i].last_status = 0;
		}
		
		for (i=0; i<pMF->Header.iNumTracks; ++i) {
//DEBUG2("  track",i);
			pMF->Track[i].pBase = ptr;
			pMF->Track[i].ptr = ptr+8;
//DEBUG2("  ptr",sizeof(pMF->Track[i].ptr));
			dwData = *((DWORD *)(ptr+4));
			pMF->Track[i].sz = SWAP_DWORD(dwData);
			pMF->Track[i].pEnd = ptr+pMF->Track[i].sz+8;
//DEBUG2("  sz",pMF->Track[i].sz);
			ptr += pMF->Track[i].sz+8;
		}
				
		bValidFile = true;
	}
	
	if (!bValidFile) {
		if (pMF)		free((void *)pMF);
		return NULL;
	}
	
	return (MIDI_FILE *)pMF;
}


typedef struct 
{
	int	iIdx;
	int	iEndPos;
} MIDI_END_POINT;


static int qs_cmp_pEndPoints(const void *e1, const void *e2)
{
	MIDI_END_POINT *p1 = (MIDI_END_POINT *)e1;
	MIDI_END_POINT *p2 = (MIDI_END_POINT *)e2;

	return p1->iEndPos-p2->iEndPos;
}



bool  midiFileClose(MIDI_FILE *_pMF)
{
	_VAR_CAST;
	if (!IsFilePtrValid(pMF))			return false;

	free((void *)pMF);
	return true;
}



int midiTrackGetEndPos(MIDI_FILE *_pMF, int iTrack)
{
	_VAR_CAST;
	if (!IsFilePtrValid(pMF))				return 0;
	if (!IsTrackValid(iTrack))				return 0;

	return pMF->Track[iTrack].pos;
}


//------------------------------------------------------------------------------------------------------------------------
/// @brief Read a MIDI value at the pointer <ptr> according to size
/// @param ptr Pointer to value to read
/// @param num Pointer to read value
/// @return pointer to next val
const BYTE *_midiReadVarLen(const BYTE *ptr, DWORD *num)
{
//register DWORD value;
//register BYTE c;
	DWORD value;
	BYTE c;

    if ((value = *ptr++) & 0x80) {
		value &= 0x7f;
		do	{
			value = (value << 7) + ((c = *ptr++) & 0x7f);
		} while (c & 0x80);
	} 
	*num = value;
	return(ptr);
}


//------------------------------------------------------------------------------------------------------------------------
/// @brief Copy data to message (if <bCopyPtrData> is true)
/// @param pMsg 
/// @param ptr 
/// @param sz 
/// @param bCopyPtrData 
/// @return 
static bool _midiReadTrackCopyData(MIDI_MSG *pMsg, BYTE *ptr, DWORD sz, bool bCopyPtrData)
{
	if (sz > pMsg->data_sz)	{
		pMsg->data = (BYTE *)realloc(pMsg->data, sz);
		pMsg->data_sz = sz;
	}
	
	if (!pMsg->data)
		return false;
	
	if (bCopyPtrData && ptr)
		memcpy(pMsg->data, ptr, sz);
	
	return true;
}

//------------------------------------------------------------------------------------------------------------------------
/// @brief Get number of tracks
/// @param _pMF MIDI file structure
/// @return number of tracks
int midiReadGetNumTracks(const MIDI_FILE *_pMF)
{
	_VAR_CAST;
	return pMF->Header.iNumTracks;
}

//------------------------------------------------------------------------------------------------------------------------
/// @brief Get and parse next MIDI message of a track
/// @param _pMF    Pointer to a MIDI file
/// @param iTrack  track
/// @param pMsg    Pointer to an existing MIDI_MSG record
/// @return 
bool midiReadGetNextMessage(const MIDI_FILE *_pMF, int iTrack, MIDI_MSG *pMsg)
{
	MIDI_FILE_TRACK *pTrack;
	const BYTE *bptr; 
	const BYTE *pMsgDataPtr;
	int sz;

	_VAR_CAST;
	if (!IsTrackValid(iTrack))			return false;
	
	pTrack = &pMF->Track[iTrack];
	/* FIXME: Check if there is data on this track first!!!	*/
	if (pTrack->ptr >= pTrack->pEnd)
		return false;

	// Get delta time
	pTrack->ptr = _midiReadVarLen(pTrack->ptr, &pMsg->dt);

	// Compute position
	pTrack->pos += pMsg->dt;

	// Compute absolute position
	pMsg->dwAbsPos = pTrack->pos;

	/* Is this is sys message */
	if (*pTrack->ptr & 0x80) {
		pMsg->iType = (tMIDI_MSG)((*pTrack->ptr) & 0xf0);
		pMsgDataPtr = pTrack->ptr+1;

		/* SysEx & Meta events don't carry channel info, but something
		** important in their lower bits that we must keep */
		if (pMsg->iType == 0xf0)
			pMsg->iType = (tMIDI_MSG)(*pTrack->ptr);
	} else {						/* just data - so use the last msg type */
		pMsg->iType = pMsg->iLastMsgType;
		pMsgDataPtr = pTrack->ptr;
	}
	
	pMsg->iLastMsgType = (tMIDI_MSG)pMsg->iType;
	pMsg->iLastMsgChnl = (BYTE)((*pTrack->ptr) & 0x0f)+1;

	switch(pMsg->iType) {
		case	msgNoteOn:
			pMsg->MsgData.NoteOn.iChannel = pMsg->iLastMsgChnl;
			pMsg->MsgData.NoteOn.iNote = *(pMsgDataPtr);
			pMsg->MsgData.NoteOn.iVolume = *(pMsgDataPtr+1);
			pMsg->iMsgSize = 3;
			break;

		case	msgNoteOff:
			pMsg->MsgData.NoteOff.iChannel = pMsg->iLastMsgChnl;
			pMsg->MsgData.NoteOff.iNote = *(pMsgDataPtr);
			pMsg->iMsgSize = 3;
			break;

		case	msgNoteKeyPressure:
			pMsg->MsgData.NoteKeyPressure.iChannel = pMsg->iLastMsgChnl;
			pMsg->MsgData.NoteKeyPressure.iNote = *(pMsgDataPtr);
			pMsg->MsgData.NoteKeyPressure.iPressure = *(pMsgDataPtr+1);
			pMsg->iMsgSize = 3;
			break;

		case	msgSetParameter:
			pMsg->MsgData.NoteParameter.iChannel = pMsg->iLastMsgChnl;
			pMsg->MsgData.NoteParameter.iControl = (tMIDI_CC)*(pMsgDataPtr);
			pMsg->MsgData.NoteParameter.iParam = *(pMsgDataPtr+1);
			pMsg->iMsgSize = 3;
			break;

		case	msgSetProgram:
			pMsg->MsgData.ChangeProgram.iChannel = pMsg->iLastMsgChnl;
			pMsg->MsgData.ChangeProgram.iProgram = *(pMsgDataPtr);
			pMsg->iMsgSize = 2;
			break;

		case	msgChangePressure:
			pMsg->MsgData.ChangePressure.iChannel = pMsg->iLastMsgChnl;
			pMsg->MsgData.ChangePressure.iPressure = *(pMsgDataPtr);
			pMsg->iMsgSize = 2;
			break;

		case	msgSetPitchWheel:
			pMsg->MsgData.PitchWheel.iChannel = pMsg->iLastMsgChnl;
			pMsg->MsgData.PitchWheel.iPitch = *(pMsgDataPtr) | (*(pMsgDataPtr+1) << 7);
			pMsg->MsgData.PitchWheel.iPitch -= MIDI_WHEEL_CENTRE;
			pMsg->iMsgSize = 3;
			break;

		case	msgMetaEvent:
			/* We can use 'pTrack->ptr' from now on, since meta events
			** always have bit 7 set */
			bptr = pTrack->ptr;
			pMsg->MsgData.MetaEvent.iType = (tMIDI_META)*(pTrack->ptr+1);
			pTrack->ptr = _midiReadVarLen(pTrack->ptr+2, &pMsg->iMsgSize);
			sz = (pTrack->ptr-bptr)+pMsg->iMsgSize;
//			if (_midiReadTrackCopyData(pMsg, pTrack->ptr, sz, false) == false)
//				return false;

			/* Now copy the data...*/
//			memcpy(pMsg->data, bptr, sz);

			/* Now place it in a neat structure */
			switch(pMsg->MsgData.MetaEvent.iType) {
				case	metaMIDIPort:
					pMsg->MsgData.MetaEvent.Data.iMIDIPort = *(pTrack->ptr+0);
					break;
				case	metaSequenceNumber:
					pMsg->MsgData.MetaEvent.Data.iSequenceNumber = *(pTrack->ptr+0);
					break;
				case	metaTextEvent:
				case	metaCopyright:
				case	metaTrackName:
				case	metaInstrument:
				case	metaLyric:
				case	metaMarker:
				case	metaCuePoint:
						/* TODO - Add NULL terminator ??? */
					pMsg->MsgData.MetaEvent.Data.Text.pData = pTrack->ptr;
					break;
				case	metaEndSequence:
						/* NO DATA */
						break;
				case	metaSetTempo:
					{
					DWORD us = ((*(pTrack->ptr+0))<<16)|((*(pTrack->ptr+1))<<8)|(*(pTrack->ptr+2));
					pMsg->MsgData.MetaEvent.Data.Tempo.iBPM = 60000000L/us;
					}
					break;
				case	metaSMPTEOffset:
					pMsg->MsgData.MetaEvent.Data.SMPTE.iHours = *(pTrack->ptr+0);
					pMsg->MsgData.MetaEvent.Data.SMPTE.iMins= *(pTrack->ptr+1);
					pMsg->MsgData.MetaEvent.Data.SMPTE.iSecs = *(pTrack->ptr+2);
					pMsg->MsgData.MetaEvent.Data.SMPTE.iFrames = *(pTrack->ptr+3);
					pMsg->MsgData.MetaEvent.Data.SMPTE.iFF = *(pTrack->ptr+4);
					break;
				case	metaTimeSig:
					pMsg->MsgData.MetaEvent.Data.TimeSig.iNom = *(pTrack->ptr+0);
					pMsg->MsgData.MetaEvent.Data.TimeSig.iDenom = *(pTrack->ptr+1) * MIDI_NOTE_MINIM;
					/* TODO: Variations without 24 & 8 */
					break;
				case	metaKeySig:
					if (*pTrack->ptr & 0x80)
						{
						/* Do some trendy sign extending in reverse :) */
						pMsg->MsgData.MetaEvent.Data.KeySig.iKey =  (tMIDI_KEYSIG) ((256-*pTrack->ptr)&keyMaskKey);
						pMsg->MsgData.MetaEvent.Data.KeySig.iKey = (tMIDI_KEYSIG) (pMsg->MsgData.MetaEvent.Data.KeySig.iKey | keyMaskNeg );
						}
					else
						{
						pMsg->MsgData.MetaEvent.Data.KeySig.iKey = (tMIDI_KEYSIG)(*pTrack->ptr&keyMaskKey);
						}
					if (*(pTrack->ptr+1)) 
						pMsg->MsgData.MetaEvent.Data.KeySig.iKey = (tMIDI_KEYSIG) (pMsg->MsgData.MetaEvent.Data.KeySig.iKey | keyMaskMin);
					break;
				case	metaSequencerSpecific:
					pMsg->MsgData.MetaEvent.Data.Sequencer.iSize = pMsg->iMsgSize;
					pMsg->MsgData.MetaEvent.Data.Sequencer.pData = pTrack->ptr;
					break;
			}

			pTrack->ptr += pMsg->iMsgSize;
			pMsg->iMsgSize = sz;
			break;

		case	msgSysEx1:
		case	msgSysEx2:
			bptr = pTrack->ptr;
			pTrack->ptr = _midiReadVarLen(pTrack->ptr+1, &pMsg->iMsgSize);
			sz = (pTrack->ptr-bptr)+pMsg->iMsgSize;
DEBUG1("MALLOC msgSysEx2");
//			if (_midiReadTrackCopyData(pMsg, pTrack->ptr, sz, false) == false)
//				return false;

			/* Now copy the data... */
			memcpy(pMsg->data, bptr, sz);
			pTrack->ptr += pMsg->iMsgSize;
			pMsg->iMsgSize = sz;
			pMsg->MsgData.SysEx.pData = pMsg->data;
			pMsg->MsgData.SysEx.iSize = sz;
			break;
	}
	/*
	** Standard MIDI messages use a common copy routine
	*/
	pMsg->bImpliedMsg = false;
	if ((pMsg->iType&0xf0) != 0xf0)	{
		if (*pTrack->ptr & 0x80) {
		} else 	{
			pMsg->bImpliedMsg = true;
			pMsg->iImpliedMsg = pMsg->iLastMsgType;
			pMsg->iMsgSize--;
		}
//		_midiReadTrackCopyData(pMsg, pTrack->ptr, pMsg->iMsgSize, true);
		pTrack->ptr+=pMsg->iMsgSize;
	}
	return true;
}

//------------------------------------------------------------------------------------------------------------------------
/// @brief Initialise a MIDI_MSG record
/// @param pMsg MIDI record to initialise
void midiReadInitMessage(MIDI_MSG *pMsg)
{
	pMsg->data = NULL;
	pMsg->data_sz = 0;
	pMsg->bImpliedMsg = false;
}

//------------------------------------------------------------------------------------------------------------------------
/// @brief Free memoru 
/// @param pMsg MIDI record to free memory
void midiReadFreeMessage(MIDI_MSG *pMsg)
{
	if (pMsg->data)	free((void *)pMsg->data);
	//pMsg->data = NULL;
	midiReadInitMessage(pMsg);
}



//------------------------------------------------------------------------------------------------------------------------
/// @brief 
/// @param command noteOn / noteOff
/// @param MIDInote 0 - 127
/// @param MIDIvelocity 0 - 127
/// @param channel 1:16
// void midiMessage(int command, int MIDInote, int MIDIvelocity, int channel=1) {
//   Serial.write(command+(channel-1));//send note on or note off command 
//   Serial.write(MIDInote);//send pitch data
//   Serial.write(MIDIvelocity);//send velocity data
// }