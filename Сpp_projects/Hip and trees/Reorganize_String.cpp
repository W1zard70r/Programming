#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

string reorganize(string S);

int main()
{
	string s = "122232124";
	cout << s << endl;

	string res = reorganize(s);
	cout << res << endl;

	return 0;
}

string reorganize(string S) 
{
	swap(S[0], S[1]);
	string result = { S[0] };
	string stack = "";

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
	if (stack.length() == 0)
	{
		return result;
	}
	else
	{
		swap(S[0], S[1]);
		static bool flag = true;
		if (flag)
		{
			flag = false;
			return reorganize(S);
		}
		else
			return "";
	}
}