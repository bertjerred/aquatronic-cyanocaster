/*********************************************************
This is a library for the MPR121 12-channel Capacitive touch sensor

Designed specifically to work with the MPR121 Breakout in the Adafruit shop 
  ----> https://www.adafruit.com/products/

These sensors use I2C communicate, at least 2 pins are required 
to interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.  
BSD license, all text above must be included in any redistribution
**********************************************************/

#include <Adafruit_MPR121.h>
#include <Tiny4kOLED.h>
#include <Wire.h>

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

Adafruit_MPR121 capA = Adafruit_MPR121();
Adafruit_MPR121 capB = Adafruit_MPR121();
Adafruit_MPR121 capC = Adafruit_MPR121();

uint16_t lasttouchedA = 0;
uint16_t currtouchedA = 0;
uint16_t lasttouchedB = 0;
uint16_t currtouchedB = 0;
uint16_t lasttouchedC = 0;
uint16_t currtouchedC = 0;

int outputJack = 2;
int note;
int noteDuration;
int delayMod;

int slider = A0;
int sliderVal;
int knob1 = A3;
int knob1Val;
int knob2 = A2;
int knob2Val;

int modeA = 11;
int modeAVal;
int modeB = 12;
int modeBVal;
int mode1 = 4;
int mode1Val;
int mode2 = 5;
int mode2Val;
int mode3 = 6;
int mode3Val;
int mode4 = 7;
int mode4Val;
int mode5 = 8;
int mode5Val;
int mode6 = 9;
int mode6Val;

int thirtySeven = 3;

void setup() {
  Serial.begin(9600);

  capA.begin(0x5A);
  capB.begin(0x5B);
  capC.begin(0x5C);

  pinMode(modeA, INPUT_PULLUP);
  pinMode(modeB, INPUT_PULLUP);

  pinMode(mode1, INPUT_PULLUP);
  pinMode(mode2, INPUT_PULLUP);
  pinMode(mode3, INPUT_PULLUP);
  pinMode(mode4, INPUT_PULLUP);
  pinMode(mode5, INPUT_PULLUP);
  pinMode(mode6, INPUT_PULLUP);

  oled.begin();
  oled.setFont(FONT6X8);
  oled.clear();
  oled.on();
}

