# Unity 3D Physics Engine

> 如何使用Unity Physics Engine实现各种游戏效果以及应该注意的地方，来自[`Unity Tutorials`](http://unity3d.com/learn/tutorials/topics/physics)。

### Collider

> [Collider Docs](http://docs.unity3d.com/ScriptReference/Collider.html)
> Collider是物体带有碰撞效果; Trigger使物体不触发碰撞，但可以相互穿过; Rigidbody是物体带有基本物理属性;

*	*Collider*组件用于实现两个GameObject之间的相互作用（要求至少其中一个GameObject附加有*Rigidbody*组件），使GameObject周围覆盖着collider volumes，
	Collison检测即检测两个Collider之间的collider volumes是否重叠(overlapping)。当collisions发生时，会触发Collision events（只有当其中一个Collider拥有non-kinematic rigidbody时触发）; 函数`OnCollisionEnter`、`OnCollisionStay`、`OnCollisionExit`实现对collision的响应;

	如果不希望GameObject产生collision，而同时跟踪GameObject的collider volumes相互重叠，可以改变collider为*Trigger Colliders*，则*collider volumes*改变为*trigger volumes*，当两个GameObject（其中一个包含有Trigger Colliders组件）相遇，collider将会穿过(penetration)trigger collider，同时出发`Trigger events`; 函数`OnTriggerEnter`、`OnTriggerStay`、`OnTriggerExit`实现对trigger的响应;

*	*`Rigidbody`*组件使Unity物理引擎作用于该GameObject，当一个GameObject需要使用到物理交互时使用。Rigidbody使得GameObject获得基本的物理属性，包括质量(mass)、阻力(drag)等;

### Static Colliders & Dynamic Colliders

> Ordinarily when a scene begins, all static geometry, meaning any non-rigidbody objects are checked once by the physics engine and not checked again for efficiency. howerver when you move a static object, the physics engine must re-check all other static objects for the sake of accuracy.

> As a performance optimisation Unity calculates all the volumes of all the static colliders in a scene and holds this information in a cache. This makes sense as static colliders shouldn't move, and this saves recalculating this information every frame. Any time we move, rotate, or scale a static collider Unity will recalculate all the static colliders again and update the static collider cache. To recalculate the cache takes resources. We can move, rotate or scale dynamic colliders as often as we want and Unity won't recache any collider volumes. Unity expects us to move colliders, We simply need to indicate to Unity which colliders are dynamic before we move them. We do this by using the rigid body component. Any game object with a collider and a rigid body is considered dynamic. Any game object with a collider attached but no physics rigid body is expected to be static.

不带有rigidbody的collider会被视为静态的物体，Unity默认该物体不会被移动，会在scene加载的时候计算其信息并缓存，但是如果在游戏过程中移动了该物体，unity会寻找场景中的所有静态物体，重新计算；但是带有rigidbody的collider则被视为动态物体，移动该物体不会引起Unity重新计算；如果一个rigidbody具有kinematic属性，则其不具有物理特性，但是移动不会引起Unity重新计算；所以，如果想要移动一个collider，并且不希望其具有物理特性，且会移动它，最好为其添加rigidbody并设置kinematic.

### AddForce & AddTorque

### Physics Materials & Physics Joints

### Raycasting