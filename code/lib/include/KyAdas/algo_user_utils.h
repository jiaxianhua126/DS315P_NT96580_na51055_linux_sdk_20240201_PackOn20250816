#ifndef _ALGO_USER_UTILS_H_
#define _ALGO_USER_UTILS_H_


#ifdef __cplusplus
extern "C"{
#endif

/*
 *   名称：ALGO_UTILS_ReadJpgFile
 *	 参数：path:文件路劲
 *        data:用户分配的内存地址 ,NV21
 *        width:图像宽
 *        height:图像高
 *   返回:0 success
 *       -1 faild
 */
int ALGO_UTILS_ReadJpgFileToYuv(const char *path,unsigned char *data,int *width,int *height);

/*
 *   名称：ALGO_UTILS_YuvToJpgFile
 *	 参数：path:文件路劲
 *        data:用户分配的内存地址 ,NV21
 *        width:图像宽
 *        height:图像高
 *   返回:0 success
 *       -1 faild
 */
int ALGO_UTILS_WriteYuvToJpgFile(const char *path,unsigned char *data,int width,int height);

/*
 *   名称：ALGO_UTILS_Nv21Roi
 *	 参数：org:用户分配的内存地址 ,NV21
 *        width:图像宽
 *        height:图像高
 *        x:ROI X坐标
 *        y:ROI Y坐标
 *        roi_width:ROI图像宽
 *        roi_height:ROI图像高
 *   返回:0 success
 *       -1 faild
 */
int ALGO_UTILS_Nv21Roi(unsigned char *org,int width,int height, unsigned char *roi,int x,int y,int roi_width,int roi_height);

#ifdef __cplusplus
};
#endif


#endif
