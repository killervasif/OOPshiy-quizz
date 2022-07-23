#include <iostream>
#include <fstream>
#include <conio.h>
#include <Windows.h>
#include <string> 
#include <vector>
#include <algorithm>
using namespace std;
#include "User.h"
#include "Admin.h"
#include "Functions.h"
#include "Answer.h"
#include "Question.h"
#include "Quiz.h"
#include "Options.h"
#include "QuizFunctions.h"
#include "FileHandling.h"
using namespace UserReleated;
using namespace QuizReleated;
using namespace FunctionReleated;
string adminEnterance = "Kelem";
void main()
{
	srand(time(0));
	enum names { Quizes, Admins, Users };
	vector<string> files = { "Quizes.txt","Admins.txt","Users.txt" };
	vector<Quiz*> quizes;
	vector<Admin*> admins;
	vector<User*> users;

	try {
		quizes = loadQuizes(files[names::Quizes]);
	}
	catch(...){ }
	try {
		admins = loadAdmins(files[names::Admins]);
	}
	catch(...){ }
	try{
		users = loadUsers(files[names::Users]);
	}
	catch (...) { }
	Options starts;
	starts.options.push_back("Start");
	starts.options.push_back("Controls");
	starts.options.push_back("Exit");
	bool exit = false;
	bool choice;
	system("cls");
	while (!exit) {
	start:
		setCursor();
		cout << starts;
		choice = optionCursor(starts);
		if (choice)
		{
			switch (starts.optionIndex)
			{
			case 0:

				exit = true;
				break;

			case 1:
				system("cls");
				controls();
				system("pause");
				system("cls");
				break;

			case 2:
				system("cls");
				cout << "Cya";
				return ;
				break;
			}
		}
	}

	Options start;
	start.options.push_back("Sign up");
	start.options.push_back("Sign in");
	start.options.push_back("Continue as a Guest");
	start.options.push_back("Back");

	Options signUp;
	signUp.options.push_back("Sign up as Player");
	signUp.options.push_back("Sign up as Admin");
	signUp.options.push_back("Back");

	Options signIn;
	signIn.options.push_back("Sign in as Player");
	signIn.options.push_back("Sign in as Admin");
	signIn.options.push_back("Back");

	string name;
	string password;
	string adminLogIn;
	User* currentUser = nullptr;
	Admin* currentAdmin = nullptr;

	bool isAdmin = false;
	bool isGuest = false;
	bool back = false;
	
	exit = false;
	while (!exit)
	{
		setCursor();
		cout << start;
		choice = optionCursor(start);
		if (choice)
		{
			switch (start.optionIndex)
			{
			case 0:
				system("cls");
				while (!back)
				{
					enterance:
					setCursor();
					cout << signUp;
					choice = optionCursor(signUp);
					if (choice)
					{
						switch (signUp.optionIndex)
						{
						case 0:
							system("cls");
							cout << "Enter name: ";
							getline(cin, name);
							cout << "\nEnter  password: ";
							getline(cin, password);

							if (checkName(users, admins, name))
							{
								cout << "\nThis name already exists\n";
								system("pause");
								system("cls");
								continue;
							}

							try
							{
								currentUser = new User(name, password);
								users.push_back(currentUser);
							}
							catch (const exception& ex)
							{
								cout << ex.what() << endl;
								system("pause");
								system("cls");
								continue;
							}

							exit = true;
							back = true;
							break;

						case 1:
							cout << "Admin pass: ";
							getline(cin, adminLogIn);
							if (adminLogIn != adminEnterance)
							{
								cout << "You're not qualified\n";
								Sleep(2000);
								system("pause");
								system("cls");
								goto enterance;
							}
							Sleep(1000);
							system("cls");
							cout << "Enter name: ";
							getline(cin, name);
							cout << "\nEnter password: ";
							getline(cin, password);

							if (checkName(users, admins, name))
							{
								cout << "\nThis name already exists\n";
								system("pause");
								system("cls");
								continue;
							}
							try
							{
								currentAdmin = new Admin(name, password);
								isAdmin = true;
								admins.push_back(currentAdmin);
							}
							catch (const std::exception& ex)
							{
								cout << ex.what() << endl;
								system("pause");
								system("cls");
								continue;
							}

							exit = true;
							back = true;
							break;

						case 2:
							back = true;
						}
					}
				}

				back = false;
				break;

			case 1:
				system("cls");
				while (!back)
				{
					setCursor();
					cout << signIn;
					choice = optionCursor(signIn);
					if (choice)
					{
						switch (signIn.optionIndex)
						{
						case 0:
							system("cls");
							cout << "Enter name: ";
							getline(cin, name);
							cout << "\nEnter password: ";
							getline(cin, password);

							currentUser = findUser(users, name, password);
							if (currentUser == nullptr)
							{
								cout << "No player found\n";
								system("pause");
								system("cls");
								continue;
							}

							back = true;
							exit = true;
							break;

						case 1:
							system("cls");
							cout << "Enter name: ";
							getline(cin, name);
							cout << "\nEnter password: ";
							getline(cin, password);
							currentAdmin = findAdmin(admins, name, password);
							if (currentAdmin == nullptr)
							{
								cout << "Admin not found\n";
								system("pause");
								system("cls");
								continue;
							}
							isAdmin = true;
							back = true;
							exit = true;
							break;
						case 2:
							back = true;
						}
					}
				}
				back = false;
				break;
			case 2:
				isGuest = true;
				exit = true;
				break;
			case 3:
				goto start;
			}
		}
	}
	back = false;
	exit = false;

	Quiz* currentQuiz = nullptr;
	Quiz* tempQuiz = nullptr;

	Options quizNames;
	quizNames.options.push_back("Exit\n");

	Options adminMenu;
	adminMenu.options.push_back("Create ");
	adminMenu.options.push_back("Play ");
	adminMenu.options.push_back("See all Players Results");
	adminMenu.options.push_back("Exit");

	Options userMenu;
	userMenu.options.push_back("Play ");
	userMenu.options.push_back("See all Players Results");
	userMenu.options.push_back("Exit");

	Options guestMenu;
	guestMenu.options.push_back("Play Quiz");
	guestMenu.options.push_back("Exit");

	Options afterQuiz;
	afterQuiz.options.push_back("See the score");
	afterQuiz.options.push_back("Save statistics");
	afterQuiz.options.push_back("Exit");



	if (isAdmin)
	{
		system("cls");
		while (!exit)
		{
			showQuizChoices(quizNames, quizes);
			setCursor();
			cout << adminMenu;
			choice = optionCursor(adminMenu);
			if (choice)
			{
				switch (adminMenu.optionIndex)
				{
				case 0:
					try
					{
						tempQuiz = createQuiz(currentAdmin->name());
					}
					catch (const exception& ex)
					{
						cout << ex.what() << endl;
						system("pause");
						system("cls");
						continue;
					}
					if (tempQuiz == nullptr)
						continue;
					quizes.push_back(new Quiz(*tempQuiz));
					break;
				case 1:
					system("cls");
					while (!back)
					{
						if (quizes.size() == 0)
						{
							cout << "No quiz found\n";
							system("pause");
							system("cls");
							break;
						}
						setCursor();
						cout << quizNames;
						choice = optionCursor(quizNames);
						if (choice)
						{
							if (quizNames.optionIndex == 0)
								break;
							currentQuiz = findQuiz(quizes, quizNames.options[quizNames.optionIndex]);

							currentQuiz->shuffle();
							currentQuiz = playQuiz(currentQuiz);
							system("cls");
							while (!back)
							{
								setCursor();
								cout << afterQuiz;
								choice = optionCursor(afterQuiz);
								if (choice)
								{
									switch (afterQuiz.optionIndex)
									{
									case 0:
										system("cls");
										currentAdmin->setScore(currentQuiz->score());
										cout << "Your score is: " <<currentAdmin->score() << " pts.\n";
										system("pause");
										system("cls");
										break;
									case 1:
										try
										{
											currentAdmin->setScore(currentQuiz->score());
										}
										catch (const std::exception& ex)
										{
											system("cls");
											cout << ex.what() << endl;
											system("pause");
											system("cls");
											continue;
										}
										system("cls");
										cout << "Saved succesfully";
										system("pause");
										system("cls");
										break;
									case 2:
										back = true;
									}
								}
							}
							back = false;
						}
					}

					break;

				case 2:
					system("cls");
					seeAllResults(admins, users);
					system("pause");
					system("cls");
					break;

				case 3:
					system("cls");
					cout << "Cya\n";
					Sleep(2500);
					exit = true;
				}
			}
			quizNames.options.clear();
			quizNames.options.push_back("Exit\n");
		}
	}

	else if (isGuest)
	{
		system("cls");
		while (!exit)
		{
			showQuizChoices(quizNames, quizes);
			setCursor();
			cout << guestMenu;
			choice = optionCursor(guestMenu);
			if (choice)
			{
				switch (guestMenu.optionIndex)
				{
				case 0:
					system("cls");
					while (!back)
					{
						if (quizes.size() == 0)
						{
							cout << "No quizes found\n";
							system("pause");
							system("cls");
							break;
						}
						setCursor();
						cout << quizNames;
						choice = optionCursor(quizNames);
						if (choice)
						{
							if (quizNames.optionIndex == 0)
								break;
							currentQuiz = findQuiz(quizes, quizNames.options[quizNames.optionIndex]);

							currentQuiz->shuffle();
							currentQuiz = playQuiz(currentQuiz);
							system("cls");
							while (!back)
							{
								setCursor();
								cout << afterQuiz;
								choice = optionCursor(afterQuiz);
								if (choice)
								{
									switch (afterQuiz.optionIndex)
									{
									case 0:
										system("cls");
										cout << "Your score is: " << currentQuiz->score() << "\n";
										system("pause");
										system("cls");
										break;

									
									case 1:
										system("cls");
										cout << "You need to sign up for saving your progress";
										system("pause");
										system("cls");
										break;

									case 2:
										back = true;
									}
								}
							}
							back = false;
						}
					}
					break;

				case 1:
					system("cls");
					cout << "Cya\n";
					Sleep(2500);
					exit = true;

				}
			}
			quizNames.options.clear();
			quizNames.options.push_back("Exit\n");
		}
	}

	else
	{
		system("cls");
		while (!exit)
		{
			showQuizChoices(quizNames, quizes);
			setCursor();
			cout << userMenu;
			choice = optionCursor(userMenu);
			if (choice)
			{
				switch (userMenu.optionIndex)
				{
				case 0:
					system("cls");
					while (!back)
					{
						if (quizNames.options.size() == 0)
						{
							cout << "No quiz found\n";
							system("pause");
							system("cls");
							break;
	
						}
						setCursor();
						cout << quizNames;
						choice = optionCursor(quizNames);
						if (choice)
						{
							if (quizNames.optionIndex == 0)
								break;
							currentQuiz = findQuiz(quizes, quizNames.options[quizNames.optionIndex]);

							currentQuiz->shuffle();
							currentQuiz = playQuiz(currentQuiz);
							system("cls");
							while (!back)
							{
								setCursor();
								cout << afterQuiz;
								choice = optionCursor(afterQuiz);
								if (choice)
								{
									switch (afterQuiz.optionIndex)
									{
									case 0:
										system("cls");
										cout << "Your score is: " << currentQuiz->score() << "\n";
										system("pause");
										system("cls");
										break;

									case 1:
										try
										{
											currentUser->setScore(currentQuiz->score());
										}
										catch (const std::exception& ex)
										{
											system("cls");
											cout << ex.what() << endl;
											system("pause");
											system("cls");
											continue;
										}

										system("cls");
										cout << "Succesfylly saved";
										system("pause");
										system("cls");
										break;

									case 2:
										back = true;
									}
								}
							}
							back = false;
						}
					}

					break;

				case 1:
					system("cls");
					seeAllResults(admins, users);
					system("pause");
					system("cls");
					break;

				case 2:
					system("cls");
					cout << "Cya\n";
					Sleep(2500);
					exit = true;
				}
			}
			quizNames.options.clear();
			quizNames.options.push_back("Exit\n");
		}
	}
	saveAdmins(files[names::Admins], admins);
	saveUsers(files[names::Users], users);
	saveQuizes(files[names::Quizes], quizes);

	for (auto& admin : admins)
		delete admin;
	for (auto& user : users)
		delete user;
	for (auto& quiz : quizes)
		delete quiz;
}
