#pragma once
namespace FunctionReleated {
	using namespace UserReleated;
	using namespace QuizReleated;
	void writeAnswer(fstream& stream, Answer* a)
	{
		if (!stream)
			throw exception("Cannot create ");
		if (!stream.is_open())
			throw exception("Cannot open ");
		stream << a->answer() << endl << a->isCorrect() << endl;
		return;
	}

	Answer* readAnswer(fstream& stream)
	{
		string answer;
		bool isCorrect;
		if (!stream)
			throw exception("Cannot create ");
		if (!stream.is_open())
			throw exception("Cannot open ");
		getline(stream, answer);
		stream >> isCorrect;
		stream.ignore();
		return new Answer(answer, isCorrect);
	}

	void writeQuesetion(fstream& stream, Question* q)
	{
		if (!stream)
			throw exception("Cannot create ");
		if (!stream.is_open())
			throw exception("Cannot open ");
		stream << q->question() << endl << q->answers().size() << endl;;
		for (auto& answer : q->answers())
			writeAnswer(stream, answer);
	}

	Question* readQuestion(fstream& stream)
	{
		if (!stream)
			throw exception("Cannot create ");
		if (!stream.is_open())
			throw exception("Cannot open ");
		string question;
		getline(stream, question);
		size_t answersCount;
		stream >> answersCount;
		stream.ignore();
		Question* q = new Question(question);
		for (size_t i = 0; i < answersCount; i++)
			q->addAnswer(readAnswer(stream));
		return q;
	}

	void writeQuiz(fstream& stream, Quiz* quiz)
	{
		if (!stream)
			throw exception("Cannot create ");
		if (!stream.is_open())
			throw exception("Cannot open ");
		stream << quiz->name() << endl << quiz->author() << endl;
		stream << quiz->questions().size() << endl;
		for (auto& question : quiz->questions())
			writeQuesetion(stream, question);
	}

	Quiz* readQuiz(fstream& stream)
	{
		if (!stream)
			throw exception("Cannot create ");
		if (!stream.is_open())
			throw exception("Cannot open ");
		string name, author;
		size_t questionCount;
		getline(stream, name);
		getline(stream, author);
		Quiz* quiz = new Quiz(name, author);
		stream >> questionCount;
		stream.ignore();
		for (size_t i = 0; i < questionCount; i++)
			quiz->addQuestion(readQuestion(stream));
		return quiz;
	}

	vector<Quiz*> loadQuizes(string file)
	{
		fstream stream(file, ios::in);
		vector<Quiz*> quizes;
		if (!stream || !stream.is_open() || stream.peek() == 10)
			return quizes;
		size_t quizCount;
		stream >> quizCount;
		stream.ignore();
		for (size_t i = 0; i < quizCount; i++)
			quizes.push_back(readQuiz(stream));
		return quizes;
	}

	void saveQuizes(string file, vector<Quiz*>& quizes)
	{
		fstream stream(file, ios::out);
		if (!stream)
			throw exception("Cannot create ");
		if (!stream.is_open())
			throw exception("Cannot open ");
		stream.seekg(0);
		stream << quizes.size() << endl;
		for (auto& quiz : quizes)
			writeQuiz(stream, quiz);
	}





void writeUser(fstream& stream, User* u)
{
	if (!stream)
		throw exception("Cannot create ");
	if (!stream.is_open())
		throw exception("Cannot open ");
	stream << u->name() << endl
		<< u->password() << endl
		<< u->score() << endl;
}

User* readUser(fstream& stream)
{
	if (!stream)
		throw exception("Cannot create ");
	if (!stream.is_open())
		throw exception("Cannot open ");
	string name;
	string pass;
	size_t score;
	getline(stream, name);
	getline(stream, pass);
	stream >> score;
	User* u = new User(name, pass);
	u->setScore(score);
	return u;
}

vector<User*> loadUsers(string file)
{
	fstream stream(file, ios::in);
	vector<User*> users;
	if (!stream || !stream.is_open() || stream.peek() == 10)
		return users;
	size_t usersCount;
	stream >> usersCount;
	stream.ignore();
	for (size_t i = 0; i < usersCount; i++)
		users.push_back(readUser(stream));
	return users;
}

void saveUsers(string file, vector<User*> users)
{
	fstream stream(file, ios::out);
	if (!stream)
		throw exception("Cannot create ");
	if (!stream.is_open())
		throw exception("Cannot open ");
	stream << users.size() << endl;
	for (auto& user : users)
		writeUser(stream, user);
}

void writeAdmin(fstream& stream, Admin* u)
{
	if (!stream)
		throw exception("Cannot create ");

	if (!stream.is_open())
		throw exception("Cannot open ");

	stream << u->name() << endl
		<< u->password() << endl
		<< u->score() << endl;
}

Admin* readAdmin(fstream& stream)
{
	if (!stream)
		throw exception("Cannot create ");
	if (!stream.is_open())
		throw exception("Cannot open ");
	string name;
	string pass;
	float score;
	getline(stream, name);
	getline(stream, pass);
	stream >> score;
	Admin* u = new Admin(name, pass);
	u->setScore(score);
	return u;
}

vector<Admin*> loadAdmins(string file)
{
	fstream stream(file, ios::in);
	vector<Admin*> admins;
	if (!stream || !stream.is_open() || stream.peek() == 10)
		return admins;
	size_t playersCount;
	stream >> playersCount;
	stream.ignore();
	for (size_t i = 0; i < playersCount; i++)
		admins.push_back(readAdmin(stream));
	return admins;
}

void saveAdmins(string file, vector<Admin*> admins)
{
	fstream stream(file, ios::out);
	if (!stream)
		throw exception("Cannot create ");
	if (!stream.is_open())
		throw exception("Cannot open ");
	stream << admins.size() << endl;
	for (auto& admin : admins)
		writeAdmin(stream, admin);
}
}