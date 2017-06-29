



－－－－－－－－－－－－－－－－－－－－－－－－－－－
#pragma mark 1.libSoSoCamSDK简介

1.libSoSoCamSDK简介

libSoSoCamSDK由7个部分组成，整个libSoSoCamSDK的使用思路是：
集成libSoSoCamSDK－－－》初始化SDK －－－》添加摄像机 －－－》连接摄像机 －－－》操作摄像机的各种功能。SDK各个部分
的功能以及之间的联系,如下：

IPCamMgr：IPCamMgr是使用libSoSoCamSDK必须要使用到的一部分，用于批量管理cam。主要包括SDK初始化／反初始化，局域网搜索，摄像机批量连接管理功能。在使用其他功能之前，必须先通过IPCamMgr的get_share初始化成功后，才能去使用呢，另外不管你使用哪一种连接方式都要使用IPCamMgr的局域网搜索功能，所以IPCamMgr是非常核心的部分。同时IPCamMgr多处使用了Util的方法和IPCam的方法。

IPCam:IPCam也是libSoSoCamSDK中操作摄像机的核心部分。一般用于摄像机连接后，实现摄像机的各种功能以及监控摄像机的各种状态。比如摄像机视频／音频／对讲／录像／拍照／云台操作／tf卡功能实现，也可监控摄像机连接状态／报警状态／tf卡状态等等。当然它也用于创建IPCam对象和实现cam的连接。

IPCamVideoView:IPCamVideoView是观看视频必需要用到的一个类。IPCamVideoView其实就是一个UIView,需要结合IPCam才能实现观看视频功能，另外IPCamVideoView还实现了一个协议，可以自定义实现在视频上单点和上下左右滑动操作功能。

Storage:Storage用于本地存储的，主要有存储用户／摄像机／收藏摄像机／录像和照片／报警图片信息。你可以不适用这个Storage自己实现存储，你也可以直接用我们的存储接口，值得注意的是，如果使用我们的接口且你不需要登录功能，你必需创建一个账号，否则存储不了［因为我们的存储路径是以账号开头的］。

WebService:WebService是在需要用到平台的时候用到。一般都是需要登录功能时用到，用来管理从服务器获取用户信息／用户中添加的摄像机信息／用户中收藏分享的摄像机／用户添加摄像机的报警信息。当然WebService中还有升级系统固件和app版本的功能，这个不需要登录就可以使用。

Util:Util是用的比较多的一些处理方法，比如字符串的处理。这些功能在libSoSoCamSDK中多个类中有用到，你也可以直接在你的项目里调用。

WiFiMatching:WiFiMatching是实现SmartLink设置无线功能用的。主要是开始／停止SmartLink设置以及SmartLink设置成功的协议代理。

SoundWaveWifiSetting:SoundWaveWifiSetting是实现声音设置无线功能用的。主要是开始／停止声音设置记忆声音设置过程中各个状态的监控。

－－－－－－－－－－－－－－－－－－－－－
#pragma mark 2.集成libSoSoCamSDK

2.集成libSoSoCamSDK

1)说明：集成libSoSoCamSDK是指把libSoSoCamSDK集成到你的项目中，供你使用。libSoSoCamSDK是真机版本，不包括模拟器版本，所以调试运行的时候需要在真机上调试

2）版本支持：
arm64 armv7 armv7s以及IOS7.0 以上

3）组成:
头文件：IPCamMgr.h;IPCam.h;IPCamVideoView.h;
         Storage.h;WebService.h;Util.h;
         WiFiMatching.h;SoundWaveWifiSetting.h
静态文件：libSoSoCamSDK.a
资源文件：SoSoCamSDKBundle

4)框架
基本框架（必须要添加的框架）
libc++.tdb
AudioToolbox.framework
AVFoundation.framework
CoreMedia.framework
MediaPlayer.framework
SystemConfiguration.framework
coreFoundation.framework
可选框架（用到的时候添加,这里罗列了一部分，其他Libraries根据报错提示添加）
AddressBookUI.framework
AddressBook.framework
CoreVideo.framework
libicucore.dylib
libiconv.dylib
JavaScriptCore.framework
libz.dylib
MOBFoundation.framework
5)步骤：
第一步：导入API开发包到应用程序项目。在XCode中选择“Add files to “Your project name”...”，将解压的libSoSoCamSDK文件夹（包含Include,lib,SoSoCamSDKBundle）添加到你的工程目录中。

第二步：添加必要的框架。在"Project target" ---> "Build Phases" ---> "Link Binary Libraries" ---->选择"+"添加必要的框架。

第三步：在"Project target"--->"General" --->"Deployment Target"设置为7.0+

第四步：在"Project target"--->"Build Settings"--->"Architectures"设置为"Standard(arm64 armv7)"
第五步：在"Project target"--->"Build Settings"--->"Valid Architectures"--->添加"arm64 armv7 armv7s"


第六步：更改Build。如果你使用Xcode7以上版本编译，请在项目中选择择"TARGET" ---> "Build Settings" --->"bitCode"设置为NO,否则将无法正常编译通过。

第七步：编译。如果能编译通过就算成成功了。


#pragma mark 3.SDK初始化
3.SDK初始化
1)说明：SDK初始化是指：使用libSoSoCamSDK之前必须初始化SDK，初始化完成之后，才能使用libSoSoCamSDK。

2)注意：a)SDK初始化使用的是单列模式;
    b)为提高程序性能，一般在程序开启（即AppDelegate的didFinishLaunchingWithOptions里）时，就开始初始化SDK;
    c)为提高程序性能，一般在程序（即AppDelegate的applicationWillTerminate里）退出时，反初始化SDK;

3)使用的类：IPCamMgr

4)函数：
/*
 *初始化SDK
 */
+(IPCamMgr *)get_share;//创建IPCamMgr 初始化

/*
 *反初始SDK
 */
+(void)release_share;//释放IPCamMgr，反初始化

5)示例：
/*使用SDK之前初始化SDK*/
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    [IPCamMgr get_share]; //初始化
    return YES;
}

/*程序退出反初始化SDK*/
- (void)applicationWillTerminate:(UIApplication *)application {
    [IPCamMgr release_share]; //反初始化
}

#pragma mark 4.局域网搜索

4.局域网搜索

1）说明：局域网搜索是指：搜索和手机在同一个网络里的摄像机，并获获取到这些摄像机。只要创建且开始了PCamMgr，程序就会一直在后台搜索局域网内的摄像机，且不断更新搜索到的摄像机。直到停止PCamMgr。

2）使用的类：PCamMgr

3）注意：只有满足以下条件的摄像机才可以搜索到：
        a)系统固件版本为：@"x.x.x.4.x"
        b)书写了设备id,且id前缀为@"RTEST-",@"SOSO-",@"RCAM-",@"LSCAM-",@"YSTC-"
        c)获取到了局域网IP且局域网IP不为@"0.0.0.0"或@"169.78.32.56"
        d)摄像机为路由器模式[摄像机为点对点模式时搜不到]
        e）如果start之后，你立即去get_discovered_cameras_list，需要通过异步延时来get_discovered_cameras_list，否则获取不到摄像机，因为PCamMgr的start需要时间搜索（不能是同步，同步程序是暂停运行还是搜索不到）。
        f)为提高性能，一般程序一开始（即AppDelegate）就开始start局域网搜索和连接。需要获取局域网时再直接get_discovered_cameras_list。但如果此时get_discovered_cameras_list放在rootview的加载显示时，还是要异步，因为时间太短，只有几十ms。
        g)ios不允许程序后台运行，所以每次当程序挂起applicationWillResignActive时，都要stop掉IPCamMgr的连接和局域网搜索。每次到程序复原applicationDidBecomeActive的时候都要重新start IPCamMgr的连接和局域网搜索。
/*
 *获取局域网摄像机
 *返回参数：
 *返回一个数组，数组的每一个元素是一个字典，key/value如下：
 *camera_id/NSString *   //摄像机id
 *d_type/NSNumber * (int32_t) //摄像机id_type
 *alias/NSString *    //名称
 *fw_version/NSString *  //系统固件版本
 *ui_version/NSString *  //网页固件版本
 *model/NSNumber *(int32_t)  //这个值没有特定的意义，你可以自己定义，但是如果你不去设置的话  它默认一直是0。
  我们是定义0为云台机，1为卡片机
 *dhcp/NSNumber *(BOOL)//是否开启dhcp
 *ip/NSString * //网络配置的ip,主要用于网络配置实用，若开启dhcp,那么ip和current_ip是不相等的，如果不开启，固定ip,ip和current_ip相等
 *mask/NSString *
 *gateway/NSString *
 *dns1/NSString *
 *dns2/NSString *
 *current_ip/NSString * //摄像机当前实用的ip
 *current_mask/NSString *  //摄像机当前子网
 *port/NSNumber *(int)    //端口号
 *https/NSNumber *(BOOL)  //是否安全加密传输，Yes:安全加密  No:非安全加密
 *used/NSNumber *(BOOL)   //是否被添加，两个值，Yes:被添加  No:未被添加。
 */
-(NSArray *)get_discovered_cameras_list;//获取局域网里的cams

/*
 *开始局域网搜索，开始批量摄像机连接
 */
-(void)start;
/*
 *停止局域网搜索，批量停止摄像机连接
 */
-(void)stop;


5）步骤：
第一步：用IPCamMgr的init和start函数进行sdk初始化开始IPCamMgr;

第二步：用IPCamMgr的get_discovered_cameras_list获取局域网的摄像机;

6）示例：
/*
 *第一步：初始化开始IPCamMgr 开始后台局域网搜索
 */
IPCamMgr * ipCamMgr = [IPCamMgr get_share]start];

/*
 *第二步：获取局域网摄像机
 */
dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^(void) {
    NSArray * array = [[IPCamMgr get_share]get_discovered_cameras_list];
}); //start后立即get_discovered_cameras_list需要异步延时

NSArray * cameras_list = [ ipCamMgr get_discovered_cameras_list];//start隔了一段时间（足够程序搜索完毕，一般超过5s上就可）get_discovered_cameras_list，直接获取即可


#pragma mark 5.摄像机的添加／删除／修改更新

5.摄像机的添加／删除／修改更新
说明：摄像机的添加／删除／修改更新有三个部分，服务器的，本地的和IPCamMgr的，流程如下：
添加：WebService添加／删除／修改更新－－－》Storage添加／删除／修改修改更新－－－》IPCamMgr添加／删除／修改更新。
这些过程按照你的需求，择选，详细如下：
如果用到服务器平台管理摄像机，那么需要在WebService添加／删除／修改更新[可选项];
如果用到本地管理摄像机，那么需要在Storage添加／删除／修改更新;
如果用到批量管理摄像机或使用IPCamMgr连接摄像机，那么需要在IPCamMgr添加／删除／修改更新。［推荐使用IPCamMgr管理];
#pragma mark－－5.1摄像机的添加<服务器／本地／IPCamMgr>
5.1摄像机的添加
1）说明：摄像机的添加是是指添加摄像机到服务器／本地／IPCamMgr，添加成功后，这样子你才可以对它操作，监控它的状态等。

2）使用的类：WebService，IPCam，Storage,IPCamMgr

3）函数：

/*
 *Storage类
 *Storage的帐号创建和更新
 *详细用法参考<Storage的本地存储用户管理更新>
 */
-(void)update_user:(NSString *)user_id
login_type:(int)login_type
auth_name:(NSString *)auth_name
auth_pwd:(NSString *)auth_pwd
alias:(NSString *)alias;

/*
 *Storage类
 *Storage的设置当前帐号
 *详细用法参考<Storage的本地存储用户管理更新>
 */
-(void)set_current_user:(NSString *)user_id; //设置user_id为当前账号

/*
 *WebService添加摄像机到服务器
 *参数：
 *camera_id：摄像机id
 *alias:摄像机昵称
 *https:安全加密传输，两个值：YES:加密 NO:非加密
 *model：这个值没有特定的意义，你可以自己定义，但是如果你不去设置的话  它默认一直是0。我们是定义0云台机  1为卡片机  
 *delegate:添加摄像机的代理，可以监控到添加摄像机到服务器的结果
 *返回：
 *当WEBSERVICE_ERROR == WEBSERVICE_ERROR_NO_ERROR时表示添加执行成功
 */
-(WEBSERVICE_ERROR)add_camera:(NSString *)camera_id
alias:(NSString *)alias
https:(BOOL)https
model:(int32_t)model
delegate:(id<WebServiceAddCameraDelegate>)delegate;

/*
 *Storage添加摄像机到本地
 *camera_id:摄像机id
 *alias:摄像机昵称
 *user:摄像机登录用户名
 *pwd:摄像机登录密码
 *https:加密安全传输，两个值 0:非加密 1:加密
 *sosocam_id:摄像机sosocam_id
 *model:这个值没有特定的意义，你可以自己定义，但是如果你不去设置的话  它默认一直是0。我们是定义0云台机  1为卡片机
 *master: 主摄像机，BOOL值，YES:主摄像机，NO:非主摄像机
 */
-(void)add_camera:(NSString *)camera_id
alias:(NSString *)alias
user:(NSString *)user
pwd:(NSString *)pwd
https:(BOOL)https
sosocam_id:(NSString *)sosocam_id
model:(int32_t)model
master:(BOOL)master;

/*
 *IPCamMgr添加摄像机到IPCamMgr
 *参数：
 *camera_id：摄像机id
 *alias:摄像机昵称
 *user:摄像机登录用户名
 *pwd:摄像机登录密码
 *https:安全加密传输，两个值：YES:加密 NO:非加密
 *另外IPCamMgr添加有个添加代理IPCamMgrDelegate，添加后可以监控添加结果
 */
-(IPCam *)add_camera:(NSString *)camera_id
alias:(NSString *)alias
user:(NSString *)user
pwd:(NSString *)pwd
https:(BOOL)https;

/*
 *IPCam方法：更新摄像机局域网信息
 *参数如下：
 *in_lan：BOOL值，是否使用局域网连接。YES:使用局域网直连；NO:使用p2p连接；缺省为NO
 *ip：局域网（in_lan设置为YES):当前摄像机ip；p2p（in_lan设置为NO）:可以不用设置
 *port：局域网（in_lan设置为YES）:当前摄像机port；p2p（in_lan设置为NO）:可以不用设置
 *https：BOOL值，当前摄像机是否加密传输.YES:加密传输。NO:不加密传输。
 */
-(void)update_lan_status:(BOOL)in_lan
ip:(NSString *)ip
port:(int)port
https:(BOOL)https

/*
 *IPCam方法：连接摄像机
 *摄像机的id、pwd、user、https参数都设置好了以后,就可以开始连接了
 *参数如下：
 *retryable:是否重连,YES:当因为网络错误时会自动重连接； NO:不重连
 *retry_delay:int类型，单位ms,延迟多长时间重连。
 */
-(IPCAM_ERROR)start_connect:(BOOL)retryable
retry_delay:(int)retry_delay;


4）步骤：

第一步：使用Storage里的方法创建更新一个帐号，且设置当前帐号。只要你用到Storage的方法来存储，不管你是否需要帐号登陆，都必须进行这一步。

第二步：使用IPCam中的方法更新局域网信息，连接摄像机，添加摄像机代理。<如果你不需要执行下面第四第五步骤，此步骤可以省略，详细参考摄像机连接：通过IPCam摄像机的连接>

第三步：用WebService的方法添加到服务器上，如果不需用用到服务器平台这一步省略。<这一步骤可以添加WebServiceAddCameraDelegate代理监控添加结果，详情参考：IPCamMgr的服务器上添加摄像机>

第四步：用WebService的方法添加到服务器上,如果监控到摄像机已经被注册，先解绑在继续添加。<如果你需要推送功能，且是通过以账号为id来settag实现的，就必须进行这一步。如果不需要这一步可不实现>

第五步：用WebService的方法添加到服务器上,监控添加成功后，需要relogin一下摄像机，使摄像机登陆服务器平台。<如果你需要推送功能，且是通过以账号为id来settag实现的，就必须进行这一步。如果不需要这一步可不实现>

第六步：用Storage的方法把摄像机添加到本地。

第七步：用IPCamMgr的方法添加摄像机到IPCamMgr。<这一步骤可以添加IPCamMgrDelegate代理，监控添加，详情草考：IPCamMgr的cam添加和删除>

5)注意：1）用Storage的方法add_camera把摄像机添加到本地来存储，使用之前，不管你是否需要帐号登陆，都必须创建一个帐号且设置一个当前帐号。<因为本地存储路径是以帐号为路径的，如果没有创建路径，存储地址就是无效的>
       2）update_user是为了创建路径，创建有效的存储地址。set_current_user是为了指定后面取本地文件的路径，这两个要是同一个账号，且必须实现的两步。
       3）如果只要添加到本地，直接使用第一，第六，第七步骤即可。
       4）摄像机unregister_from_sosocam和relogin_to_sosocam的操作必须是在摄像机连接成功的状态下进行，所以如果要进行这些操作，必须先连接摄像机。
       5）摄像机的一次性连接使用update_lan_status和start_connect可实现，具体可参考摄像机连接之通过IPCam摄像机的连接
       6）监控摄像机的连接状态必须添加代理IPCamDelegate，但是使用完必须remove。IPCamDelegate的具体使用参考IPCam的基础代理
       7) 目前瑞彩的服务器的规则是一个摄像机只能被一个账号添加，所以被添加了必须unregister_from_sosocam。
       8）只有relogin_to_sosocam成功了，摄像机才能像服务器上传报警图片以及实现推送功能。

6）示列：
/*第一步：创建更新一个帐号，且设置当前帐号*/
[[Storage get_share] update_user:@"local@localhost" login_type:OFFLINE_USER auth_name:@"" auth_pwd:@"" alias:@""];
[[Storage get_share] set_current_user:@"local@localhost"];

/*第二步：更新局域网信息，连接摄像机*/
-(void)update_lan_camemera:(NSString*)camera_id{
    NSDictionary*camera = [[NSDictionary alloc]init];
    NSArray *m_camera_list = [[IPCamMgr get_share]get_discovered_cameras_list]; //局域网中的所有摄像机
    for (int i = 0; i < m_camera_list.count; i++) {
        camera  = [m_camera_list objectAtIndex:i];
        if ([[camera objectForKey:@"camera_id"] isEqualToString:camera_id]) {
            /*如果id在局域网内就更新局域网信息*/
            [m_ipcam update_lan_status:YES ip:[camera objectForKey:@"current_ip"] port:[[camera objectForKey:@"port"] intValue] https:[[camera objectForKey:@"https"] boolValue]];
        }
    }
}

- (void)start_connect_camera {
    
    [self update_lan_camemera:camera_id];
    /*连接摄像机
     *如果上一步有更新局域网信息，此刻就是局域网连接，否则是p2p连接
     */
    if (IPCAM_ERROR_NO_ERROR == [m_ipcam start_connect:NO retry_delay:0]) {
        [m_ipcam add_delegate:self]; //监控摄像机的连接状态，详细参考摄像机的基础代理IPCamDelegate
    }
}

/*第三步：监控摄像机连接成功后，开始添加摄像机到服务器*/
//IPCamDelegate
-(void)on_status_changed:(id)ipcam{
    
    IPCAM_STATUS m_status = [m_ipcam status];
    if (m_status == IPCAM_STATUS_CONNECTED){
        /*连接摄像机成功，开始添加到服务器*/
        [self add_camera_to_server];
    }
    else if (m_status == IPCAM_STATUS_IDLE){
        /*连接摄像机失败，删除摄像机代理*/
        [m_ipcam remove_delegate:self];
    }
    else{
    }
}
-(void)add_camera_to_server
{
    //添加到IPCamMgr
    if (WEBSERVICE_ERROR_NO_ERROR != [[WebService get_share] add_camera:[m_camera objectForKey:@"camera_id"]alias:m_camera_name
                                                                  https:[m_ipcam https]
                                                                  model:[m_ipcam model]
                                                               delegate:self]) {
        /*添加失败*/
    }
}
//WebServiceAddCameraDelegate
-(void)on_add_camera_result:(WEBSERVICE_ERROR)error
sosocam_camera_id:(NSString *)sosocam_camera_id{
    if (WEBSERVICE_ERROR_NO_ERROR == error) {
        /*监控到添加添加摄像机到服务器成功*/
        [m_ipcam relogin_to_sosocam:self]; //第五步：重新登陆服务器
        [[Storage get_share] add_camera:[m_camera objectForKey:@"camera_id"]
                                  alias:m_camera_name
                                   user:@"admin"
                                    pwd:[m_ipcam pwd]
                                  https:[m_ipcam https]
                             sosocam_id:sosocam_camera_id
                                  model:[m_ipcam model]
                                 master:NO];//第六步：添加到本地
        IPCam * ipcam = [[IPCamMgr get_share] add_camera:[m_camera objectForKey:@"camera_id"]
                                                   alias:m_camera_name
                                                    user:@"admin"
                                                     pwd:[m_ipcam pwd]
                                                   https:[m_ipcam https]];//第七步：添加到IPCamMgr
    } else if (WEBSERVICE_ERROR_REGISTERED_BY_OTHERS == error) {
        [m_ipcam unregister_from_sosocam:self];//第四步：摄像机已被其他账号添加，先解绑
    } else {
        /*添加摄像机到服务器失败，删除摄像机代理*/
        [m_ipcam remove_delegate:self];
    }
}

