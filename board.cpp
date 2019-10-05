#include "board.h"
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <cstdio>
#include <string.h>
using namespace std;

//=======================================================================

Board::Board(){

	count=0;
	for(int i=0; i<10; ++i)
		for(int j=0; j<10; ++j)
			p[i][j]=-1;
}


void Board::Reset(){

	count=0;
	for(int i=0; i<10; ++i)
		for(int j=0; j<10; ++j)
			p[i][j]=-1;
}

void Board::Set(int x, int y, int value){
	if(x>9||x<0||y>9||y<0)
		return;

	if(1==value) // ставят подбитую палубу
		--count;
	p[x][y]=value;
}


int Board::GetCount(){
	return count;
}

int Board::Get(int x, int y){
	if(x>9||x<0||y>9||y<0)
		return -404;
	return p[x][y];
}

Board::~Board(){
}


bool Board::AutoFill(){

	for(int i=1; i<=4; ++i)
		for(int j=5-i; j>=1; --j)
		{
			int s=1;
			while(s)
			{
				int x1=rand()%10;
				int y1=rand()%10;
				int x2,y2;

				if(rand()%2) // вычисляем направление (вбок или вниз)
				{
					x2=x1+i-1;
					y2=y1;
				}
				else
				{
					x2=x1;
					y2=y1+i-1;
				}
				// проверка на выход за границу поля
				if(x2>9||y2>9||x2<0||y2<0)
					continue;
				if(SetShip(i,x1,y1,x2,y2))
					s=0;
			}
		}

	return true;
}


bool Board::HandFill(){

	for(int i=1; i<=4; ++i)
		for(int j=5-i; j>=1; --j)
		{
			int s=1;
			while(s)
			{
				RusMsg("Введите координаты ");
				cout<<i;
				RusMsg("-палубного корабля.");

				char coord[7];
				cin>>coord;

				if(1==i&&strlen(coord)>3)
				{
					RusMsg("Ошибка! Корабль не установлен!\nНажмите любую клавишу...");
					cout.flush();
					cin.get();
					Board::Print();
					continue;
				}
				int x1,y1,x2,y2;

				Convert(coord,x1,y1,x2,y2);

				// проверка на выход за грницу поля
				if(x2>9||y2>9||x2<0||y2<0)
					continue;
				if(SetShip(i,x1,y1,x2,y2))
				{
					RusMsg("Корабль установлен!\nНажмите любую клавишу...");
					cout.flush();
					s=0;
					std::cin.get();
				}
				else
				{
					RusMsg("Ошибка! Корабль не установлен!\nНажмите любую клавишу...");
					cout.flush();
					s=1;
					cin.get();
				}
				Board::Print();
			}
		}
	RusMsg("Все корабли успешно установлены!\nНажмите любую клавишу...");
	cout.flush();
	cin.get();
	return true;
}


void Convert(char * str, int & x1, int & y1, int & x2, int & y2){

	strlwr(str);

	if(strlen(str)<4)// т.е. координаты однопалубного корабля
	{
		y1=y2=str[0]-97;
		x1=x2=atoi(str+1)-1;
		return;
	}


	int a,b,c,d,i=0;
	a=str[0]-97;
	b=atoi(str+1)-1;

	if(b>8)i=1;

	c=str[2+i]-97;
	d=atoi(str+3+i)-1;

	if(a>c||b>d)
	{
		y1=c;
		x1=d;
		y2=a;
		x2=b;
		return;
	}
	else
	{
		y1=a;
		x1=b;
		y2=c;
		x2=d;
		return;
	}

	x1=x2=y1=y2=-1;
}




