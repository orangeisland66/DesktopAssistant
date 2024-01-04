#include"PasswordRecorderManager.h"


#define FILENAME "./txts/PasswordRecorder.png"
#define PASSWORDFILE "./txts/ThePasswordOfPasswordRecorder.png"

PasswordRecorderManager::PasswordRecorderManager() :is_Init(false)
{
	system("cls");
	cout << "正在初始化……\n";
	Sleep(1000);
	cout << "正在读取密码文件……\n";
	Sleep(1000);
	ifstream ifs;
	ifs.open(PASSWORDFILE, ios::in);
	if (!ifs.is_open())
	{
		printf("密码文件未创建……\n");
		ifs.close();
		Sleep(1000);
		system("cls");
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		printf("密码文件为空……\n");
		ifs.close();
		Sleep(1000);
		system("cls");
		return;
	}
	ifs.close();
	ifs.open(PASSWORDFILE, ios::in);
	ifs >> to_Visit_Password;
	ifs.close();
	cout << "密码文件读取成功……\n";
	Sleep(1000);
	cout << "正在读取记录文件……\n";
	Sleep(1000);
	if (!ifs.is_open())
		ifs.open(FILENAME, ios::in);
	is_Init = true;
	string AccountName, Password;
	if (!ifs.is_open())
	{
		printf("记录文件未创建……\n");
		ifs.close();
		Sleep(1000);
		system("cls");
		return;
	}
	ifs >> ch;
	if (ifs.eof())
	{
		printf("记录文件为空……\n");
		ifs.close();
		Sleep(1000);
		system("cls");
		return;
	}
	ifs.close();
	ifs.open(FILENAME, ios::in);

	while (ifs >> AccountName && ifs >> Password)
	{
		PasswordRecorderArray.push_back(make_pair(AccountName, Password));
	}
	ifs.close();
	cout << "记录文件获取成功……\n";
	Sleep(1000);
	cout << "初始化成功！";
	Sleep(1000);
}

void PasswordRecorderManager::operator()()
{
	int choice;
	while (1)
	{
		if (!is_Init)init();
		MenuManager(4)();
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1:write(); break;
		case 2:show(); break;
		case 3:search(); break;
		case 4:delete_(); break;
		case 5:reset(); break;
		case 6:goto flag; break;
		default:break;
		}
		Pause_and_Cls();
	}
flag:
	system("cls");
	return;
}

void MyPasswordRecorderArrayPrint::operator()(const pair<string, string>& p)
{
	cout << "账号：" << p.first << "\t\t" << "密码：" << p.second << endl;
}

void PasswordRecorderManager::init()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::trunc);
	ofs.close();
	string Password, Password_to_Confirm;
	cout << "当前暂未设置访问密码，正在进行访问密码初始化……\n";
	int cnt = 0;
	do
	{
		if (cnt != 0)
		{
			cout << "两次输入的密码不同！请重新输入！\n";
		}
		cout << "请输入访问密码：" << endl;
		cin >> Password;
		cout << "请再次输入访问密码以确认：" << endl;
		cin >> Password_to_Confirm;
		cnt++;
	} while (Password != Password_to_Confirm);
	to_Visit_Password = Password;
	ofs.open(PASSWORDFILE, ios::out);
	ofs << Password;
	is_Init = true;
	SetFileAttributes(PASSWORDFILE, FILE_ATTRIBUTE_HIDDEN);
	cout << "设置成功！\n";
	Sleep(1000);
}

bool PasswordRecorderManager::checkPassword()
{
	string Password_to_Input;
	cout << "请输入密码以访问：\n";
	cin >> Password_to_Input;
	while (Password_to_Input != to_Visit_Password)
	{
		cout << "密码输入错误，请重新输入：\n";
		cin >> Password_to_Input;
		if (Password_to_Input == "0")
		{
			cout << "已经取消访问，即将退出至密码记录器主页……\n";
			Sleep(1000);
			return false;
		}
	}
	system("cls");
	cout << "密码正确！正在加载已保存的密码……\n";
	Sleep(1000);
	system("cls");
	return true;

}

void PasswordRecorderManager::write()
{
	cout << "正在记录账号密码：\n";
	string AccountName, Password;
	cout << "请输入账号名称：\n";
	cin >> AccountName;
	cout << "请输入账号密码：\n";
	cin >> Password;
	PasswordRecorderArray.push_back(make_pair(AccountName, Password));
	ofstream ofs;
	ofs.open(FILENAME, ios::app);
	ofs << AccountName << " " << Password << endl;
	ofs.close();
	SetFileAttributes(FILENAME, FILE_ATTRIBUTE_HIDDEN);
	cout << "密码已经被记录！\n";
}

void PasswordRecorderManager::show()
{
	if (PasswordRecorderArray.empty())
	{
		cout << "当前密码记录器为空，请先记录密码……\n";
		Sleep(3000);
		return;
	}
	cout << "正在访问账号密码：\n";
	if (!checkPassword())return;
	for_each(PasswordRecorderArray.begin(), PasswordRecorderArray.end(), MyPasswordRecorderArrayPrint());
}

