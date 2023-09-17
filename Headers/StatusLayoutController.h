#ifndef SMALLEXPERTSYSTEM_STATUSLAYOUTCONTROLLER_H
#define SMALLEXPERTSYSTEM_STATUSLAYOUTCONTROLLER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class StatusLayoutController; }
QT_END_NAMESPACE

class StatusLayoutController : public QWidget {
Q_OBJECT

public:
    explicit StatusLayoutController(QWidget *parent = nullptr);

    ~StatusLayoutController() override;
private:
    Ui::StatusLayoutController *ui;
};


#endif //SMALLEXPERTSYSTEM_STATUSLAYOUTCONTROLLER_H
