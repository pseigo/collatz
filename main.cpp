/*
 * Peyton Seigo, 2017
 *
 * This program calculates the steps taken for
 * a given number according to the Collatz
 * Conjecture.
*/


#include <iostream>
#include <map>
#include <limits>

using namespace std;

// recursive implementation of collatz
int collatzR(uint64_t n)
{
    if (n == 1) {
        return 0; // the base case should always cover the simplest case!
    } else if (n % 2 == 0) {
        return 1 + collatzR(n/2); // "n" is even
    } else {
        return 2 + collatzR((3*n + 1)/2); // "n" is odd
    }
}
    /* INFO ABOUT ODD CASE
     * We return 1 + collatz(...) because the '1'
     * accounts for the current 'step,' plus
     * whatever the next step happens to be.
     *
     * For odd numbers, instead of returning:
     *     1 + collatz(3*n +1)
     * I have instead decided to return:
     *     2 + collatz( (3*n + 1) / 2 )
     * The 'odd' case ALWAYS results in an even
     * number, therefore inevitably leading to
     * the 'even' case. We're able to save some
     * cycles by combining two cases into one
     * and accounting for the condensed steps by
     * adding '2' instead of '1.'
    */

// iterative implementation of collatz
int collatzI(uint64_t n)
{
    int steps = 0;
    while (n > 1) {
        if (n % 2 == 0) {
            n = n/2;
            steps++;
        } else {
            n = (3*n + 1)/2;
            steps+=2;
        }
    }

    return steps;
}

/* =============== Menu Functions =============== */
int getValidInput(int min, int max)
{
    int input;
    do {
        cout << " >> ";
        cin >> input;

        if (!cin.good() || input < min || input > max) {
            cout << "Invalid input. Must be between " << max << " and " << max << endl;
            cin.clear();
            cin.ignore(128, '\n');
        } else {
            cout << '\n';
            break;
        }
    } while (true);
    return input; // only returns once valid input is given
}

void collatzSingleNumber()
{
    cout << "Enter any natural number: " << endl;
    int number = getValidInput(1, 10000000000);

    cout << number << " took " << collatzR(number) << " step(s). \n\n";
}

void collatzMostSteps()
{
    cout << "Enter number of iterations: " << endl;
    int iterations = getValidInput(1, 10000000000);

    // Track which number took the most steps
    map<string, int> mostSteps {{"number", 1}, {"steps", 0}};
    int stepsTaken;

    for (int currentNum = 1; currentNum < iterations; currentNum++) {
        stepsTaken = collatzI(currentNum);

        // if currentNum took more stepsTaken than recorded in mostSteps, update the record
        if (stepsTaken > mostSteps["steps"]) {
            cout << "New record: " << currentNum << " with " << stepsTaken << " steps." << endl;

            mostSteps["number"] = currentNum;
            mostSteps["steps"] = stepsTaken;
        }
    }

    cout << "\n\nFor numbers from 1 to " << iterations << ", \n";
    cout << mostSteps["number"] << " took the most steps with " << mostSteps["steps"] << " iterations." << endl;
}

void collatzMenu()
{
    cout << "This program calculates the steps taken for \n"
        << "a given number according to the Collatz Conjecture. \n" << endl;
    cout << "\t1. Calculate a single number \n"
        << "\t2. Find number which takes most steps within a range" << endl;

    int number;
    switch (getValidInput(1, 2)) {
    case 1:
        collatzSingleNumber();
        break;
    case 2:
        collatzMostSteps();
        break;
    } // END OF SWITCH
}

int main(int argc, char *argv[])
{
    collatzMenu();
    return 0;
}
