using UnityEngine;
using System.Collections;

public class CameraFollow : MonoBehaviour {
    public Vector3 distance = new Vector3(0.0f, 10.0f, 0.0f);

    // Use this for initialization
    void Start () {
	}
	
	// Update is called once per frame
	void Update () {
        if (GameKernel.actorManager.playerGameObj != null) {
            gameObject.transform.position = GameKernel.actorManager.playerGameObj.transform.position + distance;
        }
	}
}
