import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

plt.rcParams["font.family"] = "serif"
plt.rcParams["font.serif"] = ["Times New Roman"]
config = {"fontsize":20, "labelpad":20}

df = pd.read_csv("./out/runtime_DSU_optimizado.csv")

f, ax = plt.subplots(figsize=(7, 7))
sns.regplot(x="n", y="time", data=df, ax=ax, order=2) #, ci=None)
ax.set_xscale("linear")
ax.set_yscale("linear")
ax.set_xlabel("tamaño de la entrada", **config)
ax.set_ylabel("tiempo (segundos)", **config)
ax.tick_params(labelsize=16, size=10)
ax.grid()
f.savefig("./out/DSU_optimizado.png", bbox_inches='tight')

r = np.corrcoef(df['time'], df['n'])[0][1]
print("El coeficiente de correlación de Pearson para la muestra optimizada es: r="+str(r))


df = pd.read_csv("./out/runtime_DSU_optimizado.csv")
df2 = pd.read_csv("./out/runtime_cuadratico.csv")

f, ax = plt.subplots(figsize=(7, 7))
ax.scatter(df["n"], df["time"], color='orange')
ax.plot(df["n"], df["time"], color='orange', label='supercuadrático')
ax.scatter(df2["n"], df2["time"])
ax.plot(df2["n"], df2["time"], label='cuadrático')
ax.set_xscale("linear")
ax.set_yscale("linear")
ax.set_xlabel("tamaño de la entrada", **config)
ax.set_ylabel("tiempo (segundos)", **config)
ax.tick_params(labelsize=16, size=10)
ax.grid()
ax.legend(fontsize="xx-large")
f.savefig("./out/comparacion_asintótica.png", bbox_inches='tight')

df3 = df
df3["time"] = np.abs(df["time"] - df2["time"])

data = np.polyfit(df3["n"], df3["time"], 2, full=True)
fit = np.poly1d(data[0]) 
print(data)


f, ax = plt.subplots(figsize=(7, 7))
ax.scatter(df3["n"], df3["time"])
plt.plot(df3["n"], fit(df3["n"]), color="green", label="diferencia")
#sns.regplot(x="n", y="time", data=df3, ax=ax, order=2) #, ci=None)
ax.set_xscale("linear")
ax.set_yscale("linear")
ax.set_xlabel("tamaño de la entrada", **config)
ax.set_ylabel("tiempo (segundos)", **config)
ax.tick_params(labelsize=16, size=10)
ax.grid()
ax.legend(fontsize="xx-large")
f.savefig("./out/comparacion_asintótica_diff.png", bbox_inches='tight')





df = pd.read_csv("./out/runtime_DSU_optimizado.csv")
df2 = pd.read_csv("./out/runtime_DSU_suboptimo.csv")

f, ax = plt.subplots(figsize=(7, 7))
ax.scatter(df["n"], df["time"], color='orange')
ax.plot(df["n"], df["time"], color='orange', label='optimizado')
ax.scatter(df2["n"], df2["time"])
ax.plot(df2["n"], df2["time"], label='suboptimo')
ax.set_xscale("linear")
ax.set_yscale("linear")
ax.set_xlabel("tamaño de la entrada", **config)
ax.set_ylabel("tiempo (segundos)", **config)
ax.tick_params(labelsize=16, size=10)
ax.grid()
ax.legend(fontsize="xx-large")
f.savefig("./out/comparacion_DSU.png", bbox_inches='tight')