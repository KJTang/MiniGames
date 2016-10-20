using UnityEngine;
using System;
using System.Collections;
using System.Collections.Generic;

public struct MapPoint {
    public int x, y;
    public MapPoint(int x, int y) {
        this.x = x;
        this.y = y;
    }
}

public struct RoomInfo {
    public int x, y;
    public int w, h;
}

public struct MonsterInfo {
    public int x, y;
    public int type;
}

public enum MapType {
    Blank,
    Floor,
    Stairs, 
    Door, 
    DoorOut, 
    WallVertical,
    WallHorizontal,
    ItemGold, 
    ItemHeal, 
    Mark,   // will be cleared after using
};

public class MapGenerator {
    public const int MAP_WIDTH = 40;
    public const int MAP_HEIGHT = 40;
    public const int MIN_ROOM_SIZE = 10;
    public const int MAX_ROOM_SIZE = 15;
    public const int MIN_MONSTER_COUNT = 0;
    public const int MAX_MONSTER_COUNT = 3;
    public const int MIN_GOLD_COUNT = 1;
    public const int MAX_GOLD_COUNT = 3;
    public const int MIN_HEAL_COUNT = 0;
    public const int MAX_HEAL_COUNT = 2;

    public MapType[,] map;
    public int playerPosX;
    public int playerPosY;
    public List<MonsterInfo> monsters;
    public List<RoomInfo> rooms;

    private System.Random rand;

    public void Init() {
        map = new MapType[MAP_HEIGHT, MAP_WIDTH];
        for (int i = 0; i != MAP_HEIGHT; ++i) {
            for (int j = 0; j != MAP_WIDTH; ++j) {
                map[i, j] = MapType.Blank;
            }
        }
        monsters = new List<MonsterInfo>();
        rooms = new List<RoomInfo>();
        rand = new System.Random();
    }

    public void GenerateMap(int expectedRoomCount, int maxTriedTimes = 100) {
        int triedTimes = 0;
        int roomCount = 0;
        while (roomCount < expectedRoomCount && triedTimes < maxTriedTimes) {
            if (GenerateRoom(rand.Next(MAP_WIDTH), rand.Next(MAP_HEIGHT))) {
                ++roomCount;
            }
            ++triedTimes;
        }

        GenerateStairsPosition();
        GenerateDoorPosition();
        GeneratePlayerPosition();
        GenerateMonsterPosition();
        GenerateItemGoldPosition();
        GenerateItemHealPosition();
        ClearAllMarks();
    }

    bool GenerateRoom(int x, int y) {
        int originX = x, originY = y;
        int width = rand.Next(MIN_ROOM_SIZE, MAX_ROOM_SIZE);
        int height = rand.Next(MIN_ROOM_SIZE, MAX_ROOM_SIZE);
        // detect
        if ((originX < 0 || originX + width >= MAP_WIDTH) || 
            (originY < 0 || originY + height >= MAP_HEIGHT)) {
            return false;
        }
        for (int i = 0; i != rooms.Count; ++i) {
            if ((originX <= rooms[i].x && rooms[i].x < originX + width && rooms[i].y < originY + height) || 
                (rooms[i].x <= originX && originX < rooms[i].x + rooms[i].w && originY < rooms[i].y + rooms[i].h)) {
                return false;
            }
        }
        // draw
        for (int i = 1; i != height; ++i) {
            for (int j = 1; j != width; ++j) {
                map[originY+i, originX+j] = MapType.Floor;
            }
        }
        for (int i = 0; i != height; ++i) {
            map[originY+i, originX] = MapType.WallHorizontal;
            map[originY+i, originX+width-1] = MapType.WallHorizontal;
        }
        for (int j = 1; j != width-1; ++j) {
            map[originY, originX+j] = MapType.WallVertical;
            map[originY+height-1, originX+j] = MapType.WallVertical;
        }
        // save
        RoomInfo room = new RoomInfo();
        room.x = originX;
        room.y = originY;
        room.w = width;
        room.h = height;
        rooms.Add(room);
        return true;
    }

    void GenerateStairsPosition() {
        RoomInfo room = rooms[rand.Next(rooms.Count)];
        int stairsPosX, stairsPosY;
        do {
            stairsPosX = rand.Next(1, room.w - 1) + room.x;
            stairsPosY = rand.Next(2, room.h - 1) + room.y;
        } while (map[stairsPosY, stairsPosX] != MapType.Floor);
        map[stairsPosY, stairsPosX] = MapType.Stairs;
    }

