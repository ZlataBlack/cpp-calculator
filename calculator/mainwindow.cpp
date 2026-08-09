#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>

namespace {

QString RemoveLeadingZeroes(const QString& text) {
    for (qsizetype i = 0; i < text.size(); ++i) {
        if (text.at(i) != '0') {
            return text.mid(i);
        }
    }
    return "";
}

QString NormalizeNumber(const QString& text) {
    if (text.isEmpty() || text == "-") {
        return "0";
    }
    if (text.startsWith('.')) {
        return NormalizeNumber("0" + text);
    }
    if (text.startsWith('-')) {
        QString rest = NormalizeNumber(text.mid(1));
        if (rest == "0") {
            return "0";
        }
        return "-" + rest;
    }
    if (text.startsWith('0') && !text.startsWith("0.")) {
        return NormalizeNumber(RemoveLeadingZeroes(text));
    }
    return text;
}

QString OpToString(Operation operation) {
    switch (operation) {
    case Operation::ADDITION:
        return "+";
    case Operation::SUBTRACTION:
        return "−";
    case Operation::MULTIPLICATION:
        return "×";
    case Operation::DIVISION:
        return "÷";
    case Operation::POWER:
        return "^";
    case Operation::NO_OPERATION:
        return "";
    }
    return "";
}

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    // Кнопки цифр
    connect(ui_->button_zero,  &QPushButton::clicked, this, &MainWindow::OnDigitButtonClicked);
    connect(ui_->button_one,   &QPushButton::clicked, this, &MainWindow::OnDigitButtonClicked);
    connect(ui_->button_two,   &QPushButton::clicked, this, &MainWindow::OnDigitButtonClicked);
    connect(ui_->button_three, &QPushButton::clicked, this, &MainWindow::OnDigitButtonClicked);
    connect(ui_->button_four,  &QPushButton::clicked, this, &MainWindow::OnDigitButtonClicked);
    connect(ui_->button_five,  &QPushButton::clicked, this, &MainWindow::OnDigitButtonClicked);
    connect(ui_->button_six,   &QPushButton::clicked, this, &MainWindow::OnDigitButtonClicked);
    connect(ui_->button_seven, &QPushButton::clicked, this, &MainWindow::OnDigitButtonClicked);
    connect(ui_->button_eight, &QPushButton::clicked, this, &MainWindow::OnDigitButtonClicked);
    connect(ui_->button_nine,  &QPushButton::clicked, this, &MainWindow::OnDigitButtonClicked);

    // Остальные кнопки ввода
    connect(ui_->button_dot,       &QPushButton::clicked, this, &MainWindow::OnDotButtonClicked);
    connect(ui_->button_sign,      &QPushButton::clicked, this, &MainWindow::OnSignButtonClicked);
    connect(ui_->button_backspace, &QPushButton::clicked, this, &MainWindow::OnBackspaceButtonClicked);

    // Кнопки операций
    connect(ui_->button_power,    &QPushButton::clicked, this, &MainWindow::OnPowerButtonClicked);
    connect(ui_->button_divide,   &QPushButton::clicked, this, &MainWindow::OnDivideButtonClicked);
    connect(ui_->button_multiply, &QPushButton::clicked, this, &MainWindow::OnMultiplyButtonClicked);
    connect(ui_->button_subtract, &QPushButton::clicked, this, &MainWindow::OnSubtractButtonClicked);
    connect(ui_->button_add,      &QPushButton::clicked, this, &MainWindow::OnAddButtonClicked);

    // Кнопки управления
    connect(ui_->button_equals, &QPushButton::clicked, this, &MainWindow::OnEqualsButtonClicked);
    connect(ui_->button_clear,  &QPushButton::clicked, this, &MainWindow::OnClearButtonClicked);

    // Кнопки памяти
    connect(ui_->button_memory_save,  &QPushButton::clicked, this, &MainWindow::OnMemorySaveButtonClicked);
    connect(ui_->button_memory_clear, &QPushButton::clicked, this, &MainWindow::OnMemoryClearButtonClicked);
    connect(ui_->button_memory_load,  &QPushButton::clicked, this, &MainWindow::OnMemoryLoadButtonClicked);

