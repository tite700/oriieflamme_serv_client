$(function () {
    /* Cette fonction va répondre automatiquement aux messages envoyés par le serveur */
    /* En respectant le protocole qu'on avait fixé */
    function handleMessage(serveur_message, id_client) {
        if ( serveur_message === "OK" ) {
            return "";
        } else if ( serveur_message === "WAIT" ) {
            return "OK";
        } else if ( serveur_message === "GO" ) {
            return "FACTION_" + id_client;
        } else if ( serveur_message.startsWith("NAME") ) {
            return "OK";
        } else if ( serveur_message.startsWith("MAIN") ) {
            return "OK";
        } else if ( serveur_message.startsWith("REPIOCHE") ) {
            return "OUI";
        } else if ( serveur_message.startsWith("PLATEAU") ) {
            return "OK";
        } else if ( serveur_message.startsWith("CARTE") ) {
            return "0";
        } else if ( serveur_message.startsWith("POSITION") ) {
             if ( first ) {
                 first = false;
                 return "0 0";
             } else
                return "0 1";
        } else if ( serveur_message.startsWith("EFFET") ) {
            return "OK";
        } else if ( serveur_message.startsWith("SCORE") ) {
            return "OK";
        } else if ( serveur_message.startsWith("VAINQUEUR") ) {
            first = true
            return "OK";
        } else {
            alert(serveur_message + " Not handled");
        }
    }

    let socket_0;

    let first = true;
    $("#connexion_0").click(function () {
        /* On initialise le WebSocket vers le serveur passerelle */
        socket_0 = new WebSocket("ws://localhost:2020");
        /* On ajoute un événement qui va s'occuper de la réception de message client */
        socket_0.addEventListener('message', function (event) {
            /* On split si jamais on reçoit plusieurs messages en même temps */
            /* Le character de fin de message est /n */
            var messages = event.data.split("\n");
            messages.forEach(function (element) {
                /* Pour chaque message */
                if (element.length > 0) {
                    /* On affiche le message reçu */
                    var message = "Message reçu : " + element;
                    $("#log_0").append(message + "\n");
                    /* On génère la réponse au message reçu */
                    var reponse = handleMessage(element, 0);
                    /* Si la réponse n'est pas vide */
                    if (reponse.length > 0) {
                        /* On envoie la réponse */
                        socket_0.send(reponse);
                        /* On log la réponse envoyée */
                        $("#log_0").append("Message envoyé :" + reponse + "\n");
                    }
                }
            })
        });
    });

    let socket_1;
    $("#connexion_1").click(function () {
        socket_1 = new WebSocket("ws://localhost:2020");
        socket_1.addEventListener('message', function (event) {
            var messages = event.data.split("\n");
            messages.forEach(function (element) {
                if (element.length > 0) {
                    var message = "Message reçu : " + element;
                    $("#log_1").append(message + "\n");

                    var reponse = handleMessage(element, 1);
                    if (reponse.length > 0) {
                        socket_1.send(reponse);
                        $("#log_1").append("Message envoyé :" + reponse + "\n");
                    }
                }
            })
        });
    });
});
