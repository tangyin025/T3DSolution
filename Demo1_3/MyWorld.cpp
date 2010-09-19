
#include "StdAfx.h"
#include "MyWorld.h"

MyWorld::MyWorld(void)
	: my::World(256)
{
}

MyWorld::~MyWorld(void)
{
}

void MyWorld::integrate(real duration)
{
}

unsigned MyWorld::generateContacts(my::Contact * contacts, unsigned limits)
{
	return 0;
}
