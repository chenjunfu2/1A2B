#pragma once

#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>

//�汾�š���Ϣ
#define Version_number "1.3"																	
#define CopyRight_C "CopyRight (C) 2020~2025 chenjunfu2"

inline void Pause(void)
{
	printf("�����������...");
	(void)_getch();
}

//��ȡ�������ַ�ֱ��\n
inline void JumpLine(void)
{
	while (getchar() != '\n') continue;
}

//����
inline void ClearScreen(void)
{
	system("cls");
}

int GetInputInt(int iBeg, int iEnd)
{
	printf("��ѡ��:");
	int iChoise = 0;
	while (true)
	{
		if (scanf("%d", &iChoise) != 1)
		{
			JumpLine();
			printf("�����������������:");
			continue;//����
		}

		//��������ʣ������
		JumpLine();

		if (iChoise < iBeg || iChoise > iEnd)
		{
			printf("��Χ��������������:");
			continue;//����
		}

		break;//ִ�е�������֤ȫ��ͨ��
	}

	return iChoise;
}


//�˵�
inline void PrintMenu(void)
{
	printf("1A2B������С��Ϸ\n\n");
	printf("******************�� ��******************\n");
	printf("1)��ʼ��Ϸ                     2)�淨˵��\n");
	printf("3)�鿴��Ȩ                     4)�˳���Ϸ\n");
	printf("*****************************************\n");
}

//�û�ѡ��
inline int MenuSwitch(void)
{
	return GetInputInt(1, 4);
}

//����
inline void PrintHelp(void)
{
	printf("��Ϸ����:\n"
		"Ӧ�û����ϵͳʱ������һ����λ������λ���ֲ����ظ���\n"
		"��Ϸ��ʼ������Ҳ�Ӧ�������ɵ���λ�����²�Ľ�����ᱻӦ����A��B����ʾ�������ȷ���\n"
		"Aǰ���һ�����֣���ʾ�²�Ľ�����м���A��A����²�������У�������ͬ��λ��Ҳ��ȷ��\n"
		"Bǰ���һ�����֣���ʾ�²�Ľ�����м���B��B����²�������У�������ͬ��λ�ò�һ����\n\n"
		"������˵�����Ӧ�����ɵ�����Ϊ1234������µ�����Ϊ5283������2���µ���λ����ȷ��3Ҳ���µ���λ�ò��ԣ����Խ�������1A1B��\n"
		"��Ϸ�������³��������ֺ���ʤ����Ҳ���ǵõ�4A0Bʱ��Ϸ��������\n\n\n");
}

inline void PrintCPR(void)
{
	printf("��Ȩ����:%s\n�汾��:%s\n\n", CopyRight_C, Version_number);
}

//��Ϸ���ز˵�
inline void PrintSubMenu(void)
{
	printf("******************�� ��******************\n");
	printf("1)���ز˵�                     2)�˳���Ϸ\n");
	printf("*****************************************\n");
}

inline void Exit(void)
{
	exit(0);
}

//�û�ѡ��
inline int SubMenuSwitch(void)
{
	return GetInputInt(1, 2);
}

//��ʼ�������������
inline void InitRandom(void)
{
	srand((unsigned)time(NULL));
}

//ʹ�þܾ������������������Χ
inline int GetRandom(int iBeg, int iEnd)
{
	int iRange = iEnd - iBeg + 1;
	int iLimit = RAND_MAX - (RAND_MAX % iRange);//�ܾ����������ֵ����������

	int iRandomNum = 0;
	do
	{
		iRandomNum = rand();
	} while (iRandomNum >= iLimit);//������Χ���ܾ���������������

	return iRandomNum % iRange + iBeg;//���ط�Χ�ڵ�ֵ
}


