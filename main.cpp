#include"MenuManager.h"
#include"AccountBookManager.h"
#include"StudyRecorderManager.h"
#include"PasswordRecorderManager.h"
#include"MemoManager.h"
#include"DailyRecorderManager.h"

using namespace std;


int main()
{
	while (1)
	{
		ShowMainMenu();
		int choice;
		cin >> choice;
		switch (choice)
		{
			
		case 1:AccountBookManager()(); break;
		case 2:PasswordRecorderManager()();break; 
		case 3:StudyRecorderManager()(); break;
		case 4:MemoManager()(); break;
		case 5:DailyRecorderManager()(); break;
		case 6:exit(0); break;
		default:cout << "输入无效！" << endl;
		}

	}

	return 0;
}
