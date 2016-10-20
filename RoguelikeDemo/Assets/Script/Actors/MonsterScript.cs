using UnityEngine;
using UnityEngine.SceneManagement;
using System.Collections;

public class MonsterScript : Actor, IEventListener {
    public StateMachine stateMachine;
    public ActionMachine actionMachine;
    public Animation monsterAnimation;
    public AudioSource audioSource;

    public bool isHurt = false;
    public float chasingDistance = 3.5f;
    public float patrolDistance = 5.0f;
    public float attackDistance = 1.5f;

    void Awake() {
        monsterAnimation = GetComponent<Animation>();
        audioSource = GetComponent<AudioSource>();

        stateMachine = new StateMachine();
        stateMachine.actor = this;
        stateMachine.Init();
        stateMachine.AddState(new MonsterPatrolState());
        stateMachine.AddState(new MonsterChasingState());
        stateMachine.AddState(new MonsterAttackState());
        stateMachine.AddState(new MonsterHurtState());
        stateMachine.AddState(new MonsterDeadState());

        actionMachine = new ActionMachine();
        actionMachine.actor = this;
        actionMachine.Init();
    }

    void Start() {
        stateMachine.ChangeState("Patrol");
        actionMachine.ClearActions();

        GameKernel.eventManager.AddEventListener("HurtByPlayer", this);
        GameKernel.eventManager.AddEventListener("MonsterDead", this);
    }

    void Update() {
        stateMachine.Update();
        actionMachine.Update();
    }

    void OnDestroy() {
        GameKernel.eventManager.RemoveEventListener("HurtByPlayer", this);
        GameKernel.eventManager.RemoveEventListener("MonsterDead", this);
    }

    public void OnEvent(string eventName, EventData data) {
        if (eventName == "HurtByPlayer") {
            if (((HurtByPlayerEventData)data).hurtObject == this.gameObject) {
                isHurt = true;
            }
        } else if (eventName == "MonsterDead") {
            if (((MonsterDeadEventData)data).deadObject == this.gameObject) {
                Destroy(this.gameObject);
            }
        }
    }
}
