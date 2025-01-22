# Communication Protocol

To synchronise our server and client during in-game events we use a command based protocol like shown below

## Commands Table

| **Command**            | **Parameters**          | **Description**                                                              | **Source**    |
|-------------------------|-------------------------|------------------------------------------------------------------------------|---------------|
| **CLIENT_JOIN**         | None                   | Client requests to join the game.                                            | Client 💻      |
| **CLIENT_LEAVE**        | None                   | Client requests to leave the game.                                           | Client 💻      |
| **CLIENT_SHOOT**        | None                   | Client sends a shooting action.                                              | Client 💻      |
| **CLIENT_MOVEMENT**     | `Position (float)`     | Client sends movement data.                                                  | Client 💻      |
| **CLIENT_START_GAME**   | None                   | Client requests to start the game.                                           | Client 💻      |
| **CLIENT_SELECT_SHIP**  | `ShipID (int)`         | Client selects a ship.                                                       | Client 💻      |
| **SERVER_ENTITY_NEW**   | `EntityID (int)`       | Server notifies of a new entity.                                             | Server 🗄️     |
| **SERVER_ENTITY_DEAD**  | `EntityID (int)`       | Server notifies of an entity's destruction.                                  | Server 🗄️     |
| **SERVER_GAME_END**     | `Highscore (int)` `Lastscore (int)`      | Server notifies the end of the game                        | Server 🗄️     |
| **SERVER_MOVEMENT**     | `Position (float)`     | Server sends movement updates.                                               | Server 🗄️     |
| **SERVER_ENTITY_HIT**   | `EntityID (int)`       | Server notifies of an entity being hit.                                      | Server 🗄️     |
| **SERVER_WAVE_STATUS**  | `WaveNumber (int)`     | Server sends wave status updates.                                            | Server 🗄️     |
| **SERVER_OK**           | None                   | Server acknowledges a client request.                                        | Server 🗄️     |
| **SERVER_START_GAME**   | None                   | Server notifies the start of the game.                                       | Server 🗄️     |
| **SERVER_PLAYERS_IN_LOBBY** | `PlayerList (array)`| Server sends the list of players in the lobby.                               | Server 🗄️     |
| **SERVER_PLAYERS_READY**| `ReadyStatus (bool)`   | Server notifies players' ready status.                                       | Server 🗄️     |
| **SERVER_UPDATE_POSITION** | `Position (float)`  | Server updates position information.                                         | Server 🗄️     |
| **SERVER_UPDATE_STATS** | `Stats (object)`       | Server updates player or game statistics.                                    | Server 🗄️     |

## Commands Details

### CLIENT_JOIN

**Request Example:**
```json
{
  "command": "CLIENT_JOIN"
}
```

**Return Value:**
SERVER_OK

**Error Value:**


---

### CLIENT_LEAVE

**Request Example:**
```json
{
  "command": "CLIENT_LEAVE"
}
```

**Return Value:**
None (Client is disconnected and data related is destroyed)

**Error Value:**

---

### CLIENT_SHOOT

**Request Example:**
```json
{
  "command": "CLIENT_SHOOT"
}
```

**Return Value:**
200 OK

**Error Value:**
- 500: Not in a game

---

### CLIENT_MOVEMENT

**Request Example:**
```json
{
  "command": "CLIENT_MOVEMENT",
  "position": {
    "x": 10.5,
    "y": 20.3
  }
}
```

**Return Value:**
200 OK

**Error Value:**
- 500: Can't move

---

### CLIENT_START_GAME

**Request Example:**
```json
{
  "command": "CLIENT_START_GAME"
}
```

**Return Value:**
200 OK

**Error Value:**
- 500: Unable to start game

---

### CLIENT_SELECT_SHIP

**Request Example:**
```json
{
  "command": "CLIENT_SELECT_SHIP",
  "shipId": 3
}
```

**Return Value:**
200 OK

**Error Value:**
- 500: Invalid ship ID

---

### SERVER_ENTITY_NEW

**Response Example:**
```json
{
  "command": "SERVER_ENTITY_NEW",
  "entityId": 42
}
```

**Description:**
Server notifies of a new entity.

