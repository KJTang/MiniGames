using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Actor : MonoBehaviour {
    public int health;
    public int attack;
    public int defence;
    public float speed;
    public float rotateSpeed;
    public float attackSpeed;
    public bool isDead;
}

public class ActorManager : IGameSystem {
    public GameObject playerGameObj = null;
    public List<GameObject> monsterGameObjs = new List<GameObject>();

    public Actor playerActor = null;
    public List<Actor> monsterActors = new List<Actor>();

    public void Init() {
        // Debug.Log("ActorManager Init");
    }

    public void Update() {
        // Debug.Log("ActorManager Update");
    }

    public void Destroy() {
        // Debug.Log("ActorManager Destroy");
    }

    public GameObject CreatePlayer(GameObject prefab, Vector3 pos) {
        // Debug.Log("ActorManager CreatePlayer");
        playerGameObj = Object.Instantiate(prefab) as GameObject;
        playerGameObj.transform.position = pos;
        
        PlayerScript playerScript = playerGameObj.GetComponent<PlayerScript>();

        GameData data = GameKernel.fileManager.FastLoadData("gamedata.xml");
        playerScript.health = data.health;
        playerScript.attack = data.attack;
        playerScript.gold = data.gold;

        playerActor = playerScript;
        return playerGameObj;
    }

    public GameObject CreateMonster(GameObject prefab, Vector3 pos) {
        GameObject monsterGameObj = Object.Instantiate(prefab) as GameObject;
        monsterGameObjs.Add(monsterGameObj);
        monsterGameObj.transform.position = pos;

        MonsterScript monsterScript = monsterGameObj.GetComponent<MonsterScript>();
        monsterActors.Add(monsterScript);
        return monsterGameObj;
    }
}