#include<iostream>
#include "MenuManager.h"
//#include<windows.h>
using namespace std;

MenuManager::MenuManager(int mode):mode(mode){}

void MenuManager::Refresh(void (*p)())
{
		system("cls");
		p();
}

void MenuManager::operator()()
{
	switch (mode)
	{
	case 0:Refresh(ShowMainMenu); break;
	case 1:Refresh(ShowAccountBookMenu); break;
	case 2:Refresh(ShowStudyRecorderMenu); break;
	case 3:break;
	case 4:Refresh(ShowPasswordRecorderMenu); break;
	default:
		break;
	}
}

void ShowMainMenu()
{
	cout << "欢迎使用桌面助手！\n";
	cout << "1、记账本功能\n";
	cout << "2、密码记录器功能\n";
	cout << "3、学习记录器功能\n";
	cout << "4、课程备忘录功能\n";
	cout << "5、生活轨迹生成器功能\n";
	cout << "6、退出\n";
	cout << "请输入你想要使用的功能：\n";
}

void ShowAccountBookMenu()
{
	cout << "欢迎使用记账本功能！\n";
	cout << "1、记录日常收入和开销\n";
	cout << "2、显示记账本\n";
	cout << "3、显示特定时间范围内的收入与支出\n";
	cout << "4、删除收入与开销\n";
	cout << "5、退出至主页面\n";
	cout << "请输入你想要使用的功能：\n";
}

void ShowStudyRecorderMenu()
{
	cout << "欢迎使用学习记录器功能！\n";
	cout << "1、增加学习记录\n";
	cout << "2、显示学习记录\n";
	cout << "3、删除学习记录\n";
	cout << "4、退出至主页面\n";
	cout << "请输入你想要使用的功能：\n";
}

void ShowPasswordRecorderMenu()
{
	cout << "欢迎使用密码记录器功能！\n";
	cout << "1、保存新账号密码\n";
	cout << "2、显示账号密码\n";
	cout << "3、查找账号密码\n";
	cout << "4、删除账号密码\n";
	cout << "5、修改密码记录器密码\n";
	cout << "6、退出至主页面\n";
	cout << "请输入你想要使用的功能：\n";
}

void Pause_and_Cls()
{
	system("pause");
	system("cls");
}