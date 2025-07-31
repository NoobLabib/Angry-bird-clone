// // // #include "iGraphics.h"
// // // #include <math.h>
// // // #include <stdbool.h>
// // // #include <time.h>

// // // #define WIN_W 1550
// // // #define WIN_H 1000

// // // // Game state
// // // int gameState = -1;
// // // int coverTimer = 0;

// // // // Bird and physics
// // // double bird_x = 120, bird_y = 450;
// // // double velocity = 90; // initial speed
// // // double angle = 30;    // launch angle
// // // double g = 9.8;
// // // double t = 0;
// // // bool launched = false;
// // // bool ready = true;

// // // static double toRad(double deg) { return deg * M_PI / 180.0; }

// // // void iDraw()
// // // {
// // //     iClear();

// // //     if (gameState == -1)
// // //     {
// // //         // COVER SCREEN
// // //         // iSetColor(0, 0, 0);
// // //         // iFilledRectangle(0, 0, WIN_W, WIN_H);
// // //         iShowImage(0, 0, "assets/images/coverS.bmp");
// // //         iSetColor(209, 24, 203);
// // //         iText(WIN_W / 2 - 30, 60, "Loading...", GLUT_BITMAP_TIMES_ROMAN_24);
// // //     }

// // //     else if (gameState == 0)
// // //     {
// // //         // MAIN MENU
// // //         iSetColor(97, 148, 227);
// // //         iFilledRectangle(0, 0, WIN_W, WIN_H);

// // //         const char *title = "ANGRY BIRDS";
// // //         int titleX = 615, titleY = 600;
// // //         int spacing = 30;
// // //         for (int i = 0; title[i]; i++)
// // //         {
// // //             int r = 200 + rand() % 55;
// // //             int g = 50 + rand() % 200;
// // //             int b = 50 + rand() % 200;

// // //             iSetColor(r, g, b);
// // //             char ch[2] = {title[i], '\0'};
// // //             iText(titleX + i * spacing, titleY, ch, GLUT_BITMAP_TIMES_ROMAN_24);
// // //         }

// // //         int btnW = 200, btnH = 50, x = 660;
// // //         int y1 = 400, y2 = 300, y3 = 200;
// // //         // Start Game Button
// // //         iSetColor(0, 100, 0);
// // //         iFilledRectangle(x + 5, y1 - 5, btnW, btnH);
// // //         iSetColor(0, 200, 0);
// // //         iFilledRectangle(x, y1, btnW, btnH);
// // //         iSetColor(255, 255, 255);
// // //         iText(x + 50, y1 + 15, "START GAME", GLUT_BITMAP_HELVETICA_18);

// // //         iSetColor(0, 0, 100);
// // //         iFilledRectangle(x + 5, y2 - 5, btnW, btnH);
// // //         iSetColor(0, 0, 200);
// // //         iFilledRectangle(x, y2, btnW, btnH);
// // //         iSetColor(255, 255, 255);
// // //         iText(x + 70, y2 + 15, "HELP", GLUT_BITMAP_HELVETICA_18);
// // //         // Exit Button
// // //         iSetColor(100, 0, 0);
// // //         iFilledRectangle(x + 5, y3 - 5, btnW, btnH);
// // //         iSetColor(200, 0, 0);
// // //         iFilledRectangle(x, y3, btnW, btnH);
// // //         iSetColor(255, 255, 255);
// // //         iText(x + 75, y3 + 15, "EXIT", GLUT_BITMAP_HELVETICA_18);
// // //     }
// // //     // Gameplay
// // //     else if (gameState == 1)
// // //     {
// // //         iShowImage(0, 0, "assets/images/groundImage2.bmp");
// // //         iShowImage(0, 350, "assets/images/skyImage.bmp");
// // //         iShowImage(1150, 330, "assets/images/tree.png");
// // //         iShowImage(0, 330, "assets/images/grassDecor.png");
// // //         iShowImage(400, 330, "assets/images/grassDecor.png");
// // //         iShowImage(800, 330, "assets/images/grassDecor.png");
// // //         iShowImage(1200, 330, "assets/images/grassDecor.png");
// // //         iShowImage((int)bird_x, (int)bird_y, "assets/images/extractedCartoonBirdAdd.bmp");
// // //         iShowImage(100, 285, "assets/images/extractedCartoonSlingshotAdd.bmp.bmp");

// // //         if (ready)
// // //         {
// // //             double rad = toRad(angle),
// // //                    len = 150,
// // //                    ex = bird_x + len * cos(rad),
// // //                    ey = bird_y + len * sin(rad);

// // //             iSetColor(0, 100, 255);
// // //             iLine(bird_x, bird_y, ex, ey);
// // //         }
// // //         // HUD
// // //         int boxW = 250, boxH = 70;
// // //         int boxX = WIN_W - 10 - boxW;
// // //         int boxY = WIN_H - 10 - boxH;
// // //         iSetColor(0, 0, 0);
// // //         iFilledRectangle(boxX, boxY, boxW, boxH);
// // //         // HUD text
// // //         char s1[32], s2[32];
// // //         sprintf(s1, "Angle: %.0f°", angle);
// // //         sprintf(s2, "Speed: %.0f", velocity);
// // //         iSetColor(255, 255, 255);
// // //         iText(boxX + 10, boxY + boxH - 20, s1, GLUT_BITMAP_HELVETICA_18);
// // //         iText(boxX + 10, boxY + boxH - 45, s2, GLUT_BITMAP_HELVETICA_18);
// // //     }
// // //     else if (gameState == 2)
// // //     {
// // //         iSetColor(0, 0, 0);
// // //         iFilledRectangle(0, 0, WIN_W, WIN_H);
// // //         // Help text
// // //         iSetColor(255, 255, 255);
// // //         iText(100, 900, "HELP");
// // //         iText(100, 850, "Use arrow keys to set angle and speed.");
// // //         iText(100, 800, "Left click to shoot. R to reset. Q to quit.");
// // //         iText(100, 750, "B to return to menu.");
// // //     }
// // // }

// // // // void iDraw()
// // // // {
// // // //     iClear();
// // // //     if (gameState == 0)
// // // //     {
// // // //         // Background sky blue
// // // //         iSetColor(135, 206, 250);
// // // //         iFilledRectangle(0, 0, WIN_W, WIN_H);
// // // //         // Fancy Title: ANGRY BIRDS (Capitalized, Colored Letters)
// // // //         const char *title = "ANGRY BIRDS";
// // // //         int titleX = 615, titleY = 600;
// // // //         int spacing = 30;
// // // //         for (int i = 0; title[i]; i++)
// // // //         {
// // // //             int r = 200 + rand() % 55;
// // // //             int g = 50 + rand() % 200;
// // // //             int b = 50 + rand() % 200;

// // // //             iSetColor(r, g, b);
// // // //             char ch[2] = {title[i], '\0'};
// // // //             iText(titleX + i * spacing, titleY, ch, GLUT_BITMAP_TIMES_ROMAN_24);
// // // //         }
// // // //         // Buttons
// // // //         int btnW = 200, btnH = 50, x = 660;
// // // //         int y1 = 400, y2 = 300, y3 = 200;

// // // //         // Start
// // // //         iSetColor(0, 100, 0);
// // // //         iFilledRectangle(x + 5, y1 - 5, btnW, btnH);
// // // //         iSetColor(0, 200, 0);
// // // //         iFilledRectangle(x, y1, btnW, btnH);
// // // //         iSetColor(255, 255, 255);
// // // //         iText(x + 50, y1 + 15, "START GAME", GLUT_BITMAP_HELVETICA_18);

// // // //         // Help
// // // //         iSetColor(0, 0, 100);
// // // //         iFilledRectangle(x + 5, y2 - 5, btnW, btnH);
// // // //         iSetColor(0, 0, 200);
// // // //         iFilledRectangle(x, y2, btnW, btnH);
// // // //         iSetColor(255, 255, 255);
// // // //         iText(x + 70, y2 + 15, "HELP", GLUT_BITMAP_HELVETICA_18);

// // // //         // Exit
// // // //         iSetColor(100, 0, 0);
// // // //         iFilledRectangle(x + 5, y3 - 5, btnW, btnH);
// // // //         iSetColor(200, 0, 0);
// // // //         iFilledRectangle(x, y3, btnW, btnH);
// // // //         iSetColor(255, 255, 255);
// // // //         iText(x + 75, y3 + 15, "EXIT", GLUT_BITMAP_HELVETICA_18);
// // // //     }

// // // //     else if (gameState == 1)
// // // //     {
// // // //         // Gameplay
// // // //         iShowImage(0, 0, "assets/images/cartoongroundAdd.bmp");
// // // //         iShowImage(0, 350, "assets/images/cartoonskyAdd.bmp");
// // // //         iShowImage((int)bird_x, (int)bird_y, "assets/images/extractedCartoonBirdAdd.bmp");
// // // //         iShowImage(100, 285, "assets/images/extractedCartoonSlingshotAdd.bmp.bmp");

// // // //         if (ready)
// // // //         {
// // // //             double rad = toRad(angle),
// // // //                    len = 150,
// // // //                    ex = bird_x + len * cos(rad),
// // // //                    ey = bird_y + len * sin(rad);

// // // //             iSetColor(0, 100, 255);
// // // //             iLine(bird_x, bird_y, ex, ey);
// // // //         }

// // // //         // HUD
// // // //         int boxW = 250, boxH = 70;
// // // //         int boxX = WIN_W - 10 - boxW;
// // // //         int boxY = WIN_H - 10 - boxH;
// // // //         iSetColor(0, 0, 0);
// // // //         iFilledRectangle(boxX, boxY, boxW, boxH);

// // // //         char s1[32], s2[32];
// // // //         sprintf(s1, "Angle: %.0f°", angle);
// // // //         sprintf(s2, "Speed: %.0f", velocity);
// // // //         iSetColor(255, 255, 255);
// // // //         iText(boxX + 10, boxY + boxH - 20, s1, GLUT_BITMAP_HELVETICA_18);
// // // //         iText(boxX + 10, boxY + boxH - 45, s2, GLUT_BITMAP_HELVETICA_18);
// // // //     }
// // // //     else if (gameState == 2)
// // // //     {
// // // //         iSetColor(0, 0, 0);
// // // //         iFilledRectangle(0, 0, WIN_W, WIN_H);

// // // //         iSetColor(255, 255, 255);
// // // //         iText(100, 900, "HELP");
// // // //         iText(100, 850, "Use arrow keys to set angle and speed.");
// // // //         iText(100, 800, "Left click to shoot. R to reset. Q to quit.");
// // // //         iText(100, 750, "B to return to menu.");
// // // //     }
// // // // }

// // // void ballChange()
// // // {
// // //     if (gameState != 1 || !launched)
// // //         return;
// // //     // Update physics
// // //     t += 0.7;
// // //     double rad = toRad(angle);
// // //     bird_x = 120 + velocity * cos(rad) * t;
// // //     bird_y = 450 + velocity * sin(rad) * t - 0.5 * g * t * t;

