#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int INF = 9999, SWITCHES = 10/*행*/, CLOCKS = 16 /*열*/;
//linked[i][j] ='x': i번 스위치와 j번 시계가 연결되어 있다.
//linked[i][j] ='.': i번 스위치와 j번 시계가 연결되어 있지 않다.

const char linked[SWITCHES][CLOCKS + 1] = {
	//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
	"xxx.............",
	"...x...x.x.x....",
	"....x.....x...xx",
	"x...xxxx........",
	"......xxx.x.x...",
	"x.x...........xx",
	"...x..........xx",
	"....xx.x......xx",
	".xxxxx..........",
	"...xxx...x...x.." };

//모든 시계가 12시를 가리키고 있는지 확인한다.
bool check(const vector<int>& clocks)
{
	for (int i = 0; i < CLOCKS; i++)
	{
		if (clocks[i] != 12)
			return false;
	}
		return true;
	
}
//switch번 스위치를 누른다.
void push(vector<int>& clocks, int swtch)
{
	for (int clock = 0; clock < CLOCKS; ++clock)
	if (linked[swtch][clock] == 'x')
	{
		clocks[clock] += 3;
		if (clocks[clock] == 15) clocks[clock] = 3;
	}
}

//ClockBoard: 현재 시계들의 상태
//swtch: 이번에 누를 스위치의 번호
//가 주어질 때, 남은 스위치들을 눌러서 clocks를 12시로 맞출 수 있는 최소 횟수를 반환한다.
//만약 불가능하다면 INF이상의 큰 수를 반환한다.
int solve(vector<int>& clocks, int swtch) {
	if (swtch == SWITCHES) return check(clocks) ? 0 : INF;
	//이 스위치를 0번 누르는 경우부터 세 번 누르는 경우까지를 모두 시도한다.
	int ret = INF;
	for (int cnt = 0; cnt < 4; ++cnt)
	{
		ret = min(ret, cnt + solve(clocks, swtch + 1));
		push(clocks, swtch);
	}

	//push(clocks, swtch)가 4번 호출되었으니 clocks는 원래와 같은 상태가 된다.
	return ret;
}
int main(int argc, char * argv[])
{
	vector<int> ClockBoard(CLOCKS);
	int TestCase;
	cin >> TestCase;
	if (TestCase < 0 || TestCase>30) return 0;

	for (int i = 0; i < TestCase; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			cin >> ClockBoard[j];

			/*if (ClockBoard[j] == 3);
			else if (ClockBoard[j] == 6);
			else if (ClockBoard[j] == 9);
			else if (ClockBoard[j] == 12);
			else return 0;
			*/
		}
		int result = solve(ClockBoard, 0);
		if (result == INF)
			cout << -1 << endl;
		else
			cout << result << endl;
		
	}
	return 0;
	
}
