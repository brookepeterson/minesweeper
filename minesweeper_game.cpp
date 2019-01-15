
#include <iostream>
#include <time.h> 
#include <cstdlib>

using namespace std;

/* Set random seed */
#ifdef TESTING
#define RANDOMSEED 1
#else
#define RANDOMSEED time(NULL)
#endif

//declare global variables 
const int NUM_ROWS = 9;
const int NUM_COLS = 9;

//declare functions 
void initialize_user_array(char user_array[NUM_ROWS][NUM_COLS]);
void initialize_secret_array(char secret_array[NUM_ROWS][NUM_COLS]);
bool valid_input(int row, int col, char secret_array[NUM_ROWS][NUM_COLS]);
bool is_hit(int row, int col, char user_array[NUM_ROWS][NUM_COLS], 
    char secret_array[NUM_ROWS][NUM_COLS]);
bool user_win(char secret_array[NUM_ROWS][NUM_COLS]);
int calculate_vicinity(int row, int col, char secret_array[NUM_ROWS][NUM_COLS]);
bool is_mine(int row, int col, char secret_array[NUM_ROWS][NUM_COLS]);
void print_board(char array[NUM_ROWS][NUM_COLS]);
void fill_array(int row, int col, char user_array[NUM_ROWS][NUM_COLS], 
    char secret_array[NUM_ROWS][NUM_COLS]);

int main() {
    //initialize variables and arrays  
    srand(RANDOMSEED); 
    char secret_array[NUM_ROWS][NUM_COLS];
    char user_array[NUM_ROWS][NUM_COLS];
    int user_row, user_col = 0; 

    initialize_secret_array(secret_array); //load secret_array
    initialize_user_array(user_array); //load user_array
    print_board(user_array); //print initial board 
    
    do { //do while loop that executes as long as user hasn't hit a mine
        cout << "Enter the row and column of the square to uncover: "; 
        cin >> user_row >> user_col; 
        //prompt user over again until it's a valid input
        while (valid_input(user_row, user_col, secret_array) == false) {
            cout << "Enter the row and column of the square to uncover: "; 
            cin >> user_row >> user_col; 
        } 
        //if user loses, exit program, otherwise follow is_hit accordingly
        if (is_hit(user_row, user_col, user_array, secret_array) == false) {
            return 0; 
        }
        //if user wins, exit program 
        if (user_win(secret_array) == true) {
            cout << "GAME OVER. YOU WON!" << endl;
            return 0; 
        }
    } while (is_mine(user_row, user_col, secret_array) == false);
    return 0;
}

/*
 * initialize_secret_array -- fill in secret_array with random mines 
   and rest of spaces with '-'
 *   args: secret array 
 *   rets: nothing
 *   note: secret array: array that user cannot see that contains bombs 
 */
void initialize_secret_array(char secret_array[NUM_ROWS][NUM_COLS]) {
    
    for (int i = 0; i < NUM_ROWS; ++i)
    {
        for (int j = 0; j < NUM_COLS; ++j)
        {
            //fills array with x 30% of time
            if (rand() % 100 < 30) {
                secret_array[i][j] = 'x';
            //other times, fills with dash 
            } else {
                secret_array[i][j] = '-';
            }
        } 
    }
}

/*
 * initialize_user_array -- fill in user_array with '-' 
 *   args: user array 
 *   rets: nothing
 *   note: user array: array that user can see with dashes
 */
void initialize_user_array(char user_array[NUM_ROWS][NUM_COLS]) {
    for (int i = 0; i < NUM_ROWS; ++i)
    {
        for (int j = 0; j < NUM_COLS; ++j)
        {
            user_array[i][j] = '-';
        }
    }
}


/*
 * valid_input -- checks to see if user input is valid 
 *   args: user inputted value (row, col), secret array 
 *   rets: true or false 
 *   note: secret array: array that user cannot see that contains bombs 
 */
bool valid_input(int row, int col, 
    char secret_array[NUM_ROWS][NUM_COLS]) { 
    //when row is out of bounds 
    if (row < 0 || row > 8 || col < 0 || col > 8) {
        cout << "Bad input. Row and col must be >= 0 and < 9." << endl; 
        return false; 
    //when row is not a dash or an x (aka when it is a number), means
    //that spot has already been guessed 
    } else if (secret_array[row][col] != '-' 
        && secret_array[row][col] != 'x') {
        cout << "Bad input. Select another square." << endl; 
        return false; 
    } else {
        return true; 
    }
    
}

/*
 * is_hit -- checks to see if user has made a correct hit 
 *   args: user inputted value (row, col), user array, and secret array 
 *   rets: true or false 
 *   note: if user has made a hit, fills array location with number of 
           proximal bombs and prints out the user array
           if user has hit a bomb, prints out secret array and exits 
           main program 
 */
