#include "DailyRecorder.h"
DailyRecorder::DailyRecorder(string title, string content,string address, string time):
	title(title),content(content),address(address),time(time)
{
	image = new IMAGE;
	::loadimage(image, address.c_str(), image->getwidth(), image->getheight());
}

void DailyRecorder::show()
{
	putimage(0, (MyWindow::height() - this->image->getheight()) / 2, this->image);
	settextcolor(BLACK);
	settextstyle(50, 0, ("Œ¢»Ì—≈∫⁄"));
	int tx1, ty1, tx2, ty2;
	tx1 = 200 + (MyWindow::width() - textwidth(title.c_str())) / 2;
	ty1 = 50;
	outtextxy(tx1, ty1, title.c_str());
	settextstyle(30, 0, ("Œ¢»Ì—≈∫⁄"));
	outtextxy(30, 20, time.c_str());
	settextstyle(22, 0, ("–– È"));
	//cout << this->image->getwidth() << endl;
	if (this->image->getwidth() < 400)
	{
		tx2 = this->image->getwidth() + 20;
		ty2 = 150;
		setfillcolor(WHITE);
		fillrectangle(tx2, ty2, MyWindow::width() - 20, MyWindow::height() - 100);
	}
	else
	{
		tx2 = 100;
		ty2 = 500;
		setfillcolor(WHITE);
		fillrectangle(100, 500, 540, 630);
	}
	string temp1 = content;
	string temp2;
	int size = (int)content.size(), cnt = 0;
	for (int i = 0; i < size; i++)
	{
		if (((int)temp1[i] < 0))//ºÏ≤‚ «∑ÒŒ™÷–Œƒ◊÷∑˚
		{
			temp2 += temp1[i++];
			temp2 += temp1[i];
		}
		else temp2 += temp1[i];
		if (textwidth(temp2.c_str()) >= (this->image->getwidth() < 400 ? MyWindow::width() - tx2 - 40 : 420))
		{
			outtextxy(tx2, ty2 + cnt * 22, temp2.c_str());
			temp2.clear();
			cnt++;
		}
		if (i == size - 1 && !temp2.empty())outtextxy(tx2, ty2 + cnt * 22, temp2.c_str());
	}
	settextcolor(WHITE);
	settextstyle(18, 0, ("Œ¢»Ì—≈∫⁄"));
}

DailyRecorder::~DailyRecorder()
{
}

ofstream& operator<<(ofstream& ofs, DailyRecorder da)
{
	ofs << da.title << " " << da.content << " " << da.time << " " << da.address << endl;
	return ofs;
}
