#ifndef SMALLEXPERTSYSTEM_OUTCOME_H
#define SMALLEXPERTSYSTEM_OUTCOME_H

#include <iostream>
#include <utility>
#include <QString>
#include <cfloat>
#include <ranges>
#include <map>

using namespace std;
namespace views = std::ranges::views;

class Outcome {
    //Variables
private:
    QString name;
    double priorProbability;
    map<int, pair<double, double>> probabilities;

    //Methods
public:
    Outcome();
    Outcome(QString name, double priorProbability,
                     map<int, pair<double, double>> probabilities);
    QString getName();
    double getPriorProbability();
    map<int, pair<double, double>> getProbabilities();
};

#endif //SMALLEXPERTSYSTEM_OUTCOME_H