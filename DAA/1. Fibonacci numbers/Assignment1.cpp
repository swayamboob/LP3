/*
Write a program non-recursive and recursive program to calculate Fibonacci numbers and
analyze their time and space complexity.
*/
#include <bits/stdc++.h>
#include <iostream>
typedef long long ll;
using namespace std;
bool sortby(const pair<ll, ll> &a, const pair<ll, ll> &b)
{
    return a.second < b.second;
}
int fibo_recursive(int x)
{
    if ((x == 1) || (x == 0))
    {
        return (x);
    }
    else
    {
        return (fibo_recursive(x - 1) + fibo_recursive(x - 2));
    }
}
void fibo_iterative(int x)
{
    int first = 0, second = 1, temp = 0;
    for (int i = 1; i <= x; ++i)
    {
        cout << first << " ";
        temp = first + second;
        first = second;
        second = temp;
    }
}
int main()
{
    int x, i = 0;
    cout << "Enter the number of terms of series : ";
    cin >> x;
    cout << "\nFibonnaci Series Using Recursion : ";
    while (i < x)
    {
        cout << " " << fibo_recursive(i);
        i++;
    }
    cout << "\nFibonnaci Series Using Non-Recursion : ";

    fibo_iterative(x);

    return 0;
}