/* Write a program to solve a fractional Knapsack problem using a greedy method. */
// C++ program to solve fractional
// Knapsack Problem
#include <bits/stdc++.h>
using namespace std;
class Item
{
public:
    int value, weight;
    Item(int value, int weight)
    {
        this->value = value;
        this->weight = weight;
    }
};
bool cmp(Item a, Item b)
{
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}
// Main greedy function to solve problem
double fractionalKnapsack(Item arr[], int N, int size)
{
    sort(arr, arr + size, cmp);
    int curWeight = 0;
    double finalvalue = 0.0;
    for (int i = 0; i < size; i++)
    {
        if (curWeight + arr[i].weight <= N)
        {
            curWeight += arr[i].weight;
            finalvalue += arr[i].value;
        }
        else
        {
            int remain = N - curWeight;
            finalvalue += arr[i].value * ((double)remain / arr[i].weight);
            break;
        }
    }
    return finalvalue;
}
int main()
{
    // Weight of knapsack
    int N;
    cout << "Enter the Weight of Knapsack : ";
    cin >> N;
    Item arr[] = {{100, 10}, // Profit and Weight
                  {280, 40},
                  {120, 20},
                  {120, 24}};

    int size = sizeof(arr) / sizeof(arr[0]);
    cout << "Maximum profit earned = "
         << fractionalKnapsack(arr, N, size);
    return 0;
}
