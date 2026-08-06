///=======================================================================================================================
///
/// @file sound.cpp
/// 
/// Header file for sound management:
/// 
/// @author Eric GENOTELLE
/// @date 2024
///
///=======================================================================================================================

#pragma once

#include "arduino.h"
#include "midifile.h"


//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
//     WAVE and NOTES types (enum, structures, ...)
//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
#define NOTE_MIDI_CLIC1  0
#define NOTE_MIDI_CLIC2  1
#define NOTE_MIDI_ERROR  2
#define NOTE_CLIC1  (14)
#define NOTE_CLIC2  (NOTE_CLIC1 + 1) 
#define NOTE_ERROR  (NOTE_CLIC1 + 2) 


//------------------------------------------------------------------------------------------------------------------------
/// @brief Status of a note
typedef enum {
  Idle          = 0,
  ToBePlayed    = 1,
  Playing       = 2,
  Played        = 3,
} NoteState;


//------------------------------------------------------------------------------------------------------------------------
/// @brief Left or Right HAND
typedef enum {
  HandLeft  = 0,
  HandRight = 1,
  HandBoth  = 2,
} HandLeftRight;

//------------------------------------------------------------------------------------------------------------------------
/// @brief Structure for WAV header
typedef struct 
{
  //   RIFF Section    
  char RIFFSectionID[4];      // Letters "RIFF"
  uint32_t Size;              // Size of entire file less 8
  char RiffFormat[4];         // Letters "WAVE"
  
  //   Format Section    
  char FormatSectionID[4];    // letters "fmt"
  uint32_t FormatSize;        // Size of format section less 8
  uint16_t FormatID;          // 1=uncompressed PCM
  uint16_t NumChannels;       // 1=mono,2=stereo
  uint32_t SampleRate;        // 44100, 16000, 8000 etc.
  uint32_t ByteRate;          // =SampleRate * Channels * (BitsPerSample/8)
  uint16_t BlockAlign;        // =Channels * (BitsPerSample/8)
  uint16_t BitsPerSample;     // 8,16,24 or 32

  // Data Section
  char DataSectionID[4];      // The letters "data"
  uint32_t DataSize;          // Size of the data that follows
} T_WavHeader;



//------------------------------------------------------------------------------------------------------------------------
/// @brief Structure for a sound : note + wavHeader + wav signal
typedef struct 
{
    int16_t               noteMidi;           // MIDI note 
    char                  noteName [4];   // MIDI note name
    size_t                wavSize;
    const int16_t       * wavBody;            // WAV body
    unsigned long         timeMsStop = 0;     // when the sound was finished to be played
    uint8_t               PINpiezzo ;
    uint8_t               PINledLeft;
    uint8_t               PINledRight;
    bool                  ledLeftOn = false;
    bool                  ledRightOn = false;
    HandLeftRight         lastHand = HandLeft;
    int16_t               threshold ;           // Threshold for piezzo signal to consider the volume min
    unsigned long         lastPressed = 0;    // When the piezzo was played
    int16_t               lastPiezzoVal = 0;  // last value from piezzo
    int16_t               nbPressed = 0;      // Nb time the piezzo is pressed 
    unsigned long         lastMidiMessage = 0;       // when MIDI note has been sent
} T_Sound;



//------------------------------------------------------------------------------------------------------------------------
/// @brief Structure for a played note. Used in table <notesPoly>
typedef struct 
{
  NoteState    state;               // 'Idle' or 'Playing'
  T_Sound *     pSound;             // Pointer to a sound <T_Sound> in table <sounds>
  uint32_t      posWav;             // cursor position in the sound WAV array
  int           volume;             // 0 -> 127  //TBD velocity ?
  uint32_t      chrono;             // unique incremental ID (used to get the oldest note)
} T_NotePoly;



//------------------------------------------------------------------------------------------------------------------------
/// @brief A note to be played in a song <T_Song>, referenced in table <song.lNotes[]>
typedef struct 
{
	int			        num;              // Num of the note in the song
  int             idxSound;         // index of the sound in <sounds> table
	int			        noteMidi;         // MIDI Note
  NoteState       state;            // Idle, ToBePlayed, Played
	int			        velocity;         // Velocity of the note : 0->127
  int             measure;          // Mesure in  which the note is
  bool            trille;           // Is this note played in trille mode ?
	unsigned long   timeMidiStart;    // MIDI tick when the note starts
	unsigned long   timeMidiStop;     // MIDI tick when the note stops
	unsigned long   timeMsStart;      // time in ms position when the note starts 
	unsigned long   timeMsStop;       // time in ms position when the note stops 
  unsigned long   lastPlayed;       // when the note was played last time
} T_SongNote;


