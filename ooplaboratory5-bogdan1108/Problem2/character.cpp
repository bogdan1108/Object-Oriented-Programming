#include <iostream>
#include <cstring>
#include <vector>
#include "character.h"

// constructor for character
Character::Character(std::string name, int health, int level) :
    name(name), health(health), level(level)
{}

// destructor for character
Character::~Character() {}

// getters for character
std::string Character::getName() {
    return name;
}

int Character::getHealth() {
    return health;
}

int Character::getLevel() {
    return level;
}

// setters for character
void Character::setName(std::string name) {
    this->name = name;
}

void Character::setHealth(int health) {
    this->health = health;
}

void Character::setLevel(int level) {
    this->level = level;
}

// constructor for knight
Knight::Knight(std::string name, int health, int level, double armor, int swordDamage) :
    Character(name, health, level), armor(armor), swordDamage(swordDamage)
{}

// destructor for knight
Knight::~Knight() {}

// getters for knight
double Knight::getArmor() {
    return armor;
}

int Knight::getSwordDamage() {
    return swordDamage;
}

// setters for knight
void Knight::setArmor(double armor) {
    this->armor = armor;
}

void Knight::setSwordDamage(int swordDamage) {
    this->swordDamage = swordDamage;
}

// methods for knight
void Knight::takeDamage(double damage) {
    if (this->armor > 0) {
        this->health -= damage * (1 - this->armor);
        if (this->health < 0) {
            this->health = 0;
        }
    }
    else {
        this->health -= damage;
        if (this->health < 0) {
            this->health = 0;
        }
    }
}

// constructor for wizard
Wizard::Wizard(std::string name, int health, int level, int mana, std::vector <std::string> spells, int spellPower) :
    Character(name, health, level), mana(mana), spells(spells), spellPower(spellPower)
{}

// destructor for wizard
Wizard::~Wizard() {}

// getters for wizard
int Wizard::getMana() {
    return mana;
}

std::vector <std::string> Wizard::getSpells() {
    return spells;
}

int Wizard::getSpellPower() {
    return spellPower;
}

// setters for wizard
void Wizard::setMana(int mana) {
    this->mana = mana;
}

void Wizard::setSpells(std::vector <std::string> spells) {
    this->spells = spells;
}

void Wizard::setSpellPower(int spellPower) {
    this->spellPower = spellPower;
}

// methods for wizard
bool Wizard::castSpell(std::string spell) {
    for (int i = 0; i < this->spells.size(); i++) {
        if (this->spells[i] == spell) {
            this->mana -= 10;
            if (this->mana < 0) {
                this->mana = 0;
            }
            return true;
        }
    }
    return false;
}

