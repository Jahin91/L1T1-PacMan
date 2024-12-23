#include "iGraphics.h"
#include <windows.h>
#include <mmsystem.h>
#include <bits/stdc++.h>
using namespace std;

#define mazeStartX  100
#define mazeStartY 660
#define screenWidth 970
#define screenHeight 720
#define ghostX 120
#define ghostY 120

void pacmanMovement();
void changePacCordinate();
void changeImageIndx();
void drawMaze();
void trackPackPosition(int startX, int startY, int indx);
int dfs(int startI, int startJ, int endI, int endJ, int check[29][30], int path_found, int i);
void generateRandomIndx(int ara[]);
void findPath(int i);
void defineGhost();
void showGhost();
void showIntro();
void changeIntroIndx();
void showMenu();
void setDots();
void saveDots();
void dotCollusionCheck();
void bfsMovement();
void showScore();
void difficultyPage();
void releaseGhost();
void initializeGame();
void ghostCollusion();
void dieAnimation();
void playDieAnimation();
void namePage();
void updateScore();
void gameOverPage();
void manageScore();
void showInstruction();
void soundPage();

bool pacMoveRight = false;
bool pacMoveLeft = false;
bool pacMoveUp = false;
bool pacMoveDown = false;
bool pacBase = true;
bool introSound = true;
bool bfsMove = false;
bool movingSound = false;
bool fGhostSound = false;
bool fGhost = false;
bool dying = false;
bool fGhostB = false;
bool eatGhost = false;
bool gamePlayed = false;
bool gameSound = true;

int pacX = 500+21;
int pacY = 500+21;
int pacMazeX = 27;
int pacMazeY = 1;
int rightMovementIndx = 0;
int leftMovementIndx = 0;
int downMovementIndx = 0;
int upMovementIndx = 0;
int gameState = 0;
int introIndx = 0;
int timerId1;
int timerId2;
int timerId3;
int timerId4;
int timerId5;
int timerId6;
int timerId7;
int gameDifficulty = 1;
int movingGhost = 1;
int ghostRealseInterval = 20000;
int ghostMovementCall = 5;
int dieAnimationIndx = 1;
int scoreLvl = 1;
int nameIndx = 0;
int life = 3;
int liveScore = 0;
double elapsed;
clock_t start;
clock_t finish;
clock_t eatGhostTimerStart, eatGhostTimerEnd;

typedef struct {
    int x1, x2, y1, y2;
} wallPosition;

typedef struct{
    int i, j, indx, ct, x, y;
    int pathX[1000];
    int pathY[1000];
    bool mxn;
    bool mxp;
    bool myp;
    bool myn;
} ghosts;
ghosts ghost[4];

wallPosition wall[320];

char rightMovementImage[3][20]={
    "pacman/base.bmp",
    "pacman/right1.bmp",
    "pacman/right2.bmp"
};
char leftMovementImage[3][20]={
    "pacman/base.bmp",
    "pacman/left1.bmp",
    "pacman/left2.bmp"
};
char upMovementImage[3][20]={
    "pacman/base.bmp",
    "pacman/up1.bmp",
    "pacman/up2.bmp"
};
char downMovementImage[3][25]={
    "pacman/base.bmp",
    "pacman/down1.bmp",
    "pacman/down2.bmp"
};
char ghostRightImage[4][25] = {
    "pacman/blueRight.bmp",
    "pacman/pinkRight.bmp",
    "pacman/yellowRight.bmp",
    "pacman/redRight.bmp"
};
char ghostLeftImage[4][25] = {
    "pacman/blueLeft.bmp",
    "pacman/pinkLeft.bmp",
    "pacman/yellowLeft.bmp",
    "pacman/redLeft.bmp"
};
char ghostUpImage[4][25] = {
    "pacman/blueUp.bmp",
    "pacman/pinkUp.bmp",
    "pacman/yellowUp.bmp",
    "pacman/redUp.bmp"
};
char ghostDownImage[4][25] = {
    "pacman/blueDown.bmp",
    "pacman/pinkDown.bmp",
    "pacman/yellowDown.bmp",
    "pacman/redDown.bmp"
};
char name[50];
int maze[29][30]=
{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,
    1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,
    1,0,1,0,0,1,1,1,0,0,1,0,0,0,1,1,0,0,0,1,0,0,1,1,1,0,0,1,0,1,
    1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
    1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
    1,0,1,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,1,0,1,
    1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,
    1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,
    1,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,1,
    1,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,
    1,0,1,2,1,0,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,1,2,1,0,1,
    1,0,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,0,1,
    1,0,1,2,1,0,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,1,2,1,0,1,
    1,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,
    1,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,1,
    1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,
    1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,
    1,0,1,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,1,0,1,
    1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
    1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
    1,0,1,0,0,1,1,1,0,0,1,0,0,0,1,1,0,0,0,1,0,0,1,1,1,0,0,1,0,1,
    1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,
    1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

void iDraw(){
    iClear();
    if(gameState == 0){
        showIntro();
    }
    if(gameState == 1){
        showMenu();
    }
	if(gameState == 69){
        drawMaze();
        if(dying) dieAnimation();
        else  pacmanMovement();
        showGhost();
        updateScore();
	}
	if(gameState == 4){
        showScore();
	}
	if(gameState == 3) showInstruction();
	if(gameState == 2) difficultyPage();
	if(gameState == -1) namePage();
	if(gameState == 5) gameOverPage();
	if(gameState == 6) soundPage();
    finish = clock();
}
void pacmanMovement(){
    if(pacBase){
        iShowBMP2(pacX, pacY, "pacman/base.bmp", 0);
    }
    else if(pacMoveRight){
        iShowBMP2(pacX, pacY, rightMovementImage[rightMovementIndx], 0);
    }
    else if(pacMoveLeft){
        iShowBMP2(pacX, pacY, leftMovementImage[leftMovementIndx], 0);
    }
    else if(pacMoveUp){
        iShowBMP2(pacX, pacY, upMovementImage[upMovementIndx], 0);
    }
    else if(pacMoveDown){
        iShowBMP2(pacX, pacY, downMovementImage[downMovementIndx], 0);
    }
}
void drawMaze(){
    int mazeY = mazeStartY;
	for(int i = 0; i < 29; i++){
        int mazeX= mazeStartX;

        for(int j = 0; j < 30; j++){
            if(maze[i][j] == 1){
                iSetColor(0, 0, 255);
                iShowBMP2(mazeX, mazeY, "pacman/mazeBrick.bmp", 0);
            }
            else if(maze[i][j] == 0){
                iSetColor(255, 255, 255);

            }
            mazeX = mazeX + 20;
        }
        mazeY = mazeY - 20;
	}
	 setDots();
}
void saveWallCordinate()
{
    int mazeY = mazeStartY;
    int r = 0;
	for(int i = 0; i < 29; i++){
        int mazeX= mazeStartX;

        for(int j = 0; j < 30; j++){
            if(maze[i][j] == 1){
                iSetColor(0, 0, 255);
                wall[r].x1 = mazeX;
                wall[r].x2 = mazeX+20;
                wall[r].y1 = mazeY;
                wall[r].y2 = mazeY+20;
                r++;
            }
            else if(maze[i][j] == 0){
                iSetColor(255, 255, 255);

            }
            mazeX = mazeX + 20;
        }
        mazeY = mazeY - 20;
	}


}
/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my) {
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if(gameState == 1 && mx >= 423 && mx <= 423+147 && my >= 522 && my <= (58+522)){
            gameState = -1;
		}
		if(gameState == 1 && mx >= 423 && mx <= 423+147 && my >= 522-65 && my <= 58+522-65){
            gameState = 2;
		}
		if(gameState == 1 && mx >= 423 && mx <= 423+147 && my >= (522-65*2) && my <= (522+68-65*2)){
            gameState = 3;
		}
		if(gameState == 1 && mx >= 423  && mx <= 423+147 && my >= (522-65*3) && my <= (522+68-65*3)){
            gameState = 4;
		}
		if(gameState == 1 && mx >= 423 && mx <= 423+147 && my >= (522-65*4) && my <= (522+68-65*4)){
            gameState = 6;
		}
		if(gameState == 4 && mx >= 5 && mx <= 5+160 && my >= 660 && my <= 660+50 && scoreLvl == 1 && !gamePlayed){
            gameState = 1;
		}
		if(gameState == 2 && mx >= 250+3 && mx <= 250+160-2 && my >= 250 && my <= 250+50){
            gameState = 1;
            gameDifficulty = 1;
            if(gameDifficulty == 1){
                movingGhost = 1;
                ghostRealseInterval = 200000;
            }
		}
		if(gameState == 2 && mx >= 250+170+3 && mx <= 250+170+160-2 && my >= 250 && my <= 250+50){
            gameState = 1;
            gameDifficulty = 2;
            if(gameDifficulty){
                ghostRealseInterval = 100000;
            }
		}
		if(gameState == 2 && mx >= 250+170*2+3 && mx <= 250+170*2+160-2 && my >= 250 && my <= 250+50){
            gameState = 1;
            gameDifficulty = 3;
            if(gameDifficulty == 3){
                ghostRealseInterval = 100;
            }
		}
		if(gameState == 4 && (scoreLvl == 1 || scoreLvl == 2) && mx >= 783 && mx <= 937 && my >= 60 && my <= 110){
            scoreLvl++;
		}
		if(gameState == 4 && (scoreLvl == 2 || scoreLvl == 3) && mx >= 5 && mx <= 5+160 && my >= 660 && my <= 660+50 ){
            scoreLvl--;
		}
        if(gameState == -1 && mx >= 370 && mx <= 625 && my >= 120 && my <= 180){
            gameState = 69;
            initializeGame();
            if(!movingSound){
                movingSound = true;
                if(gameSound) PlaySound("Sounds/pacman_chomp.wav", NULL, SND_LOOP | SND_ASYNC);
            }
        }
		 if(gameState == 5 && mx >= 783 && mx <= 937 && my >= 60 && my <= 110 && gamePlayed){
            gameState = 4;
		}

		/*iShowBMP(0, 0, "pacman/menubackgroundC.bmp");
        if(gameSound){
        iSetColor(255, 255, 204);
        iFilledCircle(345, 373, 7, 100);
        iCircle(545, 373, 7, 100);
        }
        else{
        iSetColor(255, 255, 204);
        iCircle(345, 373, 7, 100);
        iFilledCircle(545, 373, 7, 100);
        }
        iShowBMP2(350, 350, "Menu/on.bmp", 0);
        iShowBMP2(550, 350, "Menu/off.bmp", 0); */

		if(gameState == 6 && mx >= 353 && mx <= 507 && my >= 350 && my <= 400) gameSound = true;
		if(gameState == 6 && mx >= 553 && mx <= 707 && my >= 350 && my <= 400) gameSound = false;

	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
            if(gameState == 4 && scoreLvl == 3 && mx >= 783 && mx <= 937 && my >= 60 && my <= 110 && gamePlayed){
            exit(0);
		}
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key) {
	if (key == 'q') {

	}
	if(key != '\b' && gameState == -1){
        name[nameIndx] = key;
        nameIndx++;
        name[nameIndx] = '\0';
	}
	if(nameIndx > 0 && key == '\b' && gameState == -1){
        nameIndx--;
        name[nameIndx] = '\0';
	}
	if(gameState == 3 && key == 'b'){
        gameState = 1;
	}
	if(gameState == 6 && key == 'b') gameState = 1;
	//place your codes for other keys here
}
bool changeDirection(){
    for(int i = 0; i < 320; i++){
        if(pacMoveDown){
            if((pacY >= wall[i].y1 && pacY <= wall[i].y2) && ((pacX+15 >= wall[i].x1 && pacX+15 <= wall[i].x2) || (pacX >= wall[i].x1 && pacX <= wall[i].x2))){
               return false;
            }
        }
        if(pacMoveRight){
            if((pacX+15 >= wall[i].x1 && pacX+15 <= wall[i].x2) &&((pacY+15 >= wall[i].y1 && pacY+15 <= wall[i].y2) || (pacY >= wall[i].y1 && pacY <= wall[i].y2))){
                return false;
            }
        }
        if(pacMoveUp){
            if((pacY+15 >= wall[i].y1 && pacY+15 <= wall[i].y2) && ((pacX+15 >= wall[i].x1 && pacX+15 <= wall[i].x2) || (pacX >= wall[i].x1 && pacX <= wall[i].x2))){
                return false;
            }
        }
        if(pacMoveLeft){
            if((pacX >= wall[i].x1 && pacX <= wall[i].x2) && ((pacY+15 >= wall[i].y1 && pacY+15 <= wall[i].y2) ||(pacY >= wall[i].y1 && pacY <= wall[i].y2))){
                return false;
            }
        }
    }
    return true;

}
void checkCordinate(){
    for(int i = 0; i < 320; i++){
        if(pacMoveDown){
            if((pacY >= wall[i].y1 && pacY <= wall[i].y2) && ((pacX+15 >= wall[i].x1 && pacX+15 <= wall[i].x2) || (pacX >= wall[i].x1 && pacX <= wall[i].x2))){
                pacMoveDown = false;
                pacBase = true;
                pacY+=1;
            }
        }
        if(pacMoveRight){
            if((pacX+15 >= wall[i].x1 && pacX+15 <= wall[i].x2) &&((pacY+15 >= wall[i].y1 && pacY+15 <= wall[i].y2) || (pacY >= wall[i].y1 && pacY <= wall[i].y2))){
                pacX-=1;
                pacMoveRight = false;
                pacBase = true;
            }
        }
        if(pacMoveUp){
            if((pacY+15 >= wall[i].y1 && pacY+15 <= wall[i].y2) && ((pacX+15 >= wall[i].x1 && pacX+15 <= wall[i].x2) || (pacX >= wall[i].x1 && pacX <= wall[i].x2))){
                pacMoveUp = false;
                pacY-=1;
                pacBase = true;
            }
        }
        if(pacMoveLeft){
            if((pacX >= wall[i].x1 && pacX <= wall[i].x2) && ((pacY+15 >= wall[i].y1 && pacY+15 <= wall[i].y2) ||(pacY >= wall[i].y1 && pacY <= wall[i].y2))){
                pacMoveLeft = false;
                pacX+=1;
                pacBase = true;
            }
        }
    }
    dotCollusionCheck();
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key) {

	if (key == GLUT_KEY_UP) {
        if(changeDirection()){
            pacMoveUp = true;
            pacMoveDown = false;
            pacMoveLeft = false;
            pacMoveRight = false;
            pacBase = false;
        }

	}
	if (key == GLUT_KEY_DOWN) {
		if(changeDirection()){
            pacMoveUp = false;
            pacMoveDown = true;
            pacMoveLeft = false;
            pacMoveRight = false;
            pacBase = false;
        }
	}
	if (key == GLUT_KEY_LEFT) {
		if(changeDirection()){
            pacMoveUp = false;
            pacMoveDown = false;
            pacMoveLeft = true;
            pacMoveRight = false;
            pacBase = false;
        }
	}
	if (key == GLUT_KEY_RIGHT) {
		if(changeDirection()){
            pacMoveUp = false;
            pacMoveDown = false;
            pacMoveLeft = false;
            pacMoveRight = true;
            pacBase = false;
        }
	}
	//place your codes for other keys here
}

