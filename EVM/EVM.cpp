#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
using namespace std;
const int MAX_USERS = 10;
const int MAX_CANDIDATES = 10;
// Function to change text color
void SetTextColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
// Function to set position of text on page
void gotoxy(int x, int y)
{
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, coordinate);
}

void clearScreen()
{
    system("cls");
}

// Function to pause the program
void pause()
{
    system("pause"); // Waits for user input to continue
}

// function to display e voting
void frontpage()
{
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
void login()
{
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

void logout()
{
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

class User
{
protected:
    string username;
    string password;
public:
    User(string u, string p) : username(u), password(p) {}
    bool login(const string& user, const string& pass)
    {
        return username == user && password == pass;
    }

    virtual void showMenu() = 0;
};

class Voter : public User 
{
    int voterId;
    string cnic;
    string postalCode;
    bool hasVoted = false;
public:
    Voter() : User("", ""), voterId(0) {}
    Voter(string u, string p, int id, string cnic, string postal)
        : User(u, p), voterId(id), cnic(cnic), postalCode(postal) {}

    void showMenu() 
    {
        cout << "Welcome Voter: " << username << endl;
        cout << "1. View Elections" << endl;
        cout << "2. Cast Vote" << endl;
    }

    int getId() const { return voterId; }

    string getPostalCode() const { return postalCode; }

    string getCNIC() const { return cnic; }

    bool getHasVoted() const { return hasVoted; }

    void setHasVoted(bool voted) { hasVoted = voted; }

    static bool isValidCNIC(const string& cnic) 
    {
        return voterId;
    }
    void viewElections() {
        cout << "Displaying available elections..." << endl;
    }
    void castVote() {
        cout << "Casting vote..." << endl;
    }
    // Load voter credentials from file (as already done)
    static void loadVoterData(Voter voters[], int& numVoters) {
        ifstream file("voters.txt");
        if (!file) {
            cout << "Error opening voters file!" << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string username, password;
            int id;
            getline(ss, username, ',');
            getline(ss, password, ',');
            ss >> id;
            voters[numVoters++] = Voter(username, password, id);
        }
        file.close();
    }
    string getPostalCode() {
        return postalCode;
    }
    static bool isValidCNIC(const string& cnic) {
        if (cnic.length() != 11) {
            return false;
        }
        for (int i = 0; i < cnic.length(); i++) {
            if (cnic[i] < '0' || cnic[i] > '9') {
                return false;
            }
        }
        return true;
        return cnic.length() == 11 && all_of(cnic.begin(), cnic.end(), ::isdigit);
    }
    static bool isValidPostalCode(const string& code) {
        if (code.length() != 5) {
            return false;
        }
        for (int i = 0; i < code.length(); i++) {
            if (code[i] < '0' || code[i] > '9') {
                return false;
            }
        }
        return true;
    }

    void inputRegionInfo() {
        do {
            cout << "Enter 11-digit CNIC: ";
            cin >> cnic;
        } while (!isValidCNIC(cnic));
        do {
            cout << "Enter 5-digit Postal Code: ";
            cin >> postalCode;
        } while (!isValidPostalCode(postalCode));
    }
};

class Candidate 
{
    string name;
    string party;
    int votes;
public:
    Candidate() : votes(0) {}
    Candidate(string n, string p) : name(n), party(p), votes(0) {}
    void incrementVotes() { 
        votes++; 
    }
    void displayInfo() const 
    {
        cout << "Name: " << name << ", Party: " << party << ", Votes: " << votes << endl;
    }
    string getName() const { 
        return name; 
    }
    string getParty() const { 
        return party; 
    }
    int getVotes() const {
        return votes;
    }
};

class Election 
{
protected:
    string title;
    Candidate candidates[MAX_CANDIDATES];
    int candidateCount;
    Voter voters[100];
    int voterCount;

public:
    Election(string t) : title(t), candidateCount(0), voterCount(0) {}

    virtual void showElectionType() 
    {
        cout << "Generic Election" << endl;
    }

    void addCandidate(string name, string party) {
        if (candidateCount < MAX_CANDIDATES) 
        {


            int id = candidateCount + 1; // or any unique ID logic
            Candidate c(name, party);

            // Save to file
            ofstream file("candidates.txt", ios::app); // append mode
            if (file.is_open()) 
            {
                file << name << "," << party << "," << 0 << endl; // votes = 0 initially
                file.close();
            }
            else 
            {
                cout << "Error: Could not open candidate file for writing." << endl;
                return;
            }

            // Add to array
            candidates[candidateCount++] = c;

            cout << "Candidate '" << name << "' added and stored in file." << endl;
        }
        else 
        {
            cout << "Maximum candidates reached!" << endl;
        }
    }


    void displayCandidates() 
    {
    ifstream file("candidates.txt");
    if (!file.is_open()) 
    {
        cout << "Error: Could not open candidate file for reading." << endl;
        return;
    }

    cout << "\n--- Candidates List ---\n";
    string line;
    int count = 1;

    while (getline(file, line)) 
    {
        stringstream ss(line);
        string idStr, name, party, votesStr;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, party, ',');
        getline(ss, votesStr, ',');

        cout << count++ << ". ";
        cout << "ID: " << idStr << ", Name: " << name << ", Party: " << party << ", Votes: " << votesStr << endl;
    }

    file.close();
    }

    void secureVote(string cnic, string postalCode, int candidateIndex) 
    {
        for (int i = 0; i < voterCount; i++) {
            if (voters[i].getCNIC() == cnic && voters[i].getPostalCode() == postalCode) 
            {
                if (voters[i].getHasVoted()) 
                {
                    cout << "You have already voted!" << endl;
                    return;
                }
                if (candidateIndex >= 0 && candidateIndex < candidateCount) 
                {
                    candidates[candidateIndex].incrementVotes();
                    voters[i].setHasVoted(true);
                    cout << "Vote cast for " << candidates[candidateIndex].getName() << "!\n";
                    return;
                }
                else 
                {
                    cout << "Invalid candidate index!" << endl;
                    return;
                }
            }
        }
        cout << "CNIC or Postal Code not found!" << endl;
    }

    void showResults() 
    {
        cout << "\n--- Election Results ---\n";
        for (int i = 0; i < candidateCount; i++) {
            cout << setw(20) << left << candidates[i].getName() << " | Votes: " << candidates[i].getVotes() << endl;
        }
    }

    void showWinner() 
    {
        int maxVotes = -1;
        string winner = "None";
        for (int i = 0; i < candidateCount; i++) 
        {
            if (candidates[i].getVotes() > maxVotes) 
            {
                maxVotes = candidates[i].getVotes();
                winner = candidates[i].getName();
            }
        }
        cout << "\nWinner: " << winner << " with " << maxVotes << " votes!" << endl;
    }
};

class NationalElection : public Election 
{
    string country;
public:
    NationalElection(string title, string c) : Election(title), country(c) {}
    void showElectionType() override {
        cout << "National Election - Country: " << country << endl;
    }
};


class ProvincialElection : public Election 
{
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

    void showElectionType() override 
    {
        cout << "Provincial Election - Province: " << province << endl;
    }

    void castProvincialVote() 
    {
        cout << "\nSelect your Province from the list below:\n";
        for (int i = 0; i < 4; i++) 
        {
            cout << i + 1 << ". " << provinces[i] << endl;
        }

        int provinceChoice;
        cout << "Enter the province number (1-4): ";
        cin >> provinceChoice;
        cin.ignore();

        if (provinceChoice < 1 || provinceChoice > 4) 
        {
            cout << "Invalid province selection.\n";
            return;
        }

        province = provinces[provinceChoice - 1]; // Save selected province
        cout << "\nYou selected: " << province << endl;

        cout << "\nNow select your Region in " << province << ":\n";
        for (int j = 0; j < 3; j++) 
        {
            cout << j + 1 << ". " << regions[provinceChoice - 1][j] << endl;
        }

        int regionChoice;
        cout << "Enter the region number (1-3): ";
        cin >> regionChoice;
        cin.ignore();

        if (regionChoice < 1 || regionChoice > 3) 
        {
            cout << "Invalid region selection.\n";
            return;
        }

        string selectedRegion = regions[provinceChoice - 1][regionChoice - 1];
        cout << "\nYou selected region: " << selectedRegion << endl;

        // Now get CNIC and Postal Code
        string cnic, postalCode;
        cout << "\nEnter your CNIC (without dashes): ";
        getline(cin, cnic);
        cout << "Enter your Postal Code: ";
        getline(cin, postalCode);

        // Show candidates
        displayCandidates();
        int candidateIndex;
        cout << "Enter the number of the candidate you want to vote for: ";
        cin >> candidateIndex;
        cin.ignore();

        // Cast the vote
        secureVote(cnic, postalCode, candidateIndex - 1);
    }

};

// ----------------- Admin Class ---------------------
class Admin 
{
private:
    bool isUsernameExists(const string& username) 
    {
        ifstream file("admins.txt");
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(',');
            string storedUsername = line.substr(0, pos);
            if (storedUsername == username) 
            {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    bool isValidPassword(const string& password) 
    {
        return password.length() >= 6;
    }

    bool isValidName(const string& name) 
    {
        for (char ch : name) 
        {
            if (!isalpha(ch) && ch != ' ')
                return false;
        }
        return !name.empty();
    }

    bool isValidCNIC(const string& cnic) 
    {
        for (char ch : cnic) 
        {
            if (!isdigit(ch) && ch != '-')
                return false;
        }
        return !cnic.empty();
    }

    bool isValidPostalCode(int postalCode) 
    {
        return (postalCode >= 10000 && postalCode <= 99999);
    }

public:
    void registerAdmin() 
    {
        string username, password;

        while (true) 
        {
            cout << "Enter username: ";
            getline(cin, username);
            if (isUsernameExists(username)) 
            {
                cout << "Username already exists. Enter another.\n";
            }
            else break;
        }

        while (true) 
        {
            cout << "Enter password: ";
            getline(cin, password);
            if (isValidPassword(password)) break;
            else cout << "Password should consist of at least 6 characters.\n";
        }

        ofstream file("admins.txt", ios::app);
        if (file.is_open()) 
        {
            file << username << "," << password << endl;
            file.close();
            cout << "Admin registered successfully.\n";
        }
        else 
        {
            cout << "Error in saving data.\n";
        }
    }

    bool loginAdmin() 
    {
        string username, password;
        cout << "Enter username: ";
        getline(cin, username);
        cout << "Enter password: ";
        getline(cin, password);

        ifstream file("admins.txt");
        string line;
        while (getline(file, line)) 
        {
            size_t pos = line.find(',');
            string storedUsername = line.substr(0, pos);
            string storedPassword = line.substr(pos + 1);
            if (storedUsername == username && storedPassword == password) 
            {
                cout << "Admin login successful.\n";
                return true;
            }
        }
        cout << "Invalid username or password.\n";
        return false;
    }

    void addVoter(const string& filename) 
    {
        ofstream file(filename, ios::app);
        if (!file) 
        {
            cout << "Error opening file: " << filename << endl;
            return;
        }

        string name;
        int id;
        string cnic;
        int postalCode;

        while (true) 
        {
            cout << "Enter Name: ";
            getline(cin, name);
            if (isValidName(name)) break;
            cout << "Invalid name.\n";
        }

        while (true) 
        {
            cout << "Enter ID: ";
            if (cin >> id) break;
            cout << "Invalid ID! Must be an integer.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cin.ignore();

        while (true) {
            cout << "Enter CNIC: ";
            getline(cin, cnic);
            if (isValidCNIC(cnic)) break;
            cout << "Invalid CNIC.\n";
        }

        while (true) 
        {
            cout << "Enter Postal Code: ";
            if (cin >> postalCode && isValidPostalCode(postalCode)) break;
            cout << "Invalid postal code.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        file << name << "," << id << "," << cnic << "," << postalCode << endl;
        file.close();
        cout << "Voter added successfully.\n";
    }

    void addCandidateToElection(Election& election) 
    {
        string name, party;
        cout << "Enter Candidate Name: ";
        getline(cin, name);
        cout << "Enter Party Name: ";
        getline(cin, party);

        election.addCandidate(name, party);
    }

    void adminMenu(Election& election) 
    {
        bool isLoggedIn = false;
        int choice;

        do 
        {
            cout << "\nAdmin Menu:\n";
            cout << "1. Register Admin\n";
            cout << "2. Login Admin\n";
            cout << "3. Add Voter\n";
            cout << "4. Add Candidate\n";
            cout << "5. Display Candidates\n";
            cout << "6. Show Results\n";
            cout << "7. Exit\n";
            cout << "Choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) 
            {
            case 1:
                registerAdmin();
                break;
            case 2:
                isLoggedIn = loginAdmin();
                break;
            case 3:
                if (isLoggedIn)
                    addVoter("voters.txt");
                else
                    cout << "Please login first.\n";
                break;
            case 4:
                if (isLoggedIn)
                    addCandidateToElection(election);
                else
                    cout << "Please login first.\n";
                break;
            case 5:
                election.displayCandidates();
                break;
            case 6:
                election.showResults();
                election.showWinner();
                break;
            case 7:
                cout << "Exiting Admin Menu.\n";
                break;
            default:
                cout << "Invalid choice.\n";
            }
        } while (choice != 7);
    }
};

int main() 
{
    NationalElection nationalElection("National Election 2025", "Pakistan");
    ProvincialElection provincialElection("Provincial Election 2025", "Pakistan");
    Admin admin;

    int userChoice;
    cout << "Welcome to the Election System!\n";
    cout << "Are you:\n";
    cout << "1. Admin\n";
    cout << "2. Voter\n";
    cout << "Enter your choice: ";
    cin >> userChoice;
    cin.ignore(); // to clear input buffer

    if (userChoice == 1) 
    {
        // Admin section
        admin.adminMenu(nationalElection); // Admin will manage NationalElection (you can change if needed)
    }
    else if (userChoice == 2) 
    {
        // Voter section
        int electionChoice;
        cout << "\nWhich Election you want to participate in?\n";
        cout << "1. National Election\n";
        cout << "2. Provincial Election\n";
        cout << "Enter your choice: ";
        cin >> electionChoice;
        cin.ignore(); // to clear input buffer

        if (electionChoice == 1) 
        {
            nationalElection.displayCandidates();
            string cnic, postalCode;
            int candidateIndex;
            cout << "\nEnter your CNIC: ";
            getline(cin, cnic);
            cout << "Enter your Postal Code: ";
            getline(cin, postalCode);
            cout << "\nEnter the number of the candidate you want to vote for: ";
            cin >> candidateIndex;
            cin.ignore();

            nationalElection.secureVote(cnic, postalCode, candidateIndex - 1);
        }
        else if (electionChoice == 2) 
        {
            provincialElection.castProvincialVote();
        }
        else 
        {
            cout << "Invalid election choice.\n";
        }
    }
    else 
    {
        cout << "Invalid choice. Exiting program.\n";
    }

    return 0;
}
