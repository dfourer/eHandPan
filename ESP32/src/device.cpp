///=======================================================================================================================
///
/// @file device.cpp
/// 
/// Body file for devices management (i2s excluded): LED, piezzo, EEPROM, Keyboard (debug)
/// 
/// @author Eric GENOTELLE
///
///=======================================================================================================================
#include <EEPROM.h>
#include "tools.h"
#include "ShiftRegister74HC595.h"
#include "CD74HC4067.h"
#include <adafruit_neopixel.h>

#include "device.h"
#include "config.h"
#include "global.h"
#include "midifile.h"

#ifdef MIDI_SEND
#include <Adafruit_TinyUSB.h>
#include <MIDI.h>
#endif

/// @brief Shift Register to manage LED.
ShiftRegister74HC595<4> sr(PIN_SR_DATA, PIN_SR_CLOCK, PIN_SR_LATCH);

/// @brief MUC to manage PAD
CD74HC4067 mux(PIN_MUX_A, PIN_MUX_B, PIN_MUX_C, PIN_MUX_D);  // (S0, S1, S2, S3)

#ifdef MIDI_SEND
Adafruit_USBD_MIDI usb_midi;
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MidiUsb);
#endif

#define NUMPIXELS 1
#define LED_PIN 48
Adafruit_NeoPixel pixels(NUMPIXELS,LED_PIN,NEO_GRB + NEO_KHZ800);


//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
//     Internal LED function
//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------

void iled_color(uint8_t r, uint8_t g, uint8_t b)
{
  pixels.setPixelColor(0, pixels.Color(r,g,b));  
//  pixels.setBrightness(255);

  pixels.show();
}

void iled_color_blue()
{
  iled_color(0,0,255);
}



void iled_off()
{
  iled_color(0,0,0);
}



//------------------------------------------------------------------------------------------------------------------------
/// @brief Setup all devices
void setupDevices()
{
  initConfig();
  setupEEPROM();
  setupLED();
  setupPiezzo();
  setupMIDI();
}

//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
//     EEPROM functions
//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------
/// @brief  Save a int value `val` EEPROM at address `*paddr`. Increment paddr to the next address to be written
/// @param paddr Pointer to address to save value
/// @param val Value to save
void saveEEPROMInt(int * paddr,int16_t val) 
{
  EEPROM.put( *paddr ,val);
  *paddr = *paddr + sizeof(val);
}


//------------------------------------------------------------------------------------------------------------------------
/// @brief Read a int value `*pval` EEPROM at address `*paddr`. Increment paddr to the next address to be read
/// @param paddr Pointer to address to read value
/// @param pval Pointer to value to read
/// @param min Min value
/// @param max Max value
/// @return false if value has to be corrected regarding min/max
bool readEEPROMInt(int * paddr,int16_t * pval,int16_t min, int16_t max) 
{
  bool ret = true;
  EEPROM.get( *paddr , *pval);
  *paddr = *paddr + sizeof(int16_t);

  if (*pval<min) {
    *pval = min;
    ret = false;
  }
    
  if (*pval>max) {
    *pval = max;
    ret = false;
  }
  return ret;
}


//------------------------------------------------------------------------------------------------------------------------
/// @brief setup EEPROM
void setupEEPROM()
{
  // Init EEPROM
  DEBUG2("EEPROM_SIZE:",EEPROM_SIZE);
  bool ret = EEPROM.begin(EEPROM_SIZE) ;
  DEBUG1 ( ret ? "  setup EEPROM OK." : "  setup EEPROM ERROR.");

  readConfigEEPROM();
}


