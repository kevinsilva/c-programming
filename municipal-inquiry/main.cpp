#include <stdio.h>
#include <locale.h>

int main() {
    // Sets PT character encoding.
    setlocale(LC_ALL, "pt_PT.UTF-8");

    const int TOTAL_INHABITANTS = 128616;

    int totalHouseholds;
    short numberOfChildren;
    float income;
    float totalIncome = 0, highestIncome = 0, lowestIncome = 0;
    int totalChildren = 0, childless = 0, incomeLessThan900 = 0;

    printf("\n\t***********************************");
    printf("\n\t*    MUNICIPAL INQUIRY PROGRAM    *");
    printf("\n\t***********************************\n\n\t");

    printf("Enter total surveyed households: ");
    while (scanf("%i", &totalHouseholds) != 1 || totalHouseholds <= 0 || totalHouseholds > TOTAL_INHABITANTS) {
           printf("\n\tInvalid number.\n\tPlease enter a value between 1 and %i (excluding): ", TOTAL_INHABITANTS);

           while (getchar() != '\n');
       }


    while (getchar() != '\n');

    for (int i = 1; i <= totalHouseholds; i++) {
        printf("\n\n\t*      HOUSEHOLD N.%i     *\n\n\t", i);

        printf("Enter monthly household income (e.g. 760,00): ");
        while(scanf("%f", &income) != 1 || income < 0) {
            printf("\n\tInvalid income.\n\tPlease enter a positive value or zero: ");

            while (getchar() != '\n');
        }

        while (getchar() != '\n');

        totalIncome += income;

        if (income > highestIncome) highestIncome = income;
        if (i == 1 || income < lowestIncome) lowestIncome = income;
        if (income < 900) incomeLessThan900++;

        printf("\n\tEnter number of children in the household: ");
        while(scanf("%hi", &numberOfChildren) != 1 || numberOfChildren < 0) {
            printf("\n\tInvalid number of children.\n\tPlease enter a positive or zero value: ");

            while (getchar() != '\n');
        }

        while (getchar() != '\n');

        if (numberOfChildren == 0) childless++;
        else totalChildren += numberOfChildren;
    }

    float averageIncome = (float)totalIncome / totalHouseholds;
    float averageNumberOfChildren = (float)totalChildren / totalHouseholds;

    printf("\n\n\t***********************************");
    printf("\n\t*   MUNICIPAL INQUIRY RESULTS     *");

    printf("\n\t***********************************\n\n\t");

    printf("Average Household Income: %.2f€\n\t", averageIncome);
    printf("Average Number of Children: %.2f Child(ren)\n\t", averageNumberOfChildren);
    printf("Highest Income: %.2f€\n\t", highestIncome);
    printf("Lowest Income: %.2f€\n\t", lowestIncome);
    printf("Percentage of Childless Households: %.2f%%\n\t", ((float)childless / totalHouseholds) * 100);
    printf("Percentage of Households with Income Less than 900.00€: %.2f%%\n\t", ((float)incomeLessThan900 / totalHouseholds) * 100);
    printf("\n\t***********************************\n\n\t");

    return 0;
}
