using UnityEngine;
using System;
using System.Collections;
using System.Collections.Generic;

public class MonsterIdleState : State {
    public MonsterIdleState() {
        name = "Idle";
    }
    public override void OnEnter() {
        // Debug.Log("Idle OnEnter");
        MonsterScript actor = (MonsterScript)stateMachine.actor;
        actor.monsterAnimation.CrossFade("Wait");
    }
    public override void Update() {
    }
    public override void OnExit() {
        // Debug.Log("Idle OnExit");
    }
}

public class MonsterMoveState : State {
    MonsterScript actor;
    public MonsterMoveState() {
        name = "Move";
    }
    public override void OnEnter() {
        actor = (MonsterScript)stateMachine.actor;
        actor.monsterAnimation.CrossFade("Walk");
        // Debug.Log("Monster Move: OnEnter");
    }
    public override void Update() {}
    public override void OnExit() {
        // Debug.Log("Monster Move: OnExit");
    }
}

public class MonsterPatrolState : State {
    private StateMachine subMachine;
    private MapGenerator mapGenerator;

    private PlayerScript player;
    private MonsterScript monster;
    private int monsterRoom;

    public MonsterPatrolState() {
        name = "Patrol";
        subMachine = new StateMachine();
        subMachine.Init();
        mapGenerator = ((AutoGenLevel)GameKernel.levelManager.curLevel).mapGenerator;
        player = (PlayerScript)GameKernel.actorManager.playerActor;
    }

    public override void OnEnter() {
        // Debug.Log("Monster Patrol: OnEnter");
        monster = (MonsterScript)stateMachine.actor;
        monster.actionMachine.ClearActions();

        subMachine.actor = monster;
        subMachine.AddState(new MonsterIdleState());
        subMachine.AddState(new MonsterMoveState());
        subMachine.ChangeState("Idle");

        monsterRoom = mapGenerator.WhichRoom(monster.gameObject.transform.position);
    }

    public override void Update() {
        if (monster.health <= 0) {
            stateMachine.ChangeState("Dead");
            return;
        }
        if (monster.isHurt) {
            stateMachine.ChangeState("Hurt");
            return;
        }
        if (!player.isPlayerDead) {
            int playerRoom = mapGenerator.WhichRoom(player.gameObject.transform.position);
            if (playerRoom == monsterRoom) {
                if (Vector3.Distance(monster.gameObject.transform.position, player.gameObject.transform.position) < monster.chasingDistance) {
                    stateMachine.ChangeState("Chasing");
                    return;
                }
            }
        }
        subMachine.Update();
    }

    public override void OnExit() {
        // Debug.Log("Monster Patrol: OnExit");
    }
}

public class MonsterChasingState : State {
    private MapGenerator mapGenerator;
    private PlayerScript player;
    private MonsterScript monster;
    private int monsterRoom;

    public MonsterChasingState() {
        name = "Chasing";
        mapGenerator = ((AutoGenLevel)GameKernel.levelManager.curLevel).mapGenerator;
        player = (PlayerScript)GameKernel.actorManager.playerActor;
    }

    public override void OnEnter() {
        // Debug.Log("Monster Chasing: OnEnter");
        monster = (MonsterScript)stateMachine.actor;
        monster.monsterAnimation.CrossFade("Walk");
        monster.actionMachine.ClearActions();
        monsterRoom = mapGenerator.WhichRoom(monster.gameObject.transform.position);
    }

    public override void Update() {
        if (monster.health <= 0) {
            stateMachine.ChangeState("Dead");
            return;
        }
        if (monster.isHurt) {
            stateMachine.ChangeState("Hurt");
            return;
        }
        if (player.isPlayerTransferring) {
            stateMachine.ChangeState("Patrol");
            return;
        }
        if (monster.actionMachine.GetActionCount() == 0) {
            if (monsterRoom == mapGenerator.WhichRoom(player.gameObject.transform.position)) {
                float distance = Vector3.Distance(monster.gameObject.transform.position, player.gameObject.transform.position);
                if (distance >= monster.patrolDistance) {
                    stateMachine.ChangeState("Patrol");
                    return;
                } else if (distance <= monster.attackDistance) {
                    stateMachine.ChangeState("Attack");
                    return;
                } else {
                    List<MapPoint> path = mapGenerator.FindPath(
                        new MapPoint(
                            (int)(monster.gameObject.transform.position.x + 0.5f), 
                            (int)(monster.gameObject.transform.position.z + 0.5f)), 
                        new MapPoint(
                            (int)(player.gameObject.transform.position.x + 0.5f), 
                            (int)(player.gameObject.transform.position.z + 0.5f)) 
                    );
                    for (int i = 0; i < 1 && i < path.Count; ++i) {
                        if (path[i].x == -1) {
                            monster.actionMachine.AddAction(new ActionRotateTo(new Vector3(0.0f, -90.0f, 0.0f)));
                        } else if (path[i].x == 1) {
                            monster.actionMachine.AddAction(new ActionRotateTo(new Vector3(0.0f, 90.0f, 0.0f)));
                        } else if (path[i].y == -1) {
                            monster.actionMachine.AddAction(new ActionRotateTo(new Vector3(0.0f, 180.0f, 0.0f)));
                        } else if (path[i].y == 1) {
                            monster.actionMachine.AddAction(new ActionRotateTo(new Vector3(0.0f, 0.0f, 0.0f)));
                        }
                        monster.actionMachine.AddAction(new ActionMoveBy(new Vector3(path[i].x, 0.0f, path[i].y), monster.speed));
                    }
                }
            }
        }
    }

