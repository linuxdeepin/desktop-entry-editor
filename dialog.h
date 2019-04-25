#ifndef DIALOG_H
#define DIALOG_H

#include <ddialog.h>

#include <QLabel>

#include <XdgDesktopFile>

#include <dlineedit.h>
#include <dfilechooseredit.h>

DWIDGET_USE_NAMESPACE

class Dialog : public DDialog
{
    Q_OBJECT

public:
    Dialog(QString desktopFile);
    ~Dialog();

public slots:
    void setIcon(const QString icon);

private:
    QLabel *m_icon;
    DLineEdit *m_nameEdit;
    DLineEdit *m_commentEdit;
    DFileChooserEdit *m_execEdit;

    XdgDesktopFile *m_parser;
    QString m_iconFile;
    QString m_desktopFile;

    void initUI();
    void initDefaultValues();
    void initConnections();

    bool eventFilter(QObject *, QEvent *);

private slots:
    void createOrUpdateDesktopFile();
};

#endif // DIALOG_H
