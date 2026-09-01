#pragma once

#include <QMainWindow>
#include <functional>
#include <optional>
#include <string>
#include "enums.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    using DigitKeyCallback = std::function<void(int)>;
    using OperationKeyCallback = std::function<void(Operation)>;
    using ControlKeyCallback = std::function<void(ControlKey)>;
    using ControllerCallback = std::function<void(ControllerType)>;

    void SetDigitKeyCallback(DigitKeyCallback callback);
    void SetProcessOperationKeyCallback(OperationKeyCallback callback);
    void SetProcessControlKeyCallback(ControlKeyCallback callback);
    void SetControllerCallback(ControllerCallback callback);

    void SetInputText(const std::string& text);
    void SetErrorText(const std::string& text);
    void SetFormulaText(const std::string& text);
    void SetMemText(const std::string& text);
    void SetExtraKey(const std::optional<std::string>& key);

private:
    Ui::MainWindow *ui;

    DigitKeyCallback digit_callback_;
    OperationKeyCallback operation_callback_;
    ControlKeyCallback control_callback_;
    ControllerCallback controller_callback_;
};
