#ifndef SMALLEXPERTSYSTEM_MAINWINDOWCONTROLLER_H
#define SMALLEXPERTSYSTEM_MAINWINDOWCONTROLLER_H

#include <KnowledgeBaseController.h>
#include <StatusLayoutController.h>
#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include <QFileDialog>
#include <QKeyEvent>
#include <iostream>
#include <QSpinBox>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowController; }
QT_END_NAMESPACE

class MainWindowController : public QMainWindow {
Q_OBJECT
    //Variables
private:
    Ui::MainWindowController *ui;
    //Elements
    QPushButton *minusSpinButton;
    QPushButton *plusSpinButton;
    QPushButton *answerButton;
    QSpinBox *answerSpinBox;
    QPushButton *openButton;
    QPushButton *runButton;
    //Widgets
    QWidget *statusWidget;
    StatusLayoutController* statusLayoutController;

    QFile *knowledgeBaseFile;

    //Methods
public:
    explicit MainWindowController(QWidget *parent = nullptr);
    ~MainWindowController() override;
protected:
    void keyPressEvent(QKeyEvent *event) override;
private slots:
    void minusSpinButtonPressed();
    void plusSpinButtonPressed();
    void goToNextQuestion();
    void openFileDialog();
private:
    void setEnableElements(bool isEnable);
};

#endif //SMALLEXPERTSYSTEM_MAINWINDOWCONTROLLER_H