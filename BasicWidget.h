#pragma once
#include"header.h"

class BasicWidget
{
public:
	BasicWidget(int x, int y, int w, int h);
	int width();
	int height();
	void setFixedSize(int w, int h);
	void set(int x, int y, int w, int h);
	int x();
	int y();
	void move(int x, int y);
	virtual void show(int mode) = 0;
protected:
	int m_x;
	int m_y;
	int m_w;
	int m_h;
};

