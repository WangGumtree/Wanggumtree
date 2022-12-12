#include "main.h"

void init_Game(Node ** HEAD, XY *tails) // 게임 초기화
{
    int i = 0, k = 0;
    for (i = 0; i <= MAP_Y; i++) // 맵 테두리 만들기, MAY_Y는 23으로 지정되어 있음.
    {
        for (k = 0; k <= MAP_X; k++) // MAY_Y는 38으로 지정되어 있음.
        {
            if (i == 0 || i == MAP_Y || k == 0) // i가 0이거나 MAP_Y이거나 k가 0이면 ▩를 출력함.
            {
                printf("ㅁ");
            }
            if (k == MAP_X) // k가 MAP_X면 MAP_X*2, i 좌표로 이동해서 ▩를 출력해줌.
            {
                gotoxy((MAP_X) * 2, i);
                printf("ㅁ");
            }
        }
        printf("\n");
    }
    insertNode(&(*HEAD), MAP_X - 2, MAP_Y / 2); // 큐에다가 삽입해줌.
    createTail(tails, NULL);
}

void checkWall(Node *HEAD)
{
    if (HEAD->x < 1 || HEAD->x >= MAP_X || HEAD->y < 1 || HEAD->y >= MAP_Y) // 만약 머리의 x가 1보다 작거나 맵보다 크고 / 머리의 y사 1보다 작거나 맵보다 크면 => 맵을 나가게 됨
        end_Game(); // 게임 끝
}