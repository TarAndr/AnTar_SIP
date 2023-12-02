/*
 * Simple Indicator Panel
 *
 * Cyclic playback of all signal modes
 *
 * https://github.com/TarAndr/AnTar_SIP
 * This example code is in the public domain.
 */

// Connecting the library
#include <AnTar_SIP.h>

// Pin numbers:
const int redLedPin = 13;
const int greenLedPin = 12;
const int buzzerPin = A2;
const long buzzerFreq = 4400;

// create an instance of the panel class, specifying
// the pins it's attached to and/or buzzer frequency
SIP myPanel(redLedPin, greenLedPin, buzzerPin, buzzerFreq);

// without frequency setting (with default value):
//SIP myPanel(redLedPin, greenLedPin, buzzerPin);

void setup() {
  // setting the buzzer frequency to 4400 Hz
  //myPanel.setBuzzerFreq(buzzerFreq);

  // Setting the default buzzer frequency
  //myPanel.setBuzzerFreq();
}

void loop() {
  // switching modes
	for(int mode = shortBeep; mode < modesNum; ++mode) {
		myPanel.signal(mode);
		delay(1000);
	}
	delay(2000);
}
