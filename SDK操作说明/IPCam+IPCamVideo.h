//
//  IPCam+IPCamVideo.h
//  SoDemon
//
//  Created by feng on 16/3/15.
//  Copyright © 2016年 feng. All rights reserved.
//
--------------------------------------------------------


#pragma mark 摄像机的解绑和注册

摄像机的解绑和注册
说明：当需要账号管理摄像机时，才会用到解绑和注册功能。大概流程事，添加时，先判断有没有被其他账号添加，如果被添加了，就先要解绑。解绑成功后，在用WebService的添加函数添加，添加成功后。在注册的到服务器上。
1）解绑
说明：解绑是，从账号里把该摄像机删除。同一个摄像机只能被一个账号添加。
函数：-(IPCAM_ERROR)unregister_from_sosocam:(id<IPCamUnregisterFromSoSoCamDelegate>)delegate;
返回：error:IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示执行成功。
ipcam：id类型,实际上就是一个IPCam类;
error:IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示获取解绑成功。

回调函数：
-(void)on_unregister_from_sosocam_result:(id)ipcam
error:(IPCAM_ERROR)error;
回调函数返回：
2）注册
说明：注册是，把摄像机向服务器注册。只有注册成功了才会有推送。
-(IPCAM_ERROR)relogin_to_sosocam:(id<IPCamReloginToSoSoCamDelegate>)delegate;
返回：error:IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示执行成功。

回调函数：-(void)on_relogin_to_sosocam_result:(id)ipcam
error:(IPCAM_ERROR)error;
回调函数返回：
ipcam：id类型,实际上就是一个IPCam类;
error:IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示注册成功。

3）示列



#pragma mark 摄像机属性添加设置和获取


1.摄像机属性添加设置和获取
说明：摄像机属性设置，包括名称，用户名，名称，id等等摄像机的相关属性参数。这些属性，只有当你往IPCam添加了，IPCam的创建的对象才具备这些属性（比如：名称，你必须先set_alias了，才能alias到名称）。所以你需要用到哪些属性，当你从stroage里面获取cam里时或添加cam时，就一定要为cam添加哪些属性，否则获取到的都是默认值。当然如果这些属性有改变时，也要同步设置到IPCam里。
函数：主要属性函数，详细如下
/*
 *名称
 *默认为空
 */
-(NSString *)alias; //获取昵称
-(void)set_alias:(NSString *)alias; //设置昵称

/*
 *用户名
 *默认为空
 */
-(NSString *)user;//获取登录名
-(void)set_user:(NSString *)user; //设置登录名

/*
 *密码设置
 *默认为空
 */
函数：-(NSString *)pwd; //获取机登录密码
-(void)set_pwd:(NSString *)pwd; //设置登录密码

/*
 ＊摄像机id
 *默认为空
 */
-(NSString *)camera_id; //获取id
-(void)set_camera_id:(NSString *)camera_id; //设置id

/*
 *摄像机sosocam_id
 *默认为空
 */
-(NSString *)sosocam_id;//获取sosocam_id
-(void)set_sosocam_id:(NSString *)sosocam_id;//设置sosocam_id


/*
 *摄像机安全传输
 *默认为No
 */

-(BOOL)https; //获取https
-(void)set_https:(BOOL)https; //设置https

/*
 *摄像机模式
 *model默认为0，有两个值，0 云台机  1 卡片机
 */
-(int32_t)model; //获取model
-(void)set_model:(int32_t)model; //设置model

/*
 *主摄像机
 *master默认为No
 */
-(BOOL)master; //设置master
-(void)set_master:(BOOL )master; //设置master值

/*
 *预览图
 *cover默认为nil
 */

-(NSData *)cover; //获取预览图
-(void)set_cover:(NSData *)cover; //设置预览图

/*
 *无线Wi-Fi信号强度，返回int值，范围［0，100］
 */

-(int)wifi_power; //获取信号强度

/*
 *缓冲时间
 *cache默认为0，局域网[0 1000ms]  P2P [1000ms 8000ms]
 */
-(int)cache; //获取缓冲时间
-(void)set_cache:(int)cache;//设置缓冲时间

/*
 *默认为0
 */
-(int)record_performance_speed;
-(void)set_record_performance_speed:(int)speed;
/*
 *默认为0
 */
-(int)video_performance_mode;
/*
 *默认为1
 */
-(void)set_video_performance_mode:(int)mode;

示列：
/*
 *以下示范，使在程序开始，开始从Storage取出cams，同时添加到IPCamMgr，使这些摄像机得到IPCamMgr的批量管里。并且为ipcam添加几个属性
 */
-(void)load_all_cameras
{
    NSArray * cameras_list = [[Storage get_share] get_cameras_list];
    IPCamMgr * ipcammgr = [IPCamMgr get_share];
    NSDictionary * camera;
    IPCam * ipcam;
    int i;
    
    for (i = 0;i < cameras_list.count;i ++) {
        camera = [cameras_list objectAtIndex:i];
        ipcam = [ipcammgr add_camera:[camera objectForKey:@"camera_id"] alias:[camera objectForKey:@"alias"] user:[camera objectForKey:@"user"] pwd:[camera objectForKey:@"pwd"] https:[[camera objectForKey:@"https"] boolValue]];//设置ID，昵称，用户名，密码和加密值
        [ipcam set_cover:[camera objectForKey:@"cover"]]; //设置预览图
        [ipcam set_model:[[camera objectForKey:@"model"] intValue]]; //设置模式
        [ipcam set_sosocam_id:[camera objectForKey:@"sosocam_id"]]; //设置sosocam_id
    }
}


----------------------------------------------------
#pragma mark 1.视频性能调节

1.视频性能调节
说明：视频性能，主要包含两个概念，视频的画质质量和视频的速度快慢。想要快必须牺牲质量。想要质量那必须要速度啦。视频调解。使用以下函数之前，必须保证视频是播放状态。
函数1:-(int)video_performance_mode;//获取当前性能值
返回:返回一个int类型，0：清晰；1：均衡；2：流畅

函数2：-(BOOL)can_set_video_performance;//判断是否允许设置
返回：返回一个BOOL类型，如果是Yes,说明允许操作，如果是No,说明禁止操作，因为视频调解具有优先级，先操作的人具有优先权操作。

函数3:-(void)set_video_performance_mode:(int)mode //设置性能值
参数：mode有三个值，详细如下
mode ＝ 0， //清晰，质量最好，速度最慢
mode ＝ 1，//均衡，质量和速度都处于均值
mode ＝ 2， //流畅，质量最差，速度最快

代理：-(void)on_can_set_video_performance:(id)ipcam;
说明：视频性能状态改变，代理是IPCamDelegate，使用方法参考［2.2.摄像机基础代理增加］

示列：
int value = [m_ipcam video_performance_mode]//获取当前性能值


- (IBAction)button_performance_onclick:(id)sender {
    if ([m_ipcam can_set_video_performance]) {//判断是否允许设置
        [m_ipcam set_video_performance_mode:1]; //设置性能值
    } else {
        [Util show_short_toast:LOCAL_STR(@"NO_RIGHTS_OPERATION")];
    }
}

#pragma mark 2.缓冲时间设置
2.缓冲时间设置
说明：缓冲时间对视频和音频生效，就是推迟多少时间再显示或发声。使用以下函数时，必须保证摄像机是连接的。
函数：-(int)cache; //获取当前缓冲值，单位ms
-(void)set_cache:(int)cache; //设置

参数：cache缓冲时间，它的值分两种，详细如下：
局域网：[0-1000],单位:ms
p2p:[1000-8000],单位:ms
示列：
[m_ipcam cache];  //获取缓冲时间
[m_ipcam set_cache:1000]; //设置缓冲时间

#pragma mark 3.名称设置
3.名称设置
说明：名称设置，是摄像机的一个昵称，设置成功以后，需要保存更新到本地，如果摄像机要保存到服务器，还需要更新保存到服务器。使用以下函数时，必须保证摄像机是连接的。

函数：-(NSString *)alias; //获取名称
-(void)set_alias:(NSString *)alias; //设置名称

说明：当摄像机的名称发生改变时，调用此函数，使用说明请参考［2.2摄像机基础代理］
代理函数：-(void)on_alias_changed:(id)ipcam;

示列：
[m_ipcam alias]; //获取名称

-(void) set_name {
    [m_ipcam set_alias:m_camera_name]; //设置名称
    [[Storage get_share] update_camera_alias:[m_ipcam camera_id] alias:m_camera_name]; //更新保存到本地
}

#pragma mark 4.重置新密码：

4.重置新密码：
说明：重置密码，是指重新设置一个新的摄像机登录密码。和设置密码不同。使用以下函数时，必须保证摄像机是连接的。

1）重置密码
说明：重新给摄像机设置一个新的密码，使用重置密码函数的条件是摄像机必须连接成功。
函数：-(IPCAM_ERROR)reset_pwd:(NSString *)pwd
delegate:(id<IPCamResetPwdDelegate>)delegate;
参数：pwd:进行utf8编码的新密码
2）回调
说明：用reset_pwd函数，添加代理IPCamResetPwdDelegate，当有结果时，就会掉用on_reset_pwd_result函数。
函数：-(void)on_reset_pwd_result:(id)ipcam
error:(IPCAM_ERROR)error;
返回：返回两个参数，详细如下：
ipcam：返回一个id类型，其实就是一个IPCam
error:IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示重置密码成功

示列：
[m_ipcam reset_pwd:[m_view get_new_pwd1] delegate:self];  //重置密码且
-(void)on_reset_pwd_result:(id)ipcam
error:(IPCAM_ERROR)error
{
    if (IPCAM_ERROR_NO_ERROR == error) {
        [[Storage get_share] update_camera_pwd:[ipcam camera_id] pwd:[ipcam pwd]]; //更新保存到本地
        [self show_error:LOCAL_STR(@"RESET_PWD_SUCCESS")];
    } else {
        [self show_error:LOCAL_STR(@"FAIL_TO_RESET_PWD")];
    }
}