// // //     // Land
// // //     if (bird_y <= 345)
// // //     {
// // //         bird_y = 345;
// // //         launched = false;
// // //         ready = false;
// // //     }
// // // }
// // // void iMouse(int button, int state, int mx, int my)
// // // {
// // //     if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
// // //     {
// // //         // Menu state
// // //         if (gameState == 0)
// // //         {
// // //             if (mx >= 660 && mx <= 860 && my >= 400 && my <= 450)
// // //             {
// // //                 gameState = 1; // START GAME
// // //                 launched = false;
// // //                 ready = true;
// // //                 bird_x = 120;
// // //                 bird_y = 450;
// // //                 t = 0;
// // //             }
// // //             else if (mx >= 660 && mx <= 860 && my >= 300 && my <= 350)
// // //             {
// // //                 gameState = 2; // HELP
// // //             }
// // //             else if (mx >= 660 && mx <= 860 && my >= 200 && my <= 250)
// // //             {
// // //                 exit(0); // EXIT
// // //             }
// // //         }

// // //         // Launch bird in Game screen
// // //         else if (gameState == 1 && ready && !launched)
// // //         {
// // //             launched = true;
// // //             ready = false;
// // //             t = 0;
// // //         }
// // //     }
// // // }

// // // void iKeyboard(unsigned char key)
// // // {
// // //     if (key == 'r')
// // //     {
// // //         bird_x = 120;
// // //         bird_y = 450;
// // //         t = 0;
// // //         launched = false;
// // //         ready = true;
// // //     }
// // //     else if (key == 'q')
// // //     {
// // //         exit(0);
// // //     }
// // //     else if (key == 'b') // back to menu
// // //     {
// // //         gameState = 0;
// // //     }
// // // }

// // // void iSpecialKeyboard(unsigned char key)
// // // {
// // //     if (gameState == 1 && ready)
// // //     {
// // //         if (key == GLUT_KEY_UP && angle < 90)
// // //             angle += 1;
// // //         else if (key == GLUT_KEY_DOWN && angle > 0)
// // //             angle -= 1;
// // //         else if (key == GLUT_KEY_RIGHT && velocity < 200)
// // //             velocity += 1;
// // //         else if (key == GLUT_KEY_LEFT && velocity > 10)
// // //             velocity -= 1;
// // //     }
// // //     if (key == GLUT_KEY_END)
// // //         exit(0);
// // // }

// // // // Timer function to handle cover screen delay
// // // // This will switch from the cover screen to the main menu after a delay
// // // void coverTimerFunc()
// // // {
// // //     if (gameState == -1)
// // //     {
// // //         coverTimer++;
// // //         if (coverTimer >= 7)
// // //         {
// // //             gameState = 0;
// // //         }
// // //     }
// // // }

// // // void iMouseMove(int mx, int my) {}
// // // void iMouseDrag(int mx, int my) {}
// // // void iMouseWheel(int dir, int mx, int my) {}

// // // int main(int argc, char *argv[])
// // // {
// // //     glutInit(&argc, argv);
// // //     iSetTimer(1000, coverTimerFunc); // Cover screen timer
// // //     iSetTimer(20, ballChange);
// // //     srand(time(0));
// // //     iInitialize(WIN_W, WIN_H, "Angry Birds Clone");
// // //     return 0;
// // // }

// // // // // #include "iGraphics.h"
// // // // // #include <math.h>
// // // // // #include <stdbool.h>

// // // // // #define WIN_W 1000
// // // // // #define WIN_H 1000

// // // // // // Bird & Physics
// // // // // double bird_x = 120, bird_y = 450;
// // // // // double velocity = 70; // launch speed
// // // // // double angle = 30;    // launch angle in degrees
// // // // // double g = 9.8;
// // // // // double t = 0;
// // // // // bool launched = false;
// // // // // bool ready = true; // true = show aim UI

// // // // // static double toRad(double deg) { return deg * M_PI / 180.0; }

// // // // // void iDraw()
// // // // // {
// // // // //     iClear();

// // // // //     // Show background images directly
// // // // //     iShowImage(0, 0, "assets/images/cartoongroundAdd.bmp");
// // // // //     iShowImage(0, 350, "assets/images/cartoonskyAdd.bmp");
// // // // //     iShowImage(120, 400, "assets/images/cartoonslingshotAdd.bmp.bmp");
// // // // //     iShowImage((int)bird_x, (int)bird_y, "assets/images/cartoonbirdAdd.bmp");

// // // // //     // Trajectory line (blue) only when ready
// // // // //     if (ready)
// // // // //     {
// // // // //         double rad = toRad(angle),
// // // // //                len = 150,
// // // // //                ex = bird_x + len * cos(rad),
// // // // //                ey = bird_y + len * sin(rad);

// // // // //         iSetColor(0, 100, 255);
// // // // //         iLine(bird_x, bird_y, ex, ey);
// // // // //     }

// // // // //     // HUD box in top‑right
// // // // //     int boxW = 250, boxH = 70;
// // // // //     int boxX = WIN_W - 10 - boxW;
// // // // //     int boxY = WIN_H - 10 - boxH;
// // // // //     iSetColor(0, 0, 0);
// // // // //     iFilledRectangle(boxX, boxY, boxW, boxH);

// // // // //     // HUD text
// // // // //     char s1[32], s2[32];
// // // // //     sprintf(s1, "Angle: %.0f°", angle);
// // // // //     sprintf(s2, "Speed: %.0f", velocity);
// // // // //     iSetColor(255, 255, 255);
// // // // //     iText(boxX + 10, boxY + boxH - 20, s1, GLUT_BITMAP_HELVETICA_18);
// // // // //     iText(boxX + 10, boxY + boxH - 45, s2, GLUT_BITMAP_HELVETICA_18);
// // // // // }

// // // // // void ballChange()
// // // // // {
// // // // //     if (!launched)
// // // // //         return;

// // // // //     t += 0.15;
// // // // //     double rad = toRad(angle);
// // // // //     bird_x = 120 + velocity * cos(rad) * t;
// // // // //     bird_y = 450 + velocity * sin(rad) * t - 0.5 * g * t * t;

// // // // //     // Land on ground (y = 200)
// // // // //     if (bird_y <= 350)
// // // // //     {
// // // // //         bird_y = 350;
// // // // //         launched = false;
// // // // //         ready = false;
// // // // //     }
// // // // // }

// // // // // void iMouse(int button, int state, int mx, int my)
// // // // // {
// // // // //     if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && ready)
// // // // //     {
// // // // //         launched = true;
// // // // //         ready = false;
// // // // //         t = 0;
// // // // //     }
// // // // // }

// // // // // void iKeyboard(unsigned char key)
// // // // // {
// // // // //     if (key == 'r')
// // // // //     {
// // // // //         // reset for next shot
// // // // //         bird_x = 120;
// // // // //         bird_y = 450;
// // // // //         t = 0;
// // // // //         launched = false;
// // // // //         ready = true;
// // // // //     }
// // // // //     else if (key == 'q')
// // // // //         exit(0);
// // // // // }

// // // // // void iSpecialKeyboard(unsigned char key)
// // // // // {
// // // // //     if (ready)
// // // // //     {
// // // // //         if (key == GLUT_KEY_UP && angle < 90)
// // // // //             angle += 1;
// // // // //         if (key == GLUT_KEY_DOWN && angle > 0)
// // // // //             angle -= 1;
// // // // //         if (key == GLUT_KEY_RIGHT && velocity < 200)
// // // // //             velocity += 1;
// // // // //         if (key == GLUT_KEY_LEFT && velocity > 10)
// // // // //             velocity -= 1;
// // // // //     }
// // // // //     if (key == GLUT_KEY_END)
// // // // //         exit(0);
// // // // // }

// // // // // void iMouseMove(int mx, int my) {}
// // // // // void iMouseDrag(int mx, int my) {}
// // // // // void iMouseWheel(int dir, int mx, int my) {}

// // // // // int main(int argc, char *argv[])
// // // // // {
// // // // //     glutInit(&argc, argv);
// // // // //     iSetTimer(20, ballChange); // ~50 FPS
// // // // //     iInitialize(WIN_W, WIN_H, "Angry Birds");
// // // // //     return 0;
// // // // // }

// // // // // #include "iGraphics.h"
// // // // // #include <math.h>
// // // // // #include <stdbool.h>

// // // // // #define WIN_W 1000
// // // // // #define WIN_H 1000

// // // // // // Game state
// // // // // int gameState = 0;

// // // // // // Bird and physics
// // // // // double bird_x = 120, bird_y = 450;
// // // // // double init_x = 120, init_y = 450;
// // // // // double velX = 0, velY = 0;
// // // // // double g = 0.5;
// // // // // bool isLaunched = false;
// // // // // bool isDragging = false;
// // // // // int dragStartX = 0, dragStartY = 0;

// // // // // // Converts degrees to radians
// // // // // static double toRad(double deg) { return deg * M_PI / 180.0; }

// // // // // void iDraw()
// // // // // {
// // // // //     iClear();

// // // // //     if (gameState == 0)
// // // // //     {
// // // // //         // Main Menu
// // // // //         iSetColor(135, 206, 235);
// // // // //         iFilledRectangle(0, 0, WIN_W, WIN_H);

// // // // //         iSetColor(255, 255, 255);
// // // // //         iText(420, 550, "Angry Birds", GLUT_BITMAP_TIMES_ROMAN_24);

// // // // //         iSetColor(0, 200, 0);
// // // // //         iFilledRectangle(400, 400, 200, 50);
// // // // //         iSetColor(255, 255, 255);
// // // // //         iText(450, 420, "Start Game");

// // // // //         iSetColor(0, 0, 200);
// // // // //         iFilledRectangle(400, 300, 200, 50);
// // // // //         iSetColor(255, 255, 255);
// // // // //         iText(460, 320, "Help");

// // // // //         iSetColor(200, 0, 0);
// // // // //         iFilledRectangle(400, 200, 200, 50);
// // // // //         iSetColor(255, 255, 255);
// // // // //         iText(460, 220, "Exit");
// // // // //     }
// // // // //     else if (gameState == 1)
// // // // //     {
// // // // //         // Gameplay
// // // // //         iShowImage(0, 0, "assets/images/cartoongroundAdd.bmp");
// // // // //         iShowImage(0, 350, "assets/images/cartoonskyAdd.bmp");
// // // // //         iShowImage(120, 400, "assets/images/cartoonslingshotAdd.bmp");
// // // // //         iShowImage((int)bird_x, (int)bird_y, "assets/images/cartoonbirdAdd.bmp");

// // // // //         // Show drag line
// // // // //         if (isDragging)
// // // // //         {
// // // // //             iSetColor(0, 0, 255);
// // // // //             iLine(bird_x, bird_y, dragStartX, dragStartY);
// // // // //         }

// // // // //         // HUD
// // // // //         int boxW = 250, boxH = 60;
// // // // //         int boxX = WIN_W - 10 - boxW;
// // // // //         int boxY = WIN_H - 10 - boxH;
// // // // //         iSetColor(0, 0, 0);
// // // // //         iFilledRectangle(boxX, boxY, boxW, boxH);

// // // // //         char s1[32], s2[32];
// // // // //         sprintf(s1, "VelX: %.1f", velX);
// // // // //         sprintf(s2, "VelY: %.1f", velY);
// // // // //         iSetColor(255, 255, 255);
// // // // //         iText(boxX + 10, boxY + boxH - 20, s1, GLUT_BITMAP_HELVETICA_18);
// // // // //         iText(boxX + 10, boxY + boxH - 45, s2, GLUT_BITMAP_HELVETICA_18);
// // // // //     }
// // // // //     else if (gameState == 2)
// // // // //     {
// // // // //         iSetColor(0, 0, 0);
// // // // //         iFilledRectangle(0, 0, WIN_W, WIN_H);
// // // // //         iSetColor(255, 255, 255);
// // // // //         iText(100, 900, "HELP");
// // // // //         iText(100, 850, "Use mouse to pull and release the bird.");
// // // // //         iText(100, 800, "Use R to reset. Q to quit.");
// // // // //     }
// // // // // }

