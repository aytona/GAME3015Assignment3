#pragma once
#include "glut.h"

class SceneNode {
public:
    SceneNode();
    ~SceneNode();
    virtual void Draw();
    void SetMaterial(int i);
    static void NewMaterial(int i, float j, float k, float x);
    void SetPoint(int i, int j);
    const static GLfloat Ambient[][24];
    const static GLfloat Diffuse[][4];
    const static GLfloat Specular[][4];
    const static GLfloat Shininess[][1];

protected:
    int list_ptr, list_size, material;
    float x, y, z;
};