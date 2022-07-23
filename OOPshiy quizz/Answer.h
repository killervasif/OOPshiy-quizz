#pragma once
namespace QuizReleated {
	class Answer
	{
		string _answer = "";
		bool _isCorrect = false;
	public:
		Answer() = default;
		Answer(string answer, bool isCorrect) : _isCorrect(isCorrect) {
			setAnswer(answer);
		}

		string answer() const { return _answer; }
		bool isCorrect() const { return _isCorrect; }
		void setAnswer(const string& answer) {
			if (answer == "")
				throw exception("Answer is empty");
			_answer = answer;
		}
	};

	ostream& operator<<(ostream& out, const Answer& a)
	{
		return out << a.answer() << ' ';
	}
}