using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class PlayerIdleState : State {
    PlayerScript actor;
    Rigidbody actorBody;

    public PlayerIdleState() {
        name = "Idle";
    }
    public override void OnEnter() {
        // Debug.Log("Idle OnEnter");
        actor = (PlayerScript)stateMachine.actor;
        actorBody = actor.gameObject.GetComponent<Rigidbody>();
        actor.playerAnimation.CrossFade("Wait");
        actorBody.velocity = new Vector3(0.0f, 0.0f, 0.0f);
    }
    public override void Update() {
        // dead
        if (actor.health <= 0) {
            stateMachine.ChangeState("Dead");
            return;
        }
        // hurt
        if (actor.isPlayerHurt) {
            stateMachine.ChangeState("Hurt");
            return;
        }
        // transfer
        if (actor.isPlayerTransferring) {
            stateMachine.ChangeState("Transfer");
            return;
        }
        // attack
        if (GameKernel.inputManager.isPlayerAttack == true) {
            stateMachine.ChangeState("Attack");
            return;
        }
        // move
        if (GameKernel.inputManager.isPlayerMove == true) {
            stateMachine.ChangeState("Move");
            return;
        }
    }
    public override void OnExit() {
        // Debug.Log("Idle OnExit");
    }
}

public class PlayerMoveState : State {
    ActionMachine actionMachine;
    PlayerScript actor;
    Rigidbody actorBody;
    public PlayerMoveState() {
        name = "Move";
    }
    public override void OnEnter() {
        // Debug.Log("Move OnEnter");
        actor = (PlayerScript)stateMachine.actor;
        actorBody = actor.gameObject.GetComponent<Rigidbody>();
        actor.playerAnimation.CrossFade("Walk");
        actionMachine = actor.actionMachine;
        AddMoveAction();
    }
    public override void Update() {
        // dead
        if (actor.health <= 0) {
            stateMachine.ChangeState("Dead");
            return;
        }
        // hurt
        if (actor.isPlayerHurt) {
            stateMachine.ChangeState("Hurt");
            return;
        }
        // transfer
        if (actor.isPlayerTransferring) {
            stateMachine.ChangeState("Transfer");
            return;
        }
        if (actionMachine.GetActionCount() == 0) {
            // attack 
            if (GameKernel.inputManager.isPlayerAttack == true) {
                actionMachine.ClearActions();
                stateMachine.ChangeState("Attack");
                return;
            }
            // move
            if (GameKernel.inputManager.isPlayerMove == false) {
                stateMachine.ChangeState("Idle");
                return;
            } else {
                AddMoveAction();
            }
        }
    }
    public override void OnExit() {
        // Debug.Log("Move OnExit");
        actorBody.velocity = new Vector3(0.0f, 0.0f, 0.0f);
        actor.actionMachine.ClearActions();
    }

    void AddMoveAction() {
        switch (GameKernel.inputManager.moveDirection) {
            case Direction.Up: {
                actionMachine.AddAction(new ActionRotateTo(new Vector3(0.0f, 0.0f, 0.0f)));
                if (GameKernel.inputManager.curDirection == Direction.Up) {
                    actorBody.velocity = new Vector3(0.0f, 0.0f, 1.0f) * actor.speed;
                } else {
                    GameKernel.inputManager.curDirection = Direction.Up;
                }
                break;
            }
            case Direction.Left: {
                actionMachine.AddAction(new ActionRotateTo(new Vector3(0.0f, -90.0f, 0.0f)));
                if (GameKernel.inputManager.curDirection == Direction.Left) {
                    actorBody.velocity = new Vector3(-1.0f, 0.0f, 0.0f) * actor.speed;
                } else {
                    GameKernel.inputManager.curDirection = Direction.Left;
                }
                break;
            }
            case Direction.Down: {
                actionMachine.AddAction(new ActionRotateTo(new Vector3(0.0f, 180.0f, 0.0f)));
                if (GameKernel.inputManager.curDirection == Direction.Down) {
                    actorBody.velocity = new Vector3(0.0f, 0.0f, -1.0f) * actor.speed;
                } else {
                    GameKernel.inputManager.curDirection = Direction.Down;
                }
                break;
            }
            case Direction.Right: {
                actionMachine.AddAction(new ActionRotateTo(new Vector3(0.0f, 90.0f, 0.0f)));
                if (GameKernel.inputManager.curDirection == Direction.Right) {
                    actorBody.velocity = new Vector3(1.0f, 0.0f, 0.0f) * actor.speed;
                } else {
                    GameKernel.inputManager.curDirection = Direction.Right;
                }
                break;
            }
        }
    }
}

public class PlayerAttackState : State {
    private PlayerScript actor;
    private PlayerWeapon weapon;

    public PlayerAttackState() {
        name = "Attack";
    }
    public override void OnEnter() {
        // Debug.Log("Attack OnEnter");
        actor = (PlayerScript)stateMachine.actor;
        AudioClip audio = Resources.Load("Sounds/player_attack") as AudioClip;
        actor.audioSource.PlayOneShot(audio);
        actor.playerAnimation.CrossFade("Attack");
        weapon = actor.gameObject.GetComponentInChildren<PlayerWeapon>();
        weapon.enabled = true;
    }
    public override void Update() {
        // dead
        if (actor.health <= 0) {
            stateMachine.ChangeState("Dead");
            return;
        }
        // hurt
        if (actor.isPlayerHurt) {
            stateMachine.ChangeState("Hurt");
            return;
        }
        // Debug.Log("Attack Update");
        if (actor.playerAnimation.IsPlaying("Attack") == false) {
            stateMachine.ChangeState("Idle");
        }
    }
    public override void OnExit() {
        // Debug.Log("Attack OnExit");
        weapon.enabled = false;
    }
}

