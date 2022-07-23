#pragma once
namespace QuizReleated {
	class Quiz
	{
		vector<Question*> _questions;
		string _name = "";
		string _author = "";
		size_t _rightCount = 0;
		size_t _wrongCount = 0;
		size_t _score = 0;

		bool check(const vector<Question*>& questions, Question* q) {
			for (auto& question : questions)
				if (question == q)
					return true;
			return false;
		};
	public:
		short questionIndex = 0;

		Quiz(string name, string author) : _name(name), _author(author) {};

		string name() const { return _name; };
		string author() const { return _author; };
		vector<Question*>& questions() { return _questions; }
		size_t trues() { return _rightCount; }
		size_t falses() { return _wrongCount; }
		size_t maxScore() { return _questions.size() * 10; }
		size_t score() { return _score; }
		void addQuestion(Question* q) {
			if (q == nullptr)
				throw exception("Question not found");
			_questions.push_back(q);
		};

		void shuffle()
		{
			for (auto& q : _questions)
				random_shuffle(q->answers().begin(), q->answers().end());
			random_shuffle(_questions.begin(), _questions.end());
		}

		void checkAnswers() {

			for (auto& q : _questions)
			{
				if (q->currentAnswer() != nullptr)
				{
					if (q->currentAnswer()->isCorrect())
					{
						_rightCount++;
					}
					else
					{
						_wrongCount++;
					}
				}
			}

		};

		void calculateScore() {
			if (_rightCount + _wrongCount > _questions.size())
				throw exception("There're more answers than questions");
			else _score = _rightCount * 10 - _wrongCount * 5;
		}

		~Quiz()
		{
			for (auto& question : _questions)
			{
				delete question;
				question = nullptr;
			}
		}
	};

}