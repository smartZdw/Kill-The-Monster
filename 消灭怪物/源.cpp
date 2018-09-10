#include <stdio.h>
#include <conio.h> //控制台输入输出的头文件
// getch();
#include <graphics.h> //头文件 必须要安装图形库
//图形库的头文件
//播放音乐的头文件
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")  //一个静态库
#include <time.h>
/*
先回顾下图形库的知识点
创建窗口 设置颜色 画图 贴图
放音乐
然后讲一个新的贴图方法???
透明遮罩法
透明色彩法

然后开始搞事情

*/

/*
int main()
{
initgraph(550,550,0); //创建一个窗口
//长 宽 控制台

// 颜色 RGB自己规定三个值确定颜色
// 可以直接调用预留的宏
// 设置颜色 字体 背景 线条
setbkcolor(GREEN); //设置背景颜色
cleardevice(); //刷新屏幕 使用设置的背景色
// 画图形
setlinecolor(RED); //设置线条颜色
setfillcolor(BLUE); //设置填充颜色
//circle(100, 100, 50);	//无填充 有线条
//solidcircle(200, 200, 50);//有填充 无线条
//fillcircle(100, 200, 50);// 有填充 有线条
//图案有三种

//贴图
//要改字符集
// 项目 属性 常规 字符集 改成多字符集
IMAGE img; //定义一个变量 图片类型
//loadimage(&img,"./res/XiaQi.jpg",0);
//loadimage(&img, "./res/XiaQi.jpg", 550,550);
//载入图片 参数意义
//放到哪一个图形变量  图片的路径 图片的大小(0表示自适应)
//也就是图片本身的大小
//路径怎么写 如果是cpp同目录 直接给出图片名字
//如果在同目录下的另一个文件夹
// 用./进入文件夹 再用/给出图片名字
//./res./res1/xiaqi.jpg
//如果返回上级目录 用..
// 如果不会写地址 给绝对路径也可以
//putimage(0,0,&img);
// 贴的图片的左上角  贴哪张图
//loadimage(0, "./res/XiaQi.jpg", 0);
//如果loadimage的第一个参数不给出变量地址
//直接给0 可以直接贴图

//NULL 表示 (void*)0
// 0   0
// 如果 需要保存图片 多次贴
// 一次性的

//mp3  wav 网易云 听说有人用了 观望态度
mciSendString("open ./res/bgm.mp3 alias bgm",0,0,0);
// alias 用来取别名  给音乐取别名
// 打开音乐  上面有头文件
mciSendString("play bgm repeat",0,0,0);
// repeat表示重复播放
//如果有下载的途径 可以用wav 导入资源文件
PlaySound((LPCTSTR)资源名,GetModuleHandle(NULL),SND_RESOURCE| SND_ASYNC |SND_LOOP );
// SND_RESOURCE 表示从资源中获取
//SND_ASYNC 异步播放
//SND_LOOP 循环播放
//播放音乐
//

getchar();
closegraph(); //关闭窗口

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

void Game_InitMap();//加载图片
void Game_Paint(); //贴图
void Game_play(); //操作
int Game_Judgement(); //判断游戏是否结束
int lose();

time_t beginTime;
// 因为要贴图 所以要给出变量
// 可以用图片数组 把图片放在数组里
IMAGE BackImage, WallImage;  //背景  墙
IMAGE Box1, Box2;   //箱子
IMAGE Tag1, Tag2;   //目的地
IMAGE Boom1, Boom2; //箱子推到目的地
IMAGE Per1, Per2;   //人
IMAGE END;  //奖励
//IMAGE a[5];  //用数组放多张图也是可以的
int lose()
{
	time_t now = time(NULL);  //获取当前时间
	if (now - beginTime >= 180)//用时300s 直接结束
	{
		MessageBox(GetHWnd(), "超过180s未完成", "Lose", MB_OK);
		closegraph();
		exit(0);
	}
}
void Game_InitMap()
{
	loadimage(&BackImage, "./res/Background.jpg", 550, 550);//背景
	loadimage(&WallImage, "./res/Wall.jpg", 69, 69);//墙壁

	loadimage(&Box2, "./res/Box.jpg", 69, 69);//箱子

	loadimage(&Tag2, "./res/Tag.jpg", 69, 69);//目的地

	loadimage(&Boom2, "./res/Boom.jpg", 69, 69);//箱子到达目的地

	loadimage(&Per2, "./res/Person.jpg", 69, 69);//人物

	loadimage(&END, "./res/1.jpg", 550, 550);//胜利奖品

}

void Game_InitMap2(int live) //给出关卡数 用来判断是第几关
{
	//因为白色为（255,255,255） 和背景做按位与操作 得到背景颜色  位与运算 
	//  255&120 1111 1111 &120 ---  120
	//黑色是（0，0,0） 和背景做按位或运算 得到背景颜色
	// 位或运算 只有同为0 才返回0 
	// 0| 120---  0000 0000 | 120  120
	// 没有必要钻牛角尖 
	// 执着  固执
	loadimage(&BackImage, "./res/Background.jpg", 550, 550); //背景
	loadimage(&WallImage, "./res/Wall.jpg", 69, 69);//墙

	loadimage(&Box1, "./res/Box1.jpg", 69, 69);//箱子白色
	loadimage(&Box2, "./res/Box.jpg", 69, 69);//箱子

	loadimage(&Tag1, "./res/Tag1.jpg", 69, 69);//目的地白色
	loadimage(&Tag2, "./res/Tag.jpg", 69, 69);//目的地

	loadimage(&Boom1, "./res/Boom1.jpg", 69, 69);//箱子到达目的地白色
	loadimage(&Boom2, "./res/Boom.jpg", 69, 69);//箱子到达目的地

	loadimage(&Per1, "./res/Person1.jpg", 69, 69);//人物白色
	loadimage(&Per2, "./res/Person.jpg", 69, 69);//人物

	loadimage(&END, "./res/1.jpg", 550, 550);//胜利奖品

	//在这里添加关卡数
	// 一个文件操作

	//66---  8*8 +2
	//10*10 --- 10*10+2 102
	FILE *fp = fopen("Map.txt", "r");
	// 定义一个文件指针 fopen打开一个文件 
	// 第一对双引号给出文件名 
	// 第二对双引号表示打开方式  r  read 

	if (NULL == fp)  //如果打开失败  异常处理
	{
		MessageBox(NULL, "地图加载失败", NULL, NULL);
		exit(0);
		//  exit 直接退出
	}

	int FileOffset; // 文件的偏移
	FileOffset = 66 * (live - 1);
	// 66 = 64+2--- 8*8+2
	fseek(fp, FileOffset, SEEK_SET);
	// 用来找到文件指针当前的位置
	// 打开的哪一个文件  偏移量  文件开始的位置

	int i, j;
	char c;
	//对地图的初始化
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			c = fgetc(fp);
			//getc() 从文件中读出一个字符
			//c = getchar();
			Map[i][j] = c - '0';
			// 因为是字符 所以要-48
		}
	}

	fclose(fp); //关闭文件  先写 防止忘记

}
// 第一个要改的地方


//普通方法贴图
void Game_Paint()
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			switch (Map[j][i])
			{
			case 0: //空地
				break;
			case 1: //墙壁
				putimage(69 * i, 69 * j, &WallImage);
				break;
			case 3://目的地
				putimage(69 * i, 69 * j, &Tag2);
				break;
			case 4://箱子
				putimage(69 * i, 69 * j, &Box2);
				break;
			case 5://人物
				putimage(69 * i, 69 * j, &Per2);
				break;
			case 7://箱子在目的地上
				putimage(69 * i, 69 * j, &Boom2);
				break;
			case 8://人物在目的地上
				putimage(69 * i, 69 * j, &Per2);
				break;
			}
		}
	}
}

/*
0       空地
1       墙壁
3       目的地
4       箱子
5       人物
7       箱子在目的地
8       人在目的
*/

