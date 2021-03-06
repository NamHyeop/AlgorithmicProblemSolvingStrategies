#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<string>

using namespace std;

//현재 정점 번호가 here이라면, 간선 번호 edge를
//따라 갔을 때 나오는 정점의 번호는?

int append(int here, int edge, int mod)
{
	int there = here * 10 + edge;
	if (there >= mod)
		return mod + there % mod;
	return there % mod;
}

//digits에 속한 숫자들만으로 구성되고,
//C mod n == m인 최소의 C를 찾는다.
string gifts(string digits, int n, int m)
{
	//간선의 번호를 오름차순으로 정렬해두면 사전순으로 가장앞에
	//있는 경로를 찾을 수 있다.
	sort(digits.begin(), digits.end());
	//흰색 정점 i는 0 ~ n-1, 회색 정점 i는 n ~ 2n-1로 표현한다.
	//이런 식으로 구분하는 이유는 n보다 나머지 값이 작은 경우
	//즉 한 개의 층에서 나오지 못하고 갇혀 있는 경우를 대비함을 위해서이다.
	//parent[i] = BFS 스패닝 트리에서 정점 i의 부모
	//choice[i] = parent[i] 에서 i로 연결된 간선의 번호
	vector<int> parent(2 * n, -1), choice(2 * n, -1);
	queue<int> q;
	//흰색 0번을 큐에 추가
	parent[0] = 0;
	q.push(0);
	while (!q.empty())
	{
		int here = q.front();
		q.pop();
		for (int i = 0; i < digits.size(); i++)
		{
			//간선 digits[i] -'0'을 따라가 본다.
			int there = append(here, digits[i] - '0', n);
			if (parent[there] == -1)
			{
				parent[there] = here;
				choice[there] = digits[i] - '0';
				q.push(there);
			}
		}
	}

	//회색 m번에 도달하지 못했으면 실패!
	if (parent[n + m] == -1)
		return "IMPOSSIBLE";

	//부모로 가는 연결을 따라가면서 C를 계산한다.
	string ret;
	int here = n + m;
	while (parent[here] != here)
	{
		ret += char('0' + choice[here]);
		here = parent[here];
	}
	reverse(ret.begin(), ret.end());
	return ret;
}

int main(int argc, char *argv[])
{
	int Testcase;
	cin >> Testcase;

	for (int i = 0; i < Testcase; i++)
	{
		string vaildNum;
		int N;
		int M;

		cin >> vaildNum >> N >> M;
		
		cout << gifts(vaildNum, N, M) << "\n";
	}

	return 0;
}
