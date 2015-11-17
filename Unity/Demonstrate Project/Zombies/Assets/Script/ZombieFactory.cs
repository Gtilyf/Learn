using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class ZombieFactory : MonoBehaviour {

    // 游戏速度, 用于控制游戏难度, 根据游戏时间阶段性增加, 用于控制僵尸速度
    public static float baseGameSpeed = 0.1f;
    // 僵尸基本单位血量, 用于控制游戏难度, 根据游戏阶段性增加, 用于控制僵尸生命值
    public static int unitBlood = 2;
    // 记录clone的gameobject数量, 主要用于对clone object的控制
    private static int cloneCount = 0;

    // 空闲僵尸队列, 如果队列中存在需要的僵尸, 则不会instantiate新的gameobject
    private static List<GameObject> inactiveZombies;
    // 方向控制面板队列, 用于随机为僵尸选择路线
    private static List<GameObject> turnOretationPlanes;

    // 游戏开始, 将scene中已存在的僵尸(模板)加入list
    void Awake()
    {
        inactiveZombies = new List<GameObject>(GameObject.FindGameObjectsWithTag("Zombie"));
        turnOretationPlanes = new List<GameObject>(GameObject.FindGameObjectsWithTag("Turn Control Plane"));
    }

    // 产生僵尸, 如果inactiveList中没有余量, 则instantiate新gameobject, 初始位置即为factory的位置
    public void CreateZombie(ZombieType zType)
    {
        GameObject zombie;
        zombie = inactiveZombies.Find(z =>
        {
            return (z.GetComponent<ZombieControler>()).zType == zType;
        });
        if (inactiveZombies.Count > 0
             && zombie != null)
        {
            inactiveZombies.Remove(zombie);
            zombie.transform.position = transform.position;
        }
        else
        {
            string zombieName = zType.ToString() + " Zombie";
            GameObject fatherZombie = GameObject.Find(zombieName);
            zombie = Instantiate(fatherZombie, transform.position, transform.rotation) as GameObject;
            zombie.name = zombieName + "-" + cloneCount;
            cloneCount++;
        }

        // 随机获取plane
        GameObject plane = turnOretationPlanes[Random.Range(0, turnOretationPlanes.Count)];
        Vector3 zombieOretation = (plane.transform.position - transform.position).normalized;
        // 将该僵尸加入该plane的检测队列
        (plane.GetComponent<TurnOretation>()).zombies.Add(zombie);

        // 初始化属性
        ZombieControler zombieControler = zombie.GetComponent<ZombieControler>();
        zombieControler.InitProperties(baseGameSpeed, unitBlood, zombieOretation);

        if (!zombie.activeInHierarchy)
            zombie.SetActive(true);
    }

    // 回收失效(即死亡)的僵尸
    public static void RecoverInactiveZombie(GameObject zombie)
    {
        // 防止将所有僵尸都失效, 则Instantiate将报错
        ZombieControler zombieControler = zombie.GetComponent<ZombieControler>();
        GameObject leftZombieFactory = GameObject.Find("Right Zombie Factory");
        if (zombie.name.Equals(zombieControler.zType.ToString() + " Zombie"))
        {
            zombie.transform.Translate(leftZombieFactory.transform.position - zombie.transform.position);
            zombie.SetActive(true);
        }
        inactiveZombies.Add(zombie);
    }
}
