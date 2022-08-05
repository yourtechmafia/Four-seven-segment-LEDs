//  IDE constants. 74HC595 shift register pinout
#define button 13
#define clockPin 3
#define dataPin 2
#define latchPin 1

const int segmentBits[] = {252, 96, 218, 242, 102, 182, 190, 224, 254, 246};
int counter;
byte units;
byte tens;

void setup() {
  pinMode(button, INPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  setCounter();
}

void loop() {
  while (digitalRead(button) == HIGH) { //  Press button to increase count
    counter++;  //  Increase the counter for display
    if (counter > 99) counter = 0; //  Counter is less than 100
    setCounter();
  }
}

void setCounter() {
  tens = (counter / 10) % 10;
  units = counter % 10;
  digitalWrite(latchPin, 0); //  Turn off the latch pin
  //  Shift out the data into the shift registers
  shiftOut(dataPin, clockPin, LSBFIRST, segmentBits[tens] );
  shiftOut(dataPin, clockPin, LSBFIRST, segmentBits[units] );
  //  Turn on the latch pin
  digitalWrite(latchPin, 1);
}
