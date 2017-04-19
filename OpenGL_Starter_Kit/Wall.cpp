#include "Wall.hpp"

Wall::Wall() {
    x = 0;
    y = 0;
    z = 0;
    material = 9;
    list_ptr - glGenLists(10);
    glNewList(list_ptr, GL_COMPILE);
    glPushMatrix();
    glutSolidCube(1);
    glPopMatrix();
    glEndList();
    glNewList(list_ptr + 9, GL_COMPILE);
    glPushMatrix();
    glScalef(1.0, 0.3, 1.0);
    glutSolidCube(1);
    glPopMatrix();
    glEndList();
}

Wall::~Wall() {

}

void Wall::Draw(int wall) {
    glPushMatrix();
    SetMaterial(this->material);
    switch (wall) {
    case '-':
        glCallList(list_ptr + 9);
        break;
    default:
        glCallList(list_ptr);
        break;
    }

    glPopMatrix();
}