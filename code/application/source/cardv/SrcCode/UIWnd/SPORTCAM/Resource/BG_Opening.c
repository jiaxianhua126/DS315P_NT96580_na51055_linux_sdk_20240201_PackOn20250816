//#include "BG_Images.h"
#include "PrjCfg.h"

//开机logo
#if 0//(MACHINE_TYPE==MACHINE_TYPE_S2P)
#include "welcome.c"
#include "Goodbye.c"
#elif 0
#include "welcome_Polaroid_new.c"
#include "Goodbye_Polaroid_new.c"
#elif 1
#include "Goodbye_Pernis_White.c"
#include "Welcome_Pernis_White.c"
#endif

int Logo_getBGOpening_size(void)
{
	return sizeof(g_ucBGOpening);
}

int Logo_getBGGoodbye_size(void)
{
	return sizeof(g_ucBGGoodbye);
}
