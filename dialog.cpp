#include "dialog.h"

#include <QHBoxLayout>

Dialog::Dialog(QWidget *parent)
    : DDialog(parent),
      m_icon(new QLabel),
      m_nameEdit(new DLineEdit),
      m_commentEdit(new DLineEdit),
      m_execEdit(new DFileChooserEdit)
{
    // set title
    setTitle(tr("Desktop item editor"));

    // default icon value
    const QSize defaultIconSize(48, 48);
    const QIcon defaultIcon = QIcon::fromTheme("firefox");
    m_icon->setFixedSize(48, 48);
    m_icon->setPixmap(defaultIcon.pixmap(defaultIconSize));

    QGridLayout *rightLayout = new QGridLayout;
    rightLayout->addWidget(new QLabel(tr("Name")), 0, 0);
    rightLayout->addWidget(m_nameEdit, 0, 1);
    rightLayout->addWidget(new QLabel(tr("Exec")), 1, 0);
    rightLayout->addWidget(m_execEdit, 1, 1);
    rightLayout->addWidget(new QLabel(tr("Comment")), 2, 0);
    rightLayout->addWidget(m_commentEdit, 2, 1);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(5);
    mainLayout->addWidget(m_icon);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(rightLayout);

    QWidget *mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);

    addContent(mainWidget);

    // add buttons
    addButton(tr("Confirm"));
}

Dialog::~Dialog()
{

}
