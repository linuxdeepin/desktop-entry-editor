#include "dialog.h"

#include <QHBoxLayout>
#include <QDebug>
#include <QEvent>

static const QSize DefaultIconSize(48, 48);

static const QString KeyType = "Type";
static const QString KeyName = "Name";
static const QString KeyIcon = "Icon";
static const QString KeyExec = "Exec";
static const QString KeyComment = "Comment";

Dialog::Dialog(QString desktopFile)
    : DDialog(),
      m_icon(new QLabel),
      m_nameEdit(new DLineEdit),
      m_commentEdit(new DLineEdit),
      m_execEdit(new DFileChooserEdit),

      m_parser(new XdgDesktopFile),
      m_desktopFile(desktopFile)
{
    initUI();
    initDefaultValues();
    initConnections();
}

Dialog::~Dialog()
{

}

void Dialog::setIcon(const QString icon)
{
    if (icon.length() == 0) {
        return;
    }
    m_iconFile = icon;

    if (QFile::exists(icon)) {
        // A specific file.
        QPixmap pix(icon);
        pix.scaled(DefaultIconSize);

        m_icon->setPixmap(pix);
    } else {
        QIcon defaultIcon = QIcon::fromTheme("application-x-executable");
        defaultIcon = QIcon::fromTheme(icon, defaultIcon);
        QPixmap defaultIconPix = defaultIcon.pixmap(DefaultIconSize);
        m_icon->setPixmap(defaultIconPix);
    }
}

void Dialog::initUI()
{
    // set title
    setTitle(tr("Desktop entry editor"));

    m_icon->setFixedSize(DefaultIconSize);
    m_icon->installEventFilter(this);

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

void Dialog::initDefaultValues()
{
    setIcon("application-x-executable");

    m_nameEdit->setPlaceholderText(tr("name to display"));
    m_commentEdit->setPlaceholderText(tr("comment of this desktop entry"));
    m_execEdit->setPlaceholderText(tr("choose a binary"));


    if (QFile::exists(m_desktopFile)) {
        QDir dir = QDir::currentPath();
        m_parser->load(dir.absoluteFilePath(m_desktopFile));

        m_nameEdit->setText(m_parser->value(KeyName).toString());
        m_commentEdit->setText(m_parser->value(KeyComment).toString());
        m_execEdit->setText(m_parser->value(KeyExec).toString());
        setIcon(m_parser->value(KeyIcon).toString());
    }
}

void Dialog::initConnections()
{
    connect(this, &Dialog::buttonClicked, this, &Dialog::createOrUpdateDesktopFile);
}

bool Dialog::eventFilter(QObject *o, QEvent *e)
{
    if (o == m_icon && e->type() == QEvent::MouseButtonRelease) {
        QString iconFile = QFileDialog::getOpenFileName();
        setIcon(iconFile);
    }

    return false;
}

void Dialog::createOrUpdateDesktopFile()
{
    m_parser->setValue(KeyType, "Application");
    m_parser->setValue(KeyName, m_nameEdit->text());
    m_parser->setValue(KeyIcon, m_iconFile);
    m_parser->setValue(KeyExec, m_execEdit->text());
    m_parser->setValue(KeyComment, m_commentEdit->text());
    m_parser->save(m_desktopFile);
}
