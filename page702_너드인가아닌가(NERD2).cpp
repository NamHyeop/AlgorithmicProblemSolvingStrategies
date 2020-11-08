#include<iostream>
#include<map>
using namespace std;

//현재 다른 점에 지배당하지 않는 점들의 목록을 저장한다.
//coords[x] = y;
map<int, int> coords;

bool isDominated(int x, int y)
{
	//x보다 오른쪽에 있는 점 중 가장 왼쪽에 있는 점을 찾는다.
	map<int, int>::iterator it = coords.lower_bound(x);
	//현재 점 (x,y)보다 오른쪽에 있는 점이 없다면 지배받지 않는다.
	if (it == coords.end())
		return false;
	//이 점은 x보다 오른쪽에 있는 점 중 가장 위에 있는 점이므로,
	//(x,y)가 어느 점에 지배되려면 이 점에도 지배되어야 한다.
	if (y < it->second)
		return true;
	else
		return false;
}

void removeDominated(int x, int y)
{
	map<int, int>::iterator it = coords.lower_bound(x);
	//(x,y)보다 왼쪽에 있는 점이 없다.
	if (it == coords.begin())
		return;
	//왼쪽에 있는 점들이 존재하는 경우, y값을 비교한다. y는 내림차순이어야만 함
	--it;
	//반복문 불변식: it는(x,y)의 바로 왼쪽에 있는 점
	while (true)
	{
		//(x,y)바로 왼쪽에 오는 점을 찾는다.
		//it가 표시하는 점이 (x,y)에 지배되지 않는다면 곧장 종료
		if (it->second > y)
			break;
		if (it == coords.begin())
		{
			coords.erase(it);
			break;
		}
		else
		{
			map<int, int>::iterator jt = it;
			--jt;
			coords.erase(it);
			it = jt;
		}
	}
}

//새 점(x, y)가 추가되었을 때 coords를 갱신하고
//다른 점에 지배당하지 않는 점들의 개수를 반환한다.
int registered(int x, int y)
{
	//(x,y)가 이미 지배당하는 경우에는 그냥 (x,y)를 버린다.
	if (isDominated(x, y))
		return coords.size();
	//지배 당하지 않는 경우는 기존에 있던 점 중(x,y)에 지배당하는 점들을 지운다.
	removeDominated(x, y);
	coords[x] = y;
	return coords.size();
}

int main(int argc, char *argv[])
{
	int Testcase;
	cin >> Testcase;

	for (int i = 0; i < Testcase; i++)
	{
		int ret = 0;
		int nodeNum;
		cin >> nodeNum;

		coords.clear();
		
		for (int i = 0; i < nodeNum; i++)
		{
			int x;
			int y;

			cin >> x >> y;
			ret += registered(x, y);
		}
		cout << ret << '\n';
	}

	return 0;
}
