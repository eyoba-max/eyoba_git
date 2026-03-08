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
const string ADMIN_PASSWORD = "admin123";
bool authenticateAdmin() {
    string pass;
    int attempts = 3;

    while (attempts--) {
        cout << "Enter admin password: ";
        getline(cin, pass);

        if (pass == ADMIN_PASSWORD) {
            cout << "Access granted.\n";
            return true;
        } else {
            cout << "Wrong password! Attempts left: " << attempts << endl;
        }
    }

    cout << "Too many failed attempts. Access denied.\n";
    return false;
}


// ----------------- Team Structure -----------------
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
        out << t[i].name << "                    "
            << t[i].played << "    "
            << t[i].win << "    "
            << t[i].draw << "    "
            << t[i].loss << "    "
            << t[i].goalsFor << "    "
            << t[i].goalsAgainst << "    "
            << t[i].points << "    "
            << t[i].cleanSheets << "    "
            << t[i].homePlayed << "    " << t[i].homeWin << "    " << t[i].homeDraw << "    " << t[i].homeLoss << "    "
            << t[i].awayPlayed << "    " << t[i].awayWin << "    " << t[i].awayDraw << "    " << t[i].awayLoss
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
    if(in.fail()) { 
        cerr << "Error: Could not open premier_league.txt for reading!\n"; 
        n=0; 
        return; 
    }

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

