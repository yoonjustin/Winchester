# Winchester
This is the teensy code to work along side the open hardware Winchester supergun PCB. The source is written in C++ using Platform IO on Visual Studio Code IDE. 

### Working Features
* Reading the +5V and +12V power lines to the Jamma PCB
* USB controller support for PS4 and XboxOne controllers for two players 
* Pressing option+share+home on PS4 controllers will show advanced controller information
* Pressing view+menu+right stick button on Xbox One controllers will show advanced controller information

### Known Issues 
* PS3 controllers can sometimes lock up the USB ports when plugging in. Mostly happens when one controller is already plugged in and a PS3 controller is plugged in as player 2. The strange thing is that ps3 controllers work fine when using only using one in single player 
* PS4 controllers will light up with the correct led color when first plugged in, but if you unplug and replug in a PS4 controller the led color is not set.
* Third party controllers wont work except for the Brook Fighting board plus Audio
* The Hori RAP N fight stick will disconnect shortly after connecting 

### Planned Features
* Bluetooth controller support using a bluetooth dongle in one of the usb ports
* Add more third party controller support
* Add a way to toggle the low pass filter on the THS7376
* Implement a way to remap buttons 
* Implement a way to switch between button maps 
* Implement a way to set buttons to turbo mode 
* Implement a way to remember specific controllers and remember what button mapping to use 
