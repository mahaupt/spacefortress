#include <iostream>
#include "ship.hpp"
#include "modules/generator.hpp"

int main()
{
    Ship s = Ship("Omega", 100, 100);
    s.addFuel(100);
    s.addModule(new Generator("Generator MKI", 10, 1, 1));
    
    std::string input;
    do {
        std::cout << std::endl;
        s.info();
        s.simulate(1);
        
        std::cin >> input;
    } while(input != "q");
    
    
    return 0;
}