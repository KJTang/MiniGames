using UnityEngine;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Xml;
using System.IO;

public struct GameData {
    public int level;
    public int health;
    public int attack;
    public int gold;

    public GameData(int l, int h, int a, int g) {
        level = l;
        health = h;
        attack = a;
        gold = g;
    }
};

public class FileManager : IGameSystem {
    public void Init() {}
    public void Update() {}
    public void Destroy() {}

    public string GetFullPath(string filePath) {
        return Application.dataPath + filePath;
    }

    public bool IsFileExist(string filePath) {
        return File.Exists(filePath);
    }

    public void DeleteFile(string filePath) {
        string path = GetFullPath(filePath);
        if (IsFileExist(path)) {
            File.Delete(path);
            File.Delete(path + ".meta");
        }
    }

    public GameData FastLoadData(string filePath) {
        GameData data = new GameData(0, 100, 10, 0);       // default
        string path = GetFullPath(filePath);
        if (!IsFileExist(path)) {
            return data;
        }
        XmlDocument xmlDoc = new XmlDocument();
        xmlDoc.Load(path);
        XmlNode root = xmlDoc.SelectSingleNode("game");
        XmlElement levelData = root["level"];
        XmlElement playerData = root["player"];
        foreach (XmlElement xe in levelData.ChildNodes) {
            switch (xe.Name) {
                case "count": {
                    data.level = Convert.ToInt32(xe.InnerText);
                    break;
                }
            }
        }
        foreach (XmlElement xe in playerData.ChildNodes) {
            switch (xe.Name) {
                case "health": {
                    data.health = Convert.ToInt32(xe.InnerText);
                    break;
                }
                case "attack": {
                    data.attack = Convert.ToInt32(xe.InnerText);
                    break;
                }
                case "gold": {
                    data.gold = Convert.ToInt32(xe.InnerText);
                    break;
                }
            }
        }
        return data;
    }

    public bool FastSaveData(string filePath, GameData data) {
        string path = GetFullPath(filePath);
        // Debug.Log("---------------  filePath: " + path);
        XmlDocument xmlDoc = new XmlDocument();
        if (!IsFileExist(path)) {
            XmlElement root = xmlDoc.CreateElement("game");
            XmlElement levelData = xmlDoc.CreateElement("level");
            XmlElement levelCount = xmlDoc.CreateElement("count");
            XmlElement playerData = xmlDoc.CreateElement("player");
            XmlElement playerHealth = xmlDoc.CreateElement("health");
            XmlElement playerAttack = xmlDoc.CreateElement("attack");
            XmlElement playerGold = xmlDoc.CreateElement("gold");

            levelCount.InnerText = data.level.ToString();
            playerHealth.InnerText = data.health.ToString();
            playerAttack.InnerText = data.attack.ToString();
            playerGold.InnerText = data.gold.ToString();

            levelData.AppendChild(levelCount);
            playerData.AppendChild(playerHealth);
            playerData.AppendChild(playerAttack);
            playerData.AppendChild(playerGold);
            root.AppendChild(levelData);
            root.AppendChild(playerData);
            xmlDoc.AppendChild(root);
        } else {
            xmlDoc.Load(path);
            XmlNode root = xmlDoc.SelectSingleNode("game");
            XmlElement levelData = root["level"];
            XmlElement playerData = root["player"];
            foreach (XmlElement xe in levelData.ChildNodes) {
                switch (xe.Name) {
                    case "count": {
                        xe.InnerText = data.level.ToString();
                        break;
                    }
                }
            }
            foreach (XmlElement xe in playerData.ChildNodes) {
                switch (xe.Name) {
                    case "health": {
                        xe.InnerText = data.health.ToString();
                        break;
                    }
                    case "attack": {
                        xe.InnerText = data.attack.ToString();
                        break;
                    }
                    case "gold": {
                        xe.InnerText = data.gold.ToString();
                        break;
                    }
                }
            }
        }
        xmlDoc.Save(path);
        return true;
    }
}