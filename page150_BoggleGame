#include<iostream>
#include<vector>
#include<string>
using namespace std;

vector<string> board;
//(0,0) 기준으로 8방향 설정 
const int dx[8] = { -1, -1, -1, 1, 1, 1, 0, 0 };
const int dy[8] = { -1, 0, 1, -1, 0, 1, -1, 1 };

bool hasWord(int x, int y, const string& word)
{
	//기저 사례1: 시작 위치가 범위 밖이면 무조건 실패
	if (x < 0 || y<0 || x>=5 || y >=5)
		return false;
	//기저 사례2: 첫 글자가 일치하지 않으면 실패
	if (board[x][y] != word[0])
		return false;
	//기저 사례3: 단어 길이가 1이면 성공
	if (word.size() == 1)
	{
		cout << x << "," << y << endl;
		return true;
	}
	//인접한 8칸을 검사한다.

	for (int direction = 0; direction < 8; ++direction)
	{
		
		int nextY = y + dy[direction];
		int nextX = x + dx[direction];

		//자신위 위치에서 방향에 대한 값을 더해 글자가 있는지 없는지 확인. 이 과정을 재귀를 통해 반복
		if (hasWord(nextX, nextY, word.substr(1)))
		{
			cout << x << "," << y << endl;
			return true;
		}

	}
		return false;
	
}

int main()
{
	string input;
	cin >> input;
	board.push_back("NNNNS");
	board.push_back("NEEEN");
	board.push_back("NEYEN");
	board.push_back("NEEEN");
	board.push_back("NNNNN");

	bool flag = false;

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (hasWord(i, j, input))
				flag = true;
			

	if (flag)
		cout << "exist" << endl;
	else
		cout << "non_exist" << endl;

	return 0;
}
