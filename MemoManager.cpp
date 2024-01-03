#include "MemoManager.h"
#define FILENAME "./txts/Memo.txt"
MemoManager::MemoManager()
	:menu(new IMAGE(640, 793)), schedule(new IMAGE(348, 640))
{
	fileInit();
	MyWindow::MyWindow(640, 680, EW_SHOWCONSOLE | EX_NOCLOSE);
	MyWindow::setWindowTitle("�γ̱���¼");

	LOGFONT f;
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ

	SystemTime::getSystemTime();
	
	setbkmode(TRANSPARENT);
	::loadimage(menu, "./MemoImages/menu.jpg", 640, 793);
	::loadimage(schedule, "./MemoImages/schedule.jpg", 348, 640);

	menu_btns.push_back(PushButton("�鿴�α�", RGB(32, 161, 98)));
	menu_btns.push_back(PushButton("�˳��γ̱���¼ϵͳ",RGB(140,194,105)));
	select_btns.push_back(PushButton("��ӿγ�����", RGB(102, 193, 140)));
	select_btns.push_back(PushButton("ɾ���γ�����", RGB(102, 193, 140)));
	select_btns.push_back(PushButton("�����ҵddl", RGB(102, 193, 140)));
	select_btns.push_back(PushButton("ɾ����ҵddl", RGB(102, 193, 140)));
	select_btns.push_back(PushButton("�鿴�γ���ϸ��Ϣ", RGB(102, 193, 140)));
	select_btns.push_back(PushButton("ɾ���ÿγ�", RGB(102, 193, 140)));
	addButton.push_back(PushButton("��ӿγ�", RGB(32, 161, 98)));

	setPos(menu_btns);
	setPos(select_btns);
	addButton[0].move(360, 560);
	addButton[0].setFixedSize(250, 50);
}

void MemoManager::operator()()
{
	int op = 0;
	while (true)
	{
		MyWindow::beginDraw();
		cleardevice();
		drawBackground(1);

		if (MyWindow::hasMsg())
		{
			msg = MyWindow::getMsg();
		}
		show_btns(menu_btns);
		SystemTime::getSystemTime();
		SystemTime::showTime();
		MyWindow::endDraw();

		switch (op)
		{
		case -1:
		{
			drawBackground(1);
			show_btns(menu_btns);
			op = 0;
		}
		case 0:op = menueventLoop(menu_btns); break;
		case 1:op = schedulePage(); break;
		case 2:goto flag;
		}
	}
flag:
	cout << "�����˳�����\n";
	closegraph();
	cout << "���˳�,���ڼ��������桭��\n";
	Sleep(1000);
	system("cls");
	return;
}

void MemoManager::fileInit()
{
	system("cls");
	cout << "���ڳ�ʼ������\n";
	Sleep(1000);
	cout << "���ڶ�ȡ�ļ�����\n";
	Sleep(1000);
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	string subjectName, teacher, string_weekday, sections;
	bool have_ddl = false, have_reminder = false;
	int year = 0, month = 0, day = 0;
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
	while (ifs >> subjectName && ifs >> teacher && ifs >> string_weekday && ifs >> sections && ifs >> have_ddl)
	{
		if (have_ddl == true)
		{
			ifs >> year;
			ifs >> month;
			ifs >> day;
			ifs >> have_reminder;
		}
		else ifs >> have_reminder;
		Subject sbj(subjectName, teacher, string_weekday, sections, have_ddl, year, month, day, have_reminder);
		subjectArray.push_back(sbj);

	}
	ifs.close();
	sortAndBtnsPushBack();
	cout << "��ʼ���ɹ���\n";
	Sleep(1000);
}

void MemoManager::transform1(string YMD,int *Y_M_D)
{
	int size = (int)YMD.size();
	string temp;
	int a = 0, count = 0;

	for (int i = 0; i < size; i++)
	{
		if (YMD[i] == '/')
		{
			temp = YMD.substr(a, i - a);
			a = i + 1;
			stringstream ss;
			ss << temp;
			ss >> Y_M_D[count++];
		}
	}

	temp = YMD.substr(a);
	stringstream ss;
	ss << temp;
	ss >> Y_M_D[count];
}

string MemoManager::transform2(vector<int>&v)
{
	stringstream ss[4];
	string day, hour, minute, second;
	ss[0] << v[0];
	ss[0] >> day;
	ss[1] << v[1];
	ss[1] >> hour;
	ss[2] << v[2];
	ss[2] >> minute;
	ss[3] << v[3];
	ss[3] >> second;
	return " " + day + "��" + hour + "Сʱ" + minute + "��" + second + "��";
}

void MemoManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < subjectArray.size(); i++)
	{
		ofs << subjectArray[i];
	}
}

