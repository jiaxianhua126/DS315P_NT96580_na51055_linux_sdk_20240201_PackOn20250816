/* 语音识别 */
#include "aiengine.h"
#include "DxASR.h"
#include "PStore.h"
#include "PrjInc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <kwrap/type.h>
#include "ImageApp/ImageApp_MovieMulti.h"

#if defined(_UI_STYLE_SPORTCAM_)
#include "UIWnd/SPORTCAM/UIInfo/UIInfo.h"
#elif defined(_UI_STYLE_LVGL_)
#include "UIWnd/LVGL_SPORTCAM/UIInfo/UIInfo.h"
#else
	#error "Unknown UI Style, please check UI_Style in nvt-info.dtsi"
#endif
#include <pthread.h>
#define Test_Param    0
const char *engineCfg_en = "{\
                        \"appKey\":\"279615564\",\
                        \"secretKey\":\"1eab70e50f71bb856d441c5dc0927a70\",\
                        \"provision\":\"/root/test/aiengine-2.9.5-279615564.provision\",\
                        \"serialNumber\":\"/root/test/aiengine-2.9.5-279615564.serialNumber\",\
                        \"version\":\"aiengine-2.9.5\",\
                        \"licensesPath\":\"./cfgbatch.authorization\",\
                        \"native\":{\
                            \"cn.wakeup\":{\
                                \"resBinPath\":\"/root/res/_wkp_aicar_eng_20210422_v4.2.bin\"\
                            }\
                        }\
                    }";
const char *engineCfg_japan = "{\
                        \"appKey\":\"279615564\",\
                        \"secretKey\":\"1eab70e50f71bb856d441c5dc0927a70\",\
                        \"provision\":\"/root/test/aiengine-2.9.5-279615564.provision\",\
                        \"serialNumber\":\"/root/test/aiengine-2.9.5-279615564.serialNumber\",\
                        \"version\":\"aiengine-2.9.5\",\
                        \"licensesPath\":\"/root/test/96580ASR.txt\",\
                        \"native\":{\
                            \"cn.wakeup\":{\
                                \"resBinPath\":\"/root/res/_wkp_aicar_japanV2_20210422_v3.bin\"\
                            }\
                        }\
                    }";

const char *engineCfg_ch = "{\
                        \"appKey\":\"279615564\",\
                        \"secretKey\":\"1eab70e50f71bb856d441c5dc0927a70\",\
                        \"provision\":\"/root/test/aiengine-2.9.5-279615564.provision\",\
                        \"serialNumber\":\"/root/test/aiengine-2.9.5-279615564.serialNumber\",\
                        \"version\":\"aiengine-2.9.5\",\
                        \"licensesPath\":\"./cfgbatch.authorization\",\
                        \"native\":{\
                            \"cn.wakeup\":{\
                                \"resBinPath\":\"/root/res/_res_ori_fsmn_h4n256p64_cus.bin\"\
                            }\
                        }\
                    }";
const char *engineCfg_rus = "{\
                        \"appKey\":\"279615564\",\
                        \"secretKey\":\"1eab70e50f71bb856d441c5dc0927a70\",\
                        \"provision\":\"/root/test/aiengine-2.9.5-279615564.provision\",\
                        \"serialNumber\":\"/root/test/aiengine-2.9.5-279615564.serialNumber\",\
                        \"version\":\"aiengine-2.9.5\",\
                        \"licensesPath\":\"./cfgbatch.authorization\",\
                        \"native\":{\
                            \"cn.wakeup\":{\
                                \"resBinPath\":\"/root/res/_wkp_aicar_rus_20210809_v2.1.bin\"\
                            }\
                        }\
                    }";
const char *engineCfg_th = "{\
                        \"appKey\":\"279615564\",\
                        \"secretKey\":\"1eab70e50f71bb856d441c5dc0927a70\",\
                        \"provision\":\"/root/test/aiengine-2.9.5-279615564.provision\",\
                        \"serialNumber\":\"/root/test/aiengine-2.9.5-279615564.serialNumber\",\
                        \"version\":\"aiengine-2.9.5\",\
                        \"licensesPath\":\"./cfgbatch.authorization\",\
                        \"native\":{\
                            \"cn.wakeup\":{\
                                \"resBinPath\":\"/root/res/_wkp_aicar_tha_20210422_v3_2.bin\"\
                            }\
                        }\
                    }";
#if(!Test_Param)
char *param_en = "{\"request\":{\"env\":\"words=kw1,kw2,kw3,kw4,kw5,kw6,kw7,kw8,kw9,kw10,kw11,kw14,kw16,kw12,kw13,kw15,kw17;thresh=0.5,0.37,0.13,0.45,0.25,0.29,0.34,0.35,0.27,0.25,0.31,0.25,0.34,0.2,0.35,0.2,0.35;\"}}";

char *param_japan = "{\"request\":{\"env\":\"words=kw6,kw7,kw10,kw11,kw14,kw15,kw1,kw2,kw3,kw4,kw5,kw8,kw9,kw12,kw13,kw16,kw17;thresh=0.38,0.31,0.53,0.62,0.31,0.4,0.45,0.5,0.47,0.5,0.44,0.55,0.65,0.6,0.33,0.45,0.35;\"}}";