//------------------------------------------------------------------------------------------------------------------------
/// @brief read config (sounds velocity, ...) from EEPROM
void readConfigEEPROM()
{
  int addr=0;
  int16_t crc;
  bool saveEEPROOM=false;
  DEBUG1("readConfigEEPROM()")

  // EEPROM CRC
  readEEPROMInt( &addr , &crc, 0,30000 );
  if (crc != EEPROM_CRC) {
    DEBUG3("EEPROM_CRC Failed : initConfig()...", crc,EEPROM_CRC);
    resetConfigEEPROM();
  } else {

    for (int i=0 ; i<NB_PIEZZO; i++) {
      if (! readEEPROMInt( &addr , &sounds[i].threshold, 10,3000 ) ) {
        saveEEPROOM = true;
      }
    }

    for (int i=0; i<nbParameters; i++) {
      if (! readEEPROMInt( &addr , parameters[i].pValue , parameters[i].min, parameters[i].max ) ) {
        saveEEPROOM = true;
      }
    }
    if (conf.DELAY_I2S != 0) {
      conf.DELAY_I2S = 0;
      conf.I2S_BUFFER_NB = I2S_BUFFER_NB_DEF;
      conf.I2S_BUFFER_SIZE = I2S_BUFFER_SIZE_DEF;
      saveEEPROOM = true;
    }
  }
  if (saveEEPROOM)  saveConfigEEPROM();
}


//------------------------------------------------------------------------------------------------------------------------
/// @brief save config (general volume, sounds velocity, ...) in EEPROM
void saveConfigEEPROM()
{
  int addr=0;
  int16_t crc = EEPROM_CRC;

  DEBUG1("saveConfigEEPROM()")

  // EEPROM CRC
  saveEEPROMInt( &addr , crc );

  for (int i=0 ; i<NB_PIEZZO; i++) {
    saveEEPROMInt( &addr , sounds[i].threshold );
  }

  for (int i=0; i<nbParameters; i++) {
    saveEEPROMInt( &addr , *(parameters[i].pValue) );
  }

  bool ret = EEPROM.commit();
  DEBUG2(" EEPROM.commit()",ret?"OK":"KO");
}

//------------------------------------------------------------------------------------------------------------------------
/// @brief reset config (general volume, sounds velocity, ...) in EEPROM
void resetConfigEEPROM()
{
  DEBUG1("resetConfigEEPROM()")

  initConfig();

  saveConfigEEPROM();
}




//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
//     LED functions related to note
//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------
/// @brief  setup LED
void setupLED()
{
  sr.setAllLow(); // set all pins LOW
  
  iled_off();
}


//------------------------------------------------------------------------------------------------------------------------
/// @brief Display quickly all LEDs one after one
void demoLED() 
{
  DEBUG1("demoLED...")
  int led_period = conf.DELAY_LED_DEMO;
  sr.setAllLow(); // set all pins LOW
//  uint8_t piezzo=0;

  // First saladier
  DEBUG1("SALADIER 1...");
  for (int i=0; i<NB_PIEZZO; i++) {
    if (sounds[i].PINpiezzo < 8) {
      sr.set(sounds[i].PINledLeft,HIGH);
    }
  }
  delay(led_period);
  sr.setAllLow(); // set all pins LOW
  for (int i=0; i<NB_PIEZZO; i++) {
    if (sounds[i].PINpiezzo < 8) {
      sr.set(sounds[i].PINledRight,HIGH);
    }
  }
  delay(led_period);
  sr.setAllLow(); // set all pins LOW

  // 2nde saladier
  DEBUG1("SALADIER 2...");
  for (int i=0; i<NB_PIEZZO; i++) {
    if (sounds[i].PINpiezzo >= 8) {
      sr.set(sounds[i].PINledLeft,HIGH);
    }
  }
  delay(led_period);
  sr.setAllLow(); // set all pins LOW
  for (int i=0; i<NB_PIEZZO; i++) {
    if (sounds[i].PINpiezzo >= 8) {
      sr.set(sounds[i].PINledRight,HIGH);
    }
  }
  delay(led_period);

  sr.setAllLow(); // set all pins LOW
  DEBUG1("demoLED.")
}

