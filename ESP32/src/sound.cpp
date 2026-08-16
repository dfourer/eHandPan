///=======================================================================================================================
///
/// @file sound.cpp
/// 
/// Body file for sound management:
///   - WAV file
///   - I2S
///   - Song 
// 
/// @author Eric GENOTELLE
/// @date 2024
///
///=======================================================================================================================

#include "driver/i2s.h"                       // Library of I2S routines, comes with ESP32 standard install
#include "tools.h"

#include "config.h"
#include "sound.h"
#include "device.h"
#include "global.h"
#include "wav/clic1.h"
#include "wav/clic2.h"
#include "wav/error.h"

#if defined(BANK1)
  #include "wav/bank1/s00.h"
  #ifndef DEBUG_PRG
    #include "wav/bank1/s01.h"
    #include "wav/bank1/s02.h"
    #include "wav/bank1/s03.h"
    #include "wav/bank1/s04.h"
    #include "wav/bank1/s05.h"
    #include "wav/bank1/s06.h"
    #include "wav/bank1/s07.h"
    #include "wav/bank1/s08.h"
    #include "wav/bank1/s09.h"
    #include "wav/bank1/s10.h"
    #include "wav/bank1/s11.h"
    #include "wav/bank1/s12.h"
    #include "wav/bank1/s13.h"
  #endif
#endif

//------------------------------------------------------------------------------------------------------------------------
/// PRIVATE VARIABLES

/// @brief Chrono number for played note
uint32_t  chronoPoly=0;

/// @brief Table of simultaneous played notes
T_NotePoly notesPoly[NB_NOTES_POLY];

/// @brief indicate actual number of playing notes in table <notesPoly>
int16_t nbPlayingNotes=0;  


//------------------------------------------------------------------------------------------------------------------------
/// @brief  I2S configuration structures
i2s_config_t i2s_config = 
{
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = 22050,                            
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
//    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
//    .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_STAND_I2S ),
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,       // high interrupt priority
//    .intr_alloc_flags = 0,       
    .dma_buf_count = 3,                             // n buffers
    .dma_buf_len = WAV_BUFFER_SIZE*2,               // 1K per buffer,  buffer space = dma_buf_count * dma_buf_len
    .use_apll=0,
    .tx_desc_auto_clear= true, 
    .fixed_mclk=-1    
};


//------------------------------------------------------------------------------------------------------------------------
/// @brief pin_config for I2S
// These are the physical wiring connections to our I2S decoder board/chip from the esp32, there are other connections
// required for the chips mentioned at the top (but not to the ESP32), please visit the page mentioned at the top for
// further information regarding these other connections.
static const i2s_pin_config_t pin_config = 
{
    .bck_io_num = PIN_I2S_BCK,                                 // The bit clock connectiom, goes to pin 27 of ESP32
    .ws_io_num = PIN_I2S_WSK,                                  // Word select, also known sas word select or left right clock
    .data_out_num = PIN_I2S_DATA,                               // Data out from the ESP32, connect to DIN on 38357A
    .data_in_num = I2S_PIN_NO_CHANGE                  // we are not interested in I2S data into the ESP32
};

static const i2s_port_t i2s_num = I2S_NUM_0;  // i2s port number


//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
//     WAVE and NOTES functions
//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------
/// @brief Reference a sound
/// @param idx       Index of the sound in table <SOUND>
/// @param wavData   WAV data
/// @param noteMidi  MIDI note related to this sound
void setupSound(int idx, const int16_t * wavData, size_t waveSize, int noteMidi,const char * noteName, int PINpiezzo, int PINledLeft, int PINledRight) 
{
  sounds[idx].wavBody = wavData ;
  sounds[idx].wavSize = waveSize;
  sounds[idx].noteMidi = noteMidi;
  strcpy(sounds[idx].noteName, noteName);
  sounds[idx].PINpiezzo = PINpiezzo;
  sounds[idx].PINledLeft = PINledLeft;
  sounds[idx].PINledRight = PINledRight;
  sounds[idx].ledRightOn = false;
  sounds[idx].ledLeftOn = false;
}

