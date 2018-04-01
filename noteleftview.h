#ifndef NOTELEFTVIEW_H
#define NOTELEFTVIEW_H

#include <QWidget>

#include "notemodel.h"

namespace Ui {
class NoteLeftView;
}

class NoteLeftView : public QWidget
{
    Q_OBJECT

public:
    explicit NoteLeftView(NoteModel* model, QWidget *parent = Q_NULLPTR);
    ~NoteLeftView();

    NoteModel* model() const { return model_; }

private slots:
    void    update();

private:
    Ui::NoteLeftView *ui;

    NoteModel* model_;
};

#endif // NOTELEFTVIEW_H