// // // // // void ballChange()
// // // // // {
// // // // //     if (gameState != 1 || !isLaunched)
// // // // //         return;

// // // // //     velY -= g;
// // // // //     bird_x += velX;
// // // // //     bird_y += velY;

// // // // //     // Stop at ground level
// // // // //     if (bird_y <= 350)
// // // // //     {
// // // // //         bird_y = 350;
// // // // //         isLaunched = false;
// // // // //     }
// // // // // }

// // // // // void iMouse(int button, int state, int mx, int my)
// // // // // {
// // // // //     // Main menu click
// // // // //     if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && gameState == 0)
// // // // //     {
// // // // //         if (mx >= 400 && mx <= 600 && my >= 400 && my <= 450)
// // // // //             gameState = 1;
// // // // //         else if (mx >= 400 && mx <= 600 && my >= 300 && my <= 350)
// // // // //             gameState = 2;
// // // // //         else if (mx >= 400 && mx <= 600 && my >= 200 && my <= 250)
// // // // //             exit(0);
// // // // //     }

// // // // //     // Drag start
// // // // //     if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !isLaunched && gameState == 1)
// // // // //     {
// // // // //         if (sqrt((mx - bird_x) * (mx - bird_x) + (my - bird_y) * (my - bird_y)) <= 30)
// // // // //         {
// // // // //             isDragging = true;
// // // // //             dragStartX = mx;
// // // // //             dragStartY = my;
// // // // //         }
// // // // //     }

// // // // //     // Release bird
// // // // //     if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && isDragging)
// // // // //     {
// // // // //         isDragging = false;
// // // // //         isLaunched = true;

// // // // //         float powerFactor = 0.5;
// // // // //         velX = (dragStartX - bird_x) * powerFactor;
// // // // //         velY = (dragStartY - bird_y) * powerFactor;
// // // // //     }
// // // // // }

// // // // // void iKeyboard(unsigned char key)
// // // // // {
// // // // //     if (key == 'r' || key == 'R')
// // // // //     {
// // // // //         // Reset bird
// // // // //         bird_x = init_x;
// // // // //         bird_y = init_y;
// // // // //         velX = velY = 0;
// // // // //         isLaunched = false;
// // // // //         isDragging = false;
// // // // //     }
// // // // //     else if (key == 'q' || key == 'Q')
// // // // //     {
// // // // //         exit(0);
// // // // //     }
// // // // //     else if (key == 'b') // Back to menu from help
// // // // //     {
// // // // //         gameState = 0;
// // // // //     }
// // // // // }

// // // // // void iSpecialKeyboard(unsigned char key)
// // // // // {
// // // // //     if (key == GLUT_KEY_END)
// // // // //         exit(0);
// // // // // }

// // // // // void iMouseMove(int mx, int my) {}
// // // // // void iMouseDrag(int mx, int my) {}
// // // // // void iMouseWheel(int dir, int mx, int my) {}

// // // // // int main(int argc, char *argv[])
// // // // // {
// // // // //     glutInit(&argc, argv);
// // // // //     iSetTimer(20, ballChange);
// // // // //     iInitialize(WIN_W, WIN_H, "Angry Birds");
// // // // //     return 0;
// // // // // }

// // // // #include "iGraphics.h"
// // // // #include <math.h>
// // // // #include <stdbool.h>
// // // // #include <time.h>

// // // // #define WIN_W 1000
// // // // #define WIN_H 1000

// // // // // Game state
// // // // int gameState = 0;

// // // // // Bird and physics
// // // // double bird_x = 120, bird_y = 450;
// // // // double velocity = 70; // initial speed
// // // // double angle = 30;    // launch angle
// // // // double g = 9.8;
// // // // double t = 0;
// // // // bool launched = false;
// // // // bool ready = true;

// // // // static double toRad(double deg) { return deg * M_PI / 180.0; }

// // // // void iDraw()
// // // // {
// // // //     iClear();

// // // //     // if (gameState == 0)
// // // //     // {
// // // //     //     // Main Menu
// // // //     //     iSetColor(135, 206, 235);
// // // //     //     iFilledRectangle(0, 0, WIN_W, WIN_H);

// // // //     //     iSetColor(255, 255, 255);
// // // //     //     iText(370, 600, "Angry Birds", GLUT_BITMAP_TIMES_ROMAN_24);

// // // //     //     iSetColor(0, 200, 0);
// // // //     //     iFilledRectangle(400, 400, 200, 50);
// // // //     //     iSetColor(255, 255, 255);
// // // //     //     iText(450, 420, "Start Game");

// // // //     //     iSetColor(0, 0, 200);
// // // //     //     iFilledRectangle(400, 300, 200, 50);
// // // //     //     iSetColor(255, 255, 255);
// // // //     //     iText(460, 320, "Help");

// // // //     //     iSetColor(200, 0, 0);
// // // //     //     iFilledRectangle(400, 200, 200, 50);
// // // //     //     iSetColor(255, 255, 255);
// // // //     //     iText(460, 220, "Exit");
// // // //     // // }
// // // //     // if (gameState == 0)
// // // //     // {
// // // //     //     // Background sky blue
// // // //     //     iSetColor(135, 206, 250);
// // // //     //     iFilledRectangle(0, 0, WIN_W, WIN_H);

// // // //     //     // Fancy Title: ANGRY BIRDS (Capitalized, Colored Letters)
// // // //     //     const char *title = "ANGRY BIRDS";
// // // //     //     int titleX = 280, titleY = 750;
// // // //     //     int spacing = 30;
// // // //     //     for (int i = 0; title[i]; i++)
// // // //     //     {
// // // //     //         int r = 200 + rand() % 55;
// // // //     //         int g = 50 + rand() % 200;
// // // //     //         int b = 50 + rand() % 200;

// // // //     //         iSetColor(r, g, b);
// // // //     //         char ch[2] = {title[i], '\0'};
// // // //     //         iText(titleX + i * spacing, titleY, ch, GLUT_BITMAP_TIMES_ROMAN_24);
// // // //     //     }

// // // //     //     // Button Shadow and Style Setup
// // // //     //     int btnW = 200, btnH = 50, x = 400;
// // // //     //     int y1 = 400, y2 = 300, y3 = 200;

// // // //     //     // Start Game Button
// // // //     //     iSetColor(0, 100, 0); // Shadow
// // // //     //     iFilledRectangle(x + 5, y1 - 5, btnW, btnH);
// // // //     //     iSetColor(0, 200, 0); // Main button
// // // //     //     iFilledRectangle(x, y1, btnW, btnH);
// // // //     //     iSetColor(255, 255, 255);
// // // //     //     iText(x + 50, y1 + 15, "START GAME", GLUT_BITMAP_HELVETICA_18);

// // // //     //     // Help Button
// // // //     //     iSetColor(0, 0, 100); // Shadow
// // // //     //     iFilledRectangle(x + 5, y2 - 5, btnW, btnH);
// // // //     //     iSetColor(0, 0, 200);
// // // //     //     iFilledRectangle(x, y2, btnW, btnH);
// // // //     //     iSetColor(255, 255, 255);
// // // //     //     iText(x + 70, y2 + 15, "HELP", GLUT_BITMAP_HELVETICA_18);

// // // //     //     // Exit Button
// // // //     //     iSetColor(100, 0, 0); // Shadow
// // // //     //     iFilledRectangle(x + 5, y3 - 5, btnW, btnH);
// // // //     //     iSetColor(200, 0, 0);
// // // //     //     iFilledRectangle(x, y3, btnW, btnH);
// // // //     //     iSetColor(255, 255, 255);
// // // //     //     iText(x + 75, y3 + 15, "EXIT", GLUT_BITMAP_HELVETICA_18);
// // // //     // }

// // // //     if (gameState == 0)
// // // //     {
// // // //         // Background sky blue
// // // //         iSetColor(135, 206, 250);
// // // //         iFilledRectangle(0, 0, WIN_W, WIN_H);

// // // //         // // Fancy, Centered Big Title
// // // //         // const char *title = "ANGRY BIRDS";
// // // //         // int titleX = WIN_W / 2 - 200;
// // // //         // int titleY = WIN_H - 150;
// // // //         // int spacing = 40;
// // // //         // for (int i = 0; title[i]; i++)
// // // //         // {
// // // //         //     int r = 200 + rand() % 55;
// // // //         //     int g = 50 + rand() % 200;
// // // //         //     int b = 50 + rand() % 200;
// // // //         //     iSetColor(r, g, b);
// // // //         //     char ch[2] = {title[i], '\0'};
// // // //         //     iText(titleX + i * spacing, titleY, ch, GLUT_BITMAP_TIMES_ROMAN_24);
// // // //         // }

// // // //         // Fancy, Centered Big Title (Larger size via multiple text calls)
// // // //         // Fancy Title: ANGRY BIRDS (Capitalized, Colored Letters)
// // // //         const char *title = "ANGRY BIRDS";
// // // //         int titleX = 350, titleY = 600;
// // // //         int spacing = 30;
// // // //         for (int i = 0; title[i]; i++)
// // // //         {
// // // //             int r = 200 + rand() % 55;
// // // //             int g = 50 + rand() % 200;
// // // //             int b = 50 + rand() % 200;

// // // //             iSetColor(r, g, b);
// // // //             char ch[2] = {title[i], '\0'};
// // // //             iText(titleX + i * spacing, titleY, ch, GLUT_BITMAP_TIMES_ROMAN_24);
// // // //         }
// // // //         // const char *title = "ANGRY BIRDS";
// // // //         // int textWidth = 500; // Approx width of whole title
// // // //         // int titleX = (WIN_W - textWidth) / 2;
// // // //         // int titleY = WIN_H - 150;
// // // //         // iSetColor(255, 0, 0);
// // // //         // iText(titleX, titleY, title, GLUT_BITMAP_TIMES_ROMAN_24);
// // // //         // iText(titleX, titleY + 30, title, GLUT_BITMAP_HELVETICA_18); // make thicker look

// // // //         // Buttons
// // // //         int btnW = 200, btnH = 50, x = 400;
// // // //         int y1 = 400, y2 = 300, y3 = 200;

// // // //         // Start
// // // //         iSetColor(0, 100, 0);
// // // //         iFilledRectangle(x + 5, y1 - 5, btnW, btnH);
// // // //         iSetColor(0, 200, 0);
// // // //         iFilledRectangle(x, y1, btnW, btnH);
// // // //         iSetColor(255, 255, 255);
// // // //         iText(x + 50, y1 + 15, "START GAME", GLUT_BITMAP_HELVETICA_18);

// // // //         // Help
// // // //         iSetColor(0, 0, 100);
// // // //         iFilledRectangle(x + 5, y2 - 5, btnW, btnH);
// // // //         iSetColor(0, 0, 200);
// // // //         iFilledRectangle(x, y2, btnW, btnH);
// // // //         iSetColor(255, 255, 255);
// // // //         iText(x + 70, y2 + 15, "HELP", GLUT_BITMAP_HELVETICA_18);