#pragma mark 5.系统固件升级

5.系统固件升级
说明：系统固件升级主要介绍：新版本检测，当前固件版本号的获取和最新固件版本号的获取，以及实现升级功能。
1）新版本检测
说明:新版本检测函数使用的条件是摄像机必须连接成功。
函数：-(BOOL)need_upgrade
返回：返回一个BOOL，返回Yes表示有新版本，需要升级；返回No表示摄像机当前固件版本已经是最新版本，不需要升级。
2）版本号获取
说明，以下两个函数使用的条件都是摄像机必须连接成功。
函数：-(NSString *)current_fw_version; //获取摄像机当前的固件版本号
-(NSString *)latest_fw_version; //获取服务器上最新的固件版本号
返回：两个函数都是返回NSString类型，即版本号。
3）升级功能实现
说明：用upgrade_fw函数，添加代理IPCamUpgradeFWDelegate，当有结果时，就会掉用on_upgrade_fw_result函数，使用升级函数的条件是摄像机必须连接成功。
函数：-(IPCAM_ERROR)upgrade_fw:(id<IPCamUpgradeFWDelegate>)delegate //升级函数
-(void)on_upgrade_fw_result:(id)ipcam
error:(IPCAM_ERROR)error; //回调函数

返回：error:IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示升级成功。，否则升级失败

示列：
/*检测当前版本是否是最新版本*/
-(void)checkNewVersion{
    if([ipcam need_upgrade]){
        /*检测到有新版本*/
        NSLog(@"delect new version,new version is :％@!", [ipcam latest_fw_version]); //获取最新版本号
        [self upGradeFw];  //升级新版本
    }
    else{
        /*没有发现新版本*/
        NSLog(@"version:％@ is lastest !", [ipcam current_fw_version]);//获取当前固件版本号
    }
}

/*执行升级动作且添加升级代理*/
-(void)upGradeFw{
    [ipcam upgrade_fw:self];
}
/*升级完以后的回调*/
-(void)on_upgrade_fw_result:(id)ipcam error:(IPCAM_ERROR)error {
    if (IPCAM_ERROR_NO_ERROR == error) {
        [self show_error:LOCAL_STR(@"UPGRADE_CAM_SUCCESS")];
    } else {
        [self show_error:LOCAL_STR(@"UPGRADE_CAM_FAIL")];
    }
}

#pragma mark 6.设置安全传输

6.设置安全传输

1）获取摄像机当前https值
说明：使用以下函数的条件摄像机必须连接成功。
函数：-(BOOL)https
返回：返回一个BOOL类型，当返回Yes表示当前是安全传输的，返回No表示当前不是安全传输的。
2）安全设置实现
说明：使用reset_https函数，添加代理IPCamResetHttpsDelegate，当有结果时，就会掉用on_reset_https_result函数，使用安全设置函数的条件是摄像机必须连接成功。
函数：-(IPCAM_ERROR)reset_https:(BOOL)https
delegate:(id<IPCamResetHttpsDelegate>)delegate; //安全设置函数
参数：https = Yes,设置成安全传输；https = No,设置成非安全传输；
回调函数：-(void)on_reset_https_result:(id)ipcam error:(IPCAM_ERROR)error

示列：

/* 获取摄像机当前https*/
BOOL m_https = [m_ipcam https];

/* 执行设置https功能*/
-(IBAction)button_ok_onclicked:(id)sender {
    m_https = !m_https;
    if (IPCAM_ERROR_NO_ERROR == [m_ipcam reset_https:m_https delegate:self]) {
        NSLog(@"setting https ...");
    } else {
        [self show_error:LOCAL_STR(@"set https fail")];
    }
}
/*设置完以后的回调*/
-(void)on_reset_https_result:(id)ipcam error:(IPCAM_ERROR)error {
    if (error == IPCAM_ERROR_NO_ERROR) {
        [[Storage get_share] update_camera_https:[m_ipcam camera_id] https:[m_ipcam https]];
        [self show_error:LOCAL_STR(@"SET_SAFE_SUCCESS")];
    } else {
        [self show_error:LOCAL_STR(@"SET_SAFE_FAIL")];
    }
}

#pragma mark 7.恢复出厂参数

7.恢复出厂参数
说明：恢复出厂参数是指把摄像机里面的参数恢复到出厂时的参数，使用以下函数时，必须保证摄像机是连接的。
1）恢复出厂
说明：恢复参数成功后，需要重启才生效［重启是通过cgi实现的］
函数：-(IPCAM_ERROR)restore_factory:(id<IPCamRestoreFactoryDelegate>)delegate; //hu
2）回调
说明：如果执行恢复参数时候，添加了IPCamRestoreFactoryDelegate代理，那么当恢复出厂有结果后，就会掉用此代理函数。
函数：-(void)on_restore_factory_result:(id)ipcam
error:(IPCAM_ERROR)error;
返回：返回两个参数，详细如下：
ipcam：返回一个id类型，其实就是一个IPCam
error:IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示恢复出厂成功。
示列：
[m_ipcam restore_factory:self] //恢复出厂参数，且添加代理
/*恢复出厂的代理*/
-(void)on_restore_factory_result:(id)ipcam error:(IPCAM_ERROR)error {
    if (error == IPCAM_ERROR_NO_ERROR) {
        if (IPCAM_ERROR_NO_ERROR == [m_ipcam set_params:@"reboot=1" delegate:self]) {
            [self show_error:LOCAL_STR(@"REBOOT_CAM_SUCCESS")];
            return;
        } else {
            [self show_error:LOCAL_STR(@"REBOOT_CAM_FAIL")];
            return;
        }
    } else {
        [self show_error:LOCAL_STR(@"RESTORE_CAM_FAIL")];
    }
}


－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
IPCam类和IPCamVideoView类

说明：
IPCam类是管理单个cam,录像，拍照，对讲等各种功能的实现以及监控cam各种状态，连接，视频，音频等。使用步骤如下：
1. 初始化:通过IPCamMgr的init函数初始化。
2. 创建对象：new一个IPCam。
3. 添加代理：添加摄像机的IPCamDelegate代理。[这一步不适必须的，但是如果想随时监控链接状态，就必须要进行连接操作前添加此代理]
4. 判断是否摄像机连接：通过status获取摄像机当前状态，如果是IPCAM_STATUS_IDLE，通过error获取错误原因。
5. 连接成功后相关可行操作：如果status是IPCAM_STATUS_CONNECTED，，表示连接成功，就可以进行名称，密码，布防等各种操作，也可以获取到接状态，报警状态的获取.
6.视频打开成功后相关可行操作：如果想要尽兴拍照，录像，看视频，视频性能，缓冲，分辨率切换，轨迹设置，启动位设置等相关操作，必须是视频状态是IPCAM_PLAY_STATUS_PLAYING。所以必须先通过set_video_view设置视频view，然后在播放视频。视频播放成功，才可进行这些操作。

IPCamVideoView类是一个视频类，继承UIView,主要是用的地方就两个：
1）看视频：new一个IPCamVideoView，设置frame,添加，然后通过IPCam的set_video_view设置视频。
2）视频上添加手势：如果想要视频上添加手势，就添加代理IPCamVideoView 的set_delegate添加代理IPCamVideoViewDelegate。在代理on_touch_event中实现功能。

－－－－－－－
#pragma mark 2.1cam状态获取

2.1cam状态获取
1）连接状态
说明：一般对摄像机做操作前，都要判断一下摄像机的连接状态
函数：-(IPCAM_STATUS)status;
返回：返回IPCAM_STATUS类型，状态如下：
typedef enum {
    IPCAM_STATUS_IDLE, //连接失败
    IPCAM_STATUS_P2P_CONNECTING,//P2P连接中
    IPCAM_STATUS_CONNECTING, //局域网连接中
    IPCAM_STATUS_AUTHING,//摄像机连接认证中
    IPCAM_STATUS_CONNECTED,//已连接
    IPCAM_STATUS_WAIT_CONNECTING,//等待连接
} IPCAM_STATUS;
示范：
IPCAM_STATUS status = [ipcam status];
2）摄像机错误
说明：一般当摄像机的连接状态[ipcam status]＝ IPCAM_STATUS_IDLE，才会去获取错误值
函数：-(IPCAM_ERROR)error;
返回：返回IPCAM_ERROR类型，状态如下：
typedef enum {
    IPCAM_ERROR_NO_ERROR,//没有错误
    IPCAM_ERROR_UNKNOWN,//未知错误
    IPCAM_ERROR_INTERNAL_ERROR,//内部错误
    IPCAM_ERROR_BAD_PARAM, //参数错误
    IPCAM_ERROR_BAD_STATUS, //状态错误
    IPCAM_ERROR_BAD_ID,//无效id
    IPCAM_ERROR_NETWORK_ERROR,//网络错误
    IPCAM_ERROR_CLOSED_BY_DEVICE,
    IPCAM_ERROR_BAD_AUTH,//认证错误
    IPCAM_ERROR_DEVICE_TOO_MANY_SESSIONS,//达到最大会话数
    IPCAM_ERROR_DEVICE_INTERNAL_ERROR,//设备内部错误
    IPCAM_ERROR_DEVICE_BAD_PARAM,//设备参数错误
    IPCAM_ERROR_DEVICE_FORBIDDEN,//
    IPCAM_ERROR_DEVICE_BAD_STATUS,//设备错误状态
    IPCAM_ERROR_DEVICE_OPERATION_FAIL,//设备操作失败
    IPCAM_ERROR_P2P_DISCONNECTED,//P2P连接断开
    IPCAM_ERROR_P2P_INVALID_ID,//无效p2p ID
    IPCAM_ERROR_P2P_DEVICE_OFFLINE,//远程设备不在线
    IPCAM_ERROR_P2P_TIMEOUT,//p2p连接超时
    IPCAM_ERROR_P2P_TOO_MANY_SESSIONS,//p2p连接达到最大会话数
    IPCAM_ERROR_P2P_NETWORK_ERROR,//p2p网络错误
    IPCAM_ERROR_P2P_OUTOF_CAPACITY,
    IPCAM_ERROR_P2P_SERVER_ERROR,
    IPCAM_ERROR_HTTP_GET_ERROR,
    IPCAM_ERROR_DEVICE_TIMEOUT,
    IPCAM_ERROR_DEVICE_BAD_REQUEST,
    IPCAM_ERROR_UPGRADE_BAD_FILE,
    IPCAM_ERROR_UPGRADE_BAD_SERVER,
    IPCAM_ERROR_UPGRADE_DOWNLOAD_FAILED,
    IPCAM_ERROR_SOSOCAM_BAD_ID,
    IPCAM_ERROR_SOSOCAM_BAD_ACCESS,
    IPCAM_ERROR_SOSOCAM_UNREGISTERED,
    IPCAM_ERROR_CANCELED,
} IPCAM_ERROR;

