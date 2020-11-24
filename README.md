       ____                 ____         __
      / _____ ___ ________ / _____  ____/ /________ ___ ___
     _\ \/ _ / _ `/ __/ -_/ _// _ \/ __/ __/ __/ -_(_-<(_-<
    /___/ .__\_,_/\__/\__/_/  \___/_/  \__/_/  \__/___/___/
       /_/


# spacefortress
Spacefortress is a science fiction command line space ship simulator.
The main inspiration for this project comes from the dwarf fortress game.  
![image](https://user-images.githubusercontent.com/4532320/100129593-076ad480-2e82-11eb-8e4b-226d3bd80598.png)

## Build Instructions
make sure you have the requirements installed:
```
# Ubuntu/Debian only:
sudo apt install build-essentials cmake libncurses-dev

# Arch only:
sudo pacman -S base-devel cmake ncurses
```
clone the repository:
```
git clone https://github.com/cbacon93/spacefortress.git
cd spacefortress
git submodule  update --init --recursive
```
build the project:
```
cmake .
make
```  


## Ships
### Modules
Modules provide the main functionality for the space ship. Modules can be installed, removed,
switched online and offline, damaged and repaired.  
Current module ideas:  
- Reactor (power generation)  
- Cargo  
- Shield Generator  
- Engine  
- Capacitor  (power storage)  
- Jump Drive  
- Weapons  
- Life Support  

### Reactor (power generation)
The reactor creates power for the ships modules.


## Ideas
Strategie - SciFi

Person
Schiff Kontroller
- alleine - Multitasking
- Gemeinsam - Effizienter

Erde - Erde muss verlassen werden
(Prototypschiff / Fehler / Fehler fixen)
Planeten Treibstoff holen
Ehemalige Zivilplaneten - Ressourcen
Schiff upgraden - Wissenschaftscore
Rätsel sammeln -> Verstorbenen Zivilisationen -> Koordinaten

Systeme // Sprungantrieb
