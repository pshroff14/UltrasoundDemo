// includes the LiquidCrystal Library
#include <LiquidCrystal.h> 

// includes the LcdBarGraph Library
#include <LcdBarGraph.h>

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

// Concept and inspiration from last minute engineers
// https://lastminuteengineers.com/arduino-sr04-ultrasonic-sensor-tutorial/

#include <Adafruit_Sensor.h>
#include <DHT.h>


// Maximum distance we want to ping for (in centimeters).
#define max_distance 200

#define DHTPIN 7     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Initialize DHT sensor.

// Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 



DHT dht(DHTPIN, DHTTYPE); //Creates DFT sensor pin and type

const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;

void setup() 
{
  Serial.begin(9600);
  lcd.begin(16, 2); // Initializes the interface to the LCD screen
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  dht.begin();
}

void loop() 
{
    // Reading temperature/humidity 
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // print humidity and temp in serial monitor 
  Serial.print(F(" Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println("/");
   
  // Write a pulse to the HC-SR04 Trigger Pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the response from the HC-SR04 Echo Pin
  duration = pulseIn(echoPin, HIGH);

    // Calc. speed of sound with respect to dht temp
  float sos = 331.3 + (0.606*t)+ (0.0124*h);
  int dhtdist = duration*(sos/10000)/2;

  
  // Determine distance from duration
  // Use 343 metres per second as speed of sound
  distance= duration*0.034/2;
  
  // Prints "Distance: <value>" on the first line of the LCD
  lcd.setCursor(0,0);
  lcd.print("Distance: "); 
  lcd.print(distance);
  lcd.print(" cm");


  // Prints "Distance: <value> (with respect to DHT sensor) on the second line of the LCD"
  lcd.setCursor(0,1);
  lcd.print("DHT.Dist: ");
  lcd.print(dhtdist);
  lcd.print(" cm");
  
   
// Prints "Distance: <value>" on the first line of the LCD
//  lcd.setCursor(0,1);
//  lcd.print("Humidity: "); 
//  lcd.print(h);
//  lcd.print("///");
//  lcd.print(f);
//  lcd.print("F");
//   
  }




  
