using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Level {
    public string name;
    public Level() {
        name = "BaseLevel";
    }

    public virtual void OnLoad() {
        // Debug.Log("BaseLevel: OnLoad");
    }
    public virtual void OnEnter() {
        // Debug.Log("BaseLevel: OnEnter");
    }
    public virtual void Update() {
        // Debug.Log("BaseLevel: Update");
    }
    public virtual void OnExit() {
        // Debug.Log("BaseLevel: OnExit");
    }
}