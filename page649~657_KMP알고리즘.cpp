#include<iostream>
#include<vector>
using namespace std;

vector<int> getPartialMatch(const string & N)
{
	int m = N.size();
	vector<int> pi(0, m);
	//KMP로 자기 자신을 찾는다
	//N을 N에서 찾는다. begin=0이면 자기 잣니을 찾아버리니까 안됨!
	int begin = 1, matched = 0;
	//비교할 문자가 N의 끝에 도달할 때까지 찾으면서 부분 일치를 모두 기록한다.
	while (begin + matched < m)
	{
		if (N[begin + matched] == N[matched])
		{
			++matched;
			pi[begin + matched - 1] = matched;
		}
		else
		{
			if (matched == 0)
				++begin;
			else{
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}

		}
	}
	return pi;
}


//H(짚더미, 왜 짚더민인지는 모름 그냥 애칭인듯)의 부분 문자열로 N(바늘,마찬가지로이유모름)이 출현하는 시작 위치들을 모두 반환한다.
vector<int> kmpSearch(const string& H, const string& N)
{
	int n = H.size(), m = N.size();
	vector<int> ret;
	vector<int> pi = getPartialMatch(N);

	//begin = matched = 0에서부터 시작하자
	int begin = 0, matched = 0;
	//만약 짚더미의 해당 글자가 바늘의 해당 글자와 같다면
	while (begin <= n - m)
	{
		if (matched < m && H[begin + matched] == N[matched])
		{
			++matched;

			//결과적으로 matched의 갯수가 m의 갯수와 같아진다면 모두 일치했다는 의미로 답에 추가한다.
			if (matched == m)
				ret.push_back(begin);
		}
		else
		{
			//예외: matched가 0인 경우에는 다음 칸에서부터 계속
			if (matched == 0)
				++begin;
			else
			{
				begin += matched - pi[matched - 1];
				//begin을 옮겼다고 처음부터 다시 비교할 필요가 없다.
				//옮긴 후에도 pi[matchd-1]만큼은 항상 일치하기 때문이다.
				matched = pi[matched - 1];
			}
		}
	}
	return ret;
}
