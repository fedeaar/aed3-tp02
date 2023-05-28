import numpy as np
import os


#
# VARIABLES
#

SEED = 11037
MIN = 1000
MAX = 10000
STEP = 1000


#
# MAIN
#

if __name__ == "__main__":

    np.random.seed(SEED)
    rng = np.random.default_rng()

    if not os.path.exists("./in/"):
        os.mkdir("./in/")

    if not os.path.exists("./out/"):
        os.mkdir("./in/")

    for n in range(MIN, MAX+1, STEP):
        x_coords = rng.choice(n, size=n, replace=False)
        y_coords = rng.choice(n, size=n, replace=False)
        f = open("./in/input_" + str(n), "w")
        for i in range(0, n):
            f.write(str(x_coords[i]) + " " + str(y_coords[i]) + " ")
        f.close()
