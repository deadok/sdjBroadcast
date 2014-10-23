#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    continuousSearching = false;
    QCoreApplication::setOrganizationName("deadokster");
    QCoreApplication::setOrganizationDomain("deadokster.com");
    QCoreApplication::setApplicationName("sdjBroadcast");
    settingsWindow = new Dialog(this);
    settingsStorage = new QSettings(this);
    initSettings();
    QObject::connect(settingsWindow, SIGNAL(accepted()), this, SLOT(saveSettings()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

const QString MainWindow::VLC_PATH = QString("/VLC/vlc.exe");

void MainWindow::initSettings()
{
    settings = loadSettings();
}

QMap<QString, QString> MainWindow::loadSettings() {
    QMap<QString, QString> settings;
    settings["castUrl"] = "http://yourpassword:yourlogin@example.com/stream.mp3";
    settings["title"] = "Famous station";
    settings["description"] = "Most_known_online_radio";
    settings["genre"] = "ElectroHardNoiseDubBass";
    settings["shoutUrl"] = "http://example.com";
    settings["bitrate"] = "256";
    settingsStorage->beginGroup("stations");
    settingsStorage->beginGroup("defaultStation");
    QMapIterator<QString, QString> i(settings);
    while (i.hasNext()) {
        i.next();
        settings.insert(i.key(), settingsStorage->value(i.key(), i.value()).toString());
    }
    settingsStorage->endGroup();
    settingsStorage->endGroup();

    return settings;
}

void MainWindow::on_StartButton_clicked()
{
    searchPath = QStandardPaths::standardLocations(QStandardPaths::MusicLocation).first();

    continuousSearching = ui->waitCheckBox->isChecked();
    if (continuousSearching) {
        timerId = startTimer(200);
    } else {
        findNewestFile(searchPath);
    }
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timerId) {
        findNewestFile(searchPath);
    }

}

void MainWindow::tryToBroadcast(QString path)
{
    if (continuousSearching) {
        killTimer(timerId);
    }
    QString executableCommand = QCoreApplication::applicationDirPath() + VLC_PATH;
    QStringList params = QStringList()
            << QDir::toNativeSeparators(path)
            << (
                   QString("--sout=#transcode{acodec=mp3,ab=%1,channels=2,samplerate=44100}:").arg(settings.value("bitrate")) +
                   QString("duplicate{dst=gather:std{access=shout,mux=mpeg1,dst=%2},select=novideo,dst=display}").arg(settings.value("castUrl"))
                )
            << QString("--sout-shout-mp3")
            << QString("--sout-keep")
            << QString("--no-sout-rtp-sap")
            << QString("--no-sout-standard-sap")
            << QString("--sout-shout-name=%1").arg(settings.value("title"))
            << QString("--sout-shout-genre=%1").arg(settings.value("genre"))
            << QString("--volume=0")
            << QString("--file-logging")
            << QString("--logfile=e:\\2.txt")
            << QString("--extraintf=logger")
    ;


    vlc.start(executableCommand, params);
}

void MainWindow::findNewestFile(const QString searchPath)
{
    QDir searchDir = QDir(searchPath + "/_Serato_/Recording temp");
    searchDir.setFilter(QDir::Files | QDir::NoSymLinks);
    searchDir.setSorting(QDir::Time);
    ui->plainTextEdit->appendHtml("<p>Looking for the file</p>");
    QFileInfoList fileList;
    QString path = "";
    fileList = searchDir.entryInfoList();
    if (!fileList.empty()) {
        QFileInfo newestFile = fileList.first();
        path = newestFile.absoluteFilePath();
        if (continuousSearching) {
            QDateTime minChangedTime = QDateTime::currentDateTime();
            minChangedTime = minChangedTime.addSecs(-2);
            QDateTime fileChangedTime = newestFile.lastModified();
            if (fileChangedTime < minChangedTime) {
                path = "";
            }
        }
    }

    if (path !="") {
        tryToBroadcast(path);
    }
}


void MainWindow::on_stopButton_clicked()
{
    if(continuousSearching) {
        killTimer(timerId);
    }
    ui->plainTextEdit->appendHtml("<p>Stopped file lookup.</p>");
}

void MainWindow::on_toolButton_2_clicked()
{    
    settingsWindow->setSettings(&settings);
    settingsWindow->show();

}

void MainWindow::saveSettings()
{
        settingsStorage->beginGroup("defaultStation");
        QMapIterator<QString, QString> i(settings);
        while (i.hasNext()) {
            i.next();
            settingsStorage->setValue(i.key(), i.value());
        }
        settingsStorage->endGroup();
}

void MainWindow::on_toolButton_clicked()
{
    QRect windowGeometry = this->geometry();
    QRect editGeometry = ui->plainTextEdit->geometry();
    int sign;
    if (ui->toolButton->text() == "▲") {
        sign = -1;
        ui->toolButton->setText("▼");
        ui->plainTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    } else {
        sign = 1;
        ui->toolButton->setText("▲");
        ui->plainTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    }
    windowGeometry.setHeight(windowGeometry.height() + sign*390);
    editGeometry.setHeight(editGeometry.height() + sign*390);
    this->setGeometry(windowGeometry);
    ui->plainTextEdit->setGeometry(editGeometry);

}