示列：    IPCAM_ERROR camError = [m_ipcam error];

#pragma mark 2.2.摄像机基础代理

2.2.摄像机基础代理
说明：一般创建了IPCam类，就会添加IPCamDelegate代理，这是IPCam的一个基本代理。add_delegate和remove_delegate是成对出现的，有add_delegate必须有remove_delegate，同时回调的那些函数，一旦add_delegate了，就必须全部写出来，即使什么功能都不实现，不然程序会奔溃。

1）添加代理
说明：使用此函
数，就添加了IPCamDelegate代理，当相关信息发生改变时，就会反馈到回调函数中。
函数：-(void)add_delegate:(id<IPCamDelegate>)delegate;

2）回调函数
说明：回调函数，主要是相关信息改变时，回调，详细如下：函数：
-(void)on_alias_changed:(id)ipcam;  //摄像机名称改变

-(void)on_cover_changed:(id)ipcam; //摄像机封面改变

-(void)on_status_changed:(id)ipcam; //摄像机连接状态改变

-(void)on_video_status_changed:(id)ipcam; //摄像机视频状态改变

-(void)on_audio_status_changed:(id)ipcam; //摄像机音频状态改变

-(void)on_speak_status_changed:(id)ipcam; //摄像机对讲状态改变

-(void)on_tf_record_status_changed:(id)ipcam; //摄像机tf卡录像状态改变

-(void)on_tf_record_event:(id)ipcam
new_record:(BOOL)new_record
record_id:(int32_t)record_id
error:(BOOL)error;

//-(void)on_camera_tf_changed:(id)ipcam;

-(void)on_camera_tf_capacity:(id)ipcam;     // 内存卡状态改变

-(void)on_camera_wifi_changed:(id)ipcam;

-(void)on_camera_alarm_changed:(id)ipcam;

-(void)on_bell_alarm_changed:(id)ipcam;

-(void)on_camera_recording_changed:(id)ipcam; //本地录像状态改变

-(void)on_camera_can_upgrade:(id)ipcam;

-(void)on_camera_power_down_changed:(id)ipcam;

-(void)on_camera_arm_changed:(id)ipcam;  //布防状态改变

-(void)on_camera_sessions_change:(id)ipcam;     // 摄像机固件版本改变

-(void)on_camera_dijia_power_changed:(id)ipcam; //客户定制版本

-(void)on_camera_dijia_speed_changed:(id)ipcam; //客户定制版本

-(void)on_camera_dijia_mute_changed:(id)ipcam; //客户定制版本

-(void)on_camera_dijia_status_changed:(id)ipcam; //客户定制版本

-(void)on_statistic:(id)ipcam;

-(void)on_can_set_video_performance:(id)ipcam; //视频性能改变

-(void)on_camera_temperature_changed:(id)ipcam; //摄像机温度改变

-(void)on_camera_meijing_play_changed:(id)ipcam; //客户定制版本

-(void)on_camera_meijing_led_changed:(id)ipcam; //客户定制版本

-(void)on_camera_ewig_status_changed:(id)ipcam; //客户定制版本

-(void)on_camera_juyang_led_changed:(id)ipcam;  //客户定制版本


3）删除代理
说明：当不需要监控回调函数里面的这些状态时，就要删除这个代理。
函数：-(void)remove_delegate:(id<IPCamDelegate>)delegate;

示列：

/* 添加代理*/
[m_ipcam add_delegate:self];
/*代理回调实现*/
-(void)on_alias_changed:(id)ipcam{
    
    NSLog(@"camera alias change to :%@",[ipcam alias]);
}
.
.
.
-(void)on_camera_meijing_led_changed:(id)ipcam{
    
    NSLog(@"camera alias change to :%@",[ipcam alias]);
    
}
/*不需要IPCamDelegate代理时，一定要记得删除*/
[m_ipcam remove_delegate:self];

#pragma mark 2.3.摄像机视频

2.3.摄像机视频
说明：摄像机视频，主要是视频设置，视频状态获取，视频开关，以及分辨率切换，使用此函数之前，摄像机必须是连接成功的
1)设置视频页面
说明：通过此函数，可以设置视频页面［之前先要创建添加一个IPCamVideoView，以及设置frame］，使用此函数之前，摄像机状态必须是连接成功的。
函数：-(void)set_video_view:(IPCamVideoView *)video_view;  //设置视频页面
参数：video_view：这是一个IPCamVideoView, IPCamVideoView是一个继承UIView.
2）视频状态
说明：通过此函数，可以获取到视频状态，使用此函数之前，摄像机必须是连接成功的。
函数：-(IPCAM_PLAY_STATUS)video_status;
返回：返回IPCAM_PLAY_STATUS类型，类型状态如下：
typedef enum {
    IPCAM_PLAY_STATUS_STOPPED, //停止
    IPCAM_PLAY_STATUS_REQUESTING,//请求中
    IPCAM_PLAY_STATUS_PLAYING,//播放中
} IPCAM_PLAY_STATUS;
3）视频质量参数
说明：通过以下参数，可以获取到视频当前的质量参数，使用以下函数之前，摄像机必须是连接的。
函数：
-(int)video_render_fps; //视频发送fps
-(int)video_recv_fps; //视频接收的fbs
-(int)video_byterate; //视频的byte

4）播放视频或切换播放视频流
说明：通过此函数，可以实现播放视频或切换播放视频流功能，使用此函数之前，摄像机必须是连接成功的。
函数：-(IPCAM_ERROR)play_video:(int)stream;
参数：stream 是视频流参数（0或1），3518e只有两个分辨率，stream = 0 640*480 标清；stream = 1, 1280*960 高清。
返回：返回IPCAM_ERROR类型，当返回类型是IPCAM_ERROR_NO_ERROR时，表示开启播放视频或者切换视频流成功。

5）停止播放视频
说明：通过此函数，可以实现停止播放视频功能，使用此函数之前，摄像机必须是连接成功的。
函数：-(void)stop_video;

6）视频代理
说明：视频代理主要有两个，一个是IPCamDelegate，请参考此章节2.2［摄像机基础代理增加］,另外一个是IPCamVideoView里的IPCamVideoViewDelegate，如果你想要在视频上[注意是IPCamVideoView上不是IPCam]添加手势，就添加此代理。
函数：-(void)set_delegate:(id<IPCamVideoViewDelegate>)delegate;
回调：-(void)on_touch_event:(IPCAMVIDEOVIEW_TOUCH_EVENT)event;
回调返回参数：返回IPCAMVIDEOVIEW_TOUCH_EVENT参数，详细如下：
typedef enum {
    IPCAMVIDEOVIEW_TOUCH_EVENT_CLICK, //单点
    IPCAMVIDEOVIEW_TOUCH_EVENT_MOVE_UP, //向上滑动
    IPCAMVIDEOVIEW_TOUCH_EVENT_MOVE_DOWN, //向下滑动
    IPCAMVIDEOVIEW_TOUCH_EVENT_MOVE_LEFT, //向左滑动
    IPCAMVIDEOVIEW_TOUCH_EVENT_MOVE_RIGHT, //向右滑动
} IPCAMVIDEOVIEW_TOUCH_EVENT;

示列：
/*创建一个IPCamVideoView设置大小，再设置视频页面*/
IPCamVideoView * m_videoview = [[IPCamVideoView alloc]initWithFrame:CGRectMake(0, 0, self.view.bounds.size.width, self.view.bounds.size.height)];
[self.view addSubview:m_videoview];
[m_ipcam set_video_view:m_videoview];//设置视频页面

/*在视频上添加代理IPCamVideoViewDelegate*/
[m_videoview set_delegate:self]; //m_videoview添加IPCamVideoViewDelegate不是m_ipcam
/* 视频播放和停止*/
- (IBAction)button_playvideo_onclick:(id)sender {
    IPCAM_PLAY_STATUS status = [m_ipcam video_status];//获取视频当前状态
    if (status == IPCAM_PLAY_STATUS_PLAYING)
        [m_ipcam stop_video]; // 停止播放视频
    else if (status == IPCAM_PLAY_STATUS_STOPPED)
        [m_ipcam play_video:m_playing_video_stream]; //播放m_playing_video_stream路视频流
}
/*设置播放视频流，即高清和标清设置或切换 */
- (IBAction)button_stream_onclick:(id)sender {
    if (m_playing_video_stream == 0)
        m_playing_video_stream = 1;
        else
            m_playing_video_stream = 0;
            
            [m_ipcam stop_video];
    [m_ipcam play_video:m_playing_video_stream];
}

