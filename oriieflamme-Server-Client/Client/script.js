$(function () {

    /* Socket qui va gérer la connexion*/
    let socket;

    /* MODAL */
    var modalGameStart = $("#modalGameStart");
    var modalGameFinish = $("#modalGameFinish");
    var modalGameRepioche = $("#modalGameRepioche");
    var modalMain = $("#modalMain");
    var modalCarte = $("#modalCarte");
    var modalPosition = $("#modalPosition");

    modalGameStart.modal("show");


    /* BUTTON */
    var buttonGameStart = $("#buttonGameStart");
    var buttonGameFinish = $("#buttonGameFinish");
    var buttonCarte = $("#buttonCarte");
    var o = $("#o");
    var n = $("#n");
    var buttonPosition = $("#buttonPosition");

    /* INPUT */
    var inputGameStart = $("#inputGameStart");


    /* SCORE */
    var score1 = $("#score1");
    var score2 = $("#score2");

    /* NOM JOUEUR */
    var nf1 = $("#nf1");
    var nf2 = $("#nf2");


    var waitP = $("#waitP");

    /* GAGNANT */
    var winner_p = $("#winner_p");
    var winner = $("#winner_p");

    var effet_carte = $("#effet_carte");
    var carte = $("#carte");

    carte.hide();
    effet_carte.hide();


    /* INPUT */
    var inputIdCarte = $("#inputIdCarte");
    var inputX = $("#inputX");
    var inputY = $("#inputY");

    /* UTILS */
    var plateau = $("#plateau");
    var main = $("#main");
    var game = $("#game");

    game.hide();

    buttonGameFinish.on("click", function () {
        socket.send("OK");
        console.log("Message envoyé : " + "OK");
        modalGameFinish.modal("hide");
    });

    o.on("click", function () {
        socket.send("OUI");
        console.log("Message envoyé : " + "OUI");
        modalGameRepioche.modal("hide");
    });

    n.on("click", function () {
        socket.send("NON");
        console.log("Message envoyé : " + "NON");
        modalGameRepioche.modal("hide");
    });

    buttonCarte.on("click", function () {
        socket.send(inputIdCarte.val());
        console.log("Message envoyé : " + inputIdCarte.val());
        modalCarte.modal("hide");
    });

    buttonPosition.on("click", function () {
        var t = inputX.val() + " " + inputY.val();
        socket.send(t);
        console.log("Message envoyé : " + t);
        modalPosition.modal("hide");
    });

    buttonGameStart.on("click", function () {
        /* On check si le nom de faciton est vide */
        if (inputGameStart.val().length === 0) {
            waitP.text("Attention le nom de faction est vide");
            waitP.addClass("text-danger");
        } else {
            try {
                socket = new WebSocket("ws://localhost:2020");
                console.log("ok");

                /* Evenement si le serveur n'est pas disponnible */
                socket.addEventListener('error', function (event) {
                    waitP.text("Le serveur ne répond pas !");
                    waitP.addClass("text-danger");
                });

                /* Evenement pour la déconnexion du serveur */
                socket.addEventListener('close', function (event) {
                    alert("Connexion perdu avec le serveur, votre adversaire à abandonné ou peut être que c'est vous !");
                });

                /* Evenement pour la réception des messages */
                socket.addEventListener('message', function (event) {
                    var messages = event.data.split("\n");
                    messages.forEach(function (element) {
                        if (element.length > 0) {
                            var message = "Message reçu : " + element;
                            var reponse = handleMessage(element, 0);
                            if (reponse.length > 0) {
                                socket.send(reponse);
                                console.log("Message envoyé : " + reponse);
                            }
                        }
                    });
                });
            } catch (e) {
                alert(e);
            }
        }
    });

    /* Affiche les tooltips */
    function refreshToolTips() {
        const tooltipTriggerList = document.querySelectorAll('[data-bs-toggle="tooltip"]');
        const tooltipList = [...tooltipTriggerList].map(tooltipTriggerEl => new bootstrap.Tooltip(tooltipTriggerEl));
    }

    /* Gère les messages venant du serveur */
    function handleMessage(serveur_message, id_client) {
        if (serveur_message === "OK") {
            carte.hide();
            effet_carte.hide();
            return "";
        } else if (serveur_message === "WAIT") {
            inputGameStart.hide();
            buttonGameStart.hide();
            waitP.text("En attente d'un deuxième joueur");
            return "OK";
        } else if (serveur_message === "GO") {
            modalGameStart.modal("hide");
            game.show();
            return inputGameStart.val();
        } else if (serveur_message.startsWith("NAME")) {
            var t = serveur_message.split("NAME")[1]
            var names = t.split("|");
            nf1.text(names[0]);
            nf2.text(names[1]);
            return "OK";
        } else if (serveur_message.startsWith("MAIN")) {
            refreshMain(serveur_message);
            return "OK";
        } else if (serveur_message.startsWith("REPIOCHE")) {
            modalGameRepioche.modal("show");
            modalMain.html(main.html());
            refreshMain();
            return "";
        } else if (serveur_message.startsWith("PLATEAU")) {
            handlePlateau(serveur_message.split("PLATEAU ")[1])
            return "OK";
        } else if (serveur_message.startsWith("CARTE")) {
            carte.hide();
            effet_carte.hide();
            modalCarte.modal("show");
            return "";
        } else if (serveur_message.startsWith("POSITION")) {
            console.log("Message reçu :" + serveur_message);
            modalPosition.modal("show");
            return "";
        } else if (serveur_message.startsWith("EFFET ")) {
            carte.show();
            effet_carte.show();
            var l = serveur_message.split("EFFET")[1];
            var t = l.split("|");
            carte.text(t[0]);
            effet_carte.text(t[1]);
            pausecomp(2);
            return "OK";
        } else if (serveur_message.startsWith("EFFET1")) {
            carte.show();
            effet_carte.show();
            var l = serveur_message.split("EFFET1")[1];
            var t = l.split("|");
            carte.text(t[0]);
            effet_carte.text(t[1]);
            return "OK";
        } else if (serveur_message.startsWith("SCORE")) {
            var scores = serveur_message.split(" ");
            score1.text(scores[1]);
            score2.text(scores[2]);
            return "OK";
        } else if (serveur_message.startsWith("VAINQUEUR")) {
            if (serveur_message.split("|")[0] === "VAINQUEUR_MANCHE") {
                carte.hide();
                effet_carte.hide();
                var t = serveur_message.split("|")[1];
                winner = "Le Vainqueur de la manche est " + t;
                winner_p.text(winner);
            } else {
                var t = serveur_message.split("|")[1];
                winner = "Le Vainqueur de la partie est " + t;
                winner_p.text(winner);
            }
            $("#modalGameFinish").modal("show");
            return "";
        } else {
            alert(serveur_message + " Not handled");
            return "";
        }
    }

    /* Gère l'affichage du plateau */
    function handlePlateau(element) {
        plateau.empty();
        let rows = element.split("&");
        rows.forEach(function (row) {
            let rec = "<div class=\"card-group\">";
            let cards = row.split("|");
            cards.forEach(function (card) {
                //rec = rec.concat("<div class=\"col\">");
                if (card === "1") {
                    rec = rec.concat(createHiddenCard());
                } else if (card === "0") {
                    rec = rec.concat(createEmptyCard());
                } else {
                    console.log(card);
                    rec = rec.concat(createCard(card,""));
                }
            });
            rec = rec.concat("</div>");
            plateau.append(rec);
        });
    }

    /* Créer les cartes vides */
    function createEmptyCard() {
        return "<div class=\"card\" style=\"font-size: 14px;max-width: 10%;\" style='min-width: 7%; max-width:10%'>" +
            "  <img src=\"img/empty.png\" class=\"card-img-top\">" +
            "</div>";
    }

    /* Créer les cartes cachée*/
    function createHiddenCard() {
        return "<div class=\"card\" style=\"font-size: 14px;max-width: 10%;\" style='min-width: 7%; max-width:10%'>" +
            "  <img src=\"img/card.jpeg\" class=\"card-img-top\">" +
            "</div>";
    }

    /* Créer les cartes de la main */
    function createCard(name, description) {
        return "<div class=\"card\" style=\"font-size: 14px;max-width: 10%;\" data-bs-toggle=\"tooltip\" data-bs-placement=\"top\" title=\"" + description + "\" style='min-width: 7%; max-width:10%'>" +
            "  <img src=\"img/card.jpeg\" class=\"card-img-top\">" +
            "  <div class=\"card-body\">" +
            "    <p class=\"card-title\">" + name + "</p>" +
            "  </div>" +
            "</div>";
    }

    /* Créer les cartes de la main */
    function createCardMain(name, description) {
        return "<div class=\"card mx-auto\" style=\"font-size: 14px;max-width: 15%;\" data-bs-toggle=\"tooltip\" data-bs-placement=\"top\" title=\"" + description + "\" style='min-width: 7%; max-width:10%'>" +
            "  <img src=\"img/card.jpeg\" class=\"card-img-top\">" +
            "  <div class=\"card-body\">" +
            "    <p class=\"card-title\">" + name + "</p>" +
            "  </div>" +
            "</div>";
    }

    /* Affiche la main */
    function refreshMain(dataMain) {
        if (typeof dataMain !== 'undefined') {
            let cartes = dataMain.split("MAIN ")[1].split("&");
            main.empty();
            console.log(cartes);
            if (cartes.length > 0) {
                cartes.forEach(function (carte) {
                    let item = carte.split("|");
                    main.append(createCardMain(item[0], item[1]));
                });
                refreshToolTips();
            }
        }
    }

    function pausecomp(s) {
        var date = new Date();
        var curDate = null;
        do { curDate = new Date(); }
        while(curDate-date < s*1000);
    }
});