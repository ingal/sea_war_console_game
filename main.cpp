#include "board.h"
#include <iostream>
#include <ctime>


void main()
{
	system("color 1f");
	system("title ������� ���   v.3.1b");
	system("cls");
	srand(time(NULL));

	Board human,pc;
	int pcstate=0;

	if(!Place(human,pc))return;// ����������� ��������

	int hod;
	do
	{
		RusMsg("\n������ �����: 0-��������� 1-����� (������� ����� 0 ��� 1)");
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
					RusMsg("\n��� ��������� ��������! ������ �� �� �������...");
				}
				if (a==0)
					RusMsg("\n� ����� �� ����� �������� ��������! ������� �� ������� �����!");
				if (a==1)
					RusMsg("\n��� ������� ��������...");

				std::cout.flush();
				std::cin.get();

			break;
		case 1:
				a=Human(pc);
				Print(human,pc);
				if (a==-1)
				{
					hod=0;
					RusMsg("\n�� ��������� ��������! �� ��� ��� �������...");
				}
				if (a==0)
					RusMsg("\n����� � ���� ��������! �� ��� ��� ����!");
				if (a==1)
					RusMsg("\n�����������!���� ���� �� ���!");

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
	RusMsg("\n!!!!!  � � � � � � � � � �   � � � � � � � � !!!!!\n");
	RusMsg("\n!!!!!  ������ ������ ������ ��� ���������    !!!!!\n");
	RusMsg("\n!!!!!                 � � �                  !!!!!\n");
	RusMsg("\n!!!!!****************************************!!!!!\n");

}
else
{
	RusMsg("\n##################################################\n");
	RusMsg("\n#####             � � � � � � � �            #####\n");
	RusMsg("\n##### ���� ������� �����������, � �� ������� #####\n");
	RusMsg("\n#####               ��� ��������             #####\n");
	RusMsg("\n##################################################\n");

}

}
