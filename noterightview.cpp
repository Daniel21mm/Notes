#include "noterightview.h"
#include "ui_noterightview.h"

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

    connect(ui->save,       &QPushButton::clicked,
            this,           &NoteRightView::save);
}

void NoteRightView::save()
{
    model_->setNewData(ui->name->text(), ui->text->toPlainText());
}
