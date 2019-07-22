#ifndef SMAINWINDOW_H
#define SMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class SMainWindow;
}

class SMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SMainWindow(QWidget *parent = nullptr);
    ~SMainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SMainWindow *ui;
};

#endif // SMAINWINDOW_H
