
#include "iGraphics.h"
#include "iSound.h"
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define WIN_W 1550
#define WIN_H 1000
#define MAX_BLOCKS 1000
#define BIRD_WIDTH 60
#define BIRD_HEIGHT 60
#define BLOCK_WIDTH 30
#define BLOCK_HEIGHT 30
#define MAX_NAME_LEN 100
#define NUM_BIRDS 5

#define STATE_COVER -1
#define STATE_MENU 0
#define STATE_LEVEL_SELECT 1
#define STATE_HELP 2
#define STATE_LEADERBOARD 3
#define STATE_GAMEOVER 4
#define STATE_CREDITS 7
#define STATE_BIRDSELECT 8
#define STATE_NAMEINPUT 9
#define STATE_LEVEL1 10
#define STATE_LEVEL2 11
#define STATE_LEVELCOMPLETE 12
#define STATE_VICTORY 13

// Game state
int gameState = STATE_COVER;
int coverTimer = 0;
int gameLevel = 1;
int selectedLevel = 1;

// Bird and physics
double velocity = 90;
double angle = 30;
double g = 9.8;
double t = 0;
bool launched = false;
bool ready = true;
int score = 0;
bool levelWon = false;
bool allGone = false;
int lives = 5;
bool gameOver = false;

// Bird struct and array
typedef struct
{
    double x, y;
    bool active;
    int type; // 0-4
} Bird;

Bird birds[NUM_BIRDS];
int currentBird = 0;

// Bird images
const char *birdImages[NUM_BIRDS] = {
    "assets/images/redBird.bmp",
    "assets/images/yellowBird.bmp",
    "assets/images/blueBird.png",
    "assets/images/blackBird.bmp",
    "assets/images/blueBird.bmp"};

// Bird selection
int selectedBirdTypes[NUM_BIRDS] = {0, 1, 2, 3, 4};
int birdSelectionIndex = 0;

// score and leaderboard
char playerName[MAX_NAME_LEN] = "";
int nameCharIndex = 0;

// Mouse drag for slingshot
bool dragging = false;
int dragX = 0, dragY = 0;

// Sound
int bgmChannel = -1;

// Block struct
typedef struct
{
    float x, y;
    float width, height;
    int isVisible;
    int hitPoints;
    int isFalling;
    int isMoving;
    float vx, vy;
    int isDeadly;
} Block;

Block blocks[MAX_BLOCKS];
int blockCount = 0;

static double toRad(double deg) { return deg * M_PI / 180.0; }

void initBirds()
{
    for (int i = 0; i < NUM_BIRDS; i++)
    {
        birds[i].x = 50 + i * 50;
        birds[i].y = 200;
        birds[i].active = true;
        birds[i].type = selectedBirdTypes[i];
    }
    birds[0].x = 120;
    birds[0].y = 450;
    currentBird = 0;
}

void resetCurrentBird()
{
    if (currentBird < NUM_BIRDS)
    {
        birds[currentBird].x = 120;
        birds[currentBird].y = 450;
    }
    t = 0;
    launched = false;
    ready = true;
}

void addBlock(float x, float y, float w, float h, int isVisible, int health, int isFalling, int isMoving, float dx, float dy, int isDeadly)
{
    if (blockCount >= MAX_BLOCKS)
        return;
    blocks[blockCount++] = (Block){x, y, w, h, isVisible, health, isFalling, isMoving, dx, dy, isDeadly};
}

void addPyramid(float centerX, float baseY, int layers, float w, float h, int health)
{
    for (int i = 0; i < layers; i++)
    {
        int count = layers - i;
        float startX = centerX - (count * w) / 2;
        for (int j = 0; j < count; j++)
        {
            addBlock(startX + j * w, baseY + i * h, w, h, 1, health, 0, 0, 0, 0, 0);
        }
    }
}

void addBlockGrid(float startX, float startY, int rows, int cols, float w, float h, int health)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            addBlock(startX + j * w, startY + i * h, w, h, 1, health, 0, 0, 0, 0, 0);
        }
    }
}

void addPerimeterGrid(float startX, float startY, int rows, int cols, float w, float h, int thickness, int health)
{
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            bool isEdge = (r < thickness || r >= rows - thickness || c < thickness || c >= cols - thickness);
            if (isEdge)
            {
                float x = startX + c * w;
                float y = startY + r * h;
                addBlock(x, y, w, h, 1, health, 0, 0, 0, 0, 0);
            }
        }
    }
}

