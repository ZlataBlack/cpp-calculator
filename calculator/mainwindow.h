#pragma once

#include <QMainWindow>

#include "calculator.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum class Operation {
    NO_OPERATION,
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    POWER
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void OnDigitButtonClicked();
    void OnDotButtonClicked();
    void OnSignButtonClicked();
    void OnBackspaceButtonClicked();

    void OnPowerButtonClicked();
    void OnDivideButtonClicked();
    void OnMultiplyButtonClicked();
    void OnSubtractButtonClicked();
    void OnAddButtonClicked();

    void OnEqualsButtonClicked();
    void OnClearButtonClicked();

    void OnMemorySaveButtonClicked();
    void OnMemoryClearButtonClicked();
    void OnMemoryLoadButtonClicked();

private:
    void SetText(const QString& text);
    void AddText(const QString& suffix);
    void SetOperation(Operation operation);

    Ui::MainWindow *ui_;

    Calculator calculator_;
    QString input_number_;
    Number active_number_ = 0;
    Operation current_operation_ = Operation::NO_OPERATION;

    Number memory_value_ = 0;
    bool has_memory_ = false;
};
