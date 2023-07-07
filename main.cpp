#include <iostream>
#include <string.h>

// Prints the board
void print_board(char board[3][3]) {
    std::cout << "   1 2 3 \n"; 
    for (int i = 0; i < 3; i++) {
        std::cout << i + 1 <<" |";
        for (int j = 0; j < 3; j++) {
            std::cout << board[i][j] << '|';
        }
        std::cout << "\n";
        
        
    }
}

// Updates the board based on whose turn it is
void update_board(char board[3][3], int row, int column, char players_turn) {
    if (players_turn % 2 == 0){
        board[row - 1][column - 1] = 'O';
    }
    else{
        board[row - 1][column - 1] = 'X';
    }
    
}

// Function to check if a player is winning. Insert appropriate player character (O or X)
bool check_if_player_is_winning(char board[3][3], char player_character){
    int k = 0;
    int m = 0;
    // Checking for 3 vertical or horizontal in a row
    for(int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++)
        {
            if(board[i][j] == player_character){
                k ++;
            }
            if(board[j][i] == player_character){
                m ++;
            }
        }
        if(k == 3 || m == 3){
            return true;
        }
        k = 0;
        m = 0;
    }
   
    // Manually checking for diagonal 3 in a row
    if (board[0][0] == player_character && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return true;
    }
    if(board[2][0] == player_character && board[1][1] == board[2][0] && board[1][1] == board[0][2]){
        return true;
    }
    return false;
}

// Checks that the square is empty and that row and column is within the range of the board
bool is_valid_move(char board[3][3], int row, int column) {
    if(row > 3 || row < 1 || column > 3 || column < 1){
        return false;
    }
    if(board[row - 1][column - 1] != ' '){
        return false;
    }
    return true;
}

struct move {
    int row;
    int column;
};

bool integer_input(char * word){
    for (int i = 0; i < strlen(word); i++) {
      if(!isdigit(word[i])){
        return false;
      }
    }
    return true;
}


move get_int_as_move(int player) {
    move m;
    player++;

    bool valid_row = false;
    bool valid_column = false;

    char input[100]; // Array to store user input

    while (!valid_row) {
        std::cout << "Player " << player << ", choose a row: ";
        std::cin >> input;
        valid_row = integer_input(input);
    }
    m.row = atoi(input); // Convert string to int

    while (!valid_column) {
        std::cout << "Player " << player << ", choose a column: ";
        std::cin >> input;
        valid_column = integer_input(input);
    }
    m.column = atoi(input); // Convert string to int

    return m;
}


int main() {
    int player_turn = 0;
    int row = 0;
    int column = 0;
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    // The game loop, which runs until one player is winning, or until nine moves have been played
    while (!(check_if_player_is_winning(board, 'X') || check_if_player_is_winning(board, 'O')) && player_turn < 9)
    {   
        move m1;
        m1.column = 0;
        m1.row = 0;

        print_board(board);
        while (!is_valid_move(board, m1.row, m1.column))
        {
            m1 = get_int_as_move(player_turn%2);

            if(!is_valid_move(board, m1.row, m1.column)){
                std::cout << "Invalid move, enter integer from 1 to 3 that gives an emtpy square \n";
                m1.row = 0;
                m1.column = 0;
            }
        }

        update_board(board, m1.row, m1.column, player_turn);

        // Reset row and column to trigger the while loop
        m1.row = 0;
        m1.column = 0;
        player_turn ++;
    }

    print_board(board);

    if(check_if_player_is_winning(board, 'O')){
        std::cout << "Player 1 wins!";
    }
    else if(check_if_player_is_winning(board, 'X')){
        std::cout << "Player 2 wins!";
    }
    else{
        std::cout << "Draw!";
    }
    return 0;
}