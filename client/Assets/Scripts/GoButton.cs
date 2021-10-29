using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using TMPro;

public class GoButton : MonoBehaviour
{
    public TMP_InputField ipIF;
    public TMP_InputField portIF;
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
        SceneManager.LoadScene(2);
    }
}
