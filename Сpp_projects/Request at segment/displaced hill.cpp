#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void print_vector(vector <int> a);

template <typename Iterator>
int search_sup(Iterator begin, Iterator end);

template <typename Iterator>
int search_inf(Iterator begin, Iterator end);

template <typename Iterator>
void search_inf_sup(Iterator left, Iterator right, int& inf_index, int& sup_index);

template <typename Iterator>
float bin_search_less(Iterator begin, Iterator end, int target);

template <typename Iterator>
float bin_search_greater(Iterator begin, Iterator end, int target);

float search(vector <int> a, int target);

int main()
{
	//vector <int> a{1000, 219, 112, 100, 90,70, 0 , 12, 321, 341, 3999, 2000, 1010};
	vector <int> a{5,4,7};
	int target = 5;
	if (!isnan(search(a, target)))
		cout << "result of search = " << search(a, target) << endl;
	else
		cout << "result of search = NAN" << endl;
	return 0;

}


float search(vector <int> a, int target)
{
	int value1, value2;
	search_inf_sup(a.begin(), a.end() - 1, value1, value2);
	//cout << a[value1] << "\t" << a[value2] << endl;
	//cout << value1 << "\t" << value2 << endl;
	if (value1 < value2) //убывание возрастание убывание
	{
		float first_segment = bin_search_less(a.begin(), a.begin() + value1, target);
		float second_segment = bin_search_greater(a.begin() + value1 + 1, a.begin() + value2, target);
		float third_segment = bin_search_less(a.begin() + value2 + 1 > a.end() - 1 ? a.end() - 1 : a.begin() + value2 + 1, a.end() - 1, target);
		//cout << isnan(first_segment) << "\t" << isnan(second_segment) << "\t" << isnan(third_segment) << endl;
		//print_vector({ a.begin(),a.begin() + value1 + 1 });
		//print_vector({ a.begin() + value1 + 1, a.begin() + value2 + 1});
		//print_vector({ a.begin() + value2 + 1, a.end() });
		if (!(isnan(first_segment) && isnan(second_segment) && isnan(third_segment)))
		{
			if (!isnan(first_segment))
				return first_segment;
			else if (!isnan(second_segment))
				return value1 + 1 + second_segment;
			return value2 + 1 + third_segment;
		}
		return NAN;
	}
	else //возрастание убывание возрастание
	{
		float first_segment = bin_search_greater(a.begin(), a.begin() + value2, target);
		float second_segment = bin_search_less(a.begin() + value2 + 1, a.begin() + value1, target);
		float third_segment = bin_search_greater(a.begin() + value1 + 1 > a.end() - 1 ? a.end() - 1 : a.begin() + value1 + 1, a.end() - 1, target);
		//cout << isnan(first_segment) << "\t" << isnan(second_segment) << "\t" << isnan(third_segment) << endl;
		//print_vector({ a.begin(),a.begin() + value1 + 1 });
		//print_vector({ a.begin() + value2 + 1, a.begin() + value1 + 1 });
		//print_vector({ a.begin() + value1 + 1, a.end() });
		if (!(isnan(first_segment) && isnan(second_segment) && isnan(third_segment)))
		{
			if (!isnan(first_segment))
				return first_segment;
			else if (!isnan(second_segment))
				return value2 + 1 + second_segment;
			return value1 + 1 + third_segment;
		}
		return NAN;
	}
}

template <typename Iterator>
float bin_search_less(Iterator begin, Iterator end, int target) //бинарный поиск в убывающем массиве
{
	if (*end == *begin)
	{
		if (*begin == target)
			return 0;
		return NAN;
	}
	auto left = begin;
	auto right = end;
	while (right - left != 1)
	{
		int mid = (right - left) / 2;
		if (*(left + mid) > target)
			left += mid;
		else if (target > *(left + mid))
			right = left + mid;
		else
			return left - begin + mid;
	}
	if (*right == target)
		return right - begin;
	else if (*left == target)
		return left - begin;
	//cout << "less NAN" << endl;
	return NAN;
}

template <typename Iterator>
float bin_search_greater(Iterator begin, Iterator end, int target) //бинарный поиск в возрастающем массиве
{
	if (*end == *begin)
	{
		if (*begin == target)
			return 0;
		//cout << "NAN" << endl;
		return NAN;
	}
	auto left = begin;
	auto right = end;
	while (right - left != 1)
	{
		int mid = (right - left) / 2;
		if (*(left + mid) < target)
			left += mid;
		else if (target < *(left + mid))
			right = left + mid;
		else
			return left - begin + mid;
	}
	if (*right == target)
		return right - begin;
	else if (*left == target)
		return left - begin;
	//cout << "greater NAN" << endl;
	return NAN;
}

