#include <stdio.h>
#include <conio.h> //����̨���������ͷ�ļ�
// getch();
#include <graphics.h> //ͷ�ļ� ����Ҫ��װͼ�ο�
//ͼ�ο��ͷ�ļ�
//�������ֵ�ͷ�ļ�
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")  //һ����̬��
#include <time.h>
/*
�Ȼع���ͼ�ο��֪ʶ��
�������� ������ɫ ��ͼ ��ͼ
������
Ȼ��һ���µ���ͼ����???
͸�����ַ�
͸��ɫ�ʷ�

Ȼ��ʼ������

*/

/*
int main()
{
initgraph(550,550,0); //����һ������
//�� �� ����̨

// ��ɫ RGB�Լ��涨����ֵȷ����ɫ
// ����ֱ�ӵ���Ԥ���ĺ�
// ������ɫ ���� ���� ����
setbkcolor(GREEN); //���ñ�����ɫ
cleardevice(); //ˢ����Ļ ʹ�����õı���ɫ
// ��ͼ��
setlinecolor(RED); //����������ɫ
setfillcolor(BLUE); //���������ɫ
//circle(100, 100, 50);	//����� ������
//solidcircle(200, 200, 50);//����� ������
//fillcircle(100, 200, 50);// ����� ������
//ͼ��������

//��ͼ
//Ҫ���ַ���
// ��Ŀ ���� ���� �ַ��� �ĳɶ��ַ���
IMAGE img; //����һ������ ͼƬ����
//loadimage(&img,"./res/XiaQi.jpg",0);
//loadimage(&img, "./res/XiaQi.jpg", 550,550);
//����ͼƬ ��������
//�ŵ���һ��ͼ�α���  ͼƬ��·�� ͼƬ�Ĵ�С(0��ʾ����Ӧ)
//Ҳ����ͼƬ����Ĵ�С
//·����ôд �����cppͬĿ¼ ֱ�Ӹ���ͼƬ����
//�����ͬĿ¼�µ���һ���ļ���
// ��./�����ļ��� ����/����ͼƬ����
//./res./res1/xiaqi.jpg
//��������ϼ�Ŀ¼ ��..
// �������д��ַ ������·��Ҳ����
//putimage(0,0,&img);
// ����ͼƬ�����Ͻ�  ������ͼ
//loadimage(0, "./res/XiaQi.jpg", 0);
//���loadimage�ĵ�һ������������������ַ
//ֱ�Ӹ�0 ����ֱ����ͼ

//NULL ��ʾ (void*)0
// 0   0
// ��� ��Ҫ����ͼƬ �����
// һ���Ե�

//mp3  wav ������ ��˵�������� ����̬��
mciSendString("open ./res/bgm.mp3 alias bgm",0,0,0);
// alias ����ȡ����  ������ȡ����
// ������  ������ͷ�ļ�
mciSendString("play bgm repeat",0,0,0);
// repeat��ʾ�ظ�����
//��������ص�;�� ������wav ������Դ�ļ�
PlaySound((LPCTSTR)��Դ��,GetModuleHandle(NULL),SND_RESOURCE| SND_ASYNC |SND_LOOP );
// SND_RESOURCE ��ʾ����Դ�л�ȡ
//SND_ASYNC �첽����
//SND_LOOP ѭ������
//��������
//

getchar();
closegraph(); //�رմ���

return 0;
}
*/

int Map[8][8] = {
	0, 0, 0, 1, 1, 1, 0, 0,
	0, 0, 0, 1, 3, 1, 0, 0,
	1, 1, 1, 1, 0, 1, 0, 0,
	1, 3, 4, 0, 4, 1, 1, 1,
	1, 1, 1, 5, 4, 0, 3, 1,
	0, 0, 1, 4, 1, 1, 1, 1,
	0, 0, 1, 3, 1, 0, 0, 0,
	0, 0, 1, 1, 1, 0, 0, 0
};

void Game_InitMap();//����ͼƬ
void Game_Paint(); //��ͼ
void Game_play(); //����
int Game_Judgement(); //�ж���Ϸ�Ƿ����
int lose();