//��Ϸ
inline void GameLoop(void)																			
{
	//��ʼ�������������
	InitRandom();

	//����4�����ظ�����
	int iNumsSwitch[] = { 0,1,2,3,4,5,6,7,8,9 };//�������ɵ����飬ÿ��������ѡ���ɾ��
	int iSwitchEnd = sizeof(iNumsSwitch) / sizeof(iNumsSwitch[0]) - 1;//ĩβ��Χ
	int iRandNums[4] = { 0 };

	for (int i = 0; i < 4; ++i)
	{
		//��iNumsSwitch�о���ѡ��1��ֵ��Ϊ��һ��
		int iSwitchRand = GetRandom(0, iSwitchEnd);
		iRandNums[i] = iNumsSwitch[iSwitchRand];

		//Ȼ�������ɾ����ֵ����ĩβֵ��ֵ����ǰ������ĩβ��һ��
		iNumsSwitch[iSwitchRand] = iNumsSwitch[iSwitchEnd];
		--iSwitchEnd;//�����´����ɵ�ʱ����ڽ�ʣ������ֵ�о���ѡ��
	}

	printf("��Ϸ��ʼ��������ĵ�һ������:\n");
	int iGuessCount = 0;
	time_t tBeg = time(NULL);//���濪ʼʱ��
	while (true)
	{
		int A = 0, B = 0;//����A��BΪ0

		int iInputNums[4] = { 0 };
		while (true)			//�õ����ַ����룬�ж�������Ϣ
		{
		RE_TRY:
			if (scanf("%1d%1d%1d%1d", &iInputNums[0], &iInputNums[1], &iInputNums[2], &iInputNums[3]) != 4)
			{
				JumpLine();
				printf("ֻ��������λ�����֡������ܿ�ʼ�²�Ŷ��\n\n");
				continue;
			}

			JumpLine();

			bool bUsedNum[10] = { 0 };//������֤�Ƿ��ظ�ʹ������
			for (int i = 0; i < 4; ++i)
			{
				int iCurrent = iInputNums[i];

				if (iCurrent < 0 || iCurrent > 9)
				{
					goto RE_TRY;//��֤ʧ�ܣ�����
				}

				//ȷ����Χû���⣬����bool�����ڽ��в����ж�
				if (bUsedNum[iCurrent] == true)
				{
					printf("ֻ�����롾���ظ�������λ���֣����ܿ�ʼ�²�Ŷ��\n\n");
					goto RE_TRY;//��֤ʧ�ܣ�����
				}

				//��֤ͨ��������ֵ
				bUsedNum[iCurrent] = true;
			}

			//��֤ͨ�����˳�
			break;
		}
		

		for (int i = 0, j = 0; i < 4; ++i)
		{
			if (iRandNums[i] == iInputNums[i])//ͳ��λ����ȷ����ֵ��ȷ
			{
				++A;
				continue;//������һ��
			}

			//ͳ��λ�ò���ȷ
			for (int j = 0; j < 4; ++j)//��ͷ��ʼ���ҵ�ǰֵ����ƥ��
			{
				if (i != j && iRandNums[i] == iInputNums[j])//ͳ��λ�ò���ȷ����ֵ��ȷ
				{
					++B;
					break;//�ҵ�һ�������˳�����Ϊ�ǲ��ظ���
				}
			}
		}

		printf("%dA%dB\n\n", A, B);//��ӡA��B�ĸ���
		if (A == 4)
		{
			break;//Ӯ�ˣ��뿪ѭ��
		}

		//��������²����
		iGuessCount++;
	}
	time_t tEnd = time(NULL);

	printf("��Ϸ��������Ӯ�ˣ�\n\n����ͳ��:\n---��һ������%d��\n---��ʱ%lld��\n\n", iGuessCount, tEnd - tBeg);
	Pause();//�ȴ��û��ķ���ָ��
	printf("\n\n");
}

inline void MenuLoop(void)
{
	typedef void(*CALL_FUNC)(void);
	CALL_FUNC funcMenuSwitch[] =
	{
		GameLoop,PrintHelp,PrintCPR,Exit,
	};
	CALL_FUNC funcSubMenuSwitch[] =
	{
		ClearScreen,Exit,
	};

	//��ʼ��ѡ��������

	while (true)								//�ж��Ƿ��˳���Ϸ
	{
		//��ӡ�˵�
		PrintMenu();
		{
			//��ȡ�û�ѡ��
			int iSwitch = MenuSwitch();
			ClearScreen();
			printf("��ѡ����:%d\n\n", iSwitch);
			//ִ��
			funcMenuSwitch[iSwitch - 1]();//��һ�õ�0��������������
		}
		//��ӡ�����˵�
		PrintSubMenu();
		{
			//��ȡ�û�ѡ��
			int iSwitch = SubMenuSwitch();
			//ִ��
			funcSubMenuSwitch[iSwitch - 1]();//��һ�õ�0��������������
		}
	}
}