# UNIVERSIDAD CATOLICA BOLIVIANA "SAN PABLO"
## Facultad de Ingeniería de Sistemas

==========

## TITULO DEL PROYECTO: Sistema de Reservacion de salas de estudio
Materia: PROGRAMACION - I  
Semestre: 2026-I  
Profesor: Pamela Shirley Valenzuela Fernandez

========

INTEGRANTES:
#- Benjamin Mauricio Quintana Flores

=======

El proyecto es una simulacion de la reservacion de la sala de estudio en una biblioteca o cualquier establecimiento que tenga estas salas de estudio. Por eso, mi sistema de reservacion de salas puede ayudar esos lugares que no tienen un sistema propio. En este sistema interactuan 3 elementos como son: Las salas que estan disponibles, el tiempo que se va  autilizar la sala medido en horas y los usuarios registrados dentro del sistema. Un ejemplo claro es como un usuario va a una biblioteca conb la intencion de reservar una sala en un horario de la mañana. Dentro del sistema esta reservacion aparece como un registro de coordenadas unico y en el sistema se identifica con todos los datos que se menciono antes.
Para manejar todos estos datos de los usuarios registrados en el sistema se utilizo los structs. La herramienta struct en la programacion es una agrupacion de diferentes tipos de datos como los enteros o cadenas de texto que hace la representacion de un objeto en la vida real. Dentro del sistema puse un struct llamado Reserva, este struct dentro de sus componentes esta el nombre del responsable, su teléfono, la fecha y el horario en formato texto, el usuario anterior cuando hace su reservacion dentro del struct se llena todos los datos que pide el sistema para reservar una sala, ademas cree otro struct mas, este struct su principal funcion es manejar las horas de la reservacion en tiempo real como que a que hora entra y a que hora el usuario debe salir.

Para la compilacion y ejecucion del codigo que lo hace mediante la consola, como es un proyecto modular, no se puede solo hacer funcionar un solo archivo como el main.cpp, sino el proyecto esta divido en varios archivos que hacen diferentes cosas. El proceso para la compilacion consta de tres pasos, en los cuales se abre la terminal de la computadora y usa el comando cd seguido con la ruta de mi carpeta que se se guardan los archivos de mi proyecto. Como el proyecto esta dividido en varias partes, el compilador todos estos archivos los junta y lo convierte en un solo archivo ejecutable, en todo este proceso tambien analza si cometimos algun error en el codigo, si lo tenemos nos devuleve el codigo y muestra el error. Dentro de mi codigo la compilacion es muy delicado pero a la vez muy ordenado porque si dentro de la consola se presiona alguna tecla equivocada ya te marac que esta mal con letras rojas y tambien sale todo ordenado y todo bien explicito en la consola.
