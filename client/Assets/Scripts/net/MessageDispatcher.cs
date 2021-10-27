using System;
using System.Collections.Generic;
using Google.Protobuf;

class MessageDispatcher : Singleton<MessageDispatcher>
{
    class MessageListener
    {
        public int cmd;
        public Type msgType;
        public Action<IMessage> onMsg;
    }

    protected override void InitSingleton()
    {

    }

    private Dictionary<int, MessageListener> m_MessageListeners = new Dictionary<int, MessageListener>();

    public void RegisterMessageListener(int cmdIndex, Type msg, Action<IMessage> handle)
    {
        MessageListener listener = new MessageListener()
        {
            cmd = cmdIndex,
            msgType = msg,
            onMsg = handle,
        };

        m_MessageListeners[cmdIndex] = listener;
    }

    public void Dispatch(int cmd, byte[] data, int index, int len)
    {
        MessageListener msg = null;
        m_MessageListeners.TryGetValue(cmd, out msg);
        if (msg != null)
        {
            if (msg.msgType == null)
            {
                msg.onMsg(null);
            }
            else
            {
                IMessage message = ProtobufHelper.FromBytes(msg.msgType, data, index, len) as IMessage;
                msg.onMsg(message);
            }
        }
    }
}
