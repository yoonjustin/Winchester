#include "XBOXONEUSB.h"


//=============================================================================
//Player 1 Xbox One connected through usb are parsed to the output jamma pins
//=============================================================================
void XBOXONEUSB::Player1ProcessXboxOneInputs(uint32_t buttons, int lt, int rt) {
  if (buttons&XBOXONE_UP){
    digitalWrite(P1_UP, HIGH);
  } else {
    digitalWrite(P1_UP, LOW);
  }

  if (buttons&XBOXONE_DOWN){
    digitalWrite(P1_DOWN, HIGH);
  } else {
    digitalWrite(P1_DOWN, LOW);
  }

  if (buttons&XBOXONE_LEFT){
    digitalWrite(P1_LEFT,HIGH);
  } else {
    digitalWrite(P1_LEFT, LOW);
  }

  if (buttons&XBOXONE_RIGHT){
    digitalWrite(P1_RIGHT, HIGH);
  } else {
    digitalWrite(P1_RIGHT, LOW);
  }   
  
  if (buttons&XBOXONE_X){
    digitalWrite(P1_B1, HIGH);
  } else {
    digitalWrite(P1_B1, LOW);
  }

  if (buttons&XBOXONE_Y){
    digitalWrite(P1_B2, HIGH);
  } else {
    digitalWrite(P1_B2, LOW);
  }

  if (buttons&XBOXONE_A){
    digitalWrite(P1_B4,HIGH);
    digitalWrite(P1_B4_K, HIGH);
  } else {
    digitalWrite(P1_B4, LOW);
    digitalWrite(P1_B4_K, LOW);
  }

  if (buttons&XBOXONE_B){
    digitalWrite(P1_B5_K, HIGH);
  } else {
    digitalWrite(P1_B5_K, LOW);
  }

  if (buttons&XBOXONE_MENU){
    digitalWrite(P1_START, HIGH);  
  } else {
    digitalWrite(P1_START, LOW);
  }

  if (buttons&XBOXONE_VIEW){
    digitalWrite(P1_COIN, HIGH);  
  } else {
    digitalWrite(P1_COIN, LOW);
  }
  
  if (buttons&XBOXONE_RB){
    digitalWrite(P1_B3, HIGH);
  } else {
    digitalWrite(P1_B3, LOW);
  }

  if (rt > 0){
    digitalWrite(P1_B6_K, HIGH);  
  } else {
    digitalWrite(P1_B6_K, LOW);
  }

/*
  if (buttons&XBOXONE_LB){
    digitalWrite(P1_COIN, HIGH);  
  } else {
    digitalWrite(P1_COIN, LOW);
  }

  if (lt>0){
    digitalWrite(P1_COIN, HIGH);  
  } else {
    digitalWrite(P1_COIN, LOW);
  }
*/
}

//=============================================================================
//Player 2 Xbox One connected through usb are parsed to the output jamma pins
//=============================================================================
void XBOXONEUSB::Player2ProcessXboxOneInputs(uint32_t buttons, int lt, int rt) {
   if (buttons&XBOXONE_UP){
    digitalWrite(P2_UP, HIGH);
  } else {
    digitalWrite(P2_UP, LOW);
  }

  if (buttons&XBOXONE_DOWN){
    digitalWrite(P2_DOWN, HIGH);
  } else {
    digitalWrite(P2_DOWN, LOW);
  }

  if (buttons&XBOXONE_LEFT){
    digitalWrite(P2_LEFT,HIGH);
  } else {
    digitalWrite(P2_LEFT, LOW);
  }

  if (buttons&XBOXONE_RIGHT){
    digitalWrite(P2_RIGHT, HIGH);
  } else {
    digitalWrite(P2_RIGHT, LOW);
  }   
  
  if (buttons&XBOXONE_X){
    digitalWrite(P2_B1, HIGH);
  } else {
    digitalWrite(P2_B1, LOW);
  }

  if (buttons&XBOXONE_Y){
    digitalWrite(P2_B2, HIGH);
  } else {
    digitalWrite(P2_B2, LOW);
  }

  if (buttons&XBOXONE_A){
    digitalWrite(P2_B4,HIGH);
    digitalWrite(P2_B4_K, HIGH);
  } else {
    digitalWrite(P2_B4, LOW);
    digitalWrite(P2_B4_K, LOW);
  }

  if (buttons&XBOXONE_B){
    digitalWrite(P2_B5_K, HIGH);
  } else {
    digitalWrite(P2_B5_K, LOW);
  }

  if (buttons&XBOXONE_MENU){
    digitalWrite(P2_START, HIGH);  
  } else {
    digitalWrite(P2_START, LOW);
  }

  if (buttons&XBOXONE_VIEW){
    digitalWrite(P2_COIN, HIGH);  
  } else {
    digitalWrite(P2_COIN, LOW);
  }
  
  if (buttons&XBOXONE_RB){
    digitalWrite(P2_B3, HIGH);
  } else {
    digitalWrite(P2_B3, LOW);
  }

  if (rt > 0){
    digitalWrite(P2_B6_K, HIGH);  
  } else {
    digitalWrite(P2_B6_K, LOW);
  }

/*
  if (buttons&XBOXONE_LB){
    digitalWrite(P1_COIN, HIGH);  
  } else {
    digitalWrite(P1_COIN, LOW);
  }

  if (lt>0){
    digitalWrite(P1_COIN, HIGH);  
  } else {
    digitalWrite(P1_COIN, LOW);
  }
*/
  
}