#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;

    cin >> n >> m;

    // Set up our data structure, which will consist of an array storing the occupation bits
    // and a Fenwick tree (see the solution for more details on what the Fenwick tree does).
    // Note that the first element of each array will be unused
    std::vector<int> occBits(n + 1);
    std::vector<int> fenwick(n + 1);

    // Process all m queries
    for (int i = 0; i < m; i++) {
        int type, index;

        // Parse the query. We're using scanf since it provides better performance than cin
        scanf("%d %d", &type, &index); 

        index++; // Since we don't use the first element of the fenwick tree
        switch(type) {
                case 1:
                    printf("%d\n", occBits[index]);
                    break;

                case 2:
                    occBits[index] = 1 - occBits[index];
                    while (index <= n) {
                        fenwick[index] = 1 - fenwick[index];
                        index += index & (-index); // adds the value of the last set bit
                    }
                    break;

                case 3:
                    int sum = 0;
                    while (index > 0) {
                        sum += fenwick[index];
                        sum = sum % 2;
                        index -= index & (-index); // unsets the last set bit
                    }
                
                    printf("%d\n", sum);
            }
    }

    return 0;
}