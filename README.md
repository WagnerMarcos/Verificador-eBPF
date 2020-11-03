# Ejercicio 2

    Alumno: Wagner Marcos
    Padrón: 98607
    github: https://github.com/WagnerMarcos/Verificador-eBPF


## Introducción:

En este trabajo se implementará una versión simplificada del verificador eBPF que sólo verificará la existencia o no de bucles de código y/o instrucciones sin ejecutar.

## Estructura utilizada:

Para este programa decidí realizar un functor para el procesamiento de eBPF en la clase FindDAG. Esta clase tiene dentro una referencia a una misma instancia de FileHandler y ResultProtected. Estos objetos comunes albergan los archivos recibidos por argumentos y los resultados de aplicar el verificador respectivamente.

Esta clase FindDAG contiene dentro una instancia de grafo. Al procesar el archivo ingresa instancias de nodos hasta que se termine de procesar el archivo. El procesamiento del código se hace basando en strings, ya que encuentra y guarda los saltos condicionales y no condicionales, los tags de instrucción y los tags a los que cada instrucción saltaría.

El manejador de archivos FileHandler fue implementado como una cola que devuelve archivos mientras no se encuentre vacía. La clase que guarda los resultados ResultProtected fue implementado como un vector, ya que de esta manera se puede incrementar el tamaño y luego ordenarlo.

## Uso de hilos

Se detectaron dos zonas críticas:
- La primer zona crítica se encontró en el pedido de archivos. Se consideró al proceso de consultar el estado de la cola y recibir un archivo como una acción que debía ser tratada como atómica.
- La segunda zona crítica es al cargar los resultados al vector. Al tener un proceso de redimensionamiento interno, se protegió este proceso para que no tuviera problemas de índices.

Se utilizó al mutex implementado dentro de un Lock para volverlo RAII, y se utilizaron dos mutex en total, uno para cada zona crítica.


### Diagrama de secuencias para un hilo

![Diagrama de secuencia](https://github.com/WagnerMarcos/Verificador-eBPF/blob/master/tp2.png?raw=true)
