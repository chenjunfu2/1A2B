#pragma once

#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//�汾�š���Ϣ
#define Project_Name "1A2B"
#define Project_Version "V1.4"																	
#define CopyRight_C "CopyRight(C)2020~2025 chenjunfu2"
#define Project_Link "https://github.com/chenjunfu2/1A2B"

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

int PeekChar(void)
{
	int iGet = getchar();
	ungetch(iGet);
	return iGet;
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
	printf("%s [%s]\n%s\n\n", Project_Name, Project_Version, CopyRight_C);
	printf("����: %s\n\n", Project_Link);
}

//��Ϸ���ز˵�
inline void PrintSubMenu(void)
{
	printf("******************�� ��******************\n");
	printf("1)���ز˵�                     2)�˳���Ϸ\n");
	printf("*****************************************\n");
}

//�û�ѡ��
inline int SubMenuSwitch(void)
{
	return GetInputInt(1, 2);
}

//��Ϸ�����˵�
inline void PrintGameEndMenu(void)
{
	printf("******************�� ��******************\n");
	printf("1)����һ��                     2)���ز˵�\n");
	printf("*****************************************\n");
}

//�û�ѡ��
inline int GameEndMenuSwitch(void)
{
	return GetInputInt(1, 2);
}

inline void Exit(void)
{
	exit(0);
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


inline void Rand4NoRepeatNum(int iRandNums[4])
{
	//����4�����ظ�����
	int iNumsSwitch[] = { 0,1,2,3,4,5,6,7,8,9 };//�������ɵ����飬ÿ��������ѡ���ɾ��
	int iSwitchEnd = sizeof(iNumsSwitch) / sizeof(iNumsSwitch[0]) - 1;//ĩβ��Χ

	for (int i = 0; i < 4; ++i)
	{
		//��iNumsSwitch�о���ѡ��1��ֵ��Ϊ��һ��
		int iSwitchRand = GetRandom(0, iSwitchEnd);
		iRandNums[i] = iNumsSwitch[iSwitchRand];

		//Ȼ�������ɾ����ֵ����ĩβֵ��ֵ����ǰ������ĩβ��һ��
		iNumsSwitch[iSwitchRand] = iNumsSwitch[iSwitchEnd];
		--iSwitchEnd;//�����´����ɵ�ʱ����ڽ�ʣ������ֵ�о���ѡ��
	}
}


inline bool Get4NoRepeatNum(int iInputNums[4])
{
	//��ȡ����
	while (true)
	{
		//�õ����������룬�ж�������Ϣ
		int iRet = scanf("%1d%1d%1d%1d", &iInputNums[0], &iInputNums[1], &iInputNums[2], &iInputNums[3]);
		if (iRet != 4)
		{
			int iGet = PeekChar();//͵��һ���ַ�
			JumpLine();//Ȼ����������
			if (iGet == 'q' || iGet == 'Q')//ֻҪ��q��ͷ�ģ����˳�
			{
				return false;
			}

			//������ʾ����
			printf("��Ҫ��λ�����֡�\n\n");
			continue;//����
		}

		//ɾ��ʣ��������������
		JumpLine();

		bool bVerify = true;//����ȷ���Ƿ�����ͨ����֤
		bool bUsedNum[10] = { 0 };//������֤�Ƿ��ظ�ʹ������
		for (int i = 0; i < 4; ++i)
		{
			int iCurrent = iInputNums[i];

			if (iCurrent < 0 || iCurrent > 9)
			{
				bVerify = false;
				break;//����for
			}

			//ȷ����Χû���⣬����bool�����ڽ��в����ж�
			if (bUsedNum[iCurrent] == true)
			{
				printf("��Ҫ�����ظ�������λ����\n\n");
				bVerify = false;
				break;//����for
			}

			//��֤ͨ��������ֵ
			bUsedNum[iCurrent] = true;
		}

		if (bVerify == true)
		{
			break;//��֤ͨ�����˳�while
		}
		//�����������
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
	//����A��B�ĸ���
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
	return (ValAB){ A,B };
}

//��Ϸ
inline void GameLoop(void)																			
{
	//��ʼ�������������
	InitRandom();
	//����4�����ظ��������
	int iRandNums[4];
	Rand4NoRepeatNum(iRandNums);
	
	//׼����������ͳ�ƺ��ж���Ӯ
	int iGuessCount = 0;
	bool bWin;

	printf("��Ϸ��ʼ��������֣�����q�˳�:\n");
	time_t tBeg = time(NULL);//���濪ʼʱ��
	while (true)
	{
		int iInputNums[4];
		if (!Get4NoRepeatNum(iInputNums))//�û������˳�
		{
			bWin = false;
			break;
		}

		//�����²����
		iGuessCount++;

		//����ABֵ
		ValAB tmpAB = CalcAB(iRandNums, iInputNums);
		printf("%dA%dB\n\n", tmpAB.A, tmpAB.B);

		//Ӯ�����뿪
		if (tmpAB.A == 4)
		{
			bWin = true;
			break;
		}
	}
	time_t tEnd = time(NULL);//�������ʱ��

	//��ʾ��ͬ��Ϣ
	if (bWin)
	{
		printf("��Ϸ��������Ӯ�ˣ�\n\n");
	}
	else
	{
		printf("\n��Ϸ�����������ˣ�\nĿ������Ϊ:[%1d%1d%1d%1d]\n\n",
			iRandNums[0], iRandNums[1], iRandNums[2], iRandNums[3]);
	}

	printf("����ͳ��:\n---��һ������%d��\n---��ʱ%lld��\n\n", iGuessCount, tEnd - tBeg);
}

inline void MenuLoop(void)
{
	//��ʼ��ѡ��������
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

		//��ӡ�˵�
		PrintMenu();
		//��ȡ�û�ѡ��
		iSwitch = MenuSwitch();
		ClearScreen();

	Restart_Game:
		printf("��ѡ����:%d\n\n", iSwitch);
		//ִ��
		funcMenuSwitch[iSwitch - 1]();//��һ�õ�0��������������

		//�ղ�ѡ�����1����Ϸģʽ
		if (iSwitch == 1)
		{
			//��ӡ��Ϸ�����˵�
			PrintGameEndMenu();
			iSwitch = GameEndMenuSwitch();
			ClearScreen();//����
			if (iSwitch == 1)//����һ��
			{
				goto Restart_Game;
			}
		}
		else//ѡ���������ӡ��ͨ�����˵�
		{
			//��ӡ�����˵�
			PrintSubMenu();
			//��ȡ�û�ѡ��
			iSwitch = SubMenuSwitch();
			//ִ��
			funcSubMenuSwitch[iSwitch - 1]();//��һ�õ�0��������������
		}
	}
}