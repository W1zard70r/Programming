#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

typedef struct segment 
{
	int l, r;
}segment;

class SegmentSet
{
private:
	int eps = 1000; //разброс значений
	// по идее, если |r,l| > eps, то его нужно увеличить, но я сегодня это уже не успею сделать

	vector <int> counter; //в кажом элементе показано сколько отрезков его покрывают
	vector <int> delta_counter; //0 - ой элемент это -eps, eps - ноль, 2 * eps элемент - eps

	vector <segment> no_added{}; //массив с ещё не добавленными отрезками
public:

	SegmentSet() : delta_counter(2 * eps + 1, 0), counter(2 * eps, 0) {}

	SegmentSet(vector <segment> s) : delta_counter(2 * eps + 1, 0), counter(2 * eps + 1, 0) {
		for (auto t : s) //добавляем отрезки в разностный массив
		{
			delta_counter[eps + t.l]++;
			delta_counter[eps + t.r + 1]--;
		}
		counter[0] = delta_counter[0]; //собираем из разностного массива массив с количеством покрывающих отрезков
		for (size_t i = 1; i < delta_counter.size(); i++)
		{
			counter[i] = delta_counter[i] + counter[i - 1];
		}
	}

	void add_segment(int l, int r)
	{
		no_added.push_back({ l, r }); 
	}

	int count_segments(int x) 
	{
		if (no_added.size() != 0) //если есть недобавленные отрезки, добавляем
		{
			for (auto t : no_added) //добавляем отрезки в разностный массив
			{
				delta_counter[eps + t.l]++;
				delta_counter[eps + t.r + 1]--;
			}
			counter[0] = delta_counter[0]; //собираем из разностного массива массив с количеством покрывающих отрезков
			for (size_t i = 1; i < delta_counter.size(); i++)
			{
				counter[i] = delta_counter[i] + counter[i - 1];
			}
			no_added.clear();
		}
		return counter[eps + x];
	}
};

int main()
{
	SegmentSet ss({ {-100, 100}, {40, 50}, {1, 2}, {3, 10}, {0, 70}, {-2, 5}, {-2, 11} });
	cout << ss.count_segments(11) << endl;
	ss.add_segment(-500, 500);
	ss.add_segment(-10, 40);
	cout << ss.count_segments(11) << endl;
	return 0;
}