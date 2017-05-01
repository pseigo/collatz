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
#include <cstdlib> // atoi

using namespace std;

/* Collatz Functions */
int collatzR(uint64_t n); // recursive implementation of collatz
int collatzI(uint64_t n); // iterative implementation of collatz

/* Menu Functions  */
uint64_t getValidInput(int min, uint64_t max);
void collatzSingleNumber(int argNumber);
void collatzMostSteps(int argIterations);
void collatzMenu();
void parameterError(string exeName);

int main(int argc, char *argv[])
{
    if (argc < 2) // if program has no arguments, call menu
        collatzMenu();
    else { // if argument is passed
        string arg1 = argv[1]; // store parameter in a string
        int number;

        // deals with the case of only passing in one argument.
        // avoids "Segmentation fault" caused by accessing non-existent element.
        if (argc == 3) {
            number = atoi(argv[2]); // convert number argument to string
        } else {
            parameterError(argv[0]);
            return 1;
        }

        if (arg1 == "-single") {
            collatzSingleNumber(number);
        } else if (arg1 == "-steps") {
            collatzMostSteps(number);
        } else {
            parameterError(argv[0]);
            return 1;
        }
    }
    return 0;
}

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
uint64_t getValidInput(int min, uint64_t max)
{
    uint64_t input;
    do {
        cout << " >> ";
        cin >> input;

        if (!cin.good() || input < min || input > max) {
            cout << "Invalid input. Must be between " << min << " and " << max << "\n\n";
            cin.clear();
            cin.ignore(128, '\n');
        } else {
            cout << '\n';
            break;
        }
    } while (true);
    return input; // only returns once valid input is given
}

void collatzSingleNumber(int argNumber)
{
    uint64_t number;
    if (argNumber < 1 || argNumber > 10000000000) {
        cout << "Enter any natural number: " << endl;
        number = getValidInput(1, 10000000000ULL);
    } else {
        number = argNumber;
    }

    cout << number << " took " << collatzR(number) << " step(s)." << endl;
    return;
}

void collatzMostSteps(int argIterations)
{
    uint64_t iterations;
    if (argIterations < 1 || argIterations > 10000000000) {
        cout << "Enter number of iterations: " << endl;
        iterations = getValidInput(1, 10000000000ULL);
    } else {
        iterations = argIterations;
    }

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

    cout << "\nFor numbers from 1 to " << iterations << ", \n";
    cout << mostSteps["number"] << " took the most steps with " << mostSteps["steps"] << " iterations." << endl;
    return;
}

void collatzMenu()
{
    cout << "This program calculates the steps taken for \n"
        << "a given number according to the Collatz Conjecture. \n" << endl;
    cout << "\t1. Calculate a single number \n"
        << "\t2. Find number which takes most steps within a range" << endl;

    uint64_t number;
    switch (getValidInput(1, 2)) {
    case 1:
        collatzSingleNumber(0);
        break;
    case 2:
        collatzMostSteps(0);
        break;
    } // END OF SWITCH
    return;
}

void parameterError(string exeName)
{
    cerr << "Usage: " << exeName << " [-single | -steps] [1 ... 10000000000] \n"
        << "    -single\tCalculates the number following this argument. \n"
        << "    -steps\tCalculate which number takes the most steps within \n\t\ta range defined by the number folllowing this argument. \n" << endl;
    return;
}