//------------------------------------------------------------------------------------------------------------------------
/// @brief setup I2S and Reference alls sounds
void setupSounds()
{
  int note = NOTE_MIDI_BASE;

  // setup I2S
  DEBUG1("setupSounds I2s...");
  i2s_config.dma_buf_count = conf.I2S_BUFFER_NB;
  i2s_config.dma_buf_len   = conf.I2S_BUFFER_SIZE * 2;  // INT: x2 

  i2s_driver_install(i2s_num, &i2s_config, 0, NULL);        // ESP32 will allocated resources to run I2S
  i2s_set_pin(i2s_num, &pin_config);                        // Tell it the pins you will be using
//  i2s_set_sample_rates( i2s_num, sounds[0].wavHeader.SampleRate );      //set sample rate 

  // setup all sounds
  DEBUG1("setupSounds WAVES...")
  setupSound( 0, s00_wav, sizeof(s00_wav) / 2,   note++, "A2",   0, 0, 1); 
#ifndef JUST1WAV
  setupSound( 1, s01_wav,  sizeof(s01_wav) / 2,  note++, "A#2",  8,16,17);
  setupSound( 2, s02_wav,  sizeof(s02_wav) / 2,  note++, "B2",   1, 2, 3);
  setupSound( 3, s03_wav,  sizeof(s03_wav) / 2,  note++, "C3",   2, 4, 5);
  setupSound( 4, s04_wav,  sizeof(s04_wav) / 2,  note++, "C#3",  9,18,19);
  setupSound( 5, s05_wav,  sizeof(s05_wav) / 2,  note++, "D3",   3, 6, 7);
  setupSound( 6, s06_wav,  sizeof(s06_wav) / 2,  note++, "D#3", 10,20,21);
  setupSound( 7, s07_wav,  sizeof(s07_wav) / 2,  note++, "E3",   4, 8, 9);
  setupSound( 8, s08_wav,  sizeof(s08_wav) / 2,  note++, "F3",   5,10,11);
  setupSound( 9, s09_wav,  sizeof(s09_wav) / 2,  note++, "F#3", 11,22,23);
  setupSound(10, s10_wav,  sizeof(s10_wav) / 2,  note++, "G3",   6,12,13);
  setupSound(11, s11_wav,  sizeof(s11_wav) / 2,  note++, "G#3", 12,24,25);
  setupSound(12, s12_wav,  sizeof(s12_wav) / 2,  note++, "A3",   7,14,15);
  setupSound(13, s13_wav,  sizeof(s13_wav) / 2,  note++, "A#3", 13,26,27);
#else
  setupSound( 1, s00_wav,  sizeof(s00_wav) / 2,  note++, "A#2",  8,16,17);
  setupSound( 2, s00_wav,  sizeof(s00_wav) / 2,  note++, "B2",   1, 2, 3);
  setupSound( 3, s00_wav,  sizeof(s00_wav) / 2,  note++, "C3",   2, 4, 5);
  setupSound( 4, s00_wav,  sizeof(s00_wav) / 2,  note++, "C#3",  9,18,19);
  setupSound( 5, s00_wav,  sizeof(s00_wav) / 2,  note++, "D3",   3, 6, 7);
  setupSound( 6, s00_wav,  sizeof(s00_wav) / 2,  note++, "D#3", 10,20,21);
  setupSound( 7, s00_wav,  sizeof(s00_wav) / 2,  note++, "E3",   4, 8, 9);
  setupSound( 8, s00_wav,  sizeof(s00_wav) / 2,  note++, "F3",   5,10,11);
  setupSound( 9, s00_wav,  sizeof(s00_wav) / 2,  note++, "F#3", 11,22,23);
  setupSound(10, s00_wav,  sizeof(s00_wav) / 2,  note++, "G3",   6,12,13);
  setupSound(11, s00_wav,  sizeof(s00_wav) / 2,  note++, "G#3", 12,24,25);
  setupSound(12, s00_wav,  sizeof(s00_wav) / 2,  note++, "A3",   7,14,15);
  setupSound(13, s00_wav,  sizeof(s00_wav) / 2,  note++, "A#3", 13,26,27);
#endif
  setupSound(14, clic1_wav, sizeof(clic1_wav) / 2,  NOTE_MIDI_CLIC1, "CL1", 14,28,29);  // CLIC : FIRST BEAT OF A MEASURE
  setupSound(15, clic2_wav, sizeof(clic2_wav) / 2,  NOTE_MIDI_CLIC2, "CL2", 15,30,31);  // CLIC : NEXT BEAT OF A MEASURE
  setupSound(16, error_wav, sizeof(error_wav) / 2,  NOTE_MIDI_ERROR, "ERR", 0,0,0);  // ERROR : not exist, ..

}


//------------------------------------------------------------------------------------------------------------------------
/// @brief Retrieve the index of the sound related to a MIDI note 
/// @param note MIDI note
/// @return index of the sound, -1 if not found
int getSoundIndexByNote(int note)
{
  for (int i=0; i<NB_SOUNDS; i++) {
    if ( sounds[i].noteMidi == note ) {
      return i;
    }
  }
  return NOTE_ERROR;
}

//------------------------------------------------------------------------------------------------------------------------
/// @brief Indicate if the sound is a clic or note
/// @param indexSound index of the sounds in table <sounds>
/// @return true=clic, false=real note
bool isSoundClic(int indexSound)
{
  return ( (indexSound == NOTE_CLIC1) || (indexSound == NOTE_CLIC2) );
}

//------------------------------------------------------------------------------------------------------------------------
/// @brief Reset states of a played note
/// @param i Index in table ``notesPoly`` of the note to reset
void resetNotePoly(int i)
{
  notesPoly[i].state = Idle;
  notesPoly[i].pSound = 0;
  notesPoly[i].posWav = 0;
  notesPoly[i].volume = 0.0;
  notesPoly[i].chrono = 0;
  nbPlayingNotes = getNbOfPlayingNotes();
}

//------------------------------------------------------------------------------------------------------------------------
/// @brief reset all notes
void resetAllNotesPoly()
{
  DEBUG1("setupNotesPoly...")
  for (int i=0; i<NB_NOTES_POLY; i++) {
    resetNotePoly(i);
  }
}


//------------------------------------------------------------------------------------------------------------------------
/// @brief  return number of playing notes in  ``notesPoly`` table
/// @return nb of playning notes
//
int getNbOfPlayingNotes()
{
  int ret=0;
  for (int i=0; i<NB_NOTES_POLY; i++) {
    if (notesPoly[i].state == Playing) {
      ret++;
    }
  }
  return ret;
}

