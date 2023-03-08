#include <prometheus-server.h>
#include <screen.h>

namespace NetworkStatScreen {
    const void loop() {
        screen.hardware.home();

        auto local_ip = Ethernet.localIP();

        if (local_ip[0] == 0) {
            screen.print_full_line("Link down!");
        }
        else {
            local_ip.printTo(screen.hardware);
        }
    }
}  // namespace NetworkStatScreen