#include <SPI.h>
#include <Wire.h>
#include <string> 
#include <Adafruit_I2CDevice.h>
#include <Adafruit_GFX.h>
#include "Adafruit_SSD1306.h"
#include <Adafruit_INA260.h>
#include "PS4USB.h"
#include "PS4BT.h"
#include "UNKNOWNUSB.h"
#include "XBOXONEUSB.h"
#include "USBHost_t36.h"

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

//BluetoothController bluet(myusb, true, "0000");
BluetoothController blue1(myusb);
//BluetoothController blue2(myusb);

USBHIDParser hid1(myusb);
USBHIDParser hid2(myusb);

USBDriver * drivers[] = {&hub1, &hub2, &joystick1, &joystick2, &hid1, &hid2, &blue1};
#define CNT_DEVICES (sizeof(drivers)/sizeof(drivers[0]))
const char * driver_names[CNT_DEVICES] = {"Hub1", "Hub2", "Controller1", "Controller2", "HID1", "HID2", "Blue1"};
bool driver_active[CNT_DEVICES] = {false, false, false, false, false, false, false};
const char * controllerType[] = { "UNKNOWN", "PS3", "PS4", "XBOXONE", "XBOX360", "PS3_MOTION", "SpaceNav" };


USBHIDInput * hiddrivers[] = {&joystick1, &joystick2};

#define CNT_HIDDEVICES (sizeof(hiddrivers)/sizeof(hiddrivers[0]))
const char * hid_driver_names[CNT_HIDDEVICES] = {"Joystick1", "Joystick2"};
bool hid_driver_active[CNT_DEVICES] = {false, false};

BTHIDInput * bthiddrivers[] = {&joystick1, &joystick2};
#define CNT_BTHIDDEVICES (sizeof(bthiddrivers)/sizeof(bthiddrivers[0]))
const char * bthid_driver_names[CNT_BTHIDDEVICES] = {"Joystick1BT","Joystick2BT"};
bool bthid_driver_active[CNT_BTHIDDEVICES] = {false, false};

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
uint8_t polling1, polling2 = 0;
uint8_t last_bdaddr[6] = {0, 0, 0, 0, 0, 0};

//=============================================================================
// DrawOled
//=============================================================================
void DrawOled(void) {
  display.clearDisplay();
  display.setCursor(0, 0);  
  if ((P1Config == false)&&(P2Config == false)) {
    if (!found1) {
      display.write("ina260(5V) is not found\n");
    } else {
      display.write("+5V:");
      char result[8]; // Buffer big enough for 7-character float
      dtostrf(ina2601.readBusVoltage()/1000, 4, 2, result); // Leave room for too large numbers!
      display.write(result);
      display.write("V ");
      //dtostrf(ina2601.readCurrent()/1000, 4, 2, result); // Leave room for too large numbers!
      //display.write(result);
      //display.write("A\n");
    }

    if (!found2) {
      display.write("ina260(12V) is not found\n");
    } else {
      display.write("+12V:");
      char result[8]; // Buffer big enough for 7-character float
      dtostrf(ina2602.readBusVoltage()/1000, 4, 2, result); // Leave room for too large numbers!
      display.write(result);
      display.write("V\n");
      //dtostrf(ina2602.readCurrent()/1000, 4, 2, result); // Leave room for too large numbers!
      
      //display.write("A\n\n");
    }
    display.write("---------------------\n");
    display.write("     Controllers\n");
    if (joystick1.operator bool()) {
      display.printf("P1: %s ",controllerType[joystick1.joystickType()]);
      display.printf(bthid_driver_active[0] ? "- BT\n":"- USB\n");
    } else {
      display.write("P1: unplugged\n");
    }

    if (joystick2.operator bool()) {
      display.printf("P2: %s ",controllerType[joystick2.joystickType()]);
      display.printf(bthid_driver_active[1] ? "- BT\n":"- USB\n");
    } else {
      display.write("P2: unplugged\n\n\n");
    }
    

    display.write(driver_active[6] ? "bt dongle: connected" : "");
  } // end config if
  

  if ((P1Config == true)) {
    const uint8_t *psz_m1 = joystick1.manufacturer();
    display.write("Player 1: ");
    if (joystick1.operator bool()){
      display.write(controllerType[joystick1.joystickType()]);
    } else {
      display.write("None");
    }
    display.printf("\n%s\n",psz_m1);
    display.printf("vid: %X  ",joystick1.idVendor());
    display.printf("pid: %X\n",joystick1.idProduct());
    display.printf("Polling: %dHz",polling1*2);
    buttons = joystick1.getButtons();
    display.write("\nButton inputs:");
    if (bthid_driver_active[0]){
      display.printf("%d", buttons); 
    } else {
      display.printf("%d", buttons);
    }
    display.write("\nButton Map: ");
    display.write("default\n");
    P2Config = false;
  }

  if ((P2Config == true)) {
    const uint8_t *psz_m2 = joystick2.manufacturer();
    display.write("Player 2: ");
    if (joystick2.operator bool()){
      display.write(controllerType[joystick2.joystickType()]);
    } else {
      display.write("None");
    }
    display.printf("\n%s\n",psz_m2);
    display.printf("vid: %X  ",joystick2.idVendor());
    display.printf("pid: %X\n",joystick2.idProduct());
    display.printf("Polling: %dHz",polling2);
    buttons = joystick2.getButtons();
    display.write("\nButton inputs:");
    if (bthid_driver_active[1]){
      display.printf("%d", buttons^8);
    } else {
      display.printf("%d", buttons);
    }
    display.write("\nButton Map: ");
    display.write("default\n");
    P1Config = false;
  }

  display.display();
  polling1 = 0;
  polling2 = 0;
}

