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
 * VS2010�Զ����ɵĶԻ�����ʵ�ִ���
 ******************************************************/

#include "stdafx.h"
#include "sample_libmp4v2.h"
#include "sample_libmp4v2Dlg.h"
#include "afxdialogex.h"

#include "UtilTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	enum { IDD = IDD_ABOUTBOX };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// Csample_libmp4v2Dlg �Ի���
Csample_libmp4v2Dlg::Csample_libmp4v2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Csample_libmp4v2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Csample_libmp4v2Dlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_HOME_WEBSITE, m_ctrlHome);
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Csample_libmp4v2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_PARSE, &Csample_libmp4v2Dlg::OnBnClickedButtonParse)
END_MESSAGE_MAP()

// Csample_libmp4v2Dlg ��Ϣ�������
BOOL Csample_libmp4v2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	
	// ���÷������ӵ�ַ...
	m_ctrlHome.SetUnderline(TRUE);
	m_ctrlHome.SetURL("https://myhaoyi.com");
	m_ctrlHome.SetWindowText("��ϵ���� => https://myhaoyi.com");
	m_ctrlHome.SetLinkCursor(CUtilTool::GetSysHandCursor());
	m_ctrlHome.SetAutoSize();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Csample_libmp4v2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Csample_libmp4v2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR Csample_libmp4v2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void myMP4LogCallback( MP4LogLevel loglevel, const char* fmt, va_list ap)
{
	// ��ϴ��ݹ����ĸ�ʽ...
	CString	strDebug;
	strDebug.FormatV(fmt, ap);
	if( (strDebug.ReverseFind('\r') < 0) && (strDebug.ReverseFind('\n') < 0) ) {
		strDebug.Append("\r\n");
	}
	// ���и�ʽת��������ӡ����...
	string strANSI = CUtilTool::UTF8_ANSI(strDebug);
	TRACE(strANSI.c_str());
}

// ����mp4�ļ�...
void Csample_libmp4v2Dlg::OnBnClickedButtonParse()
{
	// ����MP4���Լ��� => �������ϸ����...
	//MP4LogLevel theLevel = MP4LogGetLevel();
	//MP4LogSetLevel(MP4_LOG_VERBOSE4);
	//MP4SetLogCallback(myMP4LogCallback);
	// ��MP4�ļ�...
	CString strMP4File;
	MP4FileHandle hMP4Handle = MP4_INVALID_FILE_HANDLE;
	strMP4File.Format("%s\\sample.mp4", CUtilTool::GetExePath((HINSTANCE)NULL).c_str());
	string strUTF8 = CUtilTool::ANSI_UTF8(strMP4File);
	hMP4Handle = MP4Read( strUTF8.c_str() );

	// ��ӡMP4�ļ�ȫ·��...
	TRACE("=== %s ===\n", strUTF8.c_str());

	do {
		// ������ļ�ʧ�ܣ�ֱ������...
		if( hMP4Handle == MP4_INVALID_FILE_HANDLE ) {
			TRACE("=== ��MP4�ļ�ʧ�� ===\n");
			break;
		}
		// ����MP4�ļ����������Ƶ��ʽͷ...
		if( !this->doMP4ParseAV(hMP4Handle) ) {
			TRACE("=== ����MP4��ʽͷʧ�� ===\n");
			break;
		}
	} while( false );
	// �ͷ�MP4���...
	if( hMP4Handle != MP4_INVALID_FILE_HANDLE ) {
		MP4Close(hMP4Handle);
		hMP4Handle = MP4_INVALID_FILE_HANDLE;
		TRACE("=== �ر�MP4�ļ��ɹ� ===\n");
	}
}