void changePacCordinate()
{
    if(pacMoveRight){
        pacX+=1;
    }
    if(pacMoveLeft){
         pacX-=1;
    }
    if(pacMoveDown){
        pacY-=1;
    }
    if(pacMoveUp){
        pacY+=1;
    }


}

void changeImageIndx(){
    if(pacMoveRight){
        rightMovementIndx+=1;
        if(rightMovementIndx >= 3) rightMovementIndx = 0;
    }
    if(pacMoveLeft){
        leftMovementIndx+=1;
        if(leftMovementIndx >= 3) leftMovementIndx = 0;
    }
    if(pacMoveUp){
        upMovementIndx+=1;
        if(upMovementIndx >= 3) upMovementIndx = 0;
    }
    if(pacMoveDown){
        downMovementIndx+=1;
        if(downMovementIndx >= 3) downMovementIndx = 0;
    }
    if(fGhost){
        if(elapsed >= 7.0){
            if(fGhostB) fGhostB = false;
            else fGhostB = true;
        }
    }
}
int ara[4];

void trackPackPosition(int startX, int startY, int indx){
    int j = (pacX - 100 + 5)/20;
    int i = (660 - pacY+5)/20;

    int check[29][30]=
{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,
    1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,
    1,0,1,0,0,1,1,1,0,0,1,0,0,0,1,1,0,0,0,1,0,0,1,1,1,0,0,1,0,1,
    1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
    1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
    1,0,1,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,1,0,1,
    1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,
    1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,
    1,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,1,
    1,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,
    1,0,1,0,1,0,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,1,0,1,0,1,
    1,0,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,0,1,
    1,0,1,0,1,0,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,1,0,1,0,1,
    1,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,
    1,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,1,
    1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,
    1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,
    1,0,1,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,1,0,1,
    1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
    1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
    1,0,1,0,0,1,1,1,0,0,1,0,0,0,1,1,0,0,0,1,0,0,1,1,1,0,0,1,0,1,
    1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,
    1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};
 generateRandomIndx(ara);
 int path = dfs(startX, startY, i, j, check, 0, indx);
}
int dfs(int startI, int startJ, int endI, int endJ, int check[29][30], int path_found, int l){
    if(startI == endI && startJ == endJ){
        ghost[l].pathX[ghost[l].indx] = startI;
        ghost[l].pathY[ghost[l].indx] = startJ;
        ghost[l].indx++;
        return 1;
    }

    check[startI][startJ] = 1;

    for(int i = 0; i < 4; i++){
        if(path_found) break;
        if(ara[i] == 0){
            if(check[startI+1][startJ]) continue;
            if(!check[startI+1][startJ]) path_found|=dfs(startI+1, startJ, endI, endJ, check, path_found, l);
        }
        if(ara[i] == 1){
           if(check[startI-1][startJ]) continue;
           if(!check[startI-1][startJ]) path_found|=dfs(startI-1, startJ, endI, endJ, check, path_found, l);
        }
        if(ara[i] == 2){
            if(check[startI][startJ+1]) continue;
            if(!check[startI][startJ+1]) path_found|=dfs(startI, startJ+1, endI, endJ, check, path_found, l);
        }
        if(ara[i] == 3){
            if(check[startI][startJ-1]) continue;
            if(!check[startI][startJ-1]) path_found|=dfs(startI, startJ-1, endI, endJ, check, path_found, l);
        }
    }
    if(path_found){
        ghost[l].pathX[ghost[l].indx] = startI;
        ghost[l].pathY[ghost[l].indx] = startJ;
        ghost[l].indx++;
    }
    return path_found;
}
void generateRandomIndx(int ara[]){
    for(int i = 0; i < 4; i++){
        ara[i] = i;
    }
    srand(time(0));

    for(int i = 3; i >= 0; i--){
        int indx = rand() % 4;
        int temp = ara[indx];
        ara[indx] = ara[i];
        ara[i] = temp;
    }
}
void showGhost(){

   if(fGhost){
        for(int i = 0; i < 4; i++){
            if(!fGhostB) iShowBMP2(ghost[i].x, ghost[i].y, "pacman/fGhost.bmp", 0);
            else iShowBMP2(ghost[i].x, ghost[i].y, "pacman/fGhostB.bmp", 0);
        }
        return;
   }
    for(int i = 0; i < 4; i++){
        if(ghost[i].mxp){
            iShowBMP2(ghost[i].x, ghost[i].y, ghostRightImage[i], 0);
        }
        else if(ghost[i].mxn){
            iShowBMP2(ghost[i].x, ghost[i].y, ghostLeftImage[i], 0);
        }
        else if(ghost[i].myp){
            iShowBMP2(ghost[i].x, ghost[i].y, ghostUpImage[i], 0);
        }
        else if(ghost[i].myn){
            iShowBMP2(ghost[i].x, ghost[i].y, ghostDownImage[i], 0);
        }
        else iShowBMP2(ghost[i].x, ghost[i].y, ghostRightImage[i], 0);
    }
}
void defineGhost(){
    ghost[0].i = 14;
    ghost[0].j = 13;
    ghost[1].i = 14;
    ghost[1].j = 14;
    ghost[2].i = 14;
    ghost[2].j = 15;
    ghost[3].i = 14;
    ghost[3].j = 16;
    ghost[0].x = mazeStartX + (ghost[0].j) * 20;
    ghost[0].y = mazeStartY - (ghost[0].i) * 20;
    ghost[1].x = mazeStartX + (ghost[1].j) * 20;
    ghost[1].y = mazeStartY - (ghost[1].i) * 20;
    ghost[2].x = mazeStartX + (ghost[2].j) * 20;
    ghost[2].y = mazeStartY - (ghost[2].i) * 20;
    ghost[3].x = mazeStartX + (ghost[3].j) * 20;
    ghost[3].y = mazeStartY - (ghost[3].i) * 20;

    for(int i = 0; i < 4; i++){
        ghost[i].indx = 0;
        ghost[i].mxn = false;
        ghost[i].mxp = false;
        ghost[i].myp = false;
        ghost[i].myn = false;
        ghost[i].ct = 0;
    }
}
void findPath(int i){

    trackPackPosition(ghost[i].i, ghost[i].j,  i);
    ghost[i].indx-=2;

}
void ghostMovement(){
    int r = movingGhost;
    if(r == 4) r = 3;
     for(int i = 0; i < r; i++){
        if(!ghost[i].mxn && !ghost[i].mxp && !ghost[i].myp && !ghost[i].myn){
           if(ghost[i].pathY[ghost[i].indx] == ghost[i].j){
                if(ghost[i].pathX[ghost[i].indx] > ghost[i].i){
                    ghost[i].myn = true;
                }

                else ghost[i].myp = true;
           }
           else{
              if(ghost[i].pathY[ghost[i].indx] > ghost[i].j){
                    ghost[i].mxp = true;
              }
              else ghost[i].mxn = true;

           }
     }
     else{

        if(ghost[i].mxp){
            ghost[i].x++;
        }
        else if(ghost[i].mxn){
            ghost[i].x--;
        }
        else if(ghost[i].myp){
            ghost[i].y++;
        }
        else if(ghost[i].myn){
            ghost[i].y--;
        }
        ghost[i].ct++;
        if(ghost[i].ct >= 20){
            ghost[i].i = ghost[i].pathX[ghost[i].indx];
            ghost[i].j = ghost[i].pathY[ghost[i].indx];
            ghost[i].indx--;
            ghost[i].ct = 0;
            if(ghost[i].indx == 0) findPath(i);
            ghost[i].mxn = false;
            ghost[i].mxp = false;
            ghost[i].myp = false;
            ghost[i].myn = false;
        }
       }
     }

    if(bfsMove) bfsMovement();
    ghostCollusion();
    if(fGhost){
        elapsed = (double)(finish - start) / CLOCKS_PER_SEC;
        if(elapsed >= 10.0){
            fGhost = false;
            fGhostSound = false;
            fGhostB = false;
            if(gameSound) PlaySound("Sounds/pacman_chomp.wav", NULL, SND_LOOP | SND_ASYNC);
        }
    }

}

