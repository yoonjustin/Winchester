#include <SPI.h>
#include <Wire.h>
#include <string> 
#include <Adafruit_I2CDevice.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_INA260.h>
#include "PS4USB.h"
#include "UNKNOWNUSB.h"
#include "USBHost_t36.h"
//#include "defines.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool found1, found2 = false;
bool filter = false;
Adafruit_INA260 ina2601 = Adafruit_INA260();
Adafruit_INA260 ina2602 = Adafruit_INA260();

USBHost myusb;
USBHub hub1(myusb);
USBHub hub2(myusb);
JoystickController joystick1(myusb);
JoystickController joystick2(myusb);
USBHIDParser hid1(myusb);
USBHIDParser hid2(myusb);
USBDriver *drivers[] = {&hub1, &hub2, &joystick1, &joystick2, &hid1, &hid2};
#define CNT_DEVICES (sizeof(drivers)/sizeof(drivers[0]))
const char * driver_names[CNT_DEVICES] = {"Hub1", "Hub2", "Controller1", "Controller2", "HID1", "HID2"};
bool driver_active[CNT_DEVICES] = {false, false, false, false, false, false};
const char *controllerType[] = { "UNKNOWN", "PS3", "PS4", "XBOXONE", "XBOX360", "PS3_MOTION", "SpaceNav" };

IntervalTimer myTimer;
IntervalTimer controllerPoller1;
IntervalTimer controllerPoller2;
IntervalTimer filterTest;

//=============================================================================
// Other state variables.
//=============================================================================
uint32_t buttons;
uint8_t joystick_left_trigger_value = 0;
uint8_t joystick_right_trigger_value = 0;
bool P1Config, P2Config = false;
//=============================================================================
// DrawOled
//=============================================================================
void DrawOled(void) {
  display.clearDisplay();
  display.setCursor(0, 0);  
  if ((P1Config == false)||(P2Config == false)) {
    if (!found1) {
      display.write("ina260(5V) is not found\n");
    } else {
      display.write("+5V:   ");
      char result[8]; // Buffer big enough for 7-character float
      dtostrf(ina2601.readBusVoltage()/1000, 4, 2, result); // Leave room for too large numbers!
      display.write(result);
      display.write("V ");
      dtostrf(ina2601.readCurrent()/1000, 4, 2, result); // Leave room for too large numbers!
      display.write(result);
      display.write("A\n");
    }

    if (!found2) {
      display.write("ina260(12V) is not found\n");
    } else {
      display.write("+12V: ");
      char result[8]; // Buffer big enough for 7-character float
      dtostrf(ina2602.readBusVoltage()/1000, 4, 2, result); // Leave room for too large numbers!
      display.write(result);
      display.write("V ");
      dtostrf(ina2602.readCurrent()/1000, 4, 2, result); // Leave room for too large numbers!
      display.write(result);
      display.write("A\n\n");
    }

    const uint8_t *psz_m1 = joystick1.manufacturer();
    if (psz_m1 != NULL) {
      display.printf("Player 1: %s\n",psz_m1);
      display.write(controllerType[joystick1.joystickType()]);
      display.write(" - default map\n");
    } else {
      display.write("Player 1: \n\n");
    }

    const uint8_t *psz_m2 = joystick2.manufacturer();
    if (psz_m2 != NULL) {
      display.printf("Player 2: %s\n",psz_m2);
      display.write(controllerType[joystick2.joystickType()]);
      display.write(" - default map\n");
    } else {
      display.write("Player 2: ");
    }

    //buttons
    display.write("\nButton inputs:");
    buttons = joystick1.getButtons();
    char str[8];
    display.write(__itoa( buttons, str, 10 ));
  } // end config if
  
  if (P1Config == true) {
    display.write("Player 1: ");
    display.write(controllerType[joystick1.joystickType()]);
    
    buttons = joystick1.getButtons();
    char str[8];
    display.write("\nButton inputs:");
    display.write(__itoa( buttons, str, 10 ));
    display.write("\nButton Map: ");
    display.write("default\n");
    P2Config = false;
  }

  if (P2Config == true) {
    display.write("Player 2: ");
    display.write(controllerType[joystick2.joystickType()]);
    
    buttons = joystick2.getButtons();
    char str[8];
    display.write("\nButton inputs:");
    display.write(__itoa( buttons, str, 10 ));
    display.write("\nButton Map: ");
    display.write("default\n");
    P1Config = false;
  }

  display.display();
}

//=============================================================================
// PrintDeviceListChanges
//=============================================================================
void PrintDeviceListChanges() {
  for (uint8_t i = 0; i < CNT_DEVICES; i++) {
    if (*drivers[i] != driver_active[i]) {
      if (driver_active[i]) {
        Serial.printf("*** Device %s - disconnected ***\n", driver_names[i]);
        driver_active[i] = false;
      } else {
        Serial.printf("*** Device %s %x:%x - connected ***\n", driver_names[i], drivers[i]->idVendor(), drivers[i]->idProduct());
        driver_active[i] = true;

        const uint8_t *psz = drivers[i]->manufacturer();
        if (psz && *psz) Serial.printf("  manufacturer: %s\n", psz);
        psz = drivers[i]->product();
        if (psz && *psz) Serial.printf("  product: %s\n", psz);
        psz = drivers[i]->serialNumber();
        if (psz && *psz) Serial.printf("  Serial: %s\n", psz);
      }
    }
  }
}

