using UnityEngine;
using System.Collections;

public delegate void CallFuncDelegate(Object obj);

public class ActionCallFunc : Action {
    private float timer = 0.0f;
    private float triggerTime;
    private CallFuncDelegate delFunc;
    private Object data;

    public ActionCallFunc(float t, CallFuncDelegate func, Object d = null) {
        name = "CallFunc";
        triggerTime = t;
        delFunc = func;
        data = d;
    }

    public override void OnEnter() {
        // Debug.Log("CallFunc OnEnter");
    }

    public override void Update() {
        timer += Time.deltaTime;
        if (timer >= triggerTime) {
            delFunc(data);
            actionMachine.RemoveAction();
        }
    }

    public override void OnExit() {
        // Debug.Log("CallFunc OnExit");
    }
}