//------------------------------------------------------------------------------------------------------------------------
/// @brief retrieve a index in ``notesPoly`` table for the next note to be played
///         setup a chrono for this note
///         if max notes reach, retrieve the oldest note index
/// @return index of ``notesPoly`` for next note to be played
//
int getNotePolyIndexAvailable()
{
  int lastOldIdx = 0;
  uint32_t oldChrono = chronoPoly+1; // recent chrono, to help to find the min

  for (int i=0; i<NB_NOTES_POLY; i++) {
    // this lot is free to be used
    if (notesPoly[i].chrono == 0) {
      chronoPoly++;
      notesPoly[i].chrono = chronoPoly;
      return i;
    } else {
      if (notesPoly[i].chrono < oldChrono) {
        oldChrono = notesPoly[i].chrono;
        lastOldIdx = i;
      }
    }
  }

  // no free available slot : take the oldest
  chronoPoly++;
  notesPoly[lastOldIdx].chrono = chronoPoly;
  return lastOldIdx;
}

//------------------------------------------------------------------------------------------------------------------------
/// @brief Played the note `idxSound`, with the volume <volume>
//
/// @param idxSound Index in table ``sounds`` of the sound to play 
/// @param volume 0 -> 127
/// @return index of played sound , -1 if not found
//
int playSound(int idxSound, int volume)
{
  if ( (idxSound<0) || (idxSound>=NB_SOUNDS) ) {
    DEBUG2("sound not found:",idxSound)
    return -1;
  }
//DEBUG2("** playSound 1;",millis());
DEBUG5("playSound:",sounds[idxSound].noteMidi, sounds[idxSound].noteName, volume,idxSound);
//DEBUG2("** playSound 2;",millis());

  
  // Find a slot in NotePoly table
  int idxNotePoly = getNotePolyIndexAvailable();
  if (idxNotePoly<0) {
    DEBUG1("No available note");
    return -1;
  }
//||  DEBUG2("   slot:",idxNotePoly );
//DEBUG2("** playSound 3;",millis());

  notesPoly[idxNotePoly].volume = volume  ;
  notesPoly[idxNotePoly].pSound = & sounds[idxSound];
  notesPoly[idxNotePoly].posWav = 0; // At the very beggining of the WAV
  notesPoly[idxNotePoly].state = Playing;
  nbPlayingNotes++;

//DEBUG2("** playSound 4;",millis());
  //i2s_zero_dma_buffer(i2s_num);


#ifdef DEATH_CODE
DEBUG2("** playSound LOOP 1;",millis());
  unsigned long t0=millis();
  unsigned long t1=t0;
  unsigned long t2;
  bool cont=true;
  while (cont) {
    
    idxNotePoly = getNotePolyIndexAvailable();
    notesPoly[idxNotePoly].volume = volume  ;
    notesPoly[idxNotePoly].pSound = & sounds[idxSound];
    notesPoly[idxNotePoly].posWav = 0; // At the very beggining of the WAV
    notesPoly[idxNotePoly].state = Playing;
    nbPlayingNotes++;    
    
    t2 = millis();
    if  ( (t2-t1) > 1 ) {
      DEBUG1(t2-t1);
    }
    t1 = t2;
    if ( (t2-t0)>1000 ) cont=false;
  }
DEBUG2("** playSound LOOP 2;",millis());
#endif 

  return idxSound;
}

//------------------------------------------------------------------------------------------------------------------------
/// @brief Play a note
/// @param note MIDI Note to play
/// @param volume Volume 0 -> 127
/// @return idxSound if OK, -1 if KO
int playNote(int note, int volume)
{
  int idxSound = getSoundIndexByNote(note);
  if (idxSound>=0) {
    return playSound(idxSound,volume);
  } else {
    DEBUG2("playNote note not found",note);
    return -1;
  }
}

#ifdef TRACE_MIDI

//------------------------------------------------------------------------------------------------------------------------
/// @brief Print on Serial data <data>
/// @param Data      Data to be printed
/// @param NumBytes  Length of data
void dumpData(const char* Data,uint8_t NumBytes)
{
    for(uint8_t i=0;i<NumBytes;i++)
      Serial.print(Data[i]); 
      Serial.println();  
}


//------------------------------------------------------------------------------------------------------------------------
/// @brief Validate a WAV header
/// @param Wav     Header data to be valited
/// @return     true/false
bool validWavData(T_WavHeader * Wav)
{
  
  if(memcmp(Wav->RIFFSectionID,"RIFF",4)!=0) 
  {    
    Serial.print("Invlaid data - Not RIFF format");
    return false;        
  }
  if(memcmp(Wav->RiffFormat,"WAVE",4)!=0)
  {
    Serial.print("Invlaid data - Not Wave file");
    return false;           
  }
  if(memcmp(Wav->FormatSectionID,"fmt",3)!=0) 
  {
    Serial.print("Invlaid data - No format section found");
    return false;       
  }
  if(memcmp(Wav->DataSectionID,"data",4)!=0) 
  {
    Serial.print("Invlaid data - data section not found");
    return false;      
  }
  if(Wav->FormatID!=1) 
  {
    Serial.print("Invlaid data - format Id must be 1");
    return false;                          
  }
  if(Wav->FormatSize!=16) 
  {
    Serial.print("Invlaid data - format section size must be 16.");
    return false;                          
  }
  if((Wav->NumChannels!=1)&(Wav->NumChannels!=2))
  {
    Serial.print("Invlaid data - only mono or stereo permitted.");
    return false;   
  }
  if(Wav->SampleRate>48000) 
  {
    Serial.print("Invlaid data - Sample rate cannot be greater than 48000");
    return false;                       
  }
  if((Wav->BitsPerSample!=8)& (Wav->BitsPerSample!=16)) 
  {
    Serial.print("Invlaid data - Only 8 or 16 bits per sample permitted.");
    return false;                        
  }
  return true;
}


