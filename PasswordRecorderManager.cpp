#include"PasswordRecorderManager.h"


#define FILENAME "./txts/PasswordRecorder.png"
#define PASSWORDFILE "./txts/ThePasswordOfPasswordRecorder.png"

PasswordRecorderManager::PasswordRecorderManager() :is_Init(false)
{
	system("cls");
	cout << "���ڳ�ʼ������\n";
	Sleep(1000);
	cout << "���ڶ�ȡ�����ļ�����\n";
	Sleep(1000);
	ifstream ifs;
	ifs.open(PASSWORDFILE, ios::in);
	if (!ifs.is_open())
	{
		printf("�����ļ�δ��������\n");
		ifs.close();
		Sleep(1000);
		system("cls");
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		printf("�����ļ�Ϊ�ա���\n");
		ifs.close();
		Sleep(1000);
		system("cls");
		return;
	}
	ifs.close();
	ifs.open(PASSWORDFILE, ios::in);
	ifs >> to_Visit_Password;
	ifs.close();
	cout << "�����ļ���ȡ�ɹ�����\n";
	Sleep(1000);
	cout << "���ڶ�ȡ��¼�ļ�����\n";
	Sleep(1000);
	if (!ifs.is_open())
		ifs.open(FILENAME, ios::in);
	is_Init = true;
	string AccountName, Password;
	if (!ifs.is_open())
	{
		printf("��¼�ļ�δ��������\n");
		ifs.close();
		Sleep(1000);
		system("cls");
		return;
	}
	ifs >> ch;
	if (ifs.eof())
	{
		printf("��¼�ļ�Ϊ�ա���\n");
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
	cout << "��¼�ļ���ȡ�ɹ�����\n";
	Sleep(1000);
	cout << "��ʼ���ɹ���";
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
	cout << "�˺ţ�" << p.first << "\t\t" << "���룺" << p.second << endl;
}

void PasswordRecorderManager::init()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::trunc);
	ofs.close();
	string Password, Password_to_Confirm;
	cout << "��ǰ��δ���÷������룬���ڽ��з��������ʼ������\n";
	int cnt = 0;
	do
	{
		if (cnt != 0)
		{
			cout << "������������벻ͬ�����������룡\n";
		}
		cout << "������������룺" << endl;
		cin >> Password;
		cout << "���ٴ��������������ȷ�ϣ�" << endl;
		cin >> Password_to_Confirm;
		cnt++;
	} while (Password != Password_to_Confirm);
	to_Visit_Password = Password;
	ofs.open(PASSWORDFILE, ios::out);
	ofs << Password;
	is_Init = true;
	SetFileAttributes(PASSWORDFILE, FILE_ATTRIBUTE_HIDDEN);
	cout << "���óɹ���\n";
	Sleep(1000);
}

bool PasswordRecorderManager::checkPassword()
{
	string Password_to_Input;
	cout << "�����������Է��ʣ�\n";
	cin >> Password_to_Input;
	while (Password_to_Input != to_Visit_Password)
	{
		cout << "��������������������룺\n";
		cin >> Password_to_Input;
		if (Password_to_Input == "0")
		{
			cout << "�Ѿ�ȡ�����ʣ������˳��������¼����ҳ����\n";
			Sleep(1000);
			return false;
		}
	}
	system("cls");
	cout << "������ȷ�����ڼ����ѱ�������롭��\n";
	Sleep(1000);
	system("cls");
	return true;

}

void PasswordRecorderManager::write()
{
	cout << "���ڼ�¼�˺����룺\n";
	string AccountName, Password;
	cout << "�������˺����ƣ�\n";
	cin >> AccountName;
	cout << "�������˺����룺\n";
	cin >> Password;
	PasswordRecorderArray.push_back(make_pair(AccountName, Password));
	ofstream ofs;
	ofs.open(FILENAME, ios::app);
	ofs << AccountName << " " << Password << endl;
	ofs.close();
	SetFileAttributes(FILENAME, FILE_ATTRIBUTE_HIDDEN);
	cout << "�����Ѿ�����¼��\n";
}