//------------------------------------------------------------------------------------------------------------------------
/// @brief Switch ON/OFF a LED  related to a sound
/// @param idxSound  Index of a sound
/// @param on true=To switch ON, false=to switch OFF, 
/// @param hand if on=true , Right or Left . If on=false, switch off both LED
void displayLED(int idxSound, bool on, HandLeftRight hand) 
{
//  sounds[idxSound].chrono = millis();

  int ledValue =  on ? HIGH : LOW;
  // DEBUG4("displayLED",idxSound,ledValue,hand)
  switch (hand) {
    case HandLeft:
      // DEBUG2("HandLeft",sounds[idxSound].PINledLeft);
      sr.set( sounds[idxSound].PINledLeft, ledValue);
      sounds[idxSound].ledLeftOn = on;
      break;
    case HandRight:
      //DEBUG2("HandRight",sounds[idxSound].PINledRight);
      sr.set( sounds[idxSound].PINledRight, ledValue);
      sounds[idxSound].ledRightOn = on;
      break;
    case HandBoth:
      sr.set( sounds[idxSound].PINledRight, ledValue);
      sr.set( sounds[idxSound].PINledLeft, ledValue);
      sounds[idxSound].ledRightOn = on;
      sounds[idxSound].ledLeftOn = on;
      break;
  }
  if (on && !song.playing) {
    sounds[idxSound].timeMsStop = millis() + conf.DELAY_LED;
  }
}




//------------------------------------------------------------------------------------------------------------------------
/// @brief Check if there are some LED to switch ON/OFF
void loopLED() 
{
  static unsigned long timeLastLoop = 0;
  
  // Check if LEDs need to be set/unset
  unsigned long now = millis();
  if ( (now-timeLastLoop)< DELAY_LOOP_LED ) {
    return;
  }
  timeLastLoop = now;

  // For Internal LED
  if ( (timeLastLoop - song.tsiLED) > DELAY_ILED ) {
    iled_off();
  }

  if ( song.playing ) {
    if (!song.modeAuto)  {
      // In playing LEARNING mode, just checck trille mode. In not trille, LED will be checked in touchNote()
      if (song.trille) {
        // change note LED ?
        if ( (song.trilleNoteLastTime + conf.DELAY_LED_TRILLE) < now) {
          song.trilleNoteLastTime = now;
          if ( song.trilleNoteCurrent==song.trilleNote1 ) {
            song.trilleNoteCurrent = song.trilleNote2;
            displayLED(song.trilleNote1, false, song.trilleNote1Hand);
            displayLED(song.trilleNote2, true, song.trilleNote2Hand);
          } else {
            song.trilleNoteCurrent = song.trilleNote1;
            displayLED(song.trilleNote1, true, song.trilleNote1Hand);
            displayLED(song.trilleNote2, false, song.trilleNote2Hand);
          }
        }
      }
      return;
    } else {
      // In playing AUTO mode, switch OFF all leds if time's up
      for (int i=0; i<NB_PIEZZO; i++) {
        if ( sounds[i].timeMsStop < millis() ) {
            displayLED(i, false, HandBoth);
          }
      }
      return;  
    }
  } else {
    // Playing free
    for (int i=0; i<NB_PIEZZO; i++) {
      if (  ( (sounds[i].ledRightOn) || (sounds[i].ledLeftOn)) && 
            (sounds[i].timeMsStop < millis() ) ) {
           displayLED(i, false, HandBoth);
//         if (!conf.testMode) {
//           displayLED(i, false, HandBoth);
//         } else {
//           // in test mode, if left LED is ON, turn OFF left and ON right
//           if ( (sounds[i].timeMsStop < millis()) && (sounds[i].ledLeftOn) ) {
//             displayLED(i, false, HandLeft);
//             displayLED(i, true, HandRight);
// //            sounds[i].timeMsStop = millis() + conf.DELAY_LED;
//           }
//           if ( (sounds[i].timeMsStop < millis()) && (sounds[i].ledRightOn) ) {
//             displayLED(i, false, HandRight);
//           }
//         }
      }
    }
  }
}