//BFS Here
vector<pair<int, int>> path;
void bfs(){
    path.clear();
    int j = (pacX - 100 + 5)/20;
    int i = (660 - pacY+5)/20;
    vector <pair<pair<int, int>, pair<int, int>>> source;
    queue <pair<int, int>> q;
    vector <pair<int, int>> direction = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int check[29][30]=
{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,
    1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,
    1,0,1,0,0,1,1,1,0,0,1,0,0,0,1,1,0,0,0,1,0,0,1,1,1,0,0,1,0,1,
    1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
    1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
    1,0,1,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,1,0,1,
    1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,
    1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,
    1,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,1,
    1,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,
    1,0,1,0,1,0,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,1,0,1,0,1,
    1,0,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,0,1,
    1,0,1,0,1,0,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,1,0,1,0,1,
    1,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,
    1,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,1,
    1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,
    1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,
    1,0,1,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,1,0,1,
    1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
    1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
    1,0,1,0,0,1,1,1,0,0,1,0,0,0,1,1,0,0,0,1,0,0,1,1,1,0,0,1,0,1,
    1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,
    1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
    };
    int sourceX = ghost[3].i;
    int sourceY = ghost[3].j;
    q.push({sourceX, sourceY});
    source.push_back({{-1, -1}, {sourceX, sourceY}});
    while(true){
        if(sourceX == i && sourceY == j){
            break;
        }
        pair <int, int> temp = q.front();
        sourceX = temp.first;
        sourceY = temp.second;

        for(int j = 0; j < 4; j++){
            int x = sourceX+direction[j].first;
            int y = sourceY+direction[j].second;
            if(check[x][y] == 0){
                q.push({x, y});
                source.push_back({{sourceX, sourceY}, {x, y}});
                check[x][y] = 1;
            }
        }
        q.pop();
    }
    path.push_back({i, j});
    for(int r = source.size()-1; r >= 0; r--){
        if(source[r].second.first == i && source[r].second.second == j){
            path.push_back({source[r].first.first, source[r].first.second});
            i = source[r].first.first;
            j = source[r].first.second;
        }
    }
    path.pop_back();
    path.pop_back();
}

void bfsMovement(){
    if(!ghost[3].mxp && !ghost[3].mxn && !ghost[3].myp && !ghost[3].myn){
        bfs();
        if(ghost[3].i == path[path.size()-1].first){
            if(ghost[3].j > path[path.size()-1].second) ghost[3].mxn = true;
            else ghost[3].mxp = true;
        }
        if(ghost[3].j == path[path.size()-1].second){
            if(ghost[3].i > path[path.size()-1].first) ghost[3].myp = true;
            else ghost[3].myn = true;
        }
    }
     else{
        if(ghost[3].mxp){
            ghost[3].x++;
        }
        else if(ghost[3].mxn){
            ghost[3].x--;
        }
        else if(ghost[3].myp){
            ghost[3].y++;
        }
        else if(ghost[3].myn){
            ghost[3].y--;
        }
        ghost[3].ct++;
        if(ghost[3].ct >= 20){
            ghost[3].i = path[path.size()-1].first;
            ghost[3].j = path[path.size()-1].second;
            ghost[3].ct = 0;
            ghost[3].mxn = false;
            ghost[3].mxp = false;
            ghost[3].myp = false;
            ghost[3].myn = false;
        }
     }
}
char introSource[] = "Video/Intro/pacman000.bmp";
void changeIntroIndx(){
        introIndx++;
     if(introIndx >= 418){
        gameState = 1;
        if(gameSound) PlaySound("Sounds/begin.wav", NULL, SND_FILENAME | SND_ASYNC);
        iPauseTimer(timerId1);
     }

}
void showIntro(){
    iShowBMP(0, 0, introSource);
    int frameNumber = introIndx;
    snprintf(introSource, sizeof(introSource), "Video/Intro/pacman%03d.bmp", frameNumber);

}
void showMenu(){
    iShowBMP(0, 0, "pacman/backgroundMain1.bmp");
    iShowBMP2(420, 520, "Menu/play.bmp", 0);
    iShowBMP2(420, 520-65, "Menu/difficulty.bmp", 0);
    iShowBMP2(420, 520-65*2, "Menu/instruction.bmp", 0);
    iShowBMP2(420, 520-65*3, "Menu/score.bmp", 0);
    iShowBMP2(420, 520-65*4, "Menu/music.bmp", 0);
}
typedef struct{
    bool show;
    int x, y;
    bool s = false;
}dotsCordinate;

dotsCordinate dots[550];

void saveDots()
{
   int mazeY = mazeStartY;
   int ct = 0;
	for(int i = 0; i < 29; i++){
        int mazeX= mazeStartX;

        for(int j = 0; j < 30; j++){
            if(maze[i][j] == 0){
                dots[ct].x = mazeX+5;
                dots[ct].y = mazeY+5;
                dots[ct].show = true;
                dots[ct].s = false;
                ct++;
            }
            if(maze[i][j] == 2){
                dots[ct].x = mazeX+5;
                dots[ct].y = mazeY+5;
                dots[ct].show = true;
                dots[ct].s = true;
                ct++;
            }
            mazeX = mazeX + 20;
        }
        mazeY = mazeY - 20;
	}

}
void setDots(){
    iSetColor(255, 255, 255);
    for(int i = 0; i < 550; i++){
        if(dots[i].show && !dots[i].s){
            iFilledCircle(dots[i].x, dots[i].y, 1, 100);

        }
        if(dots[i].show && dots[i].s){
            iShowBMP2(dots[i].x, dots[i].y, "pacman/bigDot.bmp", 0);
        }
    }
}

