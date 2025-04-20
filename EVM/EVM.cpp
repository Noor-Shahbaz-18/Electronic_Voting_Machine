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