//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
//     TOUCH functions 
//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------
///  @brief Play the sound.  
///        If not playing a MIDI  song : display LED, If playing a MIDI song in mode "LEARN" display the LED
/// @param idxSound index of the sound to play
/// @param velocity velocity (0 -> 127 ) of the sound to play
void touchNote(int idxSound, int velocity) 
{
  // -------------------------------------------------------
  // Play the sound
  // -------------------------------------------------------
  playSound(idxSound,velocity);
  int noteMidi = sounds[idxSound].noteMidi;


  // -------------------------------------------------------
  // Send MIDI note on Serial
  // -------------------------------------------------------
#ifdef MIDI_SEND
  DEBUG2("MIDI.sendNoteOn",noteMidi)
  MidiUsb.sendNoteOn(noteMidi,velocity,1);
  sounds[idxSound].lastMidiMessage = millis();
#endif

  // -------------------------------------------------------
  // Display internal LED
  // -------------------------------------------------------
  iled_color_blue();
  song.tsiLED = millis();

  // -------------------------------------------------------
  // if playing free
  // -------------------------------------------------------
  if ( ! song.playing ) {
    displayLED(idxSound,true,HandBoth);
    return;
  }

  // -------------------------------------------------------
  // mode SEQUENCE : do nothing
  // -------------------------------------------------------
  if ( song.modeAuto ) {
    return;
  }

  // -------------------------------------------------------
  // mode LEARN
  // -------------------------------------------------------
  // User has played the right note ?
  if ( (song.lNotes[song.noteCur].state == ToBePlayed) && (song.lNotes[song.noteCur].noteMidi ==  noteMidi) ) {
    // switch OFF the LED of the note if not double notes
    if (!song.doubleNotes) {
      displayLED( song.lNotes[song.noteCur].idxSound,false,HandBoth );
    }
    DEBUG2("  Played",song.noteCur);
    song.lNotes[song.noteCur].state = Played;
    song.lNotes[song.noteCur].lastPlayed = millis();
  }

  // check if note or the 2 simultaneous notes has/have being played
  if (song.doubleNotes) {

    if ( (song.lNotes[song.noteCur+1].state == ToBePlayed) && (song.lNotes[song.noteCur+1].noteMidi == noteMidi ) ){
      // switch OFF the LED of the note
      song.lNotes[song.noteCur+1].state = Played;
      song.lNotes[song.noteCur+1].lastPlayed = millis();
      DEBUG2("  Played n2",song.noteCur+1);
    } 

    if ( (song.lNotes[song.noteCur].state == Played) && (song.lNotes[song.noteCur+1].state == Played) ) {
      DEBUG3("2 notes played",song.noteCur,song.noteCur+1);
      // check if the 2 notes are played in a short amount of time
      long delta = song.lNotes[song.noteCur+1].lastPlayed - song.lNotes[song.noteCur].lastPlayed;
      if (delta<0) 
        delta = - delta;
      if ( delta < conf.DELAY_MAX_DOUBLE_NOTES ) {
        DEBUG1("OK for the 2 notes !")
        displayLED( song.lNotes[song.noteCur].idxSound,false,HandBoth );
        displayLED( song.lNotes[song.noteCur+1].idxSound,false,HandBoth );
        song.noteCur += 2;
      } else {
        // too slow : 2 notes to be replayed
        DEBUG1("too slow for the 2 notes : replayed!")
        song.lNotes[song.noteCur].state = ToBePlayed;
        song.lNotes[song.noteCur+1].state = ToBePlayed;
        song.lNotes[song.noteCur].lastPlayed = 0;
        song.lNotes[song.noteCur+1].lastPlayed = 0;
      }
    } 
  } else {
    if (song.lNotes[song.noteCur].state == Played) {
      song.noteCur ++;
    }
  }
}



//------------------------------------------------------------------------------------------------------------------------
/// @brief same as <touchNote()> but with MIDI note in input 
/// @param noteMidi  MIDI note
/// @param velocity  velocity of note to play
void touchNoteMidi(int noteMidi, int velocity) 
{
  int idxSound = getSoundIndexByNote(noteMidi);
  touchNote(idxSound, velocity);
}



#ifdef DEBUG_KEYBOARD