//------------------------------------------------------------------------------------------------------------------------
/// @brief  Display on Serial a WAV header
/// @param Wav   WAV Header To be displayed
void dumpWAVHeader(T_WavHeader * Wav)
{
  DEBUG1("dumpWAVHeader...");
  if(memcmp(Wav->RIFFSectionID,"RIFF",4)!=0)
  {
    Serial.print("Not a RIFF format file - ");    
    dumpData(Wav->RIFFSectionID,4);
    return;
  } 
  if(memcmp(Wav->RiffFormat,"WAVE",4)!=0)
  {
    Serial.print("Not a WAVE file - ");  
    dumpData(Wav->RiffFormat,4);  
    return;
  }  
  if(memcmp(Wav->FormatSectionID,"fmt",3)!=0)
  {
    Serial.print("fmt ID not present - ");
    dumpData(Wav->FormatSectionID,3);      
    return;
  } 
  if(memcmp(Wav->DataSectionID,"data",4)!=0)
  {
    Serial.print("data ID not present - "); 
    dumpData(Wav->DataSectionID,4);
    return;
  }  
  // All looks good, dump the data
  Serial.print("Total size :");Serial.println(Wav->Size);
  Serial.print("Format section size :");Serial.println(Wav->FormatSize);
  Serial.print("Wave format :");Serial.println(Wav->FormatID);
  Serial.print("Channels :");Serial.println(Wav->NumChannels);
  Serial.print("Sample Rate :");Serial.println(Wav->SampleRate);
  Serial.print("Byte Rate :");Serial.println(Wav->ByteRate);
  Serial.print("Block Align :");Serial.println(Wav->BlockAlign);
  Serial.print("Bits Per Sample :");Serial.println(Wav->BitsPerSample);
  Serial.print("Data Size :");Serial.println(Wav->DataSize);
}

#endif // TRACE_MIDI




//------------------------------------------------------------------------------------------------------------------------------------
/// @brief  Check, according to table `notesPoly`, if there are some part of notes to play. Should be called very very frequently
void loopPlayWaves()
{
  // static unsigned long lastLoopPlayWaves = 0; // last time loopPlayWaves() has be called
 // unsigned long now=0;
 static int16_t buff[WAV_BUFFER_SIZE];  // buffer to write to I2S. Keep static to increase performance (avoid dynamic memory allocation)
  size_t nbBytes=0;         // Nb Bytes to write to I2S
  size_t bytesWritten;      // Returned by the I2S write routine
  int64_t signedSample;     // Single Signed Sample


  static unsigned long lastMeasure = 0;

//static uint8_t nbTrace=0;

  // No note to play -> END
  if (nbPlayingNotes==0) {
    return;
  }
    
  //  Check if not to fast for I2S. with the tempo, optimize blocking
//  now = millis();
  // if ( (now-lastLoopPlayWaves) < conf.DELAY_I2S) {
  //   return;
  // }
  // lastLoopPlayWaves = now;

//if (nbTrace<10) {  DEBUG2("** loopPlayWaves 1;",millis()); nbTrace++; }

  // Fill the buffer for I2S
  for (int j=0; j<conf.I2S_BUFFER_SIZE; j++) {
    boolean firstSample=true;
//    buff[j] = 0;
    int64_t sampleSum = 0; // use a signed 64 bit sum, not to loose data when reaching min/max
    for (int i=0; i<NB_NOTES_POLY; i++) {
      if ( notesPoly[i].state == Playing ) {
        // check if finish to play the sound : end of the WAV ?
        if ( notesPoly[i].posWav >= notesPoly[i].pSound->wavSize ) {
          resetNotePoly(i);
        } else {
          if (firstSample) {
            firstSample = false;
            nbBytes += 2;
          }
//DEBUG3(j,i,nbBytes);
          signedSample = notesPoly[i].pSound->wavBody [ notesPoly[i].posWav ] ;         // Get the sample of the note to play
          signedSample = signedSample * notesPoly[i].volume / 127 * conf.volumeGen / 100 ;   // ajust the volume of the sample according the to note volume & general volume
          sampleSum = sampleSum + signedSample;                                                    // Addition the sample
          notesPoly[i].posWav ++;                                                       // Next sample of the note to play
        }
      }
    }
    buff[j] = (int32_t) sampleSum;
    // Check if no sample to play anylonger regarding <notesPoly> ->  stop filling the buffer
    if (firstSample)
      j = conf.I2S_BUFFER_SIZE;
  }

  // Send the buffer to I2S
//now = micros();
  if (nbBytes>0) {
//if (nbTrace<10) {  DEBUG2("** loopPlayWaves 2;",millis()); nbTrace++; }
    
  i2s_write(i2s_num,buff,nbBytes,&bytesWritten,portMAX_DELAY);  // portMAX_DELAY
    if (nbBytes!=bytesWritten) {
      DEBUG3("!!!! NOT ALL SENT",nbBytes,bytesWritten);
    }
  }

  #ifdef TRACE_DELAI_HIT
  unsigned long tsNow = millis();
  if ( (tsNow- lastMeasure) > 6000)  { // + 6s new hit
    Serial.print("D: ");
    Serial.println( tsNow - tsHit );
    lastMeasure = millis();
  }
  #endif

}


