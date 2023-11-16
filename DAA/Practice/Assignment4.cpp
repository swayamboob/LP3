#include <bits/stdc++.h>
#include <iostream>
typedef long long ll;
using namespace std;
// ASCII of 'a'-97,'z'-123,'A'-65,'Z'-90,'0'-48,'9'-57
bool sortby(const pair<ll, ll> &a, const pair<ll, ll> &b)
{
    return a.second < b.second;
}
int main()
{
    int item = 4;
    int capacity = 10;

    int price[item + 1] = {0, 3, 7, 2, 9};
    int wt[capacity + 1] = {0, 2, 2, 4, 5};

    int dp[item + 1][capacity + 1];
    for (int i = 0; i <= item; i++)
    {
        for (int j = 0; j <= capacity; j++)
        {
            if (i == 0 || j == 0)
            {
                dp[i][j] = 0;
            }
            else if (wt[i] <= j)
            {
                dp[i][j] = max(dp[i - 1][j], price[i] + dp[i - 1][j - wt[i]]);
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    cout << "Maximum Profit Earned: " << dp[item][capacity] << "\n";
    return 0;
}