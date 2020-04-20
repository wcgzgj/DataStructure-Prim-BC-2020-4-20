#include "Draw.h"
#include "Graph.h"
#include <graphics.h>
#include <vector>
#include <math.h>
#include <string>

Draw::Draw(void)
{
}


Draw::~Draw(void)
{
}



void Draw::iniPanel()
{
	initgraph(1000,1000);
	setorigin(500,500);
}

void Draw::closePanel()
{
	closegraph();
}

void Draw::clearPanel()
{
	cleardevice();
	return;
}

void Draw::drawCircle(Graph gh)
{
	int num=gh.getSize();//顶点个数

	double x,y;
	std::vector<CircleCenter> cc; 
	int flag=0;
	double cut=2.0/num;

	while(flag<=num)
	{
		x=400*cos(cut*flag*PI);
		y=400*sin(cut*flag*PI);
		cc.push_back(CircleCenter(x,y));
		flag++;
	}


	for(int i=0;i<num;i++)
	{
		char s[100];
		sprintf(s,"%d",i);

		int n = MultiByteToWideChar(0, 0, s, -1, NULL, 0);
		wchar_t *wide = new wchar_t[n];
		MultiByteToWideChar(0, 0, s, -1, wide, n);
		circle(cc[i].x,cc[i].y,20);
		//char p=i+'0';
		outtextxy(cc[i].x,cc[i].y,wide);
	}
}



void Draw::drawLine(double x1,double y1, double x2, double y2)
{
	/*double detX=x2-x1;
	double detY=y2-y1;
	double len=sqrt(detX*detX+detY*detY);//两点之间原的距离
	double cos=detX/len;
	double sin=detY/len;
	double detx=20*cos;
	double dety=20*sin;
	x1+=detx;
	y1-=dety;
	x2-=detx;
	y2+=dety;*///<=========本来想让线不穿过球的，后来发现要分类讨论，就懒得搞了

	line(x1,y1,x2,y2);
	return;
}

void Draw::drawInstant(primResult *pr,int n, int len)
{
	int num=n;

	double x,y;
	std::vector<CircleCenter> cc; 
	int flag=0;
	double cut=2.0/num;

	while(flag<=num)
	{
		x=400*cos(cut*flag*PI);
		y=400*sin(cut*flag*PI);
		cc.push_back(CircleCenter(x,y));
		flag++;
	}

	COLORREF cf=getlinecolor();
	setlinecolor(YELLOW);


	for(int i=0;i<len;i++)
	{	
		drawLine(cc[pr[i].start].x,cc[pr[i].start].y,cc[pr[i].end].x,cc[pr[i].end].y);
		drawWeight(cc[pr[i].start].x,cc[pr[i].start].y,cc[pr[i].end].x,cc[pr[i].end].y,pr[i].weight);
	}
	setlinecolor(cf);//在输出完绿色的线后，别忘了将线的颜色变回去

	return;
}

void Draw::drawSlow(primResult *pr,int n)
{
	int num=n;

	double x,y;
	std::vector<CircleCenter> cc; 
	int flag=0;
	double cut=2.0/num;

	while(flag<=num)
	{
		x=400*cos(cut*flag*PI);
		y=400*sin(cut*flag*PI);
		cc.push_back(CircleCenter(x,y));
		flag++;
	}

	COLORREF cf=getlinecolor();
	setlinecolor(GREEN);
	for(int i=0;i<n-1;i++)
	{	
		drawLine(cc[pr[i].start].x,cc[pr[i].start].y,cc[pr[i].end].x,cc[pr[i].end].y);
		drawWeight(cc[pr[i].start].x,cc[pr[i].start].y,cc[pr[i].end].x,cc[pr[i].end].y,pr[i].weight);
		Sleep(500);
	}
	setlinecolor(cf);//在输出完绿色的线后，别忘了将线的颜色变回去
	return;
}

void Draw::drawWeight(double x1,double y1, double x2, double y2, int weight)
{
	
	//char p=weight+'0';
	char s[100];
	sprintf(s,"%d",weight);//为了让多位数的int符合outtextxy的数据规范

	int n = MultiByteToWideChar(0, 0, s, -1, NULL, 0);
	wchar_t *wide = new wchar_t[n];
	MultiByteToWideChar(0, 0, s, -1, wide, n);

	
	outtextxy((x1+x2)/2,(y1+y2)/2,wide);
	return;
}