//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
//     MIDI Song functions
//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------
/// @brief  get ms factor according to BPM and PPQN of a song
/// @return ms timestamp
float midiClic2Ms() 
{
	return (float) ( 60000.0 / (song.bpm   * song.ppqn) ) ;
}


//------------------------------------------------------------------------------------------------------------------------
/// @brief  Indicate if the note `pSongNote` should be played if left or right hand, according to parity of note velocity.  pair = Right, impair = Left
/// @param pSongNote note to play
/// @return HandLeftRight
HandLeftRight getHandVelocity(int velocity) 
{
  return (( velocity & 0x01) == 0) ? HandRight : HandLeft;
}

HandLeftRight getHandSongNote(T_SongNote * pSongNote) 
{
  return ( getHandVelocity(pSongNote->velocity) );
}


//------------------------------------------------------------------------------------------------------------------------
/// @brief Initialize a song. If existing, delete notesPoly...
/// @return true/false
bool initiateSong() 
{
  DEBUG1("initiateSong");
	// If existing sequence with notesPoly, clear notes

  resetSongMsg();
  if (song.lNotes) {
		free(song.lNotes);
		song.lNotes = NULL;
	}
  // if (song.lNotesClic) {
	// 	free(song.lNotesClic);
	// 	song.lNotesClic = NULL;
	// }
	song.nbMeasures = song.nbNotes = 0;
  song.filename[0] = 0;  // clear filename
  song.noteCur = song.noteFirst = song.noteLast = 0;
  song.measureCur = song.measureFirst = song.measureLast = 0;
  song.bpm = song.bpmBase = BPM_DEF;
  song.playing = false;
  song.ppqn = 24;
  song.t0 = 0;
	return true;
}


