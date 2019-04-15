#include "Laba2.h"
#include "stdio.h"

static const char *const mainMenu[] = {
    "=Racing UART=",
    "1. Master ",
    "2. Slave "
};
uint8_t flagMaster;
uint8_t StepFlag;
uint8_t DrawFlag;
uint8_t positionTime;
uint8_t playerposition;
uint8_t otherplayerposition;

struct damagHero{
    uint8_t centerX;
    uint8_t centerY;
    uint8_t speedX;
};
struct playerHero{
    uint8_t centerX;
    uint8_t centerY;
    uint8_t position;
};
struct playerHero player[2];
struct damagHero pers[6];

const uint8_t playerIMG[] =
{
    0x08,    // Image width in pixels
    0x01,    // Image height in rows (1 row = 8 pixels)
    0x24, 0x99, 0xff, 0xbd, 0x18, 0x7e, 0x3c, 0x18
};

const uint8_t persIMG[] =
{
    0x08,    // Image width in pixels
    0x01,    // Image height in rows (1 row = 8 pixels)
    0x18, 0x3c, 0x7e, 0x99, 0x3c, 0x66, 0x5a, 0x5a
};

const uint8_t fon[] =
{
    0x66,    // Image width in pixels
    0x08,    // Image height in rows (1 row = 8 pixels)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void GameDamageStep(){
    uint8_t i = 0;
    if(StepFlag){
        for(i=0;i<6;i++){
            if(pers[i].centerX>3){
               pers[i].centerX -= pers[i].speedX;
            }
            else{
               pers[i].centerX = 94;
            }
        }
    }
   StepFlag = 0x00;
}

void setPosition(uint8_t pos, uint8_t plr){
    if(plr){
        switch(pos){
            case 0:  player[plr].centerY = 0; break;
            case 1:  player[plr].centerY = 11; break;
            case 2:  player[plr].centerY = 21; break;
        }
    }
    else{
        switch(pos){
            case 0:  player[plr].centerY = 33; break;
            case 1:  player[plr].centerY = 44; break;
            case 2:  player[plr].centerY = 55; break;
        }
    }

}

void setPositionPlayer(){

    player[0].position = Wheel_getPosition();
    if (player[0].position > 2){
        player[0].position = 2;
    }
    setPosition(player[0].position,0);

}

void setPositionUART(){
    setPosition(player[1].position,1);
}


void DrawGame(){
    uint8_t i = 0;
    if(DrawFlag){
        Dogs102x6_imageDraw(fon, 0, 0);
        Dogs102x6_imageDrawXY(player[0].centerX,player[0].centerY,playerIMG);
        Dogs102x6_imageDrawXY(player[1].centerX,player[1].centerY,playerIMG);
        for(i=0;i<6;i++){
            Dogs102x6_imageDrawXY(pers[i].centerX, pers[i].centerY,persIMG);
        }
    }
    DrawFlag = 0;
}

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

void GameUART(){

    if(flagMaster){
        AppUart_putChar(player[0].position);
    }
    player[1].position = AppUart_getChar();

}

void UART_init(){

}


void main(void)
{
    uint8_t contrast;
    uint8_t brightness;
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    //Init start struct damagHero
    pers[0].centerX = 94;
    pers[0].centerY = 0;
    pers[1].centerX = 94;
    pers[1].centerY = 11;
    pers[2].centerX = 94;
    pers[2].centerY = 21;
    pers[0].speedX = 3;
    pers[1].speedX = 4;
    pers[2].speedX = 1;
    pers[3].centerX = 94;
    pers[3].centerY = 33;
    pers[4].centerX = 94;
    pers[4].centerY = 44;
    pers[5].centerX = 94;
    pers[5].centerY = 55;
    pers[3].speedX = 3;
    pers[4].speedX = 4;
    pers[5].speedX = 1;
    player[0].centerX = 0;
    player[0].centerY = 44;
    player[0].position =1;
    player[1].centerX = 0;
    player[1].centerY = 11;
    player[1].position =1;


    Board_init();

    // Set up LCD
    Dogs102x6_init();
    Dogs102x6_backlightInit();

    contrast = 11;      // Set Default Contrast
    brightness = 11;    // Set Default Brightness
    Dogs102x6_setBacklight(brightness);
    Dogs102x6_setContrast(contrast);
    Dogs102x6_clearScreen();

    TA0CCTL0 = CCIE;
    TA0CCR0 =  1000; //10 kHz
    TA0CTL = TASSEL_2 + MC_1 + ID_3;



     __enable_interrupt(); // ��������� ����������

    Wheel_init();
    Buttons_init(BUTTON_ALL); // �������������� ������
    Buttons_interruptEnable(BUTTON_ALL); // ��������� ���������� �� �������
    buttonsPressed = 0; // �������� ������� ������
    Dogs102x6_clearScreen();

    volatile unsigned int i;        // volatile to prevent optimization
    Dogs102x6_stringDraw(7, 0, "*S1=Enter       *", DOGS102x6_DRAW_NORMAL);

    switch (Menu_active((char **)mainMenu, 2))
       {
           case 1: flagMaster = 1; break;
           case 2: flagMaster = 0; break;
           default: break;
       }
    __enable_interrupt(); // ��������� ����������
    while(1)
    {
        __enable_interrupt();

        DrawGame();
        GameUART();
        GameDamageStep();
        setPositionPlayer();

    }
}


#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR (void)
{
    if(positionTime<50){
            positionTime++;
    }
    else{
            StepFlag = 1;
            positionTime=0;
    }
    DrawFlag = 1;
}
