#include "config.h"           // defines NUM_LED; used here and also in our custom library, CustomCRGBArray
#include "FastLED.h"          // Fastled library to control the LEDs
#include "CustomCRGBArray.h"

#define DATA_PIN 2
#define HOT_PINK 0xff0033

CustomCRGBArray<NUM_LEDS> leds;
const int ROWS = 32;
const int COLS = 32;
const int MAX_GEN = 200;
int remaining_showcase_count;
bool board[ROWS][COLS];
int prevBoard[ROWS];
int prevPrevBoard[ROWS];

void initBoard(bool board[][COLS])
{
    for (int i = 0; i < ROWS; i++) {
        prevBoard[i] = -1;
        prevPrevBoard[i] = -1;
        
        for (int j = 0; j < COLS; j++) {
            board[i][j] = rand() % 2;
        }
    }
    remaining_showcase_count = 100;
}

void printBoard(bool board[][COLS])
{
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int led_index = i + j * 32;
            if (board[i][j]) {
                leds[led_index] = HOT_PINK;
            } else {
                leds[led_index] = CRGB::Black;
            }
        }
    }
}

int countNeighbors(bool board[][COLS], int row, int col)
{
    int count = 0;
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            if (i >= 0 && i < ROWS && j >= 0 && j < COLS) {
                if (i != row || j != col) {
                    count += board[i][j];
                }
            }
        }
    }
    return count;
}

void updateBoard(bool board[][COLS])  // Update the game board for the next generation
{
    bool newBoard[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        prevPrevBoard[i] = prevBoard[i];
        prevBoard[i] = toInt(board[i]);

        for (int j = 0; j < COLS; j++) {
            int neighbors = countNeighbors(board, i, j);
            if (board[i][j]) {
                if (neighbors < 2 || neighbors > 3) {
                    newBoard[i][j] = false; // Cell dies
                } else {
                    newBoard[i][j] = true; // Cell survives
                }
            } else {
                if (neighbors == 3) {
                    newBoard[i][j] = true; // Cell is born
                } else {
                    newBoard[i][j] = false; // Cell stays dead
                }
            }
        }
    }

    // Copy the new board back to the original board
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = newBoard[i][j];
        }
    }
}

int toInt(bool arr[COLS]) {
    int packed = 0;
    for(int i = 0; i < 32; i++) {
        packed |= (arr[i] << i);
    }

    return packed;
}

bool shouldKeepGoing(int gen) {
  bool hasImmediateRepeat = true;
  for (int i = 0; i < ROWS; i++) {
    int curr = toInt(board[i]);
    if (curr != prevBoard[i]) {
      hasImmediateRepeat = false;
      break;
    }
  }

  bool hasDelayedRepeat = true;
  for (int i = 0; i < ROWS; i++) {
    int curr = toInt(board[i]);
    if (curr != prevPrevBoard[i]) {
      hasDelayedRepeat = false;
      break;
    }
  }

  if (hasDelayedRepeat || hasImmediateRepeat) {
    remaining_showcase_count--;
    return (remaining_showcase_count > 0);
  } else {
    return true; // gen < MAX_GEN;
  }
}

void setup() {
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);  // initializes the FastLED library
  FastLED.setBrightness(15);
  FastLED.clear(true);
}

void loop () {
    initBoard(board);
    for (int gen = 0; shouldKeepGoing(gen); gen++) {
        printBoard(board);
        FastLED.show();
        updateBoard(board);
        FastLED.delay(100);
    }
}