//
//  用户权限设置.h
//  SoDemon
//
//  Created by sandy on 16/5/16.
//  Copyright © 2016年 feng. All rights reserved.
//

#pragma mark 1.用户权限设置
1.用户权限设置 <至少有一个管理者权限>

1）说明：权限设置是指设置用户的音频视频等权限，权限参数@"group",下面罗列的权限可以相加使用。比如@"admin2=admin&pw2=88888888&group2=9save=1&reinit_guest=1",代表第二个用户拥有音视频权限。详细如下：

#define GROUP_VISITOR										0  //没有权限

#define PRI_VIDEO											1 //视频

#define PRI_SNAPSHOT										2  //拍照

#define PRI_RECORD											4 //录像

#define PRI_AUDIO											8 //音频

#define PRI_TALK 											16 //对讲

#define PRI_CONTROL											32  //控制

#define GROUP_ADMINSTRATOR									0x1ffff  //管理者权限

2）使用类：IPCam

3）函数：
/*
 *IPCam方法：CGI获取参数
 *参数：
 *params:cgi参数，由reecam提供
 *delegate:IPCamGetParamsDelegate代理，可以监控cgi获取的结果
 *返回：
 *返回IPCAM_ERROR类型，当返回IPCAM_ERROR_NO_ERROR，则表示函数执行成功
 */

-(IPCAM_ERROR)get_params:(NSString *)params
delegate:(id<IPCamGetParamsDelegate>)delegate;

/*
 *IPCam方法：IPCamGetParamsDelegate代理回调
 *参数：
 *ipcam：返回一个id类型，其实就是一个IPCam
 *error:IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示获取参数成功
 *params：一个字典，是get_params的params的key/value
 */
-(void)on_get_params_result:(id)ipcam
error:(IPCAM_ERROR)error
params:(NSDictionary *)params;

/*
 *IPCam方法：获取当前用户权限
 *返回：
 *返回一个十进制参数
 
 */
-(int)group;

4）注意：a)SOSO固件只有两个用户（admin1和admin2），且admin1和admin2默认都是admin且不可设置，group1默认是管理者权限且也不可设置。故SOSO固件用户管理只有pwd1，pwd2和group2可设置。
b)UCCAM固件有8个用户（admin1...admin8），且admin1默认admin，group1默认是管理者权限。所有都可设置
c)uccam固件因为user都可设置，所以要特别注意，每一个user要独一无二，不得重复

5）示例

/*第一步：获取参数＋添加代理IPCamGetParamsDelegate*/
-(void)set_group{
    if (IPCAM_ERROR_NO_ERROR != [m_ipcam set_params:@"admin2=admin&group2=9&pwd2=" delegate:self]){
        /*设置失败*/
    }
}
/*第二步：根据IPCamGetParamsDelegate结果判断状态*/
-(void)on_get_params_result:(id)ipcam
error:(IPCAM_ERROR)error
params:(NSDictionary *)params{
    if (error == IPCAM_ERROR_NO_ERROR){
        /*设置成功*/
    }
}
