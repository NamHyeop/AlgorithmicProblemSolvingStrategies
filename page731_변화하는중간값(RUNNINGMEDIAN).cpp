#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<functional>

using namespace std;

//수열 생성기
struct RNG{
	int seed;
	int a;
	int b;
	RNG(int _a, int _b) : a(_a), b(_b), seed(1983){}
	int next()
	{
		int ret = seed;
		seed = ((seed * (long long)a) + b) % 20090711;
		return ret;
	}
};

int runningMedian(int n, RNG rng)
{
	priority_queue<int, vector<int>, less<int>> maxHeap;
	priority_queue<int, vector<int>, greater<int>> minHeap;
	int ret = 0;

	//반복문 불변식:
	//1.maxHeap의 크기는 minHeap의 크기와 같거나 1 더 크다.
	//2.maxHeap.top() <= minHeap.top()
	for (int cnt = 1; cnt <= n; ++cnt)
	{
		//우선 1번 불변식부터 만족시킨다.
		if (maxHeap.size() == minHeap.size())
			maxHeap.push(rng.next());
		else
			minHeap.push(rng.next());
		//2번 불변식이 깨졌을 경우 복구하자.
		if (!minHeap.empty() && !maxHeap.empty() && minHeap.top() < maxHeap.top())
		{
			int a = maxHeap.top();
			int b = minHeap.top();
			maxHeap.pop();
			minHeap.pop();
			maxHeap.push(b);
			minHeap.push(a);
		}
		ret = (ret + maxHeap.top()) % 20090711;
	}
	return ret;
}

int main(int argc, char *argv[])
{
	int Testcase;
	cin >> Testcase;

	for (int i = 0; i < Testcase; i++)
	{
		int N;
		int a;
		int b;
		cin >> N >> a >> b;
		RNG generator(a, b);

		cout << runningMedian(N, generator) << endl;
	}
	return 0;
}
