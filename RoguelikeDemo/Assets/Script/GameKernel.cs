using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class GameKernel : MonoBehaviour {
    public static LevelManager levelManager = new LevelManager();
    public static ActorManager actorManager = new ActorManager();
    public static EventManager eventManager = new EventManager();
    public static InputManager inputManager = new InputManager();
    public static ResourceManager resourceManager = new ResourceManager();
    public static FileManager fileManager = new FileManager();

    List<IGameSystem> gameSystems = new List<IGameSystem>();

    void Awake() {
        // won't destroy after change scene
        DontDestroyOnLoad(transform.gameObject);

        gameSystems.Add(levelManager);
        gameSystems.Add(actorManager);
        gameSystems.Add(eventManager);
        gameSystems.Add(inputManager);
        gameSystems.Add(resourceManager);
        gameSystems.Add(fileManager);

        for (int i = 0; i != gameSystems.Count; ++i) {
            gameSystems[i].Init();
        }
    }

	void Start() {
        Level startLevel = new StartLevel();
        levelManager.ChangeLevel(startLevel);
	}
	
	void Update() {
        eventManager.Update();
        actorManager.Update();
        levelManager.Update();
        inputManager.Update();
        resourceManager.Update();
        fileManager.Update();
    }

    void OnDestroy() {
        for (int i = 0; i != gameSystems.Count; ++i) {
            gameSystems[i].Destroy();
            gameSystems[i] = null;
        }
    }
}
