#include <iostream>
#include <vector>

// Class to represent the Connect Four game
class ConnectFour {
public:
    // Constructor initializes the game grid and other variables
    ConnectFour() : grid(ROWS, std::vector<char>(COLS, ' ')), currentPlayer(0), gameOver(false) {}

    // Method to start the game loop
    void play() {
        int turn = 0; // Track the number of turns
        while (turn < ROWS * COLS && !gameOver) { // Continue until all spaces are filled or a winner is found
            printGrid(); // Print the current game grid
            if (playersTurn()) { // Allow the current player to take their turn
                gameOver = checkWinner(); // Check if there is a winner after the turn
                turn++; // Increment the turn count
            }
        }
        printGrid(); // Print the final grid state
        announceResult(turn); // Announce the result of the game
    }

private:
    static const int ROWS = 6; // Number of rows in the grid
    static const int COLS = 7; // Number of columns in the grid
    std::vector<std::vector<char>> grid; // 2D vector to represent the game grid
    int currentPlayer; // Variable to track whose turn it is (0 or 1)
    bool gameOver; // Flag to indicate if the game is over

    // Method to print the current state of the game grid
    void printGrid() {
        std::cout << "\n    Connect Four Game \n";
        for (const auto& row : grid) { // Loop through each row
            for (char cell : row) { // Loop through each cell in the row
                std::cout << "| " << cell << " "; // Print the cell
            }
            std::cout << "|\n-----------------------------\n"; // Print row separator
        }
        std::cout << "  1   2   3   4   5   6   7\n"; // Print column numbers
    }

    // Method to handle player input and place their piece
    bool playersTurn() {
        int column; // Variable to store the player's chosen column
        std::cout << "Player " << (currentPlayer + 1) << " (" << (currentPlayer == 0 ? 'X' : 'O') << "):\n";
        std::cout << "Enter a number 1 - 7: ";
        
        while (true) {
            std::cin >> column; // Get the player's input
            column--; // Adjust for 0-based index
            
            // Validate the input
            if (column < 0 || column >= COLS) {
                std::cout << "Number is invalid! Please try again!\n"; // Invalid input message
                continue; // Continue to prompt for input
            }

            // Place the piece in the lowest available row
            for (int r = ROWS - 1; r >= 0; r--) { // Loop from bottom to top of the column
                if (grid[r][column] == ' ') { // Check if the cell is empty
                    grid[r][column] = (currentPlayer == 0 ? 'X' : 'O'); // Place the player's piece
                    currentPlayer = (currentPlayer + 1) % 2; // Switch player
                    return true; // Successfully placed the piece
                }
            }
            std::cout << "This column is full, please select another\n"; // Column full message
        }
    }

    // Method to check for a winner
    bool checkWinner() {
        return checkHorizontal() || checkVertical() || checkDiagonal(); // Check all win conditions
    }

    // Method to check for horizontal wins
    bool checkHorizontal() {
        for (int r = 0; r < ROWS; r++) { // Loop through each row
            for (int c = 0; c < COLS - 3; c++) { // Loop through columns (stop 3 before the end)
                // Check if there are 4 pieces in a row
                if (grid[r][c] != ' ' && 
                    grid[r][c] == grid[r][c + 1] && 
                    grid[r][c] == grid[r][c + 2] && 
                    grid[r][c] == grid[r][c + 3]) {
                    return true; // Winner found
                }
            }
        }
        return false; // No horizontal winner
    }

    // Method to check for vertical wins
    bool checkVertical() {
        for (int c = 0; c < COLS; c++) { // Loop through each column
            for (int r = 0; r < ROWS - 3; r++) { // Loop through rows (stop 3 before the end)
                // Check if there are 4 pieces in a column
                if (grid[r][c] != ' ' && 
                    grid[r][c] == grid[r + 1][c] && 
                    grid[r][c] == grid[r + 2][c] && 
                    grid[r][c] == grid[r + 3][c]) {
                    return true; // Winner found
                }
            }
        }
        return false; // No vertical winner
    }

    // Method to check for diagonal wins (both directions)
    bool checkDiagonal() {
        // Check for diagonal wins from bottom-left to top-right
        for (int r = 0; r < ROWS - 3; r++) {
            for (int c = 0; c < COLS - 3; c++) {
                if (grid[r][c] != ' ' && 
                    grid[r][c] == grid[r + 1][c + 1] && 
                    grid[r][c] == grid[r + 2][c + 2] && 
                    grid[r][c] == grid[r + 3][c + 3]) {
                    return true; // Winner found
                }
            }
        }
        // Check for diagonal wins from bottom-right to top-left
        for (int r = 0; r < ROWS - 3; r++) {
            for (int c = 3; c < COLS; c++) {
                if (grid[r][c] != ' ' && 
                    grid[r][c] == grid[r + 1][c - 1] && 
                    grid[r][c] == grid[r + 2][c - 2] && 
                    grid[r][c] == grid[r + 3][c - 3]) {
                    return true; // Winner found
                }
            }
        }
        return false; // No diagonal winner
    }

    // Method to announce the result of the game
    void announceResult(int turn) {
    
        printGrid(); // Show the final grid state

    // Check if the game is a tie or if there’s a winner
    if (turn == ROWS * COLS && !gameOver) {
        std::cout << "It's a tie!" << std::endl;
    } else {
        std::cout << "Congratulations Player " << ((turn + 1) % 2 + 1) << " you are the winner!"<< std::endl;
    }
}

};

int main() {
    ConnectFour game; // Create an instance of the game
    game.play(); // Start the game
    return 0;
}