//------------------------------------------------------------------------------------------------------------------------
/// @brief  Generate a song from a MIDI_FILE : Retrieve and order notes in T_Song.lNotes table, taking into account clic notes and decompte measures
/// @param pMF 
/// @return true/false
bool generateSong(const MIDI_FILE *pMF) 
{
	char str[128];
	int ev;
	MIDI_MSG msg;
	int i,j;
	int nbNotes=0;
  unsigned long posMidiMax = 0;
  bool trille=false;

  DEBUG1("generateSong..");
	if (! initiateSong() )
		return false;

	midiReadInitMessage(&msg);
	int nbTracks = midiReadGetNumTracks(pMF);
	song.ppqn = midiFileGetPPQN(pMF);

	if (song.ppqn==0) {
    DEBUG1("ERROR: PPQN is null ! ")
    setSongMsg("le PPQN n'est pas fourni");
		return false;
	}


  // --------------------------------------------------------------------
	// first: parsing to retrieve retrieve general info to create Song :
	//     Count nb of notes 
  //     tempo
	//     BPM
  //     nb measures
  // --------------------------------------------------------------------
	for(i=0;i<nbTracks;i++) 	{
  //DEBUG2("   track ",i);
  //		printf("# Track %d\n", i);
		while(midiReadGetNextMessage(pMF, i, &msg))		{
//DEBUG1("     midiReadGetNextMessage ");
			ev = (msg.bImpliedMsg) ? msg.iImpliedMsg : msg.iType;
			switch (ev) {
				case msgNoteOn:
					nbNotes++;	
          if ( msg.dwAbsPos  > posMidiMax) // try to find last note
            posMidiMax = msg.dwAbsPos;
					break;
        case msgMetaEvent:
        switch (msg.MsgData.MetaEvent.iType) {
          case metaSetTempo:
            song.bpmBase = msg.MsgData.MetaEvent.Data.Tempo.iBPM;
            break;
          case	metaTimeSig:
            song.timeSignatureNom = msg.MsgData.MetaEvent.Data.TimeSig.iNom;
            song.timeSignatureDenom = msg.MsgData.MetaEvent.Data.TimeSig.iDenom/MIDI_NOTE_CROCHET;
          case	metaKeySig:
            muGetKeySigName(song.keySignature, msg.MsgData.MetaEvent.Data.KeySig.iKey);
            break;
        }
			}
		}
	}
  if ( song.bpmBase==0 )
    song.bpmBase = BPM_DEF;
	song.bpm  = song.bpmBase; 
  song.nbMeasures = (posMidiMax / (song.ppqn * song.timeSignatureNom)) + 1;
	song.nbNotes = nbNotes;

  DEBUG2("     iBPM             :  ",song.bpmBase);
  DEBUG2("     NB MEASURES      :  ", song.nbMeasures );
  DEBUG2("     NB NOTES         :  ", song.nbNotes );

	if (song.nbNotes==0) {
    setSongMsg("Aucune note dans le morceau");
		return false;
	}


  // --------------------------------------------------------------------
  // Create table for all notes to be potentially played 
  // --------------------------------------------------------------------
	song.lNotes = (T_SongNote*)  malloc( sizeof(T_SongNote) * song.nbNotes );
  if (song.lNotes==NULL) {
    initiateSong();
    setSongMsg("Impossible de créer le morceaux. Pas assez de mémoire.");
    DEBUG1( song.lastMsg  );
    return false;
  }

  // ------------------------------------------------------------------
  // Parse again each track to get all NOTE ON and NOTE OFF information
  // ------------------------------------------------------------------
	// reset current pointers for each track : mandatory before reparsing message
	_MIDI_FILE * _pmf = (_MIDI_FILE *) pMF;
	for (i=0; i<nbTracks; ++i) {
		_pmf->Track[i].ptr = _pmf->Track[i].pBase+8;
		_pmf->Track[i].pos = 0;
	}

	midiReadInitMessage(&msg);
	int idxNote = 0;
  unsigned long offsetPos = 0 ; //song.timeSignatureNom * song.ppqn; // shift MIDI pos cause measure 1 = clic

	for(i=0;i<nbTracks;i++) 	{
		while(midiReadGetNextMessage(pMF, i, &msg))		{
			ev = (msg.bImpliedMsg) ? msg.iImpliedMsg : msg.iType;

			if (ev == msgNoteOn)  {
				song.lNotes[idxNote].timeMidiStart = offsetPos + msg.dwAbsPos ;
				song.lNotes[idxNote].noteMidi = msg.MsgData.NoteOn.iNote;
				song.lNotes[idxNote].velocity = msg.MsgData.NoteOn.iVolume;
        song.lNotes[idxNote].trille = trille;
				idxNote++;
			}

      if (ev == msgSetParameter ) {
//        DEBUG3("msgSetParameter", msg.MsgData.NoteParameter.iControl,msg.MsgData.NoteParameter.iParam	);
        if (msg.MsgData.NoteParameter.iControl==ccSustainPedal) {
          trille = ( msg.MsgData.NoteParameter.iParam > 64);
        }
      }
      
      if (ev == msgNoteOff)  {
        bool found = false;
        // Find noteOn related to noteOff
        for (int j=idxNote-1;j>=0; j--) {
          if ( song.lNotes[j].noteMidi == msg.MsgData.NoteOff.iNote) {
            song.lNotes[j].timeMidiStop = msg.dwAbsPos ;
            found = true;
            j=-1; // to stop the loop
          }
        }
        if (!found) {
          DEBUG2("NOTEOFF not found",msg.MsgData.NoteOn.iNote)
        }
      }
			// if (ev == msgMetaEvent)  {
      //   switch(msg.MsgData.MetaEvent.iType) {
      //     // case	metaTimeSig:
      //     //   song.timeSignatureNom = msg.MsgData.MetaEvent.Data.TimeSig.iNom;
      //     //   song.timeSignatureDenom = msg.MsgData.MetaEvent.Data.TimeSig.iDenom/MIDI_NOTE_CROCHET;
      //     //   break;
      //     case	metaKeySig:
      //       muGetKeySigName(song.keySignature, msg.MsgData.MetaEvent.Data.KeySig.iKey);
      //       break;
      //   }
      // }

		}
	}


  // --------------------------------------------------------------------
	// Sort song notes (several tracks)
  // --------------------------------------------------------------------
	T_SongNote sn;
	unsigned long posMin;
	for (i=0; i<(song.nbNotes-1); i++) {

		posMin = song.lNotes[i].timeMidiStart;
		for (j=i+1; j<song.nbNotes; j++) {
			if (song.lNotes[j].timeMidiStart < posMin) {
				posMin = song.lNotes[j].timeMidiStart;
				memcpy(&sn, &song.lNotes[i], sizeof(T_SongNote));
				memcpy(&song.lNotes[i], &song.lNotes[j], sizeof(T_SongNote));
				memcpy(&song.lNotes[j], &sn, sizeof(T_SongNote));
			}
		}
	}

  int nbTicksByMeasure = song.timeSignatureNom * song.ppqn;

  // --------------------------------------------------------------------
  // Retrieve information for all notes : idxSound, measure
  // --------------------------------------------------------------------
  for (i=0;i<song.nbNotes;i++) {
    // Retrieve song index 
    song.lNotes[i].idxSound = getSoundIndexByNote( song.lNotes[i].noteMidi );

    // Retrieve measure
    song.lNotes[i].measure = (song.lNotes[i].timeMidiStart / nbTicksByMeasure ) +1  ;
  }


  // --------------------------------------------------------------------
  // Compute song information : 1st mesure and last mesure to be played
  // -------------------------------------------------------------------
  song.measureFirst = 1;
  song.measureLast = song.nbMeasures;
	

  // -------------------------------------------------------------------
  // Compute  timeline according to BPM and first note to play
  // -------------------------------------------------------------------
  computeSongTime(false);

	return true;
}


//------------------------------------------------------------------------------------------------------------------------
/// @brief  compute realtime of all notes, considering BPM, current note to be played
/// @return true if compute succeeded, false otherwise
bool computeSongTime(bool playing) 
{
  DEBUG1("computeSongTime...");
	float coef = midiClic2Ms();
  unsigned long now = millis();
  signed long timeMidi0;
  
  song.t0 = now;
  song.tf = song.t0 + ( (song.measureLast-song.measureFirst+1) * song.timeSignatureNom * song.ppqn * coef) ; // define the end

  // Get t0 MIDI time
  if (playing) {
    // if playing, get t0 midi time from the curNote
    timeMidi0 =  song.lNotes[ song.noteCur ].timeMidiStart - song.lNotes[0].timeMidiStart;
    DEBUG2("computeSongTime PLAYING",timeMidi0);
  } else {
    // otherwise, get t0 midi time from :
    //    - the first measure to play (song.noteCur = song.noteFirst)
    //    - nb of decompte measure
    timeMidi0 = (song.lNotes[ song.noteCur ].measure - 1 - song.decompte) * song.timeSignatureNom * song.ppqn;
    song.nextClicMs = now;
    DEBUG2("computeSongTime ",timeMidi0);
  }

	for (int i=0; i<song.nbNotes; i++) {
    // Do not play note before current note
    if ( i < song.noteCur  ) {
		  song.lNotes[i].timeMsStart = song.lNotes[i].timeMsStop = 0;
    } else {
		  song.lNotes[i].timeMsStart = now + (song.lNotes[i].timeMidiStart-timeMidi0) * coef;
		  song.lNotes[i].timeMsStop  = now + (song.lNotes[i].timeMidiStop-timeMidi0) * coef;
    }
	}
	return true;
}


