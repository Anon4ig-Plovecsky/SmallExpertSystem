#ifndef SMALLEXPERTSYSTEM_MAINWINDOWCONTROLLER_H
#define SMALLEXPERTSYSTEM_MAINWINDOWCONTROLLER_H

#include <QMainWindow>
#include <QApplication>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowController; }
QT_END_NAMESPACE

class MainWindowController : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindowController(QWidget *parent = nullptr);

    ~MainWindowController() override;

private:
    Ui::MainWindowController *ui;
};


#endif //SMALLEXPERTSYSTEM_MAINWINDOWCONTROLLER_H
