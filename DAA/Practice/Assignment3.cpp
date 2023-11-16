#include <bits/stdc++.h>
#include <iostream>
typedef long long ll;
using namespace std;
// ASCII of 'a'-97,'z'-123,'A'-65,'Z'-90,'0'-48,'9'-57
bool sortby(const pair<ll, ll> &a, const pair<ll, ll> &b)
{
    return a.second < b.second;
}
class Item
{
public:
    int wt;
    int profit;
    Item(int wt, int profit)
    {
        this->wt = wt;
        this->profit = profit;
    }
};
bool Compare(Item a, Item b)
{
    double r1 = (double)(a.profit) / (double)(a.wt);
    double r2 = (double)(b.profit) / (double)(b.wt);
    return r1 > r2;
}
int Fractional(Item arr[], int N, int size)
{
    sort(arr, arr + size, Compare);
    int currwt = 0;
    double FinalValue = 0.0;
    for (int i = 0; i < size; i++)
    {
        if (currwt + arr[i].wt <= N)
        {
            currwt += arr[i].wt;
            FinalValue += arr[i].profit;
        }
        else
            int remain = N - currwt;
            double temp=double(arr[i].profit)*((double)(remain)/(double)(arr[i].wt)));
            break;
    }
    return FinalValue;
}
int main()
{
    int N;
    cout << "Enter the Knapsack Wt - ";
    cin >> N;
    Item arr[] = {{}, {}, {}, {}};
    int size = sizeof(arr) / sizeof(arr[0]);
    cout << Fractional(arr, N, size);
    return 0;
}