    void GenerateDoorPosition() {
        int doorPosX, doorPosY;
        for (int i = 0; i != rooms.Count; ++i) {
            do {
                doorPosX = rand.Next(1, rooms[i].w - 1) + rooms[i].x;
                doorPosY = rand.Next(1, rooms[i].h - 1) + rooms[i].y;
            } while (map[doorPosY, doorPosX] != MapType.Floor || map[doorPosY, doorPosX + 1] != MapType.Floor);
            map[doorPosY, doorPosX] = MapType.Door;
            map[doorPosY, doorPosX+1] = MapType.DoorOut;
        }
    }

    void GeneratePlayerPosition() {
        RoomInfo room = rooms[rand.Next(rooms.Count)];
        do {
            playerPosX = rand.Next(1, room.w - 1) + room.x;
            playerPosY = rand.Next(1, room.h - 1) + room.y;
        } while (map[playerPosY, playerPosX] != MapType.Floor);
        map[playerPosY, playerPosX] = MapType.Mark;
    }

    void GenerateMonsterPosition() {
        for (int i = 0; i != rooms.Count; ++i) {
            int monsterCount = rand.Next(MIN_MONSTER_COUNT, MAX_MONSTER_COUNT+1);
            for (int j = 0; j != monsterCount; ++j) {
                // do {
                    int x = rand.Next(1, rooms[i].w - 1) + rooms[i].x;
                    int y = rand.Next(1, rooms[i].h - 1) + rooms[i].y;
                // } while (map[j, i] != MapType.Floor);
                if (map[y, x] == MapType.Floor) {
                    map[y, x] = MapType.Mark;
                    MonsterInfo newMonster = new MonsterInfo();
                    newMonster.x = x;
                    newMonster.y = y;
                    // newMonster.type = 0;
                    monsters.Add(newMonster);
                }
            }
        }
    }

    void GenerateItemGoldPosition() {
        int goldCount = rand.Next(MIN_GOLD_COUNT, MAX_GOLD_COUNT+1);
        for (int j = 0; j != goldCount; ++j) {
            int roomID = rand.Next(0, rooms.Count);
            int tried = 0;
            while (tried < 3) {
                int x = rand.Next(1, rooms[roomID].w - 1) + rooms[roomID].x;
                int y = rand.Next(1, rooms[roomID].h - 1) + rooms[roomID].y;
                if (map[y, x] == MapType.Floor) {
                    map[y, x] = MapType.ItemGold;
                    break;
                }
                ++tried;
            }
        }
    }

    void GenerateItemHealPosition() {
        int healCount = rand.Next(MIN_HEAL_COUNT, MAX_HEAL_COUNT+1);
        for (int j = 0; j != healCount; ++j) {
            int roomID = rand.Next(0, rooms.Count);
            int tried = 0;
            while (tried < 3) {
                int x = rand.Next(1, rooms[roomID].w - 1) + rooms[roomID].x;
                int y = rand.Next(1, rooms[roomID].h - 1) + rooms[roomID].y;
                if (map[y, x] == MapType.Floor) {
                    map[y, x] = MapType.ItemHeal;
                    break;
                }
                ++tried;
            }
        }
    }

    void ClearRoomMarks(int roomID) {
        RoomInfo room = rooms[roomID];
        for (int i = 0; i != room.h; ++i) {
            for (int j = 0; j != room.w; ++j) {
                if (map[room.y + i, room.x + j] == MapType.Mark) {
                    map[room.y + i, room.x + j] = MapType.Floor;
                }
            }
        }
    }

    void ClearAllMarks() {
        for (int i = 0; i != rooms.Count; ++i) {
            ClearRoomMarks(i);
        }
    }

    public bool IsAccessable(int x, int y) {
        if (x < 0 || x >= MAP_WIDTH || 
            y < 0 || y >= MAP_HEIGHT || 
            map[y, x] != MapType.Floor) {
            return false;
        }
        return true;
    }

