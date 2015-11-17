using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class GameControler : MonoBehaviour {

    // 僵尸生成时间间隔
    public float ZombieGenerationTimeInterval = 2f;
    // 触发难度提升的已打败僵尸总生命值, 当僵尸死亡总生命值到底, 而时间未到, 同样触发难度升级
    public int LevelBloodKilled = 20;
    // 难度升级基本间隔时间
    public float LevelTimeInterval = 20f;

    private float ZombieGenerationTimeClock;
    private float LevelTimeClock;
    private int TotalBloodKilld = 0;

    // 僵尸工厂队列, 用于控制僵尸生成位置
    private static List<GameObject> zombieFactories;

    void Awake()
    {
        zombieFactories = new List<GameObject>(GameObject.FindGameObjectsWithTag("Zombie Factory"));
        ZombieGenerationTimeClock = ZombieGenerationTimeInterval;
        LevelTimeClock = LevelTimeInterval;
    }
	
	// Update is called once per frame
	void Update () {
        ZombieGenerationTimeClock -= Time.deltaTime;
        LevelTimeClock -= Time.deltaTime;
        if (ZombieGenerationTimeClock <= 0)
        {
            // 随机产生僵尸
            int factoryCount = zombieFactories.Count;
            GameObject zombieFactory = zombieFactories[Random.Range(0, factoryCount)];
            ZombieFactory zFactory = zombieFactory.GetComponent<ZombieFactory>();
            ZombieType zType = (ZombieType)Random.Range(1, (int)ZombieType.Count);
            zFactory.CreateZombie(zType);
            ZombieGenerationTimeClock = ZombieGenerationTimeInterval;
        }

        if (LevelTimeClock <= 0)
        {
            // 游戏难度升级
            LevelRaise();
        }
	}

    public void BloodKilledRaise(int blood)
    {
        TotalBloodKilld += blood;
        if (TotalBloodKilld >= LevelBloodKilled)
        {
            // 游戏难度升级
            LevelRaise();
        }
    }

    private void LevelRaise()
    {
        TotalBloodKilld = 0;
        LevelTimeClock = LevelTimeInterval;
        ZombieGenerationTimeInterval /= 2;
        LevelBloodKilled *= 2;
        LevelTimeInterval += 10;
    }
}
