/* 
 * This is a reference solution submitted by Qinshi Wang (grad), Shunyu Yao (grad), 
 * and Kaifeng Lyu (grad). It implemented all the steps we were expecting and in the 
 * end, had a net win rate of 55 percent!
 */

#include <vector>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

namespace PlayerSpace {

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



string playHand(int hits){
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
    while(getMinimalHandValue(curPlayerHand) < 21){
        if(hits > 0){
            hits--;
            curPlayerHand.push_back(getCard());
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
    return result;
}

}

namespace BerlekampMassey {
    const int mod = 2;
    int L, m, b, n;
    vector<int> s, C, B;
    void init() {
        s.clear();
        C.clear();
        B.clear();
        C.push_back(1);
        B.push_back(1);
        L = n = 0;
        m = b = 1;
    }
    int pow_mod(int a, int k) {
        int s = 1;
        while (k) {
            if (k & 1)
                s = 1ll * s * a % mod;
            a = 1ll * a * a % mod;
            k >>= 1;
        }
        return s;
    }
    void update(int d) {
        s.push_back(d);
        for (int i = 1; i <= L; ++i)
            d = (d + 1ll * C[i] * s[n - i] % mod) % mod;
        if (d == 0)
            ++m;
        else if (2 * L <= n) {
            vector<int> T = C;
            C.resize(n + 1 - L + 1);
            for (int i = L + 1; i <= n + 1 - L; ++i)
                C[i] = 0;
            for (int i = 0; i < B.size(); ++i)
                C[i + m] = (C[i + m] + mod - 1ll * d * pow_mod(b, mod - 2) % mod * B[i] % mod) % mod;
            L = n + 1 - L;
            B = T;
            b = d;
            m = 1;
        } else {
            for (int i = 0; i < B.size(); ++i)
                C[i + m] = (C[i + m] + mod - 1ll * d * pow_mod(b, mod - 2) % mod * B[i] % mod) % mod;
            ++m;
        }
        ++n;
    }
    void output() {
        // printf("F(n)=");
        for (int i = 1; i < C.size(); ++i) {
            // printf("%d\n", C[i])
            int output = (mod - C[i]) % mod;
            if (output > mod / 2)
                output -= mod;
            // printf("%s%d*F(n-%d)", (output < 0 || i == 1) ? "" : "+", output, i);
            printf("%d", output);
        }
        puts("");
    }
    void output_s() {
        // printf("F(n)=");
        for (int i = 1; i < s.size(); ++i) {
            printf("%d", s[i]);
        }
        puts("");
    }
    void output_C() {
        // printf("F(n)=");
        for (int i = 1; i < C.size(); ++i) {
            printf("%d", C[i]);
        }
        puts("");
    }
    int Next() {
        int ret = 0;
        for (int j = 0; j < 6; ++ j){
            int cnt = 0;
            int n = s.size();
            for (int i = 1; i < C.size(); ++i) {
                cnt = (cnt + C[i] * s[n-i]) % 2;
            }
            s.push_back(cnt);
            ret = ret * 2 + cnt;
            // printf("%d", cnt);
        }
        return ret % 52;
    }

    void solve(int arr[6]) {
        BerlekampMassey::init();
        int tmp[6];
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 6; ++ j) {
                tmp[j] = arr[i] % 2;
                arr[i] >>= 1;
            }
            for (int j = 5; j >= 0; --j) {
                BerlekampMassey::update(tmp[j]);
            }
        }
        // printf("Formule: ");
        // BerlekampMassey::output();
        // for (int i = 0; i < 10; ++ i)
        //     printf("%d\n", BerlekampMassey::Next());
    }

}

vector<vector<pair<int, int> > > playResults;
int f[12000][600];
int f_hits[12000][600];

const int MAX_HITS = 10;

void solve(int pos, int rounds) {
    // printf("%d %d\n", pos, rounds);
    // fflush(stdout);
    playResults.resize(PlayerSpace::cards.size());
    for(int i = pos; i - pos < rounds*10; i++) {
        for(int j = 0; j < MAX_HITS; j++) {
            PlayerSpace::curCard = i;
            string result = PlayerSpace::playHand(j);
            int point;
            if(result == "WIN")
                point = 1;
            else if(result == "LOSE")
                point = -1;
            else
                point = 0;

            playResults[i].push_back(make_pair(point, PlayerSpace::curCard));
            // printf("%d %d\n", point, PlayerSpace::curCard);
        }
    }
    memset(f, -11, sizeof(f));
    for(int i = pos; i - pos < rounds * 10; i++)
        f[i][0] = 0;
    for(int i = pos + rounds * 10 - 1; i >= pos; i--) {
        for(int j = 1; j <= rounds; j++)
            for(int k = 0; k < MAX_HITS; k++) {
                int point = playResults[i][k].first;
                int nextPos = playResults[i][k].second;
                if(nextPos >= rounds * 10 + pos)
                    continue;
                if(f[nextPos][j-1] + point > f[i][j]){
                    f[i][j] = f[nextPos][j-1] + point;
                    f_hits[i][j] = k;
                }
            }
    }
    // printf("%d\n", f[pos][rounds]);
}

bool exploitation;
int pos;
int hits;
int rounds = 500;
int pendingCard;

class Player {

    public:
        bool shouldHit(){
            if(!exploitation){
                return true;
            }
            else{
                if(hits > 0) {
                    hits--;
                    return true;
                }
                return false;
            }
        }
        void hit(int card){
            if(!exploitation){
                PlayerSpace::cards.push_back(card);
            }
            else{
                // nothing
            }
        }
        void startHand(int playerCard1, int playerCard2, int openDealerCard){
            if(!exploitation){
                PlayerSpace::cards.push_back(playerCard1);
                PlayerSpace::cards.push_back(playerCard2);
                PlayerSpace::cards.push_back(openDealerCard);
                pendingCard = PlayerSpace::cards.size();
                PlayerSpace::cards.push_back(0);
                rounds--;
            }
            else{
                hits = f_hits[pos][rounds];
                pos = playResults[pos][hits].second;
                rounds--;
            }
        }
        void endHand(vector<int> dealerHand, string result){
            if(!exploitation){
                PlayerSpace::cards[pendingCard] = dealerHand[1];
                for(int i = 2; i < dealerHand.size(); i++)
                    PlayerSpace::cards.push_back(dealerHand[i]);
                
                int start = -1;
                for(int i = 0; i+6 <= PlayerSpace::cards.size(); i++) {
                    bool ok = true;
                    for(int j = 0; j < 6; j++)
                        if(PlayerSpace::cards[i+j] < 12){
                            ok = false;
                            break;
                        }
                    if(ok){
                        start = i;
                        break;
                    }
                }

                if(start != -1) {
                    pos = PlayerSpace::cards.size();
                    int x[6];
                    for(int i = 0; i < 6; i++)
                        x[i] = PlayerSpace::cards[i + start];
                    BerlekampMassey::solve(x);
                    PlayerSpace::cards.resize(10000);
                    for(int i = start+6; i < 10000; i++) 
                        PlayerSpace::cards[i] = BerlekampMassey::Next();
                    // for(int i = 0; i < 10000-pos; i++)
                    //     PlayerSpace::cards[i] = PlayerSpace::cards[i + pos];
                    // pos = 0;
                    // for(int i = start; i < start+16; i++) 
                    //     printf("%d\n", PlayerSpace::cards[i]);
                    solve(pos, rounds);
                    exploitation = true;
                }
            }
            else{
                // nothing
            }
        }
};