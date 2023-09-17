#include <MainWindowController.h>

int main(int argc, char *argv[]) {
    //Get style in style.css
    QFile qFile("../Forms/style.css");
    qFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(qFile.readAll());

    //application init
    QApplication application(argc, argv);
    application.setStyleSheet(styleSheet);

    //MainWindowController init
    MainWindowController mainWindowController;
    mainWindowController.show();

    return QApplication::exec();
}
