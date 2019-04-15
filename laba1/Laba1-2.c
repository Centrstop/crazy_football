#include "Laba1-2.h"
#include "stdio.h"

#define STARTCX 95
#define STARTCY 32


uint16_t timeoutCounter;
uint8_t DrawFlag;
uint8_t StepFlag;
uint8_t tempString[10] = {0};

int8_t centerX = STARTCX;
int8_t centerY = STARTCY;

uint8_t flagCngplr;
uint8_t flagEnd;
uint8_t countScore1;
uint8_t countScore2;

struct damagHero{
    uint8_t flagUp;
    uint8_t texturN;
    uint8_t centerX;
    uint8_t centerY;
    uint8_t speedY;
};

struct damagHero pers[3];

const uint8_t pole[] =
{
 0x66,    // Image width in pixels
 0x08,    // Image height in rows (1 row = 8 pixels)
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
 0x03, 0x03, 0x07, 0x07, 0x0e, 0x0e, 0x1c, 0x1c, 0x1c, 0x3c, 0x38, 0x38, 0x78, 0x78, 0x78, 0x78,
 0x78, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
 0x07, 0x1f, 0x3e, 0x7c, 0xf0, 0xe0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x0f, 0x7f, 0xff, 0xf0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x3c,
 0x3c, 0x3c, 0x3c, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0xc0, 0xf0, 0xfc, 0x3e, 0x1f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0,
 0xf0, 0x70, 0x38, 0x38, 0x1c, 0x1c, 0x1c, 0x1e, 0x0e, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t Logoimage[] =
{
    0x66,    // Image width in pixels
    0x08,    // Image height in rows (1 row = 8 pixels)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x01, 0x01,
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x06,
    0x02, 0x02, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x60,
    0x00, 0x00, 0x00, 0xf0, 0xf8, 0xf8, 0xfe, 0xf8, 0xf0, 0xf0, 0xe0, 0xe0, 0xe0, 0x60, 0x60, 0x00,
    0x18, 0x08, 0x00, 0x04, 0x03, 0x03, 0x03, 0x03, 0x07, 0xe7, 0xe7, 0x8f, 0x03, 0x00, 0x06, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07,
    0x07, 0x07, 0x07, 0x07, 0xff, 0xff, 0xff, 0xff, 0x07, 0x07, 0x07, 0x07, 0x07, 0xff, 0xff, 0xff,
    0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x3e, 0xc1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79, 0x79, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0x1e, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x80, 0x80, 0x80, 0x80, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x80, 0x20, 0x3c, 0x7f, 0x7f, 0xff,
    0xff, 0xff, 0xff, 0xff, 0x7d, 0x3f, 0x1f, 0x1e, 0x18, 0x00, 0x00, 0x00, 0x40, 0x40, 0x00, 0x00,
    0x00, 0x80, 0x80, 0x80, 0xc0, 0xc3, 0xc3, 0xf8, 0xc0, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x1f, 0x1f, 0x1f, 0x1f, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x80, 0x00, 0x10, 0x10, 0xe8, 0xe0, 0xe0, 0xe4, 0xe0, 0xe2, 0xe3, 0xe1, 0x01, 0x09, 0x09,
    0x09, 0x01, 0x01, 0x07, 0x06, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0xf8, 0x18, 0x18, 0x00, 0x60, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x02, 0x02, 0x01, 0x00, 0x00, 0x03,
    0x02, 0x82, 0x82, 0x81, 0x80, 0x80, 0x80, 0x81, 0x83, 0x81, 0x00, 0x00, 0x02, 0x02, 0x02, 0x03,
    0x00, 0x02, 0x01, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0x02, 0x02, 0x00,
    0x00, 0x01, 0x02, 0x02, 0x02, 0x01, 0x80, 0x80, 0x81, 0x82, 0x82, 0x82, 0x81, 0x80, 0x82, 0x82,
    0x83, 0x82, 0x82, 0x80, 0x83, 0x82, 0x82, 0x82, 0x81, 0x80, 0x80, 0x80, 0x81, 0x83, 0x81, 0x80,
    0x80, 0x80, 0x83, 0x80, 0x80, 0x80, 0x80, 0x83, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08,
    0x08, 0x08, 0x10, 0x00, 0x00, 0xf8, 0x40, 0x40, 0x60, 0x90, 0x08, 0x08, 0x38, 0xe0, 0x20, 0xe0,
    0x38, 0x18, 0x28, 0x48, 0x88, 0x08, 0x00, 0x00, 0x00, 0xd0, 0xa8, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xf8, 0x40, 0x40, 0x40, 0x00, 0xe0, 0x10, 0x08, 0x08, 0x08, 0x10, 0xe0, 0xe0, 0x10, 0x08,
    0x08, 0x08, 0x10, 0xe0, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0xf8, 0x48, 0x48, 0x48, 0xb0, 0x00,
    0x08, 0x30, 0xe0, 0x20, 0xe0, 0x30, 0x08, 0x00, 0xf8, 0x08, 0x08, 0x08, 0x00, 0xf8, 0x08, 0x08,
    0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t img_faceUP1[] =
{
    0x08,    // Image width in pixels
    0x01,    // Image height in rows (1 row = 8 pixels)
    0x1f, 0xf5, 0xff, 0x4b, 0x03, 0x13, 0xff, 0xff
};

const uint8_t img_faceUP2[] =
{
    0x08,    // Image width in pixels
    0x01,    // Image height in rows (1 row = 8 pixels)
    0x1f, 0xf5, 0xff, 0x4b, 0xff, 0xff, 0x00, 0x00
};

const uint8_t img_faceDOWN1[] =
{
    0x08,    // Image width in pixels
    0x01,    // Image height in rows (1 row = 8 pixels)
    0xf8, 0xaf, 0xff, 0xd2, 0xc0, 0xc8, 0xff, 0xff
};

const uint8_t img_faceDOWN2[] =
{
    0x08,    // Image width in pixels
    0x01,    // Image height in rows (1 row = 8 pixels)
    0xf8, 0xaf, 0xff, 0xd2, 0xff, 0xff, 0x00, 0x00
};

uint8_t EpsCenter(uint8_t centerXHole,uint8_t centerYHole,uint8_t centerXBall,uint8_t centerYBall){
    uint8_t statusX= 0x00;
    int deltaX = centerXHole-centerXBall;
    int deltaY = centerYHole-centerYBall;
        if(deltaX<0) deltaX = deltaX*-1;
        if(deltaY<0) deltaY = deltaY*-1;
        if(deltaX<6){
            if(deltaY<6)statusX = 0x01;
        }
        else{
           statusX = 0x00;
        }
     return statusX;
}

void DrawLCD(){
    uint8_t i = 0;
    if(DrawFlag){
        Board_ledToggle(LED1);
        Dogs102x6_imageDraw(pole, 0, 0);
        for(i=0;i<3;i++){
            if(!pers[i].flagUp){
                if(pers[i].texturN){
                    Dogs102x6_imageDrawXY(pers[i].centerX, pers[i].centerY,img_faceUP2);
                }
                else{
                    Dogs102x6_imageDrawXY(pers[i].centerX, pers[i].centerY,img_faceUP1);
                }
            }
            else{
                if(pers[i].texturN){
                    Dogs102x6_imageDrawXY(pers[i].centerX, pers[i].centerY,img_faceDOWN2);
                }
                else{
                    Dogs102x6_imageDrawXY(pers[i].centerX, pers[i].centerY,img_faceDOWN1);
                }
            }
        }

        Dogs102x6_circleDraw(centerX,centerY,4,DOGS102x6_DRAW_NORMAL);
        sprintf(tempString,"P1=%d",countScore1);
        Dogs102x6_stringDrawXY(77, 0, tempString, DOGS102x6_DRAW_NORMAL);
        sprintf(tempString,"P2=%d",countScore2);
        Dogs102x6_stringDrawXY(77, 55, tempString, DOGS102x6_DRAW_NORMAL);
        DrawFlag=0x00;
    }
}

void GameDamageStep(){
    uint8_t i = 0;
    if(StepFlag){
        for(i=0;i<3;i++){
            if(pers[i].flagUp){
                if(pers[i].centerY<55){
                    pers[i].texturN ^= 0x01;
                    pers[i].centerY += pers[i].speedY;
                }
                else{
                    pers[i].flagUp ^=0x01;
                }
            }
            else{
                if(pers[i].centerY>3){
                    pers[i].texturN ^= 0x01;
                    pers[i].centerY -= pers[i].speedY;
                }
                else{
                    pers[i].flagUp ^=0x01;
                }
            }
        }
    }
   StepFlag = 0x00;
}

void setPositionBall(){
    uint8_t gamma = 1;
    gamma += Wheel_getPosforGame()>>1;
    Cma3000_readAccel_offset();
    if(centerX>0){
        if(centerX<99){
            centerX = centerX - gamma*(Cma3000_xAccel/10);
        }
        else {
            centerX = 98;
        }
    }
    else{
        centerX=2;
    }
    if(centerY>5){
        if(centerY<59){
            centerY = centerY + gamma*(Cma3000_yAccel/10);
        }
        else {
            centerY = 58;
        }
    }
    else{
        centerY=6;
    }
}

void playerScore(){
    if(centerX<5){
        if(centerY>20){
            if(centerY<40){
               if(!flagCngplr){
                   countScore1++;
                   centerX=STARTCX;
                   centerY=STARTCY;
               }
               else{
                   countScore2++;
                   centerX=STARTCX;
                   centerY=STARTCY;
               }
            }
        }
    }
}

void ChangeGame(){
    Dogs102x6_clearScreen();
    Dogs102x6_stringDraw(7, 15, "Press button", DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDraw(3, 12, "Player change", DOGS102x6_DRAW_NORMAL);
    pauseGame();
}


void playerChange(){
  uint8_t i;
  for(i=0;i<3;i++){
      if(EpsCenter(pers[i].centerX+4, pers[i].centerY+4, centerX, centerY)){
          if(flagCngplr){
              Dogs102x6_clearInverseDisplay();
              centerX=STARTCX;
              centerY=STARTCY;
              flagCngplr ^=0x01;
              ChangeGame();
          }
          else{
              Dogs102x6_setInverseDisplay();
              centerX=STARTCX;
              centerY=STARTCY;
              flagCngplr ^=0x01;
              ChangeGame();
          }
      }
  }

}

void pauseGame(){
    while (!buttonsPressed){
          for (timeoutCounter = 0; timeoutCounter < 0xFFFF; timeoutCounter++)
          {
              if (buttonsPressed) break;
              __delay_cycles(1000);
          }

          //Timeout break
          break;
        }
    buttonsPressed = 0;
}


void startGame(){
    Dogs102x6_imageDraw(Logoimage, 0, 2);
    Dogs102x6_stringDraw(7, 15, "Press button", DOGS102x6_DRAW_NORMAL);
    pauseGame();
}

void endGame(){
    if(countScore1>4){
        Dogs102x6_clearScreen();
        Dogs102x6_stringDraw(7, 15, "Press button", DOGS102x6_DRAW_NORMAL);
        Dogs102x6_stringDraw(3, 15, "Player 1 WIN", DOGS102x6_DRAW_NORMAL);
        countScore1 = 0;
        countScore2 = 0;
        centerX=STARTCX;
        centerY=STARTCY;
        pauseGame();
        startGame();
    }
    if(countScore2>4){
        Dogs102x6_clearScreen();
        Dogs102x6_stringDraw(7, 15, "Press button", DOGS102x6_DRAW_NORMAL);
        Dogs102x6_stringDraw(3, 15, "Player 2 WIN", DOGS102x6_DRAW_NORMAL);
        countScore1 = 0;
        countScore2 = 0;
        centerX=STARTCX;
        centerY=STARTCY;
        pauseGame();
        startGame();
    }
}



void main(void)
{
    uint8_t contrast;
    uint8_t brightness;
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    Board_init();

    // Set up LCD
    Dogs102x6_init();
    Dogs102x6_backlightInit();

    contrast = 11;      // Set Default Contrast
    brightness = 11;    // Set Default Brightness
    DrawFlag=0x01;

    Dogs102x6_setBacklight(brightness);
    Dogs102x6_setContrast(contrast);
    Dogs102x6_clearScreen();
    // Set up Accel
    Cma3000_setAccel_offset(-23,0,0); //������ �������� �� X
    Cma3000_init();

    //Init start struct damagHero
    pers[0].flagUp = 0x01;
    pers[1].flagUp = 0x00;
    pers[2].flagUp = 0x01;
    pers[0].texturN = 0;
    pers[1].texturN = 0;
    pers[2].texturN = 0;
    pers[0].centerX = 22;
    pers[0].centerY = 0;
    pers[1].centerX = 44;
    pers[1].centerY = 55;
    pers[2].centerX = 67;
    pers[2].centerY = 0;
    pers[0].speedY = 3;
    pers[1].speedY = 2;
    pers[2].speedY = 1;
    //init Flags
    StepFlag = 0x01;
    flagCngplr = 0;
    // Set TimerA
    TA0CCTL0 = CCIE;
    TA0CCR0 =  1000;
    TA0CTL = TASSEL_2 + MC_1 + ID_3;
    // __bis_SR_register(LPM0_bits + GIE);

    __enable_interrupt(); // ��������� ����������

    Wheel_init(); // �������������� ��������
    Buttons_init(BUTTON_ALL); // �������������� ������
    Buttons_interruptEnable(BUTTON_ALL); // ��������� ���������� �� �������
    buttonsPressed = 0; // �������� ������� ������

    // Display Game logo
    startGame();
    Dogs102x6_clearScreen();

    while(1)
    {
        DrawLCD();
        GameDamageStep();
        setPositionBall();
        playerScore();
        playerChange();
        endGame();
    }
}


#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR (void)
{
    DrawFlag = 0x01;          // set draw flag
    StepFlag = 0x01;        // set step flag
}