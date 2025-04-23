#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int median(vector <int> a);
void printvector(vector <int> a);
void vector_remove(vector <int>& a, int element);
void sorted_insert(vector <int>& a, int insert_element);

template <typename Iterator>
vector <int> subvector(Iterator begin, Iterator end);

int median(vector <int> a)
{
	sort(a.begin(), a.end());
	return a[(a.size() - 1) / 2];
}

int min_delta_median(vector <int> a)
{
	vector <int > left_vector = subvector(a.begin(), a.begin() + 1);
	vector <int > right_vector = subvector(a.begin() + 1, a.end());
	sort(right_vector.begin(), right_vector.end());

	int delta = abs(median(left_vector) - median(right_vector));
	int mindelta = delta;

	printvector(left_vector);
	printvector(right_vector);
	cout << "delta = " << delta << "; mindelta = " << mindelta << "; median(left_vector) = " << median(left_vector) << "; median(right_vector) = " << median(right_vector) << ";" << endl << endl;
	for (size_t i = 3; i < a.size(); i += 2)
	{
		vector_remove(right_vector, a[i - 2]);
		vector_remove(right_vector, a[i - 1]);

		sorted_insert(left_vector, a[i - 2]);
		sorted_insert(left_vector, a[i - 1]);

		delta = abs(median(left_vector) - median(right_vector));

		mindelta = delta < mindelta ? delta : mindelta;

		printvector(left_vector);
		printvector(right_vector);


		cout << "delta = " << delta << "; mindelta = " << mindelta << "; median(left_vector) = " << median(left_vector) << "; median(right_vector) = " << median(right_vector) << ";" << endl << endl;
	}
	return mindelta;
}

template <typename Iterator>
vector <int> subvector(Iterator begin, Iterator end)
{
	vector <int> result(begin, end);
	return result;
}


void sorted_insert(vector <int>& a, int insert_element) //вставка элемента так, чтобы сохранилась сортировка, (теперь за log(n))
{
	auto left = a.begin();
	auto right = a.end();
	if (insert_element <= a[0]) 
	{
		a.insert(a.begin(), insert_element);
		return;
	}
	while (right - left != 1) 
	{
		//printvector(subvector(left, right));
		cout << endl;
		if (insert_element >= *(left + (right - left) / 2)) //не выходит написать (right + left)/2
		{
			left = (left + (right - left) / 2);
		}
		else 
		{
			right = (left + (right - left) / 2);
		}
	}
	a.insert(right, insert_element);

}

void vector_remove(vector <int>& a, int element) //удаление элемента по значению
{
	auto left = a.begin();
	auto right = a.end();
	while (right - left != 1) //по идее можно было оставить a.find(), но решил всё к log(n) привести
	{
		//printvector(subvector(left, right));
		cout << endl;
		if (element >= *(left + (right - left) / 2))
		{
			left = (left + (right - left) / 2);
		}
		else
		{
			right = (left + (right - left) / 2);
		}
	}
	a.erase(left);
}

void printvector(vector <int> a) //вывод вектора
{
	for (auto t : a)
	{
		cout << t << "\t";
	}
	cout << endl;
}


int main()
{
	vector <int> a{ 3, 1, 8, 10, -5, 32};

	for (auto t : a)
	{
		cout << t << "\t";
	}
	cout << endl << endl;
	cout << min_delta_median(a) << endl;
	return 0;
}
