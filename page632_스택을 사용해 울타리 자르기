#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
//개인적으로 종만북을 읽으면서 가장 큰 위기가 온 순간이었다.
//코드를 보기전에 이게 뭔 설명인지 이해를 못했고 그래서 반복해서 읽었다.
//저자에게 그냥 감탄과 무한의 존경이 나온다 도데체 어떻게 이렇게 깔끔하고 효율적인 코드가 나오는지 신기하다.

using namespace std;

vector<int> h;

int solveStack()
{
	stack<int> remaining;
	h.push_back(0);
	
	int ret = 0;
	for (int i = 0; i < h.size(); i++)
	{
		//남아있는 판자들 중 오른쪽 끝 판자가 h[j]보다 높다면
		//이 판자의 최대 사각형은 i에서 끝난다.
		while (!remaining.empty() && h[remaining.top()] >= h[i])
		{
			int j = remaining.top();
			remaining.pop();
			int width;
			//j번째 판자 왼쪽에 판자가 하나도 안 남아 있는 경우 left[j] = -1;
			//아닌 경우 left[j] = 남아 있는 판자 중 가장 오른쪽에 있는 판자의 번호가 된다.
			if (remaining.empty())
				width = i;
			else
				width = i - remaining.top() - 1;
			ret = max(ret, h[j] * width);
		}
		remaining.push(i);
	}
	return ret;
}

int main(int argc, char*argv[])
{
	int Testcase;
	cin >> Testcase;

	for (int i = 0; i < Testcase; i++)
	{
		int n;
		h.clear();
		cin >> n;
		for (int j = 0; j < n; j++)
		{
			int height;
			cin >> height;
			h.push_back(height);
		}
		cout << solveStack() << endl;
	}
	return 0;
}
