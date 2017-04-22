<span id="page1" class="anchor"></span>**ALGORITMOS Y ESTRUCTURAS DE DATOS**

**Guía 6. Introducción a Networking**

**Para entregar:**

Queremos implementar una aplicación que muestre una animación en una máquina y luego la continúe en otra, de forma que la animación vaya
saltando de máquina en máquina hasta que se haya mostrado en todas ellas.

 Detalles de implementación:

1.  La aplicación se ejecuta en todas las máquinas involucradas.

2.  En la carpeta en donde se encuentra la aplicación contamos también con un segundo archivo llamado direcciones.txt que contiene la dirección IP de cada máquina involucrada. Una dirección IP por línea (las líneas terminan con ‘\\n’). El archivo debe ser idéntico para todas las máquinas

 Ej: del contenido del archivo direcciones.txt con tres direcciones IP:

> 192.168.0.15
>
> 192.168.0.16
>
> 192.168.0.125

3.  Como máximo admitiremos 255 máquinas.

4.  Como mínimo admitiremos 2 máquinas.

5.  Enumeraremos las direcciones IP del archivo direcciones.txt de forma que la primera dirección corresponde al 1, la segunda al 2 y
    así sucesivamente.

6.  Dispondremos de 6 posibles animaciones y las llamaremos con letras mayúsculas según la siguiente correspondencia:

    > 1.  Cat Running
    >
    > 2.  Explosion 1
    >
    > 3.  Explosion 2
    >
    > 4.  Homer Dance
    >
    > 5.  Super Mario
    >
    > 6.  Sonic

7.  Al iniciar la aplicación esta le permitirá al usuario elegir entre 6 animaciones a mostrar entre todas las máquinas y la secuencia en que desea mostrarlas en las distintas máquinas

8.  El usuario por lo tanto elegirá una animación y una secuencia de repetición, por ejemplo, el usuario de la máquina 3 elije la animación C y la secuencia 1, 3, 2. Esto quiere decir que la secuencia se mostrará primero en la máquina 1 luego en la máquina 3 y finalmente en la máquina 2.

9. Cuando le usuario le indica a su máquina que quiere iniciar una secuencia, ésta la revisará para ver si es la primera en mostrar la    animación. Si lo es, realizará la animación y luego se conectará con la próxima máquina en la secuencia para indicarle que debe realizar la secuencia.
10. Una máquina le comunica a la otra que debe realizar la secuencia enviándole el paquete YOU\_GO conformado de la siguiente manera:   11. La máquina se conecta con la que debe recibir el paquete al puerto 12345, lo envía y luego se desconecta.                            12. Una máquina al recibir el paquete YOU\_GO mirará el valor Count el cual se incrementa cada vez que se comparte el paquete e inicia en “0”. (La primera máquina al enviar el paquete lo envía con un 0 si no realizó la secuencia o un 1 si lo hizo). Con él podrá saber a quién es el próximo al que se le debe enviar le paquete (Count+1) o si ella es la última en la secuencia.
13. Una vez recibido o enviado un paquete YOU\_GO, la máquina no le permitirá a su usuario inicinar una nueva secuencia de animación a menos que dicha máquina sea la última en la secuencia; sino que se quedará escuchando el puerto 12345 esperando un nuevo paquete YOU\_GO.

 14. Cuando se ejecuta el programa, el mismo iniciará por default en modo “escuchar” salvo que se le ejecute con el parámetro “iniciar” en cuyo caso esperará la secuencia del usuario. Se deberá cuidad de iniciar todas las máquinas en modo escucha salvo una que será el que inicie la primera secuencia.

 15. Mientras se muestra la animación, se puede evitar prestarle atención a networking (en otras palabras, la animación puede ser
 bloqueante). Mientras se recibe o envía un paquete también se puede trabajar en forma bloqueanteo. De igual forma, mientras se espera input de usuario.

16. Los detalles de las animaciones son los siguientes:

| Set   | Nombre Amigable   | Período (frame a frrame)   | Velocidad          |
|-------|-------------------|----------------------------|--------------------|
| A     | Cat Running       | 100ms                      | 20px/frame         |
|       |                   |                            |                    |
| B     | Explosion 1       | 120ms                      | N/A                |
|       |                   |                            |                    |
| C     | Explosion 2       | 100ms                      | N/A                |
|       |                   |                            |                    |
| D     | Homer Dance       | 100ms                      | 100px/frame        |
|       |                   |                            |                    |
| E     | Super Mario       | 40ms                       | 20px/frame         |
|       |                   |                            |                    |
| F     | Sonic             | 60ms                       | 70px c/ 4 frames   |
|       |                   |                            |                    |

<span id="page3" class="anchor"></span>

17.  Cada equipo podrá elegir el fondo a mostrar y el tamaño de la pantalla pero deberá respetar la velocidad en los Sets A, D, E y F
    al igual que el refresh rate de todos los Sets. Una vez que se recorrió toda la pantalla en los sets A, D, E y F o se terminó la
    animación de lo sets B y C se pasa a la próxima máquina en la secuencia salvo que sea la última.

18.  Recordar que cada vez que se comparte el paquete YOU\_GO se deberá incrementar el campo Count.