    public override void OnExit() {
        // Debug.Log("Monster Chasing: OnExit");
        Rigidbody monsterBody = monster.gameObject.GetComponent<Rigidbody>();
        monsterBody.velocity = new Vector3(0.0f, 0.0f, 0.0f);
    }
}

public class MonsterAttackState : State {
    private PlayerScript player;
    private MonsterScript monster;
    private MonsterWeapon weapon;
    private float timer = 0.0f;

    public MonsterAttackState() {
        name = "Attack";
    }
    public override void OnEnter() {
        // Debug.Log("Monster Attack OnEnter");
        player = (PlayerScript)GameKernel.actorManager.playerActor;
        monster = (MonsterScript)stateMachine.actor;
        AudioClip audio = Resources.Load("Sounds/monster_attack") as AudioClip;
        monster.audioSource.PlayOneShot(audio);
        monster.monsterAnimation.CrossFade("Attack");
        weapon = monster.gameObject.GetComponentInChildren<MonsterWeapon>();
        weapon.enabled = true;
        timer = 0.0f;
    }
    public override void Update() {
        if (monster.health <= 0) {
            stateMachine.ChangeState("Dead");
            return;
        }
        if (monster.isHurt) {
            stateMachine.ChangeState("Hurt");
            return;
        }
        if (player.isPlayerDead) {
            stateMachine.ChangeState("Patrol");
            return;
        }
        timer += Time.deltaTime;
        if (monster.actionMachine.GetActionCount() == 0 && player.isPlayerTransferring == false) {
            monster.actionMachine.AddAction(new ActionRotateTo(new Vector3(
                0.0f, 
                Mathf.Atan2(player.gameObject.transform.position.x - monster.gameObject.transform.position.x, 
                player.gameObject.transform.position.z - monster.gameObject.transform.position.z) * Mathf.Rad2Deg, 
                0.0f)
            ));
        }
        if (monster.monsterAnimation.IsPlaying("Attack") == false) {
            float distance = Vector3.Distance(monster.gameObject.transform.position, player.gameObject.transform.position);
            if (distance >= monster.chasingDistance) {
                stateMachine.ChangeState("Patrol");
            } else if (distance >= monster.attackDistance) {
                stateMachine.ChangeState("Chasing");
            } else if (timer >= monster.attackSpeed){
                stateMachine.ChangeState("Attack");
            } else {
                monster.monsterAnimation.CrossFade("Wait");
            }
        }
    }
    public override void OnExit() {
        // Debug.Log("Monster Attack OnExit");
        weapon.enabled = false;
    }
}

public class MonsterHurtState : State {
    MonsterScript monster;
    PlayerScript player;

    public MonsterHurtState() {
        name = "Hurt";
    }
    public override void OnEnter() {
        // Debug.Log("Monster Hurt: OnEnter");
        monster = (MonsterScript)stateMachine.actor;
        player = (PlayerScript)GameKernel.actorManager.playerActor;
        monster.monsterAnimation.CrossFade("Damage");
        monster.actionMachine.ClearActions();
        monster.actionMachine.AddAction(new ActionRotateTo(new Vector3(
            0.0f, 
            Mathf.Atan2(player.gameObject.transform.position.x - monster.gameObject.transform.position.x, 
            player.gameObject.transform.position.z - monster.gameObject.transform.position.z) * Mathf.Rad2Deg, 
            0.0f)
        ));
        monster.health -= player.attack;
    }
    public override void Update() {
        if (monster.health <= 0) {
            stateMachine.ChangeState("Dead");
            return;
        }
        if (!monster.monsterAnimation.IsPlaying("Damage")) {
            stateMachine.ChangeState("Patrol");
            return;
        }
    }
    public override void OnExit() {
        // Debug.Log("Monster Hurt: OnExit");
        monster.isHurt = false;
    }
}

public class MonsterDeadEventData : EventData {
    public GameObject deadObject;
}

public class MonsterDeadState : State {
    MonsterScript monster;
    PlayerScript player;
    private float timer = 0.0f;

    public MonsterDeadState() {
        name = "Dead";
    }
    public override void OnEnter() {
        // Debug.Log("Monster Dead: OnEnter");
        monster = (MonsterScript)stateMachine.actor;
        monster.monsterAnimation.CrossFade("Dead");
        player = (PlayerScript)GameKernel.actorManager.playerActor;
        player.gold += 5;
    }
    public override void Update() {
        timer += Time.deltaTime;
        if (timer >= 1.5f) {
            MonsterDeadEventData data = new MonsterDeadEventData();
            data.deadObject = monster.gameObject;
            GameKernel.eventManager.DispatchEvent("MonsterDead", data);
        }
    }
    public override void OnExit() {
        // Debug.Log("Monster Dead: OnExit");
    }
}