#pragma once

#include <cmath>

using Number = double;

class Calculator {
public:
    void Set(Number number);
    Number GetNumber() const;

    void Add(Number addend);
    void Sub(Number subtrahend);
    void Mul(Number multiplier);
    void Div(Number divisor);
    void Pow(Number exponent);

private:
    Number number_ = 0;
};
