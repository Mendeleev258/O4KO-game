#include <iostream>


template<typename T, typename Predicat>
void validation(T& x, Predicat condition, const char* message);
int exit();


int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	short choice;
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

			if ((sum <= 21 && opponent <= 21) || (sum >= 21 && opponent >= 21))
			{
				if (abs(21 - sum) < abs(21 - opponent))
					std::cout << "Вы выиграли!\n";
				if (abs(21 - sum) > abs(21 - opponent))
					std::cout << "Вы проиграли!\n";
			}
			else
			{
				if (sum < 21)
					std::cout << "Вы выиграли!\n";
				else std::cout << "Вы проиграли!\n";
			}
			if (sum == opponent)
				std::cout << "Ничья\n";

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

int exit()
{
	char isExit;
	std::cout << "\nЕщё партейку? (Y/любая клавиша) ";
	std::cin >> isExit;
	std::cout << '\n';
	if (isExit != 'Y' && isExit != 'y' && isExit != '1')
		return 2;
}