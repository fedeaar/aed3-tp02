import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

#
# GLOBAL
#

plt.rcParams["font.family"] = "serif"
plt.rcParams["font.serif"] = ["Times New Roman"]
config = {"fontsize":20, "labelpad":20}

FN_DENSO = "./out/runtime_denso.csv"
FN_DSU = "./out/runtime_dsu.csv"
FN_DSU_INGENUO = "./out/runtime_dsu_ingenuo.csv"


#
# DSU original
#

def resultados_dsu():

    df = pd.read_csv(FN_DSU)

    f, ax = plt.subplots(figsize=(7, 7))
    sns.regplot(x="n", y="time", data=df, ax=ax, order=2) #, ci=None)
    
    ax.set_xscale("linear")
    ax.set_yscale("linear")
    ax.set_xlabel("tamaño de la entrada", **config)
    ax.set_ylabel("tiempo (segundos)", **config)
    ax.tick_params(labelsize=16, size=10)
    ax.grid()
    
    f.savefig("./out/DSU_optimizado.png", bbox_inches='tight')

    # r = np.corrcoef(df['time'], df['n'])[0][1]
    # print("El coeficiente de correlación de Pearson para la muestra optimizada es: r="+str(r))


# 
# comparacion con version densa
#

def comparacion_densa():

    dsu = pd.read_csv(FN_DSU)
    denso = pd.read_csv(FN_DENSO)

    f, ax = plt.subplots(figsize=(7, 7))
    ax.scatter(dsu["n"], dsu["time"], color='orange')
    ax.plot(dsu["n"], dsu["time"], color='orange', label='supercuadrático')
    ax.scatter(denso["n"], denso["time"])
    ax.plot(denso["n"], denso["time"], label='cuadrático')

    ax.set_xscale("linear")
    ax.set_yscale("linear")
    ax.set_xlabel("tamaño de la entrada", **config)
    ax.set_ylabel("tiempo (segundos)", **config)
    ax.tick_params(labelsize=16, size=10)
    ax.grid()
    ax.legend(fontsize="xx-large")

    f.savefig("./out/comparacion_asintótica.png", bbox_inches='tight')

    # diferencia
    comparacion = dsu
    comparacion["time"] = np.abs(dsu["time"] - denso["time"])

    data = np.polyfit(comparacion["n"], comparacion["time"], 2, full=True)
    fit = np.poly1d(data[0]) 
    print(data)

    f, ax = plt.subplots(figsize=(7, 7))
    ax.scatter(comparacion["n"], comparacion["time"])
    plt.plot(comparacion["n"], fit(comparacion["n"]), color="green", label="diferencia")

    ax.set_xscale("linear")
    ax.set_yscale("linear")
    ax.set_xlabel("tamaño de la entrada", **config)
    ax.set_ylabel("tiempo (segundos)", **config)
    ax.tick_params(labelsize=16, size=10)
    ax.grid()
    ax.legend(fontsize="xx-large")

    f.savefig("./out/comparacion_asintótica_diff.png", bbox_inches='tight')


# 
# comparacion DSU con y sin heuristicas
#

def comparacion_dsu():

    dsu = pd.read_csv(FN_DSU)
    ingenuo = pd.read_csv(FN_DSU_INGENUO)

    f, ax = plt.subplots(figsize=(7, 7))
    ax.scatter(dsu["n"], dsu["time"], color='orange')
    ax.plot(dsu["n"], dsu["time"], color='orange', label='optimizado')
    ax.scatter(ingenuo["n"], ingenuo["time"])
    ax.plot(ingenuo["n"], ingenuo["time"], label='suboptimo')

    ax.set_xscale("linear")
    ax.set_yscale("linear")
    ax.set_xlabel("tamaño de la entrada", **config)
    ax.set_ylabel("tiempo (segundos)", **config)
    ax.tick_params(labelsize=16, size=10)
    ax.grid()
    ax.legend(fontsize="xx-large")

    f.savefig("./out/comparacion_DSU.png", bbox_inches='tight')


#
# MAIN
#

if __name__ == "__main__":

    comparacion_densa()
    comparacion_dsu()
