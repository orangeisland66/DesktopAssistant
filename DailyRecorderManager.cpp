#include "DailyRecorderManager.h"

#define FILENAME "./txts/DailyRecorder.txt"

DailyRecorderManager::DailyRecorderManager()
	:background(new IMAGE)
{
	MyWindow w;
	SystemTime t;
	fileInit();
	w = MyWindow(640, 680, EW_SHOWCONSOLE | EX_NOCLOSE);
	LOGFONT f;
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ
	w.setWindowTitle("С����");
	setbkmode(TRANSPARENT);
	setbkcolor(RGB(220, 220, 220));
	::loadimage(background, "./DailyRecorderImages/backgroundImage/background.jpg", background->getwidth(), background->getheight());//background
	//::loadimage(schedule, "./images/schedule.jpg", 348, 640);
	menu_btns.push_back(PushButton("��������¼"));
	menu_btns.push_back(PushButton("�鿴�����¼"));
	menu_btns.push_back(PushButton("ɾ�������¼"));
	menu_btns.push_back(PushButton("�˳�С����"));
	edit_btns.push_back(PushButton("��ӱ���"));
	edit_btns.push_back(PushButton("������д������������~"));
	edit_btns.push_back(PushButton("�༭���"));
	setPos(menu_btns);
	setPos(imageArray.second);
	setPos(recorderArray.second);
	edit_btnsSetPos();
	
	
}

void DailyRecorderManager::operator()()
{
	int op = 0;
	while (true)
	{
		MyWindow::beginDraw();
		cleardevice();
		drawBackground();
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
		case 0:
		{
			drawBackground();
			show_btns(menu_btns);
			op = -1;
		}
		case -1:op = menueventLoop(menu_btns); break;
		case 1:op = pictureChoosePage(); break;
		case 2:op = recordersSelectAndRecordersDeletePage(1); break; 
		case 3:op = recordersSelectAndRecordersDeletePage(2); break;
		case 4:goto flag;
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

void DailyRecorderManager::fileInit()
{
	intptr_t handle;//���ڲ��Ҿ��
	struct _finddata_t fileinfo;//�ļ���Ϣ�Ľṹ��
	handle = _findfirst("./DailyRecorderImages/ImagesToSelect/*.jpg", &fileinfo);//��һ�β���
	string FILENAME1 = "./DailyRecorderImages/ImagesToSelect/" + (string)fileinfo.name;
	do
	{
		IMAGE* temp = new IMAGE;
		string IMAGETOSELECT = "./DailyRecorderImages/ImagesToSelect/" + (string)fileinfo.name;
		::loadimage(temp, IMAGETOSELECT.c_str(), temp->getheight(), temp->getwidth());
		//cout << temp->getwidth() << temp->getheight();
		imageArray.first.push_back(make_pair(IMAGETOSELECT, temp));
		imageArray.second.push_back(PushButton(fileinfo.name));
	} while (!_findnext(handle, &fileinfo));
	_findclose(handle);//�����˹رվ��

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
	ifs.close();
	ifs.open(FILENAME, ios::in);
	string title, content, time, address;
	while (ifs >> title >> content >> time >> address)
	{

		recorderArray.first.push_back(DailyRecorder(title, content, address, time));
		//cout << title << address << time << content << endl;
		recorderArray.second.push_back(PushButton(title));
	}
	ifs.close();
	printf("��ʼ���ɹ���\n");
}

void DailyRecorderManager::setPos(vector<PushButton>& v)
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

int DailyRecorderManager::delete_(int i)
{
	int flag = MessageBox(MyWindow::getHWND(), "��ȷ��Ҫɾ���������¼��", "��ʾ", MB_YESNO);
	if (flag == 6)
	{
		recorderArray.first.erase(recorderArray.first.begin() + i);
		recorderArray.second.erase(recorderArray.second.begin() + i);
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc);
		for (vector<DailyRecorder>::iterator it = recorderArray.first.begin(); it != recorderArray.first.end(); it++)
		{
			ofs << (*it);
		}
		ofs.close();
		setPos(recorderArray.second);
		MessageBox(MyWindow::getHWND(), "ɾ���ɹ���", "��ʾ", MB_OK);
	}
	return 0;
}

int DailyRecorderManager::showRecorder(int i)//��ʾһ��DailyRecorder
{
	while (1)
	{

		if (isEsc())return 0;
		MyWindow::beginDraw();
		cleardevice();
		showEsc();
		recorderArray.first[i].show();
		MyWindow::endDraw();
	}
}

void DailyRecorderManager::show_btns(vector<PushButton>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		v[i].show(1);
	}
}