char * param_ch = "{\"request\":{\"env\":\"words=wo yao pai zhao,wo yao lu xiang,guan bi ping mu,da kai ping mu,da kai lu yin,guan bi lu yin,da kai re dian,guan bi re dian,da kai qian lu,xian shi qian lu,da kai hou lu,xian shi hou lu,zhua pai zhao pian,da kai nei lu,cha kan quan bu,shi pin jia suo,fan hui zhu ye,da kai wai fa,guan bi wai fa;thresh=0.32,0.32,0.31,0.31,0.28,0.28,0.29,0.25,0.27,0.21,0.21,0.21,0.25,0.22,0.21,0.20,0.8,0.25,0.20;\"}}";

char * param_rus = "{\"request\":{\"env\":\"words=kw1,kw2,kw4,kw5,kw6,kw7,kw8,kw9,kw10,kw11,kw12,kw13,kw14,kw15,kw16,kw17;thresh=0.88,0.57,0.13,0.18,0.14,0.43,0.16,0.29,0.6,0.63,0.4,0.25,0.34,0.89,0.4,0.87;\"}}";

char * param_thai = "{\"request\":{\"env\":\"words=kw1,kw2,kw4,kw5,kw6,kw7,kw8,kw9,kw10,kw11,kw12,kw13,kw14,kw15,kw16,kw17;thresh=0.77,0.76,0.41,0.17,0.45,0.64,0.8,0.25,0.27,0.32,0.5,0.5,0.81,0.5,0.5,0.78;\"}}";
#endif
//char * param_thai = "{\"request\":{\"env\":\"words=kw1,kw2,kw4,kw5,kw6,kw7,kw8,kw9,kw10,kw11,kw12,kw13,kw14,kw15,kw16,kw17;thresh=0.77,0.76,0.41,0.17,0.45,0.64,0.8,0.25,0.27,0.3,0.5,0.5,0.81,0.5,0.5,0.78;\"}}";

//char * param_vie = "{\"request\":{\"env\":\"words=kw1,kw2,kw4,kw5,kw6,kw7,kw8,kw9,kw10,kw11,kw12,kw13,kw14,kw15,kw16,kw17;thresh=0.82,0.48,0.8,0.4,0.82,0.75,0.88,0.71,0.81,0.55,0.94,0.6,0.95,0.95,0.92,0.46;\"}}";

//俄语words=kw1,kw2,kw4,kw5,kw6,kw7,kw8,kw9,kw10,kw11,kw12,kw13,kw14,kw15,kw16,kw17;thresh=0.54,0.71,0.56,0.44,0.48,0.46,0.60,0.30,0.21,0.47,0.50,0.37,0.41,0.62,0.80,0.53;
//泰语words=kw1,kw2,kw4,kw5,kw6,kw7,kw8,kw9,kw10,kw11,kw12,kw13,kw14,kw15,kw16,kw17;thresh=0.77,0.76,0.41,0.17,0.45,0.64,0.8,0.25,0.27,0.3,0.5,0.5,0.81,0.5,0.5,0.78;
//越南语words=kw1,kw2,kw4,kw5,kw6,kw7,kw8,kw9,kw10,kw11,kw12,kw13,kw14,kw15,kw16,kw17;thresh=0.82,0.48,0.8,0.4,0.82,0.75,0.88,0.71,0.81,0.55,0.94,0.6,0.95,0.95,0.92,0.46;

int g_wakeup_flag = 0;
static pthread_t asr_id;
static UINT32 ASR_SelectMode;
BOOL ASR_GetPCMData_EN = FALSE;
BOOL ASR_OpenState = FALSE;
BOOL ASR_Pstroe_Exist = FALSE;
pAsr_SerialNumber pASN = {0};
//BOOL ASR_Abnormal = FALSE;
#if 0//(defined(_EMBMEM_EMMC_) && FS_MULTI_STRG_FUNC==DISABLE && !defined(__FREERTOS))
#define MOUNT_FS_ROOT        "/mnt/emmc1/"
#else
#define MOUNT_FS_ROOT        "/mnt/sd2/"
#endif

#define ASR_URL_PATH   MOUNT_FS_ROOT"asr_url.txt"
#define ASR_SERIAL_PATH   MOUNT_FS_ROOT"asr_serialnumber.txt"

#define PRI_ASRRECEIVE            20
#define STKSIZE_ASRRECEIVE        6144//64KB stack size

// ASR Pstore
#define PS_ASR  "ASR"
#define SERIALNUMBER_MAXSIZE   24
#if Test_Param
//可以优化成数组
#define ASR_PARAM_PATH MOUNT_FS_ROOT"asr_param.txt"

