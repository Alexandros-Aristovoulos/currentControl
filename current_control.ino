/*
 * You can find the DHT Library from Arduino official website
 * https://playground.arduino.cc/Main/DHTLib
 */
#include <LiquidCrystal.h> // includes the LiquidCrystal Library
#include <dht.h>

#define dataPin 8

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
dht DHT;

boolean prevStatus;  //true for off
int power = 12;     //pin that controls the fridge

void setup() {
  // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
  lcd.begin(16,2); 

  //pin that controls the fridge
  pinMode(power, OUTPUT);
  
  prevStatus = false; //true for off
}

void loop() {
  lcd.clear(); //clear the display
  int readData = DHT.read22(dataPin);
  float t = DHT.temperature;
  float h = DHT.humidity;
  
  lcd.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
  lcd.print("Temp.: "); // Prints string "Temp." on the LCD
  lcd.print(t); // Prints the temperature value from the sensor
  lcd.print(" C");
  lcd.setCursor(0,1);
  lcd.print("Fridge is: ");


//decide if you should turn of the fridge
//if(t<1) fridge is off
//if(t>2) fridge is on
//if(1<t<2) fridge continues what it did

  if(t < 1){
    lcd.print("OFF");
    digitalWrite(power, HIGH);  
    prevStatus = true;
  }else if(t>2){
    lcd.print("ON");
    digitalWrite(power, LOW);
    prevStatus = false;
  }else{
    if(prevStatus){
      lcd.print("OFF");
      digitalWrite(power, HIGH);
      prevStatus = true;
    }else{
      lcd.print("ON");
    digitalWrite(power, LOW);
    prevStatus = false;
    }
  }
  delay(2000);
}
