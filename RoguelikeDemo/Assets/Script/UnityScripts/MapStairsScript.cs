using UnityEngine;
using System;
using System.Collections;

public class MapStairsScript : MonoBehaviour {
	// Use this for initialization
	void Start () {}

    void OnTriggerEnter(Collider other) {
        if (other.gameObject.name == "PlayerPrefab(Clone)") {
            GameKernel.eventManager.DispatchEvent("Level Pass", null);
        }
    }
}
