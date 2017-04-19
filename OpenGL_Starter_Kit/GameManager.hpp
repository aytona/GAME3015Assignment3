#pragma once
#include "Circle.h"
#include "Pacman.hpp"
#include "Wall.hpp"
#include "Text.hpp"
#include "Powerup.hpp"
#include "Seeker.hpp"

class GameManager {
public:
    GameManager();
    ~GameManager();
    void Draw();
    void Update();
    void KeyListener(int key, int x, int y);
    void Pause();
    void SetDimensions(int x, int y);
    void SetPoint(int x, int y);
    void SetKeys(int l, int t, int r, int b);
    GLboolean isPlaying();
    GLboolean hasEnded();

public:
    int Speed;
    int Score;
    int Width;
    int Height;
    int Level;

private:
    void DrawScore();
    void DrawLives();
    void DrawLevel();
    void InitHeaders();
    void InitGameboard();
    void LevelUp();
    void NewLevel();
    void SuperPacman();

private:
    GLboolean Paused;
    int Circles;
    Seeker* ghostOne;
    Seeker* ghostTwo;
    Seeker* ghostThree;
    Seeker* ghostFour;
    Pacman* pacman;
    Powerup* powerup;
    Circle* circle;
    Wall* wall;
    int x, y;
    const static char m_Gameboard[31][28];
    char gameboard[31][28];
    Text* scoreHeader;
    Text* livesHeader;
    Text* levelHeader;
};