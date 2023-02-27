#include <Arduino.h>
#include <Wire.h>
#include <SparkFun_SCD30_Arduino_Library.h>
#include <LCDKeypad.h>
#include <Ethernet.h>
#include <SPI.h>

SCD30 scd30_sensor;
LCDKeypad lcd_screen;
byte MAC_ADDRESS[] = {0xC0, 0x2C, 0x02, 0xC0, 0x2C};
EthernetServer server = EthernetServer(8080);

void setup()
{
  lcd_screen.begin(16, 2);
  lcd_screen.clear();

  Serial.begin(9600);

  lcd_screen.write("Connecting...");
  if (!Ethernet.begin(MAC_ADDRESS))
  {
    lcd_screen.clear();
    Serial.println("Failed to obtain IP address");
    lcd_screen.write("DHCP failed!");
  }

  lcd_screen.clear();
  auto ip = Ethernet.localIP();
  ip.printTo(lcd_screen);
  lcd_screen.setCursor(0, 1);

  server.begin();
}

void loop()
{
  EthernetClient client = server.available();
  if (client)
  {
    Serial.println("found client");
    bool eol = true;
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        Serial.write(c);
        if (c == '\n' && eol)
        {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/plain");
          client.println("Connection: close"); // the connection will be closed after completion of the response
          client.println();
          client.println("# HELP temperature_farenheit Temperature in farenheit");
          client.println("# TYPE temperature_farenheit gauge");
          client.print("temperature_farenheit ");
          client.println("30.0"); // TODO
          client.println("# HELP temperature_celsius Temperature in celsius");
          client.println("# TYPE temperature_celsius gauge");
          client.print("temperature_celsius ");
          client.println("30.0"); // TODO
          client.println("# HELP relative_humidity Relative humidity in percentage");
          client.println("# TYPE relative_humidity gauge");
          client.print("relative_humidity ");
          client.println("30.0"); // TODO
          client.println("# HELP absolute_humidity Absolute humidity");
          client.println("# TYPE absolute_humidity gauge");
          client.print("absolute_humidity ");
          client.println("30.0"); // TODO
          client.println("# HELP co2_ppm Amount of CO2 in the air in ppm");
          client.println("# TYPE co2_ppm gauge");
          client.print("co2_ppm ");
          client.println("30.0"); // TODO
          break;
        }
        if (c == '\n')
        {
          eol = true;
        }
        else if (c != '\r')
        {
          eol = false;
        }
      }
    }
    delay(1);
    client.stop();
    Serial.println("dc'd client");
  }
}
