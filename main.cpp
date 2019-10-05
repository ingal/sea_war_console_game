#include "board.h"
#include <iostream>
#include <ctime>


void main()
{
	system("color 1f");
	system("title Морской Бой   v.3.1b");
	system("cls");
	srand(time(NULL));

	Board human,pc;
	int pcstate=0;

	if(!Place(human,pc))return;// Расстановка кораблей

	int hod;
	do
	{
		RusMsg("\nПервым ходит: 0-Компьютер 1-Игрок (введите цифру 0 или 1)");
		std::cin >> hod;
	}while(hod!=0 && hod!=1);
	Music();
	while(human.GetCount()>0 && pc.GetCount()>0)
	{
		int a;
		system("cls");
		Print(human,pc);

		switch(hod)
		{
		case 0:
				a=Pc(human);
				Print(human,pc);
				if (a==-1)
				{
					hod=1;
					RusMsg("\nОни промазали командор! Сейчас мы им покажем...");
				}
				if (a==0)
					RusMsg("\nВ одном из наших кораблей пробоина! Торпеда по правому борту!");
				if (a==1)
					RusMsg("\nНаш корабль потопили...");

				std::cout.flush();
				std::cin.get();

			break;
		case 1:
				a=Human(pc);
				Print(human,pc);
				if (a==-1)
				{
					hod=0;
					RusMsg("\nМы промазали командор! На нас идёт торпеда...");
				}
				if (a==0)
					RusMsg("\nТочно в цель командор! Но они еще живы!");
				if (a==1)
					RusMsg("\nПоздравляем!Цель ушла на дно!");

				std::cout.flush();
				std::cin.get();
			break;
		default:
			hod=1;
			break;
		}
	}

system("cls");

if (human.GetCount()>0)
{
	RusMsg("\n!!!!!****************************************!!!!!\n");
	RusMsg("\n!!!!!  П О З Д Р А В Л Я Ю   К О М А Н Д О Р !!!!!\n");
	RusMsg("\n!!!!!  Полная победа РАЗУМА над железякой    !!!!!\n");
	RusMsg("\n!!!!!                 У Р А                  !!!!!\n");
	RusMsg("\n!!!!!****************************************!!!!!\n");

}
else
{
	RusMsg("\n##################################################\n");
	RusMsg("\n#####             К О М А Н Д О Р            #####\n");
	RusMsg("\n##### Ваша эскадра разгромлена, а вы пойдете #####\n");
	RusMsg("\n#####               под трибунал             #####\n");
	RusMsg("\n##################################################\n");

}

}
