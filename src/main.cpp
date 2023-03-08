#include <Arduino.h>
#include <SparkFun_SCD30_Arduino_Library.h>
#include <Wire.h>
#include <prometheus-server.h>
#include <screen.h>

SCD30 scd30_sensor;
ActiveScreen screen;

void setup() {
    screen.hardware.begin(16, 2);
    screen.hardware.clear();

    Serial.begin(9600);

    screen.active_func = NetworkStatScreen::loop;
    PrometheusServer::setup();
}

void loop() {
    PrometheusServer::loop();
    screen.active_func();
    delay(1);
}
