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
    User(string u, string p) : username(u), password(p) {} 
     bool login(const string& user, const string& pass) const
     {  
        return username == user && password == pass;
     }

    virtual void showMenu() = 0; 
};

class Admin
{
private:
    bool isUsernameExists(const string& username)
    {
        ifstream file("admins.txt");
        string line;
        while (getline(file, line)) 
        {
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
        string username;
        string password;
        // for username
        while (true)
        {
            cout << "Enter username: ";
            getline(cin, username);
            if (isUsernameExists(username))
            {
                cout << "Username already axists. Enter another username: ";
            }
            else
                break;
        }
        // for password
        while (true)
        {
            cout << "Enter password: ";
            getline(cin, password);
            if (isValidPassword(password))
            {
                break;
            }
            else
            {
                cout << "Password should consist of 6 characters. ";

            }
        }
        // to save in file
        ofstream file("admins.txt", ios::app);
        if (file.is_open())
        {
            file << username << "," << password << endl;
            file.close();
            cout << "Admin registered successfully.\n";
        }
        else
        {
            cout << "Error in data saving to file.\n";
        }

    }

    // for login
    bool loginAdmin()
    {
        string username;
        string password;
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
                cout << "Admin login successfully.\n";
                return true;
            }
        }
        cout << "Invalid username or password.\n" << endl;
        return false;
    }

    // add voter
    void addVoter(const string& filename)
    {
        ofstream file(filename, ios::app);
        if (!file)
        {
            cout << "Error in opening of file " << filename << endl;
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
            cout << "Invalid name. Only alphabets and spaces are allowed.\n";
        }

        while (true) 
        {
            cout << "Enter ID: ";
            if (cin >> id) 
                break;
            cout << "Invalid ID! Must be an integer.\n";
            cin.clear(); 
            cin.ignore(1000, '\n'); 
        }
        cin.ignore(); 

        while (true)
        {
            cout << "Enter CNIC: ";
            getline(cin, cnic);
            if (isValidCNIC(cnic)) 
                break;
            cout << "Invalid CNIC. Only digits and hyphens are allowed.\n";
        }

        while (true) 
        {
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

    void addCandidateToElection(Election& election) 
    {
        string name, party;
        cout << "Enter Candidate Name: ";
        getline(cin, name);
        cout << "Enter Candidate Party Name: ";
        getline(cin, party);

        if (election.candidateCount >= MAX_CANDIDATES)
        {
            cout << "Maximum candidates reached.\n";
            return;
        }

        Candidate* newCandidate = new Candidate(name, party);
        election.candidates[election.candidateCount++] = newCandidate;
        cout << "Candidate added successfully\n";
    }
    // menu
    void adminMenu(Election& election) {
        bool isLoggedIn = false;
        int choice;

        do {
            cout << "\nAdmin Menu:\n";
            cout << "1. Register Admin\n";
            cout << "2. Login Admin\n";
            cout << "3. Add Voter\n";
            cout << "4. Add Candidate to Election\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";
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
                cout << "Exiting Admin Menu.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 5);
    }
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
    string getName() const
    { 
        return name;
    }
    string getParty() const 
    {
        return party; 
    }
    int getVotes() const 
    { 
        return votes;
    }
    void saveToFile(ofstream& file) const
    {
        file << name << "," << party << "," << votes << endl;
    }
    static Candidate* loadFromFile(const string& data) {
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
class Election {
public:
    Candidate* candidates[MAX_CANDIDATES];
    int candidateCount;

    Election() : candidateCount(0) {}

    void displayCandidates() const
    {
        cout << "\nCandidates:\n";
        for (int i = 0; i < candidateCount; i++) 
        {
            candidates[i]->displayInfo();
        }
    }

    void showResults() const 
    {
        cout << "\nElection Results:\n";
        for (int i = 0; i < candidateCount; i++)
        {
            candidates[i]->displayInfo();
        }
    }

    ~Election() 
    {
        for (int i = 0; i < candidateCount; i++)
        {
            delete candidates[i];
        }
    }
};


int main() 
{
    Election election;
    Admin admin;
    admin.adminMenu(election);
    cout << "\nProgram terminated.\n";
    return 0;
}


