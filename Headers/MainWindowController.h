#ifndef SMALLEXPERTSYSTEM_MAINWINDOWCONTROLLER_H
#define SMALLEXPERTSYSTEM_MAINWINDOWCONTROLLER_H

#include <KnowledgeBaseController.h>
#include <StatusLayoutController.h>
#include <QApplication>
#include <QMessageBox>
#include <QPushButton>
#include <QMainWindow>
#include <QFileDialog>
#include <QKeyEvent>
#include <iostream>
#include <QSpinBox>
#include <chrono>
#include <random>
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
    QLabel *detailedDescription;
    QPushButton *answerButton;
    QLabel *nameDescription;
    QSpinBox *answerSpinBox;
    QPushButton *openButton;
    QPushButton *runButton;
    QLabel *questionText;
    //Widgets
    QWidget *statusWidget;
    StatusLayoutController* statusLayoutController;

    QFile *knowledgeBaseFile{};
    KnowledgeBaseController *knowledgeBaseController;
    default_random_engine *engine;
    vector<int> *order = new vector<int>();
    int currentEvidence = 0;

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
    void runUserSurvey();
private:
    void setEnableElements(bool isEnable);
    void showMessageBox(KnowledgeBaseProcessingStatus processingStatus);
};

#endif //SMALLEXPERTSYSTEM_MAINWINDOWCONTROLLER_H