//------------------------------------------------------------------------------------------------------------------------
/// @brief A song
typedef struct 
{
  int16_t     idChange;             // ID to track change in song parameters
  char        lastMsg[100];          // Last message

  char        filename[100];        // song name
	unsigned long t0=0;               // when song started
	unsigned long tf;                 // when song ends
	bool 		    playing=false;        // the song is currently playing ?
	int16_t     noteCur;              // current playing note
  int16_t     noteFirst;            // First note to be played
  int16_t     noteLast;             // Last note to be played
	int16_t     measureCur;           // current playing measure
  int16_t     measureFirst;         // First Measure to be played
  int16_t     measureLast;          // Last Measure to be played
  bool        loop = false;         // play the song in loop ?
  bool        withClic=true;        // play with the clic ?
  int         volumeClic=50;        // Volume for the clic
  unsigned long   nextClicMs;       // when next click has to be played (in ms)
  bool        metronome = false;    // Metronme is ON or OFF
  int16_t     clicCurBeat;          // 1, 2, 3, 4
  int16_t     decompte=1;           // Countdown Measure before playing song
  int16_t     timeSignatureNom = 4;     // Nominator of time signature (*4* / 4)
  int16_t     timeSignatureDenom = 4;   // Denominator of time signature (4 / *4*)
  char        keySignature[10];     // Key signature. Ex: "Cm"
	int16_t 		ppqn=24;                 // PPQN of the song
	int16_t 		bpmBase=60;      // Original BPM of the song
	int16_t 		bpm=60;          // BPM of the song
	int16_t 		nbNotes = 0;          // Nb of notes in the song
	int16_t 		nbMeasures = 0;       // Nb of measures in the song
	bool		    modeAuto=true;        // Song in mode AUTO (ESP is playing) and LEARNING (User is playing, ESP is checking)
  bool        withSound=true;       // true=play song, false=do not play sound (LED only)
	T_SongNote * 	lNotes=NULL;        // list of notes (<T_SongNote>) in the song
  bool        doubleNotes;          // current double notes to play ?
  bool        trille;               // currently playing trille ?
  uint8_t     trilleNote1;          // Num of the 1st note to play in trille
  uint8_t     trilleNote2;          // Num of the 2nd note to play in trille
  uint8_t     trilleNoteCurrent;    // Num of the current trille note 
  HandLeftRight  trilleNote1Hand;   // Hand of the 1st note to play in trille
  HandLeftRight  trilleNote2Hand;   // Hand of the 2nd note to play in trille
  unsigned long trilleNoteLastTime; // Last time when the current trille note 
	unsigned long tsiLED;             // timestamp internal LED


} T_Song;


//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
//     WAVE and NOTES functions
//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------

//void setupSound(int idx, const unsigned char * son_wav, int note,const char * noteName, int PINledLeft, int PINledRight);
void setupSounds();
int getSoundIndexByNote(int note);
bool isSoundClic(int indexSound);

void resetNotePoly(int i);
void resetAllNotesPoly();
int getNbOfPlayingNotes();
int getNotePolyIndexAvailable();

int playSound(int idxSound, int volume);
int playNote(int noteMidi, int volume);

#ifdef TRACE_MIDI
void dumpData(const char *Data, uint8_t NumBytes);
bool validWavData(T_WavHeader * Wav);
void dumpWAVHeader(T_WavHeader * Wav);
#endif

void loopPlayWaves();

float midiClic2Ms();
HandLeftRight getHandVelocity(int velocity);
HandLeftRight getHandSongNote(T_SongNote * pSongNote);

bool initiateSong() ;
bool generateSong(const MIDI_FILE *pMF);
bool computeSongTime(bool playing);
bool dumpSong();
bool loadSong(const BYTE * mem, size_t memSize) ;
void findSongFirstNote() ;
void findSongLastNote();
bool startSong();
bool stopSong();
void changeSong();
void setSongMsg(const char * msg) ;
void resetSongMsg();

void setupSong();
void startMetronome();
void stopMetronome();
bool loopSong();
