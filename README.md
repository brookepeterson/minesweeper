# minesweeper
Minesweeper Game 
/* 
 * minesweeper.cpp 
 *
 * A text-based minesweeper game that runs in the terminal.
 *
 * COMP11 Fall 2018
 * Modified by: Brooke A. Peterson 
 * Date: November 1, 2018 
 * Game Plan: 
 * 
 * I plan to use two 2D arrays, one that the user can see (user_array) 
 * that contains dashes and past user guesses, and one that the user 
 * cannot see (secret_array) that contains the bombs, as well as any past 
 * user guesses and dashes (if present). I will begin by initializing and 
 * filling the two arrays with their assigned components and then enter 
 * the user into a do-while loop that runs as long as the user has not hit 
 * a mine. The program will prompt the user to enter a row and column, store 
 * the values, and then check if the input is valid (valid_input). If it is,
 * it will check if the input is a bomb (is_mine). If it isn't, it will 
 * calculate the number of bombs around it (calculate_vicinity) and replace 
 * the contents in the user pointer with the number of proximal bombs 
 * (fill_array). It will then print the updated user board (print_board). 
 * This process will continue until the user either wins or loses, in which 
 * case, it will print the secret board if the user loses, and the user board 
 * if the user wins.
 */


