#include "Laba3.h"
#include "stdio.h"


#define ADC_PORT_SEL  P6SEL
#define ADC_INPUT_A6  BIT6

uint16_t positionData;
uint16_t positionTime;
uint8_t posY;
uint8_t posX;
uint8_t VoltH;
uint8_t VoltL;
uint8_t flagX;
uint16_t positionDataOld;
uint8_t flagDraw;
uint16_t div;

void init_ADC(){

    ADC12CTL0 = ADC12SHT02 + ADC12ON;                  // Sampling time, ADC12 on
    ADC12CTL1 = ADC12SHP;                              // Use sampling timer
    ADC12MCTL0 = ADC12INCH_6;                          // Use A6 as input
    ADC12CTL0 |= ADC12ENC;                             // Enable conversions
    ADC_PORT_SEL |= ADC_INPUT_A6;

}

void DrawOscil(){
    uint8_t Buffer[15]={0};
    if(flagDraw){
        Dogs102x6_pixelDraw(posX,58-posY,DOGS102x6_DRAW_NORMAL);
        flagDraw = 0;
    }
    sprintf(Buffer,"Volt=%d.%d",VoltH,VoltL);
    Dogs102x6_stringDraw(0,0,Buffer,DOGS102x6_DRAW_NORMAL);
}



void prescalseY(){
    posY = positionData/86;
}
void prescalseX(){
    if(flagX){
        if(posX<98){
            posX++;
            flagDraw = 1;
        }else{
            posX = 3;
            Dogs102x6_clearScreen();
            Dogs102x6_stringDrawXY(80,11,"3.6",DOGS102x6_DRAW_NORMAL);
            Dogs102x6_stringDrawXY(80,50,"0.0",DOGS102x6_DRAW_NORMAL);
            DrawXY();

        }
    }
    flagX=0;
}

