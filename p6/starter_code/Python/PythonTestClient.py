import sys
from Player import Player



#Read in predecided card draws

numHands = int(sys.argv[1])
numCards = int(sys.argv[2])

if(numHands*20 > numCards):
    print("Too many hands," + str(20*numHands) + " cards required. Only " + str(numCards) + " cards available.")
    sys.exit()

fileName = sys.argv[3]

#read file into an array
with open(fileName) as f:
    content = f.readlines()


#convert cards into ints into ints
cards = [int(x.strip()) for x in content]


#counter to maintain which index the next card is on
curCard = 0



#Utils


def getCardValue(cardIndex):
    faceValue = cardIndex//4
    #invert
    faceValue = 13 - faceValue
    #if face value is greater than 10, it is a face card
    if(faceValue > 10):
        faceValue = 10
    return faceValue

def getHandValue(hand):
    minValue = 0
    numAces = 0
    for card in hand:
        if(getCardValue(card) == 1):
            numAces += 1
        minValue += getCardValue(card)
    #if there are aces, check if they can be increased to 11
    if(numAces > 0):
        if(minValue + 10 <= 21):
            minValue += 10
    return minValue

def getMinimalHandValue(hand):
    minValue = 0
    for card in hand:
        minValue += getCardValue(card)
    return minValue

def determineWinner(playerHand, dealerHand):
    #Player Bust
    if(getHandValue(playerHand) > 21):
        return "LOSE"
    #Dealer Bust
    elif(getMinimalHandValue(dealerHand) > 21):
        return "WIN"
    #compare results
    elif(getHandValue(playerHand) > getHandValue(dealerHand)):
        return "WIN"
    elif(getHandValue(playerHand) == getHandValue(dealerHand)):
        return "TIE"
    else:
       return "LOSE"

def playDealer(dealerHand):
    while(getHandValue(dealerHand) < 17):
        dealerHand.append(getCard())
    return dealerHand



def getCard():
    global curCard
    global cards
    card = cards[curCard]
    curCard += 1
    return card


def playHand(player):
    result = "UNKNOWN"
    curPlayerHand = []
    curDealerHand = []

    #Deal player hand
    curPlayerHand.append(getCard())
    curPlayerHand.append(getCard())

    #Deal dealer hand
    curDealerHand.append(getCard())
    curDealerHand.append(getCard())

    #players turn
    player.startHand(curPlayerHand[0],curPlayerHand[1], curDealerHand[0])
    while(getMinimalHandValue(curPlayerHand) < 21):
        if(player.shouldHit()):
            curPlayerHand.append(getCard())
            player.hit(curPlayerHand[-1])
        else:
            break

    #dealer's turn
    if(getMinimalHandValue(curPlayerHand) <= 21):
        playDealer(curDealerHand)

    #determine winner
    result = determineWinner(curPlayerHand, curDealerHand)
    player.endHand(curDealerHand, result)
    return result

#Actually play the game
player = Player()
netWins = 0

for i in range(0, numHands):
    result = playHand(player)
    if(result == "WIN"):
        netWins += 1
    elif(result == "LOSE"):
        netWins -= 1

print("Net Wins: " + str(netWins))
print("Net Win Percentage: " + str(100*netWins/numHands) + "%")





