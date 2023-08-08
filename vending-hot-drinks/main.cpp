#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <chrono>
#include <thread>
#include <cstdlib>

using namespace std;

const int NUM_AVAILABLE_COINS = 6;
const string STATE[] = {"INSERT COINS", "CHOOSE OPTION", "TURN OFF"};

int currentState = 0;
float credit = 0;

string drinks[][2] = {
    {"Coffee", "0.25"},
    {"Cappuccino", "0.30"},
    {"Hot Chocolate", "0.35"},
    {"Tea", "0.20"}
};

float coins[NUM_AVAILABLE_COINS][2] = {
        {0.05, 2},
        {0.10, 2},
        {0.20, 2},
        {0.50, 2},
        {1.0, 2},
        {2.0, 2}
};


// PROTOTYPES ------------------------------------------------------------
void getState();
void updateState();
void renderState();
void init();
void showMenu();
void insertCoins();
void chooseOption();
void turnOff();
void showCredit();
void addCredit(float coin);
void returnCredit();
void serveDrink(string drink);
void showValidCoins();
bool isCoinValid(float coin);
float validateCoin(float& coin);
int validateOption(int& input);
char validateChoice();


int main() {
    init();
}

// MAIN FUNCTIONS ---------------------------------------------------

void showMenu() {
    cout << "\n\t***********************************" << endl;
    cout << "\n\t*    HOT DRINKS VENDING MACHINE   *"<< endl;
    cout << "\n\t***********************************\t" << endl;

    cout << "\n\t" << setw(10) << "Option" << setw(10) << "Drink" << setw(14) << "Price" << endl;
    cout << "\n\t" << setw(6) << "1" << setw(11) << drinks[0][0] << setw(17) << drinks[0][1] << "€" << endl;
    cout << "\t" << setw(6) << "2" << setw(16) << drinks[1][0] << setw(11) << drinks[1][1] << "€" << endl;
    cout << "\t" << setw(6) << "3" << setw(15) << drinks[2][0]<< setw(12) << drinks[2][1] << "€" << endl;
    cout << "\t" << setw(6) << "4" << setw(10) << drinks[3][0] << setw(18) << drinks[3][1] << "€" << endl;

    cout << "\n\t----------------------------------\t" << endl;

    cout << "\n\tINSTRUCTIONS" << endl;
    cout << "\n\tTo start: Press ENTER" << endl;
    cout << "\tTo change mode: Insert 0" << endl;
    cout << "\n\t***********************************" << endl;
}


void insertCoins() {
    getState();
    float input;

    while(true) {
        cout << "\n\tInsert coin: ";
        validateCoin(input);

        if (input == 0) break;

        addCredit(input);
        showCredit();
    }

    updateState();
}

void chooseOption() {
    getState();
    showCredit();
    do {
        cout << "\n\tChoose an option (1-4): ";
        int option = validateOption(option);

        if (option == 0) break;

        string optionName = drinks[option - 1][0];
        float optionPrice = stof(drinks[option-1][1]);

        if (credit < optionPrice) {
           cout << "\n\tInsufficient Credit.";
            cout << "\n\tPrice: " << optionPrice << "€\n";
            cout << "\n\tDo you want to add coins? (Y/N): ";

            char choice = validateChoice();

            if (toupper(choice) == 'Y') {
                currentState++;
                break;
            }
        } else {
            serveDrink(optionName);
            credit -= optionPrice;
        }

    } while (credit > 0);

    updateState();
}

void turnOff() {
    getState();

    cout << "\n\tDo you want to turn off the machine? (Y/N): ";
    char choice = validateChoice();

    if (toupper(choice) == 'Y') {
        cout << "\n\tShutting down..." << endl;

        if (credit > 0) {
            cout << "\n\tUnused credit available.\n" << endl;
            returnCredit();
        }
        cout << "\n\t";
    } else {
        updateState();
    }
 }

void init () {
    string input;
    showMenu();

    getline(cin, input);
    if (input.empty()) insertCoins();
    else init();
}

