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

void gotoxy(int x, int y); // 좌표 위치 이동
void insertNode(Node **head, int x, int y); // 노드 삽입
void insertObs(Node **Obs, int x, int y); // 삽입
void createTail(XY *tails, Node *obs); // 보너스 꼬리 아이템 생성
void createObs(Node *Head, Node **obs, XY *tails); // 장애물 생성
void init_Game(Node ** HEAD, XY *tails); // 게임 초기화
void end_Game(); // 게임 끝
void checkWall(Node *HEAD); // 벽에 닿았는지 확인
void checkObject(Node **HEAD, XY *tails, Node **obs); // 오브젝트에 닿았는지 확인
void moveSnake(Node *HEAD, int s); // 뱀 움직이기
void start_Game(Node **HEAD, XY *tails); // 게임 시작

void start_Game(Node **HEAD, XY *tails) // 게임 시작
{
    Node *obs = NULL; // 초기값
    char ip = '\0'; // 초기값
    int s_see = SEE_LEFT, count = 0; //
    int gameSpd = 250, score = 0; //
    short ctime = (short)time(0); // 시간 초기값
    short mtime;
    while (1)
    {
        if (_kbhit()) // 키 입력여부, 입력이 있으면 1, 없으면 0
        {
            ip = _getch(); // getch() : 사용자에게 키보드로 하나의 키를 입력받는 함수
            switch (ip)
            {
            case LEFT: // 왼쪽키를 누른다면
                s_see = SEE_LEFT; // 왼쪽을 쳐다봄
                break;
            case RIGHT: // 오른쪽키를 누른다면
                s_see = SEE_RIGHT; // 오른쪽을 쳐다봄
                break;
            case UP: // 위 키를 누른다면
                s_see = SEE_UP; // 위를 봄
                break;
            case DOWN: // 아래 키를 누른다면
                s_see = SEE_DOWN; // 아래를 봄
                break;
            case ESC:
                exit(1);
                break;
            }
            ip = '\0';
        }
        else { // 키 입력이 없을 때
            moveSnake(*HEAD, s_see);
            checkObject(HEAD, tails, &obs);
            gotoxy(tails->x * 2, tails->y); // x 좌표로 *2 움직임
            printf("⊙");
            if (obs != NULL)
            {
                gotoxy(obs->x * 2, obs->y);
                printf("▩");
            }
            Sleep(gameSpd);
        }
        mtime = (short)time(0);
        if (mtime - ctime >= 1) // 게임 속도 조절
        {
            ctime = mtime;
            count++;
            if (count == 10)
            {
                count = 0;
                if (gameSpd - (*HEAD)->t * 2 > 40)
                    gameSpd -= (*HEAD)->t * 2;
            }
            score += ((*HEAD)->t * (*HEAD)->t) * 10 + (*HEAD)->t; // 점수 계산
            gotoxy(0, MAP_Y + 1); // 점수 출력
            printf("YOUR SCORE [ %d ] / TAILS [ %d ] / GAME SPEED [ %d ]", score, (*HEAD)->t, gameSpd);
        }
    }
}

void end_Game()
{
    gotoxy(0, MAP_Y + 5);
    printf("게임 끝.....");
    _getch();
    exit(1);
}

int main()
{
    Node *HEAD = NULL;
    XY tails = { 0,0 };
    srand((unsigned)time(NULL));
    // 내림차순 버블정렬
    int i,j,n=3,temp;
    int rank[3] = {100913, 91296, 110786};
    for(i=n-1; i>0; i--)
    {
        for(j=0; j<i; j++)
        {
            if(rank[j]<rank[j+1])
            {
                temp=rank[j];
                rank[j]=rank[j+1];
                rank[j+1]=temp;
            }
        }
    }
    printf("\\(@^0^@)// WELCOME GUMTREE \\(@^0^@)// !!\n\n");
    printf("- 게임키 : 방향키 좌( ← ), 우( → ), 위( ↑ ), 아래( ↓ )\n");
    printf("- 게임종료 : ESC\n\n");
    printf("게임 설명 : \n");
    printf("벽에 닿거나 자기 꼬리에 닿으면 끝 !\n닿지 않게 잘 피하면서 자기 몸집을 불려보세요!!\n\n");
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃                                        ┃\n");
    printf("┃              지렁이 게임               ┃\n");
    printf("┃                                        ┃\n");
    printf("┃                ranking                 ┃\n");
    printf("┃                                        ┃\n");
    printf("┃              1. %d 점              ┃\n", rank[0]);
    printf("┃              2. %d 점              ┃\n", rank[1]);
    printf("┃              3. %d 점               ┃\n", rank[2]);
    printf("┃                                        ┃\n");
    printf("┃                                        ┃\n");
    printf("┃                                        ┃\n");
    printf("┃                                        ┃\n");
    printf("┃                                        ┃\n");
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n\n");

    printf("- 게임을 시작하시려면 아무키나 눌러주세요 <");
    _getch();
    system("cls");
    init_Game(&HEAD, &tails);
    start_Game(&HEAD, &tails);
    return 0;
}