void dotCollusionCheck(){
    for(int i = 0; i < 550; i++){
        if(pacMoveUp){
            if(dots[i].y >= pacY && dots[i].y <= pacY+15 && dots[i].x >= pacX && dots[i].x <= pacX+15){
                 if(dots[i].s){
                    if(!fGhostSound){
                        fGhostSound = true;
                        if(gameSound) PlaySound("Sounds/fright_firstloop.wav", NULL, SND_LOOP | SND_ASYNC);
                    }
                    dots[i].s = false;
                    fGhost = true;
                    start = clock();
                    liveScore+=99;
                 }
                 if(dots[i].show)liveScore++;
                 dots[i].show = false;

            }
        }
        if(pacMoveLeft){
            if(dots[i].y >= pacY && dots[i].y <= pacY+15 && dots[i].x == pacX){
                 if(dots[i].s){
                    if(!fGhostSound){
                        fGhostSound = true;
                        if(gameSound) PlaySound("Sounds/fright_firstloop.wav", NULL, SND_LOOP | SND_ASYNC);
                    }
                    dots[i].s = false;
                    fGhost = true;
                    start = clock();
                    liveScore+=100;
                 }
                 if(dots[i].show)liveScore++;
                 dots[i].show = false;
            }
        }
        if(pacMoveDown){
            if(dots[i].y == pacY && dots[i].x >= pacX && dots[i].x <= pacX+15){
                if(dots[i].s){
                    if(!fGhostSound){
                        fGhostSound = true;
                        if(gameSound) PlaySound("Sounds/fright_firstloop.wav", NULL, SND_LOOP | SND_ASYNC);
                    }
                     dots[i].s = false;
                    fGhost = true;
                    start = clock();
                    liveScore+=99;
                 }
                 if(dots[i].show)liveScore++;
                 dots[i].show = false;
            }
        }
        if(pacMoveRight){
            if(dots[i].y >= pacY && dots[i].y <= pacY+15 && dots[i].x >= pacX && dots[i].x <= pacX+15){
                 if(dots[i].s){
                    if(!fGhostSound){
                        fGhostSound = true;
                        if(gameSound) PlaySound("Sounds/fright_firstloop.wav", NULL, SND_LOOP | SND_ASYNC);
                    }
                    dots[i].s = false;
                    fGhost = true;
                    start = clock();
                    liveScore+=99;
                 }
                 if(dots[i].show)liveScore++;
                 dots[i].show = false;
            }
        }
    }
}

void showScore(){
    if(scoreLvl == 1){
        iShowBMP2(200, 0, "Menu/hscore.bmp", 0);
        if(!gamePlayed) iShowBMP2(5, 660, "Menu/back.bmp", 0);
        iShowBMP2(780, 660, "Menu/easy.bmp", 0);
        iShowBMP2(780, 60, "Menu/next.bmp", 0);

        int startX = 450, startY = 487;

        FILE *fp_in = fopen("Score/easy.txt", "r");

        for(int i = 0; i < 10; i++){
            char line[100], temp[50];
            int point;
            char pointStr[6];

            fgets(line, 100, fp_in);
            sscanf(line, "%s %d", &temp, &point);
            sprintf(pointStr, "%d", point);

            iText(startX, startY, temp, GLUT_BITMAP_TIMES_ROMAN_24);
            iText(startX+200, startY, pointStr, GLUT_BITMAP_TIMES_ROMAN_24);
            startY-=47;

        }
        fclose(fp_in);
    }
    if(scoreLvl == 2){
        iShowBMP2(200, 0, "Menu/hscore.bmp", 0);
        iShowBMP2(5, 660, "Menu/back.bmp", 0);
        iShowBMP2(780, 660, "Menu/medium.bmp", 0);
        iShowBMP2(780, 60, "Menu/next.bmp", 0);


        int startX = 450, startY = 487;

        FILE *fp_in = fopen("Score/medium.txt", "r");

        for(int i = 0; i < 10; i++){
            char line[100], temp[50];
            int point;
            char pointStr[6];

            fgets(line, 100, fp_in);
            sscanf(line, "%s %d", &temp, &point);
            sprintf(pointStr, "%d", point);

            iText(startX, startY, temp, GLUT_BITMAP_TIMES_ROMAN_24);
            iText(startX+200, startY, pointStr, GLUT_BITMAP_TIMES_ROMAN_24);
            startY-=47;

        }
        fclose(fp_in);
    }
    if(scoreLvl == 3){
        iShowBMP2(200, 0, "Menu/hscore.bmp", 0);
        iShowBMP2(5, 660, "Menu/back.bmp", 0);
        iShowBMP2(780, 660, "Menu/hard.bmp", 0);
        if(gamePlayed) iShowBMP2(780, 60, "Menu/quit.bmp", 0);


        int startX = 450, startY = 487;

        FILE *fp_in = fopen("Score/hard.txt", "r");

        for(int i = 0; i < 10; i++){
            char line[100], temp[50];
            int point;
            char pointStr[6];

            fgets(line, 100, fp_in);
            sscanf(line, "%s %d", &temp, &point);
            sprintf(pointStr, "%d", point);

            iText(startX, startY, temp, GLUT_BITMAP_TIMES_ROMAN_24);
            iText(startX+200, startY, pointStr, GLUT_BITMAP_TIMES_ROMAN_24);
            startY-=47;

        }
        fclose(fp_in);
    }
}
void difficultyPage(){
    iShowBMP(0, 0, "pacman/backgroundMain1.bmp");
    iShowBMP2(250, 250, "Menu/easy.bmp", 0);
    iShowBMP2(250 + 170, 250, "Menu/medium.bmp", 0);
    iShowBMP2(250 + 170 * 2,  250, "Menu/hard.bmp", 0);
}

void releaseGhost(){
    ghost[movingGhost].indx = 0;
    findPath(movingGhost);
    movingGhost++;
    if(movingGhost == 4){
        bfsMove = true;
        iPauseTimer(timerId6);
    }
}

