#include "REGX52.H" 
#include "intrins.h" 
#include "stdio.h"

sbit IN1 = P1^4; //left wheel forward
sbit IN2 = P1^3; //Left wheel reverse
sbit ENA = P1^5; //Left wheel enabled
sbit IN3 = P1^1; //Right wheel forward
sbit IN4 = P1^2; //Right wheel reverse
sbit ENB = P1^0; //Right wheel enabled

sbit E1 = P2^1; //?sensor1  Light is 0; black is 1;
sbit E2 = P0^3; //?sensor2
sbit E3 = P0^1; //?sensor3
sbit E4 = P0^5; //?sensor4
sbit E5 = P3^4; //?sensor5  

// PWM£¨0-124£©
unsigned char DutyCycle1 = 62; // Motor1PWM£¨about50%£©
unsigned char DutyCycle2 = 62; // Motor2PWM£¨about50%£©

// Timer initialization
void Timer0_Init() {
    TMOD = 0x02; 
    TH0 = 255;   
    TL0 = 255;
    ET0 = 1;     
    EA = 1;      
    TR0 = 1;     
}

//timer 0 interrupt service function
void Timer0_ISR() interrupt 1 {
    static unsigned char pwmCounter = 0; // PWM Counters.

    pwmCounter++;
    if (pwmCounter >= 125) { // PWM period is 125
        pwmCounter = 0;
    }

    // Motor 1 PWM control
    if (pwmCounter < DutyCycle1) {
        ENA = 1; // High level
    } else {
        ENA = 0; // Low level
    }

    // Motor 2 PWM control
    if (pwmCounter < DutyCycle2) {
        ENB = 1; // High level
    } else {
        ENB = 0; // Low level
    }
}

void Motor1PWM(unsigned char duty) {
    if (duty > 124) duty = 124; 
    DutyCycle1 = duty;
}

void Motor2PWM(unsigned char duty) {
    if (duty > 124) duty = 124; 
    DutyCycle2 = duty;
}


// Set the motor direction
void Motor1(unsigned char dir) {
    if (dir == 0) // stop
    {
         IN1 = 0; IN2 = 0; 
    }
    else if (dir == 1)// forward
    {
         IN1 = 1; IN2 = 0; 
    } 
    else if (dir == 2) // reverse
    {
         IN1 = 0; IN2 = 1;
    } 
}

void Motor2(unsigned char dir) {
    if (dir == 0)// stop
    {
         IN3 = 0; IN4 = 0; 
    }
    else if (dir == 1)// forward
    { 
        IN3 = 1; IN4 = 0; 
    } 
    else if (dir == 2) // reverse
    {
        IN3 = 0; IN4 = 1;
    } 
}

//delay function
void delay_nus(unsigned int i)  
{ 
  i=i/10;
  while(--i);
}   
void delay_nms(unsigned int n)  
{ 
  n=n+1;
  while(--n)  
  delay_nus(900);         
}  

//Motion status settings
void forward()
{
    Motor1(1);
    Motor2(1);
    Motor1PWM(124);
    Motor2PWM(124);
}

void back()
{
    Motor1(2);
    Motor2(2);
    Motor1PWM(50);
    Motor2PWM(50);
}

void left()
{
    Motor1(1);
    Motor2(1);
    Motor1PWM(50);
    Motor2PWM(124);

}

void right()
{
    Motor1(1);
    Motor2(1);
    Motor1PWM(124);
    Motor2PWM(50);
}

void left_big()
{
    Motor1(2);
    Motor2(1);
}

void right_big()
{
    Motor1(1);
    Motor2(2);
}

void stop()
{
    Motor1(0);
    Motor2(0);
}

