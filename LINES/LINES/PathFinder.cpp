#include "stdafx.h"
#include "PathFinder.h"

int onClosedList = 10;
int openList[mapWidth * mapHeight + 2];
int whichList[mapWidth + 1][mapHeight + 1];
int openX[mapWidth * mapHeight + 2];
int openY[mapWidth * mapHeight + 2];
int parentX[mapWidth + 1][mapHeight + 1];
int parentY[mapWidth + 1][mapHeight + 1];
int Fcost[mapWidth + 1][mapHeight + 1];
int xPath;
int yPath;

//-----------------------------------------------------------------------------
// Реализация алгоритма A*(A-star)
//-----------------------------------------------------------------------------
int FindPath(int startX, int startY, int targetX, int targetY)
{
    int a, b, m, temp, path, tempx, newOpenListItemID = 0;

    if (startX == targetX && startY == targetY)
    {
        return found;
    }

    if (walkability[targetX][targetY] != walkable &&
        HIWORD(walkability[targetX][targetY]) != HIWORD(walkability_fetus))
    {
        xPath = startX;
        yPath = startY;
        return nonexistent;
    }
    for (int x = 0; x < mapWidth; x++)
    {
        for (int y = 0; y < mapHeight; y++)
        {
            whichList[x][y] = 0;
        }
    }
    onClosedList = 2;
    int onOpenList = 1;
    pathLength = notStarted;

    int numberOfOpenListItems = 1;
    openList[1] = 1;
    openX[1] = startX;
    openY[1] = startY;

    do
    {
        if (numberOfOpenListItems != 0)
        {
            int parentXval = openX[openList[1]];
            int parentYval = openY[openList[1]];
            whichList[parentXval][parentYval] = onClosedList;
            numberOfOpenListItems--;
            openList[1] = openList[numberOfOpenListItems + 1];
            int v = 1;

            do
            {
                int u = v;
                if (2 * u + 1 <= numberOfOpenListItems)
                {
                    if (Fcost[openX[openList[u]]][openY[openList[u]]] >=
                        Fcost[openX[openList[2 * u]]][openY[openList[2 * u]]])
                        v = 2 * u;

                    if (Fcost[openX[openList[v]]][openY[openList[v]]] >=
                        Fcost[openX[openList[2 * u + 1]]][openY[openList[2 * u + 1]]])
                        v = 2 * u + 1;
                }
                else
                {
                    if (2 * u <= numberOfOpenListItems)
                    {
                        if (Fcost[openX[openList[u]]][openY[openList[u]]] >=
                            Fcost[openX[openList[2 * u]]][openY[openList[2 * u]]])
                            v = 2 * u;
                    }
                }

                if (u != v)
                {
                    temp = openList[u];
                    openList[u] = openList[v];
                    openList[v] = temp;
                }
                else
                    break;
            } while (true);

            for (a = parentXval - 1; a <= parentXval + 1; a++)
            {
                for (b = parentYval - 1 + abs(parentXval - a); b <= parentYval + 1 - abs(parentXval - a); b++)
                {
                    if (a != -1 && b != -1 && a != mapWidth && b != mapHeight)
                    {
                        if (whichList[a][b] != onClosedList)
                        {
                            if (walkability[a][b] == walkable || HIWORD(walkability[a][b]) == HIWORD(walkability_fetus))
                            {
                                if (whichList[a][b] != onOpenList)
                                {
                                    newOpenListItemID++;
                                    m = numberOfOpenListItems + 1;
                                    openList[m] = newOpenListItemID;
                                    openX[newOpenListItemID] = a;
                                    openY[newOpenListItemID] = b;

                                    Fcost[a][b] = 10 * (abs(a - targetX) + abs(b - targetY));
                                    parentX[a][b] = parentXval;
                                    parentY[a][b] = parentYval;

                                    while (m != 1)
                                    {
                                        if (Fcost[openX[openList[m]]][openY[openList[m]]] <=
                                            Fcost[openX[openList[m / 2]]][openY[openList[m / 2]]])
                                        {
                                            temp = openList[m / 2];
                                            openList[m / 2] = openList[m];
                                            openList[m] = temp;
                                            m = m / 2;
                                        }
                                        else
                                            break;
                                    }
                                    numberOfOpenListItems++;

                                    whichList[a][b] = onOpenList;
                                }

                                else
                                {
                                    if (Fcost[parentXval][parentYval] < Fcost[a][b])
                                    {
                                        parentX[a][b] = parentXval;
                                        parentY[a][b] = parentYval;
                                        for (int x = 1; x <= numberOfOpenListItems; x++)
                                        {
                                            if (openX[openList[x]] == a && openY[openList[x]] == b)
                                            {
                                                m = x;
                                                while (m != 1)
                                                {
                                                    if (Fcost[openX[openList[m]]][openY[openList[m]]] <
                                                        Fcost[openX[openList[m / 2]]][openY[openList[m / 2]]])
                                                    {
                                                        temp = openList[m / 2];
                                                        openList[m / 2] = openList[m];
                                                        openList[m] = temp;
                                                        m = m / 2;
                                                    }
                                                    else
                                                        break;
                                                }
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        else
        {
            path = nonexistent;
            break;
        }
        if (whichList[targetX][targetY] == onOpenList)
        {
            path = found;
            break;
        }
    } while (true);

    if (path == found)
    {
        int pathX = targetX;
        int pathY = targetY;
        do
        {
            tempx = parentX[pathX][pathY];
            pathY = parentY[pathX][pathY];
            pathX = tempx;
            pathLength = pathLength + 1;
        } while (pathX != startX || pathY != startY);

        pathBank = (POINT*)realloc(pathBank,
            pathLength * sizeof(POINT));

        pathX = targetX;
        pathY = targetY;
        int cellPosition = pathLength;
        do
        {
            cellPosition--;
            pathBank[cellPosition].x = pathX;
            pathBank[cellPosition].y = pathY;

            tempx = parentX[pathX][pathY];
            pathY = parentY[pathX][pathY];
            pathX = tempx;
        } while (pathX != startX || pathY != startY);
    }
    return path;    
}

void EndPathfinder()
{
    if (pathBank)
    {
        free(pathBank);
        pathBank = nullptr;
    }
}

POINT* len(int StartX, int StartY, int& length)
{
    int north = 1, south = 1, west = 1, east = 1;
    POINT* PatchDestroy = nullptr;
    length = 0;

    while (StartY - north != -1 && walkability[StartX][StartY] == walkability[StartX][StartY - north])
        north++;

    while (StartY + south != mapHeight && walkability[StartX][StartY] == walkability[StartX][StartY + south])
        south++;

    while (StartX - west != -1 && walkability[StartX][StartY] == walkability[StartX - west][StartY])
        west++;

    while (StartX + east != mapWidth && walkability[StartX][StartY] == walkability[StartX + east][StartY])
        east++;

    int height = north + south - 1;
    int width = west + east - 1;


    if (height >= 5 && width >= 5 && height >= width || height >= 5)
    {
        length = height;
        PatchDestroy = (POINT*)malloc(sizeof(POINT) * height);
        StartY -= north - 1;
        for (int i = 0; i < height; i++)
        {
            PatchDestroy[i].x = StartX;
            PatchDestroy[i].y = StartY + i;
        }
    }
    else if (width >= 5)
    {
        length = width;
        PatchDestroy = (POINT*)malloc(sizeof(POINT) * width);
        StartX -= west - 1;
        for (int i = 0; i < width; i++)
        {
            PatchDestroy[i].x = StartX + i;
            PatchDestroy[i].y = StartY;
        }
    }

    return PatchDestroy;
}

void dest_len(POINT* PatchDestroy)
{
    if (PatchDestroy)
    {
        free(PatchDestroy);
    }
}