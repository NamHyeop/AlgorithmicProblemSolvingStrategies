//루트는 기존에 있던 것
//Node는 새로 들어온 것

#include<iostream>

using namespace std;

int n;
int shifted[50000];
int A[50000];

typedef int KeyType;

//트리의 한 노드를 저장한다
struct Node{
	//노드에 저장된 원소
	KeyType key;
	//이 노드의 우선순위(priority)
	int priority;
	//이 노드를 루트로 하는 서브트리의 크기(size)
	int size;
	Node *left;
	Node *right;
	//생성자에서 난수 우선순위를 생성하고, size와 left/right를 초기화한다.
	Node(const KeyType &_key) : key(_key), priority(rand()), size(1), left(NULL), right(NULL)
	{
	}

	void setLeft(Node* newLeft)
	{
		left = newLeft;
		calcSize();
	}
	void setRight(Node* newRight)
	{
		right = newRight;
		calcSize();
	}

	void calcSize()
	{
		size = 1;
		if (left)
			size += left->size;
		if (right)
			size += right->size;
	}
};

//first가 오른쪽, second가 왼쪽
typedef pair<Node*, Node*> NodePair;

//root를 루트로 하는 트립을 key 미만의 값과 이상의 값을 갖는
//두 개의 트립으로 분리한다.

NodePair split(Node * root, KeyType key)
{
	if (root == NULL)
		return NodePair(NULL, NULL);
	//루트가 key 보다 작으면 (미만이면) 오른쪽 서브트리를 쪼갠다.
	if (root->key < key)
	{
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}

	//루트가 key 이상이면 왼쪽 서브트리를 쪼갠다.
	NodePair ls = split(root->left, key);
	root->setLeft(ls.second);
	return NodePair(ls.first, root);
}

//root를 루트로 하는 트립에 새 노드 node를 삽입한 뒤 결과 트립의
//루트를 반환한다.
Node * insert(Node * root, Node* node)
{
	if (root == NULL)
		return node;
	//노드의 우선순위가 더 클 경우 node가 루트를 대체해야 한다. 해당 서브트리를 반으로 잘라
	//각각 자손으로 한다.
	if (root->priority < node->priority)
	{
		NodePair splitted = split(root, node->key);
		node->setLeft(splitted.first);
		node->setRight(splitted.second);
		return node;
	}
	//새로들어온 키 값 보다 기존에 있던 root의 값이 더 클 경우 새로 들어온 노드를 왼쪽에 넣어준다.
	else if (node->key < root->key)
		root->setLeft(insert(root->left, node));
	//새로들어온 node의 키 값이 기존에 있던 root의 값 보다 더 클 경우 오른쪽에 넣어준다.
	else
		root->setRight(insert(root->right, node));

	return root;
}

Node* merge(Node* a, Node* b)
{
	if (a == NULL)
		return b;
	if (b == NULL)
		return a;
	if (a->priority < b->priority)
	{
		b->setLeft(merge(a, b->left));
		return b;
	}
	a->setRight(merge(a->right, b));
	return a;
}

Node * erase(Node * root, KeyType key)
{
	if (root == NULL)
		return root;
	//root를 지우고 양 서브트리를 합친 뒤 반환한다.
	if (root->key == key)
	{
		Node *ret = merge(root->left, root->right);
		delete root;
		return ret;
	}
	//왼쪽이 더크면
	if (key < root->key)
		root->setLeft(erase(root->left, key));
	else//오른쪽이 더크면
		root->setRight(erase(root->right, key));
	return root;
}

//root를 루트로 하는 트리 중에서 k번째 원소를 반환한다.
Node* kth(Node* root, int k)
{
	//왼쪽 서브트리의 크기를 우선 계산한다.
	int leftSize = 0;
	if (root->left != NULL)
		leftSize = root->left->size;
	//k번째 노드가 왼쪽 서브트리에 있을 때
	if (k <= leftSize)
		return kth(root->left, k);
	//k번째 노드가 루트 노드일때
	if (k == leftSize + 1)
		return root;
	//k번째 노드가 오른쪽 서브트리에 있을때
	return kth(root->right, k - leftSize - 1);
}

int countLessThan(Node * root, KeyType key)
{
	if (root == NULL)
		return 0;
	//왼쪽 서브트리가 더 큰 경우 왼쪽만 세주면 된다.
	if (root->key >= key)
		return countLessThan(root->left, key);
	//만약 오른쪽이 더 크다면 그 루트 기준으로 왼쪽 사이즈 크기랑 오른쪽 서브트리에서 키 값 보다 작은것들을 다 반환해주어야 한다.
	int ls = (root->left ? root->left->size : 0);
	return ls + 1 + countLessThan(root->right, key);
}

//n, shifted[]를 보고 A[]에 값을 저장한다.
void solve()
{
	// 1~N까지의 숫자를 모두 저장하는 트립을 만든다.
	Node * candidates = NULL;

	for (int i = 0; i < n; i++)
		candidates = insert(candidates, new Node(i + 1));
	//뒤에서부터 A[]를 채워나간다.
	for (int i = n - 1; i >= 0; --i)
	{
		//후보 중 이 수보다 큰수가 larger개 있다.
		int larger = shifted[i];
		Node *k = kth(candidates, i + 1 - larger);
		A[i] = k->key;
		candidates = erase(candidates, k->key);
	}
}

int main(int argc, char *argv[])
{
	int Testcase;
	cin >> Testcase;

	for (int i = 0; i < Testcase; i++)
	{
		cin >> n;

		for (int i = 0; i < n; i++)
			cin >> shifted[i];

		solve();

		for (int i = 0; i < n; i++)
			cout << A[i] << " ";

		cout << '\n';
	}

	return 0;
}
