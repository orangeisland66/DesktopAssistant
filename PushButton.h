#pragma once
#include "BasicWidget.h"

class PushButton :
    public BasicWidget
{
public:
    PushButton(const string& text = "Button", COLORREF color1 = RGB(105, 175, 240), int x = 0, int y = 0, int w = 100, int h = 30);
    void show(int mode)override;
    string get_m_text();
    bool isIn();//判断鼠标是否在按钮上
    bool isClicked();//判断鼠标是否被点击  
    void eventLoop(const ExMessage& msg,int mode);
    void set_m_text(string textToModify);
private:
    string m_text;
    ExMessage m_msg;
    COLORREF color1, color2=WHITE;
    COLORREF save;
};

