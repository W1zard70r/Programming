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
	vector <int> d1{a[0]}; //разностный массив, в него добавляем s
	for (int i = 1; i < (int) a.size(); i++)
	{
		d1.push_back(a[i] - a[i - 1]);
	}

	for (auto request : req)
	{
		d1[request.l] += request.s;
		if (request.r + 1 < (int) a.size())
		{
			d1[request.r + 1] -= request.s;
			d1[request.r + 1] -= (request.r - request.l) * request.d;
		}
		//print_vector(d1);
	}

	vector <int> d2{ d1[0] }; //разностный массив разностного массива, в него добавляем d и на выходе получим +d +d +d.. в разностном

	for (int i = 1; i < (int) a.size(); i++)
	{
		d2.push_back(d1[i] - d1[i - 1]);
	}

	for (auto request : req)
	{
		d2[request.l + 1] += request.d;
		if (request.r + 1 < (int) a.size())
		{
			d2[request.r + 1] -= request.d;
		}
		//print_vector(d2);
	}

	d1[0] = d2[0]; //собираем из d2 новый d1
	for (int i = 1; i < (int) d1.size(); i++)
	{
		d1[i] = d1[i - 1] + d2[i];
	}
	//print_vector(d1);

	a[0] = d1[0]; //собираем из d1 новый a
	for (int i = 1; i < (int) d1.size(); i++)
	{
		a[i] = a[i - 1] + d1[i];
	}

}