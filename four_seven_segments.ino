//  IDE constant
#define button_One 11
#define button_Two 12
//  Shift registers pinout - 4 shift registers (74HC595)
#define latchPin 5
#define dataPin 6
#define clockPin 7

const int segmentBits[] = {252, 96, 218, 242, 102, 182, 190, 224, 254, 246};
byte thousands, hundreds, tens, units;
int counts = 0;

void setup() {
  pinMode(button_One, INPUT);
  pinMode(button_Two, INPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  setCounter();
}

void loop() {
  if (digitalRead(button_One)) {  //  A button to increase count
    if (counts >= 9999) counts = 9999;  //  Maximum counts to be displayed
    else  counts++; //  Else increase the counter
    //  Comment this to run many counters if button is held for too long
    //  Because this ensures one counter increment per button press.
    while (digitalRead(button_One));
  } else if (digitalRead(button_Two)) {  //  A button to decrease count
    if (counts <= 0) counts = 0;  //  Count can't be less than 0
    else  counts--;
    while (digitalRead(button_Two));
  }
  setCounter(); //  Roll out the new count
}

/* If there are new shift registers to be added, you can add a new variable,
 *  e.g. (ten_thousand = (counts / 10000) % 10; and also
 *  shiftOut(dataPin, clockPin, LSBFIRST, segmentBits[ten_thousand]);
 */
void setCounter() {
  thousands = (counts / 1000) % 10;
  hundreds = (counts / 100) % 10;
  tens  = (counts / 10) % 10;
  units = (counts / 1) % 10;
  digitalWrite(latchPin, LOW); //  Turn off the latch pin
  //  Shift out the data into the shift registers
  shiftOut(dataPin, clockPin, LSBFIRST, segmentBits[thousands] );
  shiftOut(dataPin, clockPin, LSBFIRST, segmentBits[hundreds] );
  shiftOut(dataPin, clockPin, LSBFIRST, segmentBits[tens] );
  shiftOut(dataPin, clockPin, LSBFIRST, segmentBits[units] );
  //  Turn on the latch pin
  digitalWrite(latchPin, HIGH);
}
