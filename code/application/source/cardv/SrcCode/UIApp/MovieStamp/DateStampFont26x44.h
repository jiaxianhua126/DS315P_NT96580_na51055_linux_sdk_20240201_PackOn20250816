/*//////////////////////////////////////////////////////////////////////////////

 ---------- Document Info ---------------

        Author : Anonymous
       Created : 16:07:29, Apr  7 2010
 Last modified : 16:07:29, Apr  7 2010
   Making tool : UI Designer Studio
   File format : C language header file

 ----------- Object Info ----------------

         Class : ICON DB
          Name : DateStampFont26x44

*///////////////////////////////////////////////////////////////////////////////

#ifndef _DATESTAMPFONT26X44_H_
#define _DATESTAMPFONT26X44_H_

#include "draw_lib.h"
// #include "MovieStamp.h"

// ICON DB
extern const
ICON_DB gDateStampFont26x44;

// ICON ID range
#define DATESTAMPFONT26X44_MIN    gDateStampFont26x44.DrawStrOffset
#define DATESTAMPFONT26X44_NUM    gDateStampFont26x44.NumOfIcon
#define DATESTAMPFONT26X44_MAX    (DATESTAMPFONT26X44_MIN+DATESTAMPFONT26X44_NUM-1)

// ICON ID
//#define name id
#define _0020    0x0020
#define _0021    0x0021
#define _002D    0x002D  //-
#define _002E    0x002E
#define _002F    0x002F
#define _0030    0x0030
#define _0031    0x0031
#define _0032    0x0032
#define _0033    0x0033
#define _0034    0x0034
#define _0035    0x0035
#define _0036    0x0036
#define _0037    0x0037
#define _0038    0x0038
#define _0039    0x0039
#define _003A    0x003A
#define _0041      0x0041 //A
#define _0042      0x0042 //B
#define _0043      0x0043 //c
#define _0044      0x0044 //D
#define _0045      0x0045 //E
#define _0046      0x0046 //F
#define _0047      0x0047 //G
#define _0048      0x0048 //H
#define _0049      0x0049 //I
#define _004A      0x004A //J
#define _004B      0x004B //K
#define _004C      0x004C //L
#define _004D      0x004D //M
#define _004E      0x004E //N
#define _004F      0x004F //O
#define _0050      0x0050 //P
#define _0051      0x0051 //Q
#define _0052      0x0052 //R
#define _0053      0x0053 //S
#define _0054      0x0054 //T
#define _0055      0x0055 //U
#define _0056      0x0056 //V
#define _0057      0x0057 //W
#define _0058      0x0058 //X
#define _0059      0x0059 //Y
#define _005A      0x005A //Z

#define _0061     0x0061 //a
#define _0062     0x0062 //b
#define _0063     0x0063 //c
#define _0064     0x0064 //d
#define _0065     0x0065 //d //e
#define _0066     0x0066//f
#define _0067     0x0067 //g
#define _0068     0x0068 //h
#define _0069     0x0069 //i
#define _006A     0x006A //j
#define _006B     0x006B //k
#define _006C     0x006C //l
#define _006D     0x006D //m
#define _006E    0x006E//n
#define _006F    0x006F//o
#define _0070    0x0070 //p
#define _0071    0x0071 //q
#define _0072    0x0072 //r
#define _0073    0x0073 //s
#define _0074    0x0074 //t
#define _0075    0x0075 //u
#define _0076    0x0076 //v
#define _0077    0x0077 //w
#define _0078    0x0078 //x
#define _0079    0x0079 //y
#define _007A    0x007A //z



#define PLUS_ADD26X44  0x011E
#define  DX_ADD26X44  0x11E0 //¡ä¨®D¡ä

