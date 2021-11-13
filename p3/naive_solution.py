n, m = input().split(' ')
n = int(n); m = int(m)

occ_bits = [0 for i in range(n)]

# Process all m queries
for i in range(m):

    # Parse the query
    query_type, index = input().split(' ')
    query_type = int(query_type); index = int(index)

    if query_type == 1:
        print(occ_bits[index])

    elif query_type == 2:
        occ_bits[index] = 1 - occ_bits[index]
    
    else:
        sum = 0
        for j in range(index + 1): 
            sum += occ_bits[j]; sum = sum % 2
        
        print(sum)