/*IPCamVideoViewDelegate回调实现*/
-(void)on_touch_event:(IPCAMVIDEOVIEW_TOUCH_EVENT)event
{
    switch (event) {
        case IPCAMVIDEOVIEW_TOUCH_EVENT_CLICK:
            NSLog(@"单点了一下");
            break;
        case IPCAMVIDEOVIEW_TOUCH_EVENT_MOVE_DOWN:
            NSLog(@"向下移动了一下");
            break;
        case IPCAMVIDEOVIEW_TOUCH_EVENT_MOVE_LEFT:
            NSLog(@"向左移动了一下");
            break;
        case IPCAMVIDEOVIEW_TOUCH_EVENT_MOVE_RIGHT:
            NSLog(@"向右移动了一下");
            break;
        case IPCAMVIDEOVIEW_TOUCH_EVENT_MOVE_UP:
            NSLog(@"向上移动了一下");
            break;
        default:
            break;
    }
}
#pragma mark 2.4，摄像机音频

2.4，摄像机音频
说明：摄像机音频，主要包括音频状态获取，音频开启和关闭操作。操作以下函数前，摄像机必须是连接成功的。
1）音频状态
说明：通过此函数，可以获取到音频状态，使用此函数之前，摄像机必须是连接成功的。
函数：-(IPCAM_PLAY_STATUS)audio_status;
返回：返回IPCAM_PLAY_STATUS类型，类型状态如下：
typedef enum {
    IPCAM_PLAY_STATUS_STOPPED, //停止
    IPCAM_PLAY_STATUS_REQUESTING,//请求中
    IPCAM_PLAY_STATUS_PLAYING,//播放中
} IPCAM_PLAY_STATUS;

2)音频质量
说明：使用以下两个函数可以获取到音频质量的相关数据，使用以下两个函数之前，摄像机必须是连接成功的。
函数：
-(int)audio_sps; //音频的sps
-(int)audio_byterate; //音频的byte


3）开启音频
说明：通过此函数，可以实现开启音频功能，使用此函数之前，摄像机必须是连接成功的。
函数：-(IPCAM_ERROR)play_audio;
返回：返回IPCAM_ERROR类型，当返回类型是IPCAM_ERROR_NO_ERROR时，表示开启音频成功。

4）关闭音频
说明：通过此函数，可以实现关闭音频功能，使用此函数之前，摄像机必须是连接成功的。
函数：-(void)stop_audio;

5）代理
说明：使用方法请参考［2.2摄像机基础代理］
回调函数：-(void)on_audio_status_changed:(id)ipcam;

示列：
- (IBAction)button_playaudio_onclick:(UIButton*)sender {
    IPCAM_PLAY_STATUS status = [m_ipcam audio_status]; //获取音频状态
    if (status == IPCAM_PLAY_STATUS_PLAYING)
        [m_ipcam stop_audio]; //关闭音频
    else if (status == IPCAM_PLAY_STATUS_STOPPED)
        [m_ipcam play_audio];//开启音频
}
#pragma mark 2.5.摄像机对讲
2.5.摄像机对讲
说明：摄像机对讲，主要包括对讲状态获取，对讲开启和关闭操作。操作以下函数前，摄像机必须是连接成功的。
1）对讲状态
说明：通过此函数，可以获取到摄像机当前的对讲状态，使用此函数之前，摄像机必须是连接成功的。
函数：-(IPCAM_PLAY_STATUS)speak_status;
返回：返回IPCAM_PLAY_STATUS类型，类型状态如下：
typedef enum {
    IPCAM_PLAY_STATUS_STOPPED, //停止
    IPCAM_PLAY_STATUS_REQUESTING,//请求中
    IPCAM_PLAY_STATUS_PLAYING,//播放中
} IPCAM_PLAY_STATUS;
2)对讲质量
说明：通过以下函数可以获取到对讲数量相关数据，使用以下函数前，摄像机必须是连接的。
函数：
-(int)speak_sps; //对讲的sps
-(int)speak_byterate; //对讲的byte

3）开启对讲
说明：通过此函数，可以实现开启对讲功能，使用此函数之前，摄像机必须是连接成功的。
函数：-(IPCAM_ERROR)start_speak;
返回：返回IPCAM_ERROR类型，当返回类型是IPCAM_ERROR_NO_ERROR时，表示开启对讲成功。

4）关闭对讲
说明：通过此函数，可以实现关闭对讲功能，使用此函数之前，摄像机必须是连接成功的。
函数：-(void)stop_speak;

4）代理
说明：使用方法请参考［2.2摄像机基础代理］
回调函数：-(void)on_speak_status_changed:(id)ipcam;

示列：
- (IBAction)button_speak_onclick:(id)sender {
    IPCAM_PLAY_STATUS status = [m_ipcam speak_status]; //对讲状态
    if (status == IPCAM_PLAY_STATUS_PLAYING)
        [m_ipcam stop_speak];
    else if (status == IPCAM_PLAY_STATUS_STOPPED)
        [m_ipcam start_speak];
}

#pragma mark 2.6，摄像机本地录像

2.6，摄像机本地录像
说明：摄像机本地录像，主要包括本地录像状态获取，开启本地录像和停滞本地录像。操作以下函数前，摄像机必须是连接成功的。
1）本地录像状态
说明：通过此函数，可以获取到摄像机本地录像状态，使用此函数之前，摄像机必须是连接成功的。
函数：-(IPCAM_PLAY_STATUS)local_record_status;
返回：返回IPCAM_PLAY_STATUS类型，类型状态如下：
typedef enum {
    IPCAM_PLAY_STATUS_STOPPED, //停止
    IPCAM_PLAY_STATUS_REQUESTING,//请求中
    IPCAM_PLAY_STATUS_PLAYING,//录像中
} IPCAM_PLAY_STATUS;

2）开启本地录像
说明：使用下面任何一个函数可以实现录像功能，函数1不带存储地址的函数，使用前，必须创建一个登录账号[否则会因为存储地址错误，导致存储失败]，获取录像文件直接通过Storage的一个函数直接获取。函数2带存储地址，自己决定存储地址，自己从地址中获取录像文件。另外不管是用那一个函数实现录像，使用前必须保证摄像机视频是打开的。
函数1:-(IPCAM_ERROR)start_local_record;
返回：返回IPCAM_ERROR类型，当返回类型是IPCAM_ERROR_NO_ERROR时，表示开启录像成功。
函数2:-(IPCAM_ERROR)start_local_record:(NSString*)record_file_path;
参数：record_file_path：录像本地存储地址
返回：返回IPCAM_ERROR类型，当返回类型是IPCAM_ERROR_NO_ERROR时，表示拍照成功。

3）停止本地录像
说明：通过此函数实现停止录像功能
函数：-(void)stop_local_record;

4）本地录像代理
说明：使用方法请参考［2.2摄像机基础代理］
回调函数：-(void)on_camera_recording_changed:(id)ipcam;

示列：

- (IBAction)button_record_onclick:(id)sender {
    if ( [m_ipcam local_record_status] == IPCAM_PLAY_STATUS_PLAYING) { //本地录像状态获取
        [m_ipcam stop_local_record];  //停止录像
    }
    else {
        if (IPCAM_ERROR_NO_ERROR == [m_ipcam start_local_record]) //开启录像
        {
            m_record_Start_Time = [NSDate date];
            m_record_Timer = [NSTimer scheduledTimerWithTimeInterval:1.0 target:self selector:@selector(change_time) userInfo:nil repeats:YES];
            [m_record_Timer fire];}
        else
            [Util show_short_toast:LOCAL_STR(@"RECORD_SUCCESS")];
    }
}

#pragma mark 2.7.摄像机拍照
2.7.摄像机拍照
说明：使用下面任何一个函数可以实现拍照功能，函数1不带存储地址的函数，使用前，必须创建一个登录账号[否则会因为存储地址错误，导致存储失败]，获取照片直接通过Storage的一个函数直接获取。函数2带存储地址，自己决定存储地址，自己从地址中获取照片。另外不管是用那一个函数实现拍照，使用前必须保证摄像机视频是打开的。
函数1：-(IPCAM_ERROR)snapshot;
返回：返回IPCAM_ERROR类型，当返回类型是IPCAM_ERROR_NO_ERROR时，表示拍照成功。
函数2:-(IPCAM_ERROR)snapshot:(NSString*)photo_file_path;
参数：photo_file_path：照片本地存储地址
返回：返回IPCAM_ERROR类型，当返回类型是IPCAM_ERROR_NO_ERROR时，表示拍照成功。

示列：
- (IBAction)button_snapshot_onclick:(id)sender {
    if (IPCAM_ERROR_NO_ERROR == [m_ipcam snapshot])
        [Util show_short_toast:LOCAL_STR(@"SNAPSHOT_SUCCESS")];
    else
        [Util show_short_toast:LOCAL_STR(@"SNAPSHOT_FAIL")];
}


#pragma mark 2.8.ptz命令控制巡航

