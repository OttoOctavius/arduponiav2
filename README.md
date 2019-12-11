Arduponia v2: Ahora con espectometro!

Sensado
Conectar el arduino y usar cualquier sketch de la carpeta mediciones
Para guardar los datos a un fichero, ejecutar:

ipython3
>import salvarEnExcel
>salvarEnExcel.ciclograbado("nombreArchivo","puertoSerie")

Se terminara de grabar cuando se desconecte el arduino para evitar corromper archivos.
Con los resultados, ejecutar dependiendo el programa:

>dicc = salvarEnExcel.objetearTIPOMEDICION("nombreArchivo")
>salvarEnExcel.crearArchivo()
>salvarEnExcel.salvarEnExcel(dicc,"nombreArchivo")

