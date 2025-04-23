#include <iostream>
#include <algorithm>

using namespace std;
void to_right_path(int* a, int* b, int* c)
{
	if (*a <= *b && *b <= *c) // ситуация 1
	{
		swap(*a, *b);
	}
	else if (*a <= *b && *b >= *c) // ситуация 2
	{
		swap(*a, *b);
		if (*b > *c)
			swap(*b, *c);
	}
	else if (*a >= *b && *b <= *c) //условие уже верно // ситуация 3
	{
		return;
	}
	else //*a >= *b && *b>=*c // ситуация 4
	{
		swap(*b, *c);
	}
}
void to_snake(const int n, int a[]) 
{
	if (a[0] > a[1])
		swap(a[0], a[1]);

	if (n % 2 == 1 && a[n - 1] > a[n - 2])
		swap(a[n - 1], a[n - 2]);

	for (size_t i = 2; i < 2*(n/2); i+=2)
	{
		to_right_path(&a[i - 1], &a[i], &a[i + 1]);
	}
}


int main() 
{
	const int n = 5;
	int a[n]{ 1, 3, 2, 2, 5 };
	
	for (auto t : a)
	{
		cout << t << "\t";
	}
	cout << endl;
	to_snake(n, a);

	for (auto t: a)
	{
		cout << t << "\t";
	}


	return 0;
}