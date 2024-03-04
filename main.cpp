/// ************************************* ///
/// **********Ali Ekhterachian********** ///
/// *******Ali Reza Taghikhani********** ///
/// *********************************** ///

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <string>
#include <ctime>
#include <fstream>
#include <conio.h>

#define LEFT 9991
#define RIGHT 9992
#define DOWN 9994
#define UP 9993
#define CENTRE 9995
#define FIREBALL 1
#define PUNCH  2
#define INVISIBLE 3
#define THIEF 0


#define PI 3.14159
// zoj ha baraye button samt rast
// fard ha baraye button samt chap
#define BUTTON_BALL 0
#define BUTTON_PLAYERLEFT 2
#define BUTTON_PLAYERRIGHT 4
#define BUTTON_LEFTPOWER 6
#define BUTTON_RIGHTPOWER 8
#define BUTTON_COURT 10
#define BUTTON_NAME 12
#define BUTTON_SHOELEFT 14
#define BUTTON_SHOERIGHT 16

#define LEFT_PLAYER 8881
#define RIGHT_PLAYER 8882


using namespace std;

///Global Variables
const int realScreenHeight = 800*0.8;
const int screenHeight = 800*0.75;
const int screenWidth = 1280*0.8;
string cheatCode = "";
const string cheatCodes[2] = {"right", "left"};

///Structures
struct BackGround
{
    int minXBall;
    int maxXBall;
    int minYBall;
    int maxYBall;
};

struct Ball
{
    double x;//hatman double
    double y;//hatman double
    double dx;
    double dy;
    int rad;
    bool isVisible=true;
    double g=0.2;
    float zarib=0.8;
    const double dx1=7/2;
    const double dx2=5/1.5;
    const double dy1=6/2;
    const double dy2=3/2;
    const double dy3=15/1.5;//gir kardan toop
    const int shootDdx2=100;
    const int shootDdx1=25;
    const int shootUdx=8;
    const int shootUdy=10;
    SDL_Texture *texture;
    int textureNum=0;
    int imagesNum=10;
};

struct Player
{
    double x;//hatman double
    double y;//hatman double
    double dy=0; //for jump
    const double g=0.4;
    double isWorking=true;
    const int headWidth = screenWidth * 0.1*1.1*0.8;
    const int headHeight = screenHeight * 0.15*1.15;

    const int shoeWidth = screenWidth * 0.08*0.7*0.8;
    const int shoeHeight = screenHeight * 0.08*0.79*1.15;
    const double shoeAngleMax=60;
    int shoeStatus=0;
    const int shoeStatus1=19;// Hatman Adad FARD Bashe Va Baghiash Hesab Mishe
    const int width = max(headWidth, 2*shoeWidth);
    const int height = headHeight + shoeHeight;
    int sideOfPlay;
    bool isVisible=true;
    const int step = 5;
    const double dy1=10;
    const int step2=step/5;
    SDL_Texture *headTexture;
    SDL_Texture *leftShoeTexture;
    SDL_Texture *rightShoeTexture;
    int headTextureNum=0;
    int headImagesNum=4;
    int shoeTextureNum=0;
    int shoeImagesNum=4;
};

struct Court
{
    double x;//hatman double
    double y;//hatman double

    const int width = screenWidth;
    const int height = realScreenHeight*0.15;
    bool isVisible=true;
    int textureNum=0;
    int imagesNum=8;
    SDL_Texture *texture;
};

struct Goal
{
    double x;//hatman double
    double y;//hatman double
    bool isVisible=true;
    const int width = screenWidth * 0.08;
    const int height = screenHeight * 0.45;
    const int topBarHeight=height /11;
    SDL_Texture *goalTexture;
    SDL_Texture *netTexture;
};

struct Advertisement
{
    double x;//hatman double
    double y;//hatman double
    bool isVisible=true;
    const int width = screenWidth;
    const int height = screenHeight * 0.15;

    SDL_Texture *texture;
};

struct Fans
{
    double x;//hatman double
    double y;//hatman double
    bool isVisible=true;
    const int width = screenWidth;
    const int height = screenHeight * 0.15;
    const int dy=height/6;
    SDL_Texture *texture;
};

struct Stadium
{
    double x;//hatman double
    double y;//hatman double
    bool isVisible=true;
    const int width = screenWidth;
    const int height = screenHeight * 0.8;

    SDL_Texture *texture;
};

struct Scoreboard
{
    double x;//hatman double
    double y;//hatman double


    const int width = screenWidth*0.5;
    const int height = realScreenHeight*0.3;
    bool isVisible=true;
    bool isTextVisble=false;
    const int scoreWidth = width*0.15;
    const int scoreHeight = height*0.35;

    double leftScoreX = screenWidth*0.03;
    double leftScoreY = screenWidth*0.02;

    double rightScoreX = width - scoreWidth - leftScoreX;
    double rightScoreY = leftScoreY;

    int leftScoreText = 0;
    int rightScoreText = 0;

    SDL_Texture *bodyTexture;
    SDL_Texture *texture0;
    SDL_Texture *texture1;
    SDL_Texture *texture2;
    SDL_Texture *texture3;
    SDL_Texture *texture4;
    SDL_Texture *texture5;
};

struct Power
{
    double x;//hatman double
    double y=40;//hatman double
    const int width = screenWidth*0.2;
    const int height = realScreenHeight*0.15;
    bool isVisible=true;
    int powerType;
    int powerSide;
    int percentage=0;
    const int positive=4;
    const int negetive=-34;
    int dp=positive;
    clock_t time;
    SDL_Texture *punchTexture;
    SDL_Texture *invisibleBallTexture;
    SDL_Texture *fireBallTexture;
    SDL_Texture *thiefTexture;
};
struct Person
{
    string name="";
    int globalScore=0;
    int thisGameScore=0;
};

struct Button
{
    int x;
    int y;
    int width=20;
    int height=20;
    bool isVisible=true;
    bool isClicked=false;
    SDL_Texture *texture;
    /* ~Button()
     {
         SDL_DestroyTexture(texture);
     }*/
};

struct Wall
{
    int x;
    int y;
    bool isVisible=false;
    const int width = screenWidth * 0.08;
    const int height = screenHeight * 0.45;
    SDL_Texture *texture;
};

/// Functions
void clearScreenRGB(SDL_Renderer *Renderer, int R, int G, int B);
void sideRectangleRGB(SDL_Renderer *Renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian );
void ellipse(SDL_Renderer *Renderer, int x, int y, int Radius1, int Radius2, int R, int G, int B, int fill_boolian);
void angleThickLineRGB(SDL_Renderer *Renderer, int x_1, int y_1, int L,double theta,int widht, int R, int G, int B);
void pasteTextureRenderer(SDL_Renderer *m_renderer,SDL_Texture *myTexture,int xp,int yp,int width,int height);
void ballMover (Ball &thisBall, BackGround &thisBack, Goal &goalRight,Goal &goalLeft,Player &playerRight,Player &playerLeft, Wall &wallLeft, Wall &wallRight);
void playerMover (Player &thisPlayer,Player &otherPlayer,Ball &mainBall, int direction,BackGround &thisBack);
void ballDroper (int direction, Ball &thisBall);// toop ro part mikone besamti ke begi
void pasteImageRenderer(SDL_Renderer *m_renderer,int xp,int yp,string addressOfImage,int width,int height);//adres aks migire rasm mikone
void pasteBall(SDL_Renderer *m_renderer,Ball &thisBall); // rasm toop roye renderer
void pastePlayer(SDL_Renderer *m_renderer,Player &thisPlayer); // rasm bazikonha roye renderer VA modirat zaveye kafsh
void pasteCourt(SDL_Renderer *m_renderer,Court &thisCourt); // rasrvm zamin roye renderer
void pasteGoal(SDL_Renderer *m_renderer,Goal &thisGoal); // rasm daaze roye renderer
void pasteWall(SDL_Renderer *m_renderer,Wall &thisWall);
void pasteAdvertisement(SDL_Renderer *m_renderer,Advertisement &thisAdvertisement); // rasm tabligh roye renderer
void pasteFans(SDL_Renderer *m_renderer,Fans thisFans[6],double &fansStatus); // rasm tamashachiha roye renderer
void pasteStadium(SDL_Renderer *m_renderer, Stadium &thisStadium); // rasm stadium roye renderer
void pasteScoreboard(SDL_Renderer *m_renderer, Scoreboard &thisScoreboard); // rasm stadium roye renderer
void pastePowers(SDL_Renderer *m_renderer, Power &thisPower); // rasm stadium roye renderer
void playerMovementRules(Player &thisPlayer,BackGround &thisBack);
int playerBallChecker(Ball &thisBall, Player &thisPlayer);
int maxMinRand(int closedMin, int closedMax);
void shootBall(Ball &thisBall,BackGround &thisBack,Player &thisPlayer, int direction);
void comingInAnimation(Player &playerLeft,Player &playerRight,BackGround &thisBack);
void pasteTextureRenderer(SDL_Renderer *m_renderer,SDL_Texture *myTexture,int xp,int yp,int width,int height,double angle);
bool canPlayerShoot(Player &thisPlayer,Ball &mainBall);
void buttonLRInit(Button buttons[],const int buttonNum,SDL_Renderer *m_renderer,Ball &mainBall,Player &playerLeft,Player &playerRight,Court &thisCourt,Power &leftPower,Power &rightPower, Advertisement &thisAdvertisement);
void buttonLRFunction(SDL_Renderer * m_renderer, Button buttons[], int whichButton,Ball &mainBall,Player &playerLeft,Player &playerRight,Court &thisCourt,Power &leftPower,Power &rightPower, Advertisement &thisAdvertisement);
void pasteButton(SDL_Renderer *m_renderer, Button buttons[], int num);
void pasteButton(SDL_Renderer *m_renderer, Button &thisButton);
bool mouseButtonCheck(int mousex,int mousey, Button &thisButton);
void invisibleBall(Ball &mainBall,Player &thisPlayer,BackGround &thisBack,Power &thisPower);
void punch(Ball &punchBall,Power &thisPower,Player &thisPlayer,Player &otherPlayer);
void powerRules(Power &thisPower,Ball &mainBall,Player &thisPlayer);
void punchBallMover(Ball &punch,Player &playerLeft,Player &playerRight,Power &powerLeft, Power &powerRight);
int goalBall(Ball &mainBall, Goal &gr,Goal &gl,Scoreboard &s,int &goalTime,Player &pl,Player &pr,double &fans,int &side,Power &powerLeft,Power &powerRight);
void readDataBase(string names[],int scores[]);
void writeDataBase(string names[],int scores[]);
void newWindow(int type, SDL_Renderer *m_renderer);
void scoreTable(int scores[10],string names[10],SDL_Renderer *m_renderer);
void updateDataBase(string winnerName,int scores[10],string names[10]);
void writeDataBase(string names[],int scores[]);
Person persons[2];

