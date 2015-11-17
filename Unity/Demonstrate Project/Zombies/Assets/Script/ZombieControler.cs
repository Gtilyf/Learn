using UnityEngine;
using System.Collections;

// 僵尸类型, 当其类型确定, 则其生命值以及对应gameobject的tag也应确定;
public enum ZombieType : int
{
    None = 0,
    Little = 1,
    Conehead = 2,
    Count = 3,
}

public class ZombieControler : MonoBehaviour {

    // 速度根据游戏的速度决定
    private float moveSpeed = 0;
    private Vector3 moveOretation = Vector3.zero;

    // 生命值由单位生命值(unitBlood, 游戏时间增加而增加)以及僵尸类型决定
    public int blood = 2;
    public ZombieType zType = ZombieType.None;

	void Update () {
        transform.Translate(moveOretation * moveSpeed);
        // 测试
        if (transform.position.z < -2)
            DeactivateSelf();
	}

    // 初始化相应属性
    public void InitProperties(float speed, int unitBlood, Vector3 oretation)
    {
        moveSpeed = speed;

        // 僵尸类型在对应绑定的gameobject设定初始值, 如果没有设置, 则默认初始为Little
        if (zType == ZombieType.None)
            zType = ZombieType.Little;
        blood = unitBlood * (int)zType;

        // 僵尸移动方向由其所处位置决定 
        moveOretation = oretation;
    }

    // 改变移动方向
    public void ChangeOretation(Vector3 oretation)
    {
        moveOretation = oretation;
    }

    // 响应被打击事件
    private void BeHited()
    {
        if (blood-- <= 0)
        {
            DeactivateSelf();
        }
    }

    // 响应僵尸死亡事件
    private void DeactivateSelf()
    {
        GameObject self = this.gameObject;
        moveSpeed = 0;
        moveOretation = Vector3.zero;
        self.SetActive(false);
        // 将其加入Object pooling, 以待下一次使用
        ZombieFactory.RecoverInactiveZombie(self);
        GameObject gameControler = GameObject.Find("Game Controler");
        (gameControler.GetComponent<GameControler>()).BloodKilledRaise((int)zType * ZombieFactory.unitBlood);
    }
}