#include "Item.h"

Item::Item()
{
     m_statBundle = new QMap<QString,QString>;
}

// Weapon overload
Item::Item(QString name, QString attack, QString attackPercent, QString magic, QString critHitPercent) :
    m_name(name), m_attack(attack), m_attackPercent(attackPercent), m_magic(magic), m_critHitPercent(critHitPercent)
{
    m_statBundle = new QMap<QString,QString>;
    m_statBundle->insert("Name", m_name);
    m_statBundle->insert("Attack", m_attack);
    m_statBundle->insert("AttackPercent", m_attackPercent);
    m_statBundle->insert("Magic", m_magic);
    m_statBundle->insert("CritHitPercent", m_critHitPercent);
}

// Armor overload
Item::Item(QString name, QString magic, QString defense, QString magDefense, QString defensePercent, QString magDefPercent, QString strength) :
    m_name(name), m_magic(magic), m_defense(defense), m_magDefense(magDefense), m_defensePercent(defensePercent),
    m_magDefPercent(magDefPercent), m_strength(strength)
{
    m_statBundle = new QMap<QString,QString>;
    m_statBundle->insert("Name", m_name);
    m_statBundle->insert("Defense", m_defense);
    m_statBundle->insert("MagDefense", m_magDefense);
    m_statBundle->insert("DefensePercent", m_defensePercent);
    m_statBundle->insert("MagDefPercent", m_magDefPercent);
    m_statBundle->insert("Magic", m_magic);
    m_statBundle->insert("Strength", m_strength);
}

// Accessory overload
Item::Item(QString name, QString magic, QString strength, QString hp, QString mp, QString vitality, QString dexterity, QString chance, QString spirit) :
    m_name(name), m_magic(magic), m_strength(strength), m_hp(hp), m_mp(mp), m_vitality(vitality),
    m_dexterity(dexterity), m_chance(chance), m_spirit(spirit)
{
    m_statBundle = new QMap<QString,QString>;
    m_statBundle->insert("Name", m_name);
    m_statBundle->insert("Magic", m_magic);
    m_statBundle->insert("Strength", m_strength);
    m_statBundle->insert("HP", m_hp);
    m_statBundle->insert("MP", m_mp);
    m_statBundle->insert("Vitality", m_vitality);
    m_statBundle->insert("Dexterity", m_dexterity);
    m_statBundle->insert("Chance", m_chance);
    m_statBundle->insert("Spirit", m_spirit);
}

QMap<QString,QString>* Item::getStats() const{return m_statBundle;}
