#include <iostream>
#include <sstream>
#include <cstdlib>
#include "battleship.hpp"

//instruction of the game
void help()
{
    std::cout << "\nInstruction to the Game:\n";
    std::cout << "- The program generate board and ships, the user hits it.\n";    
    std::cout << "- To become the winner of Battleship you must be able to sink all ships.\n";
    std::cout << "- There are 1 four-dimensional ship, 2 three-dimensional ship, 3 two-dimensional ship and 4 one-dimensional ship.\n";
    std::cout << "- Enter your hit in this form - number.number (e.g. 1.2). Your input number have to be between 0 to 9.\n";
    std::cout << "- First number is row, second number is column.\n"; 
    std::cout << "- The ship is marked with the symbol 'X'.\n";
    std::cout << "- The miss hit is marked with the symbol '*'.\n";
    std::cout << "- The injured ship is marked with the symbol 'X'.\n";
    std::cout << "- The sank ship is marked with the symbol 'x'.\n";
    std::cout << "- If you want to stop the game input 'e'.\n";
    std::cout << "- If you want to read instruction again input 'h'.\n";
    std::cout << "- If you want to show generation board input 's'.\n";
    std::cout << "Let's play.\n\n";
}
//preface text before game
void game_preface() 
{
    std::cout << "\n-------------------------------------------------------\n";
    std::cout << "|                  Battleship Game                    |\n";
    std::cout << "-------------------------------------------------------\n";
    std::cout << "                 Welcome to the game.                  \n";
    help();
}
//print board
void print_board(char a[10][10]) 
{
    for (int i = 0; i < 10; ++i) {
        if (0 == i) std::cout << "  ";
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << i << " ";
        for (int j = 0; j < 10; ++j) {
            std::cout << a[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
//function checks area is empty or not
bool check_empty_area(char gen_board[10][10], int row, int row_up, int col, int row_down,const int& ship,const int& is_row_col) 
{
    bool b = true;
    for (int i = row - row_up; i <= row + row_down; ++i) { 
        for (int j = col - 1; j < col + ship + 1; ++j) {
            if (2 == is_row_col && gen_board[j][i] != '-') {
                b = false;
                break;
            } else if (1 == is_row_col && gen_board[i][j] != '-') {
                b = false;
                break;
            }
        }
    }
    return b;
}   
//check if area is empty or not for the appropriate direction depends on check_empty_area function's return value
bool is_empty_area(char gen_board[10][10], int row, int col, const int& ship, const int& is_row_col) 
{
    bool b = true;
    if (2 == is_row_col) {
        int t = col;
        col = row;
        row = t;
    }
    if (0 == row) {
       b = check_empty_area (gen_board, row, 0, col, 1, ship, is_row_col); 
    } else if (9 == row) {
       b = check_empty_area (gen_board, row, 1, col, 0, ship, is_row_col);
    } else {
       b = check_empty_area (gen_board, row, 1, col, 1, ship, is_row_col);
    }
    return b;
}
//find row, col where can gnerate ship
void find_row_col(char gen_board[10][10], int& row, int& col, const int& ship_length, const int& is_row_col, const int& row_or_col) 
{
    while ((10 - col) < ship_length || is_empty_area(gen_board, row, col, ship_length, is_row_col) != true) {
        row = rand() % 10;
        col = rand() % 10;
    }
}
//generates ships randomly
void gen_ship(char gen_board[10][10]) 
{
    srand(time(NULL));
    int ship_length = 4;
    int ship_count = 1;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < ship_count; ++j) {
            int row = rand() % 10;
            int col = rand() % 10;
            int is_row_col = rand() % 2 + 1;
            if (1 == is_row_col) { //for generating in row
                find_row_col(gen_board, row, col, ship_length, is_row_col, col);
                for (int l = col; l < col + ship_length; ++l) {
                    gen_board[row][l] = 'X';
                }
            } else if (2 == is_row_col) { //for generating in col
                find_row_col(gen_board, row, col, ship_length, is_row_col, row);
                for (int l = row; l < row + ship_length; ++l) {
                    gen_board[l][col] = 'X';
                }
            }
        }
        ++ship_count;
        --ship_length;
   }
}
//get checked input for row and col 
void get_checked_input(char gen_board[10][10], int& row, int& col) 
{
    bool b = false;
    std::string str("");
    std::cout << "Input your hit.\n";
    getline(std::cin,str);
    do {
        b = false;
        if (catch_error(str,gen_board)) {
            b = true;
        }
    } while (b);
    std::stringstream num1;
    num1 << str[0];
    num1 >> row;
    std::stringstream num2;
    num2 << str[2];                  
    num2 >> col;
}
//checks input of one length according to the program rule
bool check_one_size_input(std::string& str, char gen_board[10][10]) 
{
    bool b = false;   
    while (1 == str.size()) {
        switch (str[0]) 
        { 
            case 'e': int e;
                      _Exit(e);
                      b = true;
                      break;
            case 'h': help();
                      b = true;
                      break;
            case 's': print_board(gen_board);
                      break;
                      b = true;
            default: std::cout << "Incorrect input.\n";
        }      
        std::cout << "Input your hit.\n";
        getline(std::cin,str);
   }
   return b;
}
//input hit and catch error
bool catch_error(std::string& str, char gen_board [10][10]) 
{
    bool b = false;
    int result = 0;
    do {
        b = false;
        while ((1 != str.size()) && (3 != str.size())) {
                std::cout << "Incorrect input.\n";
                std::cout << "Please input number between 0 to 9 in this form - number.number (e.g. 1.2).\n";
                getline(std::cin,str);
        }
        if (check_one_size_input(str,gen_board) == true) {
                b = true;
        }
        if ((str[0] < '0' || str[0] > '9') || (str[1] != '.') || (str[2] < '0' || str[2] > '9')) {
            std::cout << "Incorrect input.\n";
            std::cout << "Please input number between 0 to 9 in this form - number.number (e.g. 1.2).\n";
            b = true;
            std::cout << "Input your hit.\n";
            getline(std::cin, str);
            break;
        }
    } while (b);
    return b;
}
//check if ship has been sank
bool is_sunk(char gen_board[10][10], char player_board[10][10], int row, int col, int& dir) 
{
    int count = 1;
    dir = 0; //vertical
    while ('X' == gen_board[row - 1][col] && row - 1 >= 0) {
        if ('X' == player_board[row - 1][col]) {
            ++count;
            --row;
        } else {
            return false;
        }
    }
    while ('X' == gen_board[row + 1][col] && row + 1 <= 9) {
        if ('X' == player_board[row + 1][col]) {
            ++count;
            ++row;
        } else {
            return false;
        }
    }
    if (1 == count) {
        while ('X' == gen_board[row][col - 1] && col - 1 >= 0) {
            if ('X' == player_board[row][col - 1]) {
                --col;
            } else {
                  return false;
            }
        }
        while ('X' == gen_board[row][col + 1] && col + 1 <= 9) {
            if ('X' == player_board[row][col + 1]) {
                ++col;
            } else {
                  return false;
            }
        }
        dir = 1; // horizonal
    }
    return true;  
}
//calls fill_around funtion for the appropriate direction
void call_fill_around_sunk_ship(char player_board[10][10], int row, int col, int& dir) 
{
    if (0 == dir) {
        fill_around_sunk_ship (player_board, row, 1, col, 0);
    } else if (1 == dir) {
        fill_around_sunk_ship (player_board, row, 0, col, 1);
    }
}

//check around sunk ship and fill around it *
void fill_around_sunk_ship(char player_board[10][10], int row, int row_up_down, int col, int col_up_down) 
{
    while ('X' == player_board[row][col]) {
        player_board[row][col] = 'x';
        for (int i = row - 1; i <= row + 1; ++i) {
            for (int j = col -1; j <= col + 1; ++j) {
                if (i < 0 || i > 9 || j < 0 || j > 9) {
                    continue;
                }
                if ('-' == player_board[i][j]) {
                    player_board[i][j] = '*';
                }      
            }
        } 
        if ('X' == player_board[row - row_up_down][col - col_up_down]) {
            row = (1 == row_up_down) ? --row : row;
            col = (1 == col_up_down) ? --col : col;
        } else if ('X' == player_board[row + row_up_down][col + col_up_down]) {
            row = (1 == row_up_down) ? ++row : row;
            col = (1 == col_up_down) ? ++col : col;
        }
    }
}
//run program
void run () 
{
    int row = 0;
    int col = 0;
    char gen_board[10][10] = {}; 
    char player_board[10][10] = {};
    for (int i = 0; i < 10; ++i) {
        for (int  j = 0; j <= 10; ++j) {
            gen_board[i][j] = '-';
            player_board[i][j] = '-';
        }
    }
    int ship_count = 0;
    int dir = -1;
    std::string s("");
    gen_ship(gen_board);
    game_preface();
    while (ship_count < 20) {
        get_checked_input(gen_board,row,col);
        switch (gen_board[row][col])
        {
            case '-': if (player_board[row][col] == '*') {
                          std::cout << "Duplicate value.\n";
                      }
                      player_board[row][col] = '*';
                      std::cout << "You missed!\n";
                      break;
            case 'X': if (player_board[row][col] == 'x') {
                          std::cout << "The ship is already sunk!!!!\n";
                          std::cout << "Try again.\n";
                          break;
                      }
                      player_board[row][col] = 'X';
                      ++ship_count;
                      if (is_sunk (gen_board, player_board, row, col, dir)  == true) {
                          std::cout << "The ship is sunk.\n";
                          call_fill_around_sunk_ship(player_board, row, col, dir);
                      } else {
                          std::cout << "The ship is injured.\n";
                      }
                      break;
        }
        print_board(player_board);
        if (ship_count == 20) {
            std::cout << "\n-------YOU WIN-------\n\n";
        }
    }
}
