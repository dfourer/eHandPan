/*

 Version 1.01 sp  -  test writting on leds
 
 Authors.  D. Fourer, B. Collin
 Date:  21-march-2024
 Last update: 17-04-2024
 Contact: dominique@fourer.fr
 
*/

// https://docs.arduino.cc/retired/hacking/hardware/PinMapping2560/


// Variables will change:
int ledState1 = LOW;             // ledState used to set the LED
int ledState2 = HIGH;
long previousMillis = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 500;           // interval at which to blink (milliseconds)

//const int pincode = 22; //

#if defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__)
  int N = 28;         //total number of pins
  int D0 = 1;         //first pin to use
  int availcodes[28]; //array to store the digital pins ids
#else
  int N = 12;         //total number of pins
  int D0 = 22;        //first pin to use
  int availcodes[12]; //array to store the digital pins ids
#endif


void setup() {
  // set the digital pin as output:
  
  for(int i=0;i<N;i++)
  {
    availcodes[i] = D0+i;
    pinMode(availcodes[i], OUTPUT);
  }
  
}

void loop()
{
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the 
  // difference between the current time and last time you blinked 
  // the LED is bigger than the interval at which you want to 
  // blink the LED.
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   

    // if the LED is off turn it on and vice-versa:
    if (ledState1 == LOW)
      ledState1 = HIGH;
    else
      ledState1 = LOW;
    if (ledState2 == LOW)
      ledState2 = HIGH;
    else
      ledState2 = LOW;
    // set the LED with the ledState of the variable:

    for(int i=0;i<N;i++)
    {
      if(i % 2 ==0 )
        digitalWrite(availcodes[i], ledState2);  //23 25  ... 49
      else
        digitalWrite(availcodes[i], ledState1); //22 - 24 - 26 ... 50
    }
  }
}

