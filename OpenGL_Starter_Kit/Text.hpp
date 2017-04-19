#pragma once
#include "SceneNode.h"

class Text : public SceneNode {
public:
    Text(char* text);
    ~Text();
    void Draw();
    static void DrawInt(int x);
    static void DrawText(char* x);
};