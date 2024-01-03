#include "MemoManager.h"
#define FILENAME "./txts/Memo.txt"
MemoManager::MemoManager()
	:menu(new IMAGE(640, 793)), schedule(new IMAGE(348, 640))
{
	fileInit();
	MyWindow::MyWindow(640, 680, EW_SHOWCONSOLE | EX_NOCLOSE);
	MyWindow::setWindowTitle("课程备忘录");

	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	settextstyle(&f);						// 设置字体样式

	SystemTime::getSystemTime();
	
	setbkmode(TRANSPARENT);
	::loadimage(menu, "./MemoImages/menu.jpg", 640, 793);
	::loadimage(schedule, "./MemoImages/schedule.jpg", 348, 640);

	menu_btns.push_back(PushButton("查看课表", RGB(32, 161, 98)));
	menu_btns.push_back(PushButton("退出课程备忘录系统",RGB(140,194,105)));
	select_btns.push_back(PushButton("添加课程提醒", RGB(102, 193, 140)));
	select_btns.push_back(PushButton("删除课程提醒", RGB(102, 193, 140)));
	select_btns.push_back(PushButton("添加作业ddl", RGB(102, 193, 140)));
	select_btns.push_back(PushButton("删除作业ddl", RGB(102, 193, 140)));
	select_btns.push_back(PushButton("查看课程详细信息", RGB(102, 193, 140)));
	select_btns.push_back(PushButton("删除该课程", RGB(102, 193, 140)));
	addButton.push_back(PushButton("添加课程", RGB(32, 161, 98)));

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
	cout << "正在退出……\n";
	closegraph();
	cout << "已退出,正在加载主界面……\n";
	Sleep(1000);
	system("cls");
	return;
}

void MemoManager::fileInit()
{
	system("cls");
	cout << "正在初始化……\n";
	Sleep(1000);
	cout << "正在读取文件……\n";
	Sleep(1000);
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	string subjectName, teacher, string_weekday, sections;
	bool have_ddl = false, have_reminder = false;
	int year = 0, month = 0, day = 0;
	if (!ifs.is_open())
	{
		printf("文件未创建！\n");
		ifs.close();
		Sleep(1000);
		system("cls");
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		printf("文件为空！\n");
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
	cout << "初始化成功！\n";
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
	return " " + day + "天" + hour + "小时" + minute + "分" + second + "秒";
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
	settextstyle(30, 0, ("黑体"));
	outtextxy(550, 5, "Esc");
	settextstyle(15, 0, ("consolas"));
	outtextxy(550, 30, "返回上一级");
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
	settextstyle(40, 0, ("行楷"));
	outtextxy(360, 10, "课程提醒");
	settextstyle(22, 0, ("微软雅黑"));
	int size1 = (int)subjectArray.size();
	int cnt = 0;
	SystemTime::getSystemTime();//用一个vector类型存储这周已经上过的课程，在输出以保证时间顺序，但是不知道为什么，不能用数组，，，显示会出问题

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
	settextstyle(40, 0, ("行楷"));
	outtextxy(360, 300, "课程作业ddl");
	settextstyle(22, 0, ("微软雅黑"));

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
	settextstyle(20, 0, ("微软雅黑"));
}

int MemoManager::deleteSubject(int i)
{

	int flag = MessageBox(MyWindow::getHWND(), "你确定要删除该课程吗？", "提示", MB_YESNO);
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
		"格式：课程名 教师名 星期几 起止节数\n例子：数电 小小 星期二(周二) 1-2 \n（各部分之间隔一个空格！课程名不多于六个字，最好中文，不要和已有科目时间重复，求求了！）",
		"添加课程信息", NULL, 0, 0, false);
	if (strlen(subjectInput) == 0 || !isInput)return -1;
	if (!cinCheck<bool>(5, 0, subjectInput))
	{
		MessageBox(MyWindow::getHWND(), "输入格式错误，添加失败！", "提示", MB_OK);
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
	MessageBox(MyWindow::getHWND(), "已经成功添加该课程！", "提示", MB_OK);
	return -1;
}

int MemoManager::add_ddl(int i)
{
	char dateInput[15] = { 0 };
	bool isInput = InputBox(dateInput, 15, "请输入截止时间\n格式：Y/M/D\n例子：2024/1/25", "输入截止时间", NULL, 0, 0, false);
	if (strlen(dateInput)==0 || !isInput)return 7;
	if (!cinCheck<bool>(4, 0, dateInput))
	{
		MessageBox(MyWindow::getHWND(), "输入格式错误，添加失败！", "提示", MB_OK);
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
		MessageBox(MyWindow::getHWND(), "别活在过去了，ddl是给未来准备的！", "提示", MB_OK);
		return 7;
	}
	if(!subjectArray[i].set_ddl(year_month_date[0], year_month_date[1], year_month_date[2]))
		MessageBox(MyWindow::getHWND(), "你已经在该课程添加了ddl，无法重复添加！", "提示", MB_OK);
	else
	{
		save();
		MessageBox(MyWindow::getHWND(), "你已经成功添加ddl！", "提示", MB_OK);
	}
	return 7;
}

int	MemoManager::delete_ddl(int i)
{
	int flag = MessageBox(MyWindow::getHWND(), "你确定要删除该课程的ddl吗？", "提示", MB_YESNO);
	if (flag == 6)
	{
		if (!subjectArray[i].delete_ddl())MessageBox(MyWindow::getHWND(), "当前未添加ddl，无需删除！", "提示", MB_OK);
		else
		{
			save();
			MessageBox(MyWindow::getHWND(), "你已经成功删除ddl！", "提示", MB_OK);
		}
	}
	return 7;
}

int MemoManager::addReminder(int i)
{
	if(!subjectArray[i].set_have_reminder(true))MessageBox(MyWindow::getHWND(), "你已经添加课程提醒，无需重复添加！", "提示", MB_OK);
	else
	{
		save();
		MessageBox(MyWindow::getHWND(), "已经成功添加课程提醒！", "提示", MB_OK);
	}
	Sleep(100);
	return 7;
}

int MemoManager::deleteReminder(int i)
{
	int flag = MessageBox(MyWindow::getHWND(), "你确定要删除该课程的课程提醒吗？", "提示", MB_YESNO);
	if (flag == 6)
	{
		if (!subjectArray[i].set_have_reminder(false))MessageBox(MyWindow::getHWND(), "当前未添加课程提醒，无需删除！", "提示", MB_OK);
		else
		{
			save();
			MessageBox(MyWindow::getHWND(), "已经成功删除课程提醒！", "提示", MB_OK);
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
			if (v[i].get_m_text() == "添加课程")return -2;
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
			}//esc退出主界面
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
	t1.tm_year = SystemTime::getYear() - 1900; t1.tm_mon = SystemTime::getMonth() - 1; t1.tm_mday = SystemTime::getDay();//现在时间
	t2.tm_year = year - 1900; t2.tm_mon = month - 1; t2.tm_mday = day;//ddl时间
	seconds = difftime(mktime(&t2), mktime(&t1));//转换结构体为time_t,利用difftime,计算时间差  
	if (seconds == 0)return -1;
	return (int)(seconds / 86400);//最后输出时间,因为一天有86400秒(60*60*24)
}

MemoManager::~MemoManager()
{
	delete menu;
	delete schedule;
}