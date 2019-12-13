#include <Servo.h>
int usb_unplugged_angle = 26;
int usb_plugged_angle = 0;
int resting_servo = 30;
int pressing_servo = 0;

int other_resting_servo = 0;
int other_pressing_servo = 30;

#define RED 2
#define GREEN 7

int SPEAKER = 8;

Servo myservo3;
Servo myservo5;
Servo myservo6;
Servo myservo9; // USB
char incomingByte;

void setup(){
  Serial.begin(9600);

  myservo3.attach(3);
  myservo3.write(resting_servo);

  myservo5.attach(5);
  myservo5.write(resting_servo);

  myservo6.attach(6);
  myservo6.write(other_resting_servo);

  myservo9.attach(9);
  myservo9.write(usb_unplugged_angle);// usb unplugged

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode (SPEAKER, OUTPUT);
}

void loop(){
  if(Serial.available() > 0){
    incomingByte = Serial.read();
    Serial.println(incomingByte);
    if (incomingByte == 'a'){ // Turn servo 3 on
      chirp();
      myservo3.write(resting_servo);
    } else if (incomingByte == 'b'){ // Turn servo 3 off
       chirp();
       myservo3.write(pressing_servo);
    } else if (incomingByte == 'c'){ // Turn servo 6 on
      meow2();
      mew();
      myservo5.write(resting_servo);
    } else if (incomingByte == 'd'){ // Turn servo 6 off
      meow2();
      mew();
      myservo5.write(pressing_servo);
    } else if (incomingByte == 'e'){ // Turn servo 10 on
      ruff();
      myservo6.write(other_resting_servo);
    } else if (incomingByte == 'f'){ // Turn servo 10 off
      ruff();
       myservo6.write(other_pressing_servo);
    } else if (incomingByte == 'g'){ // unplug usb
      arf();
      analogWrite(RED, 255);
      analogWrite(GREEN, 0);
    } else if (incomingByte == 'h'){ // plug usb
      arf();
      analogWrite(RED, 0);
      analogWrite(GREEN, 255);
      myservo9.write(usb_plugged_angle);
      myservo9.write(usb_unplugged_angle);
    }
  }
}

void chirp() {  // Bird chirp
  for(uint8_t i=200; i>180; i--)
     playTone(i,9);
}

void meow() {  // cat meow (emphasis ow "me")
  uint16_t i;
  playTone(5100,50);        // "m" (short)
  playTone(394,180);        // "eee" (long)
  for(i=990; i<1022; i+=2)  // vary "ooo" down
     playTone(i,8);
  playTone(5100,40);        // "w" (short)
}

void meow2() {  // cat meow (emphasis on "ow")
  uint16_t i;
  playTone(5100,55);       // "m" (short)
  playTone(394,170);       // "eee" (long)
  delay(30);               // wait a tiny bit
  for(i=330; i<360; i+=2)  // vary "ooo" down
     playTone(i,10);
  playTone(5100,40);       // "w" (short)
}

void mew() {  // cat mew
  uint16_t i;
  playTone(5100,55);       // "m"   (short)
  playTone(394,130);       // "eee" (long)
  playTone(384,35);        // "eee" (up a tiny bit on end)
  playTone(5100,40);       // "w"   (short)
}

void ruff() {   // dog ruff
  uint16_t i;
  for(i=890; i<910; i+=2)     // "rrr"  (vary down)
     playTone(i,3);
  playTone(1664,150);         // "uuu" (hard to do)
  playTone(12200,70);         // "ff"  (long, hard to do)
}

void arf() {    // dog arf
  uint16_t i;
  playTone(890,25);          // "a"    (short)
  for(i=890; i<910; i+=2)    // "rrr"  (vary down)
     playTone(i,5);
  playTone(4545,80);         // intermediate
  playTone(12200,70);        // "ff"   (shorter, hard to do)
}

void playTone(uint16_t tone1, uint16_t duration) {
  if(tone1 < 50 || tone1 > 15000) return;  // these do not play on a piezo
  for (long i = 0; i < duration * 1000L; i += tone1 * 2) {
     digitalWrite(SPEAKER, HIGH);
     delayMicroseconds(tone1);
     digitalWrite(SPEAKER, LOW);
     delayMicroseconds(tone1);
  }
}

