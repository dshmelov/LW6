#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define HEADER ("Лабораторная работа №6\nВыполнили: Шмелёв Д. и Пантюшов Е.\n\n")

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <stack>

using namespace std;

struct node
{
	int vertex;
	struct node* next;
};

struct Graph
{
	int numVertices;
	struct node** adjList;
};

struct node* createNode(int v)
{
	struct node* newNode = (node*)(malloc(sizeof(struct node)));
	newNode->vertex = v;
	newNode->next = NULL;
	return newNode;
}

void addEdge(struct Graph* graph, int i, int j)
{
	struct node* newNode = createNode(j);
	if (graph->adjList[i] == 0)
	{
		graph->adjList[i] = newNode;
		newNode = NULL;
	}
	struct node* temp = graph->adjList[i];
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = newNode;
	newNode = createNode(i);
	if (graph->adjList[j] == 0)
	{
		graph->adjList[j] = newNode;
		newNode = NULL;
	}
	temp = graph->adjList[j];
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = newNode;
}

struct Graph* createGraph(int** M, int vertices)
{
	struct Graph* G = (Graph*)(malloc(sizeof(struct Graph)));
	G->numVertices = vertices;
	G->adjList = (node**)(malloc(vertices * sizeof(struct node*)));
	for (int i = 0; i < vertices; i++)
		G->adjList[i] = NULL;
	for (int i = 0; i < vertices; i++)
	{
		for (int j = 0; j < vertices; j++)
		{
			if ((M[i][j] == 1) && (i < j))
			{
				addEdge(G, i, j);
			}
		}
	}
	return G;
}

void printGraph(struct Graph* graph)
{
	for (int i = 0; i < graph->numVertices; i++)
	{
		struct node* temp = graph->adjList[i];
		printf("%d-я вершина: ", i);
		while (temp)
		{
			printf("%d ", temp->vertex);
			temp = temp->next;
		}
		printf("\n");
	}
}

void dfsd_list(struct Graph* G, int n, int* dist, int* NUM, int x)
{
	stack <int> s;
	struct node* v = G->adjList[x];
	s.push(x);
	dist[x] = 0;
	while (!s.empty())
	{
		x = s.top();
		s.pop();
		v = G->adjList[x];
		if (NUM[x] == 2)
			continue;
		NUM[x] = 2;
		while(v)
		{
			if (NUM[v->vertex] != 2 && dist[v->vertex] == -1)
			{
				s.push(v->vertex);
				NUM[v->vertex] = 1;
				dist[v->vertex] = dist[x] + 1;
			}
			v = v->next;
		}
	}
}

void DFSD_LIST(struct Graph* G, int n, int* dist, int x, int k)
{
	struct node* v = G->adjList[x];
	int r = k + 1;
	dist[x] = k;
	while(v)
	{
		if (dist[v->vertex] == -1)
			DFSD_LIST(G, n, dist, v->vertex, r);
		if (k < dist[v->vertex])
			DFSD_LIST(G, n, dist, v->vertex, r);
		v = v->next;
	}
}

void DFSD(int** M, int n, int* dist, int x, int k)
{
	int r = k + 1;
	dist[x] = k;
	for (int i = 0; i < n; i++)
	{
		if (M[x][i] == 1 && dist[i] == -1)
			DFSD(M, n, dist, i, r);
		if (M[x][i] == 1 && k < dist[i])
			DFSD(M, n, dist, i, r);
	}
}

void dfsd(int** M, int n, int* dist, int* NUM, int x)
{
	stack <int> s;
	s.push(x);
	dist[x] = 0;
	while (!s.empty())
	{
		x = s.top();
		s.pop();
		if (NUM[x] == 2)
			continue;
		NUM[x] = 2;
		for (int i = n - 1; i > -1; i--)
		{
			if (M[x][i] == 1 && NUM[i] != 2 && dist[i] == -1)
			{
				s.push(i);
				NUM[i] = 1;
				dist[i] = dist[x] + 1;
			}
		}
		printf(" %d \n", x);
	}
}

void bfsd_list(struct Graph* G, int n, int* dist, int x)
{
	queue <int> q;
	struct node* v = G->adjList[x];
	q.push(x);
	dist[x] = 0;
	while (!q.empty())
	{
		x = q.front();
		v = G->adjList[x];
		q.pop();
		while (v)
		{
			if (dist[v->vertex] == -1)
			{
				q.push(v->vertex);
				dist[v->vertex] = dist[x] + 1;
			}
			v = v->next;
		}
	}
}

