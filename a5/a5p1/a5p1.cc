#include <vector>
#include <string>
#include "a5p1.h"

using namespace std;

/* ************************************************************** */
// Class Animal
// -----------------------------------------------------------------
Animal::Animal(string name) : name(name) {}

Animal::~Animal() {} // Provided for you :)

string Animal::getName() const
{
    return name;
}
/* ************************************************************** */

/* ************************************************************** */
// Class Dog
// -----------------------------------------------------------------
Dog::Dog(string name) : Animal(name) {}

Dog::~Dog() {} // Provided for you :)

string Dog::speak() const
{
    return "    Dog " + getName() + " says \"woof\".";
}
/* ************************************************************** */

/* ************************************************************** */
// Class Sheep
// -----------------------------------------------------------------
Sheep::Sheep(string name) : Animal(name) {}

Sheep::~Sheep() {} // Provided for you :)

string Sheep::speak() const
{
    return "    Sheep " + getName() + " says \"baaa\".";
}
/* ************************************************************** */

/* ************************************************************** */
// Class Flock
// -----------------------------------------------------------------
Flock::Flock(string dogName) : dog(new Dog{dogName}) {}

Flock::~Flock()
{
    for (Sheep *s : sheepList)
    {
        delete s;
    }
    delete dog;
}

void Flock::addSheep(string name)
{
    Sheep *sheep = new Sheep{name};
    sheepList.push_back(sheep);
}

string Flock::soundOff() const
{
    string res = "The flock of " + to_string(sheepList.size()) + " sheep speaks!\n";
    res += dog->speak() + "\n";
    for (Sheep *sheep : sheepList)
    {
        res += sheep->speak() + "\n";
    }
    return res;
}
/* ************************************************************** */
