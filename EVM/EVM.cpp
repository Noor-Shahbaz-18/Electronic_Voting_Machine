#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <windows.h>
using namespace std;

// Constants for maximum sizes
const int MAX_CANDIDATES = 100;
const int MAX_VOTERS = 1000;

// Function to change text color
static void SetTextColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Function to set position of text on page
static void gotoxy(int x, int y) {
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, coordinate);
}

// Function to clear the screen
static void clearScreen() {
    system("cls");
}

// Function to pause the program
static void pause() {
    system("pause");
}

// Function to display e-voting front page
static void frontpage() {
    SetTextColor(13);
    gotoxy(46, 17);
    cout << " _______                          _______ __________________ _        _______ \n";
    gotoxy(46, 18);
    cout << "(  ____ \\               |\\     /|(  ___  )\\__   __/\\__   __/( (    /|(  ____ \\\n";
    gotoxy(46, 19);
    cout << "| (    \\/               | )   ( || (   ) |   ) (      ) (   |  \\  ( || (    \\/\n";
    gotoxy(46, 20);
    cout << "| (__         _____     | |   | || |   | |   | |      | |   |   \\ | || |      \n";
    gotoxy(46, 21);
    cout << "|  __)       (_____)    ( (   ) )| |   | |   | |      | |   | (\\ \\) || | ____ \n";
    gotoxy(46, 22);
    cout << "| (                      \\ \\_/ / | |   | |   | |      | |   | | \\   || | \\_  )\n";
    gotoxy(46, 23);
    cout << "| (____/\\                 \\   /  | (___) |   | |   ___) (___| )  \\  || (___) |\n";
    gotoxy(46, 24);
    cout << "(_______/                  \\_/   (_______)   )_(   \\_______/|/    )_)(_______)\n";
}

// Function to display login page
static void login() {
    SetTextColor(13);
    gotoxy(6, 17);
    cout << " _       _______ _________________               _______         _______ _______ _______ _______ _______ _______         _       _            ";
    gotoxy(6, 18);
    cout << "( \\     (  ___  (  ____ \\__   __( (    /|       (  ____ |\\     /(  ____ (  ____ (  ____ (  ____ (  ____ (  ____ |\\     /( \\     ( \\  |\\     /|";
    gotoxy(6, 19);
    cout << "| (     | (   ) | (    \\/  ) (  |  \\  ( |       | (    \\| )   ( | (    \\| (    \\| (    \\| (    \\| (    \\| (    \\| )   ( | (     | (  ( \\   / )";
    gotoxy(6, 20);
    cout << "| |     | |   | | |        | |  |   \\ | |       | (_____| |   | | |     | |     | (__   | (_____| (_____| (__   | |   | | |     | |   \\ (_) / ";
    gotoxy(6, 21);
    cout << "| |     | |   | | | ____   | |  | (\\ \\) |       (_____  | |   | | |     | |     |  __)  (_____  (_____  |  __)  | |   | | |     | |    \\   /  ";
    gotoxy(6, 22);
    cout << "| |     | |   | | | \\_  )  | |  | | \\   |             ) | |   | | |     | |     | (           ) |     ) | (     | |   | | |     | |     ) (   ";
    gotoxy(6, 23);
    cout << "| (____/| (___) | (___) ___) (__| )  \\  |       /\\____) | (___) | (____/| (____/| (____//\\____) /\\____) | )     | (___) | (____/| (____/| |   ";
    gotoxy(6, 24);
    cout << "(_______(_______(_______\\_______|/    )_)       \\_______(_______(_______(_______(_______\\_______\\_______|/      (_______(_______(_______\\_/   ";
    cout << endl << endl;
}

