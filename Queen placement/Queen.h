#include <iostream>

class Queen
{
public:

	const int line, column;

	explicit Queen(const int lineP, const int columnP) :line{ lineP }, column{ columnP } {}

	Queen() = default;

	friend std::ostream& operator << (std::ostream& out, Queen queen)
	{
		out << '(' << queen.line << ',' << queen.column << ')';
		return out;
	}

};