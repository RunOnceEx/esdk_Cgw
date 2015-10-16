#ifndef CBB_PS_PROTOCOL_HEAD
#define CBB_PS_PROTOCOL_HEAD

//PS��ͷ��ʼ��ʶ�� 00 00 01 BA
const unsigned char PS_PACK_START_CODE[4] = {0x00, 0x00, 0x01, 0xBA};
//PS��ϵͳͷ��ʼ��ʶ�� 00 00 01 BB
const unsigned char PS_SYSTEM_PACK_START_CODE[4] = {0x00, 0x00, 0x01, 0xBB};
//PES����ʼ��ʶ��
const unsigned char PES_START_CODE[3] = {0x00, 0x00, 0x01};

const unsigned int VIDEO_BUF_LEN = 1204*1024;
const unsigned int AUDIO_BUF_LEN = 8*1024;
const unsigned int PS_PACKET_LEN = 1024*1024;
const unsigned int PES_PLAYLOAD_LEN = 5114;//�����豸ץ�����������ֵ

//iso13818�淶 P33 ����ϸ˵��
typedef enum STREAM_ID
{
    PES_PROGRAM_STREAM_MAP       = 0xbc,
    PES_PRIVATE_STREAM_1         = 0xbd,
    PES_PADDING_STREAM           = 0xbe,
    PES_PRIVATE_STREAM_2         = 0xbf,
    PES_ECM_STREAM               = 0xf0,
    PES_EMM_STREAM               = 0xf1,
    PES_ITUT_STREM               = 0xf2,
    PES_ISO13522_STREAM          = 0xf3,
    PES_H222A_STREAM             = 0xf4,
    PES_H222B_STREAM             = 0xf5,
    PES_H222C_STREAM             = 0xf6,
    PES_H222D_STREAM             = 0xf7,
    PES_H2221_STREAM             = 0xf8,
    PES_ANCILLARY_STREAM         = 0xf9,
    PES_ISO14496SL_STREAM        = 0xfa,
    PES_ISO14496FM_STREAM        = 0xfb,
    PES_PROGRAM_STREAM_DIRECTORY = 0xff,

    // 110x xxxx ISO/IEC 13818-3 or ISO/IEC 11172-3 or ISO/IEC 13818-7 or ISO/IEC
    //			 14496-3 audio stream number x xxxx
    PES_ISO13818_FOOT            = 0xc0,  // 192��Ƶ��
    PES_ISO13818_TOP             = 0xdf,   // 223

    // 1110 xxxx ITU-T Rec. H.262 | ISO/IEC 13818-2 or ISO/IEC 11172-2 or ISO/IEC
    //			 14496-2 video stream number xxxx
    PES_H262_FOOT                = 0xe0,//��Ƶ��
    PES_H262_TOP                 = 0xef
}STREAM_ID_E;

#pragma pack(push, 1)
//PS��ͷ 00 00 01 BA ��ʼ
typedef struct PS_PACK_HEADER
{
    unsigned char pack_start_code[4];
    //-------------������ֿ�
    unsigned char marker_bit_extension                  :1;
    unsigned short system_clock_reference_extension     :9;
    unsigned char marker_bit_low                        :1;
    unsigned short system_clock_reference_base_low      :15;
    unsigned char marker_bit_middle                     :1;
    unsigned short system_clock_reference_base_middle   :15;
    unsigned char marker_bit_high                       :1;
    unsigned char system_clock_reference_base_high      :3;
    unsigned char fixedValue                            :2;//'01'
    //-------------������ֿ�
    unsigned char marker_bit_rate_2                     :1;
    unsigned char marker_bit_rate_1                     :1;
    unsigned int program_mux_rate                       :22;
    //-------------������ֿ�
    unsigned char pack_stuffing_length                  :3;
    unsigned char reserved                              :5;
}PS_PACK_HEADER_S, *LPPS_PACK_HEADER_S;

//PSϵͳͷ
typedef struct PS_SYSTEM_HEADER
{
    unsigned char system_header_start_code[4];
    unsigned short header_length;
    //-------------������ֿ�
    unsigned int marker_bit_rate              :1;
    unsigned int rate_bound                   :22;
    unsigned int marker_bit_length            :1;
    //-------------������ֿ�
    unsigned int CSPS_flag                    :1;
    unsigned int fixed_flag                   :1;
    unsigned int audio_bound                  :6;
    //-------------������ֿ�
    unsigned int video_bound                  :5;
    unsigned int marker_bit_flag              :1;
    unsigned int system_video_lock_flag       :1;
    unsigned int system_audio_lock_flag       :1;
    //-------------������ֿ�
    unsigned int reserved_bits                :7;
    unsigned int packet_rate_restriction_flag :1;
}PS_SYSTEM_HEADER_S, *LPPS_SYSTEM_HEADER_S;

//PES��ͷ ������ֽ��򶼸����ֽ��������������ת�������ĵ���΢�е���
typedef struct PES_PACK_PES_HEADER
{
    //�����޸Ĳ�����������߷����õ���ֵһ��
    char packet_start_code_prefix[3];
    unsigned char stream_id;
    //-------------������ֿ�
    unsigned short PES_packet_length;
    //-------------������ֿ�
    unsigned char original_or_copy            :1;//1
    unsigned char copyright                   :1;
    unsigned char data_alignment_indicator    :1;
    unsigned char PES_priority                :1;
    unsigned char PES_scrambling_control      :2;
    unsigned char fixValue                    :2; //'10'
    //-------------������ֿ�
    unsigned char PES_extension_flag          :1;//1
    unsigned char PES_CRC_flag                :1;
    unsigned char additional_copy_info_flag   :1;
    unsigned char DSM_trick_mode_flag         :1;
    unsigned char ES_rate_flag                :1;
    unsigned char ESCR_flag                   :1;
    unsigned char PTS_DTS_flags               :2;

    unsigned char PES_header_data_length;
}PES_PACK_PES_HEADER_S, *LPPES_PACK_PES_HEADER_S;

typedef struct PES_PTS
{
    //-------------������ֿ�
    unsigned char marker_bit_high             :1;
    unsigned char PTS_high                    :3;
    unsigned char PTS_FIX_VALUE               :4;//0010
    //-------------������ֿ�
    unsigned char marker_bit_middle           :1;
    unsigned short PTS_middle                 :15;
    //-------------������ֿ�
    unsigned char marker_bit_low              :1;
    unsigned short PTS_low                    :15;
}PES_PTS_S, *LPPES_PTS_S;

typedef struct PES_DTS
{
    //-------------������ֿ�
    unsigned char marker_bit_high             :1;
    unsigned char DTS_high                    :3;
    unsigned char DTS_FIX_VALUE               :4;//0011
    //-------------������ֿ�
    unsigned char marker_bit_middle           :1;
    unsigned short DTS_middle                 :15;
    //-------------������ֿ�
    unsigned char marker_bit_low              :1;
    unsigned short DTS_low                    :15;
}PES_DTS_S, *LPPES_DTS_S;
#pragma pack(pop)

#endif //CBB_PS_PROTOCOL_HEAD