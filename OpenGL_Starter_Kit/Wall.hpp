#pragma once
#include "SceneNode.h"

class Wall : public SceneNode {
public:
    Wall();
    ~Wall();
    virtual void Draw(int wall);
};