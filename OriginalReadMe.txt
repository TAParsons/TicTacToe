CSE 3521 PROJECT 2 README

TRACY PARSONS

DATE: 4/4/2013

Note: This program does not use the pseudocode provided in the slides or reference the code provided.

TO COMPILE: enter 'g++ TTT.cpp -o progname'
TO RUN: enter 'progname' OR, if that doesn't work, './progname'

TO USE: Follow prompts on screen

TO FULFILL PART 1:

At prompt "X (Computer) Vs. O (Human/Computer?): ", Input 'C'.
At prompt "Who's turn first? (X/O): ", Input 'X'.
At prompt "Search depth? (0-9): ", Input '9'.
At prompt "Use heuristic? (Y/N): ", Input 'N'.

Scroll up until you reach the the last user prompt (should be "Use heuristic? (Y/N): N"). The minimax scores for all possible initial moves by X are displayed on the 'SCORE' board.

The sequence of moves selected by the program is optimal, with the left-most upper square selected in the event of a tie.

TO FULFILL PART 2:

At prompt "X (Computer) Vs. O (Human/Computer?): ", Input 'C'.
At prompt "Who's turn first? (X/O): ", Input 'X'.
At prompt "Search depth? (0-9): ", Input '4'.
At prompt "Use heuristic? (Y/N): ", Input 'Y'.

Scroll up until you reach the the last user prompt (should be "Use heuristic? (Y/N): N"). The h-minimax scores for all possible initial moves by X are displayed on the 'SCORE' board.

The sequence of moves selected by the program is optimal, strictly following the provided heuristic, with the left-most upper square selected in the event of a tie.
