#ifndef CHARACTER_H
#define CHARACTER_H

#include <QString>

class Character
{
public:
    Character(QString name, int level, int hp, int mp);

private:
    QString m_name;
    int m_level, m_hp, m_mp;

friend class AddCharDialog;
};

#endif // CHARACTER_H
