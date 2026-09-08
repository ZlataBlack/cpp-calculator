#pragma once

#include <iostream>
#include <numeric>
#include <compare>
#include <stdexcept>
#include <cstdint>

class Rational {
public:
    Rational() : numerator_(0), denominator_(1) {}

    Rational(std::int64_t numerator) : numerator_(numerator), denominator_(1) {}

    Rational(std::int64_t numerator, std::int64_t denominator) : numerator_(numerator), denominator_(denominator) {
        if (denominator_ == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }
        Reduction();
    }

    Rational(const Rational& other) = default;
    Rational& operator=(const Rational& other) = default;

    std::int64_t GetNumerator() const {
        return numerator_;
    }

    std::int64_t GetDenominator() const {
        return denominator_;
    }

    Rational Inv() const {
        if (numerator_ == 0) {
            throw std::invalid_argument("Cannot invert zero");
        }
        return Rational(denominator_, numerator_);
    }

    Rational& operator+=(const Rational& rhs) {
        numerator_ = numerator_ * rhs.denominator_ + rhs.numerator_ * denominator_;
        denominator_ *= rhs.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator-=(const Rational& rhs) {
        numerator_ = numerator_ * rhs.denominator_ - rhs.numerator_ * denominator_;
        denominator_ *= rhs.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator*=(const Rational& rhs) {
        numerator_ *= rhs.numerator_;
        denominator_ *= rhs.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator/=(const Rational& rhs) {
        if (rhs.numerator_ == 0) {
            throw std::invalid_argument("Division by zero");
        }
        numerator_ *= rhs.denominator_;
        denominator_ *= rhs.numerator_;
        Reduction();
        return *this;
    }

    Rational operator+(const Rational& rhs) const {
        Rational r = *this;
        r += rhs;
        return r;
    }

    Rational operator-(const Rational& rhs) const {
        Rational r = *this;
        r -= rhs;
        return r;
    }

    Rational operator*(const Rational& rhs) const {
        Rational r = *this;
        r *= rhs;
        return r;
    }

    Rational operator/(const Rational& rhs) const {
        Rational r = *this;
        r /= rhs;
        return r;
    }

    Rational operator+() const {
        return *this;
    }

    Rational operator-() const {
        return Rational(-numerator_, denominator_);
    }

    auto operator<=>(const Rational& rhs) const {
        std::int64_t lhs_val = numerator_ * rhs.denominator_;
        std::int64_t rhs_val = rhs.numerator_ * denominator_;
        return lhs_val <=> rhs_val;
    }

    bool operator==(const Rational& rhs) const = default;

    friend std::ostream& operator<<(std::ostream& os, const Rational& r) {
        os << r.numerator_;
        if (r.denominator_ != 1) {
            os << " / " << r.denominator_;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Rational& r) {
        std::int64_t num = 0;
        is >> num;
        if (!is) {
            return is;
        }

        std::int64_t den = 1;
        char slash;
        is >> std::ws;

        if (is.peek() == '/') {
            is.get(slash);
            is >> den;
            if (!is || den == 0) {
                is.setstate(std::ios::failbit);
                return is;
            }
        }

        try {
            r = Rational(num, den);
        } catch (...) {
            is.setstate(std::ios::failbit);
        }
        return is;
    }

private:
    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const std::int64_t divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

    std::int64_t numerator_;
    std::int64_t denominator_;
};
