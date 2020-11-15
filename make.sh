CXX="g++"
ROOT="src"
FLAGS="-Wno-c++11-extensions"
OUTPUT="-o spacefortress"
SRC="\
    $ROOT/main.cpp \
    $ROOT/ship.cpp \
    $ROOT/module.cpp \
    $ROOT/modules/generator.cpp \
    $ROOT/modules/capacitor.cpp \
    $ROOT/modules/shieldgenerator.cpp \
    $ROOT/modules/engine.cpp \
"

$CXX $FLAGS $SRC $OUTPUT
