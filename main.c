#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/errno.h>

// Define Constants
const int gCardsInHand = 5;
const int gNumOfSuits = 4;
const int gMaxValue = 12;
const int gNumValues = gMaxValue + 1;

#define BLACK -1
#define TIE 0
#define WHITE +1

//Define Enums
enum suit { CLUBS, DIAMONDS, HEARTS, SPADES };
enum value { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

// Define Structs
struct card { enum suit s; enum value v; };
struct hand { struct card c[gCardsInHand]; };
struct handPair { struct hand black; struct hand white; };

// Declare input file handles
FILE *gInputFile;

// Declare Functions
void usage (char *);

// Read Hand
enum value charToValue (char);
enum suit charToSuit (char);
struct handPair readHand (void);

// Print Hand
void printValue (enum value);
void printSuit (enum suit);
void printHand (struct hand);

// Needed for Rank functions
int maxValue (struct hand);
int minValue (struct hand);
int cmpFunc (const void *, const void *);
struct hand sortCard (struct hand);
void printWinner (int);
void removeCards (struct hand*, int);

// Is Rank Functions - Highest rank first
bool isStraightFlush (struct hand);
bool isFourOfAKind (struct hand);
bool isFullHouse (struct hand);
bool isFlush (struct hand);
bool isStraight (struct hand);
bool isThreeOfAKind (struct hand);
bool isTwoPair (struct hand);
bool isPair (struct hand);
// High card not needed

// Rank Functions
int highCard (struct hand, struct hand, int);
int highestPair (struct hand, int);
int highestTripple (struct hand, int);
int highestStraight (struct hand);
int highestFour (struct hand);

// Compare Hands
void compareStraightFlush (struct hand, struct hand);
void compareFourOfAKind (struct hand, struct hand);
void compareFullHouse (struct hand, struct hand);
void compareFlush (struct hand, struct hand);
void compareStraight (struct hand, struct hand);
void compareThreeOfAKind (struct hand, struct hand);
void compareTwoPair (struct hand, struct hand);
void comparePair (struct hand, struct hand);
void compareHighCard (struct hand, struct hand);
void compareHands (struct handPair);


int main(int argc, char *argv[]) {
  /*-------------------------------FILE INITIALIZATION START-----------------------------*/
  if (argc != 2) usage (argv[0]);

  if (NULL == (gInputFile = fopen(argv[1], "r"))) {
    fprintf (stderr, "inputFile: %s: %s\n", argv[1], strerror(errno));
    exit (EXIT_FAILURE);
  }
  else {
      fprintf (stderr, "%s opened for reading.\n" , argv[1]);
    }
  /*-------------------------------FILE INITIALIZATION END--------------------------------*/

  /*--------------------------------MAIN PROGRAM START------------------------------------*/

  struct handPair hp = readHand();
  printHand (hp.black);
  printHand (hp.white);
  printf ("\n");


  
  /*--------------------------------MAIN PROGRAM END--------------------------------------*/

  /*--------------------------------FILE CLEANUP START------------------------------------*/
  fclose (gInputFile);
  /*--------------------------------FILE CLEANUP END--------------------------------------*/
  return 0;
}

// Define Functions
void usage (char *cmd) {
  fprintf (stderr, "usage: %s inputFileName\n", cmd);
  exit (EXIT_SUCCESS);
}

enum value charToValue (char c) {
  switch (c) {
    case '2':
      return TWO;
      break;
    case '3':
      return THREE;
      break;
    case '4':
      return FOUR;
      break;
    case '5':
      return FIVE;
      break;
    case '6':
      return SIX;
      break;
    case '7':
      return SEVEN;
      break;
    case '8':
      return EIGHT;
      break;
    case '9':
      return NINE;
      break;
    case 'T':
      return TEN;
      break;
    case 'J':
      return JACK;
      break;
    case 'Q':
      return QUEEN;
      break;
    case 'K':
      return KING;
      break;
    case 'A':
      return ACE;
      break;
    default:
      printf ("Invalid Value: %c\n", c);
      return -1;
      break;
  }  
}

enum suit charToSuit (char c) {
  switch (c) {
    case 'C':
      return CLUBS;
      break;
    case 'D':
      return DIAMONDS;
      break;
    case 'H':
      return HEARTS;
      break;
    case 'S':
      return SPADES;
      break;
    default:
      printf ("Invalid Suit: %c\n", c);
      return -1;
      break;
  }
}

struct handPair readHand (void) {
  // I/O
  const int lineLength = 31;
  char inputArray[lineLength];
  fgets (inputArray, lineLength, gInputFile);
  inputArray[lineLength - 1] = '\0'; // Replace '\n' with '\0'