// // // //         // Exit
// // // //         iSetColor(100, 0, 0);
// // // //         iFilledRectangle(x + 5, y3 - 5, btnW, btnH);
// // // //         iSetColor(200, 0, 0);
// // // //         iFilledRectangle(x, y3, btnW, btnH);
// // // //         iSetColor(255, 255, 255);
// // // //         iText(x + 75, y3 + 15, "EXIT", GLUT_BITMAP_HELVETICA_18);
// // // //     }

// // // //     else if (gameState == 1)
// // // //     {
// // // //         // Gameplay
// // // //         iShowImage(0, 0, "assets/images/cartoongroundAdd.bmp");
// // // //         iShowImage(0, 350, "assets/images/cartoonskyAdd.bmp");
// // // //         iShowImage((int)bird_x, (int)bird_y, "assets/images/extractedCartoonBirdAdd.bmp");
// // // //         iShowImage(100, 285, "assets/images/extractedCartoonSlingshotAdd.bmp.bmp");

// // // //         if (ready)
// // // //         {
// // // //             double rad = toRad(angle),
// // // //                    len = 150,
// // // //                    ex = bird_x + len * cos(rad),
// // // //                    ey = bird_y + len * sin(rad);

// // // //             iSetColor(0, 100, 255);
// // // //             iLine(bird_x, bird_y, ex, ey);
// // // //         }

// // // //         // HUD
// // // //         int boxW = 250, boxH = 70;
// // // //         int boxX = WIN_W - 10 - boxW;
// // // //         int boxY = WIN_H - 10 - boxH;
// // // //         iSetColor(0, 0, 0);
// // // //         iFilledRectangle(boxX, boxY, boxW, boxH);

// // // //         char s1[32], s2[32];
// // // //         sprintf(s1, "Angle: %.0f°", angle);
// // // //         sprintf(s2, "Speed: %.0f", velocity);
// // // //         iSetColor(255, 255, 255);
// // // //         iText(boxX + 10, boxY + boxH - 20, s1, GLUT_BITMAP_HELVETICA_18);
// // // //         iText(boxX + 10, boxY + boxH - 45, s2, GLUT_BITMAP_HELVETICA_18);
// // // //     }
// // // //     else if (gameState == 2)
// // // //     {
// // // //         iSetColor(0, 0, 0);
// // // //         iFilledRectangle(0, 0, WIN_W, WIN_H);

// // // //         iSetColor(255, 255, 255);
// // // //         iText(100, 900, "HELP");
// // // //         iText(100, 850, "Use arrow keys to set angle and speed.");
// // // //         iText(100, 800, "Left click to shoot. R to reset. Q to quit.");
// // // //         iText(100, 750, "B to return to menu.");
// // // //     }
// // // // }

// // // // void ballChange()
// // // // {
// // // //     if (gameState != 1 || !launched)
// // // //         return;

// // // //     t += 0.15;
// // // //     double rad = toRad(angle);
// // // //     bird_x = 120 + velocity * cos(rad) * t;
// // // //     bird_y = 450 + velocity * sin(rad) * t - 0.5 * g * t * t;

// // // //     // Land
// // // //     if (bird_y <= 345)
// // // //     {
// // // //         bird_y = 345;
// // // //         launched = false;
// // // //         ready = false;
// // // //     }
// // // // }

// // // // // void iMouse(int button, int state, int mx, int my)
// // // // // {
// // // // //     // Menu interaction
// // // // //     if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && gameState == 0)
// // // // //     {
// // // // //         if (mx >= 400 && mx <= 600 && my >= 400 && my <= 450)
// // // // //             gameState = 1;
// // // // //         else if (mx >= 400 && mx <= 600 && my >= 300 && my <= 350)
// // // // //             gameState = 2;
// // // // //         else if (mx >= 400 && mx <= 600 && my >= 200 && my <= 250)
// // // // //             exit(0);
// // // // //     }

// // // // //     // Launching the bird
// // // // //     if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && gameState == 1 && ready)
// // // // //     {
// // // // //         launched = true;
// // // // //         ready = false;
// // // // //         t = 0;
// // // // //     }
// // // // // }

// // // // void iMouse(int button, int state, int mx, int my)
// // // // {
// // // //     if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
// // // //     {
// // // //         // Menu state
// // // //         if (gameState == 0)
// // // //         {
// // // //             if (mx >= 400 && mx <= 600 && my >= 400 && my <= 450)
// // // //             {
// // // //                 gameState = 1; // START GAME
// // // //                 launched = false;
// // // //                 ready = true;
// // // //                 bird_x = 120;
// // // //                 bird_y = 450;
// // // //                 t = 0;
// // // //             }
// // // //             else if (mx >= 400 && mx <= 600 && my >= 300 && my <= 350)
// // // //             {
// // // //                 gameState = 2; // HELP
// // // //             }
// // // //             else if (mx >= 400 && mx <= 600 && my >= 200 && my <= 250)
// // // //             {
// // // //                 exit(0); // EXIT
// // // //             }
// // // //         }

// // // //         // Launch bird in Game screen
// // // //         else if (gameState == 1 && ready && !launched)
// // // //         {
// // // //             launched = true;
// // // //             ready = false;
// // // //             t = 0;
// // // //         }
// // // //     }
// // // // }

// // // // void iKeyboard(unsigned char key)
// // // // {
// // // //     if (key == 'r')
// // // //     {
// // // //         bird_x = 120;
// // // //         bird_y = 450;
// // // //         t = 0;
// // // //         launched = false;
// // // //         ready = true;
// // // //     }
// // // //     else if (key == 'q')
// // // //     {
// // // //         exit(0);
// // // //     }
// // // //     else if (key == 'b') // back to menu
// // // //     {
// // // //         gameState = 0;
// // // //     }
// // // // }

// // // // void iSpecialKeyboard(unsigned char key)
// // // // {
// // // //     if (gameState == 1 && ready)
// // // //     {
// // // //         if (key == GLUT_KEY_UP && angle < 90)
// // // //             angle += 1;
// // // //         else if (key == GLUT_KEY_DOWN && angle > 0)
// // // //             angle -= 1;
// // // //         else if (key == GLUT_KEY_RIGHT && velocity < 200)
// // // //             velocity += 1;
// // // //         else if (key == GLUT_KEY_LEFT && velocity > 10)
// // // //             velocity -= 1;
// // // //     }
// // // //     if (key == GLUT_KEY_END)
// // // //         exit(0);
// // // // }

// // // // void iMouseMove(int mx, int my) {}
// // // // void iMouseDrag(int mx, int my) {}
// // // // void iMouseWheel(int dir, int mx, int my) {}

// // // // int main(int argc, char *argv[])
// // // // {
// // // //     glutInit(&argc, argv);
// // // //     iSetTimer(20, ballChange);
// // // //     srand(time(0));
// // // //     iInitialize(WIN_W, WIN_H, "Angry Birds Clone");
// // // //     return 0;
// // // // }

// // #include "iGraphics.h"
// // #include <math.h>
// // #include <stdbool.h>
// // #include <time.h>

// // #define WIN_W 1550
// // #define WIN_H 1000
// // #define MAX_BLOCKS 50
// // #define BIRD_WIDTH 60
// // #define BIRD_HEIGHT 60
// // // Game state
// // int gameState = -1;
// // int coverTimer = 0;

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

// // static double toRad(double deg) { return deg * M_PI / 180.0; }

// // typedef struct
// // {
// //     float x, y;
// //     float width, height;
// //     int isVisible;
// // } Block;

// // Block blocks[MAX_BLOCKS];
// // int blockCount = 0;
// // void initBlocks()
// // {
// //     blockCount = 13; // total blocks

// //     blocks[0] = (Block){700, 350, 30, 30, 1};
// //     blocks[1] = (Block){760, 350, 30, 30, 1};
// //     blocks[2] = (Block){730, 380, 30, 30, 1};
// //     blocks[3] = (Block){730, 350, 30, 30, 1};
// //     blocks[4] = (Block){790, 350, 30, 30, 1};
// //     blocks[5] = (Block){810, 350, 30, 30, 1};
// //     blocks[6] = (Block){840, 350, 30, 30, 1};
// //     blocks[7] = (Block){760, 380, 30, 30, 1};
// //     blocks[8] = (Block){790, 380, 30, 30, 1};
// //     blocks[9] = (Block){810, 380, 30, 30, 1};
// //     blocks[10] = (Block){760, 410, 30, 30, 1};
// //     blocks[11] = (Block){790, 410, 30, 30, 1};
// //     blocks[12] = (Block){775, 440, 30, 30, 1}; // stacked block
// // }

// // void iDraw()
// // {
// //     iClear();

// //     if (gameState == -1)
// //     {
// //         // COVER SCREEN
// //         // iSetColor(0, 0, 0);
// //         // iFilledRectangle(0, 0, WIN_W, WIN_H);
// //         iShowImage(0, 0, "assets/images/coverS.bmp");
// //         iSetColor(209, 24, 203);
// //         iText(WIN_W / 2 - 30, 60, "Loading...", GLUT_BITMAP_TIMES_ROMAN_24);
// //     }

// //     else if (gameState == 0)
// //     {
// //         // MAIN MENU
// //         // iSetColor(97, 148, 227);
// //         // iFilledRectangle(0, 0, WIN_W, WIN_H);
// //         iShowImage(0, 0, "assets/images/1ManuBackGround.bmp");

// //         const char *title = "ANGRY BIRDS";
// //         int titleX = 615, titleY = 700;
// //         int spacing = 30;
// //         for (int i = 0; title[i]; i++)
// //         {
// //             int r = 200 + rand() % 55;
// //             int g = 50 + rand() % 200;
// //             int b = 50 + rand() % 200;

// //             iSetColor(r, g, b);
// //             char ch[2] = {title[i], '\0'};
// //             iText(titleX + i * spacing, titleY, ch, GLUT_BITMAP_TIMES_ROMAN_24);
// //         }

// //         int btnW = 200, btnH = 50, x = 660;
// //         int y1 = 400, y2 = 300, y3 = 200;
// //         // Start Game Button
// //         iSetColor(0, 100, 0);
// //         iFilledRectangle(x + 5, y1 - 5, btnW, btnH);
// //         iSetColor(0, 200, 0);
// //         iFilledRectangle(x, y1, btnW, btnH);
// //         iSetColor(255, 255, 255);
// //         iText(x + 50, y1 + 15, "START GAME", GLUT_BITMAP_HELVETICA_18);

// //         iSetColor(0, 0, 100);
// //         iFilledRectangle(x + 5, y2 - 5, btnW, btnH);
// //         iSetColor(0, 0, 200);
// //         iFilledRectangle(x, y2, btnW, btnH);
// //         iSetColor(255, 255, 255);
// //         iText(x + 70, y2 + 15, "HELP", GLUT_BITMAP_HELVETICA_18);
// //         // Exit Button
// //         iSetColor(100, 0, 0);
// //         iFilledRectangle(x + 5, y3 - 5, btnW, btnH);
// //         iSetColor(200, 0, 0);
// //         iFilledRectangle(x, y3, btnW, btnH);
// //         iSetColor(255, 255, 255);
// //         iText(x + 75, y3 + 15, "EXIT", GLUT_BITMAP_HELVETICA_18);
// //     }
// //     // Gameplay
// //     else if (gameState == 1)
// //     {
// //         iShowImage(0, 0, "assets/images/groundImage2.bmp");
// //         iShowImage(0, 350, "assets/images/skyImage.bmp");
// //         iShowImage(1150, 330, "assets/images/tree.png");
// //         iShowImage(0, 330, "assets/images/grassDecor.png");
// //         iShowImage(400, 330, "assets/images/grassDecor.png");
// //         iShowImage(800, 330, "assets/images/grassDecor.png");
// //         iShowImage(1200, 330, "assets/images/grassDecor.png");
// //         iShowImage((int)bird_x, (int)bird_y, "assets/images/extractedCartoonBirdAdd.bmp");
// //         // iShowImage((int)bird_x + 50, (int)bird_y + 50, "assets/images/birdRed.bmp");
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

