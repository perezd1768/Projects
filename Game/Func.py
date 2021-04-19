from time import sleep as sleep
from sys import exit as exit
from random import randint as rand
from random import choice as choice

wildCard = ""

#creating a standard player class
class Player:

    def __init__(self, name, clss, phealth, patk, pdeff, inv = [], invsize = 20, plvl = 1):
        self.name = name
        self.clss = clss
        self.plvl = plvl
        self.phealth = phealth
        self.patk = patk
        self.pdeff = pdeff
        self.inv = inv
        self.invsize = invsize

    def attack(self):
        return self.patk
    
    def defense(self):
        return self.pdeff

    #Need to revamp how to calculate damage
    def calculateDamage(self, eatk):
        hitChance = ["Hit", "Hit", "Miss", "Miss"]
        
        if(choice(hitChance) == "Hit"):
            self.phealth -= eatk%(self.pdeff*(self.plvl))
            print("You now have " + int(self.phealth) + "points of health")
        else:
            print("You dodged")


    #adds an item to the inventory
    #needs improvement to possibly hold more than on of each item
    def addItem(self, item):
        if(len(self.inv) < self.invsize):
            self.inv.append(item)
        else:
            print("Inventory full")

    #Increases inventory size if max inventory isn't already 50
    def increaseInventory(self):
        if(self.invsize < 50):
            self.invsize += 5
        else:
            print("Cannot increase inventory size")

    #displays all character stats   
    def checkStats(self):
        print("Name: " + self.name)
        print("Class: " + self.clss)
        print("Level: " + str(self.lvl))
        print("Health: " + str(self.phealth))
        print("Attack: " + str(self.patk))
        print("Defense: " + str(self.pdeff))

    def showInventory(self):
        for item in self.inv:
            print(item)

class Fighter(Player):
    pass

class Rogue(Player):
    pass

class Mage(Player):
    pass

class Joker(Player):
    pass

#create the class from which most enemy types 
#will inherit from
class Enemy:

    def __init__(self, name, lvl, health, atk, deff, einv = []):
        self.name = name
        self.lvl = lvl
        self.health = health
        self.atk = atk
        self.deff = deff
        self.einv = einv

    def reveal(self):
        print("A " + str(self.lvl) + " " + str(self.name) + " appears!")
        
    def attack(self):
        return atk 

    def defense(self, incoming):
        print(str(self.health) + " points remaining")
    
    def revealStats(self):
        print(str(self.health) + " " + str(self.atk) + " " + str(self.deff))

    def drops(self, pinv):
        pinv.append(choice(einv))

    def eCalculateDamage(self, eatk):
        eHitChance = ["Hit", "Hit", "Miss", "Miss"]
        
        if(choice(eHitChance) == "Hit"):
            self.health -= eatk%(self.deff*(self.lvl))
            print("The enemy now has " + int(self.health) + "points of health")
        else:
            print("They dodged")

#inherits Enemy class
#might be smart to create a table in  
#sql later down the line for 
#more enemy types

class Goblin(Enemy):
    pass
        
def prologue():
    name = ""
    clss = ""
    classlist = ["FIGHTER", "ROUGUE", "MAGE"]

    print("""
    Good morning.
    Let's start off with the basics.
    """)
    
    while True:
        name = input("What's your name?")

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
                player = Joker(name, "Joker", 50, 3, 3, [wildCard])
                print("""
                Good luck out there...
                Or not, I don't care at this point. 
                """)

        elif clss.upper() == "FIGHTER":
            player = Fighter(name, clss.title(), 200, 8, 3)
        elif clss.upper() == "ROGUE":
            player = Rogue(name, clss.title(), 150, 5, 5)
        elif clss.upper() == "MAGE":
            player = Mage(name, clss.title(), 100, 6, 2)

        print("Hello " + name + ". Let's begin.")
        break
    
    act1()


def act1():
    ans = ''

    print("""
    You wake up in a forest.
    You see a goblin lying in wait.
    Will you run or fight?
    """)

    while True:
        ans = input("Run or Fight: ")

        if(ans.upper() == "FIGHT"):
            print("Good Choice")
            sleep(5)
            battle()
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

    print("So you killed it...congrats")

        

def ending():
    exit("Well...that's all we got for now")

def battle():
    option = ""

    gobbers = Goblin("Gobbers", 27, 3500, 69, 420)
    gobbers.reveal()
    gobbers.revealStats()

    print("It's time to due...fight, I meant to say fight")
    sleep(3)

    #need to finish later
    while (player.phealth != 0) and (gobbers.health != 0):
        option = input("Make your move: ")

        if(option.upper() == "ATTACK"):
            gobbers.calculateDamage(player.attack())
        elif
