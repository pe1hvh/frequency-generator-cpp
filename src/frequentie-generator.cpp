/**********************************************************************************************************
  10kHz to 225MHz VFO / RF Generator with Si5351 and Arduino Nano, with Intermediate
  Frequency (IF) offset (+ or -), RX/TX Selector for QRP Transceivers, Band Presets
  and Bargraph S-Meter.  Based on source made by J. CesarSound - ver 2.0 - Feb/2021.
  
  Forked by JA van Hernen
   - re-code: standard lowerCamelCase nameconvention
   - standard indentation
   - standard formating
   - cleancode (so far as possible)
   - comment code.

  Version 3.0 december 2024
   - complete new redesign in OO (where posible)
***********************************************************************************************************/
#include <Wire.h>                  // Allows the communication between devices or sensors connected via Two Wire Interface Bus. Specific implementation for nRF52. This Library is needed for si5341 https://docs.arduino.cc/language-reference/en/functions/communication/Wire/
#include <Rotary.h>                // Arduino library for reading rotary directions that output a 2-bit gray code. Ben  Buxton https://github.com/brianlow/Rotary
#include <si5351.h>                // A full-featured library for the Si5351 series of clock generator ICs from Silicon Labs  https://github.com/etherkit/Si5351Arduino

//User librarys
#include "maintain-data.h"         // Set the varaibles activated by the buttons and analogreads 
#include "display-handler.h"       // Display class maintain the output to LCD screen  
#include "rotary-handler.h"        // Handles the Interrupts used by the rotary
#include "input-handler.h"         // Handles the Buttons
#include "si5351-handler.h"        // Handles the si5351  


/******************************************************************************/
/*! @brief  inital ssd1305
            set the initial pins
            set start text
            inital the si5351
*/
/******************************************************************************/
void setup() {
  
  MyDisplay::displayManager.init();
  MyDisplay::displayManager.setStartupText(); //If you hang on startup, comment
  MyData::dataManager.init();
  initRotary();
  initButtonRxTx();
  initButtonTuneStep();
  initButtonBandSelector();

  MySi5251::si5251Manager.init();
                             
}

/***********************************************************************************/
/*! @brief  if the buttons touch or rotary turn new frequencies etc will be set    */
/***********************************************************************************/
void loop() {
  
  MyDisplay::displayManager.setTimeNow(); 
 
  readSignalMeterADC();
  checkButtonRxTx();
  checkButtonTuneStep();
  checkButtonBandSelector(); 

  MySi5251::si5251Manager.checkSi5251Changes( MyData::dataManager.getFrequency(),
                                              MyData::dataManager.getInterFrequency() );

  MyDisplay::displayManager.setScreen(  
                                          MyData::dataManager.getTuneStepValue(), 
                                          MyData::dataManager.getInterFrequency(), 
                                          MyData::dataManager.getFrequency(),
                                          MyData::dataManager.getBandSelector(),
                                          MyData::dataManager.getRxTxSwitch(), 
                                          MyData::dataManager.getTunePointer(), 
                                          MyData::dataManager.getSignalMeterRemap() );
}
//EOF
