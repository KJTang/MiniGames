using UnityEngine;
using UnityEngine.SceneManagement;
using System.Collections;

public class PlayerScript : Actor, IEventListener {
    public StateMachine stateMachine;
    public ActionMachine actionMachine;
    public Animation playerAnimation;
    public AudioSource audioSource;

    public int gold = 0;

    public bool isPlayerTransferring = false;
    public Actor hurtMonster;
    public bool isPlayerHurt = false;
    public bool isPlayerDead = false;

	void Awake() {
        playerAnimation = GetComponent<Animation>();
        audioSource = GetComponent<AudioSource>();

        stateMachine = new StateMachine();
        stateMachine.actor = this;
        stateMachine.Init();
        stateMachine.AddState(new PlayerIdleState());
        stateMachine.AddState(new PlayerMoveState());
        stateMachine.AddState(new PlayerAttackState());
        stateMachine.AddState(new PlayerHurtState());
        stateMachine.AddState(new PlayerDeadState());
        stateMachine.AddState(new PlayerTransferState());

        actionMachine = new ActionMachine();
        actionMachine.actor = this;
        actionMachine.Init();
	}

    void Start() {
        stateMachine.ChangeState("Idle");       // set default state
        actionMachine.ClearActions();
        GameKernel.eventManager.AddEventListener("HurtByMonster", this);
    }

    void Update() {
        stateMachine.Update();
        actionMachine.Update();
    }

    void OnDestroy() {
        GameKernel.eventManager.RemoveEventListener("HurtByMonster", this);
        stateMachine.Destroy();
        actionMachine.Destroy();
    }

    public void OnEvent(string eventName, EventData data) {
        if (eventName == "HurtByMonster") {
            hurtMonster = (Actor)((HurtByMonsterEventData)data).monster.GetComponent<Actor>();
            // Debug.Log("++++++++++++++  attack: " + attack);
            isPlayerHurt = true;
        }
    }
}
