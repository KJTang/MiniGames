using UnityEngine;
using System.Collections;

public class ActionMoveTo : Action {
    private Vector3 destination;
    private float speed;
    private GameObject gameObject;

    public ActionMoveTo(Vector3 d, float s) {
        name = "MoveTo";
        speed = s;
        destination = d;
    }

    public override void OnEnter() {
        // Debug.Log("ActionMoveTo: OnEnter");
        gameObject = actionMachine.actor.gameObject;
    }
    public override void Update() {
        // Debug.Log("ActionMoveTo: " + gameObject.transform.position + destination);
        if (gameObject.transform.position == destination) {
            actionMachine.RemoveAction();
        } else {
            float step = speed * Time.deltaTime;
            gameObject.transform.position = Vector3.MoveTowards(gameObject.transform.position, destination, step);
        }
    }
    public override void OnExit() {
        // Debug.Log("ActionMoveTo: OnExit");
    }
}