//------------------------------------------------------------------------------------------------------------------------
/// @brief Display on SERIAL a song : general info + all notes
/// @return 
bool dumpSong()
{
	static char buff[300];

	sprintf(buff,"INFO      Nb notes:%d   BPM:%d  PPQN:%d nb measures:%d",song.nbNotes, song.bpm, song.ppqn, song.nbMeasures);
	DEBUG1(buff);
	DEBUG1("N°\tPos\tChrono\tNote\tVol\tTrille\tPosEnd\tChrEnd\tMeasure");		
	DEBUG1("-----\t-----\t-----\t-----\t-----\t-----\t-----\t-----\t-----");		
	for (int i=0; i<song.nbNotes; i++) {
		sprintf(buff,"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d", 
      i,
      song.lNotes[i].timeMidiStart, 
      song.lNotes[i].timeMsStart, 
      song.lNotes[i].noteMidi, 
      song.lNotes[i].velocity,
      song.lNotes[i].trille ? 1:0,
      song.lNotes[i].timeMidiStop, 
      song.lNotes[i].timeMsStop,
      song.lNotes[i].measure
      );		
		DEBUG1(buff);
	}
	return true;
}




//------------------------------------------------------------------------------------------------------------------------
/// @brief Load in a MIDI song from memory to `song` 
/// @param mem          binary data of the song
/// @param memSize      size of the data
bool loadSong(const BYTE * mem, size_t memSize) 
{
	MIDI_FILE *mf;

	initiateSong() ;
  mf = midiMemOpen(mem,memSize);
  if (mf == NULL) {
    setSongMsg("Impossible de créer le fichier MIDI en mémoire");
    return false;
  }
	generateSong(mf);
  // #ifdef DEBUGAPP
	// dumpSong();
  // #endif
	changeSong();

  // Free space
  midiFileClose(mf);

  return true;
}


//------------------------------------------------------------------------------------------------------------------------
/// @brief  Find first note to play according to <song.measureFirst>. update <song.noteFirst> and <song.noteCur> fields
void findSongFirstNote() 
{
  if (song.nbNotes==0) 
    return;
  for (int i=0; i<song.nbNotes; i++) {
    if ( song.lNotes[i].measure >= song.measureFirst ) {
      song.noteFirst = song.noteCur = i;
      break;
    }
  }
  DEBUG2("findSongFirstNote", song.noteFirst) ; 
}

//------------------------------------------------------------------------------------------------------------------------
/// @brief  Find last note to play according to <song.measureLast>. update <song.noteLast> field
void findSongLastNote() 
{
  if (song.nbNotes==0) 
    return;
  song.noteLast = song.nbNotes-1;
  for (int i=song.nbNotes-1; i>=0; i--) {
    if ( song.lNotes[i].measure <= song.measureLast ) {
      song.noteLast = i;
      break;
    }
  }
  DEBUG2("findSongLastNote", song.noteLast) ; 
}


//------------------------------------------------------------------------------------------------------------------------
/// @brief check if there is a clic note to play 
/// @return 0 : no note to play, or NOTE_CLIC1 / NOTE_CLIC2 if a clic to play
int checkNoteClic() {
  int note = 0;
  unsigned long now = millis();

  if (now < song.nextClicMs)  
    return note;
  
  note = (song.clicCurBeat==1) ? NOTE_CLIC1 : NOTE_CLIC2;
  song.clicCurBeat++;
  if (song.clicCurBeat > song.timeSignatureNom)
    song.clicCurBeat = 1;
  // Compute next clic
  if (song.nextClicMs==0) 
    song.nextClicMs = millis();

  song.nextClicMs += (unsigned long) ( 60000.0 / song.bpm ); 

  return note;
}

//------------------------------------------------------------------------------------------------------------------------
/// @brief Start playing automatically the global song 
bool startSong() {
  if (song.nbNotes==0) {
    return false;
  }
  song.playing = true;
  song.nextClicMs = 0;
  song.doubleNotes = false;
  song.clicCurBeat = 1;
  song.measureCur = song.measureFirst;
  song.metronome = false;
  resetSongMsg();
  changeSong();
  
  // Find first and last note to play according to measureFirst
  findSongFirstNote();
  findSongLastNote();
  computeSongTime(false);

  for (int i=0; i<song.nbNotes; i++) {
    song.lNotes[i].state = Idle;
    song.lNotes[i].lastPlayed = 0;
  }

  // dumpSong();
  DEBUG1("START song !");
  return true;
}


//------------------------------------------------------------------------------------------------------------------------
/// @brief Stop the ong
/// @return true/false 
bool stopSong()
{
  song.playing = false;
  song.noteCur = song.noteFirst;
  changeSong();
  return true;
}

