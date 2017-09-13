/* GPS module for OnStepESPServer

   by Roman Hujer (roman@hujer.net)

   Copyright (C) 2017  Roman Hujer

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef GPS_ON

void OnStepGPS() {

  //read GPS data
  for (unsigned long start = millis(); millis() - start < 1000;) {
    while (gpsSerial.available() > 0)
      if (gps.encode(gpsSerial.read()))
        ProcGPSData();
    if (millis() > 5000 && gps.charsProcessed() < 10) {
      GPS_sync  = false;
#ifdef DEBUG_X_ON
      Serial.println("No GPS detected: check wiring.");
#endif
    }
  }
}
void ProcGPSData () {
  //  int   g_year;
  //  byte  g_month, g_day, g_hour, g_minute, g_second, g_sats;
  //  float g_alt;

  char ss_temp[12];
  if (gps.satellites.isValid() && gps.location.isValid() && gps.date.isValid() && gps.time.isValid() && gps.altitude.isValid() ) {
    g_sats   = gps.satellites.value();
    g_lat    = gps.location.lat();
    g_lon    = gps.location.lng();
    g_year   = gps.date.year();
    g_month  = gps.date.month();
    g_day    = gps.date.day();
    g_hour   = gps.time.hour();
    g_minute = gps.time.minute();
    g_second = gps.time.second();
    g_alt    = gps.altitude.meters();

    if ( GPS_upload_request ) {

#ifdef DEBUG_ON
      Serial.println(":");
      Serial.print(" SAT: " );
      Serial.print( g_sats  );
      Serial.print(" LAT: " );
      Serial.print( g_lat  );
      Serial.print(" LON: " );
      Serial.print( g_lon );
      Serial.print(" ALT: " );
      Serial.println( g_alt );
      sprintf(ss_temp, "%02d/%02d/%02d", g_day, g_month, g_year );
      Serial.print(" Date: " );
      Serial.println( ss_temp );
      sprintf(ss_temp, "%02d:%02d:%02d", g_hour, g_minute, g_second);
      Serial.print(" Time: " );
      Serial.println( ss_temp );
#endif
      if (g_sats > 3 ) {
   
         GPS_sync  = true;
        // Set UTC offset to 0
        Serial.print(":SG+00#");

        // Set date:  :SCMM/DD/YY#
        sprintf(ss_temp, ":SC%02d/%02d/%02d#", g_month, g_day, g_year - 2000);
        Serial.print( ss_temp );

        // Set time:  :SLHH:MM:SS#
        sprintf(ss_temp, ":SL%02d:%02d:%02d#", g_hour, g_minute, g_second);
        Serial.print( ss_temp );

        // Set Latitude (for current site)  :StsDD*MM#
        if ( g_lat > 0 ) {
          sprintf(ss_temp, ":St+%02d*%02d#", int(g_lat), i_g_min( g_lat ));
        } else {
          sprintf(ss_temp, ":St-%02d*%02d#", int(-g_lat), i_g_min( -g_lat ));
        }
        Serial.print( ss_temp );

        // Set Longitude (for current site) :SgDDD*MM#
        if ( g_lon > 0 ) {
          sprintf(ss_temp, ":Sg-%03d*%02d#", int(g_lon), i_g_min( g_lon ) );
        } else {
          sprintf(ss_temp, ":Sg+%03d*%02d#", int(-g_lon), i_g_min( -g_lon ));
        }
        Serial.print( ss_temp );

        GPS_upload_request = false;
    } else  {
      GPS_sync  = false;
#ifdef DEBUG_X_ON
      Serial.println("Satelite low count");
#endif
     }
    }  // GPS_upload_request
  } else  {
    GPS_sync  = false;
#ifdef DEBUG_X_ON
    Serial.println("Invalid GPS Data");
    delay(1000);
#endif
  }
}

int i_g_min ( float g_in)
{
  return int((g_in - int(g_in) * 1.) * 60. + 0.5);
}

int i_g_min_s ( float g_in)
{
  return int((g_in - int(g_in) * 1.) * 60. );
}

int i_g_sec_s ( float g_in)
{
  return int(((g_in - int(g_in) * 1.) * 3600. + 0.5 ) - int((g_in - int(g_in) * 1.) * 60.) * 60);
}

#endif
