# Programming Challenges
## Problem 2.2: Poker Hands[^1]

### Problem description
This program is to compare two poker hands and determine which wins (if any). A poker hand consists of five cards. The first card is named "Black", the second "White". The suit of each card is either: Clubs (C); Diamonds(D); Hearts (H); Spades (S). The value of each card is from the set { 2, 3, 4, ... 10, J, Q, K, A }. 

___

#### The rank of the poker hands is ordered as follows (from lowest to highest).  

1. **High Card**     
  If highest cards have the same value, the hands are ranked by the value of the next highest card, and so on.
2. **Pair**     
  The hand contains two cards with the same value. If the "Two Pairs" (being compared) have the same value, the hands are ranked by the highest card not in the pair, this scenario follows the rules of "High Card".      
3. **Two Pairs**         
  If both hands have "Two Pairs", cards are ranked by the value of the highest pair value. if they are the same, the hands are ranked by the value of the lowestpair value. If these cards are equal, the hands are ranked by the value of the card not in either of the pairs.
4. **Three of a Kind**
  The hand contains three cards with the same value. Hands that both contain "Three of a Kind" are ranked based on the value of the "Three of a Kind".
6. **Straight**
  The hand contains five cards of consecutive values. If both hands contain a "Straight", the hand with the highest value card wins.
8. **Flush**
  The hand contains five cards of the same suit. If both hands contain a "Flush", The hands are compared using the rules outlined for "High Card".
10. **Full House**
  The hand contains three cards of the same value plus a pair of the same value. If both hands contain a "Full House", the hand with the highest "Three of a Kind" wins.
12. **Four of a Kind**
  The hand contains four cards with the same value. If both hands contain a "Four of a Kind", the hand with the heighest "Four of a Kind" wins.
14. **Straight Flush**
  The hand contains five cards of the same suit with consecutive values. If both hands have a "Straight Flush" the hands are ranked by the highest card.

___

### Example 
> **Input**         
> 2H 3D 5S 9C KD 2C 3H 4S 8C AH           
> 2H 4S 4C 2D 4H 2S 8S AS QS 3S         
> 2H 3D 5S 9C KD 2C 3H 4S 8C KH            
> 2H 3D 5S 9C KD 2D 3H 5C 9S KH                 

>**Output**         
>White wins.       
>Black wins.     
>Black wins.         
>Tie.     


[^1]: Programming Challenges By S.Skienna and M.Revilla, page 43