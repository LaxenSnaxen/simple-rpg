#ifndef COIN_H
#define COIN_H

#include "entity.h"

class Coin : public Entity
{
public:
    Coin(float x, float y);
    void Update() override;
};

#endif // COIN_H
