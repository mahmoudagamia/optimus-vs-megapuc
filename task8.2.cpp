#include <iostream>
#include <string>
#include <cstdlib> // For srand() and rand()
#include <ctime>   // For time()
#include <unistd.h> // For sleep() (Unix/Linux/Mac). For Windows, use <windows.h> and Sleep()

// Abstract base class for a Weapon
class Weapon {
protected:
    std::string name;
    int damage;
    int accuracy; // As a percentage (e.g., 80 means 80%)

public:
    Weapon(const std::string& n, int d, int acc) : name(n), damage(d), accuracy(acc) {}
    virtual ~Weapon() {}

    // Pure virtual function to make this an abstract class
    // This function will handle the attack logic for each specific weapon.
    virtual bool attack(const std::string& attackerName, const std::string& targetName, int& targetHealth) = 0;

    std::string getName() const { return name; }
};

// Concrete class for Optimus Prime's Ion Rifle
class IonRifle : public Weapon {
public:
    IonRifle() : Weapon("Ion Rifle", 6, 100) {}

    bool attack(const std::string& attackerName, const std::string& targetName, int& targetHealth) override {
        // Accuracy is 100%, so it always hits.
        std::cout << attackerName << " uses " << name << " on " << targetName << ". It's a direct hit!" << std::endl;
        targetHealth -= damage;
        return true;
    }
};

// Concrete class for Optimus Prime's Energon Swords
class EnergonSwords : public Weapon {
public:
    EnergonSwords() : Weapon("Energon Swords", 12, 80) {}

    bool attack(const std::string& attackerName, const std::string& targetName, int& targetHealth) override {
        std::cout << attackerName << " swings the " << name << " at " << targetName << "..." << std::endl;
        sleep(1); // Pause for drama

        int randomValue = (rand() % 100) + 1; // Generate number between 1-100
        if (randomValue <= accuracy) {
            std::cout << "The attack hits! " << targetName << " takes " << damage << " damage." << std::endl;
            targetHealth -= damage;
            return true;
        } else {
            std::cout << "The attack missed!" << std::endl;
            return false;
        }
    }
};

// Concrete class for Optimus Prime's Shoulder Canon
class ShoulderCanon : public Weapon {
public:
    ShoulderCanon() : Weapon("Shoulder Canon", 45, 25) {}

    bool attack(const std::string& attackerName, const std::string& targetName, int& targetHealth) override {
        std::cout << attackerName << " charges the mighty " << name << "!..." << std::endl;
        sleep(2); // Longer pause for more drama

        int randomValue = (rand() % 100) + 1;
        if (randomValue <= accuracy) {
            std::cout << "BOOM! A devastating hit! " << targetName << " takes " << damage << " massive damage!" << std::endl;
            targetHealth -= damage;
            return true;
        } else {
            std::cout << "The blast flies wide, missing " << targetName << " completely!" << std::endl;
            return false;
        }
    }
};

// Concrete class for Megatron's Fusion Cannon
class FusionCannon : public Weapon {
public:
    FusionCannon() : Weapon("Fusion Cannon", 9, 90) {}

    bool attack(const std::string& attackerName, const std::string& targetName, int& targetHealth) override {
        std::cout << attackerName << " fires the " << name << " at " << targetName << "..." << std::endl;
        sleep(1);

        int randomValue = (rand() % 100) + 1;
        if (randomValue <= accuracy) {
            std::cout << "A solid hit! " << targetName << " is struck for " << damage << " damage." << std::endl;
            targetHealth -= damage;
            return true;
        } else {
            std::cout << "The energy blast fizzles and misses its mark!" << std::endl;
            return false;
        }
    }
};

// Concrete class for Megatron's Fusion Sword
class FusionSword : public Weapon {
public:
    FusionSword() : Weapon("Fusion Sword", 18, 70) {}

    bool attack(const std::string& attackerName, const std::string& targetName, int& targetHealth) override {
        std::cout << attackerName << " lunges forward with the " << name << "!" << std::endl;
        sleep(1);

        int randomValue = (rand() % 100) + 1;
        if (randomValue <= accuracy) {
            std::cout << "A brutal slash connects! " << targetName << " takes " << damage << " damage." << std::endl;
            targetHealth -= damage;
            return true;
        } else {
            std::cout << targetName << " dodges the deadly blade!" << std::endl;
            return false;
        }
    }
};

