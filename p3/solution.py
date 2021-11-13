n, m = input().split(' ')
n = int(n); m = int(m)

# Set up our data structure, which will consist of an array storing the occupation bits
# and a Fenwick tree (see the solution for more details on what the Fenwick tree does)
occ_bits = [0 for i in range(n + 1)]
fenwick = [0 for i in range(n + 1)]

# Process all m queries
for i in range(m):

    # Parse the query
    query_type, index = input().split(' ')
    query_type = int(query_type); index = int(index)

    index += 1 # Since we don't use the first element of the fenwick tree

    if query_type == 1:
        print(occ_bits[index])

    elif query_type == 2:
        occ_bits[index] = 1 - occ_bits[index]
        
        while index <= n: 
            fenwick[index] = 1 - fenwick[index]
            index += index & (-index) # adds the value of the last set bit

    else:
        sum = 0
        while index > 0: 
            sum += fenwick[index]
            sum = sum % 2
            index -= index & (-index) # unsets the last set bit
        
        print(sum)
