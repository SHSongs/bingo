#include<stdio.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>

#define UP 72				/*나중에 방향키로 사용 가능하게 업그레이드 할때 쓸 것들*/
#define DOWN 80			
#define LEFT 75
#define RIGHT 77					

#define ENTER 13



#define ROW_MAX 5			//행 최대
#define COL_MAX 5			//열 최대
#define Required 4			// 빙고 를 이기는데 필요한 줄수 

/*
전체적인 흐름
 빙고
 사용자에게 5 * 5의 번 의 숫자를 받는다.  (자동)
 컴퓨터에게 5 * 5의 번 의 숫자를 받는다.  (자동)

반복
 사용자와 컴퓨터(AI) 에게 번가라가며 숫자를 받는다.

 사용자나 pc 에게 받은 숫자를 0처리한다. (컴퓨터와 사용자의 각자의 배열 에)

		만약 컴퓨터나 사용자중 5개가 연속으로 있는것이 있으면 줄수 up
		만약 컴퓨터나 사용자의 줄 수가 3줄이 넘으면 종료
 */



void control_game(int(*)[COL_MAX], int(*)[COL_MAX]); 	    	// 빙고 게임 컨트롤 함수  이 프로그램의 중심함수


int scanf_number_data(int(*data)[COL_MAX]);									// 사용자와 컴퓨터에게 데이터를 받습니다.
int draw_game_map(int(*user)[COL_MAX], int(*computer)[COL_MAX]);		    // 게임판을 그립니다.


int scan_bingo(void);														// 빙고할 숫자를 받음
int eraser_number(int(*data)[COL_MAX]);										// 받은 숫자 지우기 (0)으로
int eraser_orther_number(int(*data)[COL_MAX], int);							//다른 판의 받은 숫자 삭제
void Eraser_Funcion(int(*user)[COL_MAX], int(*computer)[COL_MAX]);


void bingo(int(*user)[COL_MAX], int(*computer)[COL_MAX]);
int bingo_test(int(*data)[COL_MAX]);										//빙고줄인지 아닌지 검사


int bingo_cnt = 0;															//user 와 computer 에게 몇번 숫자를 받은지 세는 변수 입니다.
																			//user 와 computer 에게 숫자를 번가라 가며 받을수 있게 하는 변수


int numbers[25] = { 0 };													//사용자와 컴퓨터에게 받은  숫자 기록 하는 배열 종료시 받은 숫자들을 뿌려줍니다
int numbers_cnt = 0;														//numbers를 위한 i 변수 입니다.(몇번출력될지)


int A_I(int(*computer)[COL_MAX]);													//컴퓨터의 A_I입니다. 
																			/*문제점
																				대각선 감지 못함
																				가중치가 같은 경우
																				행열의 0과 가까운 부분에 한다.*/


void user_win();															//유저가 이길때 실행되는 함수
void computer_win();														//컴퓨터가 이길때 실해되는 함수
void draw();																//비길때 실행되는 함수
int result(int user_cnt, int computer_cnt);									//승패확인
void print_scan_number(int(*numbers)[25], int numbers_cnt);					// 게임이 끝난 후 입력받은 숫자를 출력함


int main()
{
	srand(time(NULL));

	int user[ROW_MAX][COL_MAX] = { 0 };											//uesr의 5*5배열 생성
	int computer[ROW_MAX][COL_MAX] = { 0 };										//computer의 5*5배열 생성


	scanf_number_data(user);													//숫자를 받는다 랜덤
	scanf_number_data(computer);

	control_game(user, computer);												//본격 게임 시작

	
	print_scan_number(numbers, numbers_cnt);

	system("PAUSE");

	return 0;
}

void control_game(int(*user)[COL_MAX], int(*computer)[COL_MAX])
{
	int user_cnt = 0;																//유저의 줄수를 알수 있는 변수
	int computer_cnt = 0;															//컴퓨터의 줄수를 알 수 있는 변수
	int num = 0;																	// 템프

	int num_temp;																	//자신이 입력한 숫자를 지우고 다른 판의 숫자도 지우기 위한 변수

	int res;																		//게임을 종료시키기 위한 플래그 변수

	draw_game_map(user, computer);													//게임 맵을 그리기 위한 함수

	while (1)
	{
		//그림 그리고

		Eraser_Funcion(user, computer);												//숫자를 삭제시키기 위한 함수		인자가 두개인 이유는 컨트롤 게임 함수를 단순화 하기 위함

		user_cnt = bingo_test(user);												//유저의 몇줄 빙고인지 센다

		computer_cnt = bingo_test(computer);										//컴퓨터 몇줄 빙고인지 센다

		system("cls");																//지우고

		res = result(user_cnt, computer_cnt);										//컴퓨터나 유저가 이기는데 필요한 충족량을 넘기면 1반환

		if (res == 1)																//1이면 게임이 끝이난다 main 함수로 돌아감
		{									
			system("PAUSE");
			break;
		}

		
		draw_game_map(user, computer);												//맵 업데이트
		printf("user : %d줄  \n compuer : %d줄\n", user_cnt,computer_cnt);													//사용자의 줄 수 표시
		bingo_cnt++;																//몇번진행됬는지 카운트 업


		
	}


	//빙고 줄 승패 발표
}


