#ifndef NOTERIGHTVIEW_H
#define NOTERIGHTVIEW_H

#include <QWidget>

#include "notemodel.h"

namespace Ui {
class NoteRightView;
}

class NoteRightView : public QWidget
{
    Q_OBJECT

public:
    explicit NoteRightView(NoteModel *model, QWidget *parent = Q_NULLPTR);
    ~NoteRightView();

    void    init();

private slots:
    void    save();

private:
    Ui::NoteRightView *ui;

    NoteModel*      model_;
};

#endif // NOTERIGHTVIEW_H
