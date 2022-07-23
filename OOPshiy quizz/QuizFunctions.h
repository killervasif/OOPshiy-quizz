#pragma once
namespace FunctionReleated {
	using namespace UserReleated;
	using namespace QuizReleated;
	bool quizCursor(Quiz& q, int& button)
	{
		vector<Question*> temp = q.questions();
		short& answerIndex = temp[q.questionIndex]->answerIndex;
		if (button == 224)
		{
			button = _getch();
			switch (button)
			{
			case 72:
				setCursor();
				answerIndex--;
				if (answerIndex < 0) answerIndex = temp[q.questionIndex]->answers().size() - 1;
				break;
			case 80:
				setCursor();
				temp[q.questionIndex]->answerIndex++;
				if (answerIndex >= temp[q.questionIndex]->answers().size()) answerIndex = 0;
				break;
			case 75:
				system("cls");
				q.questionIndex--;
				if (q.questionIndex < 0) q.questionIndex = temp.size() - 1;
				break;
			case 77:
				system("cls");
				q.questionIndex++;
				if (q.questionIndex >= temp.size()) q.questionIndex = 0;
				break;
			}
			return false;
		}
		else if (button == 13)
		{
			system("cls");
			q.questions()[q.questionIndex]->currentAnswer()
				= temp[q.questionIndex]->answers()[answerIndex];
			return true;
		}
		else
		{
			setCursor();
			return false;
		}
	}


	bool optionCursor(Options& o)
	{
		int button = _getch();
		if (button == 224)
		{
			button = _getch();

			switch (button)
			{
			case 72:
				o.optionIndex--;
				if (o.optionIndex < 0) o.optionIndex = o.options.size() - 1;
				break;
			case 80:
				o.optionIndex++;
				if (o.optionIndex >= o.options.size()) o.optionIndex = 0;
				break;
			}
			return false;
		}
		else if (button == 13)
		{
			system("cls");
			return true;
		}
		else
		{
			setCursor();
			return false;
		}
	}


	Quiz* createQuiz(string author)
	{
		string name;
		mySetColor(7, 0);
		cout << "Enter the name of the Quiz: ";
		getline(cin, name);
		system("cls");
		if (name == "")
			throw exception("Quiz name Cannot be empty");

		Options questionOptions;
		questionOptions.options.push_back("Add Question");
		questionOptions.options.push_back("Accept All Questions");
		questionOptions.options.push_back("Back");

		Options answerOptions;
		answerOptions.options.push_back("Add Answer");
		answerOptions.options.push_back("Accept All Answers");
		answerOptions.options.push_back("Back");

		Options TrueOrFalse;
		TrueOrFalse.options.push_back("True");
		TrueOrFalse.options.push_back("False");

		Quiz* tempQuiz;
		try
		{
			tempQuiz = new Quiz(name, author);
		}
		catch (const exception& ex)
		{
			cout << ex.what() << endl;
			throw exception(ex);
		}

		bool choice = false;
		bool isCorrect = false;
		bool exit = false;

		Question* tempQuestion = nullptr;
		string question;
		string answer;

		while (!exit)
		{
			setCursor();
			cout << questionOptions;
			choice = optionCursor(questionOptions);
			if (choice)
			{
				switch (questionOptions.optionIndex)
				{
				case 0:
					cout << "Enter Question Text: ";
					getline(cin, question);
					try {
						tempQuestion = new Question(question);
					}
					catch (const exception& ex)
					{
						cout << ex.what() << endl;
						system("pause");
						system("cls");
						continue;
					}
					system("cls");
					while (!exit)
					{
						setCursor();
						cout << answerOptions;
						choice = optionCursor(answerOptions);
						if (choice)
						{
							switch (answerOptions.optionIndex)
							{
							case 0:
								cout << "Enter Answer Text: ";
								getline(cin, answer);
								system("cls");
								while (true)
								{
									setCursor();
									cout << "Is Answer True or False?" << endl;
									cout << TrueOrFalse;
									choice = optionCursor(TrueOrFalse);
									if (choice) break;
								}
								switch (TrueOrFalse.optionIndex)
								{
								case 0:
									tempQuestion->addAnswer(new Answer(answer, 1));
									break;
								case 1:
									tempQuestion->addAnswer(new Answer(answer, 0));
									break;
								}
								break;
							case 1:
								exit = true;
								break;
							case 2:
								delete tempQuestion;
								tempQuestion = nullptr;
								exit = true;
							}
						}
					}
					if (tempQuestion != nullptr)
						tempQuiz->addQuestion(tempQuestion);
					exit = false;
					break;
				case 1:
					exit = true;
					break;
				case 2:
					return nullptr;
					break;
				}
			}
		}
		return tempQuiz;
	}

	bool checkName(vector<User*> users, vector<Admin*> admins, const string& name)
	{
		for (auto& user : users)
			if (user->name() == name)
				return true;

		for (auto& admin : admins)
			if (admin->name() == name)
				return true;

		return false;
	}

	User* findUser(vector<User*> users, const string& name, const string& pass)
	{
		for (auto& user : users)
			if (user->name() == name && user->password() == pass)
				return user;
		return nullptr;
	}

	Admin* findAdmin(vector<Admin*> admins, const string& name, const string& pass)
	{
		for (auto& admin : admins)
			if (admin->name() == name && admin->password() == pass)
				return admin;
		return nullptr;
	}

	void seeAllResults(vector<Admin*> admins, vector<User*> users)
	{
		for (auto& admin : admins)
			cout << *admin << endl;
		for (auto& user : users)
			cout << *user << endl;
	}

	void showQuizChoices(Options& names, vector<Quiz*> quizes)
	{
		for (auto& quiz : quizes)
			names.options.push_back(quiz->name());
	}

	Quiz* findQuiz(vector<Quiz*> quizes, string name)
	{
		for (auto& quiz : quizes)
		{
			if (quiz->name() == name)
				return new Quiz(*quiz);
		}
		return nullptr;
	}

	Quiz* playQuiz(Quiz*& quiz)
	{
		bool submit = false;
		bool choice = false;
		int button;
		while (!submit)
		{
			cout << *quiz->questions()[quiz->questionIndex];
			cout << "\n press S to submit";
			button = _getch();
			choice = quizCursor(*quiz, button);
			if (choice)
			{
				continue;
			}
			if (button == 83 || button == 115)
				submit = true;
		}
		quiz->checkAnswers();

		quiz->calculateScore();
		return quiz;
	}
}