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
	cout << "��ӭʹ���������֣�\n";
	cout << "1�����˱�����\n";
	cout << "2�������¼������\n";
	cout << "3��ѧϰ��¼������\n";
	cout << "4���γ̱���¼����\n";
	cout << "5������켣����������\n";
	cout << "6���˳�\n";
	cout << "����������Ҫʹ�õĹ��ܣ�\n";
}

void ShowAccountBookMenu()
{
	cout << "��ӭʹ�ü��˱����ܣ�\n";
	cout << "1����¼�ճ�����Ϳ���\n";
	cout << "2����ʾ���˱�\n";
	cout << "3����ʾ�ض�ʱ�䷶Χ�ڵ�������֧��\n";
	cout << "4��ɾ�������뿪��\n";
	cout << "5���˳�����ҳ��\n";
	cout << "����������Ҫʹ�õĹ��ܣ�\n";
}

void ShowStudyRecorderMenu()
{
	cout << "��ӭʹ��ѧϰ��¼�����ܣ�\n";
	cout << "1������ѧϰ��¼\n";
	cout << "2����ʾѧϰ��¼\n";
	cout << "3��ɾ��ѧϰ��¼\n";
	cout << "4���˳�����ҳ��\n";
	cout << "����������Ҫʹ�õĹ��ܣ�\n";
}

void ShowPasswordRecorderMenu()
{
	cout << "��ӭʹ�������¼�����ܣ�\n";
	cout << "1���������˺�����\n";
	cout << "2����ʾ�˺�����\n";
	cout << "3�������˺�����\n";
	cout << "4��ɾ���˺�����\n";
	cout << "5���޸������¼������\n";
	cout << "6���˳�����ҳ��\n";
	cout << "����������Ҫʹ�õĹ��ܣ�\n";
}

void Pause_and_Cls()
{
	system("pause");
	system("cls");
}