//------------------------------------------------------------------------------------------------------------------------
/// @brief for DEBUG : check if keys are pressed on keyboard. for debugging purpose
void loopKeyboard()
{
  static const char keyboard[] =  "qzsdrftghujiko";

  while (Serial.available()) {
    char inChar = Serial.read();
    bool found=false;
DEBUG1(inChar);

    char * ptr;
    if (ptr=strchr(keyboard,inChar) ) {
      found = true;
      int pos = ptr-keyboard;
      DEBUG2("note",pos);
      touchNote( pos,MIDI_VOL_FULL);
    }

    if ( (!found) && (inChar=='c') ) {
      found = true;
      DEBUG1("C - E - G");
      playSound(3,MIDI_VOL_FULL);
      playSound(7,MIDI_VOL_FULL);
      playSound(10,MIDI_VOL_FULL);
    }

    if ( (!found) && (inChar=='1') ) {
      found = true;
      DEBUG1("Clic1");
      playSound(NOTE_CLIC1,MIDI_VOL_FULL);
    }
    if ( (!found) && (inChar=='2') ) {
      found = true;
      DEBUG1("Clic2");
      playSound(NOTE_CLIC2,MIDI_VOL_FULL);
    }
    if ( (!found) && (inChar=='3') ) {
      found = true;
      DEBUG1("Note Error");
      playSound(NOTE_ERROR,MIDI_VOL_FULL);
    }

    if ( (!found) && (inChar=='v') ) {
      conf.volumeGen /= 2; 
      if (conf.volumeGen<5) conf.volumeGen=100;
      DEBUG2("volume:",conf.volumeGen);
    }
    if ( (!found) && (inChar=='m') ) {
      dumpSong();
    }
  }
}

#endif // DEBUG_KEYBOARD


//=======================================================================================================================
//
//  Functions for piezzo management
//
//=======================================================================================================================


//------------------------------------------------------------------------------------------------------------------------
/// @brief Read a analog value from MUX
/// @param channel  channel to read : 0->15
/// @return  0 -> 4095
uint16_t readAnalogFromMux(byte channel) 
{
  static byte channel_previous = 255;
  if (channel != channel_previous) {
    mux.channel(channel);  
    channel_previous = channel;
  }
  return analogRead(PIN_MUX_VAL);
}

//------------------------------------------------------------------------------------------------------------------------
/// @brief setup piezzo
void setupPiezzo()
{
  DEBUG1("setupPiezzo...")

  DEBUG3("analogSetPinAttenuation",PIN_MUX_VAL,conf.ADC_DB)
  // analogSetPinAttenuation(PIN_MUX_VAL,(adc_attenuation_t)conf.ADC_DB);
  
  DEBUG1("setupPiezzo OK.")
}


#define PIEZZO_NB_SCAN_MAX  50           // Nb of max scan to perform to read a piezzo
#define PIEZZO_SCAN_DELAI   250  

#define PIEZZO_VOID 100                 // no piezzo = undefined
unsigned long tloopScanPiezzoTS;        // meorized the time
uint8_t nbPiezzoHit = 0;                // Nb current hit piezzo

uint8_t lastPiezzoHit_0 = PIEZZO_VOID;  // slot 0 : no of hit piezzo
unsigned long lastPiezzoHitTS_0;        // slot 0 : timestamp of hit piezzo
uint8_t lastPiezzoHitNb_0;              // slot 0 : nb times piezzo has been hit

uint8_t lastPiezzoHit_1=PIEZZO_VOID;    // slot 1 : no of hit piezzo
unsigned long lastPiezzoHitTS_1;        // slot 1 : timestamp of hit piezzo
uint8_t lastPiezzoHitNb_1;              // slot 1 : nb times piezzo has been hit


//------------------------------------------------------------------------------------------------------------------------
/// @brief check if the value of a piezzo (first scan) is valid
/// @param i no of the piezzo
/// @param val value  
/// @return  true=valid, false=not valid
bool checkValidPiezzo(uint8_t i, uint16_t val)
{
  // Consider the piezzo only if above the threshold 
  if ( val < sounds[i].threshold )
    return false;

  // new hit but in a too short period regarding previous hit = boucing . Do not consider
  if (  (millis() - sounds[i].lastPressed) < conf.DELAY_PIEZZO_MIN  ) 
    return false;
  
  return true;
}



