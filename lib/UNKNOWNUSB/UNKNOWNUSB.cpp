#include "UNKNOWNUSB.h"


//=============================================================================
//Player 1 unknown connected through usb are parsed to the output jamma pins
//=============================================================================
void UNKNOWNUSB::Player1ProcessUnknownInputs(uint32_t buttons, int dpad) {
  switch(dpad){
    case UNKNOWN_NO_DPAD:
        digitalWrite(P1_UP,LOW);
        digitalWrite(P1_DOWN,LOW);
        digitalWrite(P1_LEFT,LOW);
        digitalWrite(P1_RIGHT,LOW);
        break;
    case UNKNOWN_UP:
        digitalWrite(P1_UP,HIGH);
        digitalWrite(P1_DOWN,LOW);
        digitalWrite(P1_LEFT,LOW);
        digitalWrite(P1_RIGHT,LOW);
        break;
    case UNKNOWN_DOWN:
        digitalWrite(P1_UP,LOW);
        digitalWrite(P1_DOWN,HIGH);
        digitalWrite(P1_LEFT,LOW);
        digitalWrite(P1_RIGHT,LOW);
        break;
    case UNKNOWN_LEFT:
        digitalWrite(P1_UP,LOW);
        digitalWrite(P1_DOWN,LOW);
        digitalWrite(P1_LEFT,HIGH);
        digitalWrite(P1_RIGHT,LOW);
        break;
    case UNKNOWN_RIGHT:
        digitalWrite(P1_UP,LOW);
        digitalWrite(P1_DOWN,LOW);
        digitalWrite(P1_LEFT,LOW);
        digitalWrite(P1_RIGHT,HIGH);
        break;  
    case UNKNOWN_UP_RIGHT:
        digitalWrite(P1_UP,HIGH);
        digitalWrite(P1_DOWN,LOW);
        digitalWrite(P1_LEFT,LOW);
        digitalWrite(P1_RIGHT,HIGH);
        break;  
    case UNKNOWN_DOWN_RIGHT:
        digitalWrite(P1_UP,LOW);
        digitalWrite(P1_DOWN,HIGH);
        digitalWrite(P1_LEFT,LOW);
        digitalWrite(P1_RIGHT,HIGH);
        break; 
    case UNKNOWN_DOWN_LEFT:
        digitalWrite(P1_UP,LOW);
        digitalWrite(P1_DOWN,HIGH);
        digitalWrite(P1_LEFT,HIGH);
        digitalWrite(P1_RIGHT,LOW);
        break; 
    case UNKNOWN_UP_LEFT:
        digitalWrite(P1_UP,HIGH);
        digitalWrite(P1_DOWN,LOW);
        digitalWrite(P1_LEFT,HIGH);
        digitalWrite(P1_RIGHT,LOW);
        break; 
    default:
        break;
  }
  
  if (buttons&UNKNOWN_SQUARE){
    digitalWrite(P1_B1, HIGH);
  } else {
    digitalWrite(P1_B1, LOW);
  }

  if (buttons&UNKNOWN_TRIANGLE){
    digitalWrite(P1_B2, HIGH);
  } else {
    digitalWrite(P1_B2, LOW);
  }

  if (buttons&UNKNOWN_X){
    digitalWrite(P1_B4,HIGH);
    digitalWrite(P1_B4_K, HIGH);
  } else {
    digitalWrite(P1_B4, LOW);
    digitalWrite(P1_B4_K, LOW);
  }

  if (buttons&UNKNOWN_CIRCLE){
    digitalWrite(P1_B5_K, HIGH);
  } else {
    digitalWrite(P1_B5_K, LOW);
  }

  if (buttons&UNKNOWN_SELECT){
    digitalWrite(P1_START, HIGH);  
  } else {
    digitalWrite(P1_START, LOW);
  }

  if (buttons&UNKNOWN_START){
    digitalWrite(P1_COIN, HIGH);  
  } else {
    digitalWrite(P1_COIN, LOW);
  }
  
  if (buttons&UNKNOWN_R1){
    digitalWrite(P1_B3, HIGH);
  } else {
    digitalWrite(P1_B3, LOW);
  }

  if (buttons&UNKNOWN_R2){
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
//Player 2 unknown connected through usb are parsed to the output jamma pins
//=============================================================================
void UNKNOWNUSB::Player2ProcessUnknownInputs(uint32_t buttons, int dpad) {
  switch(dpad){
    case UNKNOWN_NO_DPAD:
        digitalWrite(P2_UP,LOW);
        digitalWrite(P2_DOWN,LOW);
        digitalWrite(P2_LEFT,LOW);
        digitalWrite(P2_RIGHT,LOW);
        break;
    case UNKNOWN_UP:
        digitalWrite(P2_UP,HIGH);
        digitalWrite(P2_DOWN,LOW);
        digitalWrite(P2_LEFT,LOW);
        digitalWrite(P2_RIGHT,LOW);
        break;
    case UNKNOWN_DOWN:
        digitalWrite(P2_UP,LOW);
        digitalWrite(P2_DOWN,HIGH);
        digitalWrite(P2_LEFT,LOW);
        digitalWrite(P2_RIGHT,LOW);
        break;
    case UNKNOWN_LEFT:
        digitalWrite(P2_UP,LOW);
        digitalWrite(P2_DOWN,LOW);
        digitalWrite(P2_LEFT,HIGH);
        digitalWrite(P2_RIGHT,LOW);
        break;
    case UNKNOWN_RIGHT:
        digitalWrite(P2_UP,LOW);
        digitalWrite(P2_DOWN,LOW);
        digitalWrite(P2_LEFT,LOW);
        digitalWrite(P2_RIGHT,HIGH);
        break;  
    case UNKNOWN_UP_RIGHT:
        digitalWrite(P2_UP,HIGH);
        digitalWrite(P2_DOWN,LOW);
        digitalWrite(P2_LEFT,LOW);
        digitalWrite(P2_RIGHT,HIGH);
        break;  
    case UNKNOWN_DOWN_RIGHT:
        digitalWrite(P2_UP,LOW);
        digitalWrite(P2_DOWN,HIGH);
        digitalWrite(P2_LEFT,LOW);
        digitalWrite(P2_RIGHT,HIGH);
        break; 
    case UNKNOWN_DOWN_LEFT:
        digitalWrite(P2_UP,LOW);
        digitalWrite(P2_DOWN,HIGH);
        digitalWrite(P2_LEFT,HIGH);
        digitalWrite(P2_RIGHT,LOW);
        break; 
    case UNKNOWN_UP_LEFT:
        digitalWrite(P2_UP,HIGH);
        digitalWrite(P2_DOWN,LOW);
        digitalWrite(P2_LEFT,HIGH);
        digitalWrite(P2_RIGHT,LOW);
        break; 
    default:
        break;
  }
  
  if (buttons&UNKNOWN_SQUARE){
    digitalWrite(P2_B1, HIGH);
  } else {
    digitalWrite(P2_B1, LOW);
  }

  if (buttons&UNKNOWN_TRIANGLE){
    digitalWrite(P2_B2, HIGH);
  } else {
    digitalWrite(P2_B2, LOW);
  }

  if (buttons&UNKNOWN_X){
    digitalWrite(P2_B4,HIGH);
    digitalWrite(P2_B4_K, HIGH);
  } else {
    digitalWrite(P2_B4, LOW);
    digitalWrite(P2_B4_K, LOW);
  }

  if (buttons&UNKNOWN_CIRCLE){
    digitalWrite(P2_B5_K, HIGH);
  } else {
    digitalWrite(P2_B5_K, LOW);
  }

  if (buttons&UNKNOWN_SELECT){
    digitalWrite(P2_START, HIGH);  
  } else {
    digitalWrite(P2_START, LOW);
  }

  if (buttons&UNKNOWN_START){
    digitalWrite(P2_COIN, HIGH);  
  } else {
    digitalWrite(P2_COIN, LOW);
  }
  
  if (buttons&UNKNOWN_R1){
    digitalWrite(P2_B3, HIGH);
  } else {
    digitalWrite(P2_B3, LOW);
  }

  if (buttons&UNKNOWN_R2){
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