//IPCamUnregisterFromSoSoCamDelegate
-(void)on_unregister_from_sosocam_result:(id)ipcam
error:(IPCAM_ERROR)error{
    if (error == IPCAM_ERROR_NO_ERROR) {
        [self add_camera_to_server];//第四步：解绑成功，重新添加摄像机到服务器
    } else {
        [m_ipcam remove_delegate:self];//解绑失败，需要删除摄像机代理
    }
}
#pragma mark－－5.2摄像机的删除<服务器／本地／IPCamMgr>
5.2摄像机的删除
1）说明：摄像机的是指从服务器／本地／IPCamMgr删除摄像机。

2）使用的类：WebService[可选]，Storage,IPCamMgr

3）函数：

/*
 *WebService从服务器上删除摄像机
 *参数：
 *sosocam_camera_id:摄像机sosocam_id
 *delegate:代理WebServiceRemoveCameraDelegate，添加后可以监控删除结果
 */
-(WEBSERVICE_ERROR)remove_camera:(NSString *)sosocam_camera_id
delegate:(id<WebServiceRemoveCameraDelegate>)delegate;

/*
 *Storage从本地删除摄像机
 *参数:
 *camera_id:摄像机id
 */
-(void)remove_camera:(NSString *)camera_id;

/*
 *IPCamMgr删除摄像机
 *camera_id:摄像机id
 *另外IPCamMgr删除有个删除代理IPCamMgrDelegate，添加后可以监控删除结果
 */
-(IPCam *)remove_camera:(NSString *)camera_id;

4）步骤：

第一步：用WebService的方法从服务器上删除摄像机，如果不需用用到服务器平台这一步省略。<这一步骤可以添加WebServiceRemoveCameraDelegate代理监控删除结果，详情参考：IPCamMgr的服务器上删除摄像机>

第二步：用Storage的方法把从本地删除摄像机。

第三步：用IPCamMgr的方法从IPCamMgr中删除摄像机。<这一步骤可以添加IPCamMgrDelegate代理，监控添加，详情草考：IPCamMgr的cam添加和删除>

5）示列：

/*第一步：从服务器上删除摄像机+添加代理WebServiceRemoveCameraDelegate*/
-(void)delete_server{
    
    if (WEBSERVICE_ERROR_NO_ERROR != [[WebService get_share] remove_camera:m_sosocam_camera_id delegate:self]) {
           /*从服务器删除失败*/
    }
}
/*第二步：从本地和IPCamMgr删除摄像机*/
-(void)on_remove_camera_result:(WEBSERVICE_ERROR)error{
    /*监控到从服务器删除摄像机成功*/
    if (error == WEBSERVICE_ERROR_NO_ERROR) {
        [[Storage get_share] remove_camera:m_camera_id]; //从本地删除摄像机
        [[IPCamMgr get_share] remove_camera:m_camera_id]; //从IPCamMgr删除摄像机
        
          /*从服务器删除成功*/
    } else {
                /*从服务器删除失败*/
    }
}

#pragma mark －－5.3摄像机的修改更新<密码／名称>
5.3摄像机的修改更新
1）说明：摄像机的修改更新是指摄像机的做了修改要实时同步更新到服务器／本地／IPCamMgr。但是更新内容有限制，比如只有名称更新了才能同步更新到服务器，其他的更新就不同步到服务器。详细如下：
服务器：更新名称
IPCamMgr：更新密码
Storage：更新名称／登录名／登录密码／https／id /sosocam_id/cover/master

2）使用的类：WebService[可选]，Storage,IPCamMgr,IPCam

3）注意：
a）更新涉及到很多内容，这里着重讲密码和名称的更新。
b）密码修改，是只摄像机的登录密码修改。为了隐私保护，不会同步到服务器。所以只需要更新到本地和IPCamMgr。
c) 名称修改，不是针对摄像机修改的，只是当前帐号当前摄像机的一个昵称，故不涉及到操作摄像机，只要更新本地和服务器端就好。
d) 其他一些修改更新比如https／master，<详情参考:Storage本地存储收藏摄像机管理和IPCam的操作>

4）函数
/*
 *IPCam修改摄像机登录密码
 *参数：
 *pwd：摄像机新密码
 *delegate:代理IPCamResetPwdDelegate可以监控摄像机设置密码的结果
 *返回：
 *返回IIPCAM_ERROR ＝ PCAM_ERROR_NO_ERROR表示设置新密码成功
 */
-(IPCAM_ERROR)reset_pwd:(NSString *)pwd
delegate:(id<IPCamResetPwdDelegate>)delegate;

/*
 *IPCam设置IPCam的cam名称
 
 */
-(void)set_alias:(NSString *)alias;

/*
 *WebService更新名称
 *参数：
 *sosocam_camera_id:摄像机sosocam_id
 *alias:新名称
 *delegate:代理WebServiceUpdateCameraAliasDelegate可以监控更新结果
 *返回：
 *当WEBSERVICE_ERROR == WEBSERVICE_ERROR_NO_ERROR时表示更新执行成功
 */
-(WEBSERVICE_ERROR)update_camera_alias:(NSString *)sosocam_camera_id
alias:(NSString *)alias
delegate:(id<WebServiceUpdateCameraAliasDelegate>)delegate;

/*
 *IPCamMgr更新密码到IPCamMgr
 *参数：
 *camera_id:摄像机id
 *pwd:新密码
 */
-(void)update_camera_pwd:(NSString *)camera_id
pwd:(NSString *)pwd;

/*
 *Storage更新摄像机的名称
 *参数
 *camera_id:要被更新的摄像机id
 *alias:摄像机昵称更新为alias
 */
-(void)update_camera_alias:(NSString *)camera_id
alias:(NSString *)alias;

/*
 *Storage更新摄像机的登录密码
 *参数
 *camera_id:要被更新的摄像机id
 *pwd:摄像机登录密码更新为pwd
 */
-(void)update_camera_pwd:(NSString *)camera_id
pwd:(NSString *)pwd;

5）步骤
摄像机登录密码和更新
第一步：用IPCam的reset_pwd修改摄像机登录密码。<详情参考：IPCam的重置新密码>
第二步：用IPCamMgr的密码更新方法和Storage的密码更新方法更新密码

名称修改和更新
第一步［可选］：用WebService的方法更新名称，可以添加代理WebServiceUpdateCameraAliasDelegate监控更新结果。<详情参考：WebService服务器上更新摄像机名称>
第二步：用Storage的方法更新名称。
第三步：更新新名称到IPCam，可以添加代理IPCamDelegate。<详情参考：摄像机基础代理>

6）示例：
摄像机登录密码和更新
/*第一步：设置摄像机新密码＋添加代理*/
[m_ipcam reset_pwd:[m_view get_new_pwd1] delegate:self];
/*第二步：更新到IPCamMgr和Storage*/

-(void)on_reset_pwd_result:(id)ipcam
error:(IPCAM_ERROR)error
{
    if (IPCAM_ERROR_NO_ERROR == error) {
        [[Storage get_share] update_camera_pwd:[ipcam camera_id] pwd:[ipcam pwd]]; //更新保存到本地
        [[IPCamMgr get_share] update_camera_pwd:[m_ipcam camera_id] pwd:[ipcam pwd]];//更新到IPCamMgr
    } else {
          /*set camera pwd fail*/
    }
}

名称修改和更新
/*第一步：更新名称到服务器＋添加代理WebServiceUpdateCameraAliasDelegate*/
-(void) update_name_to_server {
    if (WEBSERVICE_ERROR_NO_ERROR !=
        [[WebService get_share] update_camera_alias:[m_ipcam sosocam_id] alias:m_camera_name delegate:self]) {
        /*update camera alias fail!*/
    }
}
/*第二步：更新名称到本地和IPCam*/
-(void)on_update_camera_alias_result:(WEBSERVICE_ERROR)error {
    
    if (WEBSERVICE_ERROR_NO_ERROR == error) {
        [[Storage get_share] update_camera_alias:[m_ipcam camera_id] alias:m_camera_name];
        [m_ipcam set_alias:m_camera_name];
    }
}

#pragma mark 6.摄像机连接操作

6.摄像机连接

说明：摄像机的连接有两种：第一种是是通过 IPCamMgr来进行摄像机的连接，可根据网络状态和前后台的状态来自动管理多个摄像机的连接，Reecam推荐此种方式。第二种是通过IPCam来进行摄像机的连接，此种方式由应用程序完全自我掌控摄像机的连接。

#pragma mark －－6.1通过IPCamMgr摄像机的连接 [Reecam推荐的连接方式]

6.1通过IPCamMgr摄像机的连接 [Reecam推荐的连接方式]

1）说明:IPCamMgr摄像机的连接是指：通过IPCamMgr里的方法来连接摄像机，方法是把摄像机添加到IPCamMgr，这样IPCamMgr里的所有摄像机就自动连接起来了。添加的cams会根据网络状态自动选择连接方式(局域网连接还是p2p连接),自动重连，还可设置moblie联网下摄像机的连接模式（禁止连接还是允许连接），还可操作让摄像机立即连接。

2）使用的类：IPCamMgr，IPCam[可选]，Storage[可选]

3)注意点：
    a)摄像机连接，至少要设置好id、user、pwd、https四个参数。其中https默认是NO,如果此时摄像机https是YES,这时是连接不上的。
    b)ios不允许程序后台运行，所以每次当程序挂起applicationWillResignActive时，都要stop掉IPCamMgr的连接和局域
    网搜索。每次到程序复原applicationDidBecomeActive的时候都要重新start IPCamMgr的连接和局域网搜索。
    c)p2p连接摄像机时，摄像机的p2p_svr和id_type要书写正确[详细参考：wiki.reecam.cn/P2p/Config]

4）函数：
/*
 *SDK初始化／反初始化＋开始／停止IPCamMgr
 详情参考：IPCamMgr的“SDK初始化和反初始化”
 */
+(IPCamMgr *)get_share;//创建IPCamMgr 初始化

+(void)release_share;//释放IPCamMgr，反初始化

-(void)start;//批量管理cams 开始连接cams

-(void)stop; //批量管理cams 停止连接cams
/*
 *局域网搜索[可选]
 * 详情参考：IPCamMgr的“局域网搜索”
 */
-(NSArray *)get_discovered_cameras_list

/*
 *IPCamMgr摄像机添加+添加的代理
 *详细参考：IPCamMgr的“添加和删除代理和协议”
 */
-(IPCam *)add_camera:(NSString *)camera_id
alias:(NSString *)alias
user:(NSString *)user
pwd:(NSString *)pwd
https:(BOOL)https;

/*
 *摄像机连接状态[可选]
 *详细参考：IPCam的“摄像机基础代理”
 */
-(void)on_status_changed:(id)ipcam;

/*
 *立即连接[可选]
 *详细参考：IPCamMgr的“立即连接”
 */
-(void)reset_camera:(NSString *)camera_id;


/*
 *moblie连接控制[可选]
 *详细参考：IPCamMgr的“数据(moblie)联网下的连接设置"
 */
-(void)set_forbidden_in_mobile:(BOOL)forbidden_in_mobile;

5）步骤：
第一步：用IPCamMgr的init和start函数进行sdk初始化开始IPCamMgr;

第二步：使用IPCamMgr的add_camera函数添加摄像机到IPCamMgr类，摄像机添加后，就会自动连接摄像机。[所以如果使用这种方式来连接摄像机的话，添加摄像机成功后，必须要在添加摄像机到IPCamMgr，同时删除摄像机后，也必须从IPCamMgr删除摄像机]

第三步[可选步]：监控摄像机的连接状态。[摄像机的连接状态监控详细参考：<IPCam类的摄像机基础代理>]

第四步[可选项]：立即连接。IPCamMgr是多个摄像机的管理。你可以通过IPCamMgr的reset_camera优先设置摄像机立即连接。

第五步[可选项]：数据流量下的连接模式设置。可通过IPCamMgr的set_forbidden_in_mobile来设置（设置mobile联网下是否允许对摄像机的连接）。

6）例子：
/*
 *第一步：使用PCamMgr的start函数初始化SDK
 */
[[IPCamMgr get_share] start];

 /*
 *第二步：添加摄像机到PCamMgr
 */

NSArray * cameras_list = [[IPCamMgr get_share] get_discovered_cameras_list];

IPCam * ipcam = [[IPCamMgr get_share] add_camera:[m_camera objectForKey:@"camera_id"]
                                           alias:@"sandy"
                                            user:@"admin"
                                             pwd:[m_ipcam pwd]
                                           https:[m_ipcam https]];//添加摄像机到IPCamMgr
/*
 *第三步[可选]：监控摄像机的连接状态 [注意IPCamDelegate的代理多有加进来，否则容易奔溃]
 */
[m_ipcam add_delegate:self];//添加IPCamDelegate代理

-(void)on_status_changed:(id)ipcam{
    
    NSLog(@"cam connect status = %@"[m_ipcam status]);
}
.
.
.

/*
 *第四步[可选]：立即连接
 */
[[IPCamMgr get_share]reset_camera:[ipcam camera_id]];

/*
 *第五步[可选]：摄像机数据流量下连接连接设置
 */
[[IPCamMgr get_share]set_forbidden_in_mobile:YES];//设置数据流量下禁止连接


#pragma mark －－6.2通过IPCam摄像机的连接

6.2通过IPCam摄像机的连接

1）说明：使用IPCam来进行摄像机的连接是指：通过IPCam的方法连接摄像机，方法是创建一个IPCam,然后调用连接函数连接（需要局域网连接的还需要更新局域网信息），这样子摄像机就连接起来。但是只是操作的摄像机连接，其他的不会去连接，而且，摄像机不会自动选择连接方式（局域网还是p2p连接）等，所有的操作必须要自己去实现。

2）使用的类：IPCamMgr，IPCam

3)注意点：
    a)摄像机连接，至少要设置好id、user、pwd、https四个参数。其中https默认是NO,如果此时摄像机https是YES,这时是连接不上的。
    b)ios不允许程序后台运行，所以每次当程序挂起applicationWillResignActive时，都要stop掉IPCamMgr的连接和局域
    网搜索。每次到程序复原applicationDidBecomeActive的时候都要重新start IPCamMgr的连接和局域网搜索。
    c)p2p连接摄像机时，摄像机的p2p_svr和id_type要书写正确[详细参考：wiki.reecam.cn/P2p/Config]

4）函数：

/*
 *更新摄像机局域网信息[可选]，注意：
 *1)如需采用局域网ip直连的方式连接摄像机，必须要调用IPCam的update_lan_status函数来设置摄像机的局域网地址，否则缺省使用p2p的方式进行连接
 *2)update_lan_status可以在start_connect前后使用都可以。如果在start_connect之前设置，摄像机就直接使用设置的模式in_lan去连接。如果在start_connect之后设置，摄像机就会先断开连接，再使用设置的模式in_lan去连接。
 *3)in_lan未改变，摄像机不会根据当前网络是局域网还是p2p自动连接。只会使用in_lan设置的模式去连接，直到in_lan值改变
*/
/*
 *参数如下：
 *in_lan：BOOL值，是否使用局域网连接。YES:使用局域网直连；NO:使用p2p连接；缺省为NO
 *ip：局域网（in_lan设置为YES):当前摄像机ip；p2p（in_lan设置为NO）:可以不用设置
 *port：局域网（in_lan设置为YES）:当前摄像机port；p2p（in_lan设置为NO）:可以不用设置
 *https：BOOL值，当前摄像机是否加密传输.YES:加密传输。NO:不加密传输。
 */
-(void)update_lan_status:(BOOL)in_lan
ip:(NSString *)ip
port:(int)port
https:(BOOL)https

/*
 *连接函数
 *摄像机的id、pwd、user、https参数都设置好了以后,就可以开始连接了
 *参数如下：
 *retryable:是否重连,YES:当因为网络错误时会自动重连接； NO:不重连
 *retry_delay:int类型，单位ms,延迟多长时间重连。
 */
-(IPCAM_ERROR)start_connect:(BOOL)retryable
retry_delay:(int)retry_delay;

/*断开摄像机
 说明：当不需要在连接摄像机时，可以使用stop_connect来主动断开摄像机的连接
 */
-(void)stop_connect;

5）步骤：
第一步：用IPCamMgr的init和start函数进行sdk初始化开始IPCamMgr;

第二步：alloc一个IPCam，且设置 IPCam 的 id、user、pwd、https参数[这四个参数必须设置];

第三步[可选步骤]：如果直接进入第五步骤，摄像机使用p2p连接。如果需要局域网直连，则在连接前  必须用IPCam的update_lan_status更新。更新步骤如下：
*通过IPCamMgr的get_discovered_cameras_list函数，获取到局域网内的摄像机。[详情参考局域网搜索]
*然后判断一下局域网内有没有你的摄像机，如果有，就把局域网的信息，用update_lan_status更新一下

第四步[可选步]：监控摄像机的连接状态，如果摄像机断开了，你要主动去update_lan_status摄像机信息，然后手动去连接。[摄像机的连接状态监控详细参考：<IPCam类的摄像机基础代理>]

第五步：用IPCam的start_connect连接摄像机。


6）示列

/*
 *第一步：使用PCamMgr的start函数初始化SDK
 */
[[IPCamMgr get_share] start];

/*
 *第二步：new一个IPCam＋设置IPCam的参数
 */
-(void)set_cameras
{
    IPCam * m_ipcam = [[IPCam alloc]init];
    [m_ipcam set_camera_id:@"SOSO-000019-VLTVM"];
    [m_ipcam set_user:@"admin"];
    [m_ipcam set_pwd:@"88888888"];
    [m_ipcam set_https:NO];
}
/*
 *第三步：更新局域信息[可选项]放在start_connect前后都可以
 */
NSArray * cameras_list = [[IPCamMgr get_share] get_discovered_cameras_list]; //获取局域网的摄像机
NSDictionary * m_camera = [cameras_list objectAtIndex:0];//假设局域网内第一个摄像机就是你添加的摄像机
[m_ipcam update_lan_status:YES ip:[m_camera objectForKey:@"current_ip"] port:[[m_camera objectForKey:@"port"] intValue] https:[[m_camera objectForKey:@"https"] boolValue]];//更新局域网地址和ip
/*
 *第四步：监控摄像机的连接状态 [注意IPCamDelegate的代理多有加进来，否则容易奔溃]
 */
[m_ipcam add_delegate:self];//添加IPCamDelegate代理

-(void)on_status_changed:(id)ipcam{
    
    IPCAM_STATUS status = [m_ipcam status];
    if (status != IPCAM_STATUS_CONNECTED){
        /*
         *切换连接方式＋更新信息
         */
        [m_ipcam update_lan_status:YES ip:[m_camera objectForKey:@"current_ip"] port:[[m_camera objectForKey:@"port"] intValue] https:[[m_camera objectForKey:@"https"] boolValue]];//切换为局域网连接＋更新局域网信息
//        [m_ipcam update_lan_status:NO ip:nil port:nil https:[[m_ipcam https] boolValue]];//切换为p2p连接
    }
}
.
.
.

/*
 *第五步：连接摄像机
 */
[m_ipcam start_connect:NO retry_delay:0];

/*
 第六步：不需要连接时，断开摄像机连接;不需要监控摄像机状态时，删除代理;不需要使用sdk时，反初始化sdk
 */
[m_ipcam remove_delegate:self];
[m_ipcam stop_connect];
[IPCamMgr release_share];

#pragma mark 7.本地摄像机和服务器摄像机获取

7.本地摄像机和服务器摄像机获取

1)说明：本地摄像机和服务器摄像机获取是指：获取被你添加到本地或服务器的摄像机，包括本地和服务器的获取以及对比同步。流程如下：
WebService里面获取服务器里的摄像机 －－－> WebService对比同步 －－－> Storage获取本地的摄像机 －－－> 添加到IPCamMgr。
这些过程按照你的需求，择选，详细如下：
如果用到服务器平台管理摄像机，那么需要在WebService获取[可选项];
如果用到服务器平台管理摄像机，那么需要在WebService对比同步[可选项];
不管用不用到平台，都需要在Storage获取[必须];
如果用到批量管理摄像机或使用IPCamMgr连接摄像机，那么需要在IPCamMgr添加。［推荐使用IPCamMgr管理];

2）使用类：storage，IPCamMgr，WebService

3）注意点：
    a)这里介绍怎么获取摄像机，是基于使用Storage存储的，而不是自己定义的存储。基于Storage存储的方法请参考上面的<摄像机的添加／删除／修改更新>。
    b)存储的时候是使用Storage存储的，才能用以下介绍的方法获取。
    c)使用IPCamMgr的方式连接摄像机批量管理，从本地获取到摄像机后或和服务器同步后必须把从本地获取到的摄像机添加到IPCamMgr，这样子摄像机才会自动连接等，而后面需要获取摄像机都从IPCamMgr获取即可。[推荐方式]
    d)使用平台管理要注意，到登录状态改变时，每次重新获取到账号登陆成功，如果比较出本地和服务器的摄像机不一样，需要先把IPCamMgr的摄像机全部清除掉，然后在获取到本地的摄像机，逐个添加到IPCamMgr。

