#include "Queen.h"
#include <iostream>
#include <string>
#include <stack>
using namespace std;

#pragma region Special_Abilities

void ClearScrean() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
	cout << "\tQueen" << endl;
}

void Enter() {
	string enter;
	cin.ignore();
	do {
		cout << "Press enter to continue: "; getline(cin, enter);
	} while (!enter.empty());
}
#pragma endregion


const char queenSymbol{ 'W' }, spaceSymbol{ '.' };
const int amountQueen{ 8 }, amountLine{ 8 }, amountColumn{ 8 };

void inputQueen(stack<Queen>& arrayQueen)
{
	for (int i{ 1 }, line{ 0 }, column{ 0 }; i <= 8; i++)
	{
		ClearScrean();
		cout << "Enter line " << i << "-th queen: "; cin >> line;
		cout << "Enter column " << i << "-th queen: "; cin >> column;
		if (line > amountLine - 1 || column > amountColumn - 1)throw exception("Numbers out of range");
		else arrayQueen.push(Queen{ line, column });
	}
}

void outQueen(const stack<Queen>& arrayQueen)
{
	for (size_t i{ 1 }; i <= amountColumn; i++)
	{
		cout << "   " << i;
	}

	cout << endl;

	for (size_t line{ 0 }; line < amountLine; line++)
	{

		stack<Queen> tempQueen{ arrayQueen };
		stack<Queen> tempArray{};
		while(!tempQueen.empty())
		{
			if (tempQueen.top().line == line)tempArray.push(tempQueen.top());
			tempQueen.pop();
		}

		for (size_t column{ 0 }; column < amountColumn; column++)
		{
			if (column == 0)cout << line + 1 << "| ";
			if (!tempArray.empty() && tempArray.top().line == line && tempArray.top().column == column)
			{
				cout << queenSymbol << " | ";
				tempArray.pop();
			}
			else cout << spaceSymbol << " | ";
		}
		cout << endl;
	}

	int count{ 0 };
	cout << string(amountColumn * 4, '-') << endl;
	for (stack<Queen> tempQueen{ arrayQueen }; !tempQueen.empty(); tempQueen.pop())
	{
		cout << ++count << " queen " << tempQueen.top() << " | ";
		if (count % 2 == 0)cout << endl;
	}
	cout << string(amountColumn * 4, '-') << endl;

}

bool isAttackLine(const stack<Queen>& arrayQueen)
{
	for (size_t line{ 0 }; line < amountLine; line++)
	{
		int amount{ 0 };
		for (stack<Queen> tempQueen{ arrayQueen }; !tempQueen.empty(); tempQueen.pop())
		{
			if (tempQueen.top().line == line)amount++;
		}
		if (amount > 1) 
		{
			throw exception("More than two queens in the line area");
			return true;
		}
	}
	return false;
}

bool isAttackColumn(const stack<Queen>& arrayQueen)
{
	for (size_t column{ 0 }; column < amountColumn; column++)
	{
		int amount{ 0 };
		for (stack<Queen> tempQueen{ arrayQueen }; !tempQueen.empty(); tempQueen.pop())
		{
			if (tempQueen.top().column == column)amount++;
		}
		if (amount > 1)
		{
			throw exception("More than two queens in the column area");
			return true;
		}
	}

	return false;
}

bool isAttackDiagonal(const stack<Queen>& arrayQueen)
{
	stack<Queen> tempQueen = arrayQueen;

	while (!tempQueen.empty())
	{
		Queen currentQueen = tempQueen.top();
		tempQueen.pop();

		stack<Queen> remainingQueens = tempQueen;
		while (!remainingQueens.empty())
		{
			Queen otherQueen = remainingQueens.top();
			remainingQueens.pop();

			if (abs(currentQueen.line - otherQueen.line) == abs(currentQueen.column - otherQueen.column))
			{
				throw exception("More than two queens in the diagonal area");
				return true; 
			}
		}
	}

	return false;
}

string isAttack(const stack<Queen>& arrayQueen)
{
	if (isAttackLine(arrayQueen) || isAttackColumn(arrayQueen) || isAttackDiagonal(arrayQueen))
	{
		return "Placement is incorrect";
	}
	return "Placement is correct";
}

int main()
{
	stack<Queen> arrayQueen;

	try
	{
		if(amountQueen <= 0)throw exception("Amount queen less or to equi zero");
		else if (amountLine <= 0)throw exception("Amount line less or to equi zero");
		else if (amountColumn <= 0)throw exception("Amount column less or to equi zero");

		inputQueen(arrayQueen);
		ClearScrean();
		outQueen(arrayQueen);
		cout << "\nCorrect placement: " << isAttack(arrayQueen) << endl;
	}
	catch(exception error)
	{
		cout << error.what() << endl;
	}

	Enter();

	return 0;
}