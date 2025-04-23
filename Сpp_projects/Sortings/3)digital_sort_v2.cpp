#include <iostream>
#include <iterator>
#include <vector>
#include <map>
#include <cmath>
#include <set>

using namespace std;

int maxlen(vector <int> a);
int num(int a, int i);
set <int> map_keys(map <int, vector <int> > dictionary);

vector <int> sort(vector <int> a, int j)
{
    vector <int> result;
    map <int, vector <int> > dict;

    //запихивание элементов в словари по i-ой цифре считая справа, i = 1,2,3,4.., если цифр нет у числа, то i = 0
    for (size_t i = 0; i < a.size(); i++)
    {
        dict[num(a[i], j)].push_back(a[i]);
    }

    //составление из словаря сортированного вектора
    for (auto u : map_keys(dict))
    {
        if (dict[u].size() != 1 && j > 1) //тут добавить условие j > 1, так как иначе бы сравнение шло по нулевой цифре, которой нет
        {
            for (auto t : sort(dict[u], j - 1))
            {
                result.push_back(t);
            }
        }
        else
        {
            for (size_t i = 0; i < dict[u].size(); i++)
            {
                result.push_back(dict[u][i]);
            }
        }
    }
    return result;
}

//функция вычисления i-ой цифры
int num(int a, int i)
{
    while (i > 1)
    {
        a /= 10;
        i--;
    }
    int num_i = a % 10;
    return num_i;
}

//функция вычисления макисмальной длинны числа
int maxlen(vector <int> a)
{
    int n = 0;
    for (size_t i = 0; i < a.size(); i++)
    {
        while (a[i] >= pow(10, n)) n++;
    }
    return n;
}

//функция получения отсортированных ключей словаря
set <int> map_keys(map <int, vector <int> > dictionary)
{
    set <int> result;
    for (auto& pair : dictionary)
    {
        result.insert(pair.first);
    }
    return result;
}

int main()
{
    ///vector <int> a{ 1, 70, 7, 77, 1000, 100, 100 };
    vector <int> a{5,3,1,4,6,99,100};
    for (auto t : a)
    {
        cout << t << "\t";
    }
    cout << endl;

    a = sort(a, maxlen(a));

    for (auto t : a)
    {
        cout << t << "\t";
    }

    return 0;
}