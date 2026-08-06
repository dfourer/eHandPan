///=======================================================================================================================
///
/// @file config.h
/// 
/// Configuration file 
/// 
/// @author Eric GENOTELLE
/// @date 2024
///
///=======================================================================================================================
#pragma once

#include "config_secret.h"


//------------------------------------------------------------------------------------------------
// Version
//------------------------------------------------------------------------------------------------
#define PROGRAMME_VERSION               "1.4c"      // Version of this program
// #define PROGRAMME_VERSION               "0104"      // Version of this program
#define PROGRAMME_DATE                  __DATE__    // Date of this programf
#define PROGRAMME_TIME                  __TIME__    // Time of this program
#define EEPROM_CRC                      12345       // checksum for EEPROM. For first run or memory map change


//------------------------------------------------------------------------------------------------
// For debugging purpose
//------------------------------------------------------------------------------------------------
// #define DEBUGAPP                    // Uncomment to output trace 
// #define JUST1WAV                    // Uncomment to debug prg : few waves file loaded
// #define PAN_WIFI_MODE_STA           //  Uncomment when pan should connect in STATION mode to WIFI box
#define MIDI_SEND                      // send MIDI on serial
// #define CAPTURE_PIEZZO              // Uncomment to store values in array when hiting a piezzo (parameter = # of piezzo)
// #define TRACE_DELAI_HIT             // to measure hit performance
// #define TRACE_MIDI                  // MIDI functions to debug 
// #define DEBUG_KEYBOARD              // to enter note with keyboard

#ifdef MIDI_SEND
    #undef DEBUGAPP
#endif  // MIDI_SEND


//------------------------------------------------------------------------------------------------
// Define Sound Bank to use. all WAV files bank should referenced in sound.cpp 
//------------------------------------------------------------------------------------------------
#define BANK1        

#if defined(BANK1)
    #define BANKNAME       "BANK1"
#elif defined(BANK2)
    #define BANKNAME       "BANK2"
#elif defined(BANK3)
    #define BANKNAME       "BANK3"
#elif defined(BANK3)
    #define BANKNAME       "BANK4"
#else 
    #define BANKNAME       "BANK1"
#endif 


#define APPLI_NAME                  "DIY e-Handpan"         //Application Name in web root page
#define APPLI_MIDI_NAME             "[MIDI] DIY Handpan"
#define PAN_WIFI_AP_SSID            "PAN"                   //SSID prefix in WIFI AP mode
#define PAN_WIFI_AP_PASSWORD        "Pan1234!"              //Password related to SSID prefix in WIFI AP mode
#define PAN_WIFI_STA_SSID           "BoxGnl_5GHz"           //SSID in WIFI STA mode
#define PAN_WIFI_IP                 "10.0.0.1"              //IP address in WIFI STA mode 
#define PAN_WIFI_MASQUE             "255.255.255.0"         //IP mask and gateway address in WIFI STA mode 


#define FILE_MIDI_MAX_SIZE              20000               // Max size of a MIDI file
#define NOTE_MIDI_BASE      (MIDI_NOTE_C2 + MIDI_NOTE_A)    // first MIDI note of the PAN
#define BPM_DEF                         60          // Default BPM if not in the song
#define CLIC_VELOCITY                   100         // Velocity for 'clic' note

#define NB_PIEZZO                       16          // Nb of piezzo <T_Sound> in <sounds> table
#define NB_SOUNDS                       17          // Nb of sounds <T_Sound> in <sounds> table
#define NB_NOTES_POLY                   9           // Nb of poly <T_Notes_Poly> in <notesPoly> table

#define WAV_BUFFER_SIZE                 512         // of <int> (x2 bytes)
#define EEPROM_SIZE                     512         // EEPROM_SIZE 
#define NB_LOG_PIEZZO                   10          // Nb piezzo hit to log in test mode 


//------------------------------------------------------------------------------------------------
// Default values 
//------------------------------------------------------------------------------------------------
#define DELAY_I2S_DEF                   0           // Delai in ms before sending another I2S packet

#define DELAY_MAX_DOUBLE_NOTES_DEF      200         // Max delay in ms when playing double notes 
#define DELAY_LOOP_LED                  20          // Delay in ms between 2 LEDs loop
#define DELAY_LOOP_VOLUMEGEN            1000        // Delay in ms between 2 VOLUMEGEN  checks
#define DELAY_LOOP_WEBPARAM             2000        // Delay in ms between 2 Web parameter retrieves 
#define DELAY_LOOP_MIDI_MESSAGE         20          // Delay in ms to check MIDI message

#define DELAY_MIDI_MESSAGE              35

#define DELAY_LED_DEMO_DEF              400         // Time in ms LED is ON when displayed for the DEMO
#define DELAY_LED_DEF                   500         // Time in ms LED is ON when playing free
#define DELAY_ILED                      200         // Time in ms internal LED is ON when a note is played

#define DELAY_PIEZZO_MIN_DEF            100         // Delay min in ms between 2 piezzo hits - to avoid rebonce
#define DELAY_PIEZZO_MAX_DEF            300         // Delay max in ms between 2 piezzo hits  // TBD 10 ?

#define PIEZZO_THRESHOLD_DEF            400         // When getting analopg value from piezzo, threshold (0 -> 4095) to consider piezzo is active, volume min
#define PIEZZO_LEVEL_MIN_DEF            400         // When getting analopg value from piezzo, level (0 -> 4095) to consider piezzo with volume min (=PIEZZO_VOLUME_MIN_DEF)
#define PIEZZO_LEVEL_MAX_DEF            2000        // When getting analopg value from piezzo, level (0 -> 4095) to consider piezzo with volume max (=127)
#define PIEZZO_VOLUME_MIN_DEF           20          // Volume at PIEZZO_LEVEL_MIN : 0 -> 127

#define BPM_MIN_DEF                     20          // BPM minimum
#define BPM_MAX_DEF                     180         // BPM maximum

#define DELAY_LED_LEARN_DEF             500         // Delay en ms before displaying next LED in LEARN mode 
#define DELAY_LED_TRILLE_DEF            150         // Delay en ms when displaying trille note
#define I2S_BUFFER_SIZE_DEF              64         // I2S buffer size
#define I2S_BUFFER_NB_DEF                 3         // I2S number of buffers


//------------------------------------------------------------------------------------------------------------------------
// PIN configuration
//------------------------------------------------------------------------------------------------------------------------
#define PIN_MUX_VAL     1           // PIN for analog value from MUX
#define PIN_VOLUME      2           // PIN for volume (potentiometer)

#define PIN_I2S_DATA    4           // PIN for I2S : DATA
#define PIN_I2S_WSK     5           // PIN for I2S : WSK    
#define PIN_I2S_BCK     6           // PIN for I2S : BSK
#define PIN_I2S_MUT     7           // NOT USED

#define PIN_BKP_1        8          // NOT USED
#define PIN_BKP_2        9          // NOT USED
#define PIN_BKP_3       10          // NOT USED
#define PIN_BKP_4       11          // NOT USED

#define PIN_SR_DATA     12          // PIN for Shift Register : DATA
#define PIN_SR_CLOCK    13          // PIN for Shift Register : CLOCK  
#define PIN_SR_LATCH    14          // PIN for Shift Register : LATCH

#define PIN_MUX_A       15          // PIN A to pilot MUX CD4067B
#define PIN_MUX_B       16          // PIN B to pilot MUX CD4067B
#define PIN_MUX_C       17          // PIN C to pilot MUX CD4067B
#define PIN_MUX_D       18          // PIN D to pilot MUX CD4067B

#define PIN_BKP_5       19          // NOT USED
#define PIN_BKP_6       20          // NOT USED
