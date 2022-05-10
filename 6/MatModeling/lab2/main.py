import math
import matplotlib.pyplot as plt

# trend
def y(x):
    return 0.9337 * math.log(x, math.e) + 6.0797

def A(x, y):
    n = len(x)
    xy = []
    x2 = []

    for i in range(n):
        xy.append(x[i] * y[i])

    for i in x:
        x2.append(i ** 2)

    return (n * sum(xy) - sum(x) * sum(y)) / (n * sum(x2) - sum(x) ** 2)

def B(a, x, y):
    return (sum(y) - a * sum(x)) / len(x)

# approximation errors
def sigma(Y, F):
    delta = []

    for i in range(len(Y)):
        delta.append((Y[i] - F[i]) ** 2)

    return sum(delta)

X = [1,    2,    3,    4,    5,   6,    7   ]
Y = [8.16, 8.25, 8.41, 8.76, 9.2, 9.78, 10.1]
# y = ax + b
a = A(X, Y)
b = B(a, X, Y)
# analitic
F = []    
# least squares method                     
F1 = [] 

for i in range(len(X)):
    F.append(y(X[i]))
    F1.append(a * X[i] + b)

print('y = ' + str(a) + 'x + ' + str(b))

# analitic
s1 = sigma(Y, F)
# least squares method   
s2 = sigma(Y, F1)

plt.figure(1)
plt.plot(X, Y, 'o')
plt.plot(X, F, 'k')
plt.plot(X, F1, 'r')
plt.show()

if (s1 < s2):
    print('Логарифмическое уравнение имеет лучшее приближение')
else:
    print('МНК имеет лучшее приближение')