#define START26X44_A_ADD  DX_ADD26X44
#ifdef _0041_
#define START26X44_B_ADD  (START26X44_A_ADD+PLUS_ADD26X44)
#else
#define START26X44_B_ADD  START26X44_A_ADD
#endif
#ifdef _0042_
#define START26X44_C_ADD  (START26X44_B_ADD+PLUS_ADD26X44)
#else
#define START26X44_C_ADD  START26X44_B_ADD
#endif
#ifdef _0043_
#define START26X44_D_ADD  (START26X44_C_ADD+PLUS_ADD26X44)
#else
#define START26X44_D_ADD  START26X44_C_ADD
#endif
#ifdef _0044_
#define START26X44_E_ADD  (START26X44_D_ADD+PLUS_ADD26X44)
#else
#define START26X44_E_ADD  START26X44_D_ADD
#endif
#ifdef _0045_
#define START26X44_F_ADD  (START26X44_E_ADD+PLUS_ADD26X44)
#else
#define START26X44_F_ADD  START26X44_E_ADD
#endif
#ifdef _0046_
#define START26X44_G_ADD  (START26X44_F_ADD+PLUS_ADD26X44)
#else
#define START26X44_G_ADD  START26X44_F_ADD
#endif
#ifdef _0047_
#define START26X44_H_ADD  (START26X44_G_ADD+PLUS_ADD26X44)
#else
#define START26X44_H_ADD  START26X44_G_ADD
#endif
#ifdef _0048_
#define START26X44_I_ADD  (START26X44_H_ADD+PLUS_ADD26X44)
#else
#define START26X44_I_ADD  START26X44_H_ADD
#endif
#ifdef _0049_
#define START26X44_J_ADD  (START26X44_I_ADD+PLUS_ADD26X44)
#else
#define START26X44_J_ADD  START26X44_I_ADD
#endif
#ifdef _004A_
#define START26X44_K_ADD  (START26X44_J_ADD+PLUS_ADD26X44)
#else
#define START26X44_K_ADD  START26X44_J_ADD
#endif
#ifdef _004B_
#define START26X44_L_ADD  (START26X44_K_ADD+PLUS_ADD26X44)
#else
#define START26X44_L_ADD  START26X44_K_ADD
#endif
#ifdef _004C_
#define START26X44_M_ADD  (START26X44_L_ADD+PLUS_ADD26X44)
#else
#define START26X44_M_ADD  START26X44_L_ADD
#endif
#ifdef _004D_
#define START26X44_N_ADD  (START26X44_M_ADD+PLUS_ADD26X44)
#else
#define START26X44_N_ADD  START26X44_M_ADD
#endif
#ifdef _004E_
#define START26X44_O_ADD  (START26X44_N_ADD+PLUS_ADD26X44)
#else
#define START26X44_O_ADD  START26X44_N_ADD
#endif
#ifdef _004F_
#define START26X44_P_ADD  (START26X44_O_ADD+PLUS_ADD26X44)
#else
#define START26X44_P_ADD  START26X44_O_ADD
#endif
#ifdef _0050_
#define START26X44_Q_ADD  (START26X44_P_ADD+PLUS_ADD26X44)
#else
#define START26X44_Q_ADD  START26X44_P_ADD
#endif
#ifdef _0051_
#define START26X44_R_ADD  (START26X44_Q_ADD+PLUS_ADD26X44)
#else
#define START26X44_R_ADD  START26X44_Q_ADD
#endif
#ifdef _0052_
#define START26X44_S_ADD  (START26X44_R_ADD+PLUS_ADD26X44)
#else
#define START26X44_S_ADD  START26X44_R_ADD
#endif
#ifdef _0053_
#define START26X44_T_ADD  (START26X44_S_ADD+PLUS_ADD26X44)
#else
#define START26X44_T_ADD  START26X44_S_ADD
#endif
#ifdef _0054_
#define START26X44_U_ADD  (START26X44_T_ADD+PLUS_ADD26X44)
#else
#define START26X44_U_ADD  START26X44_T_ADD
#endif
#ifdef _0055_
#define START26X44_V_ADD  (START26X44_U_ADD+PLUS_ADD26X44)
#else
#define START26X44_V_ADD  START26X44_U_ADD
#endif
#ifdef _0056_
#define START26X44_W_ADD  (START26X44_V_ADD+PLUS_ADD26X44)
#else
#define START26X44_W_ADD  START26X44_V_ADD
#endif
#ifdef _0057_
#define START26X44_X_ADD  (START26X44_W_ADD+PLUS_ADD26X44)
#else
#define START26X44_X_ADD  START26X44_W_ADD
#endif
#ifdef _0058_
#define START26X44_Y_ADD  (START26X44_X_ADD+PLUS_ADD26X44)
#else
#define START26X44_Y_ADD  START26X44_X_ADD
#endif
#ifdef _0059_
#define START26X44_Z_ADD  (START26X44_Y_ADD+PLUS_ADD26X44)
#else
#define START26X44_Z_ADD  START26X44_Y_ADD
#endif

#ifdef _005A_
#define START26X44_XA_ADD  (START26X44_Z_ADD+PLUS_ADD26X44)
#else
#define START26X44_XA_ADD  START26X44_Z_ADD
#endif


