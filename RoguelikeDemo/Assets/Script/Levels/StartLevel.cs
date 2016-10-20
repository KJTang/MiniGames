using UnityEngine;
using UnityEngine.SceneManagement;
using System.Collections;

public class StartLevel : Level {
    public StartLevel() {
        name = "StartLevel";
    }

    public override void OnLoad() {
        SceneManager.LoadScene("Scene/StartLevel");
    }

    public override void OnEnter() {}

    public override void Update() {}
    
    public override void OnExit() {}

    public void ChangeToLevel(int level) {
        switch (level) {
            case 0: {
                GameKernel.levelManager.ChangeLevel(new AutoGenLevel());
                break;
            }
            case 1: {
                // Debug.Log("Quit");
                UnityEngine.Application.Quit();
                break;
            }
            default: {
                // Debug.Log("Unknown Level");
                break;
            }
        }
    }
}