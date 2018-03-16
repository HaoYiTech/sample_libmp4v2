
#include "StdAfx.h"
#include "LibMP4.h"

LibMP4::LibMP4(void)
{
	m_hFileHandle = MP4_INVALID_FILE_HANDLE;
	this->Close();
}

LibMP4::~LibMP4(void)
{
	this->Close();
}
//
// �ر�¼���ļ� => ��λ����...
bool LibMP4::Close()
{
	if( m_hFileHandle != MP4_INVALID_FILE_HANDLE ) {
		MP4Close(m_hFileHandle);
		m_hFileHandle = MP4_INVALID_FILE_HANDLE;
	}
	m_hFileHandle = MP4_INVALID_FILE_HANDLE;
	m_videoID = MP4_INVALID_TRACK_ID;
	m_audioID = MP4_INVALID_TRACK_ID;
	m_nVideoTimeScale = 0;
	m_bFirstFrame = true;
	m_dwFirstStamp = 0;
	m_dwWriteSec = 0;
	m_dwWriteSize = 0;
	
	m_VLastFrame.m_nTimeStamp = 0;
	m_VLastFrame.m_strData.clear();
	m_VLastFrame.m_bKeyFrame = false;
	m_VLastFrame.m_nRenderOffset = 0;
	return true;
}
//
// ������Ƶ���...
bool LibMP4::CreateVideoTrack(const char* lpUTF8Name, int nVideoTimeScale, int width, int height, string & strSPS, string & strPPS)
{
	if( strSPS.size() <= 0 || strPPS.size() <= 0 || lpUTF8Name == NULL )
		return false;
	// ������Ϊ�գ��򴴽�MP4����...
	if( m_hFileHandle == MP4_INVALID_FILE_HANDLE ) {
		m_hFileHandle = MP4Create(lpUTF8Name);
	}
	// �ٴ��ж��ļ����...
	if( m_hFileHandle == MP4_INVALID_FILE_HANDLE )
		return false;
	// ����TimeScale��ʱ��̶ȣ�ͨ��Ϊ����Ĺ̶���ֵ...
	BYTE * lpSPS = (BYTE*)strSPS.c_str();
	uint32_t theTimeScale = nVideoTimeScale;
	MP4SetTimeScale(m_hFileHandle, theTimeScale);
	// �����Ƶ���, ��Ҫ�ù̶�ʱ��������ÿ֡��ʱ����...
	// ���������Ƶʱ������һ��Ҫ�� MP4_INVALID_DURATION��������֮֡���ʱ���ķ���...
	// ���ַ���������������ź���Դ�����ݣ��� fps ��ʽ����ȷ...(2015.10.17)
	m_videoID = MP4AddH264VideoTrack(m_hFileHandle, 
									theTimeScale, 
									MP4_INVALID_DURATION, //theTimeScale/fps,
									width, height, 
									lpSPS[1],
									lpSPS[2],
									lpSPS[3],
									3);
	if( m_videoID == MP4_INVALID_TRACK_ID ) {
		MP4Close(m_hFileHandle);
		m_hFileHandle = MP4_INVALID_FILE_HANDLE;
		return false;
	}
	// ������Ƶlevel...
	MP4SetVideoProfileLevel(m_hFileHandle, 0x7F);

	// ����SPS/PPS...
	MP4AddH264SequenceParameterSet(m_hFileHandle, m_videoID, (BYTE*)strSPS.c_str(), strSPS.size());
	MP4AddH264PictureParameterSet(m_hFileHandle, m_videoID, (BYTE*)strPPS.c_str(), strPPS.size());

	m_nVideoTimeScale = nVideoTimeScale;

	return true;
}
//
// ������Ƶ���...
bool LibMP4::CreateAudioTrack(const char* lpUTF8Name, int nAudioSampleRate, string & strAES)
{
	if( strAES.size() <= 0 || lpUTF8Name == NULL )
		return false;
	// ������Ϊ�գ��򴴽�MP4����...
	if( m_hFileHandle == MP4_INVALID_FILE_HANDLE ) {
		m_hFileHandle = MP4Create(lpUTF8Name);
	}
	// �ٴ��ж��ļ����...
	if( m_hFileHandle == MP4_INVALID_FILE_HANDLE )
		return false;

	// �����Ƶ�������Ƶʱ��̶ȹ̶�Ϊ 1024��������������...
	// AAC ���ǲ��ù̶��Ŀ̶���ת��...(2015.10.17)
	m_audioID = MP4AddAudioTrack(m_hFileHandle, nAudioSampleRate, 1024, MP4_MPEG4_AUDIO_TYPE);
	if( m_audioID == MP4_INVALID_TRACK_ID ) {
		MP4Close(m_hFileHandle);
		m_hFileHandle = MP4_INVALID_FILE_HANDLE;
		return false;
	}
	
	// ������Ƶ level �� AES...
	MP4SetAudioProfileLevel(m_hFileHandle, 0x02);//0xFF);
	MP4SetTrackESConfiguration(m_hFileHandle, m_audioID, (BYTE*)strAES.c_str(), strAES.size());

	return true;
}

