package blackjack;

import java.util.ArrayList;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class JavaTestClient{

    //globals
    private static ArrayList<Integer> cards = new ArrayList<Integer>();
    private static int curCard = 0;

    //utils

    public static int getCardValue(int cardIndex){
        int faceValue = cardIndex/4;
        //invert
        faceValue = 13 - faceValue;

        //acount for face cards
        if(faceValue > 10){
            faceValue = 10;
        }
        return faceValue;
    }

    public static int getHandValue(ArrayList<Integer> hand){
        int minValue = 0;
        int numAces = 0;
        for(int i = 0; i < hand.size(); i++){
            minValue += getCardValue(hand.get(i));
            if(getCardValue(hand.get(i)) == 1){
                numAces++;
            }
        }

        //account for aces
        if(minValue + 10 <= 21 && numAces > 0){
            minValue += 10;
        }

        return minValue;
    }

    public static int getMinimalHandValue(ArrayList<Integer> hand){
        int minValue = 0;
        for(int i = 0; i < hand.size(); i++){
            minValue += getCardValue(hand.get(i));
        }
        return minValue;
    }

    public static String determineWinner(ArrayList<Integer> playerHand, ArrayList<Integer> dealerHand){
        //player bust
        if(getHandValue(playerHand) > 21){
            return "LOSE";
        }
        // dealer bust
        else if(getHandValue(dealerHand) > 21){
            return "WIN";
        }
        //compare results
        else if(getHandValue(playerHand) > getHandValue(dealerHand)){
            return "WIN";
        }
        else if(getHandValue(playerHand) < getHandValue(dealerHand)){
            return "LOSE";
        }
        else{
            return "TIE";
        }
    }

    public static void playDealer(ArrayList<Integer> dealerHand){
        while(getHandValue(dealerHand) < 17){
            dealerHand.add(getCard());
        }
    }

    public static int getCard(){
        int card = cards.get(curCard);
        curCard = curCard + 1;
        return card;

    }

    public static String playHand(Player player){
        String result = "UNKNOWN";

        ArrayList<Integer> curPlayerHand = new ArrayList<Integer>();
        ArrayList<Integer> curDealerHand = new ArrayList<Integer>();

        //deal player hand
        curPlayerHand.add(getCard());
        curPlayerHand.add(getCard());
        //deal dealer hand
        curDealerHand.add(getCard());
        curDealerHand.add(getCard());

        //players turn
        player.startHand(curPlayerHand.get(0), curPlayerHand.get(1),curDealerHand.get(0));
        while(getMinimalHandValue(curPlayerHand) < 21){
            if(player.shouldHit()){
                curPlayerHand.add(getCard());
                player.hit(curPlayerHand.get(curPlayerHand.size()-1));
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
        player.endHand(curDealerHand, result);
        return result;
    }




    public static void main(String[] args) throws IOException{
        // read in number of cards
        int numHands = Integer.parseInt(args[0]);
        // read in number of hands
        int numCards = Integer.parseInt(args[1]);
        // read in name of file
        String fileName = args[2];

        if(numHands*20 > numCards){
            System.out.println("Too many hands, " +  (numHands*20) + " cards required. Only " + (numCards) + " cards available.");
            System.exit(0);
        }

        // read file into array
        BufferedReader bufReader = new BufferedReader(new FileReader(fileName));
        cards = new ArrayList<Integer>();

        String line = bufReader.readLine();
        while(line != null){
            cards.add(Integer.parseInt(line));
            line = bufReader.readLine();
        }

        // counter to keep track of cards
        curCard = 0;


        Player player = new Player();
        int netWins = 0;

        //actually play the game
        for(int i = 0; i < numHands; i++){
            String result = playHand(player);
            if(result == "WIN"){
                netWins++;
            }
            else if(result == "LOSE"){
                netWins--;
            }
        }

        System.out.println("Net wins: " + (netWins));
        System.out.println("Net win percentage: " + (100*(double)netWins/numHands) + "%");
    }

}