using UnityEngine;
using System;
using System.Collections;

public class ItemGold : MonoBehaviour {
    public Vector3 offset = new Vector3(0.0f, 3.0f, 0.0f);
    public float speed = 20.0f;

    private Renderer rend;
    private Shader shaderUnSeen;
    private Shader shaderSeen;

    private PlayerScript player;

    public int MIN_GOLD_COUNT = 10;
    public int MAX_GOLD_COUNT = 50;
    private System.Random rand;

    private AudioSource audio;

    // Use this for initialization
    void Start () {
        rend = GetComponent<Renderer>();
        shaderUnSeen = Shader.Find("Legacy Shaders/Diffuse");
        shaderSeen = Shader.Find("Legacy Shaders/Self-Illumin/Diffuse");
        player = (PlayerScript)GameKernel.actorManager.playerActor;
        rand = new System.Random();
        audio = GetComponent<AudioSource>();
    }
    
    // Update is called once per frame
    void Update () {
        float step = speed * Time.deltaTime;
        transform.rotation = Quaternion.RotateTowards(transform.rotation, Quaternion.Euler(transform.rotation.eulerAngles + offset), step);

        if (player != null) {
            if (Vector3.Distance(gameObject.transform.position, player.gameObject.transform.position) <= 3) {
                rend.material.shader = shaderSeen;
            } else {
                rend.material.shader = shaderUnSeen;
            }
        }
    }

    void OnTriggerEnter(Collider other) {
        if (player != null && other.gameObject == player.gameObject) {
            player.gold += rand.Next(MIN_GOLD_COUNT, MAX_GOLD_COUNT + 1);
            audio.Play();
            rend.enabled = false;
            GetComponent<Collider>().enabled = false;
            Destroy(gameObject, 0.5f);
        }
    }
}
