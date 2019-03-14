/* Buttons to USB MIDI & MIDI over serial Example

   You must select MIDI from the "Tools > USB Type" menu

   To view the raw MIDI data on Linux: aseqdump -p "Teensy MIDI"

   This example code is in the public domain.
*/

#include <Bounce.h>
#include <MIDI.h>

// the MIDI channel number to send messages
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
const int channel = 16;

// Create an array to hold the Bounce Objects.
int buttonCount = 7;
Bounce buttons[] = {
  Bounce(0, 5),
  Bounce(1, 5),
  Bounce(2, 5),
  Bounce(3, 5),
  Bounce(4, 5),
  Bounce(5, 5),
  Bounce(6, 5),
};

void setup() {

  MIDI.begin();
  Serial.begin(31250);
  Serial.println("MIDI Input Test");
  
  // Configure the pins for input mode with pullup resistors.
  // The pushbuttons connect from each pin to ground.  When
  // the button is pressed, the pin reads LOW because the button
  // shorts it to ground.  When released, the pin reads HIGH
  // because the pullup resistor connects to +5 volts inside
  // the chip.  LOW for "on", and HIGH for "off" may seem
  // backwards, but using the on-chip pullup resistors is very
  // convenient.  The scheme is called "active low", and it's
  // very commonly used in electronics... so much that the chip
  // has built-in pullup resistors!
  
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);  // Teensy++ 2.0 LED, may need 1k resistor pullup
}

void loop() {

  // Update all the buttons.  There should not be any long
  // delays in loop(), so this runs repetitively at a rate
  // faster than the buttons could be pressed and released.
  
  for (int i = 0; i < buttonCount; i++) {
    buttons[i].update();

    // Check each button for "falling" edge.
    // Send a MIDI Note On message when each button presses
    // Update the Joystick buttons only upon changes.
    // falling = high (not pressed - voltage from pullup resistor)
    //           to low (pressed - button connects pin to ground)
    
    if (buttons[i].fallingEdge()) {
      usbMIDI.sendProgramChange(i, channel);  // 60 = C4
      MIDI.sendProgramChange(i, channel);  // 60 = C4
    }
    
    if (buttons[i].risingEdge()) {
      //usbMIDI.sendNoteOff(60 + i, 99, channel);  // 60 = C4
      //MIDI.sendNoteOff(60 + i, 99, channel);  // 60 = C4
    }
  }
}
