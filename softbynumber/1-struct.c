#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _setting
{
	char *data;
} setting;

typedef struct _setting_config
{
	setting led;
	setting motion;
	setting framerate;

} setting_config;

#define bitNone 	 0x001
#define bitled       0x002
#define bitmotion    0x004
#define bitframerate 0x008

const char *feature_support[] = {
	"none",
	"playLED",
	"motion",
	"framerate"
};

setting_config setting_pluto;
int main(void)
{
	// handle pubsub killed.
	setting_config curr_setting;
	setting_pluto.led.data = "true";
	setting_pluto.motion.data = "true";
	setting_pluto.framerate.data = "30";

	curr_setting.led.data = "true";
	curr_setting.motion.data = "false";
	curr_setting.framerate.data = "24";
	
	int setting = 0;
	int i;
	int count = 0;
	char tmp[512] = {0};
	char data[512] = {0};
	if(!setting_pluto.led.data || strcmp(setting_pluto.led.data, curr_setting.led.data))
	{
		setting_pluto.led.data = curr_setting.led.data;
		if(count)
		{
			strncat(data, ",", strlen(","));
		}
		setting = setting | bitled;
		count ++;
	}

	if(!setting_pluto.motion.data || strcmp(setting_pluto.motion.data, curr_setting.motion.data))
	{
		setting_pluto.motion.data = curr_setting.motion.data;
		if(count)
		{
			strncat(data, ",", strlen(","));
		}
		strncat(data, setting_pluto.motion.data, strlen(setting_pluto.motion.data));
		setting = setting | bitmotion;
		count ++;
	}

	if(!setting_pluto.framerate.data || strcmp(setting_pluto.framerate.data, curr_setting.framerate.data))
	{
		setting_pluto.framerate.data = curr_setting.framerate.data;
		if(count)
		{
			strncat(data, ",", strlen(","));
		}
		strncat(data, setting_pluto.framerate.data, strlen(setting_pluto.framerate.data));
		setting = setting | bitframerate;
		count ++;
	}
	printf("setting: %d\n", setting);
	count = 0;
	for(i = 0; i <= 3; i ++)
	{
		if(setting & 1)
		{
			if(count)
			{
				strncat(tmp, ",", strlen(","));
			}
			strncat(tmp, feature_support[i], strlen(feature_support[i]));
			count++;
		}
		setting >>= 1;
	}

	printf("tmp: (%s), data: %s \n", tmp, data);
}
// pluto_setting_config