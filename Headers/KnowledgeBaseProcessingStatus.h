#ifndef SMALLEXPERTSYSTEM_KNOWLEDGEBASEPROCESSINGSTATUS_H
#define SMALLEXPERTSYSTEM_KNOWLEDGEBASEPROCESSINGSTATUS_H

enum class KnowledgeBaseProcessingStatus {
    SUCCESS = 0,
    SECTIONS_ERROR, //Not enough or many sectional blocks
    EVIDENCE_ERROR, //Syntax violation in evidence
    OUTCOME_ERROR //Error in the outcomes
};

#endif //SMALLEXPERTSYSTEM_KNOWLEDGEBASEPROCESSINGSTATUS_H
