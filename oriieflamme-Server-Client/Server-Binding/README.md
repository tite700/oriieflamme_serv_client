Malheureusement nous n'avions que très peu de connaissance pratique réseau en C, et les exemples étant limité par rapport à l'utilisation que nous voulions en faire.
Nous avons eu beaucoup de mal à établir une connexion entre l'interface web et le serveur en C, ce qui nous a fait perdre beaucoup de temps.

Le problème étant que les sockets ne sont pas géré nativement en Javascript et qu'il n'existe pas (à ma connaissance) de librairie que nous aurions pu utiliser.
Il est cependant possible d'utiliser des WebSockets, mais qui ne sont pas géré nativement en C.
Il faut forcément passer par une librairie, et nous n'avons pas réussi à obtenir ce que l'on souhaitait.

La solution la plus simple compte tenu des délais était de créer une passerelle en Python permettant de faire la liaison entre 
le client Web utilisant des Websockets et le serveur en C utilisant des sockets.

Ainsi le programme en Python est client sur serveur en C, et est serveur du client Web.

Procédure d'installation :
Il est nécessaire d'avoir Python3 d'installé afin de faire tourner ce serveur.
Ainsi que la dernière version du package WebSockets
    `` pip install websockets ``