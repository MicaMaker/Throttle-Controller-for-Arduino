//Libraries
  #include <Joystick.h>
  #include "U8glib.h"

//Throttle
  //Define Throttle Input Pins
  #define joyThrottle A3 // Throttle Axis
  #define joyWheel A2 // Side Wheel Axis
  #define joyAxisX A0 // Thumbstick X Axis
  #define joyAxisY A1 // Thumbstick Y Axis
  #define joyAxis1 A9 // General Potentiometer 1
  #define joyAxis2 A7 // General Potentiometer 2
  #define joyAxis3 A8 // General Potentiometer 3
  #define joyButton1 15 // Grip Button 1
  #define joyButton2 14 // Grip Button 2
  #define joyButton3 10 // Grip Button 3
  #define joyButton4 16 // Thumbstick Button
  #define joyButton5 0 // General Button 1
  #define joyButton6 5 // General Button 2
  #define joyButton7 7 // General Button 3
  #define joyButton8 4 // Big Fat Toggle Switch


  int throttle_ = 0;
  int zAxis_ = 0;
  int xAxis_ = 0;
  int yAxis_ = 0;
  int rxAxis_ = 0;
  int ryAxis_ = 0;
  int rzAxis_ = 0;

  //Set Button Default States
  int lastButton1State = 0;
  int lastButton2State = 0;
  int lastButton3State = 0;
  int lastButton4State = 0;
  int lastButton5State = 0;
  int lastButton6State = 0;
  int lastButton7State = 0;
  int lastButton8State = 0;

  //Joystick(Joystick HID ID, Joystick Type, Button Count, Hat Switch Count, Include X, Include Y, Include Z,
  //  Include Rx, Include Ry, Include Rz, Include Rudder, Include Throttle, Include Accelerator, Include Brake, Include Steering)

  Joystick_ Joystick(0x15, JOYSTICK_TYPE_JOYSTICK, 8, 0, true, true, true, true, true, true, false, true, false, false, false);

  const bool initAutoSendState = true;


// Display
  
  U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST);

  int potentiometer_value1 = 0;
  int potentiometer_value2 = 0;
  char buffer1[20];
  char buffer2[20];
  int string_width1;
  int string_width2;


void setup() {

//Throttle
  pinMode(joyButton1, INPUT_PULLUP);
  pinMode(joyButton2, INPUT_PULLUP);
  pinMode(joyButton3, INPUT_PULLUP);
  pinMode(joyButton4, INPUT_PULLUP);
  pinMode(joyButton5, INPUT_PULLUP);
  pinMode(joyButton6, INPUT_PULLUP);
  pinMode(joyButton7, INPUT_PULLUP);
  pinMode(joyButton8, INPUT_PULLUP);

  Joystick.begin();

//Display
  u8g.setFont(u8g_font_tpssb);
  u8g.setColorIndex(1);
  u8g.setRot180();
}

void loop() {

//Throttle

  //throttle
  throttle_ = analogRead(joyThrottle);
  throttle_ = map(throttle_,0,1023,0,255);
  Joystick.setThrottle(throttle_);

  //side wheel
  zAxis_ = analogRead(joyWheel);
  zAxis_ = map(zAxis_,1023,0,0,255);
  Joystick.setZAxis(zAxis_);

  //thumbstick
  xAxis_ = analogRead(joyAxisX);
  xAxis_ = map(xAxis_,1023,0,0,255);
  Joystick.setXAxis(xAxis_);

  yAxis_ = analogRead(joyAxisY);
  yAxis_ = map(yAxis_,1023,0,0,255);
  Joystick.setYAxis(yAxis_);

  //general potentiometers
  rxAxis_ = analogRead(joyAxis1);
  rxAxis_ = map(rxAxis_,1023,0,0,255);
  Joystick.setRxAxis(rxAxis_);

  ryAxis_ = analogRead(joyAxis2);
  ryAxis_ = map(ryAxis_,1023,0,0,255);
  Joystick.setRyAxis(ryAxis_);

  rzAxis_ = analogRead(joyAxis3);
  rzAxis_ = map(rzAxis_,1023,0,0,255);
  Joystick.setRzAxis(rzAxis_);


  //Button States
  int currentButton1State = !digitalRead(joyButton1);
  if (currentButton1State != lastButton1State){
  Joystick.setButton (0, currentButton1State);
  lastButton1State = currentButton1State;
  }
  int currentButton2State = !digitalRead(joyButton2);
  if (currentButton2State != lastButton2State){
  Joystick.setButton (1, currentButton2State);
  lastButton2State = currentButton2State;
  }
  int currentButton3State = !digitalRead(joyButton3);
  if (currentButton3State != lastButton3State){
  Joystick.setButton (2, currentButton3State);
  lastButton3State = currentButton3State;
  }
  int currentButton4State = !digitalRead(joyButton4);
  if (currentButton4State != lastButton4State){
  Joystick.setButton (3, currentButton4State);
  lastButton4State = currentButton4State;
  }
  int currentButton5State = !digitalRead(joyButton5);
  if (currentButton5State != lastButton5State){
  Joystick.setButton (4, currentButton5State);
  lastButton5State = currentButton5State;
  }
  int currentButton6State = !digitalRead(joyButton6);
  if (currentButton6State != lastButton6State){
  Joystick.setButton (5, currentButton6State);
  lastButton6State = currentButton6State;
  }
  int currentButton7State = !digitalRead(joyButton7);
  if (currentButton7State != lastButton7State){
  Joystick.setButton (6, currentButton7State);
  lastButton7State = currentButton7State;
  }
  int currentButton8State = !digitalRead(joyButton8);
  if (currentButton8State != lastButton8State){
  Joystick.setButton (7, currentButton8State);
  lastButton8State = currentButton8State;
  }

  //Pole Delay/Debounce
  delay(10);


//Display
  //Displays Throttle and Wheel Value Percentages
  u8g.firstPage();
  do{
  string_width1 = u8g.getStrWidth(buffer1);
  string_width2 = u8g.getStrWidth(buffer2);

  u8g.setFont(u8g_font_9x18r);
  dtostrf(potentiometer_value1/10, 1, 0, buffer1);
  dtostrf(potentiometer_value2/10, 1, 0, buffer2);
  sprintf(buffer1, "%s%s", buffer1, "%");
  sprintf(buffer2, "%s%s", buffer2, "%");

  u8g.drawStr(32-string_width1/2, 16, buffer1);
  u8g.drawStr(96-string_width2/2, 16, buffer2);
   
  } while ( u8g.nextPage() );

  potentiometer_value1 = map(analogRead(joyThrottle), 0, 1023, 0, 1000);
  potentiometer_value2 = map(analogRead(joyWheel), 0, 1023, 1000, -1000);

}

