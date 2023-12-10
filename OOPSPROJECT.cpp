#include <iostream>
#include <cstdlib>
#include <cmath>
#include <set>

#define EPSILON 1e-6

using namespace std;

class Game24Solver {
private:
    /// @brief 
    int k=0;
    int player;
    int numbers[4];
    int used[4];
    char expression[7];
    float targetValue;
    int count=0;
    set<string> uniqueSolutions;  // Set to store unique solutions

    bool isValidSolution(double result) {
        return result >= (targetValue - EPSILON) && result <= (targetValue + EPSILON);
    }

    void solve(int step, double currentResult) {
        if (step == 4) {
            if (isValidSolution(currentResult)) {
                k += 1;
                int start_index = (expression[0] == '-' || expression[0] == '*' || expression[0] == '/') ? 1 : 0;
                if (start_index > 0) {
                    return;
                } else {
                    string solution(expression);  // Convert char array to string
                    uniqueSolutions.insert(solution);
                    count = uniqueSolutions.size();
                    cout << "PLAYER " << ", SOLUTION (THIS IS THE AFTER " << k << " COMBINATION OF DIGITS): " << solution << endl;
                }
            }
            return;
        }

        for (int i = 0; i < 4; i++) {
            if (!used[i]) {
                used[i] = 1;

                // ADD TRIAL BLOCK
                expression[step * 2] = '+';
                expression[step * 2 + 1] = '0' + numbers[i];
                solve(step + 1, currentResult + numbers[i]);

                // SUBTRACTION BLOCK
                expression[step * 2] = '-';
                expression[step * 2 + 1] = '0' + numbers[i];
                solve(step + 1, currentResult - numbers[i]);

                // MULTIPLICATION BLOCK
                expression[step * 2] = '*';
                expression[step * 2 + 1] = '0' + numbers[i];
                solve(step + 1, currentResult * numbers[i]);

                // DIVISION BLOCK
                if (numbers[i] != 0) {
                    expression[step * 2] = '/';
                    expression[step * 2 + 1] = '0' + numbers[i];
                    solve(step + 1, currentResult / numbers[i]);
                }
                // BACKTRACKING
                used[i] = 0;
            }
        }
    }

public:
    Game24Solver(int playerNum) : player(playerNum), targetValue(0.0), count(0), k(0) {}

    void initialize() {
        if(player == 1)
        {
        player = 0;
        cout << "PLAYER " << player+1 << ", ENTER THE FOUR RANDOM VALUES BETWEEN 1 AND 9" << endl;
        for (int i = 0; i < 4; i++) {
            cin >> numbers[i];
            if (numbers[i] > 9 || numbers[i] < 0) {
                cout << "PLEASE PUT A VALID INPUT" << endl;
                exit(0);
            }
        }

        fill(used, used + 4, 0);

        cout << "PLAYER " << player+2 << ", PLEASE ENTER A VALUE BETWEEN 1 TO 100: ";
        cin >> targetValue;
        }
        else
        {
        cout << "PLAYER " << player << ", ENTER THE FOUR RANDOM VALUES BETWEEN 1 AND 9" << endl;
        for (int i = 0; i < 4; i++) {
            cin >> numbers[i];
            if (numbers[i] > 9 || numbers[i] < 0) {
                cout << "PLEASE PUT A VALID INPUT" << endl;
                exit(0);
            }
        }

        fill(used, used + 4, 0);

        cout << "PLAYER " << player-1 << ", PLEASE ENTER A VALUE BETWEEN 1 TO 100: ";
        cin >> targetValue;
        }
    }

    int getCount() const {
        return count;
    }

    void resetCount() {
        count = 0;
        uniqueSolutions.clear();  // Clear set for new round
    }

    void solveGame() {
        solve(0, 0.0);
    }
};

int main() {
    Game24Solver player1(1);

    player1.initialize();
    player1.solveGame();
    int player1Count = player1.getCount();
    if(player1Count == 0)
        cout << "NO SOLUTION POSSIBLE " << endl;

    Game24Solver player2(2);
    player2.initialize();
    player2.solveGame();
    int player2Count = player2.getCount();
    if(player2Count == 0)
        cout << "NO SOLUTION POSSIBLE " << endl;

    cout << "PLAYER 1  REAL(NON-REPETATIVE) COMBINATIONS: " << player1Count << endl;
    cout << "PLAYER 2 REAL (NON-REPETATIVE)COMBINATIONS: " << player2Count << endl;

    if (player1Count > player2Count) {
        cout << "PLAYER 1 WINS!" << endl;
    } else if (player2Count > player1Count) {
        cout << "PLAYER 2 WINS!" << endl;
    } else {
        cout << "IT'S A TIE! Both players have the same number of unique combinations." << endl;
    }

    return 0;
}