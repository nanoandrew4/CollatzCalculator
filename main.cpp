#include <iostream>
#include <chrono>
#include <gmp.h>

void collatz(unsigned long long i);

void bignumCollatz(const std::string &strNum);

void seqCollatz(unsigned long long start, unsigned long long end);

void parseNum(mpz_t &num, std::string strNum);

unsigned long long maxSteps = 1, numWithMaxSteps = 1;

int main() {

    std::cout << "1. Find largest number of steps in range" << std::endl;
    std::cout << "2. Find steps for single large integer" << std::endl;
    int opt;
    std::cin >> opt;
    switch (opt) {
        case 1:
            std::cout << "Enter start and ending numbers to check" << std::endl;
            unsigned long long start, end;
            std::cin >> start >> end;
            seqCollatz(start, end);
            break;
        case 2:
            std::cout << "Enter the number to determine the steps for" << std::endl;
            std::string num;
            std::cin >> num;
            bignumCollatz(num);
            break;
    }
    return 0;
}

void collatz(unsigned long long i) {
    unsigned long long num = i;
    unsigned int steps = 0;
    while (num != 1) {
        if (num % 2 == 0)
            num >>= 1;
        else {
            num = ((3 * num) + 1) >> 1;
            steps++;
        }
        steps++;
    }

    if (steps > maxSteps) {
        maxSteps = steps;
        numWithMaxSteps = i;
    }
}

void bignumCollatz(const std::string &strNum) {
    mpz_t num;
    long startTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    parseNum(num, strNum);
    unsigned long long steps = 0;

    while (mpz_cmp_ui(num, 1) != 0) {
        if (mpz_even_p(num))
            mpz_div_2exp(num, num, 1);
        else {
            mpz_mul_ui(num, num, 3);
            mpz_add_ui(num, num, 1);
            mpz_div_2exp(num, num, 1);
            steps++;
        }
        steps++;
    }

    long endTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::cout << strNum << " took: " << steps << " steps" << std::endl;
    std::cout << "Time taken: " << (endTime - startTime) / 1000000.0 << "ms" << std::endl;
}

void seqCollatz(unsigned long long start, unsigned long long end) {
    long startTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    
    for (unsigned long i = start; i < end; i++)
        collatz(i);

    long endTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::cout << "Max steps: " << maxSteps << " for number: " << numWithMaxSteps << std::endl;
    std::cout << "Time taken: " << (endTime - startTime) / 1000000000.0 << "s" << std::endl;
}

void parseNum(mpz_t &num, std::string strNum) {
    unsigned long powerSymbPos = 0;
    for (unsigned long i = 0; i < strNum.length(); i++)
        if (strNum.at(i) == '^') {
            powerSymbPos = i;
            break;
        }

    if (powerSymbPos == 0)
        mpz_init_set_str(num, strNum.c_str(), 10);
    else {
        unsigned long base = (unsigned long) atoi(strNum.substr(0, powerSymbPos).c_str());
        unsigned long power = (unsigned long) atoi(strNum.substr(powerSymbPos + 1, strNum.length()).c_str());
        mpz_init_set_ui(num, base);
        mpz_pow_ui(num, num, power);
    }
}