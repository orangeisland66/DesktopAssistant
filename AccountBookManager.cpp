#include"AccountBookManager.h"

#define FILENAME "./txts/AccountBook.txt"

void myPrintIn(const Account& ac)
{
	if (ac.getInorOut())cout << ac;
}

void myPrintOut(const Account& ac)
{
	if (!ac.getInorOut())cout << ac;
}

AccountBookManager::AccountBookManager():inSum(0),outSum(0){
	system("cls");
	cout << "���ڳ�ʼ������\n";
	Sleep(1000);
	cout << "���ڶ�ȡ�ļ�����\n";
	Sleep(1000);
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int year, month, day;
	double money;
	bool InorOut;
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
	while (ifs >> year && ifs >> month && ifs >> day && ifs >> money && ifs >> InorOut)
	{
		Account ac(year, month, day, money, InorOut);
		accountArray.insert(ac);
		if (InorOut)inSum += money;
		else outSum += money;
	}
	ifs.close();
	cout << "��ʼ���ɹ���";
	Sleep(1000);
}

void AccountBookManager::write()
{

	string dateInput;
	double money;
	cout << "��������Ҫ��¼�����ͣ�\n";
	cout << "1��֧�� 2�����룺\n";

	int choice;
	if ((choice = cinCheck<int>(1, 2)) == 0)return;
	if (choice == 1)
	{
		cout << "������֧�������ڣ�����/��/�գ�\n";
		while (cin >> dateInput && !cinCheck<bool>(4, 0, dateInput))cout << "��ʽ�������������룡\n";

		cout << "������֧����\n";
		if ((money = cinCheck<double>(2)) == 0)return;
		accountRegister(dateInput, money,choice);
	}
	if (choice == 2)
	{

		cout << "����������������ڣ�����/��/�գ�\n";
		while (cin >> dateInput && !cinCheck<bool>(4, 0, dateInput))cout<<"��ʽ�������������룡\n";
		cout << "�����������\n";
		if ((money = cinCheck<double>(2)) == 0)return;
		accountRegister(dateInput, money, choice);
	}

	cout << "��ӳɹ���\n";
}

void AccountBookManager::show()
{
	if (isEmpty())return;
	cout << "1����ʾ֧��" << endl;
	cout << "2����ʾ����" << endl;
	cout << "3����ʾȫ��" << endl;
	int choice;
	if ((choice = cinCheck<int>(1, 3)) == 0)return;
	system("cls");
	switch (choice)
	{
	case 1:
	{
		cout << endl << "��֧����" << outSum << endl << endl;
		for_each(accountArray.begin(), accountArray.end(), myPrintOut);
		break;
	}
	case 2:
	{
		cout << endl << "�����룺" << inSum << endl << endl;
		for_each(accountArray.begin(), accountArray.end(), myPrintIn);
		break;
	}
	case 3:
	{
		cout << endl << "�����룺" << inSum << " ��֧����" << outSum << endl << endl;
		for_each(accountArray.begin(), accountArray.end(), MyPrint<Account>);
		break;
	}
	default:cout << "������Ч��" << endl; break;
	}
}