int main( int argc, char * argv[] )
{

    //Here For Console
    string names[10];
    int scores[10];
    readDataBase(names,scores);

    srand(time(NULL));
    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER ;
    Uint32 WND_flags = SDL_WINDOW_SHOWN ;//| SDL_WINDOW_FULLSCREEN_DESKTOP;//SDL_WINDOW_BORDERLESS ;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Init( SDL_flags );
    SDL_CreateWindowAndRenderer( screenWidth, realScreenHeight, WND_flags, &m_window, &m_renderer );33
    //Pass the focus to the drawing window
    SDL_RaiseWindow(m_window);
    //Get screen resolution
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    /// Initializing

    // mainBall init...
    Ball mainBall;
    mainBall.rad=27;
    mainBall.texture = IMG_LoadTexture( m_renderer,"images/mainBall.png");

    BackGround back1=
    {
        .minXBall=0,
        .maxXBall= screenWidth,
        .minYBall=0,
        .maxYBall= screenHeight
    };


    // court init...
    Court court;
    court.x = 0;
    court.y = realScreenHeight - (court.height);
    court.texture = IMG_LoadTexture( m_renderer,"images/court0.png");
    // goal init
    Goal goalLeft;
    Goal goalRight;
    goalLeft.x = 0;
    goalLeft.y = screenHeight - goalLeft.height;
    goalRight.x = screenWidth - goalRight.width;
    goalRight.y = screenHeight - goalLeft.height;
    goalLeft.goalTexture = IMG_LoadTexture( m_renderer,"images/goalLeft.png");
    goalRight.goalTexture = IMG_LoadTexture( m_renderer,"images/goalRight.png");
    goalLeft.netTexture = IMG_LoadTexture( m_renderer,"images/net.png");
    goalRight.netTexture = IMG_LoadTexture( m_renderer,"images/net.png");
    // wall init...
    Wall leftWall;
    Wall rightWall;

    leftWall.x = goalLeft.x;
    leftWall.y = goalLeft.y;
    rightWall.x = goalRight.x;
    rightWall.y = goalRight.y;

    leftWall.texture = IMG_LoadTexture( m_renderer,"images/wall.png");
    rightWall.texture = IMG_LoadTexture( m_renderer,"images/wall.png");


    // Players init...
    Player playerLeft;
    Player playerRight;
    playerLeft.headTexture = IMG_LoadTexture( m_renderer,"images/playerLeftGoldHead.png");
    playerLeft.rightShoeTexture = IMG_LoadTexture( m_renderer,"images/shoeRight0.png");
    playerLeft.leftShoeTexture = IMG_LoadTexture( m_renderer,"images/shoeLeft0.png");
    playerRight.headTexture = IMG_LoadTexture( m_renderer,"images/playerRightBlackHead.png");
    playerRight.rightShoeTexture = IMG_LoadTexture( m_renderer,"images/shoeRight1.png");
    playerRight.leftShoeTexture = IMG_LoadTexture( m_renderer,"images/shoeLeft1.png");
    playerRight.shoeTextureNum=1;

    playerLeft.x = goalLeft.width;
    playerLeft.y = screenHeight - (playerLeft.headHeight + playerLeft.shoeHeight);
    playerRight.x = screenWidth - (goalRight.width + playerRight.headWidth);
    playerRight.y = screenHeight - (playerRight.headHeight + playerRight.shoeHeight);

    playerLeft.sideOfPlay = LEFT_PLAYER;
    playerRight.sideOfPlay = RIGHT_PLAYER;

    // advertisement init...
    Advertisement advertisement;
    advertisement.x = 0;
    advertisement.y = court.y - advertisement.height;
    advertisement.texture = IMG_LoadTexture( m_renderer,"images/advertisement.png");

    // fans init...
    Fans fans[6];
    for(int i=0; i<6; i++)
    {
        fans[i].x = 0;
        fans[i].y = advertisement.y - fans[i].height;
    }
    fans[0].texture = IMG_LoadTexture( m_renderer,"images/fans1.png");
    fans[1].texture = IMG_LoadTexture( m_renderer,"images/fans2.png");
    fans[2].texture = IMG_LoadTexture( m_renderer,"images/fans3.png");
    fans[3].texture = IMG_LoadTexture( m_renderer,"images/fans4.png");
    fans[4].texture = IMG_LoadTexture( m_renderer,"images/fans5.png");
    fans[5].texture = IMG_LoadTexture( m_renderer,"images/fans6.png");
    double fansStatus=0;

    // stadium init...
    Stadium stadium;

    stadium.x = 0;
    stadium.y = 0;

    stadium.texture = IMG_LoadTexture( m_renderer,"images/stadium.png");


    // scoreboard init...
    Scoreboard scoreboard;
    scoreboard.x = screenWidth*0.25;
    scoreboard.y = 10;

    scoreboard.bodyTexture = IMG_LoadTexture( m_renderer,"images/scoreboard.png");
    scoreboard.texture0 = IMG_LoadTexture( m_renderer,"images/0.png");
    scoreboard.texture1 = IMG_LoadTexture( m_renderer,"images/1.png");
    scoreboard.texture2 = IMG_LoadTexture( m_renderer,"images/2.png");
    scoreboard.texture3 = IMG_LoadTexture( m_renderer,"images/3.png");
    scoreboard.texture4 = IMG_LoadTexture( m_renderer,"images/4.png");
    scoreboard.texture5 = IMG_LoadTexture( m_renderer,"images/5.png");
    // power init ...
    Power powerLeft;
    Power powerRight;

    powerLeft.powerSide = LEFT;
    powerRight.powerSide = RIGHT;
    powerLeft.x= screenWidth*0.15;
    powerRight.x = screenWidth*0.65;
    powerLeft.powerType = PUNCH;
    powerRight.powerType = FIREBALL;

    powerLeft.punchTexture = IMG_LoadTexture( m_renderer,"images/punch.png");
    powerLeft.invisibleBallTexture = IMG_LoadTexture( m_renderer,"images/invisibleBall.png");
    powerLeft.fireBallTexture = IMG_LoadTexture( m_renderer,"images/fireBall.png");
    powerLeft.thiefTexture = IMG_LoadTexture( m_renderer,"images/thief.png");

    powerRight.punchTexture = IMG_LoadTexture( m_renderer,"images/punch.png");
    powerRight.invisibleBallTexture = IMG_LoadTexture( m_renderer,"images/invisibleBall.png");
    powerRight.fireBallTexture = IMG_LoadTexture( m_renderer,"images/fireBall.png");
    powerRight.thiefTexture = IMG_LoadTexture( m_renderer,"images/thief.png");


    Ball punchBall;
    punchBall.texture=IMG_LoadTexture(m_renderer,"images/punchBall.png");
    punchBall.rad=20;
    punchBall.g=0;
    punchBall.isVisible=false;
    /// //////////////////////////////////////////////// ///
    /// ***************MENU****************** ///
    /// /////////////////////////////////////////////// ///
    {
        bool quit=false;
        const int buttonLRNum=18; // BAYAD ZOJ BASHE
        int mousex=0,mousey=0;
        Button buttons[buttonLRNum];
        ballDroper(CENTRE,mainBall);
        buttonLRInit(buttons,buttonLRNum,m_renderer,mainBall,playerLeft,playerRight,court,powerLeft,powerRight,advertisement);
        Button startGame;
        startGame.width=screenWidth/8;
        startGame.height=screenHeight/9;
        startGame.x=screenWidth/2-startGame.width/2;
        startGame.y=370;
        startGame.texture=IMG_LoadTexture(m_renderer,"images/startGameButton.png");
        SDL_Event *event = new SDL_Event();
        while (!quit)
        {
            clearScreenRGB(m_renderer,-1,-1,-1);
            pasteCourt(m_renderer,court);
            pasteStadium(m_renderer, stadium);
            pasteScoreboard(m_renderer, scoreboard);
            pastePowers(m_renderer, powerLeft);
            pastePowers(m_renderer, powerRight);
            //pasteFans(m_renderer,fans,fansStatus);
            pasteAdvertisement(m_renderer,advertisement);
            pasteBall(m_renderer,mainBall);
            pastePlayer(m_renderer,playerLeft);
            pastePlayer(m_renderer,playerRight);
            //pasteGoal(m_renderer,goalLeft);
            //pasteGoal(m_renderer,goalRight);
            pasteButton(m_renderer,buttons,buttonLRNum);
            pasteButton(m_renderer,startGame);
            if(persons[0].name.length()>0)
                textRGBA(m_renderer,buttons[BUTTON_NAME].x+5, buttons[BUTTON_NAME].y+10, persons[0].name.c_str(), 2, 20, 0,0, 0, 255);
            if(persons[1].name.length()>0)
                textRGBA(m_renderer,buttons[BUTTON_NAME+1].x+5, buttons[BUTTON_NAME+1].y+10, persons[1].name.c_str(), 2, 20, 0,0, 0, 255);


            SDL_RenderPresent(m_renderer);
            SDL_Delay(20);

            if( SDL_PollEvent( event ) )
            {
                if( event->type == SDL_MOUSEBUTTONDOWN )
                {
                    SDL_GetMouseState(&mousex,&mousey);
                    if(mouseButtonCheck(mousex,mousey,startGame))
                    {
                        quit=true;
                    }
                    for(int i=0; i<buttonLRNum; i++)
                    {
                        if(mouseButtonCheck(mousex,mousey,buttons[i]) )
                        {
                            buttonLRFunction( m_renderer,buttons, i,mainBall,playerLeft,playerRight,court,powerLeft,powerRight, advertisement);
                        }
                    }
                }
            }
        }
    }



    {
        /// //////////////////////////////////////////////// ///
        /// ************ANIMATION*************** ///
        /// /////////////////////////////////////////////// ///

        int stepNum=(playerRight.x-((back1.maxXBall-back1.minXBall)/2))/playerRight.step;
        stepNum++;
        for(int i=0; i<=stepNum; i++)
        {
            playerMovementRules(playerLeft,back1);
            playerMovementRules(playerRight,back1);
            pasteCourt(m_renderer,court);
            pasteStadium(m_renderer, stadium);
            pasteScoreboard(m_renderer, scoreboard);
            pastePowers(m_renderer, powerLeft);
            pastePowers(m_renderer, powerRight);
            pasteFans(m_renderer,fans,fansStatus);
            pasteAdvertisement(m_renderer,advertisement);
            // pasteBall(m_renderer,mainBall);
            pastePlayer(m_renderer,playerLeft);
            pastePlayer(m_renderer,playerRight);
            pasteWall(m_renderer,leftWall);
            pasteWall(m_renderer,rightWall);
            pasteGoal(m_renderer,goalLeft);
            pasteGoal(m_renderer,goalRight);
            SDL_Delay(20);
            SDL_RenderPresent(m_renderer);
            playerMover(playerLeft,playerRight,mainBall,RIGHT,back1);
            playerMover(playerRight,playerLeft,mainBall,LEFT,back1);
        }
        bool isContinue=true;
        playerMover(playerLeft,playerRight,mainBall,UP,back1);
        playerMover(playerRight,playerLeft,mainBall,UP,back1);
        do
        {
            playerMovementRules(playerLeft,back1);
            playerMovementRules(playerRight,back1);
            pasteCourt(m_renderer,court);
            pasteStadium(m_renderer, stadium);
            pasteScoreboard(m_renderer, scoreboard);
            pastePowers(m_renderer, powerLeft);
            pastePowers(m_renderer, powerRight);
            pasteFans(m_renderer,fans,fansStatus);
            pasteAdvertisement(m_renderer,advertisement);
            // pasteBall(m_renderer,mainBall);
            pastePlayer(m_renderer,playerLeft);
            pastePlayer(m_renderer,playerRight);
            pasteWall(m_renderer,leftWall);
            pasteWall(m_renderer,rightWall);
            pasteGoal(m_renderer,goalLeft);
            pasteGoal(m_renderer,goalRight);
            SDL_Delay(20);
            SDL_RenderPresent(m_renderer);
            playerMover(playerLeft,playerRight,mainBall,RIGHT,back1);
            playerMover(playerRight,playerLeft,mainBall,LEFT,back1);
        }
        while(!(playerRight.y+playerRight.height>=back1.maxYBall ||playerLeft.y+playerLeft.height>=back1.maxYBall));

        for(int i=0; i<stepNum; i++)
        {
            //playerMovementRules(playerLeft,back1);
            playerMovementRules(playerRight,back1);
            pasteCourt(m_renderer,court);
            pasteStadium(m_renderer, stadium);
            pasteScoreboard(m_renderer, scoreboard);
            pastePowers(m_renderer, powerLeft);
            pastePowers(m_renderer, powerRight);
            pasteFans(m_renderer,fans,fansStatus);
            pasteAdvertisement(m_renderer,advertisement);
            pastePlayer(m_renderer,playerLeft);
            pastePlayer(m_renderer,playerRight);
            pasteWall(m_renderer,leftWall);
            pasteWall(m_renderer,rightWall);
            pasteGoal(m_renderer,goalLeft);
            pasteGoal(m_renderer,goalRight);
            SDL_Delay(20);
            SDL_RenderPresent(m_renderer);
            playerMover(playerLeft,playerRight,mainBall,LEFT,back1);
            playerMover(playerRight,playerLeft,mainBall,RIGHT,back1);
        }
        // SDL_Delay(1000);
        for(int i=3; i>-1; i--)
        {
            scoreboard.leftScoreText=i;
            scoreboard.rightScoreText=i;
            scoreboard.isTextVisble=true;
            pasteCourt(m_renderer,court);
            pasteStadium(m_renderer, stadium);
            pasteScoreboard(m_renderer, scoreboard);
            pastePowers(m_renderer, powerLeft);
            pastePowers(m_renderer, powerRight);
            pasteFans(m_renderer,fans,fansStatus);
            pasteAdvertisement(m_renderer,advertisement);

            pasteBall(m_renderer,mainBall);
            pastePlayer(m_renderer,playerLeft);
            pastePlayer(m_renderer,playerRight);

            pasteWall(m_renderer,leftWall);
            pasteWall(m_renderer,rightWall);
            pasteGoal(m_renderer,goalLeft);
            pasteGoal(m_renderer,goalRight);

            SDL_Delay(1000);
            SDL_RenderPresent(m_renderer);
        }
    }

    SDL_Event *event = new SDL_Event();
    const clock_t startTime=clock();
    powerRight.time=clock();
    powerLeft.time=clock();
    bool quit=false;
    ballDroper(CENTRE, mainBall);
    const Uint8 *keyBoardEvent=SDL_GetKeyboardState(NULL);
    int goalTime=-1;
    int goalSide;
    int kickFireBall=0;
    int kickFireBallPStep=0;
    int playStatus;
    while (!quit)
    {
        clearScreenRGB(m_renderer,-1,-1,-1);
        if(kickFireBall==0)
        {
            ballMover(mainBall, back1,goalRight,goalLeft,playerRight,playerLeft, leftWall, rightWall);
        }
        else if(kickFireBall>0)
        {
            if(mainBall.x+mainBall.rad>=playerRight.x)
            {
                kickFireBallPStep=20;
                kickFireBall=0;
            }
            mainBall.x+=20;
        }
        else if(kickFireBall<0)
        {

            if(mainBall.x-mainBall.rad<=playerLeft.x+playerLeft.width)
            {
                kickFireBallPStep=-20;
                kickFireBall=0;
            }
            mainBall.x-=20;
        }
        punchBallMover(punchBall,playerLeft,playerRight,powerLeft,powerRight);
        if(kickFireBallPStep==0)
        {
            playerMovementRules(playerLeft,back1);
            playerMovementRules(playerRight,back1);
        }
        else if(kickFireBallPStep>0)
        {
            playerMovementRules(playerLeft,back1);
            playerRight.x+=10;
            kickFireBallPStep--;
            if(kickFireBallPStep==0)
            {
                powerLeft.time=clock();
                powerLeft.dp=powerLeft.negetive;
                playerRight.isWorking=false;
            }
        }
        else if(kickFireBallPStep<0)
        {
            playerMovementRules(playerRight,back1);
            playerLeft.x-=10;
            kickFireBallPStep++;
            if(kickFireBallPStep==0)
            {
                powerRight.time=clock();
                powerRight.dp=powerRight.negetive;
                playerLeft.isWorking=false;
            }
        }

        powerRules(powerLeft,mainBall,playerRight);
        powerRules(powerRight,mainBall,playerLeft);
        playStatus=goalBall(mainBall,goalRight,goalLeft,scoreboard,goalTime,playerLeft,playerRight,fansStatus,goalSide,powerLeft,powerRight);
        quit=(playStatus!=0);
        pasteCourt(m_renderer,court);
        pasteStadium(m_renderer, stadium);
        pasteScoreboard(m_renderer, scoreboard);
        pastePowers(m_renderer, powerLeft);
        pastePowers(m_renderer, powerRight);
        //  textRGBA(m_renderer,powerLeft.x,powerLeft.y+powerLeft.height, persons[1].name.c_str(), 2, 20, 0,0,0, 0);
        // textRGBA(m_renderer,powerRight.x,powerRight.y+powerRight.height, persons[0].name.c_str(), 2, 20, 0,0,0, 0);
        pasteFans(m_renderer,fans,fansStatus);
        pasteAdvertisement(m_renderer,advertisement);

        pasteBall(m_renderer,mainBall);
        pasteBall(m_renderer,punchBall);
        pastePlayer(m_renderer,playerLeft);
        pastePlayer(m_renderer,playerRight);

        pasteWall(m_renderer,leftWall);
        pasteWall(m_renderer,rightWall);
        pasteGoal(m_renderer,goalLeft);
        pasteGoal(m_renderer,goalRight);

        SDL_Delay(15);
        SDL_RenderPresent(m_renderer);
        SDL_PumpEvents();
        // detecting cheatCode
        if(keyBoardEvent[SDL_SCANCODE_L])
        {
            if(cheatCode[cheatCode.length() - 1] != 'l')
            {
                cheatCode += 'l';
            }
        }

        if(keyBoardEvent[SDL_SCANCODE_A])
        {
            if(cheatCode[cheatCode.length() - 1] != 'a')
            {
                cheatCode += 'a';
            }
        }

        if(keyBoardEvent[SDL_SCANCODE_R])
        {
            if(cheatCode[cheatCode.length() - 1] != 'r')
            {
                cheatCode += 'r';
            }
        }

        if(keyBoardEvent[SDL_SCANCODE_G])
        {
            if(cheatCode[cheatCode.length() - 1] != 'g')
            {
                cheatCode += 'g';
            }
        }

        if(keyBoardEvent[SDL_SCANCODE_E])
        {
            if(cheatCode[cheatCode.length() - 1] != 'e')
            {
                cheatCode += 'e';
            }
        }

        if(keyBoardEvent[SDL_SCANCODE_F])
        {
            if(cheatCode[cheatCode.length() - 1] != 'f')
            {
                cheatCode += 'f';
            }
        }

        if(keyBoardEvent[SDL_SCANCODE_I])
        {
            if(cheatCode[cheatCode.length() - 1] != 'i')
            {
                cheatCode += 'i';
            }
        }

        if(keyBoardEvent[SDL_SCANCODE_T])
        {
            if(cheatCode[cheatCode.length() - 1] != 't')
            {
                cheatCode += 't';
            }
        }

        if(keyBoardEvent[SDL_SCANCODE_H])
        {
            if(cheatCode[cheatCode.length() - 1] != 'h')
            {
                cheatCode += 'h';
            }
        }

        for(int i = 0; i < 2; i++)
        {
            if(strstr(cheatCode.c_str(),cheatCodes[i].c_str()))
            {
                if(cheatCodes[i] == "left")
                {
                    leftWall.isVisible = !leftWall.isVisible;
                }

                if(cheatCodes[i] == "right")
                {
                    rightWall.isVisible = !rightWall.isVisible;
                }
                cheatCode = "";
            }
        }

        if(keyBoardEvent[SDL_SCANCODE_A]&&!keyBoardEvent[SDL_SCANCODE_D])
        {
            if(playerLeft.isWorking)
                playerMover (playerLeft, playerRight,mainBall,LEFT,back1);
        }
        if(keyBoardEvent[SDL_SCANCODE_D]&&!keyBoardEvent[SDL_SCANCODE_A])
        {
            if(playerLeft.isWorking)f

                playerMover (playerLeft, playerRight,mainBall,RIGHT,back1);
        }
        if(keyBoardEvent[SDL_SCANCODE_W])
        {
            if(playerLeft.isWorking)
                playerMover(playerLeft,playerRight,mainBall,UP,back1);
        }
        if(keyBoardEvent[SDL_SCANCODE_S] && !keyBoardEvent[SDL_SCANCODE_Q] )
        {
            if(playerLeft.isWorking)
                shootBall(mainBall,back1,playerLeft,DOWN);
        }
        if(keyBoardEvent[SDL_SCANCODE_Q] && !keyBoardEvent[SDL_SCANCODE_S] )
        {
            if(playerLeft.isWorking)
                shootBall(mainBall,back1,playerLeft,UP);
        }
        if(keyBoardEvent[SDL_SCANCODE_E] )
        {
            if(powerLeft.percentage>=100)
            {
                switch(powerLeft.powerType)
                {
                case INVISIBLE:
                {
                    invisibleBall(mainBall,playerLeft,back1,powerLeft);
                    break;
                }
                case PUNCH:
                {
                    punch(punchBall,powerLeft,playerLeft,playerRight);
                    break;
                }
                case FIREBALL:
                {
                    if(canPlayerShoot(playerLeft,mainBall))
                    {
                        kickFireBall=1;
                    }
                    shootBall(mainBall,back1,playerLeft,DOWN);
                    break;
                }
                case THIEF:
                {
                                        int r=maxMinRand(0,299)%3;
                    switch(r)
                    {
                    case 1:
                        invisibleBall(mainBall,playerLeft,back1,powerLeft);
                        break;
                    case 2:
                        punch(punchBall,powerLeft,playerLeft,playerRight);
                        break;
                    case 0:
                    {
                        if(canPlayerShoot(playerLeft,mainBall))
                        {
                            kickFireBall=1;
                        }
                        shootBall(mainBall,back1,playerLeft,DOWN);
                        break;
                    }
                    }
                }
                }
            }
        }
        if(keyBoardEvent[SDL_SCANCODE_LEFT] && !keyBoardEvent[SDL_SCANCODE_RIGHT] )
        {
            if(playerRight.isWorking)
                playerMover (playerRight, playerLeft,mainBall,LEFT,back1);
        }
        if(keyBoardEvent[SDL_SCANCODE_RIGHT] && !keyBoardEvent[SDL_SCANCODE_LEFT] )
        {
            if(playerRight.isWorking)
                playerMover (playerRight, playerLeft,mainBall,RIGHT,back1);
        }
        if(keyBoardEvent[SDL_SCANCODE_UP])
        {
            if(playerRight.isWorking)
                playerMover (playerRight, playerLeft,mainBall,UP,back1);
        }
        if(keyBoardEvent[SDL_SCANCODE_DOWN]&& !keyBoardEvent[SDL_SCANCODE_L])
        {
            if(playerRight.isWorking)
                shootBall(mainBall,back1,playerRight,DOWN);
        }
        if(keyBoardEvent[SDL_SCANCODE_L]&& !keyBoardEvent[SDL_SCANCODE_DOWN])
        {
            if(playerRight.isWorking)
                shootBall(mainBall,back1,playerRight,UP);
        }
        if(keyBoardEvent[SDL_SCANCODE_K] )
        {
            if(powerRight.percentage>=100)
            {
                switch(powerRight.powerType)
                {
                case INVISIBLE:
                {
                    invisibleBall(mainBall,playerRight,back1,powerRight);
                    break;
                }
                case PUNCH:
                {
                    punch(punchBall,powerRight,playerRight,playerLeft);
                    break;
                }
                case FIREBALL:
                {
                    if(canPlayerShoot(playerRight,mainBall))
                    {
                        kickFireBall=-1;
                        shootBall(mainBall,back1,playerRight,DOWN);
                    }
                    break;
                }
                case THIEF:
                    int r=maxMinRand(0,299)%3;
                    switch(r)
                    {
                    case 1:
                        invisibleBall(mainBall,playerRight,back1,powerRight);
                        break;
                    case 2:
                        punch(punchBall,powerRight,playerRight,playerLeft);
                        break;
                    case 0:
                        if(canPlayerShoot(playerRight,mainBall))
                        {
                            kickFireBall=-1;
                            shootBall(mainBall,back1,playerRight,DOWN);
                        }
                        break;
                    }
                }
            }
        }
        if(keyBoardEvent[SDL_SCANCODE_SPACE])
        {
            clock_t stopf=clock();
            SDL_Event *e= new SDL_Event();
            int w=screenWidth*0.5;
            int h=realScreenHeight*0.8;
            int x=screenWidth/2-w/2;
            int y=realScreenHeight/2-h/2;
            sideRectangleRGB(m_renderer,x,y,w,h,100,200,100,1);
            for(int i=0; i<10; i++)
            {
                if(names[i].length()>0)
                    textRGBA(m_renderer,x+w/8,y+h/12+i*h/12,names[i].c_str(),2,20,0,0,0,-1);
                textRGBA(m_renderer,x+w/2,y+h/12+i*h/12,to_string(scores[i]).c_str(),2,20,0,0,0,-1);
            }
            SDL_RenderPresent(m_renderer);
            bool isContinue=true;
            while ( isContinue)
            {
                if( SDL_PollEvent( e ) )
                {
                    if( e->type == SDL_MOUSEBUTTONDOWN )
                    {
                        isContinue=false;
                    }
                }
            }
            clock_t stopl=clock();
            powerRight.time=powerRight.time+stopf-stopl;
            powerLeft.time=powerLeft.time+stopf-stopl;
        }
        if(keyBoardEvent[SDL_SCANCODE_ESCAPE])
        {
            quit=true;
            break;
        }
    }
    if(playStatus!=0)
    {
        if(playStatus==RIGHT)
        {
        updateDataBase( persons[0].name,scores,names);
        }
        else if(playStatus==LEFT)
        {
        updateDataBase( persons[1].name,scores,names);
        }
        newWindow(playStatus,m_renderer);
        int w=screenWidth*0.5;
        int h=realScreenHeight*0.8;
        int x=screenWidth/2-w/2;
        int y=realScreenHeight/2-h/2;
        sideRectangleRGB(m_renderer,x,y,w,h,100,200,100,1);
        for(int i=0; i<10; i++)
        {
            if(names[i].length()>0)
                textRGBA(m_renderer,x+w/8,y+h/12+i*h/12,names[i].c_str(),2,20,0,0,0,-1);
            textRGBA(m_renderer,x+w/2,y+h/12+i*h/12,to_string(scores[i]).c_str(),2,20,0,0,0,-1);
        }

        //pasteImageRenderer(m_renderer,x,y,"images/cadr.png",w,h);
        SDL_RenderPresent(m_renderer);
            bool isContinue=true;
            while ( isContinue)
            {
           //     SDL_Delay(30);
            SDL_Event *e= new SDL_Event();
                if( SDL_PollEvent( e ) )
                {
                    if( e->type == SDL_MOUSEBUTTONDOWN )
                    {
                        isContinue=false;
                    }
                }
            }
    }
    writeDataBase(names,scores);
    SDL_DestroyWindow( m_window );
    SDL_DestroyRenderer( m_renderer );
    SDL_Quit();
    return 0;
}



