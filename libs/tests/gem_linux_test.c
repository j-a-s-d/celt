#include "gem_testing.h"
#include "gem_linux.h"
#include <stdio.h>

#ifdef GEM_HELP
CE_MESSAGE("compile with: -Wall -Wfatal-errors -I../include -I../src -o ../bin/gem_linux_test gem_linux_test.c");
#endif

int main(void) {
    Tests.begin("GeM LINUX");
    if (is_root()) {
        Tests.run("is_root", is_root());
        Tests.print("Running with root privileges.\n");
    } else {
        Tests.run("is_root", !is_root());
        Tests.print("Not running as root.\n");
    }
    if (under_sudo()) {
        Tests.run("under_sudo", under_sudo());
        Tests.print("Running under sudo.\n");
    } else {
        Tests.run("under_sudo", !under_sudo());
        Tests.print("Not running under sudo.\n");
    }
    int val = read_port_byte(0x40); // Example: PIT timer port
    if (val >= 0) {
        Tests.run("read_port_byte", val >= 0);
        Tests.print("Read value 0x%02X from port 0x40\n", val);
    } else {
        Tests.run("read_port_byte", val == -1);
        Tests.print("Failed to read port (try with sudo!)\n");
    }
    return Tests.end();
}

