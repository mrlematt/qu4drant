/* some code designed for using the Teensy 3 as a USB MIDI controller
v1.0, December 17 2013
by Yann Seznec www.yannseznec.com

modified by Matthieu Pernaud for teensy 3.1 and for different purposes:

use of all 12 touch pins to send midi notes.
use of all analog pins available.
use of digital pins to send notes.

no copyright or anything, use however you want

remember to select MIDI as your USB Type in the Tools menu

this should also work with other Teensy boards, apart from the "touch" pins

things that are kind of dumb in this code:
- the touch threshold is hard coded (int touchThreshold)
- touch pins only send midi note on/off with no velocity change
- no system for sending touch pin as CC
- the CC assignments are sort of random, probably should have another array for them

*/

/* MIDI CHANNEL 5 C1-B1 Analog inputs from 50 */

/* TOUCHPINS - send midi notes */

int const numTouchPins = 12; // number of pins to use as touchpins, sending note values
int touch[numTouchPins];
int touchon[numTouchPins];
int touchpin[] = {
  0,1,15,16,17,18,19,22,23,25,32,33}; // which digital pins to use as touch pins
  int touchpitch[] = {
  36,37,38,39,40,41,42,43,44,45,46,47}; // MIDI pitches
  int touchThreshold = 2255; 
  int touchMax = 3000; 

/*ANALOG PINS*/

int const numPins = 8; //  number of analog inputs 
int currentVal[numPins];
int newVal[numPins];
int analogPins[] = {  
A10,A11,A12,A13,A14,A15,A16,A17   // which analog pins to use 
};
int analogstartcc = 50; // MIDI CC number to start from.



int const numDigPins = 0; // number of digital pins to send note values
int currentDig[numDigPins];
int digitalpin[] = {
  2,3,4,5,6,7    // which digital pins to use for sending note values
};
int digitalpitch[] = {
  48,50,51,53,55,57}; // which midi notes to send from the digital pins selected above
int digInput[numDigPins];


int const numDigPinsCC = 4; // number of digital pins to send CC
int currentDigcc[numDigPinsCC];
int digitalpincc[] = {
   10,11,12,24 // which digital pins to use for sending CC
};
int digccstart = 10; // CC number to start from

int digInputcc[numDigPinsCC];





// the MIDI channel number to send messages
const int channel = 1;



void setup() {
  
//  pinMode(2, INPUT_PULLUP);
//  pinMode(3, INPUT_PULLUP);
//  pinMode(4, INPUT_PULLUP);
//  pinMode(5, INPUT_PULLUP);
//  pinMode(6, INPUT_PULLUP);  
//  pinMode(7, INPUT_PULLUP);
//  pinMode(8, INPUT_PULLUP);
//  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP); 
  pinMode(24, INPUT_PULLUP);

  Serial.begin(38400);

}

void loop() {
  
  
  //  touch sending notes
  
  for (int i = 0; i < numTouchPins; i++) {
    touch[i] = touchRead(touchpin[i]); 

    if (touch[i] > touchThreshold && touchon[i] == 0) {
      usbMIDI.sendNoteOn(touchpitch[i], 100, channel);
      touchon[i] = 1;
    }
    if (touch[i] < touchThreshold && touchon[i] == 1) {
          usbMIDI.sendNoteOff(touchpitch[i], 100, channel);
          touchon[i] = 0;
    }

/*  touchpads
  for (int i = 0; i < numTouchPins; i++) {
    touch[i] = touchRead(touchpin[i]); 

    if (touch[i] > touchThreshold && touchon[i] == 0) {
usbMIDI.sendControlChange(i+25,map(touch[i], touchThreshold, touchMax, 0, 127),4);
      touchon[i] = 1;
    }
    if (touch[i] < touchThreshold && touchon[i] == 1) {
usbMIDI.sendControlChange(i+25,0,4);
      touchon[i] = 0;
    }

  }
  
  */
 

// digital pins sending notes
//  for (int i = 0; i < numDigPins; i++) {
//    if (digitalRead(digitalpin[i]) == 1 && currentDig[i] == 0) {
//      usbMIDI.sendNoteOff(digitalpitch[i], 100, channel); 
//      currentDig[i] = 1;
//    }  
//    if (digitalRead(digitalpin[i]) == 0  && currentDig[i] == 1) {
//      usbMIDI.sendNoteOn(digitalpitch[i], 100, channel);
//      currentDig[i] = 0;
//    }  
//  }

  //// digital pins sending CC

  for (int i = 0; i < numDigPinsCC; i++) {
    if (digitalRead(digitalpincc[i]) == 1 && currentDigcc[i] == 0) {
      usbMIDI.sendControlChange(i+digccstart, 127, channel); 
      currentDigcc[i] = 1;
    }  
    if (digitalRead(digitalpincc[i]) == 0  && currentDigcc[i] == 1) {
      usbMIDI.sendControlChange(i+digccstart, 0, channel);
      currentDigcc[i] = 0;
    }  
  }

//// analog pins

  for (int i = 0; i < numPins; i++) {

    newVal[i] = analogRead(analogPins[i]);
    
    if (abs(newVal[i] - currentVal[i])>10) 
     // if (newVal[i] >> 5)
    {
      usbMIDI.sendControlChange(i+analogstartcc, newVal[i]>>3, channel); 
      currentVal[i] = newVal[i];
    }  
    
   //  else if (newVal[i] <5)
   //  { 
   //    usbMIDI.sendControlChange(i+analogstartcc, 0, channel); 
   //   currentVal[i] = newVal[i];
   //     }
  }
  
  // i think if you remove these last two lines everything breaks and things are sad and people cry
  while (usbMIDI.read()); // read and discard any incoming MIDI messages
  delay(5); 
}

}
