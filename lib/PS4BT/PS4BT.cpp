#include "PS4BT.h"


//=============================================================================
//Player 1 ps4 connected through bt are parsed to the output jamma pins
//=============================================================================
void PS4BT::Player1ProcessPS4BTInputs(uint32_t buttons) {
  if (buttons&PS4BT_UP){
    digitalWrite(P1_UP, HIGH);
    Serial.println("pressed up\n");
  } else {
    digitalWrite(P1_UP, LOW);
  }

  if (buttons&PS4BT_DOWN){
    digitalWrite(P1_DOWN, HIGH);
  } else {
    digitalWrite(P1_DOWN, LOW);
  }
  
  if (buttons&PS4BT_LEFT){
    digitalWrite(P1_LEFT, HIGH);
  } else {
    digitalWrite(P1_LEFT, LOW);
  }

  if (buttons&PS4BT_RIGHT){
    digitalWrite(P1_RIGHT, HIGH);
  } else {
    digitalWrite(P1_RIGHT, LOW);
  }

    if (buttons&PS4BT_SQUARE){
    digitalWrite(P1_B1, HIGH);
  } else {
    digitalWrite(P1_B1, LOW);
  }

  if (buttons&PS4BT_TRIANGLE){
    digitalWrite(P1_B2, HIGH);
  } else {
    digitalWrite(P1_B2, LOW);
  }

  if (buttons&PS4BT_X){
    digitalWrite(P1_B4,HIGH);
    digitalWrite(P1_B4_K, HIGH);
  } else {
    digitalWrite(P1_B4, LOW);
    digitalWrite(P1_B4_K, LOW);
  }

  if (buttons&PS4BT_CIRCLE){
    digitalWrite(P1_B5_K, HIGH);
  } else {
    digitalWrite(P1_B5_K, LOW);
  }

  if (buttons&PS4BT_OPTION){
    digitalWrite(P1_START, HIGH);  
  } else {
    digitalWrite(P1_START, LOW);
  }

  if (buttons&PS4BT_SHARE){
    digitalWrite(P1_COIN, HIGH);  
  } else {
    digitalWrite(P1_COIN, LOW);
  }
  
  if (buttons&PS4BT_R1){
    digitalWrite(P1_B3, HIGH);
  } else {
    digitalWrite(P1_B3, LOW);
  }

  if (buttons&PS4BT_R2){
    digitalWrite(P1_B6_K, HIGH);  
  } else {
    digitalWrite(P1_B6_K, LOW);
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
void PS4BT::Player2ProcessPS4Inputs(uint32_t buttons) {
  
  if (buttons&PS4_SQUARE){
    digitalWrite(P2_B1, HIGH);
  } else {
    digitalWrite(P2_B1, LOW);
  }

  if (buttons&PS4_TRIANGLE){
    digitalWrite(P2_B2, HIGH);
  } else {
    digitalWrite(P2_B2, LOW);
  }

  if (buttons&PS4_X){
    digitalWrite(P2_B4,HIGH);
    digitalWrite(P2_B4_K, HIGH);
  } else {
    digitalWrite(P2_B4, LOW);
    digitalWrite(P2_B4_K, LOW);
  }

  if (buttons&PS4_CIRCLE){
    digitalWrite(P2_B5_K, HIGH);
  } else {
    digitalWrite(P2_B5_K, LOW);
  }

  if (buttons&PS4_OPTION){
    digitalWrite(P2_START, HIGH);  
  } else {
    digitalWrite(P2_START, LOW);
  }

  if (buttons&PS4_SHARE){
    digitalWrite(P2_COIN, HIGH);  
  } else {
    digitalWrite(P2_COIN, LOW);
  }
  
  if (buttons&PS4_R1){
    digitalWrite(P2_B3, HIGH);
  } else {
    digitalWrite(P2_B3, LOW);
  }

  if (buttons&PS4_R2){
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