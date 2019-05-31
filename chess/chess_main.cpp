#include <graphics.h>	// EasyX
#include <strstream>
#include <ctime>
#pragma comment(lib, "Winmm.lib")
#define T(c) ((c == 'B') ? 'W' : 'B')


using namespace std;



/*******************************����ȫ�ֱ���*****************************/
const int difficult = 6;	// �Ѷ�
const int move[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1},
						{-1, -1}, {1, -1}, {1, 1}, {-1, 1}};
							// �˸�������չ
char map[15][15];				// ����
IMAGE img[5];				// ����ͼƬ
int black, white;			// ˫����������
int X, Y;					// ��������ӵ�

/**********************************��������*****************************/
void load(void);				// �����ز�
void print(void);				// ������
bool ask(void);					// �����Ի���
int D(char, int);				// ��̬�滮
void play(void);				// ��Ϸ����

/**********************************���庯��*****************************/
void load(void)		// �����ز�
{
	// ����ͼƬ
	loadimage(&img[0], "ͼƬ\\��λ.bmp");
	loadimage(&img[1], "ͼƬ\\����.bmp");
	loadimage(&img[2], "ͼƬ\\����.bmp");
	loadimage(&img[3], "ͼƬ\\����1.bmp");
	loadimage(&img[4], "ͼƬ\\����1.bmp");


	// ��ʼ������
	initgraph(340, 340);
	IMAGE qipan;
	loadimage(&qipan, "ͼƬ\\����.bmp");
	putimage(0, 0, &qipan);
	setorigin(26, 26);
	SetWindowText(GetHWnd(), "�ڰ���AI��");
}

void print(void)	// ������
{
	int x, y;
	black = white = 0;
	for(x = 0; x < 15; x++)
		for(y = 0; y < 15; y++)
			switch(map[x][y])
			{
				case 0:
						putimage(37 * y, 37 * x, &img[0]);
					break;
				case 'B':
						putimage(37 * y, 37 * x, &img[1]);
					black++;
					break;
				case 'W':
						putimage(37 * y, 37 * x, &img[2]);
					white++;
					break;
			}
}

bool ask(void)	// �����Ի���
{
	HWND wnd = GetHWnd();
	int key;
	char str[50];
	ostrstream strout(str, 50);
	strout <<"�ڣ�" <<black <<"  �ף�" <<white <<endl;
	if (black == white)
		strout <<"ƽ��";
	else if(black > white)
		strout <<"��Ӯ�ˣ�";
	else
		strout <<"����emm";
	strout <<"\n����һ����" <<ends;
	if(black == white)
		key = MessageBox(wnd, str, "�;�", MB_YESNO | MB_ICONQUESTION);
	else if(black > white)
		key = MessageBox(wnd, str, "��ʤ", MB_YESNO | MB_ICONQUESTION);
	else
		key = MessageBox(wnd, str, "��ʤ", MB_YESNO | MB_ICONQUESTION);
	if(key == IDYES)
		return true;
	else
		return false;
}

void play(void)			// ��Ϸ����
{
	MOUSEMSG m;
	int x, y;

	// ��ʼ������
	for(x = 0; x < 8; x++)
		for(y = 0; y < 8; y++)
			map[x][y] = 0;
	map[3][4] = map[4][3] = 'B';
	map[3][3] = map[4][4] = 'W';

	// ��ʼ��Ϸ
	print();
	mciSendString("play ����\\��������.wma from 0 repeat", NULL, 0, NULL);
	do
	{
		if (baidu('B'))										// ������������λ��							
		{
			A:
			while(true)
			{
				m = GetMouseMsg();							// ��ȡ�����Ϣ
				if(m.uMsg == WM_LBUTTONDOWN && m.x - 26 < 37 * 8 && m.y - 26 < 37 * 8)
															// ���������
					break;
			}
			x = (m.y - 26) / 37;
			y = (m.x - 26) / 37;
			if(judge(x, y, 'B'))							// �����ǰλ����Ч
			{
				draw(x, y, 'B');							// ����
				mciSendString("play ����\\����.wma from 0", NULL, 0, NULL);
				print();
				putimage(37 * y, 37 * x, &img[3]);			// ��ʶ���ӵ�
			}
			else
				goto A;
			if (quit('W'))									// ������Ƿ�ʧ��
				break;
		}
		if (baidu('W'))										// ��������������λ��
		{
			clock_t start;
			start = clock();
			D('W', 1);										// �����ⷨ
			while (clock() - start < CLOCKS_PER_SEC);
			draw(X, Y, 'W');
			print();
			mciSendString("play ����\\����.wma from 0", NULL, 0, NULL);
			putimage(37 * Y, 37 * X, &img[4]);	// ��ʶ���ӵ�
			if (quit('B'))									// ����Ƿ�ʧ��
				break;
		}
	}while (baidu('B') || baidu ('W'));




/*

  // ������
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	load();
	do
	{
		play();
	} while(ask());
	return 0;
}
	
*/

/***********************************THE END************************************/