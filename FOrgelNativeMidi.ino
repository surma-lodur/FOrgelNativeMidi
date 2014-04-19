#include <Neutron.h>
#include <PulsR.h>
#include <Harmonic.h>
#include <MIDI.h>


void setup() {
  MIDI.begin();           // Launch MIDI, by default listening to channel 1.
  Harmonic::calculate(0);
  PulsR::add(new  PulsR::Neutron(2));
  PulsR::add(new  PulsR::Neutron(3));
  PulsR::add(new  PulsR::Neutron(4));
}


void loop() {
  if (MIDI.read()) {
    switch (MIDI.getType()) {
      case midi::NoteOn:       
        PulsR::pulses(
          noteToMicros(MIDI.getData1())
        );
        break;
      case midi::NoteOff:      
        PulsR::collapse(
          noteToMicros(MIDI.getData1())
        );
        break;
        // See the online reference for other message types
      default:
        break;
    }
  }
  PulsR::rotate();
}

long noteToMicros(char note) {
  return ((60 / Harmonic::NOTES[note] ) * 100000 ) / 2;
}

