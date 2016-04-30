#include "Globals.h"

namespace Globals
{
	CSimpleIniA ini;
	bool configured = false;

	int 	update_value(int def, const char *section, const char *key);
	float 	update_value(float def, const char *section, const char *key);

	int screenWidth 			= update_value(1024, 	"dimensions", 	"width");
	int screenHeight 			= update_value(768, 	"dimensions", 	"height");
	
	float fieldRatio 			= update_value((float) 3/ (float) 4, 	NULL, 			NULL);
	int fieldWidth 				= update_value((int) (screenHeight * fieldRatio) / 10 * 10, NULL, NULL);
	int fieldHeight 			= update_value(screenHeight, NULL, NULL);
	int xOffset 				= update_value((screenWidth / 2) - (fieldWidth / 2), NULL, NULL);
	int yOffset 				= update_value(0, NULL, NULL);
	
	int blockWidth 				= update_value(fieldWidth / 10, NULL, NULL);
	int blockHeight 			= update_value((int) (blockWidth * (float) 2/(float) 3), NULL, NULL);
	
	int paddleWidth 			= update_value(blockWidth, NULL, NULL);
	int paddleHeight 			= update_value(blockHeight / 2, NULL, NULL);
	
	int ballWidth 				= update_value(blockHeight / 2, NULL, NULL);
	int ballHeight 				= update_value(blockHeight / 2, NULL, NULL);

	int fullScreen 				= update_value(0,		"dimensions", 	"fullScreen");

	int mainMenuY 				= update_value(100,		NULL,			NULL);
	int mainMenuX 				= update_value(100,		NULL,			NULL);
	int mainMenuRowPadding 		= update_value(25,		NULL,			NULL);
	int mainMenuColPadding 		= update_value(25,		NULL,			NULL);
	int mainMenuRowHeight 		= update_value(75,		NULL,			NULL);
	int mainMenuColWidth 		= update_value(100,		NULL,			NULL);

	int pauseMenuX 				= update_value(100,		NULL,			NULL);
	int pauseMenuY 				= update_value(100,		NULL,			NULL);
	int pauseMenuRowPadding 	= update_value(25,		NULL,			NULL);
	int pauseMenuColPadding 	= update_value(25,		NULL,			NULL);
	int pauseMenuRowHeight 		= update_value(75,		NULL,			NULL);
	int pauseMenuColWidth 		= update_value(100,		NULL,			NULL);


	int update_value(int def, const char *section, const char *key)
	{
		int value;
		const char* def_str;

		if(!configured)
		{
			configured = true;
			
			ini.SetUnicode();
			ini.LoadFile("breakout.ini");
		}

		if(section != NULL && key != NULL)
		{
			def_str = ini.GetValue(section, key, std::to_string(def).c_str());
			value=atoi(def_str);
			ini.SetValue(section, key, std::to_string(value).c_str());
		}
		else
		{
			value=def;
		}

		return value;
	}

	float update_value(float def, const char *section, const char *key)
	{
		float value;
		const char* def_str;

		if(!configured)
		{
			configured = true;
			
			ini.SetUnicode();
			ini.LoadFile("breakout.ini");
		}

		if(section != NULL && key != NULL)
		{
			def_str = ini.GetValue(section, key, std::to_string(def).c_str());
			value=atof(def_str);
			ini.SetValue(section, key, std::to_string(value).c_str());
		}
		else
		{
			value=def;
		}

		return value;		
	}
}