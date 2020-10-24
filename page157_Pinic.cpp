#include<iostream>
#include<vector>
#include<string>
using namespace std;

//주어진 칸을 덮을 수 있는 네 가지 방법
int covertype[4][3][2] = {
	{ { 0, 0 }, { 1, 0 }, { 0, 1 } },
	{ { 0, 0 }, { 0, 1 }, { 1, 1 } },
	{ { 0, 0 }, { 1, 0 }, { 1, 1 } },
	{ { 0, 0 }, { 1, 0 }, { 1, -1 } }
};

//v의(y,x)를 type번 방법으로 덮거나, 덮었던 블록을 없앤다.
/*delta = 1이면 덮고, -1이면 덮었던 블록을 없앤다 -> 이게 무슨 말이냐면 주어진 그림에서 체크하면 0이었던
걸 1로 바꾸어서 체크한걸로 만드는데 재귀함수 구조상 경우의 수를 다 반복해야 하므로 경우의 수를 체크하고
없었던 상태 0으로 바꾸어 다시 테스트 하는걸 의미함, 이해가 안가면 코드의 재귀구조를 다시 확인하자*/

bool set(vector<vector<int>> &v, int y, int x, int type, int delta){
	bool ok = true;
	for (int i = 0; i < 3; i++){
		int ny = y + covertype[type][i][0];
		int nx = x + covertype[type][i][1];
		//게임판에 사이즈를 벗어나면 flase 반환
		if (ny < 0 || ny >= v.size() || nx < 0 || nx >= v[0].size())
			ok = false;
		//delta가 -1인경우 -> 이게 무슨 의미냐면 이미 검게 차지한 대가 1인데 거기에 또 차지하면 1이상이니까 거짓을 반환함
		else if ((v[ny][nx] += delta) > 1)
			ok = false;
	}
	return ok;
}

int cover(vector<vector<int>> &v){
	int y = -1;
	int x = -1;
	//도형의 맨 윗줄 왼쪽을 기준으로 가장 먼저 보이는 흰칸을 찾는다.
	for (int i = 0; i<v.size(); i++){  //첫 백터 초기화 값의 사이즈까지 ex:)3
		for (int j = 0; j<v[i].size(); j++){ //두 번째 백터 초기화 값의 사이즈까지 ex:)7
			if (v[i][j] == 0){
				y = i;
				x = j;
				break;
			}
		}
		if (y != -1)
			break;
	}

	if (y == -1) return 1;
	int ret = 0;

	for (int type = 0; type < 4; ++type){
		//board(y,x)를 type 형태로 덮을 수 있으면 재귀 호출한다.
		if (set(v, y, x, type, 1))
			ret += cover(v);
		//덮었던 블록을 치운다.
		set(v, y, x, type, -1);
	}
	return ret;
}

int main(){
	int TestNum;
	cin >> TestNum;

	int y, x;
	for (int i = 0; i < TestNum; i++){
		cin >> y >> x;
		vector<vector<int>> v(y,vector<int>(x,0)); //1.행열을 의미하는 vector 생성
		string input;

		for (int j = 0; j<y; j++){ //2.행만큼 게임판에 대한 미로를 입력받고
			cin >> input;
			for (int k = 0; k < input.size(); k++){//3.입력받은것중에 #이면 1로 표시함
				if (input[k] == '#')
					v[j][k] = 1;
			}
		}

		// vector의 2차원 배열에서 v.size는 행을 의미하고 v[i].size는 열을 의미한다.
	//	cout << v.size() << endl;
	//	cout << v[1].size() << endl;
	//	cout << v[2].size() << endl;
		
		cout << cover(v) << endl;
	}
}

