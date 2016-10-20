using UnityEngine;
using UnityEngine.Assertions;
using System.Collections;

public class ActionMoveBy : Action {
    private Vector3 offset;
    private Vector3 destination;
    private float speed;
    private GameObject gameObject;

    public ActionMoveBy(Vector3 o, float s) {
        name = "MoveBy";
        offset = o;
        speed = s;
    }

    public override void OnEnter() {
        // Debug.Log("ActionMoveBy: OnEnter");
        gameObject = actionMachine.actor.gameObject;
        destination = gameObject.transform.position + offset;
        Assert.IsFalse(gameObject.transform.position == destination);
    }
    public override void Update() {
        // Debug.Log("ActionMoveBy: " + gameObject.transform.position + destination);
        if (gameObject.transform.position == destination) {
            actionMachine.RemoveAction();
        } else {
            float step = speed * Time.deltaTime;
            gameObject.transform.position = Vector3.MoveTowards(gameObject.transform.position, destination, step);
        }
    }
    public override void OnExit() {
        // Debug.Log("ActionMoveBy: OnExit");
    }
}