// //         if (bird_x <= 120 && bird_y <= 450 && bird_x >= 90 && bird_y >= 400)
// //         {
// //             // Draw slingshot puller lines
// //             iLine(100, 425, bird_x, bird_y); // Left anchor to bird
// //             iLine(110, 425, bird_x, bird_y); // Right anchor to bird

// //             // Reset the bird position
// //             bird_x = 120;
// //             bird_y = 450;
// //             launched = false;
// //             ready = true;
// //             t = 0;
// //         }

// //         // HUD
// //         int boxW = 200, boxH = 90;
// //         int boxX = 1300; // WIN_W - 300;
// //         int boxY = 720;  // WIN_H -150;
// //         // for (int i = 0; i!=-1; i++)'
// //         // {
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
// //         iText(boxX + 12, boxY + boxH - 25, s1, GLUT_BITMAP_HELVETICA_18);
// //         iText(boxX + 12, boxY + boxH - 45, s2, GLUT_BITMAP_HELVETICA_18);

// //         char scoreText[32];
// //         sprintf(scoreText, "Score: %d", score);
// //         iSetColor(255, 255, 255);
// //         iText(boxX + 12, boxY + 15, scoreText, GLUT_BITMAP_HELVETICA_18);

// //         if (levelWon)
// //         {
// //             iSetColor(255, 255, 0);
// //             iText(700, 500, "LEVEL COMPLETE!", GLUT_BITMAP_TIMES_ROMAN_24);
// //             iText(700, 450, "Press R to reset", GLUT_BITMAP_HELVETICA_18);
// //         }
// //     }
// //     else if (gameState == 2)
// //     {
// //         // iSetColor(97, 153, 8);
// //         // iFilledRectangle(0, 0, WIN_W, WIN_H);
// //         iShowImage(0, 0, "assets/images/helpBackGround.bmp");
// //         // Help text
// //         const char *help = "HELP";
// //         int helpX = 400, helpY = 650;
// //         int spacing = 30;
// //         for (int i = 0; help[i]; i++)
// //         {
// //             int r = 200 + rand() % 55;
// //             int g = 50 + rand() % 200;
// //             int b = 50 + rand() % 200;

// //             iSetColor(r, g, b);
// //             char ch[2] = {help[i], '\0'};
// //             iText(helpX + i * spacing, helpY, ch, GLUT_BITMAP_TIMES_ROMAN_24);
// //         }

// //         iSetColor(255, 255, 255);

// //         // iText(400, 650, "HELP", GLUT_BITMAP_HELVETICA_18);
// //         iText(400, 600, "Use arrow keys to set angle and speed.", GLUT_BITMAP_HELVETICA_18);
// //         iText(400, 550, "Left click to shoot. R to reset. Q to quit.", GLUT_BITMAP_HELVETICA_18);
// //         iText(400, 500, "B to return to menu.", GLUT_BITMAP_HELVETICA_18);
// //     }
// // }

// // void ballChange()
// // {
// //     if (gameState != 1 || !launched)
// //         return;
// //     // Update physics
// //     t += 0.9;
// //     double rad = toRad(angle);
// //     bird_x = 120 + velocity * cos(rad) * t;
// //     bird_y = 450 + velocity * sin(rad) * t - 0.5 * g * t * t;

// //     // Land
// //     if (bird_y <= 345)
// //     {
// //         bird_y = 345;
// //         launched = false;
// //         ready = false;
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
// //                 blocks[i].isVisible = 0;
// //                 score += 10;
// //             }
// //         }
// //     }
// //     bool allGone = true;
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
// //     }
// // }
// // void iMouse(int button, int state, int mx, int my)
// // {
// //     if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
// //     {
// //         // Menu state
// //         if (gameState == 0)
// //         {
// //             if (mx >= 660 && mx <= 860 && my >= 400 && my <= 450)
// //             {
// //                 gameState = 1; // START GAME
// //                 launched = false;
// //                 ready = true;
// //                 bird_x = 120;
// //                 bird_y = 450;
// //                 t = 0;
// //             }
// //             else if (mx >= 660 && mx <= 860 && my >= 300 && my <= 350)
// //             {
// //                 gameState = 2; // HELP
// //             }
// //             else if (mx >= 660 && mx <= 860 && my >= 200 && my <= 250)
// //             {
// //                 exit(0); // EXIT
// //             }
// //         }

// //         // Launch bird in Game screen
// //         else if (gameState == 1 && ready && !launched)
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
// //         bird_x = 120;
// //         bird_y = 450;
// //         t = 0;
// //         launched = false;
// //         ready = true;
// //         score = 0;
// //         levelWon = false;
// //         /*for(int i=0;i<blockCount;i++){
// //             if()
// //         }*/
// //     }
// //     else if (key == 'q')
// //     {
// //         exit(0);
// //     }
// //     else if (key == 'b') // back to menu
// //     {
// //         gameState = 0;
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
// // // This will switch from the cover screen to the main menu after a delay
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
// // void iMouseDrag(int mx, int my) {

// //     if (gameState == 1 && ready && !launched)
// //     {
// //         // Update bird position based on mouse drag
// //         bird_x = mx;
// //         bird_y = my;
// //     }
// // }
// // void iMouseWheel(int dir, int mx, int my) {}

// // int main(int argc, char *argv[])
// // {
// //     glutInit(&argc, argv);
// //     iSetTimer(1000, coverTimerFunc); // Cover screen timer
// //     iSetTimer(20, ballChange);
// //     srand(time(0));
// //     initBlocks();
// //     iInitialize(WIN_W, WIN_H, "Angry Birds Clone");
// //     return 0;
// // }

// #include "iGraphics.h"
// #include <math.h>
// #include <stdbool.h>
// #include <time.h>

// #define WIN_W 1550
// #define WIN_H 1000
// #define MAX_BLOCKS 50
// #define BIRD_WIDTH 60
// #define BIRD_HEIGHT 60
// // Game state
// int gameState = -1;
// int coverTimer = 0;

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

// static double toRad(double deg) { return deg * M_PI / 180.0; }

// typedef struct
// {
//     float x, y;
//     float width, height;
//     int isVisible;
// } Block;

// Block blocks[MAX_BLOCKS];
// int blockCount = 0;
// void initBlocks()
// {
//     blockCount = 13; // total blocks

//     blocks[0] = (Block){700, 350, 30, 30, 1};
//     blocks[1] = (Block){760, 350, 30, 30, 1};
//     blocks[2] = (Block){730, 380, 30, 30, 1};
//     blocks[3] = (Block){730, 350, 30, 30, 1};
//     blocks[4] = (Block){790, 350, 30, 30, 1};
//     blocks[5] = (Block){810, 350, 30, 30, 1};
//     blocks[6] = (Block){840, 350, 30, 30, 1};
//     blocks[7] = (Block){760, 380, 30, 30, 1};
//     blocks[8] = (Block){790, 380, 30, 30, 1};
//     blocks[9] = (Block){810, 380, 30, 30, 1};
//     blocks[10] = (Block){760, 410, 30, 30, 1};
//     blocks[11] = (Block){790, 410, 30, 30, 1};
//     blocks[12] = (Block){775, 440, 30, 30, 1}; // stacked block
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
//         // iSetColor(97, 148, 227);
//         // iFilledRectangle(0, 0, WIN_W, WIN_H);
//         iShowImage(0, 0, "assets/images/1ManuBackGround.bmp");

//         const char *title = "ANGRY BIRDS";
//         int titleX = 615, titleY = 700;
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
//         int y1 = 400, y2 = 300, y3 = 200;
//         // Start Game Button
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
//         iText(x + 70, y2 + 15, "HELP", GLUT_BITMAP_HELVETICA_18);
//         // Exit Button
//         iSetColor(100, 0, 0);
//         iFilledRectangle(x + 5, y3 - 5, btnW, btnH);
//         iSetColor(200, 0, 0);
//         iFilledRectangle(x, y3, btnW, btnH);
//         iSetColor(255, 255, 255);
//         iText(x + 75, y3 + 15, "EXIT", GLUT_BITMAP_HELVETICA_18);
//     }
//     // Gameplay
//     else if (gameState == 1)
//     {
//         iShowImage(0, 0, "assets/images/groundImage2.bmp");
//         iShowImage(0, 350, "assets/images/skyImage.bmp");
//         iShowImage(1150, 330, "assets/images/tree.png");
//         iShowImage(0, 330, "assets/images/grassDecor.png");
//         iShowImage(400, 330, "assets/images/grassDecor.png");
//         iShowImage(800, 330, "assets/images/grassDecor.png");
//         iShowImage(1200, 330, "assets/images/grassDecor.png");
//         iShowImage((int)bird_x, (int)bird_y, "assets/images/extractedCartoonBirdAdd.bmp");
//         // iShowImage((int)bird_x + 50, (int)bird_y + 50, "assets/images/birdRed.bmp");
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

//         if (bird_x <= 120 && bird_y <= 450 && bird_x >= 90 && bird_y >= 400)
//         {
//             // Draw slingshot puller lines
//             iLine(100, 425, bird_x, bird_y); // Left anchor to bird
//             iLine(110, 425, bird_x, bird_y); // Right anchor to bird

//             // Reset the bird position
//             bird_x = 120;
//             bird_y = 450;
//             launched = false;
//             ready = true;
//             t = 0;
//         }

//         // if(bird_x <= 120 && bird_y <= 450 && bird_x >= 90 && bird_y >= 400)
//         // {
//         //     // Reset the bird position
//         //     bird_x = 120;
//         //     bird_y = 450;
//         //     launched = false;
//         //     ready = true;
//         //     t = 0;
//         // }

//         // HUD
//         int boxW = 200, boxH = 90;
//         int boxX = 1300; // WIN_W - 300;
//         int boxY = 720;  // WIN_H -150;
//         // for (int i = 0; i!=-1; i++)'
//         // {
//         int r = 200 + rand() % 55;
//         int g = 50 + rand() % 200;
//         int b = 50 + rand() % 200;

//         iSetColor(r, g, b);
//         iFilledRectangle(boxX, boxY, boxW, boxH);
//         iSetColor(152, 79, 166);
//         iFilledRectangle(boxX + 10, boxY + 10, boxW - 20, boxH - 20);
//         // }
//         // HUD text
//         char s1[32], s2[32];
//         sprintf(s1, "Angle: %.0f°", angle);
//         sprintf(s2, "Speed: %.0f", velocity);
//         iSetColor(255, 255, 255);
//         iText(boxX + 12, boxY + boxH - 25, s1, GLUT_BITMAP_HELVETICA_18);
//         iText(boxX + 12, boxY + boxH - 45, s2, GLUT_BITMAP_HELVETICA_18);

