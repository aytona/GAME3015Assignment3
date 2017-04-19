#include <iostream>
#include <stdio.h>
#include <string>
#include "Text.hpp"

Text::Text(char* text) {
    list_ptr = glGenLists(1);
    glNewList(list_ptr, GL_COMPILE);
    Text::DrawText(text);
    glEndList();
}

Text::~Text() {

}

void Text::Draw() {
    glPushMatrix();
    glCallList(list_ptr);
    glPopMatrix();
}

void Text::DrawText(char* x) {
    glRasterPos3d(0.0, 0.0, 0.0);
    int index = 0;
    while (x[index] != '\0') {
        if (x[index] == '\n') {
            glRasterPos3d(0.0, 24.0, 0.0);
            index++;
        } else {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, x[index]);
            index++;
        }
    }
}

void Text::DrawInt(int x) {
    std::string s = std::to_string(x);
    char* a = new char[s.size() + 1];
    a[s.size()] = 0;
    memcpy(a, s.c_str(), s.size());
    Text::DrawText(a);
}