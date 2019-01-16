#include "Character.h"

Character::Character(QString type): m_type(type)
{
    m_statBundle = new QMap<QString,QString>;
    m_statBundle->insert("Type", m_type);
}

Character::Character(QString type, QString name, QString level, QString expPoints, QString hp, QString mp, QString hpMax, QString mpMax,
                     QString strength, QString vitality, QString magic, QString spirit,
                     QString dexterity, QString luck, QString limitBreak, QString attack, QString attackPercent,
                     QString magAttack, QString magAttackPercent, QString critHitPercent,
                     QString defense, QString defensePercent, QString magDefense, QString magDefPercent,
                     QString weapon, QString armor, QString accessory, bool poison, bool sadness, bool fury,
                     bool silence, bool darkness, bool frog) :
    m_type(type), m_name(name), m_level(level), m_expPoints(expPoints), m_hp(hp), m_mp(mp), m_hpMax(hpMax), m_mpMax(mpMax),
    m_strength(strength), m_vitality(vitality), m_magic(magic), m_spirit(spirit), m_dexterity(dexterity),
    m_luck(luck), m_limitBreak(limitBreak), m_attack(attack), m_attackPercent(attackPercent),
    m_magAttack(magAttack), m_magAttackPercent(magAttackPercent), m_critHitPercent(critHitPercent),
    m_defense(defense), m_defensePercent(defensePercent), m_magDefense(magDefense), m_magDefPercent(magDefPercent),
    m_currentWeapon(weapon), m_currentArmor(armor), m_currentAccessory(accessory), m_sleep(false), m_poison(poison),
    m_confusion(false), m_sadness(sadness), m_fury(fury), m_silence(silence), m_darkness(darkness), m_frog(frog),
    m_regen(false), m_haste(false), m_slow(false), m_stop(false), m_barrier(false), m_mBarrier(false), m_reflect(false)
{
    m_statBundle = new QMap<QString,QString>;

    // Stats from character creation
    m_statBundle->insert("Type", m_type);
    m_statBundle->insert("Name", m_name);
    m_statBundle->insert("Level", m_level);
    m_statBundle->insert("ExpPoints", m_expPoints);
    m_statBundle->insert("HP", m_hp);
    m_statBundle->insert("HPMax", m_hpMax);
    m_statBundle->insert("MP", m_mp);
    m_statBundle->insert("MPMax", m_mpMax);
    m_statBundle->insert("Strength", m_strength);
    m_statBundle->insert("Vitality", m_vitality);
    m_statBundle->insert("Magic", m_magic);
    m_statBundle->insert("Spirit", m_spirit);
    m_statBundle->insert("Dexterity", m_dexterity);
    m_statBundle->insert("Luck", m_luck);
    m_statBundle->insert("LimitBreak", m_limitBreak);
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
    m_statBundle->insert("Weapon", m_currentWeapon);
    m_statBundle->insert("Armor", m_currentArmor);
    m_statBundle->insert("Accessory", m_currentAccessory);

    // Ailment bundle
    m_ailmentBundle = new QMap<QString,bool>;

    m_ailmentBundle->insert("Sleep", m_sleep);
    m_ailmentBundle->insert("Poison", m_poison);
    m_ailmentBundle->insert("Confusion", m_confusion);
    m_ailmentBundle->insert("Sadness", m_sadness);
    m_ailmentBundle->insert("Fury", m_fury);
    m_ailmentBundle->insert("Silence", m_silence);
    m_ailmentBundle->insert("Darkness", m_darkness);
    m_ailmentBundle->insert("Frog", m_frog);
    m_ailmentBundle->insert("Regen", m_regen);
    m_ailmentBundle->insert("Haste", m_haste);
    m_ailmentBundle->insert("Slow", m_slow);
    m_ailmentBundle->insert("Stop", m_stop);
    m_ailmentBundle->insert("Barrier", m_barrier);
    m_ailmentBundle->insert("MBarrier", m_mBarrier);
    m_ailmentBundle->insert("Reflect", m_reflect);
}

QMap<QString, QString>* Character::getStats() const {return m_statBundle;}
QMap<QString, bool>* Character::getAilments() const {return m_ailmentBundle;}

void Character::setItems(QString weapon, QString armor, QString accessory)
{
    m_currentWeapon = weapon;
    m_currentArmor = armor;
    m_currentAccessory = accessory;

    // Update bundle
    m_statBundle->insert("Weapon", m_currentWeapon);
    m_statBundle->insert("Armor", m_currentArmor);
    m_statBundle->insert("Accessory", m_currentAccessory);
}

void Character::setStat(QString key, QString value){m_statBundle->insert(key, value);}
void Character::setAilment(QString key, bool value){m_ailmentBundle->insert(key, value);}
void Character::setLimitBreak(QString limitBreak){m_statBundle->insert("LimitBreak", limitBreak);}
