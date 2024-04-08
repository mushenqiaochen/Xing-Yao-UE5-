#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

int main() {
    const int rows = 7; 
    const int columns = 6;
    const int hold_box_columns = 7; 
    
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(columns, 0));
    std::vector<int> count(6, 0); 

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);
    
    for (int i = 0; i < rows - 2; ++i) { 
        for (int j = 0; j < columns; ++j) {
            int num = dis(gen); 
            while (count[num - 1] >= 6) { 
                num = dis(gen);
            }
            matrix[i][j] = num;
            count[num - 1]++;
        }
    }
    

    std::fill(matrix[rows - 2].begin(), matrix[rows - 2].end(), -1);
    
    
    std::fill(matrix[rows - 1].begin(), matrix[rows - 1].end(), 0);
    
   
    std::cout << "Initial Matrix:" << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (matrix[i][j] == -1) { 
                std::cout << "- ";
            } else {
                std::cout << matrix[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
    
  
    while (true) {
        int row, column;
        
       
        std::cout << "Enter row number (1-6): ";
        std::cin >> row;
        
        if (row < 1 || row > 6) {
            std::cout << "Invalid input! Row number must be between 1 and 6." << std::endl;
            continue;
        }

        std::cout << "Enter column number (1-6): ";
        std::cin >> column;
        
        if (column < 1 || column > 6) {
            std::cout << "Invalid input! Column number must be between 1 and 6." << std::endl;
            continue;
        }
        
      
        int num = matrix[row - 1][column - 1];
        auto it = std::find(matrix[rows - 1].begin(), matrix[rows - 1].end(), 0);
        if (it != matrix[rows - 1].end()) {
            *it = num;
            matrix[row - 1][column - 1] = 0;
            count[num - 1]--; 
        } else {
            std::cout << "Hold box is full! Game Over." << std::endl;
            break;
        }
        
        std::sort(matrix[rows - 1].begin(), matrix[rows - 1].end(), std::greater<int>());
        for (int i = 0; i <= hold_box_columns - 3; ++i) {
            if (matrix[rows - 1][i] == matrix[rows - 1][i + 1] && matrix[rows - 1][i] == matrix[rows - 1][i + 2]) {
                matrix[rows - 1][i] = matrix[rows - 1][i + 1] = matrix[rows - 1][i + 2] = 0;
            }
        }
        
        
        std::cout << "Updated Matrix:" << std::endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (matrix[i][j] == -1) { 
                    std::cout << "- ";
                } else {
                    std::cout << matrix[i][j] << " ";
                }
            }
            std::cout << std::endl;
        }
    }
    
    return 0;
}
