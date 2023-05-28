## TP2: Recorridos y AGM

Arienti, Zaid


<br>

### Estructura del repo

El repositorio cuenta con los siguientes archivos y carpetas:

- 'ej-1' - Los archivos correspondientes a la implementación del ejercicio 1.

- 'ej-2' - Los archivos correspondientes a la implementación del ejercicio 2.

- 'ej-3' - Los archivos correspondientes a la implementación del ejercicio 3, el informe y los archivos fuente de la experimentación.


<br>

### Cómo crear los archivos ejecutables de los ejercicios

Para este procedimiento se asume que trabajaremos en bash. Desde la raiz del repo procederemos de la siguiente forma.

1. Para crear el ejecutable de cada ejercicio (reemplazar `i` por el numero del ejercicio. Por ejemplo: ej-1)

```bash
$ cd ej-i

$ mkdir build

$ cd build

$ cmake ..

$ make
```

2. Para ejecutarlo (desde la carpeta ./ej-`i`/build/, reemplazar `i` por el numero del ejercicio)

```bash
$ ./ej-i
```


<br>

### Cómo crear los archivos ejecutables de la experimentación

Para este procedimiento se asume que trabajaremos en bash. Desde la raiz del repo procederemos de la siguiente forma.

1. Para crear los ejecutables de la experimentación

```bash
$ cd ej-3/experimentacion/

$ mkdir build

$ cd build

$ cmake ..

$ make
```

2. Para ejecutar cada experimento (desde la carpeta ./ej-3/experimentacion/)

```bash
# generamos los casos de test y directorios

$ python generar_instancias.py

# ejecutamos

$ ./build/exp-denso

$ ./build/exp-dsu

$ ./build/exp-dsu-ingenuo

```