static void logout() {
    SetTextColor(13);
    gotoxy(52, 17);
    cout << " _       _______ _______	     _______        _________";
    gotoxy(52, 18);
    cout << "( \\     (  ___  (  ____ \\       (  ___  |\\     /\\__   __/";
    gotoxy(52, 19);
    cout << "| (     | (   ) | (    \\/       | (   ) | )   ( |  ) (   ";
    gotoxy(52, 20);
    cout << "| |     | |   | | |             | |   | | |   | |  | |   ";
    gotoxy(52, 21);
    cout << "| |     | |   | | | ____        | |   | | |   | |  | |   ";
    gotoxy(52, 22);
    cout << "| |     | |   | | | ____        | |   | | |   | |  | |   ";
    gotoxy(52, 23);
    cout << "| |     | |   | | | \\_  )       | |   | | |   | |  | |   ";
    gotoxy(52, 24);
    cout << "| (____/| (___) | (___) |       | (___) | (___) |  | |   ";
    gotoxy(52, 25);
    cout << "(_______(_______(_______)       (_______(_______)  )_(   ";
    cout << endl << endl;
}

class User {
protected:
    string username;
    string password;
public:
    User(string u, string p) : username(u), password(p) {}
    bool login(const string& user, const string& pass) const {
        return username == user && password == pass;
    }
    virtual void showMenu() = 0;
};

// Forward declarations
class NationalElection;
class ProvincialElection;

class Voter : public User {
    int voterId;
    string cnic;
    string postalCode;
    string province;
    string region;
    bool hasVoted;
public:
    Voter() : User("", ""), voterId(0), hasVoted(false) {}
    Voter(string u, string p, int id, string c, string postal, string prov, string reg)
        : User(u, p), voterId(id), cnic(c), postalCode(postal), province(prov), region(reg), hasVoted(false) {
    }

    void showMenu() override {
        cout << "Welcome Voter: " << username << endl;
        cout << "1. View Elections" << endl;
        cout << "2. Cast Vote" << endl;
    }

    int getId() const { return voterId; }
    string getPostalCode() const { return postalCode; }
    string getCNIC() const { return cnic; }
    string getProvince() const { return province; }
    string getRegion() const { return region; }
    bool getHasVoted() const { return hasVoted; }
    void setHasVoted(bool voted) { hasVoted = voted; }

    static bool isValidCNIC(const string& cnic) {
        string cleanedCNIC;
        for (size_t i = 0; i < cnic.length(); i++) {
            if (isdigit(cnic[i])) cleanedCNIC += cnic[i];
        }
        return cleanedCNIC.length() == 13;
    }

    static bool isValidPostalCode(const string& code) {
        if (code.length() != 5) return false;
        for (size_t i = 0; i < code.length(); i++) {
            if (code[i] < '0' || code[i] > '9') return false;
        }
        return true;
    }

    void inputRegionInfo() {
        const string provinces[4] = { "Punjab", "Sindh", "Khyber Pakhtunkhwa", "Balochistan" };
        const string regions[4][3] = {
            {"Lahore", "Rawalpindi", "Multan"},
            {"Karachi", "Hyderabad", "Sukkur"},
            {"Peshawar", "Abbottabad", "Mardan"},
            {"Quetta", "Gwadar", "Turbat"}
        };

        do {
            cout << "Enter 13-digit CNIC (no dashes): ";
            getline(cin, cnic);
        } while (!isValidCNIC(cnic));

        do {
            cout << "Enter 5-digit Postal Code: ";
            getline(cin, postalCode);
        } while (!isValidPostalCode(postalCode));

        cout << "\nSelect Province:\n";
        for (int i = 0; i < 4; i++) {
            cout << i + 1 << ". " << provinces[i] << endl;
        }
        int provinceChoice;
        cout << "Enter province number (1-4): ";
        cin >> provinceChoice;
        cin.ignore();
        if (provinceChoice < 1 || provinceChoice > 4) {
            cout << "Invalid province selection. Defaulting to Punjab.\n";
            province = provinces[0];
        }
        else {
            province = provinces[provinceChoice - 1];
        }

        cout << "\nSelect Region in " << province << ":\n";
        for (int j = 0; j < 3; j++) {
            cout << j + 1 << ". " << regions[provinceChoice - 1][j] << endl;
        }
        int regionChoice;
        cout << "Enter region number (1-3): ";
        cin >> regionChoice;
        cin.ignore();
        if (regionChoice < 1 || regionChoice > 3) {
            cout << "Invalid region selection. Defaulting to first region.\n";
            region = regions[provinceChoice - 1][0];
        }
        else {
            region = regions[provinceChoice - 1][regionChoice - 1];
        }
    }

