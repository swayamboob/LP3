#include <bits/stdc++.h>
#include <iostream>
typedef long long ll;
using namespace std;
// ASCII of 'a'-97,'z'-123,'A'-65,'Z'-90,'0'-48,'9'-57
bool sortby(const pair<ll, ll> &a, const pair<ll, ll> &b)
{
    return a.second < b.second;
}
class Node
{
public:
    char data;
    int freq;
    Node *left, *right;
    Node(char data, int freq)
    {
        this->data = data;
        this->freq = freq;
        left = right = NULL;
    }
};
class Compare
{
public:
    bool operator()(Node *a, Node *b)
    {
        return a->freq > b->freq;
    }
};
void Display(Node *root, string str)
{
    if (root == NULL)
        return;
    if (root->data != '$')
    {
        cout << root->data << " : " << str << endl;
    }
    Display(root->left, str + "0");
    Display(root->right, str + "1");
}
void Huffman(char data[], int freq[], int size)
{
    Node *left, *right;
    priority_queue<Node *, vector<Node *>, Compare> pq;
    for (int i = 0; i < size; i++)
    {
        pq.push(new Node(data[i], freq[i]));
    }
    while (pq.size() != 1)
    {
        left = pq.top();
        pq.pop();
        right = pq.top();
        pq.pop();
        Node *temp = new Node('$', left->freq + right->freq);
        temp->left = left;
        temp->right = right;
        pq.push(temp);
    }
    Display(pq.top(), "");
}
int main()
{
    char data[] = {'A', 'B', 'C', 'D'};
    int freq[] = {23, 12, 34, 10};
    Huffman(data, freq, 4);
    return 0;
}