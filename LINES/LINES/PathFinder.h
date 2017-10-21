#pragma once

typedef struct
{
    BYTE hour, min, sec;
} TIME;

const int notfinished = 0, notStarted = 0;
const int nonexistent = 2;
const int walkable = 0;
const int walkability_fetus = 1376256;
const int mapWidth = 9, mapHeight = 9;
const int zero = 0x0000ffff;
const int found = 1;

static int path = 0;

extern int walkability[mapWidth][mapHeight];
extern int pathLength;
extern POINT* pathBank;

int FindPath(int startX, int startY, int targetX, int targetY);
void EndPathfinder();
POINT* len(int StartX, int StartY, int& length);
void dest_len(POINT* PatchDestroy);