4）函数：

/*
 *storag的方法
 *storage获取本地存储的摄像机
 *返回：返回一个NSArray，数组的每一个元素是一个字典，key/value如下：
 *camera_id:摄像机id,NSString类型
 *alias:摄像机昵称,NSString类型
 *user:摄像机登录用户名,NSString类型
 *pwd:摄像机登录密码,NSString类型
 *https:加密安全传输，两个值 0:非加密 1:加密,NSNumber类型
 *sosocam_id:摄像机sosocam_id,NSString类型
 *cover:摄像机预览图data数据,NSData类型
 *model:这个值没有特定的意义，你可以自己定义，但是如果你不去设置的话  它默认一直是0。我们是定义0云台机  1为卡片机  NSNumber类型
 *recent:NSNumber的Long类型，暂未使用，保留
 *master：主摄像机，BOOL值，YES:主摄像机，NO:非主摄像机。NSNumber的BOOL类型
 */
-(NSArray *)get_cameras_list; //storage获取本地存储的摄像机

/*
 *IPCamMgr方法
 *添加摄像机到IPCamMgr
 *参数：
 *camera_id：摄像机id
 *alias:摄像机昵称
 *user:摄像机登录用户名
 *pwd:摄像机登录密码
 *https:安全加密传输，两个值：YES:加密 NO:非加密
 *另外IPCamMgr添加有个添加代理IPCamMgrDelegate，添加后可以监控添加结果
 */
-(IPCam *)add_camera:(NSString *)camera_id
alias:(NSString *)alias
user:(NSString *)user
pwd:(NSString *)pwd
https:(BOOL)https;

/*
 *WebService的方法
 *WebService获取服务器当前帐号的摄像机
 *返回：返回一个NSArray，数组的每一个元素是一个字典，key/value如下：
 *camera_id:摄像机id,NSString类型
 *sosocam_camera_id:摄像机sosocam_id,NSString类型
 *alias:摄像机昵称,NSString类型
 *https:加密安全传输，两个值 0:非加密 1:加密,NSNumber类型
 *user:摄像机登录用户名,NSString类型
 *pwd:摄像机登录密码,NSString类型
 *model:这个值没有特定的意义，你可以自己定义，但是如果你不去设置的话，它默认一直是0。我们是定义0云台机，1为卡片机。NSNumber类型
 */
-(NSArray *)get_cameras_list; //WebService获取服务器当前帐号的摄像机

/*
 *storag的方法
 *storag的比较方法
 *参数：
 *server_cameras_list:从服务器上获取到的当前帐号的摄像机
 *返回：返回一个返回BOOL值
 *如果返回YES表示:服务器上的cams和本地的cams一样
 *如果返回NO表示:服务器上的cams和本地的cams不一样，且自动做同步
 */
-(BOOL)merge_cameras_list:(NSArray *)server_cameras_list;

5）步骤：

第一步：使用WebService的get_cameras_list获取当前帐号服务器的所有摄像机<使用平台管理，才用到此步骤，否则跳过>

第二步：使用storag的merge_cameras_list的方法比较同步<使用平台管理，才用到此步骤，否则跳过>

第三步：使用storag的get_cameras_list获取本地当前帐号的所有摄像机，也是改账号所有添加的摄像机<如果没有用到服务器存储，直接使用此步骤>

第四步：使用IPCamMgr的add添加摄像机到IPCamMgr<如果需要使用IPCamMgr管理>

第五步：如果使用平台管理摄像机，每次重新获取到账号登陆成功，且同步返回No,需先清掉IPCamMgr的摄像机，然后逐个添加到IPCamMgr。

6）示例：
/*第一步：获取服务器上当前存储的“添加摄像机”*/
NSArray * arry_svr_cams = [[WebService get_share] get_cameras_list];

/*第二步：对比且同步本地和服务器上该帐号的摄像机*/
[[Storage get_share] merge_cameras_list:arry_svr_cams]

/*第三步：获取该帐号本地的所有摄像机*/
NSArray * cameras_list = [[Storage get_share] get_cameras_list];//获取本地cams

/*第四步：添加摄像机到IPCamMgr，用于批量管理摄像机*/
-(void)add_cameras_to_ipcammgr{
    IPCamMgr * ipcammgr = [IPCamMgr get_share];
    NSDictionary * camera;
    IPCam * ipcam;
    int i;
    for (i = 0;i < cameras_list.count;i ++) {
        camera = [cameras_list objectAtIndex:i];
        ipcam = [ipcammgr add_camera:[camera objectForKey:@"camera_id"] alias:[camera objectForKey:@"alias"] user:[camera objectForKey:@"user"] pwd:[camera objectForKey:@"pwd"] https:[[camera objectForKey:@"https"] boolValue]];//逐一添加cam到IPCamMgr
        /*如果还需要为ipcam设置什么属性，在此处添加，比如设置预览图/model/sosocam_id
         *这样子IPCamMgr的cam就具备这些属性了
         */
        [ipcam set_cover:[camera objectForKey:@"cover"]];
        [ipcam set_model:[[camera objectForKey:@"model"] intValue]];
        [ipcam set_sosocam_id:[camera objectForKey:@"sosocam_id"]];
    }
}
/*第五步：如果使用平台管理摄像机，每次重新获取到账号登陆成功，且同步返回No,需先清掉IPCamMgr的摄像机，然后逐个添加到IPCamMgr。*/
-(void)on_login_status_changed{

    WEBSERVICE_LOGIN_STATUS status = [webservice get_login_status];
    if (status == WEBSERVICE_LOGIN_STATUS_LOGGING_IN) {
        if(![[Storage get_share] merge_cameras_list:arry_svr_cams]){
            [[IPCamMgr get_share] clear_cameras_list];
            [self add_cameras_to_ipcammgr];
        }
    }
}

#pragma mark 8.摄像机基本功能实现
8.摄像机基本功能实现
说明：

#pragma mark －－8.1.摄像机视频<设置视频页面／视频状态／视频质量参数／播放视频或切换播放视频流／停止播放视频>
8.1.摄像机视频

1）说明：摄像机视频主要是指：视频页面的设置，视频播放停止，视频高清标清切换，以及视频状态获取和视频的相关代理函数。

2）使用的类：IPCam,IPCamVideoView

3）函数
a)设置视频页面
/*
 *IPCamVideoView类：设置视频页面
 *参数：
 *video_view：这是一个IPCamVideoView, IPCamVideoView是一个继承UIView.
 */
-(void)set_video_view:(IPCamVideoView *)video_view;  //设置视频页面

b)视频状态
/*
 *IPCam类：获取视频状态
 *返回：返回IPCAM_PLAY_STATUS类型，详细如下IPCAM_PLAY_STATUS
 */
-(IPCAM_PLAY_STATUS)video_status;
typedef enum {
    IPCAM_PLAY_STATUS_STOPPED, //停止
    IPCAM_PLAY_STATUS_REQUESTING,//请求中
    IPCAM_PLAY_STATUS_PLAYING,//播放中
} IPCAM_PLAY_STATUS;

c)视频质量参数
/*
 *IPCam类：视频质量参数
 *返回：都是返回int类型
 */
-(int)video_render_fps; //视频发送fps
-(int)video_recv_fps; //视频接收的fbs
-(int)video_byterate; //视频当前的byte

d)播放视频或切换播放视频流
/*
 *IPCam类：播放视频或切换播放视频流
 *参数：
 *stream:视频流参数（0或1）,3518e只有两个分辨率:0:640*480(标清);1:1280*960(高清)
 *返回：
 *返回IPCAM_ERROR类型，当返回类型是IPCAM_ERROR_NO_ERROR时，表示开启播放视频或者切换视频流成功
 */

-(IPCAM_ERROR)play_video:(int)stream;


e)停止播放视频
/*
 *IPCam类：停止播放视频
 */
-(void)stop_video;

f)视频代理
/*
 *IPCamVideo类
 *IPCamVideoViewDelegate:需在视频上[注意是IPCamVideoView上不是IPCam]添加手势操作，就添加此代理
 *返回参数：
 *event:返回IPCAMVIDEOVIEW_TOUCH_EVENT参数，详细如下：
 */
-(void)set_delegate:(id<IPCamVideoViewDelegate>)delegate;//设置IPCamVideoViewDelegate代理
-(void)on_touch_event:(IPCAMVIDEOVIEW_TOUCH_EVENT)event; //IPCamVideoViewDelegate回调函数
typedef enum {
    IPCAMVIDEOVIEW_TOUCH_EVENT_CLICK, //单点
    IPCAMVIDEOVIEW_TOUCH_EVENT_MOVE_UP, //向上滑动
    IPCAMVIDEOVIEW_TOUCH_EVENT_MOVE_DOWN, //向下滑动
    IPCAMVIDEOVIEW_TOUCH_EVENT_MOVE_LEFT, //向左滑动
    IPCAMVIDEOVIEW_TOUCH_EVENT_MOVE_RIGHT, //向右滑动
} IPCAMVIDEOVIEW_TOUCH_EVENT;

/*
 *IPCam类
 *IPCamDelegate:需在监控视频状态，就要在IPCam上添加此代理
 *IPCamDelegate的详细用法请参考IPCam的基础代理
 */
-(void)add_delegate:(id<IPCamDelegate>)delegate;//设置IPCamDelegate代理
-(void)on_video_status_changed:(id)ipcam; //IPCamDelegate回调函数，视频状态改变时回调
-(void)remove_delegate:(id<IPCamDelegate>)delegate; //删除IPCamDelegate代理
4）注意点：
    a)设置视频页面时，创建添加IPCamVideoView后，必须要设置frame
    b)播放视频或获取视频状态或设置视频相关，必须是在摄像机连接成功为前提
    c)添加IPCamDelegate代理后，代理回调的所有函数都要添加，即使不用，而不是只添加视频状态回调代理。如果没有添加齐全，会引起程序奔溃
    d)因很多状态都是IPCamDelegate代理，所以要注意IPCamDelegate代理不允许多次添加，是需要使用时也要记得remove。

5）步骤：
第一步：创建并设置视频页面：即创建IPCamVideoView的UIView且设置大小。

第二步:添加代理IPCamVideoViewDelegate和IPCamDelegate，这一步根据需要添加。<可选>

第三步：进行视频操作：播放停止／视频流切换。

第三步：处理代理回调：添加了代理才有代理回调。<可选>

6）示列：
/*第一步：创建一个IPCamVideoView设置大小，再设置视频页面*/
IPCamVideoView * m_videoview = [[IPCamVideoView alloc]initWithFrame:CGRectMake(0, 0, self.view.bounds.size.width, self.view.bounds.size.height)];
[self.view addSubview:m_videoview];
[m_ipcam set_video_view:m_videoview];//设置视频页面
int m_playing_video_stream = 0;   //定义默认播放视频流

/*第二步：在视频上添加代理IPCamVideoViewDelegate和IPCamDelegate*/
[m_videoview set_delegate:self]; //m_videoview添加IPCamVideoViewDelegate不是m_ipcam
[m_ipcam add_delegate:self]; //m_ipcam添加IPCamDelegate

/* 第三步:视频播放和停止*/
- (IBAction)button_playvideo_onclick:(id)sender {
    IPCAM_PLAY_STATUS status = [m_ipcam video_status];//获取视频当前状态
    if (status == IPCAM_PLAY_STATUS_PLAYING){
        [m_ipcam stop_video]; // 停止播放视频
    }
    else if (status == IPCAM_PLAY_STATUS_STOPPED){
        [m_ipcam play_video:m_playing_video_stream]; //播放m_playing_video_stream路视频流
    }
    /*视频质量如下*/
    NSLog(@"视频发送：%@fbs",[m_ipcam video_render_fps]); //发送fbs
    NSLog(@"视频接收：%@fbs",[m_ipcam video_recv_fps]); //接收fbs
    NSLog(@"视频当前：%@byte",[m_ipcam video_byterate]); //当前视频byte
}

/*第三步:设置播放视频流，即高清和标清设置或切换 */
- (IBAction)button_stream_onclick:(id)sender {
    if (m_playing_video_stream == 0){
        m_playing_video_stream = 1;
    }
    else{
        m_playing_video_stream = 0;
    }
    [m_ipcam stop_video];
    [m_ipcam play_video:m_playing_video_stream];
}

/*第四步：IPCamVideoViewDelegate回调实现*/
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
/*第四步：IPCamDelegate摄像机视频状态改变*/
-(void)on_video_status_changed:(id)ipcam{
    IPCAM_PLAY_STATUS status = [m_ipcam video_status];
}

#pragma mark －－8.2 摄像机音频<开启／关闭音频／音频状态／质量>
8.2 摄像机音频

1)说明：摄像机音频，主要包括音频状态获取，音频开启和关闭操作。操作以下函数前，摄像机必须是连接成功的。

2)使用类：IPCam

3)函数：
a）音频状态
/*
 *IPCam类方法
 *返回：
 *返回IPCAM_PLAY_STATUS，详细如下：
 */
-(IPCAM_PLAY_STATUS)audio_status;
typedef enum {
    IPCAM_PLAY_STATUS_STOPPED, //停止
    IPCAM_PLAY_STATUS_REQUESTING,//请求中
    IPCAM_PLAY_STATUS_PLAYING,//播放中
} IPCAM_PLAY_STATUS;

b)音频质量
/*
 *IPCam类方法
 *返回：
 *返回int类型，真实大小，详细如下：
 */
-(int)audio_sps; //音频的sps
-(int)audio_byterate; //音频的byte
c）开启音频
/*
 *IPCam类方法:开启音频
 *返回：
 *返回IPCAM_ERROR类型，当返回类型是IPCAM_ERROR_NO_ERROR时，表示开启音频成功
 */
-(IPCAM_ERROR)play_audio;

d）关闭音频
/*
 *IPCam类方法:关闭音频
 */
-(void)stop_audio;

e）音频代理
/*
 *IPCam类:IPCamDelegate代理
 *IPCamDelegate的详细用法请参考IPCam的基础代理
 */
-(void)add_delegate:(id<IPCamDelegate>)delegate;//设置IPCamDelegate代理
-(void)on_audio_status_changed:(id)ipcam; //IPCamDelegate回调函数，音频状态改变时回调
-(void)remove_delegate:(id<IPCamDelegate>)delegate; //删除IPCamDelegate代理

4）注意点：
    a)开启停止音频或获取音频状态等相关操作，必须是在摄像机连接成功为前提
    b)添加IPCamDelegate代理后，代理回调的所有函数都要添加，即使不用，而不是只添加音频状态回调代理。如果没有添加齐全，会引起程序奔溃
    c)因很多状态都是IPCamDelegate代理，所以要注意IPCamDelegate代理不允许多次添加，是需要使用时也要记得remove。

5）步骤：
第一步:添加代理IPCamDelegate，这一步根据需要添加。<可选>

第二步：摄像机连接成功即可直接开启停止音频等操作。

第三步：处理代理回调：添加了代理才有代理回调。<可选>


6）示列：
/*第一步：添加IPCamDelegate代理*/
[m_ipcam add_delegate:self]; //m_ipcam添加IPCamDelegate
/*第二步：音频操作 */
- (IBAction)button_playaudio_onclick:(UIButton*)sender {
    IPCAM_PLAY_STATUS status = [m_ipcam audio_status]; //获取音频状态
    if (status == IPCAM_PLAY_STATUS_PLAYING){
        [m_ipcam stop_audio]; //关闭音频
    }
    else if (status == IPCAM_PLAY_STATUS_STOPPED){
        [m_ipcam play_audio];//开启音频
    }
    /*音频质量如下*/
    NSLog(@"音频质量：%@fbs",[m_ipcam audio_sps]); //音频的sps
    NSLog(@"音频质量：%@byte",[m_ipcam audio_byterate]); //音频的byte
}
/*第二步：代理回调 */
-(void)on_audio_status_changed:(id)ipcam{
    IPCAM_PLAY_STATUS status = [m_ipcam audio_status]; //获取音频当前状态
}

#pragma mark －－8.3 摄像机对讲<对讲开启／关闭／状态／质量>
8.3 摄像机对讲
1)说明：摄像机音频，主要包括对讲状态获取，对讲开启和关闭操作。操作以下函数前，摄像机必须是连接成功的。

2)使用类：IPCam

3)函数：

a）对讲状态
/*
 *IPCam类：对讲状态获取
 *返回：
 *返回IPCAM_PLAY_STATUS，详细状态如下：
 */
-(IPCAM_PLAY_STATUS)speak_status;
typedef enum {
    IPCAM_PLAY_STATUS_STOPPED, //停止
    IPCAM_PLAY_STATUS_REQUESTING,//请求中
    IPCAM_PLAY_STATUS_PLAYING,//播放中
} IPCAM_PLAY_STATUS;
b)对讲质量
/*
 *IPCam类：对讲状态获取
 *返回：
 *返回int类型，真实大小，详细如下：
 */
-(int)speak_sps; //对讲的sps
-(int)speak_byterate; //对讲的byte

c）开启对讲
/*
 *IPCam类：开启对讲
 *返回：
 *返回IPCAM_ERROR类型，当返回类型是IPCAM_ERROR_NO_ERROR时，表示开启对讲成功
 */
-(IPCAM_ERROR)start_speak;

d）关闭对讲
/*
 *IPCam类：关闭对讲
 */
-(void)stop_speak;

e）对讲代理
/*
 *IPCam类:IPCamDelegate代理
 *IPCamDelegate的详细用法请参考IPCam的基础代理
 */
-(void)add_delegate:(id<IPCamDelegate>)delegate;//设置IPCamDelegate代理
-(void)on_speak_status_changed:(id)ipcam; //IPCamDelegate回调函数，音频状态改变时回调
-(void)remove_delegate:(id<IPCamDelegate>)delegate; //删除IPCamDelegate代理

4）注意点：
a)开启停止对讲或获取对讲状态等相关操作，必须是在摄像机连接成功为前提
b)添加IPCamDelegate代理后，代理回调的所有函数都要添加，即使不用，而不是只添加音频状态回调代理。如果没有添加齐全，会引起程序奔溃
c)因很多状态都是IPCamDelegate代理，所以要注意IPCamDelegate代理不允许多次添加，是需要使用时也要记得remove。

5）步骤：
第一步:添加代理IPCamDelegate，这一步根据需要添加。<可选>

第二步：摄像机连接成功即可直接开启停止对讲等操作。

第三步：处理代理回调：添加了代理才有代理回调。<可选>

6）示列
/*第一步：添加IPCamDelegate代理*/
[m_ipcam add_delegate:self]; //m_ipcam添加IPCamDelegate
/*第二步：音频操作 */
- (IBAction)button_speak_onclick:(id)sender {
    IPCAM_PLAY_STATUS status = [m_ipcam speak_status]; //对讲状态
    if (status == IPCAM_PLAY_STATUS_PLAYING)
        [m_ipcam stop_speak];
    else if (status == IPCAM_PLAY_STATUS_STOPPED)
        [m_ipcam start_speak];
    /*对讲质量如下*/
    NSLog(@"对讲质量：%@fbs",[m_ipcam speak_sps]); //对讲的sps
    NSLog(@"对讲质量：%@byte",[m_ipcam speak_byterate]); //对讲的byte
}
/*第二步：代理回调 */
-(void)on_audio_status_changed:(id)ipcam{
    IPCAM_PLAY_STATUS status = [m_ipcam speak_status]; //获取对讲当前状态
}

#pragma mark －－8.4 摄像机拍照
8.4 摄像机拍照
1）说明：摄像机拍照是指：把当前画面拍照保留到本地。有两个函数可以实现拍照，使用下面任何一个函数可以实现拍照功能，函数1不带存储地址的函数，使用前，必须创建一个登录账号[否则会因为存储地址错误，导致存储失败]，获取照片直接通过Storage的一个函数直接获取<推荐方法>。函数2带存储地址，自己决定存储地址，自己从地址中获取照片。

2)使用类：IPCam

3)函数：

/*
 *IPCam方法：拍照
 *返回：
 *返回IPCAM_ERROR类型，当返回类型是IPCAM_ERROR_NO_ERROR时，表示拍照成功。
 */
函数1：-(IPCAM_ERROR)snapshot;
/*
 *IPCam方法：拍照
 *参数：
 *photo_file_path：照片存储的完整路径
 *返回：
 *返回IPCAM_ERROR类型，当返回类型是IPCAM_ERROR_NO_ERROR时，表示拍照成功。
 */
-(IPCAM_ERROR)snapshot:(NSString*)photo_file_path;

4）注意点：a)使用拍照功能必须以视频开启成功为前提，也就是能看到视频画面后才能拍照。
         b)使用snapshot保存的路径是在document目录下，而不是系统相册，需要放到系统相册，需要再导出

