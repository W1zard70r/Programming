#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

float exp_search(vector <int> a, int target);

int main()
{


	vector <int> a{1, 1, 1, 1, 1, 1, 2, 3, 3, 3, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 7, 8, 18, 100, 1000, 10000, 11111, 19191919, 20202020, 30303030};
	cout << exp_search(a, 303030301) << endl;

	return 0;
}


float exp_search(vector <int> a, int target) 
{
	size_t r = 2;
	
	//быстрый поиск границ поиск
	while (r < a.size() && target >= a[r]) 
	{
		r *= 2;
	}
	r = r > a.size() - 1 ? a.size() - 1 : r;
	size_t l = r / 2;
	
	//бинарный поиск по конечному массиву
	int mid = (r + l) / 2;
	while (r - l > 2) 
	{
		if (a[mid] < target) 
		{
			l = mid;
		}
		else 
		{
			r = mid;
		}
		mid = (r + l) / 2;
	}

	//cout << "target = " << target << endl;
	//cout << "l = " << l << endl;
	//cout << "r = " << r << endl;
	//cout << "mid = " << mid << endl;
	
	if (a[l] == target)
		return l;
	else if (a[r] == target)
		return r;
	else if (a[mid] == target)
		return mid;
	return NAN;
}