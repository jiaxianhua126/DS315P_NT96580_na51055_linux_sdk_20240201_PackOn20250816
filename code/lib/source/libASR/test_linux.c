#include "aiengine.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
                        \"licensesPath\":\"./cfgbatch.authorization\",\
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

char *param_en = "{\"request\":{\"env\":\"words=kw1,kw2,kw3,kw4,kw5,kw6,kw7,kw8,kw9,kw10,kw11,kw14,kw16,kw12,kw13,kw15,kw17;thresh=0.60,0.45,0.3,0.58,0.6,0.49,0.34,0.70,0.27,0.50,0.51,0.65,0.45,0.15,0.06,0.54,0.81;\"}}";

char *param_japan = "{\"request\":{\"env\":\"words=kw6,kw7,kw10,kw11,kw14,kw15,kw1,kw2,kw3,kw4,kw5,kw8,kw9,kw12,kw13,kw16,kw17;thresh=0.39,0.31,0.53,0.62,0.31,0.42,0.45,0.49,0.47,0.5,0.45,0.55,0.65,0.6,0.35,0.45,0.35;\"}}";

char * param_ch = "{\"request\":{\"env\":\"words=wo yao pai zhao,wo yao lu xiang,guan bi ping mu,da kai ping mu,da kai lu yin,guan bi lu yin,da kai re dian,guan bi re dian,da kai qian lu,xian shi qian lu,da kai hou lu,xian shi hou lu,zhua pai zhao pian,da kai nei lu,cha kan quan bu,shi pin jia suo,fan hui zhu ye,da kai wai fa,guan bi wai fa;thresh=0.32,0.32,0.29,0.29,0.26,0.24,0.22,0.20,0.20,0.17,0.21,0.17,0.15,0.20,0.12,0.12,0.08,0.18,0.20;\"}}";

int g_wakeup_flag = 0;


int getSerialNumber(void *userdata, const char *url, char **response)
{
    int ret;
    printf("url: %s\n", url);

    const char *body = "{\"serialNumber\": \"43cf-4120-872f-0c29-1707\", \"tips\": \"deviceId already exists\"}"; //

    *response = (char *)malloc(1024);
    memcpy(*response, body, strlen(body));

    printf("@@@getSerialNumber finish[%s]!!!\r\n", *response);
    return 1;
}

int engine_cb(void *userdata, const char *id, int type, const void *message, int size)
{
    printf("result:%s\n", (char *)message);
    g_wakeup_flag = 1;
    return 0;
}

struct aiengine *engine = NULL;

int test_audio(const char *cfg, char *param, char *audio_name)
{
    int read_bytes;
    char buf[3200] = {0};
    char id[64];
    int ret = 0;
    if (engine != NULL)
    {
        aiengine_delete(engine);
        engine = NULL;
    }

    engine = aiengine_new(cfg);
    if (!engine)
    {
        printf("create engine error\n");
        return -1;
    }
    else
    {
        printf("create engine success\n");
    }
begin:
    ret = aiengine_start(engine, param, id, engine_cb, NULL);
    if (ret == -1)
    {
        printf("start engine error\n");
        if (engine)
        {
            aiengine_delete(engine);
            engine = NULL;
        }
        return -1;
    }
    else
    {
        printf("start engine success\n");
    }

    FILE *fd = fopen(audio_name, "rb");
    if (!fd)
    {
        printf("open %s failed\n", audio_name);
    }
    else
    {
        printf("open %s success\n", audio_name);
    }
    while (1)
    {
        read_bytes = fread(buf, 1, sizeof(buf), fd);
        if (read_bytes <= 0)
        {
            printf("no data in audio files\n");
            break;
        }
        else
        {
            if (g_wakeup_flag == 1)
            {
                aiengine_stop(engine);
                aiengine_start(engine, param, id, engine_cb, NULL);
                g_wakeup_flag = 0;
            }
            ret = aiengine_feed(engine, buf, read_bytes);
			printf("ret = %d \r\n",ret);
            if (ret != 0)
            {
                printf("feed data error\n");
                break;
            }
        }
    };

    aiengine_stop(engine);
    if (fd)
        fclose(fd);
    if (engine)
    {
        aiengine_delete(engine);
        engine = NULL;
    }
    return 0;
}
int main(int argc, char **argv)
{

    char *err_info = NULL;

    int ret = aiengine_check_auth(engineCfg_ch, &err_info);
    if (ret != 0)
    {
        printf("check auth error: %s\n", err_info);
        ret = aiengine_do_auth(engineCfg_ch, &err_info, getSerialNumber, NULL);
        if (0 != ret)
        {
            printf("do auth error: %s\n", err_info);
        }
        else
        {
            printf("do auth success: %s\n", err_info);
        }
    }

    //test_audio(engineCfg_en, param_en, "/app/sd/test/take_photo.wav");
    //test_audio(engineCfg_japan, param_japan, "/app/sd/test/kw2_japan.wav");
    test_audio(engineCfg_ch, param_ch, "/root/test/AW_Russia.wav");
    printf("===================test wakeup onetime end========================= \n");
    return 0;
}