int scanf_number_data(int(*data)[COL_MAX])
{

	int cnt = 0;

	int x1, x2, y1, y2;
	int temp;
	for (int i = 0; i < ROW_MAX; i++)
	{
		for (int j = 0; j < COL_MAX; j++)
		{
			cnt++;
			data[i][j] = cnt;

		}
	}


	for (int i = 0; i < 300; i++)			//숫자 섞는 부분
	{
		x1 = (rand() % COL_MAX);
		y1 = (rand() % ROW_MAX);

		x2 = (rand() % COL_MAX);
		y2 = (rand() % ROW_MAX);

		temp = data[x1][y1];
		data[x1][y1] = data[x2][y2];
		data[x2][y2] = temp;
	}

	return 0;
}

int draw_game_map(int(*user)[COL_MAX], int(*computer)[COL_MAX])
{
	for (int i = 0; i < ROW_MAX; i++)
	{
		printf("ㅣ%4dㅣ%4dㅣ%4dㅣ%4dㅣ%4dㅣ\n\n", user[i][0], user[i][1], user[i][2], user[i][3], user[i][4]);
		printf("---------------------------------\n");

	}

	printf("\n\n");

	for (int i = 0; i < ROW_MAX; i++)
	{
		printf("ㅣ%4dㅣ%4dㅣ%4dㅣ%4dㅣ%4dㅣ\n\n", computer[i][0], computer[i][1], computer[i][2], computer[i][3], computer[i][4]);

		printf("---------------------------------\n");

	}

}


int scan_bingo(void)
{
	int num;

	printf("숫자를 입력하시오 : ");

	

	do
	{																//do while 로 효율적으로 개선
		scanf("%d", &num);

	} while (num > 25 || num < 1);



	return num;
}


void Eraser_Funcion(int(*user)[COL_MAX], int(*computer)[COL_MAX])
{
	if (bingo_cnt % 2 == 0)											//빙고 카운트 를 2로나눈 나머지가 0일대
	{
		printf("U");
		int num_temp = eraser_number(user);							// 숫자 지우고  유저
		eraser_orther_number(computer, num_temp);					//유저가 입력한 숫자 컴퓨터 판에서도 지우기
	}
	else
	{
		printf("C");
		int num_temp = eraser_number(computer);							// 컴퓨터					이곳에 ai 삽입해야되는데 가중치의 값의 
		eraser_orther_number(user, num_temp);						//컴퓨터가 입력한 숫자 유저에서도 지우기

		system("PAUSE");											//대기 컴퓨터의 생각을 볼수 있다ㅏ.
	}

}


int eraser_number(int(*data)[COL_MAX])
{
	int num = 0;

	if (bingo_cnt % 2 == 0)
	{
		num = scan_bingo();										//사용자에게 입력을 받는다
	}
	else
	{
		num = A_I(data);											//AI에게 입력을 받는다
	}

	numbers[numbers_cnt] = num;										//입력된 숫자를 numbers에 집어 넣는다.  게임이 끝나고 사용
	numbers_cnt++;


	for (int i = 0; i < ROW_MAX; i++)										//받은 숫자를 배열에서 찾아 0으로 만든다
	{
		for (int j = 0; j < COL_MAX; j++)
		{
			if (data[i][j] == num)
			{
				data[i][j] = 0;
			}
		}
	}

	return num;														//num값 반환하여 다른 판도 0으로 만든다.

}

int eraser_orther_number(int(*data)[COL_MAX], int num)
{
	for (int i = 0; i < 5; i++)										//다른 판의 숫자를 지움
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

	for (int i = 0; i < ROW_MAX; i++)
	{
		for (int j = 0; j < COL_MAX; j++)					//열검사
		{
			if (data[i][j] == 0)			//data 의 숫자가 0이면 cnt up
			{
				cnt++;
			}
		}
		if (cnt == 5)						//cnt 가 5개면 빙고 업
		{
			bingo++;
		}
		cnt = 0;

		for (int j = 0; j < ROW_MAX; j++)				//행검사
		{
			if (data[j][i] == 0)
			{
				cnt++;
			}
		}
		if (cnt == ROW_MAX)
		{
			bingo++;
		}
		cnt = 0;
	}


	for (int i = 0; i < ROW_MAX; i++)			// 윈쪽의 부터 오른쪽 아래 까지의 대각선 검사 
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
	for (int i = 0; i < ROW_MAX; i++)
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
	printf("이겼습니다.\n\n");

	return 0;
}

