/******************************************************
 * ��һ�Ƽ����ṩ��¼�����Ƽ�ص�ȫƽ̨�޲�����������
 * ֧�ְ���ֱ������㲼�أ��ֲ�ʽ�����洢����̬���ݣ�
 * ֧��΢��ɨ���¼��ȫƽ̨�ʺ�ͳһ������΢��С����
 * ֧�ֶ����������룺����ͷIPC��rtmp��rtsp��MP4�ļ���
 * ֧��ȫʵʱ��ȫ��̬��ȫ��ҳ������ҳǰ��̨����IE8��
 * ֧�ֶ��ն��޲������Ӧ���ţ�flvjs/hls/rtmp�Զ����䣻
 ******************************************************
 * �ٷ���վ => https://myhaoyi.com
 * �������� => http://blog.csdn.net/haoyitech
 * ��Դ���� => https://github.com/HaoYiTech/
 * �Ƽ��Ⱥ => 483663026��QQȺ��
 * ��¼��Ⱥ => 630379661��QQȺ��
 ******************************************************
 * LibMP4 => MP4���̷�װ��
 ******************************************************/

#pragma once

#include "mp4v2.h"

typedef struct RTMPFrame {
	string		m_strData;
	bool		m_bKeyFrame;
	uint32_t	m_nTimeStamp;
	uint32_t	m_nRenderOffset;
}RTMPFrame;

typedef	deque<RTMPFrame>	KH_DeqFrame;
class LibMP4
{
public:
	LibMP4(void);
	~LibMP4(void);
public:
	DWORD GetWriteSize()  { return m_dwWriteSize; }
	DWORD GetWriteSec()   { return m_dwWriteSec; }
	bool IsVideoCreated() { return ((m_videoID == MP4_INVALID_TRACK_ID) ? false : true); }
	bool IsAudioCreated() { return ((m_audioID == MP4_INVALID_TRACK_ID) ? false : true); }

	bool CreateAudioTrack(const char* lpUTF8Name, int nAudioSampleRate, string & strAES);
	bool CreateVideoTrack(const char* lpUTF8Name, int nVideoTimeScale, int width, int height, string & strSPS, string & strPPS);

	bool WriteSample(bool bIsVideo, BYTE * lpFrame, int nSize, uint32_t inTimeStamp, uint32_t inRenderOffset, bool bIsKeyFrame);

	bool Close();
private:
	DWORD GetDurationSecond();
private:
	MP4FileHandle	m_hFileHandle;		// �ļ����
	MP4TrackId		m_videoID;			// ��ƵID
	MP4TrackId		m_audioID;			// ��ƵID
	RTMPFrame		m_VLastFrame;		// ��һ֡��Ƶ����Ƶ�ǹ̶��ģ����ü�¼��һ֡����
	KH_DeqFrame		m_deqAudio;			// ��Ƶ��������֡
	DWORD			m_dwWriteSize;		// д���ļ�����...
	DWORD			m_dwWriteSec;		// �Ѿ�д�������...
	DWORD			m_dwFirstStamp;		// ��ʼд�̵ĵ�һ֡ʱ���...
	bool			m_bFirstFrame;		// ��һ֡����д��Ƶ�Ĺؼ�֡,֮ǰ����Ƶ����
	int				m_nVideoTimeScale;	// Ŀǰ�ǹ̶�����ֵ�����ϲ������Ʋ�����
};

