//
//  Ewig.h
//  SoDemon
//
//  Created by sandy on 16/5/16.
//  Copyright © 2016年 feng. All rights reserved.
//

/*
 *喂狗相关操作
 */

说明：ipcam为IPCam对象
#pragma mark 1.获取喂食器状态
1.获取喂食器状态
函数：
-(YOUPING_EWIG_STATUS)youping_ewig_status;
typedef enum{
    YOUPING_EWIG_NORMAL, //正常
    YOUPING_EWIG_NOFOOD, //没有食物
    YOUPING_EWIG_MOTORERROR, //马达故障
    YOUPING_EWIG_UNKNOW,  //未获取到状态
}YOUPING_EWIG_STATUS;

示范：
YOUPING_EWIG_STATUS m_ewig_status = [ipcam youping_ewig_status];

#pragma mark 2.喂食器喂食操作<设置和读取>

2.喂食器喂食操作：
2.1手动喂食：
函数：
/*
 *IPCam方法：手动喂食
 *参数：
 *cmd：命令
 *param：参数，默认写0即
 *返回：返回IPCAM_ERROR_NO_ERROR说明函数执行成功，否则执行失败
 */
-(IPCAM_ERROR)ptz_control:(IPCAM_PTZ_CMD)cmd
param:(int)param;
示范：
[ipcam ptz_control:IPCAM_PTZ_CMD_YOUPING_START_EWIG param:0]; //开始手动喂食
[ipcam ptz_control:IPCAM_PTZ_CMD_YOUPING_STOP_EWIG param:0]; //停止手动喂食

2.2喂食器预约：
1）设置预约参数：
a)函数:
/*
 *IPCam方法：设置预约参数
 *参数：
 *params:cgi参数，详细如“params说明”
 *delegate:IPCamSetParamsDelegate代理，可以监控设置的结果
 *返回：返回IPCAM_ERROR_NO_ERROR说明函数执行成功，否则执行失败
 */
-(IPCAM_ERROR)set_params:(NSString *)params
delegate:(id<IPCamSetParamsDelegate>)delegate;
params说明：
params = "save=1&ewig_schedule1=";
其中ewig_schedule1参数赋值说明如下：
a.早时间段喂食参数：ewig_schedule1：
bit16-23：小时
bit8-15：分钟
bit0-7：喂食量，0：不喂食；2：少；4：中；6：多
b.中时间段喂食参数：ewig_schedule2：
bit16-23：小时
bit8-15：分钟
bit0-7：喂食量，0：不喂食；2：少；4：中；6：多
c. 晚时间段喂食参数：ewig_schedule3：
bit16-23：小时
bit8-15：分钟
bit0-7：喂食量，0：不喂食；2：少；4：中；6：多

/*
 *IPCam方法：IPCamSetParamsDelegate回调函数
 *返回参数：
 *ipcam:返回一个id类型，其实就是一个IPCam
 *error:IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示设置成功，否则设置失败
 */
-(void)on_set_params_result:(id)ipcam
error:(IPCAM_ERROR)error;

b)示列
/*第一步：cgi设置参数+添加代理IPCamSetParamsDelegate
 */
NSString * params = @"save=1&ewig_schedule1=OXFFFF00”; //设置早时间段不喂食
[m_ipcam set_params:params delegate:self];
/*
 *第二步：IPCamSetParamsDelegate代理回调
 */
-(void)on_set_params_result:(id)ipcam
error:(IPCAM_ERROR)error {
    if (error == IPCAM_ERROR_NO_ERROR) {
        NSLog(@"set success!");
    }
    NSLog(@"error = %u",error);
}

2）获取当前宠物喂食器预约参数：
a)函数：
/*
 *IPCam方法：获取当前宠物喂食器预约参数
 *参数：
 *params:需要获取的摄像机参数，详细如params说明
 *delegate: IPCamGetParamsDelegate代理，可以监控获取的结果
 *返回：返回IPCAM_ERROR_NO_ERROR说明函数执行成功，否则执行失败
 */
-(IPCAM_ERROR)get_params:(NSString *)params
delegate:(id<IPCamGetParamsDelegate>)delegate;
params说明：
ewig_schedule1  //获取早时间段
ewig_schedule2  //获取晚时间段
ewig_schedule3  //获取晚时间段