void MemoManager::showEsc()
{
	settextcolor(BLACK);
	settextstyle(30, 0, ("����"));
	outtextxy(550, 5, "Esc");
	settextstyle(15, 0, ("consolas"));
	outtextxy(550, 30, "������һ��");
	settextcolor(WHITE);
}

void MemoManager::show_btns(vector<PushButton> &v)
{
	for (int i = 0; i < v.size(); i++)
	{
		v[i].show(0);
	}
}

void MemoManager::reminder_and_ddlShow()
{
	
	showEsc();
	settextstyle(40, 0, ("�п�"));
	outtextxy(360, 10, "�γ�����");
	settextstyle(22, 0, ("΢���ź�"));
	int size1 = (int)subjectArray.size();
	int cnt = 0;
	SystemTime::getSystemTime();//��һ��vector���ʹ洢�����Ѿ��Ϲ��Ŀγ̣�������Ա�֤ʱ��˳�򣬵��ǲ�֪��Ϊʲô�����������飬������ʾ�������

	vector < pair<string, vector<int>>>temp1;
	for (int i = 0; i < size1; i++)
	{
		vector<int>v;
		if (subjectArray[i].is_reminder())
		{
			int day = 0, hour = 0, minute = 0, second = 0, bs = 1;
			
			if (SystemTime::getSecond() == 0)
			{
				second = 60;
				bs = 0;
			}
			else second = 60 - SystemTime::getSecond();
			if ((subjectArray[i].getStartMinute() - SystemTime::getMinute() - bs) < 0)
			{
				minute = subjectArray[i].getStartMinute() - SystemTime::getMinute() - bs + 60;
				bs = 1;
			}
			else
			{
				minute = subjectArray[i].getStartMinute() - SystemTime::getMinute() - bs;
				bs = 0;
			}
			if ((subjectArray[i].getStartHour() - SystemTime::getHour() - bs) < 0)
			{
				hour = 24 + subjectArray[i].getStartHour() - SystemTime::getHour() - bs;
				bs = 1;
			}
			else
			{
				hour = subjectArray[i].getStartHour() - SystemTime::getHour() - bs;
				bs = 0;
			}
			if ((subjectArray[i].getWeekday() - SystemTime::getDayOfWeek() - bs) < 0)
			{
				day = 7 + subjectArray[i].getWeekday() - SystemTime::getDayOfWeek() - bs;
				bs = 1;
				v.push_back(day), v.push_back(hour), v.push_back(minute), v.push_back(second);
				temp1.push_back(make_pair(subjectArray[i].getSubjectName(), v));
			}
			else
			{
				day = subjectArray[i].getWeekday() - SystemTime::getDayOfWeek() - bs;
				bs = 1;
				v.push_back(day), v.push_back(hour), v.push_back(minute), v.push_back(second);
				outtextxy(360, 60 + 35 * cnt, subjectArray[i].getSubjectName().c_str());
				outtextxy(470, 60 + 35 * (cnt++), transform2(v).c_str());
				
			}
		}
		
	}

	int size2 = (int)temp1.size();
	for (int i = 0; i < size2; i++)
	{
		outtextxy(360, 60 + 35 * cnt, temp1[i].first.c_str());
		outtextxy(470, 60 + 35 * (cnt++), transform2(temp1[i].second).c_str());
	}
	settextstyle(40, 0, ("�п�"));
	outtextxy(360, 300, "�γ���ҵddl");
	settextstyle(22, 0, ("΢���ź�"));

	set <Deadline,MyCompare<Deadline>> temp_ddlArray;
	for (vector<Subject>::iterator it = subjectArray.begin(); it != subjectArray.end(); it++)
	{
		
		if ((*it).is_ddl())
		{
				int dayRemain = calculateDay((*it).getYear(), (*it).getMonth(), (*it).getDay());
				if (dayRemain <= -1)(*it).delete_ddl();
				else temp_ddlArray.insert(Deadline((*it).getSubjectName(), dayRemain));
		}
	}

	cnt = 0;
	for (set<Deadline>::iterator it = temp_ddlArray.begin(); it != temp_ddlArray.end(); it++)
	{
		(*it).deadlineOutput(cnt++);
	}
	settextstyle(20, 0, ("΢���ź�"));
}

int MemoManager::deleteSubject(int i)
{

	int flag = MessageBox(MyWindow::getHWND(), "��ȷ��Ҫɾ���ÿγ���", "��ʾ", MB_YESNO);
	if (flag == 6)
	{
		subjectArray.erase(subjectArray.begin() + i);
		sortAndBtnsPushBack();
		save();
	}
	return 7;
}