void DrawXY(){
    Dogs102x6_horizontalLineDraw(2,98,9,DOGS102x6_DRAW_NORMAL);
    Dogs102x6_horizontalLineDraw(2,98,21,DOGS102x6_DRAW_NORMAL);
    Dogs102x6_horizontalLineDraw(2,98,33,DOGS102x6_DRAW_NORMAL);
    Dogs102x6_horizontalLineDraw(2,98,45,DOGS102x6_DRAW_NORMAL);
    Dogs102x6_horizontalLineDraw(2,98,58,DOGS102x6_DRAW_NORMAL);
    Dogs102x6_verticalLineDraw(9,58,2,DOGS102x6_DRAW_NORMAL);
    Dogs102x6_verticalLineDraw(9,58,14,DOGS102x6_DRAW_NORMAL);
    Dogs102x6_verticalLineDraw(9,58,26,DOGS102x6_DRAW_NORMAL);
    Dogs102x6_verticalLineDraw(9,58,38,DOGS102x6_DRAW_NORMAL);
    Dogs102x6_verticalLineDraw(9,58,50,DOGS102x6_DRAW_NORMAL);
    Dogs102x6_verticalLineDraw(9,58,62,DOGS102x6_DRAW_NORMAL);
    Dogs102x6_verticalLineDraw(9,58,74,DOGS102x6_DRAW_NORMAL);
    Dogs102x6_verticalLineDraw(9,58,86,DOGS102x6_DRAW_NORMAL);
    Dogs102x6_verticalLineDraw(9,58,98,DOGS102x6_DRAW_NORMAL);
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

    Dogs102x6_setBacklight(brightness);
    Dogs102x6_setContrast(contrast);
    Dogs102x6_clearScreen();

    init_ADC();
    ADC12IE = 0x01;
    ADC12CTL0 |= ADC12SC;// Enable interrupt

    TA0CCTL0 = CCIE;
    TA0CCR0 =  100; //10 kHz
    TA0CTL = TASSEL_2 + MC_1 + ID_0;

    flagDraw = 0;
    posY = 0;
    posX = 3;
    div=10;
     __enable_interrupt(); // Разрешаем прерывания


    Buttons_init(BUTTON_ALL); // Инициализируем кнопки
    Buttons_interruptEnable(BUTTON_ALL); // Разрешаем прерывания по кнопкам
    buttonsPressed = 0; // обнуляем нажатие кнопки

    Dogs102x6_clearScreen();
    Dogs102x6_stringDrawXY(80,11,"3.6",DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDrawXY(80,50,"0.0",DOGS102x6_DRAW_NORMAL);
    //Dogs102x6_stringDraw(0,0,"10 kHz",DOGS102x6_DRAW_NORMAL);
    DrawXY();
    float temp;
    volatile unsigned int i;        // volatile to prevent optimization

    while(1)
    {
        DrawOscil();
        prescalseY();
        prescalseX();
        temp = (positionData/4)*3.6;
        VoltH=  temp/1000;
        VoltL=  temp-VoltH*1000;
        while((buttonsPressed & BUTTON_S1)){
            if(div<10000){
                div=div*10;
            }
            else{
                div=10;
            }
            buttonsPressed =0;
        }
    }
}


#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
    switch (__even_in_range(ADC12IV, ADC12IV_ADC12IFG15))
    {
        // Vector  ADC12IV_NONE:  No interrupt
        case  ADC12IV_NONE:
            break;

        // Vector  ADC12IV_ADC12OVIFG:  ADC overflow
        case  ADC12IV_ADC12OVIFG:
            break;

        // Vector  ADC12IV_ADC12TOVIFG:  ADC timing overflow
        case  ADC12IV_ADC12TOVIFG:
            break;

        // Vector  ADC12IV_ADC12IFG0: ADC12IFG0:
        case  ADC12IV_ADC12IFG0:
            positionData = ADC12MEM0;                  // ADC12MEM = A0 > 0.5AVcc?
            //__bic_SR_register_on_exit(LPM0_bits);      // Exit active CPU
            break;

        // Vector  ADC12IV_ADC12IFG1:  ADC12IFG1
        case  ADC12IV_ADC12IFG1:
            break;

        // Vector ADC12IV_ADC12IFG2:  ADC12IFG2
        case ADC12IV_ADC12IFG2:
            break;

        // Vector ADC12IV_ADC12IFG3:  ADC12IFG3
        case ADC12IV_ADC12IFG3:
            break;

        // Vector ADC12IV_ADC12IFG4:  ADC12IFG4
        case ADC12IV_ADC12IFG4:
            break;

        // Vector ADC12IV_ADC12IFG5:  ADC12IFG5
        case ADC12IV_ADC12IFG5:
            break;

        // Vector ADC12IV_ADC12IFG6:  ADC12IFG6
        case ADC12IV_ADC12IFG6:
            break;

        // Vector ADC12IV_ADC12IFG7:  ADC12IFG7
        case ADC12IV_ADC12IFG7:
            break;

        // Vector ADC12IV_ADC12IFG8:  ADC12IFG8
        case ADC12IV_ADC12IFG8:
            break;

        // Vector ADC12IV_ADC12IFG9:  ADC12IFG9
        case ADC12IV_ADC12IFG9:
            break;

        // Vector ADC12IV_ADC12IFG10:  ADC12IFG10
        case ADC12IV_ADC12IFG10:
            break;

        // Vector ADC12IV_ADC12IFG11:  ADC12IFG11
        case ADC12IV_ADC12IFG11:
            break;

        // Vector ADC12IV_ADC12IFG12:  ADC12IFG12
        case ADC12IV_ADC12IFG12:
            break;

        // Vector ADC12IV_ADC12IFG13:  ADC12IFG13
        case ADC12IV_ADC12IFG13:
            break;

        // Vector ADC12IV_ADC12IFG14:  ADC12IFG14
        case ADC12IV_ADC12IFG14:
            break;

        // Vector ADC12IV_ADC12IFG15:  ADC12IFG15
        case ADC12IV_ADC12IFG15:
            break;

        default:
            break;
    }
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR (void)
{
    if(positionTime<div){
        positionTime++;
    }
    else{
        flagX=1;
        positionTime=0;
    }
    ADC12CTL0 |= ADC12SC;// Enable interrupt
    //Board_ledToggle(LED1);

}

