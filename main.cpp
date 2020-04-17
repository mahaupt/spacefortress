#include <iostream>
#include <chrono>
#include <thread>

#include "ship.hpp"
#include "modules/generator.hpp"

int main()
{
    double refresh_rate = 1.0/1.0;
    
    Ship s = Ship("Omega", 100, 100);
    s.addFuel(100);
    s.addModule(new Generator("Generator MKI", 10, 1, 1));
    
    std::string cmd = "";
    
    do {
        std::cout << "\033c";
        s.simulate(refresh_rate);
        s.info();
        
        /*char c;
        std::cin.read(&c, sizeof(c));
        cmd = cmd + c;
        
        std::cout << std::endl;
        std::cout << "> " << cmd;*/
        
        std::this_thread::sleep_for(std::chrono::milliseconds((int)(refresh_rate*1000)));
    } while(true);
    
    
    return 0;
}