//=============================================================================
// PrintDeviceListChanges
//=============================================================================
void PrintDeviceListChanges() {
      // Then Bluetooth devices
  for (uint8_t i = 0; i < CNT_BTHIDDEVICES; i++) {
    if (*bthiddrivers[i] != bthid_driver_active[i]) {
      if (bthid_driver_active[i]) {
        Serial.printf("*** BTHID Device %s - disconnected ***\n", bthid_driver_names[i]);
        bthid_driver_active[i] = false;
      } else {
        Serial.printf("*** BTHID Device %s %x:%x - connected ***\n", bthid_driver_names[i], bthiddrivers[i]->idVendor(), bthiddrivers[i]->idProduct());
        bthid_driver_active[i] = true;

        const uint8_t *psz = bthiddrivers[i]->manufacturer();
        if (psz && *psz) Serial.printf("  manufacturer: %s\n", psz);
        psz = bthiddrivers[i]->product();
        if (psz && *psz) Serial.printf("  product: %s\n", psz);
        psz = bthiddrivers[i]->serialNumber();
        if (psz && *psz) Serial.printf("  Serial: %s\n", psz);
      }
    }
  }



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

        if (drivers[i] == &blue1) {
          const uint8_t *bdaddr = blue1.myBDAddr();
          // remember it...
          Serial.printf("  BDADDR: %x:%x:%x:%x:%x:%x\n", bdaddr[0], bdaddr[1], bdaddr[2], bdaddr[3], bdaddr[4], bdaddr[5]);
          for (uint8_t i = 0; i < 6; i++) last_bdaddr[i] = bdaddr[i];
        }
      }
    }
  }



  //if (joystick1.available()){
  //  Serial.print("BThid driver active: ");
  //  Serial.println(bthid_driver_active[0] ? "true" : "false");

  //  Serial.print("Joystick type: ");
  //  Serial.println(controllerType[joystick1.joystickType()]);
  //}
}

