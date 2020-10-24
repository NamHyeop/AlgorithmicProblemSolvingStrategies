#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

using namespace std;

vector<int> slice(const vector<int> &v, int a, int b)
{
	return vector<int>(v.begin() + a, v.begin() + b);
}

//트리의 전위탐색 결과와 중위탐색 결과가 주어질 때 후위탐색 결과를 출력한다.
void printPostOrder(const vector<int> & preorder, const vector<int> & inorder)
{
	//트리에 포함된 노드의 수
	const int N = preorder.size();
	//기저 사례: 텅 빈 트리면 곧장 종료
	if (preorder.empty())
		return;
	//이 트리의 루트는 전위 탐색 결과로부터 곧장 알 수 있다.
	const int root = preorder[0];
	//이 트리의 왼쪽 서브트리의 크기는 중위 탐색 결과에서 루트의 위치를 찾아서 알 수 있다.
	const int L = find(inorder.begin(), inorder.end(), root) - inorder.begin();
	//오른쪽 서브트리의 크기는 N에서 왼쪽 서브트리와 루트를 빼면 알 수 있다.
	const int R = N - 1 - L;
	//왼족과 오른쪽 서브트리의 순회 결과를 출력
	printPostOrder(slice(preorder, 1, L + 1), slice(inorder, 0, L));
	printPostOrder(slice(preorder, L + 1, N), slice(inorder, L + 1, N));
	//후위 순회이므로 루트를 가장 마지막에 출력한다.
	cout << root << ' ';
}

int main(int argc, char*argv[])
{
	int Testcase;
	cin >> Testcase;

	for (int i = 0; i < Testcase; i++)
	{
		int nodeNum;
		cin >> nodeNum;

		vector<int> preorder, inorder;

		for (int i = 0; i < nodeNum; i++)
		{
			int tmp;
			cin >> tmp;
			preorder.push_back(tmp);
		}

		for (int j = 0; j < nodeNum; j++)
		{
			int tmp;
			cin >> tmp;
			inorder.push_back(tmp);
		}

		printPostOrder(preorder, inorder);
		cout << endl;
	}
}

/*
1
7
27 16 9 12 54 36 72
9 12 16 27 36 54 72
*/
