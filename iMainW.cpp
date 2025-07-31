// #include "iGraphics.h"
// #include <math.h>
// #include <stdbool.h>

// // ── Window Size ───────────────────────────────────────────────────────────────
// #define WIN_W 1000
// #define WIN_H 1000

// void drawHomePage();

// int homePage = 1;
// // ── Sprite Images ─────────────────────────────────────────────────────────────
// Image skyImg, groundImg, slingshotImg, birdImg;

// // ── Bird & Physics ───────────────────────────────────────────────────────────
// double bird_x = 120, bird_y = 450;
// double velocity = 70; // launch speed
// double angle = 30;    // launch angle in degrees
// double g = 9.8;
// double t = 0;
// bool launched = false;
// bool ready = true; // true = show aim UI

// // ── Helpers ───────────────────────────────────────────────────────────────────
// static double toRad(double deg) { return deg * M_PI / 180.0; }

// // ── Load Images Once ─────────────────────────────────────────────────────────
// void loadAssets()
// {
//     if (!iLoadImage(&skyImg, "assets/images/sky.BMP.bmp"))
//     {
//         printf("Failed to load sky.png\n");
//         exit(1);
//     }
//     if (!iLoadImage(&groundImg, "assets/images/ground.BMP.bmp"))
//     {
//         printf("Failed to load ground.png\n");
//         exit(1);
//     }
//     if (!iLoadImage(&slingshotImg, "assets/images/slingshot.BMP.bmp"))
//     {
//         printf("Failed to load slingshot.png\n");
//         exit(1);
//     }
//     if (!iLoadImage(&birdImg, "assets/images/bird.bmp.bmp"))
//     {
//         printf("Failed to load bird.png\n");
//         exit(1);
//     }
// }

// // ── Draw Everything ──────────────────────────────────────────────────────────
// void iDraw()
// {
//     iClear();

//     if (homePage)
//     {
//         drawHomePage();
//         return;
//     }

//     // 1) Sky
//     iShowLoadedImage(0, WIN_W, &skyImg);

//     // 2) Ground (grass strip)
//     iShowLoadedImage(0, WIN_W / 2, &groundImg); // adjust Y if needed

//     // 3) Slingshot
//     iShowLoadedImage(50, WIN_H / 2, &slingshotImg);

//     // 4) Trajectory line (blue) only when ready
//     if (ready)
//     {
//         double rad = toRad(angle),
//                len = 150,
//                ex = bird_x + len * cos(rad),
//                ey = bird_y + len * sin(rad);

//         iSetColor(0, 100, 255);
//         iLine(bird_x, bird_y, ex, ey);
//     }

//     // 5) Bird sprite (centered)
//     iShowLoadedImage((int)(bird_x - birdImg.width / 2), (int)(bird_y - birdImg.height / 2), &birdImg);

//     // 6) HUD box in top‑right
//     int boxW = 250, boxH = 70;
//     int boxX = WIN_W - 10 - boxW;
//     int boxY = WIN_H - 10 - boxH;
//     iSetColor(0, 0, 0);
//     iFilledRectangle(boxX, boxY, boxW, boxH);

//     // HUD text
//     char s1[32], s2[32];
//     sprintf(s1, "Angle: %.0f°", angle);
//     sprintf(s2, "Speed: %.0f", velocity);
//     iSetColor(255, 255, 255);
//     iText(boxX + 10, boxY + boxH - 20, s1, GLUT_BITMAP_HELVETICA_18);
//     iText(boxX + 10, boxY + boxH - 45, s2, GLUT_BITMAP_HELVETICA_18);

//     //   iClear();
//     //   iSetColor(255, 0, 0);
//     //   iFilledRectangle(100, 100, 200, 200);
//     //     // ...rest of your drawing code...
// }

// // ── Physics Update ────────────────────────────────────────────────────────────
// void ballChange()
// {
//     if (!launched)
//         return;

//     t += 0.05;
//     double rad = toRad(angle);
//     bird_x = 120 + velocity * cos(rad) * t;
//     bird_y = 450 + velocity * sin(rad) * t - 0.5 * g * t * t;

//     // Land on ground (y = 200)
//     if (bird_y <= 200)
//     {
//         bird_y = 200;
//         launched = false;
//         ready = false;
//     }
// }

// // ── Mouse: launch only if ready ───────────────────────────────────────────────
// void iMouse(int button, int state, int mx, int my)
// {
//     if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && ready)
//     {
//         launched = true;
//         ready = false;
//         t = 0;
//     }
// }

// // ── Keyboard ─────────────────────────────────────────────────────────────────
// void iKeyboard(unsigned char key)
// {
//     if (key == 'r')
//     {
//         // reset for next shot
//         bird_x = 120;
//         bird_y = 450;
//         t = 0;
//         launched = false;
//         ready = true;
//     }
//     else if (key == 'q')
//         exit(0);
// }

// // ── Special Keys: adjust angle & speed only when ready ────────────────────────
// void iSpecialKeyboard(unsigned char key)
// {
//     if (ready)
//     {
//         if (key == GLUT_KEY_UP && angle < 90)
//             angle += 1;
//         if (key == GLUT_KEY_DOWN && angle > 0)
//             angle -= 1;
//         if (key == GLUT_KEY_RIGHT && velocity < 200)
//             velocity += 1;
//         if (key == GLUT_KEY_LEFT && velocity > 10)
//             velocity -= 1;
//     }
//     if (key == GLUT_KEY_END)
//         exit(0);
// }

// // ── Stubs for iGraphics linking ───────────────────────────────────────────────
// void iMouseMove(int mx, int my) {}
// void iMouseDrag(int mx, int my) {}
// void iMouseWheel(int dir, int mx, int my) {}

