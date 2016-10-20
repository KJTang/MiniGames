using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public enum Direction {
    Up, Down, Left, Right
};

public class InputManager : IGameSystem {
    public bool isPlayerMove = false;
    private int moveBtnCount = 0;
    public bool isPlayerAttack = false;
    public Direction moveDirection;
    public Direction curDirection;

    public void Init() {
        // Debug.Log("InputManager: Init");
        moveDirection = curDirection = Direction.Up;
    }

    public void Reset() {
        isPlayerMove = false;
        moveBtnCount = 0;
        isPlayerAttack = false;
        moveDirection = curDirection = Direction.Up;
    }

    public void Update() {
        // Reset -- used for debug, when pressed esc, change level to start level
        if (Input.GetKeyDown(KeyCode.Escape)) {
            GameKernel.eventManager.DispatchEvent("Reset", null);
        }
        // Attack
        if (Input.GetKeyDown(KeyCode.Mouse0)) {
            isPlayerAttack = true;
        }
        if (Input.GetKeyUp(KeyCode.Mouse0)) {
            isPlayerAttack = false;
        }
        // Move
        if (Input.GetKeyDown(KeyCode.W)) {
            moveDirection = Direction.Up;
            ++moveBtnCount;
            isPlayerMove = true;
        } else if (Input.GetKeyDown(KeyCode.A)) {
            moveDirection = Direction.Left;
            ++moveBtnCount;
            isPlayerMove = true;
        } else if (Input.GetKeyDown(KeyCode.S)) {
            moveDirection = Direction.Down;
            ++moveBtnCount;
            isPlayerMove = true;
        } else if (Input.GetKeyDown(KeyCode.D)) {
            moveDirection = Direction.Right;
            ++moveBtnCount;
            isPlayerMove = true;
        }
        if (Input.GetKeyUp(KeyCode.W) || Input.GetKeyUp(KeyCode.A) || Input.GetKeyUp(KeyCode.S) || Input.GetKeyUp(KeyCode.D)) {
            --moveBtnCount;
            if (moveBtnCount == 0) {
                isPlayerMove = false;
            }
        }
    }

    public void Destroy() {
        // Debug.Log("InputManager: Destroy");
    }

}