//透明遮罩法贴图
void Game_Paint2()
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			switch (Map[j][i])
			{
			case 0: //空地
				break;
			case 1: //墙壁
				putimage(69 * i, 69 * j, &WallImage);
				break;
			case 3://目的地
				putimage(69 * i, 69 * j, &Tag1, SRCPAINT);  //做或运算
				putimage(69 * i, 69 * j, &Tag2, SRCAND);   //做与运算
				break;
			case 4://箱子
				putimage(69 * i, 69 * j, &Box1, SRCPAINT);
				putimage(69 * i, 69 * j, &Box2, SRCAND);
				break;
			case 5://人物
				putimage(69 * i, 69 * j, &Per1, SRCPAINT);
				putimage(69 * i, 69 * j, &Per2, SRCAND);
				break;
			case 7://箱子在目的地上
				putimage(69 * i, 69 * j, &Boom1, SRCPAINT);
				putimage(69 * i, 69 * j, &Boom2, SRCAND);
				break;
			case 8://人物在目的地上
				putimage(69 * i, 69 * j, &Per1, SRCPAINT);
				putimage(69 * i, 69 * j, &Per2, SRCAND);
				break;
			}
		}
	}
}

int Game_Judgement()
{
	// 判断时间 判断步数 
	//方法1 
	// 因为地图是自己给的 目的地的位置是已知的 
	//if (map[1][5]== 7 && map[2][4] ==7)

	// 方法2
	//循环遍历整张图 判断有没有单独的箱子
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (Map[i][j] == 4) //判断 有没有落在空地上的箱子
			{
				return 1;  //游戏还没有结束
			}
		}
	}

	//如果 用 多关卡的话 
	//
	return 0;
}

