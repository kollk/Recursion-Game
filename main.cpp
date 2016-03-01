#include <iostream>
#include <sstream>
using namespace std;

void print(char grid[10][10]){
    cout << " ";
    for(int c = 0; c < 10; c++)
        cout << c;
    cout << endl;
    for(int r = 0; r < 10; r++) {
        cout << r;  //row header
        for(int c = 0; c < 10; c++) {
            cout << grid[r][c] ;
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
}

void radiationFlood(char grid[10][10], int contaminatedRow, int contaminatedCol){
    if(contaminatedRow < 0 || contaminatedCol < 0 || contaminatedRow >= 10 || contaminatedCol >= 10) {
        return;   //went out of bounds - done
    }
    if(grid[contaminatedRow][contaminatedCol] != ' ') {
        return;   //hit a filled square - done
    }

    //no need to copy grid - we want to change the original
    grid[contaminatedRow][contaminatedCol] = '.';

    //neighbor cells
    radiationFlood(grid, contaminatedRow, contaminatedCol-1);  //left
    radiationFlood(grid, contaminatedRow, contaminatedCol+1);  //right
    radiationFlood(grid, contaminatedRow-1, contaminatedCol);  //up
    radiationFlood(grid, contaminatedRow+1, contaminatedCol);  //down
    radiationFlood(grid, contaminatedRow+1, contaminatedCol+1); // diagonal
    radiationFlood(grid, contaminatedRow-1, contaminatedCol-1); //diagonal
    radiationFlood(grid, contaminatedRow-1, contaminatedCol+1);// diagonal
    radiationFlood(grid, contaminatedRow+1, contaminatedCol-1); //diagonal
}


int areaContaminated(char grid[10][10]){
    int total = 0;
    for(int row = 0; row < 10; row++){
        for(int column = 0; column < 10; column++){
            if(grid[row][column] == '.'){
                total++;
            }
        }
    }
    return total;
}


void checkLeak(char grid[10][10], int contaminatedRow, int contaminatedCol){
    radiationFlood(grid, contaminatedRow, contaminatedCol);
    print(grid);
    if(grid[0][0] == '.'){
        cout << "Not safe" << endl;
    }
    else{
        cout << "Safe" << endl;
    }
    cout << "Contaminated area: " << areaContaminated(grid) << endl;
}

int main()
{
    char grid[10][10] =
    {{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}};

    cout << "Enter row & col of contaminated point:" << endl;
    int cRow = 0;
    int cCol = 0;
    cin >> cRow >> cCol;
    grid[cRow][cCol] = ' ';

    //-------------------Enter wall stuff-------------------
    cout << "Enter row & col of wall points type 0 0 to indicate end of input:" << endl;
    int wall = 1;
    int wall2 = 1;

    while(wall != 0 || wall2 != 0){
        cin >> wall;
        cin >> wall2;
        grid[wall][wall2] = '#';
        grid[0][0] = ' ';
    }

    checkLeak(grid, cRow, cCol);

    return 0;
}
