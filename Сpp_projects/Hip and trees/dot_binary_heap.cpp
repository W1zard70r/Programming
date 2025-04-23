#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
using ll = long long;

#define sq(x) x*x

struct dot
{
	ll x;
	ll y;
};
using dot = struct dot;
void print_tree(vector <dot> Dot_hip);
void drow_dot(vector <dot>& Dot_hip, dot Dot);
ll distance(dot A);
void generate_hip(vector <dot>& Dot_hip);
bool is_power_of_two(int n);

template <typename Iterator>
void shift_up(Iterator begin, int nowindex);

template <typename Iterator>
void shift_down(Iterator begin, Iterator end, int nowindex);

void drow_dot(vector <dot>& Dot_hip, dot Dot);

dot erase_dot(vector <dot>& Dot_hip);

int main()
{
	dot B{ 5, 5 }, A{ 2,2 }, C{ 1, 1 };


		//квадраты длинны    10       562        25       20      17       13        29       41      
	vector <dot> Dot_hip{ { 1,3 }, { -11,21 }, {3, 4}, {-2, 4}, {4, 1}, { 2, 3 }, { 2, 5 }, { 3,6 } };
	cout << "Start tree:" << endl;
	print_tree(Dot_hip);
	cout << endl;

	cout << "generated tree:" << endl;
	generate_hip(Dot_hip);
	print_tree(Dot_hip);

	cout << "dot "<< distance(A) << " was added to tree:" << endl;
	drow_dot(Dot_hip, A);
	print_tree(Dot_hip);
	cout << endl;

	cout << "dot " << distance(B) << " was added to tree:" << endl;
	drow_dot(Dot_hip, B);
	print_tree(Dot_hip);
	cout << endl;

	cout << "dot " << distance(C) << " was added to tree:" << endl;
	drow_dot(Dot_hip, C);
	print_tree(Dot_hip);
	cout << endl;
	
	cout << "nearest dot was deleted from tree: ";
	cout << distance(erase_dot(Dot_hip)) << endl;
	print_tree(Dot_hip);
	cout << endl;

	cout << "nearest dot was deleted from tree: ";
	cout << distance(erase_dot(Dot_hip)) << endl;
	print_tree(Dot_hip);
	cout << endl;
	return 0;
}




ll distance(dot A) //нахождение квадрата расстояния до (0,0)
{
	return sq(A.x) + sq(A.y);
}

template <typename Iterator>
void shift_up(Iterator begin, int nowindex) //поднятие элемента nowindex
{
	while (distance(*(begin + nowindex)) < distance(*(begin + (nowindex - 1) / 2)) && nowindex != 0)
	{
		swap(*(begin + nowindex), *(begin + (nowindex - 1) / 2));
		nowindex = (nowindex - 1) / 2;
	}
}

template <typename Iterator>
void shift_down(Iterator begin, Iterator end, int nowindex) //опускание элемента nowindex
{
	while ( nowindex * 2 + 1 < end - begin)
	{
		if (nowindex * 2 + 2 < end - begin)
		{
			ll now_distance = distance(*(begin + nowindex));
			ll left_distance = distance(*(begin + nowindex * 2 + 1));
			ll right_distance =  distance(*(begin + nowindex * 2 + 2));
			if ((left_distance < now_distance) || (now_distance > right_distance))
			{
				if (left_distance < right_distance)
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
			if (distance(*(begin + nowindex)) > distance(*(begin + nowindex * 2 + 1)))
			{
				swap(*(begin + nowindex), *(begin + nowindex * 2 + 1));
				nowindex = nowindex * 2 + 1;
			}
			break;
		}
	}
}

void drow_dot(vector <dot> &Dot_hip, dot Dot) //добавление точки
{
	Dot_hip.push_back(Dot);
	size_t nowindex = Dot_hip.size() - 1;
	shift_up(Dot_hip.begin(), nowindex);
}

void generate_hip(vector <dot> &Dot_hip) //формирование двоичной кучи
{
	int k = 0;
	int t = 1;
	// k - количество строчек в дереве
	while ( t - 1 < Dot_hip.size()   ) 
	{
		k++;
		t *= 2;
	}

	//сначала опускаем верхние элементы у которых дети на последней строчке дерева
	for (int i = pow(2, k - 2) - 1; i < pow(2, k - 2) - 1 + (Dot_hip.size() - (2 * (pow(2, k - 2)) - 1)) / 2; i++)
	{
		shift_down(Dot_hip.begin(), Dot_hip.end(), i);
	}

	//затем опускаем элементы в рядях выше построчно
	for (int i = pow(2, k - 2); i >= 0; i--)
	{
		shift_down(Dot_hip.begin(), Dot_hip.end(), i);
	}
}

dot erase_dot(vector <dot>& Dot_hip) //взятие ближайшей точки
{
	dot nearest = Dot_hip[0];
	Dot_hip[0] = Dot_hip[Dot_hip.size() - 1];
	Dot_hip.pop_back();
	shift_down(Dot_hip.begin(), Dot_hip.end(), 0);
	return nearest;
}

bool is_power_of_two(int n) 
{
	return !(n & (n - 1));
}

void print_tree(vector <dot> Dot_hip) //вывод кучи как что-то похожее на дерево, но вместо точек квадрат длинны до (0,0)
{
	int k = 0;
	int t = 1;
	// k - количество строчек в дереве
	while (t - 1 < Dot_hip.size())
	{
		k++;
		t *= 2;
	}
	//рофлы с табуляцией, чтобы было похоже на что-то нормальное
	int count_tabs = pow(2, k);
	for (size_t i = 0; i < Dot_hip.size(); i++)
	{	
		if (is_power_of_two(i+1))
		{
			count_tabs = count_tabs / 2 >= 1 ? count_tabs / 2 : 1;
			cout << endl;
		}
		for (size_t i = 0; i < count_tabs; i++)
		{
			cout << '\t';
		}
		cout << distance(Dot_hip[i]);
	}
	cout << endl;
}
