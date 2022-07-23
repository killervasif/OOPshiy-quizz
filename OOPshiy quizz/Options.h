#pragma once
namespace QuizReleated {
	struct Options
	{
		vector<string> options;
		short optionIndex = 0;
	};

	ostream& operator<<(ostream& out, const Options& o)
	{
		mySetColor(7, 0);
		for (size_t i = 0; i < o.options.size(); i++)
		{
			if (i == o.optionIndex)
			{
				mySetColor(0, 7);
				out << o.options[i] << endl;
				mySetColor(7, 0);
				continue;
			}
			out << o.options[i] << endl;
		}
		return out;
	}
}
