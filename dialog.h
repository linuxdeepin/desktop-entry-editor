#ifndef DIALOG_H
#define DIALOG_H

#include <ddialog.h>

#include <QLabel>

#include <dlineedit.h>
#include <dfilechooseredit.h>

DWIDGET_USE_NAMESPACE

class Dialog : public DDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    QLabel *m_icon;
    DLineEdit *m_nameEdit;
    DLineEdit *m_commentEdit;
    DFileChooserEdit *m_execEdit;
};

#endif // DIALOG_H