#ifdef _0061_
#define START26X44_XB_ADD  (START26X44_XA_ADD+PLUS_ADD26X44)
#else
#define START26X44_XB_ADD  START26X44_XA_ADD
#endif
#ifdef _0062_
#define START26X44_XC_ADD  (START26X44_XB_ADD+PLUS_ADD26X44)
#else
#define START26X44_XC_ADD  START26X44_XB_ADD
#endif
#ifdef _0063_
#define START26X44_XD_ADD  (START26X44_XC_ADD+PLUS_ADD26X44)
#else
#define START26X44_XD_ADD  START26X44_XC_ADD
#endif
#ifdef _0064_
#define START26X44_XE_ADD  (START26X44_XD_ADD+PLUS_ADD26X44)
#else
#define START26X44_XE_ADD  START26X44_XD_ADD
#endif
#ifdef _0065_
#define START26X44_XF_ADD  (START26X44_XE_ADD+PLUS_ADD26X44)
#else
#define START26X44_XF_ADD  START26X44_XE_ADD
#endif
#ifdef _0066_
#define START26X44_XG_ADD  (START26X44_XF_ADD+PLUS_ADD26X44)
#else
#define START26X44_XG_ADD  START26X44_XF_ADD
#endif
#ifdef _0067_
#define START26X44_XH_ADD  (START26X44_XG_ADD+PLUS_ADD26X44)
#else
#define START26X44_XH_ADD  START26X44_XG_ADD
#endif
#ifdef _0068_
#define START26X44_XI_ADD  (START26X44_XH_ADD+PLUS_ADD26X44)
#else
#define START26X44_XI_ADD  START26X44_XH_ADD
#endif
#ifdef _0069_
#define START26X44_XJ_ADD  (START26X44_XI_ADD+PLUS_ADD26X44)
#else
#define START26X44_XJ_ADD  START26X44_XI_ADD
#endif
#ifdef _006A_
#define START26X44_XK_ADD  (START26X44_XJ_ADD+PLUS_ADD26X44)
#else
#define START26X44_XK_ADD  START26X44_XJ_ADD
#endif
#ifdef _006B_
#define START26X44_XL_ADD  (START26X44_XK_ADD+PLUS_ADD26X44)
#else
#define START26X44_XL_ADD  START26X44_XK_ADD
#endif
#ifdef _006C_
#define START26X44_XM_ADD  (START26X44_XL_ADD+PLUS_ADD26X44)
#else
#define START26X44_XM_ADD  START26X44_XL_ADD
#endif
#ifdef _006D_
#define START26X44_XN_ADD  (START26X44_XM_ADD+PLUS_ADD26X44)
#else
#define START26X44_XN_ADD  START26X44_XM_ADD
#endif
#ifdef _006E_
#define START26X44_XO_ADD  (START26X44_XN_ADD+PLUS_ADD26X44)
#else
#define START26X44_XO_ADD  START26X44_XN_ADD
#endif
#ifdef _006F_
#define START26X44_XP_ADD  (START26X44_XO_ADD+PLUS_ADD26X44)
#else
#define START26X44_XP_ADD  START26X44_XO_ADD
#endif
#ifdef _0070_
#define START26X44_XQ_ADD  (START26X44_XP_ADD+PLUS_ADD26X44)
#else
#define START26X44_XQ_ADD  START26X44_XP_ADD
#endif
#ifdef _0071_
#define START26X44_XR_ADD  (START26X44_XQ_ADD+PLUS_ADD26X44)
#else
#define START26X44_XR_ADD  START26X44_XQ_ADD
#endif
#ifdef _0072_
#define START26X44_XS_ADD  (START26X44_XR_ADD+PLUS_ADD26X44)
#else
#define START26X44_XS_ADD  START26X44_XR_ADD
#endif
#ifdef _0073_
#define START26X44_XT_ADD  (START26X44_XS_ADD+PLUS_ADD26X44)
#else
#define START26X44_XT_ADD  START26X44_XS_ADD
#endif
#ifdef _0074_
#define START26X44_XU_ADD  (START26X44_XT_ADD+PLUS_ADD26X44)
#else
#define START26X44_XU_ADD  START26X44_XT_ADD
#endif
#ifdef _0075_
#define START26X44_XV_ADD  (START26X44_XU_ADD+PLUS_ADD26X44)
#else
#define START26X44_XV_ADD  START26X44_XU_ADD
#endif
#ifdef _0076_
#define START26X44_XW_ADD  (START26X44_XV_ADD+PLUS_ADD26X44)
#else
#define START26X44_XW_ADD  START26X44_XV_ADD
#endif
#ifdef _0077_
#define START26X44_XX_ADD  (START26X44_XW_ADD+PLUS_ADD26X44)
#else
#define START26X44_XX_ADD  START26X44_XW_ADD
#endif
#ifdef _0078_
#define START26X44_XY_ADD  (START26X44_XX_ADD+PLUS_ADD26X44)
#else
#define START26X44_XY_ADD  START26X44_XX_ADD
#endif
#ifdef _0079_
#define START26X44_XZ_ADD  (START26X44_XY_ADD+PLUS_ADD26X44)
#else
#define START26X44_XZ_ADD  START26X44_XY_ADD
#endif

#endif //_DATESTAMPFONT26X44_H_
