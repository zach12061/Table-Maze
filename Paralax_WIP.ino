/*CopyRight Zachary A. Hardigree
 *Any unauthorized use will be fined double the cost to rights.

This demonstration shows how to use a set of four Parallax QTI sensors to provide line-following
capability to your BOE Shield-Bot Arduino robot.

Refer to the following pages for using the QTI Line Follower AppKit. 
  http://www.parallax.com/product/28108

Refer to the following help pages for additional wiring diagrams when using the QTI sensors with the
Arduino Uno:
  http://learn.parallax.com/KickStart/555-27401
*//*
Wiring Diagram for QTI Sensors:
Arduino          Sensor
D7               QTI4 - Far left
D6               QTI3 - Mid left
D5               QTI2 - Mid right
D4               QTI1 - Far right
*//*
Wiring Diagram for Servos:
Arduino          Servo
D13              Left servo
D12              Right servo

This example code makes use of an intermediate Arduino programming technique, specifically directly
manipulating multiple pins at once on the Arduino. This technique is referred to as port manipulation,
and is more fully discussed here:
  http://playground.arduino.cc/Learning/PortManipulation

Important: This demonstration was written, and intended for, use with the Arduino Uno microcontroller. 
Other Arduino boards may not be compatible.

*/

#include <Servo.h>                           // Use the Servo library (included with Arduino IDE)  

Servo servoL;                                // Define the left and right servos
Servo servoR;
int function = 0;


// Perform these steps with the Arduino is first powered on
void setup()

{
  Serial.begin(9600);                        // Set up Arduino Serial Monitor at 9600 baud
  servoL.attach(13);                         // Attach (programmatically connect) servos to pins on Arduino
  servoR.attach(12);

  //main code
  while(function<1){
  straddlethin();
  }
  servoL.writeMicroseconds(1700);
  servoR.writeMicroseconds(1700);
  delay(1000);
  servoR.writeMicroseconds(1300);
  delay(2500);
 
  while(function<2){
    straddlethick();
  }
  servoL.writeMicroseconds(1300);
  servoR.writeMicroseconds(1700);
  delay(1000);
  servoL.writeMicroseconds(1700);
  servoR.writeMicroseconds(1700);
  delay(1200);
  servoR.writeMicroseconds(1700);
  delay(400);
  
 
 while(function<3){
  avoidLeft();
 }
 while(function<4){
  avoidRight();
 }
 servoR.writeMicroseconds(1550);
 servoL.writeMicroseconds(1700);
 delay(1500);
 while(function<5){
  avoidRight();
 }
 servoR.writeMicroseconds(1300);
 servoL.writeMicroseconds(1500);
 delay(1000);
 servoR.writeMicroseconds(1300);
 servoL.writeMicroseconds(1700);
 delay(2500);
 while(function<6){
  halt();
 }
  servoR.writeMicroseconds(1500);
  servoL.writeMicroseconds(1500);
}

void loop(){
  
  
}

