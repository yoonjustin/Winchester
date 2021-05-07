#ifndef _PS4USB_H
#define _PS4USB_H
#include <Wire.h>
#include "..\defines.h"

class PS4USB {
    public:
        static void Player1ProcessPS4Inputs(uint32_t, int);
        static void Player2ProcessPS4Inputs(uint32_t, int);
    private:
        PS4USB() {};
};


#endif