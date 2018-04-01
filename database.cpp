#include "database.h"

#include <QDebug>
#include <QSqlQuery>

DataBase::DataBase(QObject *parent)
    : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.sqlite3");

    if(db.open())
        qDebug() << "База данных | База данных успешно открыта" << endl;
    else
        qDebug() << "База данных | Ошибка открытия базы данных" << endl;
}

DataBase::~DataBase()
{
    db.close();
}

NoteModelList DataBase::noteList()
{
    NoteModelList list{};

    QSqlQuery query(db);
    QString str_query = "SELECT id, name, text, date FROM Notes";

    if(query.exec(str_query))
    {
        while(query.next())
        {
            int id          = query.value("id").toInt();
            QString name    = query.value("name").toString();
            QString text    = query.value("text").toString();
            QString date = query.value("date").toString();

            NoteModel* model = new NoteModel(id, name, text, date);
            connect(model,  &NoteModel::update,
                    this,   &DataBase::saveNoteById);
            connect(model,  &NoteModel::sgDeleteNote,
                    this,   &DataBase::deleteNoteById);

            list.append(model);
        }
    }
    else
        qDebug() << "База данных | Ошибка выгрузки заметок";

    return list;
}

int DataBase::createrNewNote(const QString &name, const QString &text)
{
    QSqlQuery query(db);
    QString str_query = QString("INSERT INTO Notes (name, text, date ) "
                                "VALUES ( '%1', '%2', date('now'));"
                                )
            .arg(name)
            .arg(text);

    if(!query.exec(str_query))
    {
        qDebug() << "База данных | Ошибка создания новой заметки" << endl;
        return -1;
    }

    str_query = "SELECT max(id) as id FROM Notes;";

    if(query.exec(str_query) && query.next())
        return query.value("id").toInt();
    else
        qDebug() << "База данных | Ошибка получения id новой заметки" << endl;

    return -1;
}

NoteModel *DataBase::newNoteById(int id)
{

    QSqlQuery query(db);
    QString str_query = QString("SELECT name, text, date "
                                "FROM Notes "
                                "WHERE id = %1").arg(id);

    if(query.exec(str_query) && query.next())
    {
        int id          = query.value("id").toInt();
        QString name    = query.value("name").toString();
        QString text    = query.value("text").toString();
        QString date    = query.value("date").toString();

        NoteModel* model = new NoteModel(id, name, text, date);
        connect(model,  &NoteModel::update,
                this,   &DataBase::saveNoteById);
        connect(model,  &NoteModel::sgDeleteNote,
                this,   &DataBase::deleteNoteById);
        return model;
    }
    else
        qDebug() << "База данных | Ошибка получения новой заметки";

    return Q_NULLPTR;
}


void DataBase::saveNoteById(int id, const QString &name, const QString &text)
{
    QSqlQuery query(db);
    QString str_query = QString("UPDATE Notes "
                                "SET name = '%2', text = '%3' "
                                "WHERE id = %1"
                                )
                                .arg(id)
                                .arg(name)
                                .arg(text);

    if(!query.exec(str_query))
        qDebug() << "База данных | Ошибка сохранения инфы о заметки";

}

void DataBase::deleteNoteById(int id)
{
    QSqlQuery query(db);
    QString str_query = QString("DELETE FROM Notes WHERE id = 2").arg(id);

    if(!query.exec(str_query))
        qDebug() << "База данных | Ошибка удаления заметки";

}
