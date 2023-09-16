#include <MainWindowController.h>
#include <ui_MainWindowController.h>


MainWindowController::MainWindowController(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindowController) {
    ui->setupUi(this);
}

MainWindowController::~MainWindowController() {
    delete ui;
}