2.8.ptz命令控制巡航
说明：摄像机ptz巡航操作，主要水平巡航开关，垂直巡航开关，轨迹巡航开关，启动预置位的设置和清除，轨迹巡航点设置，以及上下左右操作
2.8.1水平/垂直／轨迹巡航设置
函数：-(IPCAM_ERROR)ptz_control:(IPCAM_PTZ_CMD)cmd
param:(int)param
参数：主要有两个参数，详细如下：
cmd：IPCAM_PTZ_CMD命令，巡航操作命令主要如下：
typedef enum {
    IPCAM_PTZ_CMD_UP, //向上
    IPCAM_PTZ_CMD_DOWN,//向下
    IPCAM_PTZ_CMD_LEFT,//向左
    IPCAM_PTZ_CMD_RIGHT,//向右
    IPCAM_PTZ_CMD_T_PATROL,//水平巡航
    IPCAM_PTZ_CMD_P_PATROL,//垂直巡航
    IPCAM_PTZ_CMD_TRACK_PATROL,//轨迹巡航
    
    IPCAM_PTZ_CMD_MEIJING_VOLUME_UP, //客户定制功能
    IPCAM_PTZ_CMD_MEIJING_VOLUME_DOWN,//客户定制功能
    IPCAM_PTZ_CMD_MEIJING_NEXT_TRACK,//客户定制功能
    IPCAM_PTZ_CMD_MEIJING_PREVIOUS_TRACK,//客户定制功能
    IPCAM_PTZ_CMD_MEIJING_PLAY_PAUSE,//客户定制功能
    IPCAM_PTZ_CMD_MEIJING_LED_POWER,//客户定制功能
    IPCAM_PTZ_CMD_MEIJING_LED_STYLE,//客户定制功能
    
    IPCAM_PTZ_CMD_DIJIA_QUIT,//客户定制功能
    IPCAM_PTZ_CMD_DIJIA_AUTO,//客户定制功能
    IPCAM_PTZ_CMD_DIJIA_TIMER,//客户定制功能
    IPCAM_PTZ_CMD_DIJIA_SWALL,//客户定制功能
    IPCAM_PTZ_CMD_DIJIA_Z,//客户定制功能
    IPCAM_PTZ_CMD_DIJIA_CHARGE,//客户定制功能
    IPCAM_PTZ_CMD_DIJIA_LEFT,//客户定制功能
    IPCAM_PTZ_CMD_DIJIA_RIGHT,//客户定制功能
    IPCAM_PTZ_CMD_DIJIA_UP,//客户定制功能
    IPCAM_PTZ_CMD_DIJIA_DOWN,//客户定制功能
    IPCAM_PTZ_CMD_DIJIA_STOP,//客户定制功能
    IPCAM_PTZ_CMD_DIJIA_MUTE,//客户定制功能
    IPCAM_PTZ_CMD_DIJIA_SPEED//客户定制功能
    IPCAM_PTZ_CMD_EWIG_LANUCH_FEED//客户定制功能
    IPCAM_PTZ_CMD_EWIG_STOP_FEED//客户定制功能
    IPCAM_PTZ_CMD_EWIG_PLAY_MELODY//客户定制功能
    IPCAM_PTZ_CMD_EWIG_STOP_MELODY//客户定制功能
    IPCAM_PTZ_CMD_EWIG_SET_FOOD//客户定制功能
    
} IPCAM_PTZ_CMD;

param：参数值，0:关  20:开 [ 上下左右控制没有停止命令，param固定位20，发一下，动一次]


示列：
／*水平巡航*/
- (IBAction)m_button_levelpatrol_go_onclick:(UIButton*)sender {
    sender.selected = YES;
    if (m_button_Level_stop.selected) {
        m_button_Level_stop.selected = NO;
    }
    [m_ipcam ptz_control:IPCAM_PTZ_CMD_P_PATROL param:20]; //开启水平巡航
}
- (IBAction)m_button_levelpatrol_stop_onclick:(UIButton*)sender {
    sender.selected = YES;
    if (m_button_Level_stop.selected) {
        m_button_Level_stop.selected = NO;
    }
    [m_ipcam ptz_control:IPCAM_PTZ_CMD_P_PATROL param:0];//关闭水平巡航
}

/*上下左右控制*/

-(void)on_touch_event:(IPCAMVIDEOVIEW_TOUCH_EVENT)event
{
    switch (event) {
        case IPCAMVIDEOVIEW_TOUCH_EVENT_MOVE_DOWN:
            [m_ipcam ptz_control:IPCAM_PTZ_CMD_DOWN param:20]; //上
            break;
        case IPCAMVIDEOVIEW_TOUCH_EVENT_MOVE_LEFT:
            [m_ipcam ptz_control:IPCAM_PTZ_CMD_LEFT param:20];//左
            break;
        case IPCAMVIDEOVIEW_TOUCH_EVENT_MOVE_RIGHT:
            [m_ipcam ptz_control:IPCAM_PTZ_CMD_RIGHT param:20];/右
            break;
        case IPCAMVIDEOVIEW_TOUCH_EVENT_MOVE_UP:
            [m_ipcam ptz_control:IPCAM_PTZ_CMD_UP param:20];//上
            break;
        default:
            break;
    }
}

2.8.2启动预置位设置
1）设置预置位
函数：-(IPCAM_ERROR)set_boot_preset:(id<IPCamSetBootPresetDelegate>)delegate; //设置预置位以及添加代理
回调函数：-(void)on_clear_boot_preset_result:(id)ipcam
error:(IPCAM_ERROR)error;
2）清除预置位置
函数：-(IPCAM_ERROR)clear_boot_preset:(id<IPCamClearBootPresetDelegate>)delegate; //清除预置位以及添加代理

回调函数：-(void)on_set_boot_preset_result:(id)ipcam
error:(IPCAM_ERROR)error;
示列：

- (void)m_button_ptz_position_clear_onclick:(id)sender {
    [m_ipcam clear_boot_preset:self];
}
- (void)m_button_ptz_position_set_onclick:(id)sender {
    [m_ipcam set_boot_preset:self];
}
-(void)on_clear_boot_preset_result:(id)ipcam
error:(IPCAM_ERROR)error;
{
    if ( IPCAM_ERROR_NO_ERROR == error ) {
        [Util show_short_toast:LOCAL_STR(@"CLEAR_BOOT_PRESET_SUCCESS")];
    }
    else
    {
        [Util show_short_toast:LOCAL_STR(@"CLEAR_BOOT_PRESET_FAIL")];
    }
}

-(void)on_set_boot_preset_result:(id)ipcam
error:(IPCAM_ERROR)error
{
    if (IPCAM_ERROR_NO_ERROR == error) {
        [Util show_short_toast:LOCAL_STR(@"SET_BOOT_PRESET_SUCCESS")];
    }
    else
    {
        [Util show_short_toast:LOCAL_STR(@"SET_BOOT_PRESET_FAIL")];
    }
}


2.8.3轨迹设置

1）获取当前轨迹位置
函数：-(IPCAM_ERROR)get_pt_pos:(id<IPCamGetPTPosDelegate>)delegate;／／获取当前轨迹位置

回调函数：-(void)on_get_pt_pos_result:(id)ipcam
error:(IPCAM_ERROR)error
pos:(int32_t)pos;

回调返回参数：回调返回三个参数，如下：
ipcam：id类实际上就是一个IPCam对象
error：错误值
pos：轨迹位置  [最多设置六个轨迹位]
2)设置轨迹位置
函数：-(IPCAM_ERROR)set_track:(NSArray *)nodes_list
delegate:(id<IPCamSetTrackDelegate>)delegate;
参数：nodes_list是一个数组，数组的每一个元素师一个字典，key/value如下：
pos/NSNumber */int32_t  //轨迹位置
ms/NSNumber */int //当前轨迹位置停留时间

回调函数：-(void)on_set_track_result:(id) ipcam
error:(IPCAM_ERROR)error;
回调返回参数：回调返回两个参数，如下：
ipcam：id类实际上就是一个IPCam对象
error：错误值

示列：
- (IBAction)m_button_track_next_position_onclick:(id)sender {
    m_ptz_position_index++;
    if (m_ptz_position_index > 16) {
        return;
    }
    [m_ipcam get_pt_pos:self];//获取当前轨迹位置，添加代理
    
}
/*获取当前轨迹的代理回调*/
-(void)on_get_pt_pos_result:(id)ipcam
error:(IPCAM_ERROR)error
pos:(int32_t)pos;
{
    NSDictionary* dic = [NSDictionary dictionaryWithObjectsAndKeys:
                         [NSString stringWithFormat:@"%d",m_ptz_position_index],@"index",  //第几个位置
                         [NSString stringWithFormat:@"%d",pos],@"pos",                     //当前轨迹位置
                         [NSString stringWithFormat:@"%d",100*m_stay_senconds],@"ms",      //当前轨迹位置停留时间
                         nil];
    [m_arry_position_set addObject:dic];
}
- (IBAction)m_button_track_done_onclick:(UIButton*)sender {
    [m_ipcam set_track:m_arry_position_set delegate:self];    //设置轨迹
}
/*设置轨迹的回调*/
-(void)on_set_track_result:(id)ipca
error:(IPCAM_ERROR)error
{
    if (!error) {
        [Util show_short_toast:LOCAL_STR(@"SET_TRACK_SUCCESS")];
    }
    else
    {
        [Util show_short_toast:LOCAL_STR(@"SET_TRACK_FAIL")];
    }
}

#pragma mark 2.9sensor命令设置参数
2.9sensor命令设置参数
说明：senor命令可以设置亮度（brightness）／对比度（contrast）／锐度（sharpness）／饱和度（saturation），频率(power_frequency),图像翻转（flip），场景设置（white_balance）这些参数，使用这个命令的条件也是要先连接摄像机。

1）用sensor命令获取参数
说明：使用get_sensor_params时添加代理IPCamGetSensorParamsDelegate，一旦有结果，就会回调on_get_sensor_params_result。
函数：-(IPCAM_ERROR)get_sensor_params:(id<IPCamGetSensorParamsDelegate>)delegate;
回调函数：-(void)on_get_sensor_params_result:(id)ipcam
error:(IPCAM_ERROR)error
brightness:(int)brightness
contrast:(int)contrast
sharpness:(int)sharpness
saturation:(int)saturation
power_frequency:(int)power_frequency
white_balance:(int)white_balance
flip:(int)flip;
回调参数：回调参数一共有9个，详情如下：
ipcam：id类型,实际上就是一个IPCam类;
error:IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示获取参数成功。
brightness：亮度，
contrast：对比度，
sharpness：锐度，
saturation：色饱和度，
power_frequency：频率设置，共有三个值。0:60Hz;1:50Hz;3:室外;
white_balance： 场景设置，共有6个值。0:自动;1：白织灯;2:冷光源;3:阳光;4:多云;5:阴天
flip：图像翻转设置，共有4个值。0:正常;1:镜像;2:上下翻转;3:镜像＋上下翻转;
2）用sensor命令设置参数
函数：-(IPCAM_ERROR)sensor_control:(IPCAM_SENSOR_CMD)cmd
param:(int)param;
参数：一共有两个参数，详细如下：
cmd,命令参数，如下：
typedef enum {
    IPCAM_SENSOR_CMD_BRIGHTNESS, //亮度设置
    IPCAM_SENSOR_CMD_CONTRAST, //对比度设置
    IPCAM_SENSOR_CMD_SHARPNESS, //锐度设置
    IPCAM_SENSOR_CMD_SATURATION, //饱和度设置
    IPCAM_SENSOR_CMD_POWER_FREQUENCY,//频率设置
    IPCAM_SENSOR_CMD_WHITE_BALANCE, //频率设置
    IPCAM_SENSOR_CMD_FLIP, //图像翻转设置
} IPCAM_SENSOR_CMD;
param,命令参数值

