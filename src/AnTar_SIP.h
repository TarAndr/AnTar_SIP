/*
 * AnTar_SIP.h - Simple indicator panel control library for Wiring/Arduino - Version 1.0
 *
 * MIT License
 * 
 * Copyright (c) 2023 Andrey Tarasenko
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

// ensure this library description is only included once
#ifndef AnTar_SimpleIndicatorPanel_h
#define AnTar_SimpleIndicatorPanel_h

// Following string need for common anode LED:
//#define COMMON_ANODE

// Constants:

#define LIBRARY_VERSION 1

// Number of LEDs:
#define LEDS_NUM 2

// Default buzzer frequency in Hz:
#define DEF_BUZ_FREQ 2222

// Determining signal parameters in accordance with its mode:

// shortBeep mode:
#define SHORT_BEEP_RED false	// Using the Red LED
#define SHORT_BEEP_GREEN true	// Using the Green LED
#define SHORT_BEEP_REPEAT 1		// Number of repetitions
#define SHORT_BEEP_DELAY 200	// Repetition duration

// lowPowerAlarm mode:
#define LOW_POWER_ALARM_RED true
#define LOW_POWER_ALARM_GREEN true
#define LOW_POWER_ALARM_REPEAT 3
#define LOW_POWER_ALARM_DELAY 200

// emptyPowerAlarm mode:
#define EMPTY_POWER_ALARM_RED true
#define EMPTY_POWER_ALARM_GREEN false
#define EMPTY_POWER_ALARM_REPEAT 4
#define EMPTY_POWER_ALARM_DELAY 400

// lockAlarm mode:
#define LOCK_ALARM_RED true
#define LOCK_ALARM_GREEN false
#define LOCK_ALARM_REPEAT 7
#define LOCK_ALARM_DELAY 650

// Signal mode enumerator:
enum signalMode {
	shortBeep = 0, 
	lowPowerAlarm, 
	emptyPowerAlarm, 
	lockAlarm, 
	modesNum	// this is to determine the number of modes
};

// Library interface description:
class SIP {
  public:
    // constructor:
    SIP(uint8_t red_led_pin, uint8_t green_led_pin, uint8_t buzzer_pin, uint16_t buzzer_freq = DEF_BUZ_FREQ);

    // main indication method:
    void signal(signalMode mode);

    // buzzer frequency setter method:
    void setBuzzerFreq(uint16_t buzzer_freq = DEF_BUZ_FREQ);

    // buzzer muting method:
    void mute(bool state);

	// Library shortened version
    uint8_t version(void);

  protected:
	// Red LED control:
    void redLed(uint8_t state);

	// Green LED control
    void greenLed(uint8_t state);

	// BUZZER control
    void beep(uint16_t duration);

    bool _silence = false;      // buzzer usage status
	uint16_t _buzzer_freq;		// buzzer frequency

	#ifdef COMMON_ANODE
	// Active levels for common anode LED
		const uint8_t ON = LOW;
		const uint8_t OFF = HIGH;
	#else
	// Active levels for common cathode LED
		const uint8_t ON = HIGH;
		const uint8_t OFF = LOW;
	#endif

    // panel pin numbers:
    uint8_t _red_led_pin;		// red LED pin
    uint8_t _green_led_pin;		// green LED pin
    uint8_t _buzzer_pin;		// BUZZER pin

	// LEDs usage map according to signal modes
	// {RED_LED,	GREEN_LED}
	const bool _ledUse[modesNum][LEDS_NUM] = {
		{SHORT_BEEP_RED, 		SHORT_BEEP_GREEN}, 
		{LOW_POWER_ALARM_RED, 	LOW_POWER_ALARM_GREEN}, 
		{EMPTY_POWER_ALARM_RED, EMPTY_POWER_ALARM_GREEN}, 
		{LOCK_ALARM_RED, 		LOCK_ALARM_GREEN}
	};

	// Array of number of repetitions according to signal modes
	const uint8_t _beepRepeat[modesNum] = {
		SHORT_BEEP_REPEAT,
		LOW_POWER_ALARM_REPEAT,
		EMPTY_POWER_ALARM_REPEAT,
		LOCK_ALARM_REPEAT
	};

	// Array of repetition durations according to signal modes
	const uint16_t _beepDelay[modesNum] = {
		SHORT_BEEP_DELAY,
		LOW_POWER_ALARM_DELAY,
		EMPTY_POWER_ALARM_DELAY, 
		LOCK_ALARM_DELAY
	};
	
/* 	struct SignalParams{
		uint16_t beepDelay;
		uint8_t beepRepeat;
		bool redLedUse;
		bool greenLedUse;
	};

	SignalParams signalMode[modesNum];

	signalMode[shortBeep].redLedUse = SHORT_BEEP_RED;
	signalMode[shortBeep].greenLedUse = SHORT_BEEP_GREEN;
	signalMode[shortBeep].beepRepeat = SHORT_BEEP_REPEAT;
	signalMode[shortBeep].beepDelay = SHORT_BEEP_DELAY; */
};

#endif
