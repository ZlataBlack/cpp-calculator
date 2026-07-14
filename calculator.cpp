// В этом файле определения функций.
// За основу возьмите решение предыдущей задачи.

#include "calculator.h"
#include <iostream>
#include <string>
#include <cmath>

//Чтение числа из потока ввода 
bool ReadNumber(Number& result) {
    if (std::cin >> result) {
        return true;
    }
    std::cerr << "Error: Numeric operand expected";
    return false;
}

//Локальные переменные 
bool RunCalculatorCycle () {
    Number current_value = 0.0;
    Number memory_value = 0.0;
    bool memory_initialized = false;

//Чтение первого числа при запуске программы
    if (!ReadNumber(current_value)) {
        return false;
    }
//Чтение команд 
    std::string token;
    while (std::cin >> token) {
        if (token == "q") {
            return true;
        }
        else if (token == "=") {
            std::cout << current_value << "\n";
        }
        else if (token == "c") {
            current_value = 0.0;
        }
        else if (token == "s") {
            memory_value = current_value;
            memory_initialized = true;
        }
        else if (token == "l") {
            if (!memory_initialized) {
                std::cerr << "Error: Memory is empty";
                return false;
            }
            current_value = memory_value; //Загружаем значение из памяти 
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "**" || token == ":") {
            Number operand;
            if (!ReadNumber(operand)) {
                return false;
            }
            // Выполнение операций 
            if (token == "+") {
                current_value += operand;
            }
            else if (token == "-") {
                current_value -= operand;
            }
            else if (token == "*") {
                current_value *= operand;
            }
            else if (token == "/"){
                current_value /= operand;
            }
            else if (token == "**") {
                current_value = std::pow(current_value, operand);
            }
            else if (token == ":") {
                current_value = operand;
            }
        }
        // ОБработака неизвестной команды 
        else {
            std::cerr << "Error: Unknown token "  << token << std::endl;
            return false;
        }
    }
    return true;
}

