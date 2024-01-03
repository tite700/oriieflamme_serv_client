import asyncio
from subprocess import Popen

import websockets


####################################################################################################################
#   Le programme en C utilise des Sockets, ces sockets ne sont pas gérés nativement par le Javascript              #
#   De même le Javascript utilise des WebSockets, qui ne sont pas gérés par le C                                   #
#   Nous tenions à avoir une interface portable, qui ne nécessite pas de logiciel à télécharger                    #
#   Après avoir essayé différente librairie (et avoir perdu beaucoup de temps)                                     #
#   Nous avons décidé d'utiliser un serveur en Python pour faire la passerelle entre les Sockets et les WebSockets #
#   Tout le fonctionnement est basé sur des événements, à chaque reception de message                              #
#   Le programme Python va retransmettre les données vers le client/ serveur concerné                              #
####################################################################################################################
class CServer(asyncio.Protocol):

    def __init__(self, message, on_con_lost, jsclient):
        self.transport = None
        self.message = message
        self.on_con_lost = on_con_lost
        self.jsClient = jsclient

    def getTransport(self):
        return self.transport

    def connection_made(self, transport):
        self.transport = transport
        transport.write("JOIN\n".encode())
        print('PY : JOIN')

    def data_received(self, data):
        print('C : ' + data.decode())
        asyncio.get_event_loop().create_task(self.jsClient.send(data.decode()))

    def connection_lost(self, exc):
        print('The server closed the connection')
        asyncio.get_event_loop().create_task(self.jsClient.close())
        self.on_con_lost.set_result(True)


# Le serveur WebSockets est client sur serveur principal en C #
# Il se résume en une boucle While qui va attendre un message #
# Et va le retransmettre au serveur principal #
async def js_client_handler(websocket):
    print("JS : Nouvelle connexion")

    # On récupère une boucle d'événements #
    loop = asyncio.get_running_loop()

    # On ajoute notre client dans cette boucle #
    cServer = CServer("", loop.create_future(), websocket)

    # On ouvre une connexion vers le serveur principal #
    await loop.create_connection(
        lambda: cServer,
        'localhost', 2000)

    while True:
        # On attend un nouveau message #
        message = await websocket.recv()
        # On ajoute un \n pour marquer la fin du message #
        message += "\n"
        # On affiche en sortie standard le message envoyé pour le serveur principal #
        print("JS : " + message.lstrip())
        # On envoie le message au serveur principal #
        cServer.getTransport().write(message.encode())


# On lance le serveur Socket en C #
p = Popen(["./../Server/bin/oriieflamme"])

# On lance le serveur WebSockets #
start_server = websockets.serve(js_client_handler, "localhost", 2020)

# On lance dans un thread séparé le serveur WebSockets #
asyncio.get_event_loop().run_until_complete(start_server)

# Le try/catch est spécifique pour Windows, cela évite que le programme s'arrête sans raison #
try:
    asyncio.get_event_loop().run_forever()
except KeyboardInterrupt:
    pass

# On récupère les sorties standard et d'erreurs venant du serveur en C pour les afficher dans la sortie du Python #
stdout, stderr = p.communicate()
