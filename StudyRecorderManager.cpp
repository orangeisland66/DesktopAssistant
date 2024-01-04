#include"StudyRecorderManager.h"
#include"header.h"

#define FILENAME "./txts/StudyRecorder.txt"

StudyRecorderManager::StudyRecorderManager()
{
	system("cls");
	cout << "���ڳ�ʼ������\n";
	Sleep(1000);
	cout << "���ڶ�ȡ�ļ�����\n";
	Sleep(1000);
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int year, month, day;
	string place, content;
	if (!ifs.is_open())
	{
		printf("�ļ�δ������\n");
		ifs.close();
	    Sleep(1000);
		system("cls");
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		printf("�ļ�Ϊ�գ�\n");
		ifs.close();
		Sleep(1000);
		system("cls");
		return;
	}
	ifs.putback(ch);
	while (ifs >> year && ifs >> month && ifs >> day && ifs >> place && ifs >> content)
	{
		StudyRecorder rc(year, month, day, place , content);
		StudyRecorderArray.push_back(rc);
	}
	ifs.close();
	cout << "��ʼ���ɹ���";
	Sleep(1000);
}

void StudyRecorderManager::write()
{
	cout << "������ѧϰ��ʱ�䣺\n";
	string StudyTime;
	while (cin >> StudyTime && !cinCheck<bool>(4, 0, StudyTime))cout << "��ʽ�������������룡\n";
	int Year_Month_Day[3];
	int size = StudyTime.size();
	string temp;
	int pos = 0, count = 0;
	for (int i = 0; i < size; i++)
	{
		if (StudyTime[i] == '/')
		{
			temp = StudyTime.substr(pos, i - pos);
			pos = i + 1;
			stringstream ss;
			ss << temp;
			ss >> Year_Month_Day[count++];
		}
	}
	temp = StudyTime.substr(pos);
	stringstream ss;
	ss << temp;
	ss >> Year_Month_Day[count];
	string place, content;
	cout << "������ѧϰ�ص㣺\n";
	cin >> place;
	cout << "������ѧϰ���ݣ�\n";
	cin >> content;
	StudyRecorder rc(Year_Month_Day[0], Year_Month_Day[1], Year_Month_Day[2], place, content);
	StudyRecorderArray.push_back(rc);
	ofstream ofs;
	ofs.open(FILENAME, ios::app);
	ofs << rc;
	ofs.close();
	cout << "��ӳɹ���";
}

void StudyRecorderManager::operator()()
{
	int choice;

	while (1)
	{
		MenuManager(2)();
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1:write(); break;
		case 2:show(); break;
		case 3:delete_(); break;
		case 4:goto flag; break;
		default:break;
		}
		Pause_and_Cls();
	}
flag:
	system("cls");
	return;
}

void StudyRecorderManager::show()
{
	for_each(StudyRecorderArray.begin(), StudyRecorderArray.end(), MyPrint<StudyRecorder>);

}

void StudyRecorderManager::delete_()
{
	int i = 0;
	for (vector<StudyRecorder>::iterator it = StudyRecorderArray.begin(); it != StudyRecorderArray.end(); it++)
	{
		i++;
		cout << i << endl << (*it);
	}
	cout << "������Ҫɾ����һ��ѧϰ��¼��\n";
	int num;
	cin >> num;
	StudyRecorderArray.erase(StudyRecorderArray.begin() + num - 1);
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (vector<StudyRecorder>::iterator it = StudyRecorderArray.begin(); it != StudyRecorderArray.end(); it++)
	{
		ofs << (*it);
	}
	ofs.close();
	cout << "��ѧϰ��¼�Ѿ���ɾ����\n";
}