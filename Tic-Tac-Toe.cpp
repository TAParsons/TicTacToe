// =============================================== //
// ||	CSE 3521 PROJECT 2						|| //
// ||	TRACY PARSONS		    				|| //
// ||	DATE: 4/4/2013							|| //
// ||											|| //
// ||	Note: This program does not use the		|| //
// ||	pseudocode provided in the slides		|| //
// ||	or reference the code provided.			|| //
// =============================================== //
// ||	TO USE:									|| //
// ||	Read Readme, follow prompts on screen	|| //
// =============================================== //

#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <float.h>
#include <unistd.h>

using namespace std;

class Board {
	public:
	// 1 = X; 0 = empty; -1 = O
	int v[3][3];
	
	void Init ();
	int Win (bool show);
	bool Draw ();
	int Hue ();
};

void Board::Init () {	// initialize board; set each square to 0
	for (int y=0; y<3; y++) {
		for (int x=0; x<3; x++) {v[y][x] = 0;}
	}
	return;
}

int Board::Win (bool show) {	// return 1 if X win, -1 if O win, 0 if no win
	if (v[1][1] == 1) {	// if middle = X, check diagonals and middle row/column
		if (v[0][0]+v[1][1]+v[2][2] == 3) {	// X wins downslope diagonal
			if (show) {cout << "X wins downslope diagonal\n";}
			return 1;
		}
		if (v[1][0]+v[1][1]+v[1][2] == 3) {	// X wins middle row
			if (show) {cout << "X wins middle row\n";}
			return 1;
		}
		if (v[2][0]+v[1][1]+v[0][2] == 3) {	// X wins upslope diagonal
			if (show) {cout << "X wins upslope diagonal\n";}
			return 1;
		}
		if (v[0][1]+v[1][1]+v[2][1] == 3) {	// X wins middle column
			if (show) {cout << "X wins middle column\n";}
			return 1;
		}
	}
	else if (v[1][1] == -1) {	// if middle = O, etc.
		if (v[0][0]+v[1][1]+v[2][2] == -3) {	// O wins downslope diagonal
			if (show) {cout << "O wins downslope diagonal\n";}
			return -1;
		}
		if (v[1][0]+v[1][1]+v[1][2] == -3) {	// O wins middle row
			if (show) {cout << "O wins middle row\n";}
			return -1;
		}
		if (v[2][0]+v[1][1]+v[0][2] == -3) {	// O wins upslope diagonal
			if (show) {cout << "O wins upslope diagonal\n";}
			return -1;
		}
		if (v[0][1]+v[1][1]+v[2][1] == -3) {	// O wins middle column
			if (show) {cout << "O wins middle column\n";}
			return -1;
		}
	}
	
	if (v[0][0] == 1) {	// if top left = X, check left column, top row, and downslope column
		if (v[0][0]+v[1][0]+v[2][0] == 3) {	// X wins left column
			if (show) {cout << "X wins left column\n";}
			return 1;
		}
		if (v[0][0]+v[0][1]+v[0][2] == 3) {	// X wins top row
			if (show) {cout << "X wins top row\n";}
			return 1;
		}
	}
	else if (v[0][0] == -1) {	// if top left = O, etc.
		if (v[0][0]+v[1][0]+v[2][0] == -3) {	// O wins left column
			if (show) {cout << "O wins left column\n";}
			return -1;
		}
		if (v[0][0]+v[0][1]+v[0][2] == -3) {	// O wins top row
			if (show) {cout << "O wins top row\n";}
			return -1;
		}
	}
	
	if (v[2][2] == 1) {	// if bottom right = X, check right column, bottom row, and upslope diagonal
		if (v[0][2]+v[1][2]+v[2][2] == 3) {	// X wins right column
			if (show) {cout << "X wins right column\n";}
			return 1;
		}
		if (v[2][0]+v[2][1]+v[2][2] == 3) {	// X wins bottom row
			if (show) {cout << "X wins bottom row\n";}
			return 1;
		}
	}
	else if (v[2][2] == -1) {	// if bottom right = O, etc.
		if (v[0][2]+v[1][2]+v[2][2] == -3) {	// O wins bottom column
			if (show) {cout << "O wins right column\n";}
			return -1;
		}
		if (v[2][0]+v[2][1]+v[2][2] == -3) {	// O wins bottom row
			if (show) {cout << "O wins bottom row\n";}
			return -1;
		}
	}
	return 0;	
}

bool Board::Draw () {	// check if board full (if any squares = 0, then ret = 0)
	bool ret = true;
	for (int y=0; y<3; y++) {
		ret *= v[y][0]*v[y][1]*v[y][2];
	}
	return ret;
}

