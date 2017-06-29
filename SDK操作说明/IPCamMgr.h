//
//  IPCamMgr.h
//  SoDemon
//
//  Created by feng on 16/3/15.
//  Copyright © 2016年 feng. All rights reserved.
//


IPCamMgr
使用此SDK必须要要使用IPCamMgr类，IPCamMgr类用于批量管理cam

#pragma mark 1.1SDK初始化和反初始化
1.1SDK初始化和反初始化
说明：使用此sdk必须先初始化，才能使用其他函数，不在使用此sdk时也必须要反初始化。
函数：下面两个四个函数，是两两成对出现，有初始化必须要有反初始化  有开始连接必须有停止连接
+(IPCamMgr *)get_share;//创建IPCamMgr 初始化

+(void)release_share;//释放IPCamMgr，反初始化

-(void)start;//批量管理cams 开始连接cams

-(void)stop; //批量管理cams 停止连接cams

示列：
[[IPCamMgr get_share] start]; //开始使用此SDK时  先初始化SDK+开始连接cams,如果不需要连接，可以先不连接，直接初始化[IPCamMgr get_share]
[[IPCamMgr get_share] stop]; //不需要连接时 停止连接cams
[IPCamMgr release_share]; //不在使用此SDK时 反初始化SDK

#pragma mark 1.2局域网搜索
1.2局域网搜索
说明：只要创建了PCamMgr,程序就一直在后台搜素局域网类的cams
/*
 *返回一个数组，数组的每一个元素是一个字典，key/value如下：
 *camera_id/NSString *   //摄像机id
 *id_type/NSNumber * (int32_t) //摄像机id_type
 *alias/NSString *    //名称
 *fw_version/NSString *  //系统固件版本
 *ui_version/NSString *  //网页固件版本
 *model/NSNumber *(int32_t)  //模式,两个值,
 *dhcp/NSNumber *(BOOL)
 *ip/NSString * //IP地址
 *mask/NSString *
 *gateway/NSString *
 *dns1/NSString *
 *dns2/NSString *
 *current_ip/NSString *
 *current_mask/NSString *
 *port/NSNumber *(int)    //端口号
 *https/NSNumber *(BOOL)  //是否安全加密传输，Yes:安全加密  No:非安全加密
 *used/NSNumber *(BOOL)   //是否被添加，两个值，Yes:被添加  No:未被添加
*/
函数：-(NSArray *)get_discovered_cameras_list;//获取局域网里的cams

示列：
NSArray * cameras_list = [[IPCamMgr get_share] get_discovered_cameras_list];
IPCam *cam = [cameras_list objectAtIndex:0];

#pragma mark 1.4获取IPCamMgr类的cams

1.4获取IPCamMgr类的cams
1）获取IPCamMgr类的cams
说明：获取被添加到IPCamMgr的所有cams，通过函数返回一个数组，数组里的每一个元素是一个IPCam *
函数：-(NSArray *)get_cameras_list;
示列：
NSArray *m_ipcams_list = [[IPCamMgr get_share] get_cameras_list];
IPCam * ipcam = [m_ipcams_list objectAtIndex:0];

2）IPCamMgr类通过id获取cam
说明：
函数：-(IPCam *)get_camera:(NSString *)camera_id;//通过摄像机id获取IPCam*对象
示列：
IPCam * ipcam = [[IPCamMgr get_share] get_camera:@"RTEST-001566-ZSIOH"];

#pragma mark 1.5IPCamMgr的cam添加和删除以及相关代理

1.5IPCamMgr的cam添加和删除

1.5.1添加和删除代理和协议
说明：添加代理IPCamMgrDelegate，当IPCamMgr里的cam有变动时，就会回调
函数：
两个函数：-(void)add_delegate:(id<IPCamMgrDelegate>)delegate;//添加IPCamMgrDelegate

-(void)remove_delegate:(id<IPCamMgrDelegate>)delegate;//删除IPCamMgrDelegate

三个代理：-(void)on_camera_added:(NSString *)camera_id;//添加IPCamMgr的cam的回调，且返回camera_id

-(void)on_camera_removed:(NSString *)camera_id;//删除IPCamMgr的cam的回调，且返回camera_id

-(void)on_cameras_cleared;//清空IPCamMgr所有的cams的回调

示列：
[[IPCamMgr get_share] add_delegate:self];//先添加代理
//代理响应
-(void)on_camera_added:(NSString *)camera_id
｛
NSLog(@"camrea:%@ already add to IPCamMgr",camera_id);
｝
-(void)on_camera_removed:(NSString *)camera_id
｛
NSLog(@"camrea:%@ already removed from IPCamMgr",camera_id);
｝
-(void)on_cameras_cleared
｛
NSLog(@"all camreas already removed from IPCamMgr");
｝
[[IPCamMgr get_share] remove_delegate:self];//不需时 删除代理

1.5.2添加
说明：如果想要批量管理cam，添加摄像机到本地后，必须要添加摄像机到IPCamMgr，添加完以后返回一个IPCam *
函数：-(IPCam *)add_camera:(NSString *)camera_id
alias:(NSString *)alias
user:(NSString *)user
pwd:(NSString *)pwd
https:(BOOL)https;//添加摄像机到IPCamMgr*
示列：
NSArray * cameras_list = [[IPCamMgr get_share] get_discovered_cameras_list];
NSDictionary * m_camera = [cameras_list objectAtIndex:0];
[[Storage get_share] add_camera:[m_camera objectForKey:@"camera_id"]
                          alias:@"sandy"
                           user:@"admin"
                            pwd:[m_ipcam pwd]
                          https:[m_ipcam https]
                     sosocam_id:sosocam_camera_id
                          model:[m_ipcam model]
                         master:NO];//添加摄像机到本地
