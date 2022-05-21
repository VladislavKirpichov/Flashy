//
// Created by vladislav on 22.04.22.
//

#include <iostream>
#include "Server.h"

int main() {
    try {
        ServerManager myServer;
        myServer.run();
    }
    catch (std::exception& ec) {
        std::cerr << ec.what() << std::endl;
    }
    catch (...) {
        std::cerr << "CRITICAL ERROR!" << std::endl;
    }
}
