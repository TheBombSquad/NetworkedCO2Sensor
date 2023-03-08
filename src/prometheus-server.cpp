#include <prometheus-server.h>

namespace PrometheusServer {
    uint8_t MAC_ADDRESS[] = {0xC0, 0x2C, 0x02, 0xC0, 0x2C};
    EthernetServer server = EthernetServer(8080);

    void setup() {
        Ethernet.begin(MAC_ADDRESS);
    }
    void loop() {
        EthernetClient client = server.available();
        if (client) {
            bool end_of_line = true;
            while (client.connected()) {
                if (client.available()) {
                    char c = client.read();
                    if (c == '\n' && end_of_line) {
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-Type: text/plain");
                        client.println("Connection: close");  // the connection will be closed after completion of the response
                        client.println();
                        client.println("# HELP temperature_farenheit Temperature in farenheit");
                        client.println("# TYPE temperature_farenheit gauge");
                        client.print("temperature_farenheit ");
                        client.println("30.0");  // TODO
                        client.println("# HELP temperature_celsius Temperature in celsius");
                        client.println("# TYPE temperature_celsius gauge");
                        client.print("temperature_celsius ");
                        client.println("30.0");  // TODO
                        client.println("# HELP relative_humidity Relative humidity in percentage");
                        client.println("# TYPE relative_humidity gauge");
                        client.print("relative_humidity ");
                        client.println("30.0");  // TODO
                        client.println("# HELP absolute_humidity Absolute humidity");
                        client.println("# TYPE absolute_humidity gauge");
                        client.print("absolute_humidity ");
                        client.println("30.0");  // TODO
                        client.println("# HELP co2_ppm Amount of CO2 in the air in ppm");
                        client.println("# TYPE co2_ppm gauge");
                        client.print("co2_ppm ");
                        client.println("30.0");  // TODO
                        break;
                    }
                    else if (c == '\n') {
                        end_of_line = true;
                    }
                    else if (c != '\r') {
                        end_of_line = false;
                    }
                }
            }
            delay(10);
            client.stop();
        }
    }
}  // namespace PrometheusServer