5）示列
- (IBAction)button_snapshot_onclick:(id)sender {
    if (IPCAM_ERROR_NO_ERROR == [m_ipcam snapshot])
        NSLog(@"snapshot success!");
    else
        NSLog(@"snapshot fail!");
}

#pragma mark －－8.5 摄像机本地录像<本地录像状态／开启／停止>

8.5 摄像机本地录像

1）说明:摄像机本地录像是指：把当前视频录制到本地。主要包括本地录像状态获取，开启本地录像和停止本地录像。有两个函数可以实现录像功能，函数1不带存储地址的函数，使用前，必须创建一个登录账号[否则会因为存储地址错误，导致存储失败]，获取录像文件直接通过Storage的一个函数直接获取。函数2带存储地址，自己决定存储地址，自己从地址中获取录像文件。

2）使用类:IPCam

3）函数：

a）本地录像状态
/*
 *IPCam方法：本地录像状态
 *返回：
 *返回IPCAM_PLAY_STATUS，详细如下：
 */
-(IPCAM_PLAY_STATUS)local_record_status;
typedef enum {
    IPCAM_PLAY_STATUS_STOPPED, //停止
    IPCAM_PLAY_STATUS_REQUESTING,//请求中
    IPCAM_PLAY_STATUS_PLAYING,//录像中
} IPCAM_PLAY_STATUS;

b）开启本地录像
/*
 *IPCam方法：开启本地录像
 *返回：
 *返回IPCAM_ERROR类型，当返回类型是IPCAM_ERROR_NO_ERROR时，表示本地录像成功。
 */
函数1:-(IPCAM_ERROR)start_local_record;

/*
 *IPCam方法：开启本地录像
 *参数：
 *record_file_path：录像存储的完整路径
 *返回：
 *返回IPCAM_ERROR类型，当返回类型是IPCAM_ERROR_NO_ERROR时，表示本地录像成功。
 */

函数2:-(IPCAM_ERROR)start_local_record:(NSString*)record_file_path;


c）停止本地录像
/*
 *IPCam方法：停止本地录像
*/
-(void)stop_local_record;


d）本地录像代理
/*
 *IPCam类:IPCamDelegate代理
 *IPCamDelegate的详细用法请参考IPCam的基础代理
 */
-(void)add_delegate:(id<IPCamDelegate>)delegate;//设置IPCamDelegate代理
-(void)on_camera_recording_changed:(id)ipcam; //IPCamDelegate回调函数，本地录像状态改变时回调
-(void)remove_delegate:(id<IPCamDelegate>)delegate; //删除IPCamDelegate代理

4)注意点：
    a)使用本地录像功能必须以视频开启成功为前提，也就是能看到视频画面后才能录制。
    b)添加IPCamDelegate代理后，代理回调的所有函数都要添加，即使不用，而不是只添加本地录像状态回调代理。如果没有添加齐全，会引起程序奔溃
    c)因很多状态都是IPCamDelegate代理，所以要注意IPCamDelegate代理不允许多次添加，是需要使用时也要记得remove。
    d)使用start_local_record保存的路径是在document目录下，而不是系统相册，需要放到系统相册，需要再导出

5)步骤
第一步:添加代理IPCamDelegate，这一步根据需要添加。<可选>

第二步：摄像机视频出来后即可直接开启停止等操作。

第三步：处理代理回调：添加了代理才有代理回调。<可选>

6）示列：
/*第一步：添加IPCamDelegate代理*/
[m_ipcam add_delegate:self]; //m_ipcam添加IPCamDelegate

/*第二步：录像操作 */
- (IBAction)button_record_onclick:(id)sender {
    if ( [m_ipcam local_record_status] == IPCAM_PLAY_STATUS_PLAYING) { //本地录像状态获取
        [m_ipcam stop_local_record];  //停止录像
    }
    else {
        //开启录像
        if (IPCAM_ERROR_NO_ERROR == [m_ipcam start_local_record]){
            NSLog(@"record success!");
        }
    }
}
/*第二步：代理回调 */
-(void)on_camera_recording_changed:(id)ipcam{
    IPCAM_PLAY_STATUS status = [m_ipcam local_record_status]; //获取本地录像当前状态
}

#pragma mark 9.摄像机PTZ操作<包括云台操作>

9.摄像机PTZ操作<包括云台操作>

1）说明：摄像机ptz操作是指：通过ptz_control命令来实现摄像机的一些控制命令。主要是云台操作功能的实现。

2）使用类：IPCam

3）函数：
/*
 *IPCam方法：ptz控制命令
 *参数：
 *cmd:功能命令，详细查看一下的IPCAM_PTZ_CMD
 *param:参数值，0:关  20:开 <上下左右控制没有停止命令，param固定位20，发一下，动一次>
 */
-(IPCAM_ERROR)ptz_control:(IPCAM_PTZ_CMD)cmd
param:(int)param

typedef enum {
    IPCAM_PTZ_CMD_UP, //向上
    IPCAM_PTZ_CMD_DOWN,//向下
    IPCAM_PTZ_CMD_LEFT,//向左
    IPCAM_PTZ_CMD_RIGHT,//向右
    IPCAM_PTZ_CMD_T_PATROL,//水平巡航
    IPCAM_PTZ_CMD_P_PATROL,//垂直巡航
    IPCAM_PTZ_CMD_TRACK_PATROL,//轨迹巡航
    
    IPCAM_PTZ_CMD_MEIJING_VOLUME_UP, //客户定制功能：增大mp3播放声音
    IPCAM_PTZ_CMD_MEIJING_VOLUME_DOWN,//客户定制功能：减小mp3播放声音
    IPCAM_PTZ_CMD_MEIJING_NEXT_TRACK,//客户定制功能：播放mp3下一首
    IPCAM_PTZ_CMD_MEIJING_PREVIOUS_TRACK,//客户定制功能：播放mp3上一首
    IPCAM_PTZ_CMD_MEIJING_PLAY_PAUSE,//客户定制功能：播放mp3
    IPCAM_PTZ_CMD_MEIJING_LED_POWER,//客户定制功能:开启led
    IPCAM_PTZ_CMD_MEIJING_LED_STYLE,//客户定制功能：led模式控制
    
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
    
} IPCAM_PTZ_CMD;

4）示列：
[m_ipcam ptz_control:IPCAM_PTZ_CMD_P_PATROL param:20]; //开启水平巡航
[m_ipcam ptz_control:IPCAM_PTZ_CMD_P_PATROL param:0];//关闭水平巡航


#pragma mark 10.摄像机CGI命令设置参数<如报警布防和TF卡录像>

10.摄像机CGI命令设置参数<如报警布防和TF卡录像>

1）说明：摄像机CGI命令设置参数是指通过CGI命令设置的一些参数，比如重启，录像，tf的设置，等其它功能。

2）使用类：IPCam

3）函数：

/*
 *IPCam方法：CGI设置参数
 *参数：
 *params:cgi参数，由reecam提供，下面列举一些
 *delegate:IPCamSetParamsDelegate代理，可以监控cgi设置的结果
 */
-(IPCAM_ERROR)set_params:(NSString *)params
delegate:(id<IPCamSetParamsDelegate>)delegate;
/*其中arm_schedule有三个值，0:布防，1:计划布防，2:撤防*/
报警params："save=1&reinit_alarm=1&arm_schedule=0"
/*
 *record_schedule_list=[]   停止tf卡录像
 *record_schedule_list=[{\"start\":0,\"end\":96,\"day\":127}]   开启录像
 */
录像params："save=1&reinit_record=1&record_schedule_list=[]"
重启params:"reboot=1"
/*
 *IPCamSetParamsDelegate回调函数
 *返回参数：
 *ipcam：返回一个id类型，其实就是一个IPCam
 *IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示设置成功
 */

-(void)on_set_params_result:(id)ipcam
error:(IPCAM_ERROR)error;

4）注意：
    a)这些CGI的参数，不会主动反馈参数的值，如果想要知道此时参数是什么值什么状态，请参考<IPCam的CGI命令设置参数>，有详细介绍cgi
    命令设置参数以及参数值的获取。
    b)CGI命令设置参数是以摄像机连接成功为前提的。

5)示列
/*第一步：cgi设置参数+添加代理IPCamSetParamsDelegate
 */
NSString * params = @"save=1&reinit_alarm=1&arm_schedule=1"; //计划布防cgi
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

#pragma mark  11.无线网络设置
11.无线网络设置

说明：无线网络设置是指：把摄像机设置成连接某一个无线路由器。无线设置分两大类：手机已连接的摄像机的无线网络设置和手机未连接的摄像机无线网络设置。

#pragma mark  －－11.1已连接的摄像机的无线网络设置
11.1已连接的摄像机的无线网络设置
#pragma mark  －－－－11.1web设置无线
11.1web设置无线
1）说明：web设置无线是指通过html实现的，你只需要加载html，其他的都由html实现。它可以实现wifi的选择，保存多个Wi-Fi，增加和删除Wi-Fi。
2）注意：
    1）这个html由reecam提供，需要的可以联系reecam
3)示例：
-(void)set_wifi_from_web
{
    //WebViewController是一个vc,上面增加了一个UIWebView
    WebViewController * vc = [[WebViewController alloc]init];
    [self presentViewController:vc animated:YES completion:nil];
    NSString * url = [NSString stringWithFormat:@"%@/web_app/wifi.html?host=%@&port=%d&ssl=%d&user=%@&pwd=%@&lng=%@&sys=1", [[NSBundle mainBundle] bundlePath],
                      [ipcam ip],
                      [ipcam port],
                      [ipcam https]?1:0,
                      [ipcam user],
                      [Util url_query_value_encode:[ipcam pwd]],
                      [Util check_language]];
    [vc open:url];
}

#pragma mark  －－－－11.2APP设置无线
11.2APP设置无线

说明：无线网络设置包括，扫描周围wifi和设置摄像机wifi功能。
使用类：ipcam
函数：

a）扫描wifi
注意：1）扫描Wi-Fi，是通过摄像机去扫描周围的wifi,不是通过手机扫描，所以使用wifi_scan前必须先
要连接摄像机成功。
     2）使用wifi_scan时，如添加了IPCamWifiScanDelegate，一旦扫描有结果了就会调用on_wifi_scan_result。

/*
 *扫描函数
 *返回：
 *返回IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示wifi_scan执行成功
 */
-(IPCAM_ERROR)wifi_scan:(id<IPCamWifiScanDelegate>)delegate;

/*
 *扫描结果函数回调
 *参数：
 *ipcam：返回一个id类型，其实就是一个IPCam
 *error:IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示scan成功
 *ap_list:wifi信息的一个数组，数组的每一个元素是一个字典，key/value如下：
    bssid:bssid wifi的唯一标示码
    ssid: wifi名称
    rssi:信号强度
    auth:认证方式,共有五种，详细参考下面的IPCAM_WIFI_AUTH
    encrypt:加密方式,共有五种，详细参考下面的IPCAM_WIFI_ENCRYPT
*/
-(void)on_wifi_scan_result:(id)ipcam
error:(IPCAM_ERROR)error
ap_list:(NSArray *)ap_list;

typedef enum {
    IPCAM_WIFI_AUTH_OPEN, //无密码
    IPCAM_WIFI_AUTH_WEP, //WEP
    IPCAM_WIFI_AUTH_WPAPSK, //WPAPSK
    IPCAM_WIFI_AUTH_WPA2PSK, //WPA2PSK
    IPCAM_WIFI_AUTH_UNKNOWN, //unknown
} IPCAM_WIFI_AUTH;

typedef enum {
    IPCAM_WIFI_ENCRYPT_NONE, //无密码
    IPCAM_WIFI_ENCRYPT_WEP, //WEP
    IPCAM_WIFI_ENCRYPT_TKIP,//TKIP
    IPCAM_WIFI_ENCRYPT_AES, //AES
    IPCAM_WIFI_ENCRYPT_UNKNOWN,//未知
} IPCAM_WIFI_ENCRYPT;

b）摄像机无线设置
注意点：
1）函数1和函数2都可以实现设置无线功能。函数1增加了无线测试功能，但是只有当当前摄像机的是有线连接时（即[m_ipcam wifi_power] == 0,wifi信号是0）时，才可以使用。
2）函数2没有无线测试功能，直接设置。不管摄像机当前是有线连接还是无线连接都可以使用。
3）推荐方式，摄像机当前是有线连接时，使用函数1设置。摄像机当前是无线连接时，使用函数2设置。

/*
 *参数：
 *ssid:wifi名称，通过扫描返回
 *auth：认证方式，通过scan扫描返回。当auth是wep时，才要使用wep_key_index，wep_key_type参数，其他认证方式，这两个参数实际上用不着
 *encrypt：加密方式，通过scan扫描返回
 *wep_key_index：wep索引，共有四种，［0，3］。瑞彩处理：强制设置为0索引，其他三个索引就不考虑了
 *wep_key_type:wep类型，共有两种，HEX和ASCII。瑞彩处理：当auth无密码或auth是wep+key的长度是5或13时，把wep_key_type设置为HEX，其他都是ASCII。详细参考下面的IPCAM_WIFI_WEP_KEY_TYPE
 *key：wifi密码
 *delegate:代理IPCamSetWifiDelegate
 */

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

typedef enum {
    IPCAM_WIFI_WEP_KEY_TYPE_HEX, //hex类型
    IPCAM_WIFI_WEP_KEY_TYPE_ASCII, //ASCII类型
} IPCAM_WIFI_WEP_KEY_TYPE;

/*
 *IPCamSetWifiDelegate回调函数 Wi-Fi设置进程
 *参数返回：
 *ipcam：返回一个id类型，其实就是一个IPCam
 *state：设置Wi-Fi的进程，是一个IPCAM_SET_WIFI_STATE类型，详细参考下面的IPCAM_SET_WIFI_STATE
 */
-(void)on_set_wifi_progress:(id)ipcam
state:(IPCAM_SET_WIFI_STATE)state;

typedef enum {
    IPCAM_SET_WIFI_STATE_SETTING, //wifi设置中
    IPCAM_SET_WIFI_STATE_TESTING, //wifi测试中
    IPCAM_SET_WIFI_STATE_SAVING, //wifi保存中
} IPCAM_SET_WIFI_STATE;

/*
 *IPCamSetWifiDelegate回调函数 Wi-Fi设置结果
 *参数返回：
 *ipcam：返回一个id类型，其实就是一个IPCam
 *error：IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示设置wifi成功，返回IPCAM_ERROR_DEVICE_OPERATION_FAIL表示密码错误，其他都是设置失败。 
 */
-(void)on_set_wifi_result:(id)ipcam


步骤：
第一步：扫描wifi
第二步：选择wifi设置无线
第三步：监控无线设置过程和结果

3)示列
/*第一步：扫描Wi-Fi*/
-(void)scan_wifi {
    /*扫描Wi-Fi+添加代理IPCamWifiScanDelegate*/
    if (IPCAM_ERROR_NO_ERROR != [m_ipcam wifi_scan:self]) {
        NSLog(@"Scan wifi fail");
    }
}
/*第二步：扫描结果，IPCamWifiScanDelegate回调 */
-(void)on_wifi_scan_result:(id)ipcam
error:(IPCAM_ERROR)error
ap_list:(NSArray *)ap_list
{
    if (IPCAM_ERROR_NO_ERROR == error && ap_list.count >0 ) {
        m_aps_list = ap_list;
    }
}

/*第三步：设置wifi*/
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
/*第四步：设置wifi进度和结果监控，IPCamSetWifiDelegate回调*/

-(void)on_set_wifi_progress:(id)ipcam
state:(IPCAM_SET_WIFI_STATE)state
{
    switch (state) {
        case IPCAM_SET_WIFI_STATE_SETTING: //Wifi设置中
            NSLog(@"wifi setting!");
            break;
        case IPCAM_SET_WIFI_STATE_TESTING://wifi测试中
            NSLog(@"wifi test!");
            break;
        case IPCAM_SET_WIFI_STATE_SAVING://wifi保存中
            NSLog(@"wifi save");
            break;
        default:
            break;
    }
}

-(void)on_set_wifi_result:(id)ipcam
error:(IPCAM_ERROR)error
{
    if (error == IPCAM_ERROR_NO_ERROR) {
        NSLog(@"Scan wifi success");
    } else if (error == IPCAM_ERROR_DEVICE_OPERATION_FAIL) {
        NSLog(@"wifi key error");
    } else {
        NSLog(@"set wifi fai");
    }
}

#pragma mark  －－11.2未连接的摄像机的无线网络设置
11.2未连接的摄像机的无线网络设置

说明：未连接的摄像机的无线网络设置：是指摄像机未添加到app里，或摄像机添加到app但是未连接成功，在这两种情况下进行的摄像机无线设置。未连接的摄像机的无线网络设置有两种：声音（sound）设置无线网络，smartlink设置无线。这两种方式可以单独使用，也可以同时使用。但同时使用时，一定要注意。当一种方式成功时，一定要记得把另外一种设置方式停止。即smartlinK设置先成功时，要记得把声音（sound）止。当声音（sound）设置先成功时，要记得把smartlink停止。

#pragma mark －－－－11.2.1声音（sound）设置无线
11.2.1声音（sound）设置无线

1）说明：使用声音设置无线就是利用声音传输来设置无线网络。可以实现开始／停止无线网络设置，也可监控无线设置过程和结果。

2）使用类：SoundWaveWifiSetting,Util，IPCamMgr

3）注意点：
    a)SDK初始化成功
    a)系统固件版本为：@"^\\d+.\\d+.\\d+.4.\\d+$"
    b)书写了设备id,且id前缀为@"RTEST-",@"SOSO-",@"RCAM-",@"LSCAM-",@"YSTC-"
    c)手机喇叭是好的
    d)设置成功后返回的id是分两部分编码返回，需查询id是否在局域网，需要先用Util的方法对id进行编码再比较
    e)获取局域网摄像机之前，必须有开启局域网搜索[IPCamMgr get_share]start]。

4）函数：
a）开始声音设置无线
/*
 *SoundWaveWifiSetting开始无线设置
 * 参数如下：
 * ssid:wifi的ssid
 * psk:wifi的密码
 * test:测试无线，默认设置为NO
 * delegate:代理SoundWaveWifiSettingDelegate
 * 返回：
 * 返回一个BOOL值，当返回YES时，表示函数执行成功，否则执行失败。
 */
-(BOOL)start:(NSString *)ssid
psk:(NSString *)psk
test:(BOOL)test
delegate:(id<SoundWaveWifiSettingDelegate>)delegate;//开始声音无线设置

/*
 *SoundWaveWifiSetting无线设置SoundWaveWifiSettingDelegate回调函数
 *开始声音设时，添加了此代理
 *只要声音设置无线状态有改变时候就会调用此函数
 */
-(void)on_sound_wave_wifi_setting_state_changed;

b）停止声音设置无线
/*
 *SoundWaveWifiSetting停止声音设置无线
 *SoundWaveWifiSetting设置成功自动就停止了声音设置，不需要主动去设置停止
 *当退出设置或者smartlink先设置成功就需要主动停止sound设置
 */
-(void)stop;

c）声音设置无线信息获取：
/*
 *SoundWaveWifiSetting声音设置无线结果
 *共有五种结果，详细如下：
 */
-(SOUND_WAVE_WIFI_SETTING_RESULT)result; //声音设置无线结果
typedef enum {
    SOUND_WAVE_WIFI_SETTING_RESULT_SUCCEED, //设置成功
    SOUND_WAVE_WIFI_SETTING_RESULT_TIMEOUT,//设置超时
    SOUND_WAVE_WIFI_SETTING_RESULT_FAILED_JOIN,//JSON解析错误
    SOUND_WAVE_WIFI_SETTING_RESULT_FAILED_BUSY,//网络繁忙
    SOUND_WAVE_WIFI_SETTING_RESULT_FAILED_INTERNAL,//内部出错
} SOUND_WAVE_WIFI_SETTING_RESULT;

/*
 *SoundWaveWifiSetting声音设置无线状态
 *共有五种结果，详细如下：
 */
-(SOUND_WAVE_WIFI_SETTING_STATE)state;//声音设置无线状态
typedef enum {
    SOUND_WAVE_WIFI_SETTING_STATE_IDLE, //设置失败
    SOUND_WAVE_WIFI_SETTING_STATE_SEND_SETTING, //发送声音设置
    SOUND_WAVE_WIFI_SETTING_STATE_WAIT_CONFIRM,//等待信息确认
    SOUND_WAVE_WIFI_SETTING_STATE_WAIT_RESULT,//等待设置结果
    SOUND_WAVE_WIFI_SETTING_STATE_SEND_CONFIRM,//发送确认信息
} SOUND_WAVE_WIFI_SETTING_STATE;

d) 查询ID是否在局域网里
/*
 *设置成功后，查询id是否在局域网内，通过和局域网的摄像机比较id知晓
 *因为id太长，摄像机传不过来，所以把id编码分成name_of_camera_id和serial_of_camera_id来传
 *比较的时候，先把局域网的id通过get_name_of_camera_id和get_serial_of_camera_id编码再来一一比较
 */