static char param_en[200];
static char param_japan[200];
static char param_ch[500];
static char param_rus[200];
static char param_thai[200];
static char param_data[200];
static UINT32 kw1 = 0;
static UINT32 kw2 = 0;
static UINT32 kw3 = 0;
static UINT32 kw4 = 0;
static UINT32 kw5 = 0;
static UINT32 kw6 = 0;
static UINT32 kw7 = 0;
static UINT32 kw8 = 0;
static UINT32 kw9 = 0;
static UINT32 kw10 = 0;
static UINT32 kw11 = 0;
static UINT32 kw12 = 0;
static UINT32 kw13 = 0;
static UINT32 kw14 = 0;
static UINT32 kw15 = 0;
static UINT32 kw16 = 0;
static UINT32 kw17 = 0;
static UINT32 ch1 = 0;
static UINT32 ch2 = 0;
static UINT32 ch3 = 0;
static UINT32 ch4 = 0;
static UINT32 ch5 = 0;
static UINT32 ch6 = 0;
static UINT32 ch7 = 0;
static UINT32 ch8 = 0;
static UINT32 ch9 = 0;
static UINT32 ch10 = 0;
static UINT32 ch11 = 0;
static UINT32 ch12 = 0;
static UINT32 ch13 = 0;
static UINT32 ch14 = 0;
static UINT32 ch15 = 0;
static UINT32 ch16 = 0;
static UINT32 ch17 = 0;
static UINT32 ch18 = 0;
static UINT32 ch19 = 0;
BOOL param_en_flag = FALSE;
BOOL param_japan_flag = FALSE;
BOOL param_ch_flag = FALSE;
BOOL param_rus_flag = FALSE;
BOOL param_thai_flag = FALSE;
void Clear_data(void)
{
    kw1 = 0;
    kw2 = 0;
    kw3 = 0;
    kw4 = 0;
    kw5 = 0;
    kw6 = 0;
    kw7 = 0;
    kw8 = 0;
    kw9 = 0;
    kw10 = 0;
    kw11 = 0;
    kw12 = 0;
    kw13 = 0;
    kw14 = 0;
    kw15 = 0;
    kw16 = 0;
    kw17 = 0;
    ch1 = 0;
    ch2 = 0;
    ch3 = 0;
    ch4 = 0;
    ch5 = 0;
    ch6 = 0;
    ch7 = 0;
    ch8 = 0;
    ch9 = 0;
    ch10 = 0;
    ch11 = 0;
    ch12 = 0;
    ch13 = 0;
    ch14 = 0;
    ch15 = 0;
    ch16 = 0;
    ch17 = 0;
    ch18 = 0;
    ch19 = 0;
}

void Asr_Test_Param(void)
{
    FILE *test_fp;
    int i = 0;
    char Asr_TestParam[500] = {0};
    bzero(param_en,sizeof(param_en));
    bzero(param_japan,sizeof(param_japan));
    bzero(param_ch,sizeof(param_ch));
    bzero(param_rus,sizeof(param_rus));
    bzero(param_thai,sizeof(param_thai));
    test_fp = fopen(ASR_PARAM_PATH,"r+");
    if (test_fp == NULL) {
        printf("open %sasr_param fail \r\n",MOUNT_FS_ROOT);
    } else {
        while (fgets(Asr_TestParam,sizeof(Asr_TestParam),test_fp)) {
            i = i + 1;
            Asr_TestParam[strlen(Asr_TestParam)-1] = '\0';
            switch (i) {
            case 1:
                strncpy(param_en,Asr_TestParam,strlen(Asr_TestParam));
                printf("\n");
                printf("********************************English*******************************\r\n");
                printf("call param_en = %s\r\n",param_en);
                printf("********************************English*******************************\r\n");
                printf("\n");
                break;
            case 2:
                strncpy(param_japan,Asr_TestParam,strlen(Asr_TestParam));
                printf("\n");
                printf("********************************Japan*******************************\r\n");
                printf("call param_japan = %s\r\n",param_japan);
                printf("********************************Japan*******************************\r\n");
                printf("\n");
                break;
            case 3:
                strncpy(param_ch,Asr_TestParam,strlen(Asr_TestParam));
                printf("\n");
                printf("********************************Chinese*******************************\r\n");
                printf("call param_ch = %s\r\n",param_ch);
                printf("********************************Chinese*******************************\r\n");
                printf("\n");
                break;
            case 4:
                strncpy(param_rus,Asr_TestParam,strlen(Asr_TestParam));
                printf("\n");
                printf("********************************Russian*******************************\r\n");
                printf("call param_rus = %s\r\n",param_rus);
                printf("********************************Russian*******************************\r\n");
                printf("\n");
                break;
            case 5:
                strncpy(param_thai,Asr_TestParam,strlen(Asr_TestParam));
                printf("\n");
                printf("********************************Thai*******************************\r\n");
                printf("call param_thai = %s\r\n",param_thai);
                printf("********************************Thai*******************************\r\n");
                printf("\n");
                break;
            }
        }
        fclose(test_fp);
    }
}

