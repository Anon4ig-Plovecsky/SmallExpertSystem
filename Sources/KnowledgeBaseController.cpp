#include <KnowledgeBaseController.h>

//null constructor
KnowledgeBaseController::KnowledgeBaseController() {
    processingStatus = KnowledgeBaseProcessingStatus::SECTIONS_ERROR;
}
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

    //knowledgeBaseDescription init
    knowledgeBaseDescription = baseSections[0];

    //evidences init
    evidences = std::move(getEvidences());
    if(evidences.empty()) {
        processingStatus = KnowledgeBaseProcessingStatus::EVIDENCE_ERROR;
        return;
    }

    //outcomes init
    outcomes = std::move(getOutcomes());
    if(outcomes.empty()) {
        processingStatus = KnowledgeBaseProcessingStatus::OUTCOME_ERROR;
        return;
    }

    processingStatus = KnowledgeBaseProcessingStatus::SUCCESS;
}

//Get evidences from second section of knowledge base
map<int, QString> KnowledgeBaseController::getEvidences() {
    map<int, QString> evidencesMap;
    //Get every string from evidence section
    auto evidencesQStringList = baseSections[1].split("\r\n");

    //First string is evidence description
    if(evidencesQStringList.length() <= 1) return evidencesMap;

    //Obtaining evidences and number
    for(auto i : views::iota(1, evidencesQStringList.length()))
        evidencesMap[i] = evidencesQStringList[i];
    return evidencesMap;
}

//Get outcomes from third section of knowledge base
vector<Outcome> KnowledgeBaseController::getOutcomes() {
    auto outcomeQStringsList = baseSections[2].split("\r\n");
    auto *outcomesVector = new vector<Outcome>((outcomeQStringsList.length()));

    //Filling outcomes with values from a file
    for(auto i : views::iota(0, outcomeQStringsList.length())) {
        //Getting collection of outcome parameters
        auto outcomeParameters = outcomeQStringsList[i].split(", ");
        if(outcomeParameters.length() < 3) //Must be at least three values
            return *(new vector<Outcome>());

        //The first two parameters are the name of the outcome and the prior probability
        auto outcomeName = outcomeParameters[0];
        auto outcomePriorProbability = outcomeParameters[1].toDouble();

        //Obtaining outcome probabilities for evidence
        map<int, pair<double, double>> outcomeProbabilities;

        //Regular Expression on int and double
        QRegularExpression qRegularExpression[] { QRegularExpression(QRegularExpression::anchoredPattern("\\d+")),                       //Evidence number
                                                  QRegularExpression(QRegularExpression::anchoredPattern(R"((1\.0+|1|(0\.\d+)))"))};     //Probability values
        for(auto parameterIndex : views::iota(2, outcomeParameters.length())) {
            //Checking numbers for int, double, double and for missing key
            auto parameterValues = outcomeParameters[parameterIndex].split(",");
            if(
                    parameterValues.length() != 3 ||
                    !qRegularExpression[0].match(parameterValues[0]).hasMatch() ||
                    !qRegularExpression[1].match(parameterValues[1]).hasMatch() ||
                    !qRegularExpression[1].match(parameterValues[2]).hasMatch() ||
                    outcomeProbabilities.find(parameterValues[0].toInt()) != outcomeProbabilities.end()
            ) return *(new vector<Outcome>());

            //Get probabilities
            pair<double, double> probabilityValues;
            probabilityValues.first = parameterValues[1].toDouble();
            probabilityValues.second = parameterValues[2].toDouble();
            outcomeProbabilities[parameterValues[0].toInt()] = probabilityValues;
        }

        //Adding outcome to vector
        Outcome outcome(outcomeName, outcomePriorProbability,
                        outcomeProbabilities);
        (*outcomesVector)[i] = outcome;
    }
    return *outcomesVector;
}

//processingStatus getter
KnowledgeBaseProcessingStatus KnowledgeBaseController::getProcessingStatus() {
    return processingStatus;
}

//knowledgeDescription getter
QString KnowledgeBaseController::getKnowledgeBaseDescription() {
    return knowledgeBaseDescription;
}