/*
 *SoundWaveWifiSetting&Util编码id
 *id太长，分成两部分编码，比较的时候
 *SoundWaveWifiSetting的name_of_camera_id和Util的get_name_of_camera_id比较
 *SoundWaveWifiSetting的serial_of_camera_id和Util的get_serial_of_camera_id比较
 */
-(int)name_of_camera_id; //SoundWaveWifiSetting设置成功，返回编码的id

-(int)serial_of_camera_id; //SoundWaveWifiSetting设置成功，返回编码的id

+(int)get_name_of_camera_id:(NSString *)camera_id; //Util编码id

+(int)get_serial_of_camera_id:(NSString *)camera_id; //Util编码id

5）步骤：
第一步：创建SoundWaveWifiSetting对象。
第二步：开始sound无线设置
第三步：实时监控sound的无线设置状态和结果
第四步：设置成功后，获取摄像机的id和局域网内的摄像机一一比较，确认是否成功设置，摄像机是否再局域网了

6）示列：
/*
 第一步：创建一个SoundWaveWifiSetting对象
 */
SoundWaveWifiSetting * m_sound_wifi_setting = [[SoundWaveWifiSetting alloc] init];

/*
 *第二步：开始无线声音设置＋ 添加代理SoundWaveWifiSettingDelegate
 */
-(void)startSound{
    BOOL  m_sound_wifi = [m_sound_wifi_setting start:m_ssid psk:m_text_input.text test:NO delegate:self];
    if (! m_sound_wifi){
        [self show_error:LOCAL_STR(@"SEND_WIFI_INFO_FAIL")];
    }
}

/*
 *第二步：监控声音设置无线的过程和结果
 */
-(void)on_sound_wave_wifi_setting_state_changed {
    SOUND_WAVE_WIFI_SETTING_STATE state = [m_sound_wifi_setting state];
    SOUND_WAVE_WIFI_SETTING_RESULT result = [m_sound_wifi_setting result];
    NSLog(@"SOUND_WAVE_WIFI_SETTING_STATE = %u SOUND_WAVE_WIFI_SETTING_RESULT = %u",state,result);
    if (result == SOUND_WAVE_WIFI_SETTING_RESULT_SUCCEED){
        [self discover];//设置成功开始在局域网查询
    }
}

/*
 *第三步：设置成功后，获取id,查询id是否在局域网内 */
-(void)discover{
    /*获取局域网的摄像机，必须前面有开始局域网搜索[IPCamMgr get_share]start];*/
    NSArray * cameras_list = [[IPCamMgr get_share] get_discovered_cameras_list]; //局域网内的摄像机
    int i;
    NSString * camera_id;
    int camera_id_name;
    int camera_id_serial;
    NSDictionary * camera;
    for (i = 0;i < cameras_list.count;i ++) {
        camera =  [cameras_list objectAtIndex:i];
        camera_id = [camera objectForKey:@"camera_id"];
        /*对局域网的摄像机id进行编码*/
        camera_id_name = [Util get_name_of_camera_id:camera_id];
        camera_id_serial = [Util get_serial_of_camera_id:camera_id];
        /*比较id,查id是否在局域网内*/
        if (camera_id_name == [m_sound_wifi_setting name_of_camera_id] &&
            camera_id_serial == [m_sound_wifi_setting serial_of_camera_id]) {
            /*查询id在局域网里，可以进行下一步操作，比如添加摄像机*/
            NSLog(@"camera id is :%@",camera_id);
        }
    }
}
/*第四步：不需要了，强制取消SoundWaveWifisetting设置。设置成功了，不需要做停止的的操作*/
    [m_sound_wifi_setting stop];
    
#pragma mark －－－－11.2.2.smartlink设置无线网络
11.2.2.smartlink设置无线网络

说明：smartlink设置无线网络是指通过手机广播一个UDP数据包,包中放置SSID跟密码等信息。摄像机接收到该包，解析后，获得
SSID和密码等数据，就可以配置自己，连接路由器了。smartlink设置无线包括开始／停止smartlink设置和smartlink设置成功返回摄像机id。

使用的类：smartlink
注意点：
    a)SDK初始化成功
    b)系统固件版本为：@"^\\d+.\\d+.\\d+.4.\\d+$"
    c)书写了设备id,且id前缀为@"RTEST-",@"SOSO-",@"RCAM-",@"LSCAM-",@"YSTC-"
函数：
/*
 *开始smartlink设置
 *参数如下：
 *ssid:wifi的ssid
 *psk:wifi的密码
 *delegate:WiFiMatchingDelegate代理
 * 返回：
 * 返回一个BOOL值，当返回YES时，表示函数执行成功，否则执行失败。
 */
-(BOOL)start:(NSString *)ssid
psk:(NSString *)psk
delegate:(id<WiFiMatchingDelegate>)delegate;

/*
 *smartlink设置代理WiFiMatchingDelegate的回调函数
 *开始smartlink设置时时，添加了此代理
 *当smartlink设置无线成功后就会调用此函数且返回成功摄像机的id,其他时候不会掉用此函数
 *参数：smartlink设置成功后，返回一个id
 *camera_id:摄像机id
 */
-(void)on_wifi_matching_succeed:(NSString *)camera_id;

/*
 *smartlink停止设置无线
 *smartlink设置成功自动就停止了设置，不需要主动去设置停止
 *当退出设置或者SoundWaveWifiSetting先设置成功就需要主动停止sound设置
 */
-(void)stop;

步骤：
第一步：创建WiFiMatching对象
第二步：开始smartlink设置且添加代理WiFiMatchingDelegate
第三步：如果smartlink设置成功了且前面添加了代理WiFiMatchingDelegate回调代理，传递id

3）示列：
/*
 *第一步：创建一个WiFiMatching对象
 */
WiFiMatching * m_wifi_match = [[WiFiMatching alloc]init];

/*
 *第二步：发送smartlink 添加代理WiFiMatchingDelegate
 */
-(void)startSmartlink{
    BOOL  m_smart_link = [m_wifi_match start:m_ssid psk:m_text_input.text delegate:self];
    if (! m_smart_link){
        [self show_error:LOCAL_STR(@"SEND_WIFI_INFO_FAIL")];
    }
}

/*
 *第三步：WiFiMatchingDelegate代理回调
 */
-(void)on_wifi_matching_succeed:(NSString *)camera_id{
    if (camera_id) {
        /*设置成功获取到id,可以进行下一步操作，比如添加摄像机*/
        NSLog(@"smartlink设置成功, camera_id= %@",camera_id);
    }
}

/*
*第四步：不需要了，强制取消smartlink设置，设置成功了，不需要做停止的的操作
*/
[m_wifi_match stop];


#pragma mark 12 摄像机本地录像和拍照文件管理<本地录像和图片获取／删除／导出到系统相册>

12 摄像机本地录像和拍照文件管理

1）说明：摄像机本地录像和拍照文件管理是指把存储到本地的录像和拍照文件获取出来，导出到系统相册以及删除等操作。

2）使用类：storage,Util

3）注意：以下介绍的文件的获取和删除都是基于保存方式是使用瑞彩的方式保存的，即保存路径不是自己定义的。

4）函数：
a)获取本地录像和图片

/*
 *storage方法:获取本地录像和图片
 *参数:
 *camera_id:摄像机id
 *返回:返回一个NSMutableArray，数组的每一个元素是一个字典，字典的key/value如下:
 *time/NSDate *    //时间NSDate
 *size/NSNumber * /long long  // 文件大小
 *type/NSNumber * /int //文件类型，两个值，0:图片 1:录像
 *path/NSString *    //文件路径
 */
-(NSMutableArray *)get_album:(NSString *)camera_id;

示例1：
NSArray * album = [storage get_album:[ipcam camera_id]];

b）删除文件
/*
 *storage方法：删除指定摄像机的所有的录像和拍照文件
 *参数：camera_id:摄像机id
 */
-(void)remove_album:(NSString *)camera_id;//删除所有文件

/*
 *storage方法：删除指定摄像机的指定的录像或拍照文件
 *参数：path:文件路径
 */
-(void)remove_album_item:(NSString *)path; //删除某一个文件

示例2：

[[Storage get_share] remove_album:[ipcam camera_id]];//删除所有文件

[[Storage get_share] remove_album_item:[item objectForKey:@"path"]];//删除某一个文件

c)导出文件
/*
 *Util方法：把图片从document导出到系统相册
 *参数：
 *picture_path:图片路径
 */
+(void)save_picture_to_system_album:(NSString *)picture_path//导出图片
/*
 *Util方法：把录像从document导出到系统相册
 *参数：
 *clip_path:录像路径
 */
+(void)save_clip_to_system_album:(NSString *)clip_path //导出录像

示例3：
-(void)on_button_export_clicked:(int)index
{
    NSDictionary * item = [m_album objectAtIndex:index];
    if (item) {
        if ([[item objectForKey:@"type"] intValue] == MEDIA_CLIP) {
            [Util save_clip_to_system_album:[item objectForKey:@"path"]]; //导出录像
        } else {
            [Util save_picture_to_system_album:[item objectForKey:@"path"]];//导出图片
        }
    }
}

#pragma mark 13 推送的实现
13 推送的实现

说明：推送的实现是基于Jpush上实现的，相关lib和使用请参考jpush官方文档。这里主要介绍settag瑞彩服务器部分。瑞彩实现推送两种方式，一种是以账号为id来settag,另外是以摄像机为id来settag。
#pragma mark --13.1以账号为id来settag(使用了平台功能)
13.1以账号为id来settag

1）说明：以账号为id来settag是指：使用账号登陆，以账号为标记码，对账号里的摄像机进行推送总管理，只要账号settag成功，账号里所有摄像机就可以收到推送消息。这种方式，优点是：实现简单，只要使用的时候，以账号为id来settag一次就可以，不需要推送时，以@""为id来settag。账号里删除添加了摄像机瑞彩服务器会处理，客户端这边不需要任何处理。缺点是：必须使用服务器平台管理摄像机，即用账号登陆服务器。

2）使用的类：APService [jpush的类]
3）函数：
/*
 *APService方法
 *此接口为jpush提供，不是瑞彩提供
 *每一个参数说明请查阅jpush官方文档
 *此方法的tags为账号登陆成功后，服务器返回的账号的“user_id”
 */
+ (void)setTags:(NSSet *)tags
alias:(NSString *)alias
callbackSelector:(SEL)cbSelector
target:(id)theTarget;

4）步骤：
第一步：在jpush上创建应用后，把应用的AppKey和Master Secret提供给瑞彩，瑞彩需要添加到服务器，才可测试使用。
第二步：客户端实现推送。

5）注意：1）setTags的tags不是账号，而是账号登陆成功后，服务器返回的账号的“user_id”
        2)通过这种方式实现推送，一个摄像机只能添加到一个账号，所以添加摄像机的时候需要注意，如果摄像机被注册
了也就是被其他账号添加了，需要先解绑unregister,再添加。［详细参考：摄像机的添加］
        3）通过这种方式实现推送的，摄像机必须要登陆SOSO服务器平台成功，所以添加摄像机的时候需要注意，添加摄像机成功后，需要relogin_to_sosocam，登陆服务器。［详细参考：摄像机的添加］
        4)ios在测试推送的时候，jpush选择的开发或生产环境无效，先处于什么环境，以服务器当前设置为准（即需要瑞彩来设置当前环境）
6）示例：
/*这里只介绍setTags部分，其他部分请参考jpush官方文档*/

[self set_jpush_tag:[user objectForKey:@"user_id"]]; //注册账号，需要推送
[self set_jpush_tag:[user objectForKey:@""]]; //反注册账号，不需要推送了

- (void)set_jpush_tag:(NSString *)tag {
    NSSet * set;
    if ([tag isEqualToString:@""])
        set = [NSSet set];
    else
        set = [NSSet setWithObject:tag];
            
    [APService setTags: [APService filterValidTags: set ] alias:@"" callbackSelector:@selector(tagsAliasCallback:tags:alias:) target:self];
}
-(void)tagsAliasCallback:(int)iResCode
tags:(NSSet*)tags
alias:(NSString*)alias
{
    NSLog(@"%s: result %d\n", __func__, iResCode);
    if( iResCode == 6002 ) {
        [APService setTags:tags alias:alias callbackSelector:@selector(tagsAliasCallback:tags:alias:) target:self];
    }
}
#pragma mark --13.2以摄像机为id来settag(未使用平台功能)
13.2以摄像机为id来settag
1）说明：以摄像机为id来settag是指：使摄像机为标记码，对摄像机进行单个推送管理，那一台摄像机settag成功，哪一台摄像机就可以收到推送消息。这种方式，优点是：只要本地管理摄像机就好，不需要用到服务器平台管理摄像机。缺点是：实现比较复杂，只要使用的时候，以摄像机为id来一个一个settag，需要推送时，以@""为id来settag。账号里删除添加了摄像机，客户端这边都需要重新把本地的摄像机一个一个settag。

2）使用类：Util和APService [jpush的类]

3）函数：
/*
 *APService方法
 *此接口为jpush提供，不是瑞彩提供
 *每一个参数说明请查阅jpush官方文档
 *此方法的tags为摄像机id，id需要编码
 */
+ (void)setTags:(NSSet *)tags
alias:(NSString *)alias
callbackSelector:(SEL)cbSelector
target:(id)theTarget;
APService [jpush的类]
/*
 *Util方法
 *对摄像机id进行编码
 */
+(NSString *)encodeTag:(NSString*)camID;

4）步骤：
第一步：在jpush上创建应用后，把应用的AppKey和Master Secret提供给瑞彩，瑞彩需要添加到服务器，才可测试使用。
第二步：客户端实现推送。

注意：1）setTags的tags是摄像机id，但是必须先把id通过encodeTag编码，才去settags。
     2）通过这种方式实现推送的推送，摄像机的推送地址必须要是正确的，具体的请联系瑞彩
     3)ios在测试推送的时候，jpush选择的开发或生产环境无效，先处于什么环境，以服务器当前设置为准（即需要瑞彩来设置当前环境）
                                                                                    
5）示例：
/*这里只介绍setTags部分，其他部分请参考jpush官方文档*/

NSMutableSet * set = [[NSMutableSet alloc]init];
[set addObject:[Util encodeTag:[camera_list[i] objectForKey@"camera_id"]]];//把摄像机一个个添加到set
[self set_jpush_tag:set]; //注册所有摄像机，需要推送
[self set_jpush_tag:nil]; //反注册，不需要推送了


- (void)set_jpush_tag:(NSMutableSet *)tag {
    [APService setTags: [APService filterValidTags: set ] alias:@"" callbackSelector:@selector(tagsAliasCallback:tags:alias:) target:self];
}
-(void)tagsAliasCallback:(int)iResCode
tags:(NSSet*)tags
alias:(NSString*)alias
{
    NSLog(@"%s: result %d\n", __func__, iResCode);
    if( iResCode == 6002 ) {
        [APService setTags:tags alias:alias callbackSelector:@selector(tagsAliasCallback:tags:alias:) target:self];
    }
}

#pragma mark 14.登陆实现
参考WebService的用户管理 <注册／忘记密码／登录／激活／账号信息>

#pragma mark 15.报警信息
15.报警信息
说明：报警信息是指摄像机或连接到摄像机的外部设备发生报警，像服务器推送的报警信息（包括图片，报警类型）。这些信息保存在服务器，保留7天的报警信息，最多300张图片，100条报警信息（一条报警信息最多最多有5张图片）。

#pragma mark －－15.1 获取当前账号内所有摄像机的报警信息
15.1 获取当前账号内所有摄像机的报警信息

1）说明：获取当前账号内所有摄像机的报警信息是指：获取当前账号所有摄像机（不管有没有报警）的id,sosocam_id以及各个报警摄像机报警总数目和已查看的报警信息数目。

2）使用类：WebService

3）函数：
/*
 *WebService方法:获取当前账号所有摄像机的报警信息
 *返回：返回WEBSERVICE_ERROR类型，如果不是返回WEBSERVICE_ERROR_NO_ERROR 说明获取失败
 */
-(WEBSERVICE_ERROR)get_alarm_cameras_list:(id<WebServiceGetAlarmCamerasListDelegate>)delegate;

/*
 *WebService方法:WebServiceGetAlarmCamerasListDelegate代理回调
 *回调参数：
 *error:WEBSERVICE_ERROR类型，error == WEBSERVICE_ERROR_NO_ERROR表示获取成功
 *alarm_cameras_list:报警信息列表数组，数组的每个元素是一个NSDictionary，key/value如下：
 *  sosocam_camera_id:摄像机sosocam_id,/NSString *
 *  camera_id:摄像机id,类型NSString *
 *  unread:已查看报警数目，类型NSNumber
 *  total:报警总数目，类型NSNumber
 */
-(void)on_get_alarm_cameras_list_result:(WEBSERVICE_ERROR)error
alarm_cameras_list:(NSArray *)alarm_cameras_list;

4）步骤：
第一步：获取当前账号内所有摄像机的报警信息，且添加WebServiceGetAlarmCamerasListDelegate代理
第二步：WebServiceGetAlarmCamerasListDelegate回调，取得信息

4）注意：1）此操作必须以成功登陆账号（服务器）为前提

5）示例：

/*第一步：获取当前账号内所有摄像机的报警信息 + 添加WebServiceGetAlarmCamerasListDelegate代理*/
-(void)get_all_camera_alarm_info{
    if(WEBSERVICE_ERROR_NO_ERROR != [[WebService get_share] get_alarm_cameras_list:self]){
        /*
         *获取失败
         */
    }
}

/*第二步：WebServiceGetAlarmCamerasListDelegate回调*/
-(void)on_get_alarm_cameras_list_result:(WEBSERVICE_ERROR)error
alarm_cameras_list:(NSArray *)alarm_cameras_list
{
    NSMutableDictionary * camera;
    NSDictionary * server_camera;
    if (error == WEBSERVICE_ERROR_NO_ERROR) {
        //获取到结果后就会掉用代理，当代理中返回error == WEBSERVICE_ERROR_NO_ERROR表示获取成功
        int i, j;
        for (i = 0;i < m_cameras_list.count;i ++) {
            camera = [m_cameras_list objectAtIndex:i];//m_cameras_list从storage获取
            for (j = 0;j < alarm_cameras_list.count;j ++) {
                server_camera = [alarm_cameras_list objectAtIndex:j];
                NSString *alarm_id = [server_camera objectForKey:@"camera_id"];
                NSString * alarm_sosocam_id = [server_camera objectForKey:@"sosocam_camera_id"];
                NSString * alarm_total = [server_camera objectForKey:@"total"];
                NSString * alarm_unread = [server_camera objectForKey:@"unread"];
            }
        }
    }
}
#pragma mark －－15.2 获取单个cam报警信息
15.2 获取单个cam报警信息

1）说明：获取单个cam报警信息是指：获取当前账号某一个摄像机的报警信息，包括每一条报警信息的类型，id,图片数目，报警时间，预览图和查看状态。

2）使用类：WebService

3）函数
/*
 *WebService方法:获取摄像机详细报警信息
 *参数：
 *sosocam_camera_id：摄像机sosocam_id
 *delegate:WebServiceGetCameraAlarmsListDelegate代理
 */
-(WEBSERVICE_ERROR)get_camera_alarms_list:(NSString *)sosocam_camera_id
delegate:(id<WebServiceGetCameraAlarmsListDelegate>)delegate;

/*
 *WebService方法:WebServiceGetCameraAlarmsListDelegate回调
 *回调参数：
 *error:WEBSERVICE_ERROR类型，error == WEBSERVICE_ERROR_NO_ERROR表示获取成功
 *camera_alarms_list:摄像机的报警信息列表，数组的每个元素是一个NSDictionary也就是一条报警信息，
 *key/value如下：
 *alarm_id:报警id，类型NSString
 *alarm_type:报警类型，类型NSNumber(int32_t)
 *image_numbers：图片数量，类型NSNumber(int)
 *read：查看状态，类型NSNumber(BOOL)
 *time：报警时间，类型NSDate
 *thumb_url：预览图URL，类型NSString
 */
-(void)on_get_camera_alarms_list_result:(WEBSERVICE_ERROR)error
                     camera_alarms_list:(NSArray *)camera_alarms_list;

4）步骤：
第一步：获取当前账号内当前摄像机的报警信息，且添加WebServiceGetCameraAlarmsListDelegate代理
第二步：WebServiceGetCameraAlarmsListDelegate回调，取得信息

5）注意：a)以摄像机登陆成功为前提

6）示例：

/*第一步：获取当前账号内当前摄像机的报警信息+添加WebServiceGetCameraAlarmsListDelegate代理*/
-(void)get_camera_all_alarm_info{
    if (WEBSERVICE_ERROR_NO_ERROR != [[WebService get_share] get_camera_alarms_list:m_sosocam_camera_id delegate:self]) {
        /*获取失败*/
    }
}

