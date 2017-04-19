#include <stdio.h>
#include <iostream>
#include "GameManager.hpp"

GameManager::GameManager() {
    wall = new Wall();
    circle = new Circle();
    powerup = new Powerup();
    pacman = new Pacman();
    ghostOne = new Seeker();
    ghostTwo = new Seeker();
    ghostThree = new Seeker();
    ghostFour = new Seeker();
    Speed = 200;
    Level = 1;
    Score = 0;
    Paused = false;
    InitHeaders();
    NewLevel();
}

GameManager::~GameManager() {

}

void GameManager::InitHeaders() {
    livesHeader = new Text("Lives: ");
    levelHeader = new Text("Level: ");
    scoreHeader = new Text("Score: ");
}

void GameManager::SetPoint(int x, int y) {
    this->x = x;
    this->y = y;
}

void GameManager::Draw() {
    glViewport(x, y, Width, Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.5, 28.5, 31.5, -1.5, -512, 512);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (int i = 0; i < 31; i++) {
        for (int j = 0; j < 28; j++) {
            glPushMatrix();
            glTranslatef(j, i, 0);
            switch (gameboard[i][j]) {
            case 'd':
                circle->Draw();
                break;
            case 'u':
                powerup->Draw();
                break;
            case '0':
            case '9':
                break;
            default:
                wall->Draw(gameboard[i][j]);
                break;
            }
            glPopMatrix();
        }
    }

    pacman->Draw();
    ghostOne->Draw();
    ghostTwo->Draw();
    ghostThree->Draw();
    ghostFour->Draw();
    glViewport(Width * 0.7 + x, 0 + y, Width * 0.3, Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-150.0, 150.0, 500.0, -500.0, -512.0, -512.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-50, -500, 0);
    DrawScore();
    DrawLives();
    DrawLevel();
    glPopMatrix();
}

void GameManager::SetKeys(int l, int t, int r, int b) {
    pacman->SetKeys(l, t, r, b);
}

void GameManager::DrawLevel() {
    SceneNode::NewMaterial(1, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 150.0, 0.0);
    levelHeader->Draw();
    glPushMatrix();
    glTranslatef(50.0, 30.0, 0.0);
    Text::DrawInt(Level);
    glPopMatrix();
}

void GameManager::DrawLives() {
    SceneNode::NewMaterial(1, 1.0, 1.0, 0.0);
    glTranslatef(0.0, 150.0, 0.0);
    livesHeader->Draw();
    glPushMatrix();
    glTranslatef(50.0, 30.0, 0.0);
    Text::DrawInt(pacman->Lives);
    glPopMatrix();
}

void GameManager::DrawScore() {
    SceneNode::NewMaterial(1, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 150.0, 0.0);
    scoreHeader->Draw();
    glPushMatrix();
    glTranslatef(50.0, 30.0, 0.0);
    Text::DrawInt(Score);
    glPopMatrix();
}

void GameManager::SuperPacman() {
    ghostOne->MakeKillable();
    ghostTwo->MakeKillable();
    ghostThree->MakeKillable();
    ghostFour->MakeKillable();
}

void GameManager::Update() {
    if (Circles > 0) {
        pacman->Update(gameboard);
        int x = pacman->GetX();
        int y = pacman->GetY();
        switch (gameboard[y][x]) {
        case 'u':
            SuperPacman();
            Score++;
        case 'd':
            Score++;
            Circles--;
            gameboard[y][x] = '0';
            break;
        }
        GLboolean hit = false;
        hit = ghostOne->Update(x, y, gameboard) || hit;
        hit = ghostTwo->Update(x, y, gameboard) || hit;
        hit = ghostThree->Update(x, y, gameboard) || hit;
        hit = ghostFour->Update(x, y, gameboard) || hit;

        if (hit) {
            pacman->Die();
        }
    } else {
        LevelUp();
    }
}

void GameManager::LevelUp() {
    Level++;
    if (Level % 3 == 0) {
        pacman->Lives++;
    }
    if (Speed > 100) {
        Speed -= 20;
    }

    NewLevel();
}

void GameManager::NewLevel() {
    pacman->SetPoint(13, 23);
    ghostOne->Die();
    ghostTwo->Die();
    ghostThree->Die();
    ghostFour->Die();
    ghostOne->SetPoint(12, 14);
    ghostTwo->SetPoint(13, 14);
    ghostThree->SetPoint(14, 14);
    ghostFour->SetPoint(15, 14);
    Circles = 0;
    InitGameboard();
}

void GameManager::Pause() {
    Paused = !Paused;
}

GLboolean GameManager::isPlaying() {
    return !Paused;
}

GLboolean GameManager::hasEnded() {
    return pacman->isDead();
}

void GameManager::InitGameboard() {
    for (int i = 0; i < 31; i++) {
        for (int j = 0; j < 28; j++) {
            if (this->m_Gameboard[i][j] == 'd' || this->m_Gameboard[i][j] == 'u') {
                Circles++;
            }
            gameboard[i][j] = this->m_Gameboard[i][j];
        }
    }
}

