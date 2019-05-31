#include <graphics.h>	// EasyX
#include <strstream>
#include <ctime>
#pragma comment(lib, "Winmm.lib")
#define T(c) ((c == 'B') ? 'W' : 'B')


using namespace std;



/*******************************定义全局变量*****************************/
const int difficult = 6;	// 难度
const int move[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1},
						{-1, -1}, {1, -1}, {1, 1}, {-1, 1}};
							// 八个方向扩展
char map[15][15];				// 棋盘
IMAGE img[5];				// 保存图片
int black, white;			// 双方的棋子数
int X, Y;					// 白棋的下子点

/**********************************函数声明*****************************/
void load(void);				// 加载素材
void print(void);				// 画棋盘
bool ask(void);					// 弹出对话框
int D(char, int);				// 动态规划
void play(void);				// 游戏过程

/**********************************定义函数*****************************/
void load(void)		// 加载素材
{
	// 加载图片
	loadimage(&img[0], "图片\\空位.bmp");
	loadimage(&img[1], "图片\\黑子.bmp");
	loadimage(&img[2], "图片\\白子.bmp");
	loadimage(&img[3], "图片\\黑子1.bmp");
	loadimage(&img[4], "图片\\白子1.bmp");


	// 初始化棋盘
	initgraph(340, 340);
	IMAGE qipan;
	loadimage(&qipan, "图片\\棋盘.bmp");
	putimage(0, 0, &qipan);
	setorigin(26, 26);
	SetWindowText(GetHWnd(), "黑白棋AI版");
}

void print(void)	// 画棋盘
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

bool ask(void)	// 弹出对话框
{
	HWND wnd = GetHWnd();
	int key;
	char str[50];
	ostrstream strout(str, 50);
	strout <<"黑：" <<black <<"  白：" <<white <<endl;
	if (black == white)
		strout <<"平局";
	else if(black > white)
		strout <<"你赢了！";
	else
		strout <<"输了emm";
	strout <<"\n再来一局吗？" <<ends;
	if(black == white)
		key = MessageBox(wnd, str, "和局", MB_YESNO | MB_ICONQUESTION);
	else if(black > white)
		key = MessageBox(wnd, str, "黑胜", MB_YESNO | MB_ICONQUESTION);
	else
		key = MessageBox(wnd, str, "白胜", MB_YESNO | MB_ICONQUESTION);
	if(key == IDYES)
		return true;
	else
		return false;
}

void play(void)			// 游戏过程
{
	MOUSEMSG m;
	int x, y;

	// 初始化棋子
	for(x = 0; x < 8; x++)
		for(y = 0; y < 8; y++)
			map[x][y] = 0;
	map[3][4] = map[4][3] = 'B';
	map[3][3] = map[4][4] = 'W';

	// 开始游戏
	print();
	mciSendString("play 音乐\\背景音乐.wma from 0 repeat", NULL, 0, NULL);
	do
	{
		if (baidu('B'))										// 如果玩家有下子位置							
		{
			A:
			while(true)
			{
				m = GetMouseMsg();							// 获取鼠标消息
				if(m.uMsg == WM_LBUTTONDOWN && m.x - 26 < 37 * 8 && m.y - 26 < 37 * 8)
															// 如果左键点击
					break;
			}
			x = (m.y - 26) / 37;
			y = (m.x - 26) / 37;
			if(judge(x, y, 'B'))							// 如果当前位置有效
			{
				draw(x, y, 'B');							// 下子
				mciSendString("play 音乐\\下子.wma from 0", NULL, 0, NULL);
				print();
				putimage(37 * y, 37 * x, &img[3]);			// 标识下子点
			}
			else
				goto A;
			if (quit('W'))									// 计算机是否失败
				break;
		}
		if (baidu('W'))										// 如果计算机有下子位置
		{
			clock_t start;
			start = clock();
			D('W', 1);										// 搜索解法
			while (clock() - start < CLOCKS_PER_SEC);
			draw(X, Y, 'W');
			print();
			mciSendString("play 音乐\\下子.wma from 0", NULL, 0, NULL);
			putimage(37 * Y, 37 * X, &img[4]);	// 标识下子点
			if (quit('B'))									// 玩家是否失败
				break;
		}
	}while (baidu('B') || baidu ('W'));




/*

  // 主函数
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