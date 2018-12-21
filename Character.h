#ifndef CHARACTER_H
#define CHARACTER_H

#include <QString>
#include <QVector>

class Character
{
public:
    Character(QString name, QString level, QString hp, QString mp);

private:
    QString m_name, m_level, m_hp, m_mp;
};

#endif // CHARACTER_H
