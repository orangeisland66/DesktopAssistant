#pragma once
#include"header.h"
#include"MenuManager.h"
#include<graphics.h>

class MyWindow
{
public:
	MyWindow();
	MyWindow(int w, int h, int flag);
	void setWindowTitle(const string& title);
	int exec();
	static int width();
	static int height();
	static void clear();
	static void beginDraw();
	static void flushDraw();
	static void endDraw();
	static HWND getHWND();

	inline static bool hasMsg() { return ::peekmessage(&m_msg, EM_MOUSE | EM_KEY); }
	inline static const EASYXMSG& getMsg() { return m_msg; };
private:
	static HWND m_handle;//创建窗口句柄
	static ExMessage m_msg;//消息
};


