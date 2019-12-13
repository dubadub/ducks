#include <Servo.h>
int usb_unplugged_angle = 26;
int usb_plugged_angle = 0;
int resting_servo = 30;
int pressing_servo = 0;

int other_resting_servo = 0;
int other_pressing_servo = 30;

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
}

void loop(){
  if(Serial.available() > 0){
    incomingByte = Serial.read();
    Serial.println(incomingByte);
    if (incomingByte == 'a'){ // Turn servo 3 on
      myservo3.write(resting_servo);
    } else if (incomingByte == 'b'){ // Turn servo 3 off
       myservo3.write(pressing_servo);
    } else if (incomingByte == 'c'){ // Turn servo 6 on
      myservo5.write(resting_servo);
    } else if (incomingByte == 'd'){ // Turn servo 6 off
       myservo5.write(pressing_servo);
    } else if (incomingByte == 'e'){ // Turn servo 10 on
      myservo6.write(other_resting_servo);
    } else if (incomingByte == 'f'){ // Turn servo 10 off
       myservo6.write(other_pressing_servo);
    } else if (incomingByte == 'g'){ // unplug usb
       myservo9.write(usb_unplugged_angle);
    } else if (incomingByte == 'h'){ // plug usb
       myservo9.write(usb_plugged_angle);
    }
  }
}