/*
 *IPCam方法：IPCamGetParamsDelegate回调函数
 *返回参数：
 *ipcam：返回一个id类型，其实就是一个IPCam
 * error:IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示获取成功，否则获取失败
 */
-(void)on_get_params_result:(id)ipcam
error:(IPCAM_ERROR)error
params:(NSDictionary *)params;

b)示范：
/*
 *获取参数＋添加代理IPCamGetParamsDelegate
 */
[m_ipcam get_params:@"ewig_schedule1 =" delegate:self]

/*
 *代理IPCamGetParamsDelegate回调
 */

-(void)on_get_params_result:(id)ipcam
error:(IPCAM_ERROR)error
params:(NSDictionary *)params{
    if (error == IPCAM_ERROR_NO_ERROR) {
        int m_ewig_schedule1 = [[params objectForKey:@"ewig_schedule1"] intValue];
        NSLog(@"get success!");
    }
    else{
        NSLog(@“get fail!”);
    }
}

#pragma mark 3.宠物召唤声音录音设置 <录制／上传>
3.宠物召唤声音录音设置：
3.1开始／停止录音
a)函数
/*
 *Util方法：开始录音
 *参数：
 *max_seconds:录音允许的最大时间，时间一到会自动停止,单位s
 *delegate: UtilRecordAudioDelegate代理，录音停止会调用
 *返回：返回BOOL值，YES说明函数执行成功，NO执行失败
 */
+(BOOL)start_record_audio:(unsigned int)max_seconds delegate:(id<UtilRecordAudioDelegate>)delegate;

/*
 *Util方法：停止录音
 */
+(void)stop_record_audio;

/*
 *Util方法：UtilRecordAudioDelegate回调
 *参数：
 *data:录音数据
 */
-(void)on_record_audio_finished:(NSData *)data;

b)示范
/*
 *开始录音
 */
[Util start_record_audio:10 delegate:self];
/*
 *停止录音
 */
[Util stop_record_audio];

/*
 * UtilRecordAudioDelegat回调
 */
-(void)on_record_audio_finished:(NSData *)data{
    NSLog(@“record audio finished!”);
    m_data = data;  //获取到录音数据，供播放和上传用
}

3.2播放／停止已录制好的录音文件

a)函数
/*
 *Util方法：播放录音
 *参数：
 * NSData:录音数据
 *delegate: UtilPlayAudioDelegate代理，播放录音停止或完成会调用
 *返回：返回BOOL值，YES说明函数执行成功，NO执行失败
 */
+(BOOL)start_play_audio:(NSData *)data delegate:(id<UtilPlayAudioDelegate>)delegate;

/*
 *Util方法：停止播放录音
 */
+(void)stop_play_audio;

/*
 *Util方法：停止或完成播放录音UtilPlayAudioDelegate回调，
 */
-(void)on_play_audio_finished;

b)示范
/*
 *播放录音
 */
[Util start_play_audio:m_data delegate:self];

/*
 *停止播放录音
 */
[Util stop_play_audio];

/*
 *代理on_play_audio_finished回调
 */
-(void)on_play_audio_finished
{
    NSLog(@“play audio finished!”);
}

3.3上传录音文件至IPC

a)函数
/*
 *IPCam方法：上传录音文件至IPC
 *参数：
 * type：规定为11
 * factory:设置为YES
 * data:上传的录音文件数据
 * delegate:代理IPCamUploadFileDelegate
 *返回：
 *返回IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示获上传成功，否则上传失败
 */
-(IPCAM_ERROR)upload_file:(int)type
factory:(BOOL)factory
data:(NSData *)data
delegate:(id<IPCamUploadFileDelegate>)delegate;

/*
 *IPCam方法：IPCamUploadFileDelegate回调函数
 *参数：
 *ipcam：返回一个id类型，其实就是一个IPCam
 * error:IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示获上传成功，否则上传失败
 */
-(void)on_upload_file_result:(id)ipcam
error:(IPCAM_ERROR)error;

示范：

/*
 *上传＋添加代理IPCamUploadFileDelegate
 */
[m_ipcam upload_file:11 factory:YES data:m_data delegate:self];

/*
 *代理IPCamUploadFileDelegate回调
 */

-(void)on_upload_file_result:(id)ipcam
error:(IPCAM_ERROR)error{
    if (error == IPCAM_ERROR_NO_ERROR) {
        NSLog(@"upload success!");
    }
    else{
        NSLog(@“upload fail!”);
    }
}