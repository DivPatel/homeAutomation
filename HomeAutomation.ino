/* AUTHOR: DIVYESH HINGRAJIYA
EMAIL:DIVYESH636ATU2B@GMAIL.COM
GITHUB:github.com/DivPatel
LINKEDIN:in.linkedin.com/in/divyesh-hingrajiya-373131122
DO NOT PUBLISH CODE IN AMY RESEARCH PAPER OR WHITE PAPER AS ALL RESOURCES ARE COPYRIGHT RESERVED.
*/

/*
CONTROLS DC FAN SPEED,RGB LED WITH REMOTE.
Following code works on arduino with IR Sensor,a DC Fan and RGB LEDs.
All equipment is controlled by remote and its following HEX code is also given.
My RGB LEDa have anode common, check you's proper before using it.
*/

#include <IRremote.h>
#define COMMON_ANODE //for led

int RECV_PIN = 6; // IR Receiver - Arduino Pin Number 6

IRrecv irrecv(RECV_PIN);
decode_results results;

int redPinLed = 2; // Pin for RED LED Here
int greenPinLed = 3; //pin for Green LED Here
int bluePinLed = 4; //pin for Green LED Here
int pwmPin = 5; // Arduino Pin Number 5 to the Base of the Transistor
int pwmValue;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(redPinLed, OUTPUT);
  pinMode(greenPinLed, OUTPUT);
  pinMode(bluePinLed, OUTPUT);  
  pinMode( pwmPin, OUTPUT);
  pwmValue = 0; // Starts the program with turned off motor  
}

void loop() {
  
  if (irrecv.decode(&results)) {  
    
    analogWrite(pwmPin, pwmValue); 
    
    if (results.value == 0x1FE50AF) { // Red Button=1
      setColor(255, 0, 0);  // Sets Red Color to the RGB LED
      delay(100);
      }
    if (results.value == 0x1FED827) { // Green Button=2
       setColor(0, 255, 0);  // Green Color
      delay(100);
      }
    if (results.value == 0x1FEF807) { // Blue Button=3
      setColor(0, 0, 255);  // Blue Color
      delay(100);
      }
	  
      /*
	  
    if (results.value == 0x6623D37C) { // Yellow Button=4
      setColor(255, 255, 0);  // Yellow Color
      delay(100);
      }
      */   
	  
     if (results.value == 0x1FEE01F) { // Stop Button=0
      setColor(0, 0, 0);  // OFF
      delay(100);
      }
      
    // Code for Fan Control
    
    if (results.value == 0x1FE807F) { // PLAY Button= "->||" blue button
        pwmValue = 255; // 100% Duty Cycle | Max Speed
        }

      if (results.value == 0x1FE48B7) { // STOP Button=power off button red
        pwmValue = 0; // 0% Duty Cycke | Turned off
        }

       if (results.value == 0x1FE609F) { // Speed Increase Button= VOL +
        if(pwmValue <= 245){  
        pwmValue = pwmValue + 10; // Increases the Duty Cycle of the PWM Signal
        delay(20);     
      }   
    }
    if (results.value == 0x1FEA05F) { // Speed Decrease Button= VOL -
      if(pwmValue >= 20){
        pwmValue = pwmValue - 10; // Decreases the Duty Cycle of the PWM Signal
        delay(20);    
      }
    }
    
  Serial.print(pwmValue);
  Serial.print(" ");
  Serial.println(results.value, HEX);
    
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}


// Custom made function for activating the RGB LED 
void setColor(int red, int green, int blue)
{
  analogWrite(redPinLed, 255-red); // Sends PWM signal to the Red pin
  analogWrite(greenPinLed, 255-green);
  analogWrite(bluePinLed, 255-blue);  
}
