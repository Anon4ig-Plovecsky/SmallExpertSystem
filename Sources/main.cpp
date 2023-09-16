#include <MainWindowController.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindowController mainWindowController;
    mainWindowController.show();
    return QApplication::exec();
}
