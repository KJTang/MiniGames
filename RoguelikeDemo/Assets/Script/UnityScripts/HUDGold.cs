using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class HUDGold : MonoBehaviour {
    private Text goldText;

    // Use this for initialization
    void Start () {
        goldText = GetComponent<Text>();
    }
    
    // Update is called once per frame
    void Update () {
        PlayerScript player = (PlayerScript)GameKernel.actorManager.playerActor;
        if (player != null) {
            goldText.text = "Gold: " + player.gold;
        }
    }
}