void Board::Print(){
	cout<<"\n   A B C D E F G H I J \n";

	cout<<"  "	<<(char)218<<(char)196<<(char)194<<(char)196<<(char)194<<(char)196
				<<(char)194<<(char)196<<(char)194<<(char)196<<(char)194<<(char)196
				<<(char)194<<(char)196<<(char)194<<(char)196<<(char)194<<(char)196
				<<(char)194<<(char)196<<(char)191<<endl;


	for(int i=0; i<10; ++i)
	{
		if(i<9)
			cout<<" "<<i+1;
		else
			cout<<10;
		for(int j=0; j<10; ++j)
		{
			cout<<(char)179;
			if(p[i][j]==-1)
				cout<<" ";
			if(p[i][j]==0)
				cout<<(char)258;
			if(p[i][j]==1)
				cout<<(char)178;
			if(p[i][j]==2)
				cout<<".";
			if(p[i][j]==3)
				cout<<"X";
		}
		cout<<(char)179<<endl;
		if(i<9)
		{
			cout<<"  "<<(char)195<<(char)196<<(char)197<<(char)196<<(char)197
					<<(char)196<<(char)197<<(char)196<<(char)197<<(char)196
					<<(char)197<<(char)196<<(char)197<<(char)196<<(char)197
					<<(char)196<<(char)197<<(char)196<<(char)197<<(char)196
					<<(char)180<<endl;
		}
		else
		{
			cout<<"  "<<(char)192<<(char)196<<(char)193<<(char)196<<(char)193
					<<(char)196<<(char)193<<(char)196<<(char)193<<(char)196
					<<(char)193<<(char)196<<(char)193<<(char)196<<(char)193
					<<(char)196<<(char)193<<(char)196<<(char)193<<(char)196
					<<(char)217<<endl;
		}
	}
	cout<<endl;


}


bool Board::SetShip(int palub, int x1, int y1, int x2, int y2){


// проверка на длину палубы
	if(x2-x1!=palub-1&&y2-y1!=palub-1)
		return false;


//проверка на пересечение с другими кораблями
	if(! CheckAura(x1,y1,x2,y2))
		return false;



// все ОК - прописываем корабль и выходим
	if(x1==x2) // корбаль вертикальный
	{
		for(int i=y1; i<=y2; ++i)
		{
			p[x1][i]=0;
			++count;
		}
		return true;
	}
	if(y1==y2) // корбаль гооризонтальный
	{
		for(int i=x1; i<=x2; ++i)
		{
			p[i][y1]=0;
			++count;
		}
		return true;
	}

// проверка выхода за границы поля выполняется при вводе и преобразовании координат
// корабль наискосок - не поддерживается
	return false;
}



//  просмотр полей вокруг корабля (перед его установкой)
bool Board::CheckAura(int x1, int y1, int x2, int y2){
	for(int i=x1-1; i<=x2+1; ++i)
	{
		if(i<0||i>9)continue;
		for(int j=y1-1; j<=y2+1; ++j)
		{
			if(j<0||j>9)continue;
			if(p[i][j]!=-1)return false;
		}
	}
	return true;
}

//  отметка полей вокруг корабля (после его потопления)
// принимается координата любой палубы корабля

void Board::SetAura(int x, int y){

	int x1,y1,x2,y2; // находим координаты начала и конца корабля

	int i=0;
	while(x+i<=9&&x+i>=0) // не выходить за границы поля
	{
		if(Get(x+i,y)==1||Get(x+i,y)==3)
		{
			Set(x+i,y,3);
			x2=x+i;
			++i;
		}
		else
		{
			break;
		}
	}

	i=0;
	while(x-i<=9&&x-i>=0) // не выходить за границы поля
	{
		if(Get(x-i,y)==1||Get(x-i,y)==3)
		{
			Set(x-i,y,3);
			x1=x-i;
			++i;
		}
		else
		{
			break;
		}
	}

	i=0;
	while(y+i<=9&&y+i>=0) // не выходить за границы поля
	{
		if(Get(x,y+i)==1||Get(x,y+i)==3)
		{
			Set(x,y+i,3);
			y2=y+i;
			++i;
		}
		else
		{
			break;
		}
	}

	i=0;
	while(y-i<=9&&y-i>=0) // не выходить за границы поля
	{
		if(Get(x,y-i)==1||Get(x,y-i)==3)
		{
			Set(x,y-i,3);
			y1=y-i;
			++i;
		}
		else
		{
			break;
		}
	}

	for(i=x1-1; i<=x2+1; ++i)
	{
		if(i<0||i>9)continue;
		for(int j=y1-1; j<=y2+1; ++j)
		{
			if(j<0||j>9)
				continue;
			if(Get(i,j)==3)
				continue;
			Set(i,j,2); // 2-стреляная клетка
		}
	}


}