// ����MP4���������Ƶ����֡...
bool Csample_libmp4v2Dlg::doMP4ParseAV(MP4FileHandle inFile)
{
	if( inFile == MP4_INVALID_FILE_HANDLE )
		return false;
	ASSERT( inFile != MP4_INVALID_FILE_HANDLE );
	
	// ���Ȼ�ȡ�ļ���ÿ��̶������̶ܿ���(���Ǻ�����)...
	uint32_t dwFileScale = MP4GetTimeScale(inFile);
	MP4Duration theDuration = MP4GetDuration(inFile);
	TRACE("=== �ļ�ÿ��̶�����%lu ===\n", dwFileScale);
	TRACE("=== �ļ��̶ܿ�����%lu ===\n", theDuration);
	// �ܺ����� = �̶ܿ���*1000/ÿ��̶��� => �ȳ˷����Խ������...
	uint32_t		dwMP4Duration = theDuration*1000/dwFileScale;
	TRACE("=== �ܺ����� = �ļ��̶ܿ���*1000/�ļ�ÿ��̶��� => %lu ===\n", dwMP4Duration);
	MP4TrackId		tidVideo = MP4_INVALID_TRACK_ID;	// ��Ƶ������
	MP4TrackId		tidAudio = MP4_INVALID_TRACK_ID;	// ��Ƶ������
	string			strSPS, strPPS, strAES;
	int				audio_rate_index = 0;
	int				audio_channel_num = 0;
	int				audio_type = 0;
	uint32_t		audio_time_scale = 0;
	uint32_t		video_time_scale = 0;
	// ��ȡ��Ҫ�������Ϣ...
    uint32_t trackCount = MP4GetNumberOfTracks( inFile );
	TRACE("=== ���ֹ������%lu ===\n", trackCount);
    for( uint32_t i = 0; i < trackCount; ++i ) {
		MP4TrackId  id = MP4FindTrackId( inFile, i );
		const char* type = MP4GetTrackType( inFile, id );
		if( MP4_IS_VIDEO_TRACK_TYPE( type ) ) {
			// ��Ƶ�Ѿ���Ч�������һ��...
			if( tidVideo > 0 )
				continue;
			// ��ȡ��Ƶ��Ϣ...
			tidVideo = id;
			TRACE("=== ��Ƶ����ţ�%d����ʶ��%s ===\n", tidVideo, type);
			char * lpVideoInfo = MP4Info(inFile, id);
			TRACE("��Ƶ��Ϣ��%s \n", lpVideoInfo);
			free(lpVideoInfo);
			// ��ȡ��Ƶʱ����...
			video_time_scale = MP4GetTrackTimeScale(inFile, id);
			TRACE("=== ��Ƶÿ��̶�����%lu ===\n", video_time_scale);
			const char * video_name = MP4GetTrackMediaDataName(inFile, id);
			TRACE("=== ��Ƶ���룺%s ===\n", video_name);
			// ��ȡ��Ƶ��PPS/SPS��Ϣ...
			uint8_t  ** spsHeader = NULL;
			uint8_t  ** ppsHeader = NULL;
			uint32_t  * spsSize = NULL;
			uint32_t  * ppsSize = NULL;
			uint32_t    ix = 0;
			bool bResult = MP4GetTrackH264SeqPictHeaders(inFile, id, &spsHeader, &spsSize, &ppsHeader, &ppsSize);
			for(ix = 0; spsSize[ix] != 0; ++ix) {
				// SPSָ��ͳ���...
				uint8_t * lpSPS = spsHeader[ix];
				uint32_t  nSize = spsSize[ix];
				// ֻ�洢��һ��SPS��Ϣ...
				if( strSPS.size() <= 0 && nSize > 0 ) {
					strSPS.assign((char*)lpSPS, nSize);
				}
				free(spsHeader[ix]);
				TRACE("=== �ҵ��� %d ��SPS��ʽͷ�����ȣ�%lu ===\n", ix+1, nSize);
			}
			free(spsHeader);
			free(spsSize);
			for(ix = 0; ppsSize[ix] != 0; ++ix) {
				// PPSָ��ͳ���...
				uint8_t * lpPPS = ppsHeader[ix];
				uint32_t  nSize = ppsSize[ix];
				// ֻ�洢��һ��PPS��Ϣ...
				if( strPPS.size() <= 0 && nSize > 0 ) {
					strPPS.assign((char*)lpPPS, nSize);
				}
				free(ppsHeader[ix]);
				TRACE("=== �ҵ��� %d ��PPS��ʽͷ�����ȣ�%lu ===\n", ix+1, nSize);
			}
			free(ppsHeader);
			free(ppsSize);
		} else if( MP4_IS_AUDIO_TRACK_TYPE( type ) ) {
			// ��Ƶ�Ѿ���Ч�������һ��...
			if( tidAudio > 0 )
				continue;
			// ��ȡ��Ƶ��Ϣ...
			tidAudio = id;
			TRACE("=== ��Ƶ����ţ�%d����ʶ��%s ===\n", tidVideo, type);
			char * lpAudioInfo = MP4Info(inFile, id);
			TRACE("��Ƶ��Ϣ��%s \n", lpAudioInfo);
			free(lpAudioInfo);

			// ��ȡ��Ƶ������/����/������/������Ϣ...
			audio_type = MP4GetTrackAudioMpeg4Type(inFile, id);
			TRACE("=== ��Ƶ��ʽ���ͣ�%d ===\n", audio_type);
			audio_channel_num = MP4GetTrackAudioChannels(inFile, id);
			TRACE("=== ��Ƶ��������%d ===\n", audio_channel_num);
			const char * audio_name = MP4GetTrackMediaDataName(inFile, id);
			TRACE("=== ��Ƶ���룺%s ===\n", audio_name);
			audio_time_scale = MP4GetTrackTimeScale(inFile, id);
			TRACE("=== ��Ƶÿ��̶���(������)��%lu ===\n", audio_time_scale);
			if (audio_time_scale == 48000)
				audio_rate_index = 0x03;
			else if (audio_time_scale == 44100)
				audio_rate_index = 0x04;
			else if (audio_time_scale == 32000)
				audio_rate_index = 0x05;
			else if (audio_time_scale == 24000)
				audio_rate_index = 0x06;
			else if (audio_time_scale == 22050)
				audio_rate_index = 0x07;
			else if (audio_time_scale == 16000)
				audio_rate_index = 0x08;
			else if (audio_time_scale == 12000)
				audio_rate_index = 0x09;
			else if (audio_time_scale == 11025)
				audio_rate_index = 0x0a;
			else if (audio_time_scale == 8000)
				audio_rate_index = 0x0b;
			TRACE("=== ��Ƶ�����ʱ�ţ�%lu ===\n", audio_rate_index);
			// ��ȡ��Ƶ��չ��Ϣ...
            uint8_t  * pAES = NULL;
            uint32_t   nSize = 0;
            bool haveEs = MP4GetTrackESConfiguration(inFile, id, &pAES, &nSize);
			// �洢��Ƶ��չ��Ϣ...
			if( strAES.size() <= 0 && nSize > 0 ) {
				strAES.assign((char*)pAES, nSize);
			}
			TRACE("=== ��Ƶ��չ��Ϣ���ȣ�%lu ===\n", nSize);
			// �ͷŷ���Ļ���...
			if( pAES != NULL ) {
				free(pAES);
				pAES = NULL;
			}
		}
	}
	// �����Ƶ����Ƶ��û�У�����ʧ��...
	if((tidVideo == MP4_INVALID_TRACK_ID) && (tidAudio == MP4_INVALID_TRACK_ID)) {
		MsgLogGM(GM_File_Read_Err);
		return false;
	}
	// һ��������ѭ����ȡ����Ƶ����֡...
	return this->doMP4ReadFrame(inFile, tidVideo, tidAudio);
}

