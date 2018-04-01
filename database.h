#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql/QSqlDatabase>

#include "notemodel.h"

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();

    NoteModelList   noteList();

    int             createrNewNote(const QString& name,
                                   const QString& text);
    NoteModel*      newNoteById(int id);


signals:

public slots:

    void            saveNoteById(int id, const QString& name, const QString& text);
    void            deleteNoteById(int id);
private:
    QSqlDatabase  db;

};

#endif // DATABASE_H
