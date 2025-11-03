#include "coin.h"
#include <iostream>

Coin::Coin(float x, float y)
{
    this->Load("data/gfx/coin.png");
    this->setPosition(x, y);
}

void Coin::Update()
{
}