void initializeGame()
{
    if(gameDifficulty == 1){
        ghostRealseInterval = 20000;
    }
    if(gameDifficulty == 2){
        ghostRealseInterval = 10000;
    }
    if(gameDifficulty == 3){
        ghostRealseInterval = 5000;
    }

    timerId6 = iSetTimer(ghostRealseInterval, releaseGhost);
    timerId2 = iSetTimer(15, changePacCordinate);
    timerId3 = iSetTimer(90, changeImageIndx);
    timerId4 = iSetTimer(1, checkCordinate);
	timerId5 = iSetTimer(1, ghostMovement);

}
void ghostCollusion(){

    for (int i = 0; i < movingGhost; i++) {
        if (ghost[i].mxp && pacMoveRight) {
            if (ghost[i].x + 15 >= pacX && ghost[i].x < pacX + 15){
                if (ghost[i].y + 15 >= pacY && ghost[i].y <= pacY + 15) {
                    if(!fGhost){
                        iPauseTimer(timerId2);
                        iPauseTimer(timerId3);
                        iPauseTimer(timerId5);
                        dying = true;
                        if(gameSound) PlaySound("Sounds/death.wav", NULL, SND_FILENAME | SND_ASYNC);
                        if(life == 3){
                            timerId7 = iSetTimer(30, playDieAnimation);
                        }
                        else iResumeTimer(timerId7);
                        life--;
                    }
                    else{
                        iPauseTimer(timerId5);
                        if(i == 0){
                            ghost[0].i = 14;
                            ghost[0].j = 13;
                            ghost[0].x = mazeStartX + (ghost[0].j) * 20;
                            ghost[0].y = mazeStartY - (ghost[0].i) * 20;
                        }
                        if(i == 1){
                            ghost[1].i = 14;
                            ghost[1].j = 14;
                            ghost[1].x = mazeStartX + (ghost[1].j) * 20;
                            ghost[1].y = mazeStartY - (ghost[1].i) * 20;
                        }
                        if(i == 2){
                            ghost[2].i = 14;
                            ghost[2].j = 15;
                            ghost[2].x = mazeStartX + (ghost[2].j) * 20;
                            ghost[2].y = mazeStartY - (ghost[2].i) * 20;
                        }
                        if(i == 3){
                           ghost[3].i = 14;
                           ghost[3].j = 16;
                           ghost[3].x = mazeStartX + (ghost[3].j) * 20;
                           ghost[3].y = mazeStartY - (ghost[3].i) * 20;
                        }
                        ghost[i].indx = 0;
                        ghost[i].ct = 0;
                        ghost[i].mxn = false;
                        ghost[i].mxp = false;
                        ghost[i].myp = false;
                        ghost[i].myn = false;
                        liveScore+=500;
                        findPath(i);
                        iResumeTimer(timerId5);

                    }
                }
            }
        }
        if (ghost[i].mxp && pacMoveLeft) {
            if (ghost[i].x + 15 >= pacX && ghost[i].x < pacX + 15) {
                if (ghost[i].y + 15 >= pacY && ghost[i].y <= pacY + 15) {
                    if(!fGhost){
                        iPauseTimer(timerId2);
                        iPauseTimer(timerId3);
                        iPauseTimer(timerId5);
                        dying = true;
                        if(gameSound) PlaySound("Sounds/death.wav", NULL, SND_FILENAME | SND_ASYNC);
                        if(life == 3){
                            timerId7 = iSetTimer(30, playDieAnimation);
                        }
                        else iResumeTimer(timerId7);
                        life--;
                    }
                    else{
                        iPauseTimer(timerId5);
                        if(i == 0){
                            ghost[0].i = 14;
                            ghost[0].j = 13;
                            ghost[0].x = mazeStartX + (ghost[0].j) * 20;
                            ghost[0].y = mazeStartY - (ghost[0].i) * 20;
                        }
                        if(i == 1){
                            ghost[1].i = 14;
                            ghost[1].j = 14;
                            ghost[1].x = mazeStartX + (ghost[1].j) * 20;
                            ghost[1].y = mazeStartY - (ghost[1].i) * 20;
                        }
                        if(i == 2){
                            ghost[2].i = 14;
                            ghost[2].j = 15;
                            ghost[2].x = mazeStartX + (ghost[2].j) * 20;
                            ghost[2].y = mazeStartY - (ghost[2].i) * 20;
                        }
                        if(i == 3){
                           ghost[3].i = 14;
                           ghost[3].j = 16;
                           ghost[3].x = mazeStartX + (ghost[3].j) * 20;
                           ghost[3].y = mazeStartY - (ghost[3].i) * 20;
                        }
                        ghost[i].indx = 0;
                        ghost[i].ct = 0;
                        ghost[i].mxn = false;
                        ghost[i].mxp = false;
                        ghost[i].myp = false;
                        ghost[i].myn = false;
                        liveScore+=500;
                        findPath(i);
                        iResumeTimer(timerId5);

                    }
                }
            }
        }
        if (ghost[i].mxp && pacMoveUp) {
            if (ghost[i].x + 15 >= pacX && ghost[i].x < pacX + 15) {
                if (ghost[i].y + 15 >= pacY && ghost[i].y <= pacY + 15) {
                    if(!fGhost){
                        iPauseTimer(timerId2);
                        iPauseTimer(timerId3);
                        iPauseTimer(timerId5);
                        dying = true;
                        if(gameSound) PlaySound("Sounds/death.wav", NULL, SND_FILENAME | SND_ASYNC);
                        if(life == 3){
                            timerId7 = iSetTimer(30, playDieAnimation);
                        }
                        else iResumeTimer(timerId7);
                        life--;
                    }
                    else{
                        iPauseTimer(timerId5);
                        if(i == 0){
                            ghost[0].i = 14;
                            ghost[0].j = 13;
                            ghost[0].x = mazeStartX + (ghost[0].j) * 20;
                            ghost[0].y = mazeStartY - (ghost[0].i) * 20;
                        }
                        if(i == 1){
                            ghost[1].i = 14;
                            ghost[1].j = 14;
                            ghost[1].x = mazeStartX + (ghost[1].j) * 20;
                            ghost[1].y = mazeStartY - (ghost[1].i) * 20;
                        }
                        if(i == 2){
                            ghost[2].i = 14;
                            ghost[2].j = 15;
                            ghost[2].x = mazeStartX + (ghost[2].j) * 20;
                            ghost[2].y = mazeStartY - (ghost[2].i) * 20;
                        }
                        if(i == 3){
                           ghost[3].i = 14;
                           ghost[3].j = 16;
                           ghost[3].x = mazeStartX + (ghost[3].j) * 20;
                           ghost[3].y = mazeStartY - (ghost[3].i) * 20;
                        }
                        ghost[i].indx = 0;
                        ghost[i].ct = 0;
                        ghost[i].mxn = false;
                        ghost[i].mxp = false;
                        ghost[i].myp = false;
                        ghost[i].myn = false;
                        liveScore+=500;
                        findPath(i);
                        iResumeTimer(timerId5);

                    }
                }
            }
        }
        if (ghost[i].mxp && pacMoveDown) {
            if (ghost[i].x + 15 >= pacX && ghost[i].x < pacX + 15) {
                if (ghost[i].y + 15 >= pacY && ghost[i].y <= pacY + 15) {
                    if(!fGhost){
                        iPauseTimer(timerId2);
                        iPauseTimer(timerId3);
                        iPauseTimer(timerId5);
                        dying = true;
                        if(gameSound) PlaySound("Sounds/death.wav", NULL, SND_FILENAME | SND_ASYNC);
                        if(life == 3){
                            timerId7 = iSetTimer(30, playDieAnimation);
                        }
                        else iResumeTimer(timerId7);
                        life--;
                    }
                    else{
                        iPauseTimer(timerId5);
                        if(i == 0){
                            ghost[0].i = 14;
                            ghost[0].j = 13;
                            ghost[0].x = mazeStartX + (ghost[0].j) * 20;
                            ghost[0].y = mazeStartY - (ghost[0].i) * 20;
                        }
                        if(i == 1){
                            ghost[1].i = 14;
                            ghost[1].j = 14;
                            ghost[1].x = mazeStartX + (ghost[1].j) * 20;
                            ghost[1].y = mazeStartY - (ghost[1].i) * 20;
                        }
                        if(i == 2){
                            ghost[2].i = 14;
                            ghost[2].j = 15;
                            ghost[2].x = mazeStartX + (ghost[2].j) * 20;
                            ghost[2].y = mazeStartY - (ghost[2].i) * 20;
                        }
                        if(i == 3){
                           ghost[3].i = 14;
                           ghost[3].j = 16;
                           ghost[3].x = mazeStartX + (ghost[3].j) * 20;
                           ghost[3].y = mazeStartY - (ghost[3].i) * 20;
                        }
                        ghost[i].indx = 0;
                        ghost[i].ct = 0;
                        ghost[i].mxn = false;
                        ghost[i].mxp = false;
                        ghost[i].myp = false;
                        ghost[i].myn = false;
                        liveScore+=500;
                        findPath(i);
                        iResumeTimer(timerId5);

                    }
                }
            }
        }
        if (ghost[i].mxn && pacMoveRight) {
            if (ghost[i].x <= pacX + 15 && ghost[i].x > pacX) {
                if (ghost[i].y + 15 >= pacY && ghost[i].y <= pacY + 15) {
                    if(!fGhost){
                        iPauseTimer(timerId2);
                        iPauseTimer(timerId3);
                        iPauseTimer(timerId5);
                        dying = true;
                        if(gameSound) PlaySound("Sounds/death.wav", NULL, SND_FILENAME | SND_ASYNC);
                        if(life == 3){
                            timerId7 = iSetTimer(30, playDieAnimation);
                        }
                        else iResumeTimer(timerId7);
                        life--;
                    }
                    else{
                        iPauseTimer(timerId5);
                        if(i == 0){
                            ghost[0].i = 14;
                            ghost[0].j = 13;
                            ghost[0].x = mazeStartX + (ghost[0].j) * 20;
                            ghost[0].y = mazeStartY - (ghost[0].i) * 20;
                        }
                        if(i == 1){
                            ghost[1].i = 14;
                            ghost[1].j = 14;
                            ghost[1].x = mazeStartX + (ghost[1].j) * 20;
                            ghost[1].y = mazeStartY - (ghost[1].i) * 20;
                        }
                        if(i == 2){
                            ghost[2].i = 14;
                            ghost[2].j = 15;
                            ghost[2].x = mazeStartX + (ghost[2].j) * 20;
                            ghost[2].y = mazeStartY - (ghost[2].i) * 20;
                        }
                        if(i == 3){
                           ghost[3].i = 14;
                           ghost[3].j = 16;
                           ghost[3].x = mazeStartX + (ghost[3].j) * 20;
                           ghost[3].y = mazeStartY - (ghost[3].i) * 20;
                        }
                        ghost[i].indx = 0;
                        ghost[i].ct = 0;
                        ghost[i].mxn = false;
                        ghost[i].mxp = false;
                        ghost[i].myp = false;
                        ghost[i].myn = false;
                        liveScore+=500;
                        findPath(i);
                        iResumeTimer(timerId5);

                    }
                }
            }
        }
        if (ghost[i].mxn && pacMoveLeft) {
            if (ghost[i].x <= pacX + 15 && ghost[i].x > pacX) {
                if (ghost[i].y + 15 >= pacY && ghost[i].y <= pacY + 15) {
                    if(!fGhost){
                        iPauseTimer(timerId2);
                        iPauseTimer(timerId3);
                        iPauseTimer(timerId5);
                        dying = true;
                        if(gameSound) PlaySound("Sounds/death.wav", NULL, SND_FILENAME | SND_ASYNC);
                        if(life == 3){
                            timerId7 = iSetTimer(30, playDieAnimation);
                        }
                        else iResumeTimer(timerId7);
                        life--;
                    }
                    else{
                        iPauseTimer(timerId5);
                        if(i == 0){
                            ghost[0].i = 14;
                            ghost[0].j = 13;
                            ghost[0].x = mazeStartX + (ghost[0].j) * 20;
                            ghost[0].y = mazeStartY - (ghost[0].i) * 20;
                        }
                        if(i == 1){
                            ghost[1].i = 14;
                            ghost[1].j = 14;
                            ghost[1].x = mazeStartX + (ghost[1].j) * 20;
                            ghost[1].y = mazeStartY - (ghost[1].i) * 20;
                        }
                        if(i == 2){
                            ghost[2].i = 14;
                            ghost[2].j = 15;
                            ghost[2].x = mazeStartX + (ghost[2].j) * 20;
                            ghost[2].y = mazeStartY - (ghost[2].i) * 20;
                        }
                        if(i == 3){
                           ghost[3].i = 14;
                           ghost[3].j = 16;
                           ghost[3].x = mazeStartX + (ghost[3].j) * 20;
                           ghost[3].y = mazeStartY - (ghost[3].i) * 20;
                        }
                        ghost[i].indx = 0;
                        ghost[i].ct = 0;
                        ghost[i].mxn = false;
                        ghost[i].mxp = false;
                        ghost[i].myp = false;
                        ghost[i].myn = false;
                        liveScore+=500;
                        findPath(i);
                        iResumeTimer(timerId5);

                    }
                }
            }
        }
        if (ghost[i].mxn && pacMoveUp) {
            if (ghost[i].x <= pacX + 15 && ghost[i].x > pacX) {
                if (ghost[i].y + 15 >= pacY && ghost[i].y <= pacY + 15) {
                    if(!fGhost){
                        iPauseTimer(timerId2);
                        iPauseTimer(timerId3);
                        iPauseTimer(timerId5);
                        dying = true;
                        if(gameSound) PlaySound("Sounds/death.wav", NULL, SND_FILENAME | SND_ASYNC);
                        if(life == 3){
                            timerId7 = iSetTimer(30, playDieAnimation);
                        }
                        else iResumeTimer(timerId7);
                        life--;
                    }
                    else{
                        iPauseTimer(timerId5);
                        if(i == 0){
                            ghost[0].i = 14;
                            ghost[0].j = 13;
                            ghost[0].x = mazeStartX + (ghost[0].j) * 20;
                            ghost[0].y = mazeStartY - (ghost[0].i) * 20;
                        }
                        if(i == 1){
                            ghost[1].i = 14;
                            ghost[1].j = 14;
                            ghost[1].x = mazeStartX + (ghost[1].j) * 20;
                            ghost[1].y = mazeStartY - (ghost[1].i) * 20;
                        }
                        if(i == 2){
                            ghost[2].i = 14;
                            ghost[2].j = 15;
                            ghost[2].x = mazeStartX + (ghost[2].j) * 20;
                            ghost[2].y = mazeStartY - (ghost[2].i) * 20;
                        }
                        if(i == 3){
                           ghost[3].i = 14;
                           ghost[3].j = 16;
                           ghost[3].x = mazeStartX + (ghost[3].j) * 20;
                           ghost[3].y = mazeStartY - (ghost[3].i) * 20;
                        }
                        ghost[i].indx = 0;
                        ghost[i].ct = 0;
                        ghost[i].mxn = false;
                        ghost[i].mxp = false;
                        ghost[i].myp = false;
                        ghost[i].myn = false;
                        liveScore+=500;
                        findPath(i);
                        iResumeTimer(timerId5);

                    }
                }
            }
        }
        if (ghost[i].mxn && pacMoveDown) {
            if (ghost[i].x <= pacX + 15 && ghost[i].x > pacX) {
                if (ghost[i].y + 15 >= pacY && ghost[i].y <= pacY + 15) {
                    if(!fGhost){
                        iPauseTimer(timerId2);
                        iPauseTimer(timerId3);
                        iPauseTimer(timerId5);
                        dying = true;
                        if(gameSound) PlaySound("Sounds/death.wav", NULL, SND_FILENAME | SND_ASYNC);
                        if(life == 3){
                            timerId7 = iSetTimer(30, playDieAnimation);
                        }
                        else iResumeTimer(timerId7);
                        life--;
                    }
                    else{
                        iPauseTimer(timerId5);
                        if(i == 0){
                            ghost[0].i = 14;
                            ghost[0].j = 13;
                            ghost[0].x = mazeStartX + (ghost[0].j) * 20;
                            ghost[0].y = mazeStartY - (ghost[0].i) * 20;
                        }
                        if(i == 1){
                            ghost[1].i = 14;
                            ghost[1].j = 14;
                            ghost[1].x = mazeStartX + (ghost[1].j) * 20;
                            ghost[1].y = mazeStartY - (ghost[1].i) * 20;
                        }
                        if(i == 2){
                            ghost[2].i = 14;
                            ghost[2].j = 15;
                            ghost[2].x = mazeStartX + (ghost[2].j) * 20;
                            ghost[2].y = mazeStartY - (ghost[2].i) * 20;
                        }
                        if(i == 3){
                           ghost[3].i = 14;
                           ghost[3].j = 16;
                           ghost[3].x = mazeStartX + (ghost[3].j) * 20;
                           ghost[3].y = mazeStartY - (ghost[3].i) * 20;
                        }
                        ghost[i].indx = 0;
                        ghost[i].ct = 0;
                        ghost[i].mxn = false;
                        ghost[i].mxp = false;
                        ghost[i].myp = false;
                        ghost[i].myn = false;
                        liveScore+=500;
                        findPath(i);
                        iResumeTimer(timerId5);

                    }
                }
            }
        }
        if (ghost[i].myp && pacMoveRight) {
            if (ghost[i].x + 15 >= pacX && ghost[i].x < pacX + 15) {
                if (ghost[i].y + 15 >= pacY && ghost[i].y < pacY + 15) {
                    if(!fGhost){
                        iPauseTimer(timerId2);
                        iPauseTimer(timerId3);
                        iPauseTimer(timerId5);
                        dying = true;
                        if(gameSound) PlaySound("Sounds/death.wav", NULL, SND_FILENAME | SND_ASYNC);
                        if(life == 3){
                            timerId7 = iSetTimer(30, playDieAnimation);
                        }
                        else iResumeTimer(timerId7);
                        life--;
                    }
                    else{
                        iPauseTimer(timerId5);
                        if(i == 0){
                            ghost[0].i = 14;
                            ghost[0].j = 13;
                            ghost[0].x = mazeStartX + (ghost[0].j) * 20;
                            ghost[0].y = mazeStartY - (ghost[0].i) * 20;
                        }
                        if(i == 1){
                            ghost[1].i = 14;
                            ghost[1].j = 14;
                            ghost[1].x = mazeStartX + (ghost[1].j) * 20;
                            ghost[1].y = mazeStartY - (ghost[1].i) * 20;
                        }
                        if(i == 2){
                            ghost[2].i = 14;
                            ghost[2].j = 15;
                            ghost[2].x = mazeStartX + (ghost[2].j) * 20;
                            ghost[2].y = mazeStartY - (ghost[2].i) * 20;
                        }
                        if(i == 3){
                           ghost[3].i = 14;
                           ghost[3].j = 16;
                           ghost[3].x = mazeStartX + (ghost[3].j) * 20;
                           ghost[3].y = mazeStartY - (ghost[3].i) * 20;
                        }
                        ghost[i].indx = 0;
                        ghost[i].ct = 0;
                        ghost[i].mxn = false;
                        ghost[i].mxp = false;
                        ghost[i].myp = false;
                        ghost[i].myn = false;
                        liveScore+=500;
                        findPath(i);
                        iResumeTimer(timerId5);

                    }
                }
            }
        }
        if (ghost[i].myp && pacMoveLeft) {
            if (ghost[i].x + 15 >= pacX && ghost[i].x < pacX + 15) {
                if (ghost[i].y + 15 >= pacY && ghost[i].y < pacY + 15) {
                    if(!fGhost){
                        iPauseTimer(timerId2);
                        iPauseTimer(timerId3);
                        iPauseTimer(timerId5);
                        dying = true;
                        if(gameSound) PlaySound("Sounds/death.wav", NULL, SND_FILENAME | SND_ASYNC);
                        if(life == 3){
                            timerId7 = iSetTimer(30, playDieAnimation);
                        }
                        else iResumeTimer(timerId7);
                        life--;
                    }
                    else{
                        iPauseTimer(timerId5);
                        if(i == 0){
                            ghost[0].i = 14;
                            ghost[0].j = 13;
                            ghost[0].x = mazeStartX + (ghost[0].j) * 20;
                            ghost[0].y = mazeStartY - (ghost[0].i) * 20;
                        }
                        if(i == 1){
                            ghost[1].i = 14;
                            ghost[1].j = 14;
                            ghost[1].x = mazeStartX + (ghost[1].j) * 20;
                            ghost[1].y = mazeStartY - (ghost[1].i) * 20;
                        }
                        if(i == 2){
                            ghost[2].i = 14;
                            ghost[2].j = 15;
                            ghost[2].x = mazeStartX + (ghost[2].j) * 20;
                            ghost[2].y = mazeStartY - (ghost[2].i) * 20;
                        }
                        if(i == 3){
                           ghost[3].i = 14;
                           ghost[3].j = 16;
                           ghost[3].x = mazeStartX + (ghost[3].j) * 20;
                           ghost[3].y = mazeStartY - (ghost[3].i) * 20;
                        }
                        ghost[i].indx = 0;
                        ghost[i].ct = 0;
                        ghost[i].mxn = false;
                        ghost[i].mxp = false;
                        ghost[i].myp = false;
                        ghost[i].myn = false;
                        liveScore+=500;
                        findPath(i);
                        iResumeTimer(timerId5);

                    }
                }
            }
        }
        if (ghost[i].myp && pacMoveUp) {
            if (ghost[i].x + 15 >= pacX && ghost[i].x < pacX + 15) {
                if (ghost[i].y + 15 >= pacY && ghost[i].y < pacY + 15) {
                    if(!fGhost){
                        iPauseTimer(timerId2);
                        iPauseTimer(timerId3);
                        iPauseTimer(timerId5);
                        dying = true;
                        if(gameSound) PlaySound("Sounds/death.wav", NULL, SND_FILENAME | SND_ASYNC);
                        if(life == 3){
                            timerId7 = iSetTimer(30, playDieAnimation);
                        }
                        else iResumeTimer(timerId7);
                        life--;
                    }
                    else{
                        iPauseTimer(timerId5);
                        if(i == 0){
                            ghost[0].i = 14;
                            ghost[0].j = 13;
                            ghost[0].x = mazeStartX + (ghost[0].j) * 20;
                            ghost[0].y = mazeStartY - (ghost[0].i) * 20;
                        }
                        if(i == 1){
                            ghost[1].i = 14;
                            ghost[1].j = 14;
                            ghost[1].x = mazeStartX + (ghost[1].j) * 20;
                            ghost[1].y = mazeStartY - (ghost[1].i) * 20;
                        }
                        if(i == 2){
                            ghost[2].i = 14;
                            ghost[2].j = 15;
                            ghost[2].x = mazeStartX + (ghost[2].j) * 20;
                            ghost[2].y = mazeStartY - (ghost[2].i) * 20;
                        }
                        if(i == 3){
                           ghost[3].i = 14;
                           ghost[3].j = 16;
                           ghost[3].x = mazeStartX + (ghost[3].j) * 20;
                           ghost[3].y = mazeStartY - (ghost[3].i) * 20;
                        }
                        ghost[i].indx = 0;
                        ghost[i].ct = 0;
                        ghost[i].mxn = false;
                        ghost[i].mxp = false;
                        ghost[i].myp = false;
                        ghost[i].myn = false;
                        liveScore+=500;
                        findPath(i);
                        iResumeTimer(timerId5);

                    }
                }
            }
        }
        if (ghost[i].myp && pacMoveDown) {
            if (ghost[i].x + 15 >= pacX && ghost[i].x < pacX + 15) {
                if (ghost[i].y + 15 >= pacY && ghost[i].y < pacY + 15) {
                   if(!fGhost){
                        iPauseTimer(timerId2);
                        iPauseTimer(timerId3);
                        iPauseTimer(timerId5);
                        dying = true;
                        if(gameSound) PlaySound("Sounds/death.wav", NULL, SND_FILENAME | SND_ASYNC);
                        if(life == 3){
                            timerId7 = iSetTimer(30, playDieAnimation);
                        }
                        else iResumeTimer(timerId7);
                        life--;
                    }
                    else{
                        iPauseTimer(timerId5);
                        if(i == 0){
                            ghost[0].i = 14;
                            ghost[0].j = 13;
                            ghost[0].x = mazeStartX + (ghost[0].j) * 20;
                            ghost[0].y = mazeStartY - (ghost[0].i) * 20;
                        }
                        if(i == 1){
                            ghost[1].i = 14;
                            ghost[1].j = 14;
                            ghost[1].x = mazeStartX + (ghost[1].j) * 20;
                            ghost[1].y = mazeStartY - (ghost[1].i) * 20;
                        }
                        if(i == 2){
                            ghost[2].i = 14;
                            ghost[2].j = 15;
                            ghost[2].x = mazeStartX + (ghost[2].j) * 20;
                            ghost[2].y = mazeStartY - (ghost[2].i) * 20;
                        }
                        if(i == 3){
                           ghost[3].i = 14;
                           ghost[3].j = 16;
                           ghost[3].x = mazeStartX + (ghost[3].j) * 20;
                           ghost[3].y = mazeStartY - (ghost[3].i) * 20;
                        }
                        ghost[i].indx = 0;
                        ghost[i].ct = 0;
                        ghost[i].mxn = false;
                        ghost[i].mxp = false;
                        ghost[i].myp = false;
                        ghost[i].myn = false;
                        liveScore+=500;
                        findPath(i);
                        iResumeTimer(timerId5);

                    }
                }
            }
        }
        if (ghost[i].myn && pacMoveRight) {
            if (ghost[i].x + 15 >= pacX && ghost[i].x < pacX + 15) {
                if (ghost[i].y + 15 >= pacY && ghost[i].y < pacY + 15) {
                   if(!fGhost){
                        iPauseTimer(timerId2);
                        iPauseTimer(timerId3);
                        iPauseTimer(timerId5);
                        dying = true;
                        if(gameSound) PlaySound("Sounds/death.wav", NULL, SND_FILENAME | SND_ASYNC);
                        if(life == 3){
                            timerId7 = iSetTimer(30, playDieAnimation);
                        }
                        else iResumeTimer(timerId7);
                        life--;
                    }
                    else{
                        iPauseTimer(timerId5);
                        if(i == 0){
                            ghost[0].i = 14;
                            ghost[0].j = 13;
                            ghost[0].x = mazeStartX + (ghost[0].j) * 20;
                            ghost[0].y = mazeStartY - (ghost[0].i) * 20;
                        }
                        if(i == 1){
                            ghost[1].i = 14;
                            ghost[1].j = 14;
                            ghost[1].x = mazeStartX + (ghost[1].j) * 20;
                            ghost[1].y = mazeStartY - (ghost[1].i) * 20;
                        }
                        if(i == 2){
                            ghost[2].i = 14;
                            ghost[2].j = 15;
                            ghost[2].x = mazeStartX + (ghost[2].j) * 20;
                            ghost[2].y = mazeStartY - (ghost[2].i) * 20;
                        }
                        if(i == 3){
                           ghost[3].i = 14;
                           ghost[3].j = 16;
                           ghost[3].x = mazeStartX + (ghost[3].j) * 20;
                           ghost[3].y = mazeStartY - (ghost[3].i) * 20;
                        }
                        ghost[i].indx = 0;
                        ghost[i].ct = 0;
                        ghost[i].mxn = false;
                        ghost[i].mxp = false;
                        ghost[i].myp = false;
                        ghost[i].myn = false;
                        liveScore+=500;
                        findPath(i);
                        iResumeTimer(timerId5);

                    }
                }
            }
        }
        if (ghost[i].myn && pacMoveLeft) {
            if (ghost[i].x + 15 >= pacX && ghost[i].x < pacX + 15) {
                if (ghost[i].y + 15 >= pacY && ghost[i].y < pacY + 15) {
                   if(!fGhost){
                        iPauseTimer(timerId2);
                        iPauseTimer(timerId3);
                        iPauseTimer(timerId5);
                        dying = true;
                        if(gameSound) PlaySound("Sounds/death.wav", NULL, SND_FILENAME | SND_ASYNC);
                        if(life == 3){
                            timerId7 = iSetTimer(30, playDieAnimation);
                        }
                        else iResumeTimer(timerId7);
                        life--;
                    }
                    else{
                        iPauseTimer(timerId5);
                        if(i == 0){
                            ghost[0].i = 14;
                            ghost[0].j = 13;
                            ghost[0].x = mazeStartX + (ghost[0].j) * 20;
                            ghost[0].y = mazeStartY - (ghost[0].i) * 20;
                        }
                        if(i == 1){
                            ghost[1].i = 14;
                            ghost[1].j = 14;
                            ghost[1].x = mazeStartX + (ghost[1].j) * 20;
                            ghost[1].y = mazeStartY - (ghost[1].i) * 20;
                        }
                        if(i == 2){
                            ghost[2].i = 14;
                            ghost[2].j = 15;
                            ghost[2].x = mazeStartX + (ghost[2].j) * 20;
                            ghost[2].y = mazeStartY - (ghost[2].i) * 20;
                        }
                        if(i == 3){
                           ghost[3].i = 14;
                           ghost[3].j = 16;
                           ghost[3].x = mazeStartX + (ghost[3].j) * 20;
                           ghost[3].y = mazeStartY - (ghost[3].i) * 20;
                        }
                        ghost[i].indx = 0;
                        ghost[i].ct = 0;
                        ghost[i].mxn = false;
                        ghost[i].mxp = false;
                        ghost[i].myp = false;
                        ghost[i].myn = false;
                        liveScore+=500;
                        findPath(i);
                        iResumeTimer(timerId5);

                    }
                }
            }
        }
        if (ghost[i].myn && pacMoveUp) {
            if (ghost[i].x + 15 >= pacX && ghost[i].x < pacX + 15) {
                if (ghost[i].y + 15 >= pacY && ghost[i].y < pacY + 15) {
                    if(!fGhost){
                        iPauseTimer(timerId2);
                        iPauseTimer(timerId3);
                        iPauseTimer(timerId5);
                        dying = true;
                        if(gameSound) PlaySound("Sounds/death.wav", NULL, SND_FILENAME | SND_ASYNC);
                        if(life == 3){
                            timerId7 = iSetTimer(30, playDieAnimation);
                        }
                        else iResumeTimer(timerId7);
                        life--;
                    }
                    else{
                        iPauseTimer(timerId5);
                        if(i == 0){
                            ghost[0].i = 14;
                            ghost[0].j = 13;
                            ghost[0].x = mazeStartX + (ghost[0].j) * 20;
                            ghost[0].y = mazeStartY - (ghost[0].i) * 20;
                        }
                        if(i == 1){
                            ghost[1].i = 14;
                            ghost[1].j = 14;
                            ghost[1].x = mazeStartX + (ghost[1].j) * 20;
                            ghost[1].y = mazeStartY - (ghost[1].i) * 20;
                        }
                        if(i == 2){
                            ghost[2].i = 14;
                            ghost[2].j = 15;
                            ghost[2].x = mazeStartX + (ghost[2].j) * 20;
                            ghost[2].y = mazeStartY - (ghost[2].i) * 20;
                        }
                        if(i == 3){
                           ghost[3].i = 14;
                           ghost[3].j = 16;
                           ghost[3].x = mazeStartX + (ghost[3].j) * 20;
                           ghost[3].y = mazeStartY - (ghost[3].i) * 20;
                        }
                        ghost[i].indx = 0;
                        ghost[i].ct = 0;
                        ghost[i].mxn = false;
                        ghost[i].mxp = false;
                        ghost[i].myp = false;
                        ghost[i].myn = false;
                        liveScore+=500;
                        findPath(i);
                        iResumeTimer(timerId5);

                    }
                }
            }
        }
        if (ghost[i].myn && pacMoveDown) {
            if (ghost[i].x + 15 >= pacX && ghost[i].x < pacX + 15) {
                if (ghost[i].y + 15 >= pacY && ghost[i].y < pacY + 15) {
                   if(!fGhost){
                        iPauseTimer(timerId2);
                        iPauseTimer(timerId3);
                        iPauseTimer(timerId5);
                        dying = true;
                        if(gameSound) PlaySound("Sounds/death.wav", NULL, SND_FILENAME | SND_ASYNC);
                        if(life == 3){
                            timerId7 = iSetTimer(30, playDieAnimation);
                        }
                        else iResumeTimer(timerId7);
                        life--;
                    }
                    else{
                        iPauseTimer(timerId5);
                        if(i == 0){
                            ghost[0].i = 14;
                            ghost[0].j = 13;
                            ghost[0].x = mazeStartX + (ghost[0].j) * 20;
                            ghost[0].y = mazeStartY - (ghost[0].i) * 20;
                        }
                        if(i == 1){
                            ghost[1].i = 14;
                            ghost[1].j = 14;
                            ghost[1].x = mazeStartX + (ghost[1].j) * 20;
                            ghost[1].y = mazeStartY - (ghost[1].i) * 20;
                        }
                        if(i == 2){
                            ghost[2].i = 14;
                            ghost[2].j = 15;
                            ghost[2].x = mazeStartX + (ghost[2].j) * 20;
                            ghost[2].y = mazeStartY - (ghost[2].i) * 20;
                        }
                        if(i == 3){
                           ghost[3].i = 14;
                           ghost[3].j = 16;
                           ghost[3].x = mazeStartX + (ghost[3].j) * 20;
                           ghost[3].y = mazeStartY - (ghost[3].i) * 20;
                        }
                        ghost[i].indx = 0;
                        ghost[i].ct = 0;
                        ghost[i].mxn = false;
                        ghost[i].mxp = false;
                        ghost[i].myp = false;
                        ghost[i].myn = false;
                        liveScore+=500;
                        findPath(i);
                        iResumeTimer(timerId5);

                    }
                }
            }
        }
    }


}

