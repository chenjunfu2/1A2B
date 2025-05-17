#include "1A2B.h"

int main(void)
{
	printf("1A2B猜数字小游戏\n");

	pause();
	system("cls");
	
	int choise = 0, lchoise = 0;

	while (lchoise != 2 && (choise = menu()) != 4)								//判断是否退出游戏
	{
		switch (choise)
		{
		case 1:
			system("cls");
			printf("您选择了:%d\n\n", choise);
			game();
			break;
		case 2:
			system("cls");
			printf("您选择了:%d\n\n", choise);
			help();
			break;
		case 3:
			system("cls");
			printf("您选择了:%d\n\n", choise);
			copyright();
			break;
		default:
			system("cls");
			printf("您选择了:%d\n\n", choise);
			printf("被调函数返回值错误！");										//函数判断验证（可有可无）
			break;
		}

		gchoise(&lchoise);														//指针传参

	}

	system("cls");																//清屏
	
	return 0;
}
