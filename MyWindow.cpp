#include "MyWindow.h"

MyWindow::MyWindow()
{
}

MyWindow::MyWindow(int w, int h, int flag)
{
	m_handle = ::initgraph(w, h, flag);
	MoveWindow(m_handle, 400, 200, w, h, TRUE);
	settextstyle(20, 0, ("ºÚÌå"));
}

void MyWindow::setWindowTitle(const string& title)
{
	::SetWindowText(m_handle, title.c_str());
}

int MyWindow::exec()
{
	return getchar();
}

int MyWindow::width()
{
	return ::getwidth();
}

int MyWindow::height()
{
	return ::getwidth();
}

void MyWindow::clear()
{
	::cleardevice();
}

void MyWindow::beginDraw()
{
	::BeginBatchDraw();
}

void MyWindow::flushDraw()
{
	::FlushBatchDraw();
}

void MyWindow::endDraw()
{
	::EndBatchDraw();
}

HWND MyWindow::getHWND()
{
	return m_handle;
}

HWND MyWindow::m_handle;
ExMessage MyWindow::m_msg;