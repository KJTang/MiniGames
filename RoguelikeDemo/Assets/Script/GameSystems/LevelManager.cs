using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class LevelManager : IGameSystem {
    public Level curLevel = null;

    private bool isChangingLevel = false;
    private int timer = 0;

    public void Init() {
        // Debug.Log("LevelManager Init");
    }

    public void Update() {
        if (curLevel != null) {
            curLevel.Update();
        }
        if (isChangingLevel) {
            ++timer;
            // wait 1 frame, cause SceneManager.LoadScene() take effect in next frame
            if (timer > 1) {
                isChangingLevel = false;
                timer = 0;
                // reset input message
                GameKernel.inputManager.Reset();
                curLevel.OnEnter();
            }
        }
    }

    public void Destroy() {
        // Debug.Log("LevelManager Destroy");
    }

    public void ChangeLevel(Level l) {
        // Debug.Log("LevelManager ChangeLevel");
        if (curLevel != null) {
            curLevel.OnExit();
            curLevel = null;
        }
        curLevel = l;
        curLevel.OnLoad();
        isChangingLevel = true;
    }
}