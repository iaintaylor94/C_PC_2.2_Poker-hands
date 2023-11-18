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
enum value { TWO = 0, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

// Define Structs
struct card { enum suit s; enum value v; };
struct hand { struct card c[gCardsInHand]; };

// Declare input file handles
FILE *gInputFile;

// Declare Functions
void usage (char *);
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

// Define Structs
struct card { enum suit s; enum value v; };
struct hand { struct card c[gCardsInHand]; };


// Rank Functions - straight/flush/straight flush
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

bool flush (struct hand);
int straightFlush (struct hand);