    void voterMenu(NationalElection& nationalElection, ProvincialElection& provincialElection);
};

class Candidate {
    string name;
    string party;
    int votes;
public:
    Candidate() : votes(0) {}
    Candidate(string n, string p) : name(n), party(p), votes(0) {}

    void incrementVotes() { votes++; }
    void displayInfo() const {
        cout << "Name: " << name << ", Party: " << party << ", Votes: " << votes << endl;
    }
    string getName() const { return name; }
    string getParty() const { return party; }
    int getVotes() const { return votes; }
};

class Election {
protected:
    string title;
    Candidate candidates[MAX_CANDIDATES];
    int candidateCount;
    Voter voters[MAX_VOTERS];
    int voterCount;

public:
    Election(string t) : title(t), candidateCount(0), voterCount(0) {}

    virtual void showElectionType() {
        cout << "Generic Election" << endl;
    }

    bool isCandidatesEmpty() const {
        return candidateCount == 0;
    }

    virtual void loadCandidatesFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "No candidates file found, starting fresh.\n";
            return;
        }

        candidateCount = 0;
        string line;
        while (getline(file, line) && candidateCount < MAX_CANDIDATES) {
            stringstream ss(line);
            string name, party, voteStr;
            getline(ss, name, ',');
            getline(ss, party, ',');
            getline(ss, voteStr);
            int votes = 0;
            try {
                votes = stoi(voteStr);
            }
            catch (...) {
                votes = 0;
            }
            Candidate c(name, party);
            for (int i = 0; i < votes; ++i) {
                c.incrementVotes();
            }
            candidates[candidateCount++] = c;
        }
        file.close();
    }

    virtual void addCandidate(string name, string party) {
        if (candidateCount >= MAX_CANDIDATES) {
            cout << "Candidate list is full.\n";
            return;
        }
        Candidate c(name, party);
        candidates[candidateCount++] = c;
        cout << "Candidate '" << name << "' added to in-memory list." << endl;
    }

    void displayCandidates() {
        if (candidateCount == 0) {
            cout << "\nNo candidates available.\n";
            return;
        }

        cout << "\n--- Candidate List ---\n";
        for (int i = 0; i < candidateCount; ++i) {
            cout << (i + 1) << ". Name: " << candidates[i].getName()
                << ", Party: " << candidates[i].getParty()
                << ", Votes: " << candidates[i].getVotes() << "\n";
        }
    }

    virtual bool findVoter(const string& cnic, const string& postalCode, const string& province = "", const string& region = "") {
        for (int i = 0; i < voterCount; ++i) {
            if (voters[i].getCNIC() == cnic && voters[i].getPostalCode() == postalCode) {
                cout << "Voter found: CNIC = " << cnic << ", Postal = " << postalCode << "\n";
                return true;
            }
        }
        cout << "Voter not found: CNIC = " << cnic << ", Postal = " << postalCode << "\n";
        return false;
    }

    void secureVote(string cnic, string postalCode, int candidateIndex, string province = "", string region = "") {
        for (int i = 0; i < voterCount; ++i) {
            if (voters[i].getCNIC() == cnic && voters[i].getPostalCode() == postalCode) {
                if (voters[i].getHasVoted()) {
                    cout << "You have already voted!" << endl;
                    return;
                }
                if (candidateIndex >= 0 && candidateIndex < candidateCount) {
                    candidates[candidateIndex].incrementVotes();
                    voters[i].setHasVoted(true);
                    updateCandidateFile();
                    cout << "Vote cast for " << candidates[candidateIndex].getName() << "!\n";
                    return;
                }
                else {
                    cout << "Invalid candidate index! Please select a number between 1 and " << candidateCount << ".\n";
                    return;
                }
            }
        }
        cout << "CNIC or Postal Code not found in registered voters!" << endl;
    }

    virtual void updateCandidateFile() {
        // Base class does not write to file; derived classes handle file operations
    }

    void showResults() {
        if (candidateCount == 0) {
            cout << "\nNo candidates available.\n";
            return;
        }
        cout << "\n--- Election Results ---\n";
        for (int i = 0; i < candidateCount; ++i) {
            cout << setw(20) << left << candidates[i].getName() << " | Votes: " << candidates[i].getVotes() << endl;
        }
    }

    void showWinner() {
        if (candidateCount == 0) {
            cout << "No candidates in this election." << endl;
            return;
        }

        int maxVotes = -1;
        string winner = "None";
        for (int i = 0; i < candidateCount; ++i) {
            if (candidates[i].getVotes() > maxVotes) {
                maxVotes = candidates[i].getVotes();
                winner = candidates[i].getName();
            }
        }
        cout << "\nWinner: " << winner << " with " << maxVotes << " votes!" << endl;
    }

    void loadVotersFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening voters file.\n";
            return;
        }

        voterCount = 0;
        string line;
        while (getline(file, line) && voterCount < MAX_VOTERS) {
            stringstream ss(line);
            string name, cnic, postalCode, province, region;
            int id;

            getline(ss, name, ',');
            ss >> id;
            ss.ignore();
            getline(ss, cnic, ',');
            getline(ss, postalCode, ',');
            getline(ss, province, ',');
            getline(ss, region);

            if (!name.empty() && !cnic.empty() && !postalCode.empty() && !province.empty() && !region.empty()) {
                voters[voterCount++] = Voter(name, "default", id, cnic, postalCode, province, region);
            }
        }
        file.close();
    }
};

