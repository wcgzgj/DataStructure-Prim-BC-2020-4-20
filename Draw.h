#pragma once

#include "Graph.h"
#define PI 3.1415

struct CircleCenter//��ͼʹ�õĺ���
{
	double x;
	double y;
	CircleCenter(double x,double y)
	{
		this->x=x;
		this->y=y;
	}
};

class Draw
{
public:
	Draw(void);
	~Draw(void);

	void iniPanel();
	void closePanel();
	void clearPanel();

	//************************************
	// Method:    drawCircle
	// FullName:  Draw::drawCircle
	// Access:    public 
	// Returns:   void
	// Qualifier: ���ݶ���ĸ���n��n��Χ��һȦ��СԲ
	//************************************
	void drawCircle(Graph gh);

	//************************************
	// Method:    drawLine
	// FullName:  Draw::drawLine
	// Access:    public 
	// Returns:   void
	// Qualifier: ������СԲ֮�������
	// Parameter: double x
	// Parameter: double y
	//************************************
	void drawLine(double x1,double y1, double x2, double y2);
	void drawInstant(primResult *pr,int n, int len);
	void drawSlow(primResult *pr,int n);
	void drawWeight(double x1,double y1, double x2, double y2, int weight);
	
};

