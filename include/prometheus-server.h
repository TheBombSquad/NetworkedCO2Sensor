#pragma once

#include <SPI.h>
#include <Ethernet.h>

namespace PrometheusServer {
    extern uint8_t MAC_ADDRESS[];
    extern EthernetServer server;

    void setup();
    void loop();
}