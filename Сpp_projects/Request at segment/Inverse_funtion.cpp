#include <iostream>
#include <cmath>

using namespace std;
using ld = long double;

ld inverse(ld(*f)(ld x), ld x0, ld epsilon = 0.00001, ld left  = 0, ld right = 1);
ld func(ld x);


int main()
{
	cout << inverse(func, 8);
	return 0;
}

ld func(ld x)
{
	//return log(x + 1)/log(2);
	//return pow(x, 2);
	//return pow(2, x);
	return x;
}

ld inverse(ld (*f)(ld x), ld x0, ld epsilon, ld left, ld right)
{
	while (!(f(left) <= x0 && x0 <= f(right) || f(left) >= x0 && x0 >= f(right)))
	{
		left = right;
		right *= 2;
		//cout << left << "\t" << right << endl;
	}

	if (f(left) < f(right))
		while (right - left >= epsilon) 
		{
			ld mid = (right + left) / 2;
			if (x0 > f(mid))
				left = mid;
			else
				right = mid;
		}

	return (right + left)/2;
}