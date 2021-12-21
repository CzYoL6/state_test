using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class UIManager : MonoBehaviour
{
    public TextMeshProUGUI fpsText;
    public TextMeshProUGUI tickText;
    public TextMeshProUGUI rttTimeText;

    public static UIManager Instance { get; private set; }
    private void Awake() {
        if (Instance == null) Instance = this;

    }
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
    }
}
