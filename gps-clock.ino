#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Create a TinyGPS++ object
TinyGPSPlus gps;

// Create a SoftwareSerial object for GPS communication
SoftwareSerial ss(4, 3); // RX, TX

// Variables to store UTC hour and minute
int utcHour;
int utcMinute;

// Define the hour offset
int hourOffset = 2;

void setup() {
  // Start the serial communication
  Serial.begin(9600);
  ss.begin(9600);

  // Set pin 4 as input
  pinMode(4, INPUT);
}

void loop() {
  // Read GPS data
  while (ss.available() > 0) {
    gps.encode(ss.read());
  }

  // Check if a valid time is available
  if (gps.time.isValid()) {
    // Extract UTC hour and minute
    utcHour = gps.time.hour();
    utcMinute = gps.time.minute();

    // Read digital pin 4, if it's high, add another hour to the hourOffset
    if (digitalRead(4) == HIGH) {
      hourOffset++;
    }

    // Add the hour offset and wrap around midnight
    utcHour = (utcHour + hourOffset) % 24;

    // Print the UTC hour and minute
    Serial.print("UTC Time: ");
    Serial.print(utcHour);
    Serial.print(":");
    Serial.println(utcMinute);
  }
}
