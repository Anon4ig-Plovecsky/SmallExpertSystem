#ifndef SMALLEXPERTSYSTEM_STATUSLAYOUTCONTROLLER_H
#define SMALLEXPERTSYSTEM_STATUSLAYOUTCONTROLLER_H

#include <QScrollArea>
#include <QScrollBar>
#include <algorithm>
#include <Outcome.h>
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
    QLabel *historyLabel;
private:
    //ui
    QLabel *resultLabel;
    QScrollArea *historyScrollArea;
    Ui::StatusLayoutController *ui;

    //Methods
public:
    explicit StatusLayoutController(QWidget *parent = nullptr);
    ~StatusLayoutController() override;
    void setResultLabel();
    void findPosteriorProbabilities(int evidenceNumber, int evidenceScale);
    void setHistoryLabel(int questionNumber, int evidenceScale, const QString& evidenceQString);
};

#endif //SMALLEXPERTSYSTEM_STATUSLAYOUTCONTROLLER_H