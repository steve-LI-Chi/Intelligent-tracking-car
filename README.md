# Intelligent-tracking-car
This intelligent tracking car uses STC89C52RC MCU and L298N driver chip to realize simple tracking function.I will introduce it from both software and hardware aspects.
##hardware
###BOM 
-MCU control board  
-Drive plate  
-Gray sensors  
-Motors  
-Car frame.  
-Battery   
These finished products can be purchased on the Internet, and the price is much lower than making them by oneself, so they only need to be assembled by oneself.Specific pictures can be viewed in the folder

> photo
###Gray sensor distribution.
Five separate Gray sensors are used here, named No.1, No.2, No.3, No.4 and No.5.See the file 
> Photo/8.png   

for the specific location distribution
##software
The No.2 and No.3 Gray sensors are used to fine-tune the left and right and reduce the shaking of the body during rapid movement.The No.1 and No.4 Gray sensors are used for large left and right turns, and the No.5 Gray sensors is used to determine whether the turn is stopped.FromThe No.1 to No.4 gray scale sensors realize the position PID control, and with PWM, the intelligent tracking car can achieve more flexible control.

##Supplement

This project comes with demo videos and schematics.The programming software is VScode.