//------------------------------------------------------------------------------------------------------------------------
/// @brief Play the piezzo (send in queue)
/// @param pLastPiezzoHit no of the piezzo : resetted after play
/// @param pLastPiezzoHitTS  timestamp of the piezzo : resetted after play
/// @param pLastPiezzoHitNb nb times the piezzo has been already hit : resetted  after play
void playPiezzo(uint8_t * pLastPiezzoHit, unsigned long * pLastPiezzoHitTS, uint8_t * pLastPiezzoHitNb)
{

  uint8_t i = *pLastPiezzoHit;
 
  sounds[i].lastPressed = millis();

  // ------------------------------------------------------------------------------------
  // Log the hit piezzo
  // ------------------------------------------------------------------------------------
  DEBUG1("");
  DEBUG4("playPiezzo",i,sounds[i].lastPiezzoVal,sounds[i].lastPressed);

  logPiezzo[logPiezzoPos].ts = sounds[i].lastPressed;
  logPiezzo[logPiezzoPos].idxSound = i;
  logPiezzo[logPiezzoPos].value = sounds[i].lastPiezzoVal;

  logPiezzoPos++;
  if (logPiezzoPos>=NB_LOG_PIEZZO) {
    logPiezzoPos = 0;
  }


  // ------------------------------------------------------------------------------------
  // Compute velocity
  // ------------------------------------------------------------------------------------
  // Limit min 
  if (sounds[i].lastPiezzoVal < conf.PIEZZO_LEVEL_MIN) {
    sounds[i].lastPiezzoVal = conf.PIEZZO_LEVEL_MIN;
  }

  // Limit max
  if (sounds[i].lastPiezzoVal > conf.PIEZZO_LEVEL_MAX) {
    sounds[i].lastPiezzoVal = conf.PIEZZO_LEVEL_MAX;
  }
  
  // Compute velocity according to threshold min/max of the piezzo + volume min/max
  int velocity = map(sounds[i].lastPiezzoVal,conf.PIEZZO_LEVEL_MIN, conf.PIEZZO_LEVEL_MAX, conf.PIEZZO_VOLUME_MIN,127 );  


  // ------------------------------------------------------------------------------------
  // Send the note in the queue to be played : managed by another thread (call loopPlayPiezzo() to unqueue)
  // ------------------------------------------------------------------------------------
  T_Note  note;
  note.t0 = sounds[i].lastPressed;
  note.note = i;
  note.velocity = velocity;
  xQueueSend(queuePiezzo,&note,portMAX_DELAY);

  // ------------------------------------------------------------------------------------
  // Reset context
  // ------------------------------------------------------------------------------------
  sounds[i].lastPiezzoVal = 0;

  *pLastPiezzoHit = PIEZZO_VOID;
  *pLastPiezzoHitNb = 0;
  nbPiezzoHit--;
}


//------------------------------------------------------------------------------------------------------------------------
/// @brief check if the piezzo `pLastPiezzoHit`, already hit, has to be played
/// @param pLastPiezzoHit no of the piezzo
/// @param pLastPiezzoHitTS timestamp of the piezzo
/// @param pLastPiezzoHitNb nb times the piezzo has been already hit
/// @return 
bool checkHitPiezzo(uint8_t * pLastPiezzoHit, unsigned long * pLastPiezzoHitTS, uint8_t * pLastPiezzoHitNb)
{
  uint16_t val;
  bool toBePlayed=false;
  uint8_t i = * pLastPiezzoHit;

  if ( (i != PIEZZO_VOID) && ((tloopScanPiezzoTS-*pLastPiezzoHitTS)>=PIEZZO_SCAN_DELAI) ) {
    val = readAnalogFromMux(sounds[i].PINpiezzo);
    *pLastPiezzoHitTS = tloopScanPiezzoTS;
//DEBUG3("Piezzo Next ",i,val);

    // if the value is lower than the previous one : play the note ! 
    if ( val < sounds[i].lastPiezzoVal ) {
//DEBUG3("  to play",i,*pLastPiezzoHitNb)
      toBePlayed = true;
    } else {
      sounds[i].lastPiezzoVal = val;
      *pLastPiezzoHitNb =  *pLastPiezzoHitNb + 1;
      
      // if piezzo hit more than n times, play the note !
      if ( *pLastPiezzoHitNb >= PIEZZO_NB_SCAN_MAX ) {
 DEBUG3("  to play",i,"max")
        toBePlayed = true;
      }
    }

    if (toBePlayed) {
//DEBUG2("** DOPLAY 1;",millis());
      playPiezzo(pLastPiezzoHit,pLastPiezzoHitTS,pLastPiezzoHitNb);
//DEBUG2("** DOPLAY 2;",millis());
    }
    return true;
  }
  return false;
}