void dieAnimation()
{
    if(pacMoveRight){
        char str[] = "pacman/Die/dieRight/die01.bmp";
        int frameNumber = dieAnimationIndx;
        snprintf(str, sizeof(str), "pacman/Die/dieRight/die%02d.bmp", dieAnimationIndx);
        iShowBMP2(pacX, pacY, str, 0);
    }
    if(pacMoveLeft){
        char str[] = "pacman/Die/dieLeft/die01.bmp";
        int frameNumber = dieAnimationIndx;
        snprintf(str, sizeof(str), "pacman/Die/dieLeft/die%02d.bmp", dieAnimationIndx);
        iShowBMP2(pacX, pacY, str, 0);
    }
    if(pacMoveUp){
        char str[] = "pacman/Die/dieUp/die01.bmp";
        int frameNumber = dieAnimationIndx;
        snprintf(str, sizeof(str), "pacman/Die/dieUp/die%02d.bmp", dieAnimationIndx);
        iShowBMP2(pacX, pacY, str, 0);
    }
    if(pacMoveDown){
        char str[] = "pacman/Die/dieDown/die01.bmp";
        int frameNumber = dieAnimationIndx;
        snprintf(str, sizeof(str), "pacman/Die/dieDown/die%02d.bmp", dieAnimationIndx);
        iShowBMP2(pacX, pacY, str, 0);
    }
}

