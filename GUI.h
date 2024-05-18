#ifndef CYBERDRUNK_GUI_H
#define CYBERDRUNK_GUI_H
#include "string"
#include "Inventory.h"

class GUI {
public:
    static void drawText(int x, int y, std::string text);
    static void drawHealthBar(int hp);
};


#endif //CYBERDRUNK_GUI_H
