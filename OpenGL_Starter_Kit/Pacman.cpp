#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "Pacman.hpp"

Pacman::Pacman() {
    Lives = 3;
    dir = 0;
    x = 0;
    y = 0;
    z = 0;
    step = 1.0;
    material = 6;
    ang = 0;
    inc_ang = -1;
    list_ptr = glGenLists(1);
    GLUquadricObj *qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_NONE);
    glNewList(list_ptr, GL_COMPILE);
    glPushMatrix();
    gluPartialDisk(qobj, 0.0, 0.5, 20, 4, 0.0, 270.0);
    glPopMatrix();
    glEndList();
}

Pacman::~Pacman() {

}

void Pacman::Draw() {
    if (ang >= 45 || ang <= 0) {
        inc_ang = inc_ang * -1;
    }

    ang += inc_ang;
    SetMaterial(material);
    glPushMatrix();
    glShadeModel(GL_SMOOTH);
    glTranslatef(x, y, 0);
    glRotatef(dir * 90, 0.0, 0.0, 1.0);
    glRotatef(45 + ang, 0.0, 0.0, 1.0);
    glCallList(list_ptr);
    glPopMatrix();
    glPushMatrix();
    glShadeModel(GL_SMOOTH);
    glTranslatef(x, y, 0);
    glRotatef(dir * 90, 0.0, 0.0, 1.0);
    glRotatef(45 - ang, 0.0, 0.0, 1.0);
    glCallList(list_ptr);
    glPopMatrix();
}

int Pacman::Update(char gameboard[][28]) {
    int newX = GetNextX();
    int newY = GetNextY();
    GLboolean move = true;

    switch (gameboard[newY][newX]) {
    case 'd':
    case 'u':
    case '0':
        break;
    case '9':
        Wrap();
        break;
    case 'a':
    case 'c':
    case 'f':
    case 's':
    default:
        move = false;
        break;
    }

    if (move) {
        IncrementX();
        IncrementY();
    }

    return gameboard[int(y)][int(x)];
}

void Pacman::Die() {
    Lives--;
    SetPoint(13, 23);
    dir = 0;
}

GLboolean Pacman::isDead() {
    return Lives <= 0;
}

void Pacman::Wrap() {
    SetPoint(abs(x - 27), y);
}

void Pacman::SetMaterial(int k) {
    GLfloat emission[4] = { 0.8, 0.8, 0.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient[k]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Diffuse[k]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Specular[k]);
    glMaterialfv(GL_FRONT, GL_SHININESS, Shininess[k]);
}

void Pacman::IncrementX() {
    if (dir == 2) {
        x += step;
    } else if (dir == 0) {
        x -= step;
    }
}

void Pacman::IncrementY() {
    if (dir == 3) {
        y += step;
    } else if (dir == 1) {
        y -= step;
    }
}

int Pacman::GetX() {
    if (dir == 0) {
        return ceil(x);
    } else {
        return floor(x);
    }
}

int Pacman::GetY() {
    if (dir == 1) {
        return ceil(y);
    } else {
        return floor(y);
    }
}

int Pacman::GetNextX() {
    if (dir == 2) {
        return ceil(x + step);
    } else if (dir == 0) {
        return floor(x - step);
    }
    return x;
}

int Pacman::GetNextY() {
    if (dir == 3) {
        return ceil(y + step);
    } else if (dir == 1) {
        return floor(y - step);
    }
    return y;
}

void Pacman::KeyListener(int key, int x, int y) {
    if (key == l) {
        dir = 0;
    } else if (key == t) {
        dir = 1;
    } else if (key == r) {
        dir = 2;
    } else if (key == b) {
        dir = 3;
    }
}

void Pacman::SetKeys(int l, int t, int r, int b) {
    this->l = l;
    this->t = t;
    this->r = r;
    this->b = b;
}