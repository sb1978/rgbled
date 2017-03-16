#include <rgbled.h>
#include <Arduino.h>
#include <inttypes.h>

//#define DEBUG
rgbled::rgbled(int led_red, int led_green, int led_blue, char kind_of_led) 
{
  _led_r = led_red; 	
  _led_g = led_green; 	
  _led_b = led_blue; 
  pinMode(_led_r, OUTPUT); // all pins are OUTPUT pins
  pinMode(_led_g, OUTPUT);
  pinMode(_led_b, OUTPUT);
  if (kind_of_led == 'a')
  {
	_kind_of_rgb = 1;
  }
  else if (kind_of_led == 'c')
  {
	_kind_of_rgb = 0;
  }
}

void rgbled::out(uint8_t red, uint8_t green, uint8_t blue) 
{
   controlLED(_led_r, red);
   controlLED(_led_g, green);
   controlLED(_led_b, blue);
   #ifdef DEBUG
   	Serial.print("rgb color = #");
   	Serial.print(red, HEX);
	Serial.print(green, HEX);
	Serial.println(blue, HEX);
   #endif 
}

void rgbled::preset(uint8_t preset_number)
{
   int j=0;
   int brightness = 0;    // how bright the LED is
   int fadeAmount = 2;    // how many points to fade the LED by
   switch (preset_number)
   {
	case 1:   //rot pulsierend
		for(int i=0; i<=99; i++)
		{
			controlLED(_led_r, brightness);
			brightness = brightness + fadeAmount;
			if (brightness == 0 || brightness == 100) 
			{
    				fadeAmount = -fadeAmount ;
  			}
    			delay(50);
		}
		controlLED(_led_r, 0);
		break;
	case 2:   //gruen pulsierend
		for(int i=0; i<=99; i++)
		{
			controlLED(_led_g, brightness);
			brightness = brightness + fadeAmount;
			if (brightness == 0 || brightness == 100) 
			{
    				fadeAmount = -fadeAmount ;
  			}
    			delay(50);
		}
		controlLED(_led_g, 0);
		break;
	case 3:   //blau pulsierend
		for(int i=0; i<=99; i++)
		{
			controlLED(_led_b, brightness);
			brightness = brightness + fadeAmount;
			if (brightness == 0 || brightness == 100) 
			{
    				fadeAmount = -fadeAmount ;
  			}
    			delay(50);
		}
		controlLED(_led_b, 0);
		break;
	case 4:   //rgb Verlauf
		brightness=0;
		for(int i=0; i<=299; i++)
		{
			j = i/50;
			switch (j)
			{
				case 0:
					controlLED(_led_r, 100);
					controlLED(_led_g, brightness);
					controlLED(_led_b, 0);
					brightness = brightness + fadeAmount;
					delay(100);
					break;
				case 1:
					controlLED(_led_r, brightness);
					controlLED(_led_g, 100);
					controlLED(_led_b, 0);
					brightness = brightness - fadeAmount;
					delay(100);
					break;	
				case 2:
					controlLED(_led_r, 0);
					controlLED(_led_g, 100);
					controlLED(_led_b, brightness);
					brightness = brightness + fadeAmount;
					delay(100);
					break;	
				case 3:
					controlLED(_led_r, 0);
					controlLED(_led_g, brightness);
					controlLED(_led_b, 100);
					brightness = brightness - fadeAmount;
					delay(100);
					break;
				case 4:
					controlLED(_led_r, brightness);
					controlLED(_led_g, 0);
					controlLED(_led_b, 100);
					brightness = brightness + fadeAmount;
					delay(100);
					break;	
				case 5:
					controlLED(_led_r, 100);
					controlLED(_led_g, 0);
					controlLED(_led_b, brightness);
					brightness = brightness - fadeAmount;
					delay(100);
					break;	
				default:
					break;
			}
			
    			
		}
	default:
		break;
   }
   delay(600);
}


void rgbled::controlLED(int led, uint8_t value) 
{
  uint8_t pwm_value=0;
  pwm_value = map(value, 0, 100, 0, 255);
  if (_kind_of_rgb == 0)
  {
	analogWrite(led, pwm_value);
  }
  else if (_kind_of_rgb == 1)
  {
	analogWrite(led, ~pwm_value);
  }
}