void playDieAnimation(){
    dieAnimationIndx++;
    if(dieAnimationIndx >= 73){
        iPauseTimer(timerId7);
        dying = false;
        if(life > 0){
            defineGhost();
            for(int i = 0; i < 3; i++) ghost[i].indx = 0;
            findPath(0);
            findPath(1);
            findPath(2);
            pacMoveUp = false;
            pacMoveDown = false;
            pacMoveLeft = false;
            pacMoveRight = false;
            pacBase = true;
            bfsMove = false;
            fGhostSound = false;
            fGhost = false;
            iResumeTimer(timerId2);
            iResumeTimer(timerId3);
            iResumeTimer(timerId5);
            iResumeTimer(timerId6);
            pacX = 500+21;
            pacY = 500+21;
            dieAnimationIndx = 1;
            movingGhost = 1;
            if(gameSound) PlaySound("Sounds/pacman_chomp.wav", NULL, SND_LOOP | SND_ASYNC);
        }
        else{
            defineGhost();
            for(int i = 0; i < 3; i++) ghost[i].indx = 0;
            findPath(0);
            findPath(1);
            findPath(2);
            pacMoveUp = false;
            pacMoveDown = false;
            pacMoveLeft = false;
            pacMoveRight = false;
            pacBase = true;
            bfsMove = false;
            fGhostSound = false;
            fGhost = false;
            iPauseTimer(timerId2);
            iPauseTimer(timerId3);
            iPauseTimer(timerId5);
            iPauseTimer(timerId6);
            pacX = 500+21;
            pacY = 500+21;
            dieAnimationIndx = 1;
            movingGhost = 1;
            gameState = 5;
            gamePlayed= true;
            manageScore();
        }

    }
}