void bfsd(int** M, int n, int* dist, int x)
{
	queue <int> q;
	q.push(x);
	dist[x] = 0;
	while (!q.empty())
	{
		x = q.front();
		q.pop();
		for (int i = 0; i < n; i++)
		{
			if (M[x][i] == 1 && dist[i] == -1)
			{
				q.push(i);
				dist[i] = dist[x] + 1;
			}
		}
		printf(" %d \n", x);
	}
}

void f5(struct Graph* G, int n)
{
	int x, k = 0;
	int* dist = (int*)(malloc(n * sizeof(int)));
	//int* NUM = (int*)(malloc(n * sizeof(int)));
	printf("\n\nПункт 2.\nВведите точку входа: ");
	scanf("%d", &x);
	for (int i = 0; i < n; i++)
	{
		dist[i] = -1;
	}
	DFSD_LIST(G, n, dist, x, k);
	for (int i = 0; i < n; i++)
	{
		if (dist[i] == -1)
		{
			dist[i] = 0;
		}
		printf("%d -> %d: %d\n", x, i, dist[i]);
	}
}

void f4(int** M, int n)
{
	int x, k = 0;;
	int* dist = (int*)(malloc(n * sizeof(int)));
	//int* NUM = (int*)(malloc(n * sizeof(int)));
	printf("\nЗадание 2.\n\nПункт 1.\nВведите точку входа: ");
	scanf("%d", &x);
	for (int i = 0; i < n; i++)
	{
		dist[i] = -1;
	}
	DFSD(M, n, dist, x, k);
	for (int i = 0; i < n; i++)
	{
		if (dist[i] == -1)
		{
			dist[i] = 0;
		}
		printf("%d -> %d: %d\n", x, i, dist[i]);
	}
}

void f3(int** M, struct Graph* G, int n)
{
	int x;
	int* dist = (int*)(malloc(n * sizeof(int)));
	printf("\n\nПункт 3.\nСписок смежности:\n");
	printGraph(G);
	printf("\nВведите точку входа: ");
	scanf("%d", &x);
	for (int i = 0; i < n; i++)
	{
		dist[i] = -1;
	}
	bfsd_list(G, n, dist, x);
	for (int i = 0; i < n; i++)
	{
		if (dist[i] == -1)
		{
			dist[i] = 0;
		}
		printf("%d -> %d: %d\n", x, i, dist[i]);
	}
}

void f2(int** M, int n)
{
	int x;
	int* dist = (int*)(malloc(n * sizeof(int)));
	printf("\nПункт 2.\nВведите точку входа: ");
	scanf("%d", &x);
	for (int i = 0; i < n; i++)
	{
		dist[i] = -1;
	}
	bfsd(M, n, dist, x);
	for (int i = 0; i < n; i++)
	{
		if (dist[i] == -1)
		{
			dist[i] = 0;
		}
		printf("%d -> %d: %d\n", x, i, dist[i]);
	}
}

void f1(int** M, int n)
{
	printf("\nЗадание 1.\n\nПункт 1.\nМатрица смежности:\n");
	for (int i = 0; i < n; i++)
	{
		M[i] = (int*)(malloc(n * sizeof(int)));
		for (int j = 0; j < n; j++)
		{
			M[i][j] = rand() % 100;
			if (M[i][j] < 40)
			{
				M[i][j] = 0;
			}
			else
			{
				M[i][j] = 1;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				M[i][j] = 0;
			}
			else
			{
				M[i][j] = M[j][i];
			}
			printf(" %d ", M[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));
	printf(HEADER);
	int n;
	printf("Введите размерность матрицы: ");
	scanf("%d", &n);
	int** M = (int**)(malloc(n * sizeof(int*)));
	f1(M, n);
	clock_t t1 = clock();
	f2(M, n);
	clock_t t2 = clock();
	float t3 = t2 - t1;
	printf("Время: %f", t3 / 1000);
	struct Graph* G = createGraph(M, n);
	f3(M, G, n);
	t1 = clock();
	f4(M, n);
	t2 = clock();
	t3 = t2 - t1;
	printf("Время: %f", t3 / 1000);
	f5(G, n);
	system("PAUSE");
	return 0;
}