void angleThickLineRGB(SDL_Renderer *Renderer, int x_1, int y_1, int L, double theta,int widht, int R, int G, int B )
{
    int x_2 = x_1 + L*cos(theta);
    int y_2 = y_1 - L*sin(theta);
    thickLineRGBA(Renderer,x_1,y_1,x_2,y_2,widht,R,G,B,255);
    //  SDL_RenderPresent(Renderer);
}

void sideRectangleRGB(SDL_Renderer *Renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian )
{
    SDL_Rect rectangle ;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;
    SDL_SetRenderDrawColor(Renderer, R, G, B, 255);
    if (fill_boolian==1)
        SDL_RenderFillRect(Renderer, &rectangle);
    SDL_RenderDrawRect(Renderer, &rectangle);
    // SDL_RenderPresent(Renderer);
}

void ellipse(SDL_Renderer *Renderer, int x, int y, int Radius1, int Radius2, int R, int G, int B, int fill_boolian)
{
    if(fill_boolian==1)
        filledEllipseRGBA(Renderer,x,y,Radius1,Radius2,R,G,B,255);

    if(fill_boolian==0)
        ellipseRGBA(Renderer,x,y,Radius1,Radius2,R,G,B,255);
    // SDL_RenderPresent(Renderer);
}

void clearScreenRGB(SDL_Renderer *Renderer, int R, int G, int B)
{
    SDL_SetRenderDrawColor( Renderer, R, G, B, 255 );
    SDL_RenderClear( Renderer );
    // Show the window
    //SDL_RenderPresent( Renderer );
}

