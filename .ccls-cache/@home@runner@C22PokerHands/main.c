#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/errno.h>

// Define Constants
const gCardsInHand = 5;
const gMaxValue = 13;

//Define Enums
enum suit { CLUBS, DIAMONDS, HEARTS, SPADES };
enum value { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

// Define Structs
struct card { enum suit s; enum value v; };
struct hand { struct card c[gCardsInHand]; };

// Declare input file handles
FILE *gInputFile;

// Declare Functions
void usage (char *);

// Read Hand
enum value getValue (char);
enum suit getSuit (char);
struct hand readHand (void);

// Rank Functions - straight/flush/straight flush
int straight (struct hand);
bool flush (struct hand);
int straightFlush (struct hand);


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

enum value getValue (char c) {
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

enum suit getSuit (char c) {
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

struct hand readHand (void) {
  // I/O
  const int lineLength = 31;
  char inputArray[lineLength];
  fgets (inputArray, lineLength, gInputFile);
  inputArray[lineLength - 1] = '\0'; // Replace '\n' with '\0'

  // Fill Hand
  struct hand h;
  for (int i = 0; i < gCardsInHand; i++) {
    h.c[i].v = getValue(inputArray[i * 3 + 0]); // Get Value
    h.c[i].s = getSuit(inputArray[i * 3 + 1]); // Get Suit
    // Strip Newline - do nothing
  }

  return h;
}


// Rank Functions - straight/flush/straight-flush
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
  int min = gMaxValue + 1;
  for (int i = 0; i < gCardsInHand ; i++) {
    if (h.c[i].v < min) {
      min = h.c[i].v;
    }
  }
  return min;
}

int straight (struct hand h) {
  if (maxValue(h) == minValue(h) + 4) {
    return (maxValue(h));
  }
  else {
    return -1;
  }
}

bool flush (struct hand h) {
  // CLUBS, DIAMONDS, HEARTS, SPADES
  enum suit flushType = h.c[0].s; // Initialize first card
  for (int i = 1; i < gCardsInHand; i++) {
    if (h.c[i].s != flushType) {
      return false;
    }
  }
  return true;
}

int straightFlush (struct hand h) {
  if (flush (h)) {
    return straight(h);
  }

  return -1;
}