3）示列：
/*
 *用sensor命令设置参数
 */
[m_ipcam sensor_control:IPCAM_SENSOR_CMD_POWER_FREQUENCY param:2];//设置频率为室外

/*
 *用sensor命令获取参数＋添加IPCamGetSensorParamsDelegate代理
 */
[m_ipcam get_sensor_params:self];

/*
 *IPCamGetSensorParamsDelegate代理回调
 */
-(void)on_get_sensor_params_result:(id)ipcam
error:(IPCAM_ERROR)error
brightness:(int)brightness
contrast:(int)contrast
sharpness:(int)sharpness
saturation:(int)saturation
power_frequency:(int)power_frequency
white_balance:(int)white_balance
flip:(int)flip;
{
    if ( IPCAM_ERROR_NO_ERROR == error) {
        
        NSLog(@"flip =%d",m_flip_value);
        
        NSLog(@"power_frequency =%d",power_frequency);
        
        NSLog(@"white_balance =%d",white_balance);
        
        NSLog(@"saturation =%d",saturation);
        
        NSLog(@"sharpness =%d",sharpness);
        
        NSLog(@"contrast =%d",contrast);
        
        NSLog(@"brightness =%d",brightness);
    }
}

#pragma mark 2.10.CGI命令设置参数

2.10.CGI命令设置参数
说明:CGI命令操作是通过cgi命令设置的一些参数，比如重启，录像，tf的设置，等其它功能。用cgi命令操作前必须确认摄像机是连接成功的。
函数：
-(IPCAM_ERROR)set_params:(NSString *)params
delegate:(id<IPCamSetParamsDelegate>)delegate;
参数：params设置功能的cgi参数。由瑞彩提供，下面提供几种常见的cgi,如下：
1）报警布防："save=1&reinit_alarm=1&arm_schedule=0"  //其中arm_schedule有三个值，0:布防，1:计划布防，2:撤防

2）录像："save=1&reinit_record=1&record_schedule_list=[]" //其中record_schedule_list=[]:停止录像；"save=1&reinit_record=1&record_schedule_list=[{\"start\":0,\"end\":96,\"day\":127}]:开启录像
3）重启:"reboot=1"

回调函数：
-(void)on_set_params_result:(id)ipcam
error:(IPCAM_ERROR)error;
回调参数：回调返回两个参数，详细如下：
ipcam：返回一个id类型，其实就是一个IPCam
error:IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示重置成功

示列：
/*
 *cgi设置参数+添加代理IPCamSetParamsDelegate
 */
NSString * params = @"save=1&reinit_alarm=1&arm_schedule=1"; //计划布防cgi
[m_ipcam set_params:params delegate:self];
/*
 *IPCamSetParamsDelegate代理回调
 */
-(void)on_set_params_result:(id)ipcam
error:(IPCAM_ERROR)error {
    if (error == IPCAM_ERROR_NO_ERROR) {
        NSLog(@"set success!");
    }
    NSLog(@"error = %u",error);
}

#pragma mark 2.11CGI命令获取参数
2.11CGI命令获取参数
说明：参数类的值都可以通过此函数获取当前数值。
函数：-(IPCAM_ERROR)get_params:(NSString *)params
delegate:(id<IPCamGetParamsDelegate>)delegate;
参数：需要去获取的那个参数。比如:图像翻转 "flip="
返回：返回IPCAM_ERROR类型，当返回IPCAM_ERROR_NO_ERROR，则表示函数执行成功。

回调函数：当get_params时，添加了代理IPCamGetParamsDelegate，当有结果时，就会回调此函数。
-(void)on_get_params_result:(id)ipcam
error:(IPCAM_ERROR)error
params:(NSDictionary *)params;
回调参数说明：返回三个参数值，详细如下：
ipcam：返回一个id类型，其实就是一个IPCam
error:IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示获取参数成功
params：一个字典，是get_params的params的key/value


示列：
/*
 *获取参数＋添加代理IPCamGetParamsDelegate
 */
[m_ipcam get_params:@"arm_schedule=" delegate:self]

/*
 *代理IPCamGetParamsDelegate回调
 */

-(void)on_get_params_result:(id)ipcam
error:(IPCAM_ERROR)error
params:(NSDictionary *)params
{
    if (error == IPCAM_ERROR_NO_ERROR) {
        int arm = [[params objectForKey:@"arm_schedule"] intValue];
        if (arm == 2){
            [m_button_disarm setTitleColor:[UIColor redColor] forState:UIControlStateNormal];
        }else if(arm == 0){
            [m_button_arm setTitleColor:[UIColor redColor] forState:UIControlStateNormal];
        }else if(arm == 1){
            [m_button_plan_arm setTitleColor:[UIColor redColor] forState:UIControlStateNormal];
        }
    }
}


#pragma mark 2.11串口通信

2.11串口通信
说明：串口通信，主要包括串口开关功能和串口的读写功能实现。用串口命令操作前必须确认摄像机是连接成功的。
函数：-(IPCAM_ERROR)write_comm:(NSData *)data;

#pragma mark 2.12.RF开关设备操作

2.12.RF开关设备操作
说明：RF开关设备操作，主要包括如何获取开关设备，以及对开关设备进行开关操作
2.12.1获取开关设备
说明：通过以下函数可以获取到rf开关设备，以及设备的相关数据
1）函数
函数：-(IPCAM_ERROR)get_rf_switch_devices:(id<IPCamGetRFSwitchDevicesDelegate>)delegate;//获取设备函数
返回：返回IPCAM_ERROR类型，返回值为IPCAM_ERROR_NO_ERROR则调用成功
2）代理：
代理：-(void)on_get_rf_switch_devices_result:(id)ipcam
error:(IPCAM_ERROR)error
rf_switch_devices_list:(NSArray *)rf_switch_devices_list;//IPCamGetRFSwitchDevicesDelegate代理

返回：回调会返回三个参数

ipcam：Ipcam对象
error：IPCAM_ERROR类型
rf_switch_devices_list：：数组，数组的每一个元素是一个字典，字典的key/value如下：
addr/NSNumber */int   //开关地址
switch/NSNumber */int //设备开关状态 1:开  0:关
link/NSNumber */int
name/NSString *  //设备名称

示列：
[m_ipcam get_rf_switch_devices:self];//获取开关设备，且添加代理 IPCamGetRFSwitchDevicesDelegate

/*
 *获取开关设备有结果后，回调代理
 */
-(void)on_get_rf_switch_devices_result:(id)ipcam
error:(IPCAM_ERROR)error
rf_switch_devices_list:(NSArray *)rf_switch_devices_list
{
    if (error == IPCAM_ERROR_NO_ERROR && rf_switch_devices_list.count > 0)
    {
        NSLog(@"rf_switch_devices_list number = %d",rf_switch_devices_list.count);
        
        NSDictionary * dic = [rf_switch_devices_list objectAtIndex:0];
        NSLog(@"device name = %@",[dic objectForKey:@"name"]);
        NSLog(@"devive status = %d",[dic objectForKey:@"switch"]);
        
    }
    else
    {
        [Util show_short_toast:LOCAL_STR(@“not found RF devices!”)];
    }
}



2.12.2对开关设备进行开关操作
说明：通过一下函数，可以对获取到的开关设备进行开关操作
1)函数：
函数：-(IPCAM_ERROR)switch_rf_device:(int)addr
status:(int)status
delegate:(id<IPCamSwitchRFDeviceDelegate>)delegate; //设置开关设备和添加IPCamSwitchRFDeviceDelegate代理
参数：两个参数，详细如下：
addr：设置的这个开关设备的地址
status：设置的值，1：开 0:关

2）代理

函数：-(void) on_switch_rf_device_result:(id)ipcam
error:(IPCAM_ERROR)error; //IPCamSwitchRFDeviceDelegate代理
返回：回调会返回两个参数，如下：
ipcam：Ipcam对象
error:错误值
示列：

- (void)m_button_switch_onclick:(UIButton*)sender {
    
    NSDictionary * dic = [m_rf_device_list objectAtIndex:sender.tag];
    cell.m_button_rf.selected = !cell.m_button_rf.selected;
    int value;
    if (cell.m_button_rf.selected) {
        value = 1;
    }
    else
    {
        value = 0;
    }
    [m_ipcam switch_rf_device:[[dic objectForKey:@"addr"] intValue] status:value delegate:self]; //设置开关以及添加代理
}

/* 设置开关有结果后的回调*/
-(void) on_switch_rf_device_result:(id)ipcam
error:(IPCAM_ERROR)error{
    if (IPCAM_ERROR_NO_ERROR == error) {
        [Util show_short_toast:LOCAL_STR(@"SET_SUCCESS")];
    }
    else
    {
        [Util show_short_toast:LOCAL_STR(@"SET_FAIL")];
    }
}
#pragma mark 2.13.TF卡相关操作

2.13.TF卡相关操作
说明：TF卡相关操作，主要包括弹出tf卡，格式化tf卡操作，等相关功能的实现。

