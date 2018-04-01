#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QWidget>

namespace Ui {
class startPage;
}

class StartPage : public QWidget
{
    Q_OBJECT

public:
    explicit StartPage(QWidget *parent = 0);
    ~StartPage();

private:
    Ui::startPage *ui;
};

#endif // STARTPAGE_H