IPCam * ipcam = [[IPCamMgr get_share] add_camera:[m_camera objectForKey:@"camera_id"]
                                           alias:@"sandy"
                                            user:@"admin"
                                             pwd:[m_ipcam pwd]
                                           https:[m_ipcam https]];//添加摄像机到IPCamMgr
1.5.3删除IPCamMgr类的cam

1）删除IPCamMgr类里指定的cam
说明：这个函数一般删除本地摄像机后，需要从IPCamMgr类里删除
函数：-(IPCam *)remove_camera:(NSString *)camera_id;//删除IPCamMgr类里camera_id摄像机
示列：
[[Storage get_share] remove_camera:@"RTEST-001566-ZSIOH"];//从本地删除:@"RTEST-001566-ZSIOH"
[[IPCamMgr get_share] remove_camera:@"RTEST-001566-ZSIOH"];//从IPCamMgr删除:@"RTEST-001566-ZSIOH"
2）删除IPCamMgr里的所有cams
 说明：当不需要在对cams做管理的时（如账号切换的时候），需要删除IPCamMgr里的所有cams
 函数：-(void)clear_cameras_list;
 示列：
 [[IPCamMgr get_share] clear_cameras_list];


#pragma mark 1.6更新cam的密码到IPCamMgr
1.6更新cam的密码到IPCamMgr / 更新用户名到IPCamMgr
  说明：一般摄像机密码做了修改，需要保存到本地，同时保存到IPCamMgr类
  函数：-(void)update_camera_pwd:(NSString *)camera_id
                            pwd:(NSString *)pwd;
        -(void)update_camera_user:(NSString *)camera_id
                             user:(NSString *)user;

  示列:
  [m_ipcam reset_pwd:pwd1 delegate:self]//修改密码
  [[Storage get_share] update_camera_pwd:[m_ipcam camera_id] pwd:[m_view get_input_text]];//更新密码到本地
  [[IPCamMgr get_share] update_camera_pwd:[m_ipcam camera_id] pwd:[m_view get_input_text]];//更新密码到IPCamMgr

#pragma mark 1.8立即连接

1.8立即连接
说明：立即连接是指手动断开cam然后重新连接，用这个函数摄像机必须是添加到了IPCamMgr类，
函数：-(void)reset_camera:(NSString *)camera_id;
示列：
[[IPCamMgr get_share]reset_camera:@"RTEST-001566-ZSIOH"];

#pragma mark 1.10一次性摄像机管理


1.10一次性摄像机管理
说明：一次性管理摄像机，主要用于收藏的摄像机管理，一次性摄像机数量小于等于1
函数：-(IPCam *)get_disposable_camera;//获取一次性摄像机

-(BOOL)set_disposable_camera:(NSString *)camera_id
user:(NSString *)user
pwd:(NSString *)pwd
https:(BOOL)https;//设定一次性摄像机

-(void)clear_disposable_camera;//清除一次性摄像机

-(BOOL)update_disposable_camera_pwd:(NSString *)pwd;//更新一次性摄像机密码到IPCamMgr

-(BOOL)reset_disposable_camera;//重连一次性摄像机
示列：
[[IPCamMgr get_share] set_disposable_camera:camera_id user:m_user pwd:m_pwd https:https];
IPCam * m_ipcam = [[IPCamMgr get_share] get_disposable_camera];
[[IPCamMgr get_share] update_disposable_camera_pwd:m_pwd];
[[IPCamMgr get_share] reset_disposable_camera]
[[IPCamMgr get_share] clear_disposable_camera];

#pragma mark  1.9数据(moblie)联网下的连接设置

  1.9数据(moblie)联网下的连接设置
  说明：把forbidden_in_mobile参数设置到本地后，必须要设置到IPCamMgr才生效.针对所有摄像机，缺省值是数据流量下允许连接。
  函数：-(void)set_forbidden_in_mobile:(BOOL)forbidden_in_mobile;
  示列：
  [[Storage get_share]set_forbidden_with_mobile:[[Storage get_share]get_forbidden_with_mobile]];//从本地获取get_forbidden_with_mobile值（默认值为NO）设置到本地
  BOOL  m_forbidden_mobile = [[Storage get_share] get_forbidden_with_mobile];//从本地获取到m_forbidden_mobile值
  [[IPCamMgr get_share]set_forbidden_in_mobile:m_forbidden_mobile];//把m_forbidden_mobile设置到IPCamMgr生效

#pragma mark   1.10 获取到当前网络类型
  1.10 获取到当前网络类型
  说明：获取到当前网络类型，返回网络类型
  IPCAMMGR_NETWORK_DOWN //无网络
  IPCAMMGR_NETWORK_WIFI //WIFI网络
  IPCAMMGR_NETWORK_MOBILE //数据流量
  
  函数：-(IPCAMMGR_NETWORK_TYPE)get_network_type;
  示列：
  IPCAMMGR_NETWORK_TYPE * NetworkType = [[IPCamMgr get_share]get_network_type];
 

 
