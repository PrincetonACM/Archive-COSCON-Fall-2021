#include <iostream>
#include <vector>
using namespace std;

int maximize_cost(int n, vector<int> costs)
{
    if (n == 1)
        return costs[0];

    int a = costs[0], b = max(costs[0], costs[1]);

    for (int i = 2; i < n; i++)
    {
        int c = max(a + costs[i], b);
        a = b;
        b = c;
    }

    return b;
}

int main()
{
    int n;
    cin >> n;
    vector<int> costs(n, 0);
    for (int i = 0; i < n; i++)
        scanf("%d", &costs[i]); // scanf is faster than cin
    cout << maximize_cost(n, costs) << endl;
}