void CalculateAudio(int note,
                    int noteDuration,
                    int modeAVal,
                    int modeBVal,
                    int mode1Val,
                    int mode2Val,
                    int mode3Val,
                    int mode4Val,
                    int mode5Val,
                    int mode6Val,
                    int delayMod,
                    int sliderVal) {
  int myArray[12];

  if (modeAVal == LOW) {
    if (mode1Val == LOW) {
      tone(outputJack, note);
    }
    else if (mode2Val == LOW) {

    }
    else if (mode3Val == LOW) {

    }
    else if (mode4Val == LOW) {

    }
    else if (mode5Val == LOW) {

    }
    else if (mode6Val == LOW) {

    }
  }

  else if (modeBVal == LOW) {
    if (mode1Val == LOW) {
      int myArray[16] = {1,1,4,4,9,9,16,16,25,25,36,36,49,49,64,64};
      for (byte i = 0; i <= 8; i = i + 1) {
        note = note + myArray[i];
        tone(outputJack, note+sliderVal, noteDuration);
        delay(delayMod);
      }
    }
    else if (mode2Val == LOW) {
      int myArray[16] = {16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
      for (byte i = 0; i <= 11; i = i + 1) {
        note = note + myArray[i];
        tone(outputJack, note, noteDuration);
        delay(delayMod);
      }
    }
    else if (mode3Val == LOW) {

    }
    else if (mode4Val == LOW) {

    }
    else if (mode5Val == LOW) {

    }
    else if (mode6Val == LOW) {

    }
  }
}

void Aftertouch(int note,
                int noteDuration,
                int modeAVal,
                int modeBVal,
                int mode1Val,
                int mode2Val,
                int mode3Val,
                int mode4Val,
                int mode5Val,
                int mode6Val,
                int delayMod,
                int sliderVal) {
  if (modeAVal == LOW) {
    if (mode1Val == LOW) {

    }
    else if (mode2Val == LOW) {

    }
    else if (mode3Val == LOW) {

    }
    else if (mode4Val == LOW) {

    }
    else if (mode5Val == LOW) {

    }
    else if (mode6Val == LOW) {

    }
  }
  if (modeBVal == LOW) {
    if (mode1Val == LOW) {

    }
    else if (mode2Val == LOW) {

    }
    else if (mode3Val == LOW) {

    }
    else if (mode4Val == LOW) {

    }
    else if (mode5Val == LOW) {

    }
    else if (mode6Val == LOW) {

    }
  }
  noTone(outputJack);
}

void loop() {
  noteDuration = 0;
  delayMod = 0;

  mode1Val = digitalRead(mode1);
  mode2Val = digitalRead(mode2);
  mode3Val = digitalRead(mode3);
  mode4Val = digitalRead(mode4);
  mode5Val = digitalRead(mode5);
  mode6Val = digitalRead(mode6);

  knob1Val = analogRead(knob1);
  knob2Val = analogRead(knob2);
  sliderVal = analogRead(slider);

  modeAVal = digitalRead(modeA);
  modeBVal = digitalRead(modeB);

  if (modeBVal == LOW) {
    noteDuration = map(knob2Val, 0, 800, 8, 100);
    delayMod = map(knob1Val, 0, 800, 8, 100);
    sliderVal = map(sliderVal, 0, 800, 0, 800);
  }
  else if (modeAVal == LOW) {
    //
  }

  currtouchedA = capA.touched();
  currtouchedB = capB.touched();
  currtouchedC = capC.touched();

  int note01 = 130; //C3  130.81
  int note02 = 139; //C#3 138.59
  int note03 = 147; //D3  146.83
  int note04 = 156; //D#3 155.56
  int note05 = 165; //E3  164.81
  int note06 = 175; //F3  174.61
  int note07 = 185; //F#3 185.00
  int note08 = 196; //G3  196.00
  int note09 = 208; //G#3 207.65
  int note10 = 220; //A3  220.00
  int note11 = 233; //A#3 233.08
  int note12 = 247; //B3  246.94
  int note13 = 262; //C4  261.63
  int note14 = 277; //C#4 277.18
  int note15 = 294; //D4  293.66
  int note16 = 311; //D#4 311.13
  int note17 = 330; //E4  329.63
  int note18 = 349; //F4  349.23
  int note19 = 370; //F#4 369.99
  int note20 = 392; //G4  392.00
  int note21 = 415; //G#4 415.30
  int note22 = 440; //A4  440.00
  int note23 = 466; //A#4 466.16
  int note24 = 494; //B4  493.88
  int note25 = 523; //C5  523.25
  int note26 = 554; //C#5 554.37
  int note27 = 587; //D5  587.33
  int note28 = 622; //D#5 622.25
  int note29 = 659; //E5  659.25
  int note30 = 698; //F5  698.46
  int note31 = 740; //F#5 739.99
  int note32 = 784; //G5  783.99
  int note33 = 831; //G#5 830.61
  int note34 = 880; //A5  880.00
  int note35 = 932; //A#5 932.33
  int note36 = 988; //B5  987.77
  int note37 = 1047;//C6 1046.50

  for (uint8_t i = 0; i < 12; i++) {
    if ((currtouchedA & _BV(i)) && !(lasttouchedA & _BV(i)) ) {
      if (i == 0)       {
        note = note01;
      }
      else if (i == 1)  {
        note = note02;
      }
      else if (i == 2)  {
        note = note03;
      }
      else if (i == 3)  {
        note = note04;
      }
      else if (i == 4)  {
        note = note05;
      }
      else if (i == 5)  {
        note = note06;
      }
      else if (i == 6)  {
        note = note07;
      }
      else if (i == 7)  {
        note = note08;
      }
      else if (i == 8)  {
        note = note09;
      }
      else if (i == 9)  {
        note = note10;
      }
      else if (i == 10) {
        note = note11;
      }
      else if (i == 11) {
        note = note12;
      }
      CalculateAudio(note,
                     noteDuration,
                     modeAVal,
                     modeBVal,
                     mode1Val,
                     mode2Val,
                     mode3Val,
                     mode4Val,
                     mode5Val,
                     mode6Val,
                     delayMod,
                     sliderVal);
    }
    if (!(currtouchedA & _BV(i)) && (lasttouchedA & _BV(i)) ) {
      Aftertouch(note,
                 noteDuration,
                 modeAVal,
                 modeBVal,
                 mode1Val,
                 mode2Val,
                 mode3Val,
                 mode4Val,
                 mode5Val,
                 mode6Val,
                 delayMod,
                 sliderVal);
    }
    if ((currtouchedB & _BV(i)) && !(lasttouchedB & _BV(i)) ) {
      if (i == 0) {
        note = note13;
      }
      else if (i == 1)  {
        note = note14;
      }
      else if (i == 2)  {
        note = note15;
      }
      else if (i == 3)  {
        note = note16;
      }
      else if (i == 4)  {
        note = note17;
      }
      else if (i == 5)  {
        note = note18;
      }
      else if (i == 6)  {
        note = note19;
      }
      else if (i == 7)  {
        note = note20;
      }
      else if (i == 8)  {
        note = note21;
      }
      else if (i == 9)  {
        note = note22;
      }
      else if (i == 10) {
        note = note23;
      }
      else if (i == 11) {
        note = note24;
      }
      CalculateAudio(note,
                     noteDuration,
                     modeAVal,
                     modeBVal,
                     mode1Val,
                     mode2Val,
                     mode3Val,
                     mode4Val,
                     mode5Val,
                     mode6Val,
                     delayMod,
                     sliderVal);
    }
    if (!(currtouchedB & _BV(i)) && (lasttouchedB & _BV(i)) ) {
      Aftertouch(note,
                 noteDuration,
                 modeAVal,
                 modeBVal,
                 mode1Val,
                 mode2Val,
                 mode3Val,
                 mode4Val,
                 mode5Val,
                 mode6Val,
                 delayMod,
                 sliderVal);
    }
    if ((currtouchedC & _BV(i)) && !(lasttouchedC & _BV(i)) ) {
      if (i == 0) {
        note = note25;
      }
      else if (i == 1)  {
        note = note26;
      }
      else if (i == 2)  {
        note = note27;
      }
      else if (i == 3)  {
        note = note28;
      }
      else if (i == 4)  {
        note = note29;
      }
      else if (i == 5)  {
        note = note30;
      }
      else if (i == 6)  {
        note = note31;
      }
      else if (i == 7)  {
        note = note32;
      }
      else if (i == 8)  {
        note = note33;
      }
      else if (i == 9)  {
        note = note34;
      }
      else if (i == 10) {
        note = note35;
      }
      else if (i == 11) {
        note = note36;
      }
      CalculateAudio(note,
                     noteDuration,
                     modeAVal,
                     modeBVal,
                     mode1Val,
                     mode2Val,
                     mode3Val,
                     mode4Val,
                     mode5Val,
                     mode6Val,
                     delayMod,
                     sliderVal);
    }
    if (!(currtouchedC & _BV(i)) && (lasttouchedC & _BV(i)) ) {
      Aftertouch(note,
                 noteDuration,
                 modeAVal,
                 modeBVal,
                 mode1Val,
                 mode2Val,
                 mode3Val,
                 mode4Val,
                 mode5Val,
                 mode6Val,
                 delayMod,
                 sliderVal);
    }
  }
  lasttouchedA = currtouchedA;
  lasttouchedB = currtouchedB;
  lasttouchedC = currtouchedC;
  return;
}