time_t beginTime;
// ��ΪҪ��ͼ ����Ҫ��������
// ������ͼƬ���� ��ͼƬ����������
IMAGE BackImage, WallImage;  //����  ǽ
IMAGE Box1, Box2;   //����
IMAGE Tag1, Tag2;   //Ŀ�ĵ�
IMAGE Boom1, Boom2; //�����Ƶ�Ŀ�ĵ�
IMAGE Per1, Per2;   //��
IMAGE END;  //����
//IMAGE a[5];  //������Ŷ���ͼҲ�ǿ��Ե�
int lose()
{
	time_t now = time(NULL);  //��ȡ��ǰʱ��
	if (now - beginTime >= 180)//��ʱ300s ֱ�ӽ���
	{
		MessageBox(GetHWnd(), "����180sδ���", "Lose", MB_OK);
		closegraph();
		exit(0);
	}
}
void Game_InitMap()
{
	loadimage(&BackImage, "./res/Background.jpg", 550, 550);//����
	loadimage(&WallImage, "./res/Wall.jpg", 69, 69);//ǽ��

	loadimage(&Box2, "./res/Box.jpg", 69, 69);//����

	loadimage(&Tag2, "./res/Tag.jpg", 69, 69);//Ŀ�ĵ�

	loadimage(&Boom2, "./res/Boom.jpg", 69, 69);//���ӵ���Ŀ�ĵ�

	loadimage(&Per2, "./res/Person.jpg", 69, 69);//����

	loadimage(&END, "./res/1.jpg", 550, 550);//ʤ����Ʒ

}

void Game_InitMap2(int live) //�����ؿ��� �����ж��ǵڼ���
{
	//��Ϊ��ɫΪ��255,255,255�� �ͱ�������λ����� �õ�������ɫ  λ������ 
	//  255&120 1111 1111 &120 ---  120
	//��ɫ�ǣ�0��0,0�� �ͱ�������λ������ �õ�������ɫ
	// λ������ ֻ��ͬΪ0 �ŷ���0 
	// 0| 120---  0000 0000 | 120  120
	// û�б�Ҫ��ţ�Ǽ� 
	// ִ��  ��ִ
	loadimage(&BackImage, "./res/Background.jpg", 550, 550); //����
	loadimage(&WallImage, "./res/Wall.jpg", 69, 69);//ǽ

	loadimage(&Box1, "./res/Box1.jpg", 69, 69);//���Ӱ�ɫ
	loadimage(&Box2, "./res/Box.jpg", 69, 69);//����

	loadimage(&Tag1, "./res/Tag1.jpg", 69, 69);//Ŀ�ĵذ�ɫ
	loadimage(&Tag2, "./res/Tag.jpg", 69, 69);//Ŀ�ĵ�

	loadimage(&Boom1, "./res/Boom1.jpg", 69, 69);//���ӵ���Ŀ�ĵذ�ɫ
	loadimage(&Boom2, "./res/Boom.jpg", 69, 69);//���ӵ���Ŀ�ĵ�

	loadimage(&Per1, "./res/Person1.jpg", 69, 69);//�����ɫ
	loadimage(&Per2, "./res/Person.jpg", 69, 69);//����

	loadimage(&END, "./res/1.jpg", 550, 550);//ʤ����Ʒ

	//��������ӹؿ���
	// һ���ļ�����

	//66---  8*8 +2
	//10*10 --- 10*10+2 102
	FILE *fp = fopen("Map.txt", "r");
	// ����һ���ļ�ָ�� fopen��һ���ļ� 
	// ��һ��˫���Ÿ����ļ��� 
	// �ڶ���˫���ű�ʾ�򿪷�ʽ  r  read 

	if (NULL == fp)  //�����ʧ��  �쳣����
	{
		MessageBox(NULL, "��ͼ����ʧ��", NULL, NULL);
		exit(0);
		//  exit ֱ���˳�
	}

	int FileOffset; // �ļ���ƫ��
	FileOffset = 66 * (live - 1);
	// 66 = 64+2--- 8*8+2
	fseek(fp, FileOffset, SEEK_SET);
	// �����ҵ��ļ�ָ�뵱ǰ��λ��
	// �򿪵���һ���ļ�  ƫ����  �ļ���ʼ��λ��

	int i, j;
	char c;
	//�Ե�ͼ�ĳ�ʼ��
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			c = fgetc(fp);
			//getc() ���ļ��ж���һ���ַ�
			//c = getchar();
			Map[i][j] = c - '0';
			// ��Ϊ���ַ� ����Ҫ-48
		}
	}

	fclose(fp); //�ر��ļ�  ��д ��ֹ����

}
// ��һ��Ҫ�ĵĵط�


