#ifndef CHARACTER_H
#define CHARACTER_H

#include <QString>
#include <QVector>

class Character
{
public:
    Character(QString name, QString level, QString hp, QString mp);

    QVector<QString> getStats() const;

private:
    QString m_name, m_level, m_hp, m_mp;

    QVector<QString> *m_statBundle;
};

#endif // CHARACTER_H