  // Fill black Hand
  struct hand b;
  for (int i = 0; i < gCardsInHand; i++) {
    b.c[i].v = charToValue(inputArray[i * 3 + 0]); // Get Value
    b.c[i].s = charToSuit(inputArray[i * 3 + 1]); // Get Suit
    // Strip Newline - do nothing
  }
  // Fill white Hand
  struct hand w;
  for (int i = gCardsInHand, j = 0; i < 2 * gCardsInHand; i++, j++) {
    w.c[j].v = charToValue(inputArray[i * 3 + 0]); // Get Value
    w.c[j].s = charToSuit(inputArray[i * 3 + 1]); // Get Suit
    // Strip Newline - do nothing
  }


  struct handPair h;
  h.black = b;
  h.white = w;

  return h;
}

void printValue (enum value v) {
  switch (v) {
    case TWO:
      printf ("2");
      break;
    case THREE:
      printf ("3");
      break;
    case FOUR:
        printf ("4");
      break;
    case FIVE:
        printf ("5");
      break;
    case SIX:
        printf ("6");
      break;
    case SEVEN:
        printf ("7");
      break;
    case EIGHT:
        printf ("8");
      break;
    case NINE:
        printf ("9");
      break;
    case TEN:
        printf ("10");
      break;
    case JACK:
        printf ("J");
      break;
    case QUEEN:
        printf ("Q");
      break;
    case KING:
        printf ("K");
      break;
    case ACE:
        printf ("A");
      break;
    default:
      printf ("Invalid Value: %d\n", v);
      break;
  }  
}

void printSuit (enum suit s) {
  switch (s) {
    case CLUBS:
      printf ("C");
      break;
    case DIAMONDS:
      printf ("D");
      break;
    case HEARTS:
      printf ("H");
      break;
    case SPADES:
      printf ("S");
      break;
    default:
      printf ("Invalid Suit: %c\n", s);
      break;
  }
}

void printHand (struct hand h) {
  for (int i = 0; i < gCardsInHand; i++) {
    printValue (h.c[i].v);
    printSuit(h.c[i].s);
    printf (" ");
  }
}




// Common Functions
int maxValue (struct hand h) {
  int max = 0;
  for (int i = 0; i < gCardsInHand ; i++) {
    if (h.c[i].v > max) {
      max = h.c[i].v;
    }
  }
  return max;
}

int minValue (struct hand h) {
  int min = gMaxValue;
  for (int i = 0; i < gCardsInHand ; i++) {
    if (h.c[i].v < min) {
      min = h.c[i].v;
    }
  }
  return min;
}



int cmpFunc (const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}
struct hand sortCard (struct hand h) {
  // 1. Sort cards in descending order (highest card first)
  qsort (h.c, gCardsInHand, sizeof(struct card), cmpFunc);

