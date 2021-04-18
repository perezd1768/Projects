
class Cov:
    def __init__(self, eff, term):
        self.eff = eff
        self.term = term
    

list1 =[]
list2 =[]
currentEff = -1
currentTerm = -1
maxCoverage = 0

    
coverages = [Cov(1, 20), Cov(21, 30), Cov(15, 25), Cov(28, 40), Cov(50, 60), Cov(61, 200)]

for i in coverages:
    list1.append(i.eff)
    list2.append(i.term)

combinedCoverages = list(zip(list1, list2))

combinedCoverages.sort()
print(combinedCoverages)

for i in combinedCoverages:
    if(i[0] > currentTerm + 1):
        currentEff = i[0]
        currentTerm = i[1]
    elif(i[1] > currentTerm):
        currentTerm = i[1]
    if(currentTerm - currentEff >= maxCoverage):
        maxCoverage =  currentTerm - currentEff + 1


print("The max coverage needed is " + str(maxCoverage) + " days")