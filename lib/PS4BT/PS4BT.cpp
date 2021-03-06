#include "PS4BT.h"


//=============================================================================
//Player 1 ps4 connected through bt are parsed to the output jamma pins
//=============================================================================
void PS4BT::Player1ProcessPS4BTInputs(uint32_t buttons) {
  byte dpad = (byte)buttons & 0xF; 
  switch(dpad){
    case PS4BT_NOTHING:
        digitalWrite(P1_UP,LOW);
        digitalWrite(P1_DOWN,LOW);
        digitalWrite(P1_LEFT,LOW);
        digitalWrite(P1_RIGHT,LOW);
        break;
    case PS4BT_UP:
        digitalWrite(P1_UP,HIGH);
        digitalWrite(P1_DOWN,LOW);
        digitalWrite(P1_LEFT,LOW);
        digitalWrite(P1_RIGHT,LOW);
        Serial.printf("up: %d\n",buttons);
        break;
    case PS4BT_DOWN:
        digitalWrite(P1_UP,LOW);
        digitalWrite(P1_DOWN,HIGH);
        digitalWrite(P1_LEFT,LOW);
        digitalWrite(P1_RIGHT,LOW);
        Serial.printf("down: %d\n",buttons);
        break;
    case PS4BT_LEFT:
        digitalWrite(P1_UP,LOW);
        digitalWrite(P1_DOWN,LOW);
        digitalWrite(P1_LEFT,HIGH);
        digitalWrite(P1_RIGHT,LOW);
        Serial.printf("left: %d\n",buttons);
        break;
    case PS4BT_RIGHT:
        digitalWrite(P1_UP,LOW);
        digitalWrite(P1_DOWN,LOW);
        digitalWrite(P1_LEFT,LOW);
        digitalWrite(P1_RIGHT,HIGH);
        Serial.printf("right: %d\n",buttons);
        break; 
    case PS4BT_UP_RIGHT: 
        digitalWrite(P1_UP,HIGH);
        digitalWrite(P1_DOWN,LOW);
        digitalWrite(P1_LEFT,LOW);
        digitalWrite(P1_RIGHT,HIGH);
        Serial.printf("u/r: %d\n",buttons);
        break;  
    case PS4BT_DOWN_RIGHT: 
        digitalWrite(P1_UP,LOW);
        digitalWrite(P1_DOWN,HIGH);
        digitalWrite(P1_LEFT,LOW);
        digitalWrite(P1_RIGHT,HIGH);
        Serial.printf("d/r: %d\n",buttons);
        break; 
    case PS4BT_DOWN_LEFT: 
        digitalWrite(P1_UP,LOW);
        digitalWrite(P1_DOWN,HIGH);
        digitalWrite(P1_LEFT,HIGH);
        digitalWrite(P1_RIGHT,LOW);
        Serial.printf("d/l: %d\n",buttons);
        break; 
    case PS4BT_UP_LEFT: 
        digitalWrite(P1_UP,HIGH);
        digitalWrite(P1_DOWN,LOW);
        digitalWrite(P1_LEFT,HIGH);
        digitalWrite(P1_RIGHT,LOW);
        Serial.printf("u/l: %d\n",buttons);
        break;
    default:
        break;
  }

  buttons = buttons >> 4;
  if (buttons&PS4BT_SQUARE){
    digitalWrite(P1_B1, HIGH);
    Serial.printf("B1: %d\n",buttons);
  } else {
    digitalWrite(P1_B1, LOW);
  }

  if (buttons&PS4BT_TRIANGLE){
    digitalWrite(P1_B2, HIGH);
    Serial.printf("B2: %d\n",buttons);
  } else {
    digitalWrite(P1_B2, LOW);
  }

  if (buttons&PS4BT_X){
    digitalWrite(P1_B4,HIGH);
    Serial.printf("B4: %d\n",buttons);
    digitalWrite(P1_B4_K, HIGH);
  } else {
    digitalWrite(P1_B4, LOW);
    digitalWrite(P1_B4_K, LOW);
  }

  if (buttons&PS4BT_CIRCLE){
    digitalWrite(P1_B5_K, HIGH);
    Serial.printf("B5: %d\n",buttons);
  } else {
    digitalWrite(P1_B5_K, LOW);
  }

  if ((buttons&PS4BT_OPTION)==20){
    digitalWrite(P1_START, HIGH);  
    Serial.printf("start pressed: %d\n", buttons);
  } else {
    digitalWrite(P1_START, LOW);
  }

  if ((buttons&PS4BT_SHARE)==10){
    digitalWrite(P1_COIN, HIGH);  
    Serial.printf("coin: %d\n",buttons);
  } else {
    digitalWrite(P1_COIN, LOW);
  }
  
  if ((buttons&PS4BT_R1)&&!(buttons&0x4)){
    digitalWrite(P1_B3, HIGH);
    Serial.printf("R1 pressed: %d\n", buttons);
  } else {
    digitalWrite(P1_B3, LOW);
  }

  if ((buttons&PS4BT_R2)==5){
    digitalWrite(P1_B6_K, HIGH); 
    Serial.printf("R2 pressed: %d\n", buttons); 
  } else {
    digitalWrite(P1_B6_K, LOW);
  }

  if ((buttons&PS4BT_R1R2)==6){
    digitalWrite(P1_B6_K, HIGH); 
    digitalWrite(P1_B3, HIGH);
    Serial.printf("R1 and R2 pressed: %d\n", buttons); 
  } 
/*
  if (buttons&PS4_L1){
    digitalWrite(P1_COIN, HIGH);  
  } else {
    digitalWrite(P1_COIN, LOW);
  }

  if (buttons&PS4_L2){
    digitalWrite(P1_COIN, HIGH);  
  } else {
    digitalWrite(P1_COIN, LOW);
  }
*/
}