void DailyRecorderManager::drawBackground()
{
	::putimage(0, 0, background);
}

int DailyRecorderManager::menueventLoop(vector<PushButton>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		v[i].eventLoop(msg, 1);
		if (v[i].isClicked())
		{
			return i + 1;
		}
	}
	return -1;
}

int DailyRecorderManager::pictureChoosePage()
{
	int op = -1;
	Sleep(100);
	MyWindow::beginDraw();
	cleardevice();
	drawBackground();
	showEsc();
	show_btns(imageArray.second);
	MyWindow::endDraw();
	while (1)
	{
		if (isEsc())return 0;
		if (MyWindow::hasMsg())msg = MyWindow::getMsg();
		switch (op)
		{
		case 0:
		{
			MyWindow::beginDraw();
			cleardevice();
			drawBackground();
			showEsc();
			show_btns(imageArray.second);
			MyWindow::endDraw();
			Sleep(100);
			op = -1;
			break;
		}
		case -1:
		{
			op = menueventLoop(imageArray.second);
			break;
		}
		default:op = editPage(op - 1); break;
		}
	}
	return 0;
}

int DailyRecorderManager::recordersSelectAndRecordersDeletePage(int mode)
{
	int op = 0;
	Sleep(100);
	MyWindow::beginDraw();
	cleardevice();
	drawBackground();
	showEsc();
	show_btns(recorderArray.second);
	MyWindow::endDraw();
	while (1)
	{

		if (isEsc())return 0;
		if (MyWindow::hasMsg())msg = MyWindow::getMsg();
		switch (op)
		{
			//case -2:op = addSubject(); break;
		case -1:
		{
			op = menueventLoop(recorderArray.second);
			break;
		}
		case 0:
		{
			MyWindow::beginDraw();
			cleardevice();
			drawBackground();
			showEsc();
			show_btns(recorderArray.second);
			MyWindow::endDraw();
			Sleep(100);
			op = -1;
			break;
		}
		default:
		{
			if (mode == 1)op = showRecorder(op - 1);
			if (mode == 2)op = delete_(op - 1);
			break;
		}
		}
	}
	return 0;
}

bool DailyRecorderManager::isEsc()
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

void DailyRecorderManager::showEsc()
{
	settextcolor(BLACK);
	settextstyle(30, 0, ("΢���ź�"));
	outtextxy(550, 5, "Esc");
	settextstyle(18, 0, ("΢���ź�"));
	outtextxy(550, 30, "������һ��");
	settextcolor(WHITE);
}

