#ifndef _XBOXONEUSB_H
#define _XBOXONEUSB_H
#include <Wire.h>
#include "..\defines.h"

class XBOXONEUSB {
    public:
        static void Player1ProcessXboxOneInputs(uint32_t, int, int);
        static void Player2ProcessXboxOneInputs(uint32_t, int, int);
    private:
        XBOXONEUSB() {};
};


#endif