void GameManager::KeyListener(int key, int x, int y) {
    if (key == 1112) {
        Paused = !Paused;
    }
    pacman->KeyListener(key, x, y);
}

void GameManager::SetDimensions(int x, int y) {
    Width = x;
    Height = y;
}

const char GameManager::m_Gameboard[31][28] = { 
{ '1','2','2','2','2','2','2','2','2','2','2','2','2','3','1','2','2','2','2','2','2','2','2','2','2','2','2','3' },
{ '8','d','d','d','d','d','d','d','d','d','d','d','d','4','8','d','d','d','d','d','d','d','d','d','d','d','d','4' },
{ '8','d','1','2','2','3','d','1','2','2','2','3','d','8','4','d','1','2','2','2','3','d','1','2','2','3','d','4' },
{ '8','u','d','d','d','d','d','d','d','d','d','d','d','8','4','d','d','d','d','d','d','d','d','d','d','d','u','4' },
{ '8','d','7','6','6','5','d','7','6','6','6','5','d','7','5','d','7','6','6','6','5','d','7','6','6','5','d','4' },
{ '8','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','4' },
{ '8','d','1','2','2','3','d','1','3','d','1','2','2','2','2','2','2','3','d','3','1','d','1','2','2','3','d','4' },
{ '8','d','7','6','6','5','d','8','4','d','7','6','6','3','1','6','6','5','d','4','8','d','7','6','6','5','d','4' },
{ '8','d','d','d','d','d','d','8','4','d','d','d','d','8','4','d','d','d','d','4','8','d','d','d','d','d','d','4' },
{ '7','2','2','2','2','3','d','8','7','2','2','3','0','8','4','0','1','2','2','5','8','d','7','2','2','2','2','5' },
{ '0','0','0','0','0','4','d','8','1','6','6','5','0','7','5','0','7','6','6','3','8','d','8','0','0','0','0','0' },
{ '0','0','0','0','0','4','d','8','4','d','d','d','d','d','d','d','d','d','d','4','8','d','8','0','0','0','0','0' },
{ '0','0','0','0','0','4','d','8','4','d','1','2','2','-','-','2','2','3','d','4','8','d','8','0','0','0','0','0' },
{ '6','6','6','6','6','5','d','7','5','d','8','0','0','0','0','0','0','4','d','5','7','d','7','6','6','6','6','6' },
{ '9','d','d','d','d','d','u','d','d','d','8','0','0','0','0','0','0','4','d','d','d','u','d','d','d','d','d','9' },
{ '2','2','2','2','2','3','d','1','3','d','8','0','0','0','0','0','0','4','d','1','3','d','1','2','2','2','2','2' },
{ '0','0','0','0','0','4','d','8','4','d','7','6','6','6','6','6','6','5','d','8','4','d','8','0','0','0','0','0' },
{ '0','0','0','0','0','4','d','8','4','d','d','d','d','u','u','d','d','d','d','8','4','d','8','0','0','0','0','0' },
{ '0','0','0','0','0','4','d','8','4','d','1','2','2','2','2','2','2','3','d','8','4','d','8','0','0','0','0','0' },
{ '1','6','6','6','6','5','d','7','5','d','7','6','6','3','1','6','6','5','d','7','5','d','7','6','6','6','6','3' },
{ '8','d','d','d','d','d','d','d','d','d','d','d','d','8','4','d','d','d','d','d','d','d','d','d','d','d','d','4' },
{ '8','d','1','2','2','3','d','1','2','2','2','3','d','8','4','d','1','2','2','2','3','d','1','2','2','3','d','4' },
{ '8','d','7','6','3','4','d','7','6','6','6','5','d','7','5','d','7','6','6','6','5','d','8','1','6','5','d','4' },
{ '8','u','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','u','4' },
{ '7','2','3','d','8','4','d','1','3','d','1','2','2','d','d','2','2','3','d','1','3','d','8','4','d','1','6','5' },
{ '1','6','5','d','7','5','d','8','4','d','7','6','6','3','1','6','6','5','d','8','4','d','7','5','d','7','2','3' },
{ '8','d','d','d','d','d','d','8','4','d','d','d','d','d','d','d','d','d','d','8','4','d','d','d','d','d','d','4' },
{ '8','d','1','2','2','2','d','5','7','2','2','3','d','8','4','d','1','2','2','2','2','5','7','2','d','3','d','4' },
{ '8','d','7','6','6','6','d','6','6','6','6','5','d','7','5','d','7','6','6','6','6','6','6','6','d','5','d','4' },
{ '8','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','4' },
{ '7','6','6','6','6','6','6','6','6','6','6','6','6','6','6','6','6','6','6','6','6','6','6','6','6','6','6','5' } };