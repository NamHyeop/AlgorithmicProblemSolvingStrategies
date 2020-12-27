#include<iostream>
#include<vector>

using namespace std;

//그래프의 인접 리스트 표현
vector<vector<int>> adj;
//두 구간 a와 b가 서로 겹치지 않는지를 확인한다.
bool disjoint(const pair<int, int> &a, const pair<int, int>& b)
{
	return a.second <= b.first || b.second <= a.first;
}

//meetings[]가 각 팀이 하고 싶어하는 회의 시간의 목록일 때, 이를
//2-SAT 문제로 변환한 뒤 함의 그래프를 생성한다.
//i번 팀은 meetings[2*i]혹은 meetings[2*i+1]중 하나 시간에 회의실을 써야 한다.
void makeGraph(const vector<pair<int, int>> &meetings)
{
	int vars = meetings.size();
	//그래프는 각 변수마다 두 개의 정점을 갖는다.
	adj.clear();
	adj.resize(vars * 2); // 2n개의 변수가 있는데 각 변수를 참인 경우와 거짓인 경우가 있으니 4n이 되는거다.
	for (int i = 0; i < vars; i += 2)
	{
		//각 팀은 i번 회의나 j번 회의 둘 중 하나는 해야 한다.
		//(i or j)절을 추가한다.
		int j = i + 1;
		adj[i * 2 + 1].push_back(j * 2); // ~i -> j, a0,!a0,a1,!a1 순서로 입력받기 때문이다
		adj[j * 2 + 1].push_back(i * 2);// ~j -> i
	}
	for (int i = 0; i < vars; i++)
	for (int j = 0; j < j < i; j++)
	{
			//i번 회의와 j번 회의가 서로 겹칠 경우
			if (!disjoint(meetings[i], meetings[j]))
			{
				//i번 회의가 열리지 않거나, j번 회의가 열리지 않아야 한다.
				//(~i or ~j) 절을 추가한다.
				adj[i * 2].push_back(j * 2 + 1); // i => ~j
				adj[j * 2].push_back(i * 2 + 1); // j => ~i
			}
	}
}
