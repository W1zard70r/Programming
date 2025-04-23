#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int max(vector <int> a);
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


void sorted_insert(vector <int> &a, int insert_element) //вставка элемента так, чтобы сохранилась сортировка
{
	int i = 0;
	while (i< a.size() && insert_element > a[i])
		i++;
	if (i != a.size())
		a.insert(a.begin() + i, insert_element);
	else
		a.push_back(insert_element);
}

void vector_remove(vector <int> &a, int element) //удаление элемента по значению
{
	a.erase(find(a.begin(), a.end(), element));
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
	vector <int> a{ 1, 2, 99, 3, 99, 100};

	for (auto t : a)
	{
		cout << t << "\t";
	}

	cout << endl << endl;
	cout << min_delta_median(a) << endl;
	return 0;
}