2.13.1.弹出tf卡
说明：弹出tf卡后，tf讲不在能使用，需要重新插拔才能读取到tf卡。
函数：-(IPCAM_ERROR)unplug_tf:(id<IPCamUnplugTFDelegate>)delegate;
返回：返回IPCAM_ERROR类型，当返回IPCAM_ERROR_NO_ERROR，表示没有测试，调用成功。


回调函数：-(void)on_unplug_tf_result:(id)ipcam
error:(IPCAM_ERROR)error;
回调参数：
ipcam：返回一个id类型，其实就是一个IPCam
error:IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示弹出成功

示列：
/*
 * 弹出tf卡＋添加代理IPCamUnplugTFDelegate
 */
[m_ipcam unplug_tf:self];

/*
 * 代理IPCamUnplugTFDelegate回调
 */

-(void)on_unplug_tf_result:(id)ipcam
error:(IPCAM_ERROR)error {
    if (error == IPCAM_ERROR_NO_ERROR)
        [self show_error:LOCAL_STR(@"EJECT_TF_SUCCESS")];
    else
        [self show_error:LOCAL_STR(@"EJECT_TF_FAIL")];
}

2.13.2.格式化tf卡
说明：格式化tf卡后，
函数：-(IPCAM_ERROR)format_tf:(id<IPCamFormatTFDelegate>)delegate;
返回：返回IPCAM_ERROR类型，当返回IPCAM_ERROR_NO_ERROR，表示没有测试，调用成功。

回调函数：-(void)on_format_tf_result:(id)ipcam
error:(IPCAM_ERROR)error;
回调参数：
ipcam：返回一个id类型，其实就是一个IPCam
error:IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示弹出成功

示列：

/*
 * 格式化tf卡＋添加代理IPCamFormatTFDelegate
 */
[m_ipcam format_tf:self];
/*
 * 代理IPCamFormatTFDelegate回调
 */

-(void)on_format_tf_result:(id)ipcam
error:(IPCAM_ERROR)error {
    if (error == IPCAM_ERROR_NO_ERROR)
        [self show_error:LOCAL_STR(@"FORMAT_SUCCESS")];
    else
        [self show_error:LOCAL_STR(@"FORMAT_TF_FAIL")];
}
2.13.3
-(IPCAM_TF_STATUS)tf_status;
-(int)tf_free;

#pragma mark 2.14.无线网络设置

2.14.无线网络设置
说明：无线网络设置包括，扫描周围wifi和设置摄像机wifi功能。

1）扫描wifi
说明：扫描Wi-Fi，是通过摄像机去扫描周围的wifi,不是通过手机扫描。所以使用wifi_scan前必须先要链接摄像机成功。使用wifi_scan时，如添加了IPCamWifiScanDelegate，一旦扫描有结果了就会调用on_wifi_scan_result。

函数：-(IPCAM_ERROR)wifi_scan:(id<IPCamWifiScanDelegate>)delegate;
返回：返回IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示wifi_scan执行成功。

回调函数：-(void)on_wifi_scan_result:(id)ipcam
error:(IPCAM_ERROR)error
ap_list:(NSArray *)ap_list;
回调参数：回调函数返回三个参数，详细如下：
ipcam：返回一个id类型，其实就是一个IPCam
error:IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示scan成功
ap_list:wifi信息的一个数组，数组的每一个元素是一个字典，key/value如下：
bssid/NSString *  // bssid wifi的唯一标示码
ssid/NSString *   // ssid  wifi名称
rssi/NSNumber */int  //信号强度
/*
 *认证方式有五种，如IPCAM_WIFI_AUTH所示
 */
auth/NSNumber */int/IPCAM_WIFI_AUTH //认证方式
typedef enum {
    IPCAM_WIFI_AUTH_OPEN, //无密码
    IPCAM_WIFI_AUTH_WEP, //WEP
    IPCAM_WIFI_AUTH_WPAPSK, //WPAPSK
    IPCAM_WIFI_AUTH_WPA2PSK, //WPA2PSK
    IPCAM_WIFI_AUTH_UNKNOWN, //unknown
} IPCAM_WIFI_AUTH;
/*
 *加密方式有五种，如IPCAM_WIFI_ENCRYPT所示
 */

encrypt/NSNumber */int/IPCAM_WIFI_ENCRYPT //加密方式
typedef enum {
    IPCAM_WIFI_ENCRYPT_NONE,
    IPCAM_WIFI_ENCRYPT_WEP,
    IPCAM_WIFI_ENCRYPT_TKIP,
    IPCAM_WIFI_ENCRYPT_AES,
    IPCAM_WIFI_ENCRYPT_UNKNOWN,
} IPCAM_WIFI_ENCRYPT;

2）摄像机无线设置
说明：函数1和函数2都可以实现设置无线功能。函数1增加了无线测试功能，但是只有当当前摄像机的是有线连接时（即[m_ipcam wifi_power] == 0,wifi信号是0）时，才可以使用。函数2没有无线测试功能，直接设置。不管摄像机当前是有线连接还是无线连接都可以使用。，推荐方式，摄像机当前是有线连接时，使用函数1设置。摄像机当前是无线连接时，使用函数2设置。
函数1：
-(IPCAM_ERROR)set_wifi:(NSString *)ssid
auth:(IPCAM_WIFI_AUTH)auth
encrypt:(IPCAM_WIFI_ENCRYPT)encrypt
wep_key_index:(int)wep_key_index
wep_key_type:(IPCAM_WIFI_WEP_KEY_TYPE)wep_key_type
key:(NSString *)key
delegate:(id<IPCamSetWifiDelegate>)delegate;
函数2:-(IPCAM_ERROR)set_wifi_without_testing:(NSString *)ssid
auth:(IPCAM_WIFI_AUTH)auth
encrypt:(IPCAM_WIFI_ENCRYPT)encrypt
wep_key_index:(int)wep_key_index
wep_key_type:(IPCAM_WIFI_WEP_KEY_TYPE)wep_key_type
key:(NSString *)key
delegate:(id<IPCamSetWifiDelegate>)delegate;

参数：当认证方式auth是wep时，才要使用wep_key_index，wep_key_type参数，其他加密方式，这两个参数实际上用不着。

ssid:wifi名称，通过扫描返回
key：wifi密码
auth：认证方式，通过扫描返回
encrypt：加密方式，通过扫描返回
/*
 *wep索引，共有四种，［0，3］。瑞彩处理：强制设置为0索引，其他三个索引就不考虑了
 */
wep_key_index：wep索引
/*
 *wep类型，共有两种，HEX和ASCII。瑞彩处理：当auth无密码或auth是wep+key的长度是5或13时，把wep_key_type设置为HEX，其他都是ASCII
 */
wep_key_type：wep类型
typedef enum {
    IPCAM_WIFI_WEP_KEY_TYPE_HEX, //hex类型
    IPCAM_WIFI_WEP_KEY_TYPE_ASCII, //ASCII类型
} IPCAM_WIFI_WEP_KEY_TYPE;

回调函数1：
-(void)on_set_wifi_progress:(id)ipcam
state:(IPCAM_SET_WIFI_STATE)state;

回调返回：返回两个参数，详细如下：
ipcam：返回一个id类型，其实就是一个IPCam
state：设置Wi-Fi的进程，是一个IPCAM_SET_WIFI_STATE类型，详细如下：
typedef enum {
    IPCAM_SET_WIFI_STATE_SETTING, //wifi设置中
    IPCAM_SET_WIFI_STATE_TESTING, //wifi测试中
    IPCAM_SET_WIFI_STATE_SAVING, //wifi保存中
} IPCAM_SET_WIFI_STATE;

回调函数2:
-(void)on_set_wifi_result:(id)ipcam
error:(IPCAM_ERROR)error;
回调返回：
ipcam：返回一个id类型，其实就是一个IPCam
error:IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示设置wifi成功，返回IPCAM_ERROR_DEVICE_OPERATION_FAIL表示密码错误，其他都是设置失败。

3)示列
/*扫描Wi-Fi*/
-(void)scan_wifi {
    /*扫描Wi-Fi+添加代理IPCamWifiScanDelegate*/
    if (IPCAM_ERROR_NO_ERROR != [m_ipcam wifi_scan:self]) {
        [self show_error:LOCAL_STR(@"SCAN_WIFI_FAIL")];
    }
}
/*IPCamWifiScanDelegate回调 */
-(void)on_wifi_scan_result:(id)ipcam
error:(IPCAM_ERROR)error
ap_list:(NSArray *)ap_list
{
    if (IPCAM_ERROR_NO_ERROR == error && ap_list.count >0 ) {
        m_aps_list = ap_list;
        [m_tableview_wifi reloadData];
        
    } else {
        [self show_error:LOCAL_STR(@"SCAN_WIFI_FAIL")];
    }
}

/*设置wifi*/
-(void)set_wifi {
    IPCAM_ERROR error;
    NSString * key;
    IPCAM_WIFI_WEP_KEY_TYPE type;
    IPCAM_WIFI_AUTH auth;
    IPCAM_WIFI_ENCRYPT encrypt;
    
    auth = (IPCAM_WIFI_AUTH)[[m_ap objectForKey:@"auth"] intValue];
    encrypt = (IPCAM_WIFI_ENCRYPT)[[m_ap objectForKey:@"encrypt"] intValue];
    key = [m_view get_input_text];
    
    if (auth == IPCAM_WIFI_AUTH_OPEN) {
        type = IPCAM_WIFI_WEP_KEY_TYPE_ASCII;//无加密方式，type为ASCII
    }
    else {
        if (key.length == 5 || key.length == 13)
            type = IPCAM_WIFI_WEP_KEY_TYPE_ASCII;//有加密方式，且key的长度是5或13时type为ASCII
            else
                type = IPCAM_WIFI_WEP_KEY_TYPE_HEX; //其他加密，type为hex
                }
    if ([m_ipcam wifi_power] == 0) {
        /*当摄像机当前是有线连接，使用set_wifi,且强制设置索引为0*/
        error = [m_ipcam set_wifi:[m_ap objectForKey:@"ssid" ]
                             auth:auth
                          encrypt:encrypt
                    wep_key_index:0
                     wep_key_type:type
                              key:key
                         delegate:self];
    } else {
        /*当摄像机当前是无线连接，使用set_wifi_without_testing，且强制设置索引为0*/
        error = [m_ipcam set_wifi_without_testing:[m_ap objectForKey:@"ssid" ]
                                             auth:auth
                                          encrypt:encrypt
                                    wep_key_index:0
                                     wep_key_type:type
                                              key:key
                                         delegate:self];
    }
    
}
/*IPCamSetWifiDelegate回调*/

