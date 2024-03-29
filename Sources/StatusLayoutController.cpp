#include "ui_StatusLayoutController.h"
#include "StatusLayoutController.h"

//Constructor
StatusLayoutController::StatusLayoutController(QWidget *parent) :
        QWidget(parent), ui(new Ui::StatusLayoutController) {
    ui->setupUi(this);
    resultLabel = ui->resultLabel;
    historyLabel = ui->historyLabel;
    historyScrollArea = ui->historyScrollArea;
}

//Destructor
StatusLayoutController::~StatusLayoutController() {
    delete resultLabel;
    delete historyLabel;
    delete historyScrollArea;
    delete ui;
}

//displays the result in resultLabel, sorting the data by prior probability
void StatusLayoutController::setResultLabel() {
    //Sorting outcomes by priorProbability
    std::sort(outcomes.begin(), outcomes.end(), [](const Outcome& outcome1, const Outcome& outcome2) {
        return outcome1.priorProbability > outcome2.priorProbability;
    });
    //resultQString init
    QString resultQString;
    for(auto i : views::iota(0, (int)outcomes.size())) {
        auto roundPriorProbability = QLatin1String(to_string(round(outcomes[i].priorProbability * 1000000.0) / 1000000.0));
        if(i != 0)
            resultQString.append(QString("\r\n"));
        resultQString.append(QString("(") + roundPriorProbability + QString(") ") + outcomes[i].getName());
    }
    //Show outcomes in resultLabel
    resultLabel->setText(resultQString);
}

//Finding the posterior probability and displaying the results and history
void StatusLayoutController::findPosteriorProbabilities(int evidenceNumber, int evidenceScale) {
    //Finding the posterior probability using Bayes' formula
    for(auto i : views::iota(0, (int)outcomes.size()))
        if(outcomes[i].getProbabilities().find(evidenceNumber)->first != outcomes[i].getProbabilities().end()->first)
            if(evidenceScale != 0) {
                auto priorProbability = outcomes[i].priorProbability;
                outcomes[i].priorProbability = (evidenceScale > 0)
                        ? ((outcomes[i].getProbabilities()[evidenceNumber].first * priorProbability)/(outcomes[i].getProbabilities()[evidenceNumber].first * priorProbability + outcomes[i].getProbabilities()[evidenceNumber].second * (1 - priorProbability)))
                        : (((1 - outcomes[i].getProbabilities()[evidenceNumber].first) * priorProbability)/((1 - outcomes[i].getProbabilities()[evidenceNumber].first) * priorProbability + (1 - outcomes[i].getProbabilities()[evidenceNumber].second) * (1 - priorProbability)));
                outcomes[i].priorProbability = (evidenceScale > 0)
                        ? (priorProbability + (outcomes[i].priorProbability - priorProbability) * ((double)evidenceScale / 5.0))
                        : (priorProbability + (priorProbability - outcomes[i].priorProbability) * ((double)evidenceScale / 5.0));
            }
    setResultLabel();
}

//Show answers in historyLabel
void StatusLayoutController::setHistoryLabel(int questionNumber, int evidenceScale, const QString& evidenceQString) {
    //historyQString init
    QString historyQString = "";
    if(questionNumber != 1) {
        historyQString = historyLabel->text();
        historyQString.append(QString("\r\n"));
    }
    historyQString.append(QLatin1String(to_string(questionNumber)) + QString(") Ответ: ") + QLatin1String(to_string(evidenceScale)) + QString(" - \"") + evidenceQString);
    //Show all history
    historyLabel->setText(historyQString);
    historyScrollArea->verticalScrollBar()->setValue(historyScrollArea->verticalScrollBar()->maximum());
}