#include<iostream>
#include<string>
#include <fstream>
using namespace std;
// ---------- Base Election Class ----------
class Election {
    protected:
        string title;
       Candidate candidates[100];
       Voter voters[100];
        int candidateCount;
        int voterCount;

    public:
        Election(string title) : title(title), candidateCount(0), voterCount(0){}
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