#include "Player.cpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

vector<int> cards;
int curCard = 0;

int getCard(){
    int card = cards[curCard];
    curCard++;
    return card;
}


int getCardValue(int cardIndex){
    int faceValue = cardIndex/4;

    //invert 
    faceValue = 13 - faceValue;

    //account for face cards
    if(faceValue > 10){
        faceValue = 10;
    }

    return faceValue;
}

int getHandValue(vector<int> hand){
    int handValue = 0;
    int numAces = 0;

    for(int i = 0; i < hand.size(); i++){
        handValue += getCardValue(hand[i]);
        if(getCardValue(hand[i]) == 1){
            numAces++;
        }
    }

    //account for aces
    if(numAces > 0 && handValue + 10 <= 21){
        handValue += 10;
    }

    return handValue;
}

int getMinimalHandValue(vector<int> hand){
    int handValue = 0;

    for(int i = 0; i < hand.size(); i++){
        handValue += getCardValue(hand[i]);
    }
    return handValue;
}

string determineWinner(vector<int> playerHand, vector<int> dealerHand){
    //player bust
    if(getHandValue(playerHand) > 21){
        return "LOSE";
    }

    //dealer bust
    if(getHandValue(dealerHand) > 21){
        return "WIN";
    }

    //compare results
    if(getHandValue(playerHand) > getHandValue(dealerHand)){
        return "WIN";
    }
    else if(getHandValue(playerHand) < getHandValue(dealerHand)){
        return "LOSE";
    }
    else{
        return "TIE";
    }
}

void playDealer(vector<int> &dealerHand){
    while(getHandValue(dealerHand) < 17){
        dealerHand.push_back(getCard());
    }
}



string playHand(Player player){
    string result = "UNKNOWN";

    vector<int> curPlayerHand;
    vector<int> curDealerHand;

    //deal player hand
    curPlayerHand.push_back(getCard());
    curPlayerHand.push_back(getCard());
    //deal dealer hand
    curDealerHand.push_back(getCard());
    curDealerHand.push_back(getCard());

    //players turn
    player.startHand(curPlayerHand[0], curPlayerHand[1], curDealerHand[0]);
    while(getMinimalHandValue(curPlayerHand) < 21){
        if(player.shouldHit()){
            curPlayerHand.push_back(getCard());
            player.hit(curPlayerHand[curPlayerHand.size() - 1]);
        }
        else{
            break;
        }
    }

    //dealer turn
    if(getMinimalHandValue(curPlayerHand) <= 21){
        playDealer(curDealerHand);
    }

    //determine winner
    result = determineWinner(curPlayerHand, curDealerHand);
    player.endHand(curDealerHand,result);
    return result;
}


int main(int argc, char **argv){
    //read in number of cards


    int numHands = atoi(argv[1]);
    //read in number of hands
    int numCards = atoi(argv[2]);
    //read in name of file
    string filename(argv[3]);

    if(numHands * 20 > numCards){
        cout << "Too many hands, " << (20 *numHands) << " cards required, only " << numCards << " cards available" << endl;
        return 0;
    }

    //read file into array
    int number;

    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        return EXIT_FAILURE;
    }

    while (input_file >> number) {
        cards.push_back(number);
    }

    //counter to keep track of cards
    curCard = 0;

    Player player = Player();
    int netWins = 0;

    //actually play the game
    for(int i = 0; i < numHands; i++){
        string result = playHand(player);
        if(result == "WIN"){
            netWins++;
        }
        else if(result == "LOSE"){
            netWins--;
        }
    }

    printf("Net wins: %d\n", netWins);
    printf("Net win percentage: %f %% \n", 100*(float)netWins / numHands);
    return 0;
}