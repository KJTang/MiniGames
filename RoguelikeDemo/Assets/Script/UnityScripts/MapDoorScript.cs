using UnityEngine;
using System;
using System.Collections;

public class MapDoorScript : MonoBehaviour {
    AudioSource audio;

	// Use this for initialization
	void Start () {
        audio = GetComponent<AudioSource>();
	}

    void OnCollisionEnter(Collision collision) {
        if (collision.gameObject.name == "PlayerPrefab(Clone)") {
            if (Math.Abs(collision.gameObject.transform.position.z - this.gameObject.transform.position.z) <= 0.3) {
                PlayerScript player = (PlayerScript)GameKernel.actorManager.playerActor;
                player.isPlayerTransferring = true;
                audio.Play();
            }
        }
    }
}
