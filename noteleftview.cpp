#include "noteleftview.h"
#include "ui_noteleftview.h"

NoteLeftView::NoteLeftView(NoteModel *model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NoteLeftView)
{
    ui->setupUi(this);

    model_ = model;
    connect(model_, &NoteModel::update,
            this,   &NoteLeftView::update);
    connect(model_, &NoteModel::destroyed,
            this,   &NoteLeftView::deleteLater);

   ui->name->setText(model_->name());
   ui->date->setText(model_->date());
}

NoteLeftView::~NoteLeftView()
{
    delete ui;
}

void NoteLeftView::update()
{
    ui->name->setText(model_->name());
}
