#include "Character.h"

Character::Character(QString type, QString name) : m_type(type), m_name(name)
{
    m_statBundle = new QMap<QString,QString>;
    m_statBundle->insert("Type", m_type);
    m_statBundle->insert("Name", m_name);
}

QMap<QString, QString>* Character::getStats() const {return m_statBundle;}
