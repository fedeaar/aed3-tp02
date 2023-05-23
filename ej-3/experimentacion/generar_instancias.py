import numpy as np

np.random.seed(11037)

for power in range(1,11):
    n = 1000 * power
    f = open("inputs/input_" + str(n), "w")
    input = range(0, n)
    for num in input:
        f.write(str(num) + " " + str(num + 1) + " ")
    f.close()
