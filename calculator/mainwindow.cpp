#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QComboBox>
#include <QString>
#include <QMap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Кнопки 0-9
    QMap<QPushButton*, int> digit_buttons = {
        {ui->button_zero, 0}, {ui->button_one, 1}, {ui->button_two, 2},
        {ui->button_three, 3}, {ui->button_four, 4}, {ui->button_five, 5},
        {ui->button_six, 6}, {ui->button_seven, 7}, {ui->button_eight, 8},
        {ui->button_nine, 9}
    };

    for (auto it = digit_buttons.begin(); it != digit_buttons.end(); ++it) {
        connect(it.key(), &QPushButton::clicked, this, [this, digit = it.value()]() {
            if (digit_callback_) {
                digit_callback_(digit);
            }
        });
    }

    // Кнопки операций
    QMap<QPushButton*, Operation> operation_buttons = {
        {ui->button_add, Operation::ADDITION},
        {ui->button_subtract, Operation::SUBTRACTION},
        {ui->button_multiply, Operation::MULTIPLICATION},
        {ui->button_divide, Operation::DIVISION},
        {ui->button_power, Operation::POWER}
    };

    for (auto it = operation_buttons.begin(); it != operation_buttons.end(); ++it) {
        connect(it.key(), &QPushButton::clicked, this, [this, operation = it.value()]() {
            if (operation_callback_) {
                operation_callback_(operation);
            }
        });
    }

    // Кнопки управления
    QMap<QPushButton*, ControlKey> control_buttons = {
        {ui->button_equals, ControlKey::EQUALS},
        {ui->button_clear, ControlKey::CLEAR},
        {ui->button_memory_save, ControlKey::MEM_SAVE},
        {ui->button_memory_load, ControlKey::MEM_LOAD},
        {ui->button_memory_clear, ControlKey::MEM_CLEAR},
        {ui->button_sign, ControlKey::PLUS_MINUS},
        {ui->button_backspace, ControlKey::BACKSPACE},
        {ui->tb_extra, ControlKey::EXTRA_KEY}
    };

    for (auto it = control_buttons.begin(); it != control_buttons.end(); ++it) {
        connect(it.key(), &QPushButton::clicked, this, [this, key = it.value()]() {
            if (control_callback_) {
                control_callback_(key);
            }
        });
    }

    connect(ui->cmb_controller, &QComboBox::currentTextChanged, this, [this](const QString& text) {
        if (!controller_callback_) {
            return;
        }
        if (text == "double") {
            controller_callback_(ControllerType::DOUBLE);
        }
        else if (text == "float") {
            controller_callback_(ControllerType::FLOAT);
        }
        else if (text == "uint8_t") {
            controller_callback_(ControllerType::UINT8_T);
        }
        else if (text == "int") {
            controller_callback_(ControllerType::INT);
        }
        else if (text == "int64_t") {
            controller_callback_(ControllerType::INT64_T);
        }
        else if (text == "size_t") {
            controller_callback_(ControllerType::SIZE_T);
        }
        else if (text == "Rational") {
            controller_callback_(ControllerType::RATIONAL);
        }
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetDigitKeyCallback(DigitKeyCallback callback) {
    digit_callback_ = std::move(callback);
}

void MainWindow::SetProcessOperationKeyCallback(OperationKeyCallback callback) {
    operation_callback_ = std::move(callback);
}

void MainWindow::SetProcessControlKeyCallback(ControlKeyCallback callback) {
    control_callback_ = std::move(callback);
}

void MainWindow::SetControllerCallback(ControllerCallback callback) {
    controller_callback_ = std::move(callback);
}

void MainWindow::SetInputText(const std::string& text) {
    ui->l_result->setStyleSheet("");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetErrorText(const std::string& text) {
    ui->l_result->setStyleSheet("color: red;");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetFormulaText(const std::string& text) {
    ui->l_formula->setText(QString::fromStdString(text));
}

void MainWindow::SetMemText(const std::string& text) {
    ui->l_memory->setText(QString::fromStdString(text));
}

void MainWindow::SetExtraKey(const std::optional<std::string>& key) {
    if (key.has_value()) {
        ui->tb_extra->setText(QString::fromStdString(key.value()));
        ui->tb_extra->setVisible(true);
    } else {
        ui->tb_extra->setVisible(false);
    }
}
