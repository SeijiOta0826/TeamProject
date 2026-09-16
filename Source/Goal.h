#pragma once

#include "GameObject.h"

class Player;

class Goal : public GameObject
{
public:
    Goal(std::string filename,VECTOR initPos,const bool _shape[3][3]);
    ~Goal();

    void Update(float _deltaTime) override;
    void Draw() override;

    bool IsPlayerTouching() const;

    bool IsShapeMatched(Player* _player) const;
    bool IsWithinDistance(Player* _player);

private:
    bool mShape[3][3] =
    {
        { false, false, false },
        { false, true,  false },
        { false, false, false }
    };
};