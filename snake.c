#include "main.h"

void checkObject(Node **HEAD, XY *tails, Node **obs) // 오브젝트(벽, 꼬리에 닿였는지 확인)
{
    Node *tmp = (*HEAD)->tail;

    checkWall(*HEAD); // 벽 닿았는지 확인


    while (tmp != NULL) // 자기 꼬리
    {
        if (tmp->x == (*HEAD)->x && tmp->y == (*HEAD)->y) // 만약 자기 꼬리에 머리가 닿이면
            end_Game(); // 게임 끝
        tmp = tmp->tail;
    }

    if ((tails->x == (*HEAD)->x) && (tails->y == (*HEAD)->y)) // 꼬리
    {
        insertNode(&(*HEAD), (*HEAD)->x, (*HEAD)->y);
        (*HEAD)->t++;
        createTail(tails, *obs);
        createObs(*HEAD, &(*obs), tails);
        createObs(*HEAD, &(*obs), tails);
    }

    while (*obs != NULL) // 장애물
    {
        if ((*obs)->x == (*HEAD)->x && (*obs)->y == (*HEAD)->y)
            end_Game();
        obs = &(*obs)->tail;
    }
}

void moveSnake(Node *HEAD, int s) // 뱀의 이동
{
    Node *tmp = HEAD;
    XY tmp1 = { HEAD->x,HEAD->y };
    XY tmp2 = tmp1;
    if (s == SEE_LEFT) // 왼쪽을 바라보고 있으면
        HEAD->x -= 1; // x좌표 -1(왼쪽으로 가려면 x -1 해야함)
    else if (s == SEE_RIGHT) // 오른쪽
        HEAD->x += 1; // x좌표 +1
    else if (s == SEE_UP)
        HEAD->y -= 1;
    else
        HEAD->y += 1;
    HEAD = HEAD->tail;
    while (HEAD != NULL) // 꼬리들 좌표 전달
    {
        tmp2.x = HEAD->x;
        tmp2.y = HEAD->y;
        HEAD->x = tmp1.x;
        HEAD->y = tmp1.y;
        tmp1.x = tmp2.x;
        tmp1.y = tmp2.y;
        HEAD = HEAD->tail;
    }
    gotoxy(tmp2.x * 2, tmp2.y); // 맨 뒤 꼬리 지우기
    printf("  ");
    gotoxy(tmp->x * 2, tmp->y); // 머리 출력
    printf("◎");
    if (tmp->tail != NULL) // 전 머리부분 몸통 출력
    {
        gotoxy(tmp->tail->x * 2, tmp->tail->y);
        printf("⊙");
    }
}

void createTail(XY *tails, Node *obs) // 보너스 꼬리 아이템 생성
{
    int flag = 1;
    while (flag)
    {
        flag = 0;
        tails->x = rand() % (MAP_X - 1) + 1;
        tails->y = rand() % (MAP_Y - 1) + 1;
        while (obs != NULL) // 장애물하고 위치 중복 체크
        {
            if (obs->x == tails->x && obs->y == tails->y)
            {
                flag = 1;
                break;
            }
            obs = obs->tail;
        }
    }
    gotoxy(tails->x * 2, tails->y);
    printf("⊙");
}

void createObs(Node *Head, Node **obs, XY *tails) // 장애물 생성
{
    Node *tmp = *obs;
    int flag = 1;
    XY oxy = { 0,0 };
    while (flag) {
        flag = 0;
        oxy.x = rand() % (MAP_X - 1) + 1;
        oxy.y = rand() % (MAP_Y - 1) + 1;
        if ((oxy.x == tails->x && oxy.y == tails->y) || // 뱀의 머리, 보너스 꼬리 아이템하고 위치 중복 체크
            (oxy.x == Head->x && oxy.x == Head->y))
        {
            flag = 1;
            continue;
        }
        while (tmp != NULL) // 이전에 생성된 장애물들과 위치 중복 체크
        {
            if (tmp->x == oxy.x && tmp->y == oxy.y)
            {
                flag = 1;
                break;
            }
            tmp = tmp->tail;
        }
    }
    insertObs(&(*obs), oxy.x, oxy.y); // 장애물 추가
    gotoxy(oxy.x * 2, oxy.y);
    printf("▩");
}