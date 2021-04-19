
class Cov:
    def __init__(self, eff, term):
        self.eff = eff
        self.term = term
    
list1 =[]
list2 =[]

currentEff = -1
currentTerm = 0
maxCoverage = 0

    
coverages = [Cov(1, 20), Cov(21, 30), Cov(15, 25), Cov(28, 40), Cov(50, 60), Cov(61, 200)]

#added effective start dates to list1, end/term dates to list2
for i in coverages:
    list1.append(i.eff)
    list2.append(i.term)

#used zip() to combine into multidimensional list to iterate through
combinedCoverages = list(zip(list1, list2))

#sort the list based off the first value/eff of each list in the larger multidimensional list
combinedCoverages.sort()

for i in combinedCoverages:
    #first account for gaps in coverage
    #i[0] = eff, i[1] = term
    if(i[0] > currentTerm + 1):
        currentEff = i[0]
        currentTerm = i[1]
    #if first check doesn't pass, check for overlap
    elif(i[1] > currentTerm):
        currentTerm = i[1]
    #if current coverage is larger than recorded coverage, replace recorded coverage
    if(currentTerm - currentEff >= maxCoverage):
        maxCoverage =  currentTerm - currentEff + 1


print("The max coverage needed is " + str(maxCoverage) + " days")