-(void)on_set_wifi_progress:(id)ipcam
state:(IPCAM_SET_WIFI_STATE)state
{
    switch (state) {
        case IPCAM_SET_WIFI_STATE_SETTING: //Wifi设置中
            m_state = SETTING_WIFI;
            break;
        case IPCAM_SET_WIFI_STATE_TESTING://wifi测试中
            m_state = TESTING_WIFI;
            break;
        case IPCAM_SET_WIFI_STATE_SAVING://wifi保存中
            m_state = SAVING_WIFI;
            break;
        default:
            break;
    }
    [self show_state];
}

-(void)on_set_wifi_result:(id)ipcam
error:(IPCAM_ERROR)error
{
    if (error == IPCAM_ERROR_NO_ERROR) {
        [self show_error:LOCAL_STR(@"SET_WIFI_SUCCESS")];
    } else if (error == IPCAM_ERROR_DEVICE_OPERATION_FAIL) {
        [self show_error:LOCAL_STR(@"WIFI_KEY_ERROR")];
    } else {
        [self show_error:LOCAL_STR(@"SET_WIFI_FAIL")];
    }
}

#pragma mark 2.15报警类型和报警设备名字获取

2.15报警类型和报警设备名字获取

1）报警状态监控
说明：报警状态监控，情参考［2.2.摄像机基础代理］
函数：-(void)on_camera_alarm_changed:(id)ipcam;

2)获取报名名字
说明：这是外连设备的名字，只有外连设备才使用此函数获取，摄像机本身检测到的报警类型没有此选项。
函数：-(IPCAM_ERROR)get_alarm_name:(id<IPCamGetAlarmNameDelegate>)delegate;

回调函数：-(void)on_get_alarm_name_result:(id)ipcam
error:(IPCAM_ERROR)error
alarm_name:(NSString *)alarm_name;
回调函数说明：当get_alarm_name时添加了代理IPCamGetAlarmNameDelegate，当有结果时，就会掉用回调函数on_get_alarm_name_result。回调函数，共返回三个参数，详细如下：
ipcam：返回一个id类型，其实就是一个IPCam
error:IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示获取名字成功。

2）报警类型获取
说明：通过此函数，可以获取当前报警类型
函数：-(IPCAM_ALARM)alarm;
返回：返回IPCAM_ALARM类型，RF是外连设备的报警，类型状态如下：
typedef enum {
    IPCAM_ALARM_NONE, //无报警
    IPCAM_ALARM_MOTION_DETECT,//移动侦测报警
    IPCAM_ALARM_TRIGGER_DETECT,//红外报警
    IPCAM_ALARM_SOUND_DETECT,//声音侦测报警
    IPCAM_ALARM_TEMPERATURE,//温度报警
    IPCAM_ALARM_HUMIDITY,//湿度报警
    IPCAM_ALARM_RF_EMERGENCY,//RF紧急报警
    IPCAM_ALARM_RF_MAGNETIC,//RF门磁报警
    IPCAM_ALARM_RF_PIR,//PIR报警
    IPCAM_ALARM_RF_SMOKE,//RF延误报警
    IPCAM_ALARM_RF_GAS,//RF天然气报警
    IPCAM_ALARM_RF_LOW_VOLTAGE,//RF低压报警
    IPCAM_ALARM_RF_SHOCK,//RF震动报警
    IPCAM_ALARM_RF_GLASS,//RF玻璃破碎报警
    IPCAM_ALARM_USER_DEFINED,//RF用户自定义报警
    IPCAM_ALARM_UNKNOWN,//未知
} IPCAM_ALARM;

3）报警设备名字获取
说明：只有on_get_alarm_name_result的error返回IPCAM_ERROR_NO_ERROR,执行此函数才有效，且只有rf类型报警的，才有报警设备名字获取。
函数：-(NSString *)alarm_name;
返回：返回一个NSString类型，就是报警设备的名字

4)示列
/*
 *报警状态的监控，添加了IPCamDelegate代理，每当有报警就会回调此函数
 */
-(void)on_camera_alarm_changed:(id)ipcam
{
    [m_tableview_cameras_list reloadData];
    IPCAM_ALARM alarm = [ipcam alarm]; //获取报警类型
    if (alarm == IPCAM_ALARM_NONE)
        ;
    else if (alarm == IPCAM_ALARM_MOTION_DETECT)
        ;
    else if (alarm == IPCAM_ALARM_TRIGGER_DETECT)
        ;
    else if (alarm == IPCAM_ALARM_SOUND_DETECT)
        ;
    else
        [ipcam get_alarm_name:self];//RF设备，可以获取报警的rf设备名字＋添加代理IPCamGetAlarmNameDelegate
}

/*
 *添加了代理IPCamGetAlarmNameDelegate，当get_alarm_name有结果时，就会掉用此函数。
 */

-(void)on_get_alarm_name_result:(id)ipcam
error:(IPCAM_ERROR)error
alarm_name:(NSString *)alarm_name
{
    [m_tableview_cameras_list reloadData];
}

/*
 * 显示报警详细信息，报警类型＋报警名字
 */
-(void)show_camera:(IPCam *)ipcam
camera_id_expanded:(NSString *)camera_id_expanded
{
    
    IPCAM_ALARM alarm = [ipcam alarm];//获取报警类型
    if (alarm == IPCAM_ALARM_NONE) {
        NSlog(@"no alarm!");
        
    } else {
        NSlog(@"alarm!");
        if (alarm == IPCAM_ALARM_MOTION_DETECT)
            NSlog(@"motion!");
        else if (alarm == IPCAM_ALARM_TRIGGER_DETECT)
            NSlog(@"trigger!");
        else if (alarm == IPCAM_ALARM_SOUND_DETECT)
            NSlog(@"sound!");
        else if (alarm == IPCAM_ALARM_RF_EMERGENCY)
            NSlog(@"%@ emegency!",[ipcam alarm_name]);//获取报警名字
        else if (alarm == IPCAM_ALARM_RF_GAS)
            NSlog(@"%@ gas!",[ipcam alarm_name]);//获取报警名字
        else if (alarm == IPCAM_ALARM_RF_LOW_VOLTAGE)
            NSlog(@"%@ low voltage!",[ipcam alarm_name]); //获取报警名字
        else if (alarm == IPCAM_ALARM_RF_MAGNETIC)
            NSlog(@"%@ megnetic!",[ipcam alarm_name]);//获取报警名字
        else if (alarm == IPCAM_ALARM_RF_PIR)
            NSlog(@"%@ pir!",[ipcam alarm_name]);//获取报警名字
        else if (alarm == IPCAM_ALARM_RF_SMOKE)
            NSlog(@"%@ smoke!",[ipcam alarm_name]);//获取报警名字
        else if(alarm == IPCAM_ALARM_RF_GLASS)
            NSlog(@"%@ glass!",[ipcam alarm_name]);//获取报警名字
        else if(alarm == IPCAM_ALARM_RF_SHOCK)
            NSlog(@"%@ shock!",[ipcam alarm_name]);//获取报警名字
        else if (alarm == IPCAM_ALARM_USER_DEFINED)
            NSlog(@"%@ user define!",[ipcam alarm_name]);//获取报警名字
                                                        }
}


#pragma mark - 新添加接口/功能

/**
 获取参数字典

 @return 参数字典
 */
//  key/value
//  brightness/NSNumber */bool/can set brightness
//  brightness_min/NSNumber */int
//  brightness_max/NSNumber */int
//  brightness_default/NSNumber */int
//  contrast/NSNumber */bool
//  contrast_min/NSNumber */int
//  contrast_max/NSNumber */int
//  contrast_default/NSNumber */int
//  hue/NSNumber */bool
//  hue_min/NSNumber */int
//  hue_max/NSNumber */int
//  hue_default/NSNumber */int
//  saturation/NSNumber */bool
//  saturation_min/NSNumber */int
//  saturation_max/NSNumber */int
//  saturation_default/NSNumber */int
//  sharpness/NSNumber */bool
//  sharpness_min/NSNumber */int
//  sharpness_max/NSNumber */int
//  sharpness_default/NSNumber */int
//  powerfreq/NSNumber */bool
//  powerfreq_min/NSNumber */int
//  powerfreq_max/NSNumber */int
//  powerfreq_default/NSNumber */int
//  ev/NSNumber */bool
//  ev_min/NSNumber */int
//  ev_max/NSNumber */int
//  ev_default/NSNumber */int
//  scene/NSNumber */bool
//  scene_min/NSNumber */int
//  scene_max/NSNumber */int
//  scene_default/NSNumber */int
//  flip/NSNumber */bool
//  flip_min/NSNumber */int
//  flip_max/NSNumber */int
//  flip_default/NSNumber */int
-(NSDictionary *)get_sensor_capability;

/**
 获取参数数组
 
 @return 参数数组
 */
//  every element of NSArray returned is type of NSDictionary
//  key/value
//  stream/NSNumber */int;
//  codec/NSNumber */int;
//  resolution/NSNumber */int
-(NSArray *)get_video_streams_info;





