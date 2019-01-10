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
             QString attack, QString attackPercent, QString magAttack, QString magAttackPercent, QString critHitPercent,
             QString defense, QString defensePercent, QString magDefense, QString magDefPercent,
             QString weapon, QString armor, QString accessory);

    QMap<QString, QString>* getStats() const;
    void setItems(QString weapon, QString armor, QString accessory);

private:

    QString m_type, m_name, m_level, m_hp, m_mp, m_strength;
    QString m_vitality, m_magic, m_spirit, m_dexterity, m_chance;
    QString m_attack, m_attackPercent, m_magAttack, m_magAttackPercent, m_critHitPercent;
    QString m_defense, m_defensePercent, m_magDefense, m_magDefPercent;
    QString m_precision, m_currentWeapon, m_currentArmor, m_currentAccessory;

    QMap<QString, QString> *m_statBundle;
};

#endif // CHARACTER_H
