#include <ui_MainWindowController.h>
#include <MainWindowController.h>

//Constructor
MainWindowController::MainWindowController(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindowController) {
    ui->setupUi(this);
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    engine = new default_random_engine(seed);
    knowledgeBaseController = new KnowledgeBaseController();

    //Widget init
    statusWidget = ui->statusWidget;
    statusLayoutController = new StatusLayoutController();
    statusWidget->layout()->addWidget(statusLayoutController);

    //Elements init
    detailedDescription = ui->detailedDescription;
    nameDescription = ui->nameDescription;
    minusSpinButton = ui->minusSpinButton;
    plusSpinButton = ui->plusSpinButton;
    answerSpinBox = ui->answerSpinBox;
    answerButton = ui->answerButton;
    questionText = ui->questionText;
    openButton = ui->openButton;
    runButton = ui->runButton;

    //Connecting to slots
    connect(minusSpinButton, &QPushButton::clicked, this, &MainWindowController::minusSpinButtonPressed);
    connect(plusSpinButton, &QPushButton::clicked, this, &MainWindowController::plusSpinButtonPressed);
    connect(answerButton, &QPushButton::clicked, this, &MainWindowController::goToNextQuestion);
    connect(openButton, &QPushButton::clicked, this, &MainWindowController::openFileDialog);
    connect(runButton, &QPushButton::clicked, this, &MainWindowController::runUserSurvey);

    //Deactivation of elements
    setEnableElements(false);
}

//Buttons for AnswerSpinBox: Button "+"
void MainWindowController::plusSpinButtonPressed() {
    answerSpinBox->setValue(answerSpinBox->value() + 1);
}
// Button "-"
void MainWindowController::minusSpinButtonPressed() {
    answerSpinBox->setValue(answerSpinBox->value() - 1);
}

//Write the result and move on to the next question
void MainWindowController::goToNextQuestion() {
    //Displaying results in statusLayout
    statusLayoutController->findPosteriorProbabilities((*order)[currentEvidence], answerSpinBox->value());
    statusLayoutController->setHistoryLabel(currentEvidence + 1, answerSpinBox->value(), knowledgeBaseController->getEvidences()[(*order)[currentEvidence]]);

    //Show next question
    currentEvidence++;
    if(currentEvidence == knowledgeBaseController->getEvidences().size() //if all questions have been asked--
        || std::find_if(statusLayoutController->outcomes.begin(), statusLayoutController->outcomes.end(), // or if the probabilities of all outcomes are zero
                        [](const Outcome& outcome) {
            return outcome.priorProbability != 0.0;
        }) == statusLayoutController->outcomes.end()) {
        questionText->setText(QString("Консультация завершена"));
        setEnableElements(false);
        runButton->setEnabled(true);
    }
    else questionText->setText(knowledgeBaseController->getEvidences()[(*order)[currentEvidence]]);
}

//Press enter(return) in answerSpinBox
void MainWindowController::keyPressEvent(QKeyEvent *event) {
    QWidget::keyPressEvent(event);
    if(answerSpinBox->hasFocus()
        && (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return))
        goToNextQuestion();
}

void MainWindowController::openFileDialog() {
    setEnableElements(false);
    delete knowledgeBaseController; //Memory release

    //Opening a file
    auto path = QFileDialog::getOpenFileName(this, tr("Выберите файл"),
                                                     "../", tr("База знаний (*.mkb)"));
    if(std::equal(path.begin(), path.end(), tr("").begin())) {
        knowledgeBaseController = new KnowledgeBaseController();
        return;
    }
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
    runButton->setEnabled(true);

    //Show description
    auto nameDescriptionQString = std::move(knowledgeBaseController->getKnowledgeBaseDescription()).section("\r\n", 0, 0, QString::SectionSkipEmpty);
    auto detailedDescriptionQString = std::move(knowledgeBaseController->getKnowledgeBaseDescription()).section("\r\n", 1);
    nameDescription->setText(nameDescriptionQString);
    detailedDescription->setText(detailedDescriptionQString);

    //Show outcomes
    statusLayoutController->outcomes = knowledgeBaseController->getOutcomes();
    statusLayoutController->setResultLabel();
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

//Starts displaying questions from the knowledge base and accepting answers
void MainWindowController::runUserSurvey() {
    //data reset and releasing then initializing order
    delete order;
    order = new vector<int>();
    currentEvidence = 0;
    statusLayoutController->outcomes = knowledgeBaseController->getOutcomes();
    statusLayoutController->setResultLabel();
    statusLayoutController->historyLabel->setText(QString(""));
    answerSpinBox->setValue(0);

    uniform_int_distribution<int> distribution(1, (int)knowledgeBaseController->getEvidences().size());

    //fill order
    while(order->size() != knowledgeBaseController->getEvidences().size()) {
        auto number = distribution(*engine);
        if(std::find(order->begin(), order->end(), number) == order->end())
            order->push_back(number);
    }

    //Displaying evidence on the screen and enabling all elements
    setEnableElements(true);
    questionText->setText(knowledgeBaseController->getEvidences()[(*order)[currentEvidence]]);
}

//Destructor
MainWindowController::~MainWindowController() {
    delete detailedDescription;
    delete nameDescription;
    delete minusSpinButton;
    delete plusSpinButton;
    delete answerSpinBox;
    delete answerButton;
    delete openButton;
    delete runButton;
    delete statusWidget;
    delete statusLayoutController;
    delete engine;
    delete order;
    delete ui;
}