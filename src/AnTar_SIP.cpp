/*
 * AnTar_SIP.cpp - Simple indicator panel control library for Wiring/Arduino - Version 1.0
 *
 * The circuits can be found at
 *
 * https://github.com/TarAndr/AnTar_SIP
 */

#include "Arduino.h"
#include "AnTar_SIP.h"

/*
 *   constructor
 *   Sets which wires should control the panel.
 */
SIP::SIP(uint8_t red_led_pin, uint8_t green_led_pin, uint8_t buzzer_pin, uint16_t buzzer_freq)
{
  this->_red_led_pin = red_led_pin;    		// pin for red LED
  this->_green_led_pin = green_led_pin;    	// pin for green LED
  this->_buzzer_pin = buzzer_pin;    		// pin for buzzer
  this->_buzzer_freq = buzzer_freq;    		// buzzer frequency

  // setup the pins on the microcontroller:
  pinMode(this->_red_led_pin, OUTPUT);
  pinMode(this->_green_led_pin, OUTPUT);
  pinMode(this->_buzzer_pin, OUTPUT);
}

/* 
 *	Control of the red LED
 */
void SIP::redLed(uint8_t state)
{
	digitalWrite(this->_red_led_pin, state);
}

/* 
 *	Control of the green LED
 */
void SIP::greenLed(uint8_t state)
{
	digitalWrite(this->_green_led_pin, state);
}

/* 
 *	Control of the BUZZER
 */
void SIP::beep(uint16_t duration)
{
	if(this->_silence) return;
	tone(this->_buzzer_pin, this->_buzzer_freq, duration);
}

/* 
 *	Sets the resonant frequency of the buzzer being used or changes the frequency during operation
 */
void SIP::setBuzzerFreq(uint16_t buzzer_freq)
{
	this->_buzzer_freq = buzzer_freq;
}

/* 
 *	Turn the buzzer sound mute or unmute. If option is mute then beeper will stop immediately
 */
void SIP::mute(bool state)
{
	if(state) noTone(this->_buzzer_pin);
	this->_silence = state;
}

/* 
 *	The method returns the shortened version of the library
 */
uint8_t SIP::version(void)
{
	return LIBRARY_VERSION;
}

/* 
 *	Main method for panel control
 */
void SIP::signal(signalMode mode)
{
	if(mode >= modesNum) return;
	for(int i = 0; i < this->_beepRepeat[mode]; ++i) {
		this->beep(this->_beepDelay[mode]);
		if(this->_ledUse[mode][0]) redLed(this->ON);
		if(this->_ledUse[mode][1]) greenLed(this->ON);
		delay(this->_beepDelay[mode]);
		if(this->_ledUse[mode][0]) redLed(this->OFF);
		if(this->_ledUse[mode][1]) greenLed(this->OFF);
		delay(this->_beepDelay[mode] / 2);
	}
}
