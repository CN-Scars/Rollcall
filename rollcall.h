#ifndef ROLLCALL_H
#define ROLLCALL_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Rollcall; }
QT_END_NAMESPACE

class Rollcall : public QWidget
{
    Q_OBJECT

public:
    Rollcall(QWidget *parent = nullptr);
    ~Rollcall();

private slots:

    void on_checkprecautions_clicked();

    void on_inputBt_clicked();

    void on_displayBt_clicked();

    void on_refreshBt_clicked();

    void on_customBt_clicked();

private:
    Ui::Rollcall *ui;
};
#endif // ROLLCALL_H
