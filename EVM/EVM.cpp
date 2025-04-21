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
    User(string u, string p) : username(u), password(p) {} // constructor initializer list
     bool login(const string& user, const string& pass) {  // function to check whether correct(pass or user)
        return username == user && password == pass;
     }
    virtual void showMenu() = 0; // pure virtual function
};
class Admin : public User {
public:
    Admin(string u, string p) : User(u, p) {}
    void showMenu() {
        cout << "Welcome Admin: " << username << endl;
        cout << "1. Create Election" << endl;
        cout << "2. View Results" << endl;
        cout << "3. End Election" << endl;
    }
    void createElection() {
        cout << "Creating Election..." << endl;
    }
    void viewResults() {
        cout << "Viewing Election Results..." << endl;
    }
    void endElection() {
        cout << "Ending Election..." << endl;
    }
    // Save election results (admin might save new candidates or changes)
    void saveElectionResultsToFile(const string& filename, const string& electionResults) {
        ofstream file(filename, ios::app);   //existing file append
        if (!file) {
            cout << "Error opening file!" << endl;
            return;
        }
        file << electionResults << endl;
        file.close();
    }
};
class Voter : public User {
    int voterId;
    string unionCouncilCode;
public:
    Voter(string u, string p, int id, string code) : User(u, p), voterId(id), unionCouncilCode(code) {}
    string getUnionCouncilCode() { 
        return unionCouncilCode; 
    }
    void showMenu() {
        cout << "Welcome Voter: " << username << endl;
        cout << "1. View Elections" << endl;
        cout << "2. Cast Vote" << endl;
    }
    int getId() {
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
            getline(ss, code, ',');
            voters[numVoters++] = Voter(username, password, id, code);
        }
        file.close();
    }
};
class Candidate {
private:
    string name;
    string party;
    int votes;

public:
    Candidate(string n, string p) : name(n), party(p), votes(0) {}
    void incrementVotes() {
        votes++;
    }
    void displayInfo() const {
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
    void saveToFile(ofstream& file) {
        file << name << "," << party << "," << votes << endl;
    }
    static Candidate loadFromFile(const string& data) {   
        stringstream ss(data);
        string name, party;
        int votes;
        getline(ss, name, ',');
        getline(ss, party, ',');
        ss >> votes;
        return Candidate(name, party);
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


    void secureVote(string cnic, string postalCode, int candidateId)
    {
        bool voterFound = false;

        for (int i = 0; i < voterCount; i++)
        {
            if (voters[i].cnic == cnic && voters[i].postalCode == postalCode)
            {
                voterFound = true;

                if (voters[i].hasVoted)
                {
                    cout << "\n You have already voted!" << endl;
                    return;
                }

                bool candidateFound = false;
                for (int j = 0; j < candidateCount; j++)
                {
                    if (candidates[j].getId() == candidateId)
                    {
                        candidates[j].addVote();
                        voters[i].hasVoted = true;
                        cout << "\n Vote cast for " << candidates[j].getName() << "!\n";
                        candidateFound = true;
                        break;
                    }
                }

                if (!candidateFound)
                {
                    cout << "\n Invalid Candidate ID!\n";
                }

                return;
            }
        }
        if (!voterFound) {
            cout << "\n CNIC or Postal Code did not match our records!\n";
        }
    }
    void showResults()
    {
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


