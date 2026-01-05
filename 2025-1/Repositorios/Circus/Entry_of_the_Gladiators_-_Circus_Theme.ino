
// Can be moved in header file i.e notes.h
#define ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))
#define B5 988
#define Ab5 932
#define A5 880
#define Gb5 831
#define G5 784
#define Fb5 740
#define F5 698
#define E5 659
#define Db5 622
#define D5 587
#define C5 523
#define Cb5 554
#define Ab4 466
#define B4 494

const int midi1[148][3] = {
 {B5, 130, 130},
 {Ab5, 130, 130},
 {A5, 65, 65},
 {Ab5, 65, 65},
 {A5, 65, 65},
 {Gb5, 65, 65},
 {G5, 130, 130},
 {Fb5, 130, 130},
 {F5, 260, 0},
 {Fb5, 260, 0},
 {Gb5, 130, 130},
 {G5, 130, 130},
 {Fb5, 65, 65},
 {G5, 65, 65},
 {Fb5, 65, 65},
 {F5, 65, 65},
 {E5, 130, 130},
 {Db5, 130, 130},
 {D5, 260, 0},
 {Db5, 260, 0},
 {Fb5, 130, 130},
 {E5, 65, 65},
 {E5, 65, 65},
 {C5, 260, 0},
 {Cb5, 260, 0},
 {Fb5, 130, 130},
 {E5, 65, 65},
 {E5, 65, 65},
 {C5, 260, 0},
 {Cb5, 260, 0},
 {Ab4, 130, 0},
 {B4, 130, 0},
 {C5, 130, 0},
 {Cb5, 130, 0},
 {D5, 130, 0},
 {Db5, 130, 0},
 {E5, 130, 0},
 {F5, 130, 0},
 {Fb5, 130, 0},
 {G5, 130, 0},
 {Gb5, 130, 0},
 {Ab5, 130, 0},
 {Gb5, 260, 0},
 {Fb5, 260, 0},
 {B5, 130, 130},
 {Ab5, 130, 130},
 {A5, 65, 65},
 {Ab5, 65, 65},
 {A5, 65, 65},
 {Gb5, 65, 65},
 {G5, 130, 130},
 {Fb5, 130, 130},
 {F5, 260, 0},
 {Fb5, 260, 0},
 {Gb5, 130, 130},
 {G5, 130, 130},
 {Fb5, 65, 65},
 {G5, 65, 65},
 {Fb5, 65, 65},
 {F5, 65, 65},
 {E5, 130, 130},
 {Db5, 130, 130},
 {D5, 260, 0},
 {Db5, 260, 0},
 {D5, 260, 0},
 {D5, 65, 65},
 {D5, 65, 65},
 {F5, 260, 0},
 {Ab4, 260, 0},
 {Fb5, 65, 65},
 {Gb5, 65, 65},
 {Fb5, 65, 65},
 {F5, 65, 65},
 {Db5, 260, 0},
 {Ab4, 260, 0},
 {Ab5, 260, 0},
 {Ab5, 65, 65},
 {Ab5, 65, 65},
 {Ab5, 195, 65},
 {Ab5, 195, 65},
 {Ab5, 65, 65},
 {Ab5, 65, 65},
 {Ab5, 65, 65},
 {Ab5, 65, 65},
 {Ab5, 65, 65},
 {Ab5, 65, 65},
 {Ab5, 195, 0},
};

void playMidi(int pin, const int notes[][3], size_t len){
 for (int i = 0; i < len; i++) {
    tone(pin, notes[i][0]);
    delay(notes[i][1]);
    noTone(pin);
    delay(notes[i][2]);
  }
}
// Generated using https://github.com/ShivamJoker/MIDI-to-Arduino

// main.ino or main.cpp
void setup() {
  // put your setup code here, to run once:
  // play midi by passing pin no., midi, midi len
  // playMidi(11, midi1, ARRAY_LEN(midi1));
}

void loop() {
  // put your main code here, to run repeatedly:
  playMidi(10, midi1, ARRAY_LEN(midi1));
}
