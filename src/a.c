#include<stdio.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>

#define UP 72				/*���߿� ����Ű�� ��� �����ϰ� ���׷��̵� �Ҷ� �� �͵�*/
#define DOWN 80			
#define LEFT 75
#define RIGHT 77					

#define ENTER 13



#define ROW_MAX 5			//�� �ִ�
#define COL_MAX 5			//�� �ִ�
#define Required 2			// ���� �� �̱�µ� �ʿ��� �ټ� 

/*
��ü���� �帧
 ����
 ����ڿ��� 5 * 5�� �� �� ���ڸ� �޴´�.  (�ڵ�)
 ��ǻ�Ϳ��� 5 * 5�� �� �� ���ڸ� �޴´�.  (�ڵ�)

�ݺ�
 ����ڿ� ��ǻ��(AI) ���� �����󰡸� ���ڸ� �޴´�.

 ����ڳ� pc ���� ���� ���ڸ� 0ó���Ѵ�. (��ǻ�Ϳ� ������� ������ �迭 ��)

		���� ��ǻ�ͳ� ������� 5���� �������� �ִ°��� ������ �ټ� up
		���� ��ǻ�ͳ� ������� �� ���� 3���� ������ ����
 */



void control_game(int(*user)[COL_MAX], int(*computer)[COL_MAX]); 	    	// ���� ���� ��Ʈ�� �Լ�  �� ���α׷��� �߽��Լ�


int scanf_number_data(int(*data)[COL_MAX]);									// ����ڿ� ��ǻ�Ϳ��� �����͸� �޽��ϴ�.
int draw_game_map(int(*user[COL_MAX]), int(*computer[COL_MAX]));		    // �������� �׸��ϴ�.


int scan_bingo(void);														// ������ ���ڸ� ����
int eraser_number(int(*data)[COL_MAX]);										// ���� ���� ����� (0)����
int eraser_orther_number(int(*data)[COL_MAX], int);							//�ٸ� ���� ���� ���� ����
void EraserFuncion(int(*user)[COL_MAX], int(*computer)[COL_MAX]);


void bingo(int(*user)[COL_MAX], int(*computer)[COL_MAX]);					//���ڸ� ����� ��Ʈ�� �Լ�
int bingo_test(int(*data)[COL_MAX]);										//���������� �ƴ��� �˻�


int bingo_cnt = 0;															//user �� computer ���� ��� ���ڸ� ������ ���� ���� �Դϴ�.
																			//user �� computer ���� ���ڸ� ������ ���� ������ �ְ� �ϴ� ����


int numbers[25] = { 0 };													//����ڿ� ��ǻ�Ϳ��� ����  ���� ��� �ϴ� �迭 ����� ���� ���ڵ��� �ѷ��ݴϴ�
int numbers_cnt = 0;														//numbers�� ���� i ���� �Դϴ�.(�����µ���)


int A_I(int(*computer)[5]);													//��ǻ���� A_I�Դϴ�. 
																			/*������
																				�밢�� ���� ����
																				����ġ�� ���� ���
																				�࿭�� 0�� ����� �κп� �Ѵ�.*/


void user_win();															//������ �̱涧 ����Ǵ� �Լ�
void computer_win();														//��ǻ�Ͱ� �̱涧 ���صǴ� �Լ�
void draw();																//��涧 ����Ǵ� �Լ�
int result(int user_cnt, int computer_cnt);									//����Ȯ��
void print_scan_number(int(*numbers)[25], int numbers_cnt);					// ������ ���� �� �Է¹��� ���ڸ� �����


int main()
{
	srand(time(NULL));

	int user[ROW_MAX][COL_MAX] = { 0 };											//uesr�� 5*5�迭 ����
	int computer[ROW_MAX][COL_MAX] = { 0 };										//computer�� 5*5�迭 ����


	scanf_number_data(user);													//���ڸ� ���´� ����
	scanf_number_data(computer);

	control_game(user, computer);												//���� ���� ����


	print_scan_number(numbers, numbers_cnt);									//������ ���� �� ���� ���ڸ� �վ

	system("PAUSE");

	return 0;
}

void control_game(int(*user)[COL_MAX], int(*computer)[COL_MAX])
{
	int user_cnt = 0;																//������ �ټ�
	int computer_cnt = 0;															//��ǻ���� �ټ�


	int res;																		//������ �����Ű�� ���� �÷��� ����

	draw_game_map(user, computer);													//���� �� �׸�


	while (1)
	{


		EraserFuncion(user, computer);												//���� ���ڸ� ������Ű�� ���� �Լ�		���ڰ� �ΰ��� ������ ��Ʈ�� ���� �Լ��� �ܼ�ȭ �ϱ� ����

		user_cnt = bingo_test(user);												//������ ���� �������� ����

		computer_cnt = bingo_test(computer);										//��ǻ�� ���� �������� ����

		system("cls");																//�����

		res = result(user_cnt, computer_cnt);										//��ǻ�ͳ� ������ �̱�µ� �ʿ��� �������� �ѱ�� 1��ȯ

		if (res == 1)																//1�̸� ������ ���̳��� main �Լ��� ���ư�
		{
			system("PAUSE");
			break;
		}


		draw_game_map(user, computer);												//�� ������Ʈ
		printf("user : %d��  \n compuer : %d��\n", user_cnt, computer_cnt);			//�ټ��� �ܼ�¦�� ����	
																					//������� �� �� ǥ��

		bingo_cnt++;																//���° ������  ī��Ʈ ��

	}


}


