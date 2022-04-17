#include <iostream>
#include <vector>
#include <stack>
using namespace std;

//Dimmensions of 2d Array
int width = 3;
int height = 3;

//Nodes used to store in frontier
//Keeps track of state of the entire board and the path taken to get to that state from the start
class MyNode {
	public:
	string state;
	string path = "";
	//string path;
	MyNode operator =(MyNode const &obj) {
		MyNode temp;
		temp.state = obj.state;
		temp.path = obj.path;
		return temp;
	}

};

//Create a 3x3 board from given string
void create_board(int (&a)[3][3], string tiles) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			a[i][j] = tiles[(i*3)+j] - '0';
		}
	}
}

//Create a 4x4 board from given string
void create_4x4board(char (&a)[4][4], string tiles) {
//	cout << "4x4\n";
        for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                        a[i][j] = tiles[(i*4)+j];
                }
        }
}

//Prints 3x3 board
void print_board(int a[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}

//Prints 4x4 board
void print_4x4board(char a[4][4]) {
        for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                        cout << a[i][j] << " ";
                }
                cout << endl;
        }
}

//Returns the index of the empty tile on the board 
int search (string board) {
	int index = 0;
	for (char c : board) {
		if (c == '0') return index;
		index++;
	}
	return -1;
}

//Swaps two tiles and returns the board state
string swap(string board, int curr, int target) {
	char temp = board[curr];
	board[curr] = board[target];
	board[target] = temp;
	return board;
}

//Checks if a certain board state has already been reached
bool reached_check(vector<string> reached, string board) {
	for (string s : reached) {
		if (s == board) return true;
	}
	return false;
}

//Depth-First Search implentation to find path to goal state
void dfs (string startState, string goalState) {
	//Checks if already in goal state
	if (startState == goalState) {
		cout << "# of Expanded: 0" << " Path: N/A\n";
                return;
        }
	/*
	if (startState.size() == 9) width = 3;
        else if (startState.size() == 16) width = 4;
        else {
                cout << "String Size must be 9 or 16\n";
                return;
        }
	*/
	//Create intial node and set it to starting problem
	MyNode intial;
	intial.state = startState; 
	//Add intial node to frontier
	stack<MyNode> frontier;
	frontier.push(intial);
	//Add intial node to reached states
	vector<string> reached;
	reached.push_back(startState);
	//Keeps Track of % of expanded nodes
	int expanded = 0;
	while (!frontier.empty()) {
//		if (frontier.size() % 1000 == 0)cout << frontier.size() << endl;
		//Updates # of expanded nodes
		expanded++;
		//FIFO: Pops first node of queue
		MyNode poppedNode = frontier.top();
		frontier.pop();
		//Grabs the index of the tile we are in
		int index = search(poppedNode.state);		
		//Calculate the coordinates of the tile in the matrix: 1d -> 2d
		int x = index % width;
		int y = index / width;
		int curr_index = x+width*y;
		//Reaches Tiles in order of UDLR: Up Down Left Right
		//Up
		if (y-1 >= 0) {
			//Swap current tile with tile above
			int state_index = x+width*(y-1);
			string new_board = swap(poppedNode.state,curr_index,state_index);
			//CHecks if new board is the same as the goal
			if (new_board == goalState) {
				cout << "GOAL REACHED\n";
				string path = poppedNode.path + 'U';
				cout << "# of Expanded: " << expanded << " Path: " << path << endl;
				return;
			}
			//Checks if new board has already been reached
			if (!reached_check(reached, new_board)) {
				//Adds new board to reached
				reached.push_back(new_board);
				//Creates new board state 
				MyNode temp;
				temp.state = new_board;
				string newPath = poppedNode.path;
				newPath.push_back('U');
				temp.path = newPath;
				//Adds new board state to frontier
				frontier.push(temp);
			}
		}
		//Down
		if (y+1 < height) {
			int state_index = x+width*(y+1);
			string new_board = swap(poppedNode.state,curr_index,state_index);
			if (new_board == goalState) {
				cout << "GOAL REACHED\n";
				string path = poppedNode.path + 'D';
				cout << "# of Expanded: " << expanded << " Path: " << path << endl;
				return;
			}
			if (!reached_check(reached, new_board)) {
				//Adds new board to reached
				reached.push_back(new_board);
				MyNode temp;
				temp.state = new_board;
				string newPath = poppedNode.path;
				newPath.push_back('D');
				temp.path = newPath;
				frontier.push(temp);
			}
		}
		//Left
		if (x-1 >= 0) {
			int state_index = (x-1)+width*y;
			string new_board = swap(poppedNode.state,curr_index,state_index);
			if (new_board == goalState) {
				cout << "GOAL REACHED\n";
				string path = poppedNode.path + 'L';
				cout << "# of Expanded: " << expanded << " Path: " << path << endl;
				return;
			}
			if (!reached_check(reached, new_board)) {
				reached.push_back(new_board);
				MyNode temp;
				temp.state = new_board;
				string newPath = poppedNode.path;
				newPath.push_back('L');
				temp.path = newPath;
				frontier.push(temp);
			}
		}
		//Right
		if (x+1 < width) {
			int state_index = (x+1)+width*y;
			string new_board = swap(poppedNode.state,curr_index,state_index);
			if (new_board == goalState) {
				cout << "GOAL REACHED\n";
				string path = poppedNode.path + 'R';
				cout << "# of Expanded: " << expanded << " Path: " << path << endl;
				return;
			}
			if (!reached_check(reached, new_board)) {
				reached.push_back(new_board);
				MyNode temp;
				temp.state = new_board;
				string newPath = poppedNode.path;
				newPath.push_back('R');
				temp.path = newPath;
				frontier.push(temp);
			}
		}
	}
	cout << "No Soltion Found\n";
}