void fallingBlock(float x, float y, float w, float h, int health, float dy, int isDeadly)
{
    addBlock(x, y, w, h, 1, health, 1, 0, 0, dy, isDeadly);
}

void movingBlocks(float x, float y, float w, float h, int health, float dx)
{
    addBlock(x, y, w, h, 1, health, 0, 1, dx, 0, 0);
}

void initBlocks1()
{
    blockCount = 0;
    addPerimeterGrid(600, 350, 5, 7, BLOCK_WIDTH, BLOCK_HEIGHT, 2, 1);
    float pyramidcenterX = 600 + 7 * BLOCK_WIDTH / 2;
    float pyramidbaseY = 350 + 2 * BLOCK_HEIGHT;
    addPyramid(pyramidcenterX, pyramidbaseY, 4, BLOCK_WIDTH, BLOCK_HEIGHT, 1);
}

void initBlocks2()
{
    blockCount = 0;
    addBlockGrid(700, 350, 5, 3, BLOCK_WIDTH, BLOCK_HEIGHT, 1);
    addPyramid(800, 300, 3, BLOCK_WIDTH, BLOCK_HEIGHT, 1);
    movingBlocks(600, 500, BLOCK_WIDTH, BLOCK_HEIGHT, 1, 4);
    fallingBlock(600, 800, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
    fallingBlock(800, 600, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
    fallingBlock(1000, 800, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
    movingBlocks(1200, 600, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4);
    movingBlocks(400, 500, BLOCK_WIDTH, BLOCK_HEIGHT, 1, 4);
}

void drawSlingshotPuller()
{
    int slingBaseX = 120, slingBaseY = 450;
    int slingTopX = 120, slingTopY = 520;
    int birdCenterX = (int)birds[currentBird].x + BIRD_WIDTH / 2;
    int birdCenterY = (int)birds[currentBird].y + BIRD_HEIGHT / 2;

    iSetColor(139, 69, 19);
    iFilledRectangle(110, 420, 20, 100);
    iSetColor(100, 50, 10);
    iFilledRectangle(120, 450, 40, 10);

    if (ready && !launched && birds[currentBird].active && dragging)
    {
        iSetColor(80, 40, 10);
        iLine(slingBaseX, slingBaseY, dragX, dragY);
        iLine(slingTopX, slingTopY, dragX, dragY);
    }
    else if (ready && !launched && birds[currentBird].active)
    {
        iSetColor(80, 40, 10);
        iLine(slingBaseX, slingBaseY, birdCenterX, birdCenterY);
        iLine(slingTopX, slingTopY, birdCenterX, birdCenterY);
    }
}

void showLeaderBoard()
{
    typedef struct{
        char name[MAX_NAME_LEN];
        int score;
    } Entry;
    Entry entries[100];
    int count = 0;
    
    FILE *file = fopen("assets/leaderboard.txt", "r");
    if(!file) {
        // If file doesn't exist in assets/, try bin/assets/
        file = fopen("bin/assets/leaderboard.txt", "r");
        if(!file) {
            iSetColor(255, 0, 0);
            iText(350, 400, "No scores yet!", GLUT_BITMAP_HELVETICA_18);
            return;
        }
    }

    while(fscanf(file, "%s %d", entries[count].name, &entries[count].score) == 2)
    {
        count++;
        if(count >= 100) break;
    }
    fclose(file);
    //Sort descending
     for(int i=0; i<count - 1; i++){
        for(int j=i+1; j<count; j++){
            if(entries[i].score < entries[j].score)
            {
                Entry temp = entries[i];
                entries[i] = entries[j];
                entries[j] = temp;
            }
        }
     }
     // Display top 5
     for(int i=0; i<count && i<5; i++){
        char line[200];
        if(i == 0) iSetColor(255, 215, 0);  // Gold
        else if(i == 1) iSetColor(192, 192, 192);  // Silver
        else if(i == 2) iSetColor(205, 127, 50);  // Bronze
        else iSetColor(255, 255, 255);  // White for others
        sprintf(line, "%d. %s - %d", i+1, entries[i].name, entries[i].score);
        iText(350, 650-i*30, line, GLUT_BITMAP_HELVETICA_18);
     }
}

void saveScore()
{
    static bool scoreSaved = false;
    if (scoreSaved) return;  // Prevent multiple saves of the same score
    
    FILE *file = fopen("assets/leaderboard.txt", "a");
    if(file){
        fprintf(file, "%s %d\n", playerName, score);
        fclose(file);
        scoreSaved = true;
    }
    
    // Reset the flag when starting a new game or selecting level
    if (gameState == STATE_LEVEL_SELECT || gameState == STATE_NAMEINPUT) {
        scoreSaved = false;
    }
}

void iDraw()
{
    iClear();

    if (gameState == STATE_COVER)
    {
        iShowImage(0, 0, "assets/images/coverS.bmp");
        int r = 200 + rand() % 55;
        int g = 50 + rand() % 200;
        int b = 50 + rand() % 200;
        iSetColor(r, g, b);
        iText(WIN_W / 2 - 30, 60, "Loading...", GLUT_BITMAP_TIMES_ROMAN_24);

        // Try to play sound again if it's not playing
        if (bgmChannel == -1) {
            bgmChannel = iPlaySound("assets/sounds/gameBGM.wav", true, 100);
            if (bgmChannel == -1) {
                bgmChannel = iPlaySound("bin/assets/sounds/gameBGM.wav", true, 100);
            }
        }
    }

    else if (gameState == STATE_MENU)
    {
        iShowImage(0, 0, "assets/images/MenuCover.jpg");
        iShowImage(510, 630, "assets/images/AngryBwritting.bmp");

        int btnW = 200, btnH = 50, x = 660;
        int y1 = 500, y2 = 400, y3 = 300, y4 = 200, y5 = 100;
        // Start Game
        iSetColor(0, 100, 0);
        iFilledRectangle(x + 5, y1 - 5, btnW, btnH);
        iSetColor(0, 200, 0);
        iFilledRectangle(x, y1, btnW, btnH);
        iSetColor(255, 255, 255);
        iText(x + 50, y1 + 15, "START GAME", GLUT_BITMAP_HELVETICA_18);
        // Leaderboard
        iSetColor(0, 0, 100);
        iFilledRectangle(x + 5, y2 - 5, btnW, btnH);
        iSetColor(0, 0, 200);
        iFilledRectangle(x, y2, btnW, btnH);
        iSetColor(255, 255, 255);
        iText(x + 50, y2 + 15, "LEADERBOARD", GLUT_BITMAP_HELVETICA_18);
        // Help
        iSetColor(100, 0, 100);
        iFilledRectangle(x + 5, y3 - 5, btnW, btnH);
        iSetColor(200, 0, 200);
        iFilledRectangle(x, y3, btnW, btnH);
        iSetColor(255, 255, 255);
        iText(x + 50, y3 + 15, "HELP", GLUT_BITMAP_HELVETICA_18);
        // Credits
        iSetColor(100, 100, 0);
        iFilledRectangle(x + 5, y4 - 5, btnW, btnH);
        iSetColor(200, 200, 0);
        iFilledRectangle(x, y4, btnW, btnH);
        iSetColor(255, 255, 255);
        iText(x + 50, y4 + 15, "CREDIT", GLUT_BITMAP_HELVETICA_18);
        // Exit
        iSetColor(100, 0, 0);
        iFilledRectangle(x + 5, y5 - 5, btnW, btnH);
        iSetColor(200, 0, 0);
        iFilledRectangle(x, y5, btnW, btnH);
        iSetColor(255, 255, 255);
        iText(x + 75, y5 + 15, "EXIT", GLUT_BITMAP_HELVETICA_18);

        // Sound button (top-right)
        
    }
    else if(gameState == STATE_LEVEL_SELECT)
    {
        //Level selection
        iShowImage(0, 0, "assets/images/1MAnuBackGround.bmp");
        int btnX = 200, btnY = 50, x=660;
        int y1 = 400, y2 = 300;
        iSetColor(0, 0, 0);
        iText(600, 700, "SELECT LEVEL", GLUT_BITMAP_TIMES_ROMAN_24);
        //Level 1
        iSetColor(100, 0, 0);
        iFilledRectangle(x + 5, y1 - 5, btnX, btnY);
        iSetColor(200, 0, 0);
        iFilledRectangle(x, y1, btnX, btnY);
        iSetColor(255, 255, 255);
        iText(x + 75, y1 + 15, "LEVEL 1", GLUT_BITMAP_HELVETICA_18);
        //Level 2
        iSetColor(100, 100, 0);
        iFilledRectangle(x + 5, y2 - 5, btnX, btnY);
        iSetColor(200, 200, 0);
        iFilledRectangle(x, y2, btnX, btnY);
        iSetColor(255, 255, 255);
        iText(x + 75, y2 + 15, "LEVEL 2", GLUT_BITMAP_HELVETICA_18);

    }
    else if (gameState == STATE_NAMEINPUT)
    {
        iSetColor(0, 0, 0);
        iFilledRectangle(0, 0, WIN_W, WIN_H);
        iSetColor(255, 255, 255);
        iText(WIN_W / 2 - 100, WIN_H / 2, "Enter your name: ", GLUT_BITMAP_HELVETICA_18);
        iText(WIN_W / 2 - 100, WIN_H / 2 - 30, playerName, GLUT_BITMAP_HELVETICA_18);
    }
    else if (gameState == STATE_BIRDSELECT)
    {
        iSetColor(0, 0, 0);
        iFilledRectangle(0, 0, WIN_W, WIN_H);
        iSetColor(255, 255, 255);
        char msg[128];
        sprintf(msg, "Select bird for slot %d", birdSelectionIndex + 1);
        iText(WIN_W / 2 - 100, WIN_H - 100, msg, GLUT_BITMAP_HELVETICA_18);

        for (int i = 0; i < NUM_BIRDS; i++)
        {
            int bx = 300 + i * 200;
            int by = WIN_H / 2;
            iShowImage(bx, by, birdImages[i]);
        }
        iSetColor(255, 255, 0);
        iText(200, 200, "Your bird order:", GLUT_BITMAP_HELVETICA_18);
        for (int i = 0; i < birdSelectionIndex; i++)
        {
            iShowImage(400 + i * 70, 150, birdImages[selectedBirdTypes[i]]);
        }
    }
    else if (gameState == STATE_LEVEL1 || gameState == STATE_LEVEL2)
    {
        iShowImage(0, 0, "assets/images/groundImage2.bmp");
        iShowImage(0, 350, "assets/images/skyImage.bmp");
        iShowImage(1150, 330, "assets/images/tree.png");
        iShowImage(0, 330, "assets/images/grassDecor.png");
        iShowImage(400, 330, "assets/images/grassDecor.png");
        iShowImage(800, 330, "assets/images/grassDecor.png");
        iShowImage(1200, 330, "assets/images/grassDecor.png");

        for (int i = 0; i < blockCount; i++)
        {
            if (blocks[i].isVisible)
            {
                iShowImage((int)blocks[i].x, (int)blocks[i].y, "assets/images/blockImage.bmp");
            }
        }
        for (int i = 0; i < NUM_BIRDS; i++)
        {
            if (birds[i].active)
            {
                iShowImage((int)birds[i].x, (int)birds[i].y, birdImages[birds[i].type]);
            }
        }
        drawSlingshotPuller();
        iShowImage(100, 285, "assets/images/extractedCartoonSlingshotAdd.bmp.bmp");

        // Show projection while aiming (dragging) or ready
        if (ready && birds[currentBird].active && (!launched || dragging))
        {
            double rad = toRad(angle);
            double vx = velocity * cos(rad);
            double vy = velocity * sin(rad);
            double px = 120, py = 450;
            double t_step = 0.1;
            double t_proj = 0;
            int max_steps = 200;

            for (int i = 0; i < max_steps; i++)
            {
                double next_t = t_proj + t_step;
                double next_px = 120 + vx * next_t;
                double next_py = 450 + vy * next_t - 0.5 * g * next_t * next_t;

                if (next_py < 345)
                    break;

                int hit = 0;
                for (int j = 0; j < blockCount; j++)
                {
                    if (blocks[j].isVisible)
                    {
                        if (next_px + BIRD_WIDTH > blocks[j].x && next_px < blocks[j].x + blocks[j].width &&
                            next_py + BIRD_HEIGHT > blocks[j].y && next_py < blocks[j].y + blocks[j].height)
                        {
                            hit = 1;
                            break;
                        }
                    }
                }
                if (hit)
                    break;

                iSetColor(255, 255, 0);
                iLine(px, py, next_px, next_py);

                px = next_px;
                py = next_py;
                t_proj = next_t;
            }
        }

        int boxW = 220, boxH = 120;
        int boxX = 1300;
        int boxY = 720;

        int r = 200 + rand() % 55;
        int g = 50 + rand() % 200;
        int b = 50 + rand() % 200;
        iSetColor(r, g, b);
        iFilledRectangle(boxX, boxY, boxW, boxH);
        iSetColor(152, 79, 166);
        iFilledRectangle(boxX + 10, boxY + 10, boxW - 20, boxH - 20);

        char s1[32], s2[32];
        sprintf(s1, "Angle: %.0f°", angle);
        sprintf(s2, "Speed: %.0f", velocity);
        iSetColor(255, 255, 255);
        iText(boxX + 12, boxY + boxH - 30, s1, GLUT_BITMAP_HELVETICA_18);
        iText(boxX + 12, boxY + boxH - 50, s2, GLUT_BITMAP_HELVETICA_18);

        char scoreText[32];
        sprintf(scoreText, "Score: %d", score);
        iSetColor(255, 255, 255);
        iText(boxX + 12, boxY + boxH - 70, scoreText, GLUT_BITMAP_HELVETICA_18);

        char livesText[32];
        sprintf(livesText, "Lives: %d", lives);
        iSetColor(255, 255, 255);
        iText(boxX + 12, boxY + boxH - 90, livesText, GLUT_BITMAP_HELVETICA_18);
        char levelText[32];
        sprintf(levelText, "Level: %d", gameLevel);
        iText(boxX + 12, boxY + boxH - 110, levelText, GLUT_BITMAP_HELVETICA_18);

        if (levelWon)
        {
            iSetColor(255, 255, 0);
            iText(700, 500, "LEVEL COMPLETE!", GLUT_BITMAP_TIMES_ROMAN_24);
            iText(700, 450, "Press R to continue", GLUT_BITMAP_HELVETICA_18);
        }
    }
    else if (gameState == STATE_LEADERBOARD)
    {
        iSetColor(0, 0, 0);
        iFilledRectangle(0, 0, WIN_W, WIN_H);
        iShowImage(40, 0, "assets/images/LeaderBcover.bmp");
        int r = 200 + rand() % 55;
        int g = 50 + rand() % 200;
        int b = 50 + rand() % 200;
        iSetColor(r, g, b);
        iText(330, 720, "LEADERBOARD", GLUT_BITMAP_TIMES_ROMAN_24);

        // Show all leaderboard entries in white
       iSetColor(255, 255, 255);
       showLeaderBoard();
       
       iSetColor(200, 0, 0);
       iText(60, 60, "Press B to go back", GLUT_BITMAP_HELVETICA_18);
    }
    else if (gameState == STATE_HELP)
    {
        iSetColor(0, 0, 0);
        iFilledRectangle(0, 0, WIN_W, WIN_H);
        iShowImage(0, 0, "assets/images/helpBackGround.bmp");
        iSetColor(0, 0, 0);
        iText(400, 600, "Use arrow keys to set angle and speed.", GLUT_BITMAP_HELVETICA_18);
        iText(400, 550, "Left click to shoot. R to reset. Q to quit.", GLUT_BITMAP_HELVETICA_18);
        iText(400, 500, "B to return to menu.", GLUT_BITMAP_HELVETICA_18);
        iText(400, 450, "Some blocks are harder to break,", GLUT_BITMAP_HELVETICA_18);
        iText(400, 400, "and the falling ones are deadly. Avoid them!", GLUT_BITMAP_HELVETICA_18);
        iText(400, 350, "Complete all levels to win!", GLUT_BITMAP_HELVETICA_18);
        iText(400, 300, "Good luck!", GLUT_BITMAP_HELVETICA_18);
        iText(100, 100, "Press B to go back", GLUT_BITMAP_HELVETICA_18);
    }
    else if (gameState == STATE_CREDITS)
    {
        iSetColor(207, 209, 107);
        iFilledRectangle(0, 0, WIN_W, WIN_H);
        iSetColor(0, 0, 0);
        iText(600, 800, "CREDITS", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(100, 600, "Protik Roy", GLUT_BITMAP_HELVETICA_18);
        iText(100, 550, "BUET CSE'24", GLUT_BITMAP_HELVETICA_18);
        iText(100, 500, "Student ID: 2405163", GLUT_BITMAP_HELVETICA_18);
        iText(900, 600, "Saiful Haque Labib", GLUT_BITMAP_HELVETICA_18);
        iText(900, 550, "BUET CSE'24", GLUT_BITMAP_HELVETICA_18);
        iText(900, 500, "Student ID: 2405164", GLUT_BITMAP_HELVETICA_18);
        iText(400, 400, "Supervised by:", GLUT_BITMAP_HELVETICA_18);
        iText(400, 350, "Rifat Rahman", GLUT_BITMAP_HELVETICA_18);
        iText(100, 100, "Press B to go back", GLUT_BITMAP_HELVETICA_18);
    }
    else if (gameState == STATE_GAMEOVER)
    {
        iSetColor(73, 73, 156);
        iFilledRectangle(0, 0, WIN_W, WIN_H);
        iSetColor(255, 0, 0);
        iText(600, 500, "GAME OVER!", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(600, 450, "Press R to restart or B to go to main menu Q to quit", GLUT_BITMAP_HELVETICA_18);
        iText(600, 400, "Lives: 0", GLUT_BITMAP_HELVETICA_18);

        char scoreMsg[100];
        sprintf(scoreMsg, "Final Score: %d", score);
        iSetColor(255, 0, 0);
        iText(600, 350, scoreMsg, GLUT_BITMAP_HELVETICA_18);
        iText(100, 100, "Press B to go back", GLUT_BITMAP_HELVETICA_18);
    }
    else if(gameState == STATE_VICTORY)
    {
        iShowImage(0, 0, "assets/images/victorycover.bmp");
        iSetColor(255, 215, 0);
        iText(100, 700, "CONGATULATIONS!", GLUT_BITMAP_TIMES_ROMAN_24);

        char scoreMsg[100];
        sprintf(scoreMsg, "Final Score: %d", score);
        iSetColor(0, 0, 0);
        iText(100, 600, scoreMsg, GLUT_BITMAP_HELVETICA_18);
        iText(50, 200, "Press 'B' for menu or 'Q' to quit", GLUT_BITMAP_HELVETICA_18);
    }
}

void ballChange()
{
    if ((gameState != STATE_LEVEL1 && gameState != STATE_LEVEL2) || !launched || gameOver)
        return;

    t += 0.9;
    double rad = toRad(angle);
    double vx = velocity * cos(rad);
    double vy = velocity * sin(rad);
    birds[currentBird].x = 120 + vx * t;
    birds[currentBird].y = 450 + vy * t - 0.5 * g * t * t;

    // Block collision: bird continues flying after hit
    for (int i = 0; i < blockCount; i++)
    {
        if (blocks[i].isVisible)
        {
            Block *b = &blocks[i];
            if (birds[currentBird].x + BIRD_WIDTH > b->x && birds[currentBird].x < b->x + b->width &&
                birds[currentBird].y + BIRD_HEIGHT > b->y && birds[currentBird].y < b->y + b->height)
            {
                b->hitPoints--;
                if (b->hitPoints <= 0)
                {
                    b->isVisible = 0;
                    score += 10;
                }
            }
        }
    }

    // Only end bird's flight when it touches the ground
    if (birds[currentBird].y <= 345)
    {
        birds[currentBird].y = 345;
        launched = false;
        ready = false;
        birds[currentBird].active = false;
        currentBird++;
        if (currentBird < NUM_BIRDS)
        {
            resetCurrentBird();
        }
        else
        {
            gameOver = true;
            gameState = STATE_GAMEOVER;
            saveScore();  // Save score when game actually ends
        }
        return;
    }

    allGone = true;
    for (int i = 0; i < blockCount; i++)
    {
        if (blocks[i].isVisible)
        {
            allGone = false;
            break;
        }
    }
    if (allGone && !levelWon)
    {
        levelWon = true;
        launched = false;
        ready = false;
        // Check for game victory
        if (gameState == STATE_LEVEL2) {
            gameState = STATE_VICTORY;
            saveScore();
            return;
        }
        // Save score only once per level
        saveScore();
    }
}

void updateBlockPositions()
{
    for (int i = 0; i < blockCount; i++)
    {
        if (!blocks[i].isVisible)
            continue;

        // Falling block
        if (blocks[i].isFalling)
        {
            blocks[i].y += blocks[i].vy;
            if (blocks[i].y <= 345)
            {
                blocks[i].y = 345;
                blocks[i].vy = 0;
                blocks[i].isFalling = 0;
            }
        }
        // Moving block
        if (blocks[i].isMoving)
        {
            blocks[i].x += blocks[i].vx;
            if (blocks[i].x <= 100 || blocks[i].x + blocks[i].width >= WIN_W)
            {
                blocks[i].vx *= -1;
            }
            if (blocks[i].y <= 300 || blocks[i].y + blocks[i].height >= WIN_H)
            {
                blocks[i].vy *= -1;
            }
        }
    }
}

void coverTimerFunc()
{
    if (gameState == STATE_COVER)
    {
        coverTimer++;
        if (coverTimer >= 7)
        {
            gameState = STATE_MENU;
        }
    }
}

void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (gameState == STATE_MENU)
        {
            int btnW = 200, btnH = 50, x = 660;
            int y1 = 500, y2 = 400, y3 = 300, y4 = 200, y5 = 100;
            int soundBtnX = WIN_W - 80, soundBtnY = WIN_H - 80, soundBtnW = 60, soundBtnH = 60;
            // Menu buttons continue below
            // Start Game
            if (mx >= x && mx <= x + btnW && my >= y1 && my <= y1 + btnH)
            {
                gameState = STATE_LEVEL_SELECT;
                return;
            }
            // Leaderboard
            if (mx >= x && mx <= x + btnW && my >= y2 && my <= y2 + btnH)
            {
                gameState = STATE_LEADERBOARD;
                return;
            }
            // Help
            if (mx >= x && mx <= x + btnW && my >= y3 && my <= y3 + btnH)
            {
                gameState = STATE_HELP;
                return;
            }
            // Credits
            if (mx >= x && mx <= x + btnW && my >= y4 && my <= y4 + btnH)
            {
                gameState = STATE_CREDITS;
                return;
            }
            // Exit
            if (mx >= x && mx <= x + btnW && my >= y5 && my <= y5 + btnH)
            {
                if (bgmChannel != -1) {
                    iStopSound(bgmChannel);
                }
                exit(0);
            }
        }
        else if(gameState == STATE_LEVEL_SELECT)
        {
            //Level select
            if(mx>=660 && mx<=860 && my>=400 && my<=450)
            {
                selectedLevel = 1;
                gameState = STATE_NAMEINPUT;
                nameCharIndex = 0;
                playerName[0] = '\0';
            }
            else if(mx>=660 && mx<=860 && my>=300 && my<=350)
            {
                selectedLevel = 2;
                gameState = STATE_NAMEINPUT;
                nameCharIndex = 0;
                playerName[0] = '\0';
            }
        }
        else if (gameState == STATE_BIRDSELECT)
        {
            for (int i = 0; i < NUM_BIRDS; i++)
            {
                int bx = 300 + i * 200;
                int by = WIN_H / 2;
                if (mx >= bx && mx <= bx + BIRD_WIDTH && my >= by && my <= by + BIRD_HEIGHT)
                {
                    selectedBirdTypes[birdSelectionIndex] = i;
                    birdSelectionIndex++;
                    if (birdSelectionIndex == NUM_BIRDS)
                    {
                        if(selectedLevel == 1){
                            gameState = STATE_LEVEL1;
                            score = 0;
                            lives = 5;
                            gameOver = false;
                            levelWon = false;
                            initBlocks1();
                            initBirds();
                            resetCurrentBird();
                            launched = false;
                            ready = true;
                            dragging = false;
                        }
                        else if(selectedLevel == 2){
                            gameState = STATE_LEVEL2;
                            score = 0;
                            lives = 5;
                            gameOver = false;
                            levelWon = false;
                            initBlocks2();
                            initBirds();
                            resetCurrentBird();
                            launched = false;
                            ready = true;
                            dragging = false;
                        }
                    }
                }
            }
        }
        else if ((gameState == STATE_LEVEL1 || gameState == STATE_LEVEL2) && ready && !launched && birds[currentBird].active)
        {
            if (!dragging)
            {
                launched = true;
                ready = false;
                t = 0;
            }
        }
    }
    if ((gameState == STATE_LEVEL1 || gameState == STATE_LEVEL2) && ready && !launched && birds[currentBird].active)
    {
        int bx = (int)birds[currentBird].x + BIRD_WIDTH / 2;
        int by = (int)birds[currentBird].y + BIRD_HEIGHT / 2;
        if (abs(mx - bx) < 40 && abs(my - by) < 40)
        {
            dragging = true;
            dragX = mx;
            dragY = my;
        }
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        if (dragging)
        {
            int dx = 120 - dragX;
            int dy = 450 - dragY;
            double dist = sqrt(dx * dx + dy * dy);
            angle = atan2(dy, dx) * 180.0 / M_PI;
            if (angle < 0)
                angle += 360;
            if (angle > 90)
                angle = 90;
            if (angle < 0)
                angle = 0;
            velocity = dist * 1.2;
            if (velocity > 200)
                velocity = 200;
            if (velocity < 10)
                velocity = 10;
            launched = true;
            ready = false;
            t = 0;
            dragging = false;
        }
    }
}

void iMouseMove(int mx, int my)
{
    if (dragging)
    {
        dragX = mx;
        dragY = my;
    }
}

void iMouseDrag(int mx, int my)
{
    if (dragging)
    {
        dragX = mx;
        dragY = my;
    }
}

void iMouseWheel(int dir, int mx, int my) {}

void iKeyboard(unsigned char key)
{
    if (gameState == STATE_NAMEINPUT)
    {
        if (key == '\r')
        {
            gameState = STATE_BIRDSELECT;
            gameLevel = selectedLevel;
            birdSelectionIndex = 0;
        }
        else if (key == '\b' && nameCharIndex > 0)
        {
            playerName[--nameCharIndex] = '\0';
        }
        else if (nameCharIndex < 99 && ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9')))
        {
            playerName[nameCharIndex++] = key;
            playerName[nameCharIndex] = '\0';
        }
        return;
    }
    if (key == 'r')
    {
        if (levelWon && gameState == STATE_LEVEL1)
        {
            // Go to level 2
            gameState = STATE_LEVEL2;
            gameLevel = 2;
            initBlocks2();
            initBirds();
            resetCurrentBird();
            launched = false;
            ready = true;
            levelWon = false;
            gameOver = false;
        }
        else if (levelWon && gameState == STATE_LEVEL2)
        {
            // Game complete, back to menu
            saveScore();
            gameState = STATE_MENU;
            bgmChannel = iPlaySound("bin/assets/sounds/gameBGM.wav", true, 100);
        }
        else if (gameState == STATE_GAMEOVER)
        {
            // Restart from level 1
            gameState = STATE_LEVEL1;
            gameLevel = 1;
            score = 0;
            lives = 5;
            initBlocks1();
            initBirds();
            resetCurrentBird();
            launched = false;
            ready = true;
            levelWon = false;
            gameOver = false;
        }
        else if ((gameState == STATE_LEVEL1 || gameState == STATE_LEVEL2) && !levelWon && gameOver)
        {
            // Restart current level
            if (gameState == STATE_LEVEL1)
                initBlocks1();
            else
                initBlocks2();
            initBirds();
            resetCurrentBird();
            launched = false;
            ready = true;
            levelWon = false;
            gameOver = false;
        }
    }
    else if (key == 'q')
    {
        saveScore();
        if (bgmChannel != -1) {
            iStopSound(bgmChannel);
        }
        exit(0);
    }
    else if (key == 'b')
    {
        gameState = STATE_MENU;
        // State changed to menu
    }
}

void iSpecialKeyboard(unsigned char key)
{
    if ((gameState == STATE_LEVEL1 || gameState == STATE_LEVEL2) && ready && !dragging)
    {
        if (key == GLUT_KEY_UP && angle < 90)
            angle += 1;
        else if (key == GLUT_KEY_DOWN && angle > 0)
            angle -= 1;
        else if (key == GLUT_KEY_RIGHT && velocity < 200)
            velocity += 1;
        else if (key == GLUT_KEY_LEFT && velocity > 10)
            velocity -= 1;
    }
    if (key == GLUT_KEY_END) {
        if (bgmChannel != -1) {
            iStopSound(bgmChannel);
        }
        exit(0);
    }
}

int main(int argc, char *argv[])
{
    // Ensure console window stays visible
    ShowWindow(GetConsoleWindow(), SW_SHOW);
    
    iInitializeSound();
    glutInit(&argc, argv);
    iSetTimer(500, coverTimerFunc);
    iSetTimer(10, ballChange);
    iSetTimer(20, updateBlockPositions);
    srand(time(0));
    initBlocks1();
    for (int i = 0; i < NUM_BIRDS; i++)
        selectedBirdTypes[i] = i;
    initBirds();

    iInitialize(WIN_W, WIN_H, "Angry Birds Clone");
    
    bgmChannel = iPlaySound("bin/assets/sounds/gameBGM.wav", true, 100);
    
    // Do NOT call iFreeSound() here; let the OS clean up on exit.
    return 0;
}