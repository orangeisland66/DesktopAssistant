#pragma once
#include"header.h"
void ShowMainMenu();
void ShowAccountBookMenu();
void ShowStudyRecorderMenu();
void ShowPasswordRecorderMenu();
void Pause_and_Cls();

class MenuManager
{
public:
	MenuManager(int mode);
	void Refresh(void (*p)());
	void operator()();
private:
	int mode;
};

