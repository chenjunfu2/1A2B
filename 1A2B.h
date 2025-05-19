#pragma once

#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//版本号、信息
#define Project_Name "1A2B"
#define Project_Version "V1.4"																	
#define CopyRight_C "CopyRight(C)2020~2025 chenjunfu2"
#define Project_Link "https://github.com/chenjunfu2/1A2B"

//读取并丢弃字符直到\n
inline void JumpLine(void)
{
	while (getchar() != '\n') continue;
}

//清屏
inline void ClearScreen(void)
{
	system("cls");
}

int GetInputInt(int iBeg, int iEnd)
{
	printf("请选择:");
	int iChoise = 0;
	while (true)
	{
		if (scanf("%d", &iChoise) != 1)
		{
			JumpLine();
			printf("输入错误，请重新输入:");
			continue;//重试
		}

		//清理缓冲区剩余内容
		JumpLine();

		if (iChoise < iBeg || iChoise > iEnd)
		{
			printf("范围错误，请重新输入:");
			continue;//重试
		}

		break;//执行到此则验证全部通过
	}

	return iChoise;
}

int PeekChar(void)
{
	int iGet = getchar();
	ungetch(iGet);
	return iGet;
}


//菜单
inline void PrintMenu(void)
{
	printf("1A2B猜数字小游戏\n\n");
	printf("******************菜 单******************\n");
	printf("1)开始游戏                     2)玩法说明\n");
	printf("3)查看版权                     4)退出游戏\n");
	printf("*****************************************\n");
}

//用户选择
inline int MenuSwitch(void)
{
	return GetInputInt(1, 4);
}

//帮助
inline void PrintHelp(void)
{
	printf("游戏规则:\n"
		"应用会根据系统时间生成一个四位数，各位数字不会重复。\n"
		"游戏开始后，由玩家猜应用所生成的四位数，猜测的结果将会被应用以A和B来表示结果的正确与否。\n"
		"A前面跟一个数字，表示猜测的结果中有几个A，A代表猜测的数字中，数字相同且位置也正确。\n"
		"B前面跟一个数字，表示猜测的结果中有几个B，B代表猜测的数字中，数字相同但位置不一样。\n\n"
		"举例来说，如果应用生成的数字为1234，且你猜的数字为5283，其中2被猜到且位置正确，3也被猜到但位置不对，所以结果会出现1A1B。\n"
		"游戏在完整猜出所有数字后获得胜利（也就是得到4A0B时游戏结束）。\n\n\n");
}

inline void PrintCPR(void)
{
	printf("%s [%s]\n%s\n\n", Project_Name, Project_Version, CopyRight_C);
	printf("链接: %s\n\n", Project_Link);
}

//游戏返回菜单
inline void PrintSubMenu(void)
{
	printf("******************引 导******************\n");
	printf("1)返回菜单                     2)退出游戏\n");
	printf("*****************************************\n");
}

//用户选择
inline int SubMenuSwitch(void)
{
	return GetInputInt(1, 2);
}

//游戏结束菜单
inline void PrintGameEndMenu(void)
{
	printf("******************引 导******************\n");
	printf("1)再来一局                     2)返回菜单\n");
	printf("*****************************************\n");
}

//用户选择
inline int GameEndMenuSwitch(void)
{
	return GetInputInt(1, 2);
}

inline void Exit(void)
{
	exit(0);
}

//初始化随机数生成器
inline void InitRandom(void)
{
	srand((unsigned)time(NULL));
}

//使用拒绝采样法生成随机数范围
inline int GetRandom(int iBeg, int iEnd)
{
	int iRange = iEnd - iBeg + 1;
	int iLimit = RAND_MAX - (RAND_MAX % iRange);//拒绝采样法最大值（不包含）

	int iRandomNum = 0;
	do
	{
		iRandomNum = rand();
	} while (iRandomNum >= iLimit);//超出范围，拒绝采样，重新生成

	return iRandomNum % iRange + iBeg;//返回范围内的值
}


inline void Rand4NoRepeatNum(int iRandNums[4])
{
	//生成4个不重复的数
	int iNumsSwitch[] = { 0,1,2,3,4,5,6,7,8,9 };//用于生成的数组，每次在其中选择后删除
	int iSwitchEnd = sizeof(iNumsSwitch) / sizeof(iNumsSwitch[0]) - 1;//末尾范围

	for (int i = 0; i < 4; ++i)
	{
		//从iNumsSwitch中均匀选择1个值作为第一个
		int iSwitchRand = GetRandom(0, iSwitchEnd);
		iRandNums[i] = iNumsSwitch[iSwitchRand];

		//然后从其中删除此值（把末尾值赋值给当前，并将末尾减一）
		iNumsSwitch[iSwitchRand] = iNumsSwitch[iSwitchEnd];
		--iSwitchEnd;//这样下次生成的时候会在仅剩的其余值中均匀选择
	}
}