// ѭ����ȡ����Ƶ����֡...
bool Csample_libmp4v2Dlg::doMP4ReadFrame(MP4FileHandle inFile, MP4TrackId inVideoID, MP4TrackId inAudioID)
{
	BOOL		bAudioComplete = false;
	BOOL		bVideoComplete = false;
	uint32_t	dwOutVSendTime = 0;
	uint32_t	dwOutASendTime = 0;
	uint32_t	iVSampleInx = 1;
	uint32_t	iASampleInx = 1;
	while( true ) {
		// ��ȡһ֡��Ƶ֡...
		if( !bVideoComplete && !this->doMP4ReadOneFrame(inFile, inVideoID, iVSampleInx++, true, dwOutVSendTime) ) {
			bVideoComplete = true;
			continue;
		}
		// ��ȡһ֡��Ƶ֡...
		if( !bAudioComplete && !this->doMP4ReadOneFrame(inFile, inAudioID, iASampleInx++, false, dwOutASendTime) ) {
			bAudioComplete = true;
			continue;
		}
		// �����Ƶ����Ƶȫ���������˳�ѭ��...
		if( bVideoComplete && bAudioComplete ) {
			TRACE("=== MP4�ļ�����֡��ȡ��� ===\n");
			TRACE("=== �Ѷ�ȡ��Ƶ֡��%lu ===\n", iVSampleInx);
			TRACE("=== �Ѷ�ȡ��Ƶ֡��%lu ===\n", iASampleInx);
			break;
		}
	}
	return true;
}

