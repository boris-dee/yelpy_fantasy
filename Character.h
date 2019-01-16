#ifndef CHARACTER_H
#define CHARACTER_H

#include <QMap>
#include <QString>

class Character
{
public:
   Character(QString type);
   Character(QString type, QString name, QString level, QString hp, QString mp, QString hpMax, QString mpMax, QString strength,
             QString vitality, QString magic, QString spirit, QString dexterity, QString luck, QString limitBreak,
             QString attack, QString attackPercent, QString magAttack, QString magAttackPercent, QString critHitPercent,
             QString defense, QString defensePercent, QString magDefense, QString magDefPercent,
             QString weapon, QString armor, QString accessory, bool poison, bool sadness, bool fury,
             bool silence, bool darkness, bool frog);

    QMap<QString, QString>* getStats() const;
    QMap<QString, bool>* getAilments() const;
    void setItems(QString weapon, QString armor, QString accessory);
    void setStat(QString key, QString value);
    void setAilment(QString key, bool value);
    void setLimitBreak(QString limitBreak);

private:

    QString m_type, m_name, m_level, m_hp, m_mp, m_hpMax, m_mpMax, m_strength;
    QString m_vitality, m_magic, m_spirit, m_dexterity, m_luck, m_limitBreak;
    QString m_attack, m_attackPercent, m_magAttack, m_magAttackPercent, m_critHitPercent;
    QString m_defense, m_defensePercent, m_magDefense, m_magDefPercent;
    QString m_precision, m_currentWeapon, m_currentArmor, m_currentAccessory;

    bool m_sleep, m_poison, m_confusion, m_sadness, m_fury, m_silence;
    bool m_darkness, m_frog, m_regen, m_haste, m_slow, m_stop;
    bool m_barrier, m_mBarrier, m_reflect;

    QMap<QString, QString> *m_statBundle;
    QMap<QString, bool> *m_ailmentBundle;
};

#endif // CHARACTER_H