int Board::Hue () {	// heuristic evaluation
	int H = 0;
	for (int i=0;i<3;i++) {
		if (v[i][0]*v[i][1]*v[i][2] == 0) {		// empty space in ith row; determine subscore
			int s = v[i][0]+v[i][1]+v[i][2];
			if (s == 2) {H+=3;}	// 2 X's
			else if (s == 1) {H++;}	// 1 X
			else if (s == -2) {H-=3;}	// 2 O's
			else if (s == -1) {H--;}	// 1 O
		}
		if (v[0][i]*v[1][i]*v[2][i] == 0) {		// empty space in ith column; determine subscore
			int s = v[0][i]+v[1][i]+v[2][i];
			if (s == 2) {H+=3;}	// 2 X's
			else if (s == 1) {H++;}	// 1 X
			else if (s == -2) {H-=3;}	// 2 O's
			else if (s == -1) {H--;}	// 1 O
		}
	}	
	if (v[0][0]*v[1][1]*v[2][2] == 0) {		// empty space in downslope diagonal; determine subscore
		int s = v[0][0]+v[1][1]+v[2][2];
		if (s == 2) {H+=3;}	// 2 X's
		else if (s == 1) {H++;}	// 1 X
		else if (s == -2) {H-=3;}	// 2 O's
		else if (s == -1) {H--;}	// 1 O
	}
	if (v[0][2]*v[1][1]*v[2][0] == 0) {		// empty space in upslope diagonal; determine subscore
		int s = v[0][2]+v[1][1]+v[2][0];
		if (s == 2) {H+=3;}	// 2 X's
		else if (s == 1) {H++;}	// 1 X
		else if (s == -2) {H-=3;}	// 2 O's
		else if (s == -1) {H--;}	// 1 O
	}
	return H;	// return heuristic value
}

class Move {
	public:
	// If move invalid, then pointer to move = NULL
	Move *TL;	//	-------------------------
	Move *T;	//	|	TL	|	T	|	TR	|
	Move *TR;	//	-------------------------
	Move *L;	//	|	L	|	C	|	R	|
	Move *C;	//	-------------------------
	Move *R;	//	|	BL	|	B	|	BR	|
	Move *BL;	//	-------------------------
	Move *B;
	Move *BR;
	
	bool XTurn;	// X's turn or O's turn?
	Board State;	// game state
	int score;		// state score
	void Init ();
	void Del ();
	void Display ();
	void DefineMoves (int depth, bool h);	// this is where the magic happens
};

void Move::Init () {
	// initialize moves to null pointers
	TL = 0;
	T = 0;
	TR = 0;
	L = 0;
	C = 0;
	R = 0;
	BL = 0;
	B = 0;
	BR = 0;
	// XTurn = 0;	// set during DefineMoves
	State.Init ();	// initialize game state
	score = 0;
}

void Move::Del () {	// this is used to delete the move tree; doesn't get used because it takes too long
	if (TL != 0) {
		TL->Del ();
		free (TL = 0);
	}
	if (T != 0) {
		T->Del ();
		free (T = 0);
	}
	if (TR != 0) {
		TR->Del ();
		free (TR = 0);
	}
	if (L != 0) {
		L->Del ();
		free (L = 0);
	}
	if (C != 0) {
		C->Del ();
		free (C = 0);
	}
	if (R != 0) {
		R->Del ();
		free (R = 0);
	}
	if (BL != 0) {
		BL->Del ();
		free (BL);
	}
	if (B != 0) {
		B->Del ();
		free (B = 0);
	}
	if (BR != 0) {
		BR->Del ();
		free (BR = 0);
	}
	return;
}

void Move::Display () {	// display game state and move scores
	cout << "	BOARD  #  SCORE\n";
	for (int y=0; y<3; y++) {
		cout << "  -----------  #  -----------\n";
		for (int x=0; x<3; x++) {
			cout << " | ";
			if (State.v[y][x] > 0) {cout << 'X';}
			else if (State.v[y][x] < 0) {cout << 'O';}
			else {//cout << '.';}
				cout << y*3+x+1;	// output coordinate
			}
		}
		cout << " | #";
		for (int x=0; x<3; x++) {
			cout << " | ";
			Move *disp = 0;	// to make code tidy, this pointer points to each move getting printed
			switch (y*3+x) {
				case 0: disp = TL; break;
				case 1: disp = T; break;
				case 2: disp = TR; break;
				case 3: disp = L; break;
				case 4: disp = C; break;
				case 5: disp = R; break;
				case 6: disp = BL; break;
				case 7: disp = B; break;
				case 8: disp = BR; break;
			}
			if (!disp) {cout << '#';}
			else {cout << disp->score;}
		}
		cout << " |\n";
	}
	cout << "  -----------  #  -----------\n";
	return;
}