void Test_KW(char *param)
{
    char kw[30] = {0};
    char test_language[10] = {0};
    int test_kw_fd;
    switch(ASR_SelectMode) {
    case LANG_SC:
    case LANG_TC:
        strcpy(test_language,"ch");
        break;
    case LANG_EN:
        strcpy(test_language,"en");
        break;
    case LANG_JP:
        strcpy(test_language,"jp");
        break;
    case LANG_RU:
        strcpy(test_language,"rus");
        break;
    case LANG_TH:
        strcpy(test_language,"thai");
        break;
    default:
        break;
    }
    if ((0 == strcmp(param,"kw1"))){
        kw1 ++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,kw1);
    } else if ((0 == strcmp(param,"kw2"))) {
        kw2 ++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,kw2);
    } else if ((0 == strcmp(param,"kw3"))) {
        kw3 ++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,kw3);
    } else if ((0 == strcmp(param,"kw4"))) {
        kw4 ++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,kw4);
    } else if ((0 == strcmp(param,"kw5"))) {
        kw5 ++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,kw5);
    } else if ((0 == strcmp(param,"kw6"))) {
        kw6 ++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,kw6);
    } else if ((0 == strcmp(param,"kw7"))) {
        kw7 ++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,kw7);
    } else if ((0 == strcmp(param,"kw8"))) {
        kw8 ++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,kw8);
    } else if ((0 == strcmp(param,"kw9"))) {
        kw9 ++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,kw9);
    } else if ((0 == strcmp(param,"kw10"))) {
        kw10 ++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,kw10);
    } else if ((0 == strcmp(param,"kw11"))) {
        kw11 ++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,kw11);
    } else if ((0 == strcmp(param,"kw12"))) {
        kw12 ++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,kw12);
    } else if ((0 == strcmp(param,"kw13"))) {
        kw13 ++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,kw13);
    } else if ((0 == strcmp(param,"kw14"))) {
        kw14 ++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,kw14);
    } else if ((0 == strcmp(param,"kw15"))) {
        kw15 ++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,kw15);
    } else if ((0 == strcmp(param,"kw16"))) {
        kw16 ++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,kw16);
    } else if ((0 == strcmp(param,"kw17"))) {
        kw17 ++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,kw17);
    } else if ((0 == strcmp(param,"wo yao pai zhao"))){
        ch1++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,ch1);
    } else if ((0 == strcmp(param,"wo yao lu xiang"))) {
        ch2++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,ch2);
    } else if ((0 == strcmp(param,"guan bi ping mu"))) {
        ch3++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,ch3);
    } else if ((0 == strcmp(param,"da kai ping mu"))) {
        ch4++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,ch4);
    } else if ((0 == strcmp(param,"da kai lu yin"))) {
        ch5++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,ch5);
    } else if ((0 == strcmp(param,"guan bi lu yin"))) {
        ch6++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,ch6);
    } else if ((0 == strcmp(param,"da kai re dian"))) {
        ch7++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,ch7);
    } else if ((0 == strcmp(param,"guan bi re dian"))) {
        ch8++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,ch8);
    } else if ((0 == strcmp(param,"da kai qian lu"))) {
        ch9++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,ch9);
    } else if ((0 == strcmp(param,"xian shi qian lu"))) {
        ch10++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,ch10);
    } else if ((0 == strcmp(param,"da kai hou lu"))) {
        ch11++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,ch11);
    }else if ((0 == strcmp(param,"xian shi hou lu"))) {
        ch12++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,ch12);
    }else if ((0 == strcmp(param,"zhua pai zhao pian"))) {
        ch13++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,ch13);
    }else if ((0 == strcmp(param,"da kai nei lu"))) {
        ch14++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,ch14);
    }else if ((0 == strcmp(param,"cha kan quan bu"))) {
        ch15++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,ch15);
    }else if ((0 == strcmp(param,"fan hui zhu ye"))) {
        ch16++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,ch16);
    }else if ((0 == strcmp(param,"shi pin jia suo"))) {
        ch17++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,ch17);
    } else if ((0 == strcmp(param,"da kai wai fa"))) {
        ch18++;
        sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,ch18);
    } else if ((0 == strcmp(param,"guan bi wai fa"))) {
        ch19++;
       sprintf(kw,"%s%s_%s_%d.txt",MOUNT_FS_ROOT,test_language,param,ch19);
    } 

    test_kw_fd = open(kw,O_RDWR|O_CREAT|O_EXCL);
    if (test_kw_fd < 0) {
        printf("open en_kw1 error\r\n");
    } else {
        write(test_kw_fd,param_data,strlen(param_data));
        fsync(test_kw_fd);
        close(test_kw_fd);
    }    
}

#endif


//判断字符串
UINT8 Ch_String_Check(char *arg)
{
    if ((0 == strcmp(arg,"wo yao pai zhao"))){
        return ASR_PHOTO;
    } else if ((0 == strcmp(arg,"wo yao lu xiang"))) {
        return ASR_STARTVIDEO;
    } else if ((0 == strcmp(arg,"guan bi ping mu"))) {
        return ASR_CLOSELCD;
    } else if ((0 == strcmp(arg,"da kai ping mu"))) {
        return ASR_OPENLCD;
    } else if ((0 == strcmp(arg,"da kai lu yin"))) {
        return ASR_ENRECODING;
    } else if ((0 == strcmp(arg,"guan bi lu yin"))) {
        return ASR_DISRECODING;
    } else if ((0 == strcmp(arg,"da kai re dian"))) {
        return ASR_OPENAP;
    } else if ((0 == strcmp(arg,"guan bi re dian"))) {
        return ASR_CLOSEAP;
    } else if ((0 == strcmp(arg,"da kai qian lu"))) {
        return ASR_OPENAHEAD;
    } else if ((0 == strcmp(arg,"xian shi qian lu"))) {
        return ASR_OPENAHEAD;
    } else if ((0 == strcmp(arg,"da kai hou lu"))) {
        return ASR_OPENBACK;
    }else if ((0 == strcmp(arg,"shi pin jia suo"))) {
        return ASR_VLOCKING;
    } else if ((0 == strcmp(arg,"da kai wai fa"))) {
        return ASR_OPENWIFI;
    } else if ((0 == strcmp(arg,"guan bi wai fa"))) {
        return ASR_CLOSEWIFI;
    } else {
        return 0;
    }
}

