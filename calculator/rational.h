#pragma once

#include <iostream>
#include <numeric>
#include <compare>
#include <stdexcept>
#include <cstdint>

class Rational {
public:
    // Конструктор по умолчанию 0/1
    Rational() : numerator_(0), denominator_(1) {}

    // Конструктор. Числитель и знаменатель = 1
    Rational(int numerator) : numerator_(numerator), denominator_(1) {}

    // Конструктор из двух чисел
    Rational(int numerator, int denominator) : numerator_(numerator), denominator_(denominator) {
        if (denominator_ == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }
        Reduction();
    }

    // Конструктор копирования и оператор присваивания
    Rational(const Rational& other) = default;
    Rational& operator=(const Rational& other) = default;

    // Публичные методы
    int GetNumerator() const { return numerator_; }
    int GetDenominator() const { return denominator_; }

    Rational Inv() const {
        if (numerator_ == 0) {
            throw std::invalid_argument("Cannot invert zero");
        }
        return Rational(denominator_, numerator_);
    }

    // Присваивание операций
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

    Rational operator+(const Rational& rhs) const { Rational r = *this; r += rhs; return r; }
    Rational operator-(const Rational& rhs) const { Rational r = *this; r -= rhs; return r; }
    Rational operator*(const Rational& rhs) const { Rational r = *this; r *= rhs; return r; }
    Rational operator/(const Rational& rhs) const { Rational r = *this; r /= rhs; return r; }
    Rational operator+() const { return *this; }
    Rational operator-() const { return Rational(-numerator_, denominator_); }

    auto operator<=>(const Rational& rhs) const {
        int64_t lhs_val = static_cast<int64_t>(numerator_) * rhs.denominator_;
        int64_t rhs_val = static_cast<int64_t>(rhs.numerator_) * denominator_;
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
        int num = 0;
        is >> num;
        if (!is) return is;

        int den = 1;
        char slash;
        is >> std::ws; // Пропускаем пробелы

        // Проверяем, есть ли дробная часть
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
    // Метод приведения дроби к несократимому виду
    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

    int numerator_;
    int denominator_;
};
