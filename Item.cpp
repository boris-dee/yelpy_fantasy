#include "Item.h"

Item::Item()
{
     m_statBundle = new QMap<QString,QString>;
}

// Item overload
Item::Item(QString name) : m_name(name)
{
     m_statBundle = new QMap<QString,QString>;
     m_statBundle->insert("Name", m_name);
}

// Attack overload
Item::Item(QString name, QString factor) : m_name(name), m_factor(factor)
{
     m_statBundle = new QMap<QString,QString>;
     m_statBundle->insert("Name", m_name);
     m_statBundle->insert("Factor", m_factor);
}

// Magic and Summons overload
Item::Item(QString name, QString magAttackPercent, QString factor, QString mpCost) :
    m_name(name), m_magAttackPercent(magAttackPercent), m_factor(factor), m_mpCost(mpCost)
{
    m_statBundle = new QMap<QString,QString>;
    m_statBundle->insert("Name", m_name);
    m_statBundle->insert("MagAttackPercent", m_magAttackPercent);
    m_statBundle->insert("Factor", m_factor);
    m_statBundle->insert("MPCost", m_mpCost);
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
Item::Item(QString name, QString magic, QString strength, QString hpMax, QString mpMax, QString vitality, QString dexterity, QString luck, QString spirit) :
    m_name(name), m_magic(magic), m_strength(strength), m_hpMax(hpMax), m_mpMax(mpMax), m_vitality(vitality),
    m_dexterity(dexterity), m_luck(luck), m_spirit(spirit)
{
    m_statBundle = new QMap<QString,QString>;
    m_statBundle->insert("Name", m_name);
    m_statBundle->insert("Magic", m_magic);
    m_statBundle->insert("Strength", m_strength);
    m_statBundle->insert("HPMax", m_hpMax);
    m_statBundle->insert("MPMax", m_mpMax);
    m_statBundle->insert("Vitality", m_vitality);
    m_statBundle->insert("Dexterity", m_dexterity);
    m_statBundle->insert("Luck", m_luck);
    m_statBundle->insert("Spirit", m_spirit);
}

QMap<QString,QString>* Item::getStats() const{return m_statBundle;}
