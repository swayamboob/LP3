#include <bits/stdc++.h>
using namespace std;
class Node
{
public:
	char data;
	int freq;
	Node *left, *right;
	Node(char data, int freq)
	{
		left = right = nullptr;
		this->data = data;
		this->freq = freq;
	}
};
void printCodes(Node *root, string str)
{
	if (root == nullptr)
	{
		return;
	}
	if (root->data != '$')
	{
		cout << root->data << ": " << str << endl;
	}
	printCodes(root->left, str + "0");
	printCodes(root->right, str + "1");
}

class compare
{
public:
	bool operator()(Node *a, Node *b)
	{
		return (a->freq > b->freq);
	}
};
void HuffmanCode(char data[], int freq[], int size)
{
	Node *left, *right, *temp;
	priority_queue<Node *, vector<Node *>, compare> minHeap;
	for (int i = 0; i < size; i++)
	{
		minHeap.push(new Node(data[i], freq[i]));
	}
	while (minHeap.size() != 1)
	{
		left = minHeap.top();
		minHeap.pop();
		right = minHeap.top();
		minHeap.pop();
		temp = new Node('$', left->freq + right->freq);
		temp->left = left;
		temp->right = right;
		minHeap.push(temp);
	}
	printCodes(minHeap.top(), "");
}
int main()
{
	char data[] = {'A', 'B', 'C', 'D'};
	int freq[] = {23, 12, 34, 10};
	HuffmanCode(data, freq, 4);
	return 0;
}

/*
Huffman Coding :
Time complexity: O(nlogn) where n is the number of unique characters.
If there are n nodes, extractMin() is called 2*(n – 1) times. extractMin() takes O(logn) time as it calls minHeapify(). So, overall complexity is O(nlogn).
*/