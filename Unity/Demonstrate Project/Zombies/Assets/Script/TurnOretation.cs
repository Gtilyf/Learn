using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class TurnOretation : MonoBehaviour {

    // 由其控制方向变化的僵尸队列
    public List<GameObject> zombies;

    void Awake()
    {
        zombies = new List<GameObject>();
    }

    void OnTriggerEnter(Collider other)
    {
        GameObject zombie = other.gameObject;
        if (zombies.Exists(z => { return z.gameObject.name.Equals(zombie.gameObject.name); }))
        {
            Vector3 oretation = (GameObject.Find("lawns").transform.position - GameObject.Find("street").transform.position).normalized;
            (zombie.GetComponent<ZombieControler>()).ChangeOretation(oretation);
            zombies.Remove(zombie);
        }
    }
}