void getState() {
    cout << "\n\t----------------------------------\t" << endl;
    if (currentState == 2) {
        cout << "\t|" << setw(15) << "MODE: " << STATE[currentState] << setw(10) << "|" << endl;
    } else {
        cout << "\t|" << setw(13) << "MODE: " << STATE[currentState] << setw(6) << "|" << endl;
    }
    cout << "\t----------------------------------\t" << endl;
};

void updateState() {
    if (currentState == 2) currentState = 0;
    else currentState++;

    renderState();
}


void renderState() {
    switch(currentState) {
        case 0:
            insertCoins();
            break;
        case 1:
            chooseOption();
            break;
        case 2:
            turnOff();
            break;
        default:
            break;
    }
};


// UTILITARY FUNCTIONS ---------------------------------------------------

void showCredit() {
    cout << "\n\t*" << setw(19) << "CREDIT: " << fixed << setprecision(2) << credit << "€" << setw(10)<< "*" << endl;
}

void addCredit(float coin) {
    for (int i = 0; i < NUM_AVAILABLE_COINS; i++) {
        float coinValue = coins[i][0];

        if (coin == coinValue) {
            coins[i][1]++;
            credit += coin;
        }
    }
}

void returnCredit() {
    showCredit();
    cout << "\n\n\tPlease retrieve coin(s):\n" <<  endl;


    // adds tolerance for precision errors in floating point numbers
    float floatTolerance = 0.0001;

    for (int i = NUM_AVAILABLE_COINS - 1; i >= 0; i--) {
        float coinValue = coins[i][0];
        float coinQuantity = coins[i][1];

        while (coinQuantity > 0 && credit >= coinValue - floatTolerance) {
                   credit -= coinValue;
                   coins[i][1]--;
                   cout << "\t* " << coinValue << "€" << endl;
               }
    }
}

void serveDrink(string drink) {
    cout << "\n\tServing " << drink << "." << endl;
    cout << "\tPlease wait...\n\n" << endl;

    int counter = 0;

    for (int percentage = 0; percentage <= 100; percentage += 20) {
        if (counter == 0) {
            cout << "\t((  "<< endl;
            cout << "\t  ))"<< endl;
            counter++;
        } else {
            cout << "\t  (("<< endl;
            cout << "\t))  "<< endl;
            counter = 0;
        }
        cout << "\t____"<< endl;
        cout << "\t\\__/>"<< setw(5) << percentage << "%\n\n" << endl;

        this_thread::sleep_for(chrono::milliseconds(1500));
    }

    cout << "\n\tATTENTION!" << endl;
    cout << "\tRetrieve your " << drink  << "." << endl;

}

void showValidCoins() {
    cout << "\n\t--------------" << endl;
    cout << "\t  Valid Coins " << endl;
    cout << "\t--------------" << endl;

    int counter = 0;

    for (int i = 0; i < NUM_AVAILABLE_COINS; i++)
    {
        if (counter == 2 && i != NUM_AVAILABLE_COINS -1) {
            cout << "\n";
            counter = 0;
        }
        cout << "\t" << fixed << setprecision(2) << coins[i][0] << "€";
        counter++;
    }

    cout << "\n\t--------------" << endl;
}


bool isCoinValid(float coin) {
    for (int i = 0; i < NUM_AVAILABLE_COINS; i++) {
        float coinValue = coins[i][0];

        if (coin == coinValue) return true;
    }
    return false;
};

float validateCoin(float& input) {
    while (!(cin >> input) || (input != 0 && !isCoinValid(input))) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\n\tINVALID COIN!" << endl;

        showValidCoins();
        cout << "\n\tPlease insert one of the valid coins: ";

    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return input;
}

int validateOption(int& input) {
    while (!(cin >> input) || input < 0 || input > 4) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n\tInvalid Option." << endl;
        cout << "\tPlease enter a valid option (1-4): ";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}

char validateChoice() {
    char choice;

    while ((cin >> choice) && (toupper(choice) != 'Y' && toupper(choice) != 'N' &&  choice != '0')) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n\tInvalid choice. Enter 'Y' or 'N': ";
       }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}
