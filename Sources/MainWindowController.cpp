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

    //Elements init
    minusSpinButton = ui->minusSpinButton;
    plusSpinButton = ui->plusSpinButton;
    answerSpinBox = ui->answerSpinBox;
    answerButton = ui->answerButton;
    openButton = ui->openButton;
    runButton = ui->runButton;

    //Connecting to slots
    connect(minusSpinButton, &QPushButton::clicked, this, &MainWindowController::minusSpinButtonPressed);
    connect(plusSpinButton, &QPushButton::clicked, this, &MainWindowController::plusSpinButtonPressed);
    connect(answerButton, &QPushButton::clicked, this, &MainWindowController::goToNextQuestion);
    connect(openButton, &QPushButton::clicked, this, &MainWindowController::openFileDialog);

    //Deactivation of elements
    setEnableElements(false);
}

//Destructor
MainWindowController::~MainWindowController() {
    delete minusSpinButton;
    delete plusSpinButton;
    delete answerSpinBox;
    delete answerButton;
    delete openButton;
    delete runButton;
    delete statusWidget;
    delete statusLayoutController;
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

void MainWindowController::openFileDialog() {
    delete knowledgeBaseController; //Memory release

    //Opening a file
    auto path = QFileDialog::getOpenFileName(this, tr("Выберите файл"),
                                                     "../", tr("База знаний (*.mkb)"));
    if(std::equal(path.begin(), path.end(), tr("").begin())) return;
    knowledgeBaseFile = new QFile(path);
    knowledgeBaseFile->open(QFile::ReadOnly);

    //Retrieving data from a file
    auto knowledgeBaseString = QString(knowledgeBaseFile->readAll());
    knowledgeBaseFile->close();
    delete knowledgeBaseFile;

    //Processing of received data
    knowledgeBaseController = new KnowledgeBaseController(knowledgeBaseString);
    if(knowledgeBaseController->getProcessingStatus() != KnowledgeBaseProcessingStatus::SUCCESS) {
        showMessageBox(knowledgeBaseController->getProcessingStatus());
        return;
    }
    setEnableElements(true);
}

//Set active or inactive elements other than openButton
void MainWindowController::setEnableElements(bool isEnable) {
    minusSpinButton->setEnabled(isEnable);
    plusSpinButton->setEnabled(isEnable);
    answerSpinBox->setEnabled(isEnable);
    answerButton->setEnabled(isEnable);
    runButton->setEnabled(isEnable);
}

//Show file opening error message
void MainWindowController::showMessageBox(KnowledgeBaseProcessingStatus processingStatus) {
    QString message;
    switch(processingStatus) {
        case KnowledgeBaseProcessingStatus::SECTIONS_ERROR:
            message = QString("Ошибка в секциях");
            break;
        case KnowledgeBaseProcessingStatus::EVIDENCE_ERROR:
            message = QString("Ошибка в свидетельствах");
            break;
        case KnowledgeBaseProcessingStatus::OUTCOME_ERROR:
            message = QString("Ошибка в исходах");
            break;
        default: message = QString("");
            break;
    }
    QMessageBox::critical(this, tr("Ошибка открытия файла"), message);
}