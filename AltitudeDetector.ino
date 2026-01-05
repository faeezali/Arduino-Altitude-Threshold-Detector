#include <Wire.h>
#include <Adafruit_BMP085.h> // Unified driver for BMP180/BMP085 barometric sensors
#include <math.h>


Adafruit_BMP085 bmp;


const int LED = 13; 
const float seaLevel_hPa = 1016; // Reference pressure (hPa) for relative altitude calculation

const float ft = 0.3048;
const float ON_m  = 5.0 * ft;       
const float OFF_m = 4.8 * ft;    // Implemented hysteresis to prevent rapid LED flickering at threshold  


float startAlt = 0; 
bool ledOn = false;



// Function that averages the initial reading from the sensor
float avgAlt(int n) {
 float sum = 0;
 for (int i = 0; i < n; i++) {
   sum += bmp.readAltitude(seaLevel_hPa);
   delay(40);
 }
 return sum / n;
}


void setup() {
 pinMode(LED, OUTPUT);
 digitalWrite(LED, LOW);
 Serial.begin(9600);



 if (!bmp.begin()) {
   Serial.println("BMP180 not found");
   while (1) {}
 }

// Establish multi-sample average to filter atmospheric noise on startup
 delay(2000);                 
 startAlt = avgAlt(50);        
 Serial.println("Baseline set.");
}


void loop() {
 float alt = avgAlt(10);
 float change = fabs(alt - startAlt);   

 
 if (!ledOn && change >= ON_m) {
   ledOn = true;
   digitalWrite(LED, HIGH);
 } else if (ledOn && change <= OFF_m) {
   ledOn = false;
   digitalWrite(LED, LOW);
 }


 Serial.print("Change(m): "); Serial.println(change);
 delay(100);
}
