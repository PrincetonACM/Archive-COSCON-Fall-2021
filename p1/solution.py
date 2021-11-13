def maximize_cost(n, costs):
    if (n == 1):
        return costs[0]

    a = costs[0]; b = max(costs[0], costs[1])

    for i in range(2, n):
        c = max(a + costs[i], b)
        a = b
        b = c

    return b

if __name__ == '__main__':
    n = int(input().strip())
    costs = list(map(int, input().rstrip().split()))
    print(maximize_cost(n, costs))