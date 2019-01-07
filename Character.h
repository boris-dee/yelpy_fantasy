#ifndef CHARACTER_H
#define CHARACTER_H

#include <QMap>
#include <QString>

class Character
{
public:
   Character(QString type);
   Character(QString type, QString name, QString level, QString hp, QString mp, QString strength,
             QString vitality, QString magic, QString spirit, QString dexterity, QString chance,
             QString attack);

    QMap<QString, QString>* getStats() const;

private:

    // Stats used for character's creation
    QString m_type, m_name, m_level, m_hp, m_mp, m_strength;
    QString m_vitality, m_magic, m_spirit, m_dexterity, m_chance;

    // Stats computed afterwards
    QString m_attack, m_attackPercent, m_defense, m_defensePercent;
    QString m_magAttack, m_magAttPercent, m_magDefense, m_magDefPercent;
    QString m_precision, m_critHitPercent;

    QMap<QString, QString> *m_statBundle;
};

#endif // CHARACTER_H