//Breadth First Search implentation to find path to goal state
void bfs (string startState, string goalState) {
	//Checks if already in goal state
	if (startState == goalState) {
		cout << "# of Expanded: 0" << " Path: N/A\n";
                return;
        }
	//Create intial node and set it to starting problem
	MyNode intial;
	intial.state = startState; 
	//Add intial node to frontier
	queue<MyNode> frontier;
	frontier.push(intial);
	//Add intial node to reached states
	vector<string> reached;
	reached.push_back(startState);
	//Keeps Track of % of expanded nodes
	int expanded = 0;

	while (!frontier.empty()) {
//		if (frontier.size() % 1000 == 0)cout << frontier.size() << endl;
		//Updates # of expanded nodes
		expanded++;
		//FIFO: Pops first node of queue
		MyNode poppedNode = frontier.front();
		frontier.pop();
		//Grabs the index of the tile we are in
		int index = search(poppedNode.state);		
		//Calculate the coordinates of the tile in the matrix: 1d -> 2d
		int x = index % width;
		int y = index / width;
		int curr_index = x+width*y;

		//Reaches Tiles in order of UDLR: Up Down Left Right
		//Up
		if (y-1 >= 0) {
			//Swap current tile with tile above
			int state_index = x+width*(y-1);
			string new_board = swap(poppedNode.state,curr_index,state_index);
			//CHecks if new board is the same as the goal
			if (new_board == goalState) {
				cout << "GOAL REACHED\n";
				string path = poppedNode.path + 'U';
				cout << "# of Expanded: " << expanded << " Path: " << path << endl;
				return;
			}
			//Checks if new board has already been reached
			if (!reached_check(reached, new_board)) {
				//Adds new board to reached
				reached.push_back(new_board);
				MyNode temp;
				temp.state = new_board;
				string newPath = poppedNode.path;
				newPath.push_back('U');
				temp.path = newPath;
				frontier.push(temp);
			}
		}
		//Down
		if (y+1 < height) {
			int state_index = x+width*(y+1);
			string new_board = swap(poppedNode.state,curr_index,state_index);
			if (new_board == goalState) {
				cout << "GOAL REACHED\n";
				string path = poppedNode.path + 'D';
				cout << "# of Expanded: " << expanded << " Path: " << path << endl;
				return;
			}
			if (!reached_check(reached, new_board)) {
				//Adds new board to reached
				reached.push_back(new_board);
				MyNode temp;
				temp.state = new_board;
				string newPath = poppedNode.path;
				newPath.push_back('D');
				temp.path = newPath;
				frontier.push(temp);
			}
		}
		//Left
		if (x-1 >= 0) {
			int state_index = (x-1)+width*y;
			string new_board = swap(poppedNode.state,curr_index,state_index);
			if (new_board == goalState) {
				cout << "GOAL REACHED\n";
				string path = poppedNode.path + 'L';
				cout << "# of Expanded: " << expanded << " Path: " << path << endl;
				return;
			}
			if (!reached_check(reached, new_board)) {
				reached.push_back(new_board);
				MyNode temp;
				temp.state = new_board;
				string newPath = poppedNode.path;
				newPath.push_back('L');
				temp.path = newPath;
				frontier.push(temp);
			}
		}
		//Right
		if (x+1 < width) {
			int state_index = (x+1)+width*y;
			string new_board = swap(poppedNode.state,curr_index,state_index);
			if (new_board == goalState) {
				cout << "GOAL REACHED\n";
				string path = poppedNode.path + 'R';
				cout << "# of Expanded: " << expanded << " Path: " << path << endl;
				return;
			}
			if (!reached_check(reached, new_board)) {
				reached.push_back(new_board);
				MyNode temp;
				temp.state = new_board;
				string newPath = poppedNode.path;
				newPath.push_back('R');
				temp.path = newPath;
				frontier.push(temp);
			}
		}
	}
	cout << "No Soltion Found\n";
}

