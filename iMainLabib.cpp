
// #include "iGraphics.h"
// #include <math.h>
// #include <stdbool.h>
// #include <time.h>
// #include <stdio.h>
// #include <stdlib.h>

// #define WIN_W 1550
// #define WIN_H 1000
// #define MAX_BLOCKS 1000
// #define BIRD_WIDTH 60
// #define BIRD_HEIGHT 60
// #define BLOCK_WIDTH 30
// #define BLOCK_HEIGHT 30
// #define LEADERBOARD 3
// #define MAX_NAME_LEN 100
// // Game state
// int gameState = -1;
// int coverTimer = 0;
// int gameLevel = 0;

// // Bird and physics
// double bird_x = 120, bird_y = 450;
// double velocity = 90; // initial speed
// double angle = 30;    // launch angle
// double g = 9.8;
// double t = 0;
// bool launched = false;
// bool ready = true;
// int score = 0;
// bool levelWon = false;
// bool allGone = false;
// int lives = 4;
// bool birdDead = false;
// bool gameOver = false;

// // score and leaderboard
// char playerName[MAX_NAME_LEN] = "";
// int nameCharIndex = 0;
// bool enteringName = false;

// static double toRad(double deg) { return deg * M_PI / 180.0; }

// typedef struct
// {
//     float x, y;
//     float width, height;
//     int isVisible;
//     int hitPoints;
//     int isFalling;
//     int isMoving;
//     float vx, vy;
//     int isDeadly;
// } Block;

// Block blocks[MAX_BLOCKS];
// int blockCount = 0;

// void addBlock(float x, float y, float w, float h, int isVisible, int health, int isFalling, int isMoving, float dx, float dy, int isDeadly)
// {
//     if (blockCount >= MAX_BLOCKS)
//         return;
//     blocks[blockCount++] = (Block){x, y, w, h, 1, health, isFalling, isMoving, dx, dy, isDeadly};
// }

// void addPyramid(float centerX, float baseY, int layers, float w, float h, int health)
// {
//     for (int i = 0; i < layers; i++)
//     {
//         int count = layers - i;
//         float startX = centerX - (count * w) / 2;
//         for (int j = 0; j < count; j++)
//         {
//             addBlock(startX + j * w, baseY + i * h, w, h, 1, health, 0, 0, 0, 0, 0);
//         }
//     }
// }

// void addBlockGrid(float startX, float startY, int rows, int cols, float w, float h, int health)
// {
//     for (int i = 0; i < rows; i++)
//     {
//         for (int j = 0; j < cols; j++)
//         {
//             addBlock(startX + j * w, startY + i * h, w, h, 1, health, 0, 0, 0, 0, 0);
//         }
//     }
// }

// void addPerimeterGrid(float startX, float startY, int rows, int cols, float w, float h, int thickness, int health)
// {
//     for (int r = 0; r < rows; r++)
//     {
//         for (int c = 0; c < cols; c++)
//         {
//             bool isEdge = (r < thickness || r >= rows - thickness || c < thickness || c >= cols - thickness);
//             if (isEdge)
//             {
//                 float x = startX + c * w;
//                 float y = startY + r * h;
//                 addBlock(x, y, w, h, 1, health, 0, 0, 0, 0, 0);
//             }
//         }
//     }
// }

// void fallingBlock(float x, float y, float w, float h, int health, float dy, int isDeadly)
// {
//     addBlock(x, y, w, h, 1, health, 1, 0, 0, dy, isDeadly);
// }

// void movingBlocks(float x, float y, float w, float h, int health, float dx)
// {
//     addBlock(x, y, w, h, 1, health, 0, 1, dx, 0, 0);
// }

// void initBlocks1() // blocks for level 1
// {
//     blockCount = 0;
//     addPerimeterGrid(600, 350, 7, 9, BLOCK_WIDTH, BLOCK_HEIGHT, 2, 1);
//     float pyramidcenterX = 600 + 9 * BLOCK_WIDTH / 2;
//     float pyramidbaseY = 350 + 7 * BLOCK_HEIGHT;
//     addPyramid(pyramidcenterX, pyramidbaseY, 4, BLOCK_WIDTH, BLOCK_HEIGHT, 1);
// }
// void initBlocks2() // blocks for level 2
// {
//     blockCount = 0;
//     addBlockGrid(700, 350, 5, 3, BLOCK_WIDTH, BLOCK_HEIGHT, 1);
//     addPyramid(850, 350, 3, BLOCK_WIDTH, BLOCK_HEIGHT, 1);
//     movingBlocks(600, 500, BLOCK_WIDTH, BLOCK_HEIGHT, 1, 4);
//     fallingBlock(400, 800, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
//     fallingBlock(600, 800, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
//     fallingBlock(800, 600, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
//     fallingBlock(1000, 800, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
//     fallingBlock(500, 350, BLOCK_WIDTH, BLOCK_HEIGHT, 1, 4, 1);
//     movingBlocks(1200, 600, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4);
//     movingBlocks(300, 600, BLOCK_WIDTH, BLOCK_HEIGHT, 1, 4);
//     movingBlocks(1000, 500, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4);
//     movingBlocks(400, 500, BLOCK_WIDTH, BLOCK_HEIGHT, 1, 4);
// }

// typedef struct
// {
//     char name[100];
//     int score;
// } Leader;

// Leader leaders[100];
// int leaderCount = 0;

// void loadLeaderboard()
// {
//     leaderCount = 0;
//     FILE *fp = fopen("bin\\assets\\leaderboard.txt", "r");
//     if (fp == NULL)
//         return;
//     while (fscanf(fp, "%s %d", leaders[leaderCount].name, &leaders[leaderCount].score) == 2)
//     {
//         leaderCount++;
//         if (leaderCount >= 100)
//             break; // limit to 100 leaders
//     }
//     fclose(fp);
// }

// // Save score to file
// void saveScore()
// {
//     FILE *file = fopen("bin\\assets\\leaderboard.txt", "a");
//     if (file)
//     {
//         fprintf(file, "%s %d\n", playerName, score);
//         fclose(file);
//     }
// }

// void showLeaderboard()
// {
//     FILE *file = fopen("bin\\assets\\leaderboard.txt", "r");
//     if (!file)
//     {
//         iText(600, 200, "No leaderboard data available.", GLUT_BITMAP_HELVETICA_18);
//         return;
//     }

//     Leader tempLeaders[100];
//     int count = 0;

//     while (fscanf(file, "%s %d", tempLeaders[count].name, &tempLeaders[count].score) == 2)
//     {
//         count++;
//         if (count >= 100)
//             break;
//     }
//     fclose(file);

//     if (count == 0)
//     {
//         iText(600, 200, "No leaderboard data yet.", GLUT_BITMAP_HELVETICA_18);
//         return;
//     }
//     // Sort leaders by score
//     for (int i = 0; i < count - 1; i++)
//     {
//         for (int j = i + 1; j < count; j++)
//         {
//             if (tempLeaders[j].score > tempLeaders[i].score)
//             {
//                 Leader temp = tempLeaders[i];
//                 tempLeaders[i] = tempLeaders[j];
//                 tempLeaders[j] = temp;
//             }
//         }
//     }
//     // Show top 5
//     iSetColor(255, 255, 0);
//     iText(600, 800, "LEADERBOARD", GLUT_BITMAP_HELVETICA_18);
//     for (int i = 0; i < count && i < 5; i++)
//     {
//         char line[200];
//         sprintf(line, "%d.%s - %d", i + 1, tempLeaders[i].name, tempLeaders[i].score);
//         iText(600, 550 - i * 30, line, GLUT_BITMAP_HELVETICA_18);
//     }
// }

// void iDraw()
// {
//     iClear();

//     if (gameState == -1)
//     {
//         // COVER SCREEN
//         // iSetColor(0, 0, 0);
//         // iFilledRectangle(0, 0, WIN_W, WIN_H);
//         iShowImage(0, 0, "assets/images/coverS.bmp");
//         iSetColor(209, 24, 203);
//         iText(WIN_W / 2 - 30, 60, "Loading...", GLUT_BITMAP_TIMES_ROMAN_24);
//     }

//     else if (gameState == 0)
//     {
//         // MAIN MENU
//         iSetColor(97, 148, 227);
//         iFilledRectangle(0, 0, WIN_W, WIN_H);

//         const char *title = "ANGRY BIRDS";
//         int titleX = 615, titleY = 600;
//         int spacing = 30;
//         for (int i = 0; title[i]; i++)
//         {
//             int r = 200 + rand() % 55;
//             int g = 50 + rand() % 200;
//             int b = 50 + rand() % 200;

//             iSetColor(r, g, b);
//             char ch[2] = {title[i], '\0'};
//             iText(titleX + i * spacing, titleY, ch, GLUT_BITMAP_TIMES_ROMAN_24);
//         }

//         int btnW = 200, btnH = 50, x = 660;
//         int y1 = 500, y2 = 400, y3 = 100, y4 = 300, y5 = 200;
//         // Start Game Button
//         iSetColor(0, 100, 0);
//         iFilledRectangle(x + 5, y1 - 5, btnW, btnH);
//         iSetColor(0, 200, 0);
//         iFilledRectangle(x, y1, btnW, btnH);
//         iSetColor(255, 255, 255);
//         iText(x + 50, y1 + 15, "START GAME", GLUT_BITMAP_HELVETICA_18);
//         // Help Button
//         iSetColor(0, 0, 100);
//         iFilledRectangle(x + 5, y2 - 5, btnW, btnH);
//         iSetColor(0, 0, 200);
//         iFilledRectangle(x, y2, btnW, btnH);
//         iSetColor(255, 255, 255);
//         iText(x + 70, y2 + 15, "HELP", GLUT_BITMAP_HELVETICA_18);
//         // Exit Button
//         iSetColor(100, 0, 0);
//         iFilledRectangle(x + 5, y3 - 5, btnW, btnH);
//         iSetColor(200, 0, 0);
//         iFilledRectangle(x, y3, btnW, btnH);
//         iSetColor(255, 255, 255);
//         iText(x + 75, y3 + 15, "EXIT", GLUT_BITMAP_HELVETICA_18);
//         // Leaderboard Button
//         iSetColor(100, 100, 0);
//         iFilledRectangle(x + 5, y4 - 5, btnW, btnH);
//         iSetColor(200, 200, 0);
//         iFilledRectangle(x, y4, btnW, btnH);
//         iSetColor(255, 255, 255);
//         iText(x + 50, y4 + 15, "LEADERBOARD", GLUT_BITMAP_HELVETICA_18);
//         // Credits
//         iSetColor(100, 0, 100);
//         iFilledRectangle(x + 5, y5 - 5, btnW, btnH);
//         iSetColor(200, 0, 200);
//         iFilledRectangle(x, y5, btnW, btnH);
//         iSetColor(255, 255, 255);
//         iText(x + 50, y5 + 15, "CREDITS", GLUT_BITMAP_HELVETICA_18);

//         if (enteringName)
//         {
//             iSetColor(0, 0, 0);
//             iFilledRectangle(0, 0, WIN_W, WIN_H);
//             iSetColor(255, 255, 255);
//             iText(WIN_W / 2 - 100, WIN_H / 2, "Enter your name: ", GLUT_BITMAP_HELVETICA_18);
//             iText(WIN_W / 2 - 100, WIN_H / 2 - 30, playerName, GLUT_BITMAP_HELVETICA_18);
//         }
//     }
//     // Gameplay
//     else if (gameState == 1 && gameLevel == 1)
//     {
//         iShowImage(0, 0, "assets/images/groundImage2.bmp");
//         iShowImage(0, 350, "assets/images/skyImage.bmp");
//         iShowImage(1150, 330, "assets/images/tree.png");
//         iShowImage(0, 330, "assets/images/grassDecor.png");
//         iShowImage(400, 330, "assets/images/grassDecor.png");
//         iShowImage(800, 330, "assets/images/grassDecor.png");
//         iShowImage(1200, 330, "assets/images/grassDecor.png");
//         iShowImage((int)bird_x, (int)bird_y, "assets/images/extractedCartoonBirdAdd.bmp");
//         iShowImage(100, 285, "assets/images/extractedCartoonSlingshotAdd.bmp.bmp");

//         for (int i = 0; i < blockCount; i++)
//         {
//             if (blocks[i].isVisible)
//             {
//                 iShowImage((int)blocks[i].x, (int)blocks[i].y, "assets/images/blockImage.bmp");
//             }
//         }

//         if (ready)
//         {
//             double rad = toRad(angle),
//                    len = 150,
//                    ex = bird_x + len * cos(rad),
//                    ey = bird_y + len * sin(rad);

//             iSetColor(0, 100, 255);
//             iLine(bird_x, bird_y, ex, ey);
//         }
//         // HUD
//         int boxW = 220, boxH = 120;
//         int boxX = 1300;
//         int boxY = 720;

//         int r = 200 + rand() % 55;
//         int g = 50 + rand() % 200;
//         int b = 50 + rand() % 200;
//         iSetColor(r, g, b);
//         iFilledRectangle(boxX, boxY, boxW, boxH);
//         iSetColor(152, 79, 166);
//         iFilledRectangle(boxX + 10, boxY + 10, boxW - 20, boxH - 20);

//         // HUD text
//         char s1[32], s2[32];
//         sprintf(s1, "Angle: %.0f°", angle);
//         sprintf(s2, "Speed: %.0f", velocity);
//         iSetColor(255, 255, 255);
//         iText(boxX + 12, boxY + boxH - 10, s1, GLUT_BITMAP_HELVETICA_18);
//         iText(boxX + 12, boxY + boxH - 30, s2, GLUT_BITMAP_HELVETICA_18);

//         char scoreText[32];
//         sprintf(scoreText, "Score: %d", score);
//         iSetColor(255, 255, 255);
//         iText(boxX + 12, boxY + boxH - 50, scoreText, GLUT_BITMAP_HELVETICA_18);

//         char livesText[32];
//         sprintf(livesText, "Lives: %d", lives);
//         iSetColor(255, 255, 255);
//         iText(boxX + 12, boxY + boxH - 80, livesText, GLUT_BITMAP_HELVETICA_18);
//         char levelText[32];
//         sprintf(levelText, "Level: %d", gameLevel);
//         iText(boxX + 12, boxY + boxH - 110, levelText, GLUT_BITMAP_HELVETICA_18);

//         if (levelWon)
//         {
//             iSetColor(255, 255, 0);
//             iText(700, 500, "LEVEL COMPLETE!", GLUT_BITMAP_TIMES_ROMAN_24);
//             iText(700, 450, "Press R to reset", GLUT_BITMAP_HELVETICA_18);
//         }
//     }
//     else if (gameState == 1 && gameLevel == 2)
//     {
//         iShowImage(0, 0, "assets/images/groundImage2.bmp");
//         iShowImage(0, 350, "assets/images/skyImage.bmp");
//         iShowImage(1150, 330, "assets/images/tree.png");
//         iShowImage(0, 330, "assets/images/grassDecor.png");
//         iShowImage(400, 330, "assets/images/grassDecor.png");
//         iShowImage(800, 330, "assets/images/grassDecor.png");
//         iShowImage(1200, 330, "assets/images/grassDecor.png");
//         iShowImage((int)bird_x, (int)bird_y, "assets/images/extractedCartoonBirdAdd.bmp");
//         iShowImage(100, 285, "assets/images/extractedCartoonSlingshotAdd.bmp.bmp");

//         for (int i = 0; i < blockCount; i++)
//         {
//             if (blocks[i].isVisible)
//             {
//                 iShowImage((int)blocks[i].x, (int)blocks[i].y, "assets/images/blockImage.bmp");
//             }
//         }

//         if (ready)
//         {
//             double rad = toRad(angle),
//                    len = 150,
//                    ex = bird_x + len * cos(rad),
//                    ey = bird_y + len * sin(rad);

//             iSetColor(0, 100, 255);
//             iLine(bird_x, bird_y, ex, ey);
//         }

//         // HUD
//         int boxW = 220, boxH = 150;
//         int boxX = 1300;
//         int boxY = 720;

//         int r = 200 + rand() % 55;
//         int g = 50 + rand() % 200;
//         int b = 50 + rand() % 200;
//         iSetColor(r, g, b);
//         iFilledRectangle(boxX, boxY, boxW, boxH);
//         iSetColor(152, 79, 166);
//         iFilledRectangle(boxX + 10, boxY + 10, boxW - 20, boxH - 20);

//         // HUD text
//         char s1[32], s2[32];
//         sprintf(s1, "Angle: %.0f°", angle);
//         sprintf(s2, "Speed: %.0f", velocity);
//         iSetColor(255, 255, 255);
//         iText(boxX + 12, boxY + boxH - 10, s1, GLUT_BITMAP_HELVETICA_18);
//         iText(boxX + 12, boxY + boxH - 30, s2, GLUT_BITMAP_HELVETICA_18);

//         char scoreText[32];
//         sprintf(scoreText, "Score: %d", score);
//         iSetColor(255, 255, 255);
//         iText(boxX + 12, boxY + boxH - 50, scoreText, GLUT_BITMAP_HELVETICA_18);

//         char livesText[32];
//         sprintf(livesText, "Lives: %d", lives);
//         iSetColor(255, 255, 255);
//         iText(boxX + 12, boxY + boxH - 80, livesText, GLUT_BITMAP_HELVETICA_18);
//         char levelText[32];
//         sprintf(levelText, "Level: %d", gameLevel);
//         iText(boxX + 12, boxY + boxH - 110, levelText, GLUT_BITMAP_HELVETICA_18);

//         if (levelWon)
//         {
//             iSetColor(255, 255, 0);
//             iText(700, 500, "LEVEL COMPLETE!", GLUT_BITMAP_TIMES_ROMAN_24);
//             iText(700, 450, "Press R to reset", GLUT_BITMAP_HELVETICA_18);
//         }
//     }

//     else if (gameState == 2)
//     {
//         iSetColor(97, 153, 8);
//         iFilledRectangle(0, 0, WIN_W, WIN_H);
//         // Help text
//         iSetColor(255, 255, 255);

//         iText(400, 650, "HELP", GLUT_BITMAP_HELVETICA_18);
//         iText(400, 600, "Use arrow keys to set angle and speed.", GLUT_BITMAP_HELVETICA_18);
//         iText(400, 550, "Left click to shoot. R to reset. Q to quit.", GLUT_BITMAP_HELVETICA_18);
//         iText(400, 500, "B to return to menu.", GLUT_BITMAP_HELVETICA_18);
//     }

//     else if (gameState == LEADERBOARD)
//     {
//         iSetColor(97, 153, 8);
//         iFilledRectangle(0, 0, WIN_W, WIN_H);
//         iSetColor(255, 255, 255);
//         iText(400, 650, "LEADERBOARD", GLUT_BITMAP_TIMES_ROMAN_24);
//         showLeaderboard();
//         iText(100, 100, "Press B to go back", GLUT_BITMAP_HELVETICA_18);
//     }
//     else if (gameState == 4)
//     {
//         iSetColor(73, 73, 156);
//         iFilledRectangle(0, 0, WIN_W, WIN_H);
//         iSetColor(255, 0, 0);
//         iText(600, 500, "GAME OVER!", GLUT_BITMAP_TIMES_ROMAN_24);
//         iText(600, 450, "Press R to restart or Q to quit", GLUT_BITMAP_HELVETICA_18);
//         iText(600, 400, "Lives: 0", GLUT_BITMAP_HELVETICA_18);
//     }
//     else if (gameState == 5)
//     {
//         iSetColor(201, 103, 104);
//         iFilledRectangle(0, 0, WIN_W, WIN_H);
//         int r = 200 + rand() % 55;
//         int g = 50 + rand() % 200;
//         int b = 50 + rand() % 200;
//         iSetColor(r, g, b);
//         iText(600, 500, "CONGRATULATIONS!", GLUT_BITMAP_TIMES_ROMAN_24);
//         iSetColor(0, 0, 0);

//         char msg[100];
//         sprintf(msg, "You completed the game with a score of %d", score);
//         iText(500, 450, msg, GLUT_BITMAP_HELVETICA_18);

//         iText(600, 200, "Press B to return to Main menu", GLUT_BITMAP_HELVETICA_18);
//         iText(600, 150, "Press Q to quit", GLUT_BITMAP_HELVETICA_18);
//         iText(600, 100, "Press R to restart", GLUT_BITMAP_HELVETICA_18);
//     }
//     else if (gameState == 6)
//     {
//         iSetColor(0, 0, 0);
//         iFilledRectangle(0, 0, WIN_W, WIN_H);
//         iSetColor(255, 255, 0);
//         iText(WIN_W / 2 - 120, WIN_H / 2, "Get Ready! Moving to Level 2...", GLUT_BITMAP_TIMES_ROMAN_24);
//         iText(WIN_W / 2 - 100, WIN_H / 2 - 40, "Press R to Continue", GLUT_BITMAP_HELVETICA_18);
//     }
// }

// void ballChange()
// {
//     if (gameState != 1 || !launched || gameOver)
//         return;
//     // Update physics
//     t += 0.9;
//     double rad = toRad(angle);
//     bird_x = 120 + velocity * cos(rad) * t;
//     bird_y = 450 + velocity * sin(rad) * t - 0.5 * g * t * t;

//     // Land
//     if (bird_y <= 345)
//     {
//         bird_y = 345;
//         launched = false;
//         ready = false;
//         birdDead = true; // bird landed without hitting deadly block
//     }

//     // Check collision with blocks
//     for (int i = 0; i < blockCount; i++)
//     {
//         if (blocks[i].isVisible)
//         {
//             Block b = blocks[i];

//             if (bird_x + BIRD_WIDTH > b.x && bird_x - BIRD_WIDTH < b.x + b.width &&
//                 bird_y + BIRD_HEIGHT > b.y && bird_y - BIRD_HEIGHT < b.y + b.height)
//             {
//                 if (b.isDeadly)
//                 {
//                     birdDead = true;
//                     launched = false;
//                     ready = false;
//                 }
//                 else
//                 {
//                     blocks[i].hitPoints--;
//                     if (blocks[i].hitPoints <= 0)
//                     {
//                         blocks[i].isVisible = 0;
//                         score += b.isDeadly ? -10 : (b.hitPoints == 2 ? 20 : 10);
//                     }
//                 }
//             }
//         }
//     }
//     allGone = true;
//     for (int i = 0; i < blockCount; i++)
//     {
//         if (blocks[i].isVisible)
//         {
//             allGone = false;
//             break;
//         }
//     }
//     if (allGone && !levelWon)
//     {
//         levelWon = true;
//         launched = false;
//         ready = false;

//         if (gameLevel == 2)
//         {
//             gameState = 5;
//             saveScore();
//         }
//     }
// }

// void updateBlockPositions()
// {
//     for (int i = 0; i < blockCount; i++)
//     {
//         if (!blocks[i].isVisible)
//             continue;

//         // Falling block (e.g., drops from sky)
//         if (blocks[i].isFalling)
//         {
//             blocks[i].y += blocks[i].vy;

//             // If it hits the ground (you can adjust the threshold)
//             if (blocks[i].y <= 345)
//             {
//                 blocks[i].y = 345;
//                 blocks[i].vy = 0;
//                 blocks[i].isFalling = 0;
//             }

