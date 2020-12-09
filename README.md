       ____                 ____         __
      / _____ ___ ________ / _____  ____/ /________ ___ ___
     _\ \/ _ / _ `/ __/ -_/ _// _ \/ __/ __/ __/ -_(_-<(_-<
    /___/ .__\_,_/\__/\__/_/  \___/_/  \__/_/  \__/___/___/
       /_/


# spacefortress
Spacefortress is a science fiction command line space ship simulator.
The main inspiration for this project comes from the dwarf fortress game.  
![image](https://user-images.githubusercontent.com/4532320/100347507-c7bcfd80-2fe5-11eb-8ee2-17ef50186a7f.png)

## Build Instructions
make sure you have the requirements installed:
```
# Ubuntu/Debian only:
sudo apt install build-essentials cmake libncurses-dev

# Arch only:
sudo pacman -S base-devel cmake ncurses

# MacOS
# install command line tools and cmake (via brew or directly)
xcode-select --install
brew install cmake

# Windows 
# make sure you have your favourite build tools installed
# you need: compiler(gcc, vs), cmake, ncurses, git
# cygwin or mingw32 work fine
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


## Ship
Your character is already inside your ship when the game starts. If your ship gets destroyed, the game is over. You will also be able to share a ship with others via a crew code.

### Modules
Modules provide the main functionality for the space ship. Modules can be installed, removed,
switched online and offline, damaged, repaired and upgraded.  

### ShipOs
The ShipOs is the main interface between human and ship. It provides the crew with several programs and a terminal to control modules and systems.


## Ideas
### World:
- Strategy - SciFi  
- Multiplayer Client-Server  
- Open World  
- Procedurally generated?  
  
### Ship:
- Ship Controlle 
- alone - possible
- multiplayer - more efficient  
- Ship upgrade with materials (crafting?)
- Ship repair with materials
- Planet / Stars - resources/fue 
- Scientific core - research?
- Get tasks - get rewards - channelges
  
### Systems: 
- Jump drive - consumes fuel, jump fatigue?
- Star gates - quick travel between systems
- Safe systems w/ police
- Dangerous systems with high reward