void registerPremierLeagueTeams(Team t[], int &n) {
    string teamNames[20] = {
        "Arsenal","AstonVilla","Brentford","Brighton",
        "Chelsea","CrystalPalace","Everton","Fulham","LeedsUnited","Liverpool",
        "Sunderland","ManchesterCity","ManchesterUnited","NewcastleUnited",
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
int getTeamIndex(Team t[], int n, string prompt) {
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
            cout << "Team not found. Please enter an existing Premier League team.\n";
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
bool isScheduledMatch(string teamA, string teamB, int gameWeek) {
    ifstream in("fixtures.txt");
    if(in.fail()) return false;

    string line;
    string gwStr = "GW" + to_string(gameWeek);
    while(getline(in,line)){
        if(line.find(gwStr) != string::npos){
            if(line.find(teamA) != string::npos && line.find(teamB) != string::npos)
                return true;
        }
    }
    in.close();
    return false;
}

void updateFixtureAfterMatch(string teamA, string teamB, int goalA, int goalB, int gameWeek) {
    ifstream in("fixtures.txt");
    if(in.fail()){ cerr << "Error: Cannot read fixtures.txt\n"; return; }

    vector<string> lines;
    string line;
    string gwStr = "GW" + to_string(gameWeek);

    while(getline(in,line)){
        if(line.find(gwStr) != string::npos &&
           line.find(teamA) != string::npos &&
           line.find(teamB) != string::npos) {
            // Update goals and mark as played
            size_t pos = line.find("|", line.find("|")+1);
            line = line.substr(0,pos+2) + to_string(goalA) + "-" + to_string(goalB) + " | Played";
        }
        lines.push_back(line);
    }
    in.close();

    ofstream out("fixtures.txt");
    if(out.fail()){ cerr << "Error: Cannot write to fixtures.txt\n"; return; }
    for(auto &l: lines) out << l << endl;
    out.close();
}

void viewFixturesByGW() {
    ifstream in("fixtures.txt");
    if (in.fail()) { 
        cerr << "Error: Could not open fixtures.txt for reading!\n"; 
        return; 
    }

    int gw;
    cout << "Enter Game Week number: ";
    cin >> gw;
    cin.ignore();

    string line;
    bool found = false;
    cout << "\n--- Fixtures for Game Week " << gw << " ---\n";

    while (getline(in, line)) {
        // Extract the GW number from the line
        size_t gwPos = line.find("GW");
        if (gwPos != string::npos) {
            int lineGW = stoi(line.substr(gwPos + 2)); // +2 to skip "GW"
            if (lineGW == gw) {
                cout << line << endl;
                found = true;
            }
        }
    }

    if (!found) {
        cout << "No fixtures found for Game Week " << gw << ".\n";
    }

    in.close();
}
bool fixturesAlreadyGenerated() {
    ifstream in("fixtures.txt");
    if(in.fail()) return false;   // file doesn't exist
    in.seekg(0, ios::end);
    return in.tellg() > 0;        // file exists & not empty
}

// ----------------- Match & Standings -----------------
void saveMatchHistory(string teamA, string teamB, int goalA, int goalB) {
    ofstream out("match_history.txt", ios::app);
    if(out.fail()) { 
        cerr << "Error: Could not open match_history.txt for writing!\n"; 
        return; 
    }

    int gameWeek = getCurrentGameWeek();
    time_t now = time(0);
    char* dt = ctime(&now);
    dt[strlen(dt)-1] = '\0';

    out << "GW" << gameWeek << " | " << dt << " | " << teamA << " " << goalA << " - " << goalB << " " << teamB << endl;

    if(out.fail()) cerr << "Error: Failed while writing match history!\n";
    out.close();
}
void saveStandingHistory(Team t[], int n, int gameWeek) {
    ofstream out("standing_history.txt", ios::app);
    if(out.fail()) { 
        cerr << "Error: Could not open standing_history.txt\n"; 
        return; 
    }

    time_t now = time(0);
    char* dt = ctime(&now);
    dt[strlen(dt)-1] = '\0';

    out << "\n===== GAME WEEK " << gameWeek << " STANDINGS | " << dt << " =====\n";

    out << left << setw(20) << "Team" << setw(6) << "P" << setw(6) << "W"
        << setw(6) << "D" << setw(6) << "L"
        << setw(6) << "GF" << setw(6) << "GA"
        << setw(6) << "GD" << setw(6) << "Pts"
        << setw(6) << "CS" << setw(10) << "Zone" << endl;

    for(int i=0;i<n;i++){
        string zone;
        if(i < 4) zone = "CL";
        else if(i < 6) zone = "EL";
        else if(i == 6) zone = "C";
        else if(i >= n-3) zone = "RL";
        else zone = "-";

        out << left << setw(20) << t[i].name
            << setw(6) << t[i].played
            << setw(6) << t[i].win
            << setw(6) << t[i].draw
            << setw(6) << t[i].loss
            << setw(6) << t[i].goalsFor
            << setw(6) << t[i].goalsAgainst
            << setw(6) << t[i].goalsFor - t[i].goalsAgainst
            << setw(6) << t[i].points
            << setw(6) << t[i].cleanSheets
            << setw(10) << zone << endl;
    }

    out.close();
}

void addMatchResult(Team t[], int &n) {
    int a = getTeamIndex(t, n, "Enter Team A name: ");
    int b = getTeamIndex(t, n, "Enter Team B name: ");

    if(a == b) { 
        cout << "A team cannot play against itself!\n"; 
        return; 
    }

    int gameWeek = getCurrentGameWeek();
    if(!isScheduledMatch(t[a].name,t[b].name,gameWeek)) {
        cout << "Error: This match is not scheduled for this Game Week!\n";
        return;
    }
    if(alreadyPlayedThisGW(t[a].name, t[b].name, gameWeek)) {
        cout << "Error: One of the teams already played in this Game Week!\n";
        return;
    }

    int goalA = getValidInt("Enter goals scored by Team A: ");
    int goalB = getValidInt("Enter goals scored by Team B: ");

    t[a].played++; t[b].played++;
    t[a].goalsFor += goalA; t[a].goalsAgainst += goalB;
    t[b].goalsFor += goalB; t[b].goalsAgainst += goalA;

    if(goalB == 0) t[a].cleanSheets++;
    if(goalA == 0) t[b].cleanSheets++;

    // Home / Away stats
    t[a].homePlayed++; t[b].awayPlayed++;
    if(goalA > goalB){ 
        t[a].win++; t[b].loss++; t[a].homeWin++; t[b].awayLoss++; 
    }
    else if(goalB > goalA){ 
        t[b].win++; t[a].loss++; t[b].awayWin++; t[a].homeLoss++; 
    }
    else{ 
        t[a].draw++; t[b].draw++; t[a].homeDraw++; t[b].awayDraw++; 
    }

    t[a].points = calculatePoints(t[a].win, t[a].draw);
    t[b].points = calculatePoints(t[b].win, t[b].draw);

    saveMatchHistory(t[a].name, t[b].name, goalA, goalB);
    updateFixtureAfterMatch(t[a].name,t[b].name,goalA,goalB,gameWeek);

    sort(t, t+n, [](Team x, Team y){
        int gdX = x.goalsFor - x.goalsAgainst;
        int gdY = y.goalsFor - y.goalsAgainst;
        if(x.points != y.points) return x.points > y.points;
        return gdX > gdY;
    });

    saveStandingHistory(t, n, gameWeek);

    cout << "Match result updated and saved!\n";
    cout << "Game Week " << gameWeek << " standings saved!\n";
}
void sortTable(Team t[], int n) {
    sort(t, t + n, [](Team a, Team b) {
        int gdA = a.goalsFor - a.goalsAgainst;
        int gdB = b.goalsFor - b.goalsAgainst;

        if (a.points != b.points) return a.points > b.points;
        if (gdA != gdB) return gdA > gdB;
        return a.goalsFor > b.goalsFor;
    });
}
// ----------------- Display / Search -----------------
void displayTable(Team t[], int n) {
    sortTable(t, n);
    cout << left << setw(20) << "Team" << setw(6) << "P" << setw(6) << "W"
         << setw(6) << "D" << setw(6) << "L" << setw(6) << "GF"
         << setw(6) << "GA" << setw(6) << "GD" << setw(6) << "Pts"
         << setw(6) << "CS" << setw(10) << "Zone" << endl;

    for (int i = 0; i < n; i++) {
        
        string zone;
        if(i < 4) zone = "CL";
        else if(i < 6) zone = "EL";
        else if(i == 6) zone = "C";
        else if(i >= n-3) zone = "RL";
        else zone = "-";

        cout << left << setw(20) << t[i].name
             << setw(6) << t[i].played
             << setw(6) << t[i].win
             << setw(6) << t[i].draw
             << setw(6) << t[i].loss
             << setw(6) << t[i].goalsFor
             << setw(6) << t[i].goalsAgainst
             << setw(6) << t[i].goalsFor - t[i].goalsAgainst
             << setw(6) << t[i].points
             << setw(6) << t[i].cleanSheets
             << setw(10) << zone << endl;
    }
}



void searchTeam(Team t[], int n) {
    string name;
    cout << "Enter team name: ";
    getline(cin, name);
    string normalizedInput = normalizeString(name);
    for(int i=0;i<n;i++){
        if(normalizeString(t[i].name) == normalizedInput){
            cout << "\nTeam: " << t[i].name << "\nPlayed: " << t[i].played
                 << "\nWins: " << t[i].win << "\nDraws: " << t[i].draw
                 << "\nLosses: " << t[i].loss << "\nGoals For: " << t[i].goalsFor
                 << "\nGoals Against: " << t[i].goalsAgainst
                 << "\nPoints: " << t[i].points
                 << "\nClean Sheets: " << t[i].cleanSheets << endl;

            cout << "\n--- Home Record ---"
                 << "\nPlayed: " << t[i].homePlayed
                 << " W: " << t[i].homeWin
                 << " D: " << t[i].homeDraw
                 << " L: " << t[i].homeLoss << endl;

            cout << "\n--- Away Record ---"
                 << "\nPlayed: " << t[i].awayPlayed
                 << " W: " << t[i].awayWin
                 << " D: " << t[i].awayDraw
                 << " L: " << t[i].awayLoss << endl;

            return;
        }
    }
    cout << "Team not found!\n";
}

void viewStandingHistory() {
    ifstream in("standing_history.txt");
    if(in.fail()) { 
        cerr << "Error: Could not open standing_history.txt for reading!\n"; 
        return; 
    }
    string line;
    cout << "\n--- League Standings History ---\n";
    while(getline(in,line)) cout << line << endl;
    in.close();
}
void viewMatchHistoryByGW() {
    ifstream in("match_history.txt");
    if (in.fail()) {
        cerr << "Error: Could not open match_history.txt\n";
        return;
    }

    int gw;
    cout << "Enter Game Week number: ";
    cin >> gw;
    cin.ignore();

    string line;
    bool found = false;

    cout << "\n--- Match History for Game Week " << gw << " ---\n";

    while (getline(in, line)) {
        // Match exact game week
        if (line.rfind("GW" + to_string(gw) + " |", 0) == 0) {
            cout << line << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No matches found for Game Week " << gw << ".\n";
    }

    in.close();
}

void searchGameWeek() {
    ifstream in("match_history.txt");
    if(in.fail()) { 
        cerr << "Error: Could not open match_history.txt for reading!\n"; 
        return; 
    }

    int gw;
    cout << "Enter Game Week number: ";
    cin >> gw;
    cin.ignore();

    string line;
    bool found = false;

    cout << "\n--- Matches in Game Week " << gw << " ---\n";

    while(getline(in, line)) {
        if(line.find("GW" + to_string(gw)) != string::npos) {
            cout << line << endl;
            found = true;
        }
    }

    if(!found) cout << "No matches found for this game week.\n";

    in.close();
}

void displayTopScorers(Team t[], int n) {
    cout << "\n--- Top Scorers by Goals ---\n";
    Team temp[50];
    for(int i=0;i<n;i++) temp[i]=t[i];
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(temp[j].goalsFor>temp[i].goalsFor){
                Team swap=temp[i]; temp[i]=temp[j]; temp[j]=swap;
            }
        }
    }
    cout << left << setw(20) << "Team" << setw(6) << "Goals" << endl;
    for(int i=0;i<n;i++) cout << left << setw(20) << temp[i].name << setw(6) << temp[i].goalsFor << endl;
}
void customerMenu(Team teams[], int n) {
    int choice;
    do {
        cout << "\n--- CUSTOMER PANEL ---\n";
        cout << "1. View League Table\n";
        cout << "2. View Fixtures by Game Week\n";
        cout << "3. View Match History by Game Week\n";
        cout << "4. Search Team\n";
        cout << "5. View Standings History\n";
        cout<<  "6. Top Scorers\n";
        cout << "7. Exit\n";

        choice = getValidInt("Enter choice: ", 1);

        switch (choice) {
            case 1: displayTable(teams, n); break;
            case 2: viewFixturesByGW(); break;
            case 3: viewMatchHistoryByGW(); break;
            case 4: searchTeam(teams, n); break;
            case 5: viewStandingHistory(); break;
            case 6: displayTopScorers(teams, n);break;
            case 7: return;
        }
    } while (choice != 7);
}
void adminMenu(Team teams[], int n) {
    int choice;
    do {
        cout << "\n--- ADMIN PANEL ---\n";
        cout << "1. Add Match Result\n";
        cout << "2. Generate Fixtures (First Time Only)\n";
        cout << "3. Display League Table\n";
        cout << "4. View Fixtures by Game Week\n";
        cout << "5. View Standings History\n";
        cout<<  "6. Top Scorers\n";
        cout << "7. Save & Exit Admin\n";
        
        

        choice = getValidInt("Enter choice: ", 1);

        switch (choice) {
            case 1: addMatchResult(teams, n); break;
            case 2: 
                   if (fixturesAlreadyGenerated()) {
                       cout << "Fixtures already generated. Cannot generate again.\n";
                   } 
                   else {
                        generateFixtures(teams, n);
    }
    break;

            case 3: displayTable(teams, n); break;
            case 4: viewFixturesByGW(); break;
            case 5: viewStandingHistory(); break;
            case 6: displayTopScorers(teams, n);break;
            case 7: saveTeams(teams, n); break;
        }
    } while (choice != 7);
}

// ----------------- Main Program -----------------
int main() {
    Team teams[50];
    int n;

    
    if(!teamsAlreadyRegistered()) {
        registerPremierLeagueTeams(teams, n);
    }

    loadTeams(teams, n);
    sortTable(teams, n);   

int role;
cout << "Select Mode:\n";
cout << "1. Admin\n";
cout << "2. Customer\n";
cout << "Enter choice: ";
cin >> role;
cin.ignore();

if (role == 1) {
    if (authenticateAdmin()) {
        adminMenu(teams, n);
    }
} 
else if (role == 2) {
    customerMenu(teams, n);
} 
else {
    cout << "Invalid selection.\n";
}


    return 0;
}