void RusMsg(char * message){
	char rmessage[256];
	CharToOem(message,rmessage);
	cout<<rmessage;
}

//=======================================================================
// подбит "корабль" с такой координатой или ранен
// проверка проводится только после попадания в одну из палуб
// если хоть одна палуба цела - возвращается ложь (не подбит, а ранен)

bool CheckKill(Board & doska, int x, int y){

	int i=1;
	while(x+i<=9&&x+i>=0) // не выходить за границы поля
	{
		if(doska.Get(x+i,y)==-1||doska.Get(x+i,y)==2)// не выходить за границы корабля
			break;
		if(doska.Get(x+i,y)==0)// есть целая палуба
			return false;
		++i;
	}

	i=1;
	while(x-i<=9&&x-i>=0) // не выходить за границы поля
	{
		if(doska.Get(x-i,y)==-1||doska.Get(x-i,y)==2)// не выходить за границы корабля
			break;
		if(doska.Get(x-i,y)==0)// есть целая палуба
			return false;
		++i;
	}

	i=1;
	while(y+i<=9&&y+i>=0) // не выходить за границы поля
	{
		if(doska.Get(x,y+i)==-1||doska.Get(x,y+i)==2)// не выходить за границы корабля
			break;
		if(doska.Get(x,y+i)==0)// есть целая палуба
			return false;
		++i;
	}

	i=1;
	while(y-i<=9&&y-i>=0) // не выходить за границы поля
	{
		if(doska.Get(x,y-i)==-1||doska.Get(x,y-i)==2)// не выходить за границы корабля
			break;
		if(doska.Get(x,y-i)==0)// есть целая палуба
			return false;
		++i;
	}
	return true;

}
//=======================================================================
int Shot(Board & doska, int x, int y){

	int rez=doska.Get(x,y);
	if(0==rez)
	{
		doska.Set(x,y,1);

		if(CheckKill(doska,x,y))
		{
			doska.SetAura(x,y);
			return 1; // убит
		}
		else
			return 0; // ранен
	}

	if(-1==rez)
	{
		doska.Set(x,y,2);
	}
	return -1; // промазал
}
//=======================================================================

int Human(Board & pc){

	int x=0;
	int y=0;
	while(1)
	{
		RusMsg("\n Командор,введите координаты цели:");
		char answ[4];
		cin>>answ;


		strlwr(answ);

		if(strlen(answ)<4)
		{
			y=answ[0]-97;
			x=atoi(answ+1)-1;
		}

		if(x<0||x>9||y<0||y>9)
			continue;
		break;
	}

	return Shot(pc,x,y);
}
//=======================================================================
int Pc(Board & human){

	int x,y;

	do
	{
		x=rand()%10;
		y=rand()%10;
	}
	while(human.Get(x,y)>0);

	return Shot(human,x,y);
}


//=======================================================================

