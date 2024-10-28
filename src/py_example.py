import random


def add(x, y):
    return x + y


def multiplyRandomMatrices(rows, cols, tile_size):
    A = [[random.randint(0, 100) for _ in range(cols)] for _ in range(rows)]
    B = [[random.randint(0, 100) for _ in range(cols)] for _ in range(rows)]

    n, k, m = rows, cols, cols
    C = [[0] * m for _ in range(n)]

    for i in range(0, n, tile_size):
        for j in range(0, m, tile_size):
            for x in range(0, k, tile_size):
                for ii in range(i, min(i + tile_size, n)):
                    for jj in range(j, min(j + tile_size, m)):
                        for xx in range(x, min(x + tile_size, k)):
                            C[ii][jj] += A[ii][xx] * B[xx][jj]
    return C
