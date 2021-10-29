using UnityEngine;
public abstract class Singleton<T> : MonoBehaviour
    where T : MonoBehaviour {
    private static T m_instance;

    public static T Instance { get => m_instance; }

    protected virtual void Awake() {
        m_instance = this as T;
        InitSingleton();
    }
    protected virtual void InitSingleton() {

    }
}