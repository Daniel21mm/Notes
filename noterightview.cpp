#include "noterightview.h"
#include "ui_noterightview.h"

#include <QMessageBox>
#include <QDebug>

NoteRightView::NoteRightView(NoteModel *model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NoteRightView)
{
    ui->setupUi(this);

    model_ = model;

    init();
}

NoteRightView::~NoteRightView()
{
    delete ui;
}

void NoteRightView::init()
{
    ui->name->setText(model_->name());
    ui->text->setText(model_->text());

    //вынести в форму
    connect(ui->save,       &QPushButton::clicked,
            this,           &NoteRightView::save);

    connect(ui->deleteNote, &QPushButton::clicked,
            this,           &NoteRightView::showDialogByDelete);
}

void NoteRightView::save()
{
    model_->setNewData(ui->name->text(), ui->text->toPlainText());
}

void NoteRightView::showDialogByDelete()
{
    int res = QMessageBox::question(Q_NULLPTR,
                                    "Удлаение заметки",
                                    "Вы уверенны что хотите удалить эту заметку?",
                                    QMessageBox::StandardButton::Yes,
                                    QMessageBox::StandardButton::No);

    if(res == QMessageBox::StandardButton::Yes)
       emit model_->deleteNote();

}
