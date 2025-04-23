#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

string to_right(string s)
{
    vector <int> a;

    //считывание строки в вектор
    stringstream ss;
    ss.str(s);
    int temp;
    while (ss >> temp)
        a.push_back(temp);
    
    //запись количеств каждого числа
    vector <int> count_numbers(11,0);
    for (size_t i = 0; i < a.size(); i++)
    {
        count_numbers[a[i]]++;
    }
    
    //создание конечной строки
    string result;
    for (size_t i = 1; i < count_numbers.size(); i++)
    {
        while(count_numbers[i] > 0)
        {
            result+= to_string(i)+ "+";
            count_numbers[i]--;
        }
    }
    
    return result.substr(0,result.length()-1);
}   

int main()
{
    string s = "7+4+3+10+2+7+1+2+1+3+10+3";
    cout<<to_right(s);
    return 0;
}