//��ͨ������ͼ
void Game_Paint()
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			switch (Map[j][i])
			{
			case 0: //�յ�
				break;
			case 1: //ǽ��
				putimage(69 * i, 69 * j, &WallImage);
				break;
			case 3://Ŀ�ĵ�
				putimage(69 * i, 69 * j, &Tag2);
				break;
			case 4://����
				putimage(69 * i, 69 * j, &Box2);
				break;
			case 5://����
				putimage(69 * i, 69 * j, &Per2);
				break;
			case 7://������Ŀ�ĵ���
				putimage(69 * i, 69 * j, &Boom2);
				break;
			case 8://������Ŀ�ĵ���
				putimage(69 * i, 69 * j, &Per2);
				break;
			}
		}
	}
}

/*
0       �յ�
1       ǽ��
3       Ŀ�ĵ�
4       ����
5       ����
7       ������Ŀ�ĵ�
8       ����Ŀ��
*/

//͸�����ַ���ͼ
void Game_Paint2()
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			switch (Map[j][i])
			{
			case 0: //�յ�
				break;
			case 1: //ǽ��
				putimage(69 * i, 69 * j, &WallImage);
				break;
			case 3://Ŀ�ĵ�
				putimage(69 * i, 69 * j, &Tag1, SRCPAINT);  //��������
				putimage(69 * i, 69 * j, &Tag2, SRCAND);   //��������
				break;
			case 4://����
				putimage(69 * i, 69 * j, &Box1, SRCPAINT);
				putimage(69 * i, 69 * j, &Box2, SRCAND);
				break;
			case 5://����
				putimage(69 * i, 69 * j, &Per1, SRCPAINT);
				putimage(69 * i, 69 * j, &Per2, SRCAND);
				break;
			case 7://������Ŀ�ĵ���
				putimage(69 * i, 69 * j, &Boom1, SRCPAINT);
				putimage(69 * i, 69 * j, &Boom2, SRCAND);
				break;
			case 8://������Ŀ�ĵ���
				putimage(69 * i, 69 * j, &Per1, SRCPAINT);
				putimage(69 * i, 69 * j, &Per2, SRCAND);
				break;
			}
		}
	}
}

int Game_Judgement()
{
	// �ж�ʱ�� �жϲ��� 
	//����1 
	// ��Ϊ��ͼ���Լ����� Ŀ�ĵص�λ������֪�� 
	//if (map[1][5]== 7 && map[2][4] ==7)

	// ����2
	//ѭ����������ͼ �ж���û�е���������
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (Map[i][j] == 4) //�ж� ��û�����ڿյ��ϵ�����
			{
				return 1;  //��Ϸ��û�н���
			}
		}
	}

	//��� �� ��ؿ��Ļ� 
	//
	return 0;
}

