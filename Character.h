#ifndef CHARACTER_H
#define CHARACTER_H

#include <QString>

class Character
{
public:
    Character();
    Character(QString name);

private:
    QString m_name;
};

#endif // CHARACTER_H
