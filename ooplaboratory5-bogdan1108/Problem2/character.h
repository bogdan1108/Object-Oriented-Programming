#include <iostream>
#include <cstring>
#include <vector>

class Character
{
    public:
        
        // constructor
        Character(std::string name, int health, int level);

        // destructor
        ~Character();

        // getters
        std::string getName();
        int getHealth();
        int getLevel();

        // setters
        void setName(std::string name);
        void setHealth(int health);
        void setLevel(int level);
    protected:
        std::string name;
        int health;
        int level;
};

class Knight : public Character {
            public:
                // constructor
                Knight(std::string name, int health, int level, double armor, int swordDamage);

                // destructor
                ~Knight();

                // getters
                double getArmor();
                int getSwordDamage();

                // setters
                void setArmor(double armor);
                void setSwordDamage(int swordDamage);

                // methods
                void takeDamage(double damage);
            private:
                double armor;
                int swordDamage;
        };

        class Wizard : public Character{
            public:
                // constructor
                Wizard(std::string name, int health, int level, int mana, std::vector <std::string> spells, int spellPower);

                // destructor
                ~Wizard();

                // getters
                int getMana();
                std::vector <std::string> getSpells();
                int getSpellPower();

                // setters
                void setMana(int mana);
                void setSpells(std::vector <std::string> spells);
                void setSpellPower(int spellPower);

                // methods
                bool castSpell(std::string spell);
            private:
                int mana;
                std::vector <std::string> spells;
                int spellPower;
        };
