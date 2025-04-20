#include<iostream>
#include<string>
using namespace std;
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
};