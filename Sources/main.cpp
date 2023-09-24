#include <MainWindowController.h>

int main(int argc, char *argv[]) {
    //Get style in style.css
    QFile qFile("../Forms/style.css");
    qFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(qFile.readAll());
    qFile.close();

    //application init
    QApplication application(argc, argv);
    QApplication::setWindowIcon(QIcon("../Icons/titleIcon.png"));
    application.setStyleSheet(styleSheet);

    //MainWindowController init
    MainWindowController mainWindowController;
    mainWindowController.show();

    return QApplication::exec();
}
