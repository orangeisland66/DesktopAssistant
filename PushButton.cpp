#include "PushButton.h"
PushButton::PushButton(const string& text, int x, int y, int w, int h):
	BasicWidget(x,y,w,h),m_text(text)
{
	
}

void PushButton::show(int mode)
{
	setfillcolor(color1);
	settextstyle(20, 0, "Î¢ÈíÑÅºÚ");
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);
	settextcolor(color2);

	if (mode == 0)
	{
		if (m_w < m_text.size() * 11 && m_text.size() < 10)
		{
			string text1 = m_text.substr(0, 4);
			string text2 = m_text.substr(4);
			int tx = m_x + (m_w - textwidth(text1.c_str())) / 2;
			int ty = m_y + (m_h - textheight(text1.c_str())) / 2;
			::outtextxy(tx, ty - 7, text1.c_str());
			::outtextxy(tx, ty + 7, text2.c_str());
		}
		else if (m_w < m_text.size() * 11 && m_text.size() >= 10)
		{
			string text1 = m_text.substr(0, 6);
			string text2 = m_text.substr(6);
			int tx = m_x + (m_w - textwidth(text1.c_str())) / 2;
			int ty = m_y + (m_h - textheight(text1.c_str())) / 2;
			::outtextxy(tx, ty - 7, text1.c_str());
			::outtextxy(tx, ty + 7, text2.c_str());
		}
		else
		{
			int tx = m_x + (m_w - textwidth(m_text.c_str())) / 2;
			int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;
			::outtextxy(tx, ty, m_text.c_str());

		}
	}
	else
	{
		int tx = m_x + (m_w - textwidth(m_text.c_str())) / 2;
		int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;
		::outtextxy(tx, ty, m_text.c_str());

	}

}
string PushButton::get_m_text()
{
	return m_text;
}

bool PushButton::isIn()
{
	if (m_msg.x >= m_x && m_msg.x < m_x + m_w && m_msg.y >= m_y && m_msg.y < m_y + m_h)
	{
		return true;
	}
	return false;
}

bool PushButton::isClicked()
{
	if (isIn())
	{
		if (m_msg.message == WM_LBUTTONDOWN)return true;
	}
	return false;
}

void PushButton::eventLoop(const ExMessage& msg,int mode)
{
	m_msg = msg;
	if (isIn())
	{
		COLORREF temp = color1;
		color1 = LIGHTRED;
		if (temp != color1)show(mode);
	}
	else
	{
		COLORREF temp2 = color1;
		color1 = LIGHTBLUE;
		if (temp2 != color1)show(mode);
	}
	
}

void PushButton::set_m_text(string textToModify)
{
	m_text = textToModify;
}
