#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<queue>
using namespace std;

map<vector<int>, int> toSort;
//[0,....,n-1]의 모든 순열에 대해 toSort[]를 계산해 저장한다.
void precalc(int n)
{
	vector<int> perm(n);
	for (int i = 0; i < n; i++)
		perm[i] = i;
	queue<vector<int>> q;
	q.push(perm);
	toSort[perm] = 0;
	while (!q.empty())
	{
		vector<int> here = q.front();
		q.pop();
		int cost = toSort[here];
		for (int i = 0; i < n; i++)
		{
			for (int j = i + 2; j <= n; j++)
			{
				reverse(here.begin() + i, here.begin() + j);
				if (toSort.count(here) == 0)
				{
					toSort[here] = cost + 1;
					q.push(here);
				}
				reverse(here.begin() + i, here.begin() + j);
			}
		}
	}
}

int solve(const vector<int> &perm)
{
	//perm 을 [0,...n-1]의 순열로 반환한다.
	int n = perm.size();
	vector<int> fixed(n);
	for (int i = 0; i < n; i++)
	{
		int smaller = 0;
		for (int j = 0; j < n; j++)
		if (perm[j] < perm[i])
			++smaller;
		fixed[i] = smaller;
	}
	return toSort[fixed];
}

int main(int argc, char *argv[])
{
	int Testcase;
	cin >> Testcase;
	for (int i = 0; i < Testcase; i++)
	{
		int n;
		cin >> n;
		vector<int> bridge(n, 0);
		for (int i = 0; i < n; i++)
			cin >> bridge[i];

		precalc(n);
		cout << solve(bridge) << "\n";
	}
	return 0;
}
/*
//perm을 정렬하기 위해 필요한 최소 뒤집기 연산의 수를 계산한다.
int bfs(const vector<int> &perm)
{
	int n = perm.size();
	//목표 정점을 미리 계산한다.
	vector<int> sorted = perm;
	sort(sorted.begin(), sorted.end());
	//방문 목록(큐)과 시작점부터 각 정점까지의 거리
	queue<vector<int>> q;
	map<vector<int>, int> distance;
	//시작점을 큐에 넣는다.
	distance[perm] = 0;
	q.push(perm);
	while (!q.empty())
	{
		vector<int> here = q.front();
		q.pop();
		//목표 정점을 발견했으면 곧장 종료한다.
		if (here == sorted)
			return distance[here];
		int cost = distance[here];
		//가능한 모든 부분 구간을 뒤집어 본다.
		for (int i = 0; i < n; i++)
		for (int j = i+2; j <= n; j++)
		{
			reverse(here.begin() + i, here.begin() + j);
			if (distance.count(here) == 0)
			{
				distance[here] = cost + 1;
				q.push(here);
			}
			reverse(here.begin() + i, here.begin() + j);
		}
	}
	return -1;
}
*/

