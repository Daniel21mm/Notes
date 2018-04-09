#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QMap>

#include "startpage.h"
#include "database.h"
#include "noterightview.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = Q_NULLPTR);
    ~MainWidget();

    void    init();

private slots:
    void    openPage(QListWidgetItem* item);
    void    searchNotes(const QString& subStr);
    void    addItem(NoteModel* model);

    void    deleteNote(int id);

private:
    Ui::MainWidget *ui;

    StartPage*      startPage;

    DataBase*       db;
    NoteModelList   noteList;
    QMap<int, NoteRightView*> noteRightList;
};

#endif // MAINWIDGET_H