---

### SERVER_ENTITY_DEAD

**Response Example:**
```json
{
  "command": "SERVER_ENTITY_DEAD",
  "entityId": 42,
  "explosion": 'True' or 'False'
}
```

**Description:**
Server notifies of an entity's destruction.

---

### SERVER_GAME_END

**Response Example:**
```json
{
  "command": "SERVER_GAME_END",
  "highscore": 4000,
  "lastscore": 10000
}
```

**Description:**
Server notifies the end of the game.

---

### SERVER_MOVEMENT

**Response Example:**
```json
{
  "command": "SERVER_UPDATE_POSITION",
  "rotation": 0.5,
  "posx": 500,
  "posy": 500,
  "rectSprite" {1, 2, 3, 4},
  "index": 0,
}
```

**Description:**
Server sends movement updates.

---

### SERVER_UPDATE_STATS

**Response Example:**
```json
{
  "command": "SERVER_UPDATE_STATS",
  "stats": {
    "score": 1500,
    "lives": 3
  }
}
```

**Description:**
Server updates player or game statistics.

---

### SERVER_OK

**Response Example**
```json
{
  "command": "SERVER_OK",
}
```
**Description:**
Notifies the command went through (All purpose answer in the menu)

---

### SERVER_KO

**Response Example**
```json
{
  "command": "SERVER_KO",
}
```
**Description:**
Notifies the command did not went through (All purpose answer in the menu)

---

### SERVER_SEND_ROOMS

**Response Example**
```json
{
  "command": "SERVER_SEND_ROOMS",
  "index": 0,
  "isPublic": 'True' or 'False'
  "clientInRoom": 3,
  "maxPlayer": 10,
  "sizeName": 20,
  "Name": "Kenzo"
}
```
**Description:**
Send room data to server

---

### SERVER_WELL_CREATED_ROOM

**Response Example**
```json
{
  "command": "SERVER_WELL_CREATED_ROOM",
  "index": 0,
}
```
**Description:**
Set state of the World (to begin the game)

---

### SERVER_NBR_CLIENT_IN_ROOM

**Response Example**
```json
{
  "command": "SERVER_NBR_CLIENT_IN_ROOM",
  "nbInRoom": 3,
}
```
**Description:**
So the server knows how much clients there is currently in a room

---

### SERVER_START_GAME

**Response Example**
```json
{
  "command": "SERVER_START_GAME",
}
```
**Description:**
Change the state of the world IN_GAME

---

### SERVER_SEND_SCORE

**Response Example**
```json
{
  "command": "SERVER_SEND_SCORE",
  "score": 1000,
}
```
**Description:**
Send score to server

**Error:**
ERROR_IN_RECEIVE_MESSAGE: "Str"

---

### SERVER_SEND_LEVEL

**Response Example**
```json
{
  "command": "SERVER_SEND_LEVEL",
  "level": 1,
}
```
**Description:**
Level up

**Error:**
ERROR_IN_RECEIVE_MESSAGE: "Str"

---

### SERVER_SEND_PLAYER_INDEX

**Response Example**
```json
{
  "command": "SERVER_SEND_PLAYER_INDEX",
}
```
**Description:**
Send back the index of the player


## A bit about the Binary protocol
The protocol is made to send data only in binary using boost asio.<br>
It takes the data, serializes it, and sends it between clients.<br>

For example :
```cpp
void NetworkFunctions::player_joined(
    WorldsIndex &worldIndex, ClientMessage &clientMessage, NetworkServer &networkServer)
{
    std::cout << "Un joueur " << clientMessage.second << " a rejoint le serveur" << std::endl;
    Message<Protocol> welcomeMsg;
    welcomeMsg.header.id = Protocol::SERVER_OK;
    welcomeMsg << "";
    networkServer.SendToClient(welcomeMsg, clientMessage.second);
    return;
}
```

A message protocol is made, with a header (the command), and the data is inside also.

Using multithreading and mutexes, the data is optimally send through.

A binary packet looks like this for example, where each lines here represent a data, so this makes it easy and fast to send datas to clients.
```c
{
  0,
  0 FF 10 23,
  0 0 0 1,
}
```