int MemoManager::addSubject()
{
	char subjectInput[30] = { 0 };
	string transform;
	bool isInput = InputBox(subjectInput, 30, 
		"��ʽ���γ��� ��ʦ�� ���ڼ� ��ֹ����\n���ӣ����� СС ���ڶ�(�ܶ�) 1-2 \n��������֮���һ���ո񣡿γ��������������֣�������ģ���Ҫ�����п�Ŀʱ���ظ��������ˣ���",
		"��ӿγ���Ϣ", NULL, 0, 0, false);
	if (strlen(subjectInput) == 0 || !isInput)return -1;
	if (!cinCheck<bool>(5, 0, subjectInput))
	{
		MessageBox(MyWindow::getHWND(), "�����ʽ�������ʧ�ܣ�", "��ʾ", MB_OK);
		return -1;
	}
	transform = subjectInput;
	string info[4];
	int size = (int)transform.size();
	int pos = 0, cnt = 0;
	for (int i = 0; i <= size; i++)
	{
		if (transform[i] == ' ' || transform[i] == '\0')
		{
			info[cnt++] = transform.substr(pos, i - pos);
			pos = i + 1;
		}
	}
	subjectArray.push_back(Subject(info[0], info[1], info[2], info[3]));
	sortAndBtnsPushBack();

	save();
	MessageBox(MyWindow::getHWND(), "�Ѿ��ɹ���Ӹÿγ̣�", "��ʾ", MB_OK);
	return -1;
}

int MemoManager::add_ddl(int i)
{
	char dateInput[15] = { 0 };
	bool isInput = InputBox(dateInput, 15, "�������ֹʱ��\n��ʽ��Y/M/D\n���ӣ�2024/1/25", "�����ֹʱ��", NULL, 0, 0, false);
	if (strlen(dateInput)==0 || !isInput)return 7;
	if (!cinCheck<bool>(4, 0, dateInput))
	{
		MessageBox(MyWindow::getHWND(), "�����ʽ�������ʧ�ܣ�", "��ʾ", MB_OK);
		return 7;
	}
	int year_month_date[3] = { 0 };
	transform1(dateInput, year_month_date);

	SystemTime::getSystemTime();

	bool flag = true;
	if (year_month_date[0] < SystemTime::getYear())flag = false;
	if ((year_month_date[0] == SystemTime::getYear())&&(year_month_date[1] < SystemTime::getMonth()))flag = false;
	if ((year_month_date[0] == SystemTime::getYear()) && (year_month_date[1] == SystemTime::getMonth()) && (year_month_date[2] < SystemTime::getDay()))flag = false;
	if (flag == false)
	{
		MessageBox(MyWindow::getHWND(), "����ڹ�ȥ�ˣ�ddl�Ǹ�δ��׼���ģ�", "��ʾ", MB_OK);
		return 7;
	}
	if(!subjectArray[i].set_ddl(year_month_date[0], year_month_date[1], year_month_date[2]))
		MessageBox(MyWindow::getHWND(), "���Ѿ��ڸÿγ������ddl���޷��ظ���ӣ�", "��ʾ", MB_OK);
	else
	{
		save();
		MessageBox(MyWindow::getHWND(), "���Ѿ��ɹ����ddl��", "��ʾ", MB_OK);
	}
	return 7;
}

int	MemoManager::delete_ddl(int i)
{
	int flag = MessageBox(MyWindow::getHWND(), "��ȷ��Ҫɾ���ÿγ̵�ddl��", "��ʾ", MB_YESNO);
	if (flag == 6)
	{
		if (!subjectArray[i].delete_ddl())MessageBox(MyWindow::getHWND(), "��ǰδ���ddl������ɾ����", "��ʾ", MB_OK);
		else
		{
			save();
			MessageBox(MyWindow::getHWND(), "���Ѿ��ɹ�ɾ��ddl��", "��ʾ", MB_OK);
		}
	}
	return 7;
}

int MemoManager::addReminder(int i)
{
	if(!subjectArray[i].set_have_reminder(true))MessageBox(MyWindow::getHWND(), "���Ѿ���ӿγ����ѣ������ظ���ӣ�", "��ʾ", MB_OK);
	else
	{
		save();
		MessageBox(MyWindow::getHWND(), "�Ѿ��ɹ���ӿγ����ѣ�", "��ʾ", MB_OK);
	}
	Sleep(100);
	return 7;
}

int MemoManager::deleteReminder(int i)
{
	int flag = MessageBox(MyWindow::getHWND(), "��ȷ��Ҫɾ���ÿγ̵Ŀγ�������", "��ʾ", MB_YESNO);
	if (flag == 6)
	{
		if (!subjectArray[i].set_have_reminder(false))MessageBox(MyWindow::getHWND(), "��ǰδ��ӿγ����ѣ�����ɾ����", "��ʾ", MB_OK);
		else
		{
			save();
			MessageBox(MyWindow::getHWND(), "�Ѿ��ɹ�ɾ���γ����ѣ�", "��ʾ", MB_OK);
		}
	}
	Sleep(100);
	return 7;
}

