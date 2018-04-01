#ifndef NOTEMODEL_H
#define NOTEMODEL_H

#include <QObject>
#include <QList>
#include <QDate>

class NoteModel : public QObject
{
    Q_OBJECT
public:
    explicit NoteModel(int id,
                       const QString& name,
                       const QString& text,
                       const QString& date,
                       QObject *parent = nullptr);

    int                id()   const {  return id_;   }
    const QString&     name() const {  return name_; }
    const QString&     text() const {  return text_; }
    const QString&     date() const {  return date_; }

signals:

    void    update(int id, const QString& name, const QString& text);
    void    sgDeleteNote(int id);

public slots:

    void    setNewData(const QString& newName, const QString& newText);
    void    deleteNote();

private:

    int         id_;
    QString     name_;
    QString     text_;
    QString     date_;
};

using NoteModelList = QList<NoteModel*>;

#endif // NOTEMODEL_H
