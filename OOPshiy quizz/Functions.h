#pragma once
namespace FunctionReleated {
	using namespace UserReleated;
	void setCursor(int x = 0, int y = 0)
	{
		static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		cout.flush();
		COORD coord = { (SHORT)x, (SHORT)y };
		SetConsoleCursorPosition(hOut, coord);
	}

	void mySetColor(int fg, int bg)
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, fg | (bg << 4));
	}

	void controls() {
		cout << "Left and right arrow to move between questions\n"
			<< "Up and down arrows to move between answers\n"
			<< "Enter button to accept answer\n"
			<< "S button to submit quiz\n";
	}
}