void Print(Board & a, Board & b){

	cout<<"\n   A B C D E F G H I J \t   A B C D E F G H I J \n";

	cout<<"  "<<(char)218<<(char)196<<(char)194<<(char)196<<(char)194<<(char)196
			<<(char)194<<(char)196<<(char)194<<(char)196<<(char)194<<(char)196
			<<(char)194<<(char)196<<(char)194<<(char)196<<(char)194<<(char)196
			<<(char)194<<(char)196<<(char)191;

	cout<<"\t  "<<(char)218<<(char)196<<(char)194<<(char)196<<(char)194<<(char)196
			<<(char)194<<(char)196<<(char)194<<(char)196<<(char)194<<(char)196
			<<(char)194<<(char)196<<(char)194<<(char)196<<(char)194<<(char)196
			<<(char)194<<(char)196<<(char)191<<endl;

	for(int i=0; i<10; ++i)
	{
		if(i<9)
			cout<<" "<<i+1;
		else
			cout<<10;

		for(int j=0; j<10; ++j)
		{
			cout<<(char)179;
			if(a.Get(i,j)==-1)
				cout<<" ";
			if(a.Get(i,j)==0)
				cout<<(char)258;
			if(a.Get(i,j)==1)
				cout<<(char)178;
			if(a.Get(i,j)==2)
				cout<<".";
			if(a.Get(i,j)==3)
				cout<<"X";
		}
		cout<<(char)179;

		cout<<"\t";

		if(i<9)
			cout<<" "<<i+1;
		else
			cout<<10;

		for(int j=0; j<10; ++j)
		{
			cout<<(char)179;
			if(b.Get(i,j)==-1)
				cout<<" ";
			if(b.Get(i,j)==0)
				cout<<" ";
			if(b.Get(i,j)==1)
				cout<<(char)178;
			if(b.Get(i,j)==2)
				cout<<".";
			if(b.Get(i,j)==3)
				cout<<"X";
		}

		cout<<(char)179<<endl;

		if(i<9)
		{
			cout<<"  "<<(char)195<<(char)196<<(char)197<<(char)196<<(char)197
					<<(char)196<<(char)197<<(char)196<<(char)197<<(char)196
					<<(char)197<<(char)196<<(char)197<<(char)196<<(char)197
					<<(char)196<<(char)197<<(char)196<<(char)197<<(char)196
					<<(char)180;

			cout<<"\t  "<<(char)195<<(char)196<<(char)197<<(char)196<<(char)197
					<<(char)196<<(char)197<<(char)196<<(char)197<<(char)196
					<<(char)197<<(char)196<<(char)197<<(char)196<<(char)197
					<<(char)196<<(char)197<<(char)196<<(char)197<<(char)196
					<<(char)180<<endl;
		}
		else
		{
			cout<<"  "<<(char)192<<(char)196<<(char)193<<(char)196<<(char)193
					<<(char)196<<(char)193<<(char)196<<(char)193<<(char)196
					<<(char)193<<(char)196<<(char)193<<(char)196<<(char)193
					<<(char)196<<(char)193<<(char)196<<(char)193<<(char)196
					<<(char)217;

			cout<<"\t  "<<(char)192<<(char)196<<(char)193<<(char)196<<(char)193
					<<(char)196<<(char)193<<(char)196<<(char)193<<(char)196
					<<(char)193<<(char)196<<(char)193<<(char)196<<(char)193
					<<(char)196<<(char)193<<(char)196<<(char)193<<(char)196
					<<(char)217<<endl;
		}
	}
	cout<<endl;


}


//=======================================================================

bool Place(Board & human, Board & pc){

	int choice=1;
	RusMsg("\nРасставляем корабли. \n1-Расставить автоматически 2-Расставить в ручную ");
	cin>>choice;

	if(choice!=1&&choice!=2)
	{
		RusMsg("\nНе хочешь как хочешь, пока...");
		return false;
	}

	if(1==choice)
	{
		int a=1;
		while(a)
		{
			human.Reset();
			human.AutoFill();
			human.Print();
			RusMsg("\n1-Перестроить флотилию  0-Оставтиь так");
			cin>>a;
		}
	}
	else
	{
		int a=1;
		while(a)
		{
			human.Reset();
			human.HandFill();
			RusMsg("\n1-Перестроить флотилию  0-Оставтиь так");
			cin>>a;
		}
	}

	return pc.AutoFill();
}



void Music(){

	// Массив частот для мелодии "ВАРЯГ"
	double var[]={
			329.6*2,440*2,440*2,440*2,440*2,392*2,349.2*2,
			329.6*2,293.7*2,277.2*2,293.7*2,349.2*2,440*2,
			440*2,392*2,493.9*2,440*2,392*2,349.2*2,329.6*2,293.7*2,
			261.7*2,261.7*2,0
	};

	// Массив длительностей

	int dur[]={

			200,400,200,200,200,200,200,200,200,200,200,200,600,200,
			400,200,200,200,200,200,200,800,200
	};

	int i;

	for(i=0; var[i]!=0; i++)
		Beep(var[i],dur[i]);
}