int scanf_number_data(int(*data)[COL_MAX])
{

	int cnt = 0;

	int x1, x2, y1, y2;
	int temp;


	for (int i = 0; i < 5; i++)				//���ڸ� �ʱ�ȭ (1~25)
	{
		for (int j = 0; j < 5; j++)
		{
			cnt++;
			data[i][j] = cnt;

		}
	}


	for (int i = 0; i < 300; i++)			//���� ���� �κ�		ī������ϵ��� �����ش�.
	{
		x1 = (rand() % 5);
		y1 = (rand() % 5);

		x2 = (rand() % 5);
		y2 = (rand() % 5);

		temp = data[x1][y1];
		data[x1][y1] = data[x2][y2];
		data[x2][y2] = temp;
	}

	return 0;
}



int draw_game_map(int(*user)[COL_MAX], int(*computer)[COL_MAX])
{
	for (int i = 0; i < 5; i++)
	{
		printf("��%4d��%4d��%4d��%4d��%4d��\n\n", user[i][0], user[i][1], user[i][2], user[i][3], user[i][4]);
		printf("---------------------------------\n");

	}

	printf("\n\n");

	for (int i = 0; i < 5; i++)
	{
		printf("��%4d��%4d��%4d��%4d��%4d��\n\n", computer[i][0], computer[i][1], computer[i][2], computer[i][3], computer[i][4]);

		printf("---------------------------------\n");

	}

}



int scan_bingo(void)
{
	int num;

	printf("���ڸ� �Է��Ͻÿ� : ");


	do
	{
		scanf("%d", &num);

	} while (num > 25 || num < 1);		//1���� 25������ ���ڸ� ���� �� �ְ� �Ѵ�. 


	return num;
}



void EraserFuncion(int(*user)[COL_MAX], int(*computer)[COL_MAX])
{

	if (bingo_cnt % 2 == 0)											//���� ī��Ʈ �� 2�γ��� �������� 0�ϴ�
	{
		printf("U");
		int num_temp = eraser_number(user);							// ���� �����  ����
		eraser_orther_number(computer, num_temp);					//������ �Է��� ���� ��ǻ�� �ǿ����� �����
	}
	else
	{
		printf("C");
		int num_temp = eraser_number(computer);							// ��ǻ��					�̰��� ai �����ؾߵǴµ� ����ġ�� ���� 
		eraser_orther_number(user, num_temp);						//��ǻ�Ͱ� �Է��� ���� ���������� �����

		system("PAUSE");											//��� ��ǻ���� ������ ���� �ִ٤�.
	}

}



int eraser_number(int(*data)[COL_MAX])
{
	int num = 0;

	if (bingo_cnt % 2 == 0)										//���� �ϼ��� �������� �����
	{
		num = scan_bingo();										//����ڿ��� �Է��� �޴´�
	}
	else
	{
		num = A_I(data);											//AI���� �Է��� �޴´�
	}

	numbers[numbers_cnt] = num;										//�Էµ� ���ڸ� numbers�� ���� �ִ´�.  ������ ������ ���
	numbers_cnt++;


	for (int i = 0; i < 5; i++)										//���� ���ڸ� �迭���� ã�� 0���� �����
	{
		for (int j = 0; j < 5; j++)
		{
			if (data[i][j] == num)
			{
				data[i][j] = 0;
			}
		}
	}

	return num;														//num�� ��ȯ�Ͽ� �ٸ� �ǵ� 0���� �����.

}


int eraser_orther_number(int(*data)[COL_MAX], int num)
{
	for (int i = 0; i < 5; i++)										//�ٸ� ���� ���ڸ� ����
	{
		for (int j = 0; j < 5; j++)
		{
			if (data[i][j] == num)
			{
				data[i][j] = 0;
			}
		}
	}
}

int bingo_test(int(*data)[COL_MAX])
{
	int bingo = 0;
	int cnt = 0;
	int flog = 0;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)					//���˻�
		{
			if (data[i][j] == 0)			//data �� ���ڰ� 0�̸� cnt up
			{
				cnt++;
			}
		}
		if (cnt == 5)						//cnt �� 5���� ���� ��
		{
			bingo++;
		}
		cnt = 0;

		for (int j = 0; j < 5; j++)				//��˻�
		{
			if (data[j][i] == 0)
			{
				cnt++;
			}
		}
		if (cnt == 5)
		{
			bingo++;
		}
		cnt = 0;
	}


	for (int i = 0; i < 5; i++)			// ������ ���� ������ �Ʒ� ������ �밢�� �˻� 
	{
		if (data[i][i] == 0)
		{
			cnt++;
		}
	}
	if (cnt == 5)
	{
		bingo++;
	}
	cnt = 0;

	int j = 4;
	for (int i = 0; i < 5; i++)
	{
		if (data[i][j] == 0)
		{
			cnt++;
		}
		j--;
	}
	if (cnt == 5)
	{
		bingo++;
	}
	cnt = 0;


	return bingo;
}


