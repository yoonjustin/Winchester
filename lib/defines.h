#ifndef _DEFINES_H
#define _DEFINES_H

//==============================================================
//List of teensy pin number to corresponding Jamma input 
//b4 is jamma 25/c and the _K refers to the kick harness
//==============================================================
#define P1_COIN    15
#define P1_START   16
#define P1_UP      13
#define P1_DOWN    14
#define P1_RIGHT   41
#define P1_LEFT    40
#define P1_B1      37
#define P1_B2      38
#define P1_B3      35
#define P1_B4      36
#define P1_B4_K    31
#define P1_B5_K    29
#define P1_B6_K    27

#define P2_COIN    7
#define P2_START   6
#define P2_UP      9
#define P2_DOWN    8
#define P2_RIGHT   10
#define P2_LEFT    11
#define P2_B1      26
#define P2_B2      12
#define P2_B3      33
#define P2_B4      34
#define P2_B4_K    32
#define P2_B5_K    30
#define P2_B6_K    28

//==============================================================
//Playstation 3 button input values
//==============================================================
#define PS3_SELECT    1
#define PS3_START     8
#define PS3_UP        16
#define PS3_RIGHT     32
#define PS3_DOWN      64
#define PS3_LEFT      128
#define PS3_L2        256
#define PS3_R2        512
#define PS3_L1        1024
#define PS3_R1        2048
#define PS3_TRIANGLE  4096
#define PS3_CIRCLE    8192
#define PS3_X         16385
#define PS3_SQUARE    32768

//==============================================================
//Playstation 4 button input values
//==============================================================
#define PS4_SHARE     256
#define PS4_OPTION    512
#define PS4_HOME      4096
#define PS4_L2        64
#define PS4_R2        128
#define PS4_L1        16
#define PS4_R1        32
#define PS4_TRIANGLE  8
#define PS4_CIRCLE    4
#define PS4_X         2
#define PS4_SQUARE    1
//Read the ps4 dpad using axis(9)
#define PS4_UP         0
#define PS4_UP_RIGHT   1
#define PS4_RIGHT      2
#define PS4_DOWN_RIGHT 3
#define PS4_DOWN       4
#define PS4_DOWN_LEFT  5
#define PS4_LEFT       6
#define PS4_UP_LEFT    7
#define PS4_NO_DPAD    8

//==============================================================
//Xbox One button input values
//==============================================================
#define XBOXONE_MENU    4
#define XBOXONE_VIEW    8
#define XBOXONE_UP      256
#define XBOXONE_RIGHT   2048
#define XBOXONE_DOWN    512
#define XBOXONE_LEFT    1024
#define XBOXONE_X       64
#define XBOXONE_Y       128
#define XBOXONE_A       16
#define XBOXONE_B       32
#define XBOXONE_RB      8192
#define XBOXONE_LB      4096


//==============================================================
//Unknown button input values
//==============================================================
#define UNKNOWN_SELECT     256
#define UNKNOWN_START      512
#define UNKNOWN_HOME       4096
#define UNKNOWN_L2         64
#define UNKNOWN_R2         128
#define UNKNOWN_L1         16
#define UNKNOWN_R1         32
#define UNKNOWN_TRIANGLE   8
#define UNKNOWN_CIRCLE     4
#define UNKNOWN_X          2
#define UNKNOWN_SQUARE     1
//Read the unknown dpad using axis(9)
#define UNKNOWN_UP         0
#define UNKNOWN_UP_RIGHT   1
#define UNKNOWN_RIGHT      2
#define UNKNOWN_DOWN_RIGHT 3
#define UNKNOWN_DOWN       4
#define UNKNOWN_DOWN_LEFT  5
#define UNKNOWN_LEFT       6
#define UNKNOWN_UP_LEFT    7
#define UNKNOWN_NO_DPAD    8


#endif