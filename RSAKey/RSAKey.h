#ifndef RSAKEY_H
#define RSAKEY_H

#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

typedef long long int LINT;

class RSAKey {
    LINT n, e, d;
    LINT p, q;
    LINT fiN;

    /*
    *   This method finds the modular inverse of 'e' using
    *   Extended Eucledian Algorithm
    *   (Pseudocode found on Wikipedia)
    */
    LINT findModInverse(LINT e, LINT n);

    /*
    *   This method returns a random prime number
    */
    LINT getRndPrimeNumber(void);

    /*
    *   This method checks if the number if prime or not.
    */
    bool isPrime(LINT n);

    /*
    *   This method finds the the gcd of the two numbers
    */
    LINT gcd(LINT a, LINT b);
public:

    /*
    *   Default constructor of RSAKey class randomizes the seader for rand()
    */
    RSAKey(void);

    /*
    *   This method generates the key using RSA algoritm
    *   Take two prime number numbers p & q
    *   Find n = p * q
    *   Find fin = (p-1) * (q-1)
    *   Take a random prime number e between 1 & fin
    *   Find d the modular inverse of e wrt fin
    *   The two key pairs are public key(e, n) & private key(d, n)
    */
    void generateKey(void);

    /*
    *   Setting temporary values of N, E, D to the parameters
    *   All the rest are set to 0.
    */
    void tempSetValues(LINT N, LINT E, LINT D); // this method is just to set the values temporarily

    /*
    *   This method loads the key from the 'fileLoc'
    */
    void loadFromFile(string fileLoc);

    /*
    *   This method saves the key into the 'fileLoc'
    */
    void saveToFile(string fileLoc);


    /////////////// GETTER FUNCTIONS /////////////////
    LINT getN(void);
    LINT getE(void);
    LINT getD(void);
    LINT getP(void);
    LINT getQ(void);
    LINT getFinN(void);

    /*
    *   This method find base^exp using square and multiply algorithm whichm
    *   reduces the running time from O(N) to (OlnN)
    */
    static LINT modExp(LINT base, LINT exp, LINT N);
};

#endif // RSAKEY_H
