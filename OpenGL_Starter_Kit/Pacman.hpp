#pragma once
#include "SceneNode.h"

class Pacman : public SceneNode {
public:
    Pacman();
    ~Pacman();
    void KeyListener(int key, int x, int y);
    virtual void Draw();
    int Update(char gameboard[][28]);
    int GetX();
    int GetY();
    void Die();
    GLboolean isDead();
    void SetKeys(int l, int t, int r, int b);

public:
    int Lives;

private:
    void Wrap();
    int GetNextX();
    int GetNextY();
    void IncrementX();
    void IncrementY();
    void SetMaterial(int k);

private:
    int l, t, r, b, ang, inc_ang, dir;
    float step;
};