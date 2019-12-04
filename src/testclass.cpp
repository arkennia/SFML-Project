#include "testclass.h"
#include "enemy.h"
#include "game.h"
#include "audio.h"

TestClass::TestClass()
{

}

TestClass::~TestClass()
{

}

void TestClass::testCollision(Game &g)
{
    Enemy *e = g.createEnemy(1, 1000, 100, 1);
    e->setPosition(WIDTH/2, HEIGHT/2);
    g.graphics->createTexture("enemy.png",  *e);
    e->setOrigin(e->getLocalBounds().width/2 ,e->getLocalBounds().height/2);
    g.gameObjects.push_back(e);
}

void TestClass::testScore(Game &g)
{
    g.scoreNum += 10000;
}

void TestClass::testMovement(Game &g)
{
    if(clock.getElapsedTime().asSeconds() == 2.f && hasMoved == false)
    {
        g.player->setPosition(20, g.player->getPosition().y);
        hasMoved = true;
    }
}


void TestClass::testProjectile(Game &g)
{

}

void TestClass::testDamage(Game &g)
{

}