class NationalElection : public Election {
    string country;
public:
    NationalElection(string title, string c) : Election(title), country(c) {}
    void showElectionType() override {
        cout << "National Election - Country: " << country << endl;
    }

    void loadCandidatesFromFile(const string& filename) override {
        Election::loadCandidatesFromFile("national_candidates.txt");
    }

    void addCandidate(string name, string party) override {
        if (candidateCount >= MAX_CANDIDATES) {
            cout << "Candidate list is full.\n";
            return;
        }
        Candidate c(name, party);
        candidates[candidateCount++] = c;

        ofstream file("national_candidates.txt", ios::app);
        if (file.is_open()) {
            file << name << "," << party << "," << 0 << endl;
            file.close();
            cout << "Candidate '" << name << "' added to national_candidates.txt." << endl;
        }
        else {
            cout << "Error: Could not open national_candidates.txt for writing." << endl;
        }
    }

    void updateCandidateFile() override {
        ofstream file("national_candidates.txt");
        if (file.is_open()) {
            for (int i = 0; i < candidateCount; ++i) {
                file << candidates[i].getName() << "," << candidates[i].getParty() << "," << candidates[i].getVotes() << endl;
            }
            file.close();
        }
        else {
            cout << "Error updating national candidate file." << endl;
        }
    }
};

class ProvincialElection : public Election {
    string province;
    const string provinces[4] = { "Punjab", "Sindh", "Khyber Pakhtunkhwa", "Balochistan" };
    const string regions[4][3] = {
        {"Lahore", "Rawalpindi", "Multan"},
        {"Karachi", "Hyderabad", "Sukkur"},
        {"Peshawar", "Abbottabad", "Mardan"},
        {"Quetta", "Gwadar", "Turbat"}
    };

public:
    ProvincialElection(string title, string p) : Election(title), province(p) {}

    void showElectionType() override {
        cout << "Provincial Election - Province: " << province << endl;
    }

    void loadCandidatesFromFile(const string& filename) override {
        Election::loadCandidatesFromFile("provincial_candidates.txt");
    }

    void addCandidate(string name, string party) override {
        if (candidateCount >= MAX_CANDIDATES) {
            cout << "Candidate list is full.\n";
            return;
        }
        Candidate c(name, party);
        candidates[candidateCount++] = c;

        ofstream file("provincial_candidates.txt", ios::app);
        if (file.is_open()) {
            file << name << "," << party << "," << 0 << endl;
            file.close();
            cout << "Candidate '" << name << "' added to provincial_candidates.txt." << endl;
        }
        else {
            cout << "Error: Could not open provincial_candidates.txt for writing." << endl;
        }
    }