void AccountBookManager::searchByDate()
{
	if (isEmpty())return;
	int Year_Month_Date1[3], Year_Month_Date2[3];
	string s1, s2;
	cout << "��������ʼ��ѯ���ڣ�\n";
	while (cin >> s1 && !cinCheck<bool>(4, 0, s1))cout << "��ʽ�������������룡\n";
	cout << "�����������ѯ���ڣ�\n";
	while (cin >> s2 && !cinCheck<bool>(4, 0, s2))cout << "��ʽ�������������룡\n";

	transform(s1, Year_Month_Date1), transform(s2, Year_Month_Date2);
	const Account ac1(Year_Month_Date1[0], Year_Month_Date1[1], Year_Month_Date1[2], 0, 0);
	const Account ac2(Year_Month_Date2[0], Year_Month_Date2[1], Year_Month_Date2[2], 0, 0);
	multiset<Account>::iterator front;
	multiset<Account>::iterator back;
	for (multiset<Account>::iterator it = accountArray.begin(); it != accountArray.end(); it++)
	{
		if (*it < ac1)continue;
		front = it;
		break;
	}
	multiset<Account>::iterator end = accountArray.end();
	multiset<Account>::iterator begin = accountArray.begin();
	end--;
	begin--;
	for (multiset<Account>::iterator it = end; it != begin; it--)
	{
		if (ac2 < *it)continue;
		it++;
		back = it;
		break;
	}
	double InSum=0, OutSum=0;
	for (multiset<Account>::iterator it = front; it != back; it++)
	{
		if ((*it).getInorOut())InSum += (*it).getmoney();
		else OutSum += (*it).getmoney();
	}
	cout << endl << "�����룺" << InSum << "��֧����" << OutSum << endl << endl;
	for_each(front, back, MyPrint<Account>);
}

void AccountBookManager::transform(string &YMD,int *Y_M_D)
{
	int size =(int) YMD.size();
	string temp;
	int pos = 0, count = 0;
	
	for (int i = 0; i < size; i++)
	{
		if (YMD[i] == '/')
		{
			temp = YMD.substr(pos, i - pos);
			pos = i + 1;
			stringstream ss;
			ss << temp;
			ss >> Y_M_D[count++];
		}
	}
	temp = YMD.substr(pos);
	stringstream ss;
	ss << temp;
	ss >> Y_M_D[count];
}

void AccountBookManager::accountRegister(string &s,double &money,int &choice)
{
	int year_month_date[3];
	transform(s, year_month_date);
	const Account ac(year_month_date[0], year_month_date[1], year_month_date[2], money,(bool)(choice-1));
	if ((choice - 1) == 0)outSum += money;
	else inSum += money;
	accountArray.insert(ac);
	ofstream ofs;
	ofs.open(FILENAME, ios::app);
	ofs << ac;
	ofs.close();
}

void AccountBookManager::operator()()
{
	int choice;

	while (1)
	{
		MenuManager(1)();
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1:write(); break;
		case 2:show(); break;
		case 3:searchByDate(); break;
		case 4:delete_(); break;
		case 5:goto flag; break;
		default:break;
		}
		Pause_and_Cls();
	}
flag:
	system("cls");
	return;
}

void AccountBookManager::delete_()
{
	if (isEmpty())return;
	cout << endl << "�����룺" << inSum << " ��֧����" << outSum << endl << endl;
	int i = 0;
	for (multiset<Account>::iterator it= accountArray.begin(); it != accountArray.end(); it++)
	{
		i++;
		cout << i << " " << (*it);
	}
	cout << "��������Ҫɾ�����������֧����¼��\n";
	int num;
	if ((num = cinCheck<int>(1, i)) == 0)return;
	int j = 0;
	for (multiset<Account>::iterator it = accountArray.begin(); it != accountArray.end(); it++)
	{
		j++;
		if (j == num)
		{
			if ((*it).getInorOut())inSum -= (*it).getmoney();
			else outSum -= (*it).getmoney();
			accountArray.erase(it);
			break;
		}
	}
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (multiset<Account>::iterator it = accountArray.begin(); it != accountArray.end(); it++)
	{
		ofs << (*it);
	}
	ofs.close();
	doubleJudge();
	cout << "ɾ���ɹ���" << endl;
}

void AccountBookManager::doubleJudge()
{
	if (abs(outSum - (int)outSum) < 1e-9)outSum = (int)outSum;
	if (abs(inSum - (int)inSum) < 1e-9)inSum =  (int)inSum;
}

bool AccountBookManager::isEmpty()
{
	if (accountArray.empty())
	{
		cout << "��ǰ��¼Ϊ�գ�����¼����֧��¼��\n";
		return true;
	}
	return false;
}
