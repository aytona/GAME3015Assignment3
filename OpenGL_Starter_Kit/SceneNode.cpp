#include "SceneNode.h"

SceneNode::SceneNode() {

}

SceneNode::~SceneNode() {

}

void SceneNode::Draw() {
    glPushMatrix();
    SetMaterial(this->material);
    glTranslatef(x, y, 0);
    glCallList(list_ptr);
    glPopMatrix();
}

void SceneNode::SetMaterial(int i) {
    GLfloat emission[4] = { 0.0, 0.0, 0.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient[i]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Diffuse[i]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Specular[i]);
    glMaterialfv(GL_FRONT, GL_SHININESS, Shininess[i]);
}

void SceneNode::NewMaterial(int i, float j, float k, float x) {
    GLfloat emission[4] = { j, k, x, 1.0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient[i]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Diffuse[i]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Specular[i]);
    glMaterialfv(GL_FRONT, GL_SHININESS, Shininess[i]);
}

void SceneNode::SetPoint(int i, int j) {
    this->x = i;
    this->y = j;
}

const GLfloat SceneNode::Ambient[][24] = {
    {0.0215, 0.1745, 0.0215, 1.0},
    {0.9921, 1.0, 0.0, 1.0},
    {0.9176, 0.5098, 0.898, 1.0},
    {0.0, 0.0, 1.0, 0.0},
    {0.8157, 0.2431, 0.098, 1.0},
    {0.2745, 0.749, 0.933, 1.0},
    {0.8588, 0.521568, 0.098, 1.0},
    {0.2125, 0.1275, 0.054, 1.0},
    {0.25, 0.25, 0.25, 1.0},
    {0.19125, 0.0735, 0.0225, 1.0},
    {0.24725, 0.1995, 0.0745, 1.0},
    {0.19225, 0.19225, 0.19225, 1.0},
    {0.02, 0.02, 0.02,1.0},
    {0.0, 0.05, 0.05,1.0},
    {0.0, 0.05, 0.0,1.0},
    {0.05, 0.0, 0.0,1.0},
    {0.05, 0.05, 0.05,1.0},
    {0.05, 0.05, 0.0,1.0}
};

const GLfloat SceneNode::Diffuse[][4] = {
    {0.07568, 0.61424, 0.07568,1.0},
    {0.54, 0.89, 0.63,1.0},
    {0.18275, 0.17, 0.22525,1.0},
    {1, 0.829, 0.829,1.0},
    {0.61424, 0.04136, 0.04136, 1.0},
    {0.396, 0.74151, 0.69102,1.0},
    {0.780392, 0.568627, 0.113725, 1.0},
    {0.714, 0.4284, 0.18144, 1.0},
    {0.4, 0.4, 0.4, 1.0},
    {0.7038, 0.27048, 0.0828, 1.0},
    {0.75164, 0.60648, 0.22648, 1.0},
    {0.50754, 0.50754, 0.50754, 1.0},
    {0.01, 0.01, 0.01, 1.0},
    {0.4, 0.5, 0.5, 1.0},
    {0.4, 0.5, 0.4, 1.0},
    {0.5, 0.4, 0.4, 1.0},
    {0.5, 0.5, 0.5, 1.0},
    {0.5, 0.5, 0.4, 1.0}
};

const GLfloat SceneNode::Specular[][4] = {
    {0.633,0.727811,0.633,1.0},
    {0.316228, 0.316228, 0.316228, 0.1},
    {0.332741, 0.328634, 0.346435,1.0},
    {0.296648, 0.296648, 0.296648,1.0},
    {0.727811, 0.626959, 0.626959,1.0},
    {0.297254, 0.30829, 0.306678,1.0},
    {0.992157, 0.941176, 0.807843, 1.0},
    {0.393548, 0.271906, 0.166721, 1.0},
    {0.774597, 0.774597, 0.774597, 1.0},
    {0.256777, 0.137622, 0.086014, 1.0},
    {0.628281, 0.555802, 0.366065, 1.0},
    {0.508273, 0.508273, 0.508273, 1.0},
    {0.4, 0.4, 0.4,1.0},
    {0.04, 0.7, 0.7,1.0},
    {0.04, 0.7, 0.04,1.0},
    {0.7, 0.04, 0.04,1.0},
    {0.7, 0.7, 0.7,1.0},
    {0.7, 0.7, 0.04,1.0}
};

const GLfloat SceneNode::Shininess[][1] = {
    {0.6},
    {0.1},
    {0.3},
    {0.088},
    {0.6},
    {0.1},
    {0.21794872},
    {0.2},
    {0.6},
    {0.1},
    {0.4},
    {0.4},
    {0.078125},
    {0.078125},
    {0.078125},
    {0.078125},
    {0.078125},
    {0.078125},
    {0.078125}
};