//         char scoreText[32];
//         sprintf(scoreText, "Score: %d", score);
//         iSetColor(255, 255, 255);
//         iText(boxX + 12, boxY + 15, scoreText, GLUT_BITMAP_HELVETICA_18);

//         if (levelWon)
//         {
//             iSetColor(255, 255, 0);
//             iText(700, 500, "LEVEL COMPLETE!", GLUT_BITMAP_TIMES_ROMAN_24);
//             iText(700, 450, "Press R to reset", GLUT_BITMAP_HELVETICA_18);
//         }
//     }
//     else if (gameState == 2)
//     {
//         // iSetColor(97, 153, 8);
//         // iFilledRectangle(0, 0, WIN_W, WIN_H);
//         iShowImage(0, 0, "assets/images/helpBackGround.bmp");
//         // Help text
//         const char *help = "HELP";
//         int helpX = 400, helpY = 650;
//         int spacing = 30;
//         for (int i = 0; help[i]; i++)
//         {
//             int r = 200 + rand() % 55;
//             int g = 50 + rand() % 200;
//             int b = 50 + rand() % 200;

//             iSetColor(r, g, b);
//             char ch[2] = {help[i], '\0'};
//             iText(helpX + i * spacing, helpY, ch, GLUT_BITMAP_TIMES_ROMAN_24);
//         }

//         iSetColor(255, 255, 255);

//         // iText(400, 650, "HELP", GLUT_BITMAP_HELVETICA_18);
//         iText(400, 600, "Use arrow keys to set angle and speed.", GLUT_BITMAP_HELVETICA_18);
//         iText(400, 550, "Left click to shoot. R to reset. Q to quit.", GLUT_BITMAP_HELVETICA_18);
//         iText(400, 500, "B to return to menu.", GLUT_BITMAP_HELVETICA_18);
//     }
// }

// void ballChange()
// {
//     if (gameState != 1 || !launched)
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
//                 blocks[i].isVisible = 0;
//                 score += 10;
//             }
//         }
//     }
//     bool allGone = true;
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
//     }
// }
// void iMouse(int button, int state, int mx, int my)
// {
//     if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//     {
//         // Menu state
//         if (gameState == 0)
//         {
//             if (mx >= 660 && mx <= 860 && my >= 400 && my <= 450)
//             {
//                 gameState = 1; // START GAME
//                 launched = false;
//                 ready = true;
//                 bird_x = 120;
//                 bird_y = 450;
//                 t = 0;
//             }
//             else if (mx >= 660 && mx <= 860 && my >= 300 && my <= 350)
//             {
//                 gameState = 2; // HELP
//             }
//             else if (mx >= 660 && mx <= 860 && my >= 200 && my <= 250)
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
//     }
// }

// void iKeyboard(unsigned char key)
// {
//     if (key == 'r')
//     {
//         bird_x = 120;
//         bird_y = 450;
//         t = 0;
//         launched = false;
//         ready = true;
//         score = 0;
//         levelWon = false;
//         /*for(int i=0;i<blockCount;i++){
//             if()
//         }*/
//     }
//     else if (key == 'q')
//     {
//         exit(0);
//     }
//     else if (key == 'b') // back to menu
//     {
//         gameState = 0;
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
//     srand(time(0));
//     initBlocks();
//     iInitialize(WIN_W, WIN_H, "Angry Birds Clone");
//     return 0;
// }

