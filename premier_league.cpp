//importing library
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>  
#include <ctime>
#include <algorithm>
#include <cctype>
#include <vector>
using namespace std;
//defined structure
struct Team {
    string name;
    int played, win, draw, loss;
    int goalsFor, goalsAgainst;
    int points, cleanSheets;

    // Home / Away
    int homePlayed, homeWin, homeDraw, homeLoss;
    int awayPlayed, awayWin, awayDraw, awayLoss;
};

// ----------------- Fixture Structure -----------------
struct Fixture {
    int gameWeek;
    string homeTeam;
    string awayTeam;
    int homeGoals;
    int awayGoals;
    bool played;
};
// ----------------- Helper Functions -----------------
string normalizeString(string s) {
    string result;
    for (char c : s) {
        if (!isspace(c)) result += tolower(c);
    }
    return result;
}

int calculatePoints(int win, int draw) {
    return win * 3 + draw;
}

int getValidInt(string prompt, int minValue = 0) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minValue) {
            cin.ignore();
            return value;
        } else {
            cout << "Invalid input! Enter a number >= " << minValue << ".\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}
int main(){
    return 0;
}