void computer_win()
{
	Sleep(1000);
	system("cls");
	printf("너가 졌다\n\n");

	return 0;
}

void draw()
{
	Sleep(1000);
	system("cls");
	printf("비겼습니다.");

	return 0;
}



int result(int user_cnt, int computer_cnt)
{
	if (user_cnt >= Required)							//승패
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
	printf("입력된 숫자들 : \n");
	for (int i = 0; i < numbers_cnt; i++)
	{
		printf("%2d\n", numbers[i]);
	}

}






/*AI의 규칙
computer의 판만 봐야 한다.
uesr의 판은 보면 안됨
*/



int rand_max(int save_all_max[][2], int*, int*, int);
int find_all_max(int, int save_all_max[][2], int weight[][5]);											//맥스 값과 같은 값을 찾아 배열에 저장한다



int weight_add(int(*weight)[COL_MAX], int y, int x);						//가중치를 가중치 배열에 더한다


int xyfanc(int y, int x, int xy_cnt);
int zero_number[1000][2] = { 0 };									//	0인 곳의 주소를 기억한다
int xy_cnt = 0;


int weight_max(int(*weight)[COL_MAX], int *Y_max, int *X_max);			//가중치의 높은곳을 찾아낸다.



int A_I(int(*computer)[COL_MAX])
{
	
	xy_cnt = 0;
	int save_all_max[25][2] = { 0 };
	int weight[ROW_MAX][COL_MAX] = { 0 };

	for (int i = 0; i < ROW_MAX; i++)										//computer 판의 0인곳을 찾아낸다.
	{
		for (int j = 0; j < COL_MAX; j++)
		{
			if (computer[i][j] == 0)
			{
				weight_add(weight, i, j);							//그곳의 xy 축에 가중치배열 +1
				xyfanc(i, j, xy_cnt);								//자신를 기록한다.
				xy_cnt++;											//기록한 숫자를 출력하기 위한 변수
			}
			/*weight[i][j] = 0;*/
		}
	}

	for (int i = 0; i < xy_cnt; i++)								//자신이 입력한 숫자의 가중치를 0으로 만든다.
	{
		weight[zero_number[i][0]][zero_number[i][1]] = 0;
	}

	int Y_max;
	int X_max;

	int max = weight_max(weight, &Y_max, &X_max);				//가중치중 max 값 게산 그곳의 좌표 기록
	int same_cnt = find_all_max(max, save_all_max, weight);

	rand_max(save_all_max, &Y_max, &X_max, same_cnt);


	int renumber = 0;
	renumber = computer[Y_max][X_max];							//xy좌표에 있는 compuer 배열의 숫자를 찾아 renumber에 저장


	printf("\n\n\n\n");
	printf("0인 숫자의 좌표		: \n");
	for (int i = 0; i < xy_cnt; i++)								//기록한 숫자 출력
	{  
		printf("                         ");
		for (int j = 0; j < 2; j++)
		{
			printf("%3d", zero_number[i][j]);
		}
		printf("\n");
	}
	printf("\n\n\n");

	printf("가중치			: \n");
	for (int i = 0; i < ROW_MAX; i++)									//가중치 출력
	{ 
		printf("                         ");
		for (int j = 0; j < COL_MAX; j++)
		{
			printf("%3d", weight[i][j]);
		}
		printf("\n");
	}

	printf("\n");


	printf("가중치 최대값		: %d\n\n", max);
	printf("최대값의 좌표		: %d  %d\n\n", Y_max, X_max);
	printf("좌표에 대응하는 값	: %d\n\n", renumber);


	return renumber;											//입력할 숫자 반환

}


int weight_add(int(*weight)[COL_MAX], int y, int x)					//가중치 계산 함수
{
	for (int i = 0; i < ROW_MAX; i++)
	{
		for (int j = 0; j < COL_MAX; j++)
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


int weight_max(int(*weight)[COL_MAX], int *Y_max, int *X_max)
{
	int max = -999;

	for (int i = 0; i < ROW_MAX; i++)
	{
		for (int j = 0; j < COL_MAX; j++)
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


int find_all_max(int max, int save_all_max[][2], int weight[][5])
{
	int cnt = 0;

	for (int i = 0; i < ROW_MAX; i++)
	{
		for (int j = 0; j < COL_MAX; j++)
		{
			if (weight[i][j] == max)
			{
				save_all_max[cnt][0] = i;
				save_all_max[cnt][1] = j;
				cnt++;
			}
		}
	}
	return cnt;
}

int rand_max(int save_all_max[][2], int *Y_max, int *X_max, int cnt)
{
	int rand_num;

	for (int i = 0; i < 10; i++)
	{
		rand_num = rand() % cnt;
	}


	*Y_max = save_all_max[rand_num][0];
	*X_max = save_all_max[rand_num][1];



	printf("랜덤값 : %d\n\n", rand_num);


}