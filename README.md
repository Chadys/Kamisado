Presentation
===
This is a program that play the single round basic version of the game Kamisado, [you can find the rules here](http://www.boardspace.net/kamisado/english/RULES%20ENG.pdf).
It provide severals AIs and a graphical displayer. Please note that in this program, the black pieces are at the top of the board.

How to run
===
**Dependences**
- SFML

**Compilation**
```bash
cmake CMakeLists.txt
make
```

**Launch**
```bash
python3 interface.py first_player_ai_exe_name second_player_ai_exe_name referee_exe_name display_exe_name (facultative)
```
No exe of an AI must be called `human` (see *How to add a human player*).

**Available exe after compilation**
- *Kamisado_IA_MCTS :* An AI that use an MCTS algorithm to play
- *Kamisado_IA_Minimax :* An AI that use a minimax algorithm to play
- *Kamisado_IA_Ramdom :* An AI that play at random
- *Kamisado_Referee :* The referee that validate each play and announce the end of a game
- *Kamisado_Display :* The displayer of the game, using SFML

**Launch example**
```bash
python3 ./interface.py ./Kamisado_IA_Ramdom ./Kamisado_IA_MCTS ./Kamisado_Referee ./Kamisado_Display
```

**How to add a human player**

Simply replace one (or both) of the exe name with `human` (you need the graphic displayer for this). The program will then ask you to play a move at the appropriate time. It will be your responsibility to do a legal move.
If you are the first player you need to click on the piece you want to move and then on the case you want to move it to (you can use right click to deselect that piece if you want to choose another one).
After the first move, the piece that will move is automatically selected for you so just click on the case you want to move that piece to. If you can't move and need to pass, click on the case where your piece is at.

**How to add an AI**

You just need to have a program looping over stdin and writing to stdout in reaction to these commands :

|           Commands          |      Response                      |     Other action needed             |
|:---------------------------:|:----------------------------------:|:-----------------------------------:|
|init\n|= \n\n|Initialize your board and anything else your program needs to function|
|name\n|= PROGRAM_NAME\n\n| |
|move R1 C1 R2 C2\n|= \n\n|Update your board so that move has been played|
|genmove\n|= R1 C1 R2 C2\n\n or = resign\n\n|Calls your AI to provide to move you want to do depending on the current board state (and update your board with that move)|
|quit\n|= \n\n|Do any clean up your program need, send the response and quit.|
|other or in case of problem|= ?\n\n| |

*Note :* R1 C1 R2 C2 corresponds respectively to the starting and the ending row and column of a piece.
