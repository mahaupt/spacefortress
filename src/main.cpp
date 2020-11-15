#include <iostream>
#include <chrono>
#include <thread>

#include "ship.hpp"
#include "modules/generator.hpp"
#include "modules/capacitor.hpp"

int main()
{
    Ship s = Ship("Omega", 100);
    s.addModule(new Generator("Generator MK I", 1, 1));
    s.addModule(new Capacitor("Capacitor MK I", 1, 100, 1, 10));

    std::string cmd = "";
    double simTime = 0.1;

    while(true) {
        auto start_time = std::chrono::steady_clock::now();

        std::cout << "\033c";
        s.simulate(simTime);
        s.info();
        std::cout << "Simulating " << simTime << " seconds" << std::endl;



        std::cin >> cmd;
        if (cmd == "q")
        {
            break;
        }

        auto end_time = std::chrono::steady_clock::now();
        simTime = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count()/1000.0;

    }


    return 0;
}
