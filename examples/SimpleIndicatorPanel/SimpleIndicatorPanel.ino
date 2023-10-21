/*
 * Simple Indicator Panel
 *
 * Cyclic playback of all signal modes
 *
 * https://github.com/TarAndr/AnTar_SIP
 * This example code is in the public domain.
 */

#include <AnTar_SIP.h>

// Pin numbers:
const int redLedPin = 13;
const int greenLedPin = 12;
const int buzzerPin = A2;
const long buzzerFreq = 3000;

// create an instance of the panel class, specifying
// the pins it's attached to and/or buzzer frequency
SIP lockPanel(redLedPin, greenLedPin, buzzerPin, buzzerFreq);

// without set frequency (with default value):
//SIP lockPanel(redLedPin, greenLedPin, buzzerPin);

void setup() {
  // set the frequency of the buzzer to 3000 Hz
  //lockPanel.setBuzzerFreq(buzzerFreq);
}

void loop() {
  // switching modes
	for(int mode = shortBeep; mode < modesNum; ++mode) {
		lockPanel.signal(signalMode(mode));
		delay(1000);
	}
	delay(1000);
}