    void updateCandidateFile() override {
        ofstream file("provincial_candidates.txt");
        if (file.is_open()) {
            for (int i = 0; i < candidateCount; ++i) {
                file << candidates[i].getName() << "," << candidates[i].getParty() << "," << candidates[i].getVotes() << endl;
            }
            file.close();
        }
        else {
            cout << "Error updating provincial candidate file." << endl;
        }
    }

    bool findVoter(const string& cnic, const string& postalCode, const string& province, const string& region) override {
        for (int i = 0; i < voterCount; ++i) {
            if (voters[i].getCNIC() == cnic &&
                voters[i].getPostalCode() == postalCode &&
                voters[i].getProvince() == province &&
                voters[i].getRegion() == region) {
                cout << "Voter found: CNIC=" << cnic << ", Postal=" << postalCode
                    << ", Province=" << province << ", Region=" << region << "\n";
                return true;
            }
        }
        cout << "Voter not found: CNIC = " << cnic << ", Postal = " << postalCode
            << ", Province = " << province << ", Region = " << region << "\n";
        cout << "Registered voters:\n";
        for (int i = 0; i < voterCount; ++i) {
            cout << "- CNIC = " << voters[i].getCNIC()
                << ", Postal = " << voters[i].getPostalCode()
                << ", Province = " << voters[i].getProvince()
                << ", Region = " << voters[i].getRegion() << "\n";
        }
        return false;
    }

    void castProvincialVote() {
        cout << "\nSelect your Province from the list below:\n";
        for (int i = 0; i < 4; i++) {
            cout << i + 1 << ". " << provinces[i] << endl;
        }

        int provinceChoice;
        cout << "Enter the province number (1-4): ";
        cin >> provinceChoice;
        cin.ignore();

        if (provinceChoice < 1 || provinceChoice > 4) {
            cout << "Invalid province selection.\n";
            return;
        }

        province = provinces[provinceChoice - 1];
        cout << "\nYou selected: " << province << endl;

        cout << "\nNow select your Region in " << province << ":\n";
        for (int j = 0; j < 3; j++) {
            cout << j + 1 << ". " << regions[provinceChoice - 1][j] << endl;
        }

        int regionChoice;
        cout << "Enter the region number (1-3): ";
        cin >> regionChoice;
        cin.ignore();

        if (regionChoice < 1 || regionChoice > 3) {
            cout << "Invalid region selection.\n";
            return;
        }

        string selectedRegion = regions[provinceChoice - 1][regionChoice - 1];
        cout << "\nYou selected region: " << selectedRegion << endl;

        string cnic, postalCode;
        cout << "\nEnter your CNIC (13 digits, no dashes): ";
        getline(cin, cnic);
        if (!Voter::isValidCNIC(cnic)) {
            cout << "Invalid CNIC. Must be 13 digits.\n";
            return;
        }
        cout << "Enter your Postal Code (5 digits): ";
        getline(cin, postalCode);
        if (!Voter::isValidPostalCode(postalCode)) {
            cout << "Invalid Postal Code.\n";
            return;
        }

        if (!findVoter(cnic, postalCode, province, selectedRegion)) {
            cout << "You are not registered to vote in this province and region.\n";
            return;
        }

        displayCandidates();
        if (isCandidatesEmpty()) {
            cout << "No candidates available to vote for.\n";
            return;
        }

        int candidateIndex;
        cout << "Enter the number of the candidate you want to vote for: ";
        cin >> candidateIndex;
        cin.ignore();

        secureVote(cnic, postalCode, candidateIndex - 1, province, selectedRegion);
    }
};

