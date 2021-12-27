#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <locale>
#include <stdlib.h>
#include <vector>

#define INF = 1000000000; // значение "бесконечность"
int** G;
int* used, *min_e, *sel_e;
int N, z, i, j;

using namespace std;

void printmatrix(int** source, int size);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	printf("Введите количество вершин графа: ");
	scanf_s("%d", &N);

	// Выделяем память под исходную матрицу графа
	G = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++)
		G[i] = (int*)malloc(N * sizeof(int));

	used = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++)
		used[i] = -1;

	min_e = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++)
		min_e[i] = 1000000000;

	sel_e = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++)
		sel_e[i] = -1;

		//Заполняем исходную матрицу для взвешенного неориентированного графа
		
		srand(time(NULL));
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				if (i == j)
					G[i][j] = 0;
				else
				{
					if (rand() % 10 < 4)
						G[i][j] = rand() % 10;
					else
						G[i][j] = 1000000000;
					G[j][i] = G[i][j];
				}

	printf("\nИсходная матрица графа G:\n");
	printmatrix(G, N);

	min_e[0] = 0;

	for (int i = 0; i < N; ++i) 
	{
		int v = -1;
		for (int j = 0; j < N; ++j)
			if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
				v = j;

		if (min_e[v] == 1000000000)
		{
			printf("\nNo MST!\n");
			exit(0);
		}

		used[v] = true;
		if (sel_e[v] != -1)
			cout << v << " " << sel_e[v] << endl;

		for (int to = 0; to < N; ++to)

			if (G[v][to] < min_e[to]) 
			{
				min_e[to] = G[v][to];
				sel_e[to] = v;
			}

	}
}

void printmatrix(int** source, int size)
{
		printf("   ");
		for (int i = 0; i < size; i++)
			printf("  v%d", i + 1);
		printf("\n");
	

	for (int i = 0; i < size; i++)
	{
		printf(" v%d ", i + 1);
		for (int j = 0; j < size; j++)

			if (G[i][j] == 1000000000)
				printf(" INF");

				else
					printf("%3d ", source[i][j]);


		printf("\n");
	}

	
}