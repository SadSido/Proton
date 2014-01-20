#include "window.h"
#include "ui_window.h"
#include "items.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QDrag>

namespace Proton
{

// **************************************************************************************************

ListEntry::ListEntry(QWidget *parent, const QString &type, const QString &name)
: QWidget(parent), m_name(name), m_type(type)
{
}

ListEntry::~ListEntry()
{
}

void ListEntry::mousePressEvent(QMouseEvent *event)
 {
    qDebug() << "ListEntry :: mouse pressed for item " << m_name;

     if (event->button() == Qt::LeftButton)
     {
         QDrag *drag = new QDrag(this);
         QMimeData *mimeData = new QMimeData;

         QByteArray data;
         QDataStream stream(&data, QIODevice::Append);

         stream << m_type;
         stream << m_name;

         mimeData->setData("type-name-pair", data);

         drag->setMimeData(mimeData);
         drag->exec();
     }
 }
void ListEntry::paintEvent(QPaintEvent *)
{
    auto myrect = this->rect();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::darkGreen);
    painter.drawRect(myrect);

    painter.setPen(Qt::darkGray);
    painter.drawLine(myrect.topLeft(), myrect.bottomRight());

    painter.drawText(myrect, Qt::TextWordWrap, m_name);
}

// **************************************************************************************************

// c-tor and d-tor:

Window::Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window)
{
    // layout all the stuff:
    ui->setupUi(this);

    // additional initialization:
    connectSignals();

    // create default prototype:
    m_game.reset(new GameDesc());
    loadPrototype("D:/Projects/Proton/Sample/sample.proton");

    // finally, create scene:
    m_scene.reset(new Scene());
    ui->view->setScene(m_scene.data());
}

Window::~Window()
{
    delete ui;
}

// handling of signals:

void Window::menu_OpenPrototype()
{
    QString filename = QFileDialog::getOpenFileName(this);
    loadPrototype(filename);
}

void Window::view_OnItemDropped(const QString &type, const QString &name)
{
    qDebug() << "Window :: adding item to scene" << type << name;

    if (auto item = createItem(m_scene.data(), m_game, type, name))
    {
        m_scene->addItem(item);
    }
}

// helpers:

void Window::loadPrototype(const QString &filename)
{
    qDebug() << "Window :: load prototype from " << filename;

    QFile file(filename);
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QString content(file.readAll());

        try
        {
            // parse new prototype:
            m_game.reset(new GameDesc(content));
            // on success, update ui:
            refillListViews();
        }
        catch (ParseError &pe)
        {
            const QString caption = "Failed to read file";
            const QString message = QString("%1 : %2").arg(pe.name, pe.desc);

            QMessageBox::warning(this, caption, message);
        }
    }
}

void Window::connectSignals()
{
    connect(ui->actionOpen_prototype, SIGNAL(triggered()), this, SLOT(menu_OpenPrototype()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->view, SIGNAL(onItemDropped(QString,QString)), this, SLOT(view_OnItemDropped(QString,QString)));
}

void Window::refillListViews()
{
    ui->deck_list->clear();

    auto decks = m_game->getDecks();
    auto keys  = decks.keys();

    foreach (QString key, keys)
    {
        QListWidgetItem* item = new QListWidgetItem(ui->deck_list);
        ui->deck_list->addItem(item);

        auto entry = new ListEntry(ui->deck_list, tag_deck, key);
        entry->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);


        item->setSizeHint(QSize(ui->deck_list->size().width(), 100));

        ui->deck_list->setItemWidget(item, entry);
    }
}

// **************************************************************************************************

} // namespace