//=============================================================================
// ProcessJoystickData1
//=============================================================================
void ProcessJoystickData1() {
  polling1++;

  //USB connection 
  if ((joystick1.available())&&(bthid_driver_active[0]==false)) {
    buttons = joystick1.getButtons();

    switch (joystick1.joystickType()) {
      case JoystickController::PS4: {
        //enter config mode
        if ((buttons == 4096)&&(P1Config==false)){
          P1Config = true;
        } else if ((buttons == 4096)&&(P1Config==true)){
          P1Config = false;
        }
        joystick1.setLEDs(0,0,0xFF);
        PS4USB::Player1ProcessPS4Inputs(buttons, joystick1.getAxis(9)); 
        break;}
      case JoystickController::PS3:
        break;
      case JoystickController::XBOXONE:
      case JoystickController::XBOX360:
        //enter config mode
        if ((buttons == 12)&&(P1Config==false)){
          P1Config = true;
        } else if ((buttons == 12)&&(P1Config==true)){
          P1Config = false;
        }
        XBOXONEUSB::Player1ProcessXboxOneInputs(joystick1.getButtons(), joystick1.getAxis(3), joystick1.getAxis(4)); 
        break;
      default:
        //Brook fighting board plus audio
        if ((joystick1.idProduct() == 0xE30)&&(joystick1.idVendor()== 0xC12)) {
          if ((buttons == 4864)&&(P1Config==false)){
            P1Config = true;
          } else if ((buttons == 4864)&&(P1Config==true)){
            P1Config = false;
          }
          UNKNOWNUSB::Player1ProcessUnknownInputs(joystick1.getButtons(), joystick1.getAxis(9)); 
        }
        break;
    }
  }

  //BT Connections
  if ((joystick1.available())&&(bthid_driver_active[0]==true)) {
    buttons = joystick1.getButtons();
    switch (joystick1.joystickType()) {
      case JoystickController::PS4: {
        //enter config mode
        if ((buttons == 9)&&(P1Config==false)){
          P1Config = true;
        } else if ((buttons == 9)&&(P1Config==true)){
          P1Config = false;
        }
        joystick1.setLEDs(0,0xFF,0);
        PS4BT::Player1ProcessPS4BTInputs(buttons); 
        break;}
      default:
        break;
    }
  }

  joystick1.joystickDataClear();
}
//=============================================================================
// ProcessJoystickData2
//=============================================================================
void ProcessJoystickData2() {
  polling2++;
  //USB connected controller
  if ((joystick2.available())&&(bthid_driver_active[1]==false)) {
    buttons = joystick2.getButtons();

    switch (joystick2.joystickType()) {
      case JoystickController::PS4:
        //enter config mode
        if ((buttons == 4864)&&(P2Config==false)){ P2Config = true;} 
          else if ((buttons == 4864)&&(P2Config==true)){  P2Config = false; }
        joystick2.setLEDs(0xFF,0,0);
        PS4USB::Player2ProcessPS4Inputs(joystick2.getButtons(), joystick2.getAxis(9)); 
        break;
      case JoystickController::PS3:

        break;
      case JoystickController::XBOXONE:
      case JoystickController::XBOX360:
        //enter config mode
        if ((buttons == 32780)&&(P2Config==false)){
          P2Config = true;
        } else if ((buttons == 32780)&&(P2Config==true)){
          P2Config = false;
        }
        XBOXONEUSB::Player2ProcessXboxOneInputs(joystick2.getButtons(), joystick2.getAxis(3), joystick2.getAxis(4)); 
        break;
      default:
        //Brook fighting board plus audio
        if ((joystick2.idProduct() == 0xE30)&&(joystick2.idVendor()== 0xC12)) {
          if ((buttons == 4864)&&(P2Config==false)){
            P2Config = true;
          } else if ((buttons == 4864)&&(P2Config==true)){
            P2Config = false;
          }
          UNKNOWNUSB::Player2ProcessUnknownInputs(joystick2.getButtons(), joystick2.getAxis(9)); 
        }

        break;
    }
  }

  //BT Connections
  if ((joystick2.available())&&(bthid_driver_active[1]==true)) {
    buttons = joystick2.getButtons();
    switch (joystick2.joystickType()) {
      case JoystickController::PS4: {
        //enter config mode
        if ((buttons == 9)&&(P2Config==false)){
          P1Config = true;
        } else if ((buttons == 9)&&(P2Config==true)){
          P1Config = false;
        }
        joystick2.setLEDs(0xFF,0xFF,0);
        PS4BT::Player2ProcessPS4BTInputs(buttons^8); 
        break;}
      default:
        break;
    }
  }


  joystick2.joystickDataClear();
}



//=============================================================================
// setup
//=============================================================================
void setup() {
  Serial.begin(9600);
  delay(10);
Serial.println("hello world");
  //Set GPIO pins to output
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

  //Set low pass filter to off
  pinMode(25, OUTPUT);
  digitalWrite(25, HIGH);

  //Detect the INA260's with i2c addresses
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
  Serial.println("hello world");
  //Initialize oled screen
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(("SSD1306 allocation failed"));
    for(;;); // not sure if we should hang if screen is not present
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

  //Start timers 
  myTimer.begin(DrawOled, 500000);
  controllerPoller1.begin(ProcessJoystickData1, 4000);
  controllerPoller2.begin(ProcessJoystickData2, 4000);

  myusb.begin();
} //end setup 

void loop() {
  myusb.Task();
  PrintDeviceListChanges();
}

