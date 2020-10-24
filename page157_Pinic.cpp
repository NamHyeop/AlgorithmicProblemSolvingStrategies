#include<iostream>
#include<cstring>
using namespace std;

int friendNum;
bool friendcheck[10][10];
//int line[10];

int match(bool check[10])
{
	int freeSignal = -1;

	for (int j = 0; j < friendNum; j++)
	{
		if (!check[j])
		{
			freeSignal = j;
			break;
		}
	}

	if (freeSignal == -1)
		return 1;
	
	int result = 0;

	for (int nextMatch = freeSignal + 1; nextMatch < friendNum; ++nextMatch)
	{
		if (!check[nextMatch] && friendcheck[freeSignal][nextMatch])
		{
			check[freeSignal] = check[nextMatch] = true;
			result += match(check);
			check[freeSignal] = check[nextMatch] = false;
		}
	}

	return result;
}

int main(void)
{
	int cycleNum;
	bool check[10];
	cin >> cycleNum;

	if (cycleNum > 50)
	{
		exit(-1);
	}

	for (int i = 0; i < cycleNum; i++)
	{
		int pair;
		cin >> friendNum >> pair;
		if (friendNum < 2 || friendNum > 10 || pair < 0 || pair >(((friendNum)*(friendNum - 1)) / 2)){ exit(-1); }

		memset(friendcheck, false, sizeof(friendcheck));
		memset(check, false, sizeof(check));

		for (int k = 0; k < pair; k++)
		{
			int friends1, friends2;
			cin >> friends1 >> friends2;
			friendcheck[friends1][friends2] = friendcheck[friends2][friends1] = true;

		}
		cout << match(check) << endl;
		//line[i] = match(check);
	}

	/*
	for (int a = 0; a < cycleNum; a++)
	{
		cout << line[a] << endl;
	}*/
	return 0;
}
