#pragma once

#include <string>
#include <optional>
#include <cmath>
#include <type_traits>
#include "rational.h"
#include "pow.h"

using Error = std::string;

template<class T>
class Calculator {
public:
    void Set(T value) {
        current_value_ = value;
    }

    T GetNumber() const {
        return current_value_;
    }

    void Save() {
        mem_ = current_value_;
    }

    void Load() {
        if (mem_.has_value()) {
            current_value_ = mem_.value();
        }
    }

    bool GetHasMem() const {
        return mem_.has_value();
    }

    std::optional<Error> Add(T value) {
        current_value_ += value;
        return std::nullopt;
    }

    std::optional<Error> Sub(T value) {
        current_value_ -= value;
        return std::nullopt;
    }

    std::optional<Error> Mul(T value) {
        current_value_ *= value;
        return std::nullopt;
    }

    std::optional<Error> Div(T value) {
        if constexpr (std::is_floating_point_v<T>) {
        }
        else {
            if (value == T{0}) {
                return "Division by zero";
            }
        }
        current_value_ /= value;
        return std::nullopt;
    }

    std::optional<Error> Pow(T value) {
        if constexpr (std::is_same_v<T, Rational>) {
            if (current_value_ == Rational{0} && value == Rational{0}) {
                return "Zero power to zero";
            }
            if (value.GetDenominator() != 1) {
                return "Fractional power is not supported";
            }
            current_value_ = ::Pow(current_value_, value);
        }
        else if constexpr (std::is_floating_point_v<T>) {
            current_value_ = static_cast<T>(std::pow(current_value_, value));
        }
        else {
            if (current_value_ == T{0} && value == T{0}) {
                return "Zero power to zero";
            }
            if (value < T{0}) {
                return "Integer negative power";
            }
            current_value_ = IntegerPow(current_value_, value);
        }
        return std::nullopt;
    }

private:
    T current_value_{};
    std::optional<T> mem_;
};
