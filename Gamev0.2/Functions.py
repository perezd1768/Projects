from time import sleep as sleep
from sys import exit as exit
from random import randint as rand
from random import choice as choice

WildCard = None

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
            print("You now have " + str(self.phealth) + "points of health")
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
        print("Level: " + str(self.plvl))
        print("Health: " + str(self.phealth))
        print("Attack: " + str(self.patk))
        print("Defense: " + str(self.pdeff))

    def showInventory(self):
        for item in self.inv:
            print(item)

class Fighter(Player):
    def __init__(self, name, clss, phealth = 200, patk = 8, pdeff = 3, inv = [], invsize = 20, plvl = 1):
        self.name = name
        self.clss = clss
        self.plvl = plvl
        self.phealth = phealth
        self.patk = patk
        self.pdeff = pdeff
        self.inv = inv
        self.invsize = invsize

class Rogue(Player):
    def __init__(self, name, clss, phealth = 150, patk = 5, pdeff = 5, inv = [], invsize = 20, plvl = 1):
        self.name = name
        self.clss = clss
        self.plvl = plvl
        self.phealth = phealth
        self.patk = patk
        self.pdeff = pdeff
        self.inv = inv
        self.invsize = invsize

class Mage(Player):
    def __init__(self, name, clss, phealth = 100, patk = 6, pdeff = 2, inv = [], invsize = 20, plvl = 1):
        self.name = name
        self.clss = clss
        self.plvl = plvl
        self.phealth = phealth
        self.patk = patk
        self.pdeff = pdeff
        self.inv = inv
        self.invsize = invsize

class Joker(Player):
    def __init__(self, name, clss, phealth = 50, patk = 3, pdeff = 3, inv = [WildCard], invsize = 20, plvl = 1):
        self.name = name
        self.clss = clss
        self.plvl = plvl
        self.phealth = phealth
        self.patk = patk
        self.pdeff = pdeff
        self.inv = inv
        self.invsize = invsize

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
        return self.atk 

    def defense(self, incoming):
        print(str(self.health) + " points remaining")
    
    def revealStats(self):
        print(str(self.health) + " " + str(self.atk) + " " + str(self.deff))

    def drops(self, pinv):
        pinv.append(choice(self.einv))

    def eCalculateDamage(self, eatk):
        eHitChance = ["Hit", "Hit", "Miss", "Miss"]
        
        if(choice(eHitChance) == "Hit"):
            self.health -= eatk%(self.deff*(self.lvl))
            print("The enemy now has " + str(self.health) + "points of health")
        else:
            print("They dodged")

#inherits Enemy class
#might be smart to create a table in  
#sql later down the line for 
#more enemy types

class Goblin(Enemy):
    pass
         

def ending():
    exit("Well...that's all we got for now")


def readText(text_file):
    with open(text_file) as file:
        for line in file:
            print(line)
            sleep(2)


