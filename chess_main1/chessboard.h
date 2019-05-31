#include <iostream>
#include <graphics.h>
#include <conio.h>
#include "black.h"
#include "white.h"
#include <process.h>
#include <windows.h>
#define singleGirdSize 40
#define girdLength  15
 

using namespace std;


class  chessboard
{
	//int allchessman[girdLength][girdLength] = {{0 ,0}};
	struct allchessman
	{
		int point_X;   //��¼����X��λ�� 
		int point_Y;  //��¼����Y��λ��
		int message;  //ʶ���������  (�ڷ�? �׷� ? ����? ) 
	}allchessman[girdLength][girdLength];
	
	
public :	bool win;  //�����Ӯ�ı�� 
			black b;  //����ڷ����� 
			white w;  //����׷����� 
			//����b , w ��ȫ�ֵ�  ,�ֲ��Ļ����black_chessman_count�������Եı仯��Ӱ�� 
	
	public:
		
		//�ڹ��췽���г�ʼ����������
		chessboard()
		{
			win= false;
			int x=100 , y=100;  //�������϶˵�100 ,100 
			for(int i=0 ; i<15 ; i++ , y+=singleGirdSize)
			{
				for(int u=0; u<15 ; u++ , x+=singleGirdSize)
				{
					allchessman[i][u].point_X = x;
					allchessman[i][u].point_Y = y;
					if(allchessman[i][u].point_X == 100  || allchessman[i][u].point_X == 660 || allchessman[i][u].point_Y == 100 || allchessman[i][u].point_Y == 660)
					{
						allchessman[i][u].message =2; //���̱߽��ʶ��Ϊ2 , �������� 
					}
					else
					{
						allchessman[i][u].message =0;  //��ʼ��Ϊ���� 
					}
				}
				x=100;  //��X���»ص��˵�λ�� 
			}
		} 
		
		
		
	//������� 
	bool   addchessman(int chessman_X , int  chessman_Y , int message)
	{
		if(message == -1)  //�ڷ����� 
		{
			if(allchessman[chessman_X][chessman_Y].message== 0)  //Ԥ����λ������
			{
				allchessman[chessman_X][chessman_Y].message = -1;  //���� 
				setfillcolor(RED);
				fillellipse(allchessman[chessman_X][chessman_Y].point_X , allchessman[chessman_X][chessman_Y].point_Y  ,  20 , 20); //��������ʾ���� .�뾶20 
				if(is_run()) delay_fps(10);
				return true;   //���ӳɹ� 
			} 
			else  return false;  //�������ʧ��  �ظ����ӵĴ��� 
		}
		else   
		{
		
			if (message == 1)
			{
				if(allchessman[chessman_X][chessman_Y].message == 0 )  
				{
					allchessman[chessman_X][chessman_Y].message  =1;
					setfillcolor(WHITE);
					fillellipse(allchessman[chessman_X][chessman_Y].point_X , allchessman[chessman_X][chessman_Y].point_Y  ,  20 , 20); //��������ʾ���� .�뾶20 
					if(is_run()) delay_fps(10);
					return true; //���ӳɹ� 
				}
				else  return false;
			}
			else
			{
				return false; //Ӧ��������� --message��ݳ���ʱ 
			}
		}
	} //addchessman
	
	
	
	
	void  drawchessboard()
	{
		setinitmode(INIT_WITHLOGO, CW_USEDEFAULT,  CW_USEDEFAULT);
		//������С�ݶ�800 ,800
		initgraph(800 , 800);
	
		setfont(50 ,0 ,"����");
		outtextxy(250 , 0 , "����������");
		setfont(20 , 0 , "����");
		//�������� 
		//Ԥ���������϶˵���100 ,100 ���ص�
		int startpoint_X =100  , startpoint_Y =100 ;
		char str[10];
		for(int i=0; i<15 ; i++)
		{
			sprintf(str , "%d" , i+1);
			outtextxy(startpoint_X-20 , startpoint_Y-7, str);
			line(startpoint_X , startpoint_Y  , startpoint_X+( girdLength*singleGirdSize-singleGirdSize) , startpoint_Y);  //�߶λ�����Ļ�����:ʲôҲ�������� 
			startpoint_Y+=singleGirdSize;
		} 
		
		startpoint_Y = 100;  //������ʼ��Y
		
		for(i=0 ; i<15 ; i++)
		{
			sprintf(str , "%d" , i+1);
			outtextxy(startpoint_X-7, startpoint_Y-20 , str);
			line(startpoint_X , startpoint_Y  , startpoint_X , startpoint_Y+(girdLength*singleGirdSize-singleGirdSize) );
			startpoint_X+=singleGirdSize;
		} 
		
		
		/* 
		for(int i=0 ; i<15 ; i++)
		{
			for(int u=0 ; u<15 ; u++)
			{
				if(allchessman[i][u].message == 2) {}
				else
				{
					circle(allchessman[i][u].point_X , allchessman[i][u].point_Y , 20);
				}
			}
		}
		*/ 
			
	}//drawchessboard 
	
	
	
	
	void  playchess()
	{
		if(is_run()) delay_fps(10);
		int x ,y ; //�������ӵ�λ�� 
		int identity=1; // ��ʶ�ڷ� �׷����   identityȡ�಻Ϊ0 ���Ǻڷ�
		
		do
		{
			cout<<"                           *************���������� ���������***************  "<<endl;
		 	black_entry(x ,y);
			if(is_run()) delay_fps(10);
		 	if(!win)
		 	{
		 		white_entry(x ,y);
		 	}
		 	system("cls");
		} while(!win);
		getch();
	}
	