void Game_play()
//�ڶ���Ҫ�ĵĵط�
{
	char ch; //������ȡ�����������Ϣ
	// ASCII�� �� ���� --- �Ȼὲ
	int x, y; //������ǰ����
	int live = 1; //�����ؿ�
	Game_InitMap2(live); //��ͼ
	while (true)
	{
		lose();
		BeginBatchDraw();
		//�������������ͼ ������
		cleardevice();
		putimage(0, 0, &BackImage);
		//������
		mciSendString("open ./res/bgm.mp3 alias bgm", 0, 0, 0);
		mciSendString("play bgm repeat", 0, 0, 0);

		if (!Game_Judgement()) //�ж� ÿһ���Ƿ�������
		{
			live++;  // ������һ��
			if (6 == live) // 1 +1 +1 +1
			{
				Game_Paint2();// ��ͼ
				FlushBatchDraw(); //������ͼ ������
				MessageBox(GetHWnd(), "���سɹ�\r\n", "������ʾ", MB_OK);
				// �����Ի��� 
				// һ������ ���� 
				//��ʾ���
				//�˵�
				// ��ť ok  ����д���� һ��ok һ��ȡ��
				putimage(0, 0, &END);// ������ͼ
				settextcolor(RGB(0, 255, 0));
				settextstyle(40, 0, "����");
				setbkmode(TRANSPARENT);
				outtextxy(150, 400, "��Ժ����֮һ");
				FlushBatchDraw();
				Sleep(5000); //��1S ͣ��һ��
				closegraph(); //�رմ���
				exit(0); //��������
				// sleep  ������һ���Լ��ĵ��� ����֮���ܷ��
			}
			Game_InitMap2(live);
		} // ����ƽ��
		// ������ͼ �ҵ������Ķ�

		//������ͼҪ����
		Game_Paint2();
		EndBatchDraw();

		for (x = 0; x < 8; x++)
		{
			for (y = 0; y < 8; y++)
			{	//�������Ŀ�ĵ� ���� ���ڿյ�
				if (Map[x][y] == 5 || Map[x][y] == 8)
				{
					break;
					//goto SummerSeven;
				}
			}
			if (Map[x][y] == 5 || Map[x][y] == 8)
			{
				break;
			}
		}
		//SummerSeven:x = x;

		ch = _getch(); //��ȡ������Ϣ

		// �������� ���ж�Ӧ��ASCII��ֵ
		// ����һ���ֹ��ܼ� û�ж�Ӧ��ASCII��ֵ
		// ���� ���ܼ� ������ֵ��ʾ 
		//  �̶�ֵ �����ֵ
		//  224 72   0 --- F1~F10
		// �ú�һ��ֵ ȷ����ʲô���� 
		// ��ǰһ��ֵȷ�� ����Щ����

		//���� Map[x][y]
		switch (ch)
		{
		case 'w': //case ���д�͸�� �����һ��ƥ��ɹ�֮��û������break ��ô���������ƥ�� ֱ��break����switch����Ϊֹ
		case 72://����
			if (Map[x - 1][y] == 0 || Map[x - 1][y] == 3)
				//��ʾ��һ��λ����Ŀ�ĵػ��߿յ�
			{
				Map[x][y] -= 5; //ԭ���ĵط����˲�����
				// Map[x][y]=0;  ��Ϊ����ȷ����ǰλ���ǿյػ���Ŀ�ĵ�
				Map[x - 1][y] += 5; //����ȥ��
			}
			else if (Map[x - 1][y] == 4 || Map[x - 1][y] == 7)
				//���������һ������ ������һ����Ŀ�ĵص�����
			{
				if (Map[x - 2][y] == 0 || Map[x - 2][y] == 3)
					//����������ǿյػ���Ŀ�ĵ�
				{
					Map[x - 2][y] += 4; //�����Ƶ��������
					Map[x - 1][y] += 1; //�˵�������
					Map[x][y] -= 5; //����ȥ��
				}
			}
			break;
		case 75://����
			if (Map[x][y - 1] == 0 || Map[x][y - 1] == 3)
			{
				Map[x][y] -= 5;
				Map[x][y - 1] += 5;
			}
			else if (Map[x][y - 1] == 4 || Map[x][y - 1] == 7)
			{
				if (Map[x][y - 2] == 0 || Map[x][y - 2] == 3)
				{
					Map[x][y - 2] += 4;
					Map[x][y - 1] += 1;
					Map[x][y] -= 5;
				}
			}
			break;
		case 80:  // ����
			if (Map[x + 1][y] == 0 || Map[x + 1][y] == 3)
			{
				Map[x][y] -= 5;
				Map[x + 1][y] += 5;
			}
			else if (Map[x + 1][y] == 4 || Map[x + 1][y] == 7)
			{
				if (Map[x + 2][y] == 0 || Map[x + 2][y] == 3)
				{
					Map[x + 2][y] += 4;
					Map[x + 1][y] += 1;
					Map[x][y] -= 5;
				}
			}
			break;
		case 77:  //����
			if (Map[x][y + 1] == 0 || Map[x][y + 1] == 3)
			{
				Map[x][y] -= 5;
				Map[x][y + 1] += 5;
			}
			else if (Map[x][y + 1] == 4 || Map[x][y + 1] == 7)
			{
				if (Map[x][y + 2] == 0 || Map[x][y + 2] == 3)
				{
					Map[x][y + 2] += 4;
					Map[x][y + 1] += 1;
					Map[x][y] -= 5;
				}
			}
			break;
		}
	}
}

