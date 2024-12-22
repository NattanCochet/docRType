# Communication Protocol

To synchronise our server and client during in-game events we use a command based protocol like shown below

## Commands Table

| **Command**  | **Parameters**                                                                                     | **Description**                                                              | **Source** |
|--------------|---------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------|----------------|
| **WELCOME**  | `ID (std::size_t)`                                                                                | Indicates that the client is accepted by the server and returns the client ID. | Server🗄️     |
| **POS**      | `TYPE (string), POSX (float), POSY (float), RECTWIDTH (float), RECTHEIGHT (float), ROTATION (float)` | Tells the client which sprite to display (path of the sprite) at the given position. | Server🗄️     |
| **END**      | `WIN / LOOSE (int)`                                                                               | Tells the client when the game ends and whether the player won or lost.       | Server🗄️     |
| **NBRLIFE**  | `NBRLIFE (std::size_t)`                                                                           | Tells the client how many lives remain.                                      | Server🗄️     |
| **SCORE**    | `SCORE (int)`                                                                                     | Tells the client the current score of the player.                            | Server🗄️     |
| **CONNECT**  | None                                                                                              | Indicates to the server that a new client has connected.                     | Client💻     |
| **EVENTS**   | `ID (std::size_t), EVENTS ([key : string, ispressed: bool])`                                       | Tells the server which commands the client has input.                        | Client💻     |
| **DECONNECT**| `ID (std::size_t)`                                                                                | Indicates to the server that a client has disconnected.                      | Client💻     |
| **GETROOM**  | `ID (std::size_t)`                                                                                | Requests from the server a list of available rooms to join.                  | Client💻     |
| **CREATE**   | `ID (std::size_t), ISPUBLIC (bool), NBRMAXPLAYERS (std::size_t), PASSWORD (std::string), NAME (std::string)` | Creates a room with the specified parameters.                               | Client💻     |
| **JOIN**     | `CLIENTID (std::size_t), ROOMID (std::size_t), PASSWORD (std::string)`                             | Joins a room with the specified credentials.                                 | Client💻     |
| **LEAVE**    | `ID (std::size_t)`                                                                                | Indicates to the server that the client is leaving the room.                 | Client💻     |
