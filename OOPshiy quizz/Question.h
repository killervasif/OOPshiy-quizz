#pragma once
namespace QuizReleated {
	using namespace FunctionReleated;
	class Question
	{
		vector<Answer*> _answers;
		string _question = "";
		Answer* _currentAnswer = nullptr;

	public:
		short answerIndex = 0;

		Question() = default;
		Question(const Question& q) = default;
		Question(Question&& q) noexcept {
			q._answers.swap(_answers);
			for (auto& answer : _answers)
				answer = nullptr;
			q._question.assign(_question);
			q._currentAnswer = _currentAnswer;
			_currentAnswer = nullptr;
		}
		Question(string question) :_question(question) {}

		Question& operator=(const Question& q) {
			_answers.assign(q._answers.begin(), q._answers.end());
			_question = q._question;
			_currentAnswer = new Answer(*q._currentAnswer);
			return *this;
		}
		Question& operator=(Question&& q) noexcept {
			q._answers.swap(_answers);
			q._question.assign(_question);
			q._currentAnswer = _currentAnswer;
			_currentAnswer = nullptr;
			return *this;
		}

		vector<Answer*>& answers() { return _answers; }
		string question() { return _question; }
		Answer*& currentAnswer() { return _currentAnswer; }

		void setQuestion(const string& question) {
			if (question.size() < 3)
				throw exception("Question too short");
			_question = question;
		}

		void addAnswer(Answer* answer) {
			if (answer == nullptr)
				throw exception("Answer not found");
			_answers.push_back(answer);
		};

		friend ostream& operator<<(ostream& out, const Question& q);

		~Question()
		{
			for (auto& answer : _answers)
			{
				delete answer;
				answer = nullptr;
			}
			delete _currentAnswer;
		}
	};

	ostream& operator<<(ostream& out, const Question& q)
	{
		mySetColor(7, 0);
		out << q._question << endl;
		for (size_t i = 0; i < q._answers.size(); i++)
		{
			if (i == q.answerIndex)
			{
				mySetColor(0, 7);
				out << *q._answers[i] << endl;
				mySetColor(7, 0);
				continue;
			}
			out << *q._answers[i] << endl;
		}
		mySetColor(7, 0);
		if (q._currentAnswer != nullptr)
			out << "\nCurrent Answer: " << *q._currentAnswer << endl;
		return out;
	}
}