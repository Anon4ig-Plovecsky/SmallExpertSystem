#ifndef SMALLEXPERTSYSTEM_KNOWLEDGEBASECONTROLLER_H
#define SMALLEXPERTSYSTEM_KNOWLEDGEBASECONTROLLER_H

#include <KnowledgeBaseProcessingStatus.h>
#include <QRegularExpression>
#include <Outcome.h>
#include <iostream>
#include <QString>
#include <utility>
#include <ranges>
#include <vector>
#include <QList>
#include <map>

using namespace std;
namespace ranges = std::ranges;
namespace views = ranges::views;

class KnowledgeBaseController {
    //Variables
private:
    const int SECTIONS_NUMBER = 3;
    const QString EMPTY_STRING = "\r\n\r\n";
    QStringList baseSections;
    QString knowledgeBaseString;
    KnowledgeBaseProcessingStatus processingStatus = KnowledgeBaseProcessingStatus::SUCCESS;
    //Received data
    QString knowledgeBaseDescription;
    map<int, QString> evidences;
    vector<Outcome> outcomes;

    //Methods
public:
    KnowledgeBaseController();
    explicit KnowledgeBaseController(QString knowledgeBaseString);
    KnowledgeBaseProcessingStatus getProcessingStatus();
    QString getKnowledgeBaseDescription();
    map<int, QString> getEvidences();
    vector<Outcome> getOutcomes();
private:
    void getDataFromKnowledgeBase();
};

#endif //SMALLEXPERTSYSTEM_KNOWLEDGEBASECONTROLLER_H