///------------------------------------------------------------------------------------------------------------------------
/// @brief check if any pressed piezzo. Executed by a dedicated thread
/// 
void loopScanPiezzo()
{
  
  static uint8_t i = NB_PIEZZO-1; // next piezzo to be read
  
  uint16_t val;
  tloopScanPiezzoTS = micros();

  /// ------ CODE TO ANALYSE CALL FREQUENCY : BEGIN
  // #define NB_TIMES 100
  // static unsigned long t0 = micros();
  // static unsigned long  duree = 0;
  // static unsigned long  nbTimes = 0;
  // static unsigned long  max = 0;

  // unsigned long last = micros();
  // nbTimes++;
  // duree += (last-t0);
  // if (nbTimes>=NB_TIMES) {
  //   duree = duree / NB_TIMES;
  //   if (duree>max) {
  //     DEBUG2("--call",duree);
  //     max = duree;
  //   }
  //   nbTimes = 0;
  //   duree = 0;
  // }
  /// ------ CODE TO ANALYSE CALL FREQUENCY : END

  // t0 = micros();
  
#ifdef CAPTURE_PIEZZO
  i=2; // = Note 'B', - to be changed if necessary
  val = readAnalogFromMux(sounds[i].PINpiezzo);

  // No sound ?
  if (piezzoPos==0)  {
    // Consider the piezzo only if above the threshold 
    if ( ! checkValidPiezzo(i,val) ) {
      return;
    }
    piezzoT0 = micros();
  }
  piezzoTime[piezzoPos] = micros();
  piezzoVal[piezzoPos] =val;

  piezzoPos++;

  if (piezzoPos>=PIEZZO_NB) {
    piezzoTF = micros();
    piezzoPos = 0;
    // Get the resultat with URL /capture
    // DEBUG2("DUREE: ",piezzoTF-piezzoT0);
    // for (int j=0; j<PIEZZO_NB; j++) {
    //   DEBUG1(piezzoVal[j]);
    // }
  }

  return;
#endif


  // ----------------------------------------------------------
  // check if piezzo already hit has to be played
  // ----------------------------------------------------------
  if  (nbPiezzoHit>0) {
    if ( checkHitPiezzo(&lastPiezzoHit_0, &lastPiezzoHitTS_0, &lastPiezzoHitNb_0) ) return;
    if ( checkHitPiezzo(&lastPiezzoHit_1, &lastPiezzoHitTS_1, &lastPiezzoHitNb_1) ) return;
  }


  // ----------------------------------------------------------
  // piezzo not already hit 
  // ----------------------------------------------------------
  i = (i+1) % NB_PIEZZO;
  val = readAnalogFromMux(sounds[i].PINpiezzo);

  // Consider the piezzo only if above the threshold 
  if ( ! checkValidPiezzo(i,val) ) 
    return;

  sounds[i].lastPressed = millis();

#ifdef TRACE_DELAI_HIT
  tsHit = millis() ;
#endif

  // Should not happen, but in any case : if 2 piezzos hit, play and free the oldest one
  if ( nbPiezzoHit >= 2 ) { 
    DEBUG2("Already 2 piezzo in // !!!",i);
    if  (lastPiezzoHitTS_0 < lastPiezzoHitTS_1) {
      playPiezzo(&lastPiezzoHit_0,&lastPiezzoHitTS_0,&lastPiezzoHitNb_0);
    } else {
      playPiezzo(&lastPiezzoHit_1,&lastPiezzoHitTS_1,&lastPiezzoHitNb_1);
    }
    nbPiezzoHit = 1;      
  }

  // get available piezzo slot, and memorized piezzo no, timestamp, and nb hit=1
  if (lastPiezzoHit_0==PIEZZO_VOID) {
    lastPiezzoHit_0 = i;
    lastPiezzoHitTS_0 = tloopScanPiezzoTS;
    lastPiezzoHitNb_0 = 1;
  } else {
    lastPiezzoHit_1 = i;
    lastPiezzoHitTS_1 = tloopScanPiezzoTS;
    lastPiezzoHitNb_1 = 1;
  }
  nbPiezzoHit++;
} 




