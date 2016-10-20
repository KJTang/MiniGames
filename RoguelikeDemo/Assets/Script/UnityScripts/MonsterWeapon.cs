using UnityEngine;
using System.Collections;

public class HurtByMonsterEventData : EventData {
    public GameObject monster;
}

public class MonsterWeapon : MonoBehaviour {
    BoxCollider box;

    void Awake() {
        box = gameObject.GetComponent<BoxCollider>();
        box.enabled = false;
    }

    void OnEnable() {
        box.enabled = true; 
    }

    void OnDisable() {
        box.enabled = false;
    }

    void OnTriggerEnter(Collider other) {
        HurtByMonsterEventData data = new HurtByMonsterEventData();
        data.monster = gameObject.transform.parent.gameObject;
        GameKernel.eventManager.DispatchEvent("HurtByMonster", data);
        this.enabled = false;
    }
}
