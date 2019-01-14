#ifndef ITEM_H
#define ITEM_H


#include <QMap>
#include <QString>

class Item
{
public:
    // Blank overload
    Item();

    // Item overload
    Item(QString name);

    // Attack overload
    Item(QString name, QString factor);

    // Magic and Summons overload
    Item(QString name, QString magAttackPercent, QString factor, QString mpCost);

    // Weapon overload
    Item(QString name, QString attack, QString attackPercent, QString magic, QString critHitPercent);

    // Armor overload
    Item(QString name, QString magic, QString defense, QString magDefense, QString defensePercent, QString magDefPercent, QString strength);

    // Accessory overload
    Item(QString name, QString magic, QString strength, QString hp, QString mp, QString vitality, QString dexterity, QString luck, QString spirit);

    QMap<QString, QString>* getStats() const;

private:
    QString m_name, m_attack, m_attackPercent, m_magic, m_critHitPercent;
    QString m_defense, m_magDefense, m_defensePercent, m_magDefPercent, m_strength;

    QString m_level, m_hpMax, m_mpMax, m_precision, m_vitality, m_dexterity, m_luck;
    QString m_magAttack, m_magAttackPercent, m_spirit, m_factor, m_mpCost;

    QMap<QString, QString> *m_statBundle;
};

#endif // ITEM_H
