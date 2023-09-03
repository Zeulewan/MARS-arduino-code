// pressure is in hPa
// temperature is in C
// all data on one file in future change this

#include <SPI.h>
#include <SD.h>
//pressure/temp
#include <Arduino_LPS22HB.h>
//acc gyro magnotometer
#include <Arduino_LSM9DS1.h>




//initialize vars
File data;
float ax, ay, az;
float gx, gy, gz;
float mx, my, mz;


void setup() {
  Serial.begin(9600);

  //init SD card
  while (!SD.begin(4)) {
  }
  Serial.print("Initialized SD card...");

  // init IMU (accelerometer, gyroscope, magnotometer)
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  // init temperature and barometer sensor
  if (!BARO.begin()) {
    Serial.println("Failed to initialize pressure sensor!");
    while (1);
  }

  // init data file
  data = SD.open("data.csv", FILE_WRITE);

  // initialization of csv file
  if (data) {
    data.print("time (ms)");
    data.print(",");
    
    data.print("pressure (hPa)");
    data.print(",");
    
    data.print("temperature (c)");
    data.print(",");
    
    //accelerometer
    data.print("acc sample rate (Hz): ");
    data.print(IMU.accelerationSampleRate());
    data.print(",");

    data.print("acc x (g)");
    data.print(",");

    data.print("acc y (g)");
    data.print(",");

    data.print("acc z (g)");
    data.print(",");

    //gyroscope
    data.print("gyro sample rate (Hz): ");
    data.print(IMU.gyroscopeSampleRate());
    data.print(",");

    //degrees per second
    data.print("gyro x (d/s)");
    data.print(",");

    data.print("gyro y (d/s)");
    data.print(",");

    data.print("gyro z (d/s)");
    data.print(",");

    //magnotometer
    data.print("Magnetic field sample rate (Hz)");
    data.print(IMU.magneticFieldSampleRate());
    data.print(",");

    //Magnetic Field in uT
    data.print("mag x");
    data.print(",");

    data.print("mag y");
    data.print(",");

    data.print("mag z");

    data.print("\n");
    data.close();

  }

}

void loop() {
  // read the pressure and temperature values
  float pressure = BARO.readPressure();
  float temperature = BARO.readTemperature();

    // read accelerometer (ax, ay, az) gyroscope (gx, gy, xz) and magnotometer (mx, my, mz)
    if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(ax, ay, az);
    }
    if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(gx, gy, gz);
    }
    if (IMU.magneticFieldAvailable()) {
    IMU.readMagneticField(mx, my, mz);
    }

  // might be able to delete this line by not closing the file in the setup
  data = SD.open("data.csv", FILE_WRITE);

  // creates a variable for the time since deployment
  long int time = millis();


  if (data) {
    data.print(time);
    data.print(",");
    
    data.print(pressure);
    data.print(",");
    
    data.print(temperature);
    data.print(",");

    data.print(",");

    //accelerometer
    data.print(ax);
    data.print(",");

    data.print(ay);
    data.print(",");

    data.print(az);
    data.print(",");

    data.print(",");

    //gyroscope
    data.print(gx);
    data.print(",");

    data.print(gy);
    data.print(",");

    data.print(gz);
    data.print(",");

    data.print(",");

   //magnotometer
    data.print(mx);
    data.print(",");

    data.print(my);
    data.print(",");

    data.print(mz);
    data.print("\n");

    data.close();
  } 

  delay(10);
}