void PasswordRecorderManager::show()
{
	if (PasswordRecorderArray.empty())
	{
		cout << "��ǰ�����¼��Ϊ�գ����ȼ�¼���롭��\n";
		Sleep(3000);
		return;
	}
	cout << "���ڷ����˺����룺\n";
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
		cout << "δ�ҵ����˺ţ�\n";//����󷵻������¼����ҳ����\n";
		return if_Find_Array;
	}

	int size = if_Find_Array.size();
	if (size == 1)
	{
		cout << "�˺ţ�" << if_Find_Array[0].second.first << "\t\t" << "���룺" << if_Find_Array[0].second.second << endl;
		return if_Find_Array;
	}
	cout << "�ҵ�����" << size << "���˺ż����Ӧ�����룺\n\n";
	for (int i = 0; i < size; i++)
	{
		cout << i + 1 << endl << "�˺ţ�" << if_Find_Array[i].second.first << "\t\t" << "���룺" << if_Find_Array[i].second.second << endl;
	}
	cout << "\n" << endl;
	return if_Find_Array;
}

void PasswordRecorderManager::search()
{
	if (PasswordRecorderArray.empty())
	{
		cout << "��ǰ�����¼��Ϊ�գ����ȼ�¼���롭��\n";
		Sleep(3000);
		return;
	}
	cout << "���ڲ�ѯ�˺�����\n";
	cout << "��������Ҫ��ѯ���˺ţ�" << endl;
	find();
}

void PasswordRecorderManager::delete_()
{
	if (PasswordRecorderArray.empty())
	{
		cout << "��ǰ�����¼��Ϊ�գ����ȼ�¼���롭��\n";
		Sleep(3000);
		return;
	}
	cout << "����ɾ���˺����롭��\n";
	cout << "��������Ҫɾ�����˺ţ�" << endl;
	vector<pair<int, pair<string, string>>>Password_to_Delete = find();
	int num = 0;
	if (Password_to_Delete.empty())return;
	if (Password_to_Delete.size() == 1)
	{
		comfirmToDelete(Password_to_Delete, num);
	}
	else
	{
		cout << "������Ҫɾ����һ����\n";
		cin >> num;
		while (num < 0 || num > Password_to_Delete.size())
		{
			cout << "������1-" << Password_to_Delete.size() << "֮���������\n";
			cin >> num;
		}
		if (num == 0)
		{
			cout << "�Ѿ�ȡ��ɾ��������" << endl;
			return;
		}
		else { num--; comfirmToDelete(Password_to_Delete, num); }
	}

}

void PasswordRecorderManager::comfirmToDelete(vector<pair<int, pair<string, string>>>& Password_to_Delete, int& num)
{
	cout << "������ȷ��Ҫɾ���𣿣�Y/N��\n";
	string to_Confirm;
	cin >> to_Confirm;
	while (to_Confirm != "Y" && to_Confirm != "N")
	{
		cout << "������Y��N��\n";
		cin >> to_Confirm;
	}
	if (to_Confirm == "N")
	{
		cout << "�Ѿ�ȡ��ɾ����\n";
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
	cout << "�Ѿ�ɾ�����˺ż����Ӧ�����룡\n";
}

void PasswordRecorderManager::reset()
{
	cout << "�����޸����룺\n";
	string Password_to_Input;
	cout << "������ԭ���룺\n";
	cin >> Password_to_Input;
	while (Password_to_Input != to_Visit_Password)
	{
		cout << "��������������������룺\n";
		cin >> Password_to_Input;
		if (Password_to_Input == "0")
		{
			cout << "�Ѿ�ȡ���޸ģ������˳��������¼����ҳ����";
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
			cout << "������������벻ͬ�����������룡\n";
			if (Password == "0")flag = false;
		}
		if (!flag)break;
		cout << "�����������룺" << endl;
		cin >> Password;
		cout << "���ٴ����������룺" << endl;
		cin >> Password_to_Confirm;
		cnt++;
	} while (Password != Password_to_Confirm);
	if (!flag)cout << "�����޸�ʧ�ܣ����ڷ��������¼����ҳ����\n";
	else
	{
		to_Visit_Password = Password;
		ofstream ofs;
		ofs.open(PASSWORDFILE, ios::out);
		ofs << Password;
		SetFileAttributes(PASSWORDFILE, FILE_ATTRIBUTE_HIDDEN);
		ofs.close();
		cout << "�����޸ĳɹ���" << endl;
	}
	Sleep(1000);
	return;

}


