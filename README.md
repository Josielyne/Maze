# Maze
A maze puzzle that solves itself using stacks
The coordinates of the mouse are pushed to a stack to keep track of the positions the mouse has been. An array is also used to represent
the maze board, where 1s are walls, 0s are empty spaces, 2s are mines, 3s are the exit, and 4s are visited spaces. Every time the mouse
moves, its previous position is marked as a visited space on the maze board. Mines can be implemented by editing the maze board with
randomized 2s. Once the mouse hits the exit, a message is displayed saying the exit has been found. If a mine is hit, a message appears
notifying the user.
