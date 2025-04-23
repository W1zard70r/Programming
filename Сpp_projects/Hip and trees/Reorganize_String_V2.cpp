#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

string reorganize(string S, bool __flag = true);

int main()
{
	string s = "baaba";
	//cout << s << endl;

	string res = reorganize(s);
	cout << "res = " << res << endl;
	return 0;
}

string reorganize(string S, bool __flag)
{
	string result = { S[0] };
	string stack = "";
	//cout << "reorganize " << S << endl;
	for (size_t i = 1; i < S.length(); i++)
	{
		if (stack.length() == 0)
		{
			if (result.back() == S[i])
			{
				stack = S[i];
			}
			else 
			{
				result.push_back(S[i]);
			}
		}
		else 
		{
			if (S[i] == stack[0]) 
			{
				stack.push_back(S[i]);
			}
			else 
			{
				result.push_back(S[i]);
				result.push_back(stack[0]);
				stack.pop_back();
			}
		}
	}
	if (stack.length() != 0)
	{
		if (__flag)
		{
			swap(S[0], S[1]);
			cout << S << endl;
			return reorganize(S, false);
		}
		return "";
	}
	return result;
}