using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using TMPro;

public class GoButton : MonoBehaviour
{
    public TMP_InputField ipIF;
    public TMP_InputField portIF;
    public TMP_InputField tickIF;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void Go() {
        InfoKeeper.Instance.ip = ipIF.text;
        InfoKeeper.Instance.port = int.Parse(portIF.text);
        InfoKeeper.Instance.tickRate = float.Parse(tickIF.text);
        SceneManager.LoadScene(2);
    }
}
