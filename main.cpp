#include <raylib.h>
#include <iostream>

#define HEIGHT 720
#define WIDTH 1280
#define TITLE "Pong.exe"
#define FPS 60
#define RADIUS 20
#define BVX 10
#define BVY 7
#define BPX 360
#define BPY 640
#define PH 120
#define PW 25
#define PV 10

Color Green = Color{38, 185, 154, 255};
Color Dark_Green = Color{20, 160, 133, 255};
Color Light_Green = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};

int p1_score = 0;
int p2_score = 0;

class Ball{
    public:
        float x,y;
        int vx,vy;
        int radius;

        void Draw(){
            DrawCircle(x,y,radius,WHITE);
        }

        void ResetBall(){
            // brings the ball back to the center
            x = 1280/2;
            y = 720/2;
        }

        void Update(){
            x += vx;
            y += vy;

            //check if the ball needs to be reset or it needs to bounce off

            if(radius + y >= GetScreenHeight() || y - radius <= 0){
                vy *= -1;
            }
            if(radius + x >= GetScreenWidth()){
                vx *= -1;
                ++p1_score;
            }
            if( x - radius <= 0){
                vx *= -1;
                ++p2_score;
            }
        }
};

class Paddle{
    public:
        float x,y;
        int vx,vy;
        int w,h;

        void Draw(){
            DrawRectangle(x,y,w,h,Dark_Green);
        }

        // void Update(){
        //     if (IsKeyDown())
        // }
};

// obj creation
Ball ball;
Paddle p1;
Paddle p2;

void renderScore(){
        DrawText(TextFormat("%i", p1_score), GetScreenWidth() / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", p2_score), 3 * GetScreenWidth() / 4 - 20, 20, 80, WHITE);
}

// driver code
int main(){
    std::cout<<"Started Raylib window\n";

    InitWindow(WIDTH,HEIGHT,TITLE);

    // defining the ball and paddles
    ball.x = BPX;
    ball.y = BPY;
    ball.vx = BVX;
    ball.vy = BVY;
    ball.radius = RADIUS;
    p1.w = PW;
    p2.w = PW;
    p1.h = PH;
    p2.h = PH;
    p1.x = 10;
    p1.y = GetScreenHeight()/2 - PH/2;
    p2.x = GetScreenWidth()- PW-10;
    p2.y = GetScreenHeight()/2 - PH/2;

    SetTargetFPS(FPS);
    while(!WindowShouldClose()){
        BeginDrawing();
        // DrawText("Welcome to Vault32!",720,360,50,BLACK);
        // rendering the ball in the centre of the screen

        ball.Update();

        // check event for updation of both paddles
        if(IsKeyDown(KEY_DOWN)){
            if(p2.y +PV +PH >= GetScreenHeight()){
                p2.y += 0;
            }
            else p2.y += PV;
            
        }
        if(IsKeyDown(KEY_UP)){
            if(p2.y - PV <= 0){
                p2.y += 0;
            }
            else p2.y -= PV;
        }
        if(IsKeyDown(KEY_S)){
            if(p1.y+PH +PV >= GetScreenHeight()){
                p1.y += 0;
            }
            else p1.y += PV;
        }
        if(IsKeyDown(KEY_W)){
            if(p1.y - PV <= 0){
                p1.y += 0;
            }
            else p1.y -= PV;
        }

        //check for collissions
        if (CheckCollisionCircleRec({ball.x, ball.y}, ball.radius, {p1.x, p1.y, PW, PH})) {
            ball.vx *= -1;
        }
        if (CheckCollisionCircleRec({ball.x, ball.y}, ball.radius, {p2.x, p2.y, PW, PH})) {
            ball.vx *= -1;
        }

        // draw the boundary lines
        // DrawLine(0,50,1280,50,BLACK);
        DrawCircle(GetScreenWidth() / 2, GetScreenHeight()  / 2, 150, Dark_Green);
        DrawLine(GetScreenWidth()/ 2, 0, GetScreenWidth() / 2, GetScreenHeight(), WHITE);

        // draw objects
        ball.Draw();
        p1.Draw();
        p2.Draw();
        
        // render the scores
        renderScore();
        ClearBackground(Light_Green);
        EndDrawing();
    }

    CloseWindow();

}