void namePage(){
    iShowBMP(0, 0, "Menu/namePage.bmp");
    iText(440, 270, name, GLUT_BITMAP_HELVETICA_18);
}
void updateScore(){
    int x = 720, y = 650;
    char scoreLine[100];

    for(int i = 1; i <= life; i++){
        iShowBMP2(x, y, "Score/life.bmp", 0);
        x = x+40;
    }

    x = 720;
    y = 550;
    iText(720, 600, "Player Name: ", GLUT_BITMAP_HELVETICA_18);
    iText(835, 600, name, GLUT_BITMAP_HELVETICA_18);
    sprintf(scoreLine, "Total Score: %d", liveScore);

    iText(720, 550, scoreLine, GLUT_BITMAP_TIMES_ROMAN_24);
}
void manageScore(){
    FILE *fp_in;
    if(gameDifficulty == 1){
        fp_in = fopen("Score/easy.txt", "r");
    }
    if(gameDifficulty == 2){
        fp_in = fopen("Score/medium.txt", "r");
    }
    if(gameDifficulty == 3){
        fp_in = fopen("Score/hard.txt", "r");
    }

    char names[11][50];
    int points[11];
    int i;

    for(i = 0; i < 10; i++){
        char line[100];
        fgets(line,100, fp_in);
        sscanf(line, "%s %d", &names[i], &points[i]);
    }

    points[i] = liveScore;
    strcpy(names[i], name);

    fclose(fp_in);

    if(gameDifficulty == 1){
        fp_in = fopen("Score/easy.txt", "w");
    }
    if(gameDifficulty == 2){
        fp_in = fopen("Score/medium.txt", "w");
    }
    if(gameDifficulty == 3){
        fp_in = fopen("Score/hard.txt", "w");
    }

    for(int i = 0; i < 11; i++){
        for(int j = i+1; j < 11; j++){
            if(points[j] > points[i]){
                int tempPoints = points[i];
                points[i] = points[j];
                points[j] = tempPoints;

                char tempStr[50];
                strcpy(tempStr, names[i]);
                strcpy(names[i], names[j]);
                strcpy(names[j], tempStr);
            }
        }
    }
    for(int i = 0; i < 10; i++){
        fprintf(fp_in, "%s %d\n", names[i], points[i]);
    }
    fclose(fp_in);


}

void gameOverPage(){
    iShowBMP(0,0, "Score/gameover.bmp");
    char scoreStr[10];
    sprintf(scoreStr, "%d", liveScore);
    iText(550, 335, scoreStr, GLUT_BITMAP_TIMES_ROMAN_24);
    iShowBMP2(780, 60, "Menu/leaderboard.bmp", 0);
}

void showInstruction(){
    iShowBMP(0, 0, "Menu/rules.bmp");
}

void soundPage(){
    iShowBMP(0, 0, "pacman/menubackgroundC.bmp");
    if(gameSound){
        iSetColor(255, 255, 204);
        iFilledCircle(345, 373, 7, 100);
        iCircle(545, 373, 7, 100);
    }
    else{
        iSetColor(255, 255, 204);
        iCircle(345, 373, 7, 100);
        iFilledCircle(545, 373, 7, 100);
    }
    iShowBMP2(350, 350, "Menu/on.bmp", 0);
    iShowBMP2(550, 350, "Menu/off.bmp", 0);
}

int main() {
	saveWallCordinate();
	defineGhost();
	findPath(0);
	findPath(1);
	findPath(2);
	saveDots();
	if(introSound) PlaySound("Sounds/intro.wav", NULL, SND_FILENAME | SND_ASYNC);
	timerId1 = iSetTimer(16, changeIntroIndx);



	iInitialize(screenWidth, screenHeight, "Pacman");
	return 0;
}
