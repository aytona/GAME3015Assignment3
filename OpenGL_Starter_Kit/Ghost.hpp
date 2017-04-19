#pragma once
#include "SceneNode.h"

class Ghost : public SceneNode {
public:
    Ghost();
    ~Ghost();
    GLboolean Update(int x, int y, char gameboard[][28]);
    virtual void MakeKillable();
    const static int mat;
    void Die();

public:
    int Killable;

protected:
    GLboolean MoveTo(int dir, char gameboard[][28]);
    virtual void Walk(int x, int y, char gameboard[][28]);
    void Wrap();

protected:
    float Step;
    GLboolean GoingOut;
    GLboolean Moving;
    int dir;
    int m_material;
    float moveProb;
    float changeProb;
};