//             // Check if it hits the bird
//             if (
//                 bird_x + BIRD_WIDTH > blocks[i].x && bird_x < blocks[i].x + blocks[i].width &&
//                 bird_y + BIRD_HEIGHT > blocks[i].y && bird_y < blocks[i].y + blocks[i].height &&
//                 blocks[i].isDeadly)
//             {
//                 // Bird "dies" — respawn next
//                 bird_x = 120;
//                 bird_y = 450;
//                 t = 0;
//                 launched = false;
//                 ready = true;
//             }
//         }

//         // Moving block (horizontal or vertical)
//         if (blocks[i].isMoving)
//         {
//             blocks[i].x += blocks[i].vx;

//             // Bounce from bounds (optional: give movement range limit)
//             if (blocks[i].x <= 100 || blocks[i].x + blocks[i].width >= WIN_W)
//             {
//                 blocks[i].vx *= -1;
//             }
//             if (blocks[i].y <= 300 || blocks[i].y + blocks[i].height >= WIN_H)
//             {
//                 blocks[i].vy *= -1; // Bounce vertically if needed
//             }
//         }
//     }
// }

// void transitionToLevel2()
// {
//     if (gameState == 5)
//     {
//         gameLevel = 2;
//         initBlocks2();
//         bird_x = 120;
//         bird_y = 450;
//         t = 0;
//         launched = false;
//         ready = true;
//         levelWon = false;
//         gameState = 1;
//     }
// }

// void iMouse(int button, int state, int mx, int my)
// {
//     if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//     {
//         // Menu state
//         if (gameState == 0)
//         {
//             if (mx >= 660 && mx <= 860 && my >= 500 && my <= 550)
//             {
//                 enteringName = true; // Prompt name input
//                 nameCharIndex = 0;
//                 playerName[0] = '\0'; // Reset name
//             }
//             else if (mx >= 660 && mx <= 860 && my >= 400 && my <= 450)
//             {
//                 gameState = LEADERBOARD; // LEADERBOARD
//             }
//             else if (mx >= 660 && mx <= 860 && my >= 200 && my <= 250)
//             {
//                 gameState = 2; // HELP
//             }
//             else if (mx >= 660 && mx <= 860 && my >= 100 && my <= 150)
//             {
//                 exit(0); // EXIT
//             }
//         }

//         // Launch bird in Game screen
//         else if (gameState == 1 && ready && !launched)
//         {
//             launched = true;
//             ready = false;
//             t = 0;
//         }

//         else if (gameState == 1 && gameLevel == 2 && ready && !launched)
//         {
//             launched = true;
//             ready = false;
//             t = 0;
//         }
//     }
// }

// void iKeyboard(unsigned char key)
// {
//     if (key == 'r')
//     {
//         if (levelWon)
//         {
//             if (gameLevel == 1)
//             {
//                 gameState = 6;
//             }
//             else if (gameLevel == 2)
//             {
//                 saveScore();
//                 gameState = 0;
//                 return;
//             }
//             bird_x = 120;
//             bird_y = 450;
//             t = 0;
//             launched = false;
//             ready = true;
//             levelWon = false;
//         }
//         else if (birdDead && lives > 0)
//         {
//             lives--;
//             bird_x = 120;
//             bird_y = 450;
//             t = 0;
//             launched = false;
//             ready = true;
//             levelWon = false;
//             birdDead = false;
//         }
//         else if (lives == 0)
//         {
//             gameOver = true;
//             gameState = 4;
//         }

//         bird_x = 120;
//         bird_y = 450;
//         t = 0;
//         launched = false;
//         ready = true;
//         levelWon = false;

//         if (gameLevel == 2 && levelWon && lives > 0)
//         {
//             saveScore();
//         }
//     }

//     else if (key == 'q')
//     {
//         saveScore();
//         exit(0);
//     }
//     else if (key == 'b') // back to menu
//     {
//         gameState = 0;
//     }

//     if (enteringName)
//     {
//         if (key == '\r')
//         { // Enter key
//             enteringName = false;
//             gameState = 1;
//             gameLevel = 1;
//             score = 0;
//             lives = 5;
//             initBlocks1();
//             launched = false;
//             ready = true;
//         }
//         else if (key == '\b' && nameCharIndex > 0)
//         { // Backspace
//             playerName[--nameCharIndex] = '\0';
//         }
//         else if (nameCharIndex < 99 && (key >= 'a' && key <= 'z' || key >= 'A' && key <= 'Z' || key >= '0' && key <= '9'))
//         {
//             playerName[nameCharIndex++] = key;
//             playerName[nameCharIndex] = '\0';
//         }
//         return;
//     }
// }

// void iSpecialKeyboard(unsigned char key)
// {
//     if (gameState == 1 && ready)
//     {
//         if (key == GLUT_KEY_UP && angle < 90)
//             angle += 1;
//         else if (key == GLUT_KEY_DOWN && angle > 0)
//             angle -= 1;
//         else if (key == GLUT_KEY_RIGHT && velocity < 200)
//             velocity += 1;
//         else if (key == GLUT_KEY_LEFT && velocity > 10)
//             velocity -= 1;
//     }
//     if (key == GLUT_KEY_END)
//         exit(0);
// }

// // Timer function to handle cover screen delay
// // This will switch from the cover screen to the main menu after a delay
// void coverTimerFunc()
// {
//     if (gameState == -1)
//     {
//         coverTimer++;
//         if (coverTimer >= 7)
//         {
//             gameState = 0;
//         }
//     }
// }

// void iMouseMove(int mx, int my) {}
// void iMouseDrag(int mx, int my) {}
// void iMouseWheel(int dir, int mx, int my) {}

// int main(int argc, char *argv[])
// {
//     glutInit(&argc, argv);
//     iSetTimer(1000, coverTimerFunc); // Cover screen timer
//     iSetTimer(20, ballChange);
//     iSetTimer(20, updateBlockPositions);
//     srand(time(0));
//     initBlocks1();
//     iSetTimer(2000, transitionToLevel2); // Transition to level 2 after 20 seconds
//     iInitialize(WIN_W, WIN_H, "Angry Birds Clone");
//     return 0;
// }

#include "iGraphics.h"
#include"iSound.h"
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define WIN_W 1550
#define WIN_H 1000
#define MAX_BLOCKS 1000
#define BIRD_WIDTH 60
#define BIRD_HEIGHT 60
#define BLOCK_WIDTH 30
#define BLOCK_HEIGHT 30
#define LEADERBOARD 3
#define MAX_NAME_LEN 100
// Game state
int gameState = -1;
int coverTimer = 0;
int gameLevel = 0;

// Bird and physics
double bird_x = 120, bird_y = 450;
double velocity = 90; // initial speed
double angle = 30;    // launch angle
double g = 9.8;
double t = 0;
bool launched = false;
bool ready = true;
int score = 0;
bool levelWon = false;
bool allGone = false;
int lives = 4;
bool birdDead = false;
bool gameOver = false;

// score and leaderboard
char playerName[MAX_NAME_LEN] = "";
int nameCharIndex = 0;
bool enteringName = false;

static double toRad(double deg) { return deg * M_PI / 180.0; }

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

