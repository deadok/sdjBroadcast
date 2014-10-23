#include <dialog.h>
#include <ui_dialog.h>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setSettings(QMap<QString, QString> *mainSettings)
{
    settings = mainSettings;
    ui->castUrl->setText(settings->value("castUrl"));
    ui->description->setText(settings->value("description"));
    ui->genre->setText(settings->value("genre"));
    ui->shoutUrl->setText(settings->value("shoutUrl"));
    ui->title->setText(settings->value("title"));
    int index = ui->bitrate->findData(settings->value("bitrate"));
    if ( index != -1 ) {
       ui->bitrate->setCurrentIndex(index);
    }
}


void Dialog::on_Dialog_finished(int result)
{
    if (result) {
        settings->insert("castUrl", ui->castUrl->text());
        settings->insert("description", ui->description->text());
        settings->insert("genre", ui->genre->text());
        settings->insert("shoutUrl", ui->shoutUrl->text());
        settings->insert("title",  ui->title->text());
        settings->insert("bitrate",  ui->bitrate->currentText());

    }
}
