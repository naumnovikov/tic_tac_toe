#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <string>

//void printMatrix(std::vector<std::vector<std::string>>& matr);
void printMatrix(std::vector<std::string>& matr);
void printIntroduction();

//void makeMove(std::vector<std::vector<std::string>>& matr, std::unordered_set<size_t>& moves, std::vector<std::string>& player1_moves, std::vector<std::string>& player2_moves);
void makeMove(std::vector<std::string>& matr, std::unordered_set<size_t>& moves, std::vector<std::string>& player1_moves, std::vector<std::string>& player2_moves);

size_t enterPosition(std::unordered_set<size_t>& moves, std::string& player1_moves, std::string& player2_moves);

bool checkWin(std::vector<std::string>& player_moves);

void endGame(std::unordered_set<size_t>& moves, size_t winner);

int main() {
    printIntroduction();
    //std::vector<std::vector<std::string>> matrix{{"","",""},{"","",""},{"","",""}};
    std::unordered_set<size_t> moves{};
    std::vector<std::string> player1_moves{"","",""}, player2_moves{"","",""}, matrix{"","",""};
    
    while (!checkWin(player1_moves) && !checkWin(player2_moves)){
        if (moves.size()!=0)printMatrix(matrix);
        makeMove(matrix, moves, player1_moves, player2_moves);
    }
    
    if (checkWin(player1_moves)) endGame(moves, 1);
    else endGame(moves, 2);
}





/*void printMatrix(std::vector<std::vector<std::string>>& matr){
    std::cout << '\n';
    for (size_t y{0}; y<3; ++y){
        for (size_t x{0}; x<3; ++x){
            std::cout << matr[y][x] << " ";
        }
        std::cout << '\n';
    }
    //std::cout << '\n';
}*/


void printMatrix(std::vector<std::string>& matr){
    std::cout << '\n';
    for (size_t y{0}; y<3; ++y){
        std::cout << matr[y];
        std::cout << '\n';
    }
    //std::cout << '\n';
}

void printIntroduction(){
    std::cout << "Here are matrix positions. Players make moves alternately. Who makes a triple first wins. Good luck!\n";
    std::vector<std::string> matrixHello{"0 1 2","3 4 5","6 7 8"};
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





/*void makeMove(std::vector<std::vector<std::string>>& matr, std::unordered_set<size_t>& moves, std::vector<std::string>& player1_moves, std::vector<std::string>& player2_moves){ //ходы будут начинаться от 1
    
    size_t position=enterPosition(moves);
    if (position==10){
        endGame(moves, 3);
        return;
    }
    size_t movesSize = moves.size();
    if (movesSize%2==0){
        player1_moves[std::ceil(position/3)]+=std::to_string(position);
        //matr
    }else{
        player2_moves[std::ceil(position/3)]+=std::to_string(position);
        //matr
    }
    moves.insert(position);
    
}*/
void makeMove(std::vector<std::string>& matr, std::unordered_set<size_t>& moves, std::vector<std::string>& player1_moves, std::vector<std::string>& player2_moves){ //ходы будут начинаться от 1
    
    size_t position=enterPosition(moves);
    if (position==10){
        endGame(moves, 3);
        return;
    }
    size_t movesSize = moves.size();
    if (movesSize%2==0){
        player1_moves[std::ceil(position/3)]+=std::to_string(position);
        if (position==0 || position==3 || position==6) matr[std::ceil(position/3)][0]='x';
        if (position==1 || position==4 || position==7) matr[std::ceil(position/3)][2]='x';
        if (position==2 || position==5 || position==8) matr[std::ceil(position/3)][4]='x';
    }else{
        player2_moves[std::ceil(position/3)]+=std::to_string(position);
        if (position==0 || position==3 || position==6) matr[std::ceil(position/3)][0]='o';
        if (position==1 || position==4 || position==7) matr[std::ceil(position/3)][2]='o';
        if (position==2 || position==5 || position==8) matr[std::ceil(position/3)][4]='o';
    }
    moves.insert(position);
    
}

bool checkWin(std::vector<std::string>& player_moves){
    size_t lrDiag{0}, rlDiag{0}, leftVertLine{0}, MidVertLine{0}, RightVertLine{0}; // "1) / 2) \"
    for (size_t i{0}; i<3; ++i){
        std::string str = player_moves[i];
        std::sort(str.begin(), str.end());
        if (str=="012" || str=="345" || str=="678") return true;
        if (std::count(str.begin(), str.end(), '0')==1){
            leftVertLine++;
            lrDiag++;
        }
        if (std::count(str.begin(), str.end(), '3')==1) leftVertLine++;
        if (std::count(str.begin(), str.end(), '6')==1 && leftVertLine==2) return true;
        
        if (std::count(str.begin(), str.end(), '1')==1) MidVertLine++;
        if (std::count(str.begin(), str.end(), '4')==1){
            MidVertLine++;
            lrDiag++;
        }
        if (std::count(str.begin(), str.end(), '7')==1 && MidVertLine==2) return true;
        
        if (std::count(str.begin(), str.end(), '2')==1) RightVertLine++;
        if (std::count(str.begin(), str.end(), '5')==1) RightVertLine++;
        if (std::count(str.begin(), str.end(), '8')==1 && RightVertLine==2) return true;
        
        if (std::count(str.begin(), str.end(), '2')==1) lrDiag++;
        if (std::count(str.begin(), str.end(), '4')==1) lrDiag++;
        if (std::count(str.begin(), str.end(), '6')==1 && lrDiag==2) return true;
        
        if (std::count(str.begin(), str.end(), '4')==1) rlDiag++;
        if (std::count(str.begin(), str.end(), '8')==1 && rlDiag==2) return true;
    }
    return false;
    
}

void endGame(std::unordered_set<size_t>& moves, size_t winner){
    if (winner==3) std::cout << "A drow. Game had been going for " << moves.size() << " moves.";
    std::cout << "Player " << winner << " won a game!\nGame had been going for " << moves.size() << "moves.";
    exit(0);
}

