// snake-3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<graphics.h>
#include"Snakeprev.h"
#include<conio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"Winmm.lib")



#define up 'w'
#define down 's'
#define left 'a'
#define right 'd'
#define stop 'p'
#define speed 150
#define INDEX  20

using namespace std;

/****************************************************/
IMAGE box;
IMAGE MAP;
IMAGE MAPLEFT;
IMAGE foodstyle;
IMAGE watermelon;  // 5 score

IMAGE welcome;
IMAGE bkcolor;
COLORREF scene;////COLORREF类型用来描绘一个RGB颜色
MOUSEMSG mouse;
char click = 0;
char name[20];
char NAME[30] = "你好 ， ";
int number[6] = { 8,8,8,9,8,10 };
snake * const head = snakelist(3, number);
int score = 0;
char SCORE[30];
/****************************************************/
/*****************************/
typedef struct
{
	char PWD[15] = "";
	char ID[15] = "";
	int score = 0;
}USER;
USER user;
class Food
{
private:
	int x, y;
	IMAGE yuan;
	int style;
public:
	Food();
	void drawfood(IMAGE);
	int getx() { return x; }
	int gety() { return y; }
	void setxy();
	//void setstyle(int);
	//int getstyle() { return style; }
};
Food::Food()
{
	setxy();
}
void Food::setxy()
{
	//unsigned int time=;
	//srand()用来设置rand()产生随机数时的随机数种子
	srand((unsigned)time(NULL));
	int a, b;
	snake *judge = head;
	while (1)
	{
		int panduan = 1, flag = 0;
		a = (rand() % 29 + 1)*INDEX;
		b = (rand() % 29 + 1)*INDEX;
		if (Iftouch(a, b) == true)
		{
			flag = 1;
			break;
		}
		while (true)
		{
			if (x == judge->x&&y == judge->y)
			{
				panduan = 0;
				break;
			}
			if (judge->next->next == NULL) break;
			judge = judge->next;
		}
		if (panduan == 1 && flag == 1) break;
	}
	x = a;
	y = b;
}

/*void Food::setstyle(int a)
{
	style = a;
}*/

void Food::drawfood(IMAGE yuan)
{
	SetWorkingImage(&yuan);
	SetWorkingImage(NULL);
	putimage(x - 15, y - 15, &yuan, SRCPAINT);
}
Food food;
/*****************************/



void welcomegraph();//欢迎界面
void Finish();//结束界面
int clickcontrol();//鼠标控制
void Movingsnake(char);//蛇身移动控制
void Changesnakebody(int, int);//蛇身改变控制
void Eating();//吃到食物的操作
int Deadjudge();//死亡判断


