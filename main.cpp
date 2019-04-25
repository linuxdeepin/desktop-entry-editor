#include "dialog.h"

#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("Desktop entry editor");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", QCoreApplication::translate("main", "desktop file to edit or create"));

    parser.process(a);

    const QStringList args = parser.positionalArguments();
    if (args.length() == 0) {
        parser.showHelp(0);
    }
    const QString targetFile = args.at(0);

    Dialog w(targetFile);
    w.show();

    return a.exec();
}
