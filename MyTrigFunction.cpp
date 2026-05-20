#include "MyTrigFunction.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cmath> // For pow and tgamma

MyTrigFunction::MyTrigFunction() {}

// parameter 'n' determines the number of terms in the series to include in the summation
double MyTrigFunction::FuncA(int n) {
    double x = 1.0;
    double sum = 0.0;

    for (int i = 0; i <= n; ++i) {
        double numerator = (i % 2 == 0 ? 1.0 : -1.0) * tgamma(2 * i + 1);
        double denominator = pow(4, i) * pow(tgamma(i + 1), 2);
        sum += (numerator / denominator) * pow(x, i);
    }

    return sum;
}

double RunComputeWorkload(long n) {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<double> values;
    values.reserve(n);
    MyTrigFunction trigFunc;
    for (long i = 0; i < n; ++i) {
        values.push_back(trigFunc.FuncA(i % 10));
    }
    std::sort(values.begin(), values.end());
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start).count();
}