//判断字符串
UINT8 Foreign_String_Check(char *arg)
{
    if ((0 == strcmp(arg,"kw1"))){
        return ASR_PHOTO;
    } else if ((0 == strcmp(arg,"kw2"))) {
        return ASR_STARTVIDEO;
    } else if ((0 == strcmp(arg,"kw3"))) {
        return ASR_CLOSEVIDEO;
    } else if ((0 == strcmp(arg,"kw4"))) {
        return ASR_ENRECODING;
    } else if ((0 == strcmp(arg,"kw5"))) {
        return ASR_DISRECODING;
    } else if ((0 == strcmp(arg,"kw6"))) {
        return ASR_OPENLCD;
    } else if ((0 == strcmp(arg,"kw7"))) {
        return ASR_CLOSELCD;
    } else if ((0 == strcmp(arg,"kw8"))) {
        return ASR_OPENWIFI;
    } else if ((0 == strcmp(arg,"kw9"))) {
        return ASR_CLOSEWIFI;
    } else if ((0 == strcmp(arg,"kw10"))) {
        return ASR_OPENAHEAD;
    } else if ((0 == strcmp(arg,"kw11"))) {
        return ASR_OPENBACK;
    } else if ((0 == strcmp(arg,"kw12"))) {
        return ASR_OPENAP;
    } else if ((0 == strcmp(arg,"kw13"))) {
        return ASR_CLOSEAP;
    } else if ((0 == strcmp(arg,"kw14"))) {
        return ASR_SHOWALL;
    } else if ((0 == strcmp(arg,"kw15"))) {
        return ASR_VLOCKING;
    } else if ((0 == strcmp(arg,"kw16"))) {
        return ASR_INSIDE_VIDEO;
    } else if ((0 == strcmp(arg,"kw17"))) {
        return ASR_BACK_TOHOMEPAGE;
    } else {
        return 0;
    }
}


//联咏获取PCM数据接口
ER AudioIn_FrameGet(UINT32 aichn,char *data_buff,UINT32 *data_len)
{
    ER ret = 0;
    ret =  ImageApp_MovieMulti_AudCapGetFrame(0,(UINT8 *)data_buff,data_len,200);
    return ret;
}

