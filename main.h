#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define MAP_X 38
#define MAP_Y 23
#define ESC 27
#define SEE_UP 1
#define SEE_DOWN 2
#define SEE_LEFT 3
#define SEE_RIGHT 4

typedef struct xy {
    int x;
    int y;
}XY;

typedef struct NODE {
    int t;
    int x;
    int y;
    struct NODE *tail;
}Node;

void gotoxy(int x, int y);
void insertNode(Node **head, int x, int y); // 노드 삽입
void insertObs(Node **Obs, int x, int y); // 삽입
void createTail(XY *tails, Node *obs); // 보너스 꼬리 아이템 생성
void createObs(Node *Head, Node **obs, XY *tails); // 장애물 생성
void init_Game(Node ** HEAD, XY *tails); // 게임 초기화
void end_Game(); // 게임 끝
void checkWall(Node *HEAD); // 벽에 닿았는지 확인
void checkObject(Node **HEAD, XY *tails, Node **obs); //
void moveSnake(Node *HEAD, int s); // 뱀 움직이기
void start_Game(Node **HEAD, XY *tails); // 게임 시작

