using UnityEngine;
using UnityEngine.SceneManagement;
using System.Collections;
using System.Collections.Generic;

public class AutoGenLevel : Level, IEventListener {
    public int levelCount = 0;

    private GameObject playerPrefab;
    private GameObject monsterPrefab;
    private GameObject mapFloorPrefab; 
    private GameObject mapWallHorPrefab;
    private GameObject mapWallVerPrefab;
    private GameObject mapDoorPrefab;
    private GameObject mapStairsPrefab;
    private GameObject itemGoldPrefab;
    private GameObject itemHealPrefab;

    public MapGenerator mapGenerator;

    public AutoGenLevel() {
        name = "AutoGenLevel";
    }

    public override void OnLoad() {
        // Debug.Log("AutoGenLevel: OnLoad");

        mapGenerator = new MapGenerator();
        mapGenerator.Init();
        mapGenerator.GenerateMap(5);

        ReadLevelData();
        LoadLevelResources();
    }

    public override void OnEnter() {
        // Debug.Log("AutoGenLevel: OnEnter");
        CreateMap();
        CreatePlayer();
        CreateMonster();

        GameKernel.eventManager.AddEventListener("Level Pass", this);
        GameKernel.eventManager.AddEventListener("Level Lose", this);
        // reset level -- used for debugging
        GameKernel.eventManager.AddEventListener("Reset", this);
    }

    public override void Update() {
        // Debug.Log("AutoGenLevel: Update");
    }

    public override void OnExit() {
        // Debug.Log("AutoGenLevel: OnExit");
        GameKernel.inputManager.Reset();
        // remove event listener
        GameKernel.eventManager.RemoveEventListener("Level Pass", this);
        GameKernel.eventManager.RemoveEventListener("Level Lose", this);
        GameKernel.eventManager.RemoveEventListener("Reset", this);
    }

    void ReadLevelData() {
        GameData data = GameKernel.fileManager.FastLoadData("gamedata.xml");
        levelCount = data.level;
    }

    void LoadLevelResources() {
        // scene
        SceneManager.LoadScene("Scene/AutoGenLevel");
        // player
        playerPrefab = GameKernel.resourceManager.LoadPrefab("Player", "Prefabs/PlayerPrefab");
        // monster
        monsterPrefab = GameKernel.resourceManager.LoadPrefab("Monster", "Prefabs/MonsterPrefab");
        // map
        mapFloorPrefab = GameKernel.resourceManager.LoadPrefab("MapFloor", "Prefabs/MapFloor");
        mapWallHorPrefab = GameKernel.resourceManager.LoadPrefab("MapWallHor", "Prefabs/MapWallHor");
        mapWallVerPrefab = GameKernel.resourceManager.LoadPrefab("MapWall", "Prefabs/MapWallVer");
        mapDoorPrefab = GameKernel.resourceManager.LoadPrefab("MapDoor", "Prefabs/MapDoor");
        mapStairsPrefab = GameKernel.resourceManager.LoadPrefab("MapStairs", "Prefabs/MapStairs");
        // item
        itemGoldPrefab = GameKernel.resourceManager.LoadPrefab("ItemGold", "Prefabs/ItemGold");
        itemHealPrefab = GameKernel.resourceManager.LoadPrefab("ItemHeal", "Prefabs/ItemHeal");
    }

    void CreateMap() {
        for (int i = 0; i != MapGenerator.MAP_HEIGHT; ++i) {
            for (int j = 0; j != MapGenerator.MAP_WIDTH; ++j) {
                switch (mapGenerator.map[j, i]) {
                    case MapType.WallVertical: {
                        GameObject wall = Object.Instantiate(mapWallVerPrefab) as GameObject;
                        wall.transform.position = new Vector3(i, 0.0f, j);
                        goto case MapType.Floor;
                    }
                    case MapType.WallHorizontal: {
                        GameObject wall = Object.Instantiate(mapWallHorPrefab) as GameObject;
                        wall.transform.position = new Vector3(i, 0.0f, j);
                        goto case MapType.Floor;
                    }
                    case MapType.Door: {
                        GameObject door = Object.Instantiate(mapDoorPrefab) as GameObject;
                        door.transform.position = new Vector3(i, 0.0f, j);
                        goto case MapType.Floor;
                    }
                    case MapType.DoorOut: {
                        goto case MapType.Floor;
                    }
                    case MapType.ItemGold: {
                        GameObject gold = Object.Instantiate(itemGoldPrefab) as GameObject;
                        gold.transform.position = new Vector3(i, 0.0f, j);
                        goto case MapType.Floor;
                    }
                    case MapType.ItemHeal: {
                        GameObject heal = Object.Instantiate(itemHealPrefab) as GameObject;
                        heal.transform.position = new Vector3(i, 0.0f, j);
                        goto case MapType.Floor;
                    }
                    case MapType.Stairs: {
                        GameObject stairs = Object.Instantiate(mapStairsPrefab) as GameObject;
                        stairs.transform.position = new Vector3(i, -1.0f, j);
                        // goto case MapType.Floor;
                        break;
                    }
                    case MapType.Floor: {
                        GameObject floor = Object.Instantiate(mapFloorPrefab) as GameObject;
                        floor.transform.position = new Vector3(i, 0.0f, j);
                        break;
                    }
                }
            }
        }
    }

    void CreatePlayer() {
        GameKernel.actorManager.CreatePlayer(playerPrefab, new Vector3(mapGenerator.playerPosX, 0.5f, mapGenerator.playerPosY));
    }

    void CreateMonster() {
        for (int i = 0; i != mapGenerator.monsters.Count; ++i) {
            GameKernel.actorManager.CreateMonster(monsterPrefab, new Vector3(mapGenerator.monsters[i].x, 0.5f, mapGenerator.monsters[i].y));
        }
    }

    public void OnEvent(string eventName, EventData eventData) {
        if (eventName == "Level Pass") {
            PlayerScript player = (PlayerScript)GameKernel.actorManager.playerActor;
            GameData data = new GameData(levelCount + 1, player.health, player.attack, player.gold);
            GameKernel.fileManager.FastSaveData("gamedata.xml", data);
            GameKernel.levelManager.ChangeLevel(new AutoGenLevel());
        } else if (eventName == "Level Lose" || eventName == "Reset") {
            GameKernel.fileManager.DeleteFile("gamedata.xml");
            GameKernel.levelManager.ChangeLevel(new StartLevel());
        }
    }
}