#if 0
int aiengine_get_device_id(char deviceId[64], int size) 
{
    memset(deviceId,0,64);
    strcpy(deviceId,"96580imx675r43001");
    printf("deviceId : %s,len = %d\r\n",deviceId,size);
    return 12;
}
#endif
int getSerialNumber(void *userdata, const char *url, char **response)
{
    int asr_url_fd;
    int serial_fp;
    UINT32 Asr_Result;
    FILE *asr_serial_fd;
    //int asr_ret;
    char *Check_urlDeviceId;
    char UrlDeviceId[20] = {0};
    char Asr_serialData[100] = {0};
    char *Check_serialNumber;
    char asr_serialNumber[50] = {0};
    char body[250] = {0};
    PPSTORE_SECTION_HANDLE  AsrSection;
    //读取ASR Pstore中的值
    if (ASR_Pstroe_Exist) {
        if ((AsrSection = PStore_OpenSection(PS_ASR, PS_RDWR)) != E_PS_SECHDLER) {
            Asr_Result = PStore_ReadSection((UINT8 *)&pASN, 0, sizeof(pASN), AsrSection);
            //printf("call 1getSerialNumber pASN.Asr_SerialNumber_Flag = %d\r\n",pASN.Asr_SerialNumber_Flag);
            //printf("call 1getSerialNumber pASN.SerialNumber = %s\r\n",pASN.SerialNumber);
            PStore_CloseSection(AsrSection);
        }
    }
    //获取在线url网址存在SD卡中,将新的
    if (!pASN.Asr_SerialNumber_Flag) {
        asr_url_fd = open(ASR_URL_PATH,(O_CREAT | O_RDWR | O_EXCL));
        if (asr_url_fd < 0) {
            printf("call open url.txt error or url.txt exist\r\n");
        } else {
            write(asr_url_fd,url,strlen(url));
            fsync(asr_url_fd);
            close(asr_url_fd);
            //写入device id
            bzero(UrlDeviceId,sizeof(UrlDeviceId));
            bzero(asr_serialNumber,sizeof(asr_serialNumber));
            Check_urlDeviceId = strstr((char *)url,"deviceId");
            sscanf(Check_urlDeviceId,"deviceId=%[^&]s",UrlDeviceId);
            sprintf(asr_serialNumber,"%s:NULL\n",UrlDeviceId);
            printf("call getSerialNumber UrlDeviceId = %s\n",UrlDeviceId);
            printf("call getSerialNumber asr_serialNumber = %s\n",asr_serialNumber);
            serial_fp = open(ASR_SERIAL_PATH,(O_CREAT | O_RDWR | O_EXCL));
            if (serial_fp  < 0) {
                printf("open serial_fp fail not %sasr_serialnumber.txt 11111\r\n",MOUNT_FS_ROOT);
            }
            write(serial_fp,asr_serialNumber,strlen(asr_serialNumber));
            fsync(serial_fp);
            close(serial_fp);
        }
    }

    printf("url: %s\n", url);

    if (!pASN.Asr_SerialNumber_Flag) {
        bzero(UrlDeviceId,sizeof(UrlDeviceId));
        bzero(asr_serialNumber,sizeof(asr_serialNumber));
        //读取url对应的序列用来去匹配
        Check_urlDeviceId = strstr((char *)url,"deviceId");
        //printf("call getSerialNumber Check_urlDeviceId = %s\r\n",Check_urlDeviceId);
        sscanf(Check_urlDeviceId,"deviceId=%[^&]s",UrlDeviceId);
        //printf("call getSerialNumber UrlDeviceId = %s\r\n",UrlDeviceId);
        //遍历文本中的内容
        asr_serial_fd = fopen(ASR_SERIAL_PATH,"r+");
        if (asr_serial_fd == NULL) {
            printf("open asr_serial_fd fail not %sasr_serialnumber.txt\r\n",MOUNT_FS_ROOT);
        } else {
            while (fgets(Asr_serialData,sizeof(Asr_serialData),asr_serial_fd)) {
                Asr_serialData[strlen(Asr_serialData)-1] = '\0';
                //printf("call getSerialNumber Asr_serialData = %s\r\n",Asr_serialData);
                Check_serialNumber = strstr((char *)Asr_serialData,UrlDeviceId);
                if(Check_serialNumber != NULL) {
                    //printf("call getSerialNumber Check_serialNumber = %s\r\n",Check_serialNumber);
                    sscanf(Check_serialNumber,"%*[^:]:%s",asr_serialNumber);
                    //printf("call getSerialNumber asr_serialNumber = %s\r\n",asr_serialNumber);
                    //将serialNumber存储在Pstore中
                    if (strlen(asr_serialNumber) == SERIALNUMBER_MAXSIZE) {
                        if ((AsrSection = PStore_OpenSection(PS_ASR, PS_RDWR)) != E_PS_SECHDLER) {
                            pASN.Asr_SerialNumber_Flag = 1;
                            strcpy(pASN.SerialNumber,asr_serialNumber);
                            PStore_WriteSection((UINT8 *)&pASN, 0, sizeof(pASN), AsrSection);
                            Asr_Result = PStore_ReadSection((UINT8 *)&pASN, 0, sizeof(pASN), AsrSection);
                            printf("call getSerialNumber Asr_Result = %d\r\n",Asr_Result);
                            //printf("call getSerialNumber pASN.Asr_SerialNumber_Flag = %d\r\n",pASN.Asr_SerialNumber_Flag);
                            //printf("call getSerialNumber pASN.SerialNumber = %s\r\n",pASN.SerialNumber);
                            PStore_CloseSection(AsrSection);
                            bzero(body,sizeof(body));
                            sprintf(body,"{\"serialNumber\": \"%s\", \"tips\": \"deviceId already exists\"}",pASN.SerialNumber);
                        }
                        if(unlink(ASR_SERIAL_PATH) < 0) {
                            printf("rm ASR_SERIAL_PATH error \r\n");
                        }
                        if (unlink(ASR_URL_PATH) < 0) {
                            printf("rm ASR_URL_PATH error \r\n");
                        }
                    } else {
                        printf("asr_serialNumber %s error \r\n",asr_serialNumber);
                    }
                    break;
                }
            }
            fclose(asr_serial_fd);
        }
    } else {
        bzero(body,sizeof(body));
        sprintf(body,"{\"serialNumber\": \"%s\", \"tips\": \"deviceId already exists\"}",pASN.SerialNumber);
    }
    //("call getSerialNumber body = %s\r\n",body);
    *response = (char *)malloc(1024);
    memcpy(*response, body, strlen(body));

    printf("@@@getSerialNumber finish[%s]!!!\r\n", *response);
    return 1;
}

static UINT8 GetASR_Flag = 0;
UINT8 Dx_GetASR_Flag(void)
{
    return GetASR_Flag;
}

void Dx_SetASR_Flag(UINT8 arg)
{
    GetASR_Flag = arg;
    //printf("call Dx_SetASR_Flag = %d\r\n",GetASR_Flag);
}

