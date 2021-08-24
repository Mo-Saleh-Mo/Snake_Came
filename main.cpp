#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

// vars
bool gameOver ;
const int width = 20 ;
const int height = 20 ;
int x, y, fruitY, fruitX, score, i = 0, j = 0, nTail;
int tailX[100], tailY[100];
enum eDirection {STOP =0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

// function setup
void setup(void) {
  gameOver = false ;
  dir = STOP;
  x = width / 2 ;
  y = height / 2;
  fruitX = rand() % width ;
  fruitY = rand() % height;
}

// function draw
void draw(void) {
  system("cls");
  for(i = 0; i <= width; i++)
    cout << "#";
  cout << endl ;

  for(i = 0; i < height ; i++) {
    for(j = 0; j < width; j++) {
      if (j==0)
        cout << "#";

      if(i==y && j==x)
        cout << "O";
      else if (i==fruitY && j==fruitX)
        cout << "F";
      else {

        bool print = false;
        for(int k = 0; k < nTail; k++) {
          if(tailX[k] == j && tailY[k] == i){
            cout << "o";
            print = true;
          }
        }
        if (!print)
          cout << " ";
      }

      if (j == width - 1)
        cout << "#";
    }
    cout << endl;
  }

  for (i = 0; i <= width; i++)
    cout << "#";
  cout << endl;
  cout <<"score: " << score << endl ;
}

// function input
void input(void){
  if(_kbhit()) {
    switch (_getch()){
    case 'l': dir = LEFT ; break;
    case 'r': dir = RIGHT ; break;
    case 'u': dir = UP ; break;
    case 'd': dir = DOWN ; break;
    case 'x': gameOver = true ; break;
    }
  }
}

// function setup
void logic(void){

  int prevX = tailX[0], prevY = tailY[0];
  int prevX2, prevY2;
  tailX[0] =x;
  tailY[0] =y;
  for(i=1; i< nTail; i++){
    prevX2 = tailX[i];
    prevY2 = tailY[i];
    tailY[i] = prevY;
    tailX[i] = prevX;
    prevX = prevX2;
    prevY = prevY2;
  }

  switch(dir){
    case LEFT: x--; break;
    case RIGHT: x++; break;
    case UP: y--; break;
    case DOWN: y++; break;
  }
  // if(x > width || x < 0 || y > height || y < 0)
  //   gameOver = true ;

  if(x >= width) x = 0; else if (x < 0) x = width -1 ;
  if(y >= height) y = 0; else if (y < 0) y = width -1 ;

  for(i=0;i<nTail; i++)
    if(tailX[i] == x && tailY[i] == y)
      gameOver = true ;

  if(x == fruitX && y == fruitY) {
    score += 10 ;
    fruitX = rand() % width ;
    fruitY = rand() % height ;
    nTail++;
  }
}

int main(void) {
  setup();
  while (!gameOver) {
    draw();
    input();
    logic();
    Sleep(20);
  }

  return 0;
}