vector<pair<int, pair<string, string>>> PasswordRecorderManager::find()
{
	vector<pair<int, pair<string, string>>> if_Find_Array;
	string Name_to_Find;
	cin >> Name_to_Find;
	if (!checkPassword())return if_Find_Array;
	int cnt = 0;
	for (vector<pair<string, string>>::iterator it = PasswordRecorderArray.begin();
		it != PasswordRecorderArray.end(); it++)
	{
		if ((*it).first == Name_to_Find)
			if_Find_Array.push_back(make_pair(cnt, make_pair((*it).first, (*it).second)));
		cnt++;
	}

	if (if_Find_Array.empty())
	{
		cout << "未找到该账号！\n";//三秒后返回密码记录器首页……\n";
		return if_Find_Array;
	}

	int size = if_Find_Array.size();
	if (size == 1)
	{
		cout << "账号：" << if_Find_Array[0].second.first << "\t\t" << "密码：" << if_Find_Array[0].second.second << endl;
		return if_Find_Array;
	}
	cout << "找到以下" << size << "个账号及其对应的密码：\n\n";
	for (int i = 0; i < size; i++)
	{
		cout << i + 1 << endl << "账号：" << if_Find_Array[i].second.first << "\t\t" << "密码：" << if_Find_Array[i].second.second << endl;
	}
	cout << "\n" << endl;
	return if_Find_Array;
}

void PasswordRecorderManager::search()
{
	if (PasswordRecorderArray.empty())
	{
		cout << "当前密码记录器为空，请先记录密码……\n";
		Sleep(3000);
		return;
	}
	cout << "正在查询账号密码\n";
	cout << "请输入需要查询的账号：" << endl;
	find();
}

void PasswordRecorderManager::delete_()
{
	if (PasswordRecorderArray.empty())
	{
		cout << "当前密码记录器为空，请先记录密码……\n";
		Sleep(3000);
		return;
	}
	cout << "正在删除账号密码……\n";
	cout << "请输入需要删除的账号：" << endl;
	vector<pair<int, pair<string, string>>>Password_to_Delete = find();
	int num = 0;
	if (Password_to_Delete.empty())return;
	if (Password_to_Delete.size() == 1)
	{
		comfirmToDelete(Password_to_Delete, num);
	}
	else
	{
		cout << "请问你要删除哪一个？\n";
		cin >> num;
		while (num < 0 || num > Password_to_Delete.size())
		{
			cout << "请输入1-" << Password_to_Delete.size() << "之间的整数！\n";
			cin >> num;
		}
		if (num == 0)
		{
			cout << "已经取消删除操作！" << endl;
			return;
		}
		else { num--; comfirmToDelete(Password_to_Delete, num); }
	}

}

void PasswordRecorderManager::comfirmToDelete(vector<pair<int, pair<string, string>>>& Password_to_Delete, int& num)
{
	cout << "请问你确定要删除吗？（Y/N）\n";
	string to_Confirm;
	cin >> to_Confirm;
	while (to_Confirm != "Y" && to_Confirm != "N")
	{
		cout << "请输入Y或N！\n";
		cin >> to_Confirm;
	}
	if (to_Confirm == "N")
	{
		cout << "已经取消删除！\n";
		return;
	}
	PasswordRecorderArray.erase(PasswordRecorderArray.begin() + Password_to_Delete[num].first);
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (vector<pair<string, string>>::iterator it = PasswordRecorderArray.begin(); it != PasswordRecorderArray.end(); it++)
	{
		ofs << (*it).first << " " << (*it).second << endl;
	}
	ofs.close();
	cout << "已经删除该账号及其对应的密码！\n";
}

void PasswordRecorderManager::reset()
{
	cout << "正在修改密码：\n";
	string Password_to_Input;
	cout << "请输入原密码：\n";
	cin >> Password_to_Input;
	while (Password_to_Input != to_Visit_Password)
	{
		cout << "密码输入错误，请重新输入：\n";
		cin >> Password_to_Input;
		if (Password_to_Input == "0")
		{
			cout << "已经取消修改，即将退出至密码记录器主页……";
			Sleep(1000);
			return;
		}
	}

	string Password, Password_to_Confirm;
	int cnt = 0;
	bool flag = true;
	do
	{
		if (cnt != 0)
		{
			cout << "两次输入的密码不同！请重新输入！\n";
			if (Password == "0")flag = false;
		}
		if (!flag)break;
		cout << "请输入新密码：" << endl;
		cin >> Password;
		cout << "请再次输入新密码：" << endl;
		cin >> Password_to_Confirm;
		cnt++;
	} while (Password != Password_to_Confirm);
	if (!flag)cout << "密码修改失败，正在返回密码记录器主页……\n";
	else
	{
		to_Visit_Password = Password;
		ofstream ofs;
		ofs.open(PASSWORDFILE, ios::out);
		ofs << Password;
		SetFileAttributes(PASSWORDFILE, FILE_ATTRIBUTE_HIDDEN);
		ofs.close();
		cout << "密码修改成功！" << endl;
	}
	Sleep(1000);
	return;

}


