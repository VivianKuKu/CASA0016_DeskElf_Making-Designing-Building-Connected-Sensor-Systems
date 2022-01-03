#include <Wire.h> 
#include "Adafruit_SGP30.h"
#include "Adafruit_TCS34725.h"
#include <DHT.h>
#include <LiquidCrystal.h>
#include <math.h> 
#include "Timer.h"

#include <TheThingsNetwork.h>
#define debugSerial Serial
#define loraSerial Serial1
#define freqPlan TTN_FP_EU868


#define DHTPIN 8   //Digital pin 8
#define DHTTYPE DHT22


//---------------------//
//     PRE-SETUP       //
//---------------------//

// ----LoRa----
const char *appEui = "Put in your appEui here";
const char *appKey = "Put in your appKey here";
TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);


// ----LCD----
const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


// ----dht22----
DHT dht(DHTPIN, DHTTYPE);


// ----sgp30----

Adafruit_SGP30 sgp;
uint32_t getAbsoluteHumidity(float temperature, float humidity) {
    // approximation formula from Sensirion SGP30 Driver Integration chapter 3.15
    const float absoluteHumidity = 216.7f * ((humidity / 100.0f) * 6.112f * exp((17.62f * temperature) / (243.12f + temperature)) / (273.15f + temperature)); // [g/m^3]
    const uint32_t absoluteHumidityScaled = static_cast<uint32_t>(1000.0f * absoluteHumidity); // [mg/m^3]
    return absoluteHumidityScaled;
}

// ----tcs34725----
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);


// ----Timer.h + LDR + LED----
int ldr=A0;//Set A0(Analog Input) for LDR.
int value_ldr=0;
int LED = 10;

Timer t;  //Built Timer object



//---------------------//
//        SETUP        //
//---------------------//
void setup() {
  
  debugSerial.begin(9600);
  loraSerial.begin(57600);  // Open the connection to the Lora radio
  
  lcd.begin(16, 2); // set up the LCD's number of columns and rows
 
  dht.begin(); //Initialise the DHT sensor
  
  debugSerial.println("SGP30 test");

  if (! sgp.begin()){
    debugSerial.println("Sensor not found :(");
    while (1);
  }
  debugSerial.print("Found SGP30 serial #");
  debugSerial.print(sgp.serialnumber[0], HEX);
  debugSerial.print(sgp.serialnumber[1], HEX);
  debugSerial.println(sgp.serialnumber[2], HEX);


  // ----Timer.h + LDR + LED----
  t.every(1500000,alert); // call alert function every 25 minutes
  pinMode(LED, OUTPUT);


  
  //Establish a connection to the Lora Gateway
  ttn.showStatus();
  debugSerial.println("-- JOIN");
  ttn.join(appEui, appKey);

  
}




int counter = 0;



