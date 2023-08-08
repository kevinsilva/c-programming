#include <iostream>
#include <locale.h>
#include <iomanip>
#include <ctime>
#include <sstream>

using namespace std;

// PROTOTYPES ------------------------------------------------------------

void showIntro();
string getCityName();
string getCurrentDate();
int getVisitedHomes();
void getSurveyData(int homes, int channels, int& off, int audience[], int tuning[]);
void showResults(int tv_channels, int audience[], int tuning[], int total, int off, string city);
int validatePositiveInt(int input);
int validateNonNegativeInt(int input);
int validateChannel(int input);
bool validateString(string& input);
float calculatePercentage(int num_channels, int channel, int data[]);
int getArrayTotal(int limit, int array[]);


int main() {

    // Sets PT character encoding.
    setlocale(LC_ALL, "pt_PT.UTF-8");

    const int TV_CHANNELS = 4;
    int audience[TV_CHANNELS] = {0};
    int tuning[TV_CHANNELS] = {0};
    int tvOff = 0;

    showIntro();
    string city = getCityName();
    int visitedHomes = getVisitedHomes();
    getSurveyData(visitedHomes,TV_CHANNELS, tvOff, audience, tuning);
    showResults(TV_CHANNELS, audience, tuning, visitedHomes, tvOff, city);
}



// MAIN FUNCTIONS --------------------------------------------------------

void showIntro() {
    cout << "\n\t-----------------------------------" << endl;
    cout << "\t    TELEVISION AUDIENCE PROGRAM    " << endl;
    cout << "\t-----------------------------------" << endl;
}

string getCityName() {
    string cityName;

    cout << "\n\tEnter city name: ";
    getline(cin, cityName);

    while (!validateString(cityName)) {
        cout << "\n\tInvalid name." << endl;
        cout << "\tEnter a valid name: ";
        getline(cin, cityName);
    }

    return cityName;
}

string getCurrentDate() {
    time_t currentTime = time(nullptr);
    tm info;
    localtime_r(&currentTime, &info);

    // 10 length for date format + null-terminator
    char date[11];
    strftime(date, sizeof(date),"%d/%m/%Y", &info);

    return string(date);
}


int getVisitedHomes() {
    int totalHomes = 0;
    cout << "\n\tEnter the number of surveyed homes: ";
    return validatePositiveInt(totalHomes);
};


void getSurveyData(int homes, int channels, int& tvOff,  int audience[], int tuning[]) {

    int TVsPerHome = 0;
    int channel = 0;
    int viewers = 0;

    for (int i = 0; i < homes; i++) {

        cout << "\n\n\t*           HOUSE N." << i + 1 << "            *" << endl;
        cout << "\n\tEnter the number of TVs turned on: ";

        TVsPerHome = validateNonNegativeInt(TVsPerHome);
        if (TVsPerHome == 0) tvOff++;

        for (int j = 0; j < TVsPerHome; j++) {
            cout << "\n\tTV N." << j + 1 << endl;
            cout << "\t-----------------------------------" << endl;
            cout << "\tWhat was the tuned channel (1-4)? ";
            channel = validateChannel(channel);

            tuning[channel - 1]++;

            cout << "\tHow many people were watching? ";
            viewers = validatePositiveInt(viewers);
            audience[channel - 1] += viewers;
            }
        }
    }

void showResults(int tv_channels, int audience[], int tuning[], int total, int off, string city) {
    cout << "\n\n\t-----------------------------------" << endl;
    cout << "\t  TELEVISION AUDIENCE RESULTS " << endl;
    cout << "\t-----------------------------------" << endl;

    cout << "\n\t" << city << endl;
    cout << "\t"  << getCurrentDate() << endl;

    cout << "\n\tChannel  Audience      Tuning \n" << endl;

    for (int i = 0; i < tv_channels; i++) {
        cout << "\t N." << (i + 1) << " \t" << right << setw(8) << fixed << setprecision(2) << calculatePercentage(tv_channels, i, audience) << "%" << " \t" << setw(12) << fixed << setprecision(2) << calculatePercentage(tv_channels, i, tuning) << "%" << endl;
    }

    cout << "\n\t-----------------------------------" << endl;

    cout << "\n\tTotal Surveyed Homes: " << total << endl;
    cout << "\tTotal Homes with TV Turned On: " << total - off << endl;

    cout << "\n\t-----------------------------------" << endl;
    cout << "\n\t";
}

// UTILITY FUNCTIONS ---------------------------------------------------


int validatePositiveInt(int input) {
    while (!(cin >> input) || input <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n\tInvalid number." << endl;
        cout << "\tPlease enter a number greater than zero: ";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}

int validateNonNegativeInt(int input) {
    while (!(cin >> input) || input < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n\tInvalid number." << endl;
        cout << "\tPlease enter a number greater than or equal to zero: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}

int validateChannel(int input) {
    while (!(cin >> input) || input < 1 || input > 4) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n\tInvalid channel." << endl;
        cout << "\tPlease enter a channel from 1 to 4 (inclusive): ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}

bool validateString(string& input)
{
    if (input.empty()) return false;

    for (const char c : input) {
        if (!isalpha(c) && !isspace(c))
            return false;
    }

    return true;
}


float calculatePercentage(int num_channels, int channel, int data[]) {

    int total = getArrayTotal(num_channels, data);

    return (float)data[channel] / total * 100;
}

int getArrayTotal(int limit, int array[]) {
    int total = 0;

    for (int i = 0; i < limit; i++) {
        total += array[i];
    }
    return total;
}
