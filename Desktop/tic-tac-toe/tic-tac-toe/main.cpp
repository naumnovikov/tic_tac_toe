#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <string>

void printMatrix(std::vector<std::vector<std::string>>& matr); //done

void printIntroduction(); //done

void makeMove(std::vector<std::vector<std::string>>& matr, size_t playerNumber, std::unordered_set<size_t>& moves);

size_t enterPosition(std::unordered_set<size_t>& moves, std::string& player1_moves, std::string& player2_moves);

bool checkWin(size_t playerNumber, std::unordered_set<size_t>& moves);

void endGame(std::unordered_set<size_t>& moves);

int main() {
    printIntroduction();
    std::vector<std::vector<std::string>> matrix{};
    std::unordered_set<size_t> moves{};
    std::vector<std::string> player1_moves{}, player2_moves{};
}





void printMatrix(std::vector<std::vector<std::string>>& matr){
    std::cout << '\n';
    for (size_t y{0}; y<3; ++y){
        for (size_t x{0}; x<3; ++x){
            std::cout << matr[y][x] << " ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void printIntroduction(){
    std::cout << "Here are matrix positions. Players make moves alternately. Who makes a triple first wins. Good luck!\n";
    std::vector<std::vector<std::string>> matrixHello{{"0","1","2"}, {"3","4","5"}, {"6","7","8"}};
    printMatrix(matrixHello);
}

size_t enterPosition(std::unordered_set<size_t>& moves){
    std::cout << "Position to go: ";
    size_t position{666};
    size_t movesSize = moves.size();
    if (movesSize==9) return 10;//position 10 means no moves avaliable
    std::cin >> position;
    while ((std::cin.fail()) || (std::cin.peek()!='\n') || (position <0) || (position >8) || (std::count(moves.begin(), moves.end(), position)==1) ){
        std::cout << "Incorrect! Try another move.\nPosition to go: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cin >> position;
    }
    
    return position;
}





void makeMove(std::vector<std::vector<std::string>>& matr, std::unordered_set<size_t>& moves, std::vector<std::string>& player1_moves, std::vector<std::string>& player2_moves){ //ходы будут начинаться от 1
    
    size_t position=enterPosition(moves);
    if (position==10){
        endGame(moves);
        return;
    }
    size_t movesSize = moves.size();
    if (movesSize%2==0){
        player1_moves[std::ceil(position/3)]+=std::to_string(position);
    }else{
        player2_moves[std::ceil(position/3)]+=std::to_string(position);
    }
    moves.insert(position);
    
}

bool checkWin(std::vector<std::string>& player_moves){
    //036 147 258 012 345 678 048 246
    for (size_t i{0}; i<3; ++i){// hz nado pridumat
        std::string str = player_moves[i];
        std::sort(str.begin(), str.end());
        if (str=="012" || str=="345" || str=="678") return true;
        
    }
    
}

void endGame(std::unordered_set<size_t>& moves){
    
}