void straddlethin(){
 DDRD |= B11110000;                         // Set direction of Arduino pins D4-D7 as OUTPUT
  PORTD |= B11110000;                        // Set level of Arduino pins D4-D7 to HIGH
  delayMicroseconds(230);                    // Short delay to allow capacitor charge in QTI module
  DDRD &= B00001111;                         // Set direction of pins D4-D7 as INPUT
  PORTD &= B00001111;                        // Set level of pins D4-D7 to LOW
  delayMicroseconds(230);                    // Short delay
  int pins = PIND;                           // Get values of pins D0-D7
  pins >>= 4;                                // Drop off first four bits of the port; keep only pins D4-D7
  
  Serial.println(pins, BIN);
  int vL, vR;
  switch(pins)                               // Compare pins to known line following states
  {
    case B1000:                        
      vL = -100;                             // -100 to 100 indicate course correction values
      vR = 100;                              // -100: full reverse; 0=stopped; 100=full forward
      break;
    case B1100:                        
      vL = 0;
      vR = 100;
      break;
    case B0100:                        
      vL = 50;
      vR = 100;
      break;
    case B0110:                        
      vL = 100;
      vR = 100;
      break;
    case B0010:                        
      vL = 100;
      vR = 50;
      break;
    case B0011:                        
      vL = 100;
      vR = 0;
      break;
    case B0001:                        
      vL = 100;
      vR = -100;
      break;
    case B0000:
   function=function+1;
  }
  
  servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
  servoR.writeMicroseconds(1500 - vR);
  
  delay(10);                                // Delay for 50 milliseconds (1/20 second)
}
void straddlethick(){
 DDRD |= B11110000;                         // Set direction of Arduino pins D4-D7 as OUTPUT
  PORTD |= B11110000;                        // Set level of Arduino pins D4-D7 to HIGH
  delayMicroseconds(230);                    // Short delay to allow capacitor charge in QTI module
  DDRD &= B00001111;                         // Set direction of pins D4-D7 as INPUT
  PORTD &= B00001111;                        // Set level of pins D4-D7 to LOW
  delayMicroseconds(230);                    // Short delay
  int pins = PIND;                           // Get values of pins D0-D7
  pins >>= 4;                                // Drop off first four bits of the port; keep only pins D4-D7
  
  Serial.println(pins, BIN);
  int vL, vR;
  switch(pins)                               // Compare pins to known line following states
  {
    case B1000:                        
      vL = -100;                             // -100 to 100 indicate course correction values
      vR = 100;                              // -100: full reverse; 0=stopped; 100=full forward
      break;
    case B1100:                        
      vL = -50;
      vR = 100;
      break;
    case B1110:
      vL = 0;
      vR = 100;
    case B1111:                        
      vL = 100;
      vR = 100;
      break;
    case B0111:                        
      vL = 100;
      vR = 0;
      break;
    case B0011:                        
      vL = 100;
      vR = -50;
      break;
    case B0001:                        
      vL = 100;
      vR = -100;
      break;
    case B0000:
    function=function+1;
  }
  
  servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
  servoR.writeMicroseconds(1500 - vR);
  
  delay(10);                                // Delay for 50 milliseconds (1/20 second)
}
void avoidLeft(){
 DDRD |= B11110000;                         // Set direction of Arduino pins D4-D7 as OUTPUT
  PORTD |= B11110000;                        // Set level of Arduino pins D4-D7 to HIGH
  delayMicroseconds(230);                    // Short delay to allow capacitor charge in QTI module
  DDRD &= B00001111;                         // Set direction of pins D4-D7 as INPUT
  PORTD &= B00001111;                        // Set level of pins D4-D7 to LOW
  delayMicroseconds(230);                    // Short delay
  int pins = PIND;                           // Get values of pins D0-D7
  pins >>= 4;                                // Drop off first four bits of the port; keep only pins D4-D7
  
  Serial.println(pins, BIN);
  int vL, vR;
  switch(pins)                               // Compare pins to known line following states
  {
    case B0000:
      vL=50;
      vR=100;
      break;
    case B1000:                        
      vL = 100;                             // -100 to 100 indicate course correction values
      vR = 50;                              // -100: full reverse; 0=stopped; 100=full forward
      break;
    case B1100:                        
      vL = 100;
      vR = 0;
      break;
    case B1110:
      vL = 100;
      vR = -50;
      break;
    case B0111:                        
      function = function + 1;
      break;
  }
  
  servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
  servoR.writeMicroseconds(1500 - vR);
  
  delay(10);                                // Delay for 50 milliseconds (1/20 second)
}
void avoidRight(){
 DDRD |= B11110000;                         // Set direction of Arduino pins D4-D7 as OUTPUT
  PORTD |= B11110000;                        // Set level of Arduino pins D4-D7 to HIGH
  delayMicroseconds(230);                    // Short delay to allow capacitor charge in QTI module
  DDRD &= B00001111;                         // Set direction of pins D4-D7 as INPUT
  PORTD &= B00001111;                        // Set level of pins D4-D7 to LOW
  delayMicroseconds(230);                    // Short delay
  int pins = PIND;                           // Get values of pins D0-D7
  pins >>= 4;                                // Drop off first four bits of the port; keep only pins D4-D7
  
  Serial.println(pins, BIN);
  int vL, vR;
  switch(pins)                               // Compare pins to known line following states
  {
    case B0000:
      function = function + 1;
      break;
    case B0001:                        
      vL = 100;                             // -100 to 100 indicate course correction values
      vR = 0;                              // -100: full reverse; 0=stopped; 100=full forward
      break;
    case B0011:                        
      vL = 100;
      vR = 100;
      break;
    case B0111:
      vL = 50;
      vR = 100;
      break;
    case B1111:                      
      vL = 0;
      vR = 100;
      break;
  }
  
  servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
  servoR.writeMicroseconds(1500 - vR);
  
  delay(10);                                // Delay for 50 milliseconds (1/20 second)
}
void halt(){
 DDRD |= B11110000;                         // Set direction of Arduino pins D4-D7 as OUTPUT
  PORTD |= B11110000;                        // Set level of Arduino pins D4-D7 to HIGH
  delayMicroseconds(230);                    // Short delay to allow capacitor charge in QTI module
  DDRD &= B00001111;                         // Set direction of pins D4-D7 as INPUT
  PORTD &= B00001111;                        // Set level of pins D4-D7 to LOW
  delayMicroseconds(230);                    // Short delay
  int pins = PIND;                           // Get values of pins D0-D7
  pins >>= 4;                                // Drop off first four bits of the port; keep only pins D4-D7
  
  Serial.println(pins, BIN);
  int vL, vR;
  switch(pins)                               // Compare pins to known line following states
  {
    case B0001:                        
      delay(500);
      function=function+1;
      break;
      
    case B0011:                        
      delay(500);
      function=function+1;
      break;
    case B0111:
      delay(500);
      function=function+1;
      break;
    case B1111:                        
      delay(500);
      function=function+1;
      break;
    case B1110:
      delay(500);
      function=function+1;
      break;
    case B1100:
      delay(500);
      function=function+1;
      break;
    case B1000:
      delay(500);
      function=function+1;
      break;
  }
  
  servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
  servoR.writeMicroseconds(1500 - vR);
  
  delay(10);                                // Delay for 50 milliseconds (1/20 second)
}
