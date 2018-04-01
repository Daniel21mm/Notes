#include "notemodel.h"

NoteModel::NoteModel(int id, const QString &name, const QString &text, const QString &date, QObject *parent)
    :QObject(parent),
     id_(id),
     name_(name),
     text_(text),
     date_(date)
{

}

void NoteModel::setNewData(const QString &newName, const QString &newText)
{
    name_ = newName;
    text_ = newText;
    emit update(id_, name_, text_);
}

void NoteModel::deleteNote()
{
    emit sgDeleteNote(id_);
    deleteLater();
}
