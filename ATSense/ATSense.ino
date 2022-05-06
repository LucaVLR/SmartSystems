#include <Wire.h>
#include <NewPing.h>

byte IR_PINS[8] = {0, 1, 2, 14, 15, 5, 6, 7};
byte IR_state = 0;
NewPing echo_distance(A2, A3);

#define IR_DIS A6

byte echo_dis = 0;
byte ir_dis = 0;

void setup() {
  // init IR sensor
  pinMode(IR_DIS, INPUT);

  // init IR line follower
  for(byte i = 0; i < 8; i++)
    pinMode(IR_PINS[i], INPUT);

  // init ultrasonic distance sensor
  pinMode(A2, OUTPUT); 
  pinMode(A3, INPUT); 
  
  Wire.begin(0xAA);
  Wire.onRequest(i2creq);
}

void loop() {
}

void i2creq() {
  echo_dis = echo_distance.ping_cm();
  ir_dis = map(analogRead(IR_DIS), 0, 1023, 0, 255);

  IR_state = 0;
  for(byte i = 0; i < 8; i++)
    IR_state |= digitalRead(IR_PINS[i]) << i;

  Wire.write(echo_dis);
  Wire.write(ir_dis);
  Wire.write(IR_state);
}