//=============================================================================
//Player 2 ps4 connected through usb are parsed to the output jamma pins
//=============================================================================
void PS4BT::Player2ProcessPS4BTInputs(uint32_t buttons) {
  if (buttons==PS4BT_UP){
    digitalWrite(P2_UP, HIGH);
  } else {
    digitalWrite(P2_UP, LOW);
  }

  if (buttons&PS4BT_DOWN){
    digitalWrite(P2_DOWN, HIGH);
  } else {
    digitalWrite(P2_DOWN, LOW);
  }
  
  if (buttons&PS4BT_LEFT){
    digitalWrite(P2_LEFT, HIGH);
  } else {
    digitalWrite(P2_LEFT, LOW);
  }

  if (buttons&PS4BT_RIGHT){
    digitalWrite(P2_RIGHT, HIGH);
  } else {
    digitalWrite(P2_RIGHT, LOW);
  }

    if (buttons&PS4BT_SQUARE){
    digitalWrite(P2_B1, HIGH);
  } else {
    digitalWrite(P2_B1, LOW);
  }

  if (buttons&PS4BT_TRIANGLE){
    digitalWrite(P2_B2, HIGH);
  } else {
    digitalWrite(P2_B2, LOW);
  }

  if (buttons&PS4BT_X){
    digitalWrite(P2_B4,HIGH);
    digitalWrite(P2_B4_K, HIGH);
  } else {
    digitalWrite(P2_B4, LOW);
    digitalWrite(P2_B4_K, LOW);
  }

  if (buttons&PS4BT_CIRCLE){
    digitalWrite(P2_B5_K, HIGH);
  } else {
    digitalWrite(P2_B5_K, LOW);
  }

  if (buttons&PS4BT_OPTION){
    digitalWrite(P2_START, HIGH);  
  } else {
    digitalWrite(P2_START, LOW);
  }

  if (buttons&PS4BT_SHARE){
    digitalWrite(P2_COIN, HIGH);  
  } else {
    digitalWrite(P2_COIN, LOW);
  }
  
  if (buttons&PS4BT_R1){
    digitalWrite(P2_B3, HIGH);
  } else {
    digitalWrite(P2_B3, LOW);
  }

  if (buttons&PS4BT_R2){
    digitalWrite(P2_B6_K, HIGH);  
  } else {
    digitalWrite(P2_B6_K, LOW);
  }

/*
  if (buttons&PS4_L1){
    digitalWrite(P2_COIN, HIGH);  
  } else {
    digitalWrite(P2_COIN, LOW);
  }

  if (buttons&PS4_L2){
    digitalWrite(P2_COIN, HIGH);  
  } else {
    digitalWrite(P2_COIN, LOW);
  }
*/
  
}