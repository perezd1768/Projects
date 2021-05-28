from Functions import readText as text
from Functions import ending as ending
from Functions import  Goblin, Fighter, Rogue, Mage, Joker
from time import sleep as sleep
from sys import exit as exit
import os

player = None
name = ""
pclss = ""
ans = ''

def story():
    classlist = ["FIGHTER", "ROGUE", "MAGE"]


    print("""
    Good morning.
    Let's start off with the basics.
    """)
    
    while True:
        name = input("What's your name?: ")

        if len(name) > 10:
            print("That\'s not really your name, now is it?")
            name = input("Let's try that again, shall we: ")
            if len(name) > 10:
                print("I don\'t give third chances")
                ending()
            else:
                break
        else:
            break
    while True:

        clss = input("Now choose a class(Fighter, Rougue, Mage): ")

        if clss.upper() not in classlist:
            print("...really, you\'re going to act like this again?")
            clss = input("Ok, last chance: ")
            if clss.upper() not in classlist:
                print("""
                Ok...so you're going to be a special class.
                I like to call this one the Joker.
                Since you feel like being one.    
                """)
                player = Joker(name, "Joker")

                print("""
                Good luck out there...
                Or not, I don't care at this point. 
                """)
            elif clss.upper() == "FIGHTER":
                player = Fighter(name, clss.title())
            elif clss.upper() == "ROGUE":
                player = Rogue(name, clss.title())
            elif clss.upper() == "MAGE":
                player = Mage(name, clss.title())
        
        elif clss.upper() == "FIGHTER":
            player = Fighter(name, clss.title())
        elif clss.upper() == "ROGUE":
            player = Rogue(name, clss.title())
        elif clss.upper() == "MAGE":
            player = Mage(name, clss.title())
        
        print("Hello " + name + ". Let's begin.")
        break

    sleep(5)
    os.system('cls')
    sleep(2)

    #convert to text file
    print("""
    You wake up in a forest.
    You see a goblin lying in wait.
    Will you run or fight?
    """)

    while True:
        ans = input("Run or Fight: ")

        if(ans.upper() == "FIGHT"):
            print("Good Choice")
            break

        elif(ans.upper() == "RUN"):
            print("""
        Coward.
        The Goblin kills you
        The End. 
        """)
            ending()

        else:
            print('That\'s not a choice')
    
    gobbers = Goblin("Gobbers", 27, 2, 69, 420)
    gobbers.reveal()
    gobbers.revealStats()
    player.checkStats()

    print("It's time to due...fight, I meant to say fight")

    while(player.phealth != 0) and (gobbers.health != 0):
        ans = input("Make your move: ")
        if ans.upper() == 'ATTACK':
            print("You attack!")
            gobbers.eCalculateDamage(player.patk)
            if(gobbers.health <= 0):
                break
        elif ans.upper() == "DEFEND":
            print("You defend")
        print("The goblin attacks!")
        player.calculateDamage(gobbers.atk)
        if(player.phealth <= 0):
            print("You died. Pathetic.")
            ending()
    
    print("""So you killed it...congrats.
I knew you could do it...anyway moving on""")

    sleep(3)
    os.system('cls')
    sleep(3)

    text('part2.txt')

    while(True):
        ans = input("Pretty clever right?: ")
        if ans.upper() == "YES":
            break
        elif ans.upper() == "NO":
            os.system('cls')
            sleep(2)
            print("Wrong answer")
            break
        else:
            print("It's a yes or no question")
            continue
    
    text('part2b.txt')

    while(True):
        ans = input("Which way do you want to go (kingdom or volcano)?: ")
        if ans.upper() == "KINGDOM":
            print("Yeah...about that, that doesn't really line up with the story.")
            continue
        elif ans.upper() == "VOLCANO":
            print("That's the spirit!")
            break
        else:
            print("You know, I'm worried about you")
            continue

    ending()
