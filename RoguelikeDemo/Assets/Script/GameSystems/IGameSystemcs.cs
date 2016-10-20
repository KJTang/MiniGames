using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public interface IGameSystem {
    void Init();
    void Update();
    void Destroy();
}