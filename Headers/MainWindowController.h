#ifndef SMALLEXPERTSYSTEM_MAINWINDOWCONTROLLER_H
#define SMALLEXPERTSYSTEM_MAINWINDOWCONTROLLER_H

#include <StatusLayoutController.h>
#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include <QKeyEvent>
#include <iostream>
#include <QSpinBox>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowController; }
QT_END_NAMESPACE

class MainWindowController : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindowController(QWidget *parent = nullptr);
    ~MainWindowController() override;
private slots:
    void minusSpinButtonPressed();
    void plusSpinButtonPressed();
    void goToNextQuestion();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindowController *ui;
    //Elements
    QPushButton *minusSpinButton;
    QPushButton *plusSpinButton;
    QPushButton *answerButton;
    QSpinBox *answerSpinBox;
    //Widgets
    QWidget *statusWidget;
    StatusLayoutController* statusLayoutController;
};

#endif //SMALLEXPERTSYSTEM_MAINWINDOWCONTROLLER_H