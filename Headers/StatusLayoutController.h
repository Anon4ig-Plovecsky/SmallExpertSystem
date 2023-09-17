#ifndef SMALLEXPERTSYSTEM_STATUSLAYOUTCONTROLLER_H
#define SMALLEXPERTSYSTEM_STATUSLAYOUTCONTROLLER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class StatusLayoutController; }
QT_END_NAMESPACE

class StatusLayoutController : public QWidget {
Q_OBJECT
    //Variables
private:
    Ui::StatusLayoutController *ui;

    //Methods
public:
    explicit StatusLayoutController(QWidget *parent = nullptr);
    ~StatusLayoutController() override;
};

#endif //SMALLEXPERTSYSTEM_STATUSLAYOUTCONTROLLER_H