void Voter::voterMenu(NationalElection& nationalElection, ProvincialElection& provincialElection) {
    int electionChoice;
    do {
        clearScreen();
        SetTextColor(192);
        cout << " User Menu: " << endl;
        SetTextColor(12);
        cout << "\nWhich Election you want to participate in? Enter your choice: \n";
        cout << "1. National Election\n";
        cout << "2. Provincial Election\n";
        cout << "3. Exit to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> electionChoice;
        cin.ignore();

        switch (electionChoice) {
        case 1: {
            nationalElection.displayCandidates();
            if (nationalElection.isCandidatesEmpty()) {
                cout << "No candidates available to vote for.\n";
                pause();
                break;
            }

            string cnic, postalCode;
            int candidateIndex;
            cout << "\nEnter your CNIC (13 digits, no dashes): ";
            getline(cin, cnic);
            if (!isValidCNIC(cnic)) {
                cout << "Invalid CNIC. Must be 13 digits.\n";
                pause();
                break;
            }
            cout << "Enter your Postal Code (5 digits): ";
            getline(cin, postalCode);
            if (!isValidPostalCode(postalCode)) {
                cout << "Invalid Postal Code.\n";
                pause();
                break;
            }

            if (!nationalElection.findVoter(cnic, postalCode)) {
                cout << "You are not registered to vote in this election.\n";
                pause();
                break;
            }

            cout << "\nEnter the number of the candidate you want to vote for: ";
            cin >> candidateIndex;
            cin.ignore();

            nationalElection.secureVote(cnic, postalCode, candidateIndex - 1);
            pause();
            break;
        }
        case 2:
            provincialElection.castProvincialVote();
            pause();
            break;
        case 3:
            cout << "Return to main menu.\n";
            break;
        default:
            cout << "Invalid election choice.\n";
            pause();
        }
    } while (electionChoice != 3);
}

class Admin {
private:
    bool isUsernameExists(const string& username) {
        ifstream file("admins.txt");
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(',');
            string storedUsername = line.substr(0, pos);
            if (storedUsername == username) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    bool isValidPassword(const string& password) {
        return password.length() >= 6;
    }

    bool isValidName(const string& name) {
        for (size_t i = 0; i < name.length(); i++) {
            if (!isalpha(name[i]) && name[i] != ' ')
                return false;
        }
        return !name.empty();
    }

    bool isValidCNIC(const string& cnic) {
        string cleanedCNIC;
        for (size_t i = 0; i < cnic.length(); i++) {
            if (isdigit(cnic[i])) cleanedCNIC += cnic[i];
        }
        return cleanedCNIC.length() == 13;
    }

    bool isCNICUnique(const string& cnic) {
        ifstream file("voters.txt");
        string line;

        string cleanedCNIC;
        for (size_t i = 0; i < cnic.length(); i++) {
            if (isdigit(cnic[i])) cleanedCNIC += cnic[i];
        }

        while (getline(file, line)) {
            stringstream ss(line);
            string name, storedCNIC, temp;
            int storedId;
            getline(ss, name, ',');
            ss >> storedId;
            getline(ss, temp, ','); 
            getline(ss, storedCNIC, ',');
            if (cleanedCNIC == storedCNIC) {
                file.close();
                return false; 
            }
        }

        file.close();
        return true; 
    }

    bool isValidPostalCode(const string& postalCode) {
        if (postalCode.length() != 5) return false;
        for (size_t i = 0; i < postalCode.length(); i++) {
            if (!isdigit(postalCode[i])) return false;
        }
        return true;
    }

    bool isVoterIdUnique(int id) {
        ifstream file("voters.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name;
            int storedId;
            getline(ss, name, ',');
            ss >> storedId;
            if (storedId == id) {
                file.close();
                return false;
            }
        }
        file.close();
        return true;
    }

public:
    void registerAdmin() {
        string username, password;

        while (true) {
            cout << "Enter username: ";
            getline(cin, username);
            if (isUsernameExists(username)) {
                cout << "Username already exists. Enter another.\n";
            }
            else break;
        }

        while (true) {
            cout << "Enter password: ";
            getline(cin, password);
            if (isValidPassword(password)) break;
            else cout << "Password should consist of at least 6 characters.\n";
        }

        ofstream file("admins.txt", ios::app);
        if (file.is_open()) {
            file << username << "," << password << endl;
            file.close();
            cout << "Admin registered successfully.\n";
        }
        else {
            cout << "Error in saving data.\n";
        }
    }

    bool loginAdmin() {
        string username, password;
        cout << "\n\n\n";
        cout << "Enter username: ";
        getline(cin, username);
        cout << "Enter password: ";
        getline(cin, password);

        ifstream file("admins.txt");
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(',');
            string storedUsername = line.substr(0, pos);
            string storedPassword = line.substr(pos + 1);
            if (storedUsername == username && storedPassword == password) {
                cout << "Admin login successful.\n";
                file.close();
                return true;
            }
        }
        file.close();
        cout << "Invalid username or password.\n";
        return false;
    }