void main() {

    //Initialize
    Timer0_Init(); 
    Motor1(1);     
    Motor2(1);     
    Motor1PWM(62); 
    Motor2PWM(62); 

while(1){
       if(E5 == 1){
            if(E1 == 0 && E4 == 0){
                if(E2 == 0 && E3 == 0){//00100
                    forward();
                    Motor1PWM(124);
                    Motor2PWM(124);
                }
                if(E2 == 1 && E3 == 0){//01100
                    left();
                    Motor1PWM(100);
                    Motor2PWM(124);
                }
                if(E2 == 0 && E3 == 1){//00110
                    right();
                    Motor1PWM(124);
                    Motor2PWM(100);
                }
                if(E2 == 1 && E3 == 1){//01110
                    forward();
                    Motor1PWM(62);
                    Motor2PWM(62);
                }
            }
            if(E1 == 1 && E4 == 0){
                if(E2 == 0 && E3 == 0){//10100
                    forward();
                    Motor1PWM(124);
                    Motor2PWM(124);
                }
                if(E2 == 1 && E3 == 0){//11100
                    forward();
                    Motor1PWM(124);
                    Motor2PWM(124);
                }
                if(E2 == 0 && E3 == 1){//10110
                    right();
                    Motor1PWM(124);
                    Motor2PWM(100);
                }
                if(E2 == 1 && E3 == 1){//11110
                    right();
                    Motor1PWM(124);
                    Motor2PWM(100);
                }
            }
            if(E1 == 0 && E4 == 1){
                if(E2 == 0 && E3 == 0){//00101
                    forward();
                    Motor1PWM(124);
                    Motor2PWM(124);
                }
                if(E2 == 1 && E3 == 0){//01101
                    left();
                    Motor1PWM(100);
                    Motor2PWM(124);
                }
                if(E2 == 0 && E3 == 1){//00111
                    forward();
                    Motor1PWM(124);
                    Motor2PWM(124);
                }
                if(E2 == 1 && E3 == 1){//01111
                    left();
                    Motor1PWM(100);
                    Motor2PWM(124);
                }
            }
            if(E1 == 1 && E4 == 1){
                if(E2 == 0 && E3 == 0){//10101
                    stop();
                }
                if(E2 == 1 && E3 == 0){//11101
                    stop();
                }
                if(E2 == 0 && E3 == 1){//10111
                    stop();
                }
                if(E2 == 1 && E3 == 1){//11111
                    forward();
                    Motor1PWM(124);
                    Motor2PWM(124);
                }
            }
        }
       if(E5 == 0){
            if(E1 == 0 && E4 == 0){
                if(E2 == 0 && E3 == 0){//00000
                    forward();
                    Motor1PWM(40);
                    Motor2PWM(40);
                }
                if(E2 == 1 && E3 == 0){//01000
                    left();
                    Motor1PWM(0);
                    Motor2PWM(100);
                }
                if(E2 == 0 && E3 == 1){//00010
                    right();
                    Motor1PWM(100);
                    Motor2PWM(0);
                }
                if(E2 == 1 && E3 == 1){//01010
                    forward();
                    Motor1PWM(40);
                    Motor2PWM(40);
                }
            }
            if(E1 == 1 && E4 == 0){
                if(E2 == 0 && E3 == 0){//10000
                        left();
                        Motor1PWM(100);
                        Motor2PWM(124);
                            
                }
                if(E2 == 1 && E3 == 0){//11000
                    while(1){
                        left_big();
                        Motor1PWM(100);
                        Motor2PWM(124);
                            if(E5 == 1){
                            break;
                            }
                        }
                }
                if(E2 == 0 && E3 == 1){//10010
                    while(1){
                        left_big();
                        Motor1PWM(100);
                        Motor2PWM(124);
                            if(E5 == 1){
                            break;
                            }
                        }
                }
                if(E2 == 1 && E3 == 1){//11010
                    while(1){
                        left_big();
                        Motor1PWM(100);
                        Motor2PWM(124);
                            if(E5 == 1){
                            break;
                            }
                        }
                }
            }
            if(E1 == 0 && E4 == 1){
                if(E2 == 0 && E3 == 0){//00001
                    right();
                    Motor1PWM(124);
                    Motor2PWM(100);
                }
                if(E2 == 1 && E3 == 0){//01001
                    while(1){
                        right_big();
                        Motor1PWM(124);
                        Motor2PWM(100);
                            if(E5 == 1){
                            break;
                            }
                        }
                }
                if(E2 == 0 && E3 == 1){//00011
                    while(1){
                        right_big();
                        Motor1PWM(124);
                        Motor2PWM(100);
                            if(E5 == 1){
                            break;
                            }
                        }
                }
                if(E2 == 1 && E3 == 1){//01011
                        while(1){
                        right_big();
                        Motor1PWM(124);
                        Motor2PWM(100);
                            if(E5 == 1){
                            break;
                            }
                        }
                }
            }
            if(E1 == 1 && E4 == 1){
                if(E2 == 0 && E3 == 0){//10001
                    while(1){
                        right_big();
                        Motor1PWM(124);
                        Motor2PWM(124);
                            if(E5 == 1){
                            break;
                            }
                        }
                }
                if(E2 == 1 && E3 == 0){//11001
                    stop();
                }
                if(E2 == 0 && E3 == 1){//10011
                    stop();
                }
                if(E2 == 1 && E3 == 1){//11011
                    stop();
                }
            }
        }
       
    }
}
