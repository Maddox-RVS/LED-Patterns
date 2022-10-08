// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        2 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 50 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int DELAYVAL = 40; // Time (in milliseconds) to pause between pixels
int LEDcolor = 0;
bool trough = true;

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.
 Serial.begin(9600); 
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  Serial.print("-Start\n-For loop 1\n"); 

  for(int i=0, j=NUMPIXELS; i<NUMPIXELS; i++, j--) { 
    Serial.println(i);

    switch (LEDcolor)
    {
      case 0:
        pixels.setPixelColor(i-1, pixels.Color(0, 0, 255));
        pixels.setPixelColor(j, pixels.Color(255, 0, 0));
        break;
      case 1:
        pixels.setPixelColor(i-1, pixels.Color(0, 255, 100));
        pixels.setPixelColor(j, pixels.Color(100, 255, 0));
        break;
      case 2:
        pixels.setPixelColor(i-1, pixels.Color(0, 255, 0));
        pixels.setPixelColor(j, pixels.Color(255, 0, 100));
        break;
      case 3:
        pixels.setPixelColor(i-1, pixels.Color(0, 255, 0));
        pixels.setPixelColor(j, pixels.Color(100, 0, 255));
        break;
      case 4:
        pixels.setPixelColor(i-1, pixels.Color(100, 255, 100));
        pixels.setPixelColor(j, pixels.Color(100, 200, 255));
        break;
    }

    pixels.show();
    if (i != NUMPIXELS-1)
    {  
      delay(DELAYVAL);
      pixels.clear(); 
    }     
  }

  if (LEDcolor == 4)
      {
        LEDcolor = 0;
      }
  LEDcolor++;

  if (trough == true)
  {
    DELAYVAL -= 5;

    if (DELAYVAL <= 0)
    {
      trough = false;
    }
  }
  else if (trough == false)
  {
    DELAYVAL += 5;

    if (DELAYVAL >= 40)
    {
      trough = true;
    }
  }
  
  Serial.print("-End\n");
}