    void addVoter(const string& filename) {
        pause();
        clearScreen();
        ofstream file(filename, ios::app);
        if (!file) {
            cout << "Error opening file: " << filename << endl;
            return;
        }

        string name, cnic, postalCode, province, region;
        int id;

        while (true) {
            cout << "Enter Name: ";
            getline(cin, name);
            if (isValidName(name)) break;
            cout << "Invalid name.\n";
        }

        while (true) {
            cout << "Enter ID: ";
            if (cin >> id && isVoterIdUnique(id)) break;
            cout << "Invalid or duplicate ID! Must be a unique integer.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cin.ignore();

        while (true) 
        {
            cout << "Enter CNIC (without dashes): ";
            getline(cin, cnic);

            if (isValidCNIC(cnic)) 
            {  
                if (isCNICUnique(cnic)) 
                { 
                    break;
                }
                else 
                {
                    cout << "This CNIC is already registered. Please enter a unique CNIC.\n";
                }
            }
            else
            {
                cout << "Invalid CNIC. Must be exactly 13 digits.\n";
            }
        }

        while (true) {
            cout << "Enter Postal Code (5 digits): ";
            getline(cin, postalCode);
            if (isValidPostalCode(postalCode)) break;
            cout << "Invalid postal code. Must be 5 digits.\n";
        }

        const string provinces[4] = { "Punjab", "Sindh", "Khyber Pakhtunkhwa", "Balochistan" };
        const string regions[4][3] = {
            {"Lahore", "Rawalpindi", "Multan"},
            {"Karachi", "Hyderabad", "Sukkur"},
            {"Peshawar", "Abbottabad", "Mardan"},
            {"Quetta", "Gwadar", "Turbat"}
        };

        cout << "\nSelect Province for voter:\n";
        for (int i = 0; i < 4; i++) {
            cout << i + 1 << ". " << provinces[i] << endl;
        }

        int provinceChoice;
        cout << "Enter province number (1-4): ";
        cin >> provinceChoice;
        cin.ignore();

        // Validate provinceChoice 
        if (provinceChoice < 1 || provinceChoice > 4) {
            cout << "Invalid province selection. Defaulting to Punjab (1).\n";
            provinceChoice = 1;  // Reset to Punjab (index 0)
        }

        // Now provinceChoice is guaranteed to be 1-4
        province = provinces[provinceChoice - 1];

        cout << "\nSelect Region in " << province << ":\n";
        for (int j = 0; j < 3; j++) {
            cout << j + 1 << ". " << regions[provinceChoice - 1][j] << endl;
        }

        int regionChoice;
        cout << "Enter region number (1-3): ";
        cin >> regionChoice;
        cin.ignore();

        // Validate regionChoice (force it to be 1-3)
        if (regionChoice < 1 || regionChoice > 3) {
            cout << "Invalid region selection. Defaulting to first region (1).\n";
            regionChoice = 1;  // Reset to first region (index 0)
        }

        // Now regionChoice is guaranteed to be 1-3
        region = regions[provinceChoice - 1][regionChoice - 1];
        file << name << "," << id << "," << cnic << "," << postalCode << "," << province << "," << region << endl;
        file.close();
        cout << "Voter added successfully.\n";
    }

    void addCandidateToElection(Election& election) {
        pause();
        clearScreen();
        string name, party;
        while (true) {
            cout << "Enter Candidate Name: ";
            getline(cin, name);
            if (isValidName(name)) break;
            cout << "Invalid name.\n";
        }
        while (true) {
            cout << "Enter Party Name: ";
            getline(cin, party);
            if (isValidName(name)) break;
            cout << "Invalid party name.\n";
        }

        election.addCandidate(name, party);
    }

    void adminMenu(NationalElection& nationalElection, ProvincialElection& provincialElection) {
        bool isLoggedIn = false;
        int choice;

        do {
            clearScreen();
            SetTextColor(192);
            cout << " Admin Menu: " << endl;
            SetTextColor(12);
            cout << "1. Register Admin\n";
            cout << "2. Login Admin\n";
            cout << "3. Add Voter\n";
            cout << "4. Add Candidate\n";
            cout << "5. Display Candidates\n";
            cout << "6. Show Results\n";
            cout << "7. Log out\n";
            cout << "Choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1:
                registerAdmin();
                pause();
                break;
            case 2:


                if (isLoggedIn = loginAdmin())
                {
                    pause();
                    clearScreen();
                    login();
                }
                pause();
                clearScreen();
                break;
            case 3:
                if (isLoggedIn) {
                    addVoter("voters.txt");
                    nationalElection.loadVotersFromFile("voters.txt");
                    provincialElection.loadVotersFromFile("voters.txt");
                }
                else {
                    cout << "Please login first.\n";
                }
                pause();
                break;
            case 4:
                if (isLoggedIn) {
                    pause();
                    clearScreen();
                    cout << "Add candidate to:\n";
                    cout << "1. National Election\n";
                    cout << "2. Provincial Election\n";
                    int electionChoice;
                    cout << "Enter choice:";
                    cin >> electionChoice;
                    cin.ignore();
                    if (electionChoice == 1) {
                        addCandidateToElection(nationalElection);
                    }
                    else if (electionChoice == 2) {
                        addCandidateToElection(provincialElection);
                    }
                    else {
                        cout << "Invalid choice.\n";
                    }
                }
                else {
                    cout << "Please login first.\n";
                }
                pause();
                break;
            case 5:
                pause();
                clearScreen();
                cout << "Display candidates for:\n";
                cout << "1. National Election\n";
                cout << "2. Provincial Election\n";
                int displayChoice;
                cout << "Enter choice:";
                cin >> displayChoice;
                cin.ignore();
                if (displayChoice == 1) {
                    nationalElection.displayCandidates();
                }
                else if (displayChoice == 2) {
                    provincialElection.displayCandidates();
                }
                else {
                    cout << "Invalid choice.\n";
                }
                pause();
                break;
            case 6:
                pause();
                clearScreen();
                cout << "Show results for:\n";
                cout << "1. National Election\n";
                cout << "2. Provincial Election\n";
                int resultChoice;
                cout << "Enter choice:";
                cin >> resultChoice;
                cin.ignore();
                if (resultChoice == 1) {
                    nationalElection.showResults();
                    nationalElection.showWinner();
                }
                else if (resultChoice == 2) {
                    provincialElection.showResults();
                    provincialElection.showWinner();
                }
                else {
                    cout << "Invalid choice.\n";
                }
                pause();
                break;
            case 7:
                pause();
                clearScreen();
                logout();
                pause();
                clearScreen();
                return;
            default:
                cout << "Invalid choice.\n";
                pause();
            }
        } while (choice != 7);
    }
};

int main() {
    NationalElection nationalElection("National Election 2025", "Pakistan");
    ProvincialElection provincialElection("Provincial Election 2025", "Pakistan");
    Admin admin;
    Voter voter;

    // Load candidates and voters for both elections at startup
    nationalElection.loadCandidatesFromFile("national_candidates.txt");
    provincialElection.loadCandidatesFromFile("provincial_candidates.txt");
    nationalElection.loadVotersFromFile("voters.txt");
    provincialElection.loadVotersFromFile("voters.txt");

    cout << "Let's start" << endl;
    pause();
    clearScreen();
    frontpage();
    pause();
    clearScreen();
    SetTextColor(192);
    cout << " Welcome to Electronic Voting System! " << endl;
    SetTextColor(12);

    int userChoice;
    do {
        SetTextColor(12);
        cout << "Are you:\n";
        cout << "1. Admin\n";
        cout << "2. Voter\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> userChoice;
        cin.ignore();

        switch (userChoice) {
        case 1:
            admin.adminMenu(nationalElection, provincialElection);
            break;
        case 2:
            voter.voterMenu(nationalElection, provincialElection);
            break;
        case 3:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            pause();
        }
    } while (userChoice != 3);

    return 0;
}