//--------------------//
//        LOOP        //
//--------------------//
void loop() {
  

  //--------DHT22--------
  
  float humidity = dht.readHumidity(false);
  float temperature = dht.readTemperature(false);

  // false: Celsius (default)
  // true: Farenheit

  debugSerial.print("Temperature: ");
  debugSerial.println(temperature);
  debugSerial.print("Humidity: ");
  debugSerial.println(humidity);


  if (! sgp.IAQmeasure()) {
    debugSerial.println("Measurement failed");
    return;
  }
  debugSerial.print("TVOC "); debugSerial.print(sgp.TVOC); debugSerial.print(" ppb\t");
  debugSerial.print("eCO2 "); debugSerial.print(sgp.eCO2); debugSerial.println(" ppm");

  if (! sgp.IAQmeasureRaw()) {
    debugSerial.println("Raw Measurement failed");
    return;
  }
  debugSerial.print("Raw H2 "); debugSerial.print(sgp.rawH2); debugSerial.print(" \t");
  debugSerial.print("Raw Ethanol "); debugSerial.print(sgp.rawEthanol); debugSerial.println("");
 

  counter++;
  if (counter == 30) {
    counter = 0;

    uint16_t TVOC_base, eCO2_base;
    if (! sgp.getIAQBaseline(&eCO2_base, &TVOC_base)) {
      debugSerial.println("Failed to get baseline readings");
      return;
    }
    debugSerial.print("****Baseline values: eCO2: 0x"); debugSerial.print(eCO2_base, HEX);
    debugSerial.print(" & TVOC: 0x"); debugSerial.println(TVOC_base, HEX);
  }





  //--------TC34725--------

    debugSerial.println("Color sensor starts");
    uint16_t r, g, b, c, colorTemp, lux;

    tcs.getRawData(&r, &g, &b, &c);
    // colorTemp = tcs.calculateColorTemperature(r, g, b);
    colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
    lux = tcs.calculateLux(r, g, b);
  
    debugSerial.print("Color Temp: "); debugSerial.print(colorTemp, DEC); debugSerial.print(" K - ");
    debugSerial.print("Lux: "); debugSerial.print(lux, DEC); debugSerial.print(" - ");
    debugSerial.print("R: "); debugSerial.print(r, DEC); debugSerial.print(" ");
    debugSerial.print("G: "); debugSerial.print(g, DEC); debugSerial.print(" ");
    debugSerial.print("B: "); debugSerial.print(b, DEC); debugSerial.print(" ");
    debugSerial.print("C: "); debugSerial.print(c, DEC); debugSerial.print(" ");
    debugSerial.println(" ");





  //--------LCD--------
  
  lcd.clear();
  lcd.setCursor(0,0); // Sets the cursor to col 0 and row 0
  lcd.print("Temp: "); 
  lcd.print(temperature); 
  lcd.print(" C");
  lcd.setCursor(0,1); // Sets the cursor to col 1 and row 0
  lcd.print("Humi: "); 
  lcd.print(humidity); 

  delay(2000);
  

  lcd.clear();
  lcd.setCursor(0,0); // Sets the cursor to col 0 and row 0
  lcd.print("TVOC: "); 
  lcd.print(sgp.TVOC); 
  lcd.print(" ppb");
  lcd.setCursor(0,1); // Sets the cursor to col 1 and row 0
  lcd.print("eCO2: "); 
  lcd.print(sgp.eCO2); 
  lcd.print(" ppm"); 

  delay(2000);

  
  lcd.clear();
  lcd.setCursor(0,0); // Sets the cursor to col 0 and row 0
  lcd.print("ColorTemp: "); 
  lcd.print(colorTemp, DEC); 
  lcd.print(" K");
  lcd.setCursor(0,1); // Sets the cursor to col 1 and row 0
  lcd.print("Lux: "); 
  lcd.print(lux, DEC); 

  delay(2000);





   //--------Timer.h--------
  value_ldr = analogRead(ldr); //Reads the Value of LDR(light).
  debugSerial.println("LDR value is :"); //Prints the value of LDR to Serial Monitor.
  debugSerial.println(value_ldr);
  delay(1000);
  uint16_t mode;

  if(value_ldr < 110){
    
      t.update(); //update timer t
      mode = 1;
      debugSerial.println(mode);
      
  }

  if(value_ldr >= 110){
      mode = 2;
      debugSerial.println(mode);
  }


  

  //--------LoRa--------
  uint16_t humidity_lora = 100*dht.readHumidity(false);
  uint16_t temperature_lora = 100*dht.readTemperature(false);

  uint16_t TOVC_lora = sgp.TVOC;
  uint16_t eCO2_lora = sgp.eCO2;

  uint16_t ColorTemp_lora = colorTemp;
  uint16_t Lux_lora = lux;
  uint16_t Mode_lora = mode;
  
  

  byte payload[14];
  payload[0] = highByte(temperature_lora);
  payload[1] = lowByte(temperature_lora);
  
  payload[2] = highByte(humidity_lora);
  payload[3] = lowByte(humidity_lora);
  
  payload[4] = highByte(TOVC_lora);
  payload[5] = lowByte(TOVC_lora);
  
  payload[6] = highByte(eCO2_lora);
  payload[7] = lowByte(eCO2_lora);

  payload[8] = highByte(ColorTemp_lora);
  payload[9] = lowByte(ColorTemp_lora);

  payload[10] = highByte(Lux_lora);
  payload[11] = lowByte(Lux_lora);

  payload[12] = highByte(Mode_lora);
  payload[13] = lowByte(Mode_lora);

  ttn.sendBytes(payload, sizeof(payload));


}


void alert()
{
  digitalWrite(LED,HIGH);
  delay(500);
  digitalWrite(LED,LOW);
  delay(500);
  digitalWrite(LED,HIGH);
  delay(500);
  digitalWrite(LED,LOW);
  delay(500);
  digitalWrite(LED,HIGH);
  delay(500);
  digitalWrite(LED,LOW);
  delay(500);
  digitalWrite(LED,HIGH);
  delay(500);
  digitalWrite(LED,LOW);
  delay(500);
  digitalWrite(LED,HIGH);
  delay(500);
  digitalWrite(LED,LOW);
}
