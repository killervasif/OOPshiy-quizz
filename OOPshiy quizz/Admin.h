#pragma once
namespace UserReleated {
	class Admin :
		public User
	{
	public:
		Admin() = default;
		Admin(string nickname, string password)
			:User(nickname, password) {}
	};

	ostream& operator<<(ostream& out, const Admin& a)
	{
		out << "Nickname: " << a.name() << ' ' << a.score() << endl;
		return out;
	}
}
