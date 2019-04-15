#include "Laba1-1.h"


uint16_t timeoutCounter;
static const char *const LedMenu[] = {
    "= Toggle LED =",
    "1. LED1 ",
    "2. LED2 ",
    "3. LED3 ",
    "4. LED4 ",
    "5. LED5 ",
    "6. LED6 "
};

void main(void)
{
    uint8_t contrast;
    uint8_t brightness;
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
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


	volatile unsigned int i;		// volatile to prevent optimization

	while(1)
	{
	    Dogs102x6_stringDraw(7, 0, "*S1=Enter S2=Esc*", DOGS102x6_DRAW_NORMAL);
	    switch (Menu_active((char **)LedMenu, 6)){
	        case 1: Board_ledToggle(LED1); break;
	        case 2: Board_ledToggle(LED2); break;
	        case 3: Board_ledToggle(LED3); break;
	        case 4: Board_ledToggle(LED4); break;
	        case 5: Board_ledToggle(LED5); break;
	        case 6: Board_ledToggle(LED6); break;
	        default: break;
	    }
	}
}