//=============================================================================
// ProcessJoystickData1
//=============================================================================
void ProcessJoystickData1() {
  if (joystick1.available()) {
    buttons = joystick1.getButtons();

    switch (joystick1.joystickType()) {
      case JoystickController::PS4:
        //enter config mode
        if ((buttons == 4864)&&(P1Config==false)){
          P1Config = true;
        } else if ((buttons == 4864)&&(P1Config==true)){
          P1Config = false;
        }
        joystick1.setLEDs(0,0,0xFF);
        PS4USB::Player1ProcessPS4Inputs(joystick1.getButtons(), joystick1.getAxis(9)); 
        break;
      case JoystickController::PS3:

        break;
      case JoystickController::XBOXONE:
      case JoystickController::XBOX360:
        break;
      default:
        //treat unknown controllers as ps4? probably not a good idea
        if ((buttons == 4864)&&(P1Config==false)){
          P1Config = true;
        } else if ((buttons == 4864)&&(P1Config==true)){
          P1Config = false;
        }
        UNKNOWNUSB::Player1ProcessUnknownInputs(joystick1.getButtons(), joystick1.getAxis(9)); 
        break;
    }

    joystick1.joystickDataClear();
  }
}
//=============================================================================
// ProcessJoystickData2
//=============================================================================
void ProcessJoystickData2() {
  if (joystick2.available()) {
    buttons = joystick2.getButtons();
    uint8_t ltv;
    uint8_t rtv;
    switch (joystick2.joystickType()) {
      default:
        break;
      case JoystickController::PS4:
      //enter config mode
        if ((buttons == 4864)&&(P2Config==false)){
          P2Config = true;
        } else if ((buttons == 4864)&&(P2Config==true)){
          P2Config = false;
        }
        joystick2.setLEDs(0xFF,0,0);
        PS4USB::Player2ProcessPS4Inputs(joystick2.getButtons(), joystick2.getAxis(9)); 
        break;

      case JoystickController::PS3:
        break;

      case JoystickController::XBOXONE:
      case JoystickController::XBOX360:
        ltv = joystick2.getAxis(4);
        rtv = joystick2.getAxis(5);
        if ((ltv != joystick_left_trigger_value) || (rtv != joystick_right_trigger_value)) {
          joystick_left_trigger_value = ltv;
          joystick_right_trigger_value = rtv;
          //joystick.setRumble(ltv, rtv);
          //Serial.printf(" Set Rumble %d %d", ltv, rtv);
        }
        break;
    }

    /*
    if (buttons != buttons_cur) {
      if (joystick2.joystickType() == JoystickController::PS3) {
        joystick2.setLEDs((buttons >> 12) & 0xf); //  try to get to TRI/CIR/X/SQuare
      } else {
        uint8_t lr = (buttons & 1) ? 0xff : 0;
        uint8_t lg = (buttons & 2) ? 0xff : 0;
        uint8_t lb = (buttons & 4) ? 0xff : 0;
        joystick2.setLEDs(lr, lg, lb);
      }
      buttons_cur = buttons;
    }
    */
    //tft_JoystickData();
    joystick2.joystickDataClear();
  }
}



//=============================================================================
// setup
//=============================================================================
void setup() {
  Serial.begin(9600);
  delay(10);

  pinMode(P1_COIN, OUTPUT); 
  pinMode(P1_START, OUTPUT); 
  pinMode(P1_UP, OUTPUT); 
  pinMode(P1_DOWN, OUTPUT);  
  pinMode(P1_LEFT, OUTPUT); 
  pinMode(P1_RIGHT, OUTPUT); 
  pinMode(P1_B1, OUTPUT); 
  pinMode(P1_B2, OUTPUT);
  pinMode(P1_B3, OUTPUT); 
  pinMode(P1_B4, OUTPUT); 
  pinMode(P1_B4_K, OUTPUT); 
  pinMode(P1_B5_K, OUTPUT); 
  pinMode(P1_B6_K, OUTPUT);   

  pinMode(P2_COIN, OUTPUT); 
  pinMode(P2_START, OUTPUT); 
  pinMode(P2_UP, OUTPUT); 
  pinMode(P2_DOWN, OUTPUT);  
  pinMode(P2_LEFT, OUTPUT); 
  pinMode(P2_RIGHT, OUTPUT); 
  pinMode(P2_B1, OUTPUT); 
  pinMode(P2_B2, OUTPUT);
  pinMode(P2_B3, OUTPUT); 
  pinMode(P2_B4, OUTPUT); 
  pinMode(P2_B4_K, OUTPUT); 
  pinMode(P2_B5_K, OUTPUT); 
  pinMode(P2_B6_K, OUTPUT);   

  pinMode(25, OUTPUT);
  digitalWrite(25, HIGH);
  if (!ina2601.begin(0x40,&Wire)) {
    found1 = false;
  } else {
    found1 = true;
  }

    if (!ina2602.begin(0x42,&Wire)) {
    found2 = false;
  } else {
    found2 = true;
  }

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an winchester splash screen.
  display.display();
  delay(3000); // Pause for 3 seconds
  // Clear the buffer
  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  display.setTextWrap(false);


  myTimer.begin(DrawOled, 1000000);
  controllerPoller1.begin(ProcessJoystickData1, 4000);
  controllerPoller2.begin(ProcessJoystickData2, 4000);

  myusb.begin();
} //end setup 

void loop() {
  myusb.Task();
  PrintDeviceListChanges();
}

