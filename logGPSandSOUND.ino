void logGPSandSOUND() {
  // Turn off LED
  digitalWrite(recLED, LOW);
 
 
  // See if data available
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
 
      // See if we have a complete GPS data string
      if (displayInfo() != "0") // The “0” is sent back when the GPS data for location or time isn’t valid, which will happen during a cold start. We don’t want to record those failed attempts.
      {
        // Get GPS string
        gpstext = displayInfo();
 
        // Check GPS Count
        Serial.println(gpscount);
        if (gpscount == gpsttlcount) {
 
          // LED On to indicate data to write to SD card
          digitalWrite(recLED, HIGH);
 
          //Open the file on card for writing
          File dataFile = SD.open("gpslog.csv", FILE_WRITE);
 
          if (dataFile) {
 
            // If the file is available, write to it and close the file

            //dataFile.println(F("Latitude  Longitude   Date   UTC"));       // Header
            //dataFile.println("(deg)      (deg)                   ");       // Header
            //dataFile.println("-----------------------------------");       // Header
              
            dataFile.print(gpstext); //  was dataFile.println(gpstext);
            dataFile.print(",");
            dataFile.print(analogRead(PIN_ANALOG_IN)); // new thing
            dataFile.print(",");
            dataFile.println(gps.altitude.feet()); // new thing
            dataFile.close();
 
            // Serial print GPS string for debugging
            Serial.print(gpstext); //  was Serial.println(gpstext);
            Serial.print(",");
            Serial.print(analogRead(PIN_ANALOG_IN));
            Serial.print(",");
            Serial.println(gps.altitude.feet());
          }
          // If the file isn't open print an error message for debugging
          else {
            Serial.println("error opening datalog.txt");
          }
 
        }
        // Increment GPS Count
        gpscount = gpscount + 1;
        if (gpscount > gpsttlcount) {
          gpscount = 0;
        }
      }
}
 
// Function to return GPS string
String displayInfo()
{
  // Define empty string to hold output
  String gpsdata = "";
 
  // Get latitude and longitude
  if (gps.location.isValid())
  {
    gpsdata = String(gps.location.lat(), 6);
    gpsdata += (",");
    gpsdata += String(gps.location.lng(), 6);
    gpsdata += (",");
  }
  else
  {
    return "0";
  }
 
  // Get Date
  if (gps.date.isValid())
  {
    gpsdata += String(gps.date.year());
    gpsdata += ("-");
    if (gps.date.month() < 10) gpsdata += ("0");
    gpsdata += String(gps.date.month());
    gpsdata += ("-");
    if (gps.date.day() < 10) gpsdata += ("0");
    gpsdata += String(gps.date.day());
    gpsdata += (","); // NEW
  }
  else
  {
    return "0";
  }
 
  // Space between date and time
  // gpsdata += (" ");

 
  // Get time
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) gpsdata += ("0");
    gpsdata += String(gps.time.hour());
    gpsdata += (":");
    if (gps.time.minute() < 10) gpsdata += ("0");
    gpsdata += String(gps.time.minute());
    gpsdata += (":");
    if (gps.time.second() < 10) gpsdata += ("0");
    gpsdata += String(gps.time.second());
  }
  else
  {
    return "0";
  }
 
  // Return completed string
  return gpsdata;
}
