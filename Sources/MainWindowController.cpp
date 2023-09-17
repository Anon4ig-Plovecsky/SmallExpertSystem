#include <ui_MainWindowController.h>
#include <MainWindowController.h>

//Constructor
MainWindowController::MainWindowController(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindowController) {
    ui->setupUi(this);

    //Widget init
    statusWidget = ui->statusWidget;
    statusLayoutController = new StatusLayoutController();
    statusWidget->layout()->addWidget(statusLayoutController);
//    statusLayoutController->show();

    //Elements init
    minusSpinButton = ui->minusSpinButton;
    plusSpinButton = ui->plusSpinButton;
    answerSpinBox = ui->answerSpinBox;
    answerButton = ui->answerButton;

    //Connecting to slots
    connect(minusSpinButton, &QPushButton::clicked, this, &MainWindowController::minusSpinButtonPressed);
    connect(plusSpinButton, &QPushButton::clicked, this, &MainWindowController::plusSpinButtonPressed);
    connect(answerButton, &QPushButton::clicked, this, &MainWindowController::goToNextQuestion);
}

//Destructor
MainWindowController::~MainWindowController() {
    delete minusSpinButton;
    delete plusSpinButton;
    delete answerSpinBox;
    delete answerButton;
    delete ui;
}

//Buttons for AnswerSpinBox: Button "+"
void MainWindowController::plusSpinButtonPressed() {
    answerSpinBox->setValue(answerSpinBox->value() + 1);
}
// Button "-"
void MainWindowController::minusSpinButtonPressed() {
    answerSpinBox->setValue(answerSpinBox->value() - 1);
}


void MainWindowController::goToNextQuestion() {
    std::cout << "Result: " << answerSpinBox->value() << std::endl; //TODO
}

//Press enter(return) in answerSpinBox
void MainWindowController::keyPressEvent(QKeyEvent *event) {
    QWidget::keyPressEvent(event);
    if(answerSpinBox->hasFocus()
        && (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return))
        goToNextQuestion();
}