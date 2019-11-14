#include "pch.h"
#include "Snakeprev.h"
COLORREF setcolor()
{
	IMAGE box;
	loadimage(&box, "C://Users//Administrator//source//repos//snake-3//resource//box.jpg");//loadimage只加载图片，不做任何操作
	/*
	void loadimage(
	IMAGE* pDstImg,        // 保存图像的 IMAGE 对象指针
		LPCTSTR pImgFile,        // 图片文件名
		int nWidth = 0,        // 图片的拉伸宽度
		int nHeight = 0,        // 图片的拉伸高度
		bool bResize = false    // 是否调整 IMAGE 的大小以适应图片
		);
		*/

	SetWorkingImage(&box);          //设定当前的绘图设备
	COLORREF scene = getpixel(0, 0); //COLORREF类型用来描绘一个RGB颜色
	SetWorkingImage(NULL);
	return scene;
}

IMAGE setbox()
{
	IMAGE box;
	loadimage(&box, "C://Users//Administrator//source//repos//snake-3//resource//box.jpg", 2 * INDEX, 2 * INDEX);
	return box;
}

IMAGE setmap(COLORREF scene, IMAGE box)
{

	IMAGE MAP;
	IMAGE bridge;
	loadimage(NULL, "C://Users//Administrator//source//repos//snake-3//resource//back1.jpg");

	setlinecolor(scene); //设置折线或多边形的线条颜色或透明度。
	setlinestyle(PS_SOLID | PS_JOIN_ROUND, 10);
	setfillcolor(getpixel(520, 280));
	rectangle(5, 5, 595, 595);

	
	    //函数putimage()将一个先前保存在内存中的图像输出到屏幕上。
		//void putimage(int left,int top,void *buf,int ops);
	putimage(110, 230, &box); //2
	
	for (int i = 550; i >= 410; i -= 2 * INDEX)//6
	{
		putimage(i, 390, &box);
	}
	putimage(270, 150, &bridge);
	putimage(270, 390, &bridge);
	//getimage保存左上角与右下角所定义的 屏幕上像素图形到指定的内存区域。
	getimage(&MAP, 0, 0, 600, 600);
	cleardevice();
	return MAP;
}

bool Iftouch(int x, int y)
{
	
	//judge 2 box
	if ((x >= 110 && x <= 150) && (y >= 230 && y <= 270))
	{
		return false;
	}
	
	//judge 6 box
	else if ((x >= 430 && x <= 599) && (y >= 390 && y <= 430))
	{
		return false;
	}
	else return true;
}