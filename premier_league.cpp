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
// ----------------- File Management -----------------
void saveTeams(Team t[], int n) {
    ofstream out("premier_league.txt");
    if (out.fail()) { 
        cerr << "Error: Could not open premier_league.txt for writing!\n"; 
        return; 
    }
    for (int i = 0; i < n; i++) {
        out << t[i].name << " "
            << t[i].played << " "
            << t[i].win << " "
            << t[i].draw << " "
            << t[i].loss << " "
            << t[i].goalsFor << " "
            << t[i].goalsAgainst << " "
            << t[i].points << " "
            << t[i].cleanSheets << " "
            << t[i].homePlayed << " " << t[i].homeWin << " " << t[i].homeDraw << " " << t[i].homeLoss << " "
            << t[i].awayPlayed << " " << t[i].awayWin << " " << t[i].awayDraw << " " << t[i].awayLoss
            << endl;
        if(out.fail()) { 
            cerr << "Error: Failed while writing data!\n"; 
            return; 
        }
    }
    out.close();
}

void loadTeams(Team t[], int &n) {
    ifstream in("premier_league.txt");
    if(in.fail()) { cerr << "Error: Could not open premier_league.txt for reading!\n"; n=0; return; }

    n = 0;
    while(!in.eof() && in.good()) {
        in >> t[n].name >> t[n].played >> t[n].win
           >> t[n].draw >> t[n].loss
           >> t[n].goalsFor >> t[n].goalsAgainst
           >> t[n].points >> t[n].cleanSheets
           >> t[n].homePlayed >> t[n].homeWin >> t[n].homeDraw >> t[n].homeLoss
           >> t[n].awayPlayed >> t[n].awayWin >> t[n].awayDraw >> t[n].awayLoss;
        if(in.good()) n++;
    }

    if(in.bad()) { cerr << "Error: Failed during reading premier_league.txt\n"; }
    in.close();
}
//team registration function
void registerPremierLeagueTeams(Team t[], int &n) {
    string teamNames[20] = {
        "Arsenal","AstonVilla","Brentford","Brighton",
        "Chelsea","CrystalPalace","Everton","Fulham","LeedsUnited","Liverpool",
        "Brentford","ManchesterCity","ManchesterUnited","NewcastleUnited",
        "NottinghamForest","Bournemouth","Tottenham","WestHam",
        "Wolverhampton","Burnley"
    };
    n = 20;
    for (int i = 0; i < 20; i++) {
        t[i].name = teamNames[i];
        t[i].played = t[i].win = t[i].draw = t[i].loss = 0;
        t[i].goalsFor = t[i].goalsAgainst = t[i].points = t[i].cleanSheets = 0;
        t[i].homePlayed = t[i].homeWin = t[i].homeDraw = t[i].homeLoss = 0;
        t[i].awayPlayed = t[i].awayWin = t[i].awayDraw = t[i].awayLoss = 0;
    }
    saveTeams(t, n);
    cout << "All Premier League teams have been registered successfully!\n";
}
bool teamsAlreadyRegistered() {
    ifstream in("premier_league.txt");
    if(in.fail()) return false;
    in.seekg(0, ios::end);
    return in.tellg() > 0;
}
// ----------------- Team Operations -----------------
int getTeamIndex(Team t[], int &n, string prompt) {
    string name;
    int idx = -1;
    while (idx == -1) {
        cout << prompt;
        getline(cin, name);
        string normalizedInput = normalizeString(name);

        for (int i = 0; i < n; i++) {
            if (normalizeString(t[i].name) == normalizedInput) {
                idx = i;
                break;
            }
        }

        if (idx == -1) {
            cout << "Team not found. Register it? (1=Yes, 0=No): ";
            int choice = getValidInt("", 0);
            if (choice == 1) {
                idx = n;
                t[idx].name = name;
                t[idx].played = t[idx].win = t[idx].draw = t[idx].loss = 0;
                t[idx].goalsFor = t[idx].goalsAgainst = t[idx].points = t[idx].cleanSheets = 0;
                t[idx].homePlayed = t[idx].homeWin = t[idx].homeDraw = t[idx].homeLoss = 0;
                t[idx].awayPlayed = t[idx].awayWin = t[idx].awayDraw = t[idx].awayLoss = 0;
                n++;
                cout << "Team " << name << " registered successfully!\n";
            } else {
                cout << "Please enter a valid existing team.\n";
            }
        }
    }
    return idx;
}
// ----------------- Game Week Management -----------------
int getCurrentGameWeek() {
    ifstream in("match_history.txt");
    if(in.fail()) return 1;

    int lines = 0;
    string line;
    while(getline(in, line)) {
        if(line.find("GW") != string::npos) lines++;
    }
    in.close();

    return (lines / 10) + 1;
}

bool alreadyPlayedThisGW(string teamA, string teamB, int gameWeek) {
    ifstream in("match_history.txt");
    if(in.fail()) return false;

    string line;
    while(getline(in, line)) {
        if(line.find("GW" + to_string(gameWeek)) != string::npos) {
            if(line.find(teamA) != string::npos || line.find(teamB) != string::npos)
                return true;
        }
    }
    in.close();
    return false;
}
// ----------------- Fixtures -----------------
void generateFixtures(Team t[], int n) {
    vector<Fixture> fixtures;
    vector<int> teamsIndex;

    for(int i=0;i<n;i++) teamsIndex.push_back(i);

    // First half season (round-robin using circle method)
    for(int round=0; round<n-1; round++){
        for(int i=0;i<n/2;i++){
            int home = teamsIndex[i];
            int away = teamsIndex[n-1-i];
            if(home == away) continue; // Prevent self-match

            Fixture f;
            f.gameWeek = round+1;
            f.homeTeam = t[home].name;
            f.awayTeam = t[away].name;
            f.homeGoals = f.awayGoals = 0;
            f.played = false;
            fixtures.push_back(f);
        }
        // Rotate except first element
        int last = teamsIndex.back();
        teamsIndex.pop_back();
        teamsIndex.insert(teamsIndex.begin() + 1, last); // Corrected
    }

    // Second half season (reverse home/away)
    int originalSize = fixtures.size();
    for(int i=0;i<originalSize;i++){
        Fixture f = fixtures[i];
        f.gameWeek += n-1;
        swap(f.homeTeam, f.awayTeam);
        fixtures.push_back(f);
    }

    // Save fixtures to file
    ofstream out("fixtures.txt");
    if(out.fail()){ 
        cerr<<"Error: Cannot save fixtures.\n"; 
        return; 
    }

    for(auto &f: fixtures){
        out << "GW" << f.gameWeek << " | " << f.homeTeam << " vs " << f.awayTeam
            << " | " << f.homeGoals << "-" << f.awayGoals
            << " | " << (f.played?"Played":"Not Played") << endl;
    }
    out.close();

    cout << "Fixtures generated and saved successfully!\n";
}
int main(){
    return 0;
}