int MemoManager::menueventLoop(vector<PushButton> &v)
{
	for (int i = 0; i < v.size(); i++)
	{
		v[i].eventLoop(msg, 0);
		if (v[i].isClicked())
		{
			if (v[i].get_m_text() == "��ӿγ�")return -2;
			return i+1;
		}
	}
	return 0;
}

bool MemoManager::isEsc()
{
	if (MyWindow::hasMsg())
	{
		msg = MyWindow::getMsg();
		switch (msg.message)
		{
		case WM_KEYDOWN:
			if (msg.vkcode == VK_ESCAPE)
			{
				cleardevice();
				return true;
			}//esc�˳�������
			break;
		default:break;
		}
	}
	return false;
}

int MemoManager::schedulePage()
{

	int op = 0;
	Sleep(100);
	setbkcolor(RGB(104, 177, 220));

	while (1)
	{
		MyWindow::beginDraw();
		cleardevice();
		drawBackground(2);
		show_btns(schedule_btns);
		show_btns(addButton);
		reminder_and_ddlShow();
		MyWindow::endDraw();

		if (isEsc())return -1;

		if (MyWindow::hasMsg())
		{
			msg = MyWindow::getMsg();
		}

		switch (op)
		{
		case -2:op = addSubject(); break;
		case -1:
		{
			MyWindow::beginDraw();
			cleardevice();
			drawBackground(2);
			show_btns(schedule_btns);
			show_btns(addButton);
			reminder_and_ddlShow();
			MyWindow::endDraw();
			Sleep(100);
			op = 0;
			break;
		}
		case 0:
		{
			op = menueventLoop(schedule_btns);
			if(op==0)op = menueventLoop(addButton);
			break;
		}
		
		default:op = selectMenu(op-1); break;
		}

	}
}

void MemoManager::setPos(vector<PushButton>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		v[i].setFixedSize(250, 50);
		int bx = (MyWindow::width() - v[i].width()) / 2;
		int vspace = (MyWindow::height() - (int)v.size() * v[i].height()) / 2;
		int by = i * v[i].height() + vspace;
		v[i].move(bx, by);
	}
}

void MemoManager::drawBackground(int mode)
{
	if (mode == 1)
	{
		::putimage(0, 0, menu);
	}
	if (mode == 2)
	{
		::putimage(0, 0, schedule);
	}
}

int MemoManager::selectMenu(int i)
{

	int op = 0;
	Sleep(100);

	while (1)
	{
		MyWindow::beginDraw();
		cleardevice();
		drawBackground(1);
		showEsc();
		show_btns(select_btns);
		MyWindow::endDraw();

		if (isEsc())return -1;

		if (MyWindow::hasMsg())
		{
			msg = MyWindow::getMsg();
		}

		switch (op)
		{
		case 0:op = menueventLoop(select_btns); break;
		case 1:op = addReminder(i);  break;
		case 2:op = deleteReminder(i); break;
		case 3:op = add_ddl(i);  break;
		case 4:op = delete_ddl(i); break;
		case 5:op = showSubjectInfo(i);  break;
		case 6:op = deleteSubject(i); break;
		case 7:
		{
			MyWindow::beginDraw();
			cleardevice();
			drawBackground(1);
			show_btns(select_btns);
			MyWindow::endDraw();
			Sleep(100);
			op = 0;
		}
		}
	}
}

int MemoManager::showSubjectInfo(int i)
{
	MyWindow::beginDraw();
	cleardevice();
	drawBackground(1);
	subjectArray[i].outtextInfo();
	MyWindow::endDraw();
	while (1) 
	{
		if (isEsc())return 7;
	}
	
}

void MemoManager::sortAndBtnsPushBack()
{
	sort(subjectArray.begin(), subjectArray.end(), MyCompare<Subject>());
	schedule_btns.clear();

	for (vector<Subject>::iterator it = subjectArray.begin(); it != subjectArray.end(); it++)
	{
		schedule_btns.push_back((*it).getButn());
	}
}

int MemoManager::calculateDay(int year,int month,int day)
{
	SystemTime::getSystemTime();
	struct tm t1 = { 0 };
	struct tm t2 = { 0 };
	double seconds;
	t1.tm_year = SystemTime::getYear() - 1900; t1.tm_mon = SystemTime::getMonth() - 1; t1.tm_mday = SystemTime::getDay();//����ʱ��
	t2.tm_year = year - 1900; t2.tm_mon = month - 1; t2.tm_mday = day;//ddlʱ��
	seconds = difftime(mktime(&t2), mktime(&t1));//ת���ṹ��Ϊtime_t,����difftime,����ʱ���  
	if (seconds == 0)return -1;
	return (int)(seconds / 86400);//������ʱ��,��Ϊһ����86400��(60*60*24)
}

MemoManager::~MemoManager()
{
	delete menu;
	delete schedule;
}