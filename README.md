## TP1: Técnicas Algoritmicas

Arienti, Zaid


<br>

### Estructura del repo

El repositorio cuenta con los siguientes archivos y carpetas:

- 'ej-1' - Los archivos correspondientes a la implementación del ejercicio 1.

- 'ej-2' - Los archivos correspondientes a la implementación del ejercicio 2.

- 'ej-3' - Los archivos correspondientes a la implementación del ejercicio 3, el informe y los archivos fuente de la experimentación.


<br>

### Cómo crear los archivos ejecutables

Para este procedimiento se asume que trabajaremos en bash. Desde la raiz del repo procederemos de la siguiente forma.

1. Para crear el ejecutable de cada ejercicio (reemplazar `i` por el numero del ejercicio. Por ejemplo: ej-1).

```bash
$ cd ej-i

$ mkdir build

$ cd build

$ cmake ..

$ make
```

2. Para ejecutarlo (desde la carpeta ./ej-`i`/build/)

```
$ ./ej-i
```
