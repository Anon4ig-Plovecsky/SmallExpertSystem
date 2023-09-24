#include <Outcome.h>

//Null constructor
Outcome::Outcome() {
    name = "";
    priorProbability = -DBL_MAX;
}
//Constructor
Outcome::Outcome(QString name, double priorProbability, map<int, pair<double, double>> probabilities) {
    this->name = std::move(name);
    this->priorProbability = priorProbability;
    this->probabilities = std::move(probabilities);
}
//name getter
QString Outcome::getName() {
    return name;
}
//probabilities getter
map<int, pair<double, double>> Outcome::getProbabilities() {
    return probabilities;
}