typedef struct _audio_result {
    char wakeupWord[20];
    int major;
    int frame;
}audio_result;
/*回调函数，识别到对应的语音返回Json字符串  message就是对应的字符串将其*/
int engine_cb(void *userdata, const char *id, int type, const void *message, int size)
{
    char *Asr_data;
    audio_result ASR_Result;
    UINT8 Asr_Check_Flag = 0;
    printf("result:%s\n", (char *)message);
    g_wakeup_flag = 1;
    bzero(ASR_Result.wakeupWord,sizeof(ASR_Result.wakeupWord));

#if Test_Param
    bzero(param_data,sizeof(param_data));
    strcpy(param_data,(char *)message);
#endif

#if 1
    //解析Json字符串方法一
    //{"version":"2.9.4___wakeup_ver_prefix__1.0.4_f008", "applicationId":"279615564","recordId":"339477fb581fcafb", "result":{"words":"{"wakeupWord":"wo yao pai zhao","major":0,"frame":767}"}}
    Asr_data = strstr((char *)message,"\"wakeupWord\"");
    sscanf(Asr_data,"\"wakeupWord\":\"%[^\"]s\",\"major\":%d,\"frame\":%d}\"}}"\
                        ,ASR_Result.wakeupWord,&ASR_Result.major,&ASR_Result.frame\
          );
    //printf("------------------------------\r\n");
    //printf("Asr_data:%s\r\n",Asr_data);
    //printf("ASR_Result.wakeupWord:%s\r\n",ASR_Result.wakeupWord);
    //printf("ASR_Result.major:%d\r\n",ASR_Result.major);
    //printf("ASR_Result.frame:%d\r\n",ASR_Result.frame);
    //printf("------------------------------\r\n");
#endif
    switch(ASR_SelectMode) {
    case LANG_SC:
    case LANG_TC:
        Asr_Check_Flag = Ch_String_Check(ASR_Result.wakeupWord);
    break;
    case LANG_EN:
        Asr_Check_Flag = Foreign_String_Check(ASR_Result.wakeupWord);
    break;
    case LANG_JP:
        Asr_Check_Flag = Foreign_String_Check(ASR_Result.wakeupWord);
    break;
    case LANG_RU:
        Asr_Check_Flag = Foreign_String_Check(ASR_Result.wakeupWord);
    break;
    case LANG_TH:
        Asr_Check_Flag = Foreign_String_Check(ASR_Result.wakeupWord);
    break;
    default:
        Asr_Check_Flag = Foreign_String_Check(ASR_Result.wakeupWord);
    break;
    }
    Dx_SetASR_Flag(Asr_Check_Flag);
    //printf("Asr_Check_Flag = %d\r\n",Asr_Check_Flag);
#if Test_Param
    Test_KW(ASR_Result.wakeupWord);
#endif
    return 0;
}

struct aiengine *engine = NULL;

int ASR_Audio_Task(const char *cfg, char *param)
{
    char audio_buf[2048] = {0};
    UINT32 audio_buf_len = 2048;
    char id[64];
    int ret = 0;
    if (engine != NULL) {
        aiengine_delete(engine);
        engine = NULL;
    }
    //printf("call ASR_Audio_Task param= %s\r\n",param);
    //aiengine_get_device_id(id,64);
    engine = aiengine_new(cfg);
    if (!engine) {
        printf("create engine error\n");
        return -1;
    } else {
        printf("create engine success\n");
    }
    ret = aiengine_start(engine, param, id, engine_cb, NULL);
    if (ret == -1) {
        printf("start engine error\n");
        if (engine) {
            aiengine_delete(engine);
            engine = NULL;
        }
        return -1;
    } else {
        printf("start engine success\n");
    }
    while (1)
    {
    	if(ASR_GetPCMData_EN)
    	{
	        bzero(audio_buf,sizeof(audio_buf));
	        ret = AudioIn_FrameGet(0,audio_buf,&audio_buf_len);
	        if(0 != ret) {
	            printf("\r\n");
	            printf("ret = %d\r\n",ret);
	            printf("get pcm data fail or nall\r\n");
	            //ImageApp_MovieMulti_AudCapStop(0);
	            //ImageApp_MovieMulti_AudCapStart(0);
	            //sleep(3);
	            vos_util_delay_ms(5);
	            continue;
	        }
	        if (g_wakeup_flag == 1)
	        {
	            aiengine_stop(engine);
	            aiengine_start(engine, param, id, engine_cb, NULL);
	            g_wakeup_flag = 0;
	        }
	        ret = aiengine_feed(engine,audio_buf, audio_buf_len);
	        //printf("ret = %d \r\n",ret);
	        if (ret != 0)
	        {
	            printf("feed data error\n");
	            break;
	        }
    	}
		else
		{
			vos_util_delay_ms(5);
		}
    };

    //停止语音识别引擎工作
    aiengine_stop(engine);
    if (engine)
    {
        //删除语音识别引擎
        aiengine_delete(engine);
        engine = NULL;
    }
    //ASR Task exit
    printf("call ASR Task exit \r\n");
    //ASR_Abnormal = TRUE;  
    ASR_Uninstall();
    return 0;
}

void *ASR_Install(void *arg) 
{
    ASR_OpenState = TRUE;
    //设置异步类型，碰到cancel信号立马结束线程
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
    switch(ASR_SelectMode) {
    case LANG_SC:
    case LANG_TC:
        ASR_Audio_Task(engineCfg_ch,param_ch);
    break;
    case LANG_EN:
        ASR_Audio_Task(engineCfg_en,param_en);
    break;
    case LANG_JP:
        ASR_Audio_Task(engineCfg_japan,param_japan);
    break;
    case LANG_RU:
        ASR_Audio_Task(engineCfg_rus,param_rus);
    break;
    case LANG_TH:
        ASR_Audio_Task(engineCfg_th,param_thai);
    break;
    default:
        ASR_Audio_Task(engineCfg_en,param_en);
    break;
    }
    return arg;
}

