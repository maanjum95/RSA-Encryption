#include "RSAKey.h"

RSAKey::RSAKey(void) {
    srand(time(NULL));
}

void RSAKey::generateKey(void) {
    LINT temp;
    do {
        do {
            this->p = this->getRndPrimeNumber();
            this->q = this->getRndPrimeNumber();
        } while (this->p == this->q);

        this->n = this->p * this->q;
        this->fiN = this->n - this->p - this->q + 1;

        do {
            this->e = (this->getRndPrimeNumber() % (this->fiN - 1));
        } while (!this->isPrime(this->e) || (this->gcd(this->e, this->fiN) != 1));

        this->d = this->findModInverse(this->e, this->fiN);

        temp = (this->e * this->d) % this->fiN;

    } while (temp != 1);
}

void RSAKey::tempSetValues(LINT N, LINT E, LINT D) {
    this->p = 0;
    this->q = 0;
    this->fiN = 0;
    this->n = N;
    this->e = E;
    this->d = D;
}

void RSAKey::loadFromFile(string fileLoc) {
    ifstream file;
    file.open(fileLoc, ios::in);
    if (!file.is_open()) { // if the file does not exist
        this->generateKey();
        this->saveToFile(fileLoc);
    }

    // now reading from the file
    file >> this->p;
    file >> this->q;
    file >> this->n;
    file >> this->fiN;
    file >> this->e;
    file >> this->d;

    file.close();
}

void RSAKey::saveToFile(string fileLoc) {
    ofstream file;
    file.open(fileLoc, ios::out);
    if (!file.is_open()) {
        return;
    }

    // now the writing of the variables in the file
    file << this->p << "\n";
    file << this->q << "\n";
    file << this->n << "\n";
    file << this->fiN << "\n";
    file << this->e << "\n";
    file << this->d << "\n";

    file.close();
}

LINT RSAKey::getRndPrimeNumber(void) {
    LINT toReturn;
    do {
        toReturn = rand() + 1;
    } while (!this->isPrime(toReturn) || toReturn < 1000);

    return toReturn;
}

bool RSAKey::isPrime(LINT n) {
    if (n <= 3) {
        return n > 1;
    }
    else if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }
    else {
        for (LINT i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) {
                return false;
            }
        }
        return true;
    }
}

LINT RSAKey::gcd(LINT a, LINT b) {
    while (b != 0) {
        LINT t = b;
        b = a % b;
        a = t;
    }
    return a;
}

LINT RSAKey::findModInverse(LINT e, LINT n) {
    LINT t = 0;
    LINT newt = 1;
    LINT r = n;
    LINT newr = e;
    LINT temp;
    LINT quotient;

    while (newr != 0) {
        quotient = r / newr;

        temp = newt;
        newt = t - quotient * newt;
        t = temp;

        temp = newr;
        newr = r - quotient * newr;
        r = temp;
    }
    if (r > 1) {
        return -1; // non invertiable number
    }
    if (t < 0) {
        t += n;
    }
    return t;
}

LINT RSAKey::modExp(LINT base, LINT exp, LINT N) {
    /// we are not dealing with the power being negative

    if (exp == 0) {
        return 1;
    } else if (exp == 1) {
        return base % N;
    } else if (exp % 2 == 1) { // if exponenet is an odd number
        return (base * RSAKey::modExp((base * base) % N, (exp - 1) / 2, N)) % N;
    } else if (exp % 2 == 0) { // if exponent is an even number
        return RSAKey::modExp((base * base) % N, exp / 2, N) % N;
    } else {
        return 0;
    }
}

LINT RSAKey::getN(void) {
    return this->n;
}

LINT RSAKey::getE(void) {
    return this->e;
}

LINT RSAKey::getD(void) {
    return this->d;
}

LINT RSAKey::getP(void) {
    return this->p;
}

LINT RSAKey::getQ(void) {
    return this->q;
}

LINT RSAKey::getFinN(void) {
    return this->fiN;
}
