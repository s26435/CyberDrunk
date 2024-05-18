#ifndef CYBERDRUNK2137_INVENTORY_H
#define CYBERDRUNK2137_INVENTORY_H

#include <iostream>
#include <vector>
#include <string>

class Inventory {
    unsigned int imperatorAmount;
    unsigned int specialAmount;
    unsigned int romperAmount;
    unsigned int granadeAmount;

public:
    Inventory();
    Inventory(unsigned int imper, unsigned int spec, unsigned int romper, unsigned int gran);

    [[nodiscard]] unsigned int getImperatorAmount() const;
    [[nodiscard]] unsigned int getSpecialAmount() const;
    [[nodiscard]] unsigned int getRomperAmount() const;
    [[nodiscard]] unsigned int getGranadeAmount() const;

    bool useImperator(unsigned int amount = 1);
    bool useGranade(unsigned int amount = 1);
    bool useSpecial(unsigned int amount = 1);
    bool useRomper(unsigned int amount = 1);

    void gainImperator(unsigned int amount);
    void gainSpecial(unsigned int amount);
    void gainRomper(unsigned int amount);

    [[nodiscard]] std::vector<std::string> toString() const;

    friend std::ostream& operator<<(std::ostream& os, const Inventory& inventory);
};

#endif //CYBERDRUNK2137_INVENTORY_H