	void black_entry(int &x , int &y)
	{
		//bool addchessman(int chessman_X , int chessman_Y , int message);
		cout<<"                           ��ڷ�����(����������ɫ�Ǻ�ɫ):"<<endl;
		cout<<"                           ���������λ��:"<<endl;
		cout<<"                            ";
		cin>>x;
		cout<<"                           ����������λ��:"<<endl;
		cout<<"                            ";
		cin>>y; 	
	
		if( ! b.submit_chessman(x ,y) )
		{
			cout<<"                       ����λ�ó������̴�С�򲻺Ϸ�,����������"<<endl;
			black_entry(x ,y);
		}
		
		if( !addchessman(b.getChessman_X(), b.getChessman_Y() , b.getIdentity()) )
		{
			cout<<"                       ����ʧ��! ��λ���������ӻ����̱߽粻������! ����������~~~"<<endl; 
			black_entry( x ,y);
		}
		else
		{
			 if(bunko( b.getChessman_X(), b.getChessman_Y() , b.getIdentity()) )   
			 {
			 	setfont(50 , 0 ,"����");
			 	setfontbkcolor(GREEN);
			 	outtextxy(300 ,300 ,"�ڷ�ʤ!");
			 	setfont(20 ,0 ,"����");
				outtextxy(300 ,750 ,"��������˳�!"); 
			 	win = true;
			 }
		}
		cout<<"                           ��ǰ�ڷ���������:"<<b.getChessmanCount()<<endl;
		cout<<"                           ��ǰ�׷���������:"<<w.getChessmanCount()<<endl;  
	}
	
	
	void white_entry(int &x , int &y)
	{
	//	bool addchessman(int chessman_X , int chessman_Y , int message);
		cout<<endl<<endl<<endl;
		cout<<"                          ��׷�����(����������ɫ�ǰ�ɫ):"<<endl;
		cout<<"                          ���������λ��:"<<endl;
		cout<<"                            ";
		cin>>x;
		cout<<"                          ����������λ��:"<<endl;
		cout<<"                            ";
		cin>>y; 	
		
		if( ! w.submit_chessman(x ,y) )
		{
			cout<<"                      ����λ�ó������̴�С�򲻺Ϸ�,����������"<<endl;
			black_entry(x ,y);
		}
		
		if( !addchessman(w.getChessman_X() ,w.getChessman_Y() ,w.getIdentity()) )
		{
			cout<<"                     ����ʧ��! ��λ���������ӻ����̱߽粻������! ����������~~~"<<endl;
			white_entry(x ,y);
		}
		else
		{
			 if(bunko( w.getChessman_X(), w.getChessman_Y() , w.getIdentity()) )   
			 {
			 	setfont(50 , 0 ,"����");
			 	setfontbkcolor(LIGHTGRAY);
			 	outtextxy(300 ,300 ,"�׷�ʤ!");
			 	setfont(20 ,0 ,"����");
				outtextxy(300 ,720 ,"��������˳�!"); 
			 	win = true;
			 }
		} 
	}
	
bool bunko(int x, int y , int message) //��ʤ 
{
	int xReturnZero =x;
	int yReturnZero =y; 
	int accumulative=0; //������¼�ڷ���׷��ۼ�����һ��� ���Ӹ��� 
	//���Ը���λ��Ϊ����,����(X�᲻�� ,Y�ᷴ����) ��һ�ж�
	while(allchessman[--x][y].message == message)
	{
		accumulative++;
	//cout<<"�ۼƵ�:"<<accumulative<<endl;
	} 
	/* 
	if(accumulative == 5) 
	{
	accumulative=0; //���ü���Ϊ0 
	return true;
	}
	else
	{
	return false;
	}
	*/ 
	x = xReturnZero;
	y = yReturnZero;
	//���Ը���λ��Ϊ���� , ����( X�᲻�� , Y��������) ��һ�ж� 
	while(allchessman[++x][y].message == message)
	{
		accumulative++;
		//cout<<"�ۼƵ�:"<<accumulative<<endl;
	} 
	if(accumulative == 5) 
	{
		accumulative=0; //���ü���Ϊ0 
		return true;
	}
	else
	{
		//return false;
	}
	x = xReturnZero;
	y = yReturnZero;
	//���Ը���λ��Ϊ���� , ����(Y�᲻�� , X�ᷴ����) ��һ�ж�
	while(allchessman[x][--y].message == message)
	{
		accumulative++;
		//cout<<"�ۼƵ�:"<<accumulative<<endl;
	} 
	/*
	if(accumulative == 5) 
	{
	accumulative=0; //���ü���Ϊ0 
	return true;
	}
	else
	{
	return false;
	}
	*/
	x = xReturnZero;
	y = yReturnZero;
	//���Ը���λ��Ϊ����, ����(Y�᲻�� , X��������) ��һ�ж�
	while(allchessman[x][++y].message == message)
	{
		accumulative++;
		//cout<<"�ۼƵ�:"<<accumulative<<endl;
	} 
	
	if(accumulative == 5) 
	{
		accumulative=0; //���ü���Ϊ0 
		return true;
	}
	else
	{
		//return false;
	}
	x = xReturnZero;
	y = yReturnZero;
	//���·�
	while(allchessman[++x][++y].message == message)
	{
		accumulative++;
		//cout<<"�ۼƵ�:"<<accumulative<<endl;
	} 
	/*
	if(accumulative == 5) 
	{
	accumulative=0; //���ü���Ϊ0 
	return true;
	}
	else
	{
	return false;
    } */ 
	x = xReturnZero;
	y = yReturnZero;
	//���Ϸ�
	while(allchessman[--x][--y].message == message)
	{
		accumulative++;
		//cout<<"�ۼƵ�:"<<accumulative<<endl;
	} 
	if(accumulative == 5) 
	{
		accumulative=0; //���ü���Ϊ0 
		return true;
	}
	else
	{
		//return false;
	} 
	x = xReturnZero;
	y = yReturnZero;
	//���Ϸ�
	while(allchessman[--x][++y].message == message)
	{
		accumulative++;
		//cout<<"�ۼƵ�:"<<accumulative<<endl;
	} 
	/* 
	if(accumulative == 5) 
	{
	accumulative=0; //���ü���Ϊ0 
	return true;
	}
	else
	{
	return false;
    } */ 
	x = xReturnZero;
	y = yReturnZero;
	//���·�
	while(allchessman[++x][--y].message == message)
	{
		accumulative++;
		//cout<<"�ۼƵ�:"<<accumulative<<endl;
	} 
	if(accumulative == 5) 
	{
		accumulative=0; //���ü���Ϊ0 
		return true;
	}
	else
	{
		return false;
	} 
}
//Ҫ�ڽ�������ʾ�ڷ��������Ӹ��� 
	
	
};