void addBlock(float x, float y, float w, float h, int isVisible, int health, int isFalling, int isMoving, float dx, float dy, int isDeadly)
{
    if (blockCount >= MAX_BLOCKS)
        return;
    blocks[blockCount++] = (Block){x, y, w, h, 1, health, isFalling, isMoving, dx, dy, isDeadly};
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

void initBlocks1() // blocks for level 1
{
    blockCount = 0;
    addPerimeterGrid(600, 350, 7, 9, BLOCK_WIDTH, BLOCK_HEIGHT, 2, 1);
    float pyramidcenterX = 600 + 9 * BLOCK_WIDTH / 2;
    float pyramidbaseY = 350 + 2 * BLOCK_HEIGHT;
    addPyramid(pyramidcenterX, pyramidbaseY, 4, BLOCK_WIDTH, BLOCK_HEIGHT, 1);
}
void initBlocks2() // blocks for level 2
{
    blockCount = 0;
    addBlockGrid(700, 350, 5, 3, BLOCK_WIDTH, BLOCK_HEIGHT, 1);
    addPyramid(850, 350, 3, BLOCK_WIDTH, BLOCK_HEIGHT, 1);
    movingBlocks(600, 500, BLOCK_WIDTH, BLOCK_HEIGHT, 1, 4);
    fallingBlock(400, 800, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
    fallingBlock(600, 800, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
    fallingBlock(800, 600, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
    fallingBlock(1000, 800, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
    fallingBlock(500, 350, BLOCK_WIDTH, BLOCK_HEIGHT, 1, 4, 1);
    movingBlocks(1200, 600, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4);
    movingBlocks(300, 600, BLOCK_WIDTH, BLOCK_HEIGHT, 1, 4);
    movingBlocks(1000, 500, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4);
    movingBlocks(400, 500, BLOCK_WIDTH, BLOCK_HEIGHT, 1, 4);
}

typedef struct
{
    char name[100];
    int score;
} Leader;

Leader leaders[100];
int leaderCount = 0;

void loadLeaderboard()
{
    leaderCount = 0;
    FILE *fp = fopen("bin\\assets\\leaderboard.txt", "r");
    if (fp == NULL)
        return;
    while (fscanf(fp, "%s %d", leaders[leaderCount].name, &leaders[leaderCount].score) == 2)
    {
        leaderCount++;
        if (leaderCount >= 100)
            break; // limit to 100 leaders
    }
    fclose(fp);
}

// Save score to file
void saveScore()
{
    FILE *file = fopen("bin\\assets\\leaderboard.txt", "a");
    if (file)
    {
        fprintf(file, "%s %d\n", playerName, score);
        fclose(file);
    }
}

void showLeaderboard()
{
    FILE *file = fopen("bin\\assets\\leaderboard.txt", "r");
    if (!file)
    {
        iText(600, 200, "No leaderboard data available.", GLUT_BITMAP_HELVETICA_18);
        return;
    }

    Leader tempLeaders[100];
    int count = 0;

    while (fscanf(file, "%s %d", tempLeaders[count].name, &tempLeaders[count].score) == 2)
    {
        count++;
        if (count >= 100)
            break;
    }
    fclose(file);

    if (count == 0)
    {
        iText(600, 200, "No leaderboard data yet.", GLUT_BITMAP_HELVETICA_18);
        return;
    }
    // Sort leaders by score
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (tempLeaders[j].score > tempLeaders[i].score)
            {
                Leader temp = tempLeaders[i];
                tempLeaders[i] = tempLeaders[j];
                tempLeaders[j] = temp;
            }
        }
    }
    // Show top 5
    iSetColor(255, 255, 0);
    iText(600, 800, "LEADERBOARD", GLUT_BITMAP_HELVETICA_18);
    for (int i = 0; i < count && i < 5; i++)
    {
        char line[200];
        sprintf(line, "%d.%s - %d", i + 1, tempLeaders[i].name, tempLeaders[i].score);
        iText(600, 550 - i * 30, line, GLUT_BITMAP_HELVETICA_18);
    }
}

void iDraw()
{
    iClear();

    if (gameState == -1)
    {
        // COVER SCREEN
        // iSetColor(0, 0, 0);
        // iFilledRectangle(0, 0, WIN_W, WIN_H);
        iShowImage(0, 0, "assets/images/coverS.bmp");
        iSetColor(209, 24, 203);
        iText(WIN_W / 2 - 30, 60, "Loading...", GLUT_BITMAP_TIMES_ROMAN_24);
    }

    else if (gameState == 0)
    {
        // MAIN MENU
        iSetColor(97, 148, 227);
        iFilledRectangle(0, 0, WIN_W, WIN_H);
        // iShowImage(0, 50, "assets/images/menuBack.bmp");
        // iShowImage(0, 0, "assets/images/MenuCover.jpg");
        // iShowImage(510, 630, "assets/images/AngryBwritting.bmp");

        const char *title = "ANGRY BIRDS";
        int titleX = 615, titleY = 600;
        int spacing = 30;
        for (int i = 0; title[i]; i++)
        {
            int r = 200 + rand() % 55;
            int g = 50 + rand() % 200;
            int b = 50 + rand() % 200;

            iSetColor(r, g, b);
            char ch[2] = {title[i], '\0'};
            iText(titleX + i * spacing, titleY, ch, GLUT_BITMAP_TIMES_ROMAN_24);
        }

        int btnW = 200, btnH = 50, x = 660;
        int y1 = 500, y2 = 400, y3 = 100, y4 = 300, y5 = 200;
        // Start Game Button
        iSetColor(0, 100, 0);
        iFilledRectangle(x + 5, y1 - 5, btnW, btnH);
        iSetColor(0, 200, 0);
        iFilledRectangle(x, y1, btnW, btnH);
        iSetColor(255, 255, 255);
        iText(x + 50, y1 + 15, "START GAME", GLUT_BITMAP_HELVETICA_18);
        // Help Button
        iSetColor(0, 0, 100);
        iFilledRectangle(x + 5, y2 - 5, btnW, btnH);
        iSetColor(0, 0, 200);
        iFilledRectangle(x, y2, btnW, btnH);
        iSetColor(255, 255, 255);
        iText(x + 70, y2 + 15, "HELP", GLUT_BITMAP_HELVETICA_18);
        // Exit Button
        iSetColor(100, 0, 0);
        iFilledRectangle(x + 5, y3 - 5, btnW, btnH);
        iSetColor(200, 0, 0);
        iFilledRectangle(x, y3, btnW, btnH);
        iSetColor(255, 255, 255);
        iText(x + 75, y3 + 15, "EXIT", GLUT_BITMAP_HELVETICA_18);
        // Leaderboard Button
        iSetColor(100, 100, 0);
        iFilledRectangle(x + 5, y4 - 5, btnW, btnH);
        iSetColor(200, 200, 0);
        iFilledRectangle(x, y4, btnW, btnH);
        iSetColor(255, 255, 255);
        iText(x + 50, y4 + 15, "LEADERBOARD", GLUT_BITMAP_HELVETICA_18);
        // Credits
        iSetColor(100, 0, 100);
        iFilledRectangle(x + 5, y5 - 5, btnW, btnH);
        iSetColor(200, 0, 200);
        iFilledRectangle(x, y5, btnW, btnH);
        iSetColor(255, 255, 255);
        iText(x + 50, y5 + 15, "CREDITS", GLUT_BITMAP_HELVETICA_18);

        if (enteringName)
        {
            iSetColor(0, 0, 0);
            iFilledRectangle(0, 0, WIN_W, WIN_H);
            iSetColor(255, 255, 255);
            iText(WIN_W / 2 - 100, WIN_H / 2, "Enter your name: ", GLUT_BITMAP_HELVETICA_18);
            iText(WIN_W / 2 - 100, WIN_H / 2 - 30, playerName, GLUT_BITMAP_HELVETICA_18);
        }
    }
    // Gameplay
    else if (gameState == 1 && gameLevel == 1) // Level 1
    {
        iShowImage(0, 0, "assets/images/groundImage2.bmp");
        iShowImage(0, 350, "assets/images/skyImage.bmp");
        iShowImage(1150, 330, "assets/images/tree.png");
        iShowImage(0, 330, "assets/images/grassDecor.png");
        iShowImage(400, 330, "assets/images/grassDecor.png");
        iShowImage(800, 330, "assets/images/grassDecor.png");
        iShowImage(1200, 330, "assets/images/grassDecor.png");
        iShowImage((int)bird_x, (int)bird_y, "assets/images/extractedCartoonBirdAdd.bmp");
        iShowImage(100, 285, "assets/images/extractedCartoonSlingshotAdd.bmp.bmp");
        // iShowImage((int)bird_x, (int)bird_y, "assets/images/yellowBird.bmp");
        // iShowImage(100, 200, "assets/images/extractedCartoonBirdAdd.bmp");
        // iShowImage((int)bird_x + 50, (int)bird_y + 50, "assets/images/birdRed.bmp");
        // iShowImage(100, 285, "assets/images/extractedCartoonSlingshotAdd.bmp.bmp");

        for (int i = 0; i < blockCount; i++)
        {
            if (blocks[i].isVisible)
            {
                iShowImage((int)blocks[i].x, (int)blocks[i].y, "assets/images/blockImage.bmp");
            }
        }

        if (ready)
        {
            double rad = toRad(angle),
                   len = 150,
                   ex = bird_x + len * cos(rad),
                   ey = bird_y + len * sin(rad);

            iSetColor(0, 100, 255);
            iLine(bird_x, bird_y, ex, ey);
        }

        if (bird_x <= 120 && bird_y <= 450 && bird_x >= 90 && bird_y >= 400)
        {
            // Draw slingshot puller lines
            iLine(100, 425, bird_x, bird_y); // Left anchor to bird
            iLine(110, 425, bird_x, bird_y); // Right anchor to bird

            // Reset the bird position
            bird_x = 120;
            bird_y = 450;
            launched = false;
            ready = true;
            t = 0;
        }

        //   if(bird_x <= 120 && bird_y <= 450 && bird_x >= 90 && bird_y >= 400)
        //  {
        //      // Reset the bird position
        //      bird_x = 120;
        //      bird_y = 450;
        //      launched = false;
        //      ready = true;
        //      t = 0;
        //  }

        // HUD
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

        // HUD text
        char s1[32], s2[32];
        sprintf(s1, "Angle: %.0f°", angle);
        sprintf(s2, "Speed: %.0f", velocity);
        iSetColor(255, 255, 255);
        iText(boxX + 12, boxY + boxH - 10, s1, GLUT_BITMAP_HELVETICA_18);
        iText(boxX + 12, boxY + boxH - 30, s2, GLUT_BITMAP_HELVETICA_18);

        char scoreText[32];
        sprintf(scoreText, "Score: %d", score);
        iSetColor(255, 255, 255);
        iText(boxX + 12, boxY + boxH - 50, scoreText, GLUT_BITMAP_HELVETICA_18);

        char livesText[32];
        sprintf(livesText, "Lives: %d", lives);
        iSetColor(255, 255, 255);
        iText(boxX + 12, boxY + boxH - 80, livesText, GLUT_BITMAP_HELVETICA_18);
        char levelText[32];
        sprintf(levelText, "Level: %d", gameLevel);
        iText(boxX + 12, boxY + boxH - 110, levelText, GLUT_BITMAP_HELVETICA_18);

        if (levelWon)
        {
            iSetColor(255, 255, 0);
            iText(700, 500, "LEVEL COMPLETE!", GLUT_BITMAP_TIMES_ROMAN_24);
            iText(700, 450, "Press R to reset", GLUT_BITMAP_HELVETICA_18);
        }
    }
    else if (gameState == 1 && gameLevel == 2) // Level 2
    {
        iShowImage(0, 0, "assets/images/groundImage2.bmp");
        iShowImage(0, 350, "assets/images/skyImage.bmp");
        iShowImage(1150, 330, "assets/images/tree.png");
        iShowImage(0, 330, "assets/images/grassDecor.png");
        iShowImage(400, 330, "assets/images/grassDecor.png");
        iShowImage(800, 330, "assets/images/grassDecor.png");
        iShowImage(1200, 330, "assets/images/grassDecor.png");
        iShowImage((int)bird_x, (int)bird_y, "assets/images/extractedCartoonBirdAdd.bmp");
        iShowImage(100, 285, "assets/images/extractedCartoonSlingshotAdd.bmp.bmp");

        for (int i = 0; i < blockCount; i++)
        {
            if (blocks[i].isVisible)
            {
                iShowImage((int)blocks[i].x, (int)blocks[i].y, "assets/images/blockImage.bmp");
            }
        }

        if (ready)
        {
            double rad = toRad(angle),
                   len = 150,
                   ex = bird_x + len * cos(rad),
                   ey = bird_y + len * sin(rad);

            iSetColor(0, 100, 255);
            iLine(bird_x, bird_y, ex, ey);
        }

        // HUD
        int boxW = 220, boxH = 150;
        int boxX = 1300;
        int boxY = 720;

        int r = 200 + rand() % 55;
        int g = 50 + rand() % 200;
        int b = 50 + rand() % 200;
        iSetColor(r, g, b);
        iFilledRectangle(boxX, boxY, boxW, boxH);
        iSetColor(152, 79, 166);
        iFilledRectangle(boxX + 10, boxY + 10, boxW - 20, boxH - 20);

        // HUD text
        char s1[32], s2[32];
        sprintf(s1, "Angle: %.0f°", angle);
        sprintf(s2, "Speed: %.0f", velocity);
        iSetColor(255, 255, 255);
        iText(boxX + 12, boxY + boxH - 10, s1, GLUT_BITMAP_HELVETICA_18);
        iText(boxX + 12, boxY + boxH - 30, s2, GLUT_BITMAP_HELVETICA_18);

        char scoreText[32];
        sprintf(scoreText, "Score: %d", score);
        iSetColor(255, 255, 255);
        iText(boxX + 12, boxY + boxH - 50, scoreText, GLUT_BITMAP_HELVETICA_18);

        char livesText[32];
        sprintf(livesText, "Lives: %d", lives);
        iSetColor(255, 255, 255);
        iText(boxX + 12, boxY + boxH - 80, livesText, GLUT_BITMAP_HELVETICA_18);
        char levelText[32];
        sprintf(levelText, "Level: %d", gameLevel);
        iText(boxX + 12, boxY + boxH - 110, levelText, GLUT_BITMAP_HELVETICA_18);

        if (levelWon)
        {
            iSetColor(255, 255, 0);
            iText(700, 500, "LEVEL COMPLETE!", GLUT_BITMAP_TIMES_ROMAN_24);
            iText(700, 450, "Press R to reset", GLUT_BITMAP_HELVETICA_18);
        }
    }

    else if (gameState == 2) // HELP SCREEN
    {
        iSetColor(97, 153, 8);
        iFilledRectangle(0, 0, WIN_W, WIN_H);
        //        iShowImage(0, 0, "assets/images/helpBackGround.bmp");

        // Help text
        const char *help = "HELP";
        int helpX = 400, helpY = 650;
        int spacing = 30;
        for (int i = 0; help[i]; i++)
        {
            int r = 200 + rand() % 55;
            int g = 50 + rand() % 200;
            int b = 50 + rand() % 200;

            iSetColor(r, g, b);
            char ch[2] = {help[i], '\0'};
            iText(helpX + i * spacing, helpY, ch, GLUT_BITMAP_TIMES_ROMAN_24);
        }

        iSetColor(255, 255, 255);

        iText(400, 600, "Use arrow keys to set angle and speed.", GLUT_BITMAP_HELVETICA_18);
        iText(400, 550, "Left click to shoot. R to reset. Q to quit.", GLUT_BITMAP_HELVETICA_18);
        iText(400, 500, "B to return to menu.", GLUT_BITMAP_HELVETICA_18);
        iText(400, 450, "Some blocks are harder to break,", GLUT_BITMAP_HELVETICA_18);
        iText(400, 400, "and the falling ones are deadly. Avoid them!", GLUT_BITMAP_HELVETICA_18);
        iText(400, 350, "Complete all levels to win!", GLUT_BITMAP_HELVETICA_18);
        iText(400, 300, "Good luck!", GLUT_BITMAP_HELVETICA_18);
    }

    else if (gameState == LEADERBOARD) // LEADERBOARD SCREEN
    {
        iSetColor(97, 153, 8);
        iFilledRectangle(0, 0, WIN_W, WIN_H);
        iSetColor(255, 255, 255);
        iText(400, 650, "LEADERBOARD", GLUT_BITMAP_TIMES_ROMAN_24);
        showLeaderboard();
        iText(100, 100, "Press B to go back", GLUT_BITMAP_HELVETICA_18);
    }

    else if (gameState == 4) // GAME OVER with no lives left
    {
        iSetColor(73, 73, 156);
        iFilledRectangle(0, 0, WIN_W, WIN_H);
        iSetColor(255, 0, 0);
        iText(600, 500, "GAME OVER!", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(600, 450, "Press R to restart or Q to quit", GLUT_BITMAP_HELVETICA_18);
        iText(600, 400, "Lives: 0", GLUT_BITMAP_HELVETICA_18);
    }
    else if (gameState == 5) // Victory Screen
    {
        iSetColor(201, 103, 104);
        iFilledRectangle(0, 0, WIN_W, WIN_H);
        int r = 200 + rand() % 55;
        int g = 50 + rand() % 200;
        int b = 50 + rand() % 200;
        iSetColor(r, g, b);
        iText(600, 500, "CONGRATULATIONS!", GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(0, 0, 0);

        char msg[100];
        sprintf(msg, "You completed the game with a score of %d", score);
        iText(500, 450, msg, GLUT_BITMAP_HELVETICA_18);

        iText(600, 200, "Press B to return to Main menu", GLUT_BITMAP_HELVETICA_18);
        iText(600, 150, "Press Q to quit", GLUT_BITMAP_HELVETICA_18);
        iText(600, 100, "Press R to restart", GLUT_BITMAP_HELVETICA_18);
    }
    else if (gameState == 6) // Level Transition Screen
    {
        iSetColor(0, 0, 0);
        iFilledRectangle(0, 0, WIN_W, WIN_H);
        iSetColor(255, 255, 0);
        iText(WIN_W / 2 - 120, WIN_H / 2, "Get Ready! Moving to Level 2...", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(WIN_W / 2 - 100, WIN_H / 2 - 40, "Press R to Continue", GLUT_BITMAP_HELVETICA_18);
    }
    else if (gameState == 7) // Credits Screen
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
    }
}

void ballChange()
{
    if (gameState != 1 || !launched || gameOver)
        return;
    // Update physics
    t += 0.9;
    double rad = toRad(angle);
    bird_x = 120 + velocity * cos(rad) * t;
    bird_y = 450 + velocity * sin(rad) * t - 0.5 * g * t * t;

    // Land
    if (bird_y <= 345)
    {
        bird_y = 345;
        launched = false;
        ready = false;
        birdDead = true; // bird landed without hitting deadly block
    }

    // Check collision with blocks
    for (int i = 0; i < blockCount; i++)
    {
        if (blocks[i].isVisible)
        {
            Block b = blocks[i];

            if (bird_x + BIRD_WIDTH > b.x && bird_x - BIRD_WIDTH < b.x + b.width &&
                bird_y + BIRD_HEIGHT > b.y && bird_y - BIRD_HEIGHT < b.y + b.height)
            {
                if (b.isDeadly)
                {
                    birdDead = true;
                    launched = false;
                    ready = false;
                }
                else
                {
                    blocks[i].hitPoints--;
                    if (blocks[i].hitPoints <= 0)
                    {
                        blocks[i].isVisible = 0;
                        // iPlaySound("bin\\assets\\sound\\wood-crate-destroy.wav", false);
                        score += b.isDeadly ? -10 : (b.hitPoints == 2 ? 20 : 10);
                    }
                }
            }
        }
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

        if (gameLevel == 2)
        {
            gameState = 5;
            saveScore();
        }
    }
}

void updateBlockPositions()
{
    for (int i = 0; i < blockCount; i++)
    {
        if (!blocks[i].isVisible)
            continue;

        // Falling block (e.g., drops from sky)
        if (blocks[i].isFalling)
        {
            blocks[i].y += blocks[i].vy;

            // If it hits the ground (you can adjust the threshold)
            if (blocks[i].y <= 345)
            {
                blocks[i].y = 345;
                blocks[i].vy = 0;
                blocks[i].isFalling = 0;
            }

            // Check if it hits the bird
            if (
                bird_x + BIRD_WIDTH > blocks[i].x && bird_x < blocks[i].x + blocks[i].width &&
                bird_y + BIRD_HEIGHT > blocks[i].y && bird_y < blocks[i].y + blocks[i].height &&
                blocks[i].isDeadly)
            {
                // Bird "dies" — respawn next
                bird_x = 120;
                bird_y = 450;
                t = 0;
                launched = false;
                ready = true;
            }
        }

        // Moving block (horizontal or vertical)
        if (blocks[i].isMoving)
        {
            blocks[i].x += blocks[i].vx;

            // Bounce from bounds (optional: give movement range limit)
            if (blocks[i].x <= 100 || blocks[i].x + blocks[i].width >= WIN_W)
            {
                blocks[i].vx *= -1;
            }
            if (blocks[i].y <= 300 || blocks[i].y + blocks[i].height >= WIN_H)
            {
                blocks[i].vy *= -1; // Bounce vertically if needed
            }
        }
    }
}

void transitionToLevel2()
{
    if (gameState == 5)
    {
        gameLevel = 2;
        initBlocks2();
        bird_x = 120;
        bird_y = 450;
        t = 0;
        launched = false;
        ready = true;
        levelWon = false;
        gameState = 1;
    }
}

void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // Menu state
        if (gameState == 0)
        {
            if (mx >= 660 && mx <= 860 && my >= 500 && my <= 550)
            {
                enteringName = true; // Prompt name input
                nameCharIndex = 0;
                playerName[0] = '\0'; // Reset name
            }
            else if (mx >= 660 && mx <= 860 && my >= 400 && my <= 450)
            {
                gameState = LEADERBOARD; // LEADERBOARD
            }
            else if (mx >= 660 && mx <= 860 && my >= 200 && my <= 250)
            {
                gameState = 7; // CREDITS
            }
            else if (mx >= 660 && mx <= 860 && my >= 300 && my <= 350)
            {
                gameState = 2; // HELP
            }
            else if (mx >= 660 && mx <= 860 && my >= 100 && my <= 150)
            {
                exit(0); // EXIT
            }
        }

        // Launch bird in Game screen
        else if (gameState == 1 && ready && !launched)
        {
            launched = true;
            ready = false;
            t = 0;
        }

        else if (gameState == 1 && gameLevel == 2 && ready && !launched)
        {
            launched = true;
            ready = false;
            t = 0;
        }
        /*else if(launched){
            iPlaySound("bin\\assets\\sounds\\sound-effect-bird.wav", false);
        }*/
    }
}

void iKeyboard(unsigned char key)
{
    if (key == 'r')
    {
        if (levelWon)
        {
            if (gameLevel == 1)
            {
                gameState = 6;
            }
            else if (gameLevel == 2)
            {
                saveScore();
                gameState = 0;
                return;
            }
            else if (gameState == 5)
            {
                gameLevel = 2;
                initBlocks2();
                gameState = 1;
                lives = 5;
            }

            bird_x = 120;
            bird_y = 450;
            t = 0;
            launched = false;
            ready = true;
            levelWon = false;
        }
        else if (birdDead && lives > 0)
        {
            lives--;
            bird_x = 120;
            bird_y = 450;
            t = 0;
            launched = false;
            ready = true;
            levelWon = false;
            birdDead = false;
        }
        else if (lives == 0)
        {
            gameOver = true;
            gameState = 4;
        }

        bird_x = 120;
        bird_y = 450;
        t = 0;
        launched = false;
        ready = true;
        levelWon = false;

        if (gameLevel == 2 && levelWon && lives > 0)
        {
            saveScore();
        }
    }

    else if (key == 'q')
    {
        saveScore();
        exit(0);
    }
    else if (key == 'b') // back to menu
    {
        gameState = 0;
    }

    if (enteringName)
    {
        if (key == '\r')
        { // Enter key
            enteringName = false;
            gameState = 1;
            gameLevel = 1;
            score = 0;
            lives = 5;
            initBlocks1();
            launched = false;
            ready = true;
        }
        else if (key == '\b' && nameCharIndex > 0)
        { // Backspace
            playerName[--nameCharIndex] = '\0';
        }
        else if (nameCharIndex < 99 && (key >= 'a' && key <= 'z' || key >= 'A' && key <= 'Z' || key >= '0' && key <= '9'))
        {
            playerName[nameCharIndex++] = key;
            playerName[nameCharIndex] = '\0';
        }
        return;
    }
}

void iSpecialKeyboard(unsigned char key)
{
    if (gameState == 1 && ready)
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
    if (key == GLUT_KEY_END)
        exit(0);
}

// Timer function to handle cover screen delay
// This will switch from the cover screen to the main menu after a delay
void coverTimerFunc()
{
    if (gameState == -1)
    {
        coverTimer++;
        if (coverTimer >= 7)
        {
            gameState = 0;
            // iPlaySound("bin\\assets\\sounds\\gameBGM.wav", true); // Background music
        }
    }
}

void iMouseMove(int mx, int my) {}
void iMouseDrag(int mx, int my) {}
void iMouseWheel(int dir, int mx, int my) {}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    iSetTimer(1000, coverTimerFunc); // Cover screen timer
    iSetTimer(20, ballChange);
    iSetTimer(20, updateBlockPositions);
    srand(time(0));
    initBlocks1();
    iSetTimer(2000, transitionToLevel2); // Transition to level 2 after 20 seconds
    iInitialize(WIN_W, WIN_H, "Angry Birds Clone");
    loadLeaderboard(); // Load leaderboard data

    return 0;
}

// // #include "iGraphics.h"
// // #include <math.h>
// // #include <stdbool.h>
// // #include <time.h>
// // #include <stdio.h>
// // #include <stdlib.h>

// // #define WIN_W 1550
// // #define WIN_H 1000
// // #define MAX_BLOCKS 1000
// // #define BIRD_WIDTH 60
// // #define BIRD_HEIGHT 60
// // #define BLOCK_WIDTH 30
// // #define BLOCK_HEIGHT 30
// // #define LEADERBOARD 3
// // #define MAX_NAME_LEN 100
// // #define NUM_BIRDS 5

// // // Game state
// // int gameState = -1;
// // int coverTimer = 0;
// // int gameLevel = 0;

// // // Bird and physics
// // double bird_x = 120, bird_y = 450;
// // double velocity = 90; // initial speed
// // double angle = 30;    // launch angle
// // double g = 9.8;
// // double t = 0;
// // bool launched = false;
// // bool ready = true;
// // int score = 0;
// // bool levelWon = false;
// // bool allGone = false;
// // int lives = 4;
// // bool birdDead = false;
// // bool gameOver = false;

// // // score and leaderboard
// // char playerName[MAX_NAME_LEN] = "";
// // int nameCharIndex = 0;
// // bool enteringName = false;

// // static double toRad(double deg) { return deg * M_PI / 180.0; }

// // void initBirds()
// // {
// //     for (int i = 0; i < NUM_BIRDS; i++)
// //     {
// //         birds[i].x = 50 + i * 50; // waiting positions (adjust as needed)
// //         birds[i].y = 200;
// //         birds[i].active = true;
// //     }
// //     birds[0].x = 120;
// //     birds[0].y = 450;
// // }

// // void resetCurrentBird()
// // {
// //     if (currentBird < NUM_BIRDS)
// //     {
// //         birds[currentBird].x = 120;
// //         birds[currentBird].y = 450;
// //     }
// //     bird_x = 120;
// //     bird_y = 450;
// //     t = 0;
// //     launched = false;
// //     ready = true;
// // }

// // typedef struct
// // {
// //     double x, y;
// //     bool active;
// // } Bird;

// // Bird birds[NUM_BIRDS];
// // int currentBird = 0;
// // // ...existing code...

// // typedef struct
// // {
// //     float x, y;
// //     float width, height;
// //     int isVisible;
// //     int hitPoints;
// //     int isFalling;
// //     int isMoving;
// //     float vx, vy;
// //     int isDeadly;
// // } Block;

// // Block blocks[MAX_BLOCKS];
// // int blockCount = 0;

// // void addBlock(float x, float y, float w, float h, int isVisible, int health, int isFalling, int isMoving, float dx, float dy, int isDeadly)
// // {
// //     if (blockCount >= MAX_BLOCKS)
// //         return;
// //     blocks[blockCount++] = (Block){x, y, w, h, 1, health, isFalling, isMoving, dx, dy, isDeadly};
// // }

// // void addPyramid(float centerX, float baseY, int layers, float w, float h, int health)
// // {
// //     for (int i = 0; i < layers; i++)
// //     {
// //         int count = layers - i;
// //         float startX = centerX - (count * w) / 2;
// //         for (int j = 0; j < count; j++)
// //         {
// //             addBlock(startX + j * w, baseY + i * h, w, h, 1, health, 0, 0, 0, 0, 0);
// //         }
// //     }
// // }

// // void addBlockGrid(float startX, float startY, int rows, int cols, float w, float h, int health)
// // {
// //     for (int i = 0; i < rows; i++)
// //     {
// //         for (int j = 0; j < cols; j++)
// //         {
// //             addBlock(startX + j * w, startY + i * h, w, h, 1, health, 0, 0, 0, 0, 0);
// //         }
// //     }
// // }

// // void addPerimeterGrid(float startX, float startY, int rows, int cols, float w, float h, int thickness, int health)
// // {
// //     for (int r = 0; r < rows; r++)
// //     {
// //         for (int c = 0; c < cols; c++)
// //         {
// //             bool isEdge = (r < thickness || r >= rows - thickness || c < thickness || c >= cols - thickness);
// //             if (isEdge)
// //             {
// //                 float x = startX + c * w;
// //                 float y = startY + r * h;
// //                 addBlock(x, y, w, h, 1, health, 0, 0, 0, 0, 0);
// //             }
// //         }
// //     }
// // }

// // void fallingBlock(float x, float y, float w, float h, int health, float dy, int isDeadly)
// // {
// //     addBlock(x, y, w, h, 1, health, 1, 0, 0, dy, isDeadly);
// // }

// // void movingBlocks(float x, float y, float w, float h, int health, float dx)
// // {
// //     addBlock(x, y, w, h, 1, health, 0, 1, dx, 0, 0);
// // }

// // void initBlocks1() // blocks for level 1
// // {
// //     blockCount = 0;
// //     addPerimeterGrid(600, 350, 7, 9, BLOCK_WIDTH, BLOCK_HEIGHT, 2, 1);
// //     float pyramidcenterX = 600 + 9 * BLOCK_WIDTH / 2;
// //     float pyramidbaseY = 350 + 7 * BLOCK_HEIGHT;
// //     addPyramid(pyramidcenterX, pyramidbaseY, 4, BLOCK_WIDTH, BLOCK_HEIGHT, 1);
// // }
// // void initBlocks2() // blocks for level 2
// // {
// //     blockCount = 0;
// //     addBlockGrid(700, 350, 5, 3, BLOCK_WIDTH, BLOCK_HEIGHT, 1);
// //     addPyramid(850, 350, 3, BLOCK_WIDTH, BLOCK_HEIGHT, 1);
// //     movingBlocks(600, 500, BLOCK_WIDTH, BLOCK_HEIGHT, 1, 4);
// //     fallingBlock(400, 800, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
// //     fallingBlock(600, 800, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
// //     fallingBlock(800, 600, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
// //     fallingBlock(1000, 800, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
// //     fallingBlock(500, 350, BLOCK_WIDTH, BLOCK_HEIGHT, 1, 4, 1);
// //     movingBlocks(1200, 600, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4);
// //     movingBlocks(300, 600, BLOCK_WIDTH, BLOCK_HEIGHT, 1, 4);
// //     movingBlocks(1000, 500, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4);
// //     movingBlocks(400, 500, BLOCK_WIDTH, BLOCK_HEIGHT, 1, 4);
// // }

// // typedef struct
// // {
// //     char name[100];
// //     int score;
// // } Leader;

// // Leader leaders[100];
// // int leaderCount = 0;

// // void loadLeaderboard()
// // {
// //     leaderCount = 0;
// //     FILE *fp = fopen("bin\\assets\\leaderboard.txt", "r");
// //     if (fp == NULL)
// //         return;
// //     while (fscanf(fp, "%s %d", leaders[leaderCount].name, &leaders[leaderCount].score) == 2)
// //     {
// //         leaderCount++;
// //         if (leaderCount >= 100)
// //             break; // limit to 100 leaders
// //     }
// //     fclose(fp);
// // }

// // // Save score to file
// // void saveScore()
// // {
// //     FILE *file = fopen("bin\\assets\\leaderboard.txt", "a");
// //     if (file)
// //     {
// //         fprintf(file, "%s %d\n", playerName, score);
// //         fclose(file);
// //     }
// // }

// // void showLeaderboard()
// // {
// //     FILE *file = fopen("bin\\assets\\leaderboard.txt", "r");
// //     if (!file)
// //     {
// //         iText(600, 200, "No leaderboard data available.", GLUT_BITMAP_HELVETICA_18);
// //         return;
// //     }

// //     Leader tempLeaders[100];
// //     int count = 0;

// //     while (fscanf(file, "%s %d", tempLeaders[count].name, &tempLeaders[count].score) == 2)
// //     {
// //         count++;
// //         if (count >= 100)
// //             break;
// //     }
// //     fclose(file);

// //     if (count == 0)
// //     {
// //         iText(600, 200, "No leaderboard data yet.", GLUT_BITMAP_HELVETICA_18);
// //         return;
// //     }
// //     // Sort leaders by score
// //     for (int i = 0; i < count - 1; i++)
// //     {
// //         for (int j = i + 1; j < count; j++)
// //         {
// //             if (tempLeaders[j].score > tempLeaders[i].score)
// //             {
// //                 Leader temp = tempLeaders[i];
// //                 tempLeaders[i] = tempLeaders[j];
// //                 tempLeaders[j] = temp;
// //             }
// //         }
// //     }
// //     // Show top 5
// //     iSetColor(255, 255, 0);
// //     iText(600, 800, "LEADERBOARD", GLUT_BITMAP_HELVETICA_18);
// //     for (int i = 0; i < count && i < 5; i++)
// //     {
// //         char line[200];
// //         sprintf(line, "%d.%s - %d", i + 1, tempLeaders[i].name, tempLeaders[i].score);
// //         iText(600, 550 - i * 30, line, GLUT_BITMAP_HELVETICA_18);
// //     }
// // }

// // void iDraw()
// // {
// //     iClear();

// //     if (gameState == -1)
// //     {
// //         iShowImage(0, 0, "assets/images/coverS.bmp");
// //         int r = 200 + rand() % 55;
// //         int g = 50 + rand() % 200;
// //         int b = 50 + rand() % 200;
// //         iSetColor(r, g, b);
// //         iText(WIN_W / 2 - 30, 60, "Loading...", GLUT_BITMAP_TIMES_ROMAN_24);
// //     }
// //     else if (gameState == 0)
// //     {
// //         iShowImage(0, 0, "assets/images/MenuCover.jpg");
// //         iShowImage(510, 630, "assets/images/AngryBwritting.bmp");

// //         int btnW = 200, btnH = 50, x = 660;
// //         int y1 = 500, y2 = 400, y3 = 100, y4 = 300, y5 = 200;
// //         // Start Game Button
// //         iSetColor(0, 100, 0);
// //         iFilledRectangle(x + 5, y1 - 5, btnW, btnH);
// //         iSetColor(0, 200, 0);
// //         iFilledRectangle(x, y1, btnW, btnH);
// //         iSetColor(255, 255, 255);
// //         iText(x + 50, y1 + 15, "START GAME", GLUT_BITMAP_HELVETICA_18);
// //         // Leaderboard Button
// //         iSetColor(0, 0, 100);
// //         iFilledRectangle(x + 5, y2 - 5, btnW, btnH);
// //         iSetColor(0, 0, 200);
// //         iFilledRectangle(x, y2, btnW, btnH);
// //         iSetColor(255, 255, 255);
// //         iText(x + 50, y2 + 15, "LEADERBOARD", GLUT_BITMAP_HELVETICA_18);
// //         // Exit Button
// //         iSetColor(100, 0, 0);
// //         iFilledRectangle(x + 5, y3 - 5, btnW, btnH);
// //         iSetColor(200, 0, 0);
// //         iFilledRectangle(x, y3, btnW, btnH);
// //         iSetColor(255, 255, 255);
// //         iText(x + 75, y3 + 15, "EXIT", GLUT_BITMAP_HELVETICA_18);
// //         // Credit Button
// //         iSetColor(100, 100, 0);
// //         iFilledRectangle(x + 5, y4 - 5, btnW, btnH);
// //         iSetColor(200, 200, 0);
// //         iFilledRectangle(x, y4, btnW, btnH);
// //         iSetColor(255, 255, 255);
// //         iText(x + 50, y4 + 15, "CREDIT", GLUT_BITMAP_HELVETICA_18);
// //         // Help Button
// //         iSetColor(100, 0, 100);
// //         iFilledRectangle(x + 5, y5 - 5, btnW, btnH);
// //         iSetColor(200, 0, 200);
// //         iFilledRectangle(x, y5, btnW, btnH);
// //         iSetColor(255, 255, 255);
// //         iText(x + 50, y5 + 15, "HELP", GLUT_BITMAP_HELVETICA_18);

// //         if (enteringName)
// //         {
// //             iSetColor(0, 0, 0);
// //             iFilledRectangle(0, 0, WIN_W, WIN_H);
// //             iSetColor(255, 255, 255);
// //             iText(WIN_W / 2 - 100, WIN_H / 2, "Enter your name: ", GLUT_BITMAP_HELVETICA_18);
// //             iText(WIN_W / 2 - 100, WIN_H / 2 - 30, playerName, GLUT_BITMAP_HELVETICA_18);
// //         }
// //     }
// //     // Gameplay
// //     else if (gameState == 1 && gameLevel == 1)
// //     {
// //         iShowImage(0, 0, "assets/images/groundImage2.bmp");
// //         iShowImage(0, 350, "assets/images/skyImage.bmp");
// //         iShowImage(1150, 330, "assets/images/tree.png");
// //         iShowImage(0, 330, "assets/images/grassDecor.png");
// //         iShowImage(400, 330, "assets/images/grassDecor.png");
// //         iShowImage(800, 330, "assets/images/grassDecor.png");
// //         iShowImage(1200, 330, "assets/images/grassDecor.png");
// //         for (int i = 0; i < NUM_BIRDS; i++)
// //         {
// //             if (birds[i].active)
// //             {
// //                 iShowImage((int)birds[i].x, (int)birds[i].y, "assets/images/yellowBird.bmp");
// //             }
// //         }
// //         // iShowImage((int)bird_x, (int)bird_y, "assets/images/yellowBird.bmp");
// //         iShowImage(100, 285, "assets/images/extractedCartoonSlingshotAdd.bmp.bmp");

// //         for (int i = 0; i < blockCount; i++)
// //         {
// //             if (blocks[i].isVisible)
// //             {
// //                 iShowImage((int)blocks[i].x, (int)blocks[i].y, "assets/images/blockImage.bmp");
// //             }
// //         }

// //         if (ready)
// //         {
// //             double rad = toRad(angle);
// //             double vx = velocity * cos(rad);
// //             double vy = velocity * sin(rad);
// //             double px = bird_x, py = bird_y;
// //             double t_step = 0.1; // time step for smoothness
// //             double t_proj = 0;
// //             int max_steps = 200; // limit to avoid infinite loop

// //             for (int i = 0; i < max_steps; i++)
// //             {
// //                 double next_t = t_proj + t_step;
// //                 double next_px = bird_x + vx * next_t;
// //                 double next_py = bird_y + vy * next_t - 0.5 * g * next_t * next_t;

// //                 // Stop if below ground
// //                 if (next_py < 345)
// //                     break;

// //                 // Optionally, stop if hits a block
// //                 int hit = 0;
// //                 for (int j = 0; j < blockCount; j++)
// //                 {
// //                     if (blocks[j].isVisible)
// //                     {
// //                         if (next_px + BIRD_WIDTH > blocks[j].x && next_px < blocks[j].x + blocks[j].width &&
// //                             next_py + BIRD_HEIGHT > blocks[j].y && next_py < blocks[j].y + blocks[j].height)
// //                         {
// //                             hit = 1;
// //                             break;
// //                         }
// //                     }
// //                 }
// //                 if (hit)
// //                     break;

// //                 iSetColor(255,255,0);
// //                 iLine(px, py, next_px, next_py);

// //                 px = next_px;
// //                 py = next_py;
// //                 t_proj = next_t;
// //             }
// //         }

// //         // HUD
// //         int boxW = 220, boxH = 120;
// //         int boxX = 1300;
// //         int boxY = 720;

// //         int r = 200 + rand() % 55;
// //         int g = 50 + rand() % 200;
// //         int b = 50 + rand() % 200;
// //         iSetColor(r, g, b);
// //         iFilledRectangle(boxX, boxY, boxW, boxH);
// //         iSetColor(152, 79, 166);
// //         iFilledRectangle(boxX + 10, boxY + 10, boxW - 20, boxH - 20);

// //         // HUD text
// //         char s1[32], s2[32];
// //         sprintf(s1, "Angle: %.0f°", angle);
// //         sprintf(s2, "Speed: %.0f", velocity);
// //         iSetColor(255, 255, 255);
// //         iText(boxX + 12, boxY + boxH - 10, s1, GLUT_BITMAP_HELVETICA_18);
// //         iText(boxX + 12, boxY + boxH - 30, s2, GLUT_BITMAP_HELVETICA_18);

// //         char scoreText[32];
// //         sprintf(scoreText, "Score: %d", score);
// //         iSetColor(255, 255, 255);
// //         iText(boxX + 12, boxY + boxH - 50, scoreText, GLUT_BITMAP_HELVETICA_18);

// //         char livesText[32];
// //         sprintf(livesText, "Lives: %d", lives);
// //         iSetColor(255, 255, 255);
// //         iText(boxX + 12, boxY + boxH - 80, livesText, GLUT_BITMAP_HELVETICA_18);
// //         char levelText[32];
// //         sprintf(levelText, "Level: %d", gameLevel);
// //         iText(boxX + 12, boxY + boxH - 110, levelText, GLUT_BITMAP_HELVETICA_18);

// //         if (levelWon)
// //         {
// //             iSetColor(255, 255, 0);
// //             iText(700, 500, "LEVEL COMPLETE!", GLUT_BITMAP_TIMES_ROMAN_24);
// //             iText(700, 450, "Press R to reset", GLUT_BITMAP_HELVETICA_18);
// //         }
// //             }
// //     else if (gameState == 1 && gameLevel == 2)
// //     {
// //         iShowImage(0, 0, "assets/images/groundImage2.bmp");
// //         iShowImage(0, 350, "assets/images/skyImage.bmp");
// //         iShowImage(1150, 330, "assets/images/tree.png");
// //         iShowImage(0, 330, "assets/images/grassDecor.png");
// //         iShowImage(400, 330, "assets/images/grassDecor.png");
// //         iShowImage(800, 330, "assets/images/grassDecor.png");
// //         iShowImage(1200, 330, "assets/images/grassDecor.png");
// //         for (int i = 0; i < NUM_BIRDS; i++)
// //         {
// //             if (birds[i].active)
// //             {
// //                 iShowImage((int)birds[i].x, (int)birds[i].y, "assets/images/yellowBird.bmp");
// //             }
// //         }
// //         // iShowImage((int)bird_x, (int)bird_y, "assets/images/yellowBird.bmp");
// //         iShowImage(100, 285, "assets/images/extractedCartoonSlingshotAdd.bmp.bmp");

// //         for (int i = 0; i < blockCount; i++)
// //         {
// //             if (blocks[i].isVisible)
// //             {
// //                 iShowImage((int)blocks[i].x, (int)blocks[i].y, "assets/images/blockImage.bmp");
// //             }
// //         }

// //         if (ready)
// //         {
// //             double rad = toRad(angle),
// //                    len = 150,
// //                    ex = bird_x + len * cos(rad),
// //                    ey = bird_y + len * sin(rad);

// //             iSetColor(0, 100, 255);
// //             iLine(bird_x, bird_y, ex, ey);
// //         }

// //         // HUD
// //         int boxW = 220, boxH = 150;
// //         int boxX = 1300;
// //         int boxY = 720;

// //         int r = 200 + rand() % 55;
// //         int g = 50 + rand() % 200;
// //         int b = 50 + rand() % 200;
// //         iSetColor(r, g, b);
// //         iFilledRectangle(boxX, boxY, boxW, boxH);
// //         iSetColor(152, 79, 166);
// //         iFilledRectangle(boxX + 10, boxY + 10, boxW - 20, boxH - 20);

// //         // HUD text
// //         char s1[32], s2[32];
// //         sprintf(s1, "Angle: %.0f°", angle);
// //         sprintf(s2, "Speed: %.0f", velocity);
// //         iSetColor(255, 255, 255);
// //         iText(boxX + 12, boxY + boxH - 10, s1, GLUT_BITMAP_HELVETICA_18);
// //         iText(boxX + 12, boxY + boxH - 30, s2, GLUT_BITMAP_HELVETICA_18);

// //         char scoreText[32];
// //         sprintf(scoreText, "Score: %d", score);
// //         iSetColor(255, 255, 255);
// //         iText(boxX + 12, boxY + boxH - 50, scoreText, GLUT_BITMAP_HELVETICA_18);

// //         char livesText[32];
// //         sprintf(livesText, "Lives: %d", lives);
// //         iSetColor(255, 255, 255);
// //         iText(boxX + 12, boxY + boxH - 80, livesText, GLUT_BITMAP_HELVETICA_18);
// //         char levelText[32];
// //         sprintf(levelText, "Level: %d", gameLevel);
// //         iText(boxX + 12, boxY + boxH - 110, levelText, GLUT_BITMAP_HELVETICA_18);

// //         if (levelWon)
// //         {
// //             iSetColor(255, 255, 0);
// //             iText(700, 500, "LEVEL COMPLETE!", GLUT_BITMAP_TIMES_ROMAN_24);
// //             iText(700, 450, "Press R to reset", GLUT_BITMAP_HELVETICA_18);
// //         }
// //     }
// //     else if (gameState == 2)
// //     {
// //         iShowImage(0, 0, "assets/images/helpBackGround.bmp");
// //         iSetColor(255, 255, 255);
// //         iText(400, 650, "HELP", GLUT_BITMAP_HELVETICA_18);
// //         iText(400, 600, "Use arrow keys to set angle and speed.", GLUT_BITMAP_HELVETICA_18);
// //         iText(400, 550, "Left click to shoot. R to reset. Q to quit.", GLUT_BITMAP_HELVETICA_18);
// //         iText(400, 500, "B to return to menu.", GLUT_BITMAP_HELVETICA_18);
// //     }
// //     else if (gameState == LEADERBOARD)
// //     {
// //         iSetColor(0,0,0);
// //         iFilledRectangle(0, 0, WIN_W, WIN_H);
// //         iShowImage(40, 0, "assets/images/LeaderBcover.bmp");
// //         int r = 200 + rand() % 55;
// //         int g = 50 + rand() % 200;
// //         int b = 50 + rand() % 200;
// //         iSetColor(r, g, b);
// //         iText(330, 720, "LEADERBOARD", GLUT_BITMAP_TIMES_ROMAN_24);
// //         iSetColor(0, 0, 0);
// //         iFilledRectangle(300, 90, 900, 600);
// //         showLeaderboard();
// //         iSetColor(255, 255, 255);
// //         iText(60, 60, "Press B to go back", GLUT_BITMAP_HELVETICA_18);
// //     }
// //     else if (gameState == 4)
// //     {
// //         iSetColor(73, 73, 156);
// //         iFilledRectangle(0, 0, WIN_W, WIN_H);
// //         iSetColor(255, 0, 0);
// //         iText(600, 500, "GAME OVER!", GLUT_BITMAP_TIMES_ROMAN_24);
// //         iText(600, 450, "Press R to restart or Q to quit", GLUT_BITMAP_HELVETICA_18);
// //         iText(600, 400, "Lives: 0", GLUT_BITMAP_HELVETICA_18);
// //     }
// //     else if (gameState == 5)
// //     {
// //         iSetColor(201, 103, 104);
// //         iFilledRectangle(0, 0, WIN_W, WIN_H);
// //         int r = 200 + rand() % 55;
// //         int g = 50 + rand() % 200;
// //         int b = 50 + rand() % 200;
// //         iSetColor(r, g, b);
// //         iText(600, 500, "CONGRATULATIONS!", GLUT_BITMAP_TIMES_ROMAN_24);
// //         iSetColor(0, 0, 0);

// //         char msg[100];
// //         sprintf(msg, "You completed the game with a score of %d", score);
// //         iText(500, 450, msg, GLUT_BITMAP_HELVETICA_18);

// //         iText(600, 200, "Press B to return to Main menu", GLUT_BITMAP_HELVETICA_18);
// //         iText(600, 150, "Press Q to quit", GLUT_BITMAP_HELVETICA_18);
// //         iText(600, 100, "Press R to restart", GLUT_BITMAP_HELVETICA_18);
// //     }
// //     else if (gameState == 6)
// //     {
// //         iSetColor(0, 0, 0);
// //         iFilledRectangle(0, 0, WIN_W, WIN_H);
// //         iSetColor(255, 255, 0);
// //         iText(WIN_W / 2 - 120, WIN_H / 2, "Get Ready! Moving to Level 2...", GLUT_BITMAP_TIMES_ROMAN_24);
// //         iText(WIN_W / 2 - 100, WIN_H / 2 - 40, "Press R to Continue", GLUT_BITMAP_HELVETICA_18);
// //     }
// //     else if  (gameState == 7)
// //     {
// //         iSetColor(0,0,0);
// //         iFilledRectangle(0, 0, WIN_W, WIN_H);
// //         iShowImage(20, 0, "assets/images/CreditC.bmp");
// //         iSetColor(0, 0, 0);
// //         iFilledRectangle(50,70, 400, 350);
// //         iSetColor(0, 0, 0);
// //         iFilledRectangle(1100, 70, 400, 350);

// //         int r = 200 + rand() % 55;
// //         int g = 50 + rand() % 200;
// //         int b = 50 + rand() % 200;
// //         iSetColor(r, g, b);
// //         iText(100, 450, "CREDIT", GLUT_BITMAP_TIMES_ROMAN_24);
// //         iSetColor(255, 255, 255);
// //         iText(50, 50, "Press B to go back", GLUT_BITMAP_HELVETICA_18);
// //     }
// //     {

// //     }
// //         }

// // void ballChange()
// // {
// //     if (gameState != 1 || !launched || gameOver)
// //         return;
// //     // Update physics
// //     t += 0.9;
// //     double rad = toRad(angle);
// //     bird_x = 120 + velocity * cos(rad) * t;
// //     bird_y = 450 + velocity * sin(rad) * t - 0.5 * g * t * t;

// //     // Land
// //     // if (bird_y <= 345)
// //     // {
// //     //     bird_y = 345;
// //     //     launched = false;
// //     //     ready = false;
// //     //     birdDead = true; // bird landed without hitting deadly block
// //     // }

// //     if (bird_y <= 345 /* or collision detected */)
// //     {
// //         bird_y = 345;
// //         launched = false;
// //         ready = false;
// //         birds[currentBird].active = false; // This bird is used up

// //         currentBird++;
// //         if (currentBird < NUM_BIRDS)
// //         {
// //             resetCurrentBird();
// //         }
// //         else
// //         {
// //             // All birds used up
// //             gameOver = true;
// //             gameState = 4;
// //         }
// //     }

// //     // Check collision with blocks
// //     for (int i = 0; i < blockCount; i++)
// //     {
// //         if (blocks[i].isVisible)
// //         {
// //             Block b = blocks[i];

// //             if (bird_x + BIRD_WIDTH > b.x && bird_x - BIRD_WIDTH < b.x + b.width &&
// //                 bird_y + BIRD_HEIGHT > b.y && bird_y - BIRD_HEIGHT < b.y + b.height)
// //             {
// //                 if (b.isDeadly)
// //                 {
// //                     birdDead = true;
// //                     launched = false;
// //                     ready = false;
// //                 }
// //                 else
// //                 {
// //                     blocks[i].hitPoints--;
// //                     if (blocks[i].hitPoints <= 0)
// //                     {
// //                         blocks[i].isVisible = 0;
// //                         score += b.isDeadly ? -10 : (b.hitPoints == 2 ? 20 : 10);
// //                     }
// //                 }
// //             }
// //         }
// //     }
// //     allGone = true;
// //     for (int i = 0; i < blockCount; i++)
// //     {
// //         if (blocks[i].isVisible)
// //         {
// //             allGone = false;
// //             break;
// //         }
// //     }
// //     if (allGone && !levelWon)
// //     {
// //         levelWon = true;
// //         launched = false;
// //         ready = false;

// //         if (gameLevel == 2)
// //         {
// //             gameState = 5;
// //             saveScore();
// //         }
// //     }
// // }

// // void updateBlockPositions()
// // {
// //     for (int i = 0; i < blockCount; i++)
// //     {
// //         if (!blocks[i].isVisible)
// //             continue;

// //         // Falling block (e.g., drops from sky)
// //         if (blocks[i].isFalling)
// //         {
// //             blocks[i].y += blocks[i].vy;

// //             // If it hits the ground (you can adjust the threshold)
// //             if (blocks[i].y <= 345)
// //             {
// //                 blocks[i].y = 345;
// //                 blocks[i].vy = 0;
// //                 blocks[i].isFalling = 0;
// //             }

// //             // Check if it hits the bird
// //             if (
// //                 bird_x + BIRD_WIDTH > blocks[i].x && bird_x < blocks[i].x + blocks[i].width &&
// //                 bird_y + BIRD_HEIGHT > blocks[i].y && bird_y < blocks[i].y + blocks[i].height &&
// //                 blocks[i].isDeadly)
// //             {
// //                 // Bird "dies" — respawn next
// //                 bird_x = 120;
// //                 bird_y = 450;
// //                 t = 0;
// //                 launched = false;
// //                 ready = true;
// //             }
// //         }

// //         // Moving block (horizontal or vertical)
// //         if (blocks[i].isMoving)
// //         {
// //             blocks[i].x += blocks[i].vx;

// //             // Bounce from bounds (optional: give movement range limit)
// //             if (blocks[i].x <= 100 || blocks[i].x + blocks[i].width >= WIN_W)
// //             {
// //                 blocks[i].vx *= -1;
// //             }
// //             if (blocks[i].y <= 300 || blocks[i].y + blocks[i].height >= WIN_H)
// //             {
// //                 blocks[i].vy *= -1; // Bounce vertically if needed
// //             }
// //         }
// //     }
// // }

// // void transitionToLevel2()
// // {
// //     if (gameState == 5)
// //     {
// //         gameLevel = 2;
// //         initBlocks2();
// //         bird_x = 120;
// //         bird_y = 450;
// //         t = 0;
// //         launched = false;
// //         ready = true;
// //         levelWon = false;
// //         gameState = 1;
// //     }
// // }

// // void iMouse(int button, int state, int mx, int my)
// // {
// //     if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
// //     {
// //         // Menu state
// //         if (gameState == 0)
// //         {
// //             if (mx >= 660 && mx <= 860 && my >= 500 && my <= 550)
// //             {
// //                 enteringName = true; // Prompt name input
// //                 nameCharIndex = 0;
// //                 playerName[0] = '\0'; // Reset name
// //             }
// //             else if (mx >= 660 && mx <= 860 && my >= 400 && my <= 450)
// //             {
// //                 gameState = LEADERBOARD; // LEADERBOARD
// //             }
// //             else if (mx >= 660 && mx <= 860 && my >= 200 && my <= 250)
// //             {
// //                 gameState = 2; // HELP
// //             }
// //             else if (mx >= 660 && mx <= 860 && my >= 100 && my <= 150)
// //             {
// //                 exit(0); // EXIT
// //             }
// //             else if (mx >= 660 && mx <= 860 && my >= 300 && my <= 350)
// //             {
// //                 gameState = 7; // CREDIT
// //             }
// //         }

// //         else if (gameState == 1 && ready && !launched && birds[currentBird].active)
// //         {
// //             launched = true;
// //             ready = false;
// //             t = 0;
// //         }
// //         // Launch bird in Game screen
// //         else if (gameState == 1 && ready && !launched)
// //         {
// //             launched = true;
// //             ready = false;
// //             t = 0;
// //         }

// //         else if (gameState == 1 && gameLevel == 2 && ready && !launched)
// //         {
// //             launched = true;
// //             ready = false;
// //             t = 0;
// //         }
// //     }
// // }

// // void iKeyboard(unsigned char key)
// // {
// //     if (key == 'r')
// //     {
// //         currentBird = 0;
// //         initBirds();
// //         resetCurrentBird();

// //         if (levelWon)
// //         {
// //             if (gameLevel == 1)
// //             {
// //                 gameState = 6;
// //             }
// //             else if (gameLevel == 2)
// //             {
// //                 saveScore();
// //                 gameState = 0;
// //                 return;
// //             }
// //             bird_x = 120;
// //             bird_y = 450;
// //             t = 0;
// //             launched = false;
// //             ready = true;
// //             levelWon = false;
// //         }
// //         else if (birdDead && lives > 0)
// //         {
// //             lives--;
// //             bird_x = 120;
// //             bird_y = 450;
// //             t = 0;
// //             launched = false;
// //             ready = true;
// //             levelWon = false;
// //             birdDead = false;
// //         }
// //         else if (lives == 0)
// //         {
// //             gameOver = true;
// //             gameState = 4;
// //         }

// //         bird_x = 120;
// //         bird_y = 450;
// //         t = 0;
// //         launched = false;
// //         ready = true;
// //         levelWon = false;

// //         if (gameLevel == 2 && levelWon && lives > 0)
// //         {
// //             saveScore();
// //         }
// //     }

// //     else if (key == 'q')
// //     {
// //         saveScore();
// //         exit(0);
// //     }
// //     else if (key == 'b') // back to menu
// //     {
// //         gameState = 0;
// //     }

// //     if (enteringName)
// //     {
// //         if (key == '\r')
// //         { // Enter key
// //             enteringName = false;
// //             gameState = 1;
// //             gameLevel = 1;
// //             score = 0;
// //             lives = 5;
// //             initBlocks1();
// //             launched = false;
// //             ready = true;
// //         }
// //         else if (key == '\b' && nameCharIndex > 0)
// //         { // Backspace
// //             playerName[--nameCharIndex] = '\0';
// //         }
// //         else if (nameCharIndex < 99 && ((key >= 'a' && key <= 'z' )|| (key >= 'A' && key <= 'Z') ||( key >= '0' && key <= '9')))
// //         {
// //             playerName[nameCharIndex++] = key;
// //             playerName[nameCharIndex] = '\0';
// //         }
// //         return;
// //     }
// // }

// // void iSpecialKeyboard(unsigned char key)
// // {
// //     if (gameState == 1 && ready)
// //     {
// //         if (key == GLUT_KEY_UP && angle < 90)
// //             angle += 1;
// //         else if (key == GLUT_KEY_DOWN && angle > 0)
// //             angle -= 1;
// //         else if (key == GLUT_KEY_RIGHT && velocity < 200)
// //             velocity += 1;
// //         else if (key == GLUT_KEY_LEFT && velocity > 10)
// //             velocity -= 1;
// //     }
// //     if (key == GLUT_KEY_END)
// //         exit(0);
// // }

// // // Timer function to handle cover screen delay
// // void coverTimerFunc()
// // {
// //     if (gameState == -1)
// //     {
// //         coverTimer++;
// //         if (coverTimer >= 7)
// //         {
// //             gameState = 0;
// //         }
// //     }
// // }

// // void iMouseMove(int mx, int my) {}
// // void iMouseDrag(int mx, int my) {}
// // void iMouseWheel(int dir, int mx, int my) {}

// // int main(int argc, char *argv[])
// // {
// //     glutInit(&argc, argv);
// //     iSetTimer(1000, coverTimerFunc); // Cover screen timer
// //     iSetTimer(20, ballChange);
// //     iSetTimer(20, updateBlockPositions);
// //     srand(time(0));
// //     initBlocks1();
// //     initBirds();
// //     iSetTimer(2000, transitionToLevel2); // Transition to level 2 after 20 seconds
// //     iInitialize(WIN_W, WIN_H, "Angry Birds");
// //     return 0;
// // }

// // #include "iGraphics.h"
// // #include "iSound.h"
// // #include <math.h>
// // #include <stdbool.h>
// // #include <time.h>
// // #include <stdio.h>
// // #include <stdlib.h>

// // #define WIN_W 1550
// // #define WIN_H 1000
// // #define MAX_BLOCKS 1000
// // #define BIRD_WIDTH 60
// // #define BIRD_HEIGHT 60
// // #define BLOCK_WIDTH 30
// // #define BLOCK_HEIGHT 30
// // #define LEADERBOARD 3
// // #define MAX_NAME_LEN 100
// // #define NUM_BIRDS 5

// // // Game state
// // int gameState = -1;
// // int coverTimer = 0;
// // int gameLevel = 0;

// // // Bird and physics
// // double velocity = 90; // initial speed
// // double angle = 30;    // launch angle
// // double g = 9.8;
// // double t = 0;
// // bool launched = false;
// // bool ready = true;
// // int score = 0;
// // bool levelWon = false;
// // bool allGone = false;
// // int lives = 4;
// // bool birdDead = false;
// // bool gameOver = false;

// // // Bird struct and array
// // typedef struct
// // {
// //     double x, y;
// //     bool active;
// //     int birdType; // 0-4 for bird1.bmp ... bird5.bmp
// // } Bird;

// // Bird birds[NUM_BIRDS];
// // int currentBird = 0;

// // // Bird image filenames
// // const char *birdImages[NUM_BIRDS] = {
// //     "assets/images/redBird.bmp",
// //     "assets/images/yellowBird.bmp",
// //     "assets/images/blueBird.png",
// //     "assets/images/blackBird.bmp",
// //     "assets/images/blueBird.png"};

// // // Bird selection state
// // int birdSelectionIndex = 0;                              // which slot is being selected
// // int selectedBirdTypes[NUM_BIRDS] = {-1, -1, -1, -1, -1}; // stores chosen bird type for each slot
// // bool selectingBirds = false;

// // // score and leaderboard
// // char playerName[MAX_NAME_LEN] = "";
// // int nameCharIndex = 0;
// // bool enteringName = false;

// // static double toRad(double deg) { return deg * M_PI / 180.0; }

// // // Block struct
// // typedef struct
// // {
// //     float x, y;
// //     float width, height;
// //     int isVisible;
// //     int hitPoints;
// //     int isFalling;
// //     int isMoving;
// //     float vx, vy;
// //     int isDeadly;
// // } Block;

// // Block blocks[MAX_BLOCKS];
// // int blockCount = 0;

// // // Bird position helpers
// // void initBirds()
// // {
// //     for (int i = 0; i < NUM_BIRDS; i++)
// //     {
// //         birds[i].x = 50 + i * 50; // waiting positions
// //         birds[i].y = 200;
// //         birds[i].active = true;
// //         birds[i].birdType = selectedBirdTypes[i] >= 0 ? selectedBirdTypes[i] : i; // fallback to i if not selected
// //     }
// //     birds[0].x = 120;
// //     birds[0].y = 450;
// // }

// // void resetCurrentBird()
// // {
// //     if (currentBird < NUM_BIRDS)
// //     {
// //         birds[currentBird].x = 120;
// //         birds[currentBird].y = 450;
// //     }
// //     t = 0;
// //     launched = false;
// //     ready = true;
// // }

// // // Block helpers
// // void addBlock(float x, float y, float w, float h, int isVisible, int health, int isFalling, int isMoving, float dx, float dy, int isDeadly)
// // {
// //     if (blockCount >= MAX_BLOCKS)
// //         return;
// //     blocks[blockCount++] = (Block){x, y, w, h, 1, health, isFalling, isMoving, dx, dy, isDeadly};
// // }

// // void addPyramid(float centerX, float baseY, int layers, float w, float h, int health)
// // {
// //     for (int i = 0; i < layers; i++)
// //     {
// //         int count = layers - i;
// //         float startX = centerX - (count * w) / 2;
// //         for (int j = 0; j < count; j++)
// //         {
// //             addBlock(startX + j * w, baseY + i * h, w, h, 1, health, 0, 0, 0, 0, 0);
// //         }
// //     }
// // }

// // void addBlockGrid(float startX, float startY, int rows, int cols, float w, float h, int health)
// // {
// //     for (int i = 0; i < rows; i++)
// //     {
// //         for (int j = 0; j < cols; j++)
// //         {
// //             addBlock(startX + j * w, startY + i * h, w, h, 1, health, 0, 0, 0, 0, 0);
// //         }
// //     }
// // }

// // void addPerimeterGrid(float startX, float startY, int rows, int cols, float w, float h, int thickness, int health)
// // {
// //     for (int r = 0; r < rows; r++)
// //     {
// //         for (int c = 0; c < cols; c++)
// //         {
// //             bool isEdge = (r < thickness || r >= rows - thickness || c < thickness || c >= cols - thickness);
// //             if (isEdge)
// //             {
// //                 float x = startX + c * w;
// //                 float y = startY + r * h;
// //                 addBlock(x, y, w, h, 1, health, 0, 0, 0, 0, 0);
// //             }
// //         }
// //     }
// // }

// // void fallingBlock(float x, float y, float w, float h, int health, float dy, int isDeadly)
// // {
// //     addBlock(x, y, w, h, 1, health, 1, 0, 0, dy, isDeadly);
// // }

// // void movingBlocks(float x, float y, float w, float h, int health, float dx)
// // {
// //     addBlock(x, y, w, h, 1, health, 0, 1, dx, 0, 0);
// // }

// // void initBlocks1() // blocks for level 1
// // {
// //     blockCount = 0;
// //     addPerimeterGrid(600, 350, 7, 9, BLOCK_WIDTH, BLOCK_HEIGHT, 2, 1);
// //     float pyramidcenterX = 600 + 9 * BLOCK_WIDTH / 2;
// //     float pyramidbaseY = 350 + 7 * BLOCK_HEIGHT;
// //     addPyramid(pyramidcenterX, pyramidbaseY, 4, BLOCK_WIDTH, BLOCK_HEIGHT, 1);
// // }
// // void initBlocks2() // blocks for level 2
// // {
// //     blockCount = 0;
// //     addBlockGrid(700, 350, 5, 3, BLOCK_WIDTH, BLOCK_HEIGHT, 1);
// //     addPyramid(850, 350, 3, BLOCK_WIDTH, BLOCK_HEIGHT, 1);
// //     movingBlocks(600, 500, BLOCK_WIDTH, BLOCK_HEIGHT, 1, 4);
// //     fallingBlock(400, 800, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
// //     fallingBlock(600, 800, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
// //     fallingBlock(800, 600, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
// //     fallingBlock(1000, 800, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
// //     fallingBlock(500, 350, BLOCK_WIDTH, BLOCK_HEIGHT, 1, 4, 1);
// //     movingBlocks(1200, 600, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4);
// //     movingBlocks(300, 600, BLOCK_WIDTH, BLOCK_HEIGHT, 1, 4);
// //     movingBlocks(1000, 500, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4);
// //     movingBlocks(400, 500, BLOCK_WIDTH, BLOCK_HEIGHT, 1, 4);
// // }

// // typedef struct
// // {
// //     char name[100];
// //     int score;
// // } Leader;

// // Leader leaders[100];
// // int leaderCount = 0;

// // void loadLeaderboard()
// // {
// //     leaderCount = 0;
// //     FILE *fp = fopen("bin\\assets\\leaderboard.txt", "r");
// //     if (fp == NULL)
// //         return;
// //     while (fscanf(fp, "%s %d", leaders[leaderCount].name, &leaders[leaderCount].score) == 2)
// //     {
// //         leaderCount++;
// //         if (leaderCount >= 100)
// //             break; // limit to 100 leaders
// //     }
// //     fclose(fp);
// // }

// // // Save score to file
// // void saveScore()
// // {
// //     FILE *file = fopen("bin\\assets\\leaderboard.txt", "a");
// //     if (file)
// //     {
// //         fprintf(file, "%s %d\n", playerName, score);
// //         fclose(file);
// //     }
// // }

// // void showLeaderboard()
// // {
// //     FILE *file = fopen("bin\\assets\\leaderboard.txt", "r");
// //     if (!file)
// //     {
// //         iText(600, 200, "No leaderboard data available.", GLUT_BITMAP_HELVETICA_18);
// //         return;
// //     }

// //     Leader tempLeaders[100];
// //     int count = 0;

// //     while (fscanf(file, "%s %d", tempLeaders[count].name, &tempLeaders[count].score) == 2)
// //     {
// //         count++;
// //         if (count >= 100)
// //             break;
// //     }
// //     fclose(file);

// //     if (count == 0)
// //     {
// //         iText(600, 200, "No leaderboard data yet.", GLUT_BITMAP_HELVETICA_18);
// //         return;
// //     }
// //     // Sort leaders by score
// //     for (int i = 0; i < count - 1; i++)
// //     {
// //         for (int j = i + 1; j < count; j++)
// //         {
// //             if (tempLeaders[j].score > tempLeaders[i].score)
// //             {
// //                 Leader temp = tempLeaders[i];
// //                 tempLeaders[i] = tempLeaders[j];
// //                 tempLeaders[j] = temp;
// //             }
// //         }
// //     }
// //     // Show top 5
// //     iSetColor(255, 255, 0);
// //     iText(600, 800, "LEADERBOARD", GLUT_BITMAP_HELVETICA_18);
// //     for (int i = 0; i < count && i < 5; i++)
// //     {
// //         char line[200];
// //         sprintf(line, "%d.%s - %d", i + 1, tempLeaders[i].name, tempLeaders[i].score);
// //         iText(600, 550 - i * 30, line, GLUT_BITMAP_HELVETICA_18);
// //     }
// // }

// // void iDraw()
// // {
// //     iClear();

// //     if (gameState == -1)
// //     {
// //         iShowImage(0, 0, "assets/images/coverS.bmp");
// //         int r = 200 + rand() % 55;
// //         int g = 50 + rand() % 200;
// //         int b = 50 + rand() % 200;
// //         iSetColor(r, g, b);
// //         iText(WIN_W / 2 - 30, 60, "Loading...", GLUT_BITMAP_TIMES_ROMAN_24);
// //     }
// //     else if (gameState == 0)
// //     {
// //         iShowImage(0, 0, "assets/images/MenuCover.jpg");
// //         iShowImage(510, 630, "assets/images/AngryBwritting.bmp");

// //         int btnW = 200, btnH = 50, x = 660;
// //         int y1 = 500, y2 = 400, y3 = 100, y4 = 300, y5 = 200;
// //         // Start Game Button
// //         iSetColor(0, 100, 0);
// //         iFilledRectangle(x + 5, y1 - 5, btnW, btnH);
// //         iSetColor(0, 200, 0);
// //         iFilledRectangle(x, y1, btnW, btnH);
// //         iSetColor(255, 255, 255);
// //         iText(x + 50, y1 + 15, "START GAME", GLUT_BITMAP_HELVETICA_18);
// //         // Leaderboard Button
// //         iSetColor(0, 0, 100);
// //         iFilledRectangle(x + 5, y2 - 5, btnW, btnH);
// //         iSetColor(0, 0, 200);
// //         iFilledRectangle(x, y2, btnW, btnH);
// //         iSetColor(255, 255, 255);
// //         iText(x + 50, y2 + 15, "LEADERBOARD", GLUT_BITMAP_HELVETICA_18);
// //         // Exit Button
// //         iSetColor(100, 0, 0);
// //         iFilledRectangle(x + 5, y3 - 5, btnW, btnH);
// //         iSetColor(200, 0, 0);
// //         iFilledRectangle(x, y3, btnW, btnH);
// //         iSetColor(255, 255, 255);
// //         iText(x + 75, y3 + 15, "EXIT", GLUT_BITMAP_HELVETICA_18);
// //         // Credit Button
// //         iSetColor(100, 100, 0);
// //         iFilledRectangle(x + 5, y4 - 5, btnW, btnH);
// //         iSetColor(200, 200, 0);
// //         iFilledRectangle(x, y4, btnW, btnH);
// //         iSetColor(255, 255, 255);
// //         iText(x + 50, y4 + 15, "CREDIT", GLUT_BITMAP_HELVETICA_18);
// //         // Help Button
// //         iSetColor(100, 0, 100);
// //         iFilledRectangle(x + 5, y5 - 5, btnW, btnH);
// //         iSetColor(200, 0, 200);
// //         iFilledRectangle(x, y5, btnW, btnH);
// //         iSetColor(255, 255, 255);
// //         iText(x + 50, y5 + 15, "HELP", GLUT_BITMAP_HELVETICA_18);

// //         if (enteringName)
// //         {
// //             iSetColor(0, 0, 0);
// //             iFilledRectangle(0, 0, WIN_W, WIN_H);
// //             iSetColor(255, 255, 255);
// //             iText(WIN_W / 2 - 100, WIN_H / 2, "Enter your name: ", GLUT_BITMAP_HELVETICA_18);
// //             iText(WIN_W / 2 - 100, WIN_H / 2 - 30, playerName, GLUT_BITMAP_HELVETICA_18);
// //         }
// //     }
// //     // Bird selection screen
// //     else if (selectingBirds)
// //     {
// //         iSetColor(0, 0, 0);
// //         iFilledRectangle(0, 0, WIN_W, WIN_H);
// //         iSetColor(255, 255, 255);
// //         char msg[128];
// //         sprintf(msg, "Select bird for slot %d", birdSelectionIndex + 1);
// //         iText(WIN_W / 2 - 100, WIN_H - 100, msg, GLUT_BITMAP_HELVETICA_18);

// //         // Show all bird images to choose from
// //         for (int i = 0; i < NUM_BIRDS; i++)
// //         {
// //             int bx = 300 + i * 200;
// //             int by = WIN_H / 2;
// //             iShowImage(bx, by, birdImages[i]);
// //             // Highlight if already chosen for another slot
// //             bool alreadyChosen = false;
// //             for (int j = 0; j < birdSelectionIndex; j++)
// //                 if (selectedBirdTypes[j] == i)
// //                     alreadyChosen = true;
// //             if (alreadyChosen)
// //             {
// //                 iSetColor(255, 0, 0);
// //                 iRectangle(bx, by, BIRD_WIDTH, BIRD_HEIGHT);
// //             }
// //         }
// //         // Show chosen birds so far
// //         iSetColor(255, 255, 0);
// //         iText(200, 200, "Your bird order:", GLUT_BITMAP_HELVETICA_18);
// //         for (int i = 0; i < birdSelectionIndex; i++)
// //         {
// //             iShowImage(400 + i * 70, 150, birdImages[selectedBirdTypes[i]]);
// //         }
// //     }
// //     // Gameplay
// //     else if (gameState == 1 && (gameLevel == 1 || gameLevel == 2))
// //     {
// //         iShowImage(0, 0, "assets/images/groundImage2.bmp");
// //         iShowImage(0, 350, "assets/images/skyImage.bmp");
// //         iShowImage(1150, 330, "assets/images/tree.png");
// //         iShowImage(0, 330, "assets/images/grassDecor.png");
// //         iShowImage(400, 330, "assets/images/grassDecor.png");
// //         iShowImage(800, 330, "assets/images/grassDecor.png");
// //         iShowImage(1200, 330, "assets/images/grassDecor.png");

// //         // Draw all birds (waiting and slingshot)
// //         for (int i = 0; i < NUM_BIRDS; i++)
// //         {
// //             if (birds[i].active)
// //             {
// //                 iShowImage((int)birds[i].x, (int)birds[i].y, birdImages[birds[i].birdType]);
// //             }
// //         }
// //         iShowImage(100, 285, "assets/images/extractedCartoonSlingshotAdd.bmp.bmp");

// //         for (int i = 0; i < blockCount; i++)
// //         {
// //             if (blocks[i].isVisible)
// //             {
// //                 iShowImage((int)blocks[i].x, (int)blocks[i].y, "assets/images/blockImage.bmp");
// //             }
// //         }

// //         // Trajectory preview for current bird
// //         if (ready && birds[currentBird].active)
// //         {
// //             double rad = toRad(angle);
// //             double vx = velocity * cos(rad);
// //             double vy = velocity * sin(rad);
// //             double px = 120, py = 450;
// //             double t_step = 0.1;
// //             double t_proj = 0;
// //             int max_steps = 200;

// //             for (int i = 0; i < max_steps; i++)
// //             {
// //                 double next_t = t_proj + t_step;
// //                 double next_px = 120 + vx * next_t;
// //                 double next_py = 450 + vy * next_t - 0.5 * g * next_t * next_t;

// //                 if (next_py < 345)
// //                     break;

// //                 int hit = 0;
// //                 for (int j = 0; j < blockCount; j++)
// //                 {
// //                     if (blocks[j].isVisible)
// //                     {
// //                         if (next_px + BIRD_WIDTH > blocks[j].x && next_px < blocks[j].x + blocks[j].width &&
// //                             next_py + BIRD_HEIGHT > blocks[j].y && next_py < blocks[j].y + blocks[j].height)
// //                         {
// //                             hit = 1;
// //                             break;
// //                         }
// //                     }
// //                 }
// //                 if (hit)
// //                     break;

// //                 iSetColor(255, 255, 0);
// //                 iLine(px, py, next_px, next_py);

// //                 px = next_px;
// //                 py = next_py;
// //                 t_proj = next_t;
// //             }
// //         }

// //         // HUD
// //         int boxW = 220, boxH = 120;
// //         int boxX = 1300;
// //         int boxY = 720;

// //         int r = 200 + rand() % 55;
// //         int g = 50 + rand() % 200;
// //         int b = 50 + rand() % 200;
// //         iSetColor(r, g, b);
// //         iFilledRectangle(boxX, boxY, boxW, boxH);
// //         iSetColor(152, 79, 166);
// //         iFilledRectangle(boxX + 10, boxY + 10, boxW - 20, boxH - 20);

// //         // HUD text
// //         char s1[32], s2[32];
// //         sprintf(s1, "Angle: %.0f°", angle);
// //         sprintf(s2, "Speed: %.0f", velocity);
// //         iSetColor(255, 255, 255);
// //         iText(boxX + 12, boxY + boxH - 10, s1, GLUT_BITMAP_HELVETICA_18);
// //         iText(boxX + 12, boxY + boxH - 30, s2, GLUT_BITMAP_HELVETICA_18);

// //         char scoreText[32];
// //         sprintf(scoreText, "Score: %d", score);
// //         iSetColor(255, 255, 255);
// //         iText(boxX + 12, boxY + boxH - 50, scoreText, GLUT_BITMAP_HELVETICA_18);

// //         char livesText[32];
// //         sprintf(livesText, "Lives: %d", lives);
// //         iSetColor(255, 255, 255);
// //         iText(boxX + 12, boxY + boxH - 80, livesText, GLUT_BITMAP_HELVETICA_18);
// //         char levelText[32];
// //         sprintf(levelText, "Level: %d", gameLevel);
// //         iText(boxX + 12, boxY + boxH - 110, levelText, GLUT_BITMAP_HELVETICA_18);

// //         if (levelWon)
// //         {
// //             iSetColor(255, 255, 0);
// //             iText(700, 500, "LEVEL COMPLETE!", GLUT_BITMAP_TIMES_ROMAN_24);
// //             iText(700, 450, "Press R to reset", GLUT_BITMAP_HELVETICA_18);
// //         }
// //     }
// //     else if (gameState == 2)
// //     {
// //         iShowImage(0, 0, "assets/images/helpBackGround.bmp");
// //         iSetColor(255, 255, 255);
// //         iText(400, 650, "HELP", GLUT_BITMAP_HELVETICA_18);
// //         iText(400, 600, "Use arrow keys to set angle and speed.", GLUT_BITMAP_HELVETICA_18);
// //         iText(400, 550, "Left click to shoot. R to reset. Q to quit.", GLUT_BITMAP_HELVETICA_18);
// //         iText(400, 500, "B to return to menu.", GLUT_BITMAP_HELVETICA_18);
// //     }
// //     else if (gameState == LEADERBOARD)
// //     {
// //         iSetColor(0, 0, 0);
// //         iFilledRectangle(0, 0, WIN_W, WIN_H);
// //         iShowImage(40, 0, "assets/images/LeaderBcover.bmp");
// //         int r = 200 + rand() % 55;
// //         int g = 50 + rand() % 200;
// //         int b = 50 + rand() % 200;
// //         iSetColor(r, g, b);
// //         iText(330, 720, "LEADERBOARD", GLUT_BITMAP_TIMES_ROMAN_24);
// //         iSetColor(0, 0, 0);
// //         iFilledRectangle(300, 90, 900, 600);
// //         showLeaderboard();
// //         iSetColor(255, 255, 255);
// //         iText(60, 60, "Press B to go back", GLUT_BITMAP_HELVETICA_18);
// //     }
// //     else if (gameState == 4)
// //     {
// //         iSetColor(73, 73, 156);
// //         iFilledRectangle(0, 0, WIN_W, WIN_H);
// //         iSetColor(255, 0, 0);
// //         iText(600, 500, "GAME OVER!", GLUT_BITMAP_TIMES_ROMAN_24);
// //         iText(600, 450, "Press R to restart or Q to quit", GLUT_BITMAP_HELVETICA_18);
// //         iText(600, 400, "Lives: 0", GLUT_BITMAP_HELVETICA_18);
// //     }
// //     else if (gameState == 5)
// //     {
// //         iSetColor(201, 103, 104);
// //         iFilledRectangle(0, 0, WIN_W, WIN_H);
// //         int r = 200 + rand() % 55;
// //         int g = 50 + rand() % 200;
// //         int b = 50 + rand() % 200;
// //         iSetColor(r, g, b);
// //         iText(600, 500, "CONGRATULATIONS!", GLUT_BITMAP_TIMES_ROMAN_24);
// //         iSetColor(0, 0, 0);

// //         char msg[100];
// //         sprintf(msg, "You completed the game with a score of %d", score);
// //         iText(500, 450, msg, GLUT_BITMAP_HELVETICA_18);

// //         iText(600, 200, "Press B to return to Main menu", GLUT_BITMAP_HELVETICA_18);
// //         iText(600, 150, "Press Q to quit", GLUT_BITMAP_HELVETICA_18);
// //         iText(600, 100, "Press R to restart", GLUT_BITMAP_HELVETICA_18);
// //     }
// //     else if (gameState == 6)
// //     {
// //         iSetColor(0, 0, 0);
// //         iFilledRectangle(0, 0, WIN_W, WIN_H);
// //         iSetColor(255, 255, 0);
// //         iText(WIN_W / 2 - 120, WIN_H / 2, "Get Ready! Moving to Level 2...", GLUT_BITMAP_TIMES_ROMAN_24);
// //         iText(WIN_W / 2 - 100, WIN_H / 2 - 40, "Press R to Continue", GLUT_BITMAP_HELVETICA_18);
// //     }
// //     else if (gameState == 7)
// //     {
// //         iSetColor(0, 0, 0);
// //         iFilledRectangle(0, 0, WIN_W, WIN_H);
// //         iShowImage(20, 0, "assets/images/CreditC.bmp");
// //         iSetColor(0, 0, 0);
// //         iFilledRectangle(50, 70, 400, 350);
// //         iSetColor(0, 0, 0);
// //         iFilledRectangle(1100, 70, 400, 350);

// //         int r = 200 + rand() % 55;
// //         int g = 50 + rand() % 200;
// //         int b = 50 + rand() % 200;
// //         iSetColor(r, g, b);
// //         iText(100, 450, "CREDIT", GLUT_BITMAP_TIMES_ROMAN_24);
// //         iSetColor(255, 255, 255);
// //         iText(50, 50, "Press B to go back", GLUT_BITMAP_HELVETICA_18);
// //     }
// // }

// // void ballChange()
// // {
// //     if (gameState != 1 || !launched || gameOver)
// //         return;

// //     // Update physics for current bird
// //     t += 0.9;
// //     double rad = toRad(angle);
// //     double vx = velocity * cos(rad);
// //     double vy = velocity * sin(rad);
// //     birds[currentBird].x = 120 + vx * t;
// //     birds[currentBird].y = 450 + vy * t - 0.5 * g * t * t;

// //     // Land or out of bounds
// //     if (birds[currentBird].y <= 345)
// //     {
// //         birds[currentBird].y = 345;
// //         launched = false;
// //         ready = false;
// //         birds[currentBird].active = false;

// //         currentBird++;
// //         if (currentBird < NUM_BIRDS)
// //         {
// //             resetCurrentBird();
// //         }
// //         else
// //         {
// //             gameOver = true;
// //             gameState = 4;
// //         }
// //         return;
// //     }

// //     // Check collision with blocks
// //     for (int i = 0; i < blockCount; i++)
// //     {
// //         if (blocks[i].isVisible)
// //         {
// //             Block b = blocks[i];

// //             if (birds[currentBird].x + BIRD_WIDTH > b.x && birds[currentBird].x < b.x + b.width &&
// //                 birds[currentBird].y + BIRD_HEIGHT > b.y && birds[currentBird].y < b.y + b.height)
// //             {
// //                 if (b.isDeadly)
// //                 {
// //                     birdDead = true;
// //                     launched = false;
// //                     ready = false;
// //                 }
// //                 else
// //                 {
// //                     blocks[i].hitPoints--;
// //                     if (blocks[i].hitPoints <= 0)
// //                     {
// //                         blocks[i].isVisible = 0;
// //                         score += b.isDeadly ? -10 : (b.hitPoints == 2 ? 20 : 10);
// //                     }
// //                 }
// //                 // Bird vanishes on collision
// //                 birds[currentBird].active = false;
// //                 launched = false;
// //                 ready = false;
// //                 currentBird++;
// //                 if (currentBird < NUM_BIRDS)
// //                 {
// //                     resetCurrentBird();
// //                 }
// //                 else
// //                 {
// //                     gameOver = true;
// //                     gameState = 4;
// //                 }
// //                 return;
// //             }
// //         }
// //     }

// //     // Check win
// //     allGone = true;
// //     for (int i = 0; i < blockCount; i++)
// //     {
// //         if (blocks[i].isVisible)
// //         {
// //             allGone = false;
// //             break;
// //         }
// //     }
// //     if (allGone && !levelWon)
// //     {
// //         levelWon = true;
// //         launched = false;
// //         ready = false;

// //         if (gameLevel == 2)
// //         {
// //             gameState = 5;
// //             saveScore();
// //         }
// //     }
// // }

// // void updateBlockPositions()
// // {
// //     for (int i = 0; i < blockCount; i++)
// //     {
// //         if (!blocks[i].isVisible)
// //             continue;

// //         // Falling block (e.g., drops from sky)
// //         if (blocks[i].isFalling)
// //         {
// //             blocks[i].y += blocks[i].vy;

// //             // If it hits the ground (you can adjust the threshold)
// //             if (blocks[i].y <= 345)
// //             {
// //                 blocks[i].y = 345;
// //                 blocks[i].vy = 0;
// //                 blocks[i].isFalling = 0;
// //             }

// //             // Check if it hits the bird
// //             if (
// //                 birds[currentBird].x + BIRD_WIDTH > blocks[i].x && birds[currentBird].x < blocks[i].x + blocks[i].width &&
// //                 birds[currentBird].y + BIRD_HEIGHT > blocks[i].y && birds[currentBird].y < blocks[i].y + blocks[i].height &&
// //                 blocks[i].isDeadly)
// //             {
// //                 // Bird "dies" — respawn next
// //                 resetCurrentBird();
// //             }
// //         }

// //         // Moving block (horizontal or vertical)
// //         if (blocks[i].isMoving)
// //         {
// //             blocks[i].x += blocks[i].vx;

// //             // Bounce from bounds (optional: give movement range limit)
// //             if (blocks[i].x <= 100 || blocks[i].x + blocks[i].width >= WIN_W)
// //             {
// //                 blocks[i].vx *= -1;
// //             }
// //             if (blocks[i].y <= 300 || blocks[i].y + blocks[i].height >= WIN_H)
// //             {
// //                 blocks[i].vy *= -1; // Bounce vertically if needed
// //             }
// //         }
// //     }
// // }

// // void transitionToLevel2()
// // {
// //     if (gameState == 5)
// //     {
// //         gameLevel = 2;
// //         initBlocks2();
// //         initBirds();
// //         resetCurrentBird();
// //         levelWon = false;
// //         gameState = 1;
// //     }
// // }

// // void iMouse(int button, int state, int mx, int my)
// // {
// //     // if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
// //     // {
// //     //     // Menu state
// //     //     if (gameState == 0)
// //     //     {
// //     //         if (mx >= 660 && mx <= 860 && my >= 500 && my <= 550)
// //     //         {
// //     //             // Start game: go to bird selection
// //     //             selectingBirds = true;
// //     //             birdSelectionIndex = 0;
// //     //             for (int i = 0; i < NUM_BIRDS; i++)
// //     //                 selectedBirdTypes[i] = -1;
// //     //         }
// //     //         else if (mx >= 660 && mx <= 860 && my >= 400 && my <= 450)
// //     //         {
// //     //             gameState = LEADERBOARD; // LEADERBOARD
// //     //         }
// //     //         else if (mx >= 660 && mx <= 860 && my >= 200 && my <= 250)
// //     //         {
// //     //             gameState = 2; // HELP
// //     //         }
// //     //         else if (mx >= 660 && mx <= 860 && my >= 100 && my <= 150)
// //     //         {
// //     //             exit(0); // EXIT
// //     //         }
// //     //         else if (mx >= 660 && mx <= 860 && my >= 300 && my <= 350)
// //     //         {
// //     //             gameState = 7; // CREDIT
// //     //         }
// //     //     }
// //     if (gameState == 0)
// //     {
// //         if (mx >= 660 && mx <= 860 && my >= 500 && my <= 550)
// //         {
// //             // Prompt for player name first!
// //             enteringName = true;
// //             nameCharIndex = 0;
// //             playerName[0] = '\0';
// //         }
// //         else if (mx >= 660 && mx <= 860 && my >= 400 && my <= 450)
// //         {
// //             gameState = LEADERBOARD;
// //         }
// //         else if (mx >= 660 && mx <= 860 && my >= 200 && my <= 250)
// //         {
// //             gameState = 2;
// //         }
// //         else if (mx >= 660 && mx <= 860 && my >= 100 && my <= 150)
// //         {
// //             exit(0);
// //         }
// //         else if (mx >= 660 && mx <= 860 && my >= 300 && my <= 350)
// //         {
// //             gameState = 7;
// //         }
// //     }
// //     // Bird selection screen
// //     else if (selectingBirds)
// //     {
// //         // Check which bird image was clicked
// //         for (int i = 0; i < NUM_BIRDS; i++)
// //         {
// //             int bx = 300 + i * 200;
// //             int by = WIN_H / 2;
// //             if (mx >= bx && mx <= bx + BIRD_WIDTH && my >= by && my <= by + BIRD_HEIGHT)
// //             {
// //                 // Check if already chosen
// //                 bool alreadyChosen = false;
// //                 for (int j = 0; j < birdSelectionIndex; j++)
// //                     if (selectedBirdTypes[j] == i)
// //                         alreadyChosen = true;
// //                 if (!alreadyChosen)
// //                 {
// //                     selectedBirdTypes[birdSelectionIndex] = i;
// //                     birdSelectionIndex++;
// //                     if (birdSelectionIndex == NUM_BIRDS)
// //                     {
// //                         selectingBirds = false;
// //                         gameState = 1;
// //                         gameLevel = 1;
// //                         score = 0;
// //                         lives = 5;
// //                         initBlocks1();
// //                         initBirds();
// //                         resetCurrentBird();
// //                         launched = false;
// //                         ready = true;
// //                     }
// //                 }
// //             }
// //         }
// //     }
// //     else if (gameState == 1 && ready && !launched && birds[currentBird].active)
// //     {
// //         launched = true;
// //         ready = false;
// //         t = 0;
// //     }
// // }

// // void iKeyboard(unsigned char key)
// // {
// //     if (key == 'r')
// //     {
// //         currentBird = 0;
// //         initBirds();
// //         resetCurrentBird();

// //         if (levelWon)
// //         {
// //             if (gameLevel == 1)
// //             {
// //                 gameState = 6;
// //             }
// //             else if (gameLevel == 2)
// //             {
// //                 saveScore();
// //                 gameState = 0;
// //                 return;
// //             }
// //             t = 0;
// //             launched = false;
// //             ready = true;
// //             levelWon = false;
// //         }
// //         else if (birdDead && lives > 0)
// //         {
// //             lives--;
// //             t = 0;
// //             launched = false;
// //             ready = true;
// //             levelWon = false;
// //             birdDead = false;
// //         }
// //         else if (lives == 0)
// //         {
// //             gameOver = true;
// //             gameState = 4;
// //         }

// //         t = 0;
// //         launched = false;
// //         ready = true;
// //         levelWon = false;

// //         if (gameLevel == 2 && levelWon && lives > 0)
// //         {
// //             saveScore();
// //         }
// //     }
// //     else if (key == 'q')
// //     {
// //         saveScore();
// //         exit(0);
// //     }
// //     else if (key == 'b') // back to menu
// //     {
// //         gameState = 0;
// //         selectingBirds = false;
// //     }

// //     if (enteringName)
// //     {
// //         if (key == '\r')
// //         { // Enter key
// //             enteringName = false;
// //             // Go to bird selection
// //             selectingBirds = true;
// //             birdSelectionIndex = 0;
// //             for (int i = 0; i < NUM_BIRDS; i++)
// //                 selectedBirdTypes[i] = -1;
// //         }
// //         else if (key == '\b' && nameCharIndex > 0)
// //         { // Backspace
// //             playerName[--nameCharIndex] = '\0';
// //         }
// //         else if (nameCharIndex < 99 && ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9')))
// //         {
// //             playerName[nameCharIndex++] = key;
// //             playerName[nameCharIndex] = '\0';
// //         }
// //         return;
// //     }
// // }

// // void iSpecialKeyboard(unsigned char key)
// // {
// //     if (gameState == 1 && ready)
// //     {
// //         if (key == GLUT_KEY_UP && angle < 90)
// //             angle += 1;
// //         else if (key == GLUT_KEY_DOWN && angle > 0)
// //             angle -= 1;
// //         else if (key == GLUT_KEY_RIGHT && velocity < 200)
// //             velocity += 1;
// //         else if (key == GLUT_KEY_LEFT && velocity > 10)
// //             velocity -= 1;
// //     }
// //     if (key == GLUT_KEY_END)
// //         exit(0);
// // }

// // // Timer function to handle cover screen delay
// // void coverTimerFunc()
// // {
// //     if (gameState == -1)
// //     {
// //         coverTimer++;
// //         if (coverTimer >= 7)
// //         {
// //             gameState = 0;
// //         }
// //     }
// // }

// // void iMouseMove(int mx, int my) {}
// // void iMouseDrag(int mx, int my) {}
// // void iMouseWheel(int dir, int mx, int my) {}

// // int main(int argc, char *argv[])
// // {
// //     glutInit(&argc, argv);
// //     iSetTimer(1000, coverTimerFunc); // Cover screen timer
// //     iSetTimer(20, ballChange);
// //     iSetTimer(20, updateBlockPositions);
// //     srand(time(0));
// //     initBlocks1();
// //     for (int i = 0; i < NUM_BIRDS; i++)
// //         selectedBirdTypes[i] = i;
// //     initBirds();
// //     iSetTimer(2000, transitionToLevel2); // Transition to level 2 after 20 seconds
// //     iInitialize(WIN_W, WIN_H, "Angry Birds");
// //     return 0;
// // }

// #include "iGraphics.h"
// #include <math.h>
// #include <stdbool.h>
// #include <time.h>
// #include <stdio.h>
// #include <stdlib.h>

// #define WIN_W 1550
// #define WIN_H 1000
// #define MAX_BLOCKS 1000
// #define BIRD_WIDTH 60
// #define BIRD_HEIGHT 60
// #define BLOCK_WIDTH 30
// #define BLOCK_HEIGHT 30
// #define LEADERBOARD 3
// #define MAX_NAME_LEN 100
// #define NUM_BIRDS 5

// // Game state
// int gameState = -1;
// int coverTimer = 0;
// int gameLevel = 0;

// // Bird and physics
// double velocity = 90; // initial speed
// double angle = 30;    // launch angle
// double g = 9.8;
// double t = 0;
// bool launched = false;
// bool ready = true;
// int score = 0;
// bool levelWon = false;
// bool allGone = false;
// int lives = 4;
// bool birdDead = false;
// bool gameOver = false;

// // Bird struct and array
// typedef struct
// {
//     double x, y;
//     bool active;
//     int birdType; // 0-4 for bird1.bmp ... bird5.bmp
// } Bird;

// Bird birds[NUM_BIRDS];
// int currentBird = 0;

// // Bird image filenames
// const char *birdImages[NUM_BIRDS] = {
//     "assets/images/redBird.bmp",
//     "assets/images/yellowBird.bmp",
//     "assets/images/blueBird.png",
//     "assets/images/blackBird.bmp",
//     "assets/images/blueBird.png"};

// // Bird selection state
// int birdSelectionIndex = 0;                              // which slot is being selected
// int selectedBirdTypes[NUM_BIRDS] = {-1, -1, -1, -1, -1}; // stores chosen bird type for each slot
// bool selectingBirds = false;

// // score and leaderboard
// char playerName[MAX_NAME_LEN] = "";
// int nameCharIndex = 0;
// bool enteringName = false;

// static double toRad(double deg) { return deg * M_PI / 180.0; }

// // Block struct
// typedef struct
// {
//     float x, y;
//     float width, height;
//     int isVisible;
//     int hitPoints;
//     int isFalling;
//     int isMoving;
//     float vx, vy;
//     int isDeadly;
// } Block;

// Block blocks[MAX_BLOCKS];
// int blockCount = 0;

// // Bird position helpers
// void initBirds()
// {
//     for (int i = 0; i < NUM_BIRDS; i++)
//     {
//         birds[i].x = 50 + i * 50; // waiting positions
//         birds[i].y = 200;
//         birds[i].active = true;
//         birds[i].birdType = selectedBirdTypes[i] >= 0 ? selectedBirdTypes[i] : i; // fallback to i if not selected
//     }
//     birds[0].x = 120;
//     birds[0].y = 450;
// }

// void resetCurrentBird()
// {
//     if (currentBird < NUM_BIRDS)
//     {
//         birds[currentBird].x = 120;
//         birds[currentBird].y = 450;
//     }
//     t = 0;
//     launched = false;
//     ready = true;
// }

// // Block helpers
// void addBlock(float x, float y, float w, float h, int isVisible, int health, int isFalling, int isMoving, float dx, float dy, int isDeadly)
// {
//     if (blockCount >= MAX_BLOCKS)
//         return;
//     blocks[blockCount++] = (Block){x, y, w, h, 1, health, isFalling, isMoving, dx, dy, isDeadly};
// }

// void addPyramid(float centerX, float baseY, int layers, float w, float h, int health)
// {
//     for (int i = 0; i < layers; i++)
//     {
//         int count = layers - i;
//         float startX = centerX - (count * w) / 2;
//         for (int j = 0; j < count; j++)
//         {
//             addBlock(startX + j * w, baseY + i * h, w, h, 1, health, 0, 0, 0, 0, 0);
//         }
//     }
// }

// void addBlockGrid(float startX, float startY, int rows, int cols, float w, float h, int health)
// {
//     for (int i = 0; i < rows; i++)
//     {
//         for (int j = 0; j < cols; j++)
//         {
//             addBlock(startX + j * w, startY + i * h, w, h, 1, health, 0, 0, 0, 0, 0);
//         }
//     }
// }

// void addPerimeterGrid(float startX, float startY, int rows, int cols, float w, float h, int thickness, int health)
// {
//     for (int r = 0; r < rows; r++)
//     {
//         for (int c = 0; c < cols; c++)
//         {
//             bool isEdge = (r < thickness || r >= rows - thickness || c < thickness || c >= cols - thickness);
//             if (isEdge)
//             {
//                 float x = startX + c * w;
//                 float y = startY + r * h;
//                 addBlock(x, y, w, h, 1, health, 0, 0, 0, 0, 0);
//             }
//         }
//     }
// }

// void fallingBlock(float x, float y, float w, float h, int health, float dy, int isDeadly)
// {
//     addBlock(x, y, w, h, 1, health, 1, 0, 0, dy, isDeadly);
// }

// void movingBlocks(float x, float y, float w, float h, int health, float dx)
// {
//     addBlock(x, y, w, h, 1, health, 0, 1, dx, 0, 0);
// }

// void initBlocks1() // blocks for level 1
// {
//     blockCount = 0;
//     addPerimeterGrid(600, 350, 7, 9, BLOCK_WIDTH, BLOCK_HEIGHT, 2, 1);
//     float pyramidcenterX = 600 + 9 * BLOCK_WIDTH / 2;
//     float pyramidbaseY = 350 + 7 * BLOCK_HEIGHT;
//     addPyramid(pyramidcenterX, pyramidbaseY, 4, BLOCK_WIDTH, BLOCK_HEIGHT, 1);
// }
// void initBlocks2() // blocks for level 2
// {
//     blockCount = 0;
//     addBlockGrid(700, 350, 5, 3, BLOCK_WIDTH, BLOCK_HEIGHT, 1);
//     addPyramid(850, 350, 3, BLOCK_WIDTH, BLOCK_HEIGHT, 1);
//     movingBlocks(600, 500, BLOCK_WIDTH, BLOCK_HEIGHT, 1, 4);
//     fallingBlock(400, 800, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
//     fallingBlock(600, 800, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
//     fallingBlock(800, 600, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
//     fallingBlock(1000, 800, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
//     fallingBlock(500, 350, BLOCK_WIDTH, BLOCK_HEIGHT, 1, 4, 1);
//     movingBlocks(1200, 600, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4);
//     movingBlocks(300, 600, BLOCK_WIDTH, BLOCK_HEIGHT, 1, 4);
//     movingBlocks(1000, 500, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4);
//     movingBlocks(400, 500, BLOCK_WIDTH, BLOCK_HEIGHT, 1, 4);
// }

// typedef struct
// {
//     char name[100];
//     int score;
// } Leader;

// Leader leaders[100];
// int leaderCount = 0;

// void loadLeaderboard()
// {
//     leaderCount = 0;
//     FILE *fp = fopen("bin\\assets\\leaderboard.txt", "r");
//     if (fp == NULL)
//         return;
//     while (fscanf(fp, "%s %d", leaders[leaderCount].name, &leaders[leaderCount].score) == 2)
//     {
//         leaderCount++;
//         if (leaderCount >= 100)
//             break; // limit to 100 leaders
//     }
//     fclose(fp);
// }

// // Save score to file
// void saveScore()
// {
//     FILE *file = fopen("bin\\assets\\leaderboard.txt", "a");
//     if (file)
//     {
//         fprintf(file, "%s %d\n", playerName, score);
//         fclose(file);
//     }
// }

// void showLeaderboard()
// {
//     FILE *file = fopen("bin\\assets\\leaderboard.txt", "r");
//     if (!file)
//     {
//         iText(600, 200, "No leaderboard data available.", GLUT_BITMAP_HELVETICA_18);
//         return;
//     }

//     Leader tempLeaders[100];
//     int count = 0;

//     while (fscanf(file, "%s %d", tempLeaders[count].name, &tempLeaders[count].score) == 2)
//     {
//         count++;
//         if (count >= 100)
//             break;
//     }
//     fclose(file);

//     if (count == 0)
//     {
//         iText(600, 200, "No leaderboard data yet.", GLUT_BITMAP_HELVETICA_18);
//         return;
//     }
//     // Sort leaders by score
//     for (int i = 0; i < count - 1; i++)
//     {
//         for (int j = i + 1; j < count; j++)
//         {
//             if (tempLeaders[j].score > tempLeaders[i].score)
//             {
//                 Leader temp = tempLeaders[i];
//                 tempLeaders[i] = tempLeaders[j];
//                 tempLeaders[j] = temp;
//             }
//         }
//     }
//     // Show top 5
//     iSetColor(255, 255, 0);
//     iText(600, 800, "LEADERBOARD", GLUT_BITMAP_HELVETICA_18);
//     for (int i = 0; i < count && i < 5; i++)
//     {
//         char line[200];
//         sprintf(line, "%d.%s - %d", i + 1, tempLeaders[i].name, tempLeaders[i].score);
//         iText(600, 550 - i * 30, line, GLUT_BITMAP_HELVETICA_18);
//     }
// }

// void iDraw()
// {
//     iClear();

//     if (gameState == -1)
//     {
//         iShowImage(0, 0, "assets/images/coverS.bmp");
//         int r = 200 + rand() % 55;
//         int g = 50 + rand() % 200;
//         int b = 50 + rand() % 200;
//         iSetColor(r, g, b);
//         iText(WIN_W / 2 - 30, 60, "Loading...", GLUT_BITMAP_TIMES_ROMAN_24);
//     }
//     else if (gameState == 0)
//     {
//         iShowImage(0, 0, "assets/images/MenuCover.jpg");
//         iShowImage(510, 630, "assets/images/AngryBwritting.bmp");

//         int btnW = 200, btnH = 50, x = 660;
//         int y1 = 500, y2 = 400, y3 = 100, y4 = 300, y5 = 200;
//         // Start Game Button
//         iSetColor(0, 100, 0);
//         iFilledRectangle(x + 5, y1 - 5, btnW, btnH);
//         iSetColor(0, 200, 0);
//         iFilledRectangle(x, y1, btnW, btnH);
//         iSetColor(255, 255, 255);
//         iText(x + 50, y1 + 15, "START GAME", GLUT_BITMAP_HELVETICA_18);
//         // Leaderboard Button
//         iSetColor(0, 0, 100);
//         iFilledRectangle(x + 5, y2 - 5, btnW, btnH);
//         iSetColor(0, 0, 200);
//         iFilledRectangle(x, y2, btnW, btnH);
//         iSetColor(255, 255, 255);
//         iText(x + 50, y2 + 15, "LEADERBOARD", GLUT_BITMAP_HELVETICA_18);
//         // Exit Button
//         iSetColor(100, 0, 0);
//         iFilledRectangle(x + 5, y3 - 5, btnW, btnH);
//         iSetColor(200, 0, 0);
//         iFilledRectangle(x, y3, btnW, btnH);
//         iSetColor(255, 255, 255);
//         iText(x + 75, y3 + 15, "EXIT", GLUT_BITMAP_HELVETICA_18);
//         // Credit Button
//         iSetColor(100, 100, 0);
//         iFilledRectangle(x + 5, y4 - 5, btnW, btnH);
//         iSetColor(200, 200, 0);
//         iFilledRectangle(x, y4, btnW, btnH);
//         iSetColor(255, 255, 255);
//         iText(x + 50, y4 + 15, "CREDIT", GLUT_BITMAP_HELVETICA_18);
//         // Help Button
//         iSetColor(100, 0, 100);
//         iFilledRectangle(x + 5, y5 - 5, btnW, btnH);
//         iSetColor(200, 0, 200);
//         iFilledRectangle(x, y5, btnW, btnH);
//         iSetColor(255, 255, 255);
//         iText(x + 50, y5 + 15, "HELP", GLUT_BITMAP_HELVETICA_18);

//         if (enteringName)
//         {
//             iSetColor(0, 0, 0);
//             iFilledRectangle(0, 0, WIN_W, WIN_H);
//             iSetColor(255, 255, 255);
//             iText(WIN_W / 2 - 100, WIN_H / 2, "Enter your name: ", GLUT_BITMAP_HELVETICA_18);
//             iText(WIN_W / 2 - 100, WIN_H / 2 - 30, playerName, GLUT_BITMAP_HELVETICA_18);
//         }
//     }
//     // Bird selection screen
//     else if (selectingBirds)
//     {
//         iSetColor(0, 0, 0);
//         iFilledRectangle(0, 0, WIN_W, WIN_H);
//         iSetColor(255, 255, 255);
//         char msg[128];
//         sprintf(msg, "Select bird for slot %d", birdSelectionIndex + 1);
//         iText(WIN_W / 2 - 100, WIN_H - 100, msg, GLUT_BITMAP_HELVETICA_18);

//         // Show all bird images to choose from
//         for (int i = 0; i < NUM_BIRDS; i++)
//         {
//             int bx = 300 + i * 200;
//             int by = WIN_H / 2;
//             iShowImage(bx, by, birdImages[i]);
//             // Highlight if already chosen for another slot
//             bool alreadyChosen = false;
//             for (int j = 0; j < birdSelectionIndex; j++)
//                 if (selectedBirdTypes[j] == i)
//                     alreadyChosen = true;
//             if (alreadyChosen)
//             {
//                 iSetColor(255, 0, 0);
//                 iRectangle(bx, by, BIRD_WIDTH, BIRD_HEIGHT);
//             }
//         }
//         // Show chosen birds so far
//         iSetColor(255, 255, 0);
//         iText(200, 200, "Your bird order:", GLUT_BITMAP_HELVETICA_18);
//         for (int i = 0; i < birdSelectionIndex; i++)
//         {
//             iShowImage(400 + i * 70, 150, birdImages[selectedBirdTypes[i]]);
//         }
//     }
//     // Gameplay
//     else if (gameState == 1 && (gameLevel == 1 || gameLevel == 2))
//     {
//         iShowImage(0, 0, "assets/images/groundImage2.bmp");
//         iShowImage(0, 350, "assets/images/skyImage.bmp");
//         iShowImage(1150, 330, "assets/images/tree.png");
//         iShowImage(0, 330, "assets/images/grassDecor.png");
//         iShowImage(400, 330, "assets/images/grassDecor.png");
//         iShowImage(800, 330, "assets/images/grassDecor.png");
//         iShowImage(1200, 330, "assets/images/grassDecor.png");

//         // Draw all birds (waiting and slingshot)
//         for (int i = 0; i < NUM_BIRDS; i++)
//         {
//             if (birds[i].active)
//             {
//                 iShowImage((int)birds[i].x, (int)birds[i].y, birdImages[birds[i].birdType]);
//             }
//         }
//         iShowImage(100, 285, "assets/images/extractedCartoonSlingshotAdd.bmp.bmp");

//         for (int i = 0; i < blockCount; i++)
//         {
//             if (blocks[i].isVisible)
//             {
//                 iShowImage((int)blocks[i].x, (int)blocks[i].y, "assets/images/blockImage.bmp");
//             }
//         }

//         // Trajectory preview for current bird
//         if (ready && birds[currentBird].active)
//         {
//             double rad = toRad(angle);
//             double vx = velocity * cos(rad);
//             double vy = velocity * sin(rad);
//             double px = 120, py = 450;
//             double t_step = 0.1;
//             double t_proj = 0;
//             int max_steps = 200;

//             for (int i = 0; i < max_steps; i++)
//             {
//                 double next_t = t_proj + t_step;
//                 double next_px = 120 + vx * next_t;
//                 double next_py = 450 + vy * next_t - 0.5 * g * next_t * next_t;

//                 if (next_py < 345)
//                     break;

//                 int hit = 0;
//                 for (int j = 0; j < blockCount; j++)
//                 {
//                     if (blocks[j].isVisible)
//                     {
//                         if (next_px + BIRD_WIDTH > blocks[j].x && next_px < blocks[j].x + blocks[j].width &&
//                             next_py + BIRD_HEIGHT > blocks[j].y && next_py < blocks[j].y + blocks[j].height)
//                         {
//                             hit = 1;
//                             break;
//                         }
//                     }
//                 }
//                 if (hit)
//                     break;

//                 iSetColor(255, 255, 0);
//                 iLine(px, py, next_px, next_py);

//                 px = next_px;
//                 py = next_py;
//                 t_proj = next_t;
//             }
//         }

//         // HUD
//         int boxW = 220, boxH = 120;
//         int boxX = 1300;
//         int boxY = 720;

//         int r = 200 + rand() % 55;
//         int g = 50 + rand() % 200;
//         int b = 50 + rand() % 200;
//         iSetColor(r, g, b);
//         iFilledRectangle(boxX, boxY, boxW, boxH);
//         iSetColor(152, 79, 166);
//         iFilledRectangle(boxX + 10, boxY + 10, boxW - 20, boxH - 20);

//         // HUD text
//         char s1[32], s2[32];
//         sprintf(s1, "Angle: %.0f°", angle);
//         sprintf(s2, "Speed: %.0f", velocity);
//         iSetColor(255, 255, 255);
//         iText(boxX + 12, boxY + boxH - 10, s1, GLUT_BITMAP_HELVETICA_18);
//         iText(boxX + 12, boxY + boxH - 30, s2, GLUT_BITMAP_HELVETICA_18);

//         char scoreText[32];
//         sprintf(scoreText, "Score: %d", score);
//         iSetColor(255, 255, 255);
//         iText(boxX + 12, boxY + boxH - 50, scoreText, GLUT_BITMAP_HELVETICA_18);

//         char livesText[32];
//         sprintf(livesText, "Lives: %d", lives);
//         iSetColor(255, 255, 255);
//         iText(boxX + 12, boxY + boxH - 80, livesText, GLUT_BITMAP_HELVETICA_18);
//         char levelText[32];
//         sprintf(levelText, "Level: %d", gameLevel);
//         iText(boxX + 12, boxY + boxH - 110, levelText, GLUT_BITMAP_HELVETICA_18);

//         if (levelWon)
//         {
//             iSetColor(255, 255, 0);
//             iText(700, 500, "LEVEL COMPLETE!", GLUT_BITMAP_TIMES_ROMAN_24);
//             iText(700, 450, "Press R to reset", GLUT_BITMAP_HELVETICA_18);
//         }
//     }
//     else if (gameState == 2)
//     {
//         iShowImage(0, 0, "assets/images/helpBackGround.bmp");
//         iSetColor(255, 255, 255);
//         iText(400, 650, "HELP", GLUT_BITMAP_HELVETICA_18);
//         iText(400, 600, "Use arrow keys to set angle and speed.", GLUT_BITMAP_HELVETICA_18);
//         iText(400, 550, "Left click to shoot. R to reset. Q to quit.", GLUT_BITMAP_HELVETICA_18);
//         iText(400, 500, "B to return to menu.", GLUT_BITMAP_HELVETICA_18);
//     }
//     else if (gameState == LEADERBOARD)
//     {
//         iSetColor(0, 0, 0);
//         iFilledRectangle(0, 0, WIN_W, WIN_H);
//         iShowImage(40, 0, "assets/images/LeaderBcover.bmp");
//         int r = 200 + rand() % 55;
//         int g = 50 + rand() % 200;
//         int b = 50 + rand() % 200;
//         iSetColor(r, g, b);
//         iText(330, 720, "LEADERBOARD", GLUT_BITMAP_TIMES_ROMAN_24);
//         iSetColor(0, 0, 0);
//         iFilledRectangle(300, 90, 900, 600);
//         showLeaderboard();
//         iSetColor(255, 255, 255);
//         iText(60, 60, "Press B to go back", GLUT_BITMAP_HELVETICA_18);
//     }
//     else if (gameState == 4)
//     {
//         iSetColor(73, 73, 156);
//         iFilledRectangle(0, 0, WIN_W, WIN_H);
//         iSetColor(255, 0, 0);
//         iText(600, 500, "GAME OVER!", GLUT_BITMAP_TIMES_ROMAN_24);
//         iText(600, 450, "Press R to restart or Q to quit", GLUT_BITMAP_HELVETICA_18);
//         iText(600, 400, "Lives: 0", GLUT_BITMAP_HELVETICA_18);
//     }
//     else if (gameState == 5)
//     {
//         iSetColor(201, 103, 104);
//         iFilledRectangle(0, 0, WIN_W, WIN_H);
//         int r = 200 + rand() % 55;
//         int g = 50 + rand() % 200;
//         int b = 50 + rand() % 200;
//         iSetColor(r, g, b);
//         iText(600, 500, "CONGRATULATIONS!", GLUT_BITMAP_TIMES_ROMAN_24);
//         iSetColor(0, 0, 0);

//         char msg[100];
//         sprintf(msg, "You completed the game with a score of %d", score);
//         iText(500, 450, msg, GLUT_BITMAP_HELVETICA_18);

//         iText(600, 200, "Press B to return to Main menu", GLUT_BITMAP_HELVETICA_18);
//         iText(600, 150, "Press Q to quit", GLUT_BITMAP_HELVETICA_18);
//         iText(600, 100, "Press R to restart", GLUT_BITMAP_HELVETICA_18);
//     }
//     else if (gameState == 6)
//     {
//         iSetColor(0, 0, 0);
//         iFilledRectangle(0, 0, WIN_W, WIN_H);
//         iSetColor(255, 255, 0);
//         iText(WIN_W / 2 - 120, WIN_H / 2, "Get Ready! Moving to Level 2...", GLUT_BITMAP_TIMES_ROMAN_24);
//         iText(WIN_W / 2 - 100, WIN_H / 2 - 40, "Press R to Continue", GLUT_BITMAP_HELVETICA_18);
//     }
//     else if (gameState == 7)
//     {
//         iSetColor(0, 0, 0);
//         iFilledRectangle(0, 0, WIN_W, WIN_H);
//         iShowImage(20, 0, "assets/images/CreditC.bmp");
//         iSetColor(0, 0, 0);
//         iFilledRectangle(50, 70, 400, 350);
//         iSetColor(0, 0, 0);
//         iFilledRectangle(1100, 70, 400, 350);

//         int r = 200 + rand() % 55;
//         int g = 50 + rand() % 200;
//         int b = 50 + rand() % 200;
//         iSetColor(r, g, b);
//         iText(100, 450, "CREDIT", GLUT_BITMAP_TIMES_ROMAN_24);
//         iSetColor(255, 255, 255);
//         iText(50, 50, "Press B to go back", GLUT_BITMAP_HELVETICA_18);
//     }
// }

// void ballChange()
// {
//     if (gameState != 1 || !launched || gameOver)
//         return;

//     // Update physics for current bird
//     t += 0.9;
//     double rad = toRad(angle);
//     double vx = velocity * cos(rad);
//     double vy = velocity * sin(rad);
//     birds[currentBird].x = 120 + vx * t;
//     birds[currentBird].y = 450 + vy * t - 0.5 * g * t * t;

//     // Land or out of bounds
//     if (birds[currentBird].y <= 345)
//     {
//         birds[currentBird].y = 345;
//         launched = false;
//         ready = false;
//         birds[currentBird].active = false;

//         currentBird++;
//         if (currentBird < NUM_BIRDS)
//         {
//             resetCurrentBird();
//         }
//         else
//         {
//             gameOver = true;
//             gameState = 4;
//         }
//         return;
//     }

//     // Check collision with blocks
//     for (int i = 0; i < blockCount; i++)
//     {
//         if (blocks[i].isVisible)
//         {
//             Block b = blocks[i];

//             if (birds[currentBird].x + BIRD_WIDTH > b.x && birds[currentBird].x < b.x + b.width &&
//                 birds[currentBird].y + BIRD_HEIGHT > b.y && birds[currentBird].y < b.y + b.height)
//             {
//                 if (b.isDeadly)
//                 {
//                     birdDead = true;
//                     launched = false;
//                     ready = false;
//                 }
//                 else
//                 {
//                     blocks[i].hitPoints--;
//                     if (blocks[i].hitPoints <= 0)
//                     {
//                         blocks[i].isVisible = 0;
//                         score += b.isDeadly ? -10 : (b.hitPoints == 2 ? 20 : 10);
//                     }
//                 }
//                 // Bird vanishes on collision
//                 birds[currentBird].active = false;
//                 launched = false;
//                 ready = false;
//                 currentBird++;
//                 if (currentBird < NUM_BIRDS)
//                 {
//                     resetCurrentBird();
//                 }
//                 else
//                 {
//                     gameOver = true;
//                     gameState = 4;
//                 }
//                 return;
//             }
//         }
//     }

//     // Check win
//     allGone = true;
//     for (int i = 0; i < blockCount; i++)
//     {
//         if (blocks[i].isVisible)
//         {
//             allGone = false;
//             break;
//         }
//     }
//     if (allGone && !levelWon)
//     {
//         levelWon = true;
//         launched = false;
//         ready = false;

//         if (gameLevel == 2)
//         {
//             gameState = 5;
//             saveScore();
//         }
//     }
// }

// void updateBlockPositions()
// {
//     for (int i = 0; i < blockCount; i++)
//     {
//         if (!blocks[i].isVisible)
//             continue;

//         // Falling block (e.g., drops from sky)
//         if (blocks[i].isFalling)
//         {
//             blocks[i].y += blocks[i].vy;

//             // If it hits the ground (you can adjust the threshold)
//             if (blocks[i].y <= 345)
//             {
//                 blocks[i].y = 345;
//                 blocks[i].vy = 0;
//                 blocks[i].isFalling = 0;
//             }

//             // Check if it hits the bird
//             if (
//                 birds[currentBird].x + BIRD_WIDTH > blocks[i].x && birds[currentBird].x < blocks[i].x + blocks[i].width &&
//                 birds[currentBird].y + BIRD_HEIGHT > blocks[i].y && birds[currentBird].y < blocks[i].y + blocks[i].height &&
//                 blocks[i].isDeadly)
//             {
//                 // Bird "dies" — respawn next
//                 resetCurrentBird();
//             }
//         }

//         // Moving block (horizontal or vertical)
//         if (blocks[i].isMoving)
//         {
//             blocks[i].x += blocks[i].vx;

//             // Bounce from bounds (optional: give movement range limit)
//             if (blocks[i].x <= 100 || blocks[i].x + blocks[i].width >= WIN_W)
//             {
//                 blocks[i].vx *= -1;
//             }
//             if (blocks[i].y <= 300 || blocks[i].y + blocks[i].height >= WIN_H)
//             {
//                 blocks[i].vy *= -1; // Bounce vertically if needed
//             }
//         }
//     }
// }

// void transitionToLevel2()
// {
//     if (gameState == 5)
//     {
//         gameLevel = 2;
//         initBlocks2();
//         initBirds();
//         resetCurrentBird();
//         levelWon = false;
//         gameState = 1;
//     }
// }

// void iMouse(int button, int state, int mx, int my)
// {
//     if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//     {
//         // Menu state
//         if (gameState == 0)
//         {
//             if (mx >= 660 && mx <= 860 && my >= 500 && my <= 550)
//             {
//                 // Prompt for player name first!
//                 enteringName = true;
//                 nameCharIndex = 0;
//                 playerName[0] = '\0';
//             }
//             else if (mx >= 660 && mx <= 860 && my >= 400 && my <= 450)
//             {
//                 gameState = LEADERBOARD;
//             }
//             else if (mx >= 660 && mx <= 860 && my >= 200 && my <= 250)
//             {
//                 gameState = 2;
//             }
//             else if (mx >= 660 && mx <= 860 && my >= 100 && my <= 150)
//             {
//                 exit(0);
//             }
//             else if (mx >= 660 && mx <= 860 && my >= 300 && my <= 350)
//             {
//                 gameState = 7;
//             }
//         }
//         // Bird selection screen
//         else if (selectingBirds)
//         {
//             // Check which bird image was clicked
//             for (int i = 0; i < NUM_BIRDS; i++)
//             {
//                 int bx = 300 + i * 200;
//                 int by = WIN_H / 2;
//                 if (mx >= bx && mx <= bx + BIRD_WIDTH && my >= by && my <= by + BIRD_HEIGHT)
//                 {
//                     // Check if already chosen
//                     bool alreadyChosen = false;
//                     for (int j = 0; j < birdSelectionIndex; j++)
//                         if (selectedBirdTypes[j] == i)
//                             alreadyChosen = true;
//                     if (!alreadyChosen)
//                     {
//                         selectedBirdTypes[birdSelectionIndex] = i;
//                         birdSelectionIndex++;
//                         if (birdSelectionIndex == NUM_BIRDS)
//                         {
//                             selectingBirds = false;
//                             gameState = 1;
//                             gameLevel = 1;
//                             score = 0;
//                             lives = 5;
//                             initBlocks1();
//                             initBirds();
//                             resetCurrentBird();
//                             launched = false;
//                             ready = true;
//                         }
//                     }
//                 }
//             }
//         }
//         else if (gameState == 1 && ready && !launched && birds[currentBird].active)
//         {
//             launched = true;
//             ready = false;
//             t = 0;
//         }
//     }
// }

// void iKeyboard(unsigned char key)
// {
//     if (key == 'r')
//     {
//         currentBird = 0;
//         initBirds();
//         resetCurrentBird();

//         if (levelWon)
//         {
//             if (gameLevel == 1)
//             {
//                 gameState = 6;
//             }
//             else if (gameLevel == 2)
//             {
//                 saveScore();
//                 gameState = 0;
//                 return;
//             }
//             t = 0;
//             launched = false;
//             ready = true;
//             levelWon = false;
//         }
//         else if (birdDead && lives > 0)
//         {
//             lives--;
//             t = 0;
//             launched = false;
//             ready = true;
//             levelWon = false;
//             birdDead = false;
//         }
//         else if (lives == 0)
//         {
//             gameOver = true;
//             gameState = 4;
//         }

//         t = 0;
//         launched = false;
//         ready = true;
//         levelWon = false;

//         if (gameLevel == 2 && levelWon && lives > 0)
//         {
//             saveScore();
//         }
//     }
//     else if (key == 'q')
//     {
//         saveScore();
//         exit(0);
//     }
//     else if (key == 'b') // back to menu
//     {
//         gameState = 0;
//         selectingBirds = false;
//     }

//     if (enteringName)
//     {
//         if (key == '\r')
//         { // Enter key
//             enteringName = false;
//             // Go to bird selection
//             selectingBirds = true;
//             birdSelectionIndex = 0;
//             for (int i = 0; i < NUM_BIRDS; i++)
//                 selectedBirdTypes[i] = -1;
//         }
//         else if (key == '\b' && nameCharIndex > 0)
//         { // Backspace
//             playerName[--nameCharIndex] = '\0';
//         }
//         else if (nameCharIndex < 99 && ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9')))
//         {
//             playerName[nameCharIndex++] = key;
//             playerName[nameCharIndex] = '\0';
//         }
//         return;
//     }
// }

// void iSpecialKeyboard(unsigned char key)
// {
//     if (gameState == 1 && ready)
//     {
//         if (key == GLUT_KEY_UP && angle < 90)
//             angle += 1;
//         else if (key == GLUT_KEY_DOWN && angle > 0)
//             angle -= 1;
//         else if (key == GLUT_KEY_RIGHT && velocity < 200)
//             velocity += 1;
//         else if (key == GLUT_KEY_LEFT && velocity > 10)
//             velocity -= 1;
//     }
//     if (key == GLUT_KEY_END)
//         exit(0);
// }

// // Timer function to handle cover screen delay
// void coverTimerFunc()
// {
//     if (gameState == -1)
//     {
//         coverTimer++;
//         if (coverTimer >= 7)
//         {
//             gameState = 0;
//         }
//     }
// }

// void iMouseMove(int mx, int my) {}
// void iMouseDrag(int mx, int my) {}
// void iMouseWheel(int dir, int mx, int my) {}

// int main(int argc, char *argv[])
// {
//     glutInit(&argc, argv);
//     iSetTimer(1000, coverTimerFunc); // Cover screen timer
//     iSetTimer(20, ballChange);
//     iSetTimer(20, updateBlockPositions);
//     srand(time(0));
//     initBlocks1();
//     for (int i = 0; i < NUM_BIRDS; i++)
//         selectedBirdTypes[i] = i;
//     initBirds();
//     iSetTimer(2000, transitionToLevel2); // Transition to level 2 after 20 seconds
//     iInitialize(WIN_W, WIN_H, "Angry Birds");
//     return 0;
// }

// #include "iGraphics.h"
// #include <math.h>
// #include <stdbool.h>
// #include <time.h>
// #include <stdio.h>
// #include <stdlib.h>

// #define WIN_W 1550
// #define WIN_H 1000
// #define MAX_BLOCKS 1000
// #define BIRD_WIDTH 60
// #define BIRD_HEIGHT 60
// #define BLOCK_WIDTH 30
// #define BLOCK_HEIGHT 30
// #define LEADERBOARD 3
// #define MAX_NAME_LEN 100
// #define NUM_BIRDS 5

// // Game state
// int gameState = -1;
// int coverTimer = 0;
// int gameLevel = 0;

// // Bird and physics
// double velocity = 90;
// double angle = 30;
// double g = 9.8;
// double t = 0;
// bool launched = false;
// bool ready = true;
// int score = 0;
// bool levelWon = false;
// bool allGone = false;
// int lives = 5;
// bool birdDead = false;
// bool gameOver = false;

// // Bird struct and array
// typedef struct
// {
//     double x, y;
//     bool active;
//     int type; // 0-4
// } Bird;

// Bird birds[NUM_BIRDS];
// int currentBird = 0;

// // Bird images
// const char *birdImages[NUM_BIRDS] = {
//     "assets/images/redBird.bmp",
//     "assets/images/yellowBird.bmp",
//     "assets/images/blueBird.png",
//     "assets/images/blackBird.bmp",
//     "assets/images/greenBird.bmp"};

// // Bird selection
// int selectedBirdTypes[NUM_BIRDS] = {0, 1, 2, 3, 4};
// int birdSelectionIndex = 0;
// bool selectingBirds = false;

// // score and leaderboard
// char playerName[MAX_NAME_LEN] = "";
// int nameCharIndex = 0;
// bool enteringName = false;

// // Mouse drag for slingshot
// bool dragging = false;
// int dragX = 0, dragY = 0;

// static double toRad(double deg) { return deg * M_PI / 180.0; }

// // Block struct
// typedef struct
// {
//     float x, y;
//     float width, height;
//     int isVisible;
//     int hitPoints;
//     int isFalling;
//     int isMoving;
//     float vx, vy;
//     int isDeadly;
// } Block;

// Block blocks[MAX_BLOCKS];
// int blockCount = 0;

// // Bird position helpers
// void initBirds()
// {
//     for (int i = 0; i < NUM_BIRDS; i++)
//     {
//         birds[i].x = 50 + i * 50;
//         birds[i].y = 200;
//         birds[i].active = true;
//         birds[i].type = selectedBirdTypes[i];
//     }
//     birds[0].x = 120;
//     birds[0].y = 450;
// }

// void resetCurrentBird()
// {
//     if (currentBird < NUM_BIRDS)
//     {
//         birds[currentBird].x = 120;
//         birds[currentBird].y = 450;
//     }
//     t = 0;
//     launched = false;
//     ready = true;
// }

// void addBlock(float x, float y, float w, float h, int isVisible, int health, int isFalling, int isMoving, float dx, float dy, int isDeadly)
// {
//     if (blockCount >= MAX_BLOCKS)
//         return;
//     blocks[blockCount++] = (Block){x, y, w, h, isVisible, health, isFalling, isMoving, dx, dy, isDeadly};
// }

// void addPyramid(float centerX, float baseY, int layers, float w, float h, int health)
// {
//     for (int i = 0; i < layers; i++)
//     {
//         int count = layers - i;
//         float startX = centerX - (count * w) / 2;
//         for (int j = 0; j < count; j++)
//         {
//             addBlock(startX + j * w, baseY + i * h, w, h, 1, health, 0, 0, 0, 0, 0);
//         }
//     }
// }

// void addBlockGrid(float startX, float startY, int rows, int cols, float w, float h, int health)
// {
//     for (int i = 0; i < rows; i++)
//     {
//         for (int j = 0; j < cols; j++)
//         {
//             addBlock(startX + j * w, startY + i * h, w, h, 1, health, 0, 0, 0, 0, 0);
//         }
//     }
// }

// void addPerimeterGrid(float startX, float startY, int rows, int cols, float w, float h, int thickness, int health)
// {
//     for (int r = 0; r < rows; r++)
//     {
//         for (int c = 0; c < cols; c++)
//         {
//             bool isEdge = (r < thickness || r >= rows - thickness || c < thickness || c >= cols - thickness);
//             if (isEdge)
//             {
//                 float x = startX + c * w;
//                 float y = startY + r * h;
//                 addBlock(x, y, w, h, 1, health, 0, 0, 0, 0, 0);
//             }
//         }
//     }
// }

// void fallingBlock(float x, float y, float w, float h, int health, float dy, int isDeadly)
// {
//     addBlock(x, y, w, h, 1, health, 1, 0, 0, dy, isDeadly);
// }

// void movingBlocks(float x, float y, float w, float h, int health, float dx)
// {
//     addBlock(x, y, w, h, 1, health, 0, 1, dx, 0, 0);
// }

// void initBlocks1()
// {
//     blockCount = 0;
//     addPerimeterGrid(600, 350, 7, 9, BLOCK_WIDTH, BLOCK_HEIGHT, 2, 1);
//     float pyramidcenterX = 600 + 9 * BLOCK_WIDTH / 2;
//     float pyramidbaseY = 350 + 7 * BLOCK_HEIGHT;
//     addPyramid(pyramidcenterX, pyramidbaseY, 4, BLOCK_WIDTH, BLOCK_HEIGHT, 1);
// }

// void initBlocks2()
// {
//     blockCount = 0;
//     addBlockGrid(700, 350, 5, 3, BLOCK_WIDTH, BLOCK_HEIGHT, 1);
//     addPyramid(850, 350, 3, BLOCK_WIDTH, BLOCK_HEIGHT, 1);
//     movingBlocks(600, 500, BLOCK_WIDTH, BLOCK_HEIGHT, 1, 4);
//     fallingBlock(400, 800, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
//     fallingBlock(600, 800, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
//     fallingBlock(800, 600, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
//     fallingBlock(1000, 800, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4, 1);
//     fallingBlock(500, 350, BLOCK_WIDTH, BLOCK_HEIGHT, 1, 4, 1);
//     movingBlocks(1200, 600, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4);
//     movingBlocks(300, 600, BLOCK_WIDTH, BLOCK_HEIGHT, 1, 4);
//     movingBlocks(1000, 500, BLOCK_WIDTH, BLOCK_HEIGHT, 1, -4);
//     movingBlocks(400, 500, BLOCK_WIDTH, BLOCK_HEIGHT, 1, 4);
// }

// typedef struct
// {
//     char name[100];
//     int score;
// } Leader;

// Leader leaders[100];
// int leaderCount = 0;

// void loadLeaderboard()
// {
//     leaderCount = 0;
//     FILE *fp = fopen("bin\\assets\\leaderboard.txt", "r");
//     if (fp == NULL)
//         return;
//     while (fscanf(fp, "%s %d", leaders[leaderCount].name, &leaders[leaderCount].score) == 2)
//     {
//         leaderCount++;
//         if (leaderCount >= 100)
//             break;
//     }
//     fclose(fp);
// }

// void saveScore()
// {
//     FILE *file = fopen("bin\\assets\\leaderboard.txt", "a");
//     if (file)
//     {
//         fprintf(file, "%s %d\n", playerName, score);
//         fclose(file);
//     }
// }

// void showLeaderboard()
// {
//     FILE *file = fopen("bin\\assets\\leaderboard.txt", "r");
//     if (!file)
//     {
//         iText(600, 200, "No leaderboard data available.", GLUT_BITMAP_HELVETICA_18);
//         return;
//     }

//     Leader tempLeaders[100];
//     int count = 0;

//     while (fscanf(file, "%s %d", tempLeaders[count].name, &tempLeaders[count].score) == 2)
//     {
//         count++;
//         if (count >= 100)
//             break;
//     }
//     fclose(file);

//     if (count == 0)
//     {
//         iText(600, 200, "No leaderboard data yet.", GLUT_BITMAP_HELVETICA_18);
//         return;
//     }
//     for (int i = 0; i < count - 1; i++)
//     {
//         for (int j = i + 1; j < count; j++)
//         {
//             if (tempLeaders[j].score > tempLeaders[i].score)
//             {
//                 Leader temp = tempLeaders[i];
//                 tempLeaders[i] = tempLeaders[j];
//                 tempLeaders[j] = temp;
//             }
//         }
//     }
//     iSetColor(255, 255, 0);
//     iText(600, 800, "LEADERBOARD", GLUT_BITMAP_HELVETICA_18);
//     for (int i = 0; i < count && i < 5; i++)
//     {
//         char line[200];
//         sprintf(line, "%d.%s - %d", i + 1, tempLeaders[i].name, tempLeaders[i].score);
//         iText(600, 550 - i * 30, line, GLUT_BITMAP_HELVETICA_18);
//     }
// }

// void drawSlingshotPuller()
// {
//     int slingBaseX = 120, slingBaseY = 450;
//     int slingTopX = 120, slingTopY = 520;
//     int birdCenterX = (int)birds[currentBird].x + BIRD_WIDTH / 2;
//     int birdCenterY = (int)birds[currentBird].y + BIRD_HEIGHT / 2;

//     iSetColor(139, 69, 19);
//     iFilledRectangle(110, 420, 20, 100);
//     iSetColor(100, 50, 10);
//     iFilledRectangle(120, 450, 40, 10);

//     if (ready && !launched && birds[currentBird].active && dragging)
//     {
//         iSetColor(80, 40, 10);
//         iLine(slingBaseX, slingBaseY, dragX, dragY);
//         iLine(slingTopX, slingTopY, dragX, dragY);
//     }
//     else if (ready && !launched && birds[currentBird].active)
//     {
//         iSetColor(80, 40, 10);
//         iLine(slingBaseX, slingBaseY, birdCenterX, birdCenterY);
//         iLine(slingTopX, slingTopY, birdCenterX, birdCenterY);
//     }
// }

// void iDraw()
// {
//     iClear();

//     if (gameState == -1)
//     {
//         iShowImage(0, 0, "assets/images/coverS.bmp");
//         int r = 200 + rand() % 55;
//         int g = 50 + rand() % 200;
//         int b = 50 + rand() % 200;
//         iSetColor(r, g, b);
//         iText(WIN_W / 2 - 30, 60, "Loading...", GLUT_BITMAP_TIMES_ROMAN_24);
//     }
//     else if (gameState == 0)
//     {
//         iShowImage(0, 0, "assets/images/MenuCover.jpg");
//         iShowImage(510, 630, "assets/images/AngryBwritting.bmp");

//         int btnW = 200, btnH = 50, x = 660;
//         int y1 = 500, y2 = 400, y3 = 100, y4 = 300, y5 = 200;
//         iSetColor(0, 100, 0);
//         iFilledRectangle(x + 5, y1 - 5, btnW, btnH);
//         iSetColor(0, 200, 0);
//         iFilledRectangle(x, y1, btnW, btnH);
//         iSetColor(255, 255, 255);
//         iText(x + 50, y1 + 15, "START GAME", GLUT_BITMAP_HELVETICA_18);
//         iSetColor(0, 0, 100);
//         iFilledRectangle(x + 5, y2 - 5, btnW, btnH);
//         iSetColor(0, 0, 200);
//         iFilledRectangle(x, y2, btnW, btnH);
//         iSetColor(255, 255, 255);
//         iText(x + 50, y2 + 15, "LEADERBOARD", GLUT_BITMAP_HELVETICA_18);
//         iSetColor(100, 0, 0);
//         iFilledRectangle(x + 5, y3 - 5, btnW, btnH);
//         iSetColor(200, 0, 0);
//         iFilledRectangle(x, y3, btnW, btnH);
//         iSetColor(255, 255, 255);
//         iText(x + 75, y3 + 15, "EXIT", GLUT_BITMAP_HELVETICA_18);
//         iSetColor(100, 100, 0);
//         iFilledRectangle(x + 5, y4 - 5, btnW, btnH);
//         iSetColor(200, 200, 0);
//         iFilledRectangle(x, y4, btnW, btnH);
//         iSetColor(255, 255, 255);
//         iText(x + 50, y4 + 15, "CREDIT", GLUT_BITMAP_HELVETICA_18);
//         iSetColor(100, 0, 100);
//         iFilledRectangle(x + 5, y5 - 5, btnW, btnH);
//         iSetColor(200, 0, 200);
//         iFilledRectangle(x, y5, btnW, btnH);
//         iSetColor(255, 255, 255);
//         iText(x + 50, y5 + 15, "HELP", GLUT_BITMAP_HELVETICA_18);

//         if (enteringName)
//         {
//             iSetColor(0, 0, 0);
//             iFilledRectangle(0, 0, WIN_W, WIN_H);
//             iSetColor(255, 255, 255);
//             iText(WIN_W / 2 - 100, WIN_H / 2, "Enter your name: ", GLUT_BITMAP_HELVETICA_18);
//             iText(WIN_W / 2 - 100, WIN_H / 2 - 30, playerName, GLUT_BITMAP_HELVETICA_18);
//         }
//     }
//     else if (selectingBirds)
//     {
//         iSetColor(0, 0, 0);
//         iFilledRectangle(0, 0, WIN_W, WIN_H);
//         iSetColor(255, 255, 255);
//         char msg[128];
//         sprintf(msg, "Select bird for slot %d", birdSelectionIndex + 1);
//         iText(WIN_W / 2 - 100, WIN_H - 100, msg, GLUT_BITMAP_HELVETICA_18);

//         for (int i = 0; i < NUM_BIRDS; i++)
//         {
//             int bx = 300 + i * 200;
//             int by = WIN_H / 2;
//             iShowImage(bx, by, birdImages[i]);
//         }
//         iSetColor(255, 255, 0);
//         iText(200, 200, "Your bird order:", GLUT_BITMAP_HELVETICA_18);
//         for (int i = 0; i < birdSelectionIndex; i++)
//         {
//             iShowImage(400 + i * 70, 150, birdImages[selectedBirdTypes[i]]);
//         }
//     }
//     else if (gameState == 1 && (gameLevel == 1 || gameLevel == 2))
//     {
//         iShowImage(0, 0, "assets/images/groundImage2.bmp");
//         iShowImage(0, 350, "assets/images/skyImage.bmp");
//         iShowImage(1150, 330, "assets/images/tree.png");
//         iShowImage(0, 330, "assets/images/grassDecor.png");
//         iShowImage(400, 330, "assets/images/grassDecor.png");
//         iShowImage(800, 330, "assets/images/grassDecor.png");
//         iShowImage(1200, 330, "assets/images/grassDecor.png");

//         for (int i = 0; i < blockCount; i++)
//         {
//             if (blocks[i].isVisible)
//             {
//                 iShowImage((int)blocks[i].x, (int)blocks[i].y, "assets/images/blockImage.bmp");
//             }
//         }
//         for (int i = 0; i < NUM_BIRDS; i++)
//         {
//             if (birds[i].active)
//             {
//                 iShowImage((int)birds[i].x, (int)birds[i].y, birdImages[birds[i].type]);
//             }
//         }
//         drawSlingshotPuller();
//         iShowImage(100, 285, "assets/images/extractedCartoonSlingshotAdd.bmp.bmp");

//         if (ready && birds[currentBird].active && !dragging)
//         {
//             double rad = toRad(angle);
//             double vx = velocity * cos(rad);
//             double vy = velocity * sin(rad);
//             double px = 120, py = 450;
//             double t_step = 0.1;
//             double t_proj = 0;
//             int max_steps = 200;

//             for (int i = 0; i < max_steps; i++)
//             {
//                 double next_t = t_proj + t_step;
//                 double next_px = 120 + vx * next_t;
//                 double next_py = 450 + vy * next_t - 0.5 * g * next_t * next_t;

//                 if (next_py < 345)
//                     break;

//                 int hit = 0;
//                 for (int j = 0; j < blockCount; j++)
//                 {
//                     if (blocks[j].isVisible)
//                     {
//                         if (next_px + BIRD_WIDTH > blocks[j].x && next_px < blocks[j].x + blocks[j].width &&
//                             next_py + BIRD_HEIGHT > blocks[j].y && next_py < blocks[j].y + blocks[j].height)
//                         {
//                             hit = 1;
//                             break;
//                         }
//                     }
//                 }
//                 if (hit)
//                     break;

//                 iSetColor(255, 255, 0);
//                 iLine(px, py, next_px, next_py);

//                 px = next_px;
//                 py = next_py;
//                 t_proj = next_t;
//             }
//         }

//         int boxW = 220, boxH = 120;
//         int boxX = 1300;
//         int boxY = 720;

//         int r = 200 + rand() % 55;
//         int g = 50 + rand() % 200;
//         int b = 50 + rand() % 200;
//         iSetColor(r, g, b);
//         iFilledRectangle(boxX, boxY, boxW, boxH);
//         iSetColor(152, 79, 166);
//         iFilledRectangle(boxX + 10, boxY + 10, boxW - 20, boxH - 20);

//         char s1[32], s2[32];
//         sprintf(s1, "Angle: %.0f°", angle);
//         sprintf(s2, "Speed: %.0f", velocity);
//         iSetColor(255, 255, 255);
//         iText(boxX + 12, boxY + boxH - 10, s1, GLUT_BITMAP_HELVETICA_18);
//         iText(boxX + 12, boxY + boxH - 30, s2, GLUT_BITMAP_HELVETICA_18);

//         char scoreText[32];
//         sprintf(scoreText, "Score: %d", score);
//         iSetColor(255, 255, 255);
//         iText(boxX + 12, boxY + boxH - 50, scoreText, GLUT_BITMAP_HELVETICA_18);

//         char livesText[32];
//         sprintf(livesText, "Lives: %d", lives);
//         iSetColor(255, 255, 255);
//         iText(boxX + 12, boxY + boxH - 80, livesText, GLUT_BITMAP_HELVETICA_18);
//         char levelText[32];
//         sprintf(levelText, "Level: %d", gameLevel);
//         iText(boxX + 12, boxY + boxH - 110, levelText, GLUT_BITMAP_HELVETICA_18);

//         if (levelWon)
//         {
//             iSetColor(255, 255, 0);
//             iText(700, 500, "LEVEL COMPLETE!", GLUT_BITMAP_TIMES_ROMAN_24);
//             iText(700, 450, "Press R to reset", GLUT_BITMAP_HELVETICA_18);
//         }
//     }
//     else if (gameState == LEADERBOARD)
//     {
//         iSetColor(0, 0, 0);
//         iFilledRectangle(0, 0, WIN_W, WIN_H);
//         iShowImage(40, 0, "assets/images/LeaderBcover.bmp");
//         int r = 200 + rand() % 55;
//         int g = 50 + rand() % 200;
//         int b = 50 + rand() % 200;
//         iSetColor(r, g, b);
//         iText(330, 720, "LEADERBOARD", GLUT_BITMAP_TIMES_ROMAN_24);
//         iSetColor(0, 0, 0);
//         iFilledRectangle(300, 90, 900, 600);
//         showLeaderboard();
//         iSetColor(255, 255, 255);
//         iText(60, 60, "Press B to go back", GLUT_BITMAP_HELVETICA_18);
//     }
//     else if (gameState == 4)
//     {
//         iSetColor(73, 73, 156);
//         iFilledRectangle(0, 0, WIN_W, WIN_H);
//         iSetColor(255, 0, 0);
//         iText(600, 500, "GAME OVER!", GLUT_BITMAP_TIMES_ROMAN_24);
//         iText(600, 450, "Press R to restart or Q to quit", GLUT_BITMAP_HELVETICA_18);
//         iText(600, 400, "Lives: 0", GLUT_BITMAP_HELVETICA_18);
//     }
// }

// void ballChange()
// {
//     if (gameState != 1 || !launched || gameOver)
//         return;

//     t += 0.9;
//     double rad = toRad(angle);
//     double vx = velocity * cos(rad);
//     double vy = velocity * sin(rad);
//     birds[currentBird].x = 120 + vx * t;
//     birds[currentBird].y = 450 + vy * t - 0.5 * g * t * t;

//     // Block collision: bird continues flying after hit
//     for (int i = 0; i < blockCount; i++)
//     {
//         if (blocks[i].isVisible)
//         {
//             Block *b = &blocks[i];
//             if (birds[currentBird].x + BIRD_WIDTH > b->x && birds[currentBird].x < b->x + b->width &&
//                 birds[currentBird].y + BIRD_HEIGHT > b->y && birds[currentBird].y < b->y + b->height)
//             {
//                 b->hitPoints--;
//                 if (b->hitPoints <= 0)
//                 {
//                     b->isVisible = 0;
//                     score += 10;
//                 }
//             }
//         }
//     }

//     // Only end bird's flight when it touches the ground
//     if (birds[currentBird].y <= 345)
//     {
//         birds[currentBird].y = 345;
//         launched = false;
//         ready = false;
//         birds[currentBird].active = false;
//         currentBird++;
//         if (currentBird < NUM_BIRDS)
//         {
//             resetCurrentBird();
//         }
//         else
//         {
//             gameOver = true;
//             gameState = 4;
//         }
//         return;
//     }

//     allGone = true;
//     for (int i = 0; i < blockCount; i++)
//     {
//         if (blocks[i].isVisible)
//         {
//             allGone = false;
//             break;
//         }
//     }
//     if (allGone && !levelWon)
//     {
//         levelWon = true;
//         launched = false;
//         ready = false;
//         saveScore();
//     }
// }

// void updateBlockPositions()
// {
//     for (int i = 0; i < blockCount; i++)
//     {
//         if (!blocks[i].isVisible)
//             continue;

//         // Falling block
//         if (blocks[i].isFalling)
//         {
//             blocks[i].y += blocks[i].vy;
//             if (blocks[i].y <= 345)
//             {
//                 blocks[i].y = 345;
//                 blocks[i].vy = 0;
//                 blocks[i].isFalling = 0;
//             }
//         }
//         // Moving block
//         if (blocks[i].isMoving)
//         {
//             blocks[i].x += blocks[i].vx;
//             if (blocks[i].x <= 100 || blocks[i].x + blocks[i].width >= WIN_W)
//             {
//                 blocks[i].vx *= -1;
//             }
//             if (blocks[i].y <= 300 || blocks[i].y + blocks[i].height >= WIN_H)
//             {
//                 blocks[i].vy *= -1;
//             }
//         }
//     }
// }

// void coverTimerFunc()
// {
//     if (gameState == -1)
//     {
//         coverTimer++;
//         if (coverTimer >= 7)
//         {
//             gameState = 0;
//         }
//     }
// }

// void iMouse(int button, int state, int mx, int my)
// {
//     if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//     {
//         if (gameState == 0)
//         {
//             if (mx >= 660 && mx <= 860 && my >= 500 && my <= 550)
//             {
//                 enteringName = true;
//                 nameCharIndex = 0;
//                 playerName[0] = '\0';
//             }
//             else if (mx >= 660 && mx <= 860 && my >= 400 && my <= 450)
//             {
//                 gameState = LEADERBOARD;
//             }
//             else if (mx >= 660 && mx <= 860 && my >= 100 && my <= 150)
//             {
//                 exit(0);
//             }
//         }
//         else if (selectingBirds)
//         {
//             for (int i = 0; i < NUM_BIRDS; i++)
//             {
//                 int bx = 300 + i * 200;
//                 int by = WIN_H / 2;
//                 if (mx >= bx && mx <= bx + BIRD_WIDTH && my >= by && my <= by + BIRD_HEIGHT)
//                 {
//                     selectedBirdTypes[birdSelectionIndex] = i;
//                     birdSelectionIndex++;
//                     if (birdSelectionIndex == NUM_BIRDS)
//                     {
//                         selectingBirds = false;
//                         gameState = 1;
//                         gameLevel = 1;
//                         score = 0;
//                         lives = 5;
//                         initBlocks1();
//                         initBirds();
//                         resetCurrentBird();
//                         launched = false;
//                         ready = true;
//                     }
//                 }
//             }
//         }
//         else if (gameState == 1 && ready && !launched && birds[currentBird].active)
//         {
//             if (!dragging)
//             {
//                 launched = true;
//                 ready = false;
//                 t = 0;
//             }
//         }
//     }
//     if (gameState == 1 && ready && !launched && birds[currentBird].active)
//     {
//         int bx = (int)birds[currentBird].x + BIRD_WIDTH / 2;
//         int by = (int)birds[currentBird].y + BIRD_HEIGHT / 2;
//         if (abs(mx - bx) < 40 && abs(my - by) < 40)
//         {
//             dragging = true;
//             dragX = mx;
//             dragY = my;
//         }
//     }
//     if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
//     {
//         if (dragging)
//         {
//             int dx = 120 - dragX;
//             int dy = 450 - dragY;
//             double dist = sqrt(dx * dx + dy * dy);
//             angle = atan2(dy, dx) * 180.0 / M_PI;
//             if (angle < 0)
//                 angle += 360;
//             if (angle > 90)
//                 angle = 90;
//             if (angle < 0)
//                 angle = 0;
//             velocity = dist * 1.2;
//             if (velocity > 200)
//                 velocity = 200;
//             if (velocity < 10)
//                 velocity = 10;
//             launched = true;
//             ready = false;
//             t = 0;
//             dragging = false;
//         }
//     }
// }

// void iMouseMove(int mx, int my)
// {
//     if (dragging)
//     {
//         dragX = mx;
//         dragY = my;
//     }
// }

// void iMouseDrag(int mx, int my)
// {
//     if (dragging)
//     {
//         dragX = mx;
//         dragY = my;
//     }
// }

// void iMouseWheel(int dir, int mx, int my) {}

// void iKeyboard(unsigned char key)
// {
//     if (key == 'r')
//     {
//         currentBird = 0;
//         initBirds();
//         resetCurrentBird();
//         t = 0;
//         launched = false;
//         ready = true;
//         levelWon = false;
//         gameOver = false;
//         if (gameLevel == 2)
//             initBlocks2();
//         else
//             initBlocks1();
//     }
//     else if (key == 'q')
//     {
//         saveScore();
//         exit(0);
//     }
//     else if (key == 'b')
//     {
//         gameState = 0;
//         selectingBirds = false;
//     }

//     if (enteringName)
//     {
//         if (key == '\r')
//         {
//             enteringName = false;
//             selectingBirds = true;
//             birdSelectionIndex = 0;
//         }
//         else if (key == '\b' && nameCharIndex > 0)
//         {
//             playerName[--nameCharIndex] = '\0';
//         }
//         else if (nameCharIndex < 99 && ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9')))
//         {
//             playerName[nameCharIndex++] = key;
//             playerName[nameCharIndex] = '\0';
//         }
//         return;
//     }
// }

// void iSpecialKeyboard(unsigned char key)
// {
//     if (gameState == 1 && ready && !dragging)
//     {
//         if (key == GLUT_KEY_UP && angle < 90)
//             angle += 1;
//         else if (key == GLUT_KEY_DOWN && angle > 0)
//             angle -= 1;
//         else if (key == GLUT_KEY_RIGHT && velocity < 200)
//             velocity += 1;
//         else if (key == GLUT_KEY_LEFT && velocity > 10)
//             velocity -= 1;
//     }
//     if (key == GLUT_KEY_END)
//         exit(0);
// }

// int main(int argc, char *argv[])
// {
//     glutInit(&argc, argv);
//     iSetTimer(1000, coverTimerFunc);
//     iSetTimer(20, ballChange);
//     iSetTimer(20, updateBlockPositions);
//     srand(time(0));
//     initBlocks1();
//     for (int i = 0; i < NUM_BIRDS; i++)
//         selectedBirdTypes[i] = i;
//     initBirds();
//     iInitialize(WIN_W, WIN_H, "Angry Birds");
//     return 0;