int DailyRecorderManager::editPage(int i)
{
	int op = -1;
	MyWindow::beginDraw();
	cleardevice();
	show_btns(edit_btns);
	::putimage((MyWindow::width() - imageArray.first[i].second->getwidth()) / 2, 
		(MyWindow::height() - imageArray.first[i].second->getheight()) / 2, imageArray.first[i].second);
	MyWindow::endDraw();
	Sleep(100);
	char title[20] = { 0 }, content[1000] = { 0 };
	while (1)
	{
		//show_btns(imageArray.second);
		if (isEsc()||op==-2)
		{
			edit_btns[0].set_m_text("��ӱ���");
			edit_btns[1].set_m_text("������д������������~");
			edit_btnsSetPos();
			isWrite[0] = false;
			isWrite[1] = false;
			return 0;
		}
		if (MyWindow::hasMsg())msg = MyWindow::getMsg();
			switch (op)
			{
			case 0:
			{
				draw(title,content);
				::putimage((MyWindow::width() - imageArray.first[i].second->getwidth()) / 2,
					(MyWindow::height() - imageArray.first[i].second->getheight()) / 2, imageArray.first[i].second);
				show_btns(edit_btns);
				MyWindow::endDraw();
				Sleep(100);
				op = -1;
				break;
			}
			case -1:
			{
				op = menueventLoop(edit_btns);
				break;
			}
			case 1:
			{
				op = edit(op, title, content,i);
				if (op == 0)
				{
					edit_btns[0].set_m_text("�޸ı���");
					edit_btns[0].move(0, 50);
					edit_btns[0].setFixedSize(100, 30);
					isWrite[0] = true;
				}
				if (op == -1)
				{
					op = 0;
					edit_btns[0].set_m_text("��ӱ���");
					edit_btns[0].setFixedSize(200, 60);
					edit_btns[0].move((MyWindow::width() - edit_btns[0].width()) / 2, 50);
					isWrite[0] = false;
				}
				break;
			}
			case 2:
			{
				op = edit(op, title, content,i);
				if (op == 0)
				{
					edit_btns[1].set_m_text("�޸�");
					edit_btns[1].move(20, 550);
					edit_btns[1].setFixedSize(50, 30);
					isWrite[1] = true;
				}
				if (op == -1)
				{
					op = 0;
					edit_btns[1].set_m_text("������д������������~");
					edit_btns[1].setFixedSize(200, 60);
					edit_btns[1].move((MyWindow::width() - edit_btns[1].width()) / 2, 550);
					isWrite[1] = false;
				}
				break;
			}
			case 3:op = edit(op, title, content,i);
			}
	}

	return 0;
}
void DailyRecorderManager::draw(char title[],char content[])
{
	MyWindow::beginDraw();
	cleardevice();
	settextcolor(BLACK);
	settextstyle(50, 0, ("΢���ź�"));
	int tx1, ty1, tx2, ty2;
	tx1 = (MyWindow::width() - textwidth(title)) / 2;
	ty1 = 50;
	outtextxy(tx1, ty1, title);
	settextstyle(22, 0, ("����"));
	tx2 = 100;
	ty2 = 500;
	setfillcolor(WHITE);
	if (isWrite[1])fillrectangle(tx2, ty2, 540, 630);
	string temp1 = content;
	string temp2;
	int size = (int)strlen(content), cnt = 0;
	for (int i = 0; i < size; i++)
	{
		if (((int)temp1[i] < 0))//����Ƿ�Ϊ�����ַ�
		{
			temp2 += temp1[i++];
			temp2 += temp1[i];
		}
		else temp2 += temp1[i];
		if (textwidth(temp2.c_str()) >= 420)
		{
			outtextxy(tx2, ty2 + cnt * 22, temp2.c_str());
			temp2.clear();
			cnt++;
		}
		if (i == size - 1 && !temp2.empty())outtextxy(tx2, ty2 + cnt * 22, temp2.c_str());
	}
	settextcolor(WHITE);
	settextstyle(18, 0, ("΢���ź�"));

}
int DailyRecorderManager::edit(int mode, char* title,char* content,int i)
{
	switch (mode)
	{
	case 1:
	{
		bool isInput = InputBox(title, 20, "��������⣺", "�������(10�����ڣ�", NULL, 0, 0, false);
		if (strlen(title)!=0)return 0;
		break;
	}
	case 2:
	{
		bool isInput = InputBox(content, 1000, "�������������", "��д���ݣ�200�����ڣ�", NULL, 0, 0, false);
		if (strlen(content)!=0)return 0;
		break;
	}
	case 3:
	{
		if (!isWrite[0])
		{
			MessageBox(MyWindow::getHWND(), "���ⲻ��Ϊ��Ŷ~", "��ʾ", MB_OK);
			return 0;
		}
		if (!isWrite[1])
		{
			MessageBox(MyWindow::getHWND(), "���������Ϊ��Ŷ~", "��ʾ", MB_OK);
			return 0;
		}
		SystemTime::getSystemTime();
		char time[100];
		strftime(time, sizeof(time), "%Y��%m��%d��%H:%M:%S", SystemTime::get_tm_info());
		recorderArray.first.push_back(DailyRecorder(title, content, imageArray.first[i].first, time));
		recorderArray.second.push_back(PushButton(title));
		setPos(recorderArray.second);
		ofstream ofs;
		ofs.open(FILENAME, ios::app);
		ofs << title << " " << content << " " << time<<" "<<imageArray.first[i].first << endl;
		ofs.close();
		MessageBox(MyWindow::getHWND(), "��ӳɹ���", "��ʾ", MB_OK);
		return -2;
	}
	}
	return -1;
}

void DailyRecorderManager::edit_btnsSetPos()
{
	edit_btns[0].setFixedSize(200, 60);
	edit_btns[1].setFixedSize(200, 60);
	edit_btns[0].move((MyWindow::width() - edit_btns[0].width()) / 2, 50);
	edit_btns[1].move((MyWindow::width() - edit_btns[1].width()) / 2, 550);
	edit_btns[2].move(MyWindow::width() - edit_btns[2].width()-20 , 50);
}

DailyRecorderManager::~DailyRecorderManager()
{
	delete background;
	for (int i = 0; i < imageArray.first.size(); i++)
	{
		delete imageArray.first[i].second;
	}
}

