#include "calculator.h"

void Calculator::Set(Number number) {
    number_ = number;
}

Number Calculator::GetNumber() const {
    return number_;
}

void Calculator::Add(Number addend) {
    number_ += addend;
}

void Calculator::Sub(Number subtrahend) {
    number_ -= subtrahend;
}

void Calculator::Mul(Number multiplier) {
    number_ *= multiplier;
}

void Calculator::Div(Number divisor) {
    number_ /= divisor;
}

void Calculator::Pow(Number exponent) {
    number_ = std::pow(number_, exponent);
}