/*第二步:WebServiceGetCameraAlarmsListDelegate回调*/
-(void)on_get_camera_alarms_list_result:(WEBSERVICE_ERROR)error
camera_alarms_list:(NSArray *)camera_alarms_list{
    if (error == WEBSERVICE_ERROR_NO_ERROR){
        /*在此处把改摄像机的每一条包报警信息取出*/
    }
}

#pragma mark －－15.3 获取某一条报警的图片信息
15.3 获取某一条报警的图片信息
1）说明：获取某一条报警的图片信息是指，获取某摄像机的某一条报警信息的图片信息。包括报警信息的每一张图片的url和时间，index和data。

2）使用类：WebService

3）函数：
/*
 *WebService方法:获取某一条报警的图片信息
 *参数：
 *alarm_id：报警id
 *delegate:WebServiceGetAlarmImagesListDelegate代理
 */
-(WEBSERVICE_ERROR)get_alarm_images_list:(NSString *)alarm_id
                                delegate:(id<WebServiceGetAlarmImagesListDelegate>)delegate;
/*
 *WebService方法:WebServiceGetAlarmImagesListDelegate回调
 *回调参数:
 *error:WEBSERVICE_ERROR类型，error == WEBSERVICE_ERROR_NO_ERROR表示获取成功
 *alarm_images_list:摄像机报警图片数组列表，数组的每一个元素是一个字典，key/value如下：
 *time：报警时间，类型NSDate
 *url:图片URL，类型NSString
 */
-(void)on_get_alarm_images_list_result:(WEBSERVICE_ERROR)error
                     alarm_images_list:(NSArray *)alarm_images_list;

/*
 *WebService方法:取消获取单个摄像机所有报警图片，即停止get_alarm_images_list
 */
-(void)cancel_get_alarm_images_list_tasks;

/*
 *WebService方法:获取单个摄像机的其中一条报警信息的图片
 *参数：
 *image_id:取intValue,取当前报警信息中的第几张照片，最多是5张，通过image_numbers可知
 *url:报警信息的图片URL
 *delegate:代理WebServiceGetImageDelegate
 */
-(void)get_alarm_image:(NSString *)image_id
                   url:(NSString *)url
              delegate:(id<WebServiceGetImageDelegate>)delegate;

/*
 *WebService方法:WebServiceGetImageDelegate回调
 *回调参数：
 *image_id:当前照片的index值
 *data:获取到的图片data数据
 */
-(void)on_get_image_result:(NSString *)image_id
                      data:(NSData *)data;

/*
 *WebService方法:取消获取单个摄像机某一条报警信息,即停止get_alarm_image
 */
-(void)cancel_get_alarm_image_tasks;

4）步骤：
第一步：通过get_alarm_images_list获取图片的时间和url
第二步：使用WebServiceGetAlarmImagesListDelegate回调来的url，通过get_alarm_image获取图片data数据

5）注意：
    a)get_alarm_images_list需要的参数alarm_id是通过get_camera_alarms_list获取到的。
    b)get_alarm_image需要的参数image_id,已定是通过get_camera_alarms_list获取到的image_numbers范围内
    c)get_alarm_images_list和get_camera_alarms_list都是异步的，所以不宜要的时候，一定要cancel_get_alarm_images_list_tasks和cancel_get_alarm_image_tasks

6）示例：
/*第一步：通过get_alarm_images_list获取图片的时间和url*/
[[WebService get_share] get_alarm_images_list:[alarm objectForKey:@"alarm_id"] delegate:self];

/*第二步：WebServiceGetAlarmImagesListDelegate回调＋get_alarm_image*/
-(void)on_get_alarm_images_list_result:(WEBSERVICE_ERROR)error
alarm_images_list:(NSArray *)alarm_images_list{
    if (error == WEBSERVICE_ERROR_NO_ERROR) {
        if (alarm_images_list.count > 0){
            for (i = 0;i < m_images_number;i ++){
            [[WebService get_share] get_alarm_image:[NSString stringWithFormat:@"%d", i] url:[alarm_images_list objectAtIndex:0] objectForKey:@"url"] delegate:self];
            }
        }
    }
}
/*第三步：WebServiceGetImageDelegate回调*/
-(void)on_get_image_result:(NSString *)image_id
data:(NSData *)data{
    
}

/*第四步:不需要的时候要手动取消*/
[[WebService get_share] cancel_get_alarm_images_list_tasks];
[[WebService get_share] cancel_get_alarm_image_tasks];

#pragma mark －－15.4 报警图片缓存
15.4 报警图片缓存

1)说明：报警图片本地缓存是指：把图片picture保存缓存在本地，路径是NSTemporaryDirectory而不是NSHomeDirectory

2)使用的类：Storage

3)函数：
/*
 *Storage方法：添加图片到缓存
 *参数：
 *camera_id:摄像机id
 *alarm_id:报警信息id
 *index:第几张图片
 *picture:图片数据
 */
-(void)add_alarm_picture:(NSString *)camera_id
alarm_id:(NSString *)alarm_id
index:(int)index
picture:(NSData *)picture;

/*
 *Storage方法：从缓存中取出图片
 *参数：
 *camera_id:摄像机id
 *alarm_id:报警信息id
 *index:第几张图片
 */
-(NSData *)get_alarm_picture:(NSString *)camera_id
alarm_id:(NSString *)alarm_id
index:(int)index;

4)注意：a)添加的时候，必须要设置了当前账号，因为缓存路径包括账号
       b)index,最大是4，有两种获取方法，on_get_image_result返回的image_id和get_alarm_images_list的image_number数量逐一获取。
       c)alarm_id通过on_get_camera_alarms_list_result返回的alarm_id得到

5)示例：
[[Storage get_share] add_alarm_picture:m_camera_id alarm_id:m_alarm_id index:index picture:data];

15.5报警图片导出

1)说明：报警图片导出：就是把缓存的报警图片或者从服务器下载的图片保存到本地系统相册

2)使用类：Util

3)函数：
/*
 *Util方法：报警图片导出
 *参数：
 *picture_data:图片数据信息
 */
+(void)save_picture_data_to_system_album:(NSData *)picture_data

4）示例：
    [Util save_picture_data_to_system_album:data];


#pragma mark 16.分享和收藏
16.分享和收藏

#pragma mark －－16.1开启分享
16.1开启分享
1）说明：开启分享是指：把摄像机的分享功能打开，摄像机的分享功能打开后，就会生成分享id,url QRcode，你可以通过这些收藏访问这台摄像机。

2）使用的类：WebService，IPCam

3）函数：
/*
 *WebService方法：开启分享
 *参数：
 *sosocam_camera_id:摄像机sosocam_id
 *delegate:代理WebServiceShareCameraDelegate
 */
-(WEBSERVICE_ERROR)share_camera:(NSString *)sosocam_camera_id
delegate:(id<WebServiceShareCameraDelegate>)delegate;

/*
 *WebService方法：WebServiceShareCameraDelegate回调
 *参数：
 *error:错误值，当错误值为IPCAM_ERROR_NO_ERROR时，说明开启分享成功
 *share_id:分享的id
 *share_url:分享的url
 *share_qrcode:分享的二维码
 */
-(void)on_share_camera_result:(WEBSERVICE_ERROR)error
share_id:(NSString *)share_id
share_url:(NSString *)share_url
share_qrcode:(NSString *)share_qrcode;

/*
 *IPCam方法：CGI设置参数
 *参数：
 *params:cgi参数，由reecam提供，开启分享是@"save=1&reinit_guest=1&group2=1"
 *params:IPCamSetParamsDelegate代理，可以监控cgi设置的结果
 */
-(IPCAM_ERROR)set_params:(NSString *)params
delegate:(id<IPCamSetParamsDelegate>)delegate;

/*
 *IPCam方法：IPCamSetParamsDelegate回调函数
 *返回参数：
 *ipcam：返回一个id类型，其实就是一个IPCam
 *IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示设置成功
 */
-(void)on_set_params_result:(id)ipcam
error:(IPCAM_ERROR)error;

4）步骤：
第一步：开启分享，添加代理WebServiceShareCameraDelegate。
第二步：开启分享成果后，用cgi设置权限，且添加代理IPCamSetParamsDelegate。
第三步：IPCamSetParamsDelegate回调

5）注意：a）开启分享音频也是用set_params，params为@"save=1&reinit_guest=1&group2=9"
        b）关闭分享音频也是用set_params，params为@"save=1&reinit_guest=1&group2=1"
        c)设置分享的密码也是用set_params，params为@"save=1&reinit_guest=1&pwd2=%@"
        d)这些设置必须是以摄像机连接成功为前提

6）示例：
/*第一步:开启分享，添加代理WebServiceShareCameraDelegate*/
-(void)share_camera{
    if (WEBSERVICE_ERROR_NO_ERROR != [[WebService get_share] share_camera:[m_ipcam sosocam_id] delegate:self]){
        /*开启分享失败*/
    }
}

/*第二步：开启分享成果后，用cgi设置权限，且添加代理IPCamSetParamsDelegate。*/
-(void)on_share_camera_result:(WEBSERVICE_ERROR)error
share_id:(NSString *)share_id
share_url:(NSString *)share_url
share_qrcode:(NSString *)share_qrcode
{
    if (error == WEBSERVICE_ERROR_NO_ERROR) {
        if (IPCAM_ERROR_NO_ERROR != [m_ipcam set_params:@"save=1&reinit_guest=1&group2=1" delegate:self]) {
            /*开启分享失败*/
        }
    } else {
        /*开启分享失败*/
    }
}
/*第三步：IPCamSetParamsDelegate回调*/
-(void)on_set_params_result:(id)ipcam
error:(IPCAM_ERROR)error {
    if (error == IPCAM_ERROR_NO_ERROR) {
        /*设置成功*/
    } else {
        /*设置失败*/
    }
}
#pragma mark －－16.2关闭分享
16.2关闭分享
1)说明：关闭分享是指：关闭摄像机的分享功能，摄像机的分享功能一旦关闭，id,url QRcode就会变成无效，你不可以通过这些id,url QRcode来访问摄像机了。
2)使用的类：WebService
    
3)函数：
/*
 *WebService方法：关闭分享
 *参数：
 *sosocam_camera_id:摄像机sosocam_id
 *delegate：代理WebServiceDisshareCameraDelegate
 */
-(WEBSERVICE_ERROR)disshare_camera:(NSString *)sosocam_camera_id
delegate:(id<WebServiceDisshareCameraDelegate>)delegate;
/*
 *WebService方法：WebServiceDisshareCameraDelegate回掉
 *参数：
 *error:错误值，当错误值为IPCAM_ERROR_NO_ERROR时，说明开启分享成功
 */
-(void)on_disshare_camera_result:(WEBSERVICE_ERROR)error;

/*
 *IPCam方法：CGI设置参数
 *参数：
 *params:cgi参数，由reecam提供，开启分享是@"save=1&reinit_guest=1&group2=0"
 *params:IPCamSetParamsDelegate代理，可以监控cgi设置的结果
 */
-(IPCAM_ERROR)set_params:(NSString *)params
delegate:(id<IPCamSetParamsDelegate>)delegate;

/*
 *IPCam方法：IPCamSetParamsDelegate回调函数
 *返回参数：
 *ipcam：返回一个id类型，其实就是一个IPCam
 *IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示设置成功
 */
-(void)on_set_params_result:(id)ipcam
error:(IPCAM_ERROR)error;

4）步骤
第一步：关闭分享，添加代理WebServiceDisshareCameraDelegate。
第二步：关闭分享成果后，用cgi设置权限，且添加代理IPCamSetParamsDelegate。
第三步：IPCamSetParamsDelegate回调

5）注意：a)这些设置必须是以摄像机连接成功为前提

6）示例：

-(void)share_camera{
    if (WEBSERVICE_ERROR_NO_ERROR != [[WebService get_share] disshare_camera:[m_ipcam sosocam_id] delegate:self]){
        /*关闭分享失败*/
    }
}

-(void)on_disshare_camera_result:(WEBSERVICE_ERROR)error
{
    if (error == WEBSERVICE_ERROR_NO_ERROR) {
        if (IPCAM_ERROR_NO_ERROR != [m_ipcam set_params:@"save=1&reinit_guest=1&group2=0" delegate:self]) {
            /*关闭分享失败*/
        }
    } else {
        /*关闭分享失败*/
    }
}

-(void)on_set_params_result:(id)ipcam
error:(IPCAM_ERROR)error {
    if (error == IPCAM_ERROR_NO_ERROR) {
        /*设置成功*/
    } else {
        /*设置失败*/
    }
}
#pragma mark －－16.3分享状态获取
16.3分享状态获取
1）说明：分享状态获取，是指摄像机有没有开启分享，有没有开启音频分享，有没有设置分享密码。这些状态的获取是用过get_params来实现的

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

4）步骤：
第一步：获取参数，且添加代理IPCamGetParamsDelegate
第二步：根据IPCamGetParamsDelegate结果判断状态

5）注意：a)这些设置是以摄像机连接成功为前提
        b)摄像机分享信息状态的获取，params为@"group2=&pwd2="

6）示例：
/*第一步：获取参数＋添加代理IPCamGetParamsDelegate*/
-(void)get_share_info{
    if (IPCAM_ERROR_NO_ERROR != [m_ipcam get_params:@"group2=&pwd2=" delegate:self]){
        /*获取分享信息失败*/
    }
}
/*第二步：根据IPCamGetParamsDelegate结果判断状态*/
-(void)on_get_params_result:(id)ipcam
error:(IPCAM_ERROR)error
params:(NSDictionary *)params
{
    if (error == IPCAM_ERROR_NO_ERROR) {
        /*获取分享信息成功*/
        NSNumber * group2 = [params objectForKey:@"group2"];
        NSString * pwd2 = [params objectForKey:@"pwd2"];
        if (! group2 || ! pwd2) {
            /*获取分享信息失败*/
        }
        int m_group = [group2 intValue];
        BOOL m_have_pwd = ! [pwd2 isEqualToString:@""];
        if (0 >= m_group) {
            m_group = 0;
           /*分享状态为：关闭*/
        } else {
            /*分享状态为：开启*/
            if (((m_group >> 3) & 0x01) == 1)
                /*分享音频状态为：开*/
            else
                /*分享音频状态为：关闭*/

            if (m_have_pwd)
                /*分享密码：有密码*/
            else
                /*分享密码：无密码*/

        }
    } else {
        /*获取分享信息失败*/
    }
}

#pragma mark －－16.4添加收藏摄像机
16.4添加收藏摄像机
1)说明：添加收藏摄像机是指添加别人分享的摄像机到你的账号（服务器）或者本地（离线使用）。只要摄像机被分享了，就可以被多个人（账号）添加。但是一旦摄像机的分享功能被关闭了，你就无法获取到分享摄像机信息。

2）使用的类：Storage，WebService

3）函数：
/*
 *Storage方法：添加收藏到本地
 *参数：
 *share_id：分享id
 *alias：昵称
 *cover_url：预览图url
 *返回:
 *返回一个BOOL值，YES:添加收藏到本地成功。NO:添加收藏到本地失败
 */
-(BOOL)add_collection:(NSString *)share_id
alias:(NSString *)alias
cover_url:(NSString *)cover_url;

/*
 *WebService方法:获取收藏摄像机信息
 *参数：
 *share_id：分享id
 *delegate:WebServiceGetCollectionDelegate代理
 */
-(WEBSERVICE_ERROR)get_collection:(NSString *)share_id
delegate:(id<WebServiceGetCollectionDelegate>)delegate;

/*
 *WebService方法:WebServiceGetCollectionDelegate代理回调
 *参数：
 *error:错误值，当错误值为WEBSERVICE_ERROR_NO_ERROR时，说明开启分享成功
 *alias:摄像机别名
 *cover_url：摄像机预览图
 */
-(void)on_get_collection_result:(WEBSERVICE_ERROR)error
alias:(NSString *)alias
cover_url:(NSString *)cover_url;

/*
 *WebService方法:账号添加分享的摄像机：即添加到服务器和本地
 *参数：
 *share_id:摄像机分享id号
 *delegate：代理WebServiceAddCollectionDelegate
 */
-(WEBSERVICE_ERROR)add_collection:(NSString *)share_id
delegate:(id<WebServiceAddCollectionDelegate>)delegate;

/*
 *WebService方法:WebServiceAddCollectionDelegate代理回调
 *参数：
 *error:错误值，当错误值为WEBSERVICE_ERROR_NO_ERROR时，说明开启分享成功
 *alias:摄像机别名
 *cover_url：摄像机预览图
 */
-(void)on_add_collection_result:(WEBSERVICE_ERROR)error
alias:(NSString *)alias
cover_url:(NSString *)cover_url;

4)步骤：
账号添加（需要添加到服务器）：
第一步：添加分享的摄像机到服务器上，且添加代理WebServiceAddCollectionDelegate，监控添加结果
第二步：WebServiceAddCollectionDelegate代理回调，如服务器添加成功就直接添加本地

离线使用（只需要添加都本地）：
第一步：获取收藏摄像机的信息，且添加代理WebServiceGetCollectionDelegate。
第二步：WebServiceGetCollectionDelegate代理回调，如果获取成功就直接添加到本地。

5）注意：a)添加之前，必须确保了登陆了账号（或者update_user）且set_current_user了。
        b)分享的摄像机可以被多个账号添加，没有限制
6）示例：
账号添加（需要添加到服务器）
/*第一步：添加分享的摄像机到本地＋添加代理WebServiceAddCollectionDelegate*/
-(void)add_collection_to_service
{
    if (WEBSERVICE_ERROR_NO_ERROR != [[WebService get_share] add_collection:m_share_id delegate:self]) {
        /*添加失败*/
    }
}
/*第二步：WebServiceRemoveCollectionDelegate代理回调*/
-(void)on_add_collection_result:(WEBSERVICE_ERROR)error
alias:(NSString *)alias
cover_url:(NSString *)cover_url
{
    
    if (error == WEBSERVICE_ERROR_NO_ERROR){
        /*添加到服务器成功，然后添加到本地*/
        if ([[Storage get_share] add_collection:m_share_id alias:alias cover_url:cover_url]) {
            /*添加到本地成功*/

        } else {
            /*添加到本地失败*/
        }
    } else if(error == WEBSERVICE_ERROR_INVALID_SHARE_ID){
        /*分享id无效*/

    } else {
        /*到服务器失败*/
    }
}
离线使用（只需要添加都本地）
/*第一步：获取收藏摄像机的信息＋添加代理WebServiceGetCollectionDelegate*/
-(void)add_collection_to_service
{
    if (WEBSERVICE_ERROR_NO_ERROR != [[WebService get_share] get_collection:m_share_id delegate:self]) {
        /*获取失败*/
    }
}

/*第二步：WebServiceGetCollectionDelegate代理回调*/
-(void)on_get_collection_result:(WEBSERVICE_ERROR)error
alias:(NSString *)alias
cover_url:(NSString *)cover_url
{
    
    if (error == WEBSERVICE_ERROR_NO_ERROR){
        /*获取收藏摄像机信息成功，然后添加到本地*/
        if ([[Storage get_share] add_collection:m_share_id alias:alias cover_url:cover_url]) {
            /*添加到本地成功*/
            
        } else {
            /*添加到本地失败*/
        }
    } else if(error == WEBSERVICE_ERROR_INVALID_SHARE_ID){
        /*分享id无效*/
        
    } else {
        /*获取收藏摄像机信息失败*/
    }
}

#pragma mark －－16.5连接收藏摄像机（一次性连接）
16.5连接收藏摄像机（一次性连接）
1）说明：连接收藏摄像机是指：把收藏的摄像机连接，观看视频。在此采用一次性连接。

2）使用的类：IPCamMgr

3）函数：
/*
 *IPCamMgr方法：获取一次性摄像机
 *返回：
 *返回一个IPCam对象
 */
-(IPCam *)get_disposable_camera;//获取一次性摄像机

/*
 * IPCamMgr方法：设定一个一次性摄像机且自动连接
 *参数：
 *camera_id:摄像机id
 *user：摄像机登录名
 *pwd:摄像机登陆密码
 *https:摄像机安全传输值
 *返回:
 *返回一个BOOL，YES表示设置成功，No表示设置失败
 */

-(BOOL)set_disposable_camera:(NSString *)camera_id
user:(NSString *)user
pwd:(NSString *)pwd
https:(BOOL)https;//设定一次性摄像机

/*IPCamMgr方法：清除一次性摄像机*/
-(void)clear_disposable_camera;//清除一次性摄像机

/*IPCamMgr方法：更新一次性摄像机密码到IPCamMgr
 *返回一个BOOL，YES表示更新成功，No表示更新失败
 */
-(BOOL)update_disposable_camera_pwd:(NSString *)pwd;//

/*IPCamMgr方法：重连一次性摄像机
 *返回一个BOOL，YES表示执行函数成功，No表示执行函数失败
 */
-(BOOL)reset_disposable_camera;//重连一次性摄像机

5）注意点：a)连接就一个步骤，set_disposable_camera，摄像机的其它操作，比如看视频就和其它摄像机一样
         b)如果分享无效连接是不成功的。所以连接之前最好get_collection根据回调判断摄像机是否是有效分享
         c)不连接了一定要clear_disposable_camera

