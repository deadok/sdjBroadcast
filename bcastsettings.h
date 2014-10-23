#ifndef BCASTSETTINGS_H
#define BCASTSETTINGS_H

#include <QString>

struct BSettings {
    QString castUrl, title, description, shoutUrl, genre;
    int bitrate;
};

class BcastSettings
{
public:
    BcastSettings();
};

#endif // BCASTSETTINGS_H
