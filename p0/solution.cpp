#include <iostream>
using namespace std;

int main() {
    int n, m, current;
  
    cin >> n >> m;

    int diff = 0; // The total differential in productivity we can attain
    for (int i = 0; i < n; i++) {
        cin >> current;
        diff += (m > current) ? m - current : 0;
    }
  
    cout << diff << endl;

    return 0;
}