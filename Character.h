#ifndef CHARACTER_H
#define CHARACTER_H

#include <QMap>
#include <QString>

class Character
{
public:
    Character(QString type, QString name);

    QMap<QString, QString>* getStats() const;

private:
    QString m_type;
    QString m_name;

    QMap<QString, QString> *m_statBundle;

};

#endif // CHARACTER_H
