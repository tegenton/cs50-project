#ifndef functions
#define functions

int damage;

//character stats + info
struct character
{
    string name;
    int age;
    float height;
    int hp;
    int level;
    struct attributes
    {
        int str;
        int agi;
        int intel;
        int wis;
        int def;
    } stat;
} custom;

//enemy stat storage
struct enemy
{
    string name;
    int stats;
    int hp;
};

int crit = 0;

int diceRoll(int die)
{
    srand(time(NULL));
    return (rand() % die) + 1;
};

void levelUp(level)
{
    for (int i = 0; i < level; i += 2)
    {
        printf("You leveled up!\nWhat stat would you like to increase? (str, agi, int, wis, or def) You have %i point left\n", level - i);
        string statToIncrease = get_string();
        if (strncmp(statToIncrease, "str", 3) == 0 && custom.stat.str < 20)
        {
            custom.stat.str += 1;
            printf("Strength increased!\n");
        }
        else if (strncmp(statToIncrease, "agi", 3) == 0 && custom.stat.agi < 20)
        {
            custom.stat.agi += 1;
            printf("Agility increased!\n");
        }
        else if (strncmp(statToIncrease, "int", 3) == 0 && custom.stat.intel < 20)
        {
            custom.stat.intel += 1;
            printf("Intelligence increased!\n");
        }
        else if (strncmp(statToIncrease, "wis", 3) == 0 && custom.stat.wis < 20)
        {
            custom.stat.wis += 1;
            printf("Wisdom increased!\n");
        }
        else if (strncmp(statToIncrease, "def", 3) == 0 && custom.stat.def < 20)
        {
            custom.stat.def += 1;
            printf("Defense increased!\n");
        }
        else
        {
            printf("Invalid input, retry\n");
        }
    }
};

int attack(int monsterHealth, int monsterStat, int strength, int def, int spd, int d20)
{
    damage = (d20 / 2) + (strength-10)/2;
    printf("You roll a %i, dealing %i damage\n", d20, damage);
    if (monsterStat > spd)
    {
        printf("You missed! The monster was able to dodge, and attacks back!\n");
    
        if (monsterStat <= strength)
        {
            printf("You are able to block its attack\n"); 
        }
        else if (monsterStat <= def)
        {
            printf("The attack does no damage\n");
        }
        else
        {
            printf("You take %i damage!\n", monsterStat - def);
            custom.hp -= monsterStat - def;
        }
    }
    else if (strength < monsterStat)
    {
        printf("You attack, but the monster is too strong for you! Retreat?\n");
        string retreat = get_string();
        
        if (strncmp (retreat,"y",1) == 0 ||strncmp (retreat,"Y",1) == 0)
        {
            printf("You run away, but the monster chases you!\n");
        }
        else
        {
            crit = 1;
        }
    }

    //your attack
    if (damage - monsterStat >= monsterHealth)
    {
        printf("You kill the monster\n");
        return(monsterHealth);
    }
    else
    {
        if (damage > 10 && crit == 1)
        {
            printf("Critical hit! The monster takes %i damage.\n", damage*2);
            return(damage * 2);
        }
        else if (monsterStat - def > custom.hp)
        {
            printf("The attack does nothing. The monster kills you.\n");
            custom.hp = 0;
        }
        else
        {
            printf("The monster takes %i damage\n", damage - monsterStat);
            return(damage - monsterStat);
        }
    }
    return(0);
}

//Sort of attack script
int counterAttack(struct enemy attacker, struct character defense)
{
    if ( defense.stat.agi > attacker.stats)
    {
        printf("The monster missed! You dodge.\n");
        return(0);
    }
    else if (defense.stat.str > attacker.stats)
    {
        printf("The %s attacks, but you are too strong for it!\n", attacker.name);
        return(0);
    }

    //actual attacks
    if (attacker.stats - defense.stat.def >= defense.hp)
    {
        printf("The %s kills you\n", attacker.name);
        return(defense.hp);
    }
    else
    {
        printf("You take %i damage\n", damage - attacker.stats);
        return(damage - attacker.stats);
    }
    return(0);
}

//main encounter script
void encounter(struct enemy current, struct character encountee)
{
    printf("You are approached by a %s!\n", current.name);
    while (current.hp > 0 && custom.hp > 0)
    {
        printf("Press Enter Key to Continue\n");  
        getchar();
        current.hp -= attack(current.hp, current.stats, encountee.stat.str, encountee.stat.def, encountee.stat.agi, diceRoll(20));
        if (current.hp > 0)
        {
            encountee.hp -= counterAttack(current, encountee);
        }
    }
    if (custom.hp < 1)
    {
        printf("You died. Game over\n");
    }
    else
    {
        printf("Congratulations! You killed the %s!\n", current.name);
    }
};

void assignStats(struct character changing)
{
    while ((changing.stat.str + changing.stat.agi + changing.stat.intel + changing.stat.wis + changing.stat.def > 50 || changing.stat.str + changing.stat.agi + changing.stat.intel + changing.stat.wis + changing.stat.def <= 1) && strncmp(changing.name,"tim e", 5) != 0)
    {
        changing.stat.str = 0, changing.stat.agi = 0, changing.stat.intel = 0, changing.stat.wis = 0, changing.stat.def = 0;
        while (changing.stat.str > 20 || changing.stat.str <= 0)
        {
            printf("What is your character's strength stat (must be between 1 and 20)?\n");
            changing.stat.str = get_int();
        }
        while (changing.stat.agi > 20 || changing.stat.agi <= 0)
        {
            printf("What is your agility stat (must be between 1 and 20)?\n");
            changing.stat.agi = get_int();
        }
        while (changing.stat.intel > 20 || changing.stat.intel <= 0)
        {
            printf("What is your intelligence stat (must be between 1 and 20)?\n");
            changing.stat.intel = get_int();
        }
        while (changing.stat.wis > 20 || changing.stat.wis <= 0)
        {
            printf("What is your wisdom stat (must be between 1 and 20)?\n");
            changing.stat.wis = get_int();
        }
        while (changing.stat.def > 20 || changing.stat.def <= 0)
        {
            printf("You have %i stat points remaining, but your defence cannot be more than 20 or less than 1\n", 50 - (changing.stat.str + changing.stat.agi + changing.stat.intel + changing.stat.wis));
            changing.stat.def = get_int();
        }
    }
}
#endif