    SetText(QStringLiteral("0"));
}

MainWindow::~MainWindow()
{
    delete ui_;
}

// Точка сохранения
void MainWindow::SetText(const QString& text) {
    input_number_ = NormalizeNumber(text);
    ui_->l_result->setText(input_number_);
    active_number_ = input_number_.toDouble();
}

// Дописать
void MainWindow::AddText(const QString& suffix) {
    if (current_operation_ == Operation::NO_OPERATION) {
        ui_->l_formula->clear();
    }
    SetText(input_number_ + suffix);
}

void MainWindow::OnDigitButtonClicked() {
    const auto* button = qobject_cast<QPushButton*>(sender());
    if (!button) {
        return;
    }
    AddText(button->text());
}

void MainWindow::OnDotButtonClicked() {
    if (input_number_.contains('.')) {
        return;
    }
    AddText(QStringLiteral("."));
}

void MainWindow::OnSignButtonClicked() {
    if (input_number_.isEmpty()) {
        return;
    }
    if (input_number_.startsWith('-')) {
        SetText(input_number_.mid(1));
    } else {
        SetText("-" + input_number_);
    }
}

void MainWindow::OnBackspaceButtonClicked() {
    if (input_number_.isEmpty()) {
        return;
    }
    QString shortened = input_number_;
    shortened.chop(1);
    SetText(shortened);
}

// Выбор операции
void MainWindow::SetOperation(Operation operation) {
    if (current_operation_ == Operation::NO_OPERATION) {
        calculator_.Set(active_number_);
    }

    current_operation_ = operation;
    ui_->l_formula->setText(
        QString("%1 %2")
            .arg(calculator_.GetNumber())
            .arg(OpToString(operation))
    );
    input_number_ = QString();
}

void MainWindow::OnPowerButtonClicked() {
    SetOperation(Operation::POWER);
}

void MainWindow::OnDivideButtonClicked() {
    SetOperation(Operation::DIVISION);
}

void MainWindow::OnMultiplyButtonClicked() {
    SetOperation(Operation::MULTIPLICATION);
}

void MainWindow::OnSubtractButtonClicked() {
    SetOperation(Operation::SUBTRACTION);
}

void MainWindow::OnAddButtonClicked() {
    SetOperation(Operation::ADDITION);
}

void MainWindow::OnEqualsButtonClicked() {
    if (current_operation_ == Operation::NO_OPERATION) {
        return;
    }

    ui_->l_formula->setText(
        QString("%1 %2 %3 =")
            .arg(calculator_.GetNumber())
            .arg(OpToString(current_operation_))
            .arg(active_number_)
    );

    switch (current_operation_) {
    case Operation::ADDITION:
        calculator_.Add(active_number_);
        break;
    case Operation::SUBTRACTION:
        calculator_.Sub(active_number_);
        break;
    case Operation::MULTIPLICATION:
        calculator_.Mul(active_number_);
        break;
    case Operation::DIVISION:
        calculator_.Div(active_number_);
        break;
    case Operation::POWER:
        calculator_.Pow(active_number_);
        break;
    case Operation::NO_OPERATION:
        break;
    }

    active_number_ = calculator_.GetNumber();
    ui_->l_result->setText(QString::number(active_number_));

    input_number_ = QString();
    current_operation_ = Operation::NO_OPERATION;
}

void MainWindow::OnClearButtonClicked() {
    current_operation_ = Operation::NO_OPERATION;
    ui_->l_formula->clear();
    SetText(QStringLiteral("0"));
}

void MainWindow::OnMemorySaveButtonClicked() {
    memory_value_ = active_number_;
    has_memory_ = true;
    ui_->l_memory->setText(QStringLiteral("M"));
}

void MainWindow::OnMemoryClearButtonClicked() {
    memory_value_ = 0;
    has_memory_ = false;
    ui_->l_memory->clear();
}

void MainWindow::OnMemoryLoadButtonClicked() {
    if (!has_memory_) {
        return;
    }
    active_number_ = memory_value_;
    ui_->l_result->setText(QString::number(active_number_));
    input_number_ = QString();
}