inline bool Get4NoRepeatNum(int iInputNums[4])
{
	//读取输入
	while (true)
	{
		//得到单数字输入，判断输入信息
		int iRet = scanf("%1d%1d%1d%1d", &iInputNums[0], &iInputNums[1], &iInputNums[2], &iInputNums[3]);
		if (iRet != 4)
		{
			int iGet = PeekChar();//偷看一个字符
			JumpLine();//然后跳过整行
			if (iGet == 'q' || iGet == 'Q')//只要是q开头的，则退出
			{
				return false;
			}

			//否则提示错误
			printf("需要四位【数字】\n\n");
			continue;//重试
		}

		//删掉剩余无用垃圾数据
		JumpLine();

		bool bVerify = true;//用于确认是否完整通过验证
		bool bUsedNum[10] = { 0 };//用于验证是否重复使用数字
		for (int i = 0; i < 4; ++i)
		{
			int iCurrent = iInputNums[i];

			if (iCurrent < 0 || iCurrent > 9)
			{
				bVerify = false;
				break;//跳出for
			}

			//确定范围没问题，则在bool数组内进行查重判断
			if (bUsedNum[iCurrent] == true)
			{
				printf("需要【不重复】的四位数字\n\n");
				bVerify = false;
				break;//跳出for
			}

			//验证通过，设置值
			bUsedNum[iCurrent] = true;
		}

		if (bVerify == true)
		{
			break;//验证通过，退出while
		}
		//否则继续重试
	}

	return true;
}

typedef struct
{
	int A, B;
}ValAB;

inline ValAB CalcAB(const int iRandNums[4], const int iInputNums[4])
{
	int A = 0, B = 0;
	//计算A、B的个数
	for (int i = 0, j = 0; i < 4; ++i)
	{
		if (iRandNums[i] == iInputNums[i])//统计位置正确且数值正确
		{
			++A;
			continue;//继续下一个
		}

		//统计位置不正确
		for (int j = 0; j < 4; ++j)//从头开始查找当前值有无匹配
		{
			if (i != j && iRandNums[i] == iInputNums[j])//统计位置不正确但数值正确
			{
				++B;
				break;//找到一个即可退出，因为是不重复的
			}
		}
	}
	return (ValAB){ A,B };
}

//游戏
inline void GameLoop(void)																			
{
	//初始化随机数生成器
	InitRandom();
	//生成4个不重复的随机数
	int iRandNums[4];
	Rand4NoRepeatNum(iRandNums);
	
	//准备变量用于统计和判断输赢
	int iGuessCount = 0;
	bool bWin;

	printf("游戏开始，请猜数字，输入q退出:\n");
	time_t tBeg = time(NULL);//保存开始时间
	while (true)
	{
		int iInputNums[4];
		if (!Get4NoRepeatNum(iInputNums))//用户触发退出
		{
			bWin = false;
			break;
		}

		//递增猜测计数
		iGuessCount++;

		//计算AB值
		ValAB tmpAB = CalcAB(iRandNums, iInputNums);
		printf("%dA%dB\n\n", tmpAB.A, tmpAB.B);

		//赢了则离开
		if (tmpAB.A == 4)
		{
			bWin = true;
			break;
		}
	}
	time_t tEnd = time(NULL);//保存结束时间

	//显示不同信息
	if (bWin)
	{
		printf("游戏结束，您赢了！\n\n");
	}
	else
	{
		printf("\n游戏结束，您输了！\n目标数字为:[%1d%1d%1d%1d]\n\n",
			iRandNums[0], iRandNums[1], iRandNums[2], iRandNums[3]);
	}

	printf("数据统计:\n---您一共猜了%d次\n---用时%lld秒\n\n", iGuessCount, tEnd - tBeg);
}

inline void MenuLoop(void)
{
	//初始化选择函数数组
	typedef void(*CALL_FUNC)(void);
	CALL_FUNC funcMenuSwitch[] =
	{
		GameLoop,PrintHelp,PrintCPR,Exit,
	};
	CALL_FUNC funcSubMenuSwitch[] =
	{
		ClearScreen,Exit,
	};

	while (true)
	{
		int iSwitch;

		//打印菜单
		PrintMenu();
		//获取用户选择
		iSwitch = MenuSwitch();
		ClearScreen();

	Restart_Game:
		printf("您选择了:%d\n\n", iSwitch);
		//执行
		funcMenuSwitch[iSwitch - 1]();//减一得到0基索引访问数组

		//刚才选择的是1，游戏模式
		if (iSwitch == 1)
		{
			//打印游戏结束菜单
			PrintGameEndMenu();
			iSwitch = GameEndMenuSwitch();
			ClearScreen();//清屏
			if (iSwitch == 1)//再来一局
			{
				goto Restart_Game;
			}
		}
		else//选择其他则打印普通二级菜单
		{
			//打印二级菜单
			PrintSubMenu();
			//获取用户选择
			iSwitch = SubMenuSwitch();
			//执行
			funcSubMenuSwitch[iSwitch - 1]();//减一得到0基索引访问数组
		}
	}
}