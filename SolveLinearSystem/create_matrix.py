import numpy as np

n = int(input())

A = np.random.uniform(-5, 5, (n, n))

x = np.random.uniform(-5, 5, n)

b = np.matmul(A, x)

print(n)
for i in range(n):
	for j in range(n):
		print(round(A[i][j], 2), end=" ")
	print(round(b[i], 2))