void Move::DefineMoves (int depth, bool h) {
	int W = State.Win (false);	// store result so we don't have to keep evaluating the board
	if (W != 0 || depth == 0 || State.Draw ()) {	// if someone's won or at depth limit, return
		score = W;
		if (h && !W) {score = State.Hue ();}	// if using heuristic and not win/loss, score = 3X_2 + X_1 - 3O_2 - O_1
		return;
	}
	if (XTurn) {score = -1-(4*h);}	// set score to worst possible value for player (X low, O high)
	else {score = 1+(4*h);}
	
	// for each move, check if already taken (State.v[y][x] != 0). If not, point NewMove at it.
	// If NewMove null, make new move. Work out turn and point appropriate move pointer at it.
	// Finally, DefineMoves for NewMove and evaluate scores. 
	for (int y=0; y<3; y++) {
		for (int x=0; x<3; x++) {
			if (State.v[y][x] == 0) {	// empty, so we can place a marker here
				Move *NewMove = 0;
				switch (y*3+x) {
					case 0: NewMove = TL; break;
					case 1: NewMove = T; break;
					case 2: NewMove = TR; break;
					case 3: NewMove = L; break;
					case 4: NewMove = C; break;
					case 5: NewMove = R; break;
					case 6: NewMove = BL; break;
					case 7: NewMove = B; break;
					case 8: NewMove = BR; break;
				}
				if (!NewMove) {
					NewMove = new (Move);
					NewMove->Init ();
				}
				NewMove->XTurn = (XTurn == 0);
				NewMove->State = State;
				NewMove->State.v[y][x] = -1+XTurn*2;	// = -1+(0*2) = -1, or = -1+(1*2) = 1
				switch (y*3+x) {
					case 0: TL = NewMove; break;
					case 1: T = NewMove; break;
					case 2: TR = NewMove; break;
					case 3: L = NewMove; break;
					case 4: C = NewMove; break;
					case 5: R = NewMove; break;
					case 6: BL = NewMove; break;
					case 7: B = NewMove; break;
					case 8: BR = NewMove; break;
				}					
				NewMove->DefineMoves (depth-1, h);
				if ((XTurn && score < NewMove->score) || (!XTurn && score > NewMove->score)) {	// X's turn, so pick highest min score
					score = NewMove->score;
				}
				free (NewMove = 0);	// free NewMove to prevent memory issues
			}
		}
	}
	return;
}

