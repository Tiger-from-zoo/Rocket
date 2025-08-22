#include <Arduino.h>
// #include <Wire.h>


// void setup() {
//   // put your setup code here, to run once:
//   unsigned long prev_t = millis();
//   Serial.begin(9600);
//   Wire.begin();
// }

// void loop() {
//     // Serial.print("Temperature = ");
//     // Serial.print(bmp.readTemperature());
//     // Serial.println(" *C");
    
//     // Serial.print("Pressure = ");
//     // Serial.print(bmp.readPressure());
//     // Serial.println(" Pa");
    
//     // // Calculate altitude assuming 'standard' barometric
//     // // pressure of 1013.25 millibar = 101325 Pascal
//     // Serial.print("Altitude = ");
//     // Serial.print(bmp.readAltitude());
//     // Serial.println(" meters");

//     // Serial.print("Pressure at sealevel (calculated) = ");
//     // Serial.print(bmp.readSealevelPressure());
//     // Serial.println(" Pa");
//   byte error, address;
//   int nDevices;

//   Serial.println("Scanning...");

//   nDevices = 0;
//   for(address = 1; address < 127; address++ )
//   {
//     // The i2c_scanner uses the return value of
//     // the Write.endTransmisstion to see if
//     // a device did acknowledge to the address.
//     Wire.beginTransmission(address);
//     error = Wire.endTransmission();

//     if (error == 0)
//     {
//       Serial.print("I2C device found at address 0x");
//       if (address<16)
//         Serial.print("0");
//       Serial.print(address,HEX);
//       Serial.println("  !");

//       nDevices++;
//     }
//     else if (error==4)
//     {
//       Serial.print("Unknown error at address 0x");
//       if (address<16)
//         Serial.print("0");
//       Serial.println(address,HEX);
//     }
//   }
//   if (nDevices == 0)
//     Serial.println("No I2C devices found\n");
//   else
//     Serial.println("done\n");

//   delay(5000);

// }

#include <SFE_BMP180.h>
#include <Wire.h>

// You will need to create an SFE_BMP180 object, here called "pressure":

// SFE_BMP180 pressure;
int16_t AC1;
uint8_t err;
// double baseline; // baseline pressure
void setup () {
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(100000);
  Wire.beginTransmission(0x77);
  Wire.write(0xAA);
  err = Wire.endTransmission();

  Wire.requestFrom(0x77, 2);
  if (Wire.available() >= 2) {
    AC1 = Wire.read()<<8 | Wire.read();
  }
}

void loop () {
  Serial.print("AC1: ");
  Serial.println(AC1);
  Serial.println(err);
  delay(2500);
}
// double getPressure();

// void setup()
// {
//   Serial.begin(9600);
//   Serial.println("REBOOT");
//   Wire.begin();
//   Wire.setClock(400000);
//   // Initialize the sensor (it is important to get calibration values stored on the device).

//   char x = pressure.begin();
//   if (x)
//     Serial.println("BMP180 init success");
//   else
//   {
//     // Oops, something went wrong, this is usually a connection problem,
//     // see the comments at the top of this sketch for the proper connections.
//     Serial.print("Boot status: ");
//     Serial.println(pressure.begin());
//     Serial.println("BMP180 init fail (disconnected?)\n\n");
//     while(1); // Pause forever.
//   }

//   // Get the baseline pressure:
  
//   baseline = getPressure();
  
//   Serial.print("baseline pressure: ");
//   Serial.print(baseline);
//   Serial.println(" mb");  
// }

// void loop()
// {
//   double a,P;
  
//   // Get a new pressure reading:

//   P = getPressure();

//   // Show the relative altitude difference between
//   // the new reading and the baseline reading:

//   a = pressure.altitude(P,baseline);
  
//   Serial.print("relative altitude: ");
//   if (a >= 0.0) Serial.print(" "); // add a space for positive numbers
//   Serial.print(a,1);
//   Serial.print(" meters, ");
//   if (a >= 0.0) Serial.print(" "); // add a space for positive numbers
//   Serial.print(a*3.28084,0);
//   Serial.println(" feet");
  
//   delay(500);
// }


// double getPressure()
// {
//   char status;
//   double T,P,p0,a;

//   // You must first get a temperature measurement to perform a pressure reading.
  
//   // Start a temperature measurement:
//   // If request is successful, the number of ms to wait is returned.
//   // If request is unsuccessful, 0 is returned.

//   status = pressure.startTemperature();
//   if (status != 0)
//   {
//     // Wait for the measurement to complete:

//     delay(status);

//     // Retrieve the completed temperature measurement:
//     // Note that the measurement is stored in the variable T.
//     // Use '&T' to provide the address of T to the function.
//     // Function returns 1 if successful, 0 if failure.

//     status = pressure.getTemperature(T);
//     if (status != 0)
//     {
//       // Start a pressure measurement:
//       // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
//       // If request is successful, the number of ms to wait is returned.
//       // If request is unsuccessful, 0 is returned.

//       status = pressure.startPressure(3);
//       if (status != 0)
//       {
//         // Wait for the measurement to complete:
//         delay(status);

//         // Retrieve the completed pressure measurement:
//         // Note that the measurement is stored in the variable P.
//         // Use '&P' to provide the address of P.
//         // Note also that the function requires the previous temperature measurement (T).
//         // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
//         // Function returns 1 if successful, 0 if failure.

//         status = pressure.getPressure(P,T);
//         if (status != 0)
//         {
//           return(P);
//         }
//         else Serial.println("error retrieving pressure measurement\n");
//       }
//       else Serial.println("error starting pressure measurement\n");
//     }
//     else Serial.println("error retrieving temperature measurement\n");
//   }
//   else Serial.println("error starting temperature measurement\n");
// }
