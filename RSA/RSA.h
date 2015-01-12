#ifndef RSA_H
#define RSA_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../RSAKey/RSAKey.h"

using namespace std;

class RSA {
    /*
    *   This method encrypts the string 'toEncode' using the key (E, N)
    *   to encode m = c ^ E % N where 'c' is the character to encrypt and 'm' is encoded
    */
    static vector<LINT> *encode(string toEncode, LINT E, LINT N);

    /*
    *   This method decrypts the vector of long int 'toDecode' using the key (D, N)
    *   to encode m = c ^ D % N where 'c' is the decrypted long int and 'm' is decoded
    */
    static string decode(vector<LINT> *toDecode, LINT D, LINT N);
public:
    /*
    *   This method writes the encrypts contents of the 'toEncode' string in to the file 'fileLoc'
    *   using the key (E, N)
    */
    static bool encodeToFile(string fileLoc, string toEncode, LINT E, LINT N);

    /*
    *   This method writes the decrypts the contents of the 'fileLoc' file
    *   using the key (D, N) and returns the string that was decrypted
    */
    static string decodeFromFile(string fileLoc, LINT D, LINT N);
};

#endif // RSA_H
