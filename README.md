Presentation
===
This is a program that play the single round basic version of the game Kamisado, [you can find the rules here](http://www.boardspace.net/kamisado/english/RULES%20ENG.pdf).
It provide severals AI and a graphical displayer.

How to run
===
**Dependences**
- SFML

**Compilation**
```bash
cmake CMakeList.txt
make
```

**Launch**
```bash
python3 interface.py first_player_ai_exe_name second_player_ai_exe_name referee_exe_name display_exe_name (facultative)
```

**Available exe after compilation**
- *Kamisado_IA_MCTS :* An AI that use an MCTS algorithm to play
- *Kamisado_IA_Minimax :* An AI that use a minimax algorithm to play
- *Kamisado_IA_Ramdom :* An AI that play at random
- *Kamisado_Referee :* The referee that validate each play and announce the end of a game
- *Kamisado_Display :* The displayer of the game, using SFML

**Launch example**
```bash
python3 interface.py Kamisado_IA_Ramdom Kamisado_IA_MCTS Kamisado_Referee Kamisado_Display
```

**How to add an AI**

You just need to have a program looping over stdin and writing to stdout in reaction to these commands :

|           Commands          |      Response                      |                                                     Other action needed                                                     |
|:---------------------------:|:----------------------------------:|:---------------------------------------------------------------------------------------------------------------------------:|
|            init\n           | = \n\n                             | Initialise your board and anything else your program needs to function                                                      |
|            name\n           | = PROGRAM_NAME\n\n                 |                                                                                                                             |
|      move R1 C1 R2 C2\n     | = \n\n                             | Update your board so that move has been played                                                                              |
|          genmove\n          | = R1 C1 R2 C2\n or = resign\n\n    | Calls your AI to provide to move you want to do depending on the current board state (and update your board with that move) |
|            quit\n           | = \n\n                             | Do any clean up your program need, send the response and quit.                                                              |
| other or in case of problem | = ?\n\n                            |                                                                                                                             |

*Note :* R1 C1 R2 C2 corresponds respectively to the starting and the ending row and column of of piece.
