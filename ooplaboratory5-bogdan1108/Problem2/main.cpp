#include <iostream>
#include <cstring>
#include <vector>
#include "character.h"

int main()
{
    // spell list
    std::vector<std::string> spellList;
    spellList.push_back("Fireball");
    spellList.push_back("Lightning");
    spellList.push_back("Ice");
    spellList.push_back("Heal");
    spellList.push_back("Teleport");

    // create a knight
    Knight knight("Sir Lancelot", 100, 1, 0.5, 10);
    // create a wizard
    Wizard wizard("Merlin", 100, 1, 100, spellList, 1);

    std::cout << wizard.getMana() << std::endl;
    wizard.castSpell("Fireball");
    std::cout << wizard.getMana() << std::endl;

    std::cout << knight.getHealth() << std::endl;
    knight.takeDamage(10 * wizard.getSpellPower());
    std::cout << knight.getHealth() << std::endl;
    return 0;
}