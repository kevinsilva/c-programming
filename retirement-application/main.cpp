#include <iostream>
#include <ctime>
#include <locale.h>

using namespace std;

int main() {
    // Sets PT character encoding.
    setlocale(LC_ALL, "pt_PT.UTF-8");

    // Gets current year with ctime's localtime function.
    time_t now = time(NULL);
    tm *tm_local = localtime(&now);
    int currentYear = tm_local -> tm_year + 1900;

    // Declared CONST for easing possible future changes.
    const short MINIMUM_AGE = 18, MAX_AGE = 70;
    const short REQ_RETIREMENT_AGE = 65, REQ_WORK_YEARS = 30;
    const short MIN_REQ_RETIREMENT_AGE = 60, MIN_REQ_WORK_YEARS = 25;

    int employeeNumber, birthYear, admissionYear;
    char addData = 'Y';

    cout << "\n\t-----------------------------------" << endl;
    cout << "\t    RETIREMENT REQUEST PROGRAM     " << endl;
    cout << "\t-----------------------------------" << endl;

    do {

        cout << "\n\tEnter employee number: ";

        if (!(cin >> employeeNumber) || employeeNumber <= 0) {
            cout << "\tInvalid number." << endl;
            cout << "\tThe number should be a positive integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\tEnter birth year: ";

        while (!(cin >> birthYear) || currentYear - birthYear < MINIMUM_AGE  || currentYear - birthYear > MAX_AGE) {
            cout << "\n\tInvalid birth year." << endl;
            cout << "\tAge should be above 18 and below 70." << endl;
            cout << "\n\tPlease enter a valid birth year: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\tEnter starting year of employment: ";

        while (!(cin >> admissionYear) || admissionYear < birthYear + MINIMUM_AGE  || admissionYear > birthYear + MAX_AGE || admissionYear > currentYear) {
            cout << "\n\tInvalid year of employment start." << endl;
            cout << "\tThe start of employment should be after 18 and below 70." << endl;
            cout << "\n\tPlease enter a valid year of employment start: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int age = currentYear - birthYear;
        int yearsOfActivity = currentYear - admissionYear;

        cout << "\n\t-----------------------------------" << endl;
        cout << "\t           EMPLOYEE DATA           " << endl;
        cout << "\t-----------------------------------" << endl;
        cout << "\n\t Number: " << employeeNumber << endl;
        cout << "\t Age: " << age << endl;
        cout << "\t Years of activity: " << yearsOfActivity << endl;


        if (age >= REQ_RETIREMENT_AGE || yearsOfActivity >= REQ_WORK_YEARS || (age >= MIN_REQ_RETIREMENT_AGE && yearsOfActivity >= MIN_REQ_WORK_YEARS)) {
            cout << "\n\tThe employee is eligible for retirement." << endl;
        } else {
            cout << "\n\tThe employee is not yet eligible for retirement." << endl;
            cout << "\n\tThe employee needs one of the following requirements:" << endl;
            cout << "\t * " << REQ_RETIREMENT_AGE - age << " more years of age." << endl;
            cout << "\t * " << REQ_WORK_YEARS - yearsOfActivity << " more years of activity." << endl;
            cout << "\t * " << MIN_REQ_RETIREMENT_AGE - age << " more years of age and " << MIN_REQ_WORK_YEARS - yearsOfActivity << " more years of activity." << endl;
        }

        cout << "\n\tDo you want to enter more data? (Y/N): ";

        cin >> addData;
        addData = toupper(addData);
        cout << "\n\t";

    } while (addData == 'Y');
}


