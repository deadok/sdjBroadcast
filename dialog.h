#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);

    ~Dialog();

    void setSettings(QMap<QString, QString> *mainSettings);

protected:


private slots:
    void on_Dialog_finished(int result);

private:
    Ui::Dialog *ui;
    QMap<QString, QString> *settings;
};

#endif // DIALOG_H
