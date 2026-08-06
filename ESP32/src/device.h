///=======================================================================================================================
///
/// @file device.h
/// 
/// Header file for devices management (i2s excluded): LED, piezzo, EEPROM, Keyboard (debug)
/// 
/// @author Eric GENOTELLE
/// @date 2024
///
///=======================================================================================================================

#pragma once

#include "sound.h"


void setupDevices();

void setupEEPROM();
void readConfigEEPROM();
void saveConfigEEPROM();
void resetConfigEEPROM();

void setupLED();
void demoLED();
void displayLED(int idxSound, bool on, HandLeftRight hand);
void loopLED();

void iled_color(uint8_t r, uint8_t g, uint8_t b);
void iled_off();

void setupPiezzo();
void touchNote(int noteMidi, int velocity );

void setupMIDI();

#ifdef DEBUG_KEYBOARD
void loopKeyboard();
#endif

void loopScanPiezzo();
void loopPlayPiezzo();
void loopMidiMessage();
void loopVolumeGen();

void initConfig();