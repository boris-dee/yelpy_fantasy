#include "Character.h"

Character::Character(QString name, QString level, QString hp, QString mp) : m_name(name), m_level(level), m_hp(hp), m_mp(mp)
{
    m_statBundle = new QVector<QString>;
    m_statBundle->push_back(m_name);
    m_statBundle->push_back(m_level);
    m_statBundle->push_back(m_hp);
    m_statBundle->push_back(m_mp);
}

QVector<QString> Character::getStats() const
{
    return *m_statBundle;
}
