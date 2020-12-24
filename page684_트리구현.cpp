#include<bits/stdc++.h>

using namespace std;

struct TreeNode
{
	string label; //저장할 자료(물론 꼭 문자열일 필요는 없다.)
	TreeNode* parent;//부모 노드를 가리키는 포인터
	vector<TreeNode*> children;//자손 노드들을 가리키는 포인터의 배열
};

//주어진 트리의 각 노드에 저장된 값을 모두 출력한다.
void printLabels(TreeNode* root)
{
	//루트에 저장된 값을 출력한다.
	cout << root->label << endl;
	for (int i = 0; i < root->children.size(); ++i)
		printLabels(root->children[i]);
}

int height(TreeNode* root)
{
	int h = 0;
	for (int i = 0; i < root->children.size(); i++)
		h = max(h, 1 + height(root->children[i]));
	return h;
}

int main(int argc, char*argv[])
{
	TreeNode tmp1;
	TreeNode tmp2;
	tmp1.label = "나는 첫 번째야";
	
}
