#pragma once
namespace UserReleated {
	class User
	{
	protected:
		string _name = "";
		string _password = "";
		size_t _score = 0;
	public:
		User() = default;
		User(string name, string password)
		{
			setName(name);
			setPassword(password);
		}

		string name() const { return _name; }
		string password() const { return _password; }
		size_t score() const { return _score; }
		void setName(const string& name) {
			if (name.size() < 3)
				throw exception("Username too Short");
			_name = name;
		}
		void setPassword(const string& password) {
			if (password.size() < 8)
				throw exception("Password too Short");
			_password = password;
		}
		void setScore(size_t score) {
			if (score > 10000000) {
				_score = 0;
				return;
			}
			_score = score;
		}
	};

	ostream& operator<<(ostream& out, const User& a)
	{
		out << "Nickname: " << a.name() << ' ' << a.score() << endl;
		return out;
	}
}
