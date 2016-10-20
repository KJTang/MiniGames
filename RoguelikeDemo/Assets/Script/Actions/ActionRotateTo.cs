using UnityEngine;
using System.Collections;

public class ActionRotateTo : Action {
    private Quaternion targetRotation;
    private float rotateSpeed;
    private GameObject gameObject;

    public ActionRotateTo(Vector3 direction, float s = 1000.0f) {
        name = "RotateTo";
        targetRotation = Quaternion.Euler(direction.x, direction.y, direction.z);
        rotateSpeed = s;
    }

    public override void OnEnter() {
        // Debug.Log("ActionRotateTo: OnEnter");
        gameObject = actionMachine.actor.gameObject;
    }
    public override void Update() {
        if (gameObject.transform.rotation == targetRotation) {
            actionMachine.RemoveAction();
        } else {
            float step = rotateSpeed * Time.deltaTime;
            gameObject.transform.rotation = Quaternion.RotateTowards(gameObject.transform.rotation, targetRotation, step);
        }
    }
    public override void OnExit() {
        // Debug.Log("ActionRotateTo: OnExit");
    }
}