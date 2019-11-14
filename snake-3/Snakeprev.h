#pragma once
//ÉßÉí²Ù×÷

#ifndef Snakeprev_H
#define Snakeprev_H

#define MAP_H
#define MAP_H
#include<graphics.h>
#define INDEX  20

COLORREF setcolor();
IMAGE setbox();
IMAGE setmap(COLORREF, IMAGE);
bool Iftouch(int, int);


typedef struct Snake
{
	int x, y;
	struct Snake* next;
}snake;

snake * snakelist(int, int*);//creat a list belong to number
void addsnake(snake *);//creat a point in the tail
void drawsnake(snake *, char);
void clearsnake(snake *);


#endif // !Addition_H

