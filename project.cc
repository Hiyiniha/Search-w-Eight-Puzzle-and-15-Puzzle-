#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <fstream>
#include "search.h"
using namespace std;

//Size of matrix
#define SIZE 9	//3x3 Board
//#define SIZE 16 //4x4 Board

//Applies given path to 3x3 puzzle
void apply3x3(string puzzle, string path) {
	//int arr[3][3];
	//Checks if SIZE is set correctly
	if (SIZE == 16) {
		cout << "Change SIZE to 9\n";
		return;
	}
	//Prints board before reading path
	int arr[3][3];
	create_board(arr,puzzle);
	cout << "Before:\n";
	print_board(arr);
	//MBegins moving tiles based on path
	for (char move : path) {
		//Grabs index of 0 in string
		int index = search(puzzle);		
		//Mapping 1d array to 2d
		int x = index % width;
		int y = index / width;
		int curr_index = x+width*y;
		//Based on move, swaps the two tiles
		if (move == 'U') {	
			int state_index = x+width*(y-1);
			puzzle = swap(puzzle,curr_index,state_index);
		}

		else if (move == 'D') {	
			int state_index = x+width*(y+1);
			puzzle = swap(puzzle,curr_index,state_index);
		}

		else if (move == 'L') {	
			int state_index = (x-1)+width*y;
			puzzle = swap(puzzle,curr_index,state_index);
		}

		else {
			int state_index = (x+1)+width*y;
			puzzle = swap(puzzle,curr_index,state_index);
		}
	}
	create_board(arr,puzzle);
	cout << "After:\n";
	print_board(arr);
	
}

//Applies given path to 4x4 puzzle
void apply4x4(string puzzle, string path) {
        //int arr[3][3];
	//Checks if SIZE is set correctly
	if (SIZE == 9) {
		cout << "Change SIZE to 16\n";
		return;
	}
	//Prints board before reading path
        char arr[4][4];
        create_4x4board(arr,puzzle);
	cout << "Before:\n";
        print_4x4board(arr);
	//MBegins moving tiles based on path
        for (char move : path) {
		//Grabs index of 0 in string
                int index = search(puzzle);
		//Mapping 1d array to 2d
                int x = index % width;
                int y = index / width;
                int curr_index = x+width*y;
		//Based on move, swaps the two tiles
                if (move == 'U') {
                        int state_index = x+width*(y-1);
                        puzzle = swap(puzzle,curr_index,state_index);
                }

                else if (move == 'D') {
                        int state_index = x+width*(y+1);
                        puzzle = swap(puzzle,curr_index,state_index);
                }

                else if (move == 'L') {
                        int state_index = (x-1)+width*y;
                        puzzle = swap(puzzle,curr_index,state_index);
                }

                else {
                        int state_index = (x+1)+width*y;
                        puzzle = swap(puzzle,curr_index,state_index);
                }
        }
        create_4x4board(arr,puzzle);
        cout << "After:\n";
        print_4x4board(arr);

}

//Applies given DFS path to puzzle
void applyDFS(string puzzle, string fileName) {
	//Checks if SIZE is set correctly
	if (SIZE == 16) {
		cout << "Change SIZE to 9\n";
		return;
	}
	//Prints 2d matrix before applying path
	int before[3][3];
	create_board(before,puzzle);
	//Grabs the path file of corresponding problem
	char move;
	fstream fin(fileName, fstream::in);
	while (fin >> noskipws >> move) {
		//Grabs index of 0 in string
		int index = search(puzzle);
		if (index == -1) {
			cout << "Something went wrong\n";
			return;
		}
		//Mapping 1d array to 2d
                int x = index % width;
                int y = index / width;
                int curr_index = x+width*y;
		//Based on move, swaps the two tiles
                if (move == 'U') {
			if (y-1 < 0) {
				cout << endl;
				cout << "A\n";
				cout << endl;
				//return;
			}
                        int state_index = x+width*(y-1);
                        puzzle = swap(puzzle,curr_index,state_index);
                }

                else if (move == 'D') {
			if (y+1 >= width) {
				cout << endl;
				cout << "B\n";
				cout << endl;
				//return;
			}
                        int state_index = x+width*(y+1);
                        puzzle = swap(puzzle,curr_index,state_index);
                }

                else if (move == 'L') {
			if (x-1 < 0) {
				cout << endl;
				cout << "C\n";
				cout << endl;
				//return;
			}
                        int state_index = (x-1)+width*y;
                        puzzle = swap(puzzle,curr_index,state_index);
                }

                else if (move == 'R') {
			if (x+1 >= width) {
				cout << endl;
				cout << "D\n";
				cout << endl;
				//return;
			}
                        int state_index = (x+1)+width*y;
                        puzzle = swap(puzzle,curr_index,state_index);
                }
	}
	//Prints board after finished reading path
	int after[3][3];
	create_board(after,puzzle);
	cout << "Before:\n";
	print_board(before);
	cout << "After:\n";
	print_board(after);
}

