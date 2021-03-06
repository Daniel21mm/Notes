#include "mainwidget.h"
#include "ui_mainwidget.h"

#include "noteleftview.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    setFixedSize(800, 600);

    init();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::init()
{
    db = new DataBase;

    startPage = new StartPage;
    ui->stackedWidget->addWidget(startPage);

    noteList = db->noteList();
    for(NoteModel* model : noteList)
        addItem(model);

    connect(ui->listWidget, &QListWidget::itemClicked,
            this,           &MainWidget::openPage);

    connect(ui->search,     &QLineEdit::textEdited,
            this,           &MainWidget::searchNotes);
}


void MainWidget::addItem(NoteModel *model)
{
    NoteLeftView* view = new NoteLeftView(model, this);

    QListWidgetItem* item = new QListWidgetItem{};
    item->setSizeHint(view->sizeHint());

    connect(model, &NoteModel::sgDeleteNote,
            this,  &MainWidget::deleteNote);

    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, view);

}

void MainWidget::deleteNote(int id)
{
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        QListWidgetItem* item = ui->listWidget->item(i);

        NoteLeftView* view = qobject_cast<NoteLeftView*>(ui->listWidget->itemWidget(item));

        if(id == view->model()->id())
        {
            item->setHidden(true);
            ui->listWidget->removeItemWidget(item);
            break;
        }
    }
    noteRightList[id]->hide();
    ui->stackedWidget->setCurrentWidget(startPage);
    ui->stackedWidget->removeWidget(noteRightList[id]);

    noteRightList.remove(id);
}

void MainWidget::openPage(QListWidgetItem *item)
{
    if(NoteLeftView* m =  qobject_cast<NoteLeftView*>( ui->listWidget->itemWidget(item)))
    {
        if(noteRightList.contains(m->model()->id()))
        {
            ui->stackedWidget->setCurrentWidget(noteRightList[m->model()->id()]);
        }
        else
        {
            NoteRightView* RView = new NoteRightView(m->model());
            ui->stackedWidget->addWidget(RView);
            noteRightList.insert(m->model()->id(), RView);
        }
    }
}

void MainWidget::searchNotes(const QString &subStr)
{
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        QListWidgetItem* item = ui->listWidget->item(i);

        if(NoteLeftView* view = qobject_cast<NoteLeftView*>(ui->listWidget->itemWidget(item)))
        {
            QString name = view->model()->name().toLower();
            item->setHidden(!name.contains(subStr.toLower()));
        }
    }
}