// ��ȡһ֡��Ƶ����Ƶ����֡...
bool Csample_libmp4v2Dlg::doMP4ReadOneFrame(MP4FileHandle inFile, MP4TrackId tid, uint32_t sid, bool bIsVideo, uint32_t & outSendTime)
{
	uint8_t		*	pSampleData = NULL;		// ֡����ָ��
	uint32_t		nSampleSize = 0;		// ֡���ݳ���
	MP4Timestamp	nStartTime = 0;			// ��ʼʱ��
	MP4Duration		nDuration = 0;			// ����ʱ��
	MP4Duration     nOffset = 0;			// ƫ��ʱ��
	bool			bIsKeyFrame = false;	// �Ƿ�ؼ�֡
	uint32_t		timescale = 0;
	uint64_t		msectime = 0;

	// ��ȡ����Ĳ����� �� ��ǰ֡��ʱ���...
	timescale = MP4GetTrackTimeScale( inFile, tid );
	msectime = MP4GetSampleTime( inFile, tid, sid );

	// ��ȡһ֡����֡��ʧ�ܣ�ֱ�ӷ���...
	if( false == MP4ReadSample(inFile, tid, sid, &pSampleData, &nSampleSize, &nStartTime, &nDuration, &nOffset, &bIsKeyFrame) )
		return false;

	// ���㵱ǰ��ȡ����֡��ʱ���...
	// ���㷢��ʱ�� => PTS => �̶�ʱ��ת���ɺ���...
	msectime *= UINT64_C( 1000 );
	msectime /= timescale;
	// ���㿪ʼʱ�� => DTS => �̶�ʱ��ת���ɺ���...
	nStartTime *= UINT64_C( 1000 );
	nStartTime /= timescale;
	// ����ƫ��ʱ�� => CTTS => �̶�ʱ��ת���ɺ���...
	nOffset *= UINT64_C( 1000 );
	nOffset /= timescale;
	// ֡����ʱ�� => �̶�ʱ��ת���ɺ���...
	nDuration *= UINT64_C( 1000 );
	nDuration /= timescale;

	// ������Ҫ�ͷŶ�ȡ�Ļ�����...
	MP4Free(pSampleData);
	pSampleData = NULL;

	// ���ط���ʱ��(����) => �ѽ��̶�ʱ��ת�����˺���...
	outSendTime = (uint32_t)msectime;
	
	// ��ӡ��ȡ������Ƶ����֡������Ϣ...
	TRACE("[%s] duration = %I64d, offset = %I64d, KeyFrame = %d, SendTime = %lu, StartTime = %I64d, Size = %lu\n", bIsVideo ? "Video" : "Audio", nDuration, nOffset, bIsKeyFrame, outSendTime, nStartTime, nSampleSize);

	return true;
}