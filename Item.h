#ifndef ITEM_H
#define ITEM_H


#include <QMap>
#include <QString>

class Item
{
public:
    // Blank overload
    Item();

    // Weapon overload
    Item(QString name, QString attack, QString attackPercent, QString magic, QString critHitPercent);

    // Armor overload
    Item(QString name, QString magic, QString defense, QString magDefense, QString defensePercent, QString magDefPercent, QString strength);

    // Accessory overload
    Item(QString name, QString magic, QString strength, QString hp, QString mp, QString vitality, QString dexterity, QString chance, QString spirit);

    QMap<QString, QString>* getStats() const;

private:
    QString m_name, m_attack, m_attackPercent, m_magic, m_critHitPercent;
    QString m_defense, m_magDefense, m_defensePercent, m_magDefPercent, m_strength;

    QString m_level, m_hp, m_mp, m_precision, m_vitality, m_dexterity, m_chance;
    QString m_magAttack, m_magAttackPercent, m_spirit;

    QMap<QString, QString> *m_statBundle;
};

#endif // ITEM_H
