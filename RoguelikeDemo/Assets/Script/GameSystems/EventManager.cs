using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class EventData {}

public interface IEventListener {
    void OnEvent(string eventName, EventData data);
}

public class EventManager : IGameSystem {
    Dictionary<string, List<IEventListener>> listenerTable = new Dictionary<string, List<IEventListener>>();

    public void Init() {}

    public void Update() {}

    public void Destroy() {}

    public void AddEventListener(string eventName, IEventListener listener) {
        List<IEventListener> list;
        if (!listenerTable.TryGetValue(eventName, out list)) {
            list = new List<IEventListener>();
            listenerTable.Add(eventName, list);
        }
        list.Add(listener);
    }

    public void RemoveEventListener(string eventName, IEventListener listener) {
        List<IEventListener> list;
        if (listenerTable.TryGetValue(eventName, out list)) {
            List<IEventListener> newList = new List<IEventListener>();
            for (int i = 0; i != list.Count; ++i) {
                if (list[i] != listener) {
                    newList.Add(list[i]);
                }
            }
            listenerTable.Remove(eventName);
            if (newList.Count != 0) {
                listenerTable.Add(eventName, newList);
            }
        }
    }

    public void DispatchEvent(string eventName, EventData data) {
        List<IEventListener> list;
        if (listenerTable.TryGetValue(eventName, out list)) {
            foreach (IEventListener listener in list) {
                listener.OnEvent(eventName, data);
            }
        }
    }
}