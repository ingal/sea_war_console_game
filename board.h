#ifndef _BINARY_BOARD_H_
#define _BINARY_BOARD_H_
//=======================================================================
//=======================================================================

class Board{

private:
	int p[10][10]; // ������� ����
	// ��������: -1 �����, 0 �������(������), 1 �������� ������, 2 ��������� ������, 3-�������� �������
	int count; // ���-�� ����� �����
public:
	Board();
	void Reset();
	void Set(int x,int y, int value);
	int Get(int x, int y);

	bool HandFill();
	bool AutoFill();
	bool SetShip(int palub, int x1, int y1, int x2, int y2);

	int GetCount();


//  �������� ����� ������ ������� (����� ��� ����������)
	bool CheckAura(int x1, int y1, int x2, int y2);

//  ������� ����� ������ ������� (����� ��� ����������)
	void SetAura(int x, int y);

	void Print();
	~Board();

};

//=======================================================================
void RusMsg(char *);
void Print(Board & a, Board & b );
int  Human(Board &);
int  Pc(Board &);
bool CheckKill(Board & , int x,int y);

bool Place(Board &, Board &);
int Shot(Board & , int x,int y);


//  ��������������� ������ � ����������
void Convert(char *, int&,int&,int&,int&);

//=======================================================================
void Music();


//=======================================================================


#endif