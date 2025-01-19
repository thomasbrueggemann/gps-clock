#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Create a TinyGPS++ object
TinyGPSPlus gps;

// Create a SoftwareSerial object for GPS communication
SoftwareSerial ss(3, 2); // RX, TX

// Variables to store UTC hour and minute
int utcHour;
int utcMinute;

// Variables to store individual digits of UTC hour and minute
int utcHourTens;
int utcHourOnes;
int utcMinuteTens;
int utcMinuteOnes;

// Define the hour offset
int hourOffset = 1;

void setup() {
  // Start the serial communication
  Serial.begin(9600);
  ss.begin(9600);

  // Set pin 3 as input
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
      hourOffset = 2;
    } else {
      hourOffset = 1;
    }

    // Add the hour offset and wrap around midnight
    utcHour = (utcHour + hourOffset) % 24;

    // Split UTC hour and minute into individual digits
    splitTimeDigits();

    // Print the UTC hour and minute
    Serial.print("Time: ");
    Serial.print(utcHour);
    Serial.print(":");
    Serial.println(utcMinute);

    // Print the individual digits of UTC hour and minute
    Serial.print("Hour Tens: ");
    Serial.println(utcHourTens);
    Serial.print("Hour Ones: ");
    Serial.println(utcHourOnes);
    Serial.print("Minute Tens: ");
    Serial.println(utcMinuteTens);
    Serial.print("Minute Ones: ");
    Serial.println(utcMinuteOnes);

    delay(1000);
  }
}

// Function to split UTC hour and minute into individual digits
void splitTimeDigits() {
  utcHourTens = utcHour / 10;
  utcHourOnes = utcHour % 10;
  utcMinuteTens = utcMinute / 10;
  utcMinuteOnes = utcMinute % 10;
}
