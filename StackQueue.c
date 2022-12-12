#include "main.h"

void gotoxy(int x, int y)
{
    COORD pos = { x, y }; // 커서의 위치를 저장하는 구조체
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); // 커서 위치 이동시키기
}

Node* getNode() // 노드 생성
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->tail = NULL;
    return newNode;
}

void insertNode(Node **head, int x, int y) // 큐 삽입
{
    if (*head == NULL)
    {
        *head = getNode();
        (*head)->x = x;
        (*head)->y = y;
        (*head)->t = 0;
    }
    else
        insertNode(&(*head)->tail, x, y);
}

void insertObs(Node **Obs, int x, int y) // 스택 삽입
{
    Node *tmp = *Obs;
    *Obs = getNode();
    (*Obs)->x = x;
    (*Obs)->y = y;
    if (*Obs != NULL)
        (*Obs)->tail = tmp;
} 