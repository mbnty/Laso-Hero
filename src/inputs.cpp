#include "inputs.h"

inputs::inputs()
{
    //ctor
}

inputs::~inputs()
{
    //dtor
}

void inputs::keyModel(model*)
{
    switch(wParam) {
        case VK_LEFT:       // Action for model by pressing "Left" key
            break;

        case VK_RIGHT:      // Action for model by pressing "Right" key
            break;

        case VK_UP:         // Action for model by pressing "Up" key
            break;

        case VK_DOWN:       // Action for model by pressing "Down" key
            break;
    }
}

void inputs::keyPlayer()
{
    switch(wParam) {
        case VK_LEFT:       // Action for player by pressing "Left" key and "A" key
        case 0x41:
            break;

        case VK_RIGHT:      // Action for player by pressing "Right" key and "D" key
        case 0x44:
            break;

        case VK_UP:         // Action for player by pressing "Up" key and "W" key
        case 0x57:
            break;

        case VK_DOWN:       // Action for player by pressing "Down" key and "S" key
        case 0x53:
            break;
    }
}

void inputs::mousePlayer()
{
    switch(wParam) {
        case VK_LEFT:       // Action for player by pressing "Left" key and "A" key
        case 0x41:
            break;

        case VK_RIGHT:      // Action for player by pressing "Right" key and "D" key
        case 0x44:
            break;

        case VK_UP:         // Action for player by pressing "Up" key and "W" key
        case 0x57:
            break;

        case VK_DOWN:       // Action for player by pressing "Down" key and "S" key
        case 0x53:
            break;
    }
}

void inputs::keyEnv()
{

}

void inputs::keyUp()
{

}

void inputs::mouseMove(double x, double y)
{
    prev_Mx = x;
    prev_My = y;
}

void inputs::updateWParam(WPARAM param)
{
    wParam = param;
}
