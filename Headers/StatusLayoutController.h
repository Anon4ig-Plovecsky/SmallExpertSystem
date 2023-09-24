#ifndef SMALLEXPERTSYSTEM_STATUSLAYOUTCONTROLLER_H
#define SMALLEXPERTSYSTEM_STATUSLAYOUTCONTROLLER_H

#include <Outcome.h>
#include <algorithm>
#include <QWidget>
#include <QLabel>
#include <ranges>

namespace views = std::ranges::views;

QT_BEGIN_NAMESPACE
namespace Ui { class StatusLayoutController; }
QT_END_NAMESPACE

class StatusLayoutController : public QWidget {
Q_OBJECT
    //Variables
public:
    vector<Outcome> outcomes;
private:
    //ui
    QLabel *resultLabel;
    Ui::StatusLayoutController *ui;

    //Methods
public:
    explicit StatusLayoutController(QWidget *parent = nullptr);
    ~StatusLayoutController() override;
    void setResultLabel();
    void findPosteriorProbabilities(int questionNumber, int evidenceNumber, int evidenceScale);
};

#endif //SMALLEXPERTSYSTEM_STATUSLAYOUTCONTROLLER_H