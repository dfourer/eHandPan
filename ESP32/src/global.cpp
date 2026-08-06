///=======================================================================================================================
///
/// @file global.cpp
/// 
/// Body file for all global variables
/// 
/// @author Eric GENOTELLE
///
///=======================================================================================================================

#include "config.h"
#include "global.h"


// ADC_ATTEN_DB_0   = 0,  /*!<No input attenumation, ADC can measure up to approx. 800 mV. */
// ADC_ATTEN_DB_2_5 = 1,  /*!<The input voltage of ADC will be attenuated extending the range of measurement by about 2.5 dB (1.33 x) */
// ADC_ATTEN_DB_6   = 2,  /*!<The input voltage of ADC will be attenuated extending the range of measurement by about 6 dB (2 x) */
// ADC_ATTEN_DB_11  = 3,  /*!<The input voltage of ADC will be attenuated extending the range of measurement by about 11 dB (3.55 x) */

TaskHandle_t thScanPiezzo;
// TaskHandle_t thMain;
QueueHandle_t queuePiezzo;


// @brief General config
T_Config conf;

T_Parameter parameters[] = 
{
  { "DELAY_I2S", &conf.DELAY_I2S , "OBSOLETE_Délai entre 2 buffer I2S (en ms)", 0, 1000, DELAY_I2S_DEF, 1 },
  { "DELAY_MAX_DOUBLE_NOTES", &conf.DELAY_MAX_DOUBLE_NOTES, "Délai max de double notes (en ms)", 10, 1000, DELAY_MAX_DOUBLE_NOTES_DEF, 10 },
  { "isDemoLed", &conf.isDemoLed,"Affiche les LED au démarrage (0 ou 1)", 0, 1, 1, 1 },
  { "DELAY_LED_DEMO", &conf.DELAY_LED_DEMO,"Durée d'affichage des LED au démarrage", 10, 1000, DELAY_LED_DEMO_DEF, 10},
  { "DELAY_LED", &conf.DELAY_LED, "Durée d'affichage des LED en mode libre", 10, 1000, DELAY_LED_DEF, 10},
  { "PIEZZO_VOLUME_MIN", &conf.PIEZZO_VOLUME_MIN, "Volume min au déclenchement du piezo", 1, 120, PIEZZO_VOLUME_MIN_DEF, 10 },
  { "PIEZZO_LEVEL_MIN", &conf.PIEZZO_LEVEL_MIN, "Niveau du piezzo où le volume est au min (PIEZZO_VOLUME_MIN)", 10, 4095, PIEZZO_LEVEL_MIN_DEF, 10 },
  { "PIEZZO_LEVEL_MAX", &conf.PIEZZO_LEVEL_MAX, "Niveau du piezzo où le volume est au MAX (127)", 10, 4095, PIEZZO_LEVEL_MAX_DEF, 10 },
  { "DELAY_PIEZZO_MIN", &conf.DELAY_PIEZZO_MIN, "Délai min en 2 frappes piezo (antirebond) (en ms)", 10, 1000, DELAY_PIEZZO_MIN_DEF, 10},
  { "DELAY_PIEZZO_MAX", &conf.DELAY_PIEZZO_MAX, "Délai max en 2 frappes piezo (en ms)", 10, 1000, DELAY_PIEZZO_MAX_DEF, 10},
  { "BPM_MIN", &conf.BPM_MIN, "BPM min", 10, 1000, BPM_MIN_DEF, 10},
  { "BPM_MAX", &conf.BPM_MAX, "BPM max", 10, 1000, BPM_MAX_DEF, 10},
  { "ADC_DB", &conf.ADC_DB, "Attenuation  de  l'ADC", 0, 3, 3, 1},
  { "DELAY_LED_LEARN", &conf.DELAY_LED_LEARN, "Delai en ms avant d'afficher la LED suivante en mode LEARN", 10, 1000, DELAY_LED_LEARN_DEF, 10},
  { "POTENTIOMETER", &conf.POTENTIOMETER, "Avec ou Sans potard", 0, 1, 1, 1},
  { "DELAY_LED_TRILLE", &conf.DELAY_LED_TRILLE, "Delai en ms avant d'afficher la LED suivante en mode LEARN", 100, 1000, DELAY_LED_TRILLE_DEF, 10},
  { "I2S_BUFFER_SIZE", &conf.I2S_BUFFER_SIZE, "Taille du buffer I2S (save&reboot)", 16, 512, I2S_BUFFER_SIZE_DEF, 1},
  { "I2S_BUFFER_NB", &conf.I2S_BUFFER_NB, "Nb de bufferI2S (save&reboot)", 2, 10, I2S_BUFFER_NB_DEF, 1},
};

int nbParameters = sizeof (parameters) / sizeof(T_Parameter);

T_LogPiezzo logPiezzo[NB_LOG_PIEZZO];
uint8_t logPiezzoPos = 0;

/// @brief Table of all WAV sounds
T_Sound sounds[NB_SOUNDS];

/// @brief MIDI file in memory
unsigned char fileMidi[FILE_MIDI_MAX_SIZE]; 

/// @brief MIDI file size 
size_t fileMidiLen=0;


/// @brief current song
T_Song song;

#ifdef CAPTURE_PIEZZO
unsigned long piezzoT0;
unsigned long piezzoTF;
unsigned long piezzoTime[PIEZZO_NB];
uint16_t piezzoVal[PIEZZO_NB];
int16_t piezzoPos = 0;
#endif

#ifdef TRACE_DELAI_HIT
unsigned long tsHit;
#endif