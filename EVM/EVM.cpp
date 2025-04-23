#include<iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
const int MAX_USERS = 10;
const int MAX_CANDIDATES = 10;
class User {
protected:
    string username;
    string password;
public:
    User(string u, string p) : username(u), password(p) {} // constructor initializor list
    bool login(const string& user, const string& pass) {  // function to check whether correct(pass or user)
        return username == user && password == pass;
     }

    virtual void showMenu() = 0; 
};
class Voter : public User {
    int voterId;
public:
    Voter(string u, string p, int id) : User(u, p), voterId(id) {}
    void showMenu() {
        cout << "Welcome Voter: " << username << endl;
        cout << "1. View Elections" << endl;
        cout << "2. Cast Vote" << endl;
    }
    int getId() const
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
};
class Candidate 
{
private:
    string name;
    string party;
    int votes;

public:
    Candidate(string n, string p) : name(n), party(p), votes(0) {}
    void incrementVotes() 
    {
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
    void saveToFile(ofstream& file) const
    {
        file << name << "," << party << "," << votes << endl;
    }
    static Candidate loadFromFile(const string& data) {
        stringstream ss(data);
        string name, party;
        int votes;
        getline(ss, name, ',');
        getline(ss, party, ',');
        ss >> votes;
        Candidate* c = new Candidate(name, party);
        c->votes = votes;
        return c;
    }
};
// ---------- Base Election Class ----------
class Election {
protected:
    string title;
    Candidate candidates[100];
    Voter voters[100];
    int candidateCount;
    int voterCount;

public:
    Election(string title) : title(title), candidateCount(0), voterCount(0) {}
    virtual void showElectionType() {
        cout << "Generic Election" << endl;
    }
    void addCandidate(string name, int id)
    {
        candidates[candidateCount++] = Candidate(name, id);
        cout << "  - Candidate '" << name << "' added successfully." << endl;
    }
    void showCandidates()
    {
        cout << "\n------------ Candidates ------------\n";
        for (int i = 0; i < candidateCount; i++) {
            cout << "ID: " << candidates[i].getId()
                << " | Name: " << candidates[i].getName() << endl;
        }
    }
    void loadVotersFromFile(const string& filename)
    {
        ifstream file(filename);
        if (!file)
        {
            cout << "Error: Cannot open file " << filename << endl;
            return;
        }
        string name, cnic, postal;
        int id;
        while (getline(file, name, ',')) {
            file >> id;
            file.ignore();
            getline(file, cnic, ',');
            getline(file, postal);
            voters[voterCount++] = Voter(name, id, cnic, postal);
        }
        file.close();
        cout << " Voter data loaded successfully.\n";
    }
    void showCandidates() {
        cout << "\n------------ Candidates ------------\n";
        for (int i = 0; i < candidateCount; i++) {
            cout << "ID: " << candidates[i].getId()
                << " | Name: " << candidates[i].getName() << endl;
        }
    }

    void secureVote(string cnic, string postalCode, int candidateId) {
        bool voterFound = false;
        for (int i = 0; i < voterCount; i++) {
            if (voters[i].cnic == cnic && voters[i].postalCode == postalCode) {
                voterFound = true;

                if (voters[i].hasVoted) {
                    cout << "\n You have already voted!" << endl;
                    return;
                }
                bool candidateFound = false;
                for (int j = 0; j < candidateCount; j++) {
                    if (candidates[j].getId() == candidateId) {
                        candidates[j].addVote();
                        voters[i].hasVoted = true;
                        cout << "\n Vote cast for " << candidates[j].getName() << "!\n";
                        candidateFound = true;
                        break;
                    }
                }

                if (!candidateFound) {
                    cout << "\nInvalid Candidate ID!\n";
                }

                return;
            }
        }
        if (!voterFound) {
            cout << "\n CNIC or Postal Code did not match our records!\n";
        }
    }

    void showResults() {
        cout << "\n------------ Election Results: " << title << " ------------\n";
        for (int i = 0; i < candidateCount; i++) {
            cout << setw(20) << left << candidates[i].getName()
                << " | Votes: " << candidates[i].votes << endl;
        }
    }

