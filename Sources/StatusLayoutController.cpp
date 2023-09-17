#include "ui_StatusLayoutController.h"
#include "StatusLayoutController.h"

//Constructor
StatusLayoutController::StatusLayoutController(QWidget *parent) :
        QWidget(parent), ui(new Ui::StatusLayoutController) {
    ui->setupUi(this);

}

//Destructor
StatusLayoutController::~StatusLayoutController() {
    delete ui;
}