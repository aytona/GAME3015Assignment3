#include <stdio.h>
#include <iostream>
#include "Ghost.hpp"

const int Ghost::mat = 5;

Ghost::Ghost() {
    x = 0;
    y = 0;
    z = 0;
    Step = 1;
    dir = rand() % 4;
    moveProb = 5;
    changeProb = 10;
    Killable = 0;
    material = mat;
    Moving = true;
    GoingOut = true;
    list_ptr = glGenLists(1);
    glNewList(list_ptr, GL_COMPILE);
    glPushMatrix();
    glutSolidTorus(0.15, 0.3, 25, 25);
    glPopMatrix();
    glEndList();
}

Ghost::~Ghost() {

}

GLboolean Ghost::Update(int x, int y, char gameboard[][28]) {
    if (Killable > 0) {
        Killable--;
        if (Killable == 0) {
            material = m_material;
        }
    }
    if (GoingOut && Moving && this->y > 11) {
        if (this->x < 13) {
            this->x += Step;
        } else if (this->x > 14) {
            this->x -= Step;
        } else {
            this->y -= Step;
        }
    } else if (GoingOut && Moving) {
        GoingOut = false;
    } else if (Moving) {
        if (this->x == x && this->y == y) {
            if (Killable > 0) {
                Die();
                return false;
            } else {
                return true;
            }
        }
        Walk(x, y, gameboard);
        if (this->x == x && this->y == y) {
            if (Killable > 0) {
                Die();
                return false;
            } else {
                return true;
            }
        }
    }
    return false;
}

void Ghost::Walk(int x, int y, char gameboard[][28]) {
    if ((rand() % 10) < moveProb) {
        if ((rand() % 10 < changeProb)) {
            dir = rand() % 4;
        }
        while (!MoveTo(dir, gameboard)) {
            dir = rand() % 4;
        }
    }
}

GLboolean Ghost::MoveTo(int dir, char gameboard[][28]) {
    int x = 0;
    int y = 0;
    switch (dir) {
    case 0:
        x -= Step;
        break;
    case 1:
        y -= Step;
        break;
    case 2:
        x = Step;
        break;
    case 3:
        y = Step;
        break;
    }

    switch (gameboard[int(this->y + y)][int(this->x + x)]) {
    case '0':
    case 'd':
    case 'u':
        this->y += y;
        this->x += x;
        return true;
    case '9':
        Wrap();
    default:
        return false;
        break;
    }
}

void Ghost::Wrap() {
    SetPoint(abs(x - 27), y);
}

void Ghost::MakeKillable() {
    Killable = 40;
    material = 3;
}

void Ghost::Die() {
    Killable = 0;
    x = 13;
    y = 14;
    GoingOut = true;
    material = m_material;
}