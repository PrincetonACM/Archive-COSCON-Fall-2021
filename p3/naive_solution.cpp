#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;

    cin >> n >> m;
    std::vector<int> occBits(n);

    // Process all m queries
    for (int i = 0; i < m; i++) {
        int type, index;

        // Parse the query. We're using scanf since it provides better performance than cin
        scanf("%d %d", &type, &index); 
        switch(type) {
                case 1:
                    printf("%d\n", occBits[index]);
                    break;

                case 2:
                    occBits[index] = 1 - occBits[index];
                    break;

                case 3:
                    int sum = 0;
                    for (int j = 0; j <= index; j++) sum = (sum + occBits[j]) % 2;
                    printf("%d\n", sum);
            }
    }

    return 0;
}