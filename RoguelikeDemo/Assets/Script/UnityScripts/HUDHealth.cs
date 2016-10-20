using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class HUDHealth : MonoBehaviour {
    private Text healthText;

    // Use this for initialization
    void Start () {
        healthText = GetComponent<Text>();
    }
    
    // Update is called once per frame
    void Update () {
        PlayerScript player = (PlayerScript)GameKernel.actorManager.playerActor;
        if (player != null) {
            healthText.text = "Health: " + player.health;
        }
    }
}
