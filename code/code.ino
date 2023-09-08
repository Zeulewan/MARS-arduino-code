// data transfer protocol library
#include <SPI.h>
//SD card library
#include <SD.h>
//pressure/temp library
#include <Arduino_LPS22HB.h>


//initialize variables for accelerometer data
File data;
float ax, ay, az;

// this is the set up function
void setup() {
  //establish serial communication at a data rate of 9600 bits per second
  // this establishes a connection to the computer so you can print stuff to the serial monitor
  Serial.begin(9600);
  while (!Serial);


  //initialize SD card
  // while the sd card has not been connected hold the program here
  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("Failed to initialize SD card!");
    while (1); // halts the program
  }
  Serial.print("SD card initialized");

  // initilaizes barometer 
  Serial.print("Initializing barometer...");
  if (!BARO.begin()) {
    Serial.println("Failed to initialize barometer!");
    while (1); // halts the program
  }
  Serial.print("Barometer initialized");


  // initilizes data file on SD card
  data = SD.open("data.csv", FILE_WRITE);

  // if the data file exists, write the first row
  if (data) {
    data.print("time (ms)");
    data.print(",");
    
    data.print("pressure (hPa)");
    data.print("\n");
    
    data.close();
  } 
  else {
    Serial.println("Failed to initialize");
  }

    Serial.print("Initialization complete");
}

// this is the void loop, this runs indefinatly 
void loop() {
  // read the pressure
  float pressure = BARO.readPressure();


  data = SD.open("data.csv", FILE_WRITE);

  // creates a variable for the time since deployment
  long int time = millis();

  // checks if data file exists then writes to it if it does
  if (data) {
    data.print(time);
    data.print(",");
    
    data.print(pressure);
    data.print("\n");
    
    Serial.println(time);
    Serial.println(" ");
    Serial.print(pressure);

    data.close();
  } 
  else{
    delay(100);
    Serial.println("Failed to open data.csv");

  }

  delay(100);
}
