#define TGA_PRO_REVB
#define TGA_PRO_EXPAND_REV2

#include "BALibrary.h"

using namespace BALibrary;

// Create physical controls for Expansion Board, 2 switches, 3 pots, 0 encoders, 2 LEDs
BAPhysicalControls controls(BA_EXPAND_NUM_SW, BA_EXPAND_NUM_POT, 0, BA_EXPAND_NUM_LED);

void setup() {
  delay(100);
  Serial.begin(57600);
  delay(500); // long delay to wait for Serial to init
  
  // put your setup code here, to run once:
  Serial.println("Calibrating POT1");
  Potentiometer::Calib pot1Calib = Potentiometer::calibrate(BA_EXPAND_POT1_PIN);
  if (pot1Calib.min == pot1Calib.max) { Serial.println("\n!!! The knob didn't appear to move. Are you SURE you're turning the right knob? !!!"); }
  
  Serial.println("\nCalibrating POT2");
  Potentiometer::Calib pot2Calib = Potentiometer::calibrate(BA_EXPAND_POT2_PIN);
  if (pot2Calib.min == pot2Calib.max) { Serial.println("\n!!! The knob didn't appear to move. Are you SURE you're turning the right knob? !!!"); }
  
  Serial.println("\nCalibrating POT3");
  Potentiometer::Calib pot3Calib = Potentiometer::calibrate(BA_EXPAND_POT3_PIN);
  if (pot3Calib.min == pot3Calib.max) { Serial.println("\n!!! The knob didn't appear to move. Are you SURE you're turning the right knob? !!!"); }

  // Create the controls using the calib values
  controls.addPot(BA_EXPAND_POT1_PIN, pot1Calib.min, pot1Calib.max, pot1Calib.swap);
  controls.addPot(BA_EXPAND_POT2_PIN, pot2Calib.min, pot2Calib.max, pot2Calib.swap);
  controls.addPot(BA_EXPAND_POT3_PIN, pot3Calib.min, pot3Calib.max, pot3Calib.swap);

  // Add the pushbuttons
  controls.addSwitch(BA_EXPAND_SW1_PIN);
  controls.addSwitch(BA_EXPAND_SW2_PIN);

  // Setup the LEDs
  controls.addOutput(BA_EXPAND_LED1_PIN);
  controls.setOutput(BA_EXPAND_LED1_PIN, 0);
  controls.addOutput(BA_EXPAND_LED2_PIN);
  controls.setOutput(BA_EXPAND_LED2_PIN, 0);

  Serial.println("DONE SETUP! Try turning knobs and pushing buttons!\n");

}

void loop() {
  // put your main code here, to run repeatedly:
  float value;
  for (unsigned i=0; i<BA_EXPAND_NUM_POT; i++) {
    if (controls.checkPotValue(i, value)) {
      Serial.println(String("POT") + (i+1) + String(" new value: ") + value);
    }
  }

  // Check pushbuttons
  for (unsigned i=0; i<BA_EXPAND_NUM_SW; i++) {
    if (controls.isSwitchToggled(i)) {
      Serial.println(String("Button") + (i+1) + String(" pushed!"));
      controls.toggleOutput(i);
    }
  }

  delay(10);

}
