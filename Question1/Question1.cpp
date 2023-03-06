#include<stdio.h>
void judgement(int (*array)[2], int n)
{
	int i = 0, j = 0;
	for(i=0;i<2;i++)//1代表说真话，0代表说假话，i递增循环对说真话和假话的所有情况进行模拟，并记录结果
	{
		switch (i)
		{
		case 0://假话
		{
			switch (n)
			{
			case 1:j = !1; break;
			case 2:j = i; break;
			case 3:j = 1; break;
			case 4:j = !i; break;
			}
			break;
		}
		case 1://真话
		{
			switch (n)
			{
			case 1:j = 1; break;//对对方进行定性的语句，对方说真话（本题中对应A说的话）
			case 2:j = !i; break;//自己与对方异或（本题中对应B说的话）
			case 3:j = !1; break;//对方说假话
			case 4:j = i; break;//对方与自己同说真话或同说假话
			}
			break;
		}
		}
		array[i][j] = 1;
	}
}
void main()
{
	int array1[2][2] = { 0 };//记录推导结果
	int array2[2][2] = { 0 };//同理
	int condition1 = 0,condition2=0;
	int error1 = 0, error2 = 0;//记录错误输入
	while (1)
	{
		printf("请选择A所说的话(序号):\n");
		printf("1:B说的真话\n2:自己与B一个真一个假\n3:B说的假话\n4:自己与B同说真话同说假话\n");
		error1 = scanf_s("%d", &condition1);//传入A说话内容
		if (condition1 > 4 || condition1 < 1 || error1 != 1)
		{
			printf("输入错误\n");
		}
		else
		{
			break;
		}
	}
	while (1)
	{
		printf("请选择B所说的话(序号):\n");
		printf("1:A说的真话\n2:自己与A一个真一个假\n3:A说的假话\n4:自己与A同说真话同说假话\n");
		error2=scanf_s("%d", &condition2);//传入B说话内容
		if (condition2 > 4 || condition2 < 1 || error2 != 1)
		{
			printf("输入错误\n");
		}
		else
		{
			break;
		}
	}
	int flag = 0;
	judgement(array1, condition1);
	judgement(array2, condition2);

	for (int i = 0; i < 2; i++)//打印结果
	{
		for (int j = 0; j < 2; j++)
		{
			if (array1[i][j] == array2[j][i] && array1[i][j] == 1)
			{
				if (i == 0)
				{
					printf("A说假话，");
				}
				if (i == 1)
				{
					printf("A说真话，");
				}
				if (j == 0)
				{
					printf("B说假话\n");
				}
				if (j == 1)
				{
					printf("B说真话\n");
				}
				flag = 1;//证明已找到解
			}
		}
	}
	if (flag == 1)
	{
		return;
	}
	else {
		printf("无解");
	}
}