void welcomegraph()
{
	//初始化图形系统
	initgraph(850, 600); 
	scene = setcolor();
	box = setbox();
	MAP = setmap(scene, box);
	
	float H = 190, S = 1, L = 0.7;//H 色相：S 饱和度：L 亮度
	for (int i = 0; i < 600; i++)
	{
		L += 0.0005;
		setlinecolor(HSLtoRGB(H, S, L));
		line(0, i, 849, i);
	}
	
	loadimage(&welcome, "C://Users//Administrator//source//repos//snake-3//resource//snake.jpg", 320, 600);
	loadimage(&watermelon, "C://Users//Administrator//source//repos//snake-3//resource//watermelon.jpg", 30, 30);
	foodstyle = watermelon;
	//food.setstyle(0);
	putimage(265, 0, &welcome);
	//获取全景
	IMAGE a;
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(25, 0, _T("华文行楷"));
	getimage(&a, 0, 0, 850, 600);
	//图标
	IMAGE ico;
	loadimage(&ico, "C://Users//Administrator//source//repos//snake-3//resource//ico1.jpg", 100, 100);
	SetWorkingImage(&ico);
	putimage(0, 0, &ico, SRCINVERT);
	SetWorkingImage(NULL);

	while (TRUE)
	{
		//MouseHit这个函数用于检测当前是否有鼠标消息。
		if (MouseHit() == true)
		{
			//GetMouseMsg这个函数用于获取一个鼠标消息。如果当前鼠标消息队列中没有，就一直等待。
			mouse = GetMouseMsg();
		}
		
		//LOGIN
		
		if (mouse.x >= 375 && mouse.x <= 475 && mouse.y >= 328 && mouse.y <= 363 && mouse.mkLButton)
		{
			mciSendString("play click from 0", NULL, 0, NULL);
			putimage(0, 0, &a);
			putimage(680, 130, &ico, SRCPAINT);
			setlinecolor(RGB(0, 255, 0));
			settextcolor(RGB(255, 128, 0));
			settextstyle(30, 0, _T("黑体"));
			outtextxy(590, 255, "ID");
			outtextxy(585, 315, "PWD:");
			setlinestyle(PS_SOLID, 2);
			fillrectangle(635, 255, 840, 285);
			fillrectangle(635, 315, 840, 345);
			
			settextcolor(BLACK);
			char com = 0;
			int x = 620, y = 255, i = 0;
			int times = 0;
			while (true)
			{
				if (_kbhit())
				{
					com = _getch();
					if (com == 'q') break;
					if (com == '\b')
					{
						solidrectangle(x, y + 1, x + 15, y + 29);
						x -= 15;
						i--;
					}
					else
					{
						if (com == '\r')
						{
							if (times == 0)
							{
								user.ID[i] = '\0';
								y = 315;
								x = 620;
								i = 0;
							}
							if (times == 1)
							{
								outtextxy(630, 500, user.ID);
								outtextxy(630, 550, user.PWD);
								settextcolor(BLUE);
								outtextxy(610, 350, "登陆成功O(∩_∩)O");
								_getch();
								for (int i = 0; i <= 300; i++)
								{
									setlinecolor(GREEN);
									line(0, i, 849, i);
									line(0, (600 - i), 849, (600 - i));
									Sleep(4);
								}
								InputBox(name, 10, "你的名字是");
								//char *strcat(char *dest, const char *src);
								//【参数】dest 为目的字符串指针，src 为源字符串指针
								strcat(NAME, name);
								loadimage(NULL, "C://Users//Administrator//source//repos//snake-3//resource//bkcolor.jpg");
								getimage(&MAPLEFT, 600, 0, 250, 600);
								settextcolor(RGB(0, 0, 0));
								setbkmode(TRANSPARENT);
								settextstyle(25, 0, _T("华文行楷"));
								outtextxy(650, 100, NAME);
								outtextxy(650, 150, "你的得分是：");
								settextstyle(130, 0, _T("黑体"));
								//功能:将整数value转换成字符串存入string, 
								//radix为转换时所用基数(保存到字符串中的数据的进制基数 2 8 10 16)
								itoa(score, SCORE, 10);
								outtextxy(690, 270, SCORE);
								return;
							}
							times = 1;
						}
						else
						{
							x += 15;
							if (times == 0 && i < 20 && i >= 0) user.ID[i++] = com;
							if (times == 1 && i < 20 && i >= 0) user.PWD[i++] = com;
							if (times == 0) outtextxy(x, y, com);
							if (times == 1) outtextxy(x, y, '*');
						}
					}

				}
			}

			//return;
		}
	

		//HELP
		else if (mouse.x >= 375 && mouse.x <= 475 && mouse.y >= 385 && mouse.y <= 420 && mouse.mkLButton)
		{
			settextcolor(BLACK);
			mciSendString("play click from 0", NULL, 0, NULL);
			putimage(0, 0, &a);
			settextstyle(25, 0, _T("华文行楷"));
			outtextxy(20, 40, "老师好，欢迎来到贪吃蛇");
			Sleep(20);
			outtextxy(20, 80, "o(*￣▽￣*)o");
			Sleep(20);
			outtextxy(20, 120, "请用 W A S D");
			Sleep(20);
			outtextxy(20, 160, "控制方向 P键暂停");
			Sleep(20);
			outtextxy(20, 200, "游戏中碰到箱子");
			Sleep(20);
			outtextxy(20, 240, "吃到自己或反向");
			Sleep(20);
			outtextxy(20, 280, "移动均视作死亡");
			Sleep(20);
			outtextxy(10, 340, "还要注意");
			Sleep(20);
			outtextxy(20, 360, "登陆时请勿使用");
			Sleep(20);
			outtextxy(20, 400, "非法字符（汉字等）");
			Sleep(20);
			outtextxy(20, 440, "密码不支持中文字符数");
			Sleep(20);
			outtextxy(20, 480, "最要注意：开始方向一定是wwwwwwww");
			Sleep(20);
			
		}
		
		
	}
}