    void showWinner() {
        int maxVotes = -1;
        string winner = "None";
        for (int i = 0; i < candidateCount; i++) {
            if (candidates[i].votes > maxVotes) {
                maxVotes = candidates[i].votes;
                winner = candidates[i].getName();
            }
        }
        cout << "\n Winner: " << winner << " with " << maxVotes << " votes!" << endl;
    }
};

// ---------- Derived National Election ----------
class NationalElection : public Election {
    string country;
public:
    NationalElection(string title, string country) : Election(title), country(country) {}

    void showElectionType() override {
        cout << "\nNational Election in " << country << endl;
    }
};
// ---------- Derived Provincial Election ----------
class ProvincialElection : public Election {
    string province;
public:
    ProvincialElection(string title, string province) : Election(title), province(province) {}

    void showElectionType() override {
        cout << "\n Provincial Election in " << province << endl;
    }
};
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
        for (char ch : name) {
            if (!isalpha(ch) && ch != ' ')
                return false;
        }
        return !name.empty();
    }

    bool isValidCNIC(const string& cnic) {
        for (char ch : cnic) {
            if (!isdigit(ch) && ch != '-')
                return false;
        }
        return !cnic.empty();
    }

    bool isValidPostalCode(int postalCode) {
        return (postalCode >= 10000 && postalCode <= 99999);
    }
public:
    void registerAdmin() {
        string username;
        string password;

        while (true) {
            cout << "Enter username: ";
            getline(cin, username);
            if (isUsernameExists(username)) {
                cout << "Username already exists. Enter another username: ";
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
            cout << "Error in data saving to file.\n";
        }
    }
    bool loginAdmin() {
        string username;
        string password;
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
                cout << "Admin login successfully.\n";
                return true;
            }
        }
        cout << "Invalid username or password.\n" << endl;
        return false;
    }
    void addVoter(const string& filename) {
        ofstream file(filename, ios::app);
        if (!file) {
            cout << "Error in opening file: " << filename << endl;
        }

        string name;
        int id;
        string cnic;
        int postalCode;

        while (true) {
            cout << "Enter Name: ";
            getline(cin, name);
            if (isValidName(name)) break;
            cout << "Invalid name. Only alphabets and spaces are allowed.\n";
        }

        while (true) {
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
            cout << "Invalid CNIC. Only digits and hyphens are allowed.\n";
        }

        while (true) {
            cout << "Enter Postal Code: ";
            if (cin >> postalCode && isValidPostalCode(postalCode)) break;
            cout << "Invalid postal code. Must be exactly 5 digits.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        file << name << "," << id << "," << cnic << "," << postalCode << endl;
        file.close();
        cout << "Voter added successfully.\n";
    }
    void addCandidateToElection(Election& election) {
        string name, party;
        cout << "Enter Candidate Name: ";
        getline(cin, name);
        cout << "Enter Candidate Party Name: ";
        getline(cin, party);

        if (election.candidateCount >= MAX_CANDIDATES) {
            cout << "Maximum candidates reached.\n";
            return;
        }

        Candidate* newCandidate = new Candidate(name, party);
        election.candidates[election.candidateCount++] = newCandidate;
        cout << "Candidate added successfully.\n";
    }
    void adminMenu(Election& election) {
        election.loadCandidatesFromFile("candidates.txt");

        bool isLoggedIn = false;
        int choice;

        do {
            cout << "\nAdmin Menu:\n";
            cout << "1. Register Admin\n";
            cout << "2. Login Admin\n";
            cout << "3. Add Voter\n";
            cout << "4. Add Candidate to Election\n";
            cout << "5. Display Candidates\n";
            cout << "6. Show Election Results\n";
            cout << "7. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
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
                if (isLoggedIn) {
                    addCandidateToElection(election);
                    election.saveCandidatesToFile("candidates.txt");
                }
                else
                    cout << "Please login first.\n";
                break;
            case 5:
                election.displayCandidates();
                break;
            case 6:
                election.showResults();
                break;
            case 7:
                cout << "Exiting Admin Menu.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 7);
    }
};



<<<<<<< HEAD
=======


>>>>>>> 6e4901ebb675d519113e8c7a1aeb6b18c805aff6