void Game_play()
//第二个要改的地方
{
	char ch; //用来获取键盘输入的信息
	// ASCII码 和 键码 --- 等会讲
	int x, y; //描述当前坐标
	int live = 1; //描述关卡
	Game_InitMap2(live); //贴图
	while (true)
	{
		lose();
		BeginBatchDraw();
		//如果不用批量绘图 会闪屏
		cleardevice();
		putimage(0, 0, &BackImage);
		//贴背景
		mciSendString("open ./res/bgm.mp3 alias bgm", 0, 0, 0);
		mciSendString("play bgm repeat", 0, 0, 0);

		if (!Game_Judgement()) //判断 每一关是否玩完了
		{
			live++;  // 进入下一关
			if (6 == live) // 1 +1 +1 +1
			{
				Game_Paint2();// 绘图
				FlushBatchDraw(); //批量绘图 防闪屏
				MessageBox(GetHWnd(), "闯关成功\r\n", "闯关提示", MB_OK);
				// 弹出对话框 
				// 一个函数 作用 
				//提示语句
				//菜单
				// 按钮 ok  可以写两个 一个ok 一个取消
				putimage(0, 0, &END);// 贴结束图
				settextcolor(RGB(0, 255, 0));
				settextstyle(40, 0, "楷体");
				setbkmode(TRANSPARENT);
				outtextxy(150, 400, "唐院六少之一");
				FlushBatchDraw();
				Sleep(5000); //续1S 停留一秒
				closegraph(); //关闭窗口
				exit(0); //结束程序
				// sleep  可以试一下自己的电脑 休眠之后能否打开
			}
			Game_InitMap2(live);
		} // 出入平安
		// 遍历地图 找到人在哪儿

		//批量绘图要结束
		Game_Paint2();
		EndBatchDraw();

		for (x = 0; x < 8; x++)
		{
			for (y = 0; y < 8; y++)
			{	//如果人在目的地 或者 人在空地
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

		ch = _getch(); //获取键盘消息

		// 主键盘上 都有对应的ASCII码值
		// 还有一部分功能键 没有对应的ASCII码值
		// 键码 功能键 用两个值表示 
		//  固定值 有序的值
		//  224 72   0 --- F1~F10
		// 用后一个值 确定是什么功能 
		// 用前一个值确定 是哪些功能

		//人在 Map[x][y]
		switch (ch)
		{
		case 'w': //case 具有穿透性 如果第一个匹配成功之后没有遇到break 那么会继续往下匹配 直到break或者switch结束为止
		case 72://向上
			if (Map[x - 1][y] == 0 || Map[x - 1][y] == 3)
				//表示上一个位置是目的地或者空地
			{
				Map[x][y] -= 5; //原来的地方的人不见了
				// Map[x][y]=0;  因为不能确定当前位置是空地还是目的地
				Map[x - 1][y] += 5; //人上去了
			}
			else if (Map[x - 1][y] == 4 || Map[x - 1][y] == 7)
				//如果上面是一个箱子 或者是一个在目的地的箱子
			{
				if (Map[x - 2][y] == 0 || Map[x - 2][y] == 3)
					//上面的上面是空地或者目的地
				{
					Map[x - 2][y] += 4; //箱子推到面的上面
					Map[x - 1][y] += 1; //人到了上面
					Map[x][y] -= 5; //人上去了
				}
			}
			break;
		case 75://向左
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
		case 80:  // 往下
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
		case 77:  //往右
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
//要添加资源文件的头文件
//  <> ""  的区别
// <> 会优先从库文件中 找头文件
// "" 会优先从自己写的头文件中找

int main()
{
	initgraph(550, 550, 0);
	beginTime = time(NULL);
	welcome();
	Sleep(4000);
	//initgraph(550,550);

	Game_play();

	// 导入资源文件
	// 右键 资源文件 添加 资源 
	// 导入 选择图片 导入 如果出现地址 导入成功
	//打开头文件

	//IMAGE img;
	////loadimage(&img, "", 0, 0);
	//loadimage(&img, "jpg", MAKEINTRESOURCE(101),550,550);
	////导入资源文件之后贴图的函数
	//// 第一个参数不变 第二个参数 表示图片种类
	////第三个参数是 图片 ()内 给出图片的宏  
	//// 后两个参数 不变 0表示自适应 也就是本身大小
	//putimage(0, 0, &img);
	//// 导入资源文件之后的 音乐 ----  wav
	//// 音乐导入之后 只能使用 PlaySound 
	//// 图片 jpg bmp  wav ico 
	////PlaySound((LPCTSTR)IDR_WAV1,GetModuleHandle(NULL),
	////	SND_RESOURCE | SND_ASYNC | SND_LOOP);
	//// SND_RESOURCE 表示来自资源
	//// SND_ASYNC   表示异步播放
	//// SND_LOOP    表示循环播放

	//getchar();
	//closegraph();

	// 为什么导入的函数 反而麻烦
	// 因为发送给别人的时候 可以节省东西

	//release 发布版本
	// 将debug 改成release  要重新修改字符集

	return 0;
}

//  菜单  
//  选关

//#include <time.h>
//
//int main()
//{
//	int t1, t2;
//	t1=clock(); // 用来获取当前时间
//
//
//	t2 = clock(); 
//	t2 - t1;
//	return 0;
//}

//  标准库函数 3-5函数 
//  atoi   strtol  time_t  srand 

//  链表  单链表 双向链表 
//  循环链表 双向循环链表 

void welcome()
{
	IMAGE start;
	loadimage(&start, "res/2.jpg", 550, 550);
	putimage(0, 0, &start);
	settextstyle(50, 0, "华文彩云");
	settextcolor(RGB(255, 255, 255));
	setbkmode(0);
	outtextxy(100, 100, "     消 灭 怪 兽 ");
	settextstyle(20, 0, "");
	outtextxy(390, 130, "1.10测试版");

	settextcolor(RGB(255, 255, 255));
	outtextxy(90, 200, "技巧");
	outtextxy(90, 260, "游戏指导:前路漫漫 一步错可能全盘崩溃");
	outtextxy(90, 220, "游戏操作:按↑↓←→进行操控");
	outtextxy(90, 240, "游戏目的:用炸蛋炸死所有的猪头 才能拯救小鸟");
	outtextxy(90, 280, "游戏要求:玩家要在3分钟内完成全部六个关卡");
	settextstyle(25, 0, "");
    settextcolor(RGB(0, 255, 0));
	outtextxy(100, 390, "      5s后自动进入游戏");

	settextstyle(20, 0,"");
	settextcolor(RGB(255, 0, 0));
	outtextxy(230, 500, "       开 发 者 QQ:2162304565");
}
