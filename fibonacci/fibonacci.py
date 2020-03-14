#! /usr/bin/python
"""
high level support for doing this and that.
"""
import sys
import time

def es_primo(val_n):
    """
    high level support for doing this and that.
    """
    if val_n <= 1:
        return False
    if val_n <= 3:
        return True
    if val_n % 2 == 0 or val_n % 3 == 0:
        return False
    i = 5
    while i * i <= val_n:
        if val_n % i == 0 or val_n % (i + 2) == 0:
            return False
        i = i + 6
    return True

def fibonacci(val_n):
    """
    high level support for doing this and that.
    """
    start = time.time()
    fibo_1 = 0
    fibo_2 = 1
    fibo = 0
    iter_n = 0
    while iter_n <= val_n:
        if iter_n == 0:
            fibo = 0
        elif iter_n == 1:
            fibo = 1
        else:
            fibo = fibo_1 + fibo_2
            fibo_1 = fibo_2
            fibo_2 = fibo
        print "%d %ld %d" % (iter_n, fibo, es_primo(fibo))
        iter_n = iter_n +1
    end = time.time()
    print 1000000 * (end - start)

if len(sys.argv) >= 2:
    fibonacci(int(sys.argv[1]))
