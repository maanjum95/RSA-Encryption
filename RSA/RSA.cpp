#include "RSA.h"

#include "../RSAKey/RSAKey.h"

vector<LINT> *RSA::encode(string toEncode, LINT E, LINT N) {
    vector<LINT> *toReturn = new vector<LINT>;

    for (int i = 0, m = toEncode.length(); i < m; i++) {
        LINT temp = RSAKey::modExp((LINT) toEncode[i], E, N);
        toReturn->push_back(temp);
    }

    return toReturn;
}

bool RSA::encodeToFile(string fileLoc, string toEncode, LINT E, LINT N) {
    /*
    *	The structure of encoded file will be as belows
    *	An LINT representing the value of "N" used to encode
    *	Followed by all the data that needs to be encoded
    */

    vector<LINT> *toWrite = RSA::encode(toEncode, E, N); // the vector of LINTs to write to file
    ofstream file;
    file.open(fileLoc, ios::out | ios::binary);

    if (!file.is_open()) { // if the file could not be opened
        return false;
    }
    file.write(reinterpret_cast<const char *>(&N), sizeof(LINT));

    for (int i = 0, m = toWrite->size(); i < m; i++) {
        file.write(reinterpret_cast<const char *>(&toWrite[0][i]), sizeof(LINT));
    }

    file.close();
    delete toWrite;
    return true;
}

string RSA::decode(vector<LINT> *toDecode, LINT D, LINT N) {
    string toReturn;
    for (int i = 0, m = toDecode->size(); i < m; i++) {
        toReturn += (char) RSAKey::modExp(toDecode[0][i], D, N);
    }

    delete toDecode;
    return toReturn;
}

string RSA::decodeFromFile(string fileLoc, LINT D, LINT N) {
    ifstream file;
    vector<LINT> *toDecode = new vector<LINT>;
    file.open(fileLoc, ios::in | ios::binary);

    LINT nEncode;
    file.read(reinterpret_cast<char *>(&nEncode), sizeof(LINT)); // reading the "N" which was used to encode the file

    if (nEncode != N) {
        return ""; // the file is not being decoded using the same public-private key
    }
    while (!file.eof()) {
        LINT temp;
        file.read(reinterpret_cast<char *>(&temp), sizeof(LINT));
        toDecode->push_back(temp);
    }
    // removing the excess read LINT from the file
    toDecode->pop_back();

    file.close();
    return RSA::decode(toDecode, D, N);
}


