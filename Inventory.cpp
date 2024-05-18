#include "Inventory.h"

Inventory::Inventory()
        : imperatorAmount(0), specialAmount(0), romperAmount(0), granadeAmount(0) {}

Inventory::Inventory(unsigned int imper, unsigned int spec, unsigned int romper, unsigned int gran)
        : imperatorAmount(imper), specialAmount(spec), romperAmount(romper), granadeAmount(gran) {}

unsigned int Inventory::getImperatorAmount() const {
    return imperatorAmount;
}

unsigned int Inventory::getSpecialAmount() const {
    return specialAmount;
}

unsigned int Inventory::getRomperAmount() const {
    return romperAmount;
}

unsigned int Inventory::getGranadeAmount() const {
    return granadeAmount;
}

bool Inventory::useImperator(unsigned int amount) {
    if(imperatorAmount < amount) {
        return false;
    }
    imperatorAmount -= amount;
    return true;
}

bool Inventory::useGranade(unsigned int amount) {
    if(granadeAmount < amount) {
        return false;
    }
    granadeAmount -= amount;
    return true;
}

bool Inventory::useSpecial(unsigned int amount) {
    if(specialAmount < amount) {
        return false;
    }
    specialAmount -= amount;
    return true;
}

bool Inventory::useRomper(unsigned int amount) {
    if(romperAmount < amount) {
        return false;
    }
    romperAmount -= amount;
    return true;
}

void Inventory::gainImperator(unsigned int amount) {
    imperatorAmount += amount;
}

void Inventory::gainSpecial(unsigned int amount) {
    specialAmount += amount;
}

void Inventory::gainRomper(unsigned int amount) {
    romperAmount += amount;
}

std::vector<std::string> Inventory::toString() const {
    return {std::to_string(imperatorAmount), std::to_string(specialAmount), std::to_string(romperAmount), std::to_string(granadeAmount)};
}

std::ostream& operator<<(std::ostream& os, const Inventory& inventory) {
    os << "Imperator: " << inventory.getImperatorAmount()
       << ", Special: " << inventory.getSpecialAmount()
       << ", Romper: " << inventory.getRomperAmount()
       << ", Granades: " << inventory.getGranadeAmount();
    return os;
}
