#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <iostream>
#include <SFML/Graphics.hpp>
class Game;
class TestClass
{
public:
    TestClass();
    ~TestClass();
    //Test that a player projectile can collide with an enemy
    void testCollision(Game &g);
    //Test updating the score
    void testScore(Game &g);
    //Test gameobject movement
    void testMovement(Game &g);
    //Test projectiles get deleted properly
    void testProjectile(Game &g);
    //Test that the player can take damage
    void testDamage(Game &g);

private:
    sf::Clock clock;
    bool hasMoved = false;
};

#endif // TESTCLASS_H