    public int WhichRoom(int x, int y) {
        for (int i = 0; i != rooms.Count; ++i) {
            if (rooms[i].x <= x && rooms[i].x + rooms[i].w > x && 
                rooms[i].y <= y && rooms[i].y + rooms[i].h > y) {
                return i;
            }
        }
        return -1;
    }

    public int WhichRoom(Vector3 pos) {
        int x = (int)(pos.x);
        int y = (int)(pos.z);
        return WhichRoom(x, y);
    }

    public class MySort : IComparer<int> {
        public int Compare(int x, int y) {
            int result = (int)x - (int)y;
            if (result == 0) {
                result = -1;
            }
            return result;
        }
    }

    private int[,] direction = new int[4, 2] {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    // use Dijkstra to find path
    public List<MapPoint> FindPath(MapPoint origin, MapPoint dest) {
        List<MapPoint> path = new List<MapPoint>();
        if (origin.x < 0 || origin.x >= MAP_WIDTH || 
            origin.y < 0 || origin.y >= MAP_HEIGHT) {
            // Debug.Log("MapGenerator FindPath: Out of range");
            return path;
        }
        int roomID = WhichRoom(origin.x, origin.y);
        if (roomID == -1) {
            return path;
        }

        // compute the origin and destination point in room position
        MapPoint originInRoom = new MapPoint(origin.x - rooms[roomID].x, origin.y - rooms[roomID].y);
        MapPoint destInRoom = new MapPoint(dest.x - rooms[roomID].x, dest.y - rooms[roomID].y);
        int width = rooms[roomID].w;
        int height = rooms[roomID].h;
        // record the weight value of a point
        int[,] pointWeight = new int[height, width];
        for (int i = 0; i != height; ++i) {
            for (int j = 0; j != width; ++j) {
                pointWeight[i, j] = 65535;
            }
        }
        pointWeight[originInRoom.y, originInRoom.x] = 0;
        // record last point, used to build path
        MapPoint[,] lastPoints = new MapPoint[height, width];
        lastPoints[originInRoom.y, originInRoom.x] = originInRoom;
        // mark origin point
        map[origin.y, origin.x] = MapType.Mark;

        SortedList<int, MapPoint> open = new SortedList<int, MapPoint>(20, new MySort());
        List<MapPoint> close = new List<MapPoint>(20);

        open.Add(0, originInRoom);
        bool found = false;
        while (open.Count != 0) {
            MapPoint curPoint = new MapPoint(open.Values[0].x, open.Values[0].y);
            close.Add(open.Values[0]);
            open.RemoveAt(0);
            if (curPoint.x == destInRoom.x && curPoint.y == destInRoom.y) {
                found = true;
                break;
            }
            for (int i = 0; i != 4; ++i) {
                int newX = curPoint.x + direction[i, 0];
                int newY = curPoint.y + direction[i, 1];
                if (IsAccessable(newX + rooms[roomID].x, newY + rooms[roomID].y)) {
                    // mark new point
                    map[newY + rooms[roomID].y, newX + rooms[roomID].x] = MapType.Mark;
                    // compute new point weight
                    int weight = pointWeight[curPoint.y, curPoint.x] + 1;
                    if (weight < pointWeight[newY, newX]) {
                        pointWeight[newY, newX] = weight;
                        lastPoints[newY, newX] = curPoint;
                    }
                    open.Add(pointWeight[newY, newX], new MapPoint(newX, newY));
                }
            }
        }

        // build path
        if (found) {
            List<MapPoint> steps = new List<MapPoint>();
            steps.Add(close[close.Count-1]);
            MapPoint stepPoint = steps[0];
            while (stepPoint.x != originInRoom.x || stepPoint.y != originInRoom.y) {
                steps.Add(lastPoints[stepPoint.y, stepPoint.x]);
                stepPoint = steps[steps.Count - 1];
            }
            for (int i = steps.Count - 1; i > 0; --i) {
                path.Add(new MapPoint(steps[i - 1].x - steps[i].x, steps[i - 1].y - steps[i].y));
            }
        }

        // Debug.Log("==========  origin: " + originInRoom.x + "," + originInRoom.y + " dest: " + destInRoom.x + "," + destInRoom.y);
        // for (int i = 0; i != path.Count; ++i) {
        //     Debug.Log("=============  " + path[i].x + "," + path[i].y);
        // }

        // remember to clean marks
        ClearRoomMarks(roomID);
        return path;
    }
}