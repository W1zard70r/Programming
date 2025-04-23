#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int max(vector <int> a);
int median(vector <int> a);
void printvector(vector <int> a);

template <typename Iterator>
vector <int> subvector(Iterator begin, Iterator end);

int median(vector <int> a)
{
	sort(a.begin(), a.end());
	return a[(a.size() - 1) / 2];
}

int min_delta_median(vector <int> a) 
{
	int delta;
	int mindelta = max(a);
	auto left_begin = a.begin();
	auto left_end = left_begin;
	for (size_t i = 1; i < a.size(); i+=2)
	{
		left_end = left_begin + i;
		vector <int> left_vector = subvector(left_begin, left_end);
		vector <int> right_vector = subvector(left_end, a.end());
		printvector(left_vector);
		printvector(right_vector);
		delta = abs(median(left_vector) - median(right_vector));
		mindelta = delta < mindelta ? delta : mindelta;
		cout << "delta = " << delta << "; mindelta = " << mindelta << "; median(left_vector) = " << median(left_vector) << "; median(right_vector) = " << median(right_vector) <<";" << endl << endl;
	}
	return mindelta;
}

template <typename Iterator>
vector <int> subvector(Iterator begin, Iterator end) 
{
	vector <int> result(begin, end);
	return result;
}

int max(vector <int> a) 
{
	int maximum = a[0];
	for (auto t: a)
	{
		maximum = t > maximum ? t : maximum;
	}
	return maximum;
}

void printvector(vector <int> a) 
{
	for (auto t: a)
	{
		cout << t << "\t";
	}
	cout << endl;
}


int main() 
{
	vector <int> a{ 6, 3, 2, 4, 9, 4};
	
	for (auto t : a)
	{
		cout << t << "\t";
	}
	cout << endl << endl;
	cout << min_delta_median(a) << endl;
	return 0;
}