bool LibMP4::WriteSample(bool bIsVideo, BYTE * lpFrame, int nSize, uint32_t inTimeStamp, uint32_t inRenderOffset, bool bIsKeyFrame)
{
	if( m_hFileHandle == MP4_INVALID_FILE_HANDLE || lpFrame == NULL || nSize <= 0 )
		return false;
	if( bIsVideo && m_videoID == MP4_INVALID_TRACK_ID )
		return false;
	if( !bIsVideo && m_audioID == MP4_INVALID_TRACK_ID )
		return false;
	// ���ļ��л�ȡ��д������...
	m_dwWriteSec = this->GetDurationSecond();
	// ��һ֡���ݱ�������Ƶ�ؼ�֡...
	if( m_bFirstFrame ) {
		// �������Ƶ��������֡��������...
		// ע�⣺���ﲻ��ֱ�Ӵ���Ƶ���������Ƶ������������Ƶ��ͬ������ˣ���Ҫ�Ȼ��棬���ȷʵû����Ƶ�ٴ��̡�
		if( !bIsVideo ) {
			RTMPFrame theFrame;
			theFrame.m_bKeyFrame = bIsKeyFrame;
			theFrame.m_strData.assign((char*)lpFrame, nSize);
			theFrame.m_nTimeStamp = inTimeStamp;
			theFrame.m_nRenderOffset = inRenderOffset;
			m_deqAudio.push_back(theFrame);
			// ���������500֮֡�󣬻�û����Ƶ������Ϊֻ����Ƶ��ֱ�Ӵ���...
			if( m_deqAudio.size() >= 500 ) {
				// ���÷ǵ�һ֡��־...
				m_bFirstFrame = false;
				KH_DeqFrame::iterator itor;
				// ��ʼ�洢�������Ƶ����֡��ʹ�ù̶���֡ʱ����...
				for(itor = m_deqAudio.begin(); itor != m_deqAudio.end(); ++itor) {
					RTMPFrame & myFrame = (*itor);
					if( itor == m_deqAudio.begin() ) {
						m_dwFirstStamp = myFrame.m_nTimeStamp;
					}
					MP4WriteSample(m_hFileHandle, m_audioID, (BYTE*)myFrame.m_strData.c_str(), myFrame.m_strData.size(), MP4_INVALID_DURATION, 0, myFrame.m_bKeyFrame);
					m_dwWriteSize += myFrame.m_strData.size();
					//m_dwWriteRecMS = myFrame.m_nTimeStamp - m_dwFirstStamp;
				}
				// ����֮���ͷ���Ƶ����...
				TRACE("[No Video] Audio-Deque = %d\n", m_deqAudio.size());
				m_deqAudio.clear();
			}
			return true;
		}
		// ��Ƶ�ǹؼ�֡��ֱ�Ӷ���...
		if( !bIsKeyFrame )
			return true;
		// ���÷ǵ�һ֡��־...
		m_bFirstFrame = false;
		m_dwFirstStamp = inTimeStamp;
		// ֮ǰ�������Ƶ���ݣ�ֱ�Ӷ�����������������Ƶ��ͬ��...
		TRACE("[Has Video] Audio-Deque = %d\n", m_deqAudio.size());
		m_deqAudio.clear();
	}
	// ׼��һЩ��ͬ������...
	MP4TrackId  theTrackID = bIsVideo ? m_videoID : m_audioID;
	bool		bWriteFlag = false;
	if( bIsVideo ) { 
		// �ж��Ƿ���Ҫ�����һ֡...
		if( m_VLastFrame.m_strData.size() <= 0 ) {
			m_VLastFrame.m_bKeyFrame = bIsKeyFrame;
			m_VLastFrame.m_strData.assign((char*)lpFrame, nSize);
			m_VLastFrame.m_nTimeStamp = inTimeStamp;
			m_VLastFrame.m_nRenderOffset = inRenderOffset;
			return true;
		}
		// ׼����Ҫ����������...
		int			uFrameMS = inTimeStamp - m_VLastFrame.m_nTimeStamp;
		MP4Duration uDuration = uFrameMS * m_nVideoTimeScale / 1000;
		MP4Duration uOffset = m_VLastFrame.m_nRenderOffset * m_nVideoTimeScale / 1000;
		if( uFrameMS <= 0 ) uDuration = 1;
		//TRACE("Video-Duration = %I64d, offset = %I64d, size = %lu, keyFrame = %d\n", uDuration, uOffset, m_VLastFrame.m_strData.size(), m_VLastFrame.m_bKeyFrame);
		
		// ����д��֡�Ľӿں�������Ƶ��Ҫ����֡���...
		bWriteFlag = MP4WriteSample(m_hFileHandle, theTrackID, (BYTE*)m_VLastFrame.m_strData.c_str(), m_VLastFrame.m_strData.size(), uDuration, uOffset, m_VLastFrame.m_bKeyFrame);
		// ����д��������ʱ��...
		m_dwWriteSize += m_VLastFrame.m_strData.size();
		//m_dwWriteRecMS = inTimeStamp - m_dwFirstStamp;
		
		// ������һ֡�����ݣ��´�ʹ��...
		m_VLastFrame.m_bKeyFrame = bIsKeyFrame;
		m_VLastFrame.m_strData.assign((char*)lpFrame, nSize);
		m_VLastFrame.m_nTimeStamp = inTimeStamp;
		m_VLastFrame.m_nRenderOffset = inRenderOffset;
	} else {
		// ��Ƶ���ݣ�ֱ�ӵ��ýӿ�д�̣���Ƶ���ü���֡���ʱ�䣬���ù̶���֡���...
		bWriteFlag = MP4WriteSample(m_hFileHandle, theTrackID, lpFrame, nSize, MP4_INVALID_DURATION, 0, bIsKeyFrame);
		// ����д��������ʱ��...
		m_dwWriteSize += nSize;
		//m_dwWriteRecMS = ((inTimeStamp >= m_dwFirstStamp) ? (inTimeStamp - m_dwFirstStamp) : 0);
	}
	// ���ش��̽��...
	return bWriteFlag;
}
//
// �����ļ��е�������...
DWORD LibMP4::GetDurationSecond()
{
	DWORD dwTotalSecond = 0;
	if( m_hFileHandle != MP4_INVALID_FILE_HANDLE ) {
		uint32_t dwFileScale = MP4GetTimeScale(m_hFileHandle);
		MP4Duration nDuration = MP4GetDuration(m_hFileHandle);
		dwTotalSecond = nDuration / dwFileScale;
	}
	return dwTotalSecond;
}
