#include "addnote.h"
#include "ui_addnote.h"

#include <QMessageBox>

AddNote::AddNote(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNote)
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::MSWindowsFixedSizeDialogHint);

    ui->setupUi(this);
}

AddNote::~AddNote()
{
    delete ui;
}

void AddNote::clear()
{
    ui->name->clear();
    ui->text->clear();
}

void AddNote::btOk()
{
    if(ui->name->text().isEmpty())
    {
        QMessageBox::warning(this, "Пустое имя!", "Нельзя создать заметку без имени...");
        return;
    }

    emit createNewNote(ui->name->text(), ui->text->toPlainText());

    btCancel();
}

void AddNote::btCancel()
{
    hide();
    clear();
}
