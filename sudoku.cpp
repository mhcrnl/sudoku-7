#include <iostream>
#include <vector>
#include <set>

using namespace std;

void printBoard(vector<vector<int> > * sudoku){
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			if(sudoku->at(i).at(j) == 46){
				cout << ". ";
			}else{
				cout << sudoku->at(i).at(j) << " ";
			}
		}
		cout << endl;
	}
	return;
}
void populateBoard(vector<vector<int> > * sudoku){
	for(int i=0; i<9; i++){
		sudoku->at(0).at(i) = (i+1);
		sudoku->at(1).at(i) = ((i+3)%9+1);
		sudoku->at(2).at(i) = ((i+6)%9+1);
		sudoku->at(3).at(i) = (i+1)%9+1;
		sudoku->at(4).at(i) = (i+4)%9+1;
		sudoku->at(5).at(i) = (i+7)%9+1;
		sudoku->at(6).at(i) = (i+2)%9+1;
		sudoku->at(7).at(i) = (i+5)%9+1;
		sudoku->at(8).at(i) = (i+8)%9+1;
	}
	return;
}
bool verifySudoku(vector<vector<int> > * sudoku){
	
	for(int i=0; i<9; i++){
		bool horizontalCheck[9] = { 0 };
		bool verticalCheck[9] = { 0 };
		for(int j=0; j<9; j++){
			if(horizontalCheck[sudoku->at(i).at(j)-1] || verticalCheck[sudoku->at(j).at(i)-1]){
				return false;
			}else{
				horizontalCheck[sudoku->at(i).at(j)-1] = true;
				verticalCheck[sudoku->at(j).at(i)-1] = true;
			}

		}
	}
	for(int m=0; m<3; m++){
		for(int n=0;n<3;n++){
			bool boxCheck[9] = { 0 };
			for(int i=0;i<3;i++){
				for(int j=0; j<3; j++){
					if(boxCheck[sudoku->at(i+m*3).at(j+n*3)-1]){
						return false;
					}else{
						boxCheck[sudoku->at(i+m*3).at(j+n*3)-1] = true;
					}
				}
			}
		}
	}
	return true;
}
int solver(vector<vector<int> > *sudoku){
    int solutions = 0;
    int index = 0;
    while(sudoku->at(index%9).at(index/9) != '.'){
        index++;
        if(index == 81){
            cout << "Solution : " << endl;
            printBoard(sudoku);
            cout << endl << endl;
            return 1;
        }
    }
    int i=index%9, j=index/9;
    for(int l = 1; l<=9; l++){  // find a a number that can fit
        bool testing = true;
        for(int n = 0; n<9; n++){ // i=4  j=6;
            int box_x = (i/3)*3+n%3;
            int box_y = (j/3)*3+n/3;
            if((sudoku->at(i).at(n) == l) || (sudoku->at(n).at(j) == l ) || (sudoku->at(box_x).at(box_y)==l)){
                testing = false; n = 9;
            }
        }
        if(testing){
            sudoku->at(i).at(j) = l;
            
                solutions += solver(sudoku);
            
            sudoku->at(i).at(j) = '.';
        }
    }
    return solutions;
}

void swapRows(vector<vector<int> > *vec, int row1, int row2){
    vector<int> temp = vec->at(row1);
    vec->at(row1) = vec->at(row2);
    vec->at(row2) = temp;
}
void swapCols(vector<vector<int> > *vec, int col1, int col2){
    int temp;
    for(int i=0; i<9; i++){
        temp = vec->at(i).at(col1) ;
        vec->at(i).at(col1) = vec->at(i).at(col2);
        vec->at(i).at(col2) = temp;
    }
}
void makePuzzle(vector<vector<int> > *vec){
	cout << "\n\n----------making a board------------\n\n";
	int i=5;
	for(int i=0; i<9; i++){
		if(i%2==0){
			vec->at(2).at(i) = '.';
			vec->at(7).at(i) = '.';
		}else{
			vec->at(3).at(i) = '.';
			vec->at(4).at(i) = '.';
		}
		vec->at(i).at(i) = '.';
		vec->at(i).at(8-i) = '.';
	}
	swapCols(vec, 0, 2);
	swapCols(vec, 3, 5);
	swapRows(vec, 1, 2);
	swapRows(vec, 7, 6);

}

int main(){
	vector<vector<int> > sudoku(9, vector<int>(9,0));
	populateBoard(&sudoku);
	printBoard(&sudoku);
	cout << endl << "Board test : " << verifySudoku(&sudoku) << endl;
	cout << endl << "Breaking the board: " << endl;
	sudoku[8][8] = 3;
	printBoard(&sudoku);
	cout << endl << "Broken board test : " << verifySudoku(&sudoku) << endl;
	sudoku[8][8] = 8;
	
	makePuzzle(&sudoku);	
	printBoard(&sudoku);

	cout << "\n\nTrying to solve it now! \n\n";

	cout << "\n\nSolve value : " << solver(&sudoku) << endl << endl;



}