  return h;
}
void printWinner (int w) {
  if (w == BLACK) {
    printf ("Black wins.\n");
  }
  else if (w == WHITE) {
    printf ("White wins.\n");
  }
  else if (w == TIE) {
    printf ("Tie.\n");
  }
}
void removeCards (struct hand *h, int n) {
  for (int i = 0; i < gCardsInHand; i++) {
    if (h->c[i].v == n) {
      h->c[i].v = -1;
    }
  }
}


// isHand
bool isPair (struct hand h) {
  int val[gNumValues] = {0};
  for (int i = 0; i < gCardsInHand; i++) {
    val[h.c[i].v]++;
  }
  for (int i = 0; i < gNumValues; i++) {
    if (val[i] == 2) {
      return (true);
    }
  }
  return (false);
}

bool isTwoPair (struct hand h) {
  int val[gNumValues] = {0};
  for (int i = 0; i < gCardsInHand; i++) {
    val[h.c[i].v]++;
  }
  int numDoubles = 0;
  for (int i = 0; i < gNumValues; i++) {
    if (val[i] == 2) {
      numDoubles++;
    }
  }
  if (numDoubles == 2) {
    return (true);
  }
  else {
    return (false);
  }
}

bool isThreeOfAKind (struct hand h) {
  int val[gNumValues] = {0};
  for (int i = 0; i < gCardsInHand; i++) {
    val[h.c[i].v]++;
  }
  for (int i = 0; i < gNumValues; i++) {
    if (val[i] == 3) {
      return (true);
    }
  }
  return (false);
}

bool isStraight (struct hand h) {
  int val[gNumValues] = {0};
  for (int i = 0; i < gCardsInHand; i++) {
    val[h.c[i].v]++;
  }
  int numConsecutive = 0;
  for (int i = 0; i < gNumValues; i++) {
    if (val[i] == 1) {
      numConsecutive++;
    }
    if (numConsecutive == 5) {
      return (true);
    }
    else if (val[i] != 1) {
      numConsecutive = 0;
    }
  }
  return (false);
}

bool isFlush (struct hand h) {
  int val[gNumOfSuits] = {0};
  for (int i = 0; i < gCardsInHand; i++) {
    val[h.c[i].s]++;
  }
  for (int i = 0; i < gNumOfSuits; i++) {
    if (val[i] == 5) {
      return (true);
    }
  }
  return (false);
}

bool isFullHouse (struct hand h) {
  int val[gNumValues] = {0};
  for (int i = 0; i < gCardsInHand; i++) {
    val[h.c[i].v]++;
  }
  bool two, three;
  for (int i = 0; i < gNumValues; i++) {
    if (val[i] == 2) {
      two = true;
    }
    if (val[i] == 3) {
      three = true;
    }
  }
  if (two && three) {
    return (true);
  }
  else {
    return (false);
  }
}

bool isFourOfAKind (struct hand h) {
  int val[gNumValues] = {0};
  for (int i = 0; i < gCardsInHand; i++) {
    val[h.c[i].v]++;
  }
  for (int i = 0; i < gNumValues; i++) {
    if (val[i] == 4) {
      return (true);
    }
  }
  return (false);
}

bool isStraightFlush (struct hand h) {
  if (isStraight(h) && isFlush(h)) {
    return (true);
  }
  else {
    return (false);
  }
}

// Hands
int highCard (struct hand b, struct hand w, int nc) {
  b = sortCard (b);
  w = sortCard (w);

  for (int i = 0; i < nc; i++) {
    if (b.c[i].v > w.c[i].v) {
      return (BLACK);
    }
    else if (b.c[i].v < w.c[i].v) {
      return (WHITE);
    }
    else {
      return (TIE);
    }
  }
  return (TIE);
}

int highestPair (struct hand h, int nc) {
  int val[gNumValues] = {0};
  for (int i = 0; i < nc; i++) {
    val[h.c[i].v]++;
  }
  int highest = -1;
  for (int i = 0; i < gNumValues; i++) {
    if (val[i] == 2) {
      highest = i;
    }
  }
  return (highest);
}

int highestTripple (struct hand h, int nc) {
  int val[gNumValues] = {0};
  for (int i = 0; i < nc; i++) {
    val[h.c[i].v]++;
  }
  int highest = -1;
  for (int i = 0; i < gNumValues; i++) {
    if (val[i] == 3) {
      highest = i;
    }
  }
  return (highest);
}

int highestStraight (struct hand h) {
  if (isStraight(h)) {
    return (maxValue(h));
  }
  else {
    return (-1);
  }
}

int highestFour (struct hand h) {
  int val[gNumValues] = {0};
  for (int i = 0; i < gCardsInHand; i++) {
    val[h.c[i].v]++;
  }
  int highest = -1;
  for (int i = 0; i < gNumValues; i++) {
    if (val[i] == 4) {
      highest = i;
    }
  }
  return (highest);
}


// Compare Functions
void compareHighCards (struct hand b, struct hand w, int nc) {
  int winner = highCard (b, w, nc);
  printWinner (winner);
}

void comparePair (struct hand b, struct hand w, int nc) {
  int hpBlack = highestPair (b, nc);
  int hpWhite = highestPair (w, nc);

  if (hpBlack > hpWhite) {
    printWinner(BLACK);
  }
  else if (hpBlack < hpWhite) {
    printWinner(WHITE);
  }
  else {
    removeCards (&b, hpBlack);
    removeCards (&w, hpWhite);
    compareHighCards (b, w, nc - 2);
  }
}
  
void compareTwoPairs (struct hand b, struct hand w, int nc) {
  int hpBlack = highestPair (b, nc);
  int hpWhite = highestPair (w, nc);

  if (hpBlack > hpWhite) {
    printWinner(BLACK);
  }
  else if (hpBlack < hpWhite) {
    printWinner(WHITE);
  }
  else {
    removeCards (&b, hpBlack);
    removeCards (&w, hpWhite);
    comparePair (b, w, nc - 2);
  }
}

void compareThreeOfAKind (struct hand b, struct hand w, int nc) {
  int hpBlack = highestTripple (b, nc);
  int hpWhite = highestTripple (w, nc);

  if (hpBlack > hpWhite) {
    printWinner(BLACK);
  }
  else if (hpBlack < hpWhite) {
    printWinner(WHITE);
  }
  else {
    removeCards (&b, hpBlack);
    removeCards (&w, hpWhite);
    compareTwoPairs (b, w, nc - 3);
  }
}

void compareStraight (struct hand b, struct hand w) {
  int hpBlack = highestStraight (b);
  int hpWhite = highestStraight (w);

  if (hpBlack > hpWhite) {
    printWinner(BLACK);
  }
  else if (hpBlack < hpWhite) {
    printWinner(WHITE);
  }
  else {
    printWinner(TIE);
  }
}

void compareFlush (struct hand b, struct hand w) {
  if (isFlush(b) && isFlush(w)) {
    compareHighCards (b, w, gCardsInHand);
  }
  else if (isFlush(b)) {
    printWinner(BLACK);
  }
  else {
    printWinner(WHITE);
  }
}

void compareFullHouse (struct hand b, struct hand w) {
  int h3Black = highestTripple (b, gCardsInHand);
  int h3White = highestTripple (w, gCardsInHand);

  if (h3Black > h3White) {
    printWinner(BLACK);
  }
  else if (h3Black < h3White) {
    printWinner(WHITE);
  }
  else {
    removeCards (&b, h3Black);
    removeCards (&w, h3White);
    comparePair (b, w, gCardsInHand - 3);
  }
}

void compareFourOfAKind (struct hand b, struct hand w) {
  int hpBlack = highestFour (b);
  int hpWhite = highestFour (w);

  if (hpBlack > hpWhite) {
    printWinner(BLACK);
  }
  else if (hpBlack < hpWhite) {
    printWinner(WHITE);
  }
  else {
    removeCards (&b, hpBlack);
    removeCards (&w, hpWhite);
    compareHighCards (b, w, gCardsInHand - 4);
  }
}

void compareStraightFlush (struct hand b, struct hand w) {
  if (isFlush(b) && isStraight(b) && isFlush(w) && isStraight(w)) {
    compareStraight (b, w);
  }
  else if (isFlush(b) && isStraight(b)) {
    printWinner(BLACK);
  }
  else if (isFlush(w) && isStraight(w)) {
    printWinner(WHITE);
  }
}




void compareHands (struct handPair hp) {
  if      (isStraightFlush(hp.black) || isStraightFlush(hp.white))  { compareStraightFlush(hp.black, hp.white); }
  else if (isFourOfAKind(hp.black) || isFourOfAKind(hp.white))      { compareFourOfAKind(hp.black, hp.white); }
  else if (isFullHouse(hp.black) || isFullHouse(hp.white))          { compareFullHouse(hp.black, hp.white); }
  else if (isFlush(hp.black) || isFlush(hp.white))                  { compareFlush(hp.black, hp.white); }
  else if (isStraight(hp.black) || isStraight(hp.white))            { compareStraight(hp.black, hp.white); }
  else if (isThreeOfAKind(hp.black) || isThreeOfAKind(hp.white))    { compareThreeOfAKind(hp.black, hp.white, gCardsInHand); }
  else if (isTwoPair(hp.black) || isTwoPair(hp.white))              { compareTwoPairs(hp.black, hp.white, gCardsInHand); }
  else if (isPair(hp.black) || isPair(hp.white))                    { comparePair(hp.black, hp.white, gCardsInHand); }
  else                                                              { compareHighCards(hp.black, hp.white, gCardsInHand); }
}