n, m = map(int, input().rstrip().split())
productivities = list(map(int, input().rstrip().split()))

diff = 0
for p in productivities:
    if m > p: diff += m - p

print(diff)