int Deadjudge()
{
	if (head->x == 0 * INDEX || head->x == 30 * INDEX || head->y == 0 * INDEX || head->y == 30 * INDEX)
	{
		Finish();
		return 0;
	}
	if (Iftouch(head->x, head->y) == false)
	{
		Finish();
		return 0;
	}
	int a = head->x, b = head->y;
	snake *p = head->next;
	while (p->next != NULL)
	{
		if (p->x == a && p->y == b)
		{
			Finish();
			return 0;
		}
		p = p->next;
	}
	return 1;
}

void Finish()
{
	mciSendString("close bgm", NULL, 0, NULL);
	mciSendString("play dead", NULL, 0, NULL);;
	loadimage(NULL, "C://Users//Administrator//source//repos//snake-3//resource//over.jpg", 850, 600);
	setfillcolor(RGB(128, 255, 128));
	solidrectangle(0, 0, 849, 180);
	solidrectangle(0, 400, 849, 600);
	settextcolor(BLACK);
	Sleep(1000);
	_getch();
	_getch();
}

int clickcontrol()
{
	while (TRUE)
	{
		if (Deadjudge() == 0) return 0;
		if (_kbhit())
		{
			click = _getch();
		}
		Movingsnake(click);
		Eating();
	}
	return 1;
}

void Movingsnake(char c)
{
	BeginBatchDraw();
	int x = head->x, y = head->y;
	switch (c)
	{
	case up:
		head->y -= INDEX;
		Changesnakebody(x, y);
		break;
	case down:
		head->y += INDEX;
		Changesnakebody(x, y);
		break;
	case left:
		head->x -= INDEX;
		Changesnakebody(x, y);
		break;
	case right:
		head->x += INDEX;
		Changesnakebody(x, y);
		break;
	}
	putimage(0, 0, &MAP);
	settextcolor(RGB(0, 0, 0));
	food.drawfood(foodstyle);
	drawsnake(head, c);
	FlushBatchDraw();
	Sleep(speed);
	EndBatchDraw();
}

void Changesnakebody(int x, int y)
{
	snake *p = head->next;
	int mid1, mid2, _mid1, _mid2;
	mid1 = p->x;
	mid2 = p->y;
	while (1)
	{
		if (p->next->next == NULL) break;
		_mid1 = p->next->x;
		_mid2 = p->next->y;
		p->next->x = mid1;
		p->next->y = mid2;
		mid1 = _mid1;
		mid2 = _mid2;
		p = p->next;
	}
	p = head->next;
	p->x = x;
	p->y = y;
}

void Eating()
{
	if (head->x == food.getx() && head->y == food.gety())
	{
		score += 5;
		////from 0为播放一次
		mciSendString("play eat from 0", NULL, 0, NULL);
		snake *p = head;
		snake *q = new snake;
		while (p->next->next != NULL)
		{
			p = p->next;
		}
		snake *tail = p->next;
		p->next = q;
		q->next = tail;
		putimage(600, 0, &MAPLEFT);
		setbkmode(TRANSPARENT);
		settextstyle(25, 0, _T("华文行楷"));
		outtextxy(650, 100, NAME);
		outtextxy(650, 150, "你的得分是：");
		settextstyle(130, 0, _T("黑体"));
		
		itoa(score, SCORE, 10);
		outtextxy(670, 270, SCORE);
		food.setxy();
		food.drawfood(foodstyle);
	}
}


int main()
{
	//Alias movie    定义了该操作的别名为movie，后续操作只要指明别名即可
	//type MPEGVideo 是指打开MPEG,AVI等类型，如果不加这一句，就是打开WAV,MP3等
	//mName          全路径文件名
	//mciSendString "open mName type MPEGVideo Alias movie parent %u Style %u notify", 0 & , 0, 0
	mciSendString("open C://Users//Administrator//source//repos//snake-3//resource//bgm.mp3 alias bgm", NULL, 0, NULL);
	mciSendString("open C://Users//Administrator//source//repos//snake-3//resource//dead.wav type waveaudio alias dead", NULL, 0, NULL);
	mciSendString("open C://Users//Administrator//source//repos//snake-3//resource//eat.mp3 alias eat", NULL, 0, NULL);
	mciSendString("open C://Users//Administrator//source//repos//snake-3//resource//click.wav type waveaudio alias click", NULL, 0, NULL);
	mciSendString("play bgm repeat", NULL, 0, NULL);
	welcomegraph();
	if (clickcontrol() == 0)
	{
		closegraph();
		return 0;
	}
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
