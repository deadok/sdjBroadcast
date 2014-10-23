#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDir>
#include <QProcess>
#include <QStandardPaths>
#include <QDateTime>
#include <QObject>
#include <QString>
#include <bcastsettings.h>
#include <QSettings>
#include <dialog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void saveSettings();

private slots:
    void on_StartButton_clicked();

    void on_stopButton_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_clicked();



protected:
    void timerEvent(QTimerEvent *);
    void findNewestFile(const QString searchPath);
    void tryToBroadcast(QString path);
    QSettings getSettingsStorage();
    void initSettings();
    QMap<QString, QString> loadSettings();
    QString getIniPath();
    QString searchPath;
    QProcess vlc;
    bool continuousSearching;
    int timerId;
    Dialog *settingsWindow;
    QMap<QString, QString> settings;
    QSettings *settingsStorage;

private:
    Ui::MainWindow *ui;
    static const QString VLC_PATH;
};


#endif // MAINWINDOW_H