//Counter for extended nodes
int counter = 0;
//Keeps track of reached node during IDDFS
vector<string> IDDFSReached;
//Depth Limited Search
bool DLS(MyNode src, string target, int limit) {
	//Checks if current node is target
	if (src.state == target) {
		cout << "# of Expanded: " << counter << " Path: " << src.path << endl;
		return true;
	}
	//Checks if max depth limit has been met
	if (limit <= 0) {
		return false;
	}
	//Adds to extended nodes
	counter++;
	//Grabs the index of the tile we are in
        int index = search(src.state);
        //Calculate the coordinates of the tile in the matrix: 1d -> 2d
        int x = index % width;
        int y = index / width;
        int curr_index = x+width*y;
	//Reaches Tiles in order of UDLR: Up Down Left Right
	//Up
	if (y-1 >= 0) {
		//Swap current tile with tile above
		int state_index = x+width*(y-1);
		string new_board = swap(src.state,curr_index,state_index);
		//Checks if board state has already been reached
		if (!reached_check(IDDFSReached, new_board)) {
			//Creates new board state
			MyNode temp;
			temp.state = new_board;
			string newPath = src.path;
			newPath.push_back('U');
			temp.path = newPath;
			//Creates a new DLS search with new board state that goes one more deeper
			if (DLS(temp, target, limit-1) == true) {
        			return true;
			}
		}
	}
	//Down
	if (y+1 < height) {
                int state_index = x+width*(y+1);
                string new_board = swap(src.state,curr_index,state_index);
		if (!reached_check(IDDFSReached, new_board)) {
                	MyNode temp;
                	temp.state = new_board;
                	string newPath = src.path;
                	newPath.push_back('D');
                	temp.path = newPath;
                	if (DLS(temp, target, limit-1) == true) {
                        	return true;
                	}
		}
        }	
	//Left
        if (x-1 >= 0) {
                int state_index = (x-1)+width*y;
                string new_board = swap(src.state,curr_index,state_index);
		if (!reached_check(IDDFSReached, new_board)) {

                	MyNode temp;
                	temp.state = new_board;
                	string newPath = src.path;
                	newPath.push_back('L');
                	temp.path = newPath;
                	if (DLS(temp, target, limit-1) == true) {
                        	return true;
                	}
		}
        }
	//Right
        if (x+1 < width) {
                int state_index = (x+1)+width*y;
                string new_board = swap(src.state,curr_index,state_index);
		if (!reached_check(IDDFSReached, new_board)) {
                	MyNode temp;
                	temp.state = new_board;
              	  	string newPath = src.path;
			newPath.push_back('R');
              	 	temp.path = newPath;
               		if (DLS(temp, target, limit-1) == true) {
               	 		return true;
               		}
		}
        }
	return false;
}

//Iterative Deepening Depth First Search implemntation to find path to goal state
bool IDDFS(string src, string target, int maxDepth) {
	//Resets extended node counter
	counter = 0;
	//Ckears reached board states
	IDDFSReached.clear();
	//Creates start state
	MyNode start;
	start.state = src;
	IDDFSReached.push_back(src);
	//Iterativly searches using DLS 
	for (int i = 0; i <= maxDepth; i++) {
		if (DLS(start,target,i) == true) return true;
	}
	//No path found
	cout << "Goal not found with max depth of " << maxDepth << endl;
	return false;
}