6）示列：
    [[IPCamMgr get_share] set_disposable_camera:camera_id user:m_user pwd:m_pwd https:https];

#pragma mark －－16.6删除收藏摄像机
16.6删除收藏摄像机
1)说明：删除收藏摄像机是只删除添加的收藏摄像机从服务器和本地。

2）使用的类：Storage，WebService

3）函数：
/*
 *Storage方法：删除当前账号本地收藏的摄像机
 *参数：
 *share_id:分享id
 */
-(void)remove_collection:(NSString *)share_id;

/*
 *WebService方法：删除当前账号服务器上收藏的摄像机
 *参数：
 *share_id:分享id
 *delegate:代理WebServiceRemoveCollectionDelegate
 *返回:
 *WEBSERVICE_ERROR：当返回值为WEBSERVICE_ERROR_NO_ERROR说明函数执行成功
 */
-(WEBSERVICE_ERROR)remove_collection:(NSString *)share_id
delegate:(id<WebServiceRemoveCollectionDelegate>)delegate;

/*
 *WebService方法：WebServiceRemoveCollectionDelegate代理回调函数
 *参数：
 *error:错误值，当错误值为WEBSERVICE_ERROR_NO_ERROR时，说明删除成功
 */
-(void)on_remove_collection_result:(WEBSERVICE_ERROR)error;
4）步骤：
第一步：删除服务器上的收藏摄像机，且添加代理WebServiceRemoveCollectionDelegate，监控删除结果
第二步：WebServiceRemoveCollectionDelegate代理回调，如服务器删除成功就直接删除本地

5）注意：a)未添加到服务器，即离线使用，直接删除本地remove_collection即可。
        b)这些方法的执行，前提是添加收藏的时候按照reecam的方式添加到本地添加到服务器。

6）示例：
/*第一步：删除服务器上的收藏摄像机＋添加代理WebServiceRemoveCollectionDelegate*/
-(void)delete_server
{
    if (WEBSERVICE_ERROR_NO_ERROR != [[WebService get_share] remove_collection:m_share_id delegate:self]) {
        /*删除失败*/
    }
}
/*第二步：WebServiceRemoveCollectionDelegate代理回调，如服务器删除成功就直接删除本地*/
-(void)on_remove_collection_result:(WEBSERVICE_ERROR)error
{
    if (error == WEBSERVICE_ERROR_NO_ERROR) {
        /*服务器删除成功，紧接着删除本地*/
        [[Storage get_share] remove_collection:m_share_id];//删除本地
    } else {
        /*删除失败*/
    }
}

#pragma －－16.7更新收藏摄像机本地信息
16.7更新收藏摄像机本地信息
1）说明：更新收藏摄像机本地信息是指：更新收藏摄像机的本地存储的信息，这些信息只保存到本地不会同步到服务器。

2）使用的类：Storage

3）函数：
/*
 *Storage方式：更新本地收藏摄像机是否有效
 *参数：
 *share_id:要被更新的收藏摄像机分享id
 *valid:收藏摄像机的是否有效。根据on_get_collection_camera_result获取的信息判断
 */
-(void)update_collection_valid:(NSString *)share_id
valid:(BOOL)valid;

/*
 *Storage方式：更新本地收藏摄像机的登录名
 *参数：
 *share_id:要被更新的收藏摄像机分享id
 *user:收藏摄像机的新的登陆名
 */
-(void)update_collection_user:(NSString *)share_id
user:(NSString *)user;

/*
 *Storage方式：更新本地收藏摄像机的登录名
 *参数：
 *share_id:要被更新的收藏摄像机分享id
 *pwd:收藏摄像机的新的登陆密码
 */
-(void)update_collection_pwd:(NSString *)share_id
pwd:(NSString *)pwd;

4）注意：a）分享摄像机是否还有效，是根据获取分享摄像机的回调结果中的error来判断的，详细参考on_get_collection_camera_result的用法
       b)这些方法都是基于瑞彩提供的存储方式存储的。

5）示例：
    Storage * storage = [Storage get_share];
    [[Storage get_share] update_collection_pwd:share_id pwd:new_pwd];

#pragma －－16.8获取服务器和本地收藏的摄像机
16.8获取服务器和本地收藏的摄像机
1)说明：获取服务器和本地收藏的摄像机是指：把添加到账号（服务器）或本地的分享出的摄像机获取出来显示操作。

2)使用的类：WebService，Storage

3)函数：
/*
 *WebService方法：从服务器获取账号收藏的所有摄像机
 *返回:返回一个NSArray，NSArray的每一个元素师一个字典，key/value如下：
 *share_id：分享id
 *alias：别名
 *cover_url:预览图的url
 */
-(NSArray *)get_collections_list;//WebService服务器收藏列表
                                                                                    
/*
 *Storage方法：从本地获取账号收藏的所有摄像机
 *返回一个数组，数组的每一个元素是一个字典，字典的key/value如下:
 *share_id:分享id，string类型
 *valid:是否为有效分享摄像机，bool类型.默认是YES
 *alias:摄像机昵称,string类型
 *user:摄像机登录名，string类型.默认是“guest”
 *pwd：摄像机登录密码，string类型,默认是""
 *cover_url：摄像机预览图url，string类型
 *recent:保留暂时不用，bool类型
 */
-(NSArray *)get_collections_list;//Storage本地收藏列表

/*
 *Storage方法：从本地获取指定收藏的摄像机信息
 *返回一个字典，字典的key/value如下:
 *share_id:分享id，string类型
 *valid:是否为有效分享摄像机，bool类型
 *alias:摄像机昵称,string类型
 *user:摄像机登录名，string类型
 *pwd：摄像机登录密码，string类型
 *cover_url：摄像机预览图url，string类型
 *recent:保留暂时不用，bool类型
 */
-(NSDictionary *)get_collection:(NSString *)share_id;
                                                                                    
/*
 *Storage方法：比较本地和服务器收藏的摄像机
 *参数：
 *server_collections_list:服务器收藏的摄像机列表
 *返回：返回一个BOOL参数
 *当BOOL值为YES时，表示本地和服务器的收藏摄像机一样
 *当BOOL值为NO时，表示本地和服务器的收藏摄像机不一样，且自动做同步
 */
-(BOOL)merge_collections_list:(NSArray *)server_collections_list;

4）注意：a）为提高程序性能，一般在AppDelegate就同步本地和服务器摄像机merge_collections_list。这样子，后面需要获取收藏摄像机，直接从本地Storage中获取。
        b）当然不需要使用服务器，只收藏在本地，用到的时候直接从本地Storage中获取。
        c)这些方法都是基于瑞彩提供的存储方式存储的。

5）示例
        WebService * webservice = [WebService get_share];
        Storage * storage = [Storage get_share];
        [storage merge_collections_list:[webservice get_collections_list]];
#pragma mark 17.TF卡相关操作

17.TF卡相关操作
说明：TF卡相关操作包括：tf卡操作和tf卡文件操作

#pragma mark －－17.1 tf卡操作
17.1 tf卡操作
说明：tf卡操作是指:弹出tf卡，格式化tf卡，获取tf卡的容量和状态
#pragma mark －－－－17.1.1 弹出tf卡
17.1.1 弹出tf卡
1）说明：弹出tf卡是指：把tf卡弹出磁盘，弹出之后，摄像机检测不到tf卡。

2）使用类：IPCam

3)函数：
/*
 *IPCam方法：弹出tf卡
 *参数：
 *delegate:IPCamUnplugTFDelegate
 *返回：返回IPCAM_ERROR类型，当返回IPCAM_ERROR_NO_ERROR，表示没有错误，调用成功
 */
-(IPCAM_ERROR)unplug_tf:(id<IPCamUnplugTFDelegate>)delegate;

/*
 *IPCam方法：IPCamUnplugTFDelegate回调
 *回调参数：
 *ipcam：返回一个id类型，其实就是一个IPCam
 *error:IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示弹出成功
 */
-(void)on_unplug_tf_result:(id)ipcam
error:(IPCAM_ERROR)error;

4)示例：
/*第一步：弹出tf卡＋添加代理IPCamUnplugTFDelegate */
[m_ipcam unplug_tf:self];

/*第二步：代理IPCamUnplugTFDelegate回调*/
-(void)on_unplug_tf_result:(id)ipcam
error:(IPCAM_ERROR)error {
    if (error == IPCAM_ERROR_NO_ERROR)
        [self show_error:LOCAL_STR(@"EJECT_TF_SUCCESS")];
    else
        [self show_error:LOCAL_STR(@"EJECT_TF_FAIL")];
}

#pragma mark －－－－17.1.2格式化tf卡
17.1.2格式化tf卡

1）说明：格式化tf卡是指把tf卡本摄像机的所有文件都删除

2）使用类：IPCam

3)函数：

/*
 *IPCam方法：格式化tf卡
 *参数：
 *delegate:IPCamFormatTFDelegate
 *返回：返回IPCAM_ERROR类型，当返回IPCAM_ERROR_NO_ERROR，表示没有错误，调用成功
 */
-(IPCAM_ERROR)format_tf:(id<IPCamFormatTFDelegate>)delegate;

/*
 *IPCam方法：IPCamFormatTFDelegate回调
 *回调参数：
 *ipcam：返回一个id类型，其实就是一个IPCam
 *error:IPCAM_ERROR类型，当返回是IPCAM_ERROR_NO_ERROR，表示弹出成功
 */
-(void)on_format_tf_result:(id)ipcam
error:(IPCAM_ERROR)error;

4）示列：

/*第一步：格式化tf卡＋添加代理IPCamFormatTFDelegate
 */
[m_ipcam format_tf:self];
/*第二步：代理IPCamFormatTFDelegate回调 */

-(void)on_format_tf_result:(id)ipcam
error:(IPCAM_ERROR)error {
    if (error == IPCAM_ERROR_NO_ERROR)
        [self show_error:LOCAL_STR(@"FORMAT_SUCCESS")];
    else
        [self show_error:LOCAL_STR(@"FORMAT_TF_FAIL")];
}

#pragma mark －－－－17.1.3tf卡状态和容量
17.1.3tf卡状态和容量
1）说明：tf卡状态和容量是指：查看tf状态和容量状态

2）使用类：IPCam

3)函数：
/*
 *IPCam方法：获取tf卡当前状态
 *返回：返回IPCAM_TF_STATUS类型，详细如下：
 *IPCAM_TF_STATUS_NONE:没有tf卡
 *IPCAM_TF_STATUS_READY:tf卡录像中
 *IPCAM_TF_STATUS_ERROR:tf卡错误
 *IPCAM_TF_STATUS_FULL:tf卡已满
 *IPCAM_TF_STATUS_CHECK:tf卡检测中
 */
-(IPCAM_TF_STATUS)tf_status;
/*
 *IPCam方法：获取tf当前剩余容量百分比
 *返回:返回int,返回0-100
 */
-(int)tf_free;

/*
 *IPCam方法：获取tf总容量
 *返回:返回float，单位MB
 */
-(float)sd_capactiy_total

4）示例：
    IPCAM_TF_STATUS tf = [ipcam tf_status];//状态
    int sd_disk = [ipcam tf_free]; //容量
    float sd_capacity_totly = [ipcam sd_capactiy_total]/1024; //总容量
    float sd_capacity_usered = sd_capacity_totly*sd_disk/100; //剩余容量


#pragma mark －－17.2tf卡文件列表 <下载所有文件／一天／一小时／一刻钟（预览图）>

17.2 tf卡文件列表

说明：获取tf卡文件是指获取tf卡内当前摄像机的，获取到刻钟。获取到每一刻钟录像文件的简单信息，包括时间，是否有文件，是否有报警，预览图等。录像文件是10s一个片段，我们把它组成15min一个文件来显示播放，即一个文件有90个小片段组成。
#pragma mark －－－－17.2.1 下载tf卡文件
17.2.1 下载tf卡文件（到刻钟）
1)说明：下载tf卡所有文件是指：从摄像机里面下载tf卡内当前摄像机所属的所有录像文件，到刻钟，获取简单的文件信息，需要网络和时间。对摄像机文件操作必须先load_tf_records。

2)使用类：IPCam

3)函数：
/*
 *IPCam方法：下载所有的录像文件（到刻钟）
 *参数：
 *delegate:IPCamLoadTFRecordsDelegate
 *返回:
 *返回IPCAM_ERROR类型，当返回的!IPCAM_ERROR_NO_ERROR表示下载失败
 */
-(IPCAM_ERROR)load_tf_records:(id<IPCamLoadTFRecordsDelegate>)delegate;

/*
 *IPCam方法：IPCamLoadTFRecordsDelegate回调
 *参数函数：
 *ipcam:返回当前摄像机
 *error:错误值，返回IPCAM_ERROR类型，当返回的IPCAM_ERROR_NO_ERROR表示获取成功。
 */
-(void)on_load_tf_records_result:(id)ipcam
error:(IPCAM_ERROR)error;

/*
 *IPCam方法：停止load_tf_records
 */
-(void)clear_tf_records;

4)注意：a)进行tf卡文件操作，必须先成功load_tf_records,就像使用使用libSoSoCamSDK之前必须成功初始化SDK。
       b)clear_tf_records与cancel_tf_record_tasks不同，它除了取消tf卡所有的操作，同时把存储录像文件信息的数组释放了。所以一旦clear_tf_records，必须要先load_tf_records才做tf文件其他操作
       c)当完全不需要tf卡文件操作时才clear_tf_records，而不是load_tf_records完成后就可clear_tf_records。所以clear_tf_records前肯定需要cancel_tf_record_tasks，但是cancel_tf_record_tasks不一定会去clear_tf_records。

#pragma mark －－－－17.2.2 获取一天文件
17.2.2 获取一天文件

1)说明：获取一天文件是指：获取某一天的录像文件，只是简单的获取某一个信息即可，信息在load_tf_records的时候已经下载下来，所以不需要占用时间和网络什么的。主要包含当天是否有录像文件，当天是否有报警等。

2)使用类：IPCam

3)函数：
/*
 *IPCam方法：获取每天的录像文件
 *参数：
 *day：获取哪一天的录像文件，范围[0，7)，总共7天，只保留最近7天的录像文件
 *
 *返回：返回一个NSDictionary，其key/value如下：
 *valid:当天是否有录像文件，类型NSNumber（BOOL),YES:有录像文件，NO:无录像文件
 *alarm:当天是否有报警，类型NSNumber（BOOL）,YES:有报警，NO:无报警
 *week:星期几，类型NSNumber（int），1至7分别代表星期天到星期五
 *today:今天，类型NSNumber（BOOL），YES:是今天，NO:不是今天
 *yesterday:昨天，类型NSNumber（BOOL），YES:是昨天，NO:不是昨天
 *dby/:前天，类型NSNumber（BOOL），YES:是前天，NO:不是前天
 *valid_hours:当前，此小时有没有录像文件，类型NSNumber（int）
 *
 */
-(NSDictionary *)get_tf_record_day_info:(int)day;

4)注意：必须要load_tf_records成功后才能get_tf_record_day_info

#pragma mark －－－－17.2.3 获取一小时文件
17.2.3 获取一小时文件
1)说明：获取一小时文件是指获取某一天某一个小时的的录像文件，只是简单的获取某一个信息即可，信息在load_tf_records的时候已经下载下来，所以不需要占用时间和网络什么的。

2)使用类：IPCam

3)函数：
/*
 *IPCam方法：获取第几天第几个小时的录像文件
 *参数：
 *day:第几天，共7天，范围［0，7）
 *hour：第几个小时，共24个小时，返回［0，24）
 *返回：
 *返回一个BOOL，YES表示执行成功，NO表示执行失败
 */

-(BOOL)get_tf_record_hour_valid:(int)day
hour:(int)hour;

4）注意：a)必须要load_tf_records成功后才能get_tf_record_day_info
        b)一般是get_tf_record_day_info成功后，判断valid有文件才去get_tf_record_hour_valid

#pragma mark －－－－17.2.4 17.2.4 获取一刻钟录像信息
17.2.4 获取一刻钟录像信息

1)说明：获取一刻钟录像信息是指:获取某一天某一小时某一刻钟的录像文件，只是简单的获取某一个信息即可，信息在load_tf_records的时候已经下载下来，所以不需要占用时间和网络什么的。此处只是简单的获取当前刻钟是否有录像文件，是否有报警。

2)使用的类：IPCam

3)函数：
/*
 *
 *IPCam方法：获取第几天第几个小时第几刻钟的录像文件
 *参数：
 *day:第几天，共7天，范围［0，7）
 *hour：第几个小时，共24个小时，范围[0，24)
 *quarter:第几刻钟，共4刻钟，范围[0,4)
 *
 *返回：返回一个NSDictionary，key/value如下:
 *valid:当前一刻钟是否有录像文件，类型NSNumber（BOOL）,YES:有文件，NO:没有文件
 *alarm:当前一刻钟是否有报警，类型NSNumber（BOOL）,YES:有报警，NO:没有报警
 */
-(NSDictionary *)get_tf_record_quarter_info:(int)day
hour:(int)hour
quarter:(int)quarter;

4）注意：必须是get_tf_record_hour_valid成功后，再去获取

5)示例：

#pragma mark －－－－17.2.5 获取一刻钟的录像预览图
17.2.5 获取一刻钟的录像预览图

1）说明：获取一刻钟的录像预览图是指获取某一小时内某一刻钟录像文件的预览图，原则是取最靠近这一刻钟的预览图

2）使用类：IPCam

3）函数：

/*
 *IPCam方法：获取第几天第几个小时第几刻钟的录像录像预览图
 *参数：
 *day:第几天，共7天，范围［0，7）
 *hour：第几个小时，共24个小时，范围[0，24)
 *valid_hour_index:
 *quarter:第几刻钟，共4刻钟，范围[0,4)
 *delegate:IPCamGetTFRecordQuarterThumbDelegate
 */

-(IPCAM_ERROR)get_tf_record_quarter_thumb:(int)day
hour:(int)hour
valid_hour_index:(int)valid_hour_index
quarter:(int)quarter
delegate:(id<IPCamGetTFRecordQuarterThumbDelegate>)delegate;

/*
 *IPCam方法：IPCamGetTFRecordQuarterThumbDelegate回调
 *返回参数：
 *ipcam:摄像机
 *day:第几天，共7天，范围［0，7）
 *hour：第几个小时，共24个小时，范围[0，24)
 *valid_hour_index:
 *quarter:第几刻钟，共4刻钟，范围[0,4)
 *thumb：预览图数据
 */
-(void)on_get_tf_record_quarter_thumb_result:(id)ipcam
day:(int)day
hour:(int)hour
valid_hour_index:(int)valid_hour_index
quarter:(int)quarter
thumb:(NSData *)thumb;

4)注意：a)必须是get_tf_record_quarter_info成功后再去获取。

17.2.6 示例

/*第一步：下载tf卡文件*/
-(void)load_record{
    if (IPCAM_ERROR_NO_ERROR != [m_ipcam load_tf_records:self]) {
        //下载tf卡文件失败
    }
}

