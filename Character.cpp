#include "Character.h"

Character::Character(QString type): m_type(type)
{
    m_statBundle = new QMap<QString,QString>;
    m_statBundle->insert("Type", m_type);
}

Character::Character(QString type, QString name, QString level, QString hp, QString mp,
                     QString strength, QString vitality, QString magic, QString spirit,
                     QString dexterity, QString chance, QString attack, QString attackPercent,
                     QString magAttack, QString magAttackPercent, QString critHitPercent,
                     QString defense, QString defensePercent, QString magDefense, QString magDefPercent) :
    m_type(type), m_name(name), m_level(level), m_hp(hp), m_mp(mp),
    m_strength(strength), m_vitality(vitality), m_magic(magic), m_spirit(spirit),
    m_dexterity(dexterity), m_chance(chance), m_attack(attack), m_attackPercent(attackPercent),
    m_magAttack(magAttack), m_magAttackPercent(magAttackPercent), m_critHitPercent(critHitPercent),
    m_defense(defense), m_defensePercent(defensePercent), m_magDefense(magDefense), m_magDefPercent(magDefPercent)
{
    m_statBundle = new QMap<QString,QString>;

    // Stats from character creation
    m_statBundle->insert("Type", m_type);
    m_statBundle->insert("Name", m_name);
    m_statBundle->insert("Level", m_level);
    m_statBundle->insert("HP", m_hp);
    m_statBundle->insert("HPMax", m_hp);
    m_statBundle->insert("MP", m_mp);
    m_statBundle->insert("MPMax", m_mp);
    m_statBundle->insert("Strength", m_strength);
    m_statBundle->insert("Vitality", m_vitality);
    m_statBundle->insert("Magic", m_magic);
    m_statBundle->insert("Spirit", m_spirit);
    m_statBundle->insert("Dexterity", m_dexterity);
    m_statBundle->insert("Chance", m_chance);
    m_statBundle->insert("AttackPercent", m_attackPercent);
    m_statBundle->insert("MagAttackPercent", m_magAttackPercent);
    m_statBundle->insert("CritHitPercent", m_critHitPercent);
    m_statBundle->insert("MagDefPercent", m_magDefPercent);

    // In case of character, compute some other stats
    if (type == "Character")
    {
        m_attack = m_strength;
        m_defense = m_vitality;
        m_defensePercent = QString::number(m_dexterity.toInt()/4);
        m_magAttack = m_magic;
        m_magDefense = m_spirit;
    }

    m_statBundle->insert("Attack", m_attack);
    m_statBundle->insert("Defense", m_defense);
    m_statBundle->insert("DefensePercent", m_defensePercent);
    m_statBundle->insert("MagAttack", m_magAttack);
    m_statBundle->insert("MagDefense", m_magDefense);
}

QMap<QString, QString>* Character::getStats() const {return m_statBundle;}
