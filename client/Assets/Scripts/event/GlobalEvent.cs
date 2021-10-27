public static class GlobalEvent
{
    public static GameEvent onFixedUpdate = new GameEvent();
    public static GameEvent onConnectSuccess = new GameEvent();
    public static GameEvent<string> onTipChange = new GameEvent<string>();
    public static GameEvent<int, int> onRoomInfoChange = new GameEvent<int, int>();
    public static GameEvent<Player> onPlayerCreated = new GameEvent<Player>();
}