//------------------------------------------------------------------------------------------------------------------------
/// @brief track a change of parameters in a song from pan. Increase `T_Song.idChange` if change. Allow to optimize communication between browser and pan : take into accout parameters only if change
void changeSong()
{
  song.idChange++;
}


//------------------------------------------------------------------------------------------------------------------------
/// @brief set a message in a song in order to commnicate between browser and pan
/// @param msg message to set
void setSongMsg(const char * msg) 
{
  strcpy(song.lastMsg,msg);
}


//------------------------------------------------------------------------------------------------------------------------
/// @brief reset the current message in a song
void resetSongMsg() 
{
  setSongMsg("");
}


//------------------------------------------------------------------------------------------------------------------------
/// @brief 
void setupSong()
{
  initiateSong();
}


void startMetronome()
{
  DEBUG1("startMetronome()");
  song.metronome = true;
  song.clicCurBeat = 1;
  song.nextClicMs = 0;      // force to play

}

void stopMetronome()
{
  DEBUG1("stopMetronome()");
  song.metronome = false;
}


//------------------------------------------------------------------------------------------------------------------------
/// @brief Check if 
///           there is a note to be played , 
///           song to stop (all notes played)
///        To be frequently called (in loop())
/// @return true if action done, false otherwise
bool loopSong() 
{
  bool ret=false;

  // Play the clic ?
  if ( ((song.playing && song.modeAuto && song.withClic)) || (song.metronome) )  {
    int noteClic = checkNoteClic();
    if (noteClic>0) {
      playSound( noteClic , song.volumeClic ); 
    }
  }

  // Check if song is running or not 
  if ( !song.playing ) 
    return false;

  // check if end of song  
  if ( (song.noteCur > song.noteLast ) && (millis()>song.tf) ) {
    DEBUG1("SONG FINISHED !!!");

    // If loop, restart the song, otherwise stop the song
    if (song.loop) {
      DEBUG1("Restart song !");
      startSong() ;
      ret =  true;
    } else {
      stopSong();
    }
    return ret;
  }

  // No more note to play but wait until the end of the last measure
  if (song.noteCur >= song.nbNotes) {
    return ret;
  }
  
  // Get current songNote
  T_SongNote * pSongNote = & song.lNotes[song.noteCur];


  // ----------------------------------------------
  // Mode AUTO
  // ----------------------------------------------
  if ( song.modeAuto) {

    // check if current note has to be played
    if ( pSongNote->timeMsStart <= millis() ) {
//DEBUG3("loopSongAuto",song.curNote,pNote->chrono);
      pSongNote->state = Played;
      T_Sound * pSound = &sounds[pSongNote->idxSound]; 
      pSound->timeMsStop = pSongNote->timeMsStop ; // for the LED to switch off

      // If a note to be played and the sound to be played : play this note
      if (  song.withSound )  {          
        playSound( pSongNote->idxSound , pSongNote->velocity); 
      }

      // Display the LED related to a sound
      displayLED( pSongNote->idxSound , true, getHandSongNote(pSongNote) );

      // ready for the next note
      song.noteCur ++;
      ret =  true;
    }
  
  // ----------------------------------------------
  // Mode LEARNING
  // ----------------------------------------------
  } else {
    // check if current note to be played
    if (  pSongNote->state == Idle )  {
      
      // Check if we've wait enough before displaying next note
      if ( (song.noteCur>0) && ( (millis()-song.lNotes[song.noteCur-1].lastPlayed) < conf.DELAY_LED_LEARN) )  {
        // Do nothing
      } else {
        pSongNote->state = ToBePlayed;
        displayLED( pSongNote->idxSound, true, getHandSongNote(pSongNote) );
        DEBUG3(" ---- JOUE la note ", pSongNote->idxSound, pSongNote->noteMidi);
        ret = true;

        // check if next note should be played simultenously
        if ( song.noteCur < (song.nbNotes - 1) ) {
          T_SongNote * pNextNote = & song.lNotes[song.noteCur +1]; 
          if ( pSongNote->timeMidiStart == pNextNote->timeMidiStart ) {
            pNextNote->state = ToBePlayed;
            displayLED( pNextNote->idxSound , true, getHandSongNote(pNextNote) );
            DEBUG2(" --++ JOUE aussi la note ",pNextNote->noteMidi);
            song.doubleNotes = true;
          } else {
            song.doubleNotes = false;
          }
        } else {
          song.doubleNotes = false;
        }

        // check if current note is a trille note
        if ( (!song.trille) && (song.lNotes[song.noteCur].trille) && (song.noteCur < (song.nbNotes - 1)) && (song.lNotes[song.noteCur+1].trille) ) {
          song.trille = true;
          song.trilleNote1 = song.lNotes[song.noteCur].idxSound;
          song.trilleNote2 = song.lNotes[song.noteCur+1].idxSound;
          song.trilleNote1Hand = getHandSongNote(& song.lNotes[song.noteCur]);
          song.trilleNote2Hand = (song.trilleNote1Hand==HandLeft) ? HandRight : HandLeft; // the opposite hand
          song.trilleNoteCurrent = song.trilleNote2; // force LED of note 1 
          song.trilleNoteLastTime = 0; //millis() + conf.DELAY_LED_TRILLE + 10;
        }
        // check if trille has to be stopped
        if ( (song.trille) && (!song.lNotes[song.noteCur].trille) ) {
          song.trille = false;
        }
      }
    }
  }

  return ret;
}

