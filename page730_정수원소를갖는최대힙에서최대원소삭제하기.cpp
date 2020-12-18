#include<bits/stdc++.h>

using namespace std;
//정수를 담는 최대 힙 heap에서 heap[0]를 제거한다.
void pop_heap(vector<int>& heap)
{
	heap[0] = heap.back();
	heap.pop_back();
	int here = 0;
	while (true)
	{
		int left = here * 2 + 1;
		int right = here * 2 + 2;
		//리프에 도달한 경우
		if (left >= heap.size())
			break;
		//heap[here]가 내려갈 위치를 찾는다.
		int next = here;
		if (heap[next] < heap[left])
			next = left;
		if (right < heap.size() && heap[next] < heap[right])
			next = right;
		if (next == here)
			break;
		
		int tmp;
		tmp = heap[here];
		heap[here] = heap[next];
		heap[next] = tmp;

		here = next;
	}
}
