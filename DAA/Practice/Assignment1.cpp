#include <bits/stdc++.h>
#include <iostream>
typedef long long ll;
using namespace std;
// ASCII of 'a'-97,'z'-123,'A'-65,'Z'-90,'0'-48,'9'-57
bool sortby(const pair<ll, ll> &a, const pair<ll, ll> &b)
{
    return a.second < b.second;
}
int Recursion(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return Recursion(n - 1) + Recursion(n - 2);
}
void Iterative(int n)
{
    int first = 0, second = 1;
    int temp;
    for (int i = 1; i <= n; i++)
    {
        cout << first << " ";
        temp = first + second;
        first = second;
        second = temp;
    }
}
int main()
{
    int n;
    cout << "Enter the No. serires - ";
    cin >> n;
    int i = 0;
    while (i < n)
    {
        cout << Recursion(i) << " ";
        i++;
    }
    cout<<endl;
    Iterative(n);
    return 0;
}