// void drawHomePage()
// {
//     iSetColor(255, 255, 255);
//     iFilledRectangle(0, 0, 1000, 1000);
//     iShowImage(0, 1000, "assets/images/homepage.BMP.bmp");
// }
// // ── Main ─────────────────────────────────────────────────────────────────────
// int main(int argc, char *argv[])
// {
//     glutInit(&argc, argv);

//     loadAssets();
//     iSetTimer(20, ballChange); // ~50 FPS
//     iInitialize(WIN_W, WIN_H, "Angry Birds");

//     return 0;
// }

#include "iGraphics.h"
#include <math.h>
#include <stdbool.h>
#include <time.h>

#define WIN_W 1000
#define WIN_H 1000

// Game state
int gameState = 0;

// Bird and physics
double bird_x = 120, bird_y = 450;
double velocity = 70; // initial speed
double angle = 30;    // launch angle
double g = 9.8;
double t = 0;
bool launched = false;
bool ready = true;

static double toRad(double deg) { return deg * M_PI / 180.0; }

void iDraw()
{
    iClear();
    if (gameState == 0)
    {
        // Background sky blue
        iSetColor(135, 206, 250);
        iFilledRectangle(0, 0, WIN_W, WIN_H);
   // Fancy Title: ANGRY BIRDS (Capitalized, Colored Letters)
   const char *title = "ANGRY BIRDS";
   int titleX = 350, titleY = 600;
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
   // Buttons
   int btnW = 200, btnH = 50, x = 400;
   int y1 = 400, y2 = 300, y3 = 200;

   // Start
   iSetColor(0, 100, 0);
   iFilledRectangle(x + 5, y1 - 5, btnW, btnH);
   iSetColor(0, 200, 0);
   iFilledRectangle(x, y1, btnW, btnH);
   iSetColor(255, 255, 255);
   iText(x + 50, y1 + 15, "START GAME", GLUT_BITMAP_HELVETICA_18);

   // Help
   iSetColor(0, 0, 100);
   iFilledRectangle(x + 5, y2 - 5, btnW, btnH);
   iSetColor(0, 0, 200);
   iFilledRectangle(x, y2, btnW, btnH);
   iSetColor(255, 255, 255);
   iText(x + 70, y2 + 15, "HELP", GLUT_BITMAP_HELVETICA_18);

   // Exit
   iSetColor(100, 0, 0);
   iFilledRectangle(x + 5, y3 - 5, btnW, btnH);
   iSetColor(200, 0, 0);
   iFilledRectangle(x, y3, btnW, btnH);
   iSetColor(255, 255, 255);
   iText(x + 75, y3 + 15, "EXIT", GLUT_BITMAP_HELVETICA_18);
    }

    else if (gameState == 1)
    {
        // Gameplay
        iShowImage(0, 0, "assets/images/cartoongroundAdd.bmp");
        iShowImage(0, 350, "assets/images/cartoonskyAdd.bmp");
        iShowImage((int)bird_x, (int)bird_y, "assets/images/extractedCartoonBirdAdd.bmp");
        iShowImage(100, 285, "assets/images/extractedCartoonSlingshotAdd.bmp.bmp");

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
        int boxW = 250, boxH = 70;
        int boxX = WIN_W - 10 - boxW;
        int boxY = WIN_H - 10 - boxH;
        iSetColor(0, 0, 0);
        iFilledRectangle(boxX, boxY, boxW, boxH);

        char s1[32], s2[32];
        sprintf(s1, "Angle: %.0f°", angle);
        sprintf(s2, "Speed: %.0f", velocity);
        iSetColor(255, 255, 255);
        iText(boxX + 10, boxY + boxH - 20, s1, GLUT_BITMAP_HELVETICA_18);
        iText(boxX + 10, boxY + boxH - 45, s2, GLUT_BITMAP_HELVETICA_18);
    }
    else if (gameState == 2)
    {
        iSetColor(0, 0, 0);
        iFilledRectangle(0, 0, WIN_W, WIN_H);

        iSetColor(255, 255, 255);
        iText(100, 900, "HELP");
        iText(100, 850, "Use arrow keys to set angle and speed.");
        iText(100, 800, "Left click to shoot. R to reset. Q to quit.");
        iText(100, 750, "B to return to menu.");
    }
}

void ballChange()
{
    if (gameState != 1 || !launched)
        return;

    t += 0.15;
    double rad = toRad(angle);
    bird_x = 120 + velocity * cos(rad) * t;
    bird_y = 450 + velocity * sin(rad) * t - 0.5 * g * t * t;

    // Land
    if (bird_y <= 345)
    {
        bird_y = 345;
        launched = false;
        ready = false;
    }
}
void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // Menu state
        if (gameState == 0)
        {
            if (mx >= 400 && mx <= 600 && my >= 400 && my <= 450)
            {
                gameState = 1; // START GAME
                launched = false;
                ready = true;
                bird_x = 120;
                bird_y = 450;
                t = 0;
            }
            else if (mx >= 400 && mx <= 600 && my >= 300 && my <= 350)
            {
                gameState = 2; // HELP
            }
            else if (mx >= 400 && mx <= 600 && my >= 200 && my <= 250)
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
    }
}

void iKeyboard(unsigned char key)
{
    if (key == 'r')
    {
        bird_x = 120;
        bird_y = 450;
        t = 0;
        launched = false;
        ready = true;
    }
    else if (key == 'q')
    {
        exit(0);
    }
    else if (key == 'b') // back to menu
    {
        gameState = 0;
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

void iMouseMove(int mx, int my) {}
void iMouseDrag(int mx, int my) {}
void iMouseWheel(int dir, int mx, int my) {}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    iSetTimer(20, ballChange);
    srand(time(0));
    iInitialize(WIN_W, WIN_H, "Angry Birds Clone");
    return 0;
}
