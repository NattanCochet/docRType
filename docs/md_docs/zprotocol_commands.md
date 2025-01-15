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
| **SERVER_GAME_END**     | `Result (string)`      | Server notifies the end of the game (e.g., win/lose).                        | Server 🗄️     |
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
200 OK

**Error Value:**
- 500: Game is full, cannot join at the moment
- 503: Server is down/not found
- 504: Not connected to the internet

---

### CLIENT_LEAVE

**Request Example:**
```json
{
  "command": "CLIENT_LEAVE"
}
```

**Return Value:**
200 OK

**Error Value:**
- 500: Not in a game

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
- 503: No Ammo

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
  "entityId": 42
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
  "result": "win"
}
```

**Description:**
Server notifies the end of the game (e.g., win/lose).

---

### SERVER_MOVEMENT

**Response Example:**
```json
{
  "command": "SERVER_MOVEMENT",
  "position": {
    "x": 15.2,
    "y": 25.6
  }
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
