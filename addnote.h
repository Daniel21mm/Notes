#ifndef ADDNOTE_H
#define ADDNOTE_H

#include <QDialog>

namespace Ui {
class addNote;
}

class AddNote : public QDialog
{
    Q_OBJECT

public:
    explicit AddNote(QWidget *parent = 0);
    ~AddNote();

signals:
    void    createNewNote(const QString& name, const QString& text);

private:
    void    clear();

private slots:
    void    btOk();
    void    btCancel();

private:
    Ui::addNote *ui;
};

#endif // ADDNOTE_H
