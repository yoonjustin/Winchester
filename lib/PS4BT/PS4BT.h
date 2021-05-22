#ifndef _PS4BT_H
#define _PS4BT_H
#include <Wire.h>
#include "..\defines.h"

class PS4BT {
    public:
        static void Player1ProcessPS4BTInputs(uint32_t);
        static void Player2ProcessPS4Inputs(uint32_t);
    private:
        PS4BT() {};
};


#endif