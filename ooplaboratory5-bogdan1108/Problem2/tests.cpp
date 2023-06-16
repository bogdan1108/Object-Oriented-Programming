#include <iostream>
#include <vector>
#include <string>
#include "character.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"

class CharacterTest {
    public:
    static void test_getters() {
        Character character("Bogdan", 100, 1);
        assert(character.getName() == "Bogdan");
        assert(character.getHealth() == 100);
        assert(character.getLevel() == 1);
        std::cout << GREEN << "test_getters passed" << std::endl;
    }

    static void test_setters() {
        Character character("Bogdan", 100, 1);
        character.setName("Bogdan2");
        character.setHealth(200);
        character.setLevel(2);
        assert(character.getName() == "Bogdan2");
        assert(character.getHealth() == 200);
        assert(character.getLevel() == 2);
        std::cout << GREEN << "test_setters passed" << std::endl;
    }

    static void test_knight_getters() {
        Knight knight("Bogdan", 100, 1, 0.5, 10);
        assert(knight.getName() == "Bogdan");
        assert(knight.getHealth() == 100);
        assert(knight.getLevel() == 1);
        assert(knight.getArmor() == 0.5);
        assert(knight.getSwordDamage() == 10);
        std::cout << GREEN << "test_knight_getters passed" << std::endl;
    }

    static void test_knight_setters() {
        Knight knight("Bogdan", 100, 1, 0.5, 10);
        knight.setName("Bogdan2");
        knight.setHealth(200);
        knight.setLevel(2);
        knight.setArmor(0.6);
        knight.setSwordDamage(20);
        assert(knight.getName() == "Bogdan2");
        assert(knight.getHealth() == 200);
        assert(knight.getLevel() == 2);
        assert(knight.getArmor() == 0.6);
        assert(knight.getSwordDamage() == 20);
        std::cout << GREEN << "test_knight_setters passed" << std::endl;
    }

    static void test_knight_take_damage() {
        Knight knight("Bogdan", 100, 1, 0.5, 10);
        knight.takeDamage(10);
        assert(knight.getHealth() == 95);
        knight.takeDamage(10);
        assert(knight.getHealth() == 90);
        knight.takeDamage(10);
        assert(knight.getHealth() == 85);
        knight.takeDamage(10);
        assert(knight.getHealth() == 80);
        knight.takeDamage(10);
        assert(knight.getHealth() == 75);
        knight.takeDamage(10);
        assert(knight.getHealth() == 70);
        knight.takeDamage(10);
        assert(knight.getHealth() == 65);
        knight.takeDamage(10);
        assert(knight.getHealth() == 60);
        knight.takeDamage(10);
        assert(knight.getHealth() == 55);
        knight.takeDamage(10);
        assert(knight.getHealth() == 50);
        knight.takeDamage(10);
        assert(knight.getHealth() == 45);
        knight.takeDamage(10);
        assert(knight.getHealth() == 40);
        knight.takeDamage(10);
        assert(knight.getHealth() == 35);
        knight.takeDamage(10);
        assert(knight.getHealth() == 30);
        knight.takeDamage(10);
        assert(knight.getHealth() == 25);
        knight.takeDamage(10);
        assert(knight.getHealth() == 20);
        knight.takeDamage(10);
        assert(knight.getHealth() == 15);
        knight.takeDamage(10);
        assert(knight.getHealth() == 10);
        knight.takeDamage(10);
        assert(knight.getHealth() == 5);
        knight.takeDamage(10);
        assert(knight.getHealth() == 0);
        knight.takeDamage(10);
        assert(knight.getHealth() == 0);
        std::cout << GREEN << "test_knight_take_damage passed" << std::endl;
    }

    static void test_wizard_getters() {
        std::vector <std::string> spellList;
        spellList.push_back("Fireball");
        spellList.push_back("Lightning");
        spellList.push_back("Ice");
        spellList.push_back("Heal");
        spellList.push_back("Teleport");

        Wizard wizard("Bogdan", 100, 1, 100, spellList, 1);
        assert(wizard.getName() == "Bogdan");
        assert(wizard.getHealth() == 100);
        assert(wizard.getLevel() == 1);
        assert(wizard.getMana() == 100);
        assert(wizard.getSpells() == spellList);
        assert(wizard.getSpellPower() == 1);
        std::cout << GREEN << "test_wizard_getters passed" << std::endl;
    }

    static void test_wizard_setters() {
        std::vector <std::string> spellList;
        spellList.push_back("Fireball");
        spellList.push_back("Lightning");
        spellList.push_back("Ice");
        spellList.push_back("Heal");
        spellList.push_back("Teleport");

        Wizard wizard("Bogdan", 100, 1, 100, spellList, 1);
        wizard.setName("Bogdan2");
        wizard.setHealth(200);
        wizard.setLevel(2);
        wizard.setMana(200);
        wizard.setSpells(spellList);
        wizard.setSpellPower(2);
        assert(wizard.getName() == "Bogdan2");
        assert(wizard.getHealth() == 200);
        assert(wizard.getLevel() == 2);
        assert(wizard.getMana() == 200);
        assert(wizard.getSpells() == spellList);
        assert(wizard.getSpellPower() == 2);
        std::cout << GREEN << "test_wizard_setters passed" << std::endl;
    }

    static void test_wizard_castSpell() {
        std::vector <std::string> spellList;
        spellList.push_back("Fireball");
        spellList.push_back("Lightning");
        spellList.push_back("Ice");
        spellList.push_back("Heal");
        spellList.push_back("Teleport");

        Wizard wizard("Bogdan", 100, 1, 100, spellList, 1);
        wizard.castSpell("Fireball");
        assert(wizard.getMana() == 90);
        wizard.castSpell("Lightning");
        assert(wizard.getMana() == 80);
        wizard.castSpell("Ice");
        assert(wizard.getMana() == 70);
        wizard.castSpell("Heal");
        assert(wizard.getMana() == 60);
        wizard.castSpell("Teleport");
        assert(wizard.getMana() == 50);
        wizard.castSpell("Fireball");
        assert(wizard.getMana() == 40);
        wizard.castSpell("Lightning");
        assert(wizard.getMana() == 30);
        wizard.castSpell("Ice");
        assert(wizard.getMana() == 20);
        wizard.castSpell("Heal");
        assert(wizard.getMana() == 10);
        wizard.castSpell("Teleport");
        assert(wizard.getMana() == 0);
        wizard.castSpell("Fireball");
        assert(wizard.getMana() == 0);
        std::cout << GREEN << "test_wizard_castSpell passed" << std::endl;
    }

    static void runAll() {
        test_getters();
        test_setters();
        test_knight_getters();
        test_knight_setters();
        test_knight_take_damage();
        test_wizard_getters();
        test_wizard_setters();
        test_wizard_castSpell();
    }
};

int main() {
    CharacterTest::runAll();
    return 0;
}