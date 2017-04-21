#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cs50.h>
#include <string.h>
#include "dungeon.h"

int main()
{
    //setting up character
    printf("What is your character's name?\n");
    custom.name = get_string();
    
    if (strncmp(custom.name,"tim e", 5) == 0)
    {
        printf("You have unlocked... Dev Mode!\nYou now have max stats.\n");
        custom.stat.str = 20;
        custom.stat.agi = 20;
        custom.stat.intel = 20;
        custom.stat.wis = 0;
        custom.stat.def = 20;
    }
    
    printf("How old is your character?\n");
    custom.age = get_int();
    
    printf("How tall is your character (in meters)?\n");
    custom.height = get_float();
    custom.hp = 20;
    assignStats(custom);
    
    //Adventure bit
    struct enemy slime;
    slime.name = "slime";
    slime.hp = 10;
    slime.stats = -3;
    
    encounter(slime, custom);
    
    if (custom.hp < 1)
    {
        return 0;
    }
    else
    {
        printf("You continue down the path.\n");
    }
    
    levelUp(1);
    custom.level += 1;
    
    struct enemy lizard;
    lizard.name = "stinky lizard";
    lizard.hp = 10;
    lizard.stats = 0;
    encounter(lizard,custom);
    
    if (custom.hp < 1)
    {
        return 0;
    }
    else
    {
        printf("You continue down the path.\n");
    }
    levelUp(2);
    custom.level += 1;
    
    //Sean's Enemy
    struct enemy Jason;
    Jason.name = "Ogre";
    Jason.hp = 15;
    Jason.stats = 3;
    encounter(Jason, custom);

    if (custom.hp < 1)
    {
        return 0;
    }
    else
    {
        printf("You continue down the path.\n");
    }
    
    //undefeatable boss because why not
    struct enemy stupidBoss;
    stupidBoss.name = "stupidly overpowered boss";
    stupidBoss.hp = 999;
    stupidBoss.stats = 20;
    encounter(stupidBoss, custom);
    if (custom.hp < 1)
    {
        custom.hp = 20;
        printf("You wake up in a house, feeling refreshed.\nA man tells you that he found you as he was travelling along the path.\n");
    }
    else
    {
        printf("You hacker!\n");
        return(0);
    }
    
    printf("The man tells you that you can either try and attack the boss again, or go back and gain more levels.\nWhich would you like to do?(g/r)");
    char reee = get_char();
    if (reee == 'r')
    {
        while (reee == 'r')
        {
            encounter(slime, custom);
            if (custom.hp < 1)
            {
                return 0;
            }
            encounter(lizard, custom);
            if (custom.hp < 1)
            {
                return 0;
            }
            encounter(Jason, custom);
            if (custom.hp < 1)
            {
                return 0;
            }
            levelUp(5);
        }
    }
    stupidBoss.stats = 10;
    stupidBoss.hp = 100;
    encounter(stupidBoss, custom);
    if (custom.hp < 1)
    {
        return 0;
    }
    printf("You win! Good job!");
}