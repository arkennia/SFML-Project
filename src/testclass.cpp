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

void TestClass::testCollision(Game& g)
{
	Enemy* e = g.createEnemy(1, 1000, 100, 1);
	e->setPosition(15, HEIGHT / 2);
	g.graphics->createTexture("enemy.png", *e);
	e->setOrigin(e->getLocalBounds().width / 2, e->getLocalBounds().height / 2);
	g.gameObjects.push_back(e);
}

void TestClass::testScore(Game& g)
{
	g.scoreNum += 10000;
}

void TestClass::testMovement(Game& g)
{

	if (g.player->getPosition().x >= 15)
	{
		g.player->updatePosition(-(g.player->getMoveSpeed() / 4), 0, g.getDeltaTime());

		if (g.player->getPosition().x < 15)
		{
			g.player->setPosition(15, g.player->getPosition().y);
		}
	}
}

void TestClass::testProjectile(Game& g)
{
	if (g.player->getPosition().x >= 31)
	{
		//shoot
		Projectile* p = g.player->shoot();
		if (p != NULL)
		{
			g.projectiles.push_back(p);
			g.audio->playShoot(*g.player);
		}
	}
}

void TestClass::testDamage(Game &g)
{

}
