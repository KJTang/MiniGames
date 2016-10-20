﻿using UnityEngine;
using System.Collections;

public class QuitButton : MonoBehaviour {
    public void ButtonClick(GameObject button) {
        LevelManager levelManager = GameKernel.levelManager;
        StartLevel start = (StartLevel)levelManager.curLevel;
        start.ChangeToLevel(1);
    }
}