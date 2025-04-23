#include <iostream>
#include <vector>

using namespace std;

typedef struct request 
{
	int l, r, s, d;
} request;

void add_progression(vector <int>& a, vector <request> req);
void print_vector(vector <int> a);

int main()
{
	vector <request> req{ {1, 9, 3, 2}, {2, 5, -2, -5}, {7,9,20,10} };

	vector <int> a(10, 0);
	print_vector(a);

	add_progression(a, req);

	print_vector(a);

	return 0;
}

void print_vector(vector <int> a)
{
	for (auto t : a)
	{
		cout << t << "\t";
	}
	cout << endl;
}

void add_progression(vector <int>& a, vector <request> req) 
{
	int temp = a[0];
	for (int i = 1; i < a.size(); i++)
	{
		a[i] = a[i] - temp;
		temp = a[i] + temp;
	}

	for (auto request : req)
	{
		a[request.l] += request.s;
		if (request.r + 1 < a.size())
		{
			a[request.r + 1] -= request.s;
			a[request.r + 1] -= (request.r - request.l) * request.d;
		}
		//print_vector(a);
	}
	
	temp = a[0];//разностный массив разностного массива, в него добавляем d и на выходе получим +d +d +d.. в разностном

	for (int i = 1; i < a.size(); i++)
	{
		a[i] = a[i] - temp;
		temp = a[i] + temp;
	}

	for (auto request : req)
	{
		a[request.l + 1] += request.d;
		if (request.r + 1 < a.size())
		{
			a[request.r + 1] -= request.d;
		}
		//print_vector(a);
	}
	 //собираем из раззностного разностно a разностный а
	for (int i = 1; i < a.size(); i++)
	{
		a[i] = a[i] + a[i - 1];
	}
	//print_vector(a);
	
	//собираем из разностного а новый a
	for (int i = 1; i < a.size(); i++)
	{
		a[i] = a[i] + a[i - 1];
	}
}