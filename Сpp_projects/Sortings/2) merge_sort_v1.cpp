#include <iostream>
#include <iterator>
#include <vector>

using namespace std;
vector <int> merge(vector <int> left_path, vector <int> right_path);
void printvector(vector <int> a);
bool is_sorted(vector <int> a);

inline vector <int> sort(vector <int> a)
{
    if (a.size() == 1)
        return a;
    if (is_sorted(a))
        return a;
    vector <int> left_path(a.begin(), a.begin() + (a.end() - a.begin()) / 2);
    vector <int> right_path(a.begin() + (a.end() - a.begin()) / 2, a.end());
    //printvector(left_path);
    //printvector(right_path);
    left_path = sort(left_path);
    right_path = sort(right_path);
    //printvector(left_path);
    //printvector(right_path);
    //printvector(merge(left_path, right_path));
    return merge(left_path,right_path);
    
}

 vector <int> merge(vector <int> left_path, vector <int> right_path)
 {
     auto left_min_pointer = left_path.begin();
     auto right_min_pointer = right_path.begin();
     vector <int> result;
     for (size_t i = 0; i < left_path.size() + right_path.size(); i++)
     {
         if (left_min_pointer != left_path.end() && right_min_pointer != right_path.end()) 
         {
             if (*left_min_pointer < *right_min_pointer) 
             {
                 result.push_back(*left_min_pointer);
                 left_min_pointer++;
             }
             else 
             {
                 result.push_back(*right_min_pointer);
                 right_min_pointer++;
             }
         }
         else if (left_min_pointer == left_path.end()) 
         {
             result.push_back(*right_min_pointer);
             right_min_pointer++;
         }
         else 
         {
             result.push_back(*left_min_pointer);
             left_min_pointer++;
         }
     }
     return result;
 }
 void printvector(vector <int> a) 
 {
     for (size_t i = 0; i < a.size(); i++)
     {
         cout << a[i] << "\t";
     }
     cout << endl;
 }

 bool is_sorted(vector <int> a) 
 {
     size_t i = 0;
     while (i < a.size() - 1 && a[i] <= a[i + 1]) i++;
     
     return (i == a.size()-1) ? 1 : 0;
 }

int main()
{

    vector <int> a{ 99,88, 88,80,70 };

    for (auto t : a)
    {
        cout << t << "\t";
    }
    cout << endl;

    a = sort(a);
    for (auto t : a)
    {
        cout << t << "\t";
    }

    return 0;
}