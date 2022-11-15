/* 
 * File:   main.cpp
 * Author: Arthur Choy
 * Created on November 15, 2022, 1:20 AM
 */

#include <cstdlib>
#include <iostream>
#include <random>
using namespace std;

bool checkValidity(float, float, float);
/*
 * 
 */
int main(int argc, char** argv) {
    // Code help from:
    // https://stackoverflow.com/questions/19652657/c-create-a-random-decimal-between-0-1-and-10
    // Random number generator initialization
    random_device rd;
    default_random_engine generator(rd());
    uniform_real_distribution<float> distribution(0, 1);
    
    // Initialize variables
    int counter = 0, trials = 100000;
    int distType;
    
    // Get method in choosing where to break stick
    cout << "Please enter the number corresponding to how you'd like to break the stick: " << endl;
    cout << "1 - Break stick at two random places" << endl;
    cout << "2 - Break stick once, then break remainder" << endl;
    cin >> distType;
    
    // Run 100K trials (will result in percentage with 3 decimal precision, no more no less)
    for(int i = 0; i < 100000; i++) {
        // Randomly generate A
        float A = distribution(generator);
        // Randomly generate B based on user preference
        float B;
        if(distType == 2) {
            uniform_real_distribution<float> distributionB(A, 1);
            B = distributionB(generator);
        }
        else B = distribution(generator);
        
        // A is assumed to be less than B (more left on the stick than B)
        if(A > B) {
            float temp = B;
            B = A;
            A = temp;
        }
        
        // Check triangle validity, if valid, hit
        if(checkValidity(A, (B-A), (1-B))) counter++;
    }
    
    // Output results
    cout << "Done!" << endl;
    cout << "Counter: " << counter << endl;
    cout << "Probability: " << (static_cast<float>(counter)/static_cast<float>(trials))*100.0 << "%" << endl;
    
    return 0;
}

bool checkValidity(float a, float b, float c) {
    // A triangle's sides are valid if, for any two sides, their sum is greater
    // than the third
    if(a >= (b+c)) return false;
    if(b >= (a+c)) return false;
    if(c >= (b+c)) return false;
    return true;
}