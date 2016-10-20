using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class HUDLevel : MonoBehaviour {
    private Text levelText;

	// Use this for initialization
	void Start () {
        levelText = GetComponent<Text>();
	}
	
	// Update is called once per frame
	void Update () {
        Level curLevel = GameKernel.levelManager.curLevel;
        if (curLevel != null && curLevel.name == "AutoGenLevel") {
            levelText.text = "Level: " + ((AutoGenLevel)curLevel).levelCount;
        }
	}
}