void welcome();
//Ҫ�����Դ�ļ���ͷ�ļ�
//  <> ""  ������
// <> �����ȴӿ��ļ��� ��ͷ�ļ�
// "" �����ȴ��Լ�д��ͷ�ļ�����

int main()
{
	initgraph(550, 550, 0);
	beginTime = time(NULL);
	welcome();
	Sleep(4000);
	//initgraph(550,550);

	Game_play();

	// ������Դ�ļ�
	// �Ҽ� ��Դ�ļ� ��� ��Դ 
	// ���� ѡ��ͼƬ ���� ������ֵ�ַ ����ɹ�
	//��ͷ�ļ�

	//IMAGE img;
	////loadimage(&img, "", 0, 0);
	//loadimage(&img, "jpg", MAKEINTRESOURCE(101),550,550);
	////������Դ�ļ�֮����ͼ�ĺ���
	//// ��һ���������� �ڶ������� ��ʾͼƬ����
	////������������ ͼƬ ()�� ����ͼƬ�ĺ�  
	//// ���������� ���� 0��ʾ����Ӧ Ҳ���Ǳ����С
	//putimage(0, 0, &img);
	//// ������Դ�ļ�֮��� ���� ----  wav
	//// ���ֵ���֮�� ֻ��ʹ�� PlaySound 
	//// ͼƬ jpg bmp  wav ico 
	////PlaySound((LPCTSTR)IDR_WAV1,GetModuleHandle(NULL),
	////	SND_RESOURCE | SND_ASYNC | SND_LOOP);
	//// SND_RESOURCE ��ʾ������Դ
	//// SND_ASYNC   ��ʾ�첽����
	//// SND_LOOP    ��ʾѭ������

	//getchar();
	//closegraph();

	// Ϊʲô����ĺ��� �����鷳
	// ��Ϊ���͸����˵�ʱ�� ���Խ�ʡ����

	//release �����汾
	// ��debug �ĳ�release  Ҫ�����޸��ַ���

	return 0;
}

//  �˵�  
//  ѡ��

//#include <time.h>
//
//int main()
//{
//	int t1, t2;
//	t1=clock(); // ������ȡ��ǰʱ��
//
//
//	t2 = clock(); 
//	t2 - t1;
//	return 0;
//}

//  ��׼�⺯�� 3-5���� 
//  atoi   strtol  time_t  srand 

//  ����  ������ ˫������ 
//  ѭ������ ˫��ѭ������ 

void welcome()
{
	IMAGE start;
	loadimage(&start, "res/2.jpg", 550, 550);
	putimage(0, 0, &start);
	settextstyle(50, 0, "���Ĳ���");
	settextcolor(RGB(255, 255, 255));
	setbkmode(0);
	outtextxy(100, 100, "     �� �� �� �� ");
	settextstyle(20, 0, "");
	outtextxy(390, 130, "1.10���԰�");

	settextcolor(RGB(255, 255, 255));
	outtextxy(90, 200, "����");
	outtextxy(90, 260, "��Ϸָ��:ǰ·���� һ�������ȫ�̱���");
	outtextxy(90, 220, "��Ϸ����:�������������вٿ�");
	outtextxy(90, 240, "��ϷĿ��:��ը��ը�����е���ͷ ��������С��");
	outtextxy(90, 280, "��ϷҪ��:���Ҫ��3���������ȫ�������ؿ�");
	settextstyle(25, 0, "");
    settextcolor(RGB(0, 255, 0));
	outtextxy(100, 390, "      5s���Զ�������Ϸ");

	settextstyle(20, 0,"");
	settextcolor(RGB(255, 0, 0));
	outtextxy(230, 500, "       �� �� �� QQ:2162304565");
}
