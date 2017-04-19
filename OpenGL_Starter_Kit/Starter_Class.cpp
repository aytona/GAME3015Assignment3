#include "glut.h"
#include "Circle.h"
#include "GameManager.hpp"
#include "Text.hpp"
#include <math.h>
#include <mmsystem.h>

GameManager* gameManager;
int Width = 800;
int Height = 800;
int rotX[2] = { 300, 1 };
int rotY[2] = { 0, 0 };
int rotZ[2] = { 0, 0 };
int timer = 0;

float m_AmbientDiffuse[] = { 0.0, 0.0, 0.0, 1.0 };
float m_Specular[] = { 0.0, 0.0, 0.0, 1.0 };
float m_Emission[] = { 0.0, 0.0, 0.0, 1.0 };
float m_Shininess = 0.4;
float f_Emission[] = { 0.0, 0.0, 0.0, 1.0 };
float l_Ambient[] = { 0.0, 0.2, 0.0, 1.0 };
float l_DiffuseSpecular[] = { 0.6, 0.2, 0.067, 0.0 };
float l_pos[] = { 0.0, 0.0, 2.0, 1.0 };
float spotDir[] = { 0.0, 0.0, -1.0 };
float spotCutoff = 50.0;
float spotExponent = 5.0;

void Reshape(int x, int y);
void Menu(int option);
void Init();
void InitObjects();
void Display();
void Special(int key, int x, int y);
void Key(unsigned char key, int x, int y);
static void Idle();
void Timer(int t);

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Pacman");
    InitObjects();
    Init();
    glutReshapeFunc(Reshape);
    glutDisplayFunc(Display);
    glutKeyboardFunc(Key);
    glutSpecialFunc(Special);
    glutIdleFunc(Idle);
    glutTimerFunc(350, Timer, 350);

    glutMainLoop();

    return EXIT_SUCCESS;
}

void Init() {
    glEnable(GL_DEPTH_TEST);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    glEnable(GL_LIGHTING);
    GLfloat globalAmbient[] = { 1.0, 1.0, 1.0, 0.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, m_AmbientDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m_Specular);
    glMaterialf(GL_FRONT, GL_SHININESS, m_Shininess);
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void InitObjects() {
    gameManager = new GameManager();
    gameManager->SetKeys(1000 + 97, 1000 + 119, 1000 + 100, 1000 + 115);
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if ((gameManager->isPlaying()) && (!gameManager->hasEnded())) {
        glPushMatrix();
        gameManager->SetPoint(0, 0);
        gameManager->Draw();
        glPopMatrix();
    } else if (!gameManager->isPlaying()) {
        Reshape(Width, Height);
        Text::DrawText("Game is paused, p to unpause or r to restart");
    } else if (gameManager->hasEnded()) {
        Reshape(Width, Height);
        glPushMatrix();
        Text::DrawText("Game Over!");
        glTranslatef(0.0, 1.0, 0.0);
        Text::DrawText("Your Score: ");
        glTranslatef(0.0, 1.0, 0.0);
        Text::DrawInt(gameManager->Score);
        glPopMatrix();
    }
    glutSwapBuffers();
}

void Timer(int t) {
    if (gameManager->isPlaying() && !gameManager->hasEnded()) {
        gameManager->Update();
        t = gameManager->Speed;
    }

    glutPostRedisplay();
    glutTimerFunc(t, Timer, t);
}

void Key(unsigned char key, int x, int y) {
    Special(key + 1000, x, y);
}

void Special(int key, int x, int y) {
    if (key == 1114) {
        InitObjects();
        Reshape(Width, Height);
    }

    gameManager->KeyListener(key, x, y);
    glutPostRedisplay();
}

void Menu(int option) {
    switch (option) {
    case 1:
        if (!gameManager->hasEnded()) {
            gameManager->Pause();
        }
        break;
    case 2:
        gameManager = new GameManager();
        break;
    case 0:
        exit(0);
        break;
    }
}

void Reshape(int x, int y) {
    Width = x;
    Height = y;
    glViewport(0, 0, Width, Height);
    gameManager->SetDimensions(Width, Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.5, 28.5, 31.5, -1.5, -512, 512);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void Idle() {
    glutPostRedisplay();
}