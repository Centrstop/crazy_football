#include "Laba1-4.h"



void main(void)
{
    uint8_t contrast;
    uint8_t brightness;
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    Board_init();

    __enable_interrupt();

    // Set up LCD
    Dogs102x6_init();
    Dogs102x6_backlightInit();

    contrast = 11;      // Set Default Contrast
    brightness = 11;    // Set Default Brightness

    Dogs102x6_setBacklight(brightness);
    Dogs102x6_setContrast(contrast);
    Dogs102x6_clearScreen();

    Wheel_init();
    Buttons_init(BUTTON_ALL);
    Buttons_interruptEnable(BUTTON_ALL);
    buttonsPressed = 0;
    Dogs102x6_stringDraw(3, 30, "CPU OFF", DOGS102x6_DRAW_NORMAL);
    __bis_SR_register(LPM3_bits + GIE);

    while(1)
        {
        Dogs102x6_stringDraw(3, 30, "CPU ON", DOGS102x6_DRAW_NORMAL);
        Dogs102x6_clearScreen();
        }
}
