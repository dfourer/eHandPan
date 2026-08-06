//=======================================================================================================================
///
/// @file main.cpp
/// 
/// Main programm file
/// 
/// @author Eric GENOTELLE
/// @date 2024
/// 
///=======================================================================================================================

//------------------------------------------------------------------------------------------------------------------------
// Includes
#include "arduino.h"
#include "driver/i2s.h"                       // Library of I2S routines, comes with ESP32 standard install
#include "tools.h"

#include "config.h"
#include "sound.h"
#include "web.h"
#include "device.h"
#include "global.h"



// void loop_pan()
// {    
//   loopKeyboard();                                                
//   loopPiezzo();
//   loopVolumeGen();
//   loopSong();
//   loopSong(); // recheck for double note
//   loopLED();
//   loopPlayWaves();
//   loopWeb();
// }



void taskScanPiezzo(void * pvParameters) 
{
  while(1) {
    loopScanPiezzo();
  }
  
}
 
// void taskMain(void * pvParameters) {
//   while (1) {
//     loopKeyboard();                                                
//     loopPlayPiezzo();
//     loopVolumeGen();
//     loopSong();
//     loopSong(); // recheck for double note
//     loopLED();
//     loopPlayWaves();
// //    loopWeb();
//   }
// }


//====================================================================================
/// @brief  SETUP for ESP32
void setup() 
{
#ifdef DEBUGAPP  
  Serial.begin(115200);     
  while (! Serial);
#endif
  delay(300);

  DEBUG1("SETUP...");
  setupDevices();
  setupSounds();
  resetAllNotesPoly();
  setupSong();
  setupWeb();

  if (conf.isDemoLed) {
    demoLED();
  }
  DEBUG2("Nb parameters", nbParameters);

  DEBUG2("CORE ID:",xPortGetCoreID());

  queuePiezzo = xQueueCreate(5, sizeof(T_Note));
  DEBUG1("queuePiezzo OK")

  // Create a dedicated task to scan Piezze : not to be interrupted by I2S process
  xTaskCreatePinnedToCore(
    taskScanPiezzo,     // Task function
    "Task ScanPiezzo",      // Name of the task
    4000,          // Stack size (in words, not bytes)
    NULL,          // Task input parameter
    1,             // Priority of the task (higher priority)
    &thScanPiezzo,        // Task handle
    1);            // Core to run the task on 
  DEBUG1("taskScanPiezzo OK")

  // Display GREEN internal LED when ready
  iled_color(false,true,false);
  delay(400);
  iled_off();

  DEBUG1("setup OK.");

}


//====================================================================================
///
/// @brief  LOOP for ESP32
void loop() 
{
#ifdef DEBUG_KEYBOARD
  loopKeyboard();      
#endif                                          
  loopPlayPiezzo();
  loopVolumeGen();
  loopSong();
  loopSong(); // recheck for double note
  loopLED();
  loopPlayWaves();
  loopWeb();
#ifdef MIDI_SEND
  loopMidiMessage();
#endif
}