public class PlayerHurtState : State {
    private Actor monster;
    private PlayerScript actor;

    public PlayerHurtState() {
        name = "Hurt";
    }
    public override void OnEnter() {
        // Debug.Log("Hurt OnEnter");
        actor = (PlayerScript)stateMachine.actor;
        monster = actor.hurtMonster;
        AudioClip audio = Resources.Load("Sounds/player_hit") as AudioClip;
        actor.audioSource.PlayOneShot(audio);
        actor.playerAnimation.CrossFade("Damage");
        actor.actionMachine.ClearActions();
        actor.health -= monster.attack;
    }
    public override void Update() {
        if (actor.health <= 0) {
            stateMachine.ChangeState("Dead");
            return;
        }
        if (!actor.playerAnimation.IsPlaying("Damage")) {
            stateMachine.ChangeState("Idle");
            return;
        }
    }
    public override void OnExit() {
        // Debug.Log("Hurt OnExit");
        actor.isPlayerHurt = false;
    }
}

public class PlayerDeadState : State {
    private PlayerScript actor;
    private float timer = 0.0f;

    public PlayerDeadState() {
        name = "Dead";
    }
    public override void OnEnter() {
        // Debug.Log("Dead OnEnter");
        actor = (PlayerScript)stateMachine.actor;
        actor.isPlayerDead = true;
        actor.playerAnimation.CrossFade("Dead");
        AudioClip audio = Resources.Load("Sounds/player_dead") as AudioClip;
        actor.audioSource.PlayOneShot(audio);
    }
    public override void Update() {
        timer += Time.deltaTime;
        if (timer >= 3.0f) {
            GameKernel.eventManager.DispatchEvent("Level Lose", null);
        }
    }
    public override void OnExit() {
        // Debug.Log("Dead OnExit");
    }
}

public class PlayerTransferState : State {
    private PlayerScript actor;

    public PlayerTransferState() {
        name = "Transfer";
    }
    public override void OnEnter() {
        // Debug.Log("Transfer OnEnter");
        actor = (PlayerScript)stateMachine.actor;
        // find next room
        MapGenerator mapGenerator = ((AutoGenLevel)GameKernel.levelManager.curLevel).mapGenerator;
        int roomID = mapGenerator.WhichRoom(actor.gameObject.transform.position);
        UnityEngine.Assertions.Assert.IsTrue(roomID != -1);
        int nextRoomID = (roomID + 1) % mapGenerator.rooms.Count;
        RoomInfo room = mapGenerator.rooms[nextRoomID];
        // find transfer position
        int transferX = 0, transferY = 0;
        for (int i = 0; i != room.h; ++i) {
            for (int j = 0; j != room.w; ++j) {
                if (mapGenerator.map[room.y + i, room.x + j] == MapType.DoorOut) {
                    transferX = room.x + j;
                    transferY = room.y + i;
                    break;
                }
            }
        }
        // transfer player
        CallFuncDelegate before = obj => { 
            PlayerScript actorInFunc = (PlayerScript)GameKernel.actorManager.playerActor;
            // Debug.Log("==========  before: " + actorInFunc.gameObject.transform.position);
            actorInFunc.gameObject.GetComponent<BoxCollider>().enabled = false;
            actorInFunc.gameObject.transform.localScale = new Vector3(0.0f, 0.0f, 0.0f);
        };
        CallFuncDelegate after = obj => { 
            PlayerScript actorInFunc = (PlayerScript)GameKernel.actorManager.playerActor;
            // Debug.Log("==========  after: " + actorInFunc.gameObject.transform.position);
            actorInFunc.gameObject.GetComponent<BoxCollider>().enabled = true;
            actorInFunc.gameObject.transform.localScale = new Vector3(0.015f, 0.015f, 0.015f);
        };
        actor.actionMachine.ClearActions();
        actor.actionMachine.AddAction(new ActionCallFunc(0.0f, before));
        actor.actionMachine.AddAction(new ActionMoveTo(actor.gameObject.transform.position + new Vector3(0.0f, 3.0f, 0.0f), 10.0f));
        actor.actionMachine.AddAction(new ActionMoveTo(new Vector3(transferX, 3.5f, transferY), 10.0f));
        actor.actionMachine.AddAction(new ActionMoveTo(new Vector3(transferX, 0.5f, transferY), 10.0f));
        actor.actionMachine.AddAction(new ActionRotateTo(new Vector3(0.0f, 90.0f, 0.0f)));
        actor.actionMachine.AddAction(new ActionCallFunc(0.0f, after));
    }

    public override void Update() {
        // Debug.Log("============ Count: " + actor.actionMachine.GetActionCount());
        if (actor.actionMachine.GetActionCount() == 0) {
            actor.isPlayerTransferring = false;
            stateMachine.ChangeState("Idle");
        }
    }

    public override void OnExit() {
        // Debug.Log("Transfer OnExit");
    }
}