bool is_hit(int row, int col, char user_array[NUM_ROWS][NUM_COLS], 
    char secret_array[NUM_ROWS][NUM_COLS]) {

    //fills with number of proximal bombs when not a bomb 
    if (is_mine(row, col, secret_array) == false) {
        fill_array(row, col, user_array, secret_array);
        print_board(user_array);
        return true;
    //otherwise, it is a bomb and user loses 
    } else {
        print_board(secret_array); 
        cout << "GAME OVER. YOU LOST!" << endl;
        return false;
    }
}


/*
 * user_win -- checks to see if user has won the game
 *   args: user inputted value (row, col), secret array 
 *   rets: true or false 
 *   note: if user has won, prints winning statement as well as returning true 
           secret array: array that user cannot see that contains bombs 
 */
bool user_win(char secret_array[NUM_ROWS][NUM_COLS]) {
    for (int i = 0; i < NUM_ROWS; ++i)
    {
        for (int j = 0; j < NUM_COLS; ++j)
        {
            //if there are dashes left in the array, user has not yet won
            if (secret_array[i][j] == '-') {
                return false; 
            } 
        }
    }
    return true;
}

/*
 * calculate_vicinity -- calculates number of bombs in vicinity of one 
    location on board
 *   args: user inputted value (row, col), secret array 
 *   rets: number of proximal bombs (integer) 
*    note: secret array: array that user cannot see that contains bombs 
 */
int calculate_vicinity(int row, int col, 
    char secret_array[NUM_ROWS][NUM_COLS]) {
    int counter = 0; 
    if (row + 1 < 9 && is_mine(row + 1, col, secret_array) == true) {
        counter ++; //checks spot to right of input
    } 
    if (row - 1 >= 0 && is_mine(row - 1, col, secret_array) == true) {
        counter ++; //checks spot to left of input
    } 
    if (col + 1 < 9 && is_mine(row, col + 1, secret_array) == true) {
        counter ++; //checks spot above input 
    } 
    if (col - 1 >= 0 && is_mine(row, col - 1, secret_array) == true) {
        counter ++; //checks spot below input 
    } 
    if (row - 1 >= 0 && col - 1 >= 0 
        && is_mine(row - 1, col - 1, secret_array) == true) {
        counter ++; //checks bottom left corner of input
    } 
    if (row - 1 >= 0 && col + 1 < 9 
        && is_mine(row - 1, col + 1, secret_array) == true) {
        counter ++; //checks top left corner of input 
    }
    if (row + 1 < 9 && col - 1 >= 0 
        && is_mine(row + 1, col - 1, secret_array) == true) {
        counter ++; //checks bottom right corner of input 
    } 
    if (row + 1 < 9 && col + 1 < 9 
        && is_mine(row + 1, col + 1, secret_array) == true) {
        counter ++; //checks top right corner of input 
    } 
    return counter; //total number of proximal bombs 
}

/*
 * is_mine -- checks to see if user input is a bomb/mine
 *   args: user inputted value (row, col), secret array
 *   rets: true or false 
 *   note: secret array: array that user cannot see that contains bombs 
 */
bool is_mine(int row, int col, char secret_array[NUM_ROWS][NUM_COLS]) {
    if (secret_array[row][col] == 'x') {
        return true; 
    } else {
        return false;
    }
}

/*
 * print_board -- prints array as a board 
 *   args: any character array 
 *   rets: nothing 
 *   acts: a) Loops through each row and column of array 
           b) Prints each character in array separated by space 
 */
void print_board(char array[NUM_ROWS][NUM_COLS]) {

    //prints number row bar on top 
    cout << " ";
    for (int i = 0; i < NUM_ROWS; ++i) {
        cout << " " << i;
    }
    cout << endl;

    for (int i = 0; i < NUM_ROWS; ++i)
    {
        cout << i << " "; //prints number column bar on side 
        for (int j = 0; j < NUM_COLS; ++j)
        {
            cout << array[i][j] << " "; //prints every element in array 
        }
        cout << endl; 
    }
}

/*
 * fill_array -- fills inputted array location with number of proximal bombs 
 *   args: user inputted value (row, col), secret array, and user array 
 *   rets: nothing 
 *   acts: a) Calls calculate_vicinity to return integer of proximal bombs 
           b) Converts integer to character 
           c) Inserts character into inputted value
*    note: secret array: array that user cannot see that contains bombs
           user array: array that user can see that contains past guesses   
 */
void fill_array(int row, int col, char user_array[NUM_ROWS][NUM_COLS], 
    char secret_array[NUM_ROWS][NUM_COLS]) {
    //replaces contents of arrays with number of proximal bombs in character 
    //form
    secret_array[row][col] = calculate_vicinity(row, col, secret_array) + '0'; 
    user_array[row][col] = calculate_vicinity(row, col, secret_array) + '0';
}
  