/*第二步：load_record回调成功后，先后获去天／时／刻录像文件信息*/
-(void)on_load_tf_records_result:(id)ipcam
error:(IPCAM_ERROR)error
{
    if (error != IPCAM_ERROR_NO_ERROR) {
        //下载tf卡文件失败
        return;
    }
    //load_record成功后开始获取7天的录像文件
    NSMutableDictionary * day;
    NSMutableArray * hours;
    NSMutableDictionary * hour;
    NSMutableArray * quarters;
    NSMutableDictionary * quarter;
    int i;
    int h;
    int q;
    for (i = 0;i < 7;i ++) {
        /*
         *2.1 分别获取7天的录像文件
         */
        day = [[NSMutableDictionary alloc] initWithDictionary:[m_ipcam get_tf_record_day_info:i]];
        if ([[day objectForKey:@"valid"] boolValue]) {
            //当天有录像文件
        } else {
            //当天无录像文件
        }
        if ([[day objectForKey:@"today"] boolValue]) {
            //第i天是今天
        } else if ([[day objectForKey:@"yesterday"] boolValue]) {
            //第i天是昨天
        }else if([[day objectForKey:@"dby"] boolValue]) {
            //第i天是前天
        }else {
            if ([[day objectForKey:@"week"] intValue] == 1) {
                //第i天是星期天
            } else if ([[day objectForKey:@"week"] intValue] == 2) {
                //第i天是周一
            } if ([[day objectForKey:@"week"] intValue] == 3) {
                //第i天是周二
            } if ([[day objectForKey:@"week"] intValue] == 4) {
                //第i天是周三
            } if ([[day objectForKey:@"week"] intValue] == 5) {
                //第i天是周四
            } if ([[day objectForKey:@"week"] intValue] == 6) {
                //第i天是周五
            } if ([[day objectForKey:@"week"] intValue] == 7) {
                //第i天是周六
            }
        }
        //获取当天有录像文件开始获取当天24小时录像文件
        if ([[day objectForKey:@"valid"] boolValue]) {
            hours = [[NSMutableArray alloc] init];
            for (h = 0;h < 24;h ++) {
                /*
                 *2.2 分别获取每一天24小时的录像文件
                 */
                if ([m_ipcam get_tf_record_hour_valid:i hour:h]) {
                    hour = [[NSMutableDictionary alloc] init];
                    [hour setValue:[NSNumber numberWithInt:h] forKey:@"hour"];
                    quarters = [[NSMutableArray alloc] init];
                    for (q = 0;q < 4;q ++) {
                        /*
                         *2.3 分别获去一刻钟录像文件信息
                         */
                        quarter = [[NSMutableDictionary alloc] initWithDictionary:[m_ipcam get_tf_record_quarter_info:i hour:h quarter:q]];
                        if ([[quarter objectForKey:@"valid"] boolValue]){
                            //当前刻钟有录像文件
                        }
                        else{
                            //当前刻钟无录像文件
                        }
                        if ([[quarter objectForKey:@"alarm"] boolValue]){
                            //当前刻钟有报警
                        }
                        else{
                            //当前刻钟无报警
                        }
                    }
                }
                [m_collectionview_records reloadData];
            }
        }
    }
}
/*第三步：获取刻成功后，获取每小时每刻的预览图*/

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath
{
    UINib * nib = [UINib nibWithNibName:@"TFRecordListCollectionViewCell" bundle:nil];
    [collectionView registerNib:nib forCellWithReuseIdentifier:CELL_ID];
    
    TFRecordListCollectionViewCell * cell = (TFRecordListCollectionViewCell *)[collectionView dequeueReusableCellWithReuseIdentifier:CELL_ID forIndexPath:indexPath];
    cell.delegate = self;
    
    NSMutableArray * hours = [[m_records_list objectAtIndex:m_current_day] objectForKey:@"hours"];
    NSMutableDictionary * hour = [hours objectAtIndex:indexPath.row];
    int q;
    NSMutableDictionary * quarter;
    for (q = 0;q < 4;q ++) {
        quarter = [[hour objectForKey:@"quarters"] objectAtIndex:q];
        if ([[quarter objectForKey:@"load_state"] intValue] == LOAD_STATE_UNLOAD) {
            /*分别获去每一刻钟的预览图*/
            if (IPCAM_ERROR_NO_ERROR == [m_ipcam get_tf_record_quarter_thumb:m_current_day hour:[[hour objectForKey:@"hour"] intValue] valid_hour_index:(int)indexPath.row quarter:q delegate:self])
                [quarter setValue:[NSNumber numberWithInt:LOAD_STATE_LOADING] forKey:@"load_state"];
            else {
                NSLog(@"error 1");
                [quarter setValue:[NSNumber numberWithInt:LOAD_STATE_LOADED] forKey:@"load_state"];
            }
        }
    }
    
    return cell;
}


/*第四步：获取预览图回调 */
-(void)on_get_tf_record_quarter_thumb_result:(id)ipcam
day:(int)day
hour:(int)hour
valid_hour_index:(int)valid_hour_index
quarter:(int)quarter
thumb:(NSData *)thumb
{
    if (! thumb){
        UIImage * coverImage = [UIImage imageWithData:thumb];
    }
}


#pragma mark 17.3播放tf卡文件<三中播放tf卡文件方式／上／下一个文件播放
>

17.3.1 三种播放tf卡文件方法
1）说明：播放tf卡录像文件是指播放当前摄像机存储在tf卡内的录像文件。有三种方式可以获取到录像文件。
2）使用类：IPCam
3）函数：
/*
 *IPCam方法：播放录像文件，从某一日日期开始
 *播放距离此日期最近的录像文件
 *SOSOCAM在播放报警录像的时候又用到
 *返回：
 *返回一个int32_t类型，就是播放的录像文件id
 */
-(int32_t)get_tf_record_play_id:(NSDate *)date;

/*
 *IPCam方法：播放录像文件，从某一刻钟开始
 *SOSOCAM在点击某一刻钟直接播放时用到
 *参数：
 *day:播放哪一天，范围［0，7）
 *hour:播放哪一小时，范围［0，24）
 *quarter:播放哪一个刻钟，范围［0，4）
 *返回：
 *返回一个int32_t类型，就是播放的录像文件id
 */

-(int32_t)get_tf_record_play_id_of_quarter:(int)day
hour:(int)hour
quarter:(int)quarter;

/*
 *IPCam方法：播放录像文件，从某一刻钟某10s的开始
 *SOSOCAM在播放的时候拖动进度条的时候用到
 *参数：
 *day:播放哪一天，范围［0，7）
 *hour:播放哪一小时，范围［0，24）
 *quarter:播放哪一个刻钟，范围［0，4）
 *no:播放刻钟的哪一个片段，范围［0，90）
 *返回：
 *返回一个int32_t类型，就是播放的录像文件id
 */
-(int32_t)get_tf_record_play_id_of_no:(int)day
hour:(int)hour
quarter:(int)quarter
no:(int)no;

/*
 *IPCam方法：播放tf卡录像文件
 *
 */
-(IPCAM_ERROR)play_tf_record:(int)tf_record_id;


/*
 *IPCam方法：IPCamDelegate代理方法之tf录像事件监控
 *当有新录像文件生成或录像文件出错时会掉用此方法
 *SOSOCAM在播放tf卡录像文件是使用了此代理
 *使用方法：参考IPCam基础代理
 *回调参数：
 *ipcam：摄像机
 *new_record:是否是新生成的录像文件,YES:是，NO:否
 *record_id：录像文件开始id
 *error:是否有错误，YES:是，NO:否
 *
 */
-(void)on_tf_record_event:(id)ipcam
new_record:(BOOL)new_record
record_id:(int32_t)record_id
error:(BOOL)error;

4）注意：a）这些操作必须以摄像机连接成功为前提
        b)播放完之后会自动切换播放下一个刻钟的的录像文件
        c)只支持soso固件

5）示例

    [m_ipcam get_tf_record_play_id:date];//从某个时间最近的时间开始播放

    [m_ipcam play_tf_record:[m_ipcam get_tf_record_play_id_of_quarter:0 hour:2 quarter:2]];//从某一刻开始播放

    [m_ipcam play_tf_record:[m_ipcam get_tf_record_play_id_of_no:1 hour:6 quarter:3 no:65]];//从某一刻钟某10s的开始播放


17.3.2tf卡文件播放停止／暂停／续播／TF卡录像播放状态

1）说明：tf卡文件播放停止／暂停／续播／TF卡录像播放状态分别指：停止tf卡录像播放，暂停tf卡录像播放，暂停后继续播放，以及随时获取TF卡录像播放状态。

2）使用类：IPCam

3）函数

/*
 *IPCam方法：tf卡录像播放状态
 *返回：返回IPCAM_TF_RECORD_STATUS，详细如下
 */
-(IPCAM_TF_RECORD_STATUS)tf_record_status //tf播放状态
typedef enum {
    IPCAM_TF_RECORD_STATUS_STOPPED, //停止
    IPCAM_TF_RECORD_STATUS_REQUESTING,//请求
    IPCAM_TF_RECORD_STATUS_PLAYING,//播放
    IPCAM_TF_RECORD_STATUS_BUFFING, //缓冲
    IPCAM_TF_RECORD_STATUS_PAUSING, //暂停
} IPCAM_TF_RECORD_STATUS;


/*
 *IPCam方法：IPCamDelegate代理方法之tf播放状态监控
 *使用方法：参考IPCam
 */

-(void)on_tf_record_status_changed:(id)ipcam;

/*
 *IPCam方法：停止播放tf卡录像文件
 */
-(void)stop_tf_record;//停止播放

/*
 *IPCam方法：暂停播放tf卡录像文件
 *返回:
 *返回IPCAM_ERROR类型，当返回IPCAM_ERROR_NO_ERROR时，表示暂停成功
 */
-(IPCAM_ERROR)pause_tf_record;//暂停

/*
 *IPCam方法：继续播放tf卡录像文件
 *返回:
 *返回IPCAM_ERROR类型，当返回IPCAM_ERROR_NO_ERROR时，表示继续播放成功
 */
-(IPCAM_ERROR)continue_tf_record; //继续播放

4）注意：a）这些操作必须以摄像机连接成功为前提
        b)只支持SOSO固件

5）示例

    IPCAM_TF_RECORD_STATUS status = [m_ipcam tf_record_status]; //状态

    [m_ipcam continue_tf_record];//继续播放

    [m_ipcam pause_tf_record]; //暂停

    [m_ipcam stop_tf_record];//停止


17.3.3 上／下一个tf卡录像文件播放

1)说明：上／下一个tf卡录像文件播放是指：播放当前录像文件的上一个tf卡录像文件和下一个tf卡录像文件

2）使用类：IPCam

3）函数
/*
 *IPCam方法：播放下一个文件
 *参数：
 *day:当前天，类型NSNumber（int），范围［0，7）
 *hour:当前小时，类型NSNumber（int），范围［0，24）
 *quarter:当前刻钟，类型NSNumber（int）范围［0，4）
 *
 *返回：返回下一个文件的时间，是一个字典，其key/value如下:
 *day:下一个播放录像天，范围［0，7）,类型 NSNumber（int）
 *hour:下一个播放录像小时，范围［0，24）,类型 NSNumber（int）
 *quarter:下一个播放录像刻钟，范围［0，7）,类型 NSNumber（int）
 */
-(NSDictionary *)get_next_tf_record_quarter_time:(int)day
hour:(int)hour
quarter:(int)quarter;

/*
 *IPCam方法：播放上一个文件
 *参数：
 *day:当前天，类型NSNumber（int），范围［0，7）
 *hour:当前小时，类型NSNumber（int），范围［0，24）
 *quarter:当前刻钟，类型NSNumber（int）范围［0，4）
 *
 *返回：返回上一个文件的时间，是一个字典，其key/value如下:
 *day:上一个播放录像天，范围［0，7）,类型 NSNumber（int）
 *hour:上一个播放录像小时，范围［0，24）,类型 NSNumber（int）
 *quarter:上一个播放录像刻钟，范围［0，7）,类型 NSNumber（int）
 */
-(NSDictionary *)get_previous_tf_record_quarter_time:(int)day
hour:(int)hour
quarter:(int)quarter;


4）注意：a）这些操作必须以摄像机连接成功为前提
        b)只支持SOSO固件
        c)播放之前，如果当前录像文件正在播放，需要先stop_tf_record

5）示例
/*播放上一个tf卡录像文件*/
- (void)button_previous_onclicked:(id)sender {
    NSDictionary * t = [m_ipcam get_previous_tf_record_quarter_time:m_day hour:m_hour quarter:m_quarter]; //根据当前时间获取上一个文件的时间
    if (t == nil)
        return;
    m_day = [[t objectForKey:@"day"] intValue];
    m_hour = [[t objectForKey:@"hour"] intValue];
    m_quarter = [[t objectForKey:@"quarter"] intValue];
    
    [m_ipcam stop_tf_record];//先停止播放当前文件
    [m_ipcam play_tf_record:[m_ipcam get_tf_record_play_id_of_quarter:m_day hour:m_hour quarter:m_quarter]];//播放上一个文件
}
/*播放下一个tf卡录像文件*/
- (void)button_next_onclicked:(id)sender {
    NSDictionary * t = [m_ipcam get_next_tf_record_quarter_time:m_day hour:m_hour quarter:m_quarter];//根据当前时间获取下一个文件的时间
    if (t == nil)
        return;
    m_day = [[t objectForKey:@"day"] intValue];
    m_hour = [[t objectForKey:@"hour"] intValue];
    m_quarter = [[t objectForKey:@"quarter"] intValue];
    
    [m_ipcam stop_tf_record];//先停止播放当前文件
    [m_ipcam play_tf_record:[m_ipcam get_tf_record_play_id_of_quarter:m_day hour:m_hour quarter:m_quarter]];//播放下一个文件
}

17.3.4下载tf卡录像文件
1)说明：下载tf卡录像文件是指把当前摄像机存储在tf的录像文件下载到app相册，tf录像文件是以每10s一个文件.bin 格式存储到tf卡的，且以刻钟为节点，每个刻钟90个文件。下载tf卡录像文件，实际上是一遍播放.bin 文件，一遍录制成.mov格式文件,根据设置的record_performance_speed数值，播放速度不一样，如果record_performance_speed不为0，录像是跳跃式播放的，录下来的文件也是取关键帧录制的。

2）使用类：IPCam

3）函数

/*
 *IPCam方法：
 */
-(IPCAM_ERROR)enable_tf_record_download_mode:(BOOL)enabled;


/*
 *IPCam方法：设置播放（下载）速度
 *参数
 *speed：播放（下载速度），有四个值
 *0:对应sosocam的1x,正常播放（下载）
 *3:对应sosocam的8x,跳跃播放（下载）
 *4:对应sosocam的16x,跳跃播放（下载）
 *5:对应sosocam的32x,跳跃播放（下载）
 */
-(void)set_record_performance_speed:(int)speed; //设置播放（下载）速度

/*
 *IPCam方法：播放（下载）速度
 *返回
 *speed：返回一个int数值
 *0:对应sosocam的1x,正常播放（下载）
 *3:对应sosocam的8x,跳跃播放（下载）
 *4:对应sosocam的16x,跳跃播放（下载）
 *5:对应sosocam的32x,跳跃播放（下载）
 */
-(int)record_performance_speed //播放（下载）速度

4）注意：a）这些操作必须以摄像机连接成功为前提
        b)只支持SOSO固件

5）示例

/*示例一：设置（播放）下载tf卡录像文件速度*/
- (void)button_slower_onclicked:(id)sender {
    /*这里示范的是减速设置*/
    int speed = [m_ipcam record_performance_speed]; //获取当前播放（下载）速度
    if (speed == 3) {
        speed = 0;
        m_label_speed.text = @"1X";
    } else if (speed == 4) {
        speed = 3;
        m_label_speed.text = @"8X";
    } else if (speed == 5) {
        speed = 4;
        m_label_speed.text = @"16X";
    } else {
        return;
    }
    
    [m_ipcam stop_tf_record];//先停止播放
    [m_ipcam set_record_performance_speed:speed];//设置播放（下载）速度
    /*
     *重新以新的速度播放
     *如果此时正在录像，不需要先停下来在重新开启录像
     *视频怎么播放的，录像就怎么路的，即播放的了那些片段就录制了哪些片段
     */
    [m_ipcam play_tf_record:[m_ipcam get_tf_record_play_id_of_no:m_day hour:m_hour quarter:m_quarter no:m_no]];
}
/*示例二：下载下载tf卡录像文件*/
- (void)button_download_onclicked:(id)sender {
    if ([m_ipcam local_record_status] == IPCAM_PLAY_STATUS_STOPPED) {
        /*开启录像，录制.mov格式到app相册，即下载tf卡录像文件*/
        if (IPCAM_ERROR_NO_ERROR == [m_ipcam start_local_record]) {
            
            [m_ipcam enable_tf_record_download_mode:YES];//
            
        }
    } else {
        /*停止录像，即停止下载tf卡录像文件*/
        [m_ipcam stop_local_record];//
        [m_ipcam enable_tf_record_download_mode:NO];
    }
}

17.3.5 获取10s录像信息
1)说明：获取10s录像信息是指：获取每个10s文件的录像时间，获取每个10s录像文件的预览图，获取每个10s录像文件的报警信息等

2）使用类：IPCam

3）函数
/*
 *IPCam方法：获取一刻钟的某一个10s录像文件时间
 *
 *参数：
 *subrecord_id
 *返回：返回一个NSDictionary，key/value如下:
 *day:天，类型NSNumber（int）
 *hour:时，类型NSNumber（int）
 *quarter:刻钟，类型NSNumber（int）
 *no:刻钟的第几个10s,类型NSNumber（int）
 */
-(NSDictionary *)get_tf_record_clip_time:(int)subrecord_id;


/*
 *IPCam方法：获取一刻钟的某一个10s录像预览图图
 *参数：
 *day:第几天，共7天，范围［0，7）
 *hour：第几个小时，共24个小时，范围[0，24)
 *quarter:第几刻钟，共4刻钟，范围[0,4)
 *no:第几个10s,15分钟，10s中一个文件，共90个文件，范围[0,90)
 *delegate:IPCamGetTFRecordClipThumbDelegate
 *返回：
 */
-(IPCAM_ERROR)get_tf_record_clip_thumb:(int)day
hour:(int)hour
quarter:(int)quarter
no:(int)no
delegate:(id<IPCamGetTFRecordClipThumbDelegate>)delegate;

/*
 *IPCam方法：IPCamGetTFRecordClipThumbDelegate回调
 *返回参数：
 *ipcam:摄像机
 *day:第几天，共7天，范围［0，7）
 *hour：第几个小时，共24个小时，范围[0，24)
 *quarter:第几刻钟，共4刻钟，范围[0,4)
 *no:第几个10s,15分钟，10s中一个文件，共90个文件，范围[0,90)
 *thumb：预览图数据
 */
-(void)on_get_tf_record_clip_thumb_result:(id)ipcam
day:(int)day
hour:(int)hour
quarter:(int)quarter
no:(int)no
thumb:(NSData *)thumb;


/*
 *IPCam方法：获取某一刻钟90个10s录像文件报警信息
 *
 *参数：
 *day:天，范围［0，7）,类型 NSNumber（int）
 *hour:小时，范围［0，24）,类型 NSNumber（int）
 *quarter:刻钟，范围［0，7）,类型 NSNumber（int）
 *delegate:代理IPCamGetTFRecordQuarterDetailDelegate
 */

-(IPCAM_ERROR)get_tf_record_quarter_detail:(int)day
hour:(int)hour
quarter:(int)quarter
delegate:(id<IPCamGetTFRecordQuarterDetailDelegate>)delegate;


/*
 *IPCam方法：IPCamGetTFRecordQuarterDetailDelegate回调
 *
 *返回:
 *ipcam:摄像机
 *day:天
 *hour:时
 *clips:90个10s的录像文件信息，key/value如下：
 *  valid:当前刻钟是否有录像文件，类型NSNumber(BOOL)
 *  thumb:当前刻钟是否有预览图，类型NSNumber(BOOL)
 *  alarm:当前刻钟是否有报警，类型NSNumber(int32_t）
 */
-(void)on_get_tf_record_quarter_detail_result:(id)ipcam
day:(int)day
hour:(int)hour
quarter:(int)quarter
clips:(NSArray *)clips;

4)示例

/* 示例一：获取某一刻的90个文件的信息*/
 [m_ipcam get_tf_record_quarter_detail:m_day hour:m_hour quarter:m_quarter delegate:self];

//IPCamGetTFRecordQuarterDetailDelegate回调
-(void)on_get_tf_record_quarter_detail_result:(id)ipcam
day:(int)day
hour:(int)hour
quarter:(int)quarter
clips:(NSArray *)clips{
    if (clips == nil) {
    }
    else {
        NSDictionary * clip;
        for (i = 0;i < 90;i ++) {
            clip = [[NSMutableDictionary alloc] initWithDictionary:[clips objectAtIndex:i]];
            if (! [[clip objectForKey:@"valid"] boolValue]){
                //此10s文件有录像文件
            }
            else if (! [[clip objectForKey:@"alarm"] intValue]){
                //此10s文件有录像文件+且有报警
            }
            else{
                //此10s文件有录像文件+无报警
            }
        }
    }
}


/* 示例二：通过播放id获取当前文件时间*/

NSDictionary * t = [m_ipcam get_tf_record_clip_time:record_id];
m_day = [[t objectForKey:@"day"] intValue];//天
m_hour = [[t objectForKey:@"hour"] intValue];//时间
m_quarter = [[t objectForKey:@"quarter"] intValue];//刻钟
m_no = [[t objectForKey:@"no"] intValue];//第几个10秒

int minutes = quarter * 15 + no / 6;
int seconds = (m_no * 10) % 60;

NSString *time = [NSString stringWithFormat:@"%02d:%02d:%02d", hour, minutes, seconds];

/*示例三：通过获取10s文件预览图*/
[m_ipcam get_tf_record_clip_thumb:m_day hour:m_hour quarter:m_quarter no:m_seeking_no delegate:self];

//IPCamGetTFRecordClipThumbDelegate回调
-(void)on_get_tf_record_clip_thumb_result:(id)ipcam
day:(int)day
hour:(int)hour
quarter:(int)quarter
no:(int)no
thumb:(NSData *)thumb
{
    if (thumb == nil) {
        m_imageview_clip_thumb.image = nil;
    } else {
        m_imageview_clip_thumb.image = [UIImage imageWithData:thumb];
    }

}

17.4.6取消tf卡录像文件的所有操作
1）说明：取消tf卡录像文件的所有操作是指把tf录像相关操作全部取消，除了load_tf_records。如果想要继续操作tf卡录像文件，直接操作就好不需要重新load_tf_records。
2）使用类：IPCam

3）函数：
/*
 *IPCam方法：取消tf卡录像文件的所有操作
 */
-(void)cancel_tf_record_tasks;

4)示例
    [m_ipcam cancel_tf_record_tasks];