class TankMode : public Weapon {
public:
    TankMode() : Weapon("Tank Mode", 60, 15) {}

    bool attack(const std::string& attackerName, const std::string& targetName, int& targetHealth) override {
        std::cout << "CLANK! CLANK! " << attackerName << " transforms into " << name << "! The ground shakes..." << std::endl;
        sleep(2);

        int randomValue = (rand() % 100) + 1;
        if (randomValue <= accuracy) {
            std::cout << "UNLEASHED! A catastrophic direct hit! " << targetName << " is obliterated for " << damage << " damage!" << std::endl;
            targetHealth -= damage;
            return true;
        } else {
            std::cout << "The shell whistles past " << targetName << "'s head and explodes harmlessly in the distance!" << std::endl;
            return false;
        }
    }
};

//another class
class Transformer {
private:
    std::string name;
    int health;
    Weapon* weapons[3]; // Array of pointers to Weapon objects

public:
    Transformer(const std::string& n, int h, Weapon* w1, Weapon* w2, Weapon* w3) : name(n), health(h) {
        weapons[0] = w1;
        weapons[1] = w2;
        weapons[2] = w3;
    }
    ~Transformer() {
        //dlt the weapon here
        for (int i = 0; i < 3; ++i) {
            delete weapons[i];
        }
    }

    std::string getName() const { return name; }
    int getHealth() const { return health; }

    bool isAlive() const { return health > 0; }

    void takeDamage(int amount) { health -= amount; }

    // attack here
    void performAttack(Transformer& opponent) {
        // rand() generates random weapon
        int weaponChoice = rand() % 3;
        Weapon* chosenWeapon = weapons[weaponChoice];

        std::cout << "\n--- " << name << "'s Turn ---" << std::endl;
        std::cout << "Selected weapon: " << chosenWeapon->getName() << std::endl;

        // Execute the attack using the weapon
        chosenWeapon->attack(name, opponent.getName(), opponent.health);

        // Print the result
        std::cout << opponent.getName() << "'s health is now: " << (opponent.getHealth() > 0 ? opponent.getHealth() : 0) << std::endl;
    }
};

int main() {
    // Seed the random number generator
    srand(time(0));

    std::cout << "THE BATTLE FOR CYBERTRON LESGOO" << std::endl;
    std::cout << "Optimus Prime vs. Megatron" << std::endl;
    std::cout << "Let the battle begin...(i hope my goat prime wins)\n" << std::endl;
    sleep(2);

    // Create the warriors with their arsenals
    Transformer optimus("Optimus Prime", 100, new IonRifle(), new EnergonSwords(), new ShoulderCanon());
    Transformer megatron("Megatron", 100, new FusionCannon(), new FusionSword(), new TankMode());

    Transformer* combatants[] = { &optimus, &megatron };
    int currentAttacker = 0; // 0 for Optimus, 1 for Megatron

    // Main battle loop
    while (optimus.isAlive() && megatron.isAlive()) {
        Transformer& attacker = *combatants[currentAttacker];
        Transformer& defender = *combatants[1 - currentAttacker]; // Switches between 0 and 1

        attacker.performAttack(defender);
        sleep(2); // Pause between turns

        // Switch turns for the next round
        currentAttacker = 1 - currentAttacker;
    }

    // Determine and announce the winner
    std::cout << "\n=== BATTLE END ===" << std::endl;
    if (!optimus.isAlive() && !megatron.isAlive()) {
        std::cout << "The battle ended in a draw both dead :/  Cybertron's fate remains uncertain." << std::endl;
    } else if (!optimus.isAlive()) {
        std::cout << "Megatron stands victorious!(what a puc) The Decepticons reign supreme!(not for long)" << std::endl;
    } else {
        std::cout << "Optimus Prime is victorious!(ofc he did he the goat) Freedom is the right of all sentient beings!" << std::endl;
    }

    std::cout << "Final Health -> Optimus: " << (optimus.getHealth() > 0 ? optimus.getHealth() : 0) << ", Megatron: " << (megatron.getHealth() > 0 ? megatron.getHealth() : 0) << std::endl;

    return 0;
}