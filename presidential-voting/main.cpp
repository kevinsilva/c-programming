#include <iostream>
#include <locale.h>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

int main() {
    // Sets PT character encoding.
    setlocale(LC_ALL, "pt_PT.UTF-8");

    // Seeds random number with different values on each run by using time
    srand((unsigned)time(NULL));

    short vote;
    bool pollsOpen = true;
    const int REGISTERED = 50;
    int totalVotes = 0;
    int candidate_1 = 0, candidate_2 = 0, candidate_3 = 0, candidate_4 = 0, blank = 0, spoilt = 0;

    cout << "\n\t-----------------------------------" << endl;
    cout << "\t   PRESIDENTIAL ELECTION VOTING    " << endl;

    cout << "\t-----------------------------------" << endl;

    cout << "\n\t  Code       Candidate Name     " << endl;


    cout << "\n\t\t1          Candidate A        " << endl;
    cout << "\t\t2          Candidate B        " << endl;
    cout << "\t\t3          Candidate C        " << endl;
    cout << "\t\t4          Candidate D        " << endl;
    cout << "\t\t5          Blank Vote              " << endl;

    cout << "\n\tTo end voting, enter: 0  " << endl;

    cout << "\n\t-----------------------------------" << endl;

    do {
        cout << "\n\t* Please enter the code corresponding to your vote: ";

        while (!(cin >> vote)) {
            cout << "\n\tInvalid code." << endl;
            cout << "\n\tValid Options:" << endl;
            cout << "\t- Your candidate's code (1 to 4)" << endl;
            cout << "\t- 5 for a blank vote" << endl;
            cout << "\t- 0 to end voting" << endl;
            cout << "\n\tEnter one of the valid options: ";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }


        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (vote == 0) {
            pollsOpen = false;
        } else {
            totalVotes++;

            switch (vote) {
                case 1:
                    candidate_1++;
                    break;
                case 2:
                    candidate_2++;
                    break;
                case 3:
                    candidate_3++;
                    break;
                case 4:
                    candidate_4++;
                    break;
                case 5:
                    blank++;
                    break;
                default:
                    spoilt++;
                    break;
            }

            cout << "\tYour vote has been received. Thank you!" <<endl;
        }

    } while (pollsOpen);

    if (!pollsOpen) {
        cout << "\n\tVoting closed." << endl;

        short elected = 1;
        int maxVotes = candidate_1;
        bool tie = false;

        if (candidate_2 > maxVotes)  {
            maxVotes = candidate_2;
            elected = 2;
        } else if (candidate_2 == maxVotes) {
            tie = true;
        }

        if (candidate_3 > maxVotes)  {
            maxVotes = candidate_3;
            elected = 3;
            tie = false;
        } else if (candidate_3 == maxVotes) {
            tie = true;
        }

        if (candidate_4 > maxVotes)  {
            maxVotes = candidate_4;
            elected = 4;
            tie = false;
        } else if (candidate_4 == maxVotes) {
            tie = true;
        }


        cout << "\n\t-----------------------------------" << endl;
        cout << "\t          ELECTION RESULTS         " << endl;
        cout << "\t-----------------------------------" << endl;

        cout << "\n\tCandidate     Votes    Percentage " << endl;

        cout << "\n\tCandidate A " << "\t" << candidate_1 << "\t    " << fixed << setprecision(2) << ((float)candidate_1 / totalVotes) * 100 << "%"<< endl;
        cout << "\tCandidate B " << "\t" << candidate_2 << "\t    " << fixed << setprecision(2) << ((float)candidate_2 / totalVotes) * 100 << "%"<< endl;
        cout << "\tCandidate C " << "\t" << candidate_3 << "\t    " << fixed << setprecision(2) <<  ((float)candidate_3 / totalVotes) * 100 << "%"<< endl;
        cout << "\tCandidate D " << "\t" << candidate_4 << "\t    " << fixed << setprecision(2) << ((float)candidate_4 / totalVotes) * 100 << "%"<< endl;


        cout << "\n\t-----------------------------------" << endl;

        cout << "\n\tBlank Votes: " << blank << endl;
        cout << "\tSpoilt Votes: " << spoilt << endl;
        cout << "\tAbstention: " << fixed << setprecision(2) << (float)(REGISTERED - totalVotes) * 100 / REGISTERED << "%"<< endl;
        cout << "\n\t-----------------------------------" << endl;

        if (tie) {

            bool tied_1 = false, tied_2 = false, tied_3 = false, tied_4 = false;

            if (candidate_1 == maxVotes) tied_1 = true;
            if (candidate_2 == maxVotes) tied_2 = true;
            if (candidate_3 == maxVotes) tied_3 = true;
            if (candidate_4 == maxVotes) tied_4 = true;


            cout << "\n\tTECHNICAL TIE BETWEEN:\n" << endl;

            cout << (tied_1 ? "\t* Candidate A\n" : " ");
            cout << (tied_2 ? "\t* Candidate B\n" : " ");
            cout << (tied_3 ? "\t* Candidate C\n" : " ");
            cout << (tied_4 ? "\t* Candidate D\n" : " ");
            cout << "\n\tThe prevailing tie-breaking\n\tmechanisms have been activated..." << endl;

            cout << "\n\t-----------------------------------" << endl;

            while (tie) {
                // Generates random number between 1 and 4
                int random = rand() % 5;

                switch (random) {
                    case 1:
                        if (tied_1) {
                            elected = 1;
                            tie = false;
                        }
                        break;
                    case 2:
                        if (tied_2) {
                            elected = 2;
                            tie = false;
                        }
                        break;
                    case 3:
                        if (tied_3) {
                            elected = 3;
                            tie = false;
                        }
                        break;
                    case 4:
                        if (tied_4) {
                            elected = 4;
                            tie = false;
                        }
                        break;
                    default:
                        break;
                }
            }
        }

        cout << "\n\tELECTED PRESIDENT: " << (elected == 1 ? "Candidate A" : elected == 2 ? "Candidate B" : elected == 3 ? "Candidate C" : "Candidate D") << endl;
        cout << "\n\t-----------------------------------" << endl;
    }
    cout << "\n\t";
}
