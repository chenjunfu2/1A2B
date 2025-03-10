#pragma once

#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

#define Version_number "1.2"																	//�汾��
#define CopyRight_C "CopyRight(C)2020 С��"

time_t st_t(0), en_t(0);

inline void pause(void)
{
	printf("�����������...");
	_getch();
	return;
}

inline int menu(void)																			//�˵�
{
	int choise,input;
	printf("******************�� ��******************\n");
	printf("1)��ʼ��Ϸ                     2)�淨˵��\n");
	printf("3)�鿴��Ȩ                     4)�˳���Ϸ\n");
	printf("*****************************************\n");
	printf("��ѡ��:");
	while ((input = scanf("%d", &choise)) != 1 || (choise < 1 || choise>4))						//����ѡ���ж�
	{
		if (input != 1)
			while (getchar() != '\n') continue;													//��ȡ�������ַ�ֱ��\n
		printf("ѡ�����������ѡ��:");
	}
	return choise;																				//������ѡ�����Ŀ��ֵ
}

inline void game(void)																			//��Ϸ
{
	int num[4], num_s;
	srand((unsigned)time(NULL));																//�������ר������
	for (int i = 0; i < 4; i++)
	{
	rand:
		num_s = rand() % (9 - 0 + 1) + 0;														//���ɵ��������Χ0~9
		for (int j = 0; j < i; j++)																// �������飬������ͬ���������������
		{
			if (num[j] == num_s)
				goto rand;
		}
		num[i] = num_s;																			//ȷ�Ϻ����ɵ��������˳��ֵ������
	}

	printf("��Ϸ��ʼ��������ĵ�һ������:\n");

	int input[4], count = 0;
	unsigned int A = 0, B = 0;

	st_t = time(NULL);
	while (A < 4)																				//�ж���Ϸ�Ƿ�ʤ��
	{
		A = B = 0;																				//����A��BΪ0
	dhtt:																						//gotoѭ��
		while (scanf("%1d%1d%1d%1d", &input[0], &input[1], &input[2], &input[3]) != 4)			//�õ����ַ����룬�ж�������Ϣ
		{
			while (getchar() != '\n') continue;													//��������ջ�����
			printf("ֻ��������λ�����֡������ܿ�ʼ�²�Ŷ��\n\n");
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
					printf("ֻ�����롾���ظ�������λ���֣����ܿ�ʼ�²�Ŷ��\n\n");
					goto dhtt;																	//gotoѭ��
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

		printf("%dA%dB\n\n", A, B);																//��ӡA��B�ĸ���
		count++;

	}
	en_t = time(NULL);

	printf("��Ϸ��������Ӯ�ˣ�\n\n----����ͳ��:\n----��һ������%d��\n----��ʱ%lld��\n\n", count, en_t - st_t);
	pause();																					//�ȴ��û��ķ���ָ��
	printf("\n\n");

	return;
}

inline void help(void)																			//����
{
	printf("��Ϸ����:\n"
		"Ӧ�û����ϵͳʱ������һ����λ������λ���ֲ����ظ���\n"
		"��Ϸ��ʼ������Ҳ�Ӧ�������ɵ���λ�����²�Ľ�����ᱻӦ����A��B����ʾ�������ȷ���\n"
		"Aǰ���һ�����֣���ʾ�²�Ľ�����м���A��A����²�������У�������ͬ��λ��Ҳ��ȷ��\n"
		"Bǰ���һ�����֣���ʾ�²�Ľ�����м���B��B����²�������У�������ͬ��λ�ò�һ����\n\n"
		"������˵�����Ӧ�����ɵ�����Ϊ1234������µ�����Ϊ5283������2���µ���λ����ȷ��3Ҳ���µ���λ�ò��ԣ����Խ�������1A1B��\n"
		"��Ϸ�������³��������ֺ���ʤ����Ҳ���ǵõ�4A0Bʱ��Ϸ��������\n\n\n");
	return;																						//������������Ҫ���Ҳ�У�
}

inline void copyright(void)
{
	printf("��Ȩ����:%s\n�汾��:%s\n\n", CopyRight_C, Version_number);
	return;
}

inline void gchoise(int * lchoise)																//��Ϸ���ز˵�
{
	printf("******************�� ��******************\n");
	printf("1)���ز˵�                     2)�˳���Ϸ\n");
	printf("*****************************************\n");
	printf("��ѡ��:");

	int input = 0;

	while ((input = scanf("%d", &*lchoise)) != 1 || (*lchoise < 1 || *lchoise>2))
	{
		if (input != 1)
			while (getchar() != '\n') continue;
		printf("ѡ�����������ѡ��:");
	}

	system("cls");

	return;
}