void user_win()
{
	Sleep(1000);
	system("cls");
	printf("�̰���ϴ�.\n\n");

	return 0;
}

void computer_win()
{
	Sleep(1000);
	system("cls");
	printf("�ʰ� ����\n\n");

	return 0;
}

void draw()
{
	Sleep(1000);
	system("cls");
	printf("�����ϴ�.");

	return 0;
}



int result(int user_cnt, int computer_cnt)
{
	if (user_cnt >= Required)							//����
	{
		user_win();
		return 1;
	}

	if (computer_cnt >= Required)
	{
		computer_win();
		return 1;
	}

	if (user_cnt >= Required && computer_cnt >= Required)
	{
		draw();
		return 1;
	}
}

void print_scan_number(int(*numbers), int numbers_cnt)
{
	system("cls");
	printf("�Էµ� ���ڵ� : \n");
	for (int i = 0; i < numbers_cnt; i++)
	{
		printf("%2d\n", numbers[i]);
	}

}






/*AI�� ��Ģ
computer�� �Ǹ� ���� �Ѵ�.
uesr�� ���� ���� �ȵ�
*/






int weight_add(int(*weight)[5], int y, int x);						//����ġ�� ����ġ �迭�� ���Ѵ�


int xyfanc(int y, int x, int xy_cnt);								//	0�� ���� �ּҸ� ����Ѵ�
int zero_number[1000][2] = { 0 };
int xy_cnt = 0;


int weight_max(int(*weight)[5], int *Y_max, int *X_max);			//����ġ�� �������� ã�Ƴ���.



int A_I(int(*data)[5])
{

	xy_cnt = 0;

	int weight[5][5] = { 0 };

	for (int i = 0; i < 5; i++)										//computer ���� 0�ΰ��� ã�Ƴ���.
	{
		for (int j = 0; j < 5; j++)
		{
			if (data[i][j] == 0)
			{
				weight_add(weight, i, j);							//�װ��� xy �࿡ ����ġ�迭 +1
				xyfanc(i, j, xy_cnt);								//�ڽŸ� ����Ѵ�.
				xy_cnt++;											//����� ���ڸ� ����ϱ� ���� ����
			}
			/*weight[i][j] = 0;*/
		}
	}

	for (int i = 0; i < xy_cnt; i++)								//�ڽ��� �Է��� ������ ����ġ�� 0���� �����.
	{
		weight[zero_number[i][0]][zero_number[i][1]] = 0;
	}

	int Y_max;
	int X_max;

	int max = weight_max(weight, &Y_max, &X_max);				//����ġ�� max �� �Ի� �װ��� ��ǥ ���

	int renumber = 0;
	renumber = data[Y_max][X_max];							//xy��ǥ�� �ִ� compuer �迭�� ���ڸ� ã�� renumber�� ����


	//printf("\n\n\n\n");
	//printf("0�� ������ ��ǥ		: \n");
	//for (int i = 0; i < xy_cnt; i++)								//����� ���� ���
	//{
	//	printf("                         ");
	//	for (int j = 0; j < 2; j++)
	//	{
	//		printf("%3d", zero_number[i][j]);
	//	}
	//	printf("\n");
	//}
	//printf("\n\n\n");

	//printf("����ġ			: \n");
	//for (int i = 0; i < 5; i++)									//����ġ ���
	//{
	//	printf("                         ");
	//	for (int j = 0; j < 5; j++)
	//	{
	//		printf("%3d", weight[i][j]);
	//	}
	//	printf("\n");
	//}

	//printf("\n");


	//printf("����ġ �ִ밪		: %d\n\n", max);
	//printf("�ִ밪�� ��ǥ		: %d  %d\n\n", Y_max, X_max);
	//printf("��ǥ�� �����ϴ� ��	: %d\n\n", renumber);


	return renumber;											//�Է��� ���� ��ȯ

}


int weight_add(int(*weight)[5], int y, int x)					//����ġ ��� �Լ�
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (x == i)
			{
				weight[j][i]++;
			}
			if (y == i)
			{
				weight[i][j]++;
			}
		}
		/*weight[y][x]=0;*/
	}

}

int xyfanc(int y, int x, int xy_cnt)
{
	zero_number[xy_cnt][0] = y;
	zero_number[xy_cnt][1] = x;
	return 0;
}


int weight_max(int(*weight)[5], int *Y_max, int *X_max)
{
	int max = -999;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (weight[i][j] >= max)
			{
				max = weight[i][j];
				*Y_max = i;
				*X_max = j;
			}
		}
	}

	return max;
}