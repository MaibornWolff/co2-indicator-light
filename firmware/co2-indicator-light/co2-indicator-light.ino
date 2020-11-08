#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "DHT.h"

#define DHTPIN D3
#define CO2PIN D2
#define LEDPIN D1

#define DHTTYPE DHT22
#define LED_COUNT 8

Adafruit_NeoPixel strip(LED_COUNT, LEDPIN, NEO_GRB + NEO_KHZ800);

DHT dht(DHTPIN, DHTTYPE);
long ppm=0;
unsigned long durationh;
unsigned long durationl;
unsigned long low;
unsigned long high;

void setup() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  pinMode(CO2PIN, INPUT);
  Serial.begin(9600);
  strip.begin();
  strip.show();
  strip.setBrightness(50);
  Serial.println("Init sensor");

  dht.begin();

  for(int i = 0; i<LED_COUNT; i++){
    strip.setPixelColor(i, strip.Color(0, 0, 255));
    strip.show();
  }
}

void updateLED(){
  uint32_t onColor = strip.Color(map(ppm, 400, 2000, 0, 255), 255 - map(ppm, 400, 2000, 50, 255), 0);
  uint32_t offColor = strip.Color(0, 0, 0);

  if(ppm>2000){
    onColor = strip.Color(255, 0, 0);
  }

  int onLEDs = map(ppm, 0, 2000, 1, 8);

  for(int i = 0; i<onLEDs; i++){
    strip.setPixelColor(i, onColor);
    strip.show();
  }
  for(int i = onLEDs; i<LED_COUNT; i++){
    strip.setPixelColor(i, offColor);
    strip.show();
  }
}
int getCO2(){
   durationh = pulseIn(CO2PIN,HIGH, 2000000);
   durationl = pulseIn(CO2PIN,LOW, 2000000);
   high = durationh/1000;
   low = durationl/1000;
   
   ppm = 5000 * (high-2)/(high+low-4); 
   return ppm;
}

unsigned long previous_millis = 0;
unsigned long interval = 20000;

void loop() {
	  if(millis() - previous_millis > interval) {
		  previous_millis = millis();
	  }

	float h = dht.readHumidity();
	float t = dht.readTemperature();
	float f = dht.readTemperature(true);

	// Read CO2 from pwm
	int ppm = getCO2();

	yield();

	updateLED();

	// Check if any reads failed and exit early (to try again).
	if (isnan(h) || isnan(t) || isnan(f)) {
	  Serial.println("Failed to read Sensor Data");
	  return;
}

// Compute heat index in Fahrenheit (the default)
float hif = dht.computeHeatIndex(f, h);
// Compute heat index in Celsius (isFahreheit = false)
float hic = dht.computeHeatIndex(t, h, false);

Serial.print("Humidity: ");
Serial.print(h);
Serial.print(" %\t");
Serial.print("Temperature: ");
Serial.print(t);
Serial.print(" *C ");
Serial.print(f);
Serial.print(" *F\t");
Serial.print("Heat index: ");
Serial.print(hic);
Serial.print(" *C ");
Serial.print(hif);
Serial.print(" *F\t");
Serial.print("CO2 concentration: ");
Serial.print(ppm);
Serial.println(" ppm ");

}
