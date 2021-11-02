using System;
using System.Net;
using System.Net.Sockets;
using UnityEngine;

public static class KcpProtocalType
{
    public const byte SYN = 1;
    public const byte ACK = 2;
}

public class KCPConnection
{
    private Socket m_Socket = null;
    private KCP m_Kcp = null;
    private IPEndPoint m_RemotePoint = null;
    private bool m_IsConnected = false;
    private byte[] m_RecvTemp = new byte[64 * 1024];
    private UInt32 m_NextUpdateTime = 0;
    private ByteBuffer m_RecvBuffer = ByteBuffer.Allocate(64 * 1024);
    private Action<ByteBuffer> m_MessageCallback = null;
    private uint m_Sid;
    public uint Sid { get { return m_Sid; } }

    public KCPConnection()
    {
        m_Socket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
        IPEndPoint endPoint = new IPEndPoint(IPAddress.Any, 0);
        m_Socket.Bind(endPoint);
    }
    
    public void Connect(string host, int port)
    {
        try
        {
            var address = IPAddress.Parse(host);
            m_RemotePoint = new IPEndPoint(address, port);
            ByteBuffer buffer = ByteBuffer.Allocate(1);
            buffer.WriteByte(KcpProtocalType.SYN);
            if (m_Socket != null)
            {
                m_Socket.SendTo(buffer.RawBuffer, 1, SocketFlags.None, m_RemotePoint);
            }
        }
        catch
        {

        }
    }

    public void InitKCP(uint sid, string host, int port) {
        Debug.Log($"Init kcp to sid:{sid}, host:{host}, port:{port}.");

        var address = IPAddress.Parse(host);
        m_RemotePoint = new IPEndPoint(address, port);

        m_Sid = sid;
        m_Kcp = new KCP(sid, SoketSend);
        m_Kcp.NoDelay(1, 20, 2, 1);

        //---------------------
        m_Kcp.SetMtu(1024 * 64);
        
        m_RecvBuffer.Clear();
        m_IsConnected = true;
        //GlobalEvent.onTipChange.Invoke("连接服务器成功");
        //GlobalEvent.onConnectSuccess.Invoke();
        
        Debug.Log("init succeeded.");
    }

    public bool IsConnected()
    {
        return m_IsConnected;
    }

    public void SetMessageCallback(Action<ByteBuffer> cb)
    {
        m_MessageCallback = cb;
    }

    public void Close()
    {
        if (m_Socket != null)
        {
            m_Socket.Close();
            m_Socket = null;
        }
    }

    public void SoketSend(byte[] data, int len)
    {
        if (m_Socket != null && m_IsConnected)
        {
            m_Socket.SendTo(data, len, SocketFlags.None, m_RemotePoint);
        }
    }

    public int Send(byte[] data)
    {
        if (!m_IsConnected)
            return -1;

        var n = m_Kcp.Send(data, 0, data.Length);

        return n;
    }

    public void Send(ByteBuffer buffer)
    {
        if (!m_IsConnected)
        {
            return;
        }
        //Debug.Log("send succeeded.");
        var n = m_Kcp.Send(buffer.RawBuffer, buffer.ReaderIndex, buffer.WriterIndex);
    }

    public void Recv()
    {

        if (m_Socket == null)
        {
            return;
        }

        if (!m_Socket.Poll(0, SelectMode.SelectRead))
        {
            return;
        }

        var rn = 0;
        try
        {
            rn = m_Socket.Receive(m_RecvTemp, 0, m_RecvTemp.Length, SocketFlags.None);
        }
        catch
        {
            rn = -1;
        }


        if (rn < 0)
        {
            return;
        }

        if (rn == 5 && m_RecvTemp[0] == KcpProtocalType.ACK)
        {
            uint sid = BitConverter.ToUInt32(m_RecvTemp, 1);
            m_Sid = sid;
            m_Kcp = new KCP(sid, SoketSend);
            m_Kcp.NoDelay(0, 30, 2, 1);
            m_RecvBuffer.Clear();
            m_IsConnected = true;
            GlobalEvent.onTipChange.Invoke("连接服务器成功");
            GlobalEvent.onConnectSuccess.Invoke();

            return;
        }

        if (rn < KCP.IKCP_OVERHEAD)
        {
            return;
        }

        var inputN = m_Kcp.Input(m_RecvTemp, 0, rn, true, true);

        if (inputN < 0)
        {
            return;
        }

        for (int size = m_Kcp.PeekSize(); size > 0; size = m_Kcp.PeekSize())
        {
            m_RecvBuffer.EnsureWritableBytes(size);
            var n = m_Kcp.Recv(m_RecvBuffer.RawBuffer, m_RecvBuffer.WriterIndex, size);
            if (n > 0) m_RecvBuffer.WriterIndex += n;

            if (m_RecvBuffer.ReadableBytes > 0)
            {
                m_MessageCallback?.Invoke(m_RecvBuffer);
            }
        }
    }

    public void Tick()
    {
        Recv();

        if (!m_IsConnected)
            return;

        if (0 == m_NextUpdateTime || m_Kcp.CurrentMS >= m_NextUpdateTime)
        {
            m_Kcp.Update();
            m_NextUpdateTime = m_Kcp.Check();
        }
    }


}
