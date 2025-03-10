#pragma once

#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

#define Version_number "1.2"																	//版本号
#define CopyRight_C "CopyRight(C)2020 小陈"

time_t st_t(0), en_t(0);

inline void pause(void)
{
	printf("按任意键继续...");
	_getch();
	return;
}

inline int menu(void)																			//菜单
{
	int choise,input;
	printf("******************菜 单******************\n");
	printf("1)开始游戏                     2)玩法说明\n");
	printf("3)查看版权                     4)退出游戏\n");
	printf("*****************************************\n");
	printf("请选择:");
	while ((input = scanf("%d", &choise)) != 1 || (choise < 1 || choise>4))						//错误选择判断
	{
		if (input != 1)
			while (getchar() != '\n') continue;													//读取并丢弃字符直到\n
		printf("选择错误，请重新选择:");
	}
	return choise;																				//返回所选择的项目的值
}

inline void game(void)																			//游戏
{
	int num[4], num_s;
	srand((unsigned)time(NULL));																//设置随机专属种子
	for (int i = 0; i < 4; i++)
	{
	rand:
		num_s = rand() % (9 - 0 + 1) + 0;														//生成的随机数范围0~9
		for (int j = 0; j < i; j++)																// 遍历数组，出现相同的重新生成随机数
		{
			if (num[j] == num_s)
				goto rand;
		}
		num[i] = num_s;																			//确认后将生成的随机数按顺序赋值给数组
	}

	printf("游戏开始，请猜您的第一个数字:\n");

	int input[4], count = 0;
	unsigned int A = 0, B = 0;

	st_t = time(NULL);
	while (A < 4)																				//判断游戏是否胜利
	{
		A = B = 0;																				//重置A、B为0
	dhtt:																						//goto循环
		while (scanf("%1d%1d%1d%1d", &input[0], &input[1], &input[2], &input[3]) != 4)			//得到单字符输入，判断输入信息
		{
			while (getchar() != '\n') continue;													//类似于清空缓冲区
			printf("只有输入四位【数字】，才能开始猜测哦！\n\n");
		}
		while (getchar() != '\n') continue;

		//printf("%d %d %d %d\n", input[0], input[1], input[2], input[3]);
		//printf("%d %d %d %d\n", num[0], num[1], num[2], num[3]);

		for (int k = 0; k < 4; k++)
		{
			for (int l = 0; l < 4; l++)
			{
				if (input[k] == input[l] && k != l)
				{
					printf("只有输入【不重复】的四位数字，才能开始猜测哦！\n\n");
					goto dhtt;																	//goto循环
				}
			}
		}

		for (int m = 0; m < 4; m++)
		{
			if (num[m] == input[m])
				A++;
			for (int n = 0; n < 4; n++)
			{
				if (num[m] != input[m] && num[m] == input[n])
					B++;
			}
		}

		printf("%dA%dB\n\n", A, B);																//打印A、B的个数
		count++;

	}
	en_t = time(NULL);

	printf("游戏结束，您赢了！\n\n----数据统计:\n----您一共猜了%d次\n----用时%lld秒\n\n", count, en_t - st_t);
	pause();																					//等待用户的返回指令
	printf("\n\n");

	return;
}

inline void help(void)																			//帮助
{
	printf("游戏规则:\n"
		"应用会根据系统时间生成一个四位数，各位数字不会重复。\n"
		"游戏开始后，由玩家猜应用所生成的四位数，猜测的结果将会被应用以A和B来表示结果的正确与否。\n"
		"A前面跟一个数字，表示猜测的结果中有几个A，A代表猜测的数字中，数字相同且位置也正确。\n"
		"B前面跟一个数字，表示猜测的结果中有几个B，B代表猜测的数字中，数字相同但位置不一样。\n\n"
		"举例来说，如果应用生成的数字为1234，且你猜的数字为5283，其中2被猜到且位置正确，3也被猜到但位置不对，所以结果会出现1A1B。\n"
		"游戏在完整猜出所有数字后获得胜利（也就是得到4A0B时游戏结束）。\n\n\n");
	return;																						//结束函数（不要这个也行）
}

inline void copyright(void)
{
	printf("版权所有:%s\n版本号:%s\n\n", CopyRight_C, Version_number);
	return;
}

inline void gchoise(int * lchoise)																//游戏返回菜单
{
	printf("******************引 导******************\n");
	printf("1)返回菜单                     2)退出游戏\n");
	printf("*****************************************\n");
	printf("请选择:");

	int input = 0;

	while ((input = scanf("%d", &*lchoise)) != 1 || (*lchoise < 1 || *lchoise>2))
	{
		if (input != 1)
			while (getchar() != '\n') continue;
		printf("选择错误，请重新选择:");
	}

	system("cls");

	return;
}