#include "iGraphics.h"
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
    float pyramidbaseY = 350 + 7 * BLOCK_HEIGHT;
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
        iShowImage(0, 0, "assets/images/coverS.bmp");
        iSetColor(209, 24, 203);
        iText(WIN_W / 2 - 30, 60, "Loading...", GLUT_BITMAP_TIMES_ROMAN_24);
    }
    else if (gameState == 0)
    {
        iShowImage(0, 0, "assets/images/MenuCover.jpg");
        iShowImage(510, 630, "assets/images/AngryBwritting.bmp");

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
    else if (gameState == 1 && gameLevel == 1)
    {
        iShowImage(0, 0, "assets/images/groundImage2.bmp");
        iShowImage(0, 350, "assets/images/skyImage.bmp");
        iShowImage(1150, 330, "assets/images/tree.png");
        iShowImage(0, 330, "assets/images/grassDecor.png");
        iShowImage(400, 330, "assets/images/grassDecor.png");
        iShowImage(800, 330, "assets/images/grassDecor.png");
        iShowImage(1200, 330, "assets/images/grassDecor.png");
        iShowImage((int)bird_x, (int)bird_y, "assets/images/yellowBird.bmp");
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
    else if (gameState == 1 && gameLevel == 2)
    {
        iShowImage(0, 0, "assets/images/groundImage2.bmp");
        iShowImage(0, 350, "assets/images/skyImage.bmp");
        iShowImage(1150, 330, "assets/images/tree.png");
        iShowImage(0, 330, "assets/images/grassDecor.png");
        iShowImage(400, 330, "assets/images/grassDecor.png");
        iShowImage(800, 330, "assets/images/grassDecor.png");
        iShowImage(1200, 330, "assets/images/grassDecor.png");
        iShowImage((int)bird_x, (int)bird_y, "assets/images/yellowBird.bmp");
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
    else if (gameState == 2)
    {
        iShowImage(0, 0, "assets/images/helpBackGround.bmp");
        iSetColor(255, 255, 255);
        iText(400, 650, "HELP", GLUT_BITMAP_HELVETICA_18);
        iText(400, 600, "Use arrow keys to set angle and speed.", GLUT_BITMAP_HELVETICA_18);
        iText(400, 550, "Left click to shoot. R to reset. Q to quit.", GLUT_BITMAP_HELVETICA_18);
        iText(400, 500, "B to return to menu.", GLUT_BITMAP_HELVETICA_18);
    }
    else if (gameState == LEADERBOARD)
    {
        iSetColor(97, 153, 8);
        iFilledRectangle(0, 0, WIN_W, WIN_H);
        iSetColor(255, 255, 255);
        iText(400, 650, "LEADERBOARD", GLUT_BITMAP_TIMES_ROMAN_24);
        showLeaderboard();
        iText(100, 100, "Press B to go back", GLUT_BITMAP_HELVETICA_18);
    }
    else if (gameState == 4)
    {
        iSetColor(73, 73, 156);
        iFilledRectangle(0, 0, WIN_W, WIN_H);
        iSetColor(255, 0, 0);
        iText(600, 500, "GAME OVER!", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(600, 450, "Press R to restart or Q to quit", GLUT_BITMAP_HELVETICA_18);
        iText(600, 400, "Lives: 0", GLUT_BITMAP_HELVETICA_18);
    }
    else if (gameState == 5)
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
    else if (gameState == 6)
    {
        iSetColor(0, 0, 0);
        iFilledRectangle(0, 0, WIN_W, WIN_H);
        iSetColor(255, 255, 0);
        iText(WIN_W / 2 - 120, WIN_H / 2, "Get Ready! Moving to Level 2...", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(WIN_W / 2 - 100, WIN_H / 2 - 40, "Press R to Continue", GLUT_BITMAP_HELVETICA_18);
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
void coverTimerFunc()
{
    if (gameState == -1)
    {
        coverTimer++;
        if (coverTimer >= 7)
        {
            gameState = 0;
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
    return 0;
}

// #include "iGraphics.h"
// #include <math.h>
// #include <stdbool.h>
// #include <time.h>

// #define WIN_W 1550
// #define WIN_H 1000
// #define MAX_BLOCKS 50
// #define BIRD_WIDTH 60
// #define BIRD_HEIGHT 60
// // Game state
// int gameState = -1;
// int coverTimer = 0;

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

// static double toRad(double deg) { return deg * M_PI / 180.0; }

// typedef struct
// {
//     float x, y;
//     float width, height;
//     int isVisible;
// } Block;

// Block blocks[MAX_BLOCKS];
// int blockCount = 0;
// void initBlocks()
// {
//     blockCount = 13; // total blocks

//     blocks[0] = (Block){700, 350, 30, 30, 1};
//     blocks[1] = (Block){760, 350, 30, 30, 1};
//     blocks[2] = (Block){730, 380, 30, 30, 1};
//     blocks[3] = (Block){730, 350, 30, 30, 1};
//     blocks[4] = (Block){790, 350, 30, 30, 1};
//     blocks[5] = (Block){810, 350, 30, 30, 1};
//     blocks[6] = (Block){840, 350, 30, 30, 1};
//     blocks[7] = (Block){760, 380, 30, 30, 1};
//     blocks[8] = (Block){790, 380, 30, 30, 1};
//     blocks[9] = (Block){810, 380, 30, 30, 1};
//     blocks[10] = (Block){760, 410, 30, 30, 1};
//     blocks[11] = (Block){790, 410, 30, 30, 1};
//     blocks[12] = (Block){775, 440, 30, 30, 1}; // stacked block
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
//         // iShowImage(0, 0, "assets/images/pngegg.png");
//         iSetColor(209, 24, 203);
//         iText(WIN_W / 2 - 30, 60, "Loading...", GLUT_BITMAP_TIMES_ROMAN_24);
//     }

//     else if (gameState == 0)
//     {
//         // MAIN MENU
//         // iSetColor(97, 148, 227);
//         // iFilledRectangle(0, 0, WIN_W, WIN_H);
//         // iShowImage(0, 50, "assets/images/menuBack.bmp");
//         iShowImage(0, 0, "assets/images/MenuCover.jpg");

//         iShowImage(510, 630, "assets/images/AngryBwritting.bmp");
//         // const char *title = "ANGRY BIRDS";
//         // int titleX = 615, titleY = 700;
//         // int spacing = 30;
//         // for (int i = 0; title[i]; i++)
//         // {
//         //     int r = 200 + rand() % 55;
//         //     int g = 50 + rand() % 200;
//         //     int b = 50 + rand() % 200;

//         //     iSetColor(r, g, b);
//         //     char ch[2] = {title[i], '\0'};
//         //     iText(titleX + i * spacing, titleY, ch, GLUT_BITMAP_TIMES_ROMAN_24);
//         // }

//         int btnW = 200, btnH = 50, x = 660;
//         int y1 = 400, y2 = 300, y3 = 200;
//         // Start Game Button
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
//         iText(x + 70, y2 + 15, "HELP", GLUT_BITMAP_HELVETICA_18);
//         // Exit Button
//         iSetColor(100, 0, 0);
//         iFilledRectangle(x + 5, y3 - 5, btnW, btnH);
//         iSetColor(200, 0, 0);
//         iFilledRectangle(x, y3, btnW, btnH);
//         iSetColor(255, 255, 255);
//         iText(x + 75, y3 + 15, "EXIT", GLUT_BITMAP_HELVETICA_18);
//     }
//     // Gameplay
//     else if (gameState == 1)
//     {
//         iShowImage(0, 0, "assets/images/groundImage2.bmp");
//         iShowImage(0, 350, "assets/images/skyImage.bmp");
//         iShowImage(1150, 330, "assets/images/tree.png");
//         iShowImage(0, 330, "assets/images/grassDecor.png");
//         iShowImage(400, 330, "assets/images/grassDecor.png");
//         iShowImage(800, 330, "assets/images/grassDecor.png");
//         iShowImage(1200, 330, "assets/images/grassDecor.png");
//         // iShowImage((int)bird_x, (int)bird_y, "assets/images/extractedCartoonBirdAdd.bmp");
//         iShowImage((int)bird_x, (int)bird_y, "assets/images/yellowBird.bmp");
//         iShowImage(100, 200, "assets/images/extractedCartoonBirdAdd.bmp");
//         // iShowImage((int)bird_x + 50, (int)bird_y + 50, "assets/images/birdRed.bmp");
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

//         if (bird_x <= 120 && bird_y <= 450 && bird_x >= 90 && bird_y >= 400)
//         {
//             // Draw slingshot puller lines
//             iLine(100, 425, bird_x, bird_y); // Left anchor to bird
//             iLine(110, 425, bird_x, bird_y); // Right anchor to bird

//             // Reset the bird position
//             bird_x = 120;
//             bird_y = 450;
//             launched = false;
//             ready = true;
//             t = 0;
//         }

//         // if(bird_x <= 120 && bird_y <= 450 && bird_x >= 90 && bird_y >= 400)
//         // {
//         //     // Reset the bird position
//         //     bird_x = 120;
//         //     bird_y = 450;
//         //     launched = false;
//         //     ready = true;
//         //     t = 0;
//         // }

//         // HUD
//         int boxW = 200, boxH = 90;
//         int boxX = 1300; // WIN_W - 300;
//         int boxY = 720;  // WIN_H -150;
//         // for (int i = 0; i!=-1; i++)'
//         // {
//         int r = 200 + rand() % 55;
//         int g = 50 + rand() % 200;
//         int b = 50 + rand() % 200;

//         iSetColor(r, g, b);
//         iFilledRectangle(boxX, boxY, boxW, boxH);
//         iSetColor(152, 79, 166);
//         iFilledRectangle(boxX + 10, boxY + 10, boxW - 20, boxH - 20);
//         // }
//         // HUD text
//         char s1[32], s2[32];
//         sprintf(s1, "Angle: %.0f°", angle);
//         sprintf(s2, "Speed: %.0f", velocity);
//         iSetColor(255, 255, 255);
//         iText(boxX + 12, boxY + boxH - 25, s1, GLUT_BITMAP_HELVETICA_18);
//         iText(boxX + 12, boxY + boxH - 45, s2, GLUT_BITMAP_HELVETICA_18);

//         char scoreText[32];
//         sprintf(scoreText, "Score: %d", score);
//         iSetColor(255, 255, 255);
//         iText(boxX + 12, boxY + 15, scoreText, GLUT_BITMAP_HELVETICA_18);

//         if (levelWon)
//         {
//             iSetColor(255, 255, 0);
//             iText(700, 500, "LEVEL COMPLETE!", GLUT_BITMAP_TIMES_ROMAN_24);
//             iText(700, 450, "Press R to reset", GLUT_BITMAP_HELVETICA_18);
//         }
//     }
//     else if (gameState == 2)
//     {
//         // iSetColor(97, 153, 8);
//         // iFilledRectangle(0, 0, WIN_W, WIN_H);
//         iShowImage(0, 0, "assets/images/helpBackGround.bmp");
//         // Help text
//         const char *help = "HELP";
//         int helpX = 400, helpY = 650;
//         int spacing = 30;
//         for (int i = 0; help[i]; i++)
//         {
//             int r = 200 + rand() % 55;
//             int g = 50 + rand() % 200;
//             int b = 50 + rand() % 200;

//             iSetColor(r, g, b);
//             char ch[2] = {help[i], '\0'};
//             iText(helpX + i * spacing, helpY, ch, GLUT_BITMAP_TIMES_ROMAN_24);
//         }

//         iSetColor(255, 255, 255);

//         // iText(400, 650, "HELP", GLUT_BITMAP_HELVETICA_18);
//         iText(400, 600, "Use arrow keys to set angle and speed.", GLUT_BITMAP_HELVETICA_18);
//         iText(400, 550, "Left click to shoot. R to reset. Q to quit.", GLUT_BITMAP_HELVETICA_18);
//         iText(400, 500, "B to return to menu.", GLUT_BITMAP_HELVETICA_18);
//     }
// }

// void ballChange()
// {
//     if (gameState != 1 || !launched)
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
//                 blocks[i].isVisible = 0;
//                 score += 10;
//             }
//         }
//     }
//     bool allGone = true;
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
//     }
// }
// void iMouse(int button, int state, int mx, int my)
// {
//     if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//     {
//         // Menu state
//         if (gameState == 0)
//         {
//             if (mx >= 660 && mx <= 860 && my >= 400 && my <= 450)
//             {
//                 gameState = 1; // START GAME
//                 launched = false;
//                 ready = true;
//                 bird_x = 120;
//                 bird_y = 450;
//                 t = 0;
//             }
//             else if (mx >= 660 && mx <= 860 && my >= 300 && my <= 350)
//             {
//                 gameState = 2; // HELP
//             }
//             else if (mx >= 660 && mx <= 860 && my >= 200 && my <= 250)
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
//     }
// }

// void iKeyboard(unsigned char key)
// {
//     if (key == 'r')
//     {
//         bird_x = 120;
//         bird_y = 450;
//         t = 0;
//         launched = false;
//         ready = true;
//         score = 0;
//         levelWon = false;
//         /*for(int i=0;i<blockCount;i++){
//             if()
//         }*/
//     }
//     else if (key == 'q')
//     {
//         exit(0);
//     }
//     else if (key == 'b') // back to menu
//     {
//         gameState = 0;
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
//     srand(time(0));
//     initBlocks();
//     iInitialize(WIN_W, WIN_H, "Angry Birds Clone");
//     return 0;
// }

// // #include "iGraphics.h"
// // #include <math.h>
// // #include <stdbool.h>
// // #include <time.h>

// // #define WIN_W 1550
// // #define WIN_H 1000
// // #define MAX_BLOCKS 50
// // #define BIRD_WIDTH 60
// // #define BIRD_HEIGHT 60
// // // Game state
// // int gameState = -1;
// // int coverTimer = 0;

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

// // static double toRad(double deg) { return deg * M_PI / 180.0; }

// // typedef struct
// // {
// //     float x, y;
// //     float width, height;
// //     int isVisible;
// // } Block;

// // Block blocks[MAX_BLOCKS];
// // int blockCount = 0;
// // void initBlocks()
// // {
// //     blockCount = 13; // total blocks

// //     blocks[0] = (Block){700, 350, 30, 30, 1};
// //     blocks[1] = (Block){760, 350, 30, 30, 1};
// //     blocks[2] = (Block){730, 380, 30, 30, 1};
// //     blocks[3] = (Block){730, 350, 30, 30, 1};
// //     blocks[4] = (Block){790, 350, 30, 30, 1};
// //     blocks[5] = (Block){810, 350, 30, 30, 1};
// //     blocks[6] = (Block){840, 350, 30, 30, 1};
// //     blocks[7] = (Block){760, 380, 30, 30, 1};
// //     blocks[8] = (Block){790, 380, 30, 30, 1};
// //     blocks[9] = (Block){810, 380, 30, 30, 1};
// //     blocks[10] = (Block){760, 410, 30, 30, 1};
// //     blocks[11] = (Block){790, 410, 30, 30, 1};
// //     blocks[12] = (Block){775, 440, 30, 30, 1}; // stacked block
// // }

// // void iDraw()
// // {
// //     iClear();

// //     if (gameState == -1)
// //     {
// //         // COVER SCREEN
// //         // iSetColor(0, 0, 0);
// //         // iFilledRectangle(0, 0, WIN_W, WIN_H);
// //         iShowImage(0, 0, "assets/images/coverS.bmp");
// //         iSetColor(209, 24, 203);
// //         iText(WIN_W / 2 - 30, 60, "Loading...", GLUT_BITMAP_TIMES_ROMAN_24);
// //     }

// //     else if (gameState == 0)
// //     {
// //         // MAIN MENU
// //         // iSetColor(97, 148, 227);
// //         // iFilledRectangle(0, 0, WIN_W, WIN_H);
// //         iShowImage(0, 0, "assets/images/1ManuBackGround.bmp");

// //         const char *title = "ANGRY BIRDS";
// //         int titleX = 615, titleY = 700;
// //         int spacing = 30;
// //         for (int i = 0; title[i]; i++)
// //         {
// //             int r = 200 + rand() % 55;
// //             int g = 50 + rand() % 200;
// //             int b = 50 + rand() % 200;

// //             iSetColor(r, g, b);
// //             char ch[2] = {title[i], '\0'};
// //             iText(titleX + i * spacing, titleY, ch, GLUT_BITMAP_TIMES_ROMAN_24);
// //         }

// //         int btnW = 200, btnH = 50, x = 660;
// //         int y1 = 400, y2 = 300, y3 = 200;
// //         // Start Game Button
// //         iSetColor(0, 100, 0);
// //         iFilledRectangle(x + 5, y1 - 5, btnW, btnH);
// //         iSetColor(0, 200, 0);
// //         iFilledRectangle(x, y1, btnW, btnH);
// //         iSetColor(255, 255, 255);
// //         iText(x + 50, y1 + 15, "START GAME", GLUT_BITMAP_HELVETICA_18);

// //         iSetColor(0, 0, 100);
// //         iFilledRectangle(x + 5, y2 - 5, btnW, btnH);
// //         iSetColor(0, 0, 200);
// //         iFilledRectangle(x, y2, btnW, btnH);
// //         iSetColor(255, 255, 255);
// //         iText(x + 70, y2 + 15, "HELP", GLUT_BITMAP_HELVETICA_18);
// //         // Exit Button
// //         iSetColor(100, 0, 0);
// //         iFilledRectangle(x + 5, y3 - 5, btnW, btnH);
// //         iSetColor(200, 0, 0);
// //         iFilledRectangle(x, y3, btnW, btnH);
// //         iSetColor(255, 255, 255);
// //         iText(x + 75, y3 + 15, "EXIT", GLUT_BITMAP_HELVETICA_18);
// //     }
// //     // Gameplay
// //     else if (gameState == 1)
// //     {
// //         iShowImage(0, 0, "assets/images/groundImage2.bmp");
// //         iShowImage(0, 350, "assets/images/skyImage.bmp");
// //         iShowImage(1150, 330, "assets/images/tree.png");
// //         iShowImage(0, 330, "assets/images/grassDecor.png");
// //         iShowImage(400, 330, "assets/images/grassDecor.png");
// //         iShowImage(800, 330, "assets/images/grassDecor.png");
// //         iShowImage(1200, 330, "assets/images/grassDecor.png");
// //         iShowImage((int)bird_x, (int)bird_y, "assets/images/extractedCartoonBirdAdd.bmp");
// //         // iShowImage((int)bird_x + 50, (int)bird_y + 50, "assets/images/birdRed.bmp");
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

// //         if (bird_x <= 120 && bird_y <= 450 && bird_x >= 90 && bird_y >= 400)
// //         {
// //             // Draw slingshot puller lines
// //             iLine(100, 425, bird_x, bird_y); // Left anchor to bird
// //             iLine(110, 425, bird_x, bird_y); // Right anchor to bird

// //             // Reset the bird position
// //             bird_x = 120;
// //             bird_y = 450;
// //             launched = false;
// //             ready = true;
// //             t = 0;
// //         }

// //         // if(bird_x <= 120 && bird_y <= 450 && bird_x >= 90 && bird_y >= 400)
// //         // {
// //         //     // Reset the bird position
// //         //     bird_x = 120;
// //         //     bird_y = 450;
// //         //     launched = false;
// //         //     ready = true;
// //         //     t = 0;
// //         // }

// //         // HUD
// //         int boxW = 200, boxH = 90;
// //         int boxX = 1300; // WIN_W - 300;
// //         int boxY = 720;  // WIN_H -150;
// //         // for (int i = 0; i!=-1; i++)'
// //         // {
// //         int r = 200 + rand() % 55;
// //         int g = 50 + rand() % 200;
// //         int b = 50 + rand() % 200;

// //         iSetColor(r, g, b);
// //         iFilledRectangle(boxX, boxY, boxW, boxH);
// //         iSetColor(152, 79, 166);
// //         iFilledRectangle(boxX + 10, boxY + 10, boxW - 20, boxH - 20);
// //         // }
// //         // HUD text
// //         char s1[32], s2[32];
// //         sprintf(s1, "Angle: %.0f°", angle);
// //         sprintf(s2, "Speed: %.0f", velocity);
// //         iSetColor(255, 255, 255);
// //         iText(boxX + 12, boxY + boxH - 25, s1, GLUT_BITMAP_HELVETICA_18);
// //         iText(boxX + 12, boxY + boxH - 45, s2, GLUT_BITMAP_HELVETICA_18);

// //         char scoreText[32];
// //         sprintf(scoreText, "Score: %d", score);
// //         iSetColor(255, 255, 255);
// //         iText(boxX + 12, boxY + 15, scoreText, GLUT_BITMAP_HELVETICA_18);

// //         if (levelWon)
// //         {
// //             iSetColor(255, 255, 0);
// //             iText(700, 500, "LEVEL COMPLETE!", GLUT_BITMAP_TIMES_ROMAN_24);
// //             iText(700, 450, "Press R to reset", GLUT_BITMAP_HELVETICA_18);
// //         }
// //     }
// //     else if (gameState == 2)
// //     {
// //         // iSetColor(97, 153, 8);
// //         // iFilledRectangle(0, 0, WIN_W, WIN_H);
// //         iShowImage(0, 0, "assets/images/helpBackGround.bmp");
// //         // Help text
// //         const char *help = "HELP";
// //         int helpX = 400, helpY = 650;
// //         int spacing = 30;
// //         for (int i = 0; help[i]; i++)
// //         {
// //             int r = 200 + rand() % 55;
// //             int g = 50 + rand() % 200;
// //             int b = 50 + rand() % 200;

// //             iSetColor(r, g, b);
// //             char ch[2] = {help[i], '\0'};
// //             iText(helpX + i * spacing, helpY, ch, GLUT_BITMAP_TIMES_ROMAN_24);
// //         }

// //         iSetColor(255, 255, 255);

// //         // iText(400, 650, "HELP", GLUT_BITMAP_HELVETICA_18);
// //         iText(400, 600, "Use arrow keys to set angle and speed.", GLUT_BITMAP_HELVETICA_18);
// //         iText(400, 550, "Left click to shoot. R to reset. Q to quit.", GLUT_BITMAP_HELVETICA_18);
// //         iText(400, 500, "B to return to menu.", GLUT_BITMAP_HELVETICA_18);
// //     }
// // }

// // void ballChange()
// // {
// //     if (gameState != 1 || !launched)
// //         return;
// //     // Update physics
// //     t += 0.9;
// //     double rad = toRad(angle);
// //     bird_x = 120 + velocity * cos(rad) * t;
// //     bird_y = 450 + velocity * sin(rad) * t - 0.5 * g * t * t;

// //     // Land
// //     if (bird_y <= 345)
// //     {
// //         bird_y = 345;
// //         launched = false;
// //         ready = false;
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
// //                 blocks[i].isVisible = 0;
// //                 score += 10;
// //             }
// //         }
// //     }
// //     bool allGone = true;
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
// //     }
// // }
// // void iMouse(int button, int state, int mx, int my)
// // {
// //     if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
// //     {
// //         // Menu state
// //         if (gameState == 0)
// //         {
// //             if (mx >= 660 && mx <= 860 && my >= 400 && my <= 450)
// //             {
// //                 gameState = 1; // START GAME
// //                 launched = false;
// //                 ready = true;
// //                 bird_x = 120;
// //                 bird_y = 450;
// //                 t = 0;
// //             }
// //             else if (mx >= 660 && mx <= 860 && my >= 300 && my <= 350)
// //             {
// //                 gameState = 2; // HELP
// //             }
// //             else if (mx >= 660 && mx <= 860 && my >= 200 && my <= 250)
// //             {
// //                 exit(0); // EXIT
// //             }
// //         }

// //         // Launch bird in Game screen
// //         else if (gameState == 1 && ready && !launched)
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
// //         bird_x = 120;
// //         bird_y = 450;
// //         t = 0;
// //         launched = false;
// //         ready = true;
// //         score = 0;
// //         levelWon = false;
// //         /*for(int i=0;i<blockCount;i++){
// //             if()
// //         }*/
// //     }
// //     else if (key == 'q')
// //     {
// //         exit(0);
// //     }
// //     else if (key == 'b') // back to menu
// //     {
// //         gameState = 0;
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
// // // This will switch from the cover screen to the main menu after a delay
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
// //     srand(time(0));
// //     initBlocks();
// //     iInitialize(WIN_W, WIN_H, "Angry Birds Clone");
// //     return 0;
// // }

#include "iGraphics.h"
#include "iSound.h"
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
#define NUM_BIRDS 5

#define STATE_COVER -1
#define STATE_MENU 0
#define STATE_HELP 2
#define STATE_LEADERBOARD 3
#define STATE_GAMEOVER 4
#define STATE_CREDITS 7
#define STATE_BIRDSELECT 8
#define STATE_NAMEINPUT 9
#define STATE_LEVEL1 10
#define STATE_LEVEL2 11
#define STATE_LEVELCOMPLETE 12

// Game state
int gameState = STATE_COVER;
int coverTimer = 0;
int gameLevel = 1;

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
    "assets/images/greenBird.bmp"};

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
bool soundOn = true;
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

// Leaderboard
typedef struct
{
    char name[100];
    int score;
} Leader;

Leader leaders[100];
int leaderCount = 0;

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
    addPerimeterGrid(600, 350, 7, 9, BLOCK_WIDTH, BLOCK_HEIGHT, 2, 1);
    float pyramidcenterX = 600 + 9 * BLOCK_WIDTH / 2;
    float pyramidbaseY = 350 + 7 * BLOCK_HEIGHT;
    addPyramid(pyramidcenterX, pyramidbaseY, 4, BLOCK_WIDTH, BLOCK_HEIGHT, 1);
}

void initBlocks2()
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
            break;
    }
    fclose(fp);
}

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
    iSetColor(255, 255, 0);
    iText(600, 800, "LEADERBOARD", GLUT_BITMAP_HELVETICA_18);
    for (int i = 0; i < count && i < 5; i++)
    {
        char line[200];
        sprintf(line, "%d.%s - %d", i + 1, tempLeaders[i].name, tempLeaders[i].score);
        iText(600, 550 - i * 30, line, GLUT_BITMAP_HELVETICA_18);
    }
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
        int soundBtnX = WIN_W - 80, soundBtnY = WIN_H - 80, soundBtnW = 60, soundBtnH = 60;
        iSetColor(200, 200, 0);
        iFilledCircle(soundBtnX + 30, soundBtnY + 30, 30);
        iSetColor(0, 0, 0);
        if (soundOn)
            iText(soundBtnX + 10, soundBtnY + 25, "ON", GLUT_BITMAP_HELVETICA_18);
        else
            iText(soundBtnX + 10, soundBtnY + 25, "OFF", GLUT_BITMAP_HELVETICA_18);
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

        if (ready && birds[currentBird].active && !dragging)
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
        iSetColor(0, 0, 0);
        iFilledRectangle(300, 90, 900, 600);
        showLeaderboard();
        iSetColor(255, 255, 255);
        iText(60, 60, "Press B to go back", GLUT_BITMAP_HELVETICA_18);
    }
    else if (gameState == STATE_HELP)
    {
        iSetColor(97, 153, 8);
        iFilledRectangle(0, 0, WIN_W, WIN_H);
        iSetColor(255, 255, 255);
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
        iText(100, 100, "Press B to go back", GLUT_BITMAP_HELVETICA_18);
    }
    else if (gameState == STATE_GAMEOVER)
    {
        iSetColor(73, 73, 156);
        iFilledRectangle(0, 0, WIN_W, WIN_H);
        iSetColor(255, 0, 0);
        iText(600, 500, "GAME OVER!", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(600, 450, "Press R to restart or Q to quit", GLUT_BITMAP_HELVETICA_18);
        iText(600, 400, "Lives: 0", GLUT_BITMAP_HELVETICA_18);
        iText(100, 100, "Press B to go back", GLUT_BITMAP_HELVETICA_18);
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
            if (soundOn && bgmChannel == -1)
                bgmChannel = iPlaySound("bin/assets/sounds/Voicy_Angry burd.mp3", true, 100);
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
            // Sound button
            if (mx >= soundBtnX && mx <= soundBtnX + soundBtnW && my >= soundBtnY && my <= soundBtnY + soundBtnH)
            {
                soundOn = !soundOn;
                if (soundOn)
                {
                    if (bgmChannel == -1)
                        bgmChannel = iPlaySound("bin/assets/sounds/Voicy_Angry burd.mp3", true, 100);
                }
                else
                {
                    if (bgmChannel != -1)
                    {
                        iStopSound(bgmChannel);
                        bgmChannel = -1;
                    }
                }
                return;
            }
            // Start Game
            if (mx >= x && mx <= x + btnW && my >= y1 && my <= y1 + btnH)
            {
                gameState = STATE_NAMEINPUT;
                nameCharIndex = 0;
                playerName[0] = '\0';
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
                exit(0);
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
                        gameState = STATE_LEVEL1;
                        gameLevel = 1;
                        score = 0;
                        lives = 5;
                        initBlocks1();
                        initBirds();
                        resetCurrentBird();
                        launched = false;
                        ready = true;
                        if (bgmChannel != -1)
                        {
                            iStopSound(bgmChannel);
                            bgmChannel = -1;
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
            if (soundOn && bgmChannel == -1)
                bgmChannel = iPlaySound("bin/assets/sounds/Voicy_Angry burd.mp3", true, 100);
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
        exit(0);
    }
    else if (key == 'b')
    {
        gameState = STATE_MENU;
        if (soundOn && bgmChannel == -1)
            bgmChannel = iPlaySound("bin/assets/sounds/Voicy_Angry burd.mp3", true, 100);
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
    if (key == GLUT_KEY_END)
        exit(0);
}

int main(int argc, char *argv[])
{
    iInitializeSound();
    glutInit(&argc, argv);
    iSetTimer(1000, coverTimerFunc);
    iSetTimer(20, ballChange);
    iSetTimer(20, updateBlockPositions);
    srand(time(0));
    initBlocks1();
    for (int i = 0; i < NUM_BIRDS; i++)
        selectedBirdTypes[i] = i;
    initBirds();
    iInitialize(WIN_W, WIN_H, "Angry Birds");
    iFreeSound();
    return 0;
}