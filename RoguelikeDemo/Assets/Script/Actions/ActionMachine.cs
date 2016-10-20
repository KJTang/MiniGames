using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Action {
    public string name = "default";
    public ActionMachine actionMachine;

    public virtual void OnEnter() {}
    public virtual void Update() {}
    public virtual void OnExit() {}
}

public class ActionMachine {
    public Actor actor;
    private Queue<Action> actions = new Queue<Action>();
    
    public void Init() {}

    public void AddAction(Action ac) {
        ac.actionMachine = this;
        actions.Enqueue(ac);
        if (actions.Count == 1) {
            ac.OnEnter();
        }
    }

    public void RemoveAction() {
        if (actions.Count != 0) {
            Action ac = actions.Dequeue();
            ac.OnExit();
            ac = null;
        }
        if (actions.Count != 0) {
            actions.Peek().OnEnter();
        }
    }

    public void ClearActions() {
        actions.Clear();
    }

    public int GetActionCount() {
        return actions.Count;
    }

    public void Update() {
        if (actions.Count != 0) {
            actions.Peek().Update();
        }
    }

    public void Destroy() {}
}