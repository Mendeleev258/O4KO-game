#include <iostream>


template<typename T, typename Predicat>
void validation(T& x, Predicat condition, const char* message);
void print_issue(int res, int& player_score, int& opponent_score);
int exit();


int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	short choice;
	int player_score{}, opponent_score{};
	do
	{
		int sum{};
		std::cout << 
			"1. Сыграть в очко)))\n" <<
			"2. Выйти из игры";
		validation(choice, [](int x) {return x >= 1 && x <= 2; }, "");

		if (choice == 1)
		{
			short turn = 1;
			while (sum <= 21 && turn != 2)
			{
				std::cout <<
					"\n1. Беру карту\n" <<
					"2. Мне хватит";
				validation(turn, [](int x) {return x >= 1 && x <= 2; }, "");
				if (turn == 1)
				{
					sum += 2 + rand() % (11 - 2 + 1);
				}
				std::cout << "Ваши очки: " << sum << '\n';
			}

			int opponent = 15 + rand() % (25 - 15 + 1);
			std::cout << "Очки противника: " << opponent << '\n';

			if (sum == 21)
				std::cout << "ОЧКО!!!\n";

			short res;

			if ((sum <= 21 && opponent <= 21) || (sum >= 21 && opponent >= 21))
			{
				if (abs(21 - sum) < abs(21 - opponent))
					res = 1;
				if (abs(21 - sum) > abs(21 - opponent))
					res = 0;
			}
			else
			{
				if (sum < 21)
					res = 1;
				else res = 0;
			}
			if (sum == opponent)
				res = -1;

			print_issue(res, player_score, opponent_score);
			std::cout << "\nСчёт " << player_score << " : " << opponent_score << '\n';
			choice = exit();
		}
		
	} while (choice != 2);
}


template<typename T, typename Predicat>
void validation(T& x, Predicat condition, const char* message)
{
	std::cout << message << "\n>>> ";
	while (!(std::cin >> x && condition(x)))
	{
		std::cout << "Ошибка ввода!" << '\n';
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cout << message << "\n>>> ";
	}
}

void print_issue(int res, int& player_score, int& opponent_score)
{
	switch (res)
	{
	case 0:
		std::cout << "Вы проиграли!\n";
		opponent_score++;
		break;
	case 1:
		std::cout << "Вы выиграли!\n";
		player_score++;
		break;
	default:
		std::cout << "Ничья\n";
		break;
	}
}


int exit()
{
	char isExit;
	std::cout << "\nЕщё партейку? (Y/любая клавиша) ";
	std::cin >> isExit;
	std::cout << '\n';
	if (isExit != 'Y' && isExit != 'y' && isExit != '1')
		return 2;
}