#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Processor.h"

using namespace sf;

int main()
{

    Processor chip8 = Processor();
    chip8.init("roms/VBRIX");
    chip8.loop();

    return 0;
}