void ballMover (Ball &thisBall, BackGround &thisBack, Goal &rightGoal,Goal &leftGoal,Player &rightPlayer,Player &leftPlayer, Wall &wallLeft, Wall &wallRight)
{
    int topBarYDistance;
    int temp;
    if(thisBall.dx<thisBall.g/4.0 && thisBall.dx>thisBall.g/-4.0)
    {
        thisBall.dx=0;
    }
    if(thisBall.y <= thisBack.minYBall + thisBall.rad)
    {
        // cout << "SORAt Avalye ZYAD !!!!!!!!!!!";
    }
    if(thisBall.y+thisBall.rad+thisBall.dy>=thisBack.maxYBall) // barkhord be zamin
    {
        thisBall.dy*= -1*thisBall .zarib;
        thisBall.dx*= thisBall .zarib;
    }
    if(thisBall.x <= thisBack.minXBall+thisBall .rad)
    {
        thisBall.dx*=-1;
    }
    if(thisBall.x + thisBall.rad >= thisBack.maxXBall)
    {
        thisBall.dx*=-1;
    }
///////////////////////////////////// GOALS  ///////////////////////////////////////////////////
    topBarYDistance=((leftGoal.y+(leftGoal.topBarHeight/2))-thisBall.y); ///Darvazeh Chap
    if((thisBall.x-thisBall.rad<=leftGoal.width+leftGoal.x) &&abs(topBarYDistance)<=thisBall.rad) // tirakHa
    {
        if(abs(topBarYDistance)<=thisBall.rad*0.4)//jeloye tirak
        {
            if(thisBall.dx<0)
                thisBall.dx*=-1;
        }


        else if(abs(topBarYDistance)>=thisBall.rad*0.7)//zir tirak
        {
            if(topBarYDistance*thisBall.dy>0 )
            {
                thisBall.dy*=-1;
                thisBall.y=leftGoal.y-thisBall.rad;
            }
        }
        else //goshe tirak
        {
            if(topBarYDistance*thisBall.dy>0 )
            {
                thisBall.dy*=-1;
            }
            thisBall.dx*=-1;
        }

    }
    topBarYDistance=((rightGoal.y+(rightGoal.topBarHeight/2))-thisBall.y);/// Darvazeh Rast
    if((thisBall.x+thisBall.rad>=rightGoal.x) &&abs(topBarYDistance)<=thisBall.rad) // tirakHa
    {
        if(abs(topBarYDistance)<=thisBall.rad*0.4)//jeloye tirak
        {
            if(thisBall.dx>0)
                thisBall.dx*=-1;
        }
        else if(abs(topBarYDistance)>=thisBall.rad*0.81)//zir tirak
        {
            if(topBarYDistance*thisBall.dy>0 )
            {
                thisBall.dy*=-1;
                thisBall.y=leftGoal.y-thisBall.rad;
            }
        }
        else //goshe tirak
        {
            if(topBarYDistance*thisBall.dy>0 )
            {
                thisBall.dy*=-1;
            }
            thisBall.dx*=-1;
        }
    }

    if(wallLeft.isVisible)
    {
        if((thisBall.x-thisBall.rad  <= (wallLeft.x + wallLeft.width)) && (thisBall.y >= wallLeft.y))
        {
            thisBall.dx *= -1;

        }
    }

    if(wallRight.isVisible)
    {
        if(thisBall.x+thisBall.rad >= wallRight.x && (thisBall.y >= wallRight.y))
        {
            thisBall.dx *= -1;
        }
    }
////////////////////////////////   PLAYER      /////////////////////////////////////////////////
    temp=playerBallChecker(thisBall,rightPlayer);
    switch(temp)
    {
    case(UP):
    {
        if(thisBall.dy<0)
            thisBall.dy*=-1;
        break;
        break;
    }
    case(DOWN):
    {
        if(thisBall.dy>0)
            thisBall.dy*=-1;
        break;
    }
    case(LEFT):
    {
        if(thisBall.dx<0)
            thisBall.dx*=-1;
        if(thisBall.dx==0)
        {
            thisBall.dx=thisBall.dx2;
        }
        break;
    }
    case(RIGHT):
    {
        if(thisBall.dx>0)
        {
            thisBall.dx*=-1;
        }
        if(thisBall.dx==0)
        {
            thisBall.dx=-thisBall.dx2;
        }
        break;
    }
    }
    temp=playerBallChecker(thisBall,leftPlayer);
    switch(temp)
    {
    case(UP):
    {
        if(thisBall.dy<0)
            thisBall.dy*=-1;
        break;
        break;
    }
    case(DOWN):
    {
        if(thisBall.dy>0)
            thisBall.dy*=-1;
        break;
    }
    case(LEFT):
    {
        if(thisBall.dx<0)
            thisBall.dx*=-1;
        if(thisBall.dx==0)
        {
            thisBall.dx=+thisBall.dx2;
        }
        break;
    }
    case(RIGHT):
    {
        if(thisBall.dx>0)
            thisBall.dx*=-1;
        if(thisBall.dx==0)
        {
            thisBall.dx=-thisBall.dx2;
        }

        break;
    }
    }
    // gir kardan top beyn do nafar
    if(playerBallChecker(thisBall,rightPlayer)!=0 && playerBallChecker(thisBall,leftPlayer)!=0&&thisBall.y+thisBall.rad>=thisBack.maxYBall)
    {
        thisBall.dy=-thisBall.dy3;
        thisBall.dx=maxMinRand(-3,3);
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(thisBall.dy<=thisBall.g && thisBall.dy>=thisBall.g*-1 && thisBack.maxYBall-thisBall.rad-thisBall.y<=thisBall.g)
    {
        thisBall.dy =0;
        thisBall.y=thisBack.maxYBall-thisBall.rad;
    }
    else
    {
        thisBall.dy += thisBall.g;
    }
    thisBall.y += thisBall.dy;
    thisBall.x += thisBall.dx;
    if(thisBall.y+thisBall.rad>thisBack.maxYBall)
    {
        thisBall.y=thisBack.maxYBall-thisBall.rad;
    }
    if (thisBall.x+thisBall.rad>thisBack.maxXBall)
    {
        thisBall.x=thisBack.maxXBall-thisBall.rad;
    }
    if (thisBall.x-thisBall.rad<thisBack.minXBall)
    {
        thisBall.x=thisBall.rad+thisBack.minXBall;
    }
   if(wallLeft.isVisible)
    {
        if((thisBall.x-thisBall.rad  <= (wallLeft.x + wallLeft.width)) && (thisBall.y-thisBall.rad >= wallLeft.y))
        {
            thisBall.x=wallLeft.x+wallLeft.width+thisBall.rad;
        }
    }

    if(wallRight.isVisible)
    {
        if(thisBall.x+thisBall.rad >= wallRight.x && (thisBall.y+thisBall.rad >= wallRight.y))
        {
            thisBall.x=wallRight.x-thisBall.rad;
        }
    }
}


void playerMover (Player &thisPlayer,Player &otherPlayer,Ball &mainBall,int dirction,BackGround &thisBack)
{
    if (dirction==UP)
    {
        if(thisPlayer.y+thisPlayer.height-thisPlayer.dy>=thisBack.maxYBall)
        {
            thisPlayer.dy =- thisPlayer.dy1;
        }
    }
    else if(dirction==LEFT)
    {
        if((thisPlayer.x - thisPlayer.step-mainBall.rad-mainBall.rad >= 0) && (thisPlayer.sideOfPlay==LEFT_PLAYER || thisPlayer.x-thisPlayer.step>=otherPlayer.x+otherPlayer.width))
        {
            thisPlayer.x -= thisPlayer.step;
        }
    }
    else if(dirction == RIGHT)
    {
        if( (thisPlayer.x + thisPlayer.width + thisPlayer.step+mainBall.rad*2 <= screenWidth)&& (thisPlayer.sideOfPlay==RIGHT_PLAYER || thisPlayer.x+thisPlayer.step+thisPlayer.width<=otherPlayer.x))
        {
            thisPlayer.x += thisPlayer.step;
        }
    }
    if(playerBallChecker(mainBall,thisPlayer)!=0)
    {
        switch (dirction)
        {
        case LEFT:
            mainBall.dx-=mainBall.dx2/2;
            thisPlayer.x+=thisPlayer.step2;
            break;
        case RIGHT:
            mainBall.dx+=mainBall.dx2/2;
            thisPlayer.x-=thisPlayer.step2;
            break;
        }
    }

}

void ballDroper (int direction,Ball &thisBall)
{
    thisBall.x=screenWidth/2;
    thisBall.y=screenHeight/2;
    thisBall.dy=thisBall.dy1;
    if(direction == LEFT)
    {
        thisBall.dx=thisBall.dx1 *-1;
    }
    else if(direction == RIGHT)
    {
        thisBall.dx=thisBall.dx1;
    }
    else if(direction == CENTRE)
    {
        thisBall.dx=0;
    }
}

void pasteTextureRenderer(SDL_Renderer *m_renderer,SDL_Texture *myTexture,int xp,int yp,int width,int height)
{
    int w1, h1;
    SDL_QueryTexture(myTexture, NULL, NULL, &w1, &h1);
    SDL_Rect texr1;
    texr1.x = xp;
    texr1.y = yp;
    texr1.w = width;
    texr1.h = height;
    SDL_RenderCopy( m_renderer, myTexture, NULL, &texr1);
    //SDL_DestroyTexture(myTexture);
}
/// Angle OverLoad
void pasteTextureRenderer(SDL_Renderer *m_renderer,SDL_Texture *myTexture,int xp,int yp,int width,int height,double angle)
{
    int w1, h1;
    SDL_QueryTexture(myTexture, NULL, NULL, &w1, &h1);
    SDL_Rect texr1;
    texr1.x = xp;
    texr1.y = yp;
    texr1.w = width;
    texr1.h = height;
    SDL_RenderCopyEx(m_renderer,myTexture,NULL,&texr1,angle,NULL,SDL_FLIP_NONE);
}

void pasteImageRenderer(SDL_Renderer *m_renderer,int xp,int yp,string addressOfImage,int width,int height)
{
    int n = addressOfImage.length();
    char char_array[n+1];
    strcpy(char_array, addressOfImage.c_str());
    SDL_Texture *myTexture;
    myTexture = IMG_LoadTexture( m_renderer, char_array);
    int w1, h1;
    SDL_QueryTexture(myTexture, NULL, NULL, &w1, &h1);
    SDL_Rect texr1;
    texr1.x = xp;
    texr1.y = yp;
    texr1.w = width;
    texr1.h = height;
    SDL_RenderCopy( m_renderer, myTexture, NULL, &texr1);
    SDL_DestroyTexture(myTexture);
}

void pasteBall(SDL_Renderer *m_renderer,Ball &thisBall)
{
    if(thisBall.isVisible)
    {
        pasteTextureRenderer(m_renderer,thisBall.texture,thisBall.x-thisBall.rad,thisBall.y-thisBall.rad,thisBall.rad*2,thisBall.rad*2);
    }
}

void pastePlayer(SDL_Renderer *m_renderer,Player &thisPlayer)
{
    double x=thisPlayer.x ;
    double w=thisPlayer.shoeAngleMax/((1+thisPlayer.shoeStatus1)/2);
    double angle=0;

    if(thisPlayer.isVisible)
    {
        pasteTextureRenderer(m_renderer, thisPlayer.headTexture, (x), thisPlayer.y, thisPlayer.headWidth, thisPlayer.headHeight);
        if(thisPlayer.sideOfPlay==RIGHT_PLAYER)
        {
            angle=-1*(thisPlayer.shoeAngleMax-(abs(((thisPlayer.shoeStatus1+1)/2)- thisPlayer.shoeStatus)*w));
            pasteTextureRenderer(m_renderer, thisPlayer.leftShoeTexture, (x + (0.5 * thisPlayer.headWidth)), thisPlayer.y + thisPlayer.headHeight, thisPlayer.shoeWidth, thisPlayer.shoeHeight);
            pasteTextureRenderer(m_renderer, thisPlayer.rightShoeTexture, (x + (0.5 * thisPlayer.headWidth) - thisPlayer.shoeWidth), thisPlayer.y + thisPlayer.headHeight, thisPlayer.shoeWidth, thisPlayer.shoeHeight,angle);
        }
        else
        {
            angle=(thisPlayer.shoeAngleMax-(abs(((thisPlayer.shoeStatus1+1)/2)- thisPlayer.shoeStatus)*w));
            pasteTextureRenderer(m_renderer, thisPlayer.rightShoeTexture, (x + (0.5 * thisPlayer.headWidth) - thisPlayer.shoeWidth), thisPlayer.y + thisPlayer.headHeight, thisPlayer.shoeWidth, thisPlayer.shoeHeight);
            pasteTextureRenderer(m_renderer, thisPlayer.leftShoeTexture, (x + (0.5 * thisPlayer.headWidth)), thisPlayer.y + thisPlayer.headHeight, thisPlayer.shoeWidth, thisPlayer.shoeHeight,angle);
        }
    }
    if(thisPlayer.shoeStatus>0)
    {
        thisPlayer.shoeStatus-=1;
    }
}

void pasteCourt(SDL_Renderer *m_renderer,Court &thisCourt)
{
    if(thisCourt.isVisible)
    {
        pasteTextureRenderer(m_renderer, thisCourt.texture, thisCourt.x, thisCourt.y, thisCourt.width, thisCourt.height);
    }
}

void pasteGoal(SDL_Renderer *m_renderer,Goal &thisGoal)
{
    if(thisGoal.isVisible)
    {
        pasteTextureRenderer(m_renderer, thisGoal.goalTexture, thisGoal.x, thisGoal.y, thisGoal.width, thisGoal.height);
        pasteTextureRenderer(m_renderer, thisGoal.netTexture, thisGoal.x, thisGoal.y, thisGoal.width, thisGoal.height);
    }
}

void pasteWall(SDL_Renderer *m_renderer,Wall &thisWall)
{
    if(thisWall.isVisible)
    {
        pasteTextureRenderer(m_renderer,thisWall.texture, thisWall.x, thisWall.y,thisWall.width,thisWall.height);
    }

}

void pasteAdvertisement(SDL_Renderer *m_renderer,Advertisement &thisAdvertisement)
{
    if(thisAdvertisement.isVisible)
    {
        pasteTextureRenderer(m_renderer, thisAdvertisement.texture, thisAdvertisement.x, thisAdvertisement.y, thisAdvertisement.width, thisAdvertisement.height);
    }
}

void pasteFans(SDL_Renderer *m_renderer,Fans thisFans[6],double &fansStatus)
{
    if(fansStatus>0)
    {
        for(int i=5; i>-1; i--)
        {
            if(i%2==int(fansStatus)%2)
            {
                if(thisFans[i].isVisible)
                {
                    pasteTextureRenderer(m_renderer, thisFans[i].texture, thisFans[i].x, thisFans[i].y, thisFans[i].width, thisFans[i].height);
                }
            }
            else
            {
                if(thisFans[i].isVisible)
                {
                    pasteTextureRenderer(m_renderer, thisFans[i].texture, thisFans[i].x, thisFans[i].y-thisFans[i].dy, thisFans[i].width, thisFans[i].height);
                }
            }
        }
        fansStatus-=0.05;
    }
    else
        for(int i=5; i>-1; i--)
            if(thisFans[i].isVisible)
            {
                pasteTextureRenderer(m_renderer, thisFans[i].texture, thisFans[i].x, thisFans[i].y, thisFans[i].width, thisFans[i].height);
            }
}

void pasteStadium(SDL_Renderer *m_renderer, Stadium &thisStadium)
{
    if(thisStadium.isVisible)
    {
        pasteTextureRenderer(m_renderer, thisStadium.texture, thisStadium.x, thisStadium.y, thisStadium.width, thisStadium.height);
    }
}

void pasteScoreboard(SDL_Renderer *m_renderer, Scoreboard &thisScoreboard)
{
    if(thisScoreboard.isVisible)
    {
        pasteTextureRenderer(m_renderer, thisScoreboard.bodyTexture, thisScoreboard.x, thisScoreboard.y, thisScoreboard.width, thisScoreboard.height);
        if(thisScoreboard.isTextVisble)
        {
            switch(thisScoreboard.leftScoreText)
            {
            case 0:
                pasteTextureRenderer(m_renderer, thisScoreboard.texture0, thisScoreboard.x + thisScoreboard.leftScoreX, thisScoreboard.y + thisScoreboard.leftScoreY, thisScoreboard.scoreWidth, thisScoreboard.scoreHeight);

                break;
            case 1:
                pasteTextureRenderer(m_renderer, thisScoreboard.texture1, thisScoreboard.x + thisScoreboard.leftScoreX, thisScoreboard.y + thisScoreboard.leftScoreY, thisScoreboard.scoreWidth, thisScoreboard.scoreHeight);

                break;
            case 2:
                pasteTextureRenderer(m_renderer, thisScoreboard.texture2, thisScoreboard.x + thisScoreboard.leftScoreX, thisScoreboard.y + thisScoreboard.leftScoreY, thisScoreboard.scoreWidth, thisScoreboard.scoreHeight);

                break;
            case 3:
                pasteTextureRenderer(m_renderer, thisScoreboard.texture3, thisScoreboard.x + thisScoreboard.leftScoreX, thisScoreboard.y + thisScoreboard.leftScoreY, thisScoreboard.scoreWidth, thisScoreboard.scoreHeight);

                break;
            case 4:
                pasteTextureRenderer(m_renderer, thisScoreboard.texture4, thisScoreboard.x + thisScoreboard.leftScoreX, thisScoreboard.y + thisScoreboard.leftScoreY, thisScoreboard.scoreWidth, thisScoreboard.scoreHeight);

                break;
            case 5:
                pasteTextureRenderer(m_renderer, thisScoreboard.texture5, thisScoreboard.x + thisScoreboard.leftScoreX, thisScoreboard.y + thisScoreboard.leftScoreY, thisScoreboard.scoreWidth, thisScoreboard.scoreHeight);

                break;
            }
            switch(thisScoreboard.rightScoreText)
            {
            case 0:
                pasteTextureRenderer(m_renderer, thisScoreboard.texture0, thisScoreboard.x + thisScoreboard.rightScoreX, thisScoreboard.y + thisScoreboard.rightScoreY, thisScoreboard.scoreWidth, thisScoreboard.scoreHeight);
                break;
            case 1:
                pasteTextureRenderer(m_renderer, thisScoreboard.texture1, thisScoreboard.x + thisScoreboard.rightScoreX, thisScoreboard.y + thisScoreboard.rightScoreY, thisScoreboard.scoreWidth, thisScoreboard.scoreHeight);

                break;
            case 2:
                pasteTextureRenderer(m_renderer, thisScoreboard.texture2, thisScoreboard.x + thisScoreboard.rightScoreX, thisScoreboard.y + thisScoreboard.rightScoreY, thisScoreboard.scoreWidth, thisScoreboard.scoreHeight);

                break;
            case 3:
                pasteTextureRenderer(m_renderer, thisScoreboard.texture3, thisScoreboard.x + thisScoreboard.rightScoreX, thisScoreboard.y + thisScoreboard.rightScoreY, thisScoreboard.scoreWidth, thisScoreboard.scoreHeight);

                break;
            case 4:
                pasteTextureRenderer(m_renderer, thisScoreboard.texture4, thisScoreboard.x + thisScoreboard.rightScoreX, thisScoreboard.y + thisScoreboard.rightScoreY, thisScoreboard.scoreWidth, thisScoreboard.scoreHeight);

                break;
            case 5:
                pasteTextureRenderer(m_renderer, thisScoreboard.texture5, thisScoreboard.x + thisScoreboard.rightScoreX, thisScoreboard.y + thisScoreboard.rightScoreY, thisScoreboard.scoreWidth, thisScoreboard.scoreHeight);
                break;


            }

        }
    }
}

void pastePowers(SDL_Renderer *m_renderer, Power &thisPower)
{
    if(thisPower.isVisible)
    {

        if(thisPower.powerType == PUNCH)
        {
            pasteTextureRenderer(m_renderer, thisPower.punchTexture, thisPower.x, thisPower.y, thisPower.width, thisPower.height);
        }

        if(thisPower.powerType == FIREBALL)
        {
            pasteTextureRenderer(m_renderer, thisPower.fireBallTexture, thisPower.x, thisPower.y, thisPower.width, thisPower.height);
        }

        if(thisPower.powerType == INVISIBLE)
        {
            pasteTextureRenderer(m_renderer, thisPower.invisibleBallTexture, thisPower.x, thisPower.y, thisPower.width, thisPower.height);
        }

        if(thisPower.powerType == THIEF)
        {
            pasteTextureRenderer(m_renderer, thisPower.thiefTexture, thisPower.x, thisPower.y, thisPower.width, thisPower.height);
        }
    }
    sideRectangleRGB(m_renderer,thisPower.x,thisPower.y+thisPower.height,thisPower.width*thisPower.percentage/100.0,thisPower.height/3,255*(1-double(thisPower.percentage)/100.0),255,255*(1-double(thisPower.percentage)/100.0),1);
}

void pasteButton(SDL_Renderer *m_renderer, Button buttons[], int num)
{
    for(int i=0; i<num; i++)
    {
        if(buttons[i].isVisible)
            pasteTextureRenderer(m_renderer,buttons[i].texture,buttons[i].x,buttons[i].y,buttons[i].width,buttons[i].height);
    }
}

void pasteButton(SDL_Renderer *m_renderer, Button &thisButton)
{
    if(thisButton.isVisible)
        pasteTextureRenderer(m_renderer,thisButton.texture,thisButton.x,thisButton.y,thisButton.width,thisButton.height);
}

void playerMovementRules(Player &thisPlayer,BackGround &thisBack)
{
    thisPlayer.y+=thisPlayer.dy;
    if (thisPlayer.y+thisPlayer.height<thisBack.maxYBall)
    {
        thisPlayer.dy+=thisPlayer.g;
    }
    else
    {
        thisPlayer.y=thisBack.maxYBall-thisPlayer.height;
        thisPlayer.dy=0;
    }
}

int playerBallChecker(Ball &thisBall, Player &thisPlayer)
{
    int result=0;
    if(thisBall.x+thisBall.rad>=thisPlayer.x &&
            thisBall.x+thisBall.rad<=thisPlayer.x+thisPlayer.width &&
            thisBall.y>=thisPlayer.y && thisBall.y<=thisPlayer.y+thisPlayer.height)
    {
        result=RIGHT;
    }
    else if(thisBall.x-thisBall.rad>=thisPlayer.x &&
            thisBall.x-thisBall.rad<=thisPlayer.x+thisPlayer.width &&
            thisBall.y>=thisPlayer.y && thisBall.y<=thisPlayer.y+thisPlayer.height)
    {
        result=LEFT;
    }
    else if(thisBall.y-thisBall.rad>=thisPlayer.y &&
            thisBall.y-thisBall.rad<=thisPlayer.y+thisPlayer.height &&
            thisBall.x>=thisPlayer.x && thisBall.x<=thisPlayer.x+thisPlayer.width)
    {
        result=UP;
    }
    else if(thisBall.y+thisBall.rad>=thisPlayer.y &&
            thisBall.y+thisBall.rad<=thisPlayer.y+thisPlayer.height &&
            thisBall.x>=thisPlayer.x && thisBall.x<=thisPlayer.x+thisPlayer.width)
    {
        result=DOWN;
    }
    return result;
}


int maxMinRand(int closedMin, int closedMax)
{
    return (rand()%(closedMax-closedMin+1))+closedMin;
}

void shootBall(Ball &thisBall,BackGround &thisBack,Player &thisPlayer,int direction)
{

    if(thisPlayer.shoeStatus==0 )
    {
        thisPlayer.shoeStatus=thisPlayer.shoeStatus1;
        if(canPlayerShoot(thisPlayer,thisBall))
        {
            if(thisPlayer.sideOfPlay==LEFT_PLAYER)
            {
                if(direction==DOWN)
                {
                    if(thisBall.dy==0)
                        thisBall.dx+=thisBall.shootDdx2;
                    else
                        thisBall.dx+=thisBall.shootDdx2;
                }
                else
                {
                    thisBall.dx+= thisBall.shootUdx;
                    thisBall.dy-=thisBall.shootUdy;
                }
            }
            else
            {
                if(direction==DOWN)
                {
                    if(thisBall.dy==0)
                        thisBall.dx-=thisBall.shootDdx2;
                    else
                        thisBall.dx-=thisBall.shootDdx1;
                }
                else
                {
                    thisBall.dx-= thisBall.shootUdx;
                    thisBall.dy-=thisBall.shootUdy;
                }
            }
        }
    }
}
bool canPlayerShoot(Player &thisPlayer,Ball &mainBall)
{
    bool result=false;
    if(thisPlayer.sideOfPlay==RIGHT_PLAYER)
    {
        result=(thisPlayer.x+(thisPlayer.width/2)>=mainBall.x+mainBall.rad &&
                thisPlayer.x-(mainBall.rad/2) <=mainBall.x+mainBall.rad &&
                thisPlayer.y+thisPlayer.headHeight<=mainBall.y+mainBall.rad &&
                thisPlayer.y+thisPlayer.height>=mainBall.y+mainBall.rad);
    }
    else
    {
        result=(thisPlayer.x+(thisPlayer.width/2)<=mainBall.x+mainBall.rad &&
                thisPlayer.x+thisPlayer.width+(mainBall.rad/2) >=mainBall.x-mainBall.rad &&
                thisPlayer.y+thisPlayer.headHeight<= mainBall.y+mainBall.rad &&
                thisPlayer.y+thisPlayer.height>=mainBall.y+mainBall.rad);
    }
    return result;
}


void buttonLRInit(Button buttons[],const int buttonNum,SDL_Renderer *m_renderer,Ball &mainBall,Player &playerLeft,Player &playerRight,Court &thisCourt,Power &leftPower,Power &rightPower, Advertisement &thisAdvertisement)
{
    for(int i=0; i+1<buttonNum; i+=2)
    {
        buttons[i+1].texture=IMG_LoadTexture(m_renderer,"images/leftButton.png");
        buttons[i].texture=IMG_LoadTexture(m_renderer,"images/rightButton.png");
    }
    /// Ball:
    // LEFT
    buttons[BUTTON_BALL].x=mainBall.x+mainBall.rad*3.0/2.0;
    buttons[BUTTON_BALL].y=mainBall.y-buttons[BUTTON_BALL].height/2;
    // RIGHT
    buttons[BUTTON_BALL+1].x=mainBall.x-(mainBall.rad*3.0/2.0)-buttons[BUTTON_BALL+1].width;
    buttons[BUTTON_BALL+1].y=mainBall.y-buttons[BUTTON_BALL].height/2;

    buttons[BUTTON_PLAYERLEFT].x=playerLeft.x+(playerLeft.headWidth*6.0/5.0);
    buttons[BUTTON_PLAYERLEFT].y=playerLeft.y+(playerLeft.headHeight/2)-buttons[BUTTON_PLAYERLEFT].height/2;
    buttons[BUTTON_PLAYERLEFT+1].x=playerLeft.x-(playerLeft.headWidth*1/5.0)-buttons[BUTTON_PLAYERLEFT+1].width;
    buttons[BUTTON_PLAYERLEFT+1].y=playerLeft.y+(playerLeft.headHeight/2)-buttons[BUTTON_PLAYERLEFT+1].height/2;

    buttons[BUTTON_PLAYERRIGHT].x=playerRight.x+(playerRight.headWidth*6.0/5.0);
    buttons[BUTTON_PLAYERRIGHT].y=playerRight.y+(playerRight.headHeight/2)-buttons[BUTTON_PLAYERRIGHT].height/2;
    buttons[BUTTON_PLAYERRIGHT+1].x=playerRight.x-(playerRight.headWidth*1/5.0)-buttons[BUTTON_PLAYERRIGHT+1].width;
    buttons[BUTTON_PLAYERRIGHT+1].y=playerRight.y+(playerRight.headHeight/2)-buttons[BUTTON_PLAYERRIGHT+1].height/2;

    buttons[BUTTON_SHOELEFT].x=playerLeft.x+(playerLeft.width*6.0/5.0);
    buttons[BUTTON_SHOELEFT].y=playerLeft.y+(playerLeft.height)-playerLeft.shoeHeight/2 -buttons[BUTTON_PLAYERLEFT].height/2;
    buttons[BUTTON_SHOELEFT+1].x=playerLeft.x-(playerLeft.width*1/5.0)-buttons[BUTTON_PLAYERLEFT+1].width;
    buttons[BUTTON_SHOELEFT+1].y=playerLeft.y+(playerLeft.height)-playerLeft.shoeHeight/2 -buttons[BUTTON_PLAYERLEFT+1].height/2;

    buttons[BUTTON_SHOERIGHT].x=playerRight.x+(playerRight.width*6.0/5.0);
    buttons[BUTTON_SHOERIGHT].y=playerRight.y+(playerRight.height)-playerRight.shoeHeight/2 -buttons[BUTTON_PLAYERLEFT].height/2;
    buttons[BUTTON_SHOERIGHT+1].x=playerRight.x-(playerRight.width*1/5.0)-buttons[BUTTON_PLAYERLEFT+1].width;
    buttons[BUTTON_SHOERIGHT+1].y=playerRight.y+(playerRight.height)-playerRight.shoeHeight/2 -buttons[BUTTON_PLAYERLEFT+1].height/2;

    buttons[BUTTON_LEFTPOWER].x=leftPower.x+(leftPower.width*0.75);
    buttons[BUTTON_LEFTPOWER].y=leftPower.y+(leftPower.height/2) -buttons[BUTTON_LEFTPOWER].height/2;
    buttons[BUTTON_LEFTPOWER+1].x=leftPower.x+(leftPower.width*1/5.0)-buttons[BUTTON_LEFTPOWER+1].width;
    buttons[BUTTON_LEFTPOWER+1].y=leftPower.y+(leftPower.height/2)-buttons[BUTTON_LEFTPOWER+1].height/2;

    buttons[BUTTON_RIGHTPOWER].x=rightPower.x+(rightPower.width*0.75);
    buttons[BUTTON_RIGHTPOWER].y=rightPower.y+(rightPower.height/2) -buttons[BUTTON_RIGHTPOWER].height/2;
    buttons[BUTTON_RIGHTPOWER+1].x=rightPower.x+(rightPower.width*1/5.0)-buttons[BUTTON_RIGHTPOWER+1].width;
    buttons[BUTTON_RIGHTPOWER+1].y=rightPower.y+(rightPower.height/2)-buttons[BUTTON_RIGHTPOWER+1].height/2;

    buttons[BUTTON_COURT].width=buttons[BUTTON_COURT].height=buttons[BUTTON_BALL].width*2;
    buttons[BUTTON_COURT+1].width=buttons[BUTTON_COURT+1].height=buttons[BUTTON_BALL].width*2;
    buttons[BUTTON_COURT].x=thisCourt.x+(thisCourt.width*0.6);
    buttons[BUTTON_COURT].y=thisCourt.y+(thisCourt.height/2) -buttons[BUTTON_COURT].height/2;
    buttons[BUTTON_COURT+1].x=thisCourt.x+(thisCourt.width*0.4)-buttons[BUTTON_COURT+1].width;
    buttons[BUTTON_COURT+1].y=thisCourt.y+(thisCourt.height/2)-buttons[BUTTON_COURT+1].height/2;

    buttons[BUTTON_NAME].width=screenWidth/6;
    buttons[BUTTON_NAME].height=screenHeight/13;
    buttons[BUTTON_NAME].x=(screenWidth*0.8)-(buttons[BUTTON_NAME].width/2);
    buttons[BUTTON_NAME].y=370;
    buttons[BUTTON_NAME].texture=IMG_LoadTexture(m_renderer,"images/textBoxOff.png");

    buttons[BUTTON_NAME+1].width=screenWidth/6;
    buttons[BUTTON_NAME+1].height=screenHeight/13;
    buttons[BUTTON_NAME+1].x=(screenWidth*0.2)-(buttons[BUTTON_NAME+1].width/2);
    buttons[BUTTON_NAME+1].y=370;
    buttons[BUTTON_NAME+1].texture=IMG_LoadTexture(m_renderer,"images/textBoxOff.png");
}

void buttonLRFunction(SDL_Renderer * m_renderer,Button buttons[], int whichButton,Ball &mainBall,Player &playerLeft,Player &playerRight,Court &thisCourt,Power &leftPower,Power &rightPower, Advertisement &thisAdvertisement)
{
    string address;
    int leftOrRight=(-2*(whichButton%2))+1;//age whicButton zaoj bood mishe1 age fard bood =-1
    switch(whichButton-(whichButton%2))
    {
    case BUTTON_BALL:
    {
        mainBall.textureNum+=leftOrRight;
        mainBall.textureNum=(mainBall.textureNum+mainBall.imagesNum)%mainBall.imagesNum;
        address="images//mainBall"+to_string(mainBall.textureNum)+".png";
        mainBall.texture=IMG_LoadTexture( m_renderer,address.c_str());
        break;
    }
    case BUTTON_PLAYERLEFT:
    {
        playerLeft.headTextureNum+=leftOrRight;
        playerLeft.headTextureNum=(playerLeft.headTextureNum+playerLeft.headImagesNum)%playerLeft.headImagesNum;
        address="images//playerLeftHead"+to_string(playerLeft.headTextureNum)+".png";
        playerLeft.headTexture=IMG_LoadTexture( m_renderer,address.c_str());
        break;
    }
    case BUTTON_PLAYERRIGHT:
    {
        playerRight.headTextureNum+=leftOrRight;
        playerRight.headTextureNum=(playerRight.headTextureNum+playerRight.headImagesNum)%playerRight.headImagesNum;
        address="images//playerRightHead"+to_string(playerRight.headTextureNum)+".png";
        playerRight.headTexture=IMG_LoadTexture( m_renderer,address.c_str());
        break;
    }
    case BUTTON_SHOERIGHT:
    {
        playerRight.shoeTextureNum+=leftOrRight;
        playerRight.shoeTextureNum=(playerRight.shoeTextureNum+playerRight.shoeImagesNum)%playerRight.shoeImagesNum;
        address="images//shoeLeft"+to_string(playerRight.shoeTextureNum)+".png";
        playerRight.leftShoeTexture=IMG_LoadTexture( m_renderer,address.c_str());
        address="images//shoeRight"+to_string(playerRight.shoeTextureNum)+".png";
        playerRight.rightShoeTexture=IMG_LoadTexture( m_renderer,address.c_str());
        break;
    }
    case BUTTON_SHOELEFT:
    {
        playerLeft.shoeTextureNum+=leftOrRight;
        playerLeft.shoeTextureNum=(playerLeft.shoeTextureNum+playerLeft.shoeImagesNum)%playerLeft.shoeImagesNum;
        address="images//shoeLeft"+to_string(playerLeft.shoeTextureNum)+".png";
        playerLeft.leftShoeTexture=IMG_LoadTexture( m_renderer,address.c_str());
        address="images//shoeRight"+to_string(playerLeft.shoeTextureNum)+".png";
        playerLeft.rightShoeTexture=IMG_LoadTexture( m_renderer,address.c_str());
        break;
    }
    case BUTTON_COURT:
    {
        thisCourt.textureNum+=leftOrRight;
        thisCourt.textureNum=(thisCourt.textureNum+thisCourt.imagesNum)%thisCourt.imagesNum;
        address="images//court"+to_string(thisCourt.textureNum)+".png";
        thisCourt.texture=IMG_LoadTexture( m_renderer,address.c_str());
        break;
    }
    case BUTTON_LEFTPOWER:
    {
        leftPower.powerType+=leftOrRight;
        leftPower.powerType=(leftPower.powerType+4)%4;
        break;
    }
    case BUTTON_RIGHTPOWER:
    {
        rightPower.powerType+=leftOrRight;
        rightPower.powerType=(rightPower.powerType+4)%4;
        break;
    }
    case BUTTON_NAME:
    {
        string &name=persons[whichButton%2].name;
        SDL_Event *event=new SDL_Event;
        int font =1;
        bool caps_lock = false;
        int x_position=buttons[BUTTON_NAME+(whichButton%2)].x+5;
        int y_position=buttons[BUTTON_NAME+(whichButton%2)].y+10;
        int R=100;
        int G =100;
        int B=100;
        int A=0.5;
        bool quit = false ;
        char ch=0;
        while (!quit)
        {
            SDL_Delay(20);
            if(SDL_PollEvent(event))
            {
                if(event -> type == SDL_KEYUP)
                {
                    switch(event->key.keysym.sym)
                    {
                    case SDLK_CAPSLOCK:
                    {
                        ch=0;
                        caps_lock =(!caps_lock);
                        break;
                    }
                    case SDLK_SPACE:
                    {
                        ch=' ';
                        break;
                    }
                    case SDLK_BACKSPACE:
                    {
                        ch = 0;
                        if(name.length()!=0)
                        {
                            textRGBA(m_renderer,x_position, y_position, name.c_str(), font+1, 20, 255,255,255, A);
                            name = name.substr(0,int(name.length())-1);
                            SDL_RenderPresent(m_renderer);
                        }
                        break;
                    }
                    default :
                        if(event->key.keysym.sym != SDLK_UP && event->key.keysym.sym != SDLK_DOWN && event->key.keysym.sym != SDLK_LEFT && event->key.keysym.sym != SDLK_RIGHT)
                            ch = event->key.keysym.sym;
                        break;
                    }

                    if(((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch == ' '))&& name.length()<15 && !quit)
                    {
                        if(caps_lock )
                            name+=ch + 'A' - 'a';
                        else
                            name+=ch ;
                    }
                    if(name != "" && !quit)
                    {
                        textRGBA(m_renderer,x_position, y_position, name.c_str(), font+1, 20, 0,0, 0, A);
                        SDL_RenderPresent(m_renderer);
                    }
                }

                else if(event -> type == SDL_MOUSEBUTTONDOWN)
                {
                    quit=true;
                }
            }
        }

    }
    }
}


bool mouseButtonCheck(int mousex,int mousey, Button &thisButton)
{
    return (mousex>=thisButton.x && mousex<=thisButton.x+thisButton.width &&mousey>=thisButton.y && mousey<=thisButton.y+thisButton.height);
}

void  invisibleBall(Ball &mainBall,Player &thisPlayer,BackGround &thisBack,Power &thisPower)
{
    if(canPlayerShoot(thisPlayer,mainBall))
    {
        thisPower.time=clock();
        mainBall.isVisible=false;
        thisPower.dp=thisPower.negetive;
        if(maxMinRand(0,1))
        {
            shootBall(mainBall,thisBack,thisPlayer,UP);
        }
        else
        {
            shootBall(mainBall,thisBack,thisPlayer,DOWN);
        }
    }

}

void powerRules(Power &thisPower,Ball &mainBall,Player&thisPlayer)
{
    double dt=double(clock()-thisPower.time)/1000;
    if(thisPower.dp>0)
    {
        thisPower.percentage=dt*thisPower.dp;
    }
    else
    {
        thisPower.percentage=100+(dt*thisPower.dp);
    }
    if(thisPower.percentage>=100)
    {
        thisPower.percentage=100;
    }
    if(thisPower.percentage<=0)
    {
        thisPower.percentage=0;
        mainBall.isVisible=true;
        thisPlayer.isWorking=true;
        if(thisPower.dp>0)
        {
            thisPower.dp=thisPower.negetive;
        }
        else
        {
            thisPower.dp=thisPower.positive;
        }
    }
}

void punch(Ball &punchBall,Power &thisPower,Player &thisPlayer,Player &otherPlayer)
{
    if(thisPower.percentage>=100)
    {
        punchBall.x=thisPlayer.x+thisPlayer.width+punchBall.rad;
        punchBall.y=thisPlayer.y+thisPlayer.height/2;
        punchBall.dx=20;
        if(thisPlayer.sideOfPlay!=LEFT_PLAYER)
        {
            punchBall.dx*=-1;
        }
        punchBall.isVisible=true;
    }
}

void punchBallMover(Ball &punch,Player &playerLeft,Player &playerRight,Power &powerLeft, Power &powerRight)
{
    if(punch.isVisible)
    {
        punch.x+=punch.dx;
        if(punch.dx>0)
        {
            if(punch.x+punch.rad>=playerRight.x)
            {
                punch.isVisible=false;
                powerLeft.dp=powerLeft.negetive;
                powerLeft.time=clock();
                playerRight.isWorking=false;
            }
        }
        else
        {
            if(punch.x-punch.rad<=playerLeft.x+playerLeft.width)
            {
                punch.isVisible=false;
                powerRight.dp=powerRight.negetive;
                powerRight.time=clock();
                playerLeft.isWorking=false;
            }
        }
    }
}


int goalBall(Ball &mainBall, Goal &gr,Goal &gl,Scoreboard &s,int &goalTime,Player &pl,Player &pr,double &fans,int &side,Power &powerLeft,Power &powerRight)
{
    int result=0;
    if(goalTime>0)
    {
        goalTime--;
    }
    if(goalTime ==0)
    {
        goalTime--;
        if(s.leftScoreText ==5)
        {
            result=LEFT;
        }
        else if(s.leftScoreText==4 && s.rightScoreText==4)
        {
            result=CENTRE;
        }
        else if(s.rightScoreText ==5)
        {
            result=RIGHT;
        }
        else
        {
            ballDroper(side,mainBall);
            pl.x=mainBall.rad*2;
            pr.x=screenWidth-mainBall.rad*2-pr.width;
        }
    }

    if(mainBall.x+mainBall.rad<gl.x+gl.width && mainBall.y>gl.y)
    {
        if(goalTime<0)
        {
            goalTime=70;
            s.rightScoreText++;
            side=LEFT;
            fans=20;
            if(powerLeft.dp<0)
            {
                powerLeft.dp=powerLeft.positive;
                powerLeft.time=clock();
            }
            powerLeft.time-=8000;
        }
    }
    else  if(mainBall.x-mainBall.rad>gr.x && mainBall.y>gl.y)
    {
        if(goalTime<0)
        {
            goalTime=70;
            s.leftScoreText++;
            side=RIGHT;
            fans=20;
            if(powerRight.dp<0)
            {
                powerRight.dp=powerRight.positive;
                powerRight.time=clock();
                powerRight.percentage=0;
            }
            powerRight.time-=8000;
        }
    }
    return result;
}

void readDataBase(string names[10],int scores[10])
{
    ifstream a;
    string text;
    a.open("dataBase.txt");
    for(int ii=0; ii<10; ii++)
    {
        names[ii]="null";
        scores[ii]=0;
    }
    int i=0;
    int j=0;
    if(a.good())
    {
        while (getline (a, text)|| i<10)
        {
            for( j=0; j<text.length() ; j++)
            {
                if(text[j]>='0' && text[j]<='9')
                {
                    scores[i]=scores[i]*10+int(text[j]-'0');
                }
                else
                {
                    break;
                }
            }
            if(j+1<text.length())
            {
                names[i]=text.substr(j+1,text.length()-j-1);
            }
            i++;
        }
    }
    a.close();
}

void newWindow(int type, SDL_Renderer *m_renderer)
{
    int w=screenWidth*0.5;
    int h=realScreenHeight*0.5;
    int x=screenWidth/2-w/2;
    int y=realScreenHeight/2-h/2;
    // pasteImageRenderer(m_renderer,x,y,"images/cadr.png",w,h);
    string text;
    switch(type)
    {
    case RIGHT:
    {
        if(persons[0].name!="")
        {
            text=persons[0].name;
        }
        else
        {
            text="Right Player";
        }
        text=text+" Wins";
        break;
    }
    case LEFT:
        if(persons[1].name!="")
        {
            text=persons[1].name;
        }
        else
        {
            text="Left Player";
        }
        text=text+" Wins";
        break;
    case CENTRE:
        text="Game Ends With a Draw";
        break;
    }
    sideRectangleRGB(m_renderer,x,y,w,h,100,100,-1,1);
    textRGBA(m_renderer,x+w/8,y+h/2,text.c_str(),2,30,-1,-1,-1,255);
    SDL_RenderPresent(m_renderer);
    SDL_Delay(7000);
}

void updateDataBase(string winnerName,int scores[10],string names[10])
{
    if(winnerName.length()>0)
    {
        bool flag=false;
        int scores2[10];
        string names2[10];
        for(int i=0; i<10; i++)
        {
            scores2[i]=scores[i];
            names2[i]=names[i];
        }

        int i=0;
        for(i=0; i<10 && !flag ; i++)
        {
            if(names[i]==winnerName)
            {
                scores[i]++;
                flag=true;
                break;
            }
        }
        for(i=0; i<10 && !flag ; i++)
        {
            if(names[i]=="null")
            {
                scores[i]=1;
                flag=true;
                break;
            }
        }
        if(!flag)
        {
         names[0]=winnerName;
         scores[0]=1;
         for(i=0; i<9; i++)
        {
            names[i+1]=names2[i];
            scores[i+1]=scores2[i];
        }}
    }
}


void writeDataBase(string names[],int scores[])
{
    ofstream a;
    string text="";
    for(int i=0;i<9;i++)
    {
        text=text+to_string(scores[i])+" "+names[i]+"\n";
    }
        text=text+to_string(scores[9])+" "+names[9];
    a.open("dataBase.txt");
    if(a.good())
    {
        a<<text;
    }
    a.close();

}
