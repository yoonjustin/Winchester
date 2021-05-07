#ifndef _UNKNOWNUSB_H
#define _UNKNOWNUSB_H
#include <Wire.h>
#include "..\defines.h"

class UNKNOWNUSB {
    public:
        static void Player1ProcessUnknownInputs(uint32_t, int);
        static void Player2ProcessUnknownInputs(uint32_t, int);
    private:
        UNKNOWNUSB() {};
};


#endif