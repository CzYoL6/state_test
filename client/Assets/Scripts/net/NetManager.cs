using UnityEngine;
using Google.Protobuf;

public class NetManager : Singleton<NetManager>
{
    private KCPConnection m_Connection;
    private ByteBuffer m_BufferTemp;

    protected override void InitSingleton()
    {
        m_BufferTemp = ByteBuffer.Allocate(1024 * 2);
        m_Connection = new KCPConnection();
        m_Connection.SetMessageCallback(MessageHandle);
    }

    public void InitConnection(uint sid, string host, int port) {
        m_Connection.InitKCP(sid, host, port);
        //SendMessage((int)Chat.TYPE.KcpConnectionReq, new Chat.KcpConnectReq_C_S());
        Update.KcpConnectReq_C_S msg = new Update.KcpConnectReq_C_S();
        SendMessage((int)Update.TYPE.KcpConnectionReq, msg);
    }

    private void MessageHandle(ByteBuffer data)
    {
        
        if (data.ReadableBytes < 8)
        {
            return;
        }

        
        /*int messageLen = data.GetInt(data.ReaderIndex);
        Debug.Log($"message len {messageLen}.");*/
        int messageLen = data.ReadInt();
        //Debug.Log($"message len2 is  {messageLen}, data readable: {data.ReadableBytes + 4}");
        if (messageLen > data.ReadableBytes) {
            Debug.Log("hhhh");
            return;
        }

        //data.ReaderIndex += 4;
        int cmd = data.ReadInt();
        int begin = data.ReaderIndex;
        data.ReaderIndex += messageLen - 4;
        //MessageDispatcher.Instance.Dispatch(cmd, data.RawBuffer, begin, messageLen);
        byte[] packetBytes = data.Get(begin, messageLen - 4);
        Debug.Log($"handling message cmd {cmd}.");
        switch (cmd) {
            case (int)Update.TYPE.UpdateInfoSToC: {
                Debug.Log("handling UpdateInfoSToC");
                using (Packet _packet = new Packet(packetBytes)) {
                    Debug.Log("handling ...");
                    ClientHandle.UpdateInfo(_packet);
                }
                
                break;
            }
        }

    }

    public void SendMessage(int cmd, object message)
    {
        //Debug.Log($"sending message cmd:{cmd}.");
        byte[] msgByte;
        int len = 8;
        if (message == null)
        {
            m_BufferTemp.WriteInt(0);
            m_BufferTemp.WriteInt(cmd);
        }
        else
        {
            msgByte = ((IMessage)message).ToByteArray();

            m_BufferTemp.WriteInt(msgByte.Length + 8);
            m_BufferTemp.WriteInt(cmd);
            m_BufferTemp.WriteBytes(msgByte, 0, msgByte.Length);
            //Debug.Log("msgByte len:" + msgByte.Length);
            len += msgByte.Length;
        }
        //Debug.Log("message len:" + len);
        
        m_Connection.Send(m_BufferTemp);
        m_BufferTemp.ReaderIndex += len;
    }

    public void Connect(string host, int port)
    {
        if (m_Connection == null || m_Connection.IsConnected())
        {
            return;
        }

        m_Connection.Connect(host, port);
    }

    public void Tick()
    {
        m_Connection.Tick();
    }

    public uint GetKcpSid()
    {
        return m_Connection.Sid;
    }
}
