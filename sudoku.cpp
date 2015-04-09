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
/*

1 2 3 4 5 6 7 8 .
4 5 6 . 8 9 1 2 . 
. . . . . . . . . 
2 3 4 . 6 7 8 9 . 
5 6 7 . 9 1 2 3 . 
8 9 1 . 3 4 5 6 . 
3 4 5 . 7 8 9 1 . 
. . . . . . . . . 
9 1 2 . 4 5 6 7 . 


*/
// 2, 5
bool boxVerifier(vector<vector<int> > *vec, int x, int y){
	cout << "Verifier" << endl;
	set<int> test;
	int rowFactor = (x)/3;
	int colFactor = (y)/3;
	for(int i=3*rowFactor; i<(3*(rowFactor+1)); i++){
		for(int j=3*colFactor; j<(3*(1+colFactor)); j++){
			if(vec->at(i).at(j) != '.'){
				if(test.find(vec->at(i).at(j)) == test.end()){
					test.insert(vec->at(i).at(j));
				}else{
					return false;
				}
			}
		}
	}
	return true;
}


bool solverHelper(vector<vector<int> > *vec, vector<set<int> > *rows, vector<set<int> > *cols, int cur_row){
    int solutions = 0;
    int count =0;
    for(int i=0; i<9; i++){
    	count += rows->at(i).size();
    }
    cout<< "Count " << count << endl;
    if(count == 78){ 
    	printBoard(vec);
    	return 1;
    }
    for(int i=cur_row; i<9; i++){ // rows
    	//if(i == 2){return 5;}
	    if(rows->at(i).size() < 9){	
	        for(int j=0; j<9; j++){ // columns
	        	cout << "r : " << i << "    c : " << j ;
	            if(vec->at(i).at(j) == '.'){ //Empty cell
	            	cout << "   empty ";
	                for(int l = 0; l<9; l++){  // find a a number that can fit
	                    if( (rows->at(i).find(l+1)==rows->at(i).end()) && (cols->at(j).find(l+1)==cols->at(j).end())){
	                    	//if(boxVerifier(vec, i, j)){
		                    	cout << "Filling with " << l+1 << "   " << endl;
		                        rows->at(i).insert(l+1); 
		                        cols->at(j).insert(l+1);
		                        vec->at(i).at(j) = l+1;
		                        if(solverHelper(vec, rows, cols, i)){
		                        	return true;
		                        }
		                       cout << "Removing " << l+1 << "    " << endl;
		                        rows->at(i).erase(rows->at(i).find(l+1)); 
		                        cols->at(j).erase(cols->at(j).find(l+1));
		                        vec->at(i).at(j) = '.';
		                    //}
	                    }else if(l==8){
	                    	return 0;
	                    }
	                }

	            }cout << endl;
	        }
	    }
    }

    return false;
}

bool solveSudoku(vector<vector<int> > *vec){
	vector<set<int> > rows, cols;
	for(int i=0; i<9; i++){
		set<int> temp;
		rows.push_back(temp); cols.push_back(temp);
	}
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			if(vec->at(i).at(j) != '.'){
				rows.at(i).insert(vec->at(i).at(j));
			}
			if(vec->at(j).at(i) != '.'){
				rows.at(j).insert(vec->at(j).at(i));
			}
		}
	}
	return solverHelper(vec, &rows, &cols, 0);
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
		vec->at(2).at(i) = '.';
		vec->at(7).at(i) = '.';
		vec->at(i).at(3) = '.';
		vec->at(i).at(8) = '.';
	}
	swapCols(vec, 0, 2);

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

	cout << "\n\nSolve value : " << solveSudoku(&sudoku) << endl << endl;



}