template <typename Iterator>
void search_inf_sup(Iterator left, Iterator right, int& inf_index, int& sup_index)
{
	while (*left == *right)
		right--;
	if (*left < *(right)) // убывание возрастание убывание
	{
		int mid = (right - left + 1)/2;
		bool t = true; // t помогает понять в какой отрезок попали, просто, если a[m] = a[m] не совсем понятно
		while (t)
		{
			if (*(left + mid) < *(left + mid + 1)) //центр попал в возрастание
			{
				inf_index = search_inf(left, left + mid);
				sup_index = mid + search_sup(left + mid, right);
				t = false;
			}
			else if (*(left + mid) > *(right) && *(left + mid + 1) > *(left + mid)) //центр попал в правое убывание
			{
				search_inf_sup(left, left + mid, inf_index, sup_index);
				t = false;
			}
			else if (*(left + mid) < *(left) && *(left + mid + 1) > *(left + mid))//центр попал в левое убывание
			{
				search_inf_sup(left + mid, right, inf_index, sup_index);
				inf_index += mid;
				sup_index += mid;
				t = false;
			}
			mid++;
		}
	}
	else //возрастание убывание возрастание
	{
		int mid = (right - left + 1) / 2;
		bool t = true; // t помогает понять в какой отрезок попали, просто, если a[m] = a[m] не совсем понятно
		while (t)
		{
			if (*(left + mid + 1) > *(left + mid)) //центр попал в убывание
			{
				inf_index = search_sup(left, left + mid);
				sup_index = mid + search_inf(left + mid, right);
				t = false;
			}
			else if (*(left + mid) < *(right) && *(left + mid) < *(left + mid + 1)) //центр попал в правое возрастание
			{
				search_inf_sup(left, left + mid, inf_index, sup_index);
				t = false;
			}
			else if (*(left + mid) > *(left) && *(left + mid) < *(left + mid + 1))//центр попал в левое возрастание
			{
				search_inf_sup(left + mid, right, inf_index, sup_index);
				inf_index += mid;
				sup_index += mid;
				t = false;
			}
			mid++;
		}
	}
}

void print_vector(vector <int> a)
{
	for (size_t i = 0; i < a.size(); i++)
	{
		cout << a[i] << "\t";
	}
	cout << endl;
}

template <typename Iterator>
int search_sup(Iterator begin, Iterator end)
{
	auto left = begin;
	auto right = end;
	int delta = (right - left) / 3;
	//cout << "left = " << *left << "\t right = " << *right << endl;
	while (delta != 0)
	{
		//cout << "left = " << *left << "\t right = " << *right << endl;
		if (*(left + delta) > *(right - delta))
		{
			right = right - delta;
			delta = (right - left) / 3;
		}
		else if (*(left + delta) < *(right - delta))
		{
			left = left + delta;
			delta = (right - left) / 3;
		}
		else
		{
			left = left + delta;
			right = right - delta;
			delta = (right - left) / 3;
		}
	}
	if (*(left + delta) > *(right - delta))
	{
		right = right - delta;
		delta = (right - left) / 3;
	}
	else if (*(left + delta) < *(right - delta))
	{
		left = left + delta;
		delta = (right - left) / 3;
	}
	else
	{
		left = left + delta;
		right = right - delta;
		delta = (right - left) / 3;
	}
	//cout << "left = " << *left << "\t right = " << *right << endl;
	if (*left >= *(left + 1) && *(left + 1) >= *right)
		return left - begin; 
	else if (*left <= *(left + 1) && *(left + 1) >= *right)
		return left - begin + 1;
	else
		return right - begin;
}

template <typename Iterator>
int search_inf(Iterator begin, Iterator end)
{
	auto left = begin;
	auto right = end;
	int delta = (right - left) / 3;
	//cout << "left = " << *left << "\t right = " << *right << endl;
	while (delta != 0)
	{
		//cout << "left = " << *left << "\t right = " << *right << endl;
		if (*(left + delta) < *(right - delta))
		{
			right = right - delta;
			delta = (right - left) / 3;
		}
		else if (*(left + delta) > *(right - delta))
		{
			left = left + delta;
			delta = (right - left) / 3;
		}
		else
		{
			left = left + delta;
			right = right - delta;
			delta = (right - left) / 3;
		}
	}
	if (*(left + delta) < *(right - delta))
	{
		right = right - delta;
		delta = (right - left) / 3;
	}
	else if (*(left + delta) > *(right - delta))
	{
		left = left + delta;
		delta = (right - left) / 3;
	}
	else
	{
		left = left + delta;
		right = right - delta;
		delta = (right - left) / 3;
	}
	//cout << "left = " << *left << "\t right = " << *right << endl;
	if (*left <= *(left + 1) && *(left + 1) <= *right)
		return left - begin; //индекс супремума на промежутке
	else if (*left >= *(left + 1) && *(left + 1) <= *right)
		return left - begin + 1;
	else
		return right - begin;
}






