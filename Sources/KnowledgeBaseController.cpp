#include <KnowledgeBaseController.h>

//Constructor
KnowledgeBaseController::KnowledgeBaseController(QString knowledgeBaseString) {
    this->knowledgeBaseString = std::move(knowledgeBaseString);
    getDataFromKnowledgeBase();
}

//Processing the received string, checking for errors
void KnowledgeBaseController::getDataFromKnowledgeBase() {
    //Get section of knowledge base
    baseSections = knowledgeBaseString.split(EMPTY_STRING);

    //Checking for the presence of the required number of sections
    if(baseSections.length() != SECTIONS_NUMBER) {
        processingStatus = KnowledgeBaseProcessingStatus::SECTIONS_ERROR;
        return;
    }

    //evidences init
    knowledgeBaseDescription = baseSections[0];
    evidences = std::move(getEvidences());
    if(evidences.empty()) {
        processingStatus = KnowledgeBaseProcessingStatus::EVIDENCE_ERROR;
        return;
    }


    std::cout << "result" << std::endl; //TODO
}

//Get evidences from second section of knowledge base
map<int, QString> KnowledgeBaseController::getEvidences() {
    map<int, QString> evidencesMap;
    //Get every string from evidence section
    auto evidencesQStringList = baseSections[1].split("\n");

    //First string is evidence description
    if(evidencesQStringList.length() <= 1) return evidencesMap;

    //Obtaining evidences and number
    for(auto i : views::iota(1, evidencesQStringList.length()))
        evidencesMap[i] = evidencesQStringList[i];
    return evidencesMap;
}

//Get outcomes from third section of knowledge base
vector<Outcome> KnowledgeBaseController::getOutcomes() {
    auto outcomeQStringsList = baseSections[2].split("\n");
    vector<Outcome> outcomesVector(outcomeQStringsList.length());
    //TODO
    return outcomesVector;
}