int main () {
	//srand (time (0));	// initialize random seed
	
	Move root, *current;			// root of move tree, current = current board state
	//root = new (Move);
	root.Init ();
	int mode = 0;
	string in = "y";
	while (in == "y" || in == "Y") {
		bool heur = 0, human = 0;	// whether using heuristic and whether user is playing
		int gloat = 0, depth = 1;	// gloat variable and search depth
		system ("clear");
		while (in != "h" && in != "H" && in != "c" && in != "C") {
			cout << "X (Computer) Vs. O (Human/Computer)? (H/C): ";
			cin >> in;
			if (in == "h" || in == "H") {human = true;}
			else if (in == "c" || in == "C") {human = false;}
			else {cout << "Invalid input! Try again!\n";}
		}
		while (in != "x" && in != "X" && in != "o" && in != "O") {
			cout << "Who's turn first? (X/O): ";
			cin >> in;
			if (in == "x" || in == "X" || in[0] == 'x' || in[0] == 'X') {root.XTurn = true;}
			else if (in == "o" || in == "O" || in[0] == 'o' || in[0] == 'O') {root.XTurn = false;}
			else {cout << "Invalid input! Try again!\n";}
		}
		while (in[0] < '1' || in[0] > '9') {
			cout << "Search depth? (1-9): ";
			cin >> in;
			if (in[0] >= '1' && in[0] <= '9') {depth = in[0]-'0';}
			else {cout << "Invalid input! Try again!\n";}
		}
		while (in != "y" && in != "Y" && in != "n" && in != "N") {
			cout << "Use heuristic? (Y/N): ";
			cin >> in;
			if (in == "y" || in == "Y") {heur = true;}
			else if (in == "n" || in == "N") {heur = false;}
			else {cout << "Invalid input! Try again!\n";}
		}
		
		root.DefineMoves (depth+1, heur);	// search at least two deep to prevent accessing null pointers
		current = &root;
		while (!current->State.Win (false) && !current->State.Draw ()) {	// while no one's won
			if (current->XTurn || !human) {			// computer's turn
				if (depth > 1) {
					int z = 0;
					// This commented section of code was in place to prevent the program from giving up partway through;
					// Without this, it considers losing in 8 moves as bad as losing in 1 move.
					
					/*while (current->score != -1+current->XTurn*2 && z < depth) {
						cout << "SCORE: " << current->score << "; Searching to depth of " << ++z << '\n';
						current->DefineMoves (z, heur);
					}
					while (current->score*(-1+current->XTurn*2) < 0 && z > 1) {	// score < 0. See if we can find a better option
						cout << "SCORE: " << current->score << "; Backtracking to depth of " << --z << '\n';
						current->DefineMoves (z, heur);
					}*/
					
					cout << "SCORE: " << current->score << "; Searching to depth of " << depth << '\n';
					current->DefineMoves (depth, heur);
				}
				else {
					current->DefineMoves (2, heur);
					cout << "SCORE: " << current->score << "; Searching to depth of " << depth << '\n';
					current->DefineMoves (depth, heur);
				}
				cout << "Post evaluation, pre-decision:\n";
				current->Display ();
				if (!current->State.v[0][0] && current->TL->score == current->score) {
					current = current->TL;
					cout << char('O'+('X'-'O')*!current->XTurn) << " picked TL";
				}
				else if (!current->State.v[0][1] && current->T->score == current->score) {
					current = current->T;
					cout << char('O'+('X'-'O')*!current->XTurn) << " picked T";
				}
				else if (!current->State.v[0][2] && current->TR->score == current->score) {
					current = current->TR;
					cout << char('O'+('X'-'O')*!current->XTurn) << " picked TR";
				}
				else if (!current->State.v[1][0] && current->L->score == current->score) {
					current = current->L;
					cout << char('O'+('X'-'O')*!current->XTurn) << " picked L";
				}
				else if (!current->State.v[1][1] && current->C->score == current->score) {
					current = current->C;
					cout << char('O'+('X'-'O')*!current->XTurn) << " picked C";
				}
				else if (!current->State.v[1][2] && current->R->score == current->score) {
					current = current->R;
					cout << char('O'+('X'-'O')*!current->XTurn) << " picked R";
				}
				else if (!current->State.v[2][0] && current->BL->score == current->score) {
					current = current->BL;
					cout << char('O'+('X'-'O')*!current->XTurn) << " picked BL";
				}
				else if (!current->State.v[2][1] && current->B->score == current->score) {
					current = current->B;
					cout << char('O'+('X'-'O')*!current->XTurn) << " picked B";
				}
				else if (!current->State.v[2][2] && current->BR->score == current->score) {
					current = current->BR;
					cout << char('O'+('X'-'O')*!current->XTurn) << " picked BR";
				}
				else {	// mighty big error: score selected doesn't match any possible moves.
					cout << "Nowhere left to run...expected " << current->score << "\n";
					current->Display ();
					fflush (0);
					sleep (10);
				}
				cout << " with score of " << current->score << '\n';
				if (!human) {current->Display ();}
			}
			else {							// human player's turn
				cerr << "Player's turn\n";
				current->Display ();
				if (gloat != current->score && !heur) {	// as long as you're going to make a tic-tac-toe program, you might as well make it gloat too.
					gloat = current->score;
					if (gloat == 1) {cout << "I am, by any practical definition of the words, foolproof and incapable of error.\n";}
					else if (gloat == -1) {cout << "This loss can only be attributed to human error.\n";}
				}
				cout << "Input number of square to mark: ";
				cin >> in;
				if (!current->State.v[(in[0]-'0'-1)/3][(in[0]-'0'-1)%3]) {	// track user moves by traversing move tree
					switch (in[0]-'0') {
						case 1: current = current->TL; break;
						case 2: current = current->T; break;
						case 3: current = current->TR; break;
						case 4: current = current->L; break;
						case 5: current = current->C; break;
						case 6: current = current->R; break;
						case 7: current = current->BL; break;
						case 8: current = current->B; break;
						case 9: current = current->BR; break;
					}
				}
				else {cout << "Invalid Input! Try Again!\n";}
			}
		}
		// somebody won or its a draw!
		cout << "  BOARD  \n";
		for (int y=0; y<3; y++) {
			cout << "  -----------\n";
			for (int x=0; x<3; x++) {
				cout << " | ";
				if (current->State.v[y][x] > 0) {cout << 'X';}
				else if (current->State.v[y][x] < 0) {cout << 'O';}
				else {cout << '.';}
			}
			cout << " |\n";
		}
		cout << "  -----------\n";
		if (!current->State.Win (true)) {cout << "Draw!\n";}
		else if (human) {
			if (!current->XTurn) {cout << "Bow to your silicon overlord, meatbag\n";}
			else {cout << "User won!\n";}
		}
		else {cout << char('O'+('X'-'O')*!current->XTurn) << " won!\n";}	// display which player won
		cout << "Play again? (Y): ";
		cin >> in;
	}
	return 0;
}
