#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
using ll = long long;

void print_vector(vector <int> a);
void print_tree(vector <vector <int>> Vec_heap);

void generate_heap(vector <vector <int>> &Vec_heap);
int get_min(vector <vector <int>>& Vec_heap);

template <typename Iterator>
void shift_up(Iterator begin, int nowindex);

template <typename Iterator>
void shift_down(Iterator begin, Iterator end, int nowindex);

vector <int> merge(vector <vector <int> > a);

int main()
{
	vector <vector <int>> a{ {1,3,4,5,6}, {2}, {4,10}, {6,11,23} };
	vector <int>res = merge(a);
	cout << "res = ";
	print_vector(res);
	return 0;
}

vector <int> merge(vector <vector <int> > a) 
{
	vector <int> result;
	generate_heap(a); //делаем из массива массивов кучу по первому элементу

	while (a.size() != 0)
	{
		cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
		print_tree(a);
		result.push_back(get_min(a));
	}
	return result;
}

template <typename Iterator>
void shift_up(Iterator begin, int nowindex) //поднятие элемента nowindex
{
	while ((*(begin + nowindex))[0] < (*(begin + (nowindex - 1) / 2))[0] && nowindex != 0)
	{
		swap(*(begin + nowindex), *(begin + (nowindex - 1) / 2));
		nowindex = (nowindex - 1) / 2;
	}
}

template <typename Iterator>
void shift_down(Iterator begin, Iterator end, int nowindex) //опускание элемента nowindex
{
	while (nowindex * 2 + 1 < end - begin)
	{
		if (nowindex * 2 + 2 < end - begin)
		{
			ll now_min = (*(begin + nowindex))[0];
			ll left_min = (*(begin + nowindex * 2 + 1))[0];
			ll right_min = (*(begin + nowindex * 2 + 2))[0];
			if ((left_min < now_min) || (now_min > right_min))
			{
				if (left_min < right_min)
				{
					swap(*(begin + nowindex), *(begin + nowindex * 2 + 1));
					nowindex = nowindex * 2 + 1;
				}
				else
				{
					swap(*(begin + nowindex), *(begin + nowindex * 2 + 2));
					nowindex = nowindex * 2 + 2;
				}
			}
			else
				break;
		}
		else
		{
			if ((*(begin + nowindex))[0] > (*(begin + nowindex * 2 + 1))[0])
			{
				swap(*(begin + nowindex), *(begin + nowindex * 2 + 1));
				nowindex = nowindex * 2 + 1;
			}
			break;
		}
	}
}

void generate_heap(vector <vector <int>>& Vec_heap) //формирование двоичной кучи
{
	int k = 0;
	int t = 1;
	// k - количество строчек в дереве
	while (t - 1 < Vec_heap.size())
	{
		k++;
		t *= 2;
	}

	//сначала опускаем верхние элементы у которых дети на последней строчке дерева
	for (int i = pow(2, k - 2) - 1; i < pow(2, k - 2) - 1 + (Vec_heap.size() - (2 * (pow(2, k - 2)) - 1)) / 2; i++)
	{
		shift_down(Vec_heap.begin(), Vec_heap.end(), i);
	}

	//затем опускаем элементы в рядях выше построчно
	for (int i = pow(2, k - 2); i >= 0; i--)
	{
		shift_down(Vec_heap.begin(), Vec_heap.end(), i);
	}
}

int get_min(vector <vector <int>>& Vec_heap) //взятие самого маленького элемента и опускание массива в конец кучи
{
	int nearest = Vec_heap[0][0];
	if (Vec_heap[0].size() > 1)
	{
		vector <int> temp(Vec_heap[0].begin() + 1, Vec_heap[0].end());
		Vec_heap[0] = Vec_heap[Vec_heap.size() - 1];
		shift_down(Vec_heap.begin(), Vec_heap.end(), 0);

		Vec_heap[Vec_heap.size() - 1] = temp;
		shift_up(Vec_heap.begin(), Vec_heap.size() - 1);
	}
	else
	{
		Vec_heap[0] = Vec_heap[Vec_heap.size() - 1];
		Vec_heap.pop_back();
		shift_down(Vec_heap.begin(), Vec_heap.end(), 0);
	}
	return nearest;
}

bool is_power_of_two(int n)
{
	return !(n & (n - 1));
}

void print_vector(vector <int> a) 
{
	cout << "[";
	for (int i = 0; i < a.size() - 1; i++)
	{
		cout << a[i] << ", ";
	}
	cout << a.back();
	cout << "]";
}

void print_tree(vector <vector <int>> Vec_heap) //вывод кучи как что-то похожее на дерево, но вместо точек квадрат длинны до (0,0)
{
	int k = 0;
	int t = 1;
	// k - количество строчек в дереве
	while (t - 1 < Vec_heap.size())
	{
		k++;
		t *= 2;
	}
	//рофлы с табуляцией, чтобы было похоже на что-то нормальное
	int count_tabs = pow(2, k);
	for (size_t i = 0; i < Vec_heap.size(); i++)
	{
		if (is_power_of_two(i + 1))
		{
			count_tabs = count_tabs / 2 >= 1 ? count_tabs / 2 : 1;
			cout << endl;
		}
		for (size_t i = 0; i < count_tabs; i++)
		{
			cout << '\t';
		}
		print_vector(Vec_heap[i]);
	}
	cout << endl;
}