void ASR_Uninstall(void)
{
    //取消线程
    if (ASR_OpenState) {
        pthread_cancel(asr_id);
        //vos_task_destroy(asr_id);
        //停止语音识别引擎工作
        aiengine_stop(engine);
        if (engine) {
            //删除语音识别引擎
            aiengine_delete(engine);
            engine = NULL;
        }
    }
    ASR_OpenState = FALSE;
}

void ASR_SetMode(UINT32 mode_arg)
{
    ASR_SelectMode = mode_arg;
}
//extern void SystemBoot_Delete_ASR(void);

void ASR_Aiengine_exe(const char *cfg)
{
    char *err_info = NULL;
    int ret = aiengine_check_auth(cfg, &err_info);
    if (ret != 0)
    {
        printf("check auth error: %s\n", err_info);
        ret = aiengine_do_auth(cfg, &err_info, getSerialNumber, NULL);
        if (0 != ret) {
            printf("do auth error: %s\n", err_info);
			#if 0
			SystemBoot_Delete_ASR();			
			memset(pASN.SerialNumber,0,sizeof(pASN.SerialNumber));			
			pASN.Asr_SerialNumber_Flag = 0;			
			aiengine_do_auth(cfg, &err_info, getSerialNumber, NULL);
			#endif
        } else {
            printf("do auth success: %s\n", err_info);
        }
    }
}

int ASR_Open(void)
{
    //检索ASR的Pstore有没有开劈空间
    PPSTORE_SECTION_HANDLE  AsrSection; 
    if (!ASR_OpenState) {
#if Test_Param
        Asr_Test_Param();
#endif
        if ((AsrSection = PStore_OpenSection(PS_ASR, (PS_RDWR))) != E_PS_SECHDLER) {
            printf("call ASR_Open PS_ASR already exist\r\n");
            ASR_Pstroe_Exist = TRUE;
            PStore_CloseSection(AsrSection);
        } else {
            ASR_Pstroe_Exist = FALSE;
            printf("section %s does not exist\r\n", PS_ASR);
        }
        if (ASR_Pstroe_Exist == FALSE) {
            //创建ASR Pstore 并初始化
            if ((AsrSection = PStore_OpenSection(PS_ASR, (PS_RDWR | PS_CREATE))) != E_PS_SECHDLER) {
                pASN.Asr_SerialNumber_Flag = 0;
                memset(pASN.SerialNumber,0,sizeof(pASN.SerialNumber));
                printf("call ASR_Open PStore_OpenSection\r\n");
                ASR_Pstroe_Exist = TRUE;
                //PStore_WriteSection((UINT8 *)&pASN, 0, sizeof(pASN), AsrSection);
                PStore_CloseSection(AsrSection);
            } else {
                printf("call PStore_OpenSection fail\r\n");
            }            
        } 

        switch(ASR_SelectMode) {
            case LANG_SC:
            case LANG_TC:
                #if Test_Param
                if (param_ch_flag == FALSE) {
                    param_ch_flag = TRUE;
                    Clear_data();
                }            
                #endif
				 printf("call Chinese!!!!!!!!\r\n");
                ASR_Aiengine_exe(engineCfg_ch);
            break;
            case LANG_EN:
                #if Test_Param
                if (param_en_flag == FALSE) {
                    param_en_flag = TRUE;
                    Clear_data();  
                }                             
                #endif
				printf("call English!!!!!!!!\r\n");
                ASR_Aiengine_exe(engineCfg_en);
            break;
            case LANG_JP:
                #if Test_Param
                if (param_japan_flag == FALSE) {
                    param_japan_flag = TRUE;
                    Clear_data();
                }                              
                #endif
				printf("call japan!!!!!!!!\r\n");
                ASR_Aiengine_exe(engineCfg_japan);
            break;
            case LANG_RU:
                #if Test_Param
                if (param_rus_flag == FALSE) {
                    param_rus_flag = TRUE;
                    Clear_data();
                }                             
                #endif
				printf("call rus!!!!!!!!\r\n");
                ASR_Aiengine_exe(engineCfg_rus);
            break;
            case LANG_TH:
                #if Test_Param
                if (param_thai_flag == FALSE) {
                    param_thai_flag = TRUE;
                    Clear_data();                    
                }                             
                #endif
				printf("call th!!!!!!!!\r\n");
                ASR_Aiengine_exe(engineCfg_th);
            break;
            default:
				printf("call default englis!!!!!!!!\r\n");
                ASR_Aiengine_exe(engineCfg_en);
            break;
        }
        //创建线程
        //pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
        //pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
        pthread_create(&asr_id,NULL,ASR_Install,NULL);
		} else {
        printf("ASR open already\r\n");
    }
    //printf("===================test wakeup onetime end========================= \n");
    return 0;
}



