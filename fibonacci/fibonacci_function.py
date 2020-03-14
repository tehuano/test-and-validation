# python -mtimeit -s'import fibonacci_function' 'fibonacci_function.fibonacci(10)'


import sys
import time

def fibonacci(n):
    start = time.time()
    f1 = 0
    f2 = 1
    f = 0
    if (n == 0):
        f = f1
    elif (n == 1):
        f = f2
    else:
        for x in range (2,n+1):
            f = f1 + f2
            f1 = f2
            f2 = f
        #print(f)
    print(f)
    end = time.time()
    print(1000000 * (end - start))

