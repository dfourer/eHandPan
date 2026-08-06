///=======================================================================================================================
///
/// @file global.h
/// 
/// Header file for all global variables
/// 
/// @author Eric GENOTELLE
///
///=======================================================================================================================

#pragma once

#include "arduino.h"
#include "sound.h"

/// @brief 
typedef struct 
{
    unsigned long       t0;
    int8_t              note;
    int8_t              velocity;
} T_Note;

typedef struct 
{
    int16_t volumeGen;                  // General volume : 0 ->100

    int16_t DELAY_MAX_DOUBLE_NOTES ;    // Max delay in ms when playing double notes 
    int16_t isDemoLed ;                 // Demo LED when started
    int16_t DELAY_I2S;                  // delay in ms before checking I2s
    int16_t DELAY_LED;                  // Delay in ms when displaying LED in free mode
    int16_t DELAY_LED_DEMO;             // Time in ms LED is ON when displayed for the DEMO
    int16_t DELAY_PIEZZO_MIN;           // Delay min in ms between 2 piezzo hits - to avoid rebonce. // TBD 10 ?
    int16_t DELAY_PIEZZO_MAX;           // Delay max in ms between 2 piezzo hits above which we consided it is a new hit
    int16_t PIEZZO_LEVEL_MIN;           // Piezzo level where volume is min (=PIEZZO_VOLUME_MIN)
    int16_t PIEZZO_LEVEL_MAX;           // Piezzo level where volume is MAX (=128)
    int16_t PIEZZO_VOLUME_MIN;          // Volume at threshold : 0 -> 127
    int16_t BPM_MIN;                    // BPM minimum
    int16_t BPM_MAX;                    // BPM maximum
    int16_t ADC_DB;                     // DB reduction fopr ADC
    int16_t DELAY_LED_LEARN;            // Delay in ms before displaying next LED in LEARN mode
    int16_t POTENTIOMETER;              // 1=with potard, 0=no potard
    int16_t DELAY_LED_TRILLE;           // Delay in ms when displaying trille note
    int16_t I2S_BUFFER_SIZE;            // Size of I2S buffer
    int16_t I2S_BUFFER_NB;              // Nb of I2S buffer
    bool testMode=false;                // 
} T_Config;


/// @brief Parametres which may be configurable with Web IHM
typedef struct 
{
    String              name;
    int16_t *           pValue;
    String              description;
    int16_t             min;
    int16_t             max;
    int16_t             def;
    int16_t             step;
} T_Parameter;

typedef struct 
{
    unsigned long   ts=0;
    uint8_t         idxSound;
    int16_t         value;
} T_LogPiezzo;


extern TaskHandle_t thScanPiezzo;               // Defined in global.cpp
// extern TaskHandle_t thMain;                     // Defined in global.cpp
extern QueueHandle_t queuePiezzo;               // Defined in global.cpp

extern T_Config conf;                           // Defined in global.cpp
extern T_Parameter parameters[];                // Defined in global.cpp
extern int nbParameters;                        // Defined in global.cpp

extern T_LogPiezzo logPiezzo[];                 // Defined in global.cpp
extern uint8_t logPiezzoPos;                    // Defined in global.cpp

extern T_Sound sounds[];                        // Defined in sound.cpp
extern T_Song song;                             // Defined in sound.cpp

extern unsigned char fileMidi[];                // Defined in global.cpp
extern size_t fileMidiLen;                      // Defined in global.cpp

extern const BYTE demoMidi[];                   // Defined in mididemo.cpp
extern size_t demoMidiLen;                      // Defined in mididemo.cpp

#ifdef CAPTURE_PIEZZO
#define PIEZZO_NB   300
extern unsigned long piezzoT0;                  // Defined in global.cpp
extern unsigned long piezzoTF;                  // Defined in global.cpp
extern unsigned long piezzoTime[];
extern uint16_t piezzoVal[];                    // Defined in global.cpp
extern int16_t piezzoPos;                       // Defined in global.cpp
#endif

#ifdef TRACE_DELAI_HIT
extern unsigned long tsHit;
#endif