#include "config.h"           // defines NUM_LED; used here and also in our custom library, CustomCRGBArray
#include "FastLED.h"          // Fastled library to control the LEDs
#include "CustomCRGBArray.h"

#define DATA_PIN 2
#define HOT_PINK 0xff0033

CustomCRGBArray<NUM_LEDS> leds;
const int ROWS = 32;
const int COLS = 32;
const int MAX_GEN = 2000;
int remaining_showcase_count;
bool board[ROWS][COLS];
int prevBoard[ROWS];
int prevPrevBoard[ROWS];
int animationFrameRate = 5;  // Frame rate of the color animation (x times faster than Conway's Game of Life)

CRGBPalette16 colorPalette;  // Color palette for the independent animation

void initBoard(bool board[][COLS])
{
    srand(analogRead(A0));
    for (int i = 0; i < ROWS; i++) {
        prevBoard[i] = -1;
        prevPrevBoard[i] = -1;
        
        for (int j = 0; j < COLS; j++) {
            board[i][j] = rand() % 2;
        }
    }
    remaining_showcase_count = 125;
}


float speed = 8;

void printBoard(bool board[][COLS])
{
    uint8_t colorOffset =  millis() / speed;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int led_index = i + j * 32;
            leds[led_index] = board[i][j] ? ColorFromPalette(colorPalette, (i*8) + colorOffset, 255) : CRGB::Black;
        }
    }
}

int countNeighbors(bool board[][COLS], int row, int col) 
{
    // row represents the vertical position (Y-axis), col the horizontal (X-axis)
    // decreasing row moves up (North)
    // increasing row moves down (South)
    // decreasing col moves left (West)
    // increasing col moves right (East)

    int count = 0;

    // Precompute boundary conditions
    int r0 = row > 0,        r1 = row < ROWS - 1;
    int c0 = col > 0,        c1 = col < COLS - 1;

    // Check each neighbor, avoiding out-of-bounds access
    count += r0 && c0  ? board[row - 1][col - 1] : 0; // NW (↖)
    count += r0        ? board[row - 1][col]     : 0; // N  (↑)
    count += r0 && c1  ? board[row - 1][col + 1] : 0; // NE (↗)
    count += c0        ? board[row][col - 1]     : 0; // W  (←)
    count += c1        ? board[row][col + 1]     : 0; // E  (→)
    count += r1 && c0  ? board[row + 1][col - 1] : 0; // SW (↙)
    count += r1        ? board[row + 1][col]     : 0; // S  (↓)
    count += r1 && c1  ? board[row + 1][col + 1] : 0; // SE (↘)

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
    return gen < MAX_GEN;  // to allow indefinite generations, replace this here line with:  return true;
  }
}

void setup() {
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);  // initializes the FastLED library
  FastLED.setBrightness(5);
  FastLED.clear(true);

  // Set up the color palette for the independent animation
  colorPalette = RainbowColors_p;  // PartyColors_p;  // ForestColors_p;  // CloudColors_p;  // OceanColors_p;  // RainbowColors_p; 
}

void loop () {
    initBoard(board);

    for (int gen = 0; shouldKeepGoing(gen); gen++) {
        for (int countdown = animationFrameRate; countdown >= 0; countdown--) {

          printBoard(board);
          FastLED.show();
        }
        
        updateBoard(board);
    }
}