//------------------------------------------------------------------------------------------------------------------------
/// @brief check if a note has to be played: check piezzo queue. executed by main thread
void loopPlayPiezzo()
{
  T_Note note;
  if (xQueueReceive(queuePiezzo, &note, 0) == pdPASS) {
    DEBUG3("** xQueueReceiv",note.note, note.velocity);
//DEBUG2("** loopPlayPiezzo;",millis());
    touchNote(note.note, note.velocity);
  }
}

//------------------------------------------------------------------------------------------------------------------------
/// @brief check if MIDI note should be NOTE OFF
void loopMidiMessage()
{
  static unsigned long lastLoopMidiMessage=0;
  unsigned long now = millis();

  MidiUsb.read();

  if ( (lastLoopMidiMessage+DELAY_LOOP_MIDI_MESSAGE) < now ) {
    lastLoopMidiMessage = now;
    for (int i=0; i<NB_SOUNDS; i++) {
      if ( (sounds[i].lastMidiMessage>0) && ((sounds[i].lastMidiMessage+DELAY_MIDI_MESSAGE) < now) ){
        sounds[i].lastMidiMessage = 0;
#ifdef MIDI_SEND
        DEBUG2("sendNoteOff",sounds[i].noteMidi);
        MidiUsb.sendNoteOff(sounds[i].noteMidi,0,1);
#endif
      }
    }
  }
 

}


//------------------------------------------------------------------------------------------------------------------------
/// @brief Get general volume 
void loopVolumeGen()
{
  static unsigned long timeLastVolume=0;
  unsigned long now = millis();
  if ( (timeLastVolume+DELAY_LOOP_VOLUMEGEN) < now ) {
    timeLastVolume = now;

    if (conf.POTENTIOMETER==1) {
      uint16_t val = analogRead(PIN_VOLUME);
      conf.volumeGen = map(val,0,4095,0,100);   
// DEBUG2("Volume",conf.volumeGen);
    } else {
      conf.volumeGen = 100;     
    }
    
  }
}


//------------------------------------------------------------------------------------------------------------------------
/// @brief Initialize / reset general config parameters
void initConfig()
{
  conf.volumeGen = 100;
  conf.testMode = false;
  logPiezzoPos = 0;
  for (int i=0 ; i<NB_PIEZZO; i++) {
    sounds[i].threshold = PIEZZO_THRESHOLD_DEF ;
  }
  
  for (int i=0; i<nbParameters; i++) {
    *(parameters[i].pValue) = parameters[i].def;
  }

  for (uint8_t i=0; i<NB_LOG_PIEZZO; i++) {
    logPiezzo[i].ts = 0;
    logPiezzo[i].idxSound = 0;
    logPiezzo[i].value = 0;
  }
}

void handleMIDINoteOn(byte channel, byte noteMidi, byte velocity)
{
  DEBUG3("handleMIDINoteOn",noteMidi,velocity);
  int idxSound = getSoundIndexByNote(noteMidi);
  if ( idxSound == NOTE_ERROR ) {
    return;
  }
  playSound(idxSound,velocity);
  HandLeftRight h =  getHandVelocity( velocity);  
  displayLED(idxSound, true, h);
}


void handleMIDINoteOff(byte channel, byte noteMidi, byte velocity)
{
  DEBUG3("handleMIDINoteOff",noteMidi,velocity);
  int idxSound = getSoundIndexByNote(noteMidi);
  if ( idxSound == NOTE_ERROR ) {
    return;
  }
  displayLED(idxSound, false, HandBoth);
}




void setupMIDI()
{
#ifdef MIDI_SEND
  DEBUG1("setupMIDI()...")

  TinyUSBDevice.setManufacturerDescriptor("PIO");
  TinyUSBDevice.setProductDescriptor(APPLI_MIDI_NAME);
  
  MidiUsb.setHandleNoteOn(handleMIDINoteOn);  
  MidiUsb.setHandleNoteOff(handleMIDINoteOff);
  MidiUsb.begin(MIDI_CHANNEL_OMNI);
#endif
}