int main () {
	//Changes dimmensions of the board based on SIZE
	if (SIZE == 16) {
		width = 4;
		height = 4;	
	}

//	cout << "WIDTH: " << width << endl;
	//Goal for 3x3
	string goal = "123456780";
	//Goal for 4x4
	string goal2 = "123456789ABCDEF0";
	//3x3 Problems
	vector<string> s {
		"160273485", 
		"462301587", 
		"821574360", 
		"840156372",
		"530478126", 
		"068314257", 
		"453207186", 
		"128307645", 
		"035684712", 
		"684317025", 
		"028514637", 
		"618273540", 
		"042385671", 
		"420385716", 
		"054672813", 
		"314572680", 
		"637218045", 
		"430621875", 
		"158274036", 
		"130458726"
	};
	//4x4 Problems
	vector<string> s2 {
		"16235A749C08DEBF", 
		"0634217859ABDEFC", 
		"012456379BC8DAEF", 
		"51246A38097BDEFC", 
		"12345678D9CFEBA0",
		"71A92CE03DB4658F", 
		"02348697DF5A1EBC",
		"39A1D0EC7BF86452", 
		"EAB480FC19D56237", 
		"7DB13C52F46E80A9"
	
	};
	
//The size of the path found in BFS
//Used as max depth for IDDFS to see if there is a shorter path then BFS	
	vector<int> BFSPathSize {
		18,
		24,
		28,
		24,
		24,
		22,
		16,
		20,
		26,
		26,
		24,
		24,
		26,
		20,
		22,
		24,
		22,
		20,
		24,
		14
	};

//For loops used to calculate # of extended and paths
/*
	for (int i = 0; i < s.size(); i++) { 	
		if (BFSPathSize.at(i) == 24) {
			cout << s.at(i) << endl;
			IDDFS(s.at(i),goal,BFSPathSize.at(i));
		}
	
	}

*/

/*
	for (string problem : s) {
		cout << problem << endl;
		dfs(problem,goal);
	}
*/

/*

	for (string problem : s2) {
		cout << problem << endl;
		dfs(problem,goal2);
	}
*/


//Fast 3x3 Examples using the different search algorithms
/*
	bfs(s.at(0),goal);
	dfs(s.at(18),goal);
	IDDFS(s.at(6),goal,BFSPathSize.at(6));
*/

//Fast 4x4 Examples using different search algorithms
/*
	bfs(s2.at(0),goal2);
	IDDFS(s2.at(0),goal2,BFSPathSize.at(0));
*/

//Applies all calculated paths from BFS to correlated 3x3 board
/*
	ifstream file("BFSPath.txt");
	string path; 
	int index = 0;
	while (getline(file, path)) {
		//cout << str << endl;
		cout << s.at(index) << endl;
		apply3x3(s.at(index),path);
		index++;
	}
*/

//Applies all easy calculated paths from BFS to correlated 4x4 board	
/*
	ifstream file("4x4BFSPath.txt");
        string path;
        int index = 0;
        while (getline(file, path)) {
		if (index >= 5) break;
                cout << s2.at(index) << endl;
                apply4x4(s2.at(index),path);
                index++;
	}
*/

//Applies all calculated paths from DFS to correlated 3x3 board	
/*
	for (int i = 0; i < 20; i++) {
	//	if (i == 2) continue;
		string fileName = "DFSPath";
		fileName += to_string(i+1);
		fileName += ".txt";
		cout << fileName << endl;
		applyDFS(s.at(i),fileName);
	}
*/


//Applies the found paths from IDDFS to correlated 3x3 board
/*	
        ifstream file("IDDFSPath.txt");
        string path;
        int index = 0;
        while (getline(file, path)) {
                //cout << str << endl;
		if (path == "N/A") {
			index++;
			continue;
		}
                cout << s.at(index) << endl;
                apply3x3(s.at(index),path);
                index++;
        }
*/

//Applies the easy paths from IDDFS to correlated 4x4 board
/*
	ifstream file("4x4IDDFSPath.txt");
        string path;
        int index = 0;
        while (getline(file, path)) {
                if (index >= 5) break;
                cout << s2.at(index) << endl;
                apply4x4(s2.at(index),path);
                index++;
        }
*/
}
