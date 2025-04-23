#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
void print_vector(vector <int> a);
vector <int> product_except_self(vector <int > t) 
{
	if (t.size() == 1)
		return vector<int>{};
	vector <int> result;

	vector <int> pref_multi_left{1};
	vector <int> post_multi_right{1};

	//создаем список с префиксными произведениями O(n)
	for (size_t i = 0; i < t.size(); i++)
	{
		pref_multi_left.push_back(t[i] * pref_multi_left[i]);
	}
	//print_vector(pref_multi_left);

	//создание списка с простфиксными произведениями чисел после данного O(n)
	for (int i = t.size() - 1; i >= 0; i--)
	{
		post_multi_right.push_back(t[i] * post_multi_right[t.size() - 1 - i]);
	}
	//print_vector(post_multi_right);

	//для более удобно записи перевернём post_multi_right 
	for (size_t i = 0; i < post_multi_right.size() / 2; i++)
	{
		swap(post_multi_right[i], post_multi_right[post_multi_right.size() - i - 1]);
	}
	//print_vector(post_multi_right);

	//формирование вектора result
	for (size_t i = 1; i < pref_multi_left.size(); i++)
	{
		result.push_back(pref_multi_left[i - 1] * post_multi_right[i]);
	}

	return result;
}

void print_vector(vector <int> a)
{
	for (size_t i = 0; i < a.size(); i++)
	{
		cout << a[i] << "\t";
	}
	cout << endl;
}

int main() 
{
	vector <int> a{1,0,2,5};
	print_vector(a);
	
	vector <int> b = product_except_self(a);
	print_vector(b);
	return 0;
}	