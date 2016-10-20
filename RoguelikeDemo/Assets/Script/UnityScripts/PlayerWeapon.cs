using UnityEngine;
using System.Collections;

public class HurtByPlayerEventData : EventData {
    public GameObject hurtObject;
}

public class PlayerWeapon : MonoBehaviour {
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
        HurtByPlayerEventData data = new HurtByPlayerEventData();
        data.hurtObject = other.gameObject;
        GameKernel.eventManager.DispatchEvent("HurtByPlayer", data);
    }

